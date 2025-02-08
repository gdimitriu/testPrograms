/**
 * 
 */
package poc_datanucleus.resolver;

/**
 * @author Gabriel Dimitriu
 *
 */
public class ClassLoaderAlreadyRegistered extends Exception {

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	/**
	 * 
	 */
	public ClassLoaderAlreadyRegistered() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 */
	public ClassLoaderAlreadyRegistered(String message) {
		super(message);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param cause
	 */
	public ClassLoaderAlreadyRegistered(Throwable cause) {
		super(cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 * @param cause
	 */
	public ClassLoaderAlreadyRegistered(String message, Throwable cause) {
		super(message, cause);
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param message
	 * @param cause
	 * @param enableSuppression
	 * @param writableStackTrace
	 */
	public ClassLoaderAlreadyRegistered(String message, Throwable cause, boolean enableSuppression,
			boolean writableStackTrace) {
		super(message, cause, enableSuppression, writableStackTrace);
		// TODO Auto-generated constructor stub
	}

}
