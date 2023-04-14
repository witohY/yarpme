/*
Copyright (c) 2015-2020, Intel Corporation
Copyright (c) 2019-2020, University of Utah

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at
     http://www.apache.org/licenses/LICENSE-2.0
Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

//////////////////////////////////////////////////////////////////////////////

#pragma once

#include "options.h"
#include "utils.h"
#include <cstddef>
#include <vector>

namespace yarpgen {
//生成抽象语法树AST
class GenPolicy {
  public:
    GenPolicy();

    // 限制语句数量
    size_t stmt_num_lim;

    // 单个LoopSequence中的循环数的最大值。
    size_t loop_seq_num_lim;

    // 表示LoopSequence中循环数分布的概率向量。
    std::vector<Probability<size_t>> loop_seq_num_distr;

    // 单个LoopNest的最大深度
    size_t loop_nest_depth_lim;
    // LoopNest深度分布的概率向量。
    std::vector<Probability<size_t>> loop_nest_depth_distr;

    // 循环深度的硬限制。
    size_t loop_depth_limit;

    // if-else语句深度的硬限制。
    size_t if_else_depth_limit;

    // 作用域中语句数量的最小值、最大值、概率分布
    size_t scope_stmt_min_num;
    size_t scope_stmt_max_num;
    std::vector<Probability<size_t>> scope_stmt_num_distr;

    // TODO: we want to replace constant parameters of iterators with something
    // smarter

    // 迭代器结束范围的最小值和最大值。
    size_t iters_end_limit_min;
    size_t iter_end_limit_max;
    // Step distribution for iterators 迭代器步骤分布的概率向量。
    std::vector<Probability<size_t>> iters_step_distr;

    // Distribution of statements type for structure generation
    //用于结构生成的语句类型分布的概率向量。
    std::vector<Probability<IRNodeKind>> stmt_kind_struct_distr;

    // Distribution of "else" branch in ifElseStmt
    // ifElseStmt中else分支的概率向量。
    std::vector<Probability<bool>> else_br_distr;

    // Distribution of statements type for population generation
    // 用于生成种群的语句类型分布的概率向量。
    std::vector<Probability<IRNodeKind>> stmt_kind_pop_distr;

    // Distribution of available integral types 整数类型
    std::vector<Probability<IntTypeID>> int_type_distr;

    // Number of external input variables 外部输入变量的数量的最小值和最大值。
    size_t min_inp_vars_num;
    size_t max_inp_vars_num;

    // Number of new arrays that we create in each loop scope
    // 每个循环作用域中新创建的数组数的最小值和最大值。 概率分布向量
    size_t min_new_arr_num;
    size_t max_new_arr_num;
    std::vector<Probability<size_t>> new_arr_num_distr;

    // Output kind probability
    std::vector<Probability<DataKind>> out_kind_distr;

    // Maximal depth of arithmetic expression 表达式深度
    size_t max_arith_depth;
    // Distribution of nodes in arithmetic expression 表达式节点分布
    std::vector<Probability<IRNodeKind>> arith_node_distr;
    // Unary operator distribution 一元
    std::vector<Probability<UnaryOp>> unary_op_distr; 
    // Binary operator distribution 二元
    std::vector<Probability<BinaryOp>> binary_op_distr;

    std::vector<Probability<LibCallKind>> c_lib_call_distr;
    std::vector<Probability<LibCallKind>> cxx_lib_call_distr;
    std::vector<Probability<LibCallKind>> ispc_lib_call_distr;

    static size_t leaves_prob_bump;
    // 结束循环方式的类型
    std::vector<Probability<LoopEndKind>> loop_end_kind_distr;

    std::vector<Probability<size_t>> pragma_num_distr;
    std::vector<Probability<PragmaKind>> pragma_kind_distr;

    std::vector<Probability<bool>> mutation_probability;

    // ISPC
    // Probability to generate loop header as foreach or foreach_tiled
    std::vector<Probability<bool>> foreach_distr;

    std::vector<Probability<bool>> apply_similar_op_distr;
    std::vector<Probability<SimilarOperators>> similar_op_distr;
    // This function overrides default distributions 覆盖原有概率分布
    void chooseAndApplySimilarOp();

    std::vector<Probability<bool>> apply_const_use_distr;
    std::vector<Probability<ConstUse>> const_use_distr;
    // This function overrides default distributions
    void chooseAndApplyConstUse();

    std::vector<Probability<bool>> use_special_const_distr;
    std::vector<Probability<SpecialConst>> special_const_distr;
    std::vector<Probability<bool>> use_lsb_bit_end_distr;
    std::vector<Probability<bool>> use_const_offset_distr;
    size_t max_offset;
    std::vector<Probability<bool>> pos_const_offset_distr;
    static size_t const_buf_size; //常量缓冲区大小
    //用于控制常量重复使用和变换的概率向量。
    std::vector<Probability<bool>> replace_in_buf_distr;
    std::vector<Probability<bool>> reuse_const_prob;
    std::vector<Probability<bool>> use_const_transform_distr;
    std::vector<Probability<UnaryOp>> const_transform_distr;

    // 用于控制常量重复使用和变换的概率向量。
    std::vector<Probability<bool>> allow_stencil_prob;
    size_t max_stencil_span = 4;
    std::vector<Probability<size_t>> stencil_span_distr;
    size_t max_arrs_in_stencil = 4;

    // 控制stencil的维度、偏移和维度重用的概率向量。
    std::vector<Probability<size_t>> arrs_in_stencil_distr;
    // If we want to use same dimensions for all arrays
    std::vector<Probability<bool>> stencil_same_dims_all_distr;
    // If we want to use the same dimension for each array
    std::vector<Probability<bool>> stencil_same_dims_one_arr_distr;
    // If we want to use same offsets in the same dimensions for all arrays
    std::vector<Probability<bool>> stencil_reuse_offset_distr;
    std::vector<Probability<bool>> stencil_in_dim_prob;

    double stencil_prob_weight_alternation = 0.75;
    // Probability to leave UB in DeadCode when it is allowed
    std::vector<Probability<bool>> ub_in_dc_prob;

  private:
    template <typename T>
    void uniformProbFromMax(std::vector<Probability<T>> &distr, size_t max_num,
                            size_t min_num = 0);

    SimilarOperators active_similar_op;
    ConstUse active_const_use;size_t min_offset;
    std::vector<Probability<size_t>> const_offset_distr;
    
};

} // namespace yarpgen
