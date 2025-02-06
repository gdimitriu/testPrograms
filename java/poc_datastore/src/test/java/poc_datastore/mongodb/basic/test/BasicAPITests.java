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

import static org.junit.Assert.*;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.bson.Document;
import org.junit.Test;

import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;

/**
 * Basic API tests from tutorials using base api.
 * @author Gabriel Dimitriu
 *
 */
public class BasicAPITests extends BaseTestOperations {
	/**
	 * 
	 */
	public BasicAPITests() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * some basic test for collection like:
	 * insert, update, find, delete, drop.
	 */
	@Test
	public void createInsertUpdateQueryDelete() {
		//create and validate collection
		database.createCollection(POC_COLLECTION);
		MongoCollection<Document> collection = database.getCollection(POC_COLLECTION);
		assertTrue("collection did not created successfully", database.listCollections().iterator().hasNext());
		//add first document to the collection
		List<Document> docList = new ArrayList<>();		
		docList.add(new Document("title", 1).append("key1", 1).append("key2", "value1"));
		collection.insertOne(docList.get(0));
		//validate that first element is in collection
		FindIterable<Document> documents = collection.find();
		Iterator<Document> itDoc = documents.iterator();		
		TestUtils.validateListOfDocuments(docList, itDoc);
		//add second document to the collection
		docList.add(new Document("title", 2).append("key1", 2).append("key2", "value2"));
		collection.insertOne(docList.get(1));
		//validate that the collection contains two documents
		documents = collection.find();
		itDoc = documents.iterator();		
		TestUtils.validateListOfDocuments(docList, itDoc);
		//update first document
		collection.updateOne(Filters.eq("title",1), Updates.set("key1", -1));
		//validate that the first document is update in collection
		documents = collection.find();
		itDoc = documents.iterator();
		docList.get(0).put("key1", -1);
		TestUtils.validateListOfDocuments(docList, itDoc);
		//do some filter on the collection
		documents = collection.find().filter(Filters.gt("key1", 0));
		itDoc = documents.iterator();
		TestUtils.validateListOfDocuments(docList.subList(1, docList.size()), itDoc);
		//delete a document using filter
		collection.deleteOne(Filters.lt("key1", 0));
		documents = collection.find();
		itDoc = documents.iterator();
		TestUtils.validateListOfDocuments(docList.subList(1, docList.size()), itDoc);
		//drop the collection
		collection.drop();
		collection = database.getCollection(POC_COLLECTION);
		assertTrue("collection is deleted successfully", database.listCollections().iterator().hasNext() == false);
	}
}
