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

import java.util.List;
import java.util.Map;

/**
 * @author Gabriel Dimitriu
 *
 */
public interface IPersistence {

	public String getName();
	
	public void setName(String name);
	
	public String getData();

	public void setData(String data);
	
	public List<String> getListOfStrings();
	
	public void setListOfStrings(final List<String> listOfStrings);
	
	public void addString(final String toAdd);
	
	public void addInterface(IInterface toAdd);
	
	public List<IInterface> getListOfInterfaces();
	
	public void setListOfInterfaces(final List<IInterface> listOfInterfaces);

	public Map<String, String> getHashMapOfStrings();
	
	public void setHashMapOfStrings(Map<String, String> haspMapOfString);

	void addHashMapElement(String key, String value);
	
	public Map<String, IInterface> getHashMapOfInterfaces();
	
	public void setHashMapOfInterfaces(Map<String, IInterface> hashMapOfInterfaces);

	void addHashMapElement(String key, IInterface interf);
}
