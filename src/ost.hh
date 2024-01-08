#pragma once 

#include <stddef.h>
#include <type_traits>

namespace order_statistic_tree {

    struct NullDeleter { 
        void operator() (auto ) { } 
    }; 

    template <typename T, typename Deleter_ = NullDeleter> 
    struct WeightBalancedTree {

        using size_t = size_t;  
        using DataType = T; 
        using Deleter = Deleter_; 

        struct Node {
            T value; 
            size_t size; 
            Node *son[2]; 
            Node *parent; 
        }; 

        [[no_unique_address]]
        Deleter deleter;  

        Node *root; 

    }; 

    template <typename ...Args> 
    using WBT = WeightBalancedTree<Args...>; 

    template <typename T>
    WeightBalancedTree<T> *default_tree() {
        auto tree = new WeightBalancedTree<T>; 
        tree->deleter = {}; 
        tree->root = nullptr;  
        return tree; 
    }

    auto new_node(auto tree, auto value) {
        using TreeVal = decltype(*tree); 
        using TreeDecay = std::decay_t<TreeVal>;
        auto node = new typename TreeDecay::Node(); 
        node->value = value; 
        node->size = 1; 
        node->son[0] = node->son[1] = nullptr; 
        node->parent = nullptr; 
        return node; 
    }

    auto size_impl(auto node) {
        size_t v; 
        if (node == nullptr) {
            v = 0; 
        } else {
            v = node -> size; 
        } 
        return v; 
    }

    auto size(auto tree) {
        return size_impl(tree->root);
    }

    auto instantUpdateSize(auto tree, auto node) {
        node -> size = size_impl(node->son[0]) + size_impl(node->son[1]) + 1;  
        return ; 
    }

    auto rotate_left(auto tree, auto node) { 
        auto son = node -> son[1]; 
        auto grandson = son -> son[0]; 
        son -> son[0] = node; 
        node -> son[1] = grandson; 
        if (grandson != nullptr) {
            grandson -> parent = node; 
        }
        node -> parent = son; 
        instantUpdateSize(tree, node); 
        instantUpdateSize(tree, son); 
        return son; 
    }

    auto rotate_right(auto tree, auto node) {
        auto son = node -> son[0]; 
        auto grandson = son -> son[1]; 
        son -> son[1] = node; 
        node -> son[0] = grandson; 
        if (grandson != nullptr) {
            grandson -> parent = node; 
        }
        node -> parent = son; 
        instantUpdateSize(tree, node); 
        instantUpdateSize(tree, son); 
        return son; 
    } 

    auto insert_impl(auto tree, auto node, auto index, auto value) {
        if (node == nullptr) {
            return new_node(tree, value); 
        } 
        auto left_size = size_impl(node->son[0]); 
        decltype(node) update; 
        if (index <= left_size) {
            update = node->son[0] = insert_impl(tree, node->son[0], index, value); 
        } else {
            update = node->son[1] = insert_impl(tree, node->son[1], index - left_size - 1, value); 
        } 
        update -> parent = node; 
        node -> size += 1; 
        auto limitation = node -> size / 4; 
        if (size_impl(node->son[0]) < limitation) {
            node = rotate_left(tree, node); 
        } else if (size_impl(node->son[1]) < limitation) {
            node = rotate_right(tree, node); 
        } 
        return node; 
    }

    auto insert(auto tree, auto index, auto value) {
        tree->root = insert_impl(tree, tree->root, index, value); 
        tree->root->parent = nullptr; 
    }

    auto insert_last(auto tree, auto value) {
        insert(tree, size(tree), value); 
    }

    auto insert_first(auto tree, auto value) {
        insert(tree, 0, value); 
    } 

    auto query_impl(auto tree, auto node, auto idx) {
        auto left_size = size_impl(node->son[0]); 
        if (idx == left_size) {
            return node; 
        } else if (idx < left_size) {
            return query_impl(tree, node->son[0], idx); 
        } else {
            return query_impl(tree, node->son[1], idx - left_size - 1); 
        }     
    }

    auto query(auto tree, auto idx) {
        return query_impl(tree, tree->root, idx) -> value; 
    } 

    auto walk_impl(auto tree, auto node, auto walker) {
        if (node == nullptr) {
            return ; 
        }
        walk_impl(tree, node->son[0], walker);
        walker(node->value);
        walk_impl(tree, node->son[1], walker);
    }

    auto walk(auto tree, auto walker) {
        walk_impl(tree, tree->root, walker); 
    }

    auto height_impl(auto tree, auto node) {
        if (node == nullptr) {
            return 0; 
        }
        auto l = height_impl(tree, node->son[0]) + 1;
        auto r = height_impl(tree, node->son[1]) + 1;  
        if (l > r) {
            return l; 
        } else {
            return r; 
        } 
    }

    auto height(auto tree) {
        return height_impl(tree, tree->root);  
    }

}

namespace ost = order_statistic_tree; 