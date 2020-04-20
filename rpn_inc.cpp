#include "rpn_inc.hpp"
#include "rpn_types.hpp"
#include "rpn_go.hpp"
#include "rpn_far.hpp"
#include "rpn_fcmp.hpp"
#include "rpn_fbl.hpp"
#include "rpn_func.hpp"


RPNDouble Double;
RPNConst *r_const = &Double;
RPNFunPlus Plus;
RPNFunArithm *r_far = &Plus;

RPNElem* intermediate_classes[3] = {
	r_const, 
	r_far, 
	0
};

