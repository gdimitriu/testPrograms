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
package poc_xmlbindings.tests.xstream;

import static org.junit.Assert.assertEquals;

import javax.xml.bind.JAXBException;
import org.junit.Test;
import org.xml.sax.SAXException;

import com.thoughtworks.xstream.XStream;
import poc_xmlbindings.chappy.system.configurations.xstream.FeaturePersistenceConfiguration;
import poc_xmlbindings.chappy.system.configurations.xstream.PersistenceConfiguration;
import poc_xmlbindings.chappy.system.configurations.xstream.PropertyConfiguration;
import poc_xmlbindings.chappy.system.configurations.xstream.SystemConfiguration;
import poc_xmlbindings.chappy.system.configurations.xstream.SystemConfigurations;
import poc_xmlbindings.tests.TestUtils;


/**
 * @author Gabriel Dimitriu
 *
 */
public class SystemConfigurationTest {

	/**
	 * 
	 */
	public SystemConfigurationTest() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * test a flow bindings using xstream composes from two xsl steps.
	 * @throws JAXBException 
	 * @throws SAXException 
	 */
	@Test
	public void SystemTestConfgurationlUnmarshallerTest() throws JAXBException, SAXException {
		final String XML_HEADER = "<?xml version=\"1.0\" encoding=\"UTF-8\"?>";
		XStream xstream = new XStream();
		xstream.alias("configurations", SystemConfigurations.class);
		xstream.alias("configuration", SystemConfiguration.class);
		xstream.alias("persistence", PersistenceConfiguration.class);
		xstream.alias("feature", FeaturePersistenceConfiguration.class);
		xstream.alias("property", PropertyConfiguration.class);
		xstream.autodetectAnnotations(true);
		SystemConfigurations configurations = (SystemConfigurations) xstream.fromXML(getClass().getClassLoader().getResourceAsStream("DefaultSystemConfiguration.xml"));
		SystemConfiguration configuration = configurations.getFirstConfiguration();
		assertEquals("serverName", "rest", configuration.getName());
		assertEquals("serverPort", "8100", configuration.getProperty());
		xstream = new XStream();
		xstream.alias("configurations", SystemConfigurations.class);
		xstream.alias("configuration", SystemConfiguration.class);
		xstream.alias("persistence", PersistenceConfiguration.class);
		xstream.alias("feature", FeaturePersistenceConfiguration.class);
		xstream.alias("property", PropertyConfiguration.class);
		xstream.autodetectAnnotations(true);
		assertEquals(TestUtils.getStringFromResource("DefaultSystemConfiguration.xml"),
				TestUtils.stripSpacesAndLF(XML_HEADER + xstream.toXML(configurations)));
	}
	
	
}
