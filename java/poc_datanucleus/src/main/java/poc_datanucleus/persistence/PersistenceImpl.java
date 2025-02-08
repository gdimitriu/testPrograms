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

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import javax.jdo.annotations.Element;
import javax.jdo.annotations.Extension;
import javax.jdo.annotations.IdGeneratorStrategy;
import javax.jdo.annotations.Join;
import javax.jdo.annotations.Key;
import javax.jdo.annotations.Order;
import javax.jdo.annotations.PersistenceCapable;
import javax.jdo.annotations.Persistent;
import javax.jdo.annotations.Value;

/**
 * @author Gabriel Dimitriu
 *
 */
@PersistenceCapable(detachable = "true")
public class PersistenceImpl implements IPersistence {
	
	@Persistent(valueStrategy = IdGeneratorStrategy.UUIDHEX, primaryKey = "true")
	private String transactionId;

	@Persistent(defaultFetchGroup = "true")
	private String name;
	
	@Persistent(defaultFetchGroup = "true")
	private String data;
	
	@Persistent(defaultFetchGroup = "true")
	@Order
	@Join(column = "PersistenceImp_listOfStrings")
	private List<String> listOfStrings = new ArrayList<String>();
	
	@Persistent(defaultFetchGroup = "true", serializedElement = "true")
	@Order
	@Join(column = "PersistenceImp_listOfInterfaces")
	@Extension(key = "mapping-strategy", value = "per-implementation", vendorName = "datanucleus") //is default
//	@Extension(key = "implemention-classes", value = "poc_datanucleus.persistence.InterfaceImpl", vendorName = "datanucleus")
	private List<IInterface> listOfInterfaces = new ArrayList<IInterface>();
	
	@Persistent(defaultFetchGroup = "true")
	@Join(column = "PersistenceImp_HashMapOfStrings") //not necessary
	private Map<String, String> hashMapOfStrings = new HashMap<>();
	
	@Persistent(defaultFetchGroup = "true", serializedElement = "true")
	@Join(table = "PersistenceImp_HashMapOfInterfaces")
	@Key(types=java.lang.String.class)
	@Element(embedded="true")
	@Value (types = poc_datanucleus.persistence.IInterface.class)
	//@Value(types= {poc_datanucleus.persistence.InterfaceImpl1.class, poc_datanucleus.persistence.InterfaceImpl2.class})
	@Extension(key = "mapping-strategy", value = "per-implementation", vendorName = "datanucleus")
	private Map<String, IInterface> hashMapOfInterfaces = new HashMap<>();
	
	/**
	 * 
	 */
	public PersistenceImpl() {
		// TODO Auto-generated constructor stub
		listOfStrings.add("test1");
	}
	
	@Override
	public String getName() {
		return name;
	}
	
	@Override
	public void setName(String name) {
		this.name = name;
	}
	
	@Override
	public String getData() {
		return data;
	}
	
	@Override
	public void setData(String data) {
		this.data = data;
	}

	/**
	 * @return the listOfStrings
	 */
	public List<String> getListOfStrings() {
		return listOfStrings;
	}

	/**
	 * @param listOfStrings the listOfStrings to set
	 */
	public void setListOfStrings(final List<String> listOfStrings) {
		this.listOfStrings = listOfStrings;
	}

	@Override
	public void addString(String toAdd) {
		listOfStrings.add(toAdd);
	}
	
	/**
	 * @return the listOfStrings
	 */
	public List<IInterface> getListOfInterfaces() {
		return listOfInterfaces;
	}

	/**
	 * @param listOfStrings the listOfStrings to set
	 */
	public void setListOfInterfaces(final List<IInterface> listOfInterfaces) {
		this.listOfInterfaces = listOfInterfaces;
	}

	@Override
	public void addInterface(IInterface toAdd) {
		listOfInterfaces.add(toAdd);
	}
	
	@Override
	public Map<String, String> getHashMapOfStrings() {
		return hashMapOfStrings;
	}

	@Override
	public void setHashMapOfStrings(Map<String, String> haspMapOfString) {
		this.hashMapOfStrings = haspMapOfString;
	}

	@Override
	public void addHashMapElement(String key, String value) {
		this.hashMapOfStrings.put(key, value);
	}

	@Override
	public Map<String, IInterface> getHashMapOfInterfaces() {
		return hashMapOfInterfaces;
	}

	@Override
	public void setHashMapOfInterfaces(Map<String, IInterface> hashMapOfInterfaces) {
		this.hashMapOfInterfaces = hashMapOfInterfaces;
	}
	
	@Override
	public void addHashMapElement(String key, IInterface interf) {
		this.hashMapOfInterfaces.put(key, interf);
	}
}
