package test;

import static org.junit.jupiter.api.Assertions.*;

import java.util.ArrayList;

import org.junit.jupiter.api.Test;

import wiki.StringScanner;

class StringScannerTest {

	@Test
	final void testForNull() {
		ArrayList<String> tokens = StringScanner.scanString(null, null);
		assertEquals(0, tokens.size());
	}

	@Test
	final void testFor2Tokens() {
		ArrayList<String> tokens = StringScanner.scanString("a;b", ";");
		assertEquals(2, tokens.size());

		assertEquals(tokens.get(0), "a");
		assertEquals(tokens.get(1), "b");
	}

	@Test
	final void testFor1Token() {
		ArrayList<String> tokens = StringScanner.scanString("ab", ";");
		assertEquals(1, tokens.size());

		assertEquals(tokens.get(0), "ab");
	}
}
