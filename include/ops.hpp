#pragma once
#include "tensor.hpp"
#include "utils.hpp"
#include "binary_primitives.hpp"
#include "unary_primitives.hpp"


core::Tensor binary_op(const core::Tensor& left, const core::Tensor& right, core::Primitive& op){
    if(!checkBroadcastable(left.shape()->dims(), right.shape()->dims()))
        throw std::logic_error("Tensors are not compatiable!");
    
    auto bshape = broadcastShapes(left.shape()->dims(), right.shape()->dims());
    auto bleft = broadcastTo(left, bshape);
    auto bright = broadcastTo(right, bshape);
    size_t out_size = 1;
    for (auto dim : bshape)
        out_size *= dim;
    
    auto out = core::Tensor(bshape, new float[out_size]);
    op.eval({bleft, bright}, out);
    return out;
}


namespace ops{
core::Tensor unary_op(const core::Tensor& in, core::Primitive& op){    
    auto out = core::Tensor(in.shape()->dims(), new float[in.size()]);
    op.eval({in}, out);
    return out;
}



core::Tensor add(const core::Tensor& left, const core::Tensor& right){
    // We are going to make it lazy
    core::Add op;
    return binary_op(left, right, op);
}

core::Tensor substract(const core::Tensor& left, const core::Tensor& right){
    // We are going to make it lazy
    core::Substract op;
    return binary_op(left, right, op);
}

core::Tensor divide(const core::Tensor& left, const core::Tensor& right){
    // We are going to make it lazy
    core::Divide op;
    return binary_op(left, right, op);
}

core::Tensor multiply(const core::Tensor& left, const core::Tensor& right){
    // We are going to make it lazy
    core::Divide op;
    return binary_op(left, right, op);
}

core::Tensor log(const core::Tensor& in){
    core::Log op;
    return unary_op(in, op);
}

core::Tensor sqrt(const core::Tensor& in){
    core::Sqrt op;
    return unary_op(in, op);
}

core::Tensor matmul(const core::Tensor& left, const core::Tensor& right){
    const std::vector<int>& leftShape = left.shape()->dims();
    const std::vector<int>& rightShape = right.shape()->dims();
    std::vector<int> leftBaseShape(leftShape.begin(), leftShape.end()-2);
    std::vector<int> rightBaseShape(rightShape.begin(), rightShape.end()-2);

    
    auto outShape = broadcastShapes(leftBaseShape, rightBaseShape);
    outShape.push_back(left.shape()->dims()[left.shape()->dims().size()-2]);
    outShape.push_back(right.shape()->dims()[right.shape()->dims().size()-1]);

    auto out = core::Tensor(outShape);

    core::Matmul op;
    op.eval({left, right}, out);   
    return out;
}
}