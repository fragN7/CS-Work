<?xml version="1.0"?>
<xsl:stylesheet version="1.0"
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
  <xsl:template match="/">
    <MappedEDI>
      <xsl:apply-templates select="*"/>
    </MappedEDI>
  </xsl:template>

  <xsl:template match="*">
    <MappedSegment>
      <xsl:value-of select="name()"/>:
      <xsl:value-of select="."/>
    </MappedSegment>
  </xsl:template>
</xsl:stylesheet>
