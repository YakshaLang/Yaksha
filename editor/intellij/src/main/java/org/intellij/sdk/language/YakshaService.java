package org.intellij.sdk.language;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import com.google.gson.reflect.TypeToken;
import org.intellij.sdk.language.tw.YakshaToolWindow;
import org.intellij.sdk.language.utilities.FileLogger;
import org.intellij.sdk.language.yaksha_docs.YakshaDocs;

import java.io.IOException;
import java.lang.reflect.Type;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.List;
import java.util.Map;
import java.util.Queue;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.TimeUnit;

public class YakshaService implements Runnable {
    private static final FileLogger LOGGER = FileLogger.getInstance();
    private static final ConcurrentHashMap<String, Map<String, YakshaDocs.Doc>> DUMP_CACHE =
            new ConcurrentHashMap<>();
    private static final Gson GSON = new GsonBuilder().create();
    private static final Type DUMP_TYPE = new TypeToken<Map<String, YakshaDocs.Doc>>() {
    }.getType();
    public static Boolean isRunning = true;
    private final Queue<String> queuePoke;

    public YakshaService(final Queue<String> poke) {
        super();
        this.queuePoke = poke;
        LOGGER.info("Setting up YakshaService for autocompletion");
        final Thread t = new Thread(this);
        t.setDaemon(true);
        t.start();
    }

    public static Map<String, YakshaDocs.Doc> findDumpDataForFile(String filePath) {
        if (filePath == null) return Collections.emptyMap();
        for (Map.Entry<String, Map<String, YakshaDocs.Doc>> entry : DUMP_CACHE.entrySet()) {
            if (filePath.startsWith(entry.getKey())) {
                return entry.getValue();
            }
        }
        return Collections.emptyMap();
    }

    @Override
    public void run() {
        while (isRunning) {
            final String q = queuePoke.poll();
            if (q == null) {
                try {
                    Thread.sleep(300);
                } catch (InterruptedException e) {
                    Thread.currentThread().interrupt();
                    throw new RuntimeException(e);
                }
                continue;
            }
            processFile(q);
        }
    }

    public void processFile(final String file) {
        LOGGER.info("Processing file:", file);
        final var compiler = YakshaToolWindow.YAKSHA_EXE_PATH;
        if (compiler.isBlank()) {
            LOGGER.error("Yaksha compiler path is not set");
            return;
        }
        final var fpath = Paths.get(file);
        final var dir = fpath.getParent().toString();
        final var mainFile = Paths.get(dir, "main.yaka");
        if (!mainFile.toFile().exists()) {
            LOGGER.error("main.yaka file not found in the directory:", dir);
            return;
        }
        // dump -a -i -p main.yaka
        final List<String> command = List.of(compiler, "dump", "-a", "-i", "-p", mainFile.toString());
        try {
            Process process = new ProcessBuilder(command)
                    .directory(Paths.get(dir).toFile())
                    .redirectErrorStream(true)
                    .start();
            process.waitFor(60, TimeUnit.SECONDS);

            String output = new String(process.getInputStream().readAllBytes());
            if (output.isBlank()) {
                LOGGER.info("No output from Yaksha compiler");
                return;
            }

            Map<String, YakshaDocs.Doc> dumpData = GSON.fromJson(output, DUMP_TYPE);
            if (dumpData != null) {
                DUMP_CACHE.put(dir, dumpData);
                LOGGER.info("Cached dump data for: " + dir + " (" + dumpData.size() + " entries)");
            }
        } catch (IOException e) {
            LOGGER.error("Failed to start process", e.getMessage());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        } catch (Exception e) {
            LOGGER.error("Failed to parse dump output", e.getMessage());
        }
    }
}
