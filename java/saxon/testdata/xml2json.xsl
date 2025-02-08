<?xml version="1.0" encoding="UTF-8"?>
<xsl:stylesheet
        xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
        xmlns:fn="http://www.w3.org/2005/xpath-functions"
        xmlns:xs="http://www.w3.org/2001/XMLSchema"
        exclude-result-prefixes="fn xsl xs"
        version="3.0">
    <!--
            xmlns="http://www.w3.org/2013/XSL/json"

            xmlns:math="http://www.w3.org/2005/xpath-functions/math"


    -->

    <xsl:output method="text"/>
    <xsl:template match="/">
        <!--
        <xsl:value-of select="fn:xml-to-json(., map { 'indent' : true() })"/>
        <xsl:copy-of select="fn:xml-to-json(.)" />
        -->

        <xsl:value-of select="fn:xml-to-json(.)"/>
    </xsl:template>
</xsl:stylesheet>