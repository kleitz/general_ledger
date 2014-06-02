const char * db_list_entities_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  id AS 'User ID',"
        "  name AS 'Entity Name',"
        "  currency AS 'Currency',"
        "  parent AS 'Parent'"
        "  FROM entities"
        "  ORDER BY id";
    return query;
}

