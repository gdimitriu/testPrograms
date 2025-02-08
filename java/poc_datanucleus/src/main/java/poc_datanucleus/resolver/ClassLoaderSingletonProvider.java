/**
 * 
 */
package poc_datanucleus.resolver;

import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;

/**
 * @author Gabriel Dimitriu
 *
 */
public class ClassLoaderSingletonProvider {

	private static final String DEFAULT_SYSTEM_CLASSLOADER = "defaultSystemClassLoader";

	private static ClassLoaderSingletonProvider singleton = new ClassLoaderSingletonProvider();
	
	private Map<String, ClassLoader> classLoaders = new ConcurrentHashMap<>();
	
	private String defaultClassLoader = DEFAULT_SYSTEM_CLASSLOADER;
	
	/**
	 * 
	 */
	private ClassLoaderSingletonProvider() {
		// TODO Auto-generated constructor stub
		classLoaders.put(DEFAULT_SYSTEM_CLASSLOADER, this.getClass().getClassLoader());
	}
	
	public static ClassLoaderSingletonProvider getInstance() {
		return singleton;
	}

	public void registerClassLoader(final String name, final ClassLoader loader) {
		classLoaders.put(name, loader);
	}
	
	public ClassLoader getRegisteredClassLoader(final String name) {
		if (classLoaders.containsKey(name)) {
			return classLoaders.get(name);
		}
		return null;
	}
	
	public void setDefaultClassLoader(final String name) throws ClassLoaderNotRegistered {
		if (classLoaders.containsKey(name)) {
			defaultClassLoader = name;
			return;
		} 
		throw new ClassLoaderNotRegistered(name);
	}
	
	public String getDefaultClassLoaderName() {
		return defaultClassLoader;
	}
	
	public ClassLoader getDefaultClassLoader() throws ClassLoaderNotRegistered {
		if (classLoaders.containsKey(defaultClassLoader)) {
			return classLoaders.get(defaultClassLoader);
		}
		throw new ClassLoaderNotRegistered(defaultClassLoader);
	}
}
