/**
 * 
 */
package wiki;

import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map.Entry;

/**
 * @author rkbk2 The driver class that reads the input from a file and prints
 *         the answers to the given questions from the given list.
 *
 */
public final class Wiki {

	private KeywordsFinder keysFinder_ = new KeywordsFinder();
	private Paragraph paragraph_ = null;
	private Questions questions_ = null;
	private Answers answers_ = null;
	String[] finalAnswers_ = new String[Questions.MAX_QUESTIONS];

	/*
	 * The driver program that creates the wiki class, parses the given input and
	 * prints answers.
	 */
	public static void main(String[] args) {
		Wiki mywiki = new Wiki();
		boolean parsed = mywiki.parseInput(args);
		if (parsed) {
			mywiki.getAnswers();
			mywiki.printAnswers();
		}
	}

	/*
	 * Parses the input from a file
	 * 
	 */
	public boolean parseInput(String[] args) {
		boolean result = false;

		if (args == null) {
			return result;
		}

		InputStream inFileStream = openFile(args);
		if (null == inFileStream) {
			return result;
		}
		InputParser inparser = new InputParser(inFileStream);

		paragraph_ = inparser.getParagraph();
		addCustomStopWords(paragraph_, Utils.TOPN_STOP_WORDS);

		questions_ = inparser.getQuestions();

		answers_ = inparser.getAnswers();
		result = true;
		try {
			inFileStream.close();
		} catch (IOException e) {
			e.printStackTrace();
		}
		return result;
	}

	private static InputStream openFile(String[] args) {
		InputStream inFileStream = null;

		if (args != null && args.length > 0) {
			try {
				inFileStream = new FileInputStream(args[0]);
			} catch (FileNotFoundException e) {
				// TODO: add log
			} catch (NullPointerException e) {
			}
		}
		return inFileStream;
	}

	private void addCustomStopWords(Paragraph paragraph, int max) {
		List<Entry<String, Integer>> wordcounts = WordCounter.getWordCount(paragraph.getPara());

		for (int index = 0; index < max; ++index) {
			Entry<String, Integer> word = wordcounts.get(index);
			if (word.getValue() > Utils.MIN_REPEAT_COUNT) {
				keysFinder_.addAdditionalStopWord(word.getKey());
			} else {
				break;
			}
		}
	}

	/**
	 * Gets answers in the order of given questions
	 * 
	 * @return
	 */
	public String[] getAnswers() {

		ArrayList<String> sentencesHavingAnswers = getSentencesHavingAnswers();

		for (int index = 0; index < questions_.getElements().size(); ++index) {
			String question = questions_.getElements().get(index);
			int ansIdx = getAnswerForAQuestion(sentencesHavingAnswers, question);
			finalAnswers_[index] = answers_.getElements().get(ansIdx);
		}
		return finalAnswers_;
	}

	/**
	 * @return
	 */
	private ArrayList<String> getSentencesHavingAnswers() {
		ArrayList<String> sentencesHavingAnswers = new ArrayList<String>();

		for (String answer : answers_.getElements()) {
			String match = getSentenceContainingAnswer(answer);
			sentencesHavingAnswers.add(match);
		}
		return sentencesHavingAnswers;
	}

	private String getSentenceContainingAnswer(String key) {
		ArrayList<String> data = paragraph_.getElements();
		ArrayList<String> matches = new ArrayList<String>();

		for (int index = 0; index < data.size(); ++index) {
			String cur = data.get(index).toLowerCase();
			if (cur.contains(key.toLowerCase())) {
				matches.add(cur);
			}
		}

		int kdx = getClosestMatchingStringIndex(matches, key);
		return matches.get(kdx);
	}

	/**
	 * @param matches
	 * @param key
	 * @return
	 */
	private int getClosestMatchingStringIndex(ArrayList<String> matches, String key) {
		int closest = Integer.MAX_VALUE;
		int kdx = 0;
		for (int idx = 0; idx < matches.size(); ++idx) {
			int cur = matches.get(idx).length() - key.length();
			if (cur < closest) {
				closest = cur;
				kdx = idx;
			}
		}
		return kdx;
	}

	/**
	 * @param sentencesHavingAnswers
	 * @param question
	 * @return
	 */
	private int getAnswerForAQuestion(ArrayList<String> sentencesHavingAnswers, String question) {
		ArrayList<String> keyWords = keysFinder_.getKeyWords(question);

		double maxDistance = 0;
		int fAnsIdx = 0;
		for (int aIdx = 0; aIdx < sentencesHavingAnswers.size(); ++aIdx) {
			int nmatches = getNumberOfMatchingWords(sentencesHavingAnswers.get(aIdx), keyWords);
			double curDistance = (double) nmatches / keyWords.size();
			if (curDistance > maxDistance) {
				maxDistance = curDistance;
				fAnsIdx = aIdx;
			}
		}
		return fAnsIdx;
	}

	private int getNumberOfMatchingWords(String sentence, ArrayList<String> wordsToMatch) {
		int matches = 0;
		for (String word : wordsToMatch) {
			if (sentence.contains(word.toLowerCase())) {
				++matches;
			}
		}
		return matches;
	}

	/**
	 * Prints the final answers one per line
	 * 
	 * @return
	 */
	public void printAnswers() {
		for (String answer : finalAnswers_) {
			if (null != answer) {
				System.out.println(answer.trim());
			}
		}
	}
}
