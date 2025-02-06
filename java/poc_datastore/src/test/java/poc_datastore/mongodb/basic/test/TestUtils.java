/**
    Copyright (c) 2018 Gabriel Dimitriu All rights reserved.
	DO NOT ALTER OR REMOVE COPYRIGHT NOTICES OR THIS FILE HEADER.

    This file is part of poc_datastore project.

    poc_datanucleus is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    poc_datanucleus is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with poc_datastore.  If not, see <http://www.gnu.org/licenses/>.
 */
package poc_datastore.mongodb.basic.test;

import static org.junit.Assert.assertEquals;
import static org.junit.Assert.fail;

import java.util.Iterator;
import java.util.List;

import org.bson.Document;

import com.google.gson.Gson;
import com.google.gson.JsonSyntaxException;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;

/**
 * @author Gabriel Dimitriu
 *
 */
public final class TestUtils {

	/**
	 * 
	 */
	public TestUtils() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * Validate a mongo collection with the elements which should be there
	 * @param collection to validate
	 * @param elementList which should be in collection
	 * @throws JsonSyntaxException
	 */
	public static <T> void validateCollection(final MongoCollection<T> collection, final List<T> elementList)
			throws JsonSyntaxException {
		// Getting the iterable object
		FindIterable<T> iterDoc = collection.find();
		// Getting the iterator
		Iterator<T>it = iterDoc.iterator();
		int i = 0;
		while (it.hasNext()) {
			T itDoc = it.next();			
			assertEquals("not same element at position " + i, elementList.get(i), itDoc);
			i++;
		}
		assertEquals(elementList.size(), i);
	}
	
	/**
	 * Validate a MongoDB collection with the elements which should be there.
	 * @param collection to validate
	 * @param elementList which should be in collection
	 * @throws JsonSyntaxException
	 */
	public static <T> void validateDocumentCollection(final MongoCollection<Document> collection, final List<T> elementList)
			throws JsonSyntaxException {
		Gson gson;
		// Getting the iterable object
		FindIterable<Document> iterDoc = collection.find();
		// Getting the iterator
		Iterator<Document>it = iterDoc.iterator();
		int i = 0;
		while (it.hasNext()) {
			Document itDoc = (Document) it.next();
			gson = new Gson();
			@SuppressWarnings("unchecked")
			T elem = (T) gson.fromJson(itDoc.toJson(), elementList.get(0).getClass());
			assertEquals("not same element at position " + i, elementList.get(i), elem);
			i++;
		}
		assertEquals(elementList.size(), i);
	}
	
	/**
	 * Validate a MongoDB find iterator with the elements which should be there.
	 * @param elementList elements which should be in the find.
	 * @param itDoc the iterator which resulted from find.
	 */
	public static void validateListOfDocuments(final List<Document> elementList, final Iterator<Document> itDoc) {		
		if (!itDoc.hasNext() && !elementList.isEmpty()) {
			fail("should have some documents but got none");
		}
		if(itDoc.hasNext() && elementList.isEmpty()) {
			fail("should have none documents");
		}
		int i = 0;
		while(itDoc.hasNext()) {
			Document doc = (Document) itDoc.next();
			if (i > elementList.size()) {
				fail("there are more element in interable than in list");
			}
			assertEquals("document " + i + " should be equal",elementList.get(i), doc);
			i++;
		}
	}
}
