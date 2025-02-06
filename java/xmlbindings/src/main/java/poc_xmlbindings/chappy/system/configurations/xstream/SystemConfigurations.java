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
 * @author Gabriel Dimitriu
 *
 */
//@XStreamAlias("configurations")
public class SystemConfigurations {
	
	@XStreamAlias("system")
	private SystemConfiguration systemConfiguration;
	@XStreamImplicit(itemFieldName = "configuration")
	private SystemConfiguration[] servicesConfigurations;
	@XStreamImplicit(itemFieldName = "persistence")
	private PersistenceConfiguration[] persistenceConfigurations;

	/**
	 * 
	 */
	public SystemConfigurations() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * get the first not system configuration.
	 * @return first services configuration
	 */
	public SystemConfiguration getFirstConfiguration() {
		if (servicesConfigurations.length > 0) {
			return servicesConfigurations[0];
		}
		return null;
	}


	/**
	 * get the services configurations.
	 * @return services configurations
	 */
	public SystemConfiguration[] getServicesConfigurations() {
		return servicesConfigurations;
	}

	/**
	 * get the system configuration.
	 * @return system configuration
	 */
	public SystemConfiguration getSystemConfiguration() {
		return systemConfiguration;
	}

	/** get the persistence configurations
	 * @return the persistenceConfigurations
	 */
	public PersistenceConfiguration[] getPersistenceConfigurations() {
		return persistenceConfigurations;
	}

	/**
	 * set the persistence configurations
	 * @param persistenceConfigurations the persistenceConfigurations to set
	 */
	public void setPersistenceConfigurations(final PersistenceConfiguration[] persistenceConfigurations) {
		this.persistenceConfigurations = persistenceConfigurations;
	}

	/**
	 * get the persistence configuration for the specific unit.
	 * @param frameworkName the framework name
	 * @param persistenceUnit the unit persistence name
	 * @param feature name
	 * @return configuration for the persistence.
	 */
	public PersistenceConfiguration getPersistenceConfiguration(final String persistenceUnit, final String frameworkName, 
			final String featureName) {
		for (PersistenceConfiguration conf : persistenceConfigurations) {
			if (conf.getFramework().equals(frameworkName) && conf.getPersistenceUnit().equals(persistenceUnit)) {
				for (FeaturePersistenceConfiguration feature : conf.getFeatures()) {
					if (feature.getPlugin().equals(featureName)) {
						return conf;
					}
				}
			}
		}
		return null;
	}

}
