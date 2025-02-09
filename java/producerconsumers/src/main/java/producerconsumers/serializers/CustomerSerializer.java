package producerconsumers.serializers;

import org.apache.kafka.common.errors.SerializationException;
import org.apache.kafka.common.header.Headers;
import org.apache.kafka.common.serialization.Serializer;
import producerconsumers.data.Customer;

import java.nio.ByteBuffer;
import java.util.Map;

public class CustomerSerializer implements Serializer<Customer> {

    @Override
    public void configure(Map<String, ?> configs, boolean isKey) {
        //nothing to configure
    }

    /**
     * We are serializing Customer as:
     * 4 byte int representing customerId
     * 4 byte int representing length of customerName in UTF-8 bytes (0 if name is NULL)
     * N bytes representing customerName in UTF-8
     * @param topic
     * @param data
     * @return
     */
    @Override
    public byte[] serialize(String topic, Customer data) {
        try {
            byte[] serializedName;
            int stringSize;
            if (data == null) {
                return null;
            } else {
                if (data.getCustomerName() != null) {
                    serializedName = data.getCustomerName().getBytes("UTF-8");
                    stringSize = serializedName.length;
                } else {
                    serializedName = new byte[0];
                    stringSize = 0;
                }
                ByteBuffer buffer = ByteBuffer.allocate(4 + 4 + stringSize);
                buffer.putInt(data.getCustomerID());
                buffer.putInt(stringSize);
                buffer.put(serializedName);
                return buffer.array();
            }
        } catch (Exception e) {
            throw new SerializationException("Error when serializing Customer to byte[] " + e);
        }
    }

    /**
     * I do not know what to write here !!!
     * @param topic the topic
     * @param headers the header ???
     * @param data the data customer class
     * @return
     */
    @Override
    public byte[] serialize(String topic, Headers headers, Customer data) {
        return serialize(topic, data);
    }

    @Override
    public void close() {
        //nothing to close
    }
}
