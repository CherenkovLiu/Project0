package Project0;

import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.InputStream;
import java.io.InputStreamReader;

import Project0.Semantic.*;

public class Main {

    public static void main(String[] args) {
        var path = "D:\\Harddrive\\Project0\\test.clars";
        String fileContext;
        try {
            InputStream is = new FileInputStream(path);
            InputStreamReader isr = new InputStreamReader(is);
            BufferedReader reader = new BufferedReader(isr);
            String line;
            StringBuilder sbuilder = new StringBuilder();
            while ((line = reader.readLine()) != null)
                sbuilder.append(line);
            reader.close();
            is.close();
            fileContext = String.valueOf(sbuilder);
        } catch (Exception err) {
            System.out.println("File not found");
            return;
        }

        var lexer = new Lexer(fileContext);
        try {
            var json = lexer.toJson();
            var diag = lexer.Diagnostic();
            if (!diag.isEmpty())
                for (String string : diag)
                    System.out.println(string);
            else
                System.out.println(json);
        } catch (Exception err) {
            System.out.println("Some error occured " + err.getMessage());
        }
    }
}
