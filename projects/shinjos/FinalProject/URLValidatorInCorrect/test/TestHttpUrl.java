

public class TestHttpUrl {
	
	private TestUrlPart scheme;
	private TestUrlPart hostport;
	private TestUrlPart path;
	private TestUrlPart search;
	
	
	public TestHttpUrl(TestUrlPart scheme, TestUrlPart hostport, TestUrlPart path, TestUrlPart search) {
		this.scheme = scheme;
		this.hostport = hostport;
		this.path = path;
		this.search = search;
	}
	
	public String urlString() {
		StringBuilder fullUrl = new StringBuilder();
		fullUrl.append(this.scheme.toString());
		fullUrl.append(this.hostport.toString());
		fullUrl.append(this.path.toString());
		fullUrl.append(this.search.toString());
		return fullUrl.toString();
	}
	
	public boolean validity() {
		return this.scheme.validity() & 
			   this.hostport.validity() & 
			   this.path.validity() & 
			   this.search.validity();
	}
		
	
}
