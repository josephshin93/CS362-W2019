

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {
	
	// print flag
	private static boolean PRINT = true;
	private static boolean DEBUG = false;


	
	public UrlValidatorTest(String testName) {
		super(testName);
	}
  
	
	
	// MANUAL TESTING =========================================================
	// private method to run one test with a manual constructed url as input
	private boolean singleManualTest(UrlValidator validator, String url, boolean valid) {
		if (validator.isValid(url) == valid) {
		   if (PRINT) {
			   System.out.println("Manual Test: PASSED  Url: \"" + url + "\"");
		   }
		   return true;
	   } else {
		   if (PRINT) {
			   System.out.println("Manual Test: FAILED  Url: \"" + url + "\"");
		   }
		   return false;
	   }
	}
	   
	// collection of all manual tests
	public void testManualTest() {
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
		System.out.println("- Manual Tests --------------------------------------------");
	   
		singleManualTest(validator, "http://www.google.com", true);
		singleManualTest(validator, "http://&*^(& *#Q $()&#", false);
		singleManualTest(validator, "http://", true);
		singleManualTest(validator, "http://google.com", true);
		singleManualTest(validator, "http://google.com/test1", true);
		singleManualTest(validator, "http://www.google.com/test1", true);
		singleManualTest(validator, "http://google.com/test1?action=view", true);
		singleManualTest(validator, "http://www.google.com/test1?action=view", true);
		singleManualTest(validator, "google", false);
		singleManualTest(validator, "google.com", false);
		singleManualTest(validator, "google,com:80", false);
		singleManualTest(validator, "www.google.com:80", false);
		singleManualTest(validator, "http://www.google.com:80/test1?action=view", false);
		singleManualTest(validator, "http://www.google.com:80/test1\n", false);
		singleManualTest(validator, "http://www.google.com:80/test1?action=view", false);
		singleManualTest(validator, "http:google.com", false);
		singleManualTest(validator, "http://www.google.com:80/test1?action=??view", false);
		singleManualTest(validator, "http:/www.google.com:80/-1..%%test1?action=view", false);
	   
		System.out.println("-----------------------------------------------------------\n");
	}
	// ========================================================================
      
   
	
	// UNIT TESTING ===========================================================
	// unit test to test various hostports "(hostname | hostnumber) [: port ]"
	public void testHttpHostport() {
		// object containing method under test
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
		// url parts for http url
		TestUrlPart scheme = new TestUrlPart("http://", true);
		TestUrlPart[] hostports = { new TestUrlPart("www.google.com", true),
                                   new TestUrlPart("128.119.245.12", true), // gaia.cs.umass.edu 
                                   new TestUrlPart("flip1.engr.oregonstate.edu:5002", true),
                                   new TestUrlPart("www.g>oogle.com", false),
                                   new TestUrlPart("128.119.245.    12", false),
                                   new TestUrlPart("flip1.engr.oregonstate.edu:##02", false)
			                     };
		TestUrlPart path = new TestUrlPart("/index.html", true);
		TestUrlPart search = new TestUrlPart("", true);
	   
		TestHttpUrl input;
		boolean result;
		int passed = 0;
	   
		System.out.println("- HTTP HostPort Unit Test ---------------------------------");
	   
		// go through each host port and create a url to test
		for (int i = 0; i < hostports.length; i++) {
			input = new TestHttpUrl(scheme, hostports[i], path, search);
			result = validator.isValid(input.urlString());
			if (PRINT) {
				if (result == input.validity()) {
					System.out.print("TEST CASE " + (i+1) + ": PASSED  ");
					passed++;
				} else {
					System.out.print("TEST CASE " + (i+1) + ": FAILED  ");
				}
				System.out.println("Url: \"" + input.urlString() + "\"");
			}
//		   	assertEquals(input.validity(), result);
		}
		
		System.out.println("Total passed: " + passed);
		System.out.println("Total failed: " + (hostports.length-passed));

		System.out.println("-----------------------------------------------------------\n");
	}
   
	
	// unit test to test various paths
	public void testHttpPath() {
		// object containing method under test
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
		// url parts for http url
		TestUrlPart scheme = new TestUrlPart("http://", true);
		TestUrlPart[] path = { new TestUrlPart("", true),
                               new TestUrlPart("/test", true), // gaia.cs.umass.edu 
                               new TestUrlPart("/.", true),
                               new TestUrlPart("/?", true),
                               new TestUrlPart("/..", false),
                               new TestUrlPart("/test/test2", true),
                               new TestUrlPart("/test/test2/test3", true),
                               new TestUrlPart("//test", false)
			                };
		TestUrlPart hostports = new TestUrlPart("www.google.com", true);
		TestUrlPart search = new TestUrlPart("", true);
	   
		TestHttpUrl input;
		boolean result;
		int passed = 0;
	   
		System.out.println("- HTTP Path Unit Test -------------------------------------");
	   
		// go through each host port and create a url to test
		for (int i = 0; i < path.length; i++) {
			input = new TestHttpUrl(scheme, hostports, path[i],search);
			result = validator.isValid(input.urlString());
			if (PRINT) {
				if (result == input.validity()) {
					System.out.print("TEST CASE " + (i+1) + ": PASSED  ");
					passed++;
				} else {
					System.out.print("TEST CASE " + (i+1) + ": FAILED  ");
				}
				System.out.println("Url: \"" + input.urlString() + "\"");
			}
//		   	assertEquals(input.validity(), result);
		}
		
		System.out.println("Total passed: " + passed);
		System.out.println("Total failed: " + (path.length-passed));
		
		System.out.println("-----------------------------------------------------------\n");
	}
   
	
	//unit test to test the various schemes
	public void testHttpHttp() {
		// object containing method under test
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
		// url parts for http url
		TestUrlPart[] scheme = {new TestUrlPart("http://", true), 
			   					new TestUrlPart("http:/", false),
			   					new TestUrlPart("http//", false),
			   					new TestUrlPart("http:", false),
//			   					new TestUrlPart("ftp://", true),
//			   					new TestUrlPart("fake://", false)
		};
		TestUrlPart hostports = new TestUrlPart("www.google.com", true);
		TestUrlPart path = new TestUrlPart("/index.html", true);
		TestUrlPart search = new TestUrlPart("", true);
	   
		TestHttpUrl input;
		boolean result;
		int passed = 0;
	   
		System.out.println("- Url Scheme Unit Test ------------------------------------");
	   
		// go through each scheme and create a url to test
		for (int i = 0; i < scheme.length; i++) {
			input = new TestHttpUrl(scheme[i], hostports, path, search);
			result = validator.isValid(input.urlString());
			if (PRINT) {
				if (result == input.validity()) {
					System.out.print("TEST CASE " + (i+1) + ": PASSED  ");
					passed++;
				} else {
					System.out.print("TEST CASE " + (i+1) + ": FAILED  ");
				}
				System.out.println("Url: \"" + input.urlString() + "\"");
			}
//		   	assertEquals(input.validity(), result);
		}
	   
		System.out.println("Total passed: " + passed);
		System.out.println("Total failed: " + (scheme.length-passed));
		
		System.out.println("-----------------------------------------------------------\n");
	}
   
	
	// unit test to test various searches ("aka" queries)
	public void testHttpSearch() {
		// object containing method under test
		UrlValidator validator = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
	   
		// url parts for http url
		TestUrlPart scheme = new TestUrlPart("http://", true);
		TestUrlPart hostports = new TestUrlPart("www.google.com", true);
		TestUrlPart path = new TestUrlPart("/index.html", true);
		TestUrlPart[] search = {new TestUrlPart("?crcat=test&crsource=test&crkw=buy-a-lot", true),
			   					new TestUrlPart("?&crsource=google", true),
			   					new TestUrlPart("?&&&&crsource=google", true),
			   					new TestUrlPart("?pid=232?crsource=google", false)
		};
		TestHttpUrl input;
		boolean result;
		int passed = 0;
	   
		System.out.println("- HTTP Search Unit Test -----------------------------------");
	   
		// go through each host port and create a url to test
		for (int i = 0; i < search.length; i++) {
			input = new TestHttpUrl(scheme, hostports, path,search[i]);
			result = validator.isValid(input.urlString());
			if (PRINT) {
				if (result == input.validity()) {
					System.out.print("TEST CASE " + (i+1) + ": PASSED  ");
					passed++;
				} else {
					System.out.print("TEST CASE " + (i+1) + ": FAILED  ");
				}
				System.out.println("Url: \"" + input.urlString() + "\"");
			}
//		   	assertEquals(input.validity(), result);
		}
		
		System.out.println("Total passed: " + passed);
		System.out.println("Total failed: " + (search.length-passed));
		
		System.out.println("-----------------------------------------------------------\n");
	}

    // ========================================================================
   
	
	
	// RANDOM TESTING =========================================================
	private String[] validSchemes = {"http://", "https://", "ftp://"};
	private String[] validAuthorities = {"www.google.com", "google.com", "google.au", "255.255.255.255"};
	private String[] validPaths = {"/path1", "/path2/", "/path3/file", "/$path4", ""};
	private String[] validQueries = {"?action=view", "?action=edit&mode=up", ""};

	private String[] invalidSchemes = {"http:", "https:/", "://", "htp"};
	private String[] invalidAuthorities = {"256.256.256.256", "go.a", "aaa", ".1.2.3.4", ""};
	private String[] invalidPaths = {"/..", "/../", "/..//file", "/path1//file"};
	private String[] invalidQueries = {"?action[]", "action=123"};
	 
	// random test for random valid urls
	public void testRandomValidUrls() {
		UrlValidator validator = new UrlValidator();
		Random rng = new Random();
		int passed = 0, failed = 0;

		System.out.println("- Random Valid URL Test ----------------------------------");
	   
		// Test Valid Partitions
		for (int i = 0; i < 100; i++) {
			int schemeIndex = rng.nextInt(validSchemes.length);
			int hostportIndex = rng.nextInt(validAuthorities.length);
			int pathIndex = rng.nextInt(validPaths.length);
			int searchIndex = rng.nextInt(validQueries.length);
	      
			String url = validSchemes[schemeIndex] +
					validAuthorities[hostportIndex] +
					validPaths[pathIndex] +
					validQueries[searchIndex];
	      
			if (validator.isValid(url)) {
				passed++;
				System.out.println(url);
			}
			else {
				failed++;
				System.out.println("FAILED!!! " + url);
			}
		}
	   
		System.out.println("===Valid Partitions===\nPassed: " + passed + "\nFailed: " + failed);
	   
		System.out.println("-----------------------------------------------------------\n");
	   
	}
   
	
	// random test for random invalid urls
	public void testRandomInvalidUrls() {   
		UrlValidator validator = new UrlValidator();
		Random rng = new Random();
		int passed = 0;
		int failed = 0;
	   
		System.out.println("- Random Invalid URL Test --------------------------------");

		// Test Valid Partitions
		for (int i = 0; i < 100; i++) {
			int schemeIndex = rng.nextInt(invalidSchemes.length);
			int authorityIndex = rng.nextInt(invalidAuthorities.length);
			int pathIndex = rng.nextInt(invalidPaths.length);
			int queryIndex = rng.nextInt(invalidQueries.length);
			String url = invalidSchemes[schemeIndex] +
					invalidAuthorities[authorityIndex] +
					invalidPaths[pathIndex] +
					invalidQueries[queryIndex];

			if (!validator.isValid(url)) {
				passed++;
				System.out.println("FAILED as expected: " + url);
			}
			else {
				failed++;
				System.out.println("Passed but should have failed: " + url);
			}
		}

		System.out.println("===Invalid Partitions===\nFailed properly: " + passed + 
	      "\nDid not fail: " + failed);
	   
	   
		System.out.println("-----------------------------------------------------------\n");
	}
   
	
	// random test for both valid and invalid urls
	public void testRandomUrls() {
		UrlValidator validator = new UrlValidator();
		Random rng = new Random();
		int numTestCases = 100, passed = 0;
		int scheme, hostport, path, search;
	   
		TestUrlPart[] testSchemes = {
			   new TestUrlPart("http://", true),
			   new TestUrlPart("https://", true),
			   new TestUrlPart("ftp://", true),
			   new TestUrlPart("http:", false),
			   new TestUrlPart("https:/", false),
			   new TestUrlPart("://", false),
			   new TestUrlPart("htp", false)
		};
		TestUrlPart[] testHostports = {
			   new TestUrlPart("www.google.com", true),
			   new TestUrlPart("google.com", true),
			   new TestUrlPart("google.au", true),
			   new TestUrlPart("255.255.255.255", true),
			   new TestUrlPart("256.256.256.256", false),
			   new TestUrlPart("go.a", false),
			   new TestUrlPart("aaa", false),
			   new TestUrlPart(".1.2.3.4", false),
			   new TestUrlPart("", false)
		};
		TestUrlPart[] testPaths = {
			   new TestUrlPart("/path1", true),
			   new TestUrlPart("/path2/", true),
			   new TestUrlPart("/path3/file", true),
			   new TestUrlPart("/$path4", true),
			   new TestUrlPart("", true),
			   new TestUrlPart("/..", false),
			   new TestUrlPart("/../", false),
			   new TestUrlPart("/..//file", false),
			   new TestUrlPart("/path1//file", false)
		};
		TestUrlPart[] testSearches = {
			   new TestUrlPart("?action=view", true),
			   new TestUrlPart("?action=edit&mode=up", true),
			   new TestUrlPart("", true),
			   new TestUrlPart("?action[]", false),
			   new TestUrlPart("action=123", false)
		};
	   
		TestHttpUrl testUrl;
		boolean result;
	   
		System.out.println("- Random HTTP URL Test ------------------------------------");
	   
		for (int i = 0; i < numTestCases; i++) {
			scheme = rng.nextInt(testSchemes.length);
			hostport = rng.nextInt(testHostports.length);
			path = rng.nextInt(testPaths.length);
			search = rng.nextInt(testSearches.length);
	      
			testUrl = new TestHttpUrl(
				   testSchemes[scheme],
				   testHostports[hostport],
				   testPaths[path],
				   testSearches[search]);
		   
			result = validator.isValid(testUrl.urlString());
		   
			if (DEBUG) {
				System.out.println("Test URL: \"" + testUrl.urlString() + "\"");
				System.out.println("Expected: " + testUrl.validity());
				System.out.println("Actual:   " + result);
			}
		   
			if (PRINT) {
				if (result == testUrl.validity()) {
					System.out.print("TEST CASE " + (i+1) + ": PASSED  ");
					passed++;
				} else {
					System.out.print("TEST CASE " + (i+1) + ": FAILED  ");
				}
				System.out.println("Url: \"" + testUrl.urlString() + "\"");
			}
//		   	assertEquals(input.validity(), result);
		   
		}
	   
		System.out.println("Total passed: " + passed);
		System.out.println("Total failed: " + (numTestCases-passed));
	    
		System.out.println("-----------------------------------------------------------\n");
	}
   
	// ========================================================================
	
	
	
	public void testIsValid() {
		//You can use this function for programming based testing

	}
   
}
