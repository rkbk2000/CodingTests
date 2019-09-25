/**
 * 
 */
package wiki;

import java.util.*;

/**
 * @author rkbk2 A class that provides a function to remove stop words from a
 *         given sentence and provide the list of interesting words (key words)
 *
 */
public final class KeywordsFinder {

	private ArrayList<String> stopWords_ = new ArrayList<String>();

	public KeywordsFinder() {
		Collections.addAll(stopWords_, Utils.STOPWORDS);
	}

	public void addAdditionalStopWord(String word) {
		String wordLower = word.toLowerCase();
		if (false == stopWords_.contains(wordLower)) {
			stopWords_.add(wordLower);
		}
	}

	public ArrayList<String> getKeyWords(String input) {
		ArrayList<String> result = new ArrayList<String>();
		input.replaceAll("[, :]", Utils.SPACE);

		String[] words = input.split(Utils.SPACE);

		for (String word : words) {
			if (false == stopWords_.contains(word.toLowerCase())) {
				result.add(word);
			}
		}
		return result;
	}

	public final ArrayList<String> getStopWords() {
		return stopWords_;
	}
}
