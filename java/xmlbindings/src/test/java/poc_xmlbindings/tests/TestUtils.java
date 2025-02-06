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
package poc_xmlbindings.tests;

import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.InputStreamReader;
import java.util.stream.Collectors;

/**
 * utils for unitests
 * @author Gabriel Dimitriu
 *
 */
public final class TestUtils {

	/**
	 * 
	 */
	private TestUtils() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * get the String from the resource without spaces and LR and CR
	 * @param resourceFile resource file
	 * @return the stripped String from the resource.
	 */
	public static String getStringFromResource(final String resourceFile) {
		return  new BufferedReader(new InputStreamReader(
				TestUtils.class.getClassLoader().getResourceAsStream(resourceFile)))
		  .lines().map(s -> s.trim()).collect(Collectors.joining(""));
	}
	
	/**
	 * strip the spaces and LR and CR
	 * @param str the string
	 * @return the stripped string
	 */
	public static String stripSpacesAndLF(final String str) {
		return new BufferedReader(new InputStreamReader(
				new ByteArrayInputStream(str.getBytes())))
				.lines().map(s -> s.trim()).collect(Collectors.joining("")); 
	}
}
