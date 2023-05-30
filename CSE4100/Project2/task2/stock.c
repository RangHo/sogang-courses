/**
 * \file stock.c
 * \brief Stock data structure implementations.
 */

#include "stock.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "debug.h"

struct stock_item *stock_alloc(int id, int price, int available)
{
    debug("allocating a stock item with:\n");
    debug("  id: %d\n", id);
    debug("  price: %d\n", price);
    debug("  available: %d\n", available);

    struct stock_item *item = malloc(sizeof(struct stock_item));
    if (item == NULL) {
        fprintf(stderr, "stock_alloc: malloc failed\n");
        return NULL;
    }

    item->id = id;
    item->price = price;
    item->available = available;

    return item;
}

void stock_free(struct stock_item *item)
{
    debug("freeing a stock item %d\n", item->id);

    /* Check if the item actualy exists
       If not, silently continue */
    if (item == NULL)
        return;

    /* Free the child nodes first */
    stock_free(item->left);
    stock_free(item->right);
    
    /* Free the item itself */
    free(item);
}

struct stock_item *stock_insert(struct stock_item *root, struct stock_item *item)
{
    debug("inserting a stock item %d\n", item->id);

    /* If the root is NULL, the item is the new root */
    if (root == NULL)
        return item;

    /* If the item is smaller than the root, insert it to the left */
    if (item->id < root->id) {
        debug("  going left\n");
        root->left = stock_insert(root->left, item);
        return root;
    }

    /* If the item is larger than the root, insert it to the right */
    if (item->id > root->id) {
        debug("  going right\n");
        root->right = stock_insert(root->right, item);
        return root;
    }

    /* If the item is equal to the root, update the root */
    root->price = item->price;
    root->available = item->available;
    return root;
}

struct stock_item *stock_find(struct stock_item *root, int id)
{
    debug("finding a stock item %d\n", id);

    /* If the root is NULL, the item is not found */
    if (root == NULL)
        return NULL;

    /* If the item is smaller than the root, search the left subtree */
    if (id < root->id) {
        debug("  going left\n");
        return stock_find(root->left, id);
    }

    /* If the item is larger than the root, search the right subtree */
    if (id > root->id) {
        debug("  going right\n");
        return stock_find(root->right, id);
    }

    /* If the item is equal to the root, return the root */
    debug("  found\n");
    return root;
}

bool stock_buy(struct stock_item *root, int id, int amount)
{
    debug("buying a stock item %d\n", id);

    /* Try finding the item */
    struct stock_item *target = stock_find(root, id);

    /* You can't buy nonexistent stock */
    if (target == NULL)
        return false;
    debug("  found the item\n");

    /* You also can't buy more than what's available */
    debug("  buying %d of %d left\n", amount, target->available);
    if (target->available < amount)
        return false;

    target->available -= amount;
    return true;
}

bool stock_sell(struct stock_item *root, int id, int amount)
{
    /* Try finding the item */
    struct stock_item *target = stock_find(root, id);

    /* You can't sell nonexistent stock */
    if (target == NULL)
        return false;

    target->available += amount;
    return true;
}

void stock_dump(struct stock_item *root, char *buf)
{
    static char item_info[64];
    
    /* If the root is NULL, leave the buffer as-is */
    if (root == NULL)
        return;

    /* Dump the current root */
    sprintf(item_info, "%d %d %d\n", root->id, root->price, root->available);
    strcat(buf, item_info);
    
    /* Dump the children */
    stock_dump(root->left, buf);
    stock_dump(root->right, buf);
}

void stock_print(struct stock_item *root)
{
    char buf[4096] = { '\0' };

    stock_dump(root, buf);
    printf("%s", buf);
}

struct stock_item *stock_init(const char *filename)
{
    debug("initializing stock from %s\n", filename);

    /* Open the file */
    FILE *fp = fopen(filename, "r");
    if (fp == NULL) {
        fprintf(stderr, "stock_init: failed to open stock file\n");
        return NULL;
    }

    /* Read everything until the end of the file */
    struct stock_item *root = NULL;
    int id, price, available;
    while (fscanf(fp, "%d %d %d\n", &id, &price, &available) != EOF) {
        /* Allocate a new item */
        struct stock_item *item = stock_alloc(id, price, available);
        if (item == NULL) {
            fprintf(stderr, "stock_init: failed to allocate stock item\n");
            fclose(fp);
            return NULL;
        }

        /* Insert the item to the tree */
        root = stock_insert(root, item);
    }

    /* Close the file */
    fclose(fp);

    return root;
}

bool stock_save(struct stock_item *root, const char *filename)
{
    debug("saving stock to %s\n", filename);

    /* Open the file */
    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        fprintf(stderr, "stock_save: failed to open stock file\n");
        return false;
    }

    /* Dump the stock to the file */
    char buf[4096] = { '\0' };
    stock_dump(root, buf);
    fprintf(fp, "%s", buf);

    /* Close the file */
    fclose(fp);

    return true;
}
