

import junit.framework.TestCase;
import java.util.Random;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {

	// url partitions
	private String[] validSchemes = {"http://", "https://", "ftp://"};
	private String[] validAuthorities = {"www.google.com", "google.com", "google.au", "255.255.255.255"};
	private String[] validPaths = {"/path1", "/path2/", "/path3/file", "/$path4", ""};
	private String[] validQueries = {"?action=view", "?action=edit&mode=up", ""};

	private String[] invalidSchemes = {"http:", "https:/", "://", "htp"};
	private String[] invalidAuthorities = {"256.256.256.256", "go.a", "aaa", ".1.2.3.4", ""};
	private String[] invalidPaths = {"/..", "/../", "/..//file", "/path1//file"};
	private String[] invalidQueries = {"?action[]", "action=123"};

	

   public UrlValidatorTest(String testName) {
      super(testName);
   }
  
   
   
   public void testManualTest() {
//You can use this function to implement your manual testing	   
	   
   }
   
   
   public void testYourFirstPartition() {
	   //You can use this function to implement your First Partition testing
	   
	   // Author: Chris Brown -------------------------------------------------
	   UrlValidator validator = new UrlValidator();
	   Random rng = new Random();
	   int passed = 0;
	   int failed = 0;

	   // Test Valid Partitions
	   for (int i = 0; i < 100; i++) {
	      int schemeIndex = rng.nextInt(validSchemes.length);
	      int authorityIndex = rng.nextInt(validAuthorities.length);
	      int pathIndex = rng.nextInt(validPaths.length);
	      int queryIndex = rng.nextInt(validQueries.length);
	      String url = validSchemes[schemeIndex] +
	              validAuthorities[authorityIndex] +
	              validPaths[pathIndex] +
	              validQueries[queryIndex];

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
	   // ---------------------------------------------------------------------
	   
   }
   
   
   public void testYourSecondPartition() {
	   //You can use this function to implement your Second Partition testing
	   
	   // Author: Chris Brown -------------------------------------------------
	   UrlValidator validator = new UrlValidator();
	   Random rng = new Random();
	   int passed = 0;
	   int failed = 0;

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
	   // ---------------------------------------------------------------------

   }
   //You need to create more test cases for your Partitions if you need to 
   
   
   public void testIsValid() {
	   //You can use this function for programming based testing

   }
   


}
