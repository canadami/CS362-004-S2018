

import junit.framework.TestCase;

//You can use this as a skeleton for your 3 different test approach
//It is an optional to use this file, you can generate your own test file(s) to test the target function!
// Again, it is up to you to use this file or not!





public class UrlValidatorTest extends TestCase {


   public UrlValidatorTest(String testName) {
      super(testName);
   }

   
   
   public void testManualTest()
   {
//You can use this function to implement your manual testing	   
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

	   ResultPair[] manualTest = {
	 
//	   new ResultPair("ftp://www.google.com", true),
	   new ResultPair("www.google.com", true),
	   new ResultPair("www.google.com/maps", true),
	   new ResultPair("google.com",true),
//	   new ResultPair("https://www.whitehouse.gov/",true),
//	   new ResultPair("https://oregonstate.edu/",true),
//	   new ResultPair("ttps://www.google.com/", false),
	   new ResultPair("wwww.whitehouse.gov", false ),
	   new ResultPair("www.google.commaps", false),
	   new ResultPair("google", false)};

	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));
	   for(int i = 0; i < manualTest.length; i++) {
	   boolean expected = manualTest[i].valid;
	   boolean result = urlVal.isValid(manualTest[i].item);
	            	if(result == expected) {
	         		 System.out.println("Passed manual test");
	           		 System.out.println(manualTest[i].item);
	            	}
//	   assertEquals(manualTest[i].item, expected, result);
	           		 else if(result != expected) {
	           			 System.out.println("Failed manual test");
	           			 System.out.println(manualTest[i].item);
	           		 }
	   }

	   boolean res = urlVal.isValid("google.com");
	            	if(res == true) {
	         		 System.out.println("Passed manual hardcode");
	           		 System.out.println("google.com");
	            	}
//	   assertEquals(manualTest[i].item, expected, result);
	           		 else if(res == false) {
	           			 System.out.println("Failed manual hardcode");
	           			 System.out.println("google.com");
	           		 }
   }
   
/****************************************************************************************
* Test URL Schemes
* This function uses a variety of web protocols to test UrlValidator’s ability to
* correctly interpret URL schemes.
****************************************************************************************/

   public void testYourFirstPartition()
   {
	 //You can use this function to implement your First Partition testing	   
   	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

   ResultPair[] manualTest = {

		   new ResultPair("http://www.google.com", true),
		   new ResultPair("http://", true),
//		   new ResultPair("ftp://www.google.com", true),
//		   new ResultPair("h3t://www.google.com", false),
		   new ResultPair("3ht://www.google.com",false),
		   new ResultPair("http:/www.google.com",false),
		   new ResultPair("http:www.google.com",false),
		   new ResultPair("http/www.google.com", false),
		   new ResultPair("://www.google.com", false),
		   new ResultPair("google.com", true),
   };
		   
		   assertTrue(urlVal.isValid("http://www.google.com"));
		   assertTrue(urlVal.isValid("http://www.google.com/"));

		   for(int i = 0; i < manualTest.length; i++) {
			   boolean expected = manualTest[i].valid;
			   boolean result = urlVal.isValid(manualTest[i].item);
			   		if(result == expected) {
			   			System.out.println("Passed Scheme Test");
			   			System.out.println(manualTest[i].item);
			   		}
			   		//   assertEquals(manualTest[i].item, expected, result);
			   		else if(result != expected) {
           			 System.out.println("Failed Scheme Test");
           			 System.out.println(manualTest[i].item);
			   		}
		   }

   }
   
/****************************************************************************************
   * Test URL Authorities
   * This function uses a variety of web protocols to test UrlValidator’s ability to
   * correctly interpret URL schemes.
****************************************************************************************/

   public void testYourSecondPartition()
   {
		 //You can use this function to implement your Second Partition testing	   
	   //You can use this function to implement your Second Partition testing	   
	 	UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

		  ResultPair[] manualTest = {

		  new ResultPair("www.google.com", true),
	              new ResultPair("go.com", true),
	              new ResultPair("go.au", true),
	              new ResultPair("0.0.0.0", true),
	              new ResultPair("255.255.255.255", true),
	              new ResultPair("256.256.256.256", false),
	              new ResultPair("255.com", true),
	              new ResultPair("1.2.3.4.5", false),
	              new ResultPair("1.2.3.4.", false),
	              new ResultPair("1.2.3", false),
	              new ResultPair(".1.2.3.4", false),
	              new ResultPair("go.a", false),
	              new ResultPair("go.a1a", false),
	              new ResultPair("go.1aa", false),
	              new ResultPair("aaa.", false),
	         	  new ResultPair(".aaa", false),
	              new ResultPair("aaa", false),
	              new ResultPair("", false)
		  };

		   for(int i = 0; i < manualTest.length; i++) {
		   boolean expected = manualTest[i].valid;
		   boolean result = urlVal.isValid(manualTest[i].item);
		            	if(result == expected) {
		         		 System.out.println("Passed Authority Test");
		           		 System.out.println(manualTest[i].item);
		            	}
//		   assertEquals(manualTest[i].item, expected, result);
		           		 else if(result != expected) {
		           			 System.out.println("Failed Authority Test");
		           			 System.out.println(manualTest[i].item);
		           		 }
		   }

   }
   //You need to create more test cases for your Partitions if you need to 
   
