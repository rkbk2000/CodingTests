package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import wiki.KeywordsFinder;
import wiki.Utils;

class KeywordsFinderTest {

	@Test
	final void testForDefault() {
		KeywordsFinder keywords = new KeywordsFinder();
		assertEquals(Utils.STOPWORDS.length, keywords.getStopWords().size());
	}

	@Test
	final void testForNewAddition() {
		KeywordsFinder keywords = new KeywordsFinder();
		String newWord = "zebras";
		keywords.addAdditionalStopWord(newWord);
		assertEquals(Utils.STOPWORDS.length + 1, keywords.getStopWords().size());
		assertEquals(newWord, keywords.getStopWords().get(Utils.STOPWORDS.length));
	}

	@Test
	final void testForDuplicateAddition() {
		KeywordsFinder keywords = new KeywordsFinder();
		String newWord = "a";
		keywords.addAdditionalStopWord(newWord);
		assertEquals(Utils.STOPWORDS.length, keywords.getStopWords().size());
		assertEquals(newWord, keywords.getStopWords().get(0));
	}
}
