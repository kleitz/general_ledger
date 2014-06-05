const char * db_create_entities_table_sql(void) {
    static const char * query = 
        "CREATE TABLE entities ("
        "    id         INTEGER         NOT NULL AUTO_INCREMENT,"
        "    name       VARCHAR(100)    NOT NULL,"
        "    currency   CHAR(30)        NOT NULL DEFAULT 'USD',"
        "    parent     INT             NOT NULL,"
        "    aggregate  BOOLEAN         NOT NULL DEFAULT FALSE,"
        "  CONSTRAINT entities_pk"
        "    PRIMARY KEY (id),"
        "  CONSTRAINT entities_parent_fk"
        "    FOREIGN KEY (parent)"
        "    REFERENCES entities(id)"
        ");";
    return query;
}