/****************************************************************************************
   * Test URL Ports
   * This function uses a variety of web protocols to test UrlValidator’s ability to
   * correctly interpret URL schemes.
****************************************************************************************/

   public void testYourThirdPartition(){
 		 //You can use this function to implement your Third Partition testing
 //You can use this function to implement your manual testing	   
 	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

 	   ResultPair[] manualTest = {

 	   new ResultPair("www.google.com:80", true),   
 	   new ResultPair("www.google.com:65535", true),
 	   new ResultPair("www.google.com:65535", true),
 	   new ResultPair("www.google.com:0", true),
 	   new ResultPair("www.google.com", true),
 	   new ResultPair("www.google.com:-1", false),
 	   new ResultPair("www.google.com:65636",false),
 	   new ResultPair("www.google.com:65a", false)
 	   
   };

 	   assertTrue(urlVal.isValid("http://www.google.com"));
 	   assertTrue(urlVal.isValid("http://www.google.com/"));

 	   for(int i = 0; i < manualTest.length; i++) {
 	   boolean expected = manualTest[i].valid;
 	   boolean result = urlVal.isValid(manualTest[i].item);
 	            	if(result == expected) {
 	         		 System.out.println("Passed Ports Test");
 	           		 System.out.println(manualTest[i].item);
 	            	}
// 	   assertEquals(manualTest[i].item, expected, result);
 	           		 else if(result != expected) {
 	           			 System.out.println("Failed Ports Test");
 	           			 System.out.println(manualTest[i].item);
 	           		 }
 	   }
    }

/****************************************************************************************
   * Test URL Paths
   * This function tests a variety of valid and invalid web paths, including
   * various quantities of the characters ‘/’ and ‘.’.
****************************************************************************************/

   public void testYourFourthPartition()
   {
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
    //You can use this function to implement your Fourth Partition testing
	   ResultPair[] manualTest = {
	   new ResultPair("en.wikipedia.org/wiki/Beaver", true),
       new ResultPair("linkedin.com/school/oregon-state-university/", true),
       new ResultPair("github.com/aburasa/CS362-004-S2018/", true),
//       new ResultPair("https://github.com/aburasa/CS362-004-S2018/..", false),
       new ResultPair("github.com/aburasa/CS362-004-S2018/../", false),
       new ResultPair("github.com/aburasa//CS362-004-S2018/", false),
       new ResultPair("github.com/aburasa/..//CS362-004-S2018", false),
       new ResultPair("github.com/", true)
   
   };
	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));

	   for(int i = 0; i < manualTest.length; i++) {
	   boolean expected = manualTest[i].valid;
	   boolean result = urlVal.isValid(manualTest[i].item);
	            	if(result == expected) {
	         		 System.out.println("Passed Paths Test");
	           		 System.out.println(manualTest[i].item);
	            	}
//	   assertEquals(manualTest[i].item, expected, result);
	           		 else if(result != expected) {
	           			 System.out.println("Failed Paths Test");
	           			 System.out.println(manualTest[i].item);
	           		 }
	   }
   }

   
