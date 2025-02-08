/**
 * 
 */
package poc_datanucleus.resolver;

/**
 * @author Gabriel Dimitriu
 *
 */
public class ClassLoaderNotRegistered extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * 
	 */
	public ClassLoaderNotRegistered() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 */
	public ClassLoaderNotRegistered(String message) {
		super(message);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param cause
	 */
	public ClassLoaderNotRegistered(Throwable cause) {
		super(cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 * @param cause
	 */
	public ClassLoaderNotRegistered(String message, Throwable cause) {
		super(message, cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 * @param cause
	 * @param enableSuppression
	 * @param writableStackTrace
	 */
	public ClassLoaderNotRegistered(String message, Throwable cause, boolean enableSuppression,
			boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
		// TODO Auto-generated constructor stub
	}

}
