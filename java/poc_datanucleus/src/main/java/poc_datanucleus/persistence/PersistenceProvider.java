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
package poc_datanucleus.persistence;

import java.io.IOException;
import java.lang.reflect.InvocationTargetException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Map.Entry;
import java.util.Properties;
import javax.jdo.PersistenceManager;
import javax.jdo.PersistenceManagerFactory;
import javax.jdo.Query;
import javax.jdo.Transaction;
import javax.jdo.metadata.ClassMetadata;
import javax.jdo.metadata.FieldMetadata;
import javax.jdo.metadata.Indexed;
import javax.jdo.metadata.InheritanceMetadata;
import javax.jdo.metadata.JDOMetadata;
import javax.jdo.metadata.PackageMetadata;
import javax.jdo.metadata.VersionMetadata;

import org.datanucleus.PropertyNames;
import org.datanucleus.api.jdo.JDOPersistenceManagerFactory;
import org.datanucleus.enhancer.DataNucleusEnhancer;
import org.datanucleus.exceptions.NucleusException;
import org.datanucleus.metadata.PersistenceUnitMetaData;

import poc_datanucleus.resolver.ClassLoaderNotRegistered;
import poc_datanucleus.resolver.ClassLoaderSingletonProvider;
import poc_datanucleus.utils.JavaClassLoaderSimple;
import poc_datanucleus.utils.StreamUtils;



/**
 * @author Gabriel Dimitriu
 *
 */
public class PersistenceProvider {

	private PersistenceUnitMetaData persistenceUnit = null;
	
	private PersistenceManagerFactory persistenceManagerFactory = null;
	
	private JavaClassLoaderSimple runtimeClassLoader;
	
	private String persistenceClass = "poc_datanucleus.persistence.PersistenceImpl";
	
	private String persistenceInterface1 = "poc_datanucleus.persistence.InterfaceImpl1";
	
	private String persistenceInterface2 = "poc_datanucleus.persistence.InterfaceImpl2";
	
//	private JDOMetadata mdata = null;
	
	private IPersistence persist = null;
	
	private PersistenceManager pm = null;
	/**
	 * 
	 */
	public PersistenceProvider() {
		this.getClass().getClassLoader();
		// TODO Auto-generated constructor stub
		runtimeClassLoader = new JavaClassLoaderSimple(ClassLoader.getSystemClassLoader());
	}

