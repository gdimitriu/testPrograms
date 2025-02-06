/**
    Copyright (c) 2017 Gabriel Dimitriu All rights reserved.
	DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This file is part of poc_xmlbindinds project.

    poc_xmlbindinds is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    poc_xmlbindinds is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with poc_xmlbindinds.  If not, see <http://www.gnu.org/licenses/>.
 */
package poc_xmlbindings.chappy.system.configurations.xstream;

import com.thoughtworks.xstream.annotations.XStreamAlias;
import com.thoughtworks.xstream.annotations.XStreamImplicit;

/**
 * this hold the persistence feature.
 * @author Gabriel Dimitriu
 *
 */

public class FeaturePersistenceConfiguration {

	@XStreamAlias("plugin")
	private String plugin;
	
	@XStreamImplicit(itemFieldName = "property")
	private PropertyConfiguration[] property;
	
	/**
	 * 
	 */
	public FeaturePersistenceConfiguration() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * get the feature name.
	 * @return name of the feature
	 */
	public String getPlugin() {
		return this.plugin;
	}
	/**
	 * get the property.
	 * @return property
	 */
	public String getProperty() {
		if (property != null) {
			return property[0].getValue();
		}
		return null;
	}
	
	/**
	 * get the property by nr.
	 * @param i
	 * @return property at i
	 */
	public PropertyConfiguration getProperty(final int i) {
		return property[i];
	}
	
	/**
	 * get all properties defined in this feature.
	 * @return all properties defined in this feature
	 */
	public PropertyConfiguration[] getAllProperties() {
		return property;
	}
}
