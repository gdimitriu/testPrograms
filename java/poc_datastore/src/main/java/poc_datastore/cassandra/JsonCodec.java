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
    
    This file is a version of codec presented in :    
    http://docs.datastax.com/en/developer/java-driver/3.2/manual/custom_codecs/
 */
package poc_datastore.cassandra;

import java.io.IOException;
import java.nio.ByteBuffer;

import com.datastax.driver.core.DataType;
import com.datastax.driver.core.ProtocolVersion;
import com.datastax.driver.core.TypeCodec;
import com.datastax.driver.core.exceptions.InvalidTypeException;
import com.fasterxml.jackson.core.JsonProcessingException;
import com.fasterxml.jackson.databind.JavaType;
import com.fasterxml.jackson.databind.ObjectMapper;
import com.fasterxml.jackson.databind.type.TypeFactory;

/**
 * @author Gabriel Dimitriu
 *
 */
/**
 * A simple Json codec.
 */
public class JsonCodec<T> extends TypeCodec<T> {

    private final ObjectMapper objectMapper = new ObjectMapper();

    public JsonCodec(Class<T> javaType) {
        super(DataType.varchar(), javaType);
    }

    @Override
    public ByteBuffer serialize(T value, ProtocolVersion protocolVersion) throws InvalidTypeException {
        if (value == null)
            return null;
        try {
            return ByteBuffer.wrap(objectMapper.writeValueAsBytes(value));
        } catch (JsonProcessingException e) {
            throw new InvalidTypeException(e.getMessage(), e);
        }
    }

    @Override
    @SuppressWarnings("unchecked")
    public T deserialize(ByteBuffer bytes, ProtocolVersion protocolVersion) throws InvalidTypeException {
        if (bytes == null)
            return null;
        try {
            byte[] b = new byte[bytes.remaining()];
            // always duplicate the ByteBuffer instance before consuming it!
            bytes.duplicate().get(b);
            return (T) objectMapper.readValue(b, toJacksonJavaType());
        } catch (IOException e) {
            throw new InvalidTypeException(e.getMessage(), e);
        }
    }

    @Override
    public String format(T value) throws InvalidTypeException {
        if (value == null)
            return "NULL";
        String json;
        try {
            json = objectMapper.writeValueAsString(value);
        } catch (IOException e) {
            throw new InvalidTypeException(e.getMessage(), e);
        }
        return '\'' + json.replace("\'", "''") + '\'';
    }

    @Override
    @SuppressWarnings("unchecked")
    public T parse(String value) throws InvalidTypeException {
        if (value == null || value.isEmpty() || value.equalsIgnoreCase("NULL"))
            return null;
        if (value.charAt(0) != '\'' || value.charAt(value.length() - 1) != '\'')
            throw new InvalidTypeException("JSON strings must be enclosed by single quotes");
        String json = value.substring(1, value.length() - 1).replace("''", "'");
        try {
            return (T) objectMapper.readValue(json, toJacksonJavaType());
        } catch (IOException e) {
            throw new InvalidTypeException(e.getMessage(), e);
        }
    }

    protected JavaType toJacksonJavaType() {
        return TypeFactory.defaultInstance().constructType(getJavaType().getType());
    }

}
