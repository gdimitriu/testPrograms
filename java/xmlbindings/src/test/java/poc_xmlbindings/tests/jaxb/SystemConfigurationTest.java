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
package poc_xmlbindings.tests.jaxb;

import static org.junit.Assert.assertEquals;

import javax.xml.XMLConstants;
import javax.xml.bind.JAXBContext;
import javax.xml.bind.JAXBException;
import javax.xml.bind.Unmarshaller;
import javax.xml.transform.stream.StreamSource;
import javax.xml.validation.Schema;
import javax.xml.validation.SchemaFactory;

import org.junit.Test;
import org.xml.sax.SAXException;

import poc_xmlbindings.chappy.system.configurations.jaxb.SystemConfiguration;
import poc_xmlbindings.chappy.system.configurations.jaxb.SystemConfigurations;

/**
 * Unitests for system configuration using JAXB.
 * @author Gabriel Dimitriu
 *
 */
public class SystemConfigurationTest {

	/**
	 * test a flow bindings using jaxb composes from two xsl steps.
	 * @throws JAXBException
	 * @throws SAXException 
	 */
	@Test
	public void SystemTestConfgurationlUnmarshallerTest() throws JAXBException, SAXException {
		JAXBContext context = JAXBContext.newInstance(SystemConfigurations.class);
		SchemaFactory sf = SchemaFactory.newInstance(XMLConstants.W3C_XML_SCHEMA_NS_URI);
		Schema schema = sf.newSchema(new StreamSource(
				getClass().getClassLoader().getResourceAsStream("SystemConfiguration.xsd")));
		Unmarshaller unmarshaller = context.createUnmarshaller();
		unmarshaller.setSchema(schema);
		SystemConfigurations configurations = (SystemConfigurations) unmarshaller
				.unmarshal(getClass().getClassLoader().getResourceAsStream("DefaultSystemConfiguration.xml"));
		SystemConfiguration configuration = configurations.getFirstConfiguration();
		assertEquals("serverName", "rest", configuration.getName());
		assertEquals("serverPort", "8100", configuration.getProperty());
	}
	
}
