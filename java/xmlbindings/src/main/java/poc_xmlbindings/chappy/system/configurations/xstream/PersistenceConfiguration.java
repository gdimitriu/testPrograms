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
 * this hold the persistence configuration module. 
 * @author Gabriel Dimitriu
 *
 */
public class PersistenceConfiguration {
	
	@XStreamAlias("persistenceUnit")
	private String persistenceUnit;
	
	@XStreamAlias("framework")
	private String framework;
	
	@XStreamImplicit( itemFieldName = "feature")
	private FeaturePersistenceConfiguration[] features;
	
	/**
	 * dummy constructor
	 */
	public PersistenceConfiguration() {
		// TODO Auto-generated constructor stub
	}
	
	/**get the persistence framework
	 * @return the framework
	 */
	public String getFramework() {
		return framework;
	}
	/**
	 * set the persistence framework
	 * @param framework the framework to set
	 */
	public void setFramework(final String framework) {
		this.framework = framework;
	}

	/**
	 * get the persistence framework plugin feature
	 * @return the features
	 */
	public FeaturePersistenceConfiguration[] getFeatures() {
		return features;
	}

	/**
	 * set the persistence framework plugin feature
	 * @param features the features to set
	 */
	public void setFeatures(final FeaturePersistenceConfiguration[] features) {
		this.features = features;
	}

	/**
	 * @return the persistenceUnit
	 */
	public String getPersistenceUnit() {
		return persistenceUnit;
	}

	/**
	 * @param persistenceUnit the persistenceUnit to set
	 */
	public void setPersistenceUnit(final String persistenceUnit) {
		this.persistenceUnit = persistenceUnit;
	}

}
