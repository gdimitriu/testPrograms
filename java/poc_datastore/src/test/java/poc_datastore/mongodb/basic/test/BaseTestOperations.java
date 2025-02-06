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

import java.util.Iterator;

import org.bson.Document;
import org.junit.After;
import org.junit.Before;
import org.junit.Ignore;
import org.junit.Test;

import com.mongodb.MongoClient;
import com.mongodb.MongoCredential;
import com.mongodb.client.FindIterable;
import com.mongodb.client.MongoCollection;
import com.mongodb.client.MongoDatabase;
import com.mongodb.client.model.Filters;
import com.mongodb.client.model.Updates;

/**
 * @author Gabriel Dimitriu
 *
 */
public abstract class BaseTestOperations {

	protected MongoClient mongo = null;
	
	protected MongoCredential credential = null;
	
	protected MongoDatabase database = null;
	
	protected static final String DATABASE_NAME = "poc_datastore";
	
	protected static final String POC_COLLECTION = "poc_collection";
	
	/**
	 * @throws java.lang.Exception
	 */
	@Before
	public void setUp() throws Exception {
		createDatabaseConnection();
	}

	/**
	 * @throws java.lang.Exception
	 */
	@After
	public void tearDown() throws Exception {
		database.drop();
		mongo.close();
	}
	
	/**
	 * 
	 */
	protected BaseTestOperations() {
		// TODO Auto-generated constructor stub
	}

	public void createDatabaseConnection() {
		// Creating a Mongo client
		mongo = new MongoClient("localhost", 27017);

		// Creating Credentials
		credential = MongoCredential.createCredential("poc_user", DATABASE_NAME, "password".toCharArray());

		// Accessing the database
		database = mongo.getDatabase(DATABASE_NAME);
	}
	
	/**
	 * this test is just for see how to connect and some example from tutorialspoint.com
	 * This not need to be enabled because is just a test to see how the api works.
	 */
	@Ignore @Test
	public void firstTestFromTutorials() {
		System.out.println("Credentials ::" + credential);
		// Creating a collection
		database.createCollection("sampleCollection");
		System.out.println("Collection created successfully");
		// Retrieving a collection
		MongoCollection<Document> collection = database.getCollection("sampleCollection");
		System.out.println("Collection myCollection selected successfully");
		Document document = new Document("title", "MongoDB").append("id", 1).append("description", "database")
				.append("likes", 100).append("url", "http://www.tutorialspoint.com/mongodb/")
				.append("by", "tutorials point");
		collection.insertOne(document);
		System.out.println("Document inserted successfully");

		// Getting the iterable object
		FindIterable<Document> iterDoc = collection.find();
		// Getting the iterator
		Iterator<Document> it = iterDoc.iterator();

		while (it.hasNext()) {
			Document itDoc = (Document) it.next();
			System.out.println(itDoc.toJson());
			System.out.println(itDoc);
		}

		collection.updateOne(Filters.eq("id", 1), Updates.set("likes", 150));
		System.out.println("Document update successfully...");

		// Getting the iterable object
		iterDoc = collection.find();
		// Getting the iterator
		it = iterDoc.iterator();

		while (it.hasNext()) {
			Document itDoc = (Document) it.next();
			System.out.println(itDoc.toJson());
			System.out.println(itDoc);
		}
	}
}
