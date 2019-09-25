package wiki;

import java.util.ArrayList;
import java.util.Scanner;

public class StringScanner {
	public static ArrayList<String> scanString(String data, String delimiter) {
		ArrayList<String> outList = new ArrayList<String>();

		if ((null != data) && (null != delimiter)) {
			Scanner scanner = new Scanner(data);
			scanner.useDelimiter(delimiter);

			while (scanner.hasNext()) {
				String sentence = scanner.next();
				outList.add(sentence);
			}
			scanner.close();
		}
		return outList;
	}
}