/**
 * 
 */
package poc_datanucleus.resolver;

import org.datanucleus.ClassLoaderResolverImpl;

/**
 * @author gdimitriu
 *
 */
public class ChappyClassLoaderResolver extends ClassLoaderResolverImpl {

	/**
	 * 
	 */
	public ChappyClassLoaderResolver() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param ctxLoader
	 */
	public ChappyClassLoaderResolver(ClassLoader ctxLoader) {
		super(ctxLoader);
		// TODO Auto-generated constructor stub
	}

	@Override
	public Class classForName(final String name) {
		try {
			ClassLoader classLoader = ClassLoaderSingletonProvider.getInstance().getDefaultClassLoader();
			return super.classForName(name, classLoader);
		} catch (ClassLoaderNotRegistered e) {
			return super.classForName(name); 
		}
	}
	
	@Override
	public Class classForName(final String name, final boolean init) {
		try {
			ClassLoader classLoader = ClassLoaderSingletonProvider.getInstance().getDefaultClassLoader();
			return super.classForName(name, classLoader, init);
		} catch (ClassLoaderNotRegistered e) {
			return super.classForName(name, init); 
		}
	}
	
	@Override
	public Class classForName(String name, ClassLoader primary, boolean initialize) {
		try {
			ClassLoader classLoader = ClassLoaderSingletonProvider.getInstance().getDefaultClassLoader();
			return super.classForName(name, classLoader, initialize);
		} catch (ClassLoaderNotRegistered e) {
			return super.classForName(name, primary, initialize); 
		}
	}
	
	@Override
	public Class classForName(String name, ClassLoader primary) {
		try {
			ClassLoader classLoader = ClassLoaderSingletonProvider.getInstance().getDefaultClassLoader();
			return super.classForName(name, classLoader);
		} catch (ClassLoaderNotRegistered e) {
			return super.classForName(name, primary); 
		}
	}
}
