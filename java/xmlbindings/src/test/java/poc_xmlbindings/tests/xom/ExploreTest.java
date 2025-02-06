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

package poc_xmlbindings.tests.xom;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.assertNotNull;
import static org.junit.Assert.fail;

import java.io.IOException;

import org.junit.Test;

import nu.xom.Builder;
import nu.xom.Document;
import nu.xom.Elements;
import nu.xom.ParsingException;

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
		Builder parser = new Builder();
		Document doc = null;
		try {
			doc = parser.build(getClass().getClassLoader().getResourceAsStream("FullXSDSchema.xsd"));
		} catch (ParsingException | IOException e) {
			fail("failed to load document:" + e.getLocalizedMessage());
		}
		assertNotNull("document is empty", doc);
		Elements elems = doc.getRootElement().getChildElements();
		assertEquals(8, elems.size());
	}
}
