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

package poc_xmlbindings.tests.w3cdom;

import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import java.io.IOException;

import javax.xml.parsers.DocumentBuilder;
import javax.xml.parsers.DocumentBuilderFactory;
import javax.xml.parsers.ParserConfigurationException;

import org.junit.Test;
import org.w3c.dom.Document;
import org.w3c.dom.Element;
import org.w3c.dom.NodeList;
import org.xml.sax.SAXException;

/**
 * @author Gabriel Dimitriu
 *
 */
public class ExploreTest {

	/**
	 * 
	 */
	public ExploreTest() {
		// TODO Auto-generated constructor stub
	}

	@Test
	public void exploreFullXSD() {
		DocumentBuilderFactory factory = DocumentBuilderFactory.newInstance();
		DocumentBuilder docBuilder = null;
		try {
			docBuilder = factory.newDocumentBuilder();
		} catch (ParserConfigurationException e) {
			fail("could not create document builder " + e.getLocalizedMessage());
		}
		Document doc = null;
		try {
			doc = docBuilder.parse(getClass().getClassLoader().getResourceAsStream("FullXSDSchema.xsd"));
		} catch (SAXException | IOException e) {
			fail("could not parse xsd schema " + e.getLocalizedMessage());
		}
		assertNotNull("document is empty", doc);
		Element elem = doc.getDocumentElement();
		NodeList children = elem.getChildNodes();
		children.getLength();
	}
}
