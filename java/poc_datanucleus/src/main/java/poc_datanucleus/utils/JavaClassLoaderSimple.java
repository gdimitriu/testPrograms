/**
    Copyright (c) 2017 Gabriel Dimitriu All rights reserved.
	DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This file is part of poc_datanucleus project.

    poc_datanucleus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    poc_datanucleus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with poc_datanucleus.  If not, see <http://www.gnu.org/licenses/>.
 */
package poc_datanucleus.utils;

import java.util.Base64;
import java.util.HashMap;
import java.util.Map;

/**
 * a simple ClassLoader used to load classes defined by bytecode. 
 * @author Gabriel Dimitriu
 *
 */
public class JavaClassLoaderSimple extends ClassLoader {
	
	private Map<String,Class<?>> types = new HashMap<String,Class<?>>();
	
	private ClassLoader system = ClassLoader.getSystemClassLoader();
	
	public JavaClassLoaderSimple(final ClassLoader classLoader) {
		super(classLoader);
	}
	
	@Override
	public Class<?> loadClass(final String name) throws ClassNotFoundException {
		if(name==null) {
			return null;
		}
		if(types.containsKey(name)){
			return types.get(name);
		}
		try {			
			Class<?> cls = system.loadClass(name);
			return cls;
		} catch (Throwable  e) {
			e.printStackTrace();
			return findSystemClass(name);
		}
	}
	
	public Class<?> loadClass(final String name, final String data) throws ClassNotFoundException {
		
		byte[] buffer = Base64.getDecoder().decode(data);
		Class<?> type = defineClass(null, buffer, 0, buffer.length);
		types.put(name,type);
		return type;
	}
	
	public Class<?> loadClass(final String name, final byte[] buffer) throws ClassNotFoundException {
		if (types.containsKey(name)) {
			return types.get(name);
		}
		Class<?> type = defineClass(null, buffer, 0, buffer.length);
		types.put(name,type);
		return type;
	}
}
