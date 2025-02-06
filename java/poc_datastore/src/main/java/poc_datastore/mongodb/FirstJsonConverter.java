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
package poc_datastore.mongodb;

import org.bson.BsonReader;
import org.bson.BsonWriter;
import org.bson.Document;
import org.bson.codecs.Codec;
import org.bson.codecs.DecoderContext;
import org.bson.codecs.DocumentCodec;
import org.bson.codecs.EncoderContext;

import com.google.gson.Gson;

/**
 * @author Gabriel Dimitriu
 *
 */
public class FirstJsonConverter<T> implements Codec<T> {
	
	private final Class<T> encodedClass;
	
	public FirstJsonConverter(final Class<T> clasz) {
		encodedClass = clasz;
	}

	@Override
	public void encode(final BsonWriter writer, final T value, final EncoderContext context) {
		// Serialize object to json string
		Gson gson = new Gson();
		String json = gson.toJson(value);
		Document doc = Document.parse(json);
		new DocumentCodec().encode(writer, doc, context);
	}

	@Override
	public Class<T> getEncoderClass() {
		return encodedClass;
	}

	@Override
	public T decode(final BsonReader reader, final DecoderContext context) {
		Document doc = new DocumentCodec().decode(reader, context);
		Gson gson = new Gson();
		return (T) gson.fromJson(doc.toJson(), encodedClass);
	}

}
