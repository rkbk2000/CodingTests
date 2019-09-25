package wiki;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Comparator;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.StringTokenizer;
import java.util.Map.Entry;

/*
 * A class used to get the number of occurrence of each word in a string
 */
public final class WordCounter {

	private static Map<String, Integer> getWords(String para) {
		Map<String, Integer> wordMap = new HashMap<String, Integer>();
		para.replaceAll("[,;:]", Utils.SPACE);

		StringTokenizer st = new StringTokenizer(para, Utils.SPACE);
		while (st.hasMoreTokens()) {
			String word = st.nextToken().toLowerCase();
			if (wordMap.containsKey(word)) {
				wordMap.put(word, wordMap.get(word) + 1);
			} else {
				wordMap.put(word, 1);
			}
		}
		return wordMap;
	}

	public static List<Entry<String, Integer>> getWordCount(String para) {
		Map<String, Integer> wordMap = getWords(para);
		Set<Entry<String, Integer>> set = wordMap.entrySet();
		List<Entry<String, Integer>> list = new ArrayList<Entry<String, Integer>>(set);
		Collections.sort(list, new Comparator<Map.Entry<String, Integer>>() {
			public int compare(Map.Entry<String, Integer> x, Map.Entry<String, Integer> y) {
				return (y.getValue()).compareTo(x.getValue());
			}
		});
		return list;
	}
}