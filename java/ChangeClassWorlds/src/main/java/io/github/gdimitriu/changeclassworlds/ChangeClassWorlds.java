package io.github.gdimitriu.changeclassworlds;

import java.io.*;
import java.util.ArrayList;
import java.util.List;

public class ChangeClassWorlds {
    public static void main(String...args) {
        if (args.length != 2) {
            System.err.println("Usage: ChangeClassWorlds <filename> <realm");
            System.exit(1);
        }
        List<String> classWorlds = readClassWorlds(args[0]);
        List<String> newClassWorlds = changeClassWorlds(classWorlds, args[1]);
        writeClassWorlds(args[0], newClassWorlds);
    }
    public static List<String > readClassWorlds(String filename) {
        File file = new File(filename);
        List<String> lines = new ArrayList<>();
        try (BufferedReader reader = new BufferedReader(new FileReader(file))) {
            String line = null;
            while ((line = reader.readLine()) != null) {
                lines.add(line);
            }
            return lines;
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    public static void writeClassWorlds(String filename, List<String> content) {
        File file = new File(filename);
        try (BufferedWriter writer = new BufferedWriter(new FileWriter(file))) {
            for (String line : content) {
                writer.write(line);
                writer.newLine();
            }
        } catch (IOException e) {
            throw new RuntimeException(e);
        }
    }
    public static List<String> changeClassWorlds(List<String> classWorlds, String remove) {
        boolean found = false;
        List<String> result = new ArrayList<>();
        for (int i = 0; i < classWorlds.size(); i++) {
            if (classWorlds.get(i).equals(remove)) {
                found = true;
                continue;
            }
            if ( found && classWorlds.get(i).startsWith("[") ) {
                found = false;
            }
            if ( !found ) {
                result.add(classWorlds.get(i));
            }
        }
        return result;
    }
}
