/*!
 * \file            ds_fieldtypes.h
 * \brief           Record field types enumeration.
 * \author          Paul Griffiths
 * \copyright       Copyright 2014 Paul Griffiths. Distributed under the terms
 * of the GNU General Public License. <http://www.gnu.org/licenses/>
 */

#ifndef PG_GENERAL_LEDGER_DS_FIELDTYPES_H
#define PG_GENERAL_LEDGER_DS_FIELDTYPES_H

/*!  Enumeration for field type  */
enum ds_field_types {
    DS_FIELD_STRING,        /*!<  Field is string type      */
    DS_FIELD_INT,           /*!<  Field is integer type     */
    DS_FIELD_BOOLEAN,       /*!<  Field is boolean type     */
    DS_FIELD_DOUBLE         /*!<  Field is double type      */
};

#endif      /*  PG_GENERAL_LEDGER_DS_FIELDTYPES_H  */

