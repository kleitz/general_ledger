general_ledger
==============

What is it?
-----------

**general_ledger** will be a fully-featured, open-source general ledger
system.

Who maintains it?
-----------------
**general_ledger** is written and maintained by Paul Griffiths.

The latest version
------------------
Details of the latest version can be found on the GitHub project page at
<https://github.com/paulgriffiths/general_ledger>.

Documentation
-------------
Up-to-date documentation can be found at
<https://github.com/paulgriffiths/general_ledger/wiki>.

Installation
------------
**general_ledger** is written in C. Type `make` to build. Development is still
at an early stage, but the instructions below may be followed to create a
database and work with sample data to get started working on the project.

To run general ledger, a database and appropriate users must be separately
set up. Currently, only MySQL databases are supported. It is recommended to
create an admin user with all rights, and a regular user with SELECT and
INSERT rights.

Update the file `conf_files/gl_db_conf.conf` with the hostname and database
name, and the name of the admin user. Update the file
`conf_files/gl_reports_conf.conf` with the hostname and database name, and the
name of the regular user.

`gl_db --init` may be run to delete an existing general ledger database
structure (if one exists), create a new database structure, and load it with
some provided sample data. `gl_db --delete`, `gl_db --create`, and
`gl_db --loadsample` may be used to run these operations individually.

On successful creation and loading of sample date, `gl_reports` may be used to
run reports on the sample data. Some sample commands are:

* `gl_reports --listusers` - list users
* `gl_reports --listentities` - list the corporate entities in the ledger
* `gl_reports --currenttb --entity=1` - show the current trial balance for
corporate entity number 1
* `gl_reports --entries` - show all journal entries
* `gl_reports --entries=1` - show journal entry number 1.

Both `gl_db` and `gl_reports` respond to the `-h` and `--help` options to
show a full list of supported options.

Licensing
---------
Please see the file called LICENSE.

Contacts
--------
* If you have a concrete bug report for **general_ledger** please go to the
GitHub issue tracker at
<https://github.com/paulgriffiths/general_ledger/issues>.