	public void enhance() {
		persistenceUnit = new PersistenceUnitMetaData("poc", "RESOURCE_LOCAL", null);
		persistenceUnit.setExcludeUnlistedClasses(false);
		persistenceUnit.addProperty("javax.jdo.option.ConnectionURL", "jdbc:postgresql://localhost:5432/chappy");
		persistenceUnit.addProperty("javax.jdo.option.ConnectionUserName", "chappy");
		persistenceUnit.addProperty("javax.jdo.option.ConnectionPassword", "12345678");
		persistenceUnit.addProperty("javax.jdo.option.ConnectionDriverName","org.postgresql.Driver");
		persistenceUnit.addProperty("javax.jdo.option.Mapping", "odf");
		persistenceUnit.addProperty(PropertyNames.PROPERTY_SCHEMA_AUTOCREATE_ALL, "true");
		persistenceUnit.addProperty("datanucleus.rdbms.dynamicSchemaUpdates", "true");
		Map<Object, Object> props = new HashMap<Object, Object>();
		props.putAll(persistenceUnit.getProperties());
		props.put("javax.jdo.PersistenceManagerFactoryClass","org.datanucleus.api.jdo.JDOPersistenceManagerFactory");
		props.put(PropertyNames.PROPERTY_CLASSLOADER_PRIMARY, runtimeClassLoader);
		props.put("datanucleus.autoStartMechanism","None");
		props.put(PropertyNames.PROPERTY_MAX_FETCH_DEPTH, "-1");
		props.put(PropertyNames.PROPERTY_CLASSLOADER_RESOLVER_NAME, "poc_datanucleus.resolver.ChappyClassLoaderResolver");
		props.put("targetDirectory", "d:\tmp");
		//enhance classes
		Properties enhancerProps = new Properties();
		enhancerProps.setProperty("targetDirectory", "d:\\tmp");
		DataNucleusEnhancer enhancer = new DataNucleusEnhancer("JDO", enhancerProps);
		enhancer =enhancer.setVerbose(true);
		enhancer = enhancer.setSystemOut(true);
		enhancer = enhancer.setOutputDirectory("d:\\tmp");
		enhancer = enhancer.addPersistenceUnit(persistenceUnit);
		//create manager factory
		try {
			Class<?> pmfC = runtimeClassLoader.loadClass("org.datanucleus.api.jdo.JDOPersistenceManagerFactory");
			persistenceManagerFactory = (PersistenceManagerFactory) pmfC.getDeclaredConstructor(Map.class).newInstance(props);
		} catch (InstantiationException | IllegalAccessException | ClassNotFoundException | IllegalArgumentException | InvocationTargetException | NoSuchMethodException | SecurityException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
//		mdata  = persistenceManagerFactory.newMetadata();
		
//		populateMetadata(mdata, cl);
//		ClassLoaderResolver clr = ((JDOPersistenceManagerFactory)persistenceManagerFactory).getNucleusContext().getClassLoaderResolver(runtimeClassLoader);
		try {
			JavaClassLoaderSimple compileClassLoader = new JavaClassLoaderSimple(ClassLoader.getSystemClassLoader());
			try {
				ClassLoaderSingletonProvider.getInstance().registerClassLoader("runtime", runtimeClassLoader);
				ClassLoaderSingletonProvider.getInstance().registerClassLoader("compile", compileClassLoader);
				ClassLoaderSingletonProvider.getInstance().setDefaultClassLoader("compile");
			} catch (ClassLoaderNotRegistered e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
			Class<?> cl = null;
			try {
				cl = Class.forName(persistenceClass);
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			//add discovery classes
			compileClassLoader.loadClass(persistenceClass,
					StreamUtils.getBytesFromInputStream(ClassLoader.getSystemClassLoader().getResourceAsStream(cl.getName().replace('.', '/') + ".class")));
			persistenceUnit.addClassName(persistenceClass);
			enhancer.addClasses(persistenceClass);
			//add first interface
			try {
				cl = Class.forName(persistenceInterface1);
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			compileClassLoader.loadClass(persistenceInterface1,
					StreamUtils.getBytesFromInputStream(ClassLoader.getSystemClassLoader().getResourceAsStream(cl.getName().replace('.', '/') + ".class")));
			persistenceUnit.addClassName(persistenceInterface1);
			enhancer.addClasses(persistenceInterface1);
			//add second interface
			try {
				cl = Class.forName(persistenceInterface2);
			} catch (ClassNotFoundException e) {
				e.printStackTrace();
			}
			compileClassLoader.loadClass(persistenceInterface2,
					StreamUtils.getBytesFromInputStream(ClassLoader.getSystemClassLoader().getResourceAsStream(cl.getName().replace('.', '/') + ".class")));
			persistenceUnit.addClassName(persistenceInterface2);
			enhancer.addClasses(persistenceInterface2);
			enhancer.setClassLoader(compileClassLoader);
			enhancer.enhance();
			runtimeClassLoader.loadClass(persistenceClass, enhancer.getEnhancedBytes(persistenceClass));
			runtimeClassLoader.loadClass(persistenceInterface1, enhancer.getEnhancedBytes(persistenceInterface1));
			runtimeClassLoader.loadClass(persistenceInterface2, enhancer.getEnhancedBytes(persistenceInterface2));
			try {
				ClassLoaderSingletonProvider.getInstance().setDefaultClassLoader("runtime");
			} catch (ClassLoaderNotRegistered e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		} catch (ClassNotFoundException | NucleusException e) {
			e.printStackTrace();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
//		((JDOPersistenceManagerFactory) persistenceManagerFactory).getNucleusContext().getMetaDataManager().unloadMetaDataForClass(peristenceClass);
//		persistenceManagerFactory.registerMetadata(mdata);
				
	}
/*
	private static void populateMetadata(JDOMetadata jdomd, Class<?> cl)
	{
	    PackageMetadata pmd = jdomd.newPackageMetadata(cl.getPackage().getName());
	    ClassMetadata cmd = pmd.newClassMetadata(cl.getName());
	    cmd.setTable(cl.getSimpleName()).setDetachable(true).setIdentityType(javax.jdo.annotations.IdentityType.DATASTORE);
	    cmd.setPersistenceModifier(javax.jdo.metadata.ClassPersistenceModifier.PERSISTENCE_CAPABLE);

	    FieldMetadata fmd = cmd.newFieldMetadata("name");
	    fmd.setNullValue(javax.jdo.annotations.NullValue.DEFAULT).setColumn("name");
	    fmd = cmd.newFieldMetadata("data");
	    fmd.setNullValue(javax.jdo.annotations.NullValue.DEFAULT).setColumn("data");
	    InheritanceMetadata inhmd = cmd.newInheritanceMetadata();
	    inhmd.setStrategy(javax.jdo.annotations.InheritanceStrategy.NEW_TABLE);

	    VersionMetadata vermd = cmd.newVersionMetadata();
	    vermd.setStrategy(javax.jdo.annotations.VersionStrategy.VERSION_NUMBER).setColumn("version").setIndexed(Indexed.TRUE);
	}
*/
	public void persist() {
		Transaction transaction = null;
		try {
			
			persist = (IPersistence) runtimeClassLoader.loadClass(persistenceClass).newInstance();
			persist.setData("data persist");
			persist.setName("name persist");
			IInterface interf = (IInterface) runtimeClassLoader.loadClass(persistenceInterface1).newInstance();
			
			interf.setValue("data interface 1");
			persist.addInterface(interf);
			interf = (IInterface) runtimeClassLoader.loadClass(persistenceInterface2).newInstance();
			
			interf.setValue("data interface 2");
			persist.addInterface(interf);
			persist.addHashMapElement("key1", "value1");
			interf =  (IInterface) runtimeClassLoader.loadClass(persistenceInterface1).newInstance();
			interf.setValue("data interface 1 hashmap");
			persist.addHashMapElement("key1", interf);
			interf =  (IInterface) runtimeClassLoader.loadClass(persistenceInterface2).newInstance();
			interf.setValue("data interface 2 hashmap");
			persist.addHashMapElement("key2", interf);
			pm = persistenceManagerFactory.getPersistenceManager();
			transaction = pm.currentTransaction();
			transaction.begin();
			persist = pm.makePersistent(persist);
			transaction.commit();
		} catch (InstantiationException | IllegalAccessException | ClassNotFoundException e) {
			e.printStackTrace();
		}
	}

	public void query() throws ClassNotFoundException {
		PersistenceManager pm = persistenceManagerFactory.getPersistenceManager();
		JDOPersistenceManagerFactory jpm = (JDOPersistenceManagerFactory) persistenceManagerFactory;
		jpm.setPrimaryClassLoader(runtimeClassLoader);
//		jpm.registerMetadata(mdata);
		
		Class<?> customPersistenceImpl = runtimeClassLoader.loadClass("poc_datanucleus.persistence.PersistenceImpl");
		Transaction tx = pm.currentTransaction();
		if (customPersistenceImpl != null) {
			tx.begin();
			Query<?> query = pm.newQuery(customPersistenceImpl);
			
			System.out.println("search");
			@SuppressWarnings("unchecked")
			List<IPersistence> persisted = (List<IPersistence>) query.execute(customPersistenceImpl);
			for (IPersistence persist : persisted) {
				System.out.println(persist.getName() + "  " + persist.getData());
				if(persist.getListOfStrings() != null) {
					for (String str : persist.getListOfStrings()) {
						System.out.print(str + "...");
					}
					System.out.println("");
				}
				System.out.println("List of Interfaces ...");
				if(persist.getListOfInterfaces() != null) {
					for (IInterface str : persist.getListOfInterfaces()) {
						System.out.println(str.getValue());
					}
				}
				System.out.println("HashMap of String ...");
				if (persist.getHashMapOfStrings() != null) {
					for (Entry<String, String> entry : persist.getHashMapOfStrings().entrySet()) {
						System.out.println("key=" + entry.getKey() + " value=" + entry.getValue());
					}
				}
				
				System.out.println("HashMap of Interfaces ...");
				if (persist.getHashMapOfInterfaces() != null) {
					for (Entry<String, IInterface> entry : persist.getHashMapOfInterfaces().entrySet()) {
						System.out.println("key=" + entry.getKey() + " value=" + entry.getValue().getValue());
					}
				}
			}
			tx.commit();
		}
	}
	
	public void update() {
		System.out.println("... update the persisted data ...");
		IPersistence obj = (IPersistence) pm.detachCopy(persist);
		persist = obj;
		persist.addString("test_update_1");
		Transaction transaction = pm.currentTransaction();
		transaction.begin();
		persist = pm.makePersistent(persist);
		transaction.commit();
	}

	public void close() {
		persistenceManagerFactory.close();
	}
}
