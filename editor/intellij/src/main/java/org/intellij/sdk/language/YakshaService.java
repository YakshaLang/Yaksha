package org.intellij.sdk.language;

import org.intellij.sdk.language.tw.YakshaToolWindow;
import org.intellij.sdk.language.utilities.FileLogger;

import java.io.IOException;
import java.nio.file.Paths;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.TimeUnit;

public class YakshaService implements Runnable {
    private static final FileLogger LOGGER = FileLogger.getInstance();
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
        final Process process;
        try {
            process = new ProcessBuilder(command).directory(Paths.get(dir).toFile()).redirectErrorStream(true).start();
            process.waitFor(60, TimeUnit.SECONDS);

            String output = new String(process.getInputStream().readAllBytes());
            if (output.isBlank()) {
                LOGGER.info("No output from Yaksha compiler");
                return;
            }
        } catch (IOException e) {
            LOGGER.error("Failed to start process", e.getMessage());
        } catch (InterruptedException e) {
            Thread.currentThread().interrupt();
            throw new RuntimeException(e);
        }


    }
}
