package org.intellij.sdk.language.utilities;

import java.io.BufferedOutputStream;
import java.io.FileOutputStream;
import java.io.OutputStream;
import java.nio.file.Paths;
import java.time.LocalDateTime;

public enum FileLogger {

    INSTANCE;

    private final OutputStream outputStream;

    public static FileLogger getInstance() {
        return INSTANCE;
    }

    FileLogger() {
        String HOME_DIRECTORY = System.getProperty("user.home");
        String LOG_FILENAME = "yaksha.intellij.log.txt";
        String LOG_FILE_PATH = Paths.get(HOME_DIRECTORY, LOG_FILENAME).toString();
        Paths.get(LOG_FILE_PATH).toFile().delete();
        try {
            outputStream = new BufferedOutputStream(new FileOutputStream(LOG_FILE_PATH));
            System.out.println("Log file created at: " + LOG_FILE_PATH);
        } catch (Exception e) {
            throw new RuntimeException("Failed to open log file", e);
        }
    }

    public void error(String... messages) {
        this.log("[EROR]", messages);
    }

    public void info(String... messages) {
        this.log("[INFO]", messages);
    }

    private String getDateTime() {
        return LocalDateTime.now().toString();
    }

    public void log(String prefix, String... messages) {
        try {
            outputStream.write(prefix.getBytes());
            outputStream.write(" ".getBytes());
            outputStream.write(getDateTime().getBytes());
            outputStream.write(" -->".getBytes());
            for (String message : messages) {
                outputStream.write(" ".getBytes());
                outputStream.write(message.getBytes());
            }
            outputStream.write("\n".getBytes());
            outputStream.flush();
        } catch (Exception e) {
            throw new RuntimeException("Failed to write to log file", e);
        }
    }
}
