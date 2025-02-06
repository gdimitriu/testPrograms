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

import static org.junit.Assert.assertTrue;

import java.util.ArrayList;
import java.util.List;

import org.bson.Document;
import org.bson.codecs.configuration.CodecRegistry;
import org.bson.codecs.pojo.PojoCodecProvider;
import org.junit.Test;

import com.google.gson.Gson;
import com.mongodb.MongoClient;
import com.mongodb.client.MongoCollection;

import poc_datastore.mongodb.FirstCodecRegistry;
import poc_datastore.pocelement.PocElement;

import org.bson.codecs.configuration.CodecRegistries;

/**
 * @author Gabriel Dimitriu
 *
 */
public class BaseOperationtests extends BaseTestOperations {

	@Test
	public void createCollectionInsertElemAndValidate() {
		// Creating a collection
		database.createCollection(POC_COLLECTION);
		// Retrieving a collection
		MongoCollection<Document> collection = database.getCollection(POC_COLLECTION);
		assertTrue("could not get the collection", database.listCollections().iterator().hasNext());
		List<PocElement> elementList = new ArrayList<>();
		elementList.add(new PocElement(1, "name1", "val1"));
		// Serialize object to json string
		Gson gson = new Gson();
		String json = gson.toJson(elementList.get(0));
		// Parse to bson document and insert
		Document doc = Document.parse(json);
		collection.insertOne(doc);

		TestUtils.validateDocumentCollection(collection, elementList);
		elementList.add(new PocElement(1, "name1", "val1"));
		// Serialize object to json string
		gson = new Gson();
		json = gson.toJson(elementList.get(1));
		// Parse to bson document and insert
		doc = Document.parse(json);
		collection.insertOne(doc);
		
		collection = database.getCollection(POC_COLLECTION);
		TestUtils.validateDocumentCollection(collection, elementList);
	}

	@Test
	public void createCollectionInsertElemAndValidateWConverter() {
		database = database.withCodecRegistry(new FirstCodecRegistry());
		// Creating a collection
		database.createCollection(POC_COLLECTION);
		// Retrieving a collection
		MongoCollection<PocElement> collection = database.getCollection(POC_COLLECTION, PocElement.class);
		/** missing codec decoder*/
		//assertTrue("could not get the collection", database.listCollections().iterator().hasNext());
		List<PocElement> elementList = new ArrayList<>();
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(0));
		TestUtils.validateCollection(collection, elementList);
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(1));
		collection = database.getCollection(POC_COLLECTION, PocElement.class);
		TestUtils.validateCollection(collection, elementList);
	}
	
	
	@Test
	public void createCollectionInsertElemAndValidateWPojoCodec() {
//		CodecProvider pojoCodecProvider = PojoCodecProvider.builder().register("poc_datastore.pocelement").build();
//		CodecRegistry pojoCodecRegistry = CodecRegistries.fromRegistries(MongoClient.getDefaultCodecRegistry(), CodecRegistries.fromProviders(pojoCodecProvider));
		CodecRegistry pojoCodecRegistry = CodecRegistries.fromRegistries(MongoClient.getDefaultCodecRegistry(),
	            CodecRegistries.fromProviders(PojoCodecProvider.builder().automatic(true).build()));
		database = database.withCodecRegistry(pojoCodecRegistry);
		// Creating a collection
		database.createCollection(POC_COLLECTION);
		// Retrieving a collection
		MongoCollection<PocElement> collection = database.getCollection(POC_COLLECTION, PocElement.class);
		assertTrue("could not get the collection", database.listCollections().iterator().hasNext());
		List<PocElement> elementList = new ArrayList<>();
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(0));
		TestUtils.validateCollection(collection, elementList);
		
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(1));
		collection = database.getCollection(POC_COLLECTION, PocElement.class);
		TestUtils.validateCollection(collection, elementList);
	}
	
	@Test
	public void createCollectionInsertElemAndValidateWCodec() {
		CodecRegistry jsonCodecRegistry = CodecRegistries.fromRegistries(MongoClient.getDefaultCodecRegistry(),
	            new FirstCodecRegistry());
		database = database.withCodecRegistry(jsonCodecRegistry);
		// Creating a collection
		database.createCollection(POC_COLLECTION);
		// Retrieving a collection
		MongoCollection<PocElement> collection = database.getCollection(POC_COLLECTION, PocElement.class);
		assertTrue("could not get the collection", database.listCollections().iterator().hasNext());
		List<PocElement> elementList = new ArrayList<>();
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(0));
		TestUtils.validateCollection(collection, elementList);
		
		elementList.add(new PocElement(1, "name1", "val1"));
		collection.insertOne(elementList.get(1));
		collection = database.getCollection(POC_COLLECTION, PocElement.class);
		TestUtils.validateCollection(collection, elementList);
	}
	

}
