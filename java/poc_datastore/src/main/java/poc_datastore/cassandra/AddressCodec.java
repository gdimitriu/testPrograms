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
package poc_datastore.cassandra;

import java.nio.ByteBuffer;

import com.datastax.driver.core.ProtocolVersion;
import com.datastax.driver.core.TypeCodec;
import com.datastax.driver.core.UDTValue;
import com.datastax.driver.core.UserType;
import com.datastax.driver.core.exceptions.InvalidTypeException;

import poc_datastore.address.Address;

/**
 * @author Gabriel Dimitriu
 *
 */
public class AddressCodec extends TypeCodec<Address> {

    private final TypeCodec<UDTValue> innerCodec;

    private final UserType userType;

    public AddressCodec(final TypeCodec<UDTValue> innerCodec, final Class<Address> javaType) {
        super(innerCodec.getCqlType(), javaType);
        this.innerCodec = innerCodec;
        this.userType = (UserType)innerCodec.getCqlType();
    }

    @Override
    public ByteBuffer serialize(final Address value, final ProtocolVersion protocolVersion) throws InvalidTypeException {
        return innerCodec.serialize(toUDTValue(value), protocolVersion);
    }

    @Override
    public Address deserialize(final ByteBuffer bytes, final ProtocolVersion protocolVersion) throws InvalidTypeException {
        return toAddress(innerCodec.deserialize(bytes, protocolVersion));
    }

    @Override
    public Address parse(final String value) throws InvalidTypeException {
        return value == null || value.isEmpty() || value.equals(null) ? null : toAddress(innerCodec.parse(value));
    }

    @Override
    public String format(final Address value) throws InvalidTypeException {
        return value == null ? null : innerCodec.format(toUDTValue(value));
    }

    protected Address toAddress(final UDTValue value) {
        return value == null ? null : new Address(
            value.getString("city"), 
            value.getString("street")
        );
    }

    protected UDTValue toUDTValue(final Address value) {
        return value == null ? null : userType.newValue()
            .setString("city", value.getCity())
            .setString("street", value.getStreet());
    }
}

