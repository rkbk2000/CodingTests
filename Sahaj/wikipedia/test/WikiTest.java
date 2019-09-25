package test;

import static org.junit.jupiter.api.Assertions.*;

import org.junit.jupiter.api.Test;

import wiki.Wiki;

class WikiTest {

	@Test
	final void testForDefault() {
		Wiki mywiki = new Wiki();
		boolean rc = mywiki.parseInput(null);
		assertEquals(false, rc);
	}
}
