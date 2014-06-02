const char * db_list_users_report_sql(void) {
    static const char * query = 
        "SELECT"
        "  id AS 'User ID',"
        "  user_name AS 'Username',"
        "  first_name AS 'First Name',"
        "  last_name AS 'Last Name',"
        "  enabled AS 'Enabled?'"
        "  FROM users"
        "  ORDER BY id";
    return query;
}

