/**
 * File Name:order.c
*/

/** order_info
 * This structure contains information about gender , number
 *  person,tam,parsarg etc for verbs ,nouns,adjectives ,adverbs,verbs etx
 */


/* HEADER FILES */

#include "headers/struct.h"
struct order_info order[11]={
	{
	"v",
	"tam",
	"gender",
	"number",
	"person"
	},
	{
	"vn",
	"gender",
	"number",
	"case",
	"parsarg",
	"tam"
	},
	{
	"n",
	"gender",
	"number",
	"case",
	"parsarg",
	},
	{
	"p",
	},
	{
	"adj",
	"gender",
	"number",
	"case",
	"parsarg",
	},
	{
	"P",
	"gender",
	"number",
	"case",
	"parsarg",
	},
	{
	"Avy",
	},
	{
	"sh_n",
	"number",
	"gender",
	"number1",
	"case",
	"parsarg",
	},
	{
	"D",
	"gender",
	"number",
	"case",
	"parsarg",
	},
	{
	"sh_P",
	"person",
	"number",
	"gender",
	"number1",
	"case",
	"parsarg",
	}
};
