import java.io.*;
import java.util.*;

public class Board{
	public static void main(String[] args) throws IOException{
		String pythonScriptPath = "test.py";
		String[] cmd = new String[2];
		cmd[0] = "python2.6";
		cmd[1] = pythonScriptPath;

		//create runtime to execute external commands
		Runtime rt = Runtime.getRuntime();
		Process pr = rt.exec(cmd);

		//retrieve output from python script
		BufferedReader bfr = new BufferedReader(new InputStreamReader(pr.getInputStream()));

		String line = "";

		while((line = bfr.readLine()) != null) {
			System.out.println(line);
		}


	}
}