/****************************************************************************************
   * Test URL Queries
   * This function tests various queries that may be passed to a URL through
   * a web form or other source.
****************************************************************************************/
   
   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);
   
     public void testYourFifthPartition(){
     //You can use this function to implement your Fifth Partition testing	   
     ResultPair[] manualTest = {
     new ResultPair("search.yahoo.com/search?p=oregon", true),
     new ResultPair("google.com?action=edit", true),
     new ResultPair("youtube.com/watch?v=dQw4w9WgXcQ", true),
     new ResultPair("google.com/fiejfoijeo", false)
      };

	   assertTrue(urlVal.isValid("http://www.google.com"));
	   assertTrue(urlVal.isValid("http://www.google.com/"));

	   for(int i = 0; i < manualTest.length; i++) {
	   boolean expected = manualTest[i].valid;
	   boolean result = urlVal.isValid(manualTest[i].item);
	            	if(result == expected) {
	         		 System.out.println("Passed Queries Test");
	           		 System.out.println(manualTest[i].item);
	            	}
//	   assertEquals(manualTest[i].item, expected, result);
	           		 else if(result != expected) {
	           			 System.out.println("Failed Queries Test");
	           			 System.out.println(manualTest[i].item);
	           		 }
	   }
     
   }

   
   public void testIsValid()
   {
	   //You can use this function for programming based testing
	   UrlValidator urlVal = new UrlValidator(null, null, UrlValidator.ALLOW_ALL_SCHEMES);

			   //You can use this function for programming based testing
		ResultPair[] scheme = {new ResultPair("http://", true),
		 new ResultPair("", true),
//		 new ResultPair("ftp://", true),
//		 new ResultPair("https://", true),
//		 new ResultPair("htp://", false),
		 new ResultPair("/", false),
//		 new ResultPair("rtp://", false),
//		 new ResultPair("httpss://", false)
		};

		ResultPair[] authority = {new ResultPair("www.google.com", true),
		 new ResultPair("bing.com", true),
		 new ResultPair("whitehouse.gov", true),
		 new ResultPair("oregonstate.edu", true),
		 new ResultPair("ww.google.com", false),
		 new ResultPair("bing", false),
		 new ResultPair("wwww.whitehouse.gov", false),
		 new ResultPair("www.edu", false),
		 new ResultPair("go.com", true),
		 new ResultPair("go.au", true),
		 new ResultPair("0.0.0.0", true),
		 new ResultPair("255.255.255.255", true),
		 new ResultPair("256.256.256.256", false),
		 new ResultPair("255.com", true),
		 new ResultPair("1.2.3.4.5", false),
		 new ResultPair("1.2.3.4.", false),
		 new ResultPair("1.2.3", false),
		 new ResultPair(".1.2.3.4", false),
		 new ResultPair("go.a", false),
		 new ResultPair("go.a1a", false),
		 new ResultPair("go.1aa", false),
		 new ResultPair("aaa.", false),
		 new ResultPair(".aaa", false),
		 new ResultPair("aaa", false),
		 new ResultPair("", false)
		};
		 
		 ResultPair[] port = {
		                 new ResultPair(":99", true),
		                             new ResultPair(":65535", true), //the largest valid port
		                             new ResultPair(":0", true),
		                             new ResultPair("", true),
		                             new ResultPair(":-5", false),
		                            new ResultPair(":65536",false),
		                             new ResultPair(":c888", false)
			   };

		   ResultPair[] path = {
				   				new ResultPair("/", true),
				   				new ResultPair("/test", true),
		                      	new ResultPair("/test45", true),
		                      	new ResultPair("/$965", true),
		                      	new ResultPair("/..", false),
		                      	new ResultPair("/../", false),
		                      	new ResultPair("/test/", true),
		                      	new ResultPair("", true),
		                      	new ResultPair("/test/file", true),
		                      	new ResultPair("/..//file", false),
		                      	new ResultPair("/test//file", false)
		   };



		ResultPair[] query = {new ResultPair("?whereismaps", true),
		 new ResultPair("?action=mysearch", true),
		new ResultPair("?action=whatever&mode=down", true),
		 new ResultPair("", true),
		 new ResultPair("?noneoftheseshouldfail", true),
		};

		   

			assertTrue(urlVal.isValid("http://www.google.com"));
			assertTrue(urlVal.isValid("http://www.google.com/"));
		   
		for(int i = 0; i < scheme.length; i++) {
			   boolean expected = scheme[i].valid;
			   boolean result = urlVal.isValid(scheme[i].item);
			            	if(result == expected) {
			         		 System.out.println("Passed Automated Schemes Test");
			           		 System.out.println(scheme[i].item);
			            	}
//			   assertEquals(scheme[i].item, expected, result);
			           		 else if(result != expected) {
			           			 System.out.println("Failed Automated Schemes Test");
			           			 System.out.println(scheme[i].item);
			           		 }
			   }



			for(int i = 0; i < authority.length; i++) {
			   boolean expected = authority[i].valid;
			   boolean result = urlVal.isValid(authority[i].item);
			            	if(result == expected) {
			         		 System.out.println("Passed Automated Authority Test");
			           		 System.out.println(authority[i].item);
			            	}
//			   assertEquals(authority[i].item, expected, result);
			           		 else if(result != expected) {
			           			 System.out.println("Failed Automated Authority Test");
			           			 System.out.println(authority[i].item);
			           		 }
			   }


		for(int i = 0; i < port.length; i++) {
			   boolean expected = port[i].valid;
			   boolean result = urlVal.isValid(port[i].item);
			            	if(result == expected) {
			         		 System.out.println("Passed Automated URL Test");
			           		 System.out.println(port[i].item);
			            	}
//			   assertEquals(port[i].item, expected, result);
			           		 else if(result != expected) {
			           			 System.out.println("Failed Automated Port Test");
			           			 System.out.println(port[i].item);
			           		 }
			   }


		for(int i = 0; i < path.length; i++) {
			   boolean expected = path[i].valid;
			   boolean result = urlVal.isValid(path[i].item);
			            	if(result == expected) {
			         		 System.out.println("Passed Automated Path Test");
			           		 System.out.println(path[i].item);
			            	}
//			   assertEquals(path[i].item, expected, result);
			           		 else if(result != expected) {
			           			 System.out.println("Failed Automated Path Test");
			           			 System.out.println(path[i].item);
			           		 }
			   }


			for(int i = 0; i < query.length; i++) {
			   boolean expected = query[i].valid;
			   boolean result = urlVal.isValid(query[i].item);
			            	if(result == expected) {
			         		 System.out.println("Passed Automated Query Test");
			           		 System.out.println(query[i].item);
			            	}
//			   assertEquals(query[i].item, expected, result);
			           		 else if(result != expected) {
			           			 System.out.println("Failed Automated Query Test");
			           			 System.out.println(query[i].item);
			           		 }
			   }

   }
   


}
