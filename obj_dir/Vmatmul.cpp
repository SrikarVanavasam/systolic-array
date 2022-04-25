// Verilated -*- C++ -*-
// DESCRIPTION: Verilator output: Design implementation internals
// See Vmatmul.h for the primary calling header

#include "Vmatmul.h"
#include "Vmatmul__Syms.h"

//==========

VL_CTOR_IMP(Vmatmul) {
    Vmatmul__Syms* __restrict vlSymsp = __VlSymsp = new Vmatmul__Syms(this, name());
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Reset internal values
    
    // Reset structure values
    _ctor_var_reset();
}

void Vmatmul::__Vconfigure(Vmatmul__Syms* vlSymsp, bool first) {
    if (0 && first) {}  // Prevent unused
    this->__VlSymsp = vlSymsp;
}

Vmatmul::~Vmatmul() {
    delete __VlSymsp; __VlSymsp=NULL;
}

void Vmatmul::eval() {
    VL_DEBUG_IF(VL_DBG_MSGF("+++++TOP Evaluate Vmatmul::eval\n"); );
    Vmatmul__Syms* __restrict vlSymsp = this->__VlSymsp;  // Setup global symbol table
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
#ifdef VL_DEBUG
    // Debug assertions
    _eval_debug_assertions();
#endif  // VL_DEBUG
    // Initialize
    if (VL_UNLIKELY(!vlSymsp->__Vm_didInit)) _eval_initial_loop(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        VL_DEBUG_IF(VL_DBG_MSGF("+ Clock loop\n"););
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("matmul.sv", 1, "",
                "Verilated model didn't converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

void Vmatmul::_eval_initial_loop(Vmatmul__Syms* __restrict vlSymsp) {
    vlSymsp->__Vm_didInit = true;
    _eval_initial(vlSymsp);
    // Evaluate till stable
    int __VclockLoop = 0;
    QData __Vchange = 1;
    do {
        _eval_settle(vlSymsp);
        _eval(vlSymsp);
        if (VL_UNLIKELY(++__VclockLoop > 100)) {
            // About to fail, so enable debug to see what's not settling.
            // Note you must run make with OPT=-DVL_DEBUG for debug prints.
            int __Vsaved_debug = Verilated::debug();
            Verilated::debug(1);
            __Vchange = _change_request(vlSymsp);
            Verilated::debug(__Vsaved_debug);
            VL_FATAL_MT("matmul.sv", 1, "",
                "Verilated model didn't DC converge\n"
                "- See DIDNOTCONVERGE in the Verilator manual");
        } else {
            __Vchange = _change_request(vlSymsp);
        }
    } while (VL_UNLIKELY(__Vchange));
}

VL_INLINE_OPT void Vmatmul::_sequent__TOP__1(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_sequent__TOP__1\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data 
                = vlTOPp->in_data[2U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data 
                = vlTOPp->in_data[1U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_data 
                = vlTOPp->in_data[0U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data 
                = vlTOPp->matrix_multiply__DOT__row_wire
                [2U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data 
                = vlTOPp->matrix_multiply__DOT__row_wire
                [1U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data 
                = vlTOPp->matrix_multiply__DOT__row_wire
                [7U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data 
                = vlTOPp->matrix_multiply__DOT__row_wire
                [5U];
        }
    }
    if (vlTOPp->reset) {
        vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data = 0U;
    } else {
        if ((1U & (~ (IData)(vlTOPp->ld_weight)))) {
            vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data 
                = vlTOPp->matrix_multiply__DOT__row_wire
                [4U];
        }
    }
    vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->in_weights
                                          [0U] : ((
                                                   vlTOPp->in_data
                                                   [0U] 
                                                   * vlTOPp->matrix_multiply__DOT__mu_top__DOT__weight) 
                                                  + 
                                                  vlTOPp->in_weights
                                                  [0U])));
    vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->in_weights
                                          [2U] : ((
                                                   vlTOPp->matrix_multiply__DOT__row_wire
                                                   [2U] 
                                                   * vlTOPp->matrix_multiply__DOT__genblk2__BRA__2__KET____DOT__mu_row__DOT__weight) 
                                                  + 
                                                  vlTOPp->in_weights
                                                  [2U])));
    vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->in_weights
                                          [1U] : ((
                                                   vlTOPp->matrix_multiply__DOT__row_wire
                                                   [1U] 
                                                   * vlTOPp->matrix_multiply__DOT__genblk2__BRA__1__KET____DOT__mu_row__DOT__weight) 
                                                  + 
                                                  vlTOPp->in_weights
                                                  [1U])));
    vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->matrix_multiply__DOT__col_wire
                                          [3U] : ((
                                                   vlTOPp->in_data
                                                   [1U] 
                                                   * vlTOPp->matrix_multiply__DOT__genblk3__BRA__1__KET____DOT__mu_col__DOT__weight) 
                                                  + 
                                                  vlTOPp->matrix_multiply__DOT__col_wire
                                                  [3U])));
    vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->matrix_multiply__DOT__col_wire
                                          [5U] : ((
                                                   vlTOPp->matrix_multiply__DOT__row_wire
                                                   [5U] 
                                                   * vlTOPp->matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__DOT__weight) 
                                                  + 
                                                  vlTOPp->matrix_multiply__DOT__col_wire
                                                  [5U])));
    vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_sum 
        = ((IData)(vlTOPp->reset) ? 0U : ((IData)(vlTOPp->ld_weight)
                                           ? vlTOPp->matrix_multiply__DOT__col_wire
                                          [4U] : ((
                                                   vlTOPp->matrix_multiply__DOT__row_wire
                                                   [4U] 
                                                   * vlTOPp->matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__DOT__weight) 
                                                  + 
                                                  vlTOPp->matrix_multiply__DOT__col_wire
                                                  [4U])));
    vlTOPp->matrix_multiply__DOT__row_wire[7U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[4U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[1U] = vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[3U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[2U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[8U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[6U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[5U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__mu_top__DOT__weight 
                = vlTOPp->in_weights[0U];
        }
    }
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__genblk2__BRA__2__KET____DOT__mu_row__DOT__weight 
                = vlTOPp->in_weights[2U];
        }
    }
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__genblk2__BRA__1__KET____DOT__mu_row__DOT__weight 
                = vlTOPp->in_weights[1U];
        }
    }
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__genblk3__BRA__1__KET____DOT__mu_col__DOT__weight 
                = vlTOPp->matrix_multiply__DOT__col_wire
                [3U];
        }
    }
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__DOT__weight 
                = vlTOPp->matrix_multiply__DOT__col_wire
                [5U];
        }
    }
    if ((1U & (~ (IData)(vlTOPp->reset)))) {
        if (vlTOPp->ld_weight) {
            vlTOPp->matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__DOT__weight 
                = vlTOPp->matrix_multiply__DOT__col_wire
                [4U];
        }
    }
    vlTOPp->matrix_multiply__DOT__col_wire[3U] = vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[7U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[8U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[4U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[5U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[6U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_sum;
    vlTOPp->out_sum[0U] = vlTOPp->matrix_multiply__DOT__col_wire
        [6U];
    vlTOPp->out_sum[1U] = vlTOPp->matrix_multiply__DOT__col_wire
        [7U];
    vlTOPp->out_sum[2U] = vlTOPp->matrix_multiply__DOT__col_wire
        [8U];
}

void Vmatmul::_settle__TOP__2(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_settle__TOP__2\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->matrix_multiply__DOT__row_wire[1U] = vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[5U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[6U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[8U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[2U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[3U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[4U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data;
    vlTOPp->matrix_multiply__DOT__row_wire[7U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data;
    vlTOPp->matrix_multiply__DOT__col_wire[3U] = vlTOPp->matrix_multiply__DOT____Vcellout__mu_top__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[7U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[8U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[4U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[5U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_sum;
    vlTOPp->matrix_multiply__DOT__col_wire[6U] = vlTOPp->matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_sum;
    vlTOPp->out_sum[0U] = vlTOPp->matrix_multiply__DOT__col_wire
        [6U];
    vlTOPp->out_sum[1U] = vlTOPp->matrix_multiply__DOT__col_wire
        [7U];
    vlTOPp->out_sum[2U] = vlTOPp->matrix_multiply__DOT__col_wire
        [8U];
}

void Vmatmul::_eval(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_eval\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    if (((IData)(vlTOPp->clk) & (~ (IData)(vlTOPp->__Vclklast__TOP__clk)))) {
        vlTOPp->_sequent__TOP__1(vlSymsp);
    }
    // Final
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vmatmul::_eval_initial(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_eval_initial\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->__Vclklast__TOP__clk = vlTOPp->clk;
}

void Vmatmul::final() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::final\n"); );
    // Variables
    Vmatmul__Syms* __restrict vlSymsp = this->__VlSymsp;
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
}

void Vmatmul::_eval_settle(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_eval_settle\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    vlTOPp->_settle__TOP__2(vlSymsp);
}

VL_INLINE_OPT QData Vmatmul::_change_request(Vmatmul__Syms* __restrict vlSymsp) {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_change_request\n"); );
    Vmatmul* __restrict vlTOPp VL_ATTR_UNUSED = vlSymsp->TOPp;
    // Body
    // Change detection
    QData __req = false;  // Logically a bool
    return __req;
}

#ifdef VL_DEBUG
void Vmatmul::_eval_debug_assertions() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_eval_debug_assertions\n"); );
    // Body
    if (VL_UNLIKELY((reset & 0xfeU))) {
        Verilated::overWidthError("reset");}
    if (VL_UNLIKELY((clk & 0xfeU))) {
        Verilated::overWidthError("clk");}
    if (VL_UNLIKELY((ld_weight & 0xfeU))) {
        Verilated::overWidthError("ld_weight");}
}
#endif  // VL_DEBUG

void Vmatmul::_ctor_var_reset() {
    VL_DEBUG_IF(VL_DBG_MSGF("+    Vmatmul::_ctor_var_reset\n"); );
    // Body
    { int __Vi0=0; for (; __Vi0<3; ++__Vi0) {
            in_data[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<3; ++__Vi0) {
            in_weights[__Vi0] = VL_RAND_RESET_I(32);
    }}
    reset = VL_RAND_RESET_I(1);
    clk = VL_RAND_RESET_I(1);
    ld_weight = VL_RAND_RESET_I(1);
    { int __Vi0=0; for (; __Vi0<3; ++__Vi0) {
            out_sum[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<9; ++__Vi0) {
            matrix_multiply__DOT__row_wire[__Vi0] = VL_RAND_RESET_I(32);
    }}
    { int __Vi0=0; for (; __Vi0<9; ++__Vi0) {
            matrix_multiply__DOT__col_wire[__Vi0] = VL_RAND_RESET_I(32);
    }}
    matrix_multiply__DOT____Vcellout__mu_top__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__mu_top__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk1__BRA__2__KET____DOT__genblk1__BRA__1__KET____DOT__mu__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk2__BRA__1__KET____DOT__mu_row__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk2__BRA__2__KET____DOT__mu_row__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_sum = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk3__BRA__1__KET____DOT__mu_col__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT____Vcellout__genblk3__BRA__2__KET____DOT__mu_col__out_data = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__mu_top__DOT__weight = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__1__KET____DOT__mu__DOT__weight = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__genblk1__BRA__1__KET____DOT__genblk1__BRA__2__KET____DOT__mu__DOT__weight = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__genblk2__BRA__1__KET____DOT__mu_row__DOT__weight = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__genblk2__BRA__2__KET____DOT__mu_row__DOT__weight = VL_RAND_RESET_I(32);
    matrix_multiply__DOT__genblk3__BRA__1__KET____DOT__mu_col__DOT__weight = VL_RAND_RESET_I(32);
}
