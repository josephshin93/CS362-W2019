
public class TestUrlPart {

	private String part;
	private boolean valid;
	
	public TestUrlPart(String part, boolean valid) {
		this.part = part;
		this.valid = valid;
	}
	
	@Override
	public String toString() {
		return this.part;
	}
	
	public boolean validity() {
		return this.valid;
	}
}
