#define ALLOW_EMPTY_HLS_STREAM_READS 1

//===------------------------------------------------------------*- C++ -*-===//
//
// Automatically generated file for High-level Synthesis (HLS).
//
//===----------------------------------------------------------------------===//
#include <algorithm>
#include <ap_axi_sdata.h>
#include <ap_fixed.h>
#include <ap_int.h>
#include <hls_math.h>
#include <hls_stream.h>
#include <hls_vector.h>
#include <math.h>
#include <stdint.h>
using namespace std;
void node_0_0(
  hls::stream< ap_uint<26> >& v0,
  hls::stream< ap_uint<26> >& v1,
  hls::stream< ap_uint<26> >& v2,
  hls::stream< ap_uint<26> >& v3,
  hls::stream< ap_uint<26> >& v4,
  hls::stream< ap_uint<26> >& v5,
  hls::stream< ap_uint<26> >& v6,
  hls::stream< ap_uint<26> >& v7,
  hls::stream< ap_uint<17> >& v8,
  hls::stream< ap_uint<17> >& v9,
  hls::stream< ap_uint<17> >& v10,
  hls::stream< ap_uint<17> >& v11,
  hls::stream< ap_uint<17> >& v12,
  hls::stream< ap_uint<17> >& v13,
  hls::stream< ap_uint<17> >& v14,
  hls::stream< ap_uint<17> >& v15
) {	// L4
  int32_t irf[8];	// L37
  #pragma HLS array_partition variable=irf complete dim=1

  for (int v17 = 0; v17 < 8; v17++) {	// L38
    irf[v17] = 0;	// L38
  }
  half drf[8];	// L39
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v19 = 0; v19 < 8; v19++) {	// L40
    drf[v19] = 0.000000;	// L40
  }
  int32_t drf_full[8];	// L41
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v21 = 0; v21 < 8; v21++) {	// L42
    drf_full[v21] = 0;	// L42
  }
  int32_t dsmask;	// L43
  dsmask = 0;	// L44
  int32_t crv_vld;	// L45
  crv_vld = 0;	// L46
  half crv_data;	// L47
  crv_data = 0.000000;	// L48
  int32_t crv_addr;	// L49
  crv_addr = 0;	// L50
  int32_t crv_mode;	// L51
  crv_mode = 0;	// L52
  int32_t crv_raw;	// L53
  crv_raw = 0;	// L54
  int32_t csd_vld;	// L55
  csd_vld = 0;	// L56
  ap_uint<26> csd_pkt;	// L57
  csd_pkt = 0;	// L58
  int32_t csd_dir;	// L59
  csd_dir = 0;	// L60
  int32_t row_id;	// L61
  row_id = 0;	// L62
  int32_t col_id;	// L63
  col_id = 0;	// L64
  ap_uint<17> txn_r;	// L65
  txn_r = 0;	// L66
  ap_uint<17> txs_r;	// L67
  txs_r = 0;	// L68
  ap_uint<17> txw_r;	// L69
  txw_r = 0;	// L70
  ap_uint<17> txe_r;	// L71
  txe_r = 0;	// L72
  half hold_v[4][2];	// L73
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v38 = 0; v38 < 4; v38++) {	// L74
    for (int v39 = 0; v39 < 2; v39++) {	// L74
      hold_v[v38][v39] = 0.000000;	// L74
    }
  }
  uint8_t hold_cnt[4];	// L75
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v41 = 0; v41 < 4; v41++) {	// L76
    hold_cnt[v41] = 0;	// L76
  }
  int32_t crv_ever;	// L77
  crv_ever = 0;	// L78
  int32_t fe_ever;	// L79
  fe_ever = 0;	// L80
  ap_uint<26> rbuf[4][2];	// L81
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v45 = 0; v45 < 4; v45++) {	// L82
    for (int v46 = 0; v46 < 2; v46++) {	// L82
      rbuf[v45][v46] = 0;	// L82
    }
  }
  uint8_t rbcnt[4];	// L83
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v48 = 0; v48 < 4; v48++) {	// L84
    rbcnt[v48] = 0;	// L84
  }
  int32_t cfg_isz;	// L85
  cfg_isz = 0;	// L86
  int32_t cfg_itsz;	// L87
  cfg_itsz = 0;	// L88
  uint8_t fetch_en;	// L89
  fetch_en = 0;	// L90
  uint8_t instr_cnt;	// L91
  instr_cnt = 0;	// L92
  uint8_t iter_cnt;	// L93
  iter_cnt = 0;	// L94
  uint8_t condition_reg;	// L95
  condition_reg = 0;	// L96
  uint8_t sb_v[5];	// L97
  #pragma HLS array_partition variable=sb_v complete dim=1

  for (int v56 = 0; v56 < 5; v56++) {	// L98
    sb_v[v56] = 0;	// L98
  }
  uint8_t sb_dst[5];	// L99
  #pragma HLS array_partition variable=sb_dst complete dim=1

  for (int v58 = 0; v58 < 5; v58++) {	// L100
    sb_dst[v58] = 0;	// L100
  }
  uint8_t sb_cmp[5];	// L101
  #pragma HLS array_partition variable=sb_cmp complete dim=1

  for (int v60 = 0; v60 < 5; v60++) {	// L102
    sb_cmp[v60] = 0;	// L102
  }
  uint8_t sb_rtr[5];	// L103
  #pragma HLS array_partition variable=sb_rtr complete dim=1

  for (int v62 = 0; v62 < 5; v62++) {	// L104
    sb_rtr[v62] = 0;	// L104
  }
  uint8_t sb_inj[5];	// L105
  #pragma HLS array_partition variable=sb_inj complete dim=1

  for (int v64 = 0; v64 < 5; v64++) {	// L106
    sb_inj[v64] = 0;	// L106
  }
  uint8_t sb_dir[5];	// L107
  #pragma HLS array_partition variable=sb_dir complete dim=1

  for (int v66 = 0; v66 < 5; v66++) {	// L108
    sb_dir[v66] = 0;	// L108
  }
  uint8_t sb_id[5];	// L109
  #pragma HLS array_partition variable=sb_id complete dim=1

  for (int v68 = 0; v68 < 5; v68++) {	// L110
    sb_id[v68] = 0;	// L110
  }
  uint8_t sb_rvld[5];	// L111
  #pragma HLS array_partition variable=sb_rvld complete dim=1

  for (int v70 = 0; v70 < 5; v70++) {	// L112
    sb_rvld[v70] = 0;	// L112
  }
  uint8_t sb_ix[5];	// L113
  #pragma HLS array_partition variable=sb_ix complete dim=1

  for (int v72 = 0; v72 < 5; v72++) {	// L114
    sb_ix[v72] = 0;	// L114
  }
  half resq[8];	// L115
  #pragma HLS array_partition variable=resq complete dim=1
#pragma HLS dependence variable=resq type=inter dependent=false

  for (int v74 = 0; v74 < 8; v74++) {	// L116
    resq[v74] = 0.000000;	// L116
  }
  uint8_t cmpq[8];	// L117
  #pragma HLS array_partition variable=cmpq complete dim=1
#pragma HLS dependence variable=cmpq type=inter dependent=false

  for (int v76 = 0; v76 < 8; v76++) {	// L118
    cmpq[v76] = 0;	// L118
  }
  uint8_t resq_wr;	// L119
  resq_wr = 0;	// L120
  l_S_t_0_t: for (int t = 0; t < 374; t++) {	// L121
  #pragma HLS pipeline II=1
    ap_uint<26> p_w;	// L122
    p_w = 0;	// L123
    ap_uint<26> p_e;	// L124
    p_e = 0;	// L125
    ap_uint<26> p_n;	// L126
    p_n = 0;	// L127
    ap_uint<26> p_s;	// L128
    p_s = 0;	// L129
    uint8_t v83 = rbcnt[0];	// L130
    int32_t v84 = v83;	// L131
    bool v85 = v84 < 2;	// L132
    if (v85) {	// L133
      ap_uint<26> v86;
      bool v87 = v0.read_nb(v86);
	// L134
      ap_uint<26> gw;	// L135
      gw = v86;	// L136
      bool okw;	// L137
      okw = v87;	// L138
      bool v90 = okw;	// L139
      if (v90) {	// L140
        ap_int<26> v91 = gw;	// L141
        p_w = v91;	// L142
      }
    }
    uint8_t v92 = rbcnt[1];	// L145
    int32_t v93 = v92;	// L146
    bool v94 = v93 < 2;	// L147
    if (v94) {	// L148
      ap_uint<26> v95;
      bool v96 = v1.read_nb(v95);
	// L149
      ap_uint<26> ge;	// L150
      ge = v95;	// L151
      bool oke;	// L152
      oke = v96;	// L153
      bool v99 = oke;	// L154
      if (v99) {	// L155
        ap_int<26> v100 = ge;	// L156
        p_e = v100;	// L157
      }
    }
    uint8_t v101 = rbcnt[2];	// L160
    int32_t v102 = v101;	// L161
    bool v103 = v102 < 2;	// L162
    if (v103) {	// L163
      ap_uint<26> v104;
      bool v105 = v2.read_nb(v104);
	// L164
      ap_uint<26> gn;	// L165
      gn = v104;	// L166
      bool okn;	// L167
      okn = v105;	// L168
      bool v108 = okn;	// L169
      if (v108) {	// L170
        ap_int<26> v109 = gn;	// L171
        p_n = v109;	// L172
      }
    }
    uint8_t v110 = rbcnt[3];	// L175
    int32_t v111 = v110;	// L176
    bool v112 = v111 < 2;	// L177
    if (v112) {	// L178
      ap_uint<26> v113;
      bool v114 = v3.read_nb(v113);
	// L179
      ap_uint<26> gs;	// L180
      gs = v113;	// L181
      bool oks;	// L182
      oks = v114;	// L183
      bool v117 = oks;	// L184
      if (v117) {	// L185
        ap_int<26> v118 = gs;	// L186
        p_s = v118;	// L187
      }
    }
    ap_uint<26> fin[4];	// L190
    for (int v120 = 0; v120 < 4; v120++) {	// L191
      fin[v120] = 0;	// L191
    }
    ap_int<26> v121 = p_w;	// L192
    fin[0] = v121;	// L193
    ap_int<26> v122 = p_e;	// L194
    fin[1] = v122;	// L195
    ap_int<26> v123 = p_n;	// L196
    fin[2] = v123;	// L197
    ap_int<26> v124 = p_s;	// L198
    fin[3] = v124;	// L199
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L200
      ap_uint<26> v126 = fin[d];	// L201
      bool v127;
      ap_int<26> v127_tmp = v126;
      v127 = v127_tmp[25];	// L202
      int32_t v128 = v127;	// L203
      bool v129 = v128 == 1;	// L204
      uint8_t v130 = rbcnt[d];	// L205
      int32_t v131 = v130;	// L206
      bool v132 = v131 < 2;	// L207
      bool v133 = v129 & v132;	// L208
      if (v133) {	// L209
        ap_uint<26> v134 = fin[d];	// L210
        uint8_t v135 = rbcnt[d];	// L211
        int v136 = v135;	// L212
        rbuf[d][v136] = v134;	// L213
        uint8_t v137 = rbcnt[d];	// L214
        ap_int<33> v138 = v137;	// L215
        ap_int<33> v139 = v138 + 1;	// L216
        uint8_t v140 = v139;	// L217
        rbcnt[d] = v140;	// L218
      }
    }
    ap_uint<26> hd[4];	// L221
    for (int v142 = 0; v142 < 4; v142++) {	// L222
      hd[v142] = 0;	// L222
    }
    int32_t hvld[4];	// L223
    for (int v144 = 0; v144 < 4; v144++) {	// L224
      hvld[v144] = 0;	// L224
    }
    int32_t hit[4];	// L225
    for (int v146 = 0; v146 < 4; v146++) {	// L226
      hit[v146] = 0;	// L226
    }
    int32_t axis[4];	// L227
    for (int v148 = 0; v148 < 4; v148++) {	// L228
      axis[v148] = 0;	// L228
    }
    int32_t v149 = col_id;	// L229
    axis[0] = v149;	// L230
    int32_t v150 = col_id;	// L231
    axis[1] = v150;	// L232
    int32_t v151 = row_id;	// L233
    axis[2] = v151;	// L234
    int32_t v152 = row_id;	// L235
    axis[3] = v152;	// L236
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L237
      uint8_t v154 = rbcnt[d1];	// L238
      int32_t v155 = v154;	// L239
      bool v156 = v155 > 0;	// L240
      if (v156) {	// L241
        ap_uint<26> v157 = rbuf[d1][0];	// L242
        hd[d1] = v157;	// L243
        hvld[d1] = 1;	// L244
        ap_uint<26> v158 = hd[d1];	// L245
        ap_int<4> v159;
        ap_int<26> v159_tmp = v158;
        v159 = v159_tmp(24, 21);	// L246
        int32_t v160 = axis[d1];	// L247
        int32_t v161 = v159;	// L248
        bool v162 = v161 == v160;	// L249
        if (v162) {	// L250
          hit[d1] = 1;	// L251
        }
      }
    }
    ap_uint<26> o_crv;	// L255
    o_crv = 0;	// L256
    int32_t crv_in;	// L257
    crv_in = -1;	// L258
    int32_t v165 = hit[3];	// L259
    bool v166 = v165 == 1;	// L260
    if (v166) {	// L261
      ap_uint<26> v167 = hd[3];	// L262
      o_crv = v167;	// L263
      crv_in = 3;	// L264
    } else {
      int32_t v168 = hit[2];	// L266
      bool v169 = v168 == 1;	// L267
      if (v169) {	// L268
        ap_uint<26> v170 = hd[2];	// L269
        o_crv = v170;	// L270
        crv_in = 2;	// L271
      } else {
        int32_t v171 = hit[1];	// L273
        bool v172 = v171 == 1;	// L274
        if (v172) {	// L275
          ap_uint<26> v173 = hd[1];	// L276
          o_crv = v173;	// L277
          crv_in = 1;	// L278
        } else {
          int32_t v174 = hit[0];	// L280
          bool v175 = v174 == 1;	// L281
          if (v175) {	// L282
            ap_uint<26> v176 = hd[0];	// L283
            o_crv = v176;	// L284
            crv_in = 0;	// L285
          }
        }
      }
    }
    int32_t pop[4];	// L290
    for (int v178 = 0; v178 < 4; v178++) {	// L291
      pop[v178] = 0;	// L291
    }
    int32_t inj_done;	// L292
    inj_done = 0;	// L293
    int32_t idir;	// L294
    idir = -1;	// L295
    ap_int<26> v181 = csd_pkt;	// L296
    bool v182;
    ap_int<26> v182_tmp = v181;
    v182 = v182_tmp[25];	// L297
    int32_t v183 = v182;	// L298
    bool v184 = v183 == 1;	// L299
    if (v184) {	// L300
      int32_t v185 = csd_dir;	// L301
      ap_int<33> v186 = v185;	// L302
      ap_int<33> v187 = 3 - v186;	// L303
      int32_t v188 = v187;	// L304
      idir = v188;	// L305
    }
    int32_t v189 = idir;	// L307
    bool v190 = v189 == 0;	// L308
    if (v190) {	// L309
      ap_int<26> v191 = csd_pkt;	// L310
      bool v192 = v4.write_nb(v191);
	// L311
      if (v192) {	// L312
        inj_done = 1;	// L313
      }
    } else {
      int32_t v193 = hvld[0];	// L316
      bool v194 = v193 == 1;	// L317
      int32_t v195 = hit[0];	// L318
      bool v196 = v195 == 0;	// L319
      bool v197 = v194 & v196;	// L320
      if (v197) {	// L321
        ap_uint<26> v198 = hd[0];	// L322
        bool v199 = v4.write_nb(v198);
	// L323
        if (v199) {	// L324
          pop[0] = 1;	// L325
        }
      }
    }
    int32_t v200 = idir;	// L329
    bool v201 = v200 == 1;	// L330
    if (v201) {	// L331
      ap_int<26> v202 = csd_pkt;	// L332
      bool v203 = v5.write_nb(v202);
	// L333
      if (v203) {	// L334
        inj_done = 1;	// L335
      }
    } else {
      int32_t v204 = hvld[1];	// L338
      bool v205 = v204 == 1;	// L339
      int32_t v206 = hit[1];	// L340
      bool v207 = v206 == 0;	// L341
      bool v208 = v205 & v207;	// L342
      if (v208) {	// L343
        ap_uint<26> v209 = hd[1];	// L344
        bool v210 = v5.write_nb(v209);
	// L345
        if (v210) {	// L346
          pop[1] = 1;	// L347
        }
      }
    }
    int32_t v211 = idir;	// L351
    bool v212 = v211 == 2;	// L352
    if (v212) {	// L353
      ap_int<26> v213 = csd_pkt;	// L354
      bool v214 = v6.write_nb(v213);
	// L355
      if (v214) {	// L356
        inj_done = 1;	// L357
      }
    } else {
      int32_t v215 = hvld[2];	// L360
      bool v216 = v215 == 1;	// L361
      int32_t v217 = hit[2];	// L362
      bool v218 = v217 == 0;	// L363
      bool v219 = v216 & v218;	// L364
      if (v219) {	// L365
        ap_uint<26> v220 = hd[2];	// L366
        bool v221 = v6.write_nb(v220);
	// L367
        if (v221) {	// L368
          pop[2] = 1;	// L369
        }
      }
    }
    int32_t v222 = idir;	// L373
    bool v223 = v222 == 3;	// L374
    if (v223) {	// L375
      ap_int<26> v224 = csd_pkt;	// L376
      bool v225 = v7.write_nb(v224);
	// L377
      if (v225) {	// L378
        inj_done = 1;	// L379
      }
    } else {
      int32_t v226 = hvld[3];	// L382
      bool v227 = v226 == 1;	// L383
      int32_t v228 = hit[3];	// L384
      bool v229 = v228 == 0;	// L385
      bool v230 = v227 & v229;	// L386
      if (v230) {	// L387
        ap_uint<26> v231 = hd[3];	// L388
        bool v232 = v7.write_nb(v231);
	// L389
        if (v232) {	// L390
          pop[3] = 1;	// L391
        }
      }
    }
    int32_t v233 = crv_in;	// L395
    bool v234 = v233 >= 0;	// L396
    if (v234) {	// L397
      int32_t v235 = crv_in;	// L398
      int v236 = v235;	// L399
      pop[v236] = 1;	// L400
    }
    l_S_d_2_d2: for (int d2 = 0; d2 < 4; d2++) {	// L402
      int32_t v238 = pop[d2];	// L403
      bool v239 = v238 == 1;	// L404
      if (v239) {	// L405
        l_S_sft_2_sft: for (int sft = 0; sft < 1; sft++) {	// L406
          ap_uint<26> v241 = rbuf[d2][(sft + 1)];	// L407
          rbuf[d2][sft] = v241;	// L408
        }
        uint8_t v242 = rbcnt[d2];	// L410
        ap_int<33> v243 = v242;	// L411
        ap_int<33> v244 = v243 - 1;	// L412
        uint8_t v245 = v244;	// L413
        rbcnt[d2] = v245;	// L414
      }
    }
    int32_t v246 = inj_done;	// L417
    bool v247 = v246 == 1;	// L418
    if (v247) {	// L419
      csd_pkt = 0;	// L420
    }
    ap_int<26> v248 = o_crv;	// L422
    bool v249;
    ap_int<26> v249_tmp = v248;
    v249 = v249_tmp[25];	// L423
    int32_t v250 = v249;	// L424
    crv_vld = v250;	// L425
    int32_t v251 = crv_vld;	// L426
    bool v252 = v251 == 1;	// L427
    if (v252) {	// L428
      crv_ever = 1;	// L429
    }
    ap_int<26> v253 = o_crv;	// L431
    int16_t v254;
    ap_int<26> v254_tmp = v253;
    v254 = v254_tmp(15, 0);	// L432
    half v255;
    union { uint16_t from; half to;} _converter_v254_to_v255 = {};
    _converter_v254_to_v255.from = v254;
    v255 = _converter_v254_to_v255.to;	// L433
    crv_data = v255;	// L434
    ap_int<26> v256 = o_crv;	// L435
    ap_int<4> v257;
    ap_int<26> v257_tmp = v256;
    v257 = v257_tmp(19, 16);	// L436
    int32_t v258 = v257;	// L437
    crv_addr = v258;	// L438
    ap_int<26> v259 = o_crv;	// L439
    bool v260;
    ap_int<26> v260_tmp = v259;
    v260 = v260_tmp[20];	// L440
    int32_t v261 = v260;	// L441
    crv_mode = v261;	// L442
    ap_int<26> v262 = o_crv;	// L443
    int16_t v263;
    ap_int<26> v263_tmp = v262;
    v263 = v263_tmp(15, 0);	// L444
    int32_t v264 = v263;	// L445
    crv_raw = v264;	// L446
    half rxv[4];	// L447
    for (int v266 = 0; v266 < 4; v266++) {	// L448
      rxv[v266] = 0.000000;	// L448
    }
    int32_t rxvld[4];	// L449
    for (int v268 = 0; v268 < 4; v268++) {	// L450
      rxvld[v268] = 0;	// L450
    }
    uint8_t v269 = hold_cnt[0];	// L451
    int32_t v270 = v269;	// L452
    bool v271 = v270 < 2;	// L453
    if (v271) {	// L454
      ap_uint<17> v272;
      bool v273 = v8.read_nb(v272);
	// L455
      ap_uint<17> sgn;	// L456
      sgn = v272;	// L457
      bool sqn;	// L458
      sqn = v273;	// L459
      bool v276 = sqn;	// L460
      int32_t v277 = v276;	// L461
      bool v278 = v277 == 1;	// L462
      if (v278) {	// L463
        ap_int<17> v279 = sgn;	// L464
        int16_t v280;
        ap_int<17> v280_tmp = v279;
        v280 = v280_tmp(16, 1);	// L465
        half v281;
        union { uint16_t from; half to;} _converter_v280_to_v281 = {};
        _converter_v280_to_v281.from = v280;
        v281 = _converter_v280_to_v281.to;	// L466
        rxv[0] = v281;	// L467
        rxvld[0] = 1;	// L468
      }
    }
    uint8_t v282 = hold_cnt[1];	// L471
    int32_t v283 = v282;	// L472
    bool v284 = v283 < 2;	// L473
    if (v284) {	// L474
      ap_uint<17> v285;
      bool v286 = v9.read_nb(v285);
	// L475
      ap_uint<17> sgs;	// L476
      sgs = v285;	// L477
      bool sqs;	// L478
      sqs = v286;	// L479
      bool v289 = sqs;	// L480
      int32_t v290 = v289;	// L481
      bool v291 = v290 == 1;	// L482
      if (v291) {	// L483
        ap_int<17> v292 = sgs;	// L484
        int16_t v293;
        ap_int<17> v293_tmp = v292;
        v293 = v293_tmp(16, 1);	// L485
        half v294;
        union { uint16_t from; half to;} _converter_v293_to_v294 = {};
        _converter_v293_to_v294.from = v293;
        v294 = _converter_v293_to_v294.to;	// L486
        rxv[1] = v294;	// L487
        rxvld[1] = 1;	// L488
      }
    }
    uint8_t v295 = hold_cnt[2];	// L491
    int32_t v296 = v295;	// L492
    bool v297 = v296 < 2;	// L493
    if (v297) {	// L494
      ap_uint<17> v298;
      bool v299 = v10.read_nb(v298);
	// L495
      ap_uint<17> sgw;	// L496
      sgw = v298;	// L497
      bool sqw;	// L498
      sqw = v299;	// L499
      bool v302 = sqw;	// L500
      int32_t v303 = v302;	// L501
      bool v304 = v303 == 1;	// L502
      if (v304) {	// L503
        ap_int<17> v305 = sgw;	// L504
        int16_t v306;
        ap_int<17> v306_tmp = v305;
        v306 = v306_tmp(16, 1);	// L505
        half v307;
        union { uint16_t from; half to;} _converter_v306_to_v307 = {};
        _converter_v306_to_v307.from = v306;
        v307 = _converter_v306_to_v307.to;	// L506
        rxv[2] = v307;	// L507
        rxvld[2] = 1;	// L508
      }
    }
    uint8_t v308 = hold_cnt[3];	// L511
    int32_t v309 = v308;	// L512
    bool v310 = v309 < 2;	// L513
    if (v310) {	// L514
      ap_uint<17> v311;
      bool v312 = v11.read_nb(v311);
	// L515
      ap_uint<17> sge;	// L516
      sge = v311;	// L517
      bool sqe;	// L518
      sqe = v312;	// L519
      bool v315 = sqe;	// L520
      int32_t v316 = v315;	// L521
      bool v317 = v316 == 1;	// L522
      if (v317) {	// L523
        ap_int<17> v318 = sge;	// L524
        int16_t v319;
        ap_int<17> v319_tmp = v318;
        v319 = v319_tmp(16, 1);	// L525
        half v320;
        union { uint16_t from; half to;} _converter_v319_to_v320 = {};
        _converter_v319_to_v320.from = v319;
        v320 = _converter_v319_to_v320.to;	// L526
        rxv[3] = v320;	// L527
        rxvld[3] = 1;	// L528
      }
    }
    l_S_d_4_d3: for (int d3 = 0; d3 < 4; d3++) {	// L531
      int32_t v322 = rxvld[d3];	// L532
      bool v323 = v322 == 1;	// L533
      if (v323) {	// L534
        half v324 = rxv[d3];	// L535
        uint8_t v325 = hold_cnt[d3];	// L536
        int v326 = v325;	// L537
        hold_v[d3][v326] = v324;	// L538
        uint8_t v327 = hold_cnt[d3];	// L539
        ap_int<33> v328 = v327;	// L540
        ap_int<33> v329 = v328 + 1;	// L541
        uint8_t v330 = v329;	// L542
        hold_cnt[d3] = v330;	// L543
      }
    }
    ap_uint<17> tx_n;	// L546
    tx_n = 0;	// L547
    ap_uint<17> tx_s;	// L548
    tx_s = 0;	// L549
    ap_uint<17> tx_w;	// L550
    tx_w = 0;	// L551
    ap_uint<17> tx_e;	// L552
    tx_e = 0;	// L553
    uint8_t v335 = sb_v[0];	// L554
    int32_t v336 = v335;	// L555
    bool v337 = v336 == 1;	// L556
    if (v337) {	// L557
      uint8_t v338 = sb_ix[0];	// L558
      int v339 = v338;	// L559
      half v340 = resq[v339];	// L560
      half wb;
#pragma HLS dependence variable=wb type=inter dependent=false	// L561
      wb = v340;	// L562
      uint8_t v342 = sb_cmp[0];	// L563
      int32_t v343 = v342;	// L564
      bool v344 = v343 == 1;	// L565
      if (v344) {	// L566
        uint8_t v345 = sb_ix[0];	// L567
        int v346 = v345;	// L568
        uint8_t v347 = cmpq[v346];	// L569
        condition_reg = v347;	// L570
      }
      uint8_t v348 = sb_rtr[0];	// L572
      int32_t v349 = v348;	// L573
      bool v350 = v349 == 1;	// L574
      if (v350) {	// L575
        uint8_t v351 = sb_inj[0];	// L576
        int32_t v352 = v351;	// L577
        bool v353 = v352 == 1;	// L578
        ap_int<26> v354 = csd_pkt;	// L579
        bool v355;
        ap_int<26> v355_tmp = v354;
        v355 = v355_tmp[25];	// L580
        int32_t v356 = v355;	// L581
        bool v357 = v356 == 0;	// L582
        bool v358 = v353 & v357;	// L583
        if (v358) {	// L584
          half v359 = wb;	// L585
          uint16_t v360;
          union { half from; uint16_t to;} _converter_v359_to_v360 = {};
          _converter_v359_to_v360.from = v359;
          v360 = _converter_v359_to_v360.to;	// L586
          ap_int<26> v361 = csd_pkt;	// L587
          ap_int<26> v362;
          ap_int<26> v362_tmp = v361;
          v362_tmp(15, 0) = v360;
          v362 = v362_tmp;	// L588
          csd_pkt = v362;	// L589
          uint8_t v363 = sb_dst[0];	// L590
          ap_uint<4> v364 = v363;	// L591
          ap_int<26> v365 = csd_pkt;	// L592
          ap_int<26> v366;
          ap_int<26> v366_tmp = v365;
          v366_tmp(19, 16) = v364;
          v366 = v366_tmp;	// L593
          csd_pkt = v366;	// L594
          uint8_t v367 = sb_id[0];	// L595
          ap_uint<4> v368 = v367;	// L596
          ap_int<26> v369 = csd_pkt;	// L597
          ap_int<26> v370;
          ap_int<26> v370_tmp = v369;
          v370_tmp(24, 21) = v368;
          v370 = v370_tmp;	// L598
          csd_pkt = v370;	// L599
          uint8_t v371 = sb_rvld[0];	// L600
          bool v372 = v371;	// L601
          ap_int<26> v373 = csd_pkt;	// L602
          ap_int<26> v374;
          ap_int<26> v374_tmp = v373;
          v374_tmp[25] = v372;          v374 = v374_tmp;	// L603
          csd_pkt = v374;	// L604
          uint8_t v375 = sb_dir[0];	// L605
          int32_t v376 = v375;	// L606
          csd_dir = v376;	// L607
        }
      } else {
        uint8_t v377 = sb_dst[0];	// L610
        int32_t v378 = v377;	// L611
        bool v379 = v378 >= 12;	// L612
        if (v379) {	// L613
          ap_uint<17> tw0;	// L614
          tw0 = 0;	// L615
          uint8_t v381 = sb_rvld[0];	// L616
          bool v382 = v381;	// L617
          ap_int<17> v383 = tw0;	// L618
          ap_int<17> v384;
          ap_int<17> v384_tmp = v383;
          v384_tmp[0] = v382;          v384 = v384_tmp;	// L619
          tw0 = v384;	// L620
          half v385 = wb;	// L621
          uint16_t v386;
          union { half from; uint16_t to;} _converter_v385_to_v386 = {};
          _converter_v385_to_v386.from = v385;
          v386 = _converter_v385_to_v386.to;	// L622
          ap_int<17> v387 = tw0;	// L623
          ap_int<17> v388;
          ap_int<17> v388_tmp = v387;
          v388_tmp(16, 1) = v386;
          v388 = v388_tmp;	// L624
          tw0 = v388;	// L625
          uint8_t v389 = sb_dst[0];	// L626
          int32_t v390 = v389;	// L627
          int32_t v391 = v390 & 3;	// L628
          bool v392 = v391 == 0;	// L629
          if (v392) {	// L630
            ap_int<17> v393 = tw0;	// L631
            tx_n = v393;	// L632
          } else {
            uint8_t v394 = sb_dst[0];	// L634
            int32_t v395 = v394;	// L635
            int32_t v396 = v395 & 3;	// L636
            bool v397 = v396 == 1;	// L637
            if (v397) {	// L638
              ap_int<17> v398 = tw0;	// L639
              tx_s = v398;	// L640
            } else {
              uint8_t v399 = sb_dst[0];	// L642
              int32_t v400 = v399;	// L643
              int32_t v401 = v400 & 3;	// L644
              bool v402 = v401 == 2;	// L645
              if (v402) {	// L646
                ap_int<17> v403 = tw0;	// L647
                tx_w = v403;	// L648
              } else {
                ap_int<17> v404 = tw0;	// L650
                tx_e = v404;	// L651
              }
            }
          }
        } else {
          uint8_t v405 = sb_rvld[0];	// L656
          int32_t v406 = v405;	// L657
          bool v407 = v406 == 1;	// L658
          if (v407) {	// L659
            uint8_t v408 = sb_dst[0];	// L660
            int32_t v409 = v408;	// L661
            bool v410 = v409 < 8;	// L662
            int32_t v411 = dsmask;	// L663
            int32_t v412 = v411 >> v409;	// L664
            int32_t v413 = v412 & 1;	// L665
            bool v414 = v413 == 1;	// L666
            bool v415 = v410 & v414;	// L667
            if (v415) {	// L668
              uint8_t v416 = sb_dst[0];	// L669
              int v417 = v416;	// L670
              int32_t v418 = drf_full[v417];	// L671
              bool v419 = v418 == 0;	// L672
              if (v419) {	// L673
                half v420 = wb;	// L674
                uint8_t v421 = sb_dst[0];	// L675
                int v422 = v421;	// L676
                drf[v422] = v420;	// L677
                uint8_t v423 = sb_dst[0];	// L678
                int v424 = v423;	// L679
                drf_full[v424] = 1;	// L680
              }
            } else {
              half v425 = wb;	// L683
              uint8_t v426 = sb_dst[0];	// L684
              int32_t v427 = v426;	// L685
              int32_t v428 = v427 & 7;	// L686
              int v429 = v428;	// L687
              drf[v429] = v425;	// L688
            }
          }
        }
      }
    }
    int32_t pc;	// L694
    pc = -1;	// L695
    int8_t v431 = fetch_en;	// L696
    int32_t v432 = v431;	// L697
    bool v433 = v432 == 1;	// L698
    if (v433) {	// L699
      int8_t v434 = instr_cnt;	// L700
      int32_t v435 = v434;	// L701
      pc = v435;	// L702
    }
    int8_t v436 = fetch_en;	// L704
    int32_t v437 = v436;	// L705
    bool v438 = v437 == 1;	// L706
    if (v438) {	// L707
      fe_ever = 1;	// L708
    }
    int32_t instr;	// L710
    instr = 0;	// L711
    int32_t v440 = pc;	// L712
    bool v441 = v440 >= 0;	// L713
    if (v441) {	// L714
      int32_t v442 = pc;	// L715
      int v443 = v442;	// L716
      int32_t v444 = irf[v443];	// L717
      instr = v444;	// L718
    }
    int32_t v445 = instr;	// L720
    int32_t v446 = v445 & 15;	// L721
    int32_t op;	// L722
    op = v446;	// L723
    int32_t v448 = instr;	// L724
    int32_t v449 = v448 >> 4;	// L725
    int32_t v450 = v449 & 15;	// L726
    int32_t dst;	// L727
    dst = v450;	// L728
    int32_t v452 = instr;	// L729
    int32_t v453 = v452 >> 8;	// L730
    int32_t v454 = v453 & 15;	// L731
    int32_t s1;	// L732
    s1 = v454;	// L733
    int32_t v456 = instr;	// L734
    int32_t v457 = v456 >> 12;	// L735
    int32_t v458 = v457 & 15;	// L736
    int32_t s2;	// L737
    s2 = v458;	// L738
    half a;	// L739
    a = 0.000000;	// L740
    half b;	// L741
    b = 0.000000;	// L742
    int32_t v462 = s1;	// L743
    bool v463 = v462 >= 12;	// L744
    if (v463) {	// L745
      int32_t v464 = s1;	// L746
      int32_t v465 = v464 & 3;	// L747
      int v466 = v465;	// L748
      half v467 = hold_v[v466][0];	// L749
      a = v467;	// L750
    } else {
      int32_t v468 = s1;	// L752
      int v469 = v468;	// L753
      half v470 = drf[v469];	// L754
      a = v470;	// L755
    }
    int32_t v471 = s2;	// L757
    bool v472 = v471 >= 12;	// L758
    if (v472) {	// L759
      int32_t v473 = s2;	// L760
      int32_t v474 = v473 & 3;	// L761
      int v475 = v474;	// L762
      half v476 = hold_v[v475][0];	// L763
      b = v476;	// L764
    } else {
      int32_t v477 = s2;	// L766
      int v478 = v477;	// L767
      half v479 = drf[v478];	// L768
      b = v479;	// L769
    }
    int32_t a_vld;	// L771
    a_vld = 1;	// L772
    int32_t b_vld;	// L773
    b_vld = 1;	// L774
    int32_t v482 = s1;	// L775
    bool v483 = v482 >= 12;	// L776
    if (v483) {	// L777
      a_vld = 0;	// L778
      int32_t v484 = s1;	// L779
      int32_t v485 = v484 & 3;	// L780
      int v486 = v485;	// L781
      uint8_t v487 = hold_cnt[v486];	// L782
      int32_t v488 = v487;	// L783
      bool v489 = v488 > 0;	// L784
      if (v489) {	// L785
        a_vld = 1;	// L786
      }
    }
    int32_t v490 = s2;	// L789
    bool v491 = v490 >= 12;	// L790
    if (v491) {	// L791
      b_vld = 0;	// L792
      int32_t v492 = s2;	// L793
      int32_t v493 = v492 & 3;	// L794
      int v494 = v493;	// L795
      uint8_t v495 = hold_cnt[v494];	// L796
      int32_t v496 = v495;	// L797
      bool v497 = v496 > 0;	// L798
      if (v497) {	// L799
        b_vld = 1;	// L800
      }
    }
    int32_t v498 = s1;	// L803
    bool v499 = v498 < 8;	// L804
    int32_t v500 = dsmask;	// L805
    int32_t v501 = v500 >> v498;	// L806
    int32_t v502 = v501 & 1;	// L807
    bool v503 = v502 == 1;	// L808
    bool v504 = v499 & v503;	// L809
    if (v504) {	// L810
      int32_t v505 = s1;	// L811
      int v506 = v505;	// L812
      int32_t v507 = drf_full[v506];	// L813
      bool v508 = v507 == 0;	// L814
      if (v508) {	// L815
        a_vld = 0;	// L816
      }
    }
    int32_t v509 = s2;	// L819
    bool v510 = v509 < 8;	// L820
    int32_t v511 = dsmask;	// L821
    int32_t v512 = v511 >> v509;	// L822
    int32_t v513 = v512 & 1;	// L823
    bool v514 = v513 == 1;	// L824
    bool v515 = v510 & v514;	// L825
    if (v515) {	// L826
      int32_t v516 = s2;	// L827
      int v517 = v516;	// L828
      int32_t v518 = drf_full[v517];	// L829
      bool v519 = v518 == 0;	// L830
      if (v519) {	// L831
        b_vld = 0;	// L832
      }
    }
    int32_t binop;	// L835
    binop = 0;	// L836
    int32_t v521 = op;	// L837
    bool v522 = v521 == 0;	// L838
    bool v523 = v521 == 1;	// L839
    bool v524 = v521 == 2;	// L840
    bool v525 = v521 == 8;	// L841
    bool v526 = v521 == 9;	// L842
    bool v527 = v522 | v523;	// L843
    bool v528 = v527 | v524;	// L844
    bool v529 = v528 | v525;	// L845
    bool v530 = v529 | v526;	// L846
    if (v530) {	// L847
      binop = 1;	// L848
    }
    int32_t raw;	// L850
    raw = 0;	// L851
    int32_t cmp_busy;	// L852
    cmp_busy = 0;	// L853
    l_S_k_5_k: for (int k = 0; k < 4; k++) {	// L854
      uint8_t v534 = sb_v[(k + 1)];	// L855
      int32_t v535 = v534;	// L856
      bool v536 = v535 == 1;	// L857
      uint8_t v537 = sb_rtr[(k + 1)];	// L858
      int32_t v538 = v537;	// L859
      bool v539 = v538 == 0;	// L860
      uint8_t v540 = sb_dst[(k + 1)];	// L861
      int32_t v541 = v540;	// L862
      bool v542 = v541 < 12;	// L863
      bool v543 = v536 & v539;	// L864
      bool v544 = v543 & v542;	// L865
      if (v544) {	// L866
        int32_t v545 = s1;	// L867
        bool v546 = v545 < 12;	// L868
        uint8_t v547 = sb_dst[(k + 1)];	// L869
        int32_t v548 = v547;	// L870
        int32_t v549 = v548 & 7;	// L871
        int32_t v550 = v545 & 7;	// L872
        bool v551 = v549 == v550;	// L873
        bool v552 = v546 & v551;	// L874
        if (v552) {	// L875
          raw = 1;	// L876
        }
        int32_t v553 = binop;	// L878
        bool v554 = v553 == 1;	// L879
        int32_t v555 = s2;	// L880
        bool v556 = v555 < 12;	// L881
        uint8_t v557 = sb_dst[(k + 1)];	// L882
        int32_t v558 = v557;	// L883
        int32_t v559 = v558 & 7;	// L884
        int32_t v560 = v555 & 7;	// L885
        bool v561 = v559 == v560;	// L886
        bool v562 = v554 & v556;	// L887
        bool v563 = v562 & v561;	// L888
        if (v563) {	// L889
          raw = 1;	// L890
        }
      }
      uint8_t v564 = sb_v[(k + 1)];	// L893
      int32_t v565 = v564;	// L894
      bool v566 = v565 == 1;	// L895
      uint8_t v567 = sb_cmp[(k + 1)];	// L896
      int32_t v568 = v567;	// L897
      bool v569 = v568 == 1;	// L898
      bool v570 = v566 & v569;	// L899
      if (v570) {	// L900
        cmp_busy = 1;	// L901
      }
    }
    int32_t is_cond;	// L904
    is_cond = 0;	// L905
    int32_t v572 = op;	// L906
    bool v573 = v572 >= 12;	// L907
    ap_int<33> v574 = v572;	// L908
    bool v575 = v574 <= 15;	// L909
    bool v576 = v573 & v575;	// L910
    if (v576) {	// L911
      is_cond = 1;	// L912
    }
    int32_t grant;	// L914
    grant = 0;	// L915
    int32_t v578 = pc;	// L916
    bool v579 = v578 >= 0;	// L917
    if (v579) {	// L918
      grant = 1;	// L919
    }
    int32_t v580 = pc;	// L921
    bool v581 = v580 >= 0;	// L922
    int32_t v582 = a_vld;	// L923
    bool v583 = v582 == 0;	// L924
    int32_t v584 = binop;	// L925
    bool v585 = v584 == 1;	// L926
    int32_t v586 = b_vld;	// L927
    bool v587 = v586 == 0;	// L928
    bool v588 = v585 & v587;	// L929
    bool v589 = v583 | v588;	// L930
    bool v590 = v581 & v589;	// L931
    if (v590) {	// L932
      grant = 0;	// L933
    }
    int32_t v591 = pc;	// L935
    bool v592 = v591 >= 0;	// L936
    int32_t v593 = raw;	// L937
    bool v594 = v593 == 1;	// L938
    int32_t v595 = is_cond;	// L939
    bool v596 = v595 == 1;	// L940
    int32_t v597 = cmp_busy;	// L941
    bool v598 = v597 == 1;	// L942
    bool v599 = v596 & v598;	// L943
    bool v600 = v594 | v599;	// L944
    bool v601 = v592 & v600;	// L945
    if (v601) {	// L946
      grant = 0;	// L947
    }
    int32_t v602 = grant;	// L949
    bool v603 = v602 == 1;	// L950
    if (v603) {	// L951
      int8_t v604 = instr_cnt;	// L952
      int32_t v605 = cfg_isz;	// L953
      int32_t v606 = v604;	// L954
      bool v607 = v606 == v605;	// L955
      if (v607) {	// L956
        instr_cnt = 0;	// L957
        int8_t v608 = iter_cnt;	// L958
        int32_t v609 = cfg_itsz;	// L959
        ap_int<33> v610 = v609;	// L960
        ap_int<33> v611 = v610 - 1;	// L961
        ap_int<33> v612 = v608;	// L962
        bool v613 = v612 == v611;	// L963
        if (v613) {	// L964
          fetch_en = 0;	// L965
        } else {
          int8_t v614 = iter_cnt;	// L967
          ap_int<33> v615 = v614;	// L968
          ap_int<33> v616 = v615 + 1;	// L969
          uint8_t v617 = v616;	// L970
          iter_cnt = v617;	// L971
        }
      } else {
        int8_t v618 = instr_cnt;	// L974
        ap_int<33> v619 = v618;	// L975
        ap_int<33> v620 = v619 + 1;	// L976
        uint8_t v621 = v620;	// L977
        instr_cnt = v621;	// L978
      }
    }
    int32_t c1;	// L981
    c1 = -1;	// L982
    int32_t c2;	// L983
    c2 = -1;	// L984
    int32_t v624 = grant;	// L985
    bool v625 = v624 == 1;	// L986
    int32_t v626 = s1;	// L987
    bool v627 = v626 >= 12;	// L988
    bool v628 = v625 & v627;	// L989
    if (v628) {	// L990
      int32_t v629 = s1;	// L991
      int32_t v630 = v629 & 3;	// L992
      c1 = v630;	// L993
    }
    int32_t v631 = grant;	// L995
    bool v632 = v631 == 1;	// L996
    int32_t v633 = s2;	// L997
    bool v634 = v633 >= 12;	// L998
    bool v635 = v632 & v634;	// L999
    if (v635) {	// L1000
      int32_t v636 = s2;	// L1001
      int32_t v637 = v636 & 3;	// L1002
      c2 = v637;	// L1003
    }
    int32_t v638 = c1;	// L1005
    bool v639 = v638 >= 0;	// L1006
    if (v639) {	// L1007
      int32_t v640 = c1;	// L1008
      int v641 = v640;	// L1009
      half v642 = hold_v[v641][1];	// L1010
      hold_v[v641][0] = v642;	// L1011
      int32_t v643 = c1;	// L1012
      int v644 = v643;	// L1013
      uint8_t v645 = hold_cnt[v644];	// L1014
      ap_int<33> v646 = v645;	// L1015
      ap_int<33> v647 = v646 - 1;	// L1016
      uint8_t v648 = v647;	// L1017
      hold_cnt[v644] = v648;	// L1018
    }
    int32_t v649 = c2;	// L1020
    bool v650 = v649 >= 0;	// L1021
    int32_t v651 = c1;	// L1022
    bool v652 = v649 != v651;	// L1023
    bool v653 = v650 & v652;	// L1024
    if (v653) {	// L1025
      int32_t v654 = c2;	// L1026
      int v655 = v654;	// L1027
      half v656 = hold_v[v655][1];	// L1028
      hold_v[v655][0] = v656;	// L1029
      int32_t v657 = c2;	// L1030
      int v658 = v657;	// L1031
      uint8_t v659 = hold_cnt[v658];	// L1032
      ap_int<33> v660 = v659;	// L1033
      ap_int<33> v661 = v660 - 1;	// L1034
      uint8_t v662 = v661;	// L1035
      hold_cnt[v658] = v662;	// L1036
    }
    int32_t v663 = grant;	// L1038
    bool v664 = v663 == 1;	// L1039
    int32_t v665 = s1;	// L1040
    bool v666 = v665 < 8;	// L1041
    int32_t v667 = dsmask;	// L1042
    int32_t v668 = v667 >> v665;	// L1043
    int32_t v669 = v668 & 1;	// L1044
    bool v670 = v669 == 1;	// L1045
    bool v671 = v664 & v666;	// L1046
    bool v672 = v671 & v670;	// L1047
    if (v672) {	// L1048
      int32_t v673 = s1;	// L1049
      int v674 = v673;	// L1050
      drf_full[v674] = 0;	// L1051
    }
    int32_t v675 = grant;	// L1053
    bool v676 = v675 == 1;	// L1054
    int32_t v677 = s2;	// L1055
    bool v678 = v677 < 8;	// L1056
    int32_t v679 = dsmask;	// L1057
    int32_t v680 = v679 >> v677;	// L1058
    int32_t v681 = v680 & 1;	// L1059
    bool v682 = v681 == 1;	// L1060
    bool v683 = v676 & v678;	// L1061
    bool v684 = v683 & v682;	// L1062
    if (v684) {	// L1063
      int32_t v685 = s2;	// L1064
      int v686 = v685;	// L1065
      drf_full[v686] = 0;	// L1066
    }
    half res;
#pragma HLS dependence variable=res type=inter dependent=false	// L1068
    res = 0.000000;	// L1069
    int32_t v688 = op;	// L1070
    bool v689 = v688 == 0;	// L1071
    if (v689) {	// L1072
      half v690 = a;	// L1073
      half v691 = b;	// L1074
      half v692 = v690 + v691;	// L1075
      res = v692;	// L1076
    } else {
      int32_t v693 = op;	// L1078
      bool v694 = v693 == 1;	// L1079
      if (v694) {	// L1080
        half v695 = a;	// L1081
        half v696 = b;	// L1082
        half v697 = v695 - v696;	// L1083
        res = v697;	// L1084
      } else {
        int32_t v698 = op;	// L1086
        bool v699 = v698 == 2;	// L1087
        if (v699) {	// L1088
          half v700 = a;	// L1089
          half v701 = b;	// L1090
          half v702 = v700 * v701;	// L1091
          res = v702;	// L1092
        } else {
          int32_t v703 = op;	// L1094
          bool v704 = v703 == 8;	// L1095
          if (v704) {	// L1096
            half v705 = a;	// L1097
            half v706 = b;	// L1098
            bool v707 = v705 >= v706;	// L1099
            if (v707) {	// L1100
              res = 1.000000;	// L1101
            } else {
              res = -1.000000;	// L1103
            }
          } else {
            int32_t v708 = op;	// L1106
            bool v709 = v708 == 9;	// L1107
            if (v709) {	// L1108
              half v710 = a;	// L1109
              half v711 = b;	// L1110
              bool v712 = v710 < v711;	// L1111
              if (v712) {	// L1112
                res = 1.000000;	// L1113
              } else {
                res = -1.000000;	// L1115
              }
            } else {
              half v713 = a;	// L1118
              res = v713;	// L1119
            }
          }
        }
      }
    }
    int32_t v714 = a_vld;	// L1125
    int32_t res_vld;	// L1126
    res_vld = v714;	// L1127
    int32_t v716 = op;	// L1128
    bool v717 = v716 == 0;	// L1129
    bool v718 = v716 == 1;	// L1130
    bool v719 = v716 == 2;	// L1131
    bool v720 = v716 == 8;	// L1132
    bool v721 = v716 == 9;	// L1133
    bool v722 = v717 | v718;	// L1134
    bool v723 = v722 | v719;	// L1135
    bool v724 = v723 | v720;	// L1136
    bool v725 = v724 | v721;	// L1137
    if (v725) {	// L1138
      int32_t v726 = a_vld;	// L1139
      int32_t v727 = b_vld;	// L1140
      int64_t v728 = v726;	// L1141
      int64_t v729 = v727;	// L1142
      int64_t v730 = v728 * v729;	// L1143
      int32_t v731 = v730;	// L1144
      res_vld = v731;	// L1145
    }
    int32_t v732 = grant;	// L1147
    bool v733 = v732 == 0;	// L1148
    if (v733) {	// L1149
      res_vld = 0;	// L1150
    }
    int32_t is_rtr;	// L1152
    is_rtr = 0;	// L1153
    int32_t v735 = op;	// L1154
    bool v736 = v735 >= 4;	// L1155
    ap_int<33> v737 = v735;	// L1156
    bool v738 = v737 <= 7;	// L1157
    bool v739 = v736 & v738;	// L1158
    if (v739) {	// L1159
      is_rtr = 1;	// L1160
    }
    l_S_k_6_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1162
      uint8_t v741 = sb_v[(k1 + 1)];	// L1163
      sb_v[k1] = v741;	// L1164
      uint8_t v742 = sb_dst[(k1 + 1)];	// L1165
      sb_dst[k1] = v742;	// L1166
      uint8_t v743 = sb_cmp[(k1 + 1)];	// L1167
      sb_cmp[k1] = v743;	// L1168
      uint8_t v744 = sb_rtr[(k1 + 1)];	// L1169
      sb_rtr[k1] = v744;	// L1170
      uint8_t v745 = sb_inj[(k1 + 1)];	// L1171
      sb_inj[k1] = v745;	// L1172
      uint8_t v746 = sb_dir[(k1 + 1)];	// L1173
      sb_dir[k1] = v746;	// L1174
      uint8_t v747 = sb_id[(k1 + 1)];	// L1175
      sb_id[k1] = v747;	// L1176
      uint8_t v748 = sb_rvld[(k1 + 1)];	// L1177
      sb_rvld[k1] = v748;	// L1178
      uint8_t v749 = sb_ix[(k1 + 1)];	// L1179
      sb_ix[k1] = v749;	// L1180
    }
    sb_v[4] = 0;	// L1182
    int32_t v750 = grant;	// L1183
    bool v751 = v750 == 1;	// L1184
    if (v751) {	// L1185
      half v752 = res;	// L1186
      int8_t v753 = resq_wr;	// L1187
      int v754 = v753;	// L1188
      resq[v754] = v752;	// L1189
      int32_t cq;	// L1190
      cq = 0;	// L1191
      int32_t v756 = op;	// L1192
      bool v757 = v756 == 8;	// L1193
      if (v757) {	// L1194
        half v758 = a;	// L1195
        half v759 = b;	// L1196
        bool v760 = v758 >= v759;	// L1197
        if (v760) {	// L1198
          cq = 1;	// L1199
        }
      }
      int32_t v761 = op;	// L1202
      bool v762 = v761 == 9;	// L1203
      if (v762) {	// L1204
        half v763 = a;	// L1205
        half v764 = b;	// L1206
        bool v765 = v763 < v764;	// L1207
        if (v765) {	// L1208
          cq = 1;	// L1209
        }
      }
      int32_t v766 = cq;	// L1212
      uint8_t v767 = v766;	// L1213
      int8_t v768 = resq_wr;	// L1214
      int v769 = v768;	// L1215
      cmpq[v769] = v767;	// L1216
      sb_v[4] = 1;	// L1217
      int32_t v770 = dst;	// L1218
      uint8_t v771 = v770;	// L1219
      sb_dst[4] = v771;	// L1220
      int8_t v772 = resq_wr;	// L1221
      sb_ix[4] = v772;	// L1222
      sb_cmp[4] = 0;	// L1223
      int32_t v773 = op;	// L1224
      bool v774 = v773 == 8;	// L1225
      bool v775 = v773 == 9;	// L1226
      bool v776 = v774 | v775;	// L1227
      if (v776) {	// L1228
        sb_cmp[4] = 1;	// L1229
      }
      int32_t v777 = is_rtr;	// L1231
      int32_t rtrf;	// L1232
      rtrf = v777;	// L1233
      int32_t v779 = is_cond;	// L1234
      bool v780 = v779 == 1;	// L1235
      if (v780) {	// L1236
        rtrf = 1;	// L1237
      }
      int32_t v781 = rtrf;	// L1239
      uint8_t v782 = v781;	// L1240
      sb_rtr[4] = v782;	// L1241
      int32_t v783 = is_rtr;	// L1242
      int32_t inj;	// L1243
      inj = v783;	// L1244
      int32_t v785 = is_cond;	// L1245
      bool v786 = v785 == 1;	// L1246
      int8_t v787 = condition_reg;	// L1247
      int32_t v788 = v787;	// L1248
      bool v789 = v788 == 1;	// L1249
      bool v790 = v786 & v789;	// L1250
      if (v790) {	// L1251
        inj = 1;	// L1252
      }
      int32_t v791 = inj;	// L1254
      uint8_t v792 = v791;	// L1255
      sb_inj[4] = v792;	// L1256
      int32_t v793 = op;	// L1257
      int32_t v794 = v793 & 3;	// L1258
      uint8_t v795 = v794;	// L1259
      sb_dir[4] = v795;	// L1260
      int32_t v796 = s2;	// L1261
      uint8_t v797 = v796;	// L1262
      sb_id[4] = v797;	// L1263
      int32_t v798 = res_vld;	// L1264
      uint8_t v799 = v798;	// L1265
      sb_rvld[4] = v799;	// L1266
      int8_t v800 = resq_wr;	// L1267
      ap_int<33> v801 = v800;	// L1268
      ap_int<33> v802 = v801 + 1;	// L1269
      ap_int<33> v803 = v802 & 7;	// L1270
      uint8_t v804 = v803;	// L1271
      resq_wr = v804;	// L1272
    }
    ap_int<17> v805 = tx_n;	// L1274
    txn_r = v805;	// L1275
    ap_int<17> v806 = tx_s;	// L1276
    txs_r = v806;	// L1277
    ap_int<17> v807 = tx_w;	// L1278
    txw_r = v807;	// L1279
    ap_int<17> v808 = tx_e;	// L1280
    txe_r = v808;	// L1281
    int32_t v809 = crv_vld;	// L1282
    bool v810 = v809 == 1;	// L1283
    if (v810) {	// L1284
      int32_t v811 = crv_mode;	// L1285
      bool v812 = v811 == 1;	// L1286
      if (v812) {	// L1287
        int32_t v813 = crv_addr;	// L1288
        int32_t v814 = v813 >> 3;	// L1289
        int32_t v815 = v814 & 1;	// L1290
        bool v816 = v815 == 1;	// L1291
        if (v816) {	// L1292
          int32_t v817 = crv_raw;	// L1293
          int32_t v818 = crv_addr;	// L1294
          int32_t v819 = v818 & 7;	// L1295
          int v820 = v819;	// L1296
          irf[v820] = v817;	// L1297
        } else {
          int32_t v821 = crv_addr;	// L1299
          bool v822 = v821 == 0;	// L1300
          if (v822) {	// L1301
            int32_t v823 = crv_raw;	// L1302
            int32_t v824 = v823 & 255;	// L1303
            dsmask = v824;	// L1304
            int32_t v825 = crv_raw;	// L1305
            int32_t v826 = v825 >> 8;	// L1306
            int32_t v827 = v826 & 7;	// L1307
            cfg_isz = v827;	// L1308
            int32_t v828 = crv_raw;	// L1309
            int32_t v829 = v828 >> 15;	// L1310
            int32_t v830 = v829 & 1;	// L1311
            bool v831 = v830 == 1;	// L1312
            if (v831) {	// L1313
              fetch_en = 1;	// L1314
              instr_cnt = 0;	// L1315
              iter_cnt = 0;	// L1316
            }
          } else {
            int32_t v832 = crv_addr;	// L1319
            bool v833 = v832 == 1;	// L1320
            if (v833) {	// L1321
              int32_t v834 = crv_raw;	// L1322
              int32_t v835 = v834 & 255;	// L1323
              cfg_itsz = v835;	// L1324
            }
          }
        }
      } else {
        int32_t v836 = crv_addr;	// L1329
        bool v837 = v836 < 8;	// L1330
        int32_t v838 = dsmask;	// L1331
        int32_t v839 = v838 >> v836;	// L1332
        int32_t v840 = v839 & 1;	// L1333
        bool v841 = v840 == 1;	// L1334
        bool v842 = v837 & v841;	// L1335
        if (v842) {	// L1336
          int32_t v843 = crv_addr;	// L1337
          int v844 = v843;	// L1338
          int32_t v845 = drf_full[v844];	// L1339
          bool v846 = v845 == 0;	// L1340
          if (v846) {	// L1341
            half v847 = crv_data;	// L1342
            int32_t v848 = crv_addr;	// L1343
            int v849 = v848;	// L1344
            drf[v849] = v847;	// L1345
            int32_t v850 = crv_addr;	// L1346
            int v851 = v850;	// L1347
            drf_full[v851] = 1;	// L1348
          }
        } else {
          half v852 = crv_data;	// L1351
          int32_t v853 = crv_addr;	// L1352
          int v854 = v853;	// L1353
          drf[v854] = v852;	// L1354
        }
      }
    }
    ap_int<17> v855 = txe_r;	// L1358
    bool v856;
    ap_int<17> v856_tmp = v855;
    v856 = v856_tmp[0];	// L1359
    int32_t v857 = v856;	// L1360
    bool v858 = v857 == 1;	// L1361
    if (v858) {	// L1362
      ap_int<17> v859 = txe_r;	// L1363
      v12.write(v859);	// L1364
    }
    ap_int<17> v860 = txw_r;	// L1366
    bool v861;
    ap_int<17> v861_tmp = v860;
    v861 = v861_tmp[0];	// L1367
    int32_t v862 = v861;	// L1368
    bool v863 = v862 == 1;	// L1369
    if (v863) {	// L1370
      ap_int<17> v864 = txw_r;	// L1371
      v13.write(v864);	// L1372
    }
    ap_int<17> v865 = txs_r;	// L1374
    bool v866;
    ap_int<17> v866_tmp = v865;
    v866 = v866_tmp[0];	// L1375
    int32_t v867 = v866;	// L1376
    bool v868 = v867 == 1;	// L1377
    if (v868) {	// L1378
      ap_int<17> v869 = txs_r;	// L1379
      v14.write(v869);	// L1380
    }
    ap_int<17> v870 = txn_r;	// L1382
    bool v871;
    ap_int<17> v871_tmp = v870;
    v871 = v871_tmp[0];	// L1383
    int32_t v872 = v871;	// L1384
    bool v873 = v872 == 1;	// L1385
    if (v873) {	// L1386
      ap_int<17> v874 = txn_r;	// L1387
      v15.write(v874);	// L1388
    }
  }
}

void node_0_1(
  hls::stream< ap_uint<26> >& v875,
  hls::stream< ap_uint<26> >& v876,
  hls::stream< ap_uint<26> >& v877,
  hls::stream< ap_uint<26> >& v878,
  hls::stream< ap_uint<26> >& v879,
  hls::stream< ap_uint<26> >& v880,
  hls::stream< ap_uint<26> >& v881,
  hls::stream< ap_uint<26> >& v882,
  hls::stream< ap_uint<17> >& v883,
  hls::stream< ap_uint<17> >& v884,
  hls::stream< ap_uint<17> >& v885,
  hls::stream< ap_uint<17> >& v886,
  hls::stream< ap_uint<17> >& v887,
  hls::stream< ap_uint<17> >& v888,
  hls::stream< ap_uint<17> >& v889,
  hls::stream< ap_uint<17> >& v890
) {	// L1393
  int32_t irf1[8];	// L1426
  #pragma HLS array_partition variable=irf1 complete dim=1

  for (int v892 = 0; v892 < 8; v892++) {	// L1427
    irf1[v892] = 0;	// L1427
  }
  half drf1[8];	// L1428
  #pragma HLS array_partition variable=drf1 complete dim=1

  for (int v894 = 0; v894 < 8; v894++) {	// L1429
    drf1[v894] = 0.000000;	// L1429
  }
  int32_t drf_full1[8];	// L1430
  #pragma HLS array_partition variable=drf_full1 complete dim=1

  for (int v896 = 0; v896 < 8; v896++) {	// L1431
    drf_full1[v896] = 0;	// L1431
  }
  int32_t dsmask1;	// L1432
  dsmask1 = 0;	// L1433
  int32_t crv_vld1;	// L1434
  crv_vld1 = 0;	// L1435
  half crv_data1;	// L1436
  crv_data1 = 0.000000;	// L1437
  int32_t crv_addr1;	// L1438
  crv_addr1 = 0;	// L1439
  int32_t crv_mode1;	// L1440
  crv_mode1 = 0;	// L1441
  int32_t crv_raw1;	// L1442
  crv_raw1 = 0;	// L1443
  int32_t csd_vld1;	// L1444
  csd_vld1 = 0;	// L1445
  ap_uint<26> csd_pkt1;	// L1446
  csd_pkt1 = 0;	// L1447
  int32_t csd_dir1;	// L1448
  csd_dir1 = 0;	// L1449
  int32_t row_id1;	// L1450
  row_id1 = 0;	// L1451
  int32_t col_id1;	// L1452
  col_id1 = 1;	// L1453
  ap_uint<17> txn_r1;	// L1454
  txn_r1 = 0;	// L1455
  ap_uint<17> txs_r1;	// L1456
  txs_r1 = 0;	// L1457
  ap_uint<17> txw_r1;	// L1458
  txw_r1 = 0;	// L1459
  ap_uint<17> txe_r1;	// L1460
  txe_r1 = 0;	// L1461
  half hold_v1[4][2];	// L1462
  #pragma HLS array_partition variable=hold_v1 complete dim=1
  #pragma HLS array_partition variable=hold_v1 complete dim=2

  for (int v913 = 0; v913 < 4; v913++) {	// L1463
    for (int v914 = 0; v914 < 2; v914++) {	// L1463
      hold_v1[v913][v914] = 0.000000;	// L1463
    }
  }
  uint8_t hold_cnt1[4];	// L1464
  #pragma HLS array_partition variable=hold_cnt1 complete dim=1

  for (int v916 = 0; v916 < 4; v916++) {	// L1465
    hold_cnt1[v916] = 0;	// L1465
  }
  int32_t crv_ever1;	// L1466
  crv_ever1 = 0;	// L1467
  int32_t fe_ever1;	// L1468
  fe_ever1 = 0;	// L1469
  ap_uint<26> rbuf1[4][2];	// L1470
  #pragma HLS array_partition variable=rbuf1 complete dim=1
  #pragma HLS array_partition variable=rbuf1 complete dim=2

  for (int v920 = 0; v920 < 4; v920++) {	// L1471
    for (int v921 = 0; v921 < 2; v921++) {	// L1471
      rbuf1[v920][v921] = 0;	// L1471
    }
  }
  uint8_t rbcnt1[4];	// L1472
  #pragma HLS array_partition variable=rbcnt1 complete dim=1

  for (int v923 = 0; v923 < 4; v923++) {	// L1473
    rbcnt1[v923] = 0;	// L1473
  }
  int32_t cfg_isz1;	// L1474
  cfg_isz1 = 0;	// L1475
  int32_t cfg_itsz1;	// L1476
  cfg_itsz1 = 0;	// L1477
  uint8_t fetch_en1;	// L1478
  fetch_en1 = 0;	// L1479
  uint8_t instr_cnt1;	// L1480
  instr_cnt1 = 0;	// L1481
  uint8_t iter_cnt1;	// L1482
  iter_cnt1 = 0;	// L1483
  uint8_t condition_reg1;	// L1484
  condition_reg1 = 0;	// L1485
  uint8_t sb_v1[5];	// L1486
  #pragma HLS array_partition variable=sb_v1 complete dim=1

  for (int v931 = 0; v931 < 5; v931++) {	// L1487
    sb_v1[v931] = 0;	// L1487
  }
  uint8_t sb_dst1[5];	// L1488
  #pragma HLS array_partition variable=sb_dst1 complete dim=1

  for (int v933 = 0; v933 < 5; v933++) {	// L1489
    sb_dst1[v933] = 0;	// L1489
  }
  uint8_t sb_cmp1[5];	// L1490
  #pragma HLS array_partition variable=sb_cmp1 complete dim=1

  for (int v935 = 0; v935 < 5; v935++) {	// L1491
    sb_cmp1[v935] = 0;	// L1491
  }
  uint8_t sb_rtr1[5];	// L1492
  #pragma HLS array_partition variable=sb_rtr1 complete dim=1

  for (int v937 = 0; v937 < 5; v937++) {	// L1493
    sb_rtr1[v937] = 0;	// L1493
  }
  uint8_t sb_inj1[5];	// L1494
  #pragma HLS array_partition variable=sb_inj1 complete dim=1

  for (int v939 = 0; v939 < 5; v939++) {	// L1495
    sb_inj1[v939] = 0;	// L1495
  }
  uint8_t sb_dir1[5];	// L1496
  #pragma HLS array_partition variable=sb_dir1 complete dim=1

  for (int v941 = 0; v941 < 5; v941++) {	// L1497
    sb_dir1[v941] = 0;	// L1497
  }
  uint8_t sb_id1[5];	// L1498
  #pragma HLS array_partition variable=sb_id1 complete dim=1

  for (int v943 = 0; v943 < 5; v943++) {	// L1499
    sb_id1[v943] = 0;	// L1499
  }
  uint8_t sb_rvld1[5];	// L1500
  #pragma HLS array_partition variable=sb_rvld1 complete dim=1

  for (int v945 = 0; v945 < 5; v945++) {	// L1501
    sb_rvld1[v945] = 0;	// L1501
  }
  uint8_t sb_ix1[5];	// L1502
  #pragma HLS array_partition variable=sb_ix1 complete dim=1

  for (int v947 = 0; v947 < 5; v947++) {	// L1503
    sb_ix1[v947] = 0;	// L1503
  }
  half resq1[8];	// L1504
  #pragma HLS array_partition variable=resq1 complete dim=1
#pragma HLS dependence variable=resq1 type=inter dependent=false

  for (int v949 = 0; v949 < 8; v949++) {	// L1505
    resq1[v949] = 0.000000;	// L1505
  }
  uint8_t cmpq1[8];	// L1506
  #pragma HLS array_partition variable=cmpq1 complete dim=1
#pragma HLS dependence variable=cmpq1 type=inter dependent=false

  for (int v951 = 0; v951 < 8; v951++) {	// L1507
    cmpq1[v951] = 0;	// L1507
  }
  uint8_t resq_wr1;	// L1508
  resq_wr1 = 0;	// L1509
  l_S_t_0_t1: for (int t1 = 0; t1 < 374; t1++) {	// L1510
  #pragma HLS pipeline II=1
    ap_uint<26> p_w1;	// L1511
    p_w1 = 0;	// L1512
    ap_uint<26> p_e1;	// L1513
    p_e1 = 0;	// L1514
    ap_uint<26> p_n1;	// L1515
    p_n1 = 0;	// L1516
    ap_uint<26> p_s1;	// L1517
    p_s1 = 0;	// L1518
    uint8_t v958 = rbcnt1[0];	// L1519
    int32_t v959 = v958;	// L1520
    bool v960 = v959 < 2;	// L1521
    if (v960) {	// L1522
      ap_uint<26> v961;
      bool v962 = v875.read_nb(v961);
	// L1523
      ap_uint<26> gw1;	// L1524
      gw1 = v961;	// L1525
      bool okw1;	// L1526
      okw1 = v962;	// L1527
      bool v965 = okw1;	// L1528
      if (v965) {	// L1529
        ap_int<26> v966 = gw1;	// L1530
        p_w1 = v966;	// L1531
      }
    }
    uint8_t v967 = rbcnt1[1];	// L1534
    int32_t v968 = v967;	// L1535
    bool v969 = v968 < 2;	// L1536
    if (v969) {	// L1537
      ap_uint<26> v970;
      bool v971 = v876.read_nb(v970);
	// L1538
      ap_uint<26> ge1;	// L1539
      ge1 = v970;	// L1540
      bool oke1;	// L1541
      oke1 = v971;	// L1542
      bool v974 = oke1;	// L1543
      if (v974) {	// L1544
        ap_int<26> v975 = ge1;	// L1545
        p_e1 = v975;	// L1546
      }
    }
    uint8_t v976 = rbcnt1[2];	// L1549
    int32_t v977 = v976;	// L1550
    bool v978 = v977 < 2;	// L1551
    if (v978) {	// L1552
      ap_uint<26> v979;
      bool v980 = v877.read_nb(v979);
	// L1553
      ap_uint<26> gn1;	// L1554
      gn1 = v979;	// L1555
      bool okn1;	// L1556
      okn1 = v980;	// L1557
      bool v983 = okn1;	// L1558
      if (v983) {	// L1559
        ap_int<26> v984 = gn1;	// L1560
        p_n1 = v984;	// L1561
      }
    }
    uint8_t v985 = rbcnt1[3];	// L1564
    int32_t v986 = v985;	// L1565
    bool v987 = v986 < 2;	// L1566
    if (v987) {	// L1567
      ap_uint<26> v988;
      bool v989 = v878.read_nb(v988);
	// L1568
      ap_uint<26> gs1;	// L1569
      gs1 = v988;	// L1570
      bool oks1;	// L1571
      oks1 = v989;	// L1572
      bool v992 = oks1;	// L1573
      if (v992) {	// L1574
        ap_int<26> v993 = gs1;	// L1575
        p_s1 = v993;	// L1576
      }
    }
    ap_uint<26> fin1[4];	// L1579
    for (int v995 = 0; v995 < 4; v995++) {	// L1580
      fin1[v995] = 0;	// L1580
    }
    ap_int<26> v996 = p_w1;	// L1581
    fin1[0] = v996;	// L1582
    ap_int<26> v997 = p_e1;	// L1583
    fin1[1] = v997;	// L1584
    ap_int<26> v998 = p_n1;	// L1585
    fin1[2] = v998;	// L1586
    ap_int<26> v999 = p_s1;	// L1587
    fin1[3] = v999;	// L1588
    l_S_d_0_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1589
      ap_uint<26> v1001 = fin1[d4];	// L1590
      bool v1002;
      ap_int<26> v1002_tmp = v1001;
      v1002 = v1002_tmp[25];	// L1591
      int32_t v1003 = v1002;	// L1592
      bool v1004 = v1003 == 1;	// L1593
      uint8_t v1005 = rbcnt1[d4];	// L1594
      int32_t v1006 = v1005;	// L1595
      bool v1007 = v1006 < 2;	// L1596
      bool v1008 = v1004 & v1007;	// L1597
      if (v1008) {	// L1598
        ap_uint<26> v1009 = fin1[d4];	// L1599
        uint8_t v1010 = rbcnt1[d4];	// L1600
        int v1011 = v1010;	// L1601
        rbuf1[d4][v1011] = v1009;	// L1602
        uint8_t v1012 = rbcnt1[d4];	// L1603
        ap_int<33> v1013 = v1012;	// L1604
        ap_int<33> v1014 = v1013 + 1;	// L1605
        uint8_t v1015 = v1014;	// L1606
        rbcnt1[d4] = v1015;	// L1607
      }
    }
    ap_uint<26> hd1[4];	// L1610
    for (int v1017 = 0; v1017 < 4; v1017++) {	// L1611
      hd1[v1017] = 0;	// L1611
    }
    int32_t hvld1[4];	// L1612
    for (int v1019 = 0; v1019 < 4; v1019++) {	// L1613
      hvld1[v1019] = 0;	// L1613
    }
    int32_t hit1[4];	// L1614
    for (int v1021 = 0; v1021 < 4; v1021++) {	// L1615
      hit1[v1021] = 0;	// L1615
    }
    int32_t axis1[4];	// L1616
    for (int v1023 = 0; v1023 < 4; v1023++) {	// L1617
      axis1[v1023] = 0;	// L1617
    }
    int32_t v1024 = col_id1;	// L1618
    axis1[0] = v1024;	// L1619
    int32_t v1025 = col_id1;	// L1620
    axis1[1] = v1025;	// L1621
    int32_t v1026 = row_id1;	// L1622
    axis1[2] = v1026;	// L1623
    int32_t v1027 = row_id1;	// L1624
    axis1[3] = v1027;	// L1625
    l_S_d_1_d5: for (int d5 = 0; d5 < 4; d5++) {	// L1626
      uint8_t v1029 = rbcnt1[d5];	// L1627
      int32_t v1030 = v1029;	// L1628
      bool v1031 = v1030 > 0;	// L1629
      if (v1031) {	// L1630
        ap_uint<26> v1032 = rbuf1[d5][0];	// L1631
        hd1[d5] = v1032;	// L1632
        hvld1[d5] = 1;	// L1633
        ap_uint<26> v1033 = hd1[d5];	// L1634
        ap_int<4> v1034;
        ap_int<26> v1034_tmp = v1033;
        v1034 = v1034_tmp(24, 21);	// L1635
        int32_t v1035 = axis1[d5];	// L1636
        int32_t v1036 = v1034;	// L1637
        bool v1037 = v1036 == v1035;	// L1638
        if (v1037) {	// L1639
          hit1[d5] = 1;	// L1640
        }
      }
    }
    ap_uint<26> o_crv1;	// L1644
    o_crv1 = 0;	// L1645
    int32_t crv_in1;	// L1646
    crv_in1 = -1;	// L1647
    int32_t v1040 = hit1[3];	// L1648
    bool v1041 = v1040 == 1;	// L1649
    if (v1041) {	// L1650
      ap_uint<26> v1042 = hd1[3];	// L1651
      o_crv1 = v1042;	// L1652
      crv_in1 = 3;	// L1653
    } else {
      int32_t v1043 = hit1[2];	// L1655
      bool v1044 = v1043 == 1;	// L1656
      if (v1044) {	// L1657
        ap_uint<26> v1045 = hd1[2];	// L1658
        o_crv1 = v1045;	// L1659
        crv_in1 = 2;	// L1660
      } else {
        int32_t v1046 = hit1[1];	// L1662
        bool v1047 = v1046 == 1;	// L1663
        if (v1047) {	// L1664
          ap_uint<26> v1048 = hd1[1];	// L1665
          o_crv1 = v1048;	// L1666
          crv_in1 = 1;	// L1667
        } else {
          int32_t v1049 = hit1[0];	// L1669
          bool v1050 = v1049 == 1;	// L1670
          if (v1050) {	// L1671
            ap_uint<26> v1051 = hd1[0];	// L1672
            o_crv1 = v1051;	// L1673
            crv_in1 = 0;	// L1674
          }
        }
      }
    }
    int32_t pop1[4];	// L1679
    for (int v1053 = 0; v1053 < 4; v1053++) {	// L1680
      pop1[v1053] = 0;	// L1680
    }
    int32_t inj_done1;	// L1681
    inj_done1 = 0;	// L1682
    int32_t idir1;	// L1683
    idir1 = -1;	// L1684
    ap_int<26> v1056 = csd_pkt1;	// L1685
    bool v1057;
    ap_int<26> v1057_tmp = v1056;
    v1057 = v1057_tmp[25];	// L1686
    int32_t v1058 = v1057;	// L1687
    bool v1059 = v1058 == 1;	// L1688
    if (v1059) {	// L1689
      int32_t v1060 = csd_dir1;	// L1690
      ap_int<33> v1061 = v1060;	// L1691
      ap_int<33> v1062 = 3 - v1061;	// L1692
      int32_t v1063 = v1062;	// L1693
      idir1 = v1063;	// L1694
    }
    int32_t v1064 = idir1;	// L1696
    bool v1065 = v1064 == 0;	// L1697
    if (v1065) {	// L1698
      ap_int<26> v1066 = csd_pkt1;	// L1699
      bool v1067 = v879.write_nb(v1066);
	// L1700
      if (v1067) {	// L1701
        inj_done1 = 1;	// L1702
      }
    } else {
      int32_t v1068 = hvld1[0];	// L1705
      bool v1069 = v1068 == 1;	// L1706
      int32_t v1070 = hit1[0];	// L1707
      bool v1071 = v1070 == 0;	// L1708
      bool v1072 = v1069 & v1071;	// L1709
      if (v1072) {	// L1710
        ap_uint<26> v1073 = hd1[0];	// L1711
        bool v1074 = v879.write_nb(v1073);
	// L1712
        if (v1074) {	// L1713
          pop1[0] = 1;	// L1714
        }
      }
    }
    int32_t v1075 = idir1;	// L1718
    bool v1076 = v1075 == 1;	// L1719
    if (v1076) {	// L1720
      ap_int<26> v1077 = csd_pkt1;	// L1721
      bool v1078 = v880.write_nb(v1077);
	// L1722
      if (v1078) {	// L1723
        inj_done1 = 1;	// L1724
      }
    } else {
      int32_t v1079 = hvld1[1];	// L1727
      bool v1080 = v1079 == 1;	// L1728
      int32_t v1081 = hit1[1];	// L1729
      bool v1082 = v1081 == 0;	// L1730
      bool v1083 = v1080 & v1082;	// L1731
      if (v1083) {	// L1732
        ap_uint<26> v1084 = hd1[1];	// L1733
        bool v1085 = v880.write_nb(v1084);
	// L1734
        if (v1085) {	// L1735
          pop1[1] = 1;	// L1736
        }
      }
    }
    int32_t v1086 = idir1;	// L1740
    bool v1087 = v1086 == 2;	// L1741
    if (v1087) {	// L1742
      ap_int<26> v1088 = csd_pkt1;	// L1743
      bool v1089 = v881.write_nb(v1088);
	// L1744
      if (v1089) {	// L1745
        inj_done1 = 1;	// L1746
      }
    } else {
      int32_t v1090 = hvld1[2];	// L1749
      bool v1091 = v1090 == 1;	// L1750
      int32_t v1092 = hit1[2];	// L1751
      bool v1093 = v1092 == 0;	// L1752
      bool v1094 = v1091 & v1093;	// L1753
      if (v1094) {	// L1754
        ap_uint<26> v1095 = hd1[2];	// L1755
        bool v1096 = v881.write_nb(v1095);
	// L1756
        if (v1096) {	// L1757
          pop1[2] = 1;	// L1758
        }
      }
    }
    int32_t v1097 = idir1;	// L1762
    bool v1098 = v1097 == 3;	// L1763
    if (v1098) {	// L1764
      ap_int<26> v1099 = csd_pkt1;	// L1765
      bool v1100 = v882.write_nb(v1099);
	// L1766
      if (v1100) {	// L1767
        inj_done1 = 1;	// L1768
      }
    } else {
      int32_t v1101 = hvld1[3];	// L1771
      bool v1102 = v1101 == 1;	// L1772
      int32_t v1103 = hit1[3];	// L1773
      bool v1104 = v1103 == 0;	// L1774
      bool v1105 = v1102 & v1104;	// L1775
      if (v1105) {	// L1776
        ap_uint<26> v1106 = hd1[3];	// L1777
        bool v1107 = v882.write_nb(v1106);
	// L1778
        if (v1107) {	// L1779
          pop1[3] = 1;	// L1780
        }
      }
    }
    int32_t v1108 = crv_in1;	// L1784
    bool v1109 = v1108 >= 0;	// L1785
    if (v1109) {	// L1786
      int32_t v1110 = crv_in1;	// L1787
      int v1111 = v1110;	// L1788
      pop1[v1111] = 1;	// L1789
    }
    l_S_d_2_d6: for (int d6 = 0; d6 < 4; d6++) {	// L1791
      int32_t v1113 = pop1[d6];	// L1792
      bool v1114 = v1113 == 1;	// L1793
      if (v1114) {	// L1794
        l_S_sft_2_sft1: for (int sft1 = 0; sft1 < 1; sft1++) {	// L1795
          ap_uint<26> v1116 = rbuf1[d6][(sft1 + 1)];	// L1796
          rbuf1[d6][sft1] = v1116;	// L1797
        }
        uint8_t v1117 = rbcnt1[d6];	// L1799
        ap_int<33> v1118 = v1117;	// L1800
        ap_int<33> v1119 = v1118 - 1;	// L1801
        uint8_t v1120 = v1119;	// L1802
        rbcnt1[d6] = v1120;	// L1803
      }
    }
    int32_t v1121 = inj_done1;	// L1806
    bool v1122 = v1121 == 1;	// L1807
    if (v1122) {	// L1808
      csd_pkt1 = 0;	// L1809
    }
    ap_int<26> v1123 = o_crv1;	// L1811
    bool v1124;
    ap_int<26> v1124_tmp = v1123;
    v1124 = v1124_tmp[25];	// L1812
    int32_t v1125 = v1124;	// L1813
    crv_vld1 = v1125;	// L1814
    int32_t v1126 = crv_vld1;	// L1815
    bool v1127 = v1126 == 1;	// L1816
    if (v1127) {	// L1817
      crv_ever1 = 1;	// L1818
    }
    ap_int<26> v1128 = o_crv1;	// L1820
    int16_t v1129;
    ap_int<26> v1129_tmp = v1128;
    v1129 = v1129_tmp(15, 0);	// L1821
    half v1130;
    union { uint16_t from; half to;} _converter_v1129_to_v1130 = {};
    _converter_v1129_to_v1130.from = v1129;
    v1130 = _converter_v1129_to_v1130.to;	// L1822
    crv_data1 = v1130;	// L1823
    ap_int<26> v1131 = o_crv1;	// L1824
    ap_int<4> v1132;
    ap_int<26> v1132_tmp = v1131;
    v1132 = v1132_tmp(19, 16);	// L1825
    int32_t v1133 = v1132;	// L1826
    crv_addr1 = v1133;	// L1827
    ap_int<26> v1134 = o_crv1;	// L1828
    bool v1135;
    ap_int<26> v1135_tmp = v1134;
    v1135 = v1135_tmp[20];	// L1829
    int32_t v1136 = v1135;	// L1830
    crv_mode1 = v1136;	// L1831
    ap_int<26> v1137 = o_crv1;	// L1832
    int16_t v1138;
    ap_int<26> v1138_tmp = v1137;
    v1138 = v1138_tmp(15, 0);	// L1833
    int32_t v1139 = v1138;	// L1834
    crv_raw1 = v1139;	// L1835
    half rxv1[4];	// L1836
    for (int v1141 = 0; v1141 < 4; v1141++) {	// L1837
      rxv1[v1141] = 0.000000;	// L1837
    }
    int32_t rxvld1[4];	// L1838
    for (int v1143 = 0; v1143 < 4; v1143++) {	// L1839
      rxvld1[v1143] = 0;	// L1839
    }
    uint8_t v1144 = hold_cnt1[0];	// L1840
    int32_t v1145 = v1144;	// L1841
    bool v1146 = v1145 < 2;	// L1842
    if (v1146) {	// L1843
      ap_uint<17> v1147;
      bool v1148 = v883.read_nb(v1147);
	// L1844
      ap_uint<17> sgn1;	// L1845
      sgn1 = v1147;	// L1846
      bool sqn1;	// L1847
      sqn1 = v1148;	// L1848
      bool v1151 = sqn1;	// L1849
      int32_t v1152 = v1151;	// L1850
      bool v1153 = v1152 == 1;	// L1851
      if (v1153) {	// L1852
        ap_int<17> v1154 = sgn1;	// L1853
        int16_t v1155;
        ap_int<17> v1155_tmp = v1154;
        v1155 = v1155_tmp(16, 1);	// L1854
        half v1156;
        union { uint16_t from; half to;} _converter_v1155_to_v1156 = {};
        _converter_v1155_to_v1156.from = v1155;
        v1156 = _converter_v1155_to_v1156.to;	// L1855
        rxv1[0] = v1156;	// L1856
        rxvld1[0] = 1;	// L1857
      }
    }
    uint8_t v1157 = hold_cnt1[1];	// L1860
    int32_t v1158 = v1157;	// L1861
    bool v1159 = v1158 < 2;	// L1862
    if (v1159) {	// L1863
      ap_uint<17> v1160;
      bool v1161 = v884.read_nb(v1160);
	// L1864
      ap_uint<17> sgs1;	// L1865
      sgs1 = v1160;	// L1866
      bool sqs1;	// L1867
      sqs1 = v1161;	// L1868
      bool v1164 = sqs1;	// L1869
      int32_t v1165 = v1164;	// L1870
      bool v1166 = v1165 == 1;	// L1871
      if (v1166) {	// L1872
        ap_int<17> v1167 = sgs1;	// L1873
        int16_t v1168;
        ap_int<17> v1168_tmp = v1167;
        v1168 = v1168_tmp(16, 1);	// L1874
        half v1169;
        union { uint16_t from; half to;} _converter_v1168_to_v1169 = {};
        _converter_v1168_to_v1169.from = v1168;
        v1169 = _converter_v1168_to_v1169.to;	// L1875
        rxv1[1] = v1169;	// L1876
        rxvld1[1] = 1;	// L1877
      }
    }
    uint8_t v1170 = hold_cnt1[2];	// L1880
    int32_t v1171 = v1170;	// L1881
    bool v1172 = v1171 < 2;	// L1882
    if (v1172) {	// L1883
      ap_uint<17> v1173;
      bool v1174 = v885.read_nb(v1173);
	// L1884
      ap_uint<17> sgw1;	// L1885
      sgw1 = v1173;	// L1886
      bool sqw1;	// L1887
      sqw1 = v1174;	// L1888
      bool v1177 = sqw1;	// L1889
      int32_t v1178 = v1177;	// L1890
      bool v1179 = v1178 == 1;	// L1891
      if (v1179) {	// L1892
        ap_int<17> v1180 = sgw1;	// L1893
        int16_t v1181;
        ap_int<17> v1181_tmp = v1180;
        v1181 = v1181_tmp(16, 1);	// L1894
        half v1182;
        union { uint16_t from; half to;} _converter_v1181_to_v1182 = {};
        _converter_v1181_to_v1182.from = v1181;
        v1182 = _converter_v1181_to_v1182.to;	// L1895
        rxv1[2] = v1182;	// L1896
        rxvld1[2] = 1;	// L1897
      }
    }
    uint8_t v1183 = hold_cnt1[3];	// L1900
    int32_t v1184 = v1183;	// L1901
    bool v1185 = v1184 < 2;	// L1902
    if (v1185) {	// L1903
      ap_uint<17> v1186;
      bool v1187 = v886.read_nb(v1186);
	// L1904
      ap_uint<17> sge1;	// L1905
      sge1 = v1186;	// L1906
      bool sqe1;	// L1907
      sqe1 = v1187;	// L1908
      bool v1190 = sqe1;	// L1909
      int32_t v1191 = v1190;	// L1910
      bool v1192 = v1191 == 1;	// L1911
      if (v1192) {	// L1912
        ap_int<17> v1193 = sge1;	// L1913
        int16_t v1194;
        ap_int<17> v1194_tmp = v1193;
        v1194 = v1194_tmp(16, 1);	// L1914
        half v1195;
        union { uint16_t from; half to;} _converter_v1194_to_v1195 = {};
        _converter_v1194_to_v1195.from = v1194;
        v1195 = _converter_v1194_to_v1195.to;	// L1915
        rxv1[3] = v1195;	// L1916
        rxvld1[3] = 1;	// L1917
      }
    }
    l_S_d_4_d7: for (int d7 = 0; d7 < 4; d7++) {	// L1920
      int32_t v1197 = rxvld1[d7];	// L1921
      bool v1198 = v1197 == 1;	// L1922
      if (v1198) {	// L1923
        half v1199 = rxv1[d7];	// L1924
        uint8_t v1200 = hold_cnt1[d7];	// L1925
        int v1201 = v1200;	// L1926
        hold_v1[d7][v1201] = v1199;	// L1927
        uint8_t v1202 = hold_cnt1[d7];	// L1928
        ap_int<33> v1203 = v1202;	// L1929
        ap_int<33> v1204 = v1203 + 1;	// L1930
        uint8_t v1205 = v1204;	// L1931
        hold_cnt1[d7] = v1205;	// L1932
      }
    }
    ap_uint<17> tx_n1;	// L1935
    tx_n1 = 0;	// L1936
    ap_uint<17> tx_s1;	// L1937
    tx_s1 = 0;	// L1938
    ap_uint<17> tx_w1;	// L1939
    tx_w1 = 0;	// L1940
    ap_uint<17> tx_e1;	// L1941
    tx_e1 = 0;	// L1942
    uint8_t v1210 = sb_v1[0];	// L1943
    int32_t v1211 = v1210;	// L1944
    bool v1212 = v1211 == 1;	// L1945
    if (v1212) {	// L1946
      uint8_t v1213 = sb_ix1[0];	// L1947
      int v1214 = v1213;	// L1948
      half v1215 = resq1[v1214];	// L1949
      half wb1;
#pragma HLS dependence variable=wb1 type=inter dependent=false	// L1950
      wb1 = v1215;	// L1951
      uint8_t v1217 = sb_cmp1[0];	// L1952
      int32_t v1218 = v1217;	// L1953
      bool v1219 = v1218 == 1;	// L1954
      if (v1219) {	// L1955
        uint8_t v1220 = sb_ix1[0];	// L1956
        int v1221 = v1220;	// L1957
        uint8_t v1222 = cmpq1[v1221];	// L1958
        condition_reg1 = v1222;	// L1959
      }
      uint8_t v1223 = sb_rtr1[0];	// L1961
      int32_t v1224 = v1223;	// L1962
      bool v1225 = v1224 == 1;	// L1963
      if (v1225) {	// L1964
        uint8_t v1226 = sb_inj1[0];	// L1965
        int32_t v1227 = v1226;	// L1966
        bool v1228 = v1227 == 1;	// L1967
        ap_int<26> v1229 = csd_pkt1;	// L1968
        bool v1230;
        ap_int<26> v1230_tmp = v1229;
        v1230 = v1230_tmp[25];	// L1969
        int32_t v1231 = v1230;	// L1970
        bool v1232 = v1231 == 0;	// L1971
        bool v1233 = v1228 & v1232;	// L1972
        if (v1233) {	// L1973
          half v1234 = wb1;	// L1974
          uint16_t v1235;
          union { half from; uint16_t to;} _converter_v1234_to_v1235 = {};
          _converter_v1234_to_v1235.from = v1234;
          v1235 = _converter_v1234_to_v1235.to;	// L1975
          ap_int<26> v1236 = csd_pkt1;	// L1976
          ap_int<26> v1237;
          ap_int<26> v1237_tmp = v1236;
          v1237_tmp(15, 0) = v1235;
          v1237 = v1237_tmp;	// L1977
          csd_pkt1 = v1237;	// L1978
          uint8_t v1238 = sb_dst1[0];	// L1979
          ap_uint<4> v1239 = v1238;	// L1980
          ap_int<26> v1240 = csd_pkt1;	// L1981
          ap_int<26> v1241;
          ap_int<26> v1241_tmp = v1240;
          v1241_tmp(19, 16) = v1239;
          v1241 = v1241_tmp;	// L1982
          csd_pkt1 = v1241;	// L1983
          uint8_t v1242 = sb_id1[0];	// L1984
          ap_uint<4> v1243 = v1242;	// L1985
          ap_int<26> v1244 = csd_pkt1;	// L1986
          ap_int<26> v1245;
          ap_int<26> v1245_tmp = v1244;
          v1245_tmp(24, 21) = v1243;
          v1245 = v1245_tmp;	// L1987
          csd_pkt1 = v1245;	// L1988
          uint8_t v1246 = sb_rvld1[0];	// L1989
          bool v1247 = v1246;	// L1990
          ap_int<26> v1248 = csd_pkt1;	// L1991
          ap_int<26> v1249;
          ap_int<26> v1249_tmp = v1248;
          v1249_tmp[25] = v1247;          v1249 = v1249_tmp;	// L1992
          csd_pkt1 = v1249;	// L1993
          uint8_t v1250 = sb_dir1[0];	// L1994
          int32_t v1251 = v1250;	// L1995
          csd_dir1 = v1251;	// L1996
        }
      } else {
        uint8_t v1252 = sb_dst1[0];	// L1999
        int32_t v1253 = v1252;	// L2000
        bool v1254 = v1253 >= 12;	// L2001
        if (v1254) {	// L2002
          ap_uint<17> tw01;	// L2003
          tw01 = 0;	// L2004
          uint8_t v1256 = sb_rvld1[0];	// L2005
          bool v1257 = v1256;	// L2006
          ap_int<17> v1258 = tw01;	// L2007
          ap_int<17> v1259;
          ap_int<17> v1259_tmp = v1258;
          v1259_tmp[0] = v1257;          v1259 = v1259_tmp;	// L2008
          tw01 = v1259;	// L2009
          half v1260 = wb1;	// L2010
          uint16_t v1261;
          union { half from; uint16_t to;} _converter_v1260_to_v1261 = {};
          _converter_v1260_to_v1261.from = v1260;
          v1261 = _converter_v1260_to_v1261.to;	// L2011
          ap_int<17> v1262 = tw01;	// L2012
          ap_int<17> v1263;
          ap_int<17> v1263_tmp = v1262;
          v1263_tmp(16, 1) = v1261;
          v1263 = v1263_tmp;	// L2013
          tw01 = v1263;	// L2014
          uint8_t v1264 = sb_dst1[0];	// L2015
          int32_t v1265 = v1264;	// L2016
          int32_t v1266 = v1265 & 3;	// L2017
          bool v1267 = v1266 == 0;	// L2018
          if (v1267) {	// L2019
            ap_int<17> v1268 = tw01;	// L2020
            tx_n1 = v1268;	// L2021
          } else {
            uint8_t v1269 = sb_dst1[0];	// L2023
            int32_t v1270 = v1269;	// L2024
            int32_t v1271 = v1270 & 3;	// L2025
            bool v1272 = v1271 == 1;	// L2026
            if (v1272) {	// L2027
              ap_int<17> v1273 = tw01;	// L2028
              tx_s1 = v1273;	// L2029
            } else {
              uint8_t v1274 = sb_dst1[0];	// L2031
              int32_t v1275 = v1274;	// L2032
              int32_t v1276 = v1275 & 3;	// L2033
              bool v1277 = v1276 == 2;	// L2034
              if (v1277) {	// L2035
                ap_int<17> v1278 = tw01;	// L2036
                tx_w1 = v1278;	// L2037
              } else {
                ap_int<17> v1279 = tw01;	// L2039
                tx_e1 = v1279;	// L2040
              }
            }
          }
        } else {
          uint8_t v1280 = sb_rvld1[0];	// L2045
          int32_t v1281 = v1280;	// L2046
          bool v1282 = v1281 == 1;	// L2047
          if (v1282) {	// L2048
            uint8_t v1283 = sb_dst1[0];	// L2049
            int32_t v1284 = v1283;	// L2050
            bool v1285 = v1284 < 8;	// L2051
            int32_t v1286 = dsmask1;	// L2052
            int32_t v1287 = v1286 >> v1284;	// L2053
            int32_t v1288 = v1287 & 1;	// L2054
            bool v1289 = v1288 == 1;	// L2055
            bool v1290 = v1285 & v1289;	// L2056
            if (v1290) {	// L2057
              uint8_t v1291 = sb_dst1[0];	// L2058
              int v1292 = v1291;	// L2059
              int32_t v1293 = drf_full1[v1292];	// L2060
              bool v1294 = v1293 == 0;	// L2061
              if (v1294) {	// L2062
                half v1295 = wb1;	// L2063
                uint8_t v1296 = sb_dst1[0];	// L2064
                int v1297 = v1296;	// L2065
                drf1[v1297] = v1295;	// L2066
                uint8_t v1298 = sb_dst1[0];	// L2067
                int v1299 = v1298;	// L2068
                drf_full1[v1299] = 1;	// L2069
              }
            } else {
              half v1300 = wb1;	// L2072
              uint8_t v1301 = sb_dst1[0];	// L2073
              int32_t v1302 = v1301;	// L2074
              int32_t v1303 = v1302 & 7;	// L2075
              int v1304 = v1303;	// L2076
              drf1[v1304] = v1300;	// L2077
            }
          }
        }
      }
    }
    int32_t pc1;	// L2083
    pc1 = -1;	// L2084
    int8_t v1306 = fetch_en1;	// L2085
    int32_t v1307 = v1306;	// L2086
    bool v1308 = v1307 == 1;	// L2087
    if (v1308) {	// L2088
      int8_t v1309 = instr_cnt1;	// L2089
      int32_t v1310 = v1309;	// L2090
      pc1 = v1310;	// L2091
    }
    int8_t v1311 = fetch_en1;	// L2093
    int32_t v1312 = v1311;	// L2094
    bool v1313 = v1312 == 1;	// L2095
    if (v1313) {	// L2096
      fe_ever1 = 1;	// L2097
    }
    int32_t instr1;	// L2099
    instr1 = 0;	// L2100
    int32_t v1315 = pc1;	// L2101
    bool v1316 = v1315 >= 0;	// L2102
    if (v1316) {	// L2103
      int32_t v1317 = pc1;	// L2104
      int v1318 = v1317;	// L2105
      int32_t v1319 = irf1[v1318];	// L2106
      instr1 = v1319;	// L2107
    }
    int32_t v1320 = instr1;	// L2109
    int32_t v1321 = v1320 & 15;	// L2110
    int32_t op1;	// L2111
    op1 = v1321;	// L2112
    int32_t v1323 = instr1;	// L2113
    int32_t v1324 = v1323 >> 4;	// L2114
    int32_t v1325 = v1324 & 15;	// L2115
    int32_t dst1;	// L2116
    dst1 = v1325;	// L2117
    int32_t v1327 = instr1;	// L2118
    int32_t v1328 = v1327 >> 8;	// L2119
    int32_t v1329 = v1328 & 15;	// L2120
    int32_t s11;	// L2121
    s11 = v1329;	// L2122
    int32_t v1331 = instr1;	// L2123
    int32_t v1332 = v1331 >> 12;	// L2124
    int32_t v1333 = v1332 & 15;	// L2125
    int32_t s21;	// L2126
    s21 = v1333;	// L2127
    half a1;	// L2128
    a1 = 0.000000;	// L2129
    half b1;	// L2130
    b1 = 0.000000;	// L2131
    int32_t v1337 = s11;	// L2132
    bool v1338 = v1337 >= 12;	// L2133
    if (v1338) {	// L2134
      int32_t v1339 = s11;	// L2135
      int32_t v1340 = v1339 & 3;	// L2136
      int v1341 = v1340;	// L2137
      half v1342 = hold_v1[v1341][0];	// L2138
      a1 = v1342;	// L2139
    } else {
      int32_t v1343 = s11;	// L2141
      int v1344 = v1343;	// L2142
      half v1345 = drf1[v1344];	// L2143
      a1 = v1345;	// L2144
    }
    int32_t v1346 = s21;	// L2146
    bool v1347 = v1346 >= 12;	// L2147
    if (v1347) {	// L2148
      int32_t v1348 = s21;	// L2149
      int32_t v1349 = v1348 & 3;	// L2150
      int v1350 = v1349;	// L2151
      half v1351 = hold_v1[v1350][0];	// L2152
      b1 = v1351;	// L2153
    } else {
      int32_t v1352 = s21;	// L2155
      int v1353 = v1352;	// L2156
      half v1354 = drf1[v1353];	// L2157
      b1 = v1354;	// L2158
    }
    int32_t a_vld1;	// L2160
    a_vld1 = 1;	// L2161
    int32_t b_vld1;	// L2162
    b_vld1 = 1;	// L2163
    int32_t v1357 = s11;	// L2164
    bool v1358 = v1357 >= 12;	// L2165
    if (v1358) {	// L2166
      a_vld1 = 0;	// L2167
      int32_t v1359 = s11;	// L2168
      int32_t v1360 = v1359 & 3;	// L2169
      int v1361 = v1360;	// L2170
      uint8_t v1362 = hold_cnt1[v1361];	// L2171
      int32_t v1363 = v1362;	// L2172
      bool v1364 = v1363 > 0;	// L2173
      if (v1364) {	// L2174
        a_vld1 = 1;	// L2175
      }
    }
    int32_t v1365 = s21;	// L2178
    bool v1366 = v1365 >= 12;	// L2179
    if (v1366) {	// L2180
      b_vld1 = 0;	// L2181
      int32_t v1367 = s21;	// L2182
      int32_t v1368 = v1367 & 3;	// L2183
      int v1369 = v1368;	// L2184
      uint8_t v1370 = hold_cnt1[v1369];	// L2185
      int32_t v1371 = v1370;	// L2186
      bool v1372 = v1371 > 0;	// L2187
      if (v1372) {	// L2188
        b_vld1 = 1;	// L2189
      }
    }
    int32_t v1373 = s11;	// L2192
    bool v1374 = v1373 < 8;	// L2193
    int32_t v1375 = dsmask1;	// L2194
    int32_t v1376 = v1375 >> v1373;	// L2195
    int32_t v1377 = v1376 & 1;	// L2196
    bool v1378 = v1377 == 1;	// L2197
    bool v1379 = v1374 & v1378;	// L2198
    if (v1379) {	// L2199
      int32_t v1380 = s11;	// L2200
      int v1381 = v1380;	// L2201
      int32_t v1382 = drf_full1[v1381];	// L2202
      bool v1383 = v1382 == 0;	// L2203
      if (v1383) {	// L2204
        a_vld1 = 0;	// L2205
      }
    }
    int32_t v1384 = s21;	// L2208
    bool v1385 = v1384 < 8;	// L2209
    int32_t v1386 = dsmask1;	// L2210
    int32_t v1387 = v1386 >> v1384;	// L2211
    int32_t v1388 = v1387 & 1;	// L2212
    bool v1389 = v1388 == 1;	// L2213
    bool v1390 = v1385 & v1389;	// L2214
    if (v1390) {	// L2215
      int32_t v1391 = s21;	// L2216
      int v1392 = v1391;	// L2217
      int32_t v1393 = drf_full1[v1392];	// L2218
      bool v1394 = v1393 == 0;	// L2219
      if (v1394) {	// L2220
        b_vld1 = 0;	// L2221
      }
    }
    int32_t binop1;	// L2224
    binop1 = 0;	// L2225
    int32_t v1396 = op1;	// L2226
    bool v1397 = v1396 == 0;	// L2227
    bool v1398 = v1396 == 1;	// L2228
    bool v1399 = v1396 == 2;	// L2229
    bool v1400 = v1396 == 8;	// L2230
    bool v1401 = v1396 == 9;	// L2231
    bool v1402 = v1397 | v1398;	// L2232
    bool v1403 = v1402 | v1399;	// L2233
    bool v1404 = v1403 | v1400;	// L2234
    bool v1405 = v1404 | v1401;	// L2235
    if (v1405) {	// L2236
      binop1 = 1;	// L2237
    }
    int32_t raw1;	// L2239
    raw1 = 0;	// L2240
    int32_t cmp_busy1;	// L2241
    cmp_busy1 = 0;	// L2242
    l_S_k_5_k2: for (int k2 = 0; k2 < 4; k2++) {	// L2243
      uint8_t v1409 = sb_v1[(k2 + 1)];	// L2244
      int32_t v1410 = v1409;	// L2245
      bool v1411 = v1410 == 1;	// L2246
      uint8_t v1412 = sb_rtr1[(k2 + 1)];	// L2247
      int32_t v1413 = v1412;	// L2248
      bool v1414 = v1413 == 0;	// L2249
      uint8_t v1415 = sb_dst1[(k2 + 1)];	// L2250
      int32_t v1416 = v1415;	// L2251
      bool v1417 = v1416 < 12;	// L2252
      bool v1418 = v1411 & v1414;	// L2253
      bool v1419 = v1418 & v1417;	// L2254
      if (v1419) {	// L2255
        int32_t v1420 = s11;	// L2256
        bool v1421 = v1420 < 12;	// L2257
        uint8_t v1422 = sb_dst1[(k2 + 1)];	// L2258
        int32_t v1423 = v1422;	// L2259
        int32_t v1424 = v1423 & 7;	// L2260
        int32_t v1425 = v1420 & 7;	// L2261
        bool v1426 = v1424 == v1425;	// L2262
        bool v1427 = v1421 & v1426;	// L2263
        if (v1427) {	// L2264
          raw1 = 1;	// L2265
        }
        int32_t v1428 = binop1;	// L2267
        bool v1429 = v1428 == 1;	// L2268
        int32_t v1430 = s21;	// L2269
        bool v1431 = v1430 < 12;	// L2270
        uint8_t v1432 = sb_dst1[(k2 + 1)];	// L2271
        int32_t v1433 = v1432;	// L2272
        int32_t v1434 = v1433 & 7;	// L2273
        int32_t v1435 = v1430 & 7;	// L2274
        bool v1436 = v1434 == v1435;	// L2275
        bool v1437 = v1429 & v1431;	// L2276
        bool v1438 = v1437 & v1436;	// L2277
        if (v1438) {	// L2278
          raw1 = 1;	// L2279
        }
      }
      uint8_t v1439 = sb_v1[(k2 + 1)];	// L2282
      int32_t v1440 = v1439;	// L2283
      bool v1441 = v1440 == 1;	// L2284
      uint8_t v1442 = sb_cmp1[(k2 + 1)];	// L2285
      int32_t v1443 = v1442;	// L2286
      bool v1444 = v1443 == 1;	// L2287
      bool v1445 = v1441 & v1444;	// L2288
      if (v1445) {	// L2289
        cmp_busy1 = 1;	// L2290
      }
    }
    int32_t is_cond1;	// L2293
    is_cond1 = 0;	// L2294
    int32_t v1447 = op1;	// L2295
    bool v1448 = v1447 >= 12;	// L2296
    ap_int<33> v1449 = v1447;	// L2297
    bool v1450 = v1449 <= 15;	// L2298
    bool v1451 = v1448 & v1450;	// L2299
    if (v1451) {	// L2300
      is_cond1 = 1;	// L2301
    }
    int32_t grant1;	// L2303
    grant1 = 0;	// L2304
    int32_t v1453 = pc1;	// L2305
    bool v1454 = v1453 >= 0;	// L2306
    if (v1454) {	// L2307
      grant1 = 1;	// L2308
    }
    int32_t v1455 = pc1;	// L2310
    bool v1456 = v1455 >= 0;	// L2311
    int32_t v1457 = a_vld1;	// L2312
    bool v1458 = v1457 == 0;	// L2313
    int32_t v1459 = binop1;	// L2314
    bool v1460 = v1459 == 1;	// L2315
    int32_t v1461 = b_vld1;	// L2316
    bool v1462 = v1461 == 0;	// L2317
    bool v1463 = v1460 & v1462;	// L2318
    bool v1464 = v1458 | v1463;	// L2319
    bool v1465 = v1456 & v1464;	// L2320
    if (v1465) {	// L2321
      grant1 = 0;	// L2322
    }
    int32_t v1466 = pc1;	// L2324
    bool v1467 = v1466 >= 0;	// L2325
    int32_t v1468 = raw1;	// L2326
    bool v1469 = v1468 == 1;	// L2327
    int32_t v1470 = is_cond1;	// L2328
    bool v1471 = v1470 == 1;	// L2329
    int32_t v1472 = cmp_busy1;	// L2330
    bool v1473 = v1472 == 1;	// L2331
    bool v1474 = v1471 & v1473;	// L2332
    bool v1475 = v1469 | v1474;	// L2333
    bool v1476 = v1467 & v1475;	// L2334
    if (v1476) {	// L2335
      grant1 = 0;	// L2336
    }
    int32_t v1477 = grant1;	// L2338
    bool v1478 = v1477 == 1;	// L2339
    if (v1478) {	// L2340
      int8_t v1479 = instr_cnt1;	// L2341
      int32_t v1480 = cfg_isz1;	// L2342
      int32_t v1481 = v1479;	// L2343
      bool v1482 = v1481 == v1480;	// L2344
      if (v1482) {	// L2345
        instr_cnt1 = 0;	// L2346
        int8_t v1483 = iter_cnt1;	// L2347
        int32_t v1484 = cfg_itsz1;	// L2348
        ap_int<33> v1485 = v1484;	// L2349
        ap_int<33> v1486 = v1485 - 1;	// L2350
        ap_int<33> v1487 = v1483;	// L2351
        bool v1488 = v1487 == v1486;	// L2352
        if (v1488) {	// L2353
          fetch_en1 = 0;	// L2354
        } else {
          int8_t v1489 = iter_cnt1;	// L2356
          ap_int<33> v1490 = v1489;	// L2357
          ap_int<33> v1491 = v1490 + 1;	// L2358
          uint8_t v1492 = v1491;	// L2359
          iter_cnt1 = v1492;	// L2360
        }
      } else {
        int8_t v1493 = instr_cnt1;	// L2363
        ap_int<33> v1494 = v1493;	// L2364
        ap_int<33> v1495 = v1494 + 1;	// L2365
        uint8_t v1496 = v1495;	// L2366
        instr_cnt1 = v1496;	// L2367
      }
    }
    int32_t c11;	// L2370
    c11 = -1;	// L2371
    int32_t c21;	// L2372
    c21 = -1;	// L2373
    int32_t v1499 = grant1;	// L2374
    bool v1500 = v1499 == 1;	// L2375
    int32_t v1501 = s11;	// L2376
    bool v1502 = v1501 >= 12;	// L2377
    bool v1503 = v1500 & v1502;	// L2378
    if (v1503) {	// L2379
      int32_t v1504 = s11;	// L2380
      int32_t v1505 = v1504 & 3;	// L2381
      c11 = v1505;	// L2382
    }
    int32_t v1506 = grant1;	// L2384
    bool v1507 = v1506 == 1;	// L2385
    int32_t v1508 = s21;	// L2386
    bool v1509 = v1508 >= 12;	// L2387
    bool v1510 = v1507 & v1509;	// L2388
    if (v1510) {	// L2389
      int32_t v1511 = s21;	// L2390
      int32_t v1512 = v1511 & 3;	// L2391
      c21 = v1512;	// L2392
    }
    int32_t v1513 = c11;	// L2394
    bool v1514 = v1513 >= 0;	// L2395
    if (v1514) {	// L2396
      int32_t v1515 = c11;	// L2397
      int v1516 = v1515;	// L2398
      half v1517 = hold_v1[v1516][1];	// L2399
      hold_v1[v1516][0] = v1517;	// L2400
      int32_t v1518 = c11;	// L2401
      int v1519 = v1518;	// L2402
      uint8_t v1520 = hold_cnt1[v1519];	// L2403
      ap_int<33> v1521 = v1520;	// L2404
      ap_int<33> v1522 = v1521 - 1;	// L2405
      uint8_t v1523 = v1522;	// L2406
      hold_cnt1[v1519] = v1523;	// L2407
    }
    int32_t v1524 = c21;	// L2409
    bool v1525 = v1524 >= 0;	// L2410
    int32_t v1526 = c11;	// L2411
    bool v1527 = v1524 != v1526;	// L2412
    bool v1528 = v1525 & v1527;	// L2413
    if (v1528) {	// L2414
      int32_t v1529 = c21;	// L2415
      int v1530 = v1529;	// L2416
      half v1531 = hold_v1[v1530][1];	// L2417
      hold_v1[v1530][0] = v1531;	// L2418
      int32_t v1532 = c21;	// L2419
      int v1533 = v1532;	// L2420
      uint8_t v1534 = hold_cnt1[v1533];	// L2421
      ap_int<33> v1535 = v1534;	// L2422
      ap_int<33> v1536 = v1535 - 1;	// L2423
      uint8_t v1537 = v1536;	// L2424
      hold_cnt1[v1533] = v1537;	// L2425
    }
    int32_t v1538 = grant1;	// L2427
    bool v1539 = v1538 == 1;	// L2428
    int32_t v1540 = s11;	// L2429
    bool v1541 = v1540 < 8;	// L2430
    int32_t v1542 = dsmask1;	// L2431
    int32_t v1543 = v1542 >> v1540;	// L2432
    int32_t v1544 = v1543 & 1;	// L2433
    bool v1545 = v1544 == 1;	// L2434
    bool v1546 = v1539 & v1541;	// L2435
    bool v1547 = v1546 & v1545;	// L2436
    if (v1547) {	// L2437
      int32_t v1548 = s11;	// L2438
      int v1549 = v1548;	// L2439
      drf_full1[v1549] = 0;	// L2440
    }
    int32_t v1550 = grant1;	// L2442
    bool v1551 = v1550 == 1;	// L2443
    int32_t v1552 = s21;	// L2444
    bool v1553 = v1552 < 8;	// L2445
    int32_t v1554 = dsmask1;	// L2446
    int32_t v1555 = v1554 >> v1552;	// L2447
    int32_t v1556 = v1555 & 1;	// L2448
    bool v1557 = v1556 == 1;	// L2449
    bool v1558 = v1551 & v1553;	// L2450
    bool v1559 = v1558 & v1557;	// L2451
    if (v1559) {	// L2452
      int32_t v1560 = s21;	// L2453
      int v1561 = v1560;	// L2454
      drf_full1[v1561] = 0;	// L2455
    }
    half res1;
#pragma HLS dependence variable=res1 type=inter dependent=false	// L2457
    res1 = 0.000000;	// L2458
    int32_t v1563 = op1;	// L2459
    bool v1564 = v1563 == 0;	// L2460
    if (v1564) {	// L2461
      half v1565 = a1;	// L2462
      half v1566 = b1;	// L2463
      half v1567 = v1565 + v1566;	// L2464
      res1 = v1567;	// L2465
    } else {
      int32_t v1568 = op1;	// L2467
      bool v1569 = v1568 == 1;	// L2468
      if (v1569) {	// L2469
        half v1570 = a1;	// L2470
        half v1571 = b1;	// L2471
        half v1572 = v1570 - v1571;	// L2472
        res1 = v1572;	// L2473
      } else {
        int32_t v1573 = op1;	// L2475
        bool v1574 = v1573 == 2;	// L2476
        if (v1574) {	// L2477
          half v1575 = a1;	// L2478
          half v1576 = b1;	// L2479
          half v1577 = v1575 * v1576;	// L2480
          res1 = v1577;	// L2481
        } else {
          int32_t v1578 = op1;	// L2483
          bool v1579 = v1578 == 8;	// L2484
          if (v1579) {	// L2485
            half v1580 = a1;	// L2486
            half v1581 = b1;	// L2487
            bool v1582 = v1580 >= v1581;	// L2488
            if (v1582) {	// L2489
              res1 = 1.000000;	// L2490
            } else {
              res1 = -1.000000;	// L2492
            }
          } else {
            int32_t v1583 = op1;	// L2495
            bool v1584 = v1583 == 9;	// L2496
            if (v1584) {	// L2497
              half v1585 = a1;	// L2498
              half v1586 = b1;	// L2499
              bool v1587 = v1585 < v1586;	// L2500
              if (v1587) {	// L2501
                res1 = 1.000000;	// L2502
              } else {
                res1 = -1.000000;	// L2504
              }
            } else {
              half v1588 = a1;	// L2507
              res1 = v1588;	// L2508
            }
          }
        }
      }
    }
    int32_t v1589 = a_vld1;	// L2514
    int32_t res_vld1;	// L2515
    res_vld1 = v1589;	// L2516
    int32_t v1591 = op1;	// L2517
    bool v1592 = v1591 == 0;	// L2518
    bool v1593 = v1591 == 1;	// L2519
    bool v1594 = v1591 == 2;	// L2520
    bool v1595 = v1591 == 8;	// L2521
    bool v1596 = v1591 == 9;	// L2522
    bool v1597 = v1592 | v1593;	// L2523
    bool v1598 = v1597 | v1594;	// L2524
    bool v1599 = v1598 | v1595;	// L2525
    bool v1600 = v1599 | v1596;	// L2526
    if (v1600) {	// L2527
      int32_t v1601 = a_vld1;	// L2528
      int32_t v1602 = b_vld1;	// L2529
      int64_t v1603 = v1601;	// L2530
      int64_t v1604 = v1602;	// L2531
      int64_t v1605 = v1603 * v1604;	// L2532
      int32_t v1606 = v1605;	// L2533
      res_vld1 = v1606;	// L2534
    }
    int32_t v1607 = grant1;	// L2536
    bool v1608 = v1607 == 0;	// L2537
    if (v1608) {	// L2538
      res_vld1 = 0;	// L2539
    }
    int32_t is_rtr1;	// L2541
    is_rtr1 = 0;	// L2542
    int32_t v1610 = op1;	// L2543
    bool v1611 = v1610 >= 4;	// L2544
    ap_int<33> v1612 = v1610;	// L2545
    bool v1613 = v1612 <= 7;	// L2546
    bool v1614 = v1611 & v1613;	// L2547
    if (v1614) {	// L2548
      is_rtr1 = 1;	// L2549
    }
    l_S_k_6_k3: for (int k3 = 0; k3 < 4; k3++) {	// L2551
      uint8_t v1616 = sb_v1[(k3 + 1)];	// L2552
      sb_v1[k3] = v1616;	// L2553
      uint8_t v1617 = sb_dst1[(k3 + 1)];	// L2554
      sb_dst1[k3] = v1617;	// L2555
      uint8_t v1618 = sb_cmp1[(k3 + 1)];	// L2556
      sb_cmp1[k3] = v1618;	// L2557
      uint8_t v1619 = sb_rtr1[(k3 + 1)];	// L2558
      sb_rtr1[k3] = v1619;	// L2559
      uint8_t v1620 = sb_inj1[(k3 + 1)];	// L2560
      sb_inj1[k3] = v1620;	// L2561
      uint8_t v1621 = sb_dir1[(k3 + 1)];	// L2562
      sb_dir1[k3] = v1621;	// L2563
      uint8_t v1622 = sb_id1[(k3 + 1)];	// L2564
      sb_id1[k3] = v1622;	// L2565
      uint8_t v1623 = sb_rvld1[(k3 + 1)];	// L2566
      sb_rvld1[k3] = v1623;	// L2567
      uint8_t v1624 = sb_ix1[(k3 + 1)];	// L2568
      sb_ix1[k3] = v1624;	// L2569
    }
    sb_v1[4] = 0;	// L2571
    int32_t v1625 = grant1;	// L2572
    bool v1626 = v1625 == 1;	// L2573
    if (v1626) {	// L2574
      half v1627 = res1;	// L2575
      int8_t v1628 = resq_wr1;	// L2576
      int v1629 = v1628;	// L2577
      resq1[v1629] = v1627;	// L2578
      int32_t cq1;	// L2579
      cq1 = 0;	// L2580
      int32_t v1631 = op1;	// L2581
      bool v1632 = v1631 == 8;	// L2582
      if (v1632) {	// L2583
        half v1633 = a1;	// L2584
        half v1634 = b1;	// L2585
        bool v1635 = v1633 >= v1634;	// L2586
        if (v1635) {	// L2587
          cq1 = 1;	// L2588
        }
      }
      int32_t v1636 = op1;	// L2591
      bool v1637 = v1636 == 9;	// L2592
      if (v1637) {	// L2593
        half v1638 = a1;	// L2594
        half v1639 = b1;	// L2595
        bool v1640 = v1638 < v1639;	// L2596
        if (v1640) {	// L2597
          cq1 = 1;	// L2598
        }
      }
      int32_t v1641 = cq1;	// L2601
      uint8_t v1642 = v1641;	// L2602
      int8_t v1643 = resq_wr1;	// L2603
      int v1644 = v1643;	// L2604
      cmpq1[v1644] = v1642;	// L2605
      sb_v1[4] = 1;	// L2606
      int32_t v1645 = dst1;	// L2607
      uint8_t v1646 = v1645;	// L2608
      sb_dst1[4] = v1646;	// L2609
      int8_t v1647 = resq_wr1;	// L2610
      sb_ix1[4] = v1647;	// L2611
      sb_cmp1[4] = 0;	// L2612
      int32_t v1648 = op1;	// L2613
      bool v1649 = v1648 == 8;	// L2614
      bool v1650 = v1648 == 9;	// L2615
      bool v1651 = v1649 | v1650;	// L2616
      if (v1651) {	// L2617
        sb_cmp1[4] = 1;	// L2618
      }
      int32_t v1652 = is_rtr1;	// L2620
      int32_t rtrf1;	// L2621
      rtrf1 = v1652;	// L2622
      int32_t v1654 = is_cond1;	// L2623
      bool v1655 = v1654 == 1;	// L2624
      if (v1655) {	// L2625
        rtrf1 = 1;	// L2626
      }
      int32_t v1656 = rtrf1;	// L2628
      uint8_t v1657 = v1656;	// L2629
      sb_rtr1[4] = v1657;	// L2630
      int32_t v1658 = is_rtr1;	// L2631
      int32_t inj1;	// L2632
      inj1 = v1658;	// L2633
      int32_t v1660 = is_cond1;	// L2634
      bool v1661 = v1660 == 1;	// L2635
      int8_t v1662 = condition_reg1;	// L2636
      int32_t v1663 = v1662;	// L2637
      bool v1664 = v1663 == 1;	// L2638
      bool v1665 = v1661 & v1664;	// L2639
      if (v1665) {	// L2640
        inj1 = 1;	// L2641
      }
      int32_t v1666 = inj1;	// L2643
      uint8_t v1667 = v1666;	// L2644
      sb_inj1[4] = v1667;	// L2645
      int32_t v1668 = op1;	// L2646
      int32_t v1669 = v1668 & 3;	// L2647
      uint8_t v1670 = v1669;	// L2648
      sb_dir1[4] = v1670;	// L2649
      int32_t v1671 = s21;	// L2650
      uint8_t v1672 = v1671;	// L2651
      sb_id1[4] = v1672;	// L2652
      int32_t v1673 = res_vld1;	// L2653
      uint8_t v1674 = v1673;	// L2654
      sb_rvld1[4] = v1674;	// L2655
      int8_t v1675 = resq_wr1;	// L2656
      ap_int<33> v1676 = v1675;	// L2657
      ap_int<33> v1677 = v1676 + 1;	// L2658
      ap_int<33> v1678 = v1677 & 7;	// L2659
      uint8_t v1679 = v1678;	// L2660
      resq_wr1 = v1679;	// L2661
    }
    ap_int<17> v1680 = tx_n1;	// L2663
    txn_r1 = v1680;	// L2664
    ap_int<17> v1681 = tx_s1;	// L2665
    txs_r1 = v1681;	// L2666
    ap_int<17> v1682 = tx_w1;	// L2667
    txw_r1 = v1682;	// L2668
    ap_int<17> v1683 = tx_e1;	// L2669
    txe_r1 = v1683;	// L2670
    int32_t v1684 = crv_vld1;	// L2671
    bool v1685 = v1684 == 1;	// L2672
    if (v1685) {	// L2673
      int32_t v1686 = crv_mode1;	// L2674
      bool v1687 = v1686 == 1;	// L2675
      if (v1687) {	// L2676
        int32_t v1688 = crv_addr1;	// L2677
        int32_t v1689 = v1688 >> 3;	// L2678
        int32_t v1690 = v1689 & 1;	// L2679
        bool v1691 = v1690 == 1;	// L2680
        if (v1691) {	// L2681
          int32_t v1692 = crv_raw1;	// L2682
          int32_t v1693 = crv_addr1;	// L2683
          int32_t v1694 = v1693 & 7;	// L2684
          int v1695 = v1694;	// L2685
          irf1[v1695] = v1692;	// L2686
        } else {
          int32_t v1696 = crv_addr1;	// L2688
          bool v1697 = v1696 == 0;	// L2689
          if (v1697) {	// L2690
            int32_t v1698 = crv_raw1;	// L2691
            int32_t v1699 = v1698 & 255;	// L2692
            dsmask1 = v1699;	// L2693
            int32_t v1700 = crv_raw1;	// L2694
            int32_t v1701 = v1700 >> 8;	// L2695
            int32_t v1702 = v1701 & 7;	// L2696
            cfg_isz1 = v1702;	// L2697
            int32_t v1703 = crv_raw1;	// L2698
            int32_t v1704 = v1703 >> 15;	// L2699
            int32_t v1705 = v1704 & 1;	// L2700
            bool v1706 = v1705 == 1;	// L2701
            if (v1706) {	// L2702
              fetch_en1 = 1;	// L2703
              instr_cnt1 = 0;	// L2704
              iter_cnt1 = 0;	// L2705
            }
          } else {
            int32_t v1707 = crv_addr1;	// L2708
            bool v1708 = v1707 == 1;	// L2709
            if (v1708) {	// L2710
              int32_t v1709 = crv_raw1;	// L2711
              int32_t v1710 = v1709 & 255;	// L2712
              cfg_itsz1 = v1710;	// L2713
            }
          }
        }
      } else {
        int32_t v1711 = crv_addr1;	// L2718
        bool v1712 = v1711 < 8;	// L2719
        int32_t v1713 = dsmask1;	// L2720
        int32_t v1714 = v1713 >> v1711;	// L2721
        int32_t v1715 = v1714 & 1;	// L2722
        bool v1716 = v1715 == 1;	// L2723
        bool v1717 = v1712 & v1716;	// L2724
        if (v1717) {	// L2725
          int32_t v1718 = crv_addr1;	// L2726
          int v1719 = v1718;	// L2727
          int32_t v1720 = drf_full1[v1719];	// L2728
          bool v1721 = v1720 == 0;	// L2729
          if (v1721) {	// L2730
            half v1722 = crv_data1;	// L2731
            int32_t v1723 = crv_addr1;	// L2732
            int v1724 = v1723;	// L2733
            drf1[v1724] = v1722;	// L2734
            int32_t v1725 = crv_addr1;	// L2735
            int v1726 = v1725;	// L2736
            drf_full1[v1726] = 1;	// L2737
          }
        } else {
          half v1727 = crv_data1;	// L2740
          int32_t v1728 = crv_addr1;	// L2741
          int v1729 = v1728;	// L2742
          drf1[v1729] = v1727;	// L2743
        }
      }
    }
    ap_int<17> v1730 = txe_r1;	// L2747
    bool v1731;
    ap_int<17> v1731_tmp = v1730;
    v1731 = v1731_tmp[0];	// L2748
    int32_t v1732 = v1731;	// L2749
    bool v1733 = v1732 == 1;	// L2750
    if (v1733) {	// L2751
      ap_int<17> v1734 = txe_r1;	// L2752
      v887.write(v1734);	// L2753
    }
    ap_int<17> v1735 = txw_r1;	// L2755
    bool v1736;
    ap_int<17> v1736_tmp = v1735;
    v1736 = v1736_tmp[0];	// L2756
    int32_t v1737 = v1736;	// L2757
    bool v1738 = v1737 == 1;	// L2758
    if (v1738) {	// L2759
      ap_int<17> v1739 = txw_r1;	// L2760
      v888.write(v1739);	// L2761
    }
    ap_int<17> v1740 = txs_r1;	// L2763
    bool v1741;
    ap_int<17> v1741_tmp = v1740;
    v1741 = v1741_tmp[0];	// L2764
    int32_t v1742 = v1741;	// L2765
    bool v1743 = v1742 == 1;	// L2766
    if (v1743) {	// L2767
      ap_int<17> v1744 = txs_r1;	// L2768
      v889.write(v1744);	// L2769
    }
    ap_int<17> v1745 = txn_r1;	// L2771
    bool v1746;
    ap_int<17> v1746_tmp = v1745;
    v1746 = v1746_tmp[0];	// L2772
    int32_t v1747 = v1746;	// L2773
    bool v1748 = v1747 == 1;	// L2774
    if (v1748) {	// L2775
      ap_int<17> v1749 = txn_r1;	// L2776
      v890.write(v1749);	// L2777
    }
  }
}

void node_0_2(
  hls::stream< ap_uint<26> >& v1750,
  hls::stream< ap_uint<26> >& v1751,
  hls::stream< ap_uint<26> >& v1752,
  hls::stream< ap_uint<26> >& v1753,
  hls::stream< ap_uint<26> >& v1754,
  hls::stream< ap_uint<26> >& v1755,
  hls::stream< ap_uint<26> >& v1756,
  hls::stream< ap_uint<26> >& v1757,
  hls::stream< ap_uint<17> >& v1758,
  hls::stream< ap_uint<17> >& v1759,
  hls::stream< ap_uint<17> >& v1760,
  hls::stream< ap_uint<17> >& v1761,
  hls::stream< ap_uint<17> >& v1762,
  hls::stream< ap_uint<17> >& v1763,
  hls::stream< ap_uint<17> >& v1764,
  hls::stream< ap_uint<17> >& v1765
) {	// L2782
  int32_t irf2[8];	// L2815
  #pragma HLS array_partition variable=irf2 complete dim=1

  for (int v1767 = 0; v1767 < 8; v1767++) {	// L2816
    irf2[v1767] = 0;	// L2816
  }
  half drf2[8];	// L2817
  #pragma HLS array_partition variable=drf2 complete dim=1

  for (int v1769 = 0; v1769 < 8; v1769++) {	// L2818
    drf2[v1769] = 0.000000;	// L2818
  }
  int32_t drf_full2[8];	// L2819
  #pragma HLS array_partition variable=drf_full2 complete dim=1

  for (int v1771 = 0; v1771 < 8; v1771++) {	// L2820
    drf_full2[v1771] = 0;	// L2820
  }
  int32_t dsmask2;	// L2821
  dsmask2 = 0;	// L2822
  int32_t crv_vld2;	// L2823
  crv_vld2 = 0;	// L2824
  half crv_data2;	// L2825
  crv_data2 = 0.000000;	// L2826
  int32_t crv_addr2;	// L2827
  crv_addr2 = 0;	// L2828
  int32_t crv_mode2;	// L2829
  crv_mode2 = 0;	// L2830
  int32_t crv_raw2;	// L2831
  crv_raw2 = 0;	// L2832
  int32_t csd_vld2;	// L2833
  csd_vld2 = 0;	// L2834
  ap_uint<26> csd_pkt2;	// L2835
  csd_pkt2 = 0;	// L2836
  int32_t csd_dir2;	// L2837
  csd_dir2 = 0;	// L2838
  int32_t row_id2;	// L2839
  row_id2 = 0;	// L2840
  int32_t col_id2;	// L2841
  col_id2 = 2;	// L2842
  ap_uint<17> txn_r2;	// L2843
  txn_r2 = 0;	// L2844
  ap_uint<17> txs_r2;	// L2845
  txs_r2 = 0;	// L2846
  ap_uint<17> txw_r2;	// L2847
  txw_r2 = 0;	// L2848
  ap_uint<17> txe_r2;	// L2849
  txe_r2 = 0;	// L2850
  half hold_v2[4][2];	// L2851
  #pragma HLS array_partition variable=hold_v2 complete dim=1
  #pragma HLS array_partition variable=hold_v2 complete dim=2

  for (int v1788 = 0; v1788 < 4; v1788++) {	// L2852
    for (int v1789 = 0; v1789 < 2; v1789++) {	// L2852
      hold_v2[v1788][v1789] = 0.000000;	// L2852
    }
  }
  uint8_t hold_cnt2[4];	// L2853
  #pragma HLS array_partition variable=hold_cnt2 complete dim=1

  for (int v1791 = 0; v1791 < 4; v1791++) {	// L2854
    hold_cnt2[v1791] = 0;	// L2854
  }
  int32_t crv_ever2;	// L2855
  crv_ever2 = 0;	// L2856
  int32_t fe_ever2;	// L2857
  fe_ever2 = 0;	// L2858
  ap_uint<26> rbuf2[4][2];	// L2859
  #pragma HLS array_partition variable=rbuf2 complete dim=1
  #pragma HLS array_partition variable=rbuf2 complete dim=2

  for (int v1795 = 0; v1795 < 4; v1795++) {	// L2860
    for (int v1796 = 0; v1796 < 2; v1796++) {	// L2860
      rbuf2[v1795][v1796] = 0;	// L2860
    }
  }
  uint8_t rbcnt2[4];	// L2861
  #pragma HLS array_partition variable=rbcnt2 complete dim=1

  for (int v1798 = 0; v1798 < 4; v1798++) {	// L2862
    rbcnt2[v1798] = 0;	// L2862
  }
  int32_t cfg_isz2;	// L2863
  cfg_isz2 = 0;	// L2864
  int32_t cfg_itsz2;	// L2865
  cfg_itsz2 = 0;	// L2866
  uint8_t fetch_en2;	// L2867
  fetch_en2 = 0;	// L2868
  uint8_t instr_cnt2;	// L2869
  instr_cnt2 = 0;	// L2870
  uint8_t iter_cnt2;	// L2871
  iter_cnt2 = 0;	// L2872
  uint8_t condition_reg2;	// L2873
  condition_reg2 = 0;	// L2874
  uint8_t sb_v2[5];	// L2875
  #pragma HLS array_partition variable=sb_v2 complete dim=1

  for (int v1806 = 0; v1806 < 5; v1806++) {	// L2876
    sb_v2[v1806] = 0;	// L2876
  }
  uint8_t sb_dst2[5];	// L2877
  #pragma HLS array_partition variable=sb_dst2 complete dim=1

  for (int v1808 = 0; v1808 < 5; v1808++) {	// L2878
    sb_dst2[v1808] = 0;	// L2878
  }
  uint8_t sb_cmp2[5];	// L2879
  #pragma HLS array_partition variable=sb_cmp2 complete dim=1

  for (int v1810 = 0; v1810 < 5; v1810++) {	// L2880
    sb_cmp2[v1810] = 0;	// L2880
  }
  uint8_t sb_rtr2[5];	// L2881
  #pragma HLS array_partition variable=sb_rtr2 complete dim=1

  for (int v1812 = 0; v1812 < 5; v1812++) {	// L2882
    sb_rtr2[v1812] = 0;	// L2882
  }
  uint8_t sb_inj2[5];	// L2883
  #pragma HLS array_partition variable=sb_inj2 complete dim=1

  for (int v1814 = 0; v1814 < 5; v1814++) {	// L2884
    sb_inj2[v1814] = 0;	// L2884
  }
  uint8_t sb_dir2[5];	// L2885
  #pragma HLS array_partition variable=sb_dir2 complete dim=1

  for (int v1816 = 0; v1816 < 5; v1816++) {	// L2886
    sb_dir2[v1816] = 0;	// L2886
  }
  uint8_t sb_id2[5];	// L2887
  #pragma HLS array_partition variable=sb_id2 complete dim=1

  for (int v1818 = 0; v1818 < 5; v1818++) {	// L2888
    sb_id2[v1818] = 0;	// L2888
  }
  uint8_t sb_rvld2[5];	// L2889
  #pragma HLS array_partition variable=sb_rvld2 complete dim=1

  for (int v1820 = 0; v1820 < 5; v1820++) {	// L2890
    sb_rvld2[v1820] = 0;	// L2890
  }
  uint8_t sb_ix2[5];	// L2891
  #pragma HLS array_partition variable=sb_ix2 complete dim=1

  for (int v1822 = 0; v1822 < 5; v1822++) {	// L2892
    sb_ix2[v1822] = 0;	// L2892
  }
  half resq2[8];	// L2893
  #pragma HLS array_partition variable=resq2 complete dim=1
#pragma HLS dependence variable=resq2 type=inter dependent=false

  for (int v1824 = 0; v1824 < 8; v1824++) {	// L2894
    resq2[v1824] = 0.000000;	// L2894
  }
  uint8_t cmpq2[8];	// L2895
  #pragma HLS array_partition variable=cmpq2 complete dim=1
#pragma HLS dependence variable=cmpq2 type=inter dependent=false

  for (int v1826 = 0; v1826 < 8; v1826++) {	// L2896
    cmpq2[v1826] = 0;	// L2896
  }
  uint8_t resq_wr2;	// L2897
  resq_wr2 = 0;	// L2898
  l_S_t_0_t2: for (int t2 = 0; t2 < 374; t2++) {	// L2899
  #pragma HLS pipeline II=1
    ap_uint<26> p_w2;	// L2900
    p_w2 = 0;	// L2901
    ap_uint<26> p_e2;	// L2902
    p_e2 = 0;	// L2903
    ap_uint<26> p_n2;	// L2904
    p_n2 = 0;	// L2905
    ap_uint<26> p_s2;	// L2906
    p_s2 = 0;	// L2907
    uint8_t v1833 = rbcnt2[0];	// L2908
    int32_t v1834 = v1833;	// L2909
    bool v1835 = v1834 < 2;	// L2910
    if (v1835) {	// L2911
      ap_uint<26> v1836;
      bool v1837 = v1750.read_nb(v1836);
	// L2912
      ap_uint<26> gw2;	// L2913
      gw2 = v1836;	// L2914
      bool okw2;	// L2915
      okw2 = v1837;	// L2916
      bool v1840 = okw2;	// L2917
      if (v1840) {	// L2918
        ap_int<26> v1841 = gw2;	// L2919
        p_w2 = v1841;	// L2920
      }
    }
    uint8_t v1842 = rbcnt2[1];	// L2923
    int32_t v1843 = v1842;	// L2924
    bool v1844 = v1843 < 2;	// L2925
    if (v1844) {	// L2926
      ap_uint<26> v1845;
      bool v1846 = v1751.read_nb(v1845);
	// L2927
      ap_uint<26> ge2;	// L2928
      ge2 = v1845;	// L2929
      bool oke2;	// L2930
      oke2 = v1846;	// L2931
      bool v1849 = oke2;	// L2932
      if (v1849) {	// L2933
        ap_int<26> v1850 = ge2;	// L2934
        p_e2 = v1850;	// L2935
      }
    }
    uint8_t v1851 = rbcnt2[2];	// L2938
    int32_t v1852 = v1851;	// L2939
    bool v1853 = v1852 < 2;	// L2940
    if (v1853) {	// L2941
      ap_uint<26> v1854;
      bool v1855 = v1752.read_nb(v1854);
	// L2942
      ap_uint<26> gn2;	// L2943
      gn2 = v1854;	// L2944
      bool okn2;	// L2945
      okn2 = v1855;	// L2946
      bool v1858 = okn2;	// L2947
      if (v1858) {	// L2948
        ap_int<26> v1859 = gn2;	// L2949
        p_n2 = v1859;	// L2950
      }
    }
    uint8_t v1860 = rbcnt2[3];	// L2953
    int32_t v1861 = v1860;	// L2954
    bool v1862 = v1861 < 2;	// L2955
    if (v1862) {	// L2956
      ap_uint<26> v1863;
      bool v1864 = v1753.read_nb(v1863);
	// L2957
      ap_uint<26> gs2;	// L2958
      gs2 = v1863;	// L2959
      bool oks2;	// L2960
      oks2 = v1864;	// L2961
      bool v1867 = oks2;	// L2962
      if (v1867) {	// L2963
        ap_int<26> v1868 = gs2;	// L2964
        p_s2 = v1868;	// L2965
      }
    }
    ap_uint<26> fin2[4];	// L2968
    for (int v1870 = 0; v1870 < 4; v1870++) {	// L2969
      fin2[v1870] = 0;	// L2969
    }
    ap_int<26> v1871 = p_w2;	// L2970
    fin2[0] = v1871;	// L2971
    ap_int<26> v1872 = p_e2;	// L2972
    fin2[1] = v1872;	// L2973
    ap_int<26> v1873 = p_n2;	// L2974
    fin2[2] = v1873;	// L2975
    ap_int<26> v1874 = p_s2;	// L2976
    fin2[3] = v1874;	// L2977
    l_S_d_0_d8: for (int d8 = 0; d8 < 4; d8++) {	// L2978
      ap_uint<26> v1876 = fin2[d8];	// L2979
      bool v1877;
      ap_int<26> v1877_tmp = v1876;
      v1877 = v1877_tmp[25];	// L2980
      int32_t v1878 = v1877;	// L2981
      bool v1879 = v1878 == 1;	// L2982
      uint8_t v1880 = rbcnt2[d8];	// L2983
      int32_t v1881 = v1880;	// L2984
      bool v1882 = v1881 < 2;	// L2985
      bool v1883 = v1879 & v1882;	// L2986
      if (v1883) {	// L2987
        ap_uint<26> v1884 = fin2[d8];	// L2988
        uint8_t v1885 = rbcnt2[d8];	// L2989
        int v1886 = v1885;	// L2990
        rbuf2[d8][v1886] = v1884;	// L2991
        uint8_t v1887 = rbcnt2[d8];	// L2992
        ap_int<33> v1888 = v1887;	// L2993
        ap_int<33> v1889 = v1888 + 1;	// L2994
        uint8_t v1890 = v1889;	// L2995
        rbcnt2[d8] = v1890;	// L2996
      }
    }
    ap_uint<26> hd2[4];	// L2999
    for (int v1892 = 0; v1892 < 4; v1892++) {	// L3000
      hd2[v1892] = 0;	// L3000
    }
    int32_t hvld2[4];	// L3001
    for (int v1894 = 0; v1894 < 4; v1894++) {	// L3002
      hvld2[v1894] = 0;	// L3002
    }
    int32_t hit2[4];	// L3003
    for (int v1896 = 0; v1896 < 4; v1896++) {	// L3004
      hit2[v1896] = 0;	// L3004
    }
    int32_t axis2[4];	// L3005
    for (int v1898 = 0; v1898 < 4; v1898++) {	// L3006
      axis2[v1898] = 0;	// L3006
    }
    int32_t v1899 = col_id2;	// L3007
    axis2[0] = v1899;	// L3008
    int32_t v1900 = col_id2;	// L3009
    axis2[1] = v1900;	// L3010
    int32_t v1901 = row_id2;	// L3011
    axis2[2] = v1901;	// L3012
    int32_t v1902 = row_id2;	// L3013
    axis2[3] = v1902;	// L3014
    l_S_d_1_d9: for (int d9 = 0; d9 < 4; d9++) {	// L3015
      uint8_t v1904 = rbcnt2[d9];	// L3016
      int32_t v1905 = v1904;	// L3017
      bool v1906 = v1905 > 0;	// L3018
      if (v1906) {	// L3019
        ap_uint<26> v1907 = rbuf2[d9][0];	// L3020
        hd2[d9] = v1907;	// L3021
        hvld2[d9] = 1;	// L3022
        ap_uint<26> v1908 = hd2[d9];	// L3023
        ap_int<4> v1909;
        ap_int<26> v1909_tmp = v1908;
        v1909 = v1909_tmp(24, 21);	// L3024
        int32_t v1910 = axis2[d9];	// L3025
        int32_t v1911 = v1909;	// L3026
        bool v1912 = v1911 == v1910;	// L3027
        if (v1912) {	// L3028
          hit2[d9] = 1;	// L3029
        }
      }
    }
    ap_uint<26> o_crv2;	// L3033
    o_crv2 = 0;	// L3034
    int32_t crv_in2;	// L3035
    crv_in2 = -1;	// L3036
    int32_t v1915 = hit2[3];	// L3037
    bool v1916 = v1915 == 1;	// L3038
    if (v1916) {	// L3039
      ap_uint<26> v1917 = hd2[3];	// L3040
      o_crv2 = v1917;	// L3041
      crv_in2 = 3;	// L3042
    } else {
      int32_t v1918 = hit2[2];	// L3044
      bool v1919 = v1918 == 1;	// L3045
      if (v1919) {	// L3046
        ap_uint<26> v1920 = hd2[2];	// L3047
        o_crv2 = v1920;	// L3048
        crv_in2 = 2;	// L3049
      } else {
        int32_t v1921 = hit2[1];	// L3051
        bool v1922 = v1921 == 1;	// L3052
        if (v1922) {	// L3053
          ap_uint<26> v1923 = hd2[1];	// L3054
          o_crv2 = v1923;	// L3055
          crv_in2 = 1;	// L3056
        } else {
          int32_t v1924 = hit2[0];	// L3058
          bool v1925 = v1924 == 1;	// L3059
          if (v1925) {	// L3060
            ap_uint<26> v1926 = hd2[0];	// L3061
            o_crv2 = v1926;	// L3062
            crv_in2 = 0;	// L3063
          }
        }
      }
    }
    int32_t pop2[4];	// L3068
    for (int v1928 = 0; v1928 < 4; v1928++) {	// L3069
      pop2[v1928] = 0;	// L3069
    }
    int32_t inj_done2;	// L3070
    inj_done2 = 0;	// L3071
    int32_t idir2;	// L3072
    idir2 = -1;	// L3073
    ap_int<26> v1931 = csd_pkt2;	// L3074
    bool v1932;
    ap_int<26> v1932_tmp = v1931;
    v1932 = v1932_tmp[25];	// L3075
    int32_t v1933 = v1932;	// L3076
    bool v1934 = v1933 == 1;	// L3077
    if (v1934) {	// L3078
      int32_t v1935 = csd_dir2;	// L3079
      ap_int<33> v1936 = v1935;	// L3080
      ap_int<33> v1937 = 3 - v1936;	// L3081
      int32_t v1938 = v1937;	// L3082
      idir2 = v1938;	// L3083
    }
    int32_t v1939 = idir2;	// L3085
    bool v1940 = v1939 == 0;	// L3086
    if (v1940) {	// L3087
      ap_int<26> v1941 = csd_pkt2;	// L3088
      bool v1942 = v1754.write_nb(v1941);
	// L3089
      if (v1942) {	// L3090
        inj_done2 = 1;	// L3091
      }
    } else {
      int32_t v1943 = hvld2[0];	// L3094
      bool v1944 = v1943 == 1;	// L3095
      int32_t v1945 = hit2[0];	// L3096
      bool v1946 = v1945 == 0;	// L3097
      bool v1947 = v1944 & v1946;	// L3098
      if (v1947) {	// L3099
        ap_uint<26> v1948 = hd2[0];	// L3100
        bool v1949 = v1754.write_nb(v1948);
	// L3101
        if (v1949) {	// L3102
          pop2[0] = 1;	// L3103
        }
      }
    }
    int32_t v1950 = idir2;	// L3107
    bool v1951 = v1950 == 1;	// L3108
    if (v1951) {	// L3109
      ap_int<26> v1952 = csd_pkt2;	// L3110
      bool v1953 = v1755.write_nb(v1952);
	// L3111
      if (v1953) {	// L3112
        inj_done2 = 1;	// L3113
      }
    } else {
      int32_t v1954 = hvld2[1];	// L3116
      bool v1955 = v1954 == 1;	// L3117
      int32_t v1956 = hit2[1];	// L3118
      bool v1957 = v1956 == 0;	// L3119
      bool v1958 = v1955 & v1957;	// L3120
      if (v1958) {	// L3121
        ap_uint<26> v1959 = hd2[1];	// L3122
        bool v1960 = v1755.write_nb(v1959);
	// L3123
        if (v1960) {	// L3124
          pop2[1] = 1;	// L3125
        }
      }
    }
    int32_t v1961 = idir2;	// L3129
    bool v1962 = v1961 == 2;	// L3130
    if (v1962) {	// L3131
      ap_int<26> v1963 = csd_pkt2;	// L3132
      bool v1964 = v1756.write_nb(v1963);
	// L3133
      if (v1964) {	// L3134
        inj_done2 = 1;	// L3135
      }
    } else {
      int32_t v1965 = hvld2[2];	// L3138
      bool v1966 = v1965 == 1;	// L3139
      int32_t v1967 = hit2[2];	// L3140
      bool v1968 = v1967 == 0;	// L3141
      bool v1969 = v1966 & v1968;	// L3142
      if (v1969) {	// L3143
        ap_uint<26> v1970 = hd2[2];	// L3144
        bool v1971 = v1756.write_nb(v1970);
	// L3145
        if (v1971) {	// L3146
          pop2[2] = 1;	// L3147
        }
      }
    }
    int32_t v1972 = idir2;	// L3151
    bool v1973 = v1972 == 3;	// L3152
    if (v1973) {	// L3153
      ap_int<26> v1974 = csd_pkt2;	// L3154
      bool v1975 = v1757.write_nb(v1974);
	// L3155
      if (v1975) {	// L3156
        inj_done2 = 1;	// L3157
      }
    } else {
      int32_t v1976 = hvld2[3];	// L3160
      bool v1977 = v1976 == 1;	// L3161
      int32_t v1978 = hit2[3];	// L3162
      bool v1979 = v1978 == 0;	// L3163
      bool v1980 = v1977 & v1979;	// L3164
      if (v1980) {	// L3165
        ap_uint<26> v1981 = hd2[3];	// L3166
        bool v1982 = v1757.write_nb(v1981);
	// L3167
        if (v1982) {	// L3168
          pop2[3] = 1;	// L3169
        }
      }
    }
    int32_t v1983 = crv_in2;	// L3173
    bool v1984 = v1983 >= 0;	// L3174
    if (v1984) {	// L3175
      int32_t v1985 = crv_in2;	// L3176
      int v1986 = v1985;	// L3177
      pop2[v1986] = 1;	// L3178
    }
    l_S_d_2_d10: for (int d10 = 0; d10 < 4; d10++) {	// L3180
      int32_t v1988 = pop2[d10];	// L3181
      bool v1989 = v1988 == 1;	// L3182
      if (v1989) {	// L3183
        l_S_sft_2_sft2: for (int sft2 = 0; sft2 < 1; sft2++) {	// L3184
          ap_uint<26> v1991 = rbuf2[d10][(sft2 + 1)];	// L3185
          rbuf2[d10][sft2] = v1991;	// L3186
        }
        uint8_t v1992 = rbcnt2[d10];	// L3188
        ap_int<33> v1993 = v1992;	// L3189
        ap_int<33> v1994 = v1993 - 1;	// L3190
        uint8_t v1995 = v1994;	// L3191
        rbcnt2[d10] = v1995;	// L3192
      }
    }
    int32_t v1996 = inj_done2;	// L3195
    bool v1997 = v1996 == 1;	// L3196
    if (v1997) {	// L3197
      csd_pkt2 = 0;	// L3198
    }
    ap_int<26> v1998 = o_crv2;	// L3200
    bool v1999;
    ap_int<26> v1999_tmp = v1998;
    v1999 = v1999_tmp[25];	// L3201
    int32_t v2000 = v1999;	// L3202
    crv_vld2 = v2000;	// L3203
    int32_t v2001 = crv_vld2;	// L3204
    bool v2002 = v2001 == 1;	// L3205
    if (v2002) {	// L3206
      crv_ever2 = 1;	// L3207
    }
    ap_int<26> v2003 = o_crv2;	// L3209
    int16_t v2004;
    ap_int<26> v2004_tmp = v2003;
    v2004 = v2004_tmp(15, 0);	// L3210
    half v2005;
    union { uint16_t from; half to;} _converter_v2004_to_v2005 = {};
    _converter_v2004_to_v2005.from = v2004;
    v2005 = _converter_v2004_to_v2005.to;	// L3211
    crv_data2 = v2005;	// L3212
    ap_int<26> v2006 = o_crv2;	// L3213
    ap_int<4> v2007;
    ap_int<26> v2007_tmp = v2006;
    v2007 = v2007_tmp(19, 16);	// L3214
    int32_t v2008 = v2007;	// L3215
    crv_addr2 = v2008;	// L3216
    ap_int<26> v2009 = o_crv2;	// L3217
    bool v2010;
    ap_int<26> v2010_tmp = v2009;
    v2010 = v2010_tmp[20];	// L3218
    int32_t v2011 = v2010;	// L3219
    crv_mode2 = v2011;	// L3220
    ap_int<26> v2012 = o_crv2;	// L3221
    int16_t v2013;
    ap_int<26> v2013_tmp = v2012;
    v2013 = v2013_tmp(15, 0);	// L3222
    int32_t v2014 = v2013;	// L3223
    crv_raw2 = v2014;	// L3224
    half rxv2[4];	// L3225
    for (int v2016 = 0; v2016 < 4; v2016++) {	// L3226
      rxv2[v2016] = 0.000000;	// L3226
    }
    int32_t rxvld2[4];	// L3227
    for (int v2018 = 0; v2018 < 4; v2018++) {	// L3228
      rxvld2[v2018] = 0;	// L3228
    }
    uint8_t v2019 = hold_cnt2[0];	// L3229
    int32_t v2020 = v2019;	// L3230
    bool v2021 = v2020 < 2;	// L3231
    if (v2021) {	// L3232
      ap_uint<17> v2022;
      bool v2023 = v1758.read_nb(v2022);
	// L3233
      ap_uint<17> sgn2;	// L3234
      sgn2 = v2022;	// L3235
      bool sqn2;	// L3236
      sqn2 = v2023;	// L3237
      bool v2026 = sqn2;	// L3238
      int32_t v2027 = v2026;	// L3239
      bool v2028 = v2027 == 1;	// L3240
      if (v2028) {	// L3241
        ap_int<17> v2029 = sgn2;	// L3242
        int16_t v2030;
        ap_int<17> v2030_tmp = v2029;
        v2030 = v2030_tmp(16, 1);	// L3243
        half v2031;
        union { uint16_t from; half to;} _converter_v2030_to_v2031 = {};
        _converter_v2030_to_v2031.from = v2030;
        v2031 = _converter_v2030_to_v2031.to;	// L3244
        rxv2[0] = v2031;	// L3245
        rxvld2[0] = 1;	// L3246
      }
    }
    uint8_t v2032 = hold_cnt2[1];	// L3249
    int32_t v2033 = v2032;	// L3250
    bool v2034 = v2033 < 2;	// L3251
    if (v2034) {	// L3252
      ap_uint<17> v2035;
      bool v2036 = v1759.read_nb(v2035);
	// L3253
      ap_uint<17> sgs2;	// L3254
      sgs2 = v2035;	// L3255
      bool sqs2;	// L3256
      sqs2 = v2036;	// L3257
      bool v2039 = sqs2;	// L3258
      int32_t v2040 = v2039;	// L3259
      bool v2041 = v2040 == 1;	// L3260
      if (v2041) {	// L3261
        ap_int<17> v2042 = sgs2;	// L3262
        int16_t v2043;
        ap_int<17> v2043_tmp = v2042;
        v2043 = v2043_tmp(16, 1);	// L3263
        half v2044;
        union { uint16_t from; half to;} _converter_v2043_to_v2044 = {};
        _converter_v2043_to_v2044.from = v2043;
        v2044 = _converter_v2043_to_v2044.to;	// L3264
        rxv2[1] = v2044;	// L3265
        rxvld2[1] = 1;	// L3266
      }
    }
    uint8_t v2045 = hold_cnt2[2];	// L3269
    int32_t v2046 = v2045;	// L3270
    bool v2047 = v2046 < 2;	// L3271
    if (v2047) {	// L3272
      ap_uint<17> v2048;
      bool v2049 = v1760.read_nb(v2048);
	// L3273
      ap_uint<17> sgw2;	// L3274
      sgw2 = v2048;	// L3275
      bool sqw2;	// L3276
      sqw2 = v2049;	// L3277
      bool v2052 = sqw2;	// L3278
      int32_t v2053 = v2052;	// L3279
      bool v2054 = v2053 == 1;	// L3280
      if (v2054) {	// L3281
        ap_int<17> v2055 = sgw2;	// L3282
        int16_t v2056;
        ap_int<17> v2056_tmp = v2055;
        v2056 = v2056_tmp(16, 1);	// L3283
        half v2057;
        union { uint16_t from; half to;} _converter_v2056_to_v2057 = {};
        _converter_v2056_to_v2057.from = v2056;
        v2057 = _converter_v2056_to_v2057.to;	// L3284
        rxv2[2] = v2057;	// L3285
        rxvld2[2] = 1;	// L3286
      }
    }
    uint8_t v2058 = hold_cnt2[3];	// L3289
    int32_t v2059 = v2058;	// L3290
    bool v2060 = v2059 < 2;	// L3291
    if (v2060) {	// L3292
      ap_uint<17> v2061;
      bool v2062 = v1761.read_nb(v2061);
	// L3293
      ap_uint<17> sge2;	// L3294
      sge2 = v2061;	// L3295
      bool sqe2;	// L3296
      sqe2 = v2062;	// L3297
      bool v2065 = sqe2;	// L3298
      int32_t v2066 = v2065;	// L3299
      bool v2067 = v2066 == 1;	// L3300
      if (v2067) {	// L3301
        ap_int<17> v2068 = sge2;	// L3302
        int16_t v2069;
        ap_int<17> v2069_tmp = v2068;
        v2069 = v2069_tmp(16, 1);	// L3303
        half v2070;
        union { uint16_t from; half to;} _converter_v2069_to_v2070 = {};
        _converter_v2069_to_v2070.from = v2069;
        v2070 = _converter_v2069_to_v2070.to;	// L3304
        rxv2[3] = v2070;	// L3305
        rxvld2[3] = 1;	// L3306
      }
    }
    l_S_d_4_d11: for (int d11 = 0; d11 < 4; d11++) {	// L3309
      int32_t v2072 = rxvld2[d11];	// L3310
      bool v2073 = v2072 == 1;	// L3311
      if (v2073) {	// L3312
        half v2074 = rxv2[d11];	// L3313
        uint8_t v2075 = hold_cnt2[d11];	// L3314
        int v2076 = v2075;	// L3315
        hold_v2[d11][v2076] = v2074;	// L3316
        uint8_t v2077 = hold_cnt2[d11];	// L3317
        ap_int<33> v2078 = v2077;	// L3318
        ap_int<33> v2079 = v2078 + 1;	// L3319
        uint8_t v2080 = v2079;	// L3320
        hold_cnt2[d11] = v2080;	// L3321
      }
    }
    ap_uint<17> tx_n2;	// L3324
    tx_n2 = 0;	// L3325
    ap_uint<17> tx_s2;	// L3326
    tx_s2 = 0;	// L3327
    ap_uint<17> tx_w2;	// L3328
    tx_w2 = 0;	// L3329
    ap_uint<17> tx_e2;	// L3330
    tx_e2 = 0;	// L3331
    uint8_t v2085 = sb_v2[0];	// L3332
    int32_t v2086 = v2085;	// L3333
    bool v2087 = v2086 == 1;	// L3334
    if (v2087) {	// L3335
      uint8_t v2088 = sb_ix2[0];	// L3336
      int v2089 = v2088;	// L3337
      half v2090 = resq2[v2089];	// L3338
      half wb2;
#pragma HLS dependence variable=wb2 type=inter dependent=false	// L3339
      wb2 = v2090;	// L3340
      uint8_t v2092 = sb_cmp2[0];	// L3341
      int32_t v2093 = v2092;	// L3342
      bool v2094 = v2093 == 1;	// L3343
      if (v2094) {	// L3344
        uint8_t v2095 = sb_ix2[0];	// L3345
        int v2096 = v2095;	// L3346
        uint8_t v2097 = cmpq2[v2096];	// L3347
        condition_reg2 = v2097;	// L3348
      }
      uint8_t v2098 = sb_rtr2[0];	// L3350
      int32_t v2099 = v2098;	// L3351
      bool v2100 = v2099 == 1;	// L3352
      if (v2100) {	// L3353
        uint8_t v2101 = sb_inj2[0];	// L3354
        int32_t v2102 = v2101;	// L3355
        bool v2103 = v2102 == 1;	// L3356
        ap_int<26> v2104 = csd_pkt2;	// L3357
        bool v2105;
        ap_int<26> v2105_tmp = v2104;
        v2105 = v2105_tmp[25];	// L3358
        int32_t v2106 = v2105;	// L3359
        bool v2107 = v2106 == 0;	// L3360
        bool v2108 = v2103 & v2107;	// L3361
        if (v2108) {	// L3362
          half v2109 = wb2;	// L3363
          uint16_t v2110;
          union { half from; uint16_t to;} _converter_v2109_to_v2110 = {};
          _converter_v2109_to_v2110.from = v2109;
          v2110 = _converter_v2109_to_v2110.to;	// L3364
          ap_int<26> v2111 = csd_pkt2;	// L3365
          ap_int<26> v2112;
          ap_int<26> v2112_tmp = v2111;
          v2112_tmp(15, 0) = v2110;
          v2112 = v2112_tmp;	// L3366
          csd_pkt2 = v2112;	// L3367
          uint8_t v2113 = sb_dst2[0];	// L3368
          ap_uint<4> v2114 = v2113;	// L3369
          ap_int<26> v2115 = csd_pkt2;	// L3370
          ap_int<26> v2116;
          ap_int<26> v2116_tmp = v2115;
          v2116_tmp(19, 16) = v2114;
          v2116 = v2116_tmp;	// L3371
          csd_pkt2 = v2116;	// L3372
          uint8_t v2117 = sb_id2[0];	// L3373
          ap_uint<4> v2118 = v2117;	// L3374
          ap_int<26> v2119 = csd_pkt2;	// L3375
          ap_int<26> v2120;
          ap_int<26> v2120_tmp = v2119;
          v2120_tmp(24, 21) = v2118;
          v2120 = v2120_tmp;	// L3376
          csd_pkt2 = v2120;	// L3377
          uint8_t v2121 = sb_rvld2[0];	// L3378
          bool v2122 = v2121;	// L3379
          ap_int<26> v2123 = csd_pkt2;	// L3380
          ap_int<26> v2124;
          ap_int<26> v2124_tmp = v2123;
          v2124_tmp[25] = v2122;          v2124 = v2124_tmp;	// L3381
          csd_pkt2 = v2124;	// L3382
          uint8_t v2125 = sb_dir2[0];	// L3383
          int32_t v2126 = v2125;	// L3384
          csd_dir2 = v2126;	// L3385
        }
      } else {
        uint8_t v2127 = sb_dst2[0];	// L3388
        int32_t v2128 = v2127;	// L3389
        bool v2129 = v2128 >= 12;	// L3390
        if (v2129) {	// L3391
          ap_uint<17> tw02;	// L3392
          tw02 = 0;	// L3393
          uint8_t v2131 = sb_rvld2[0];	// L3394
          bool v2132 = v2131;	// L3395
          ap_int<17> v2133 = tw02;	// L3396
          ap_int<17> v2134;
          ap_int<17> v2134_tmp = v2133;
          v2134_tmp[0] = v2132;          v2134 = v2134_tmp;	// L3397
          tw02 = v2134;	// L3398
          half v2135 = wb2;	// L3399
          uint16_t v2136;
          union { half from; uint16_t to;} _converter_v2135_to_v2136 = {};
          _converter_v2135_to_v2136.from = v2135;
          v2136 = _converter_v2135_to_v2136.to;	// L3400
          ap_int<17> v2137 = tw02;	// L3401
          ap_int<17> v2138;
          ap_int<17> v2138_tmp = v2137;
          v2138_tmp(16, 1) = v2136;
          v2138 = v2138_tmp;	// L3402
          tw02 = v2138;	// L3403
          uint8_t v2139 = sb_dst2[0];	// L3404
          int32_t v2140 = v2139;	// L3405
          int32_t v2141 = v2140 & 3;	// L3406
          bool v2142 = v2141 == 0;	// L3407
          if (v2142) {	// L3408
            ap_int<17> v2143 = tw02;	// L3409
            tx_n2 = v2143;	// L3410
          } else {
            uint8_t v2144 = sb_dst2[0];	// L3412
            int32_t v2145 = v2144;	// L3413
            int32_t v2146 = v2145 & 3;	// L3414
            bool v2147 = v2146 == 1;	// L3415
            if (v2147) {	// L3416
              ap_int<17> v2148 = tw02;	// L3417
              tx_s2 = v2148;	// L3418
            } else {
              uint8_t v2149 = sb_dst2[0];	// L3420
              int32_t v2150 = v2149;	// L3421
              int32_t v2151 = v2150 & 3;	// L3422
              bool v2152 = v2151 == 2;	// L3423
              if (v2152) {	// L3424
                ap_int<17> v2153 = tw02;	// L3425
                tx_w2 = v2153;	// L3426
              } else {
                ap_int<17> v2154 = tw02;	// L3428
                tx_e2 = v2154;	// L3429
              }
            }
          }
        } else {
          uint8_t v2155 = sb_rvld2[0];	// L3434
          int32_t v2156 = v2155;	// L3435
          bool v2157 = v2156 == 1;	// L3436
          if (v2157) {	// L3437
            uint8_t v2158 = sb_dst2[0];	// L3438
            int32_t v2159 = v2158;	// L3439
            bool v2160 = v2159 < 8;	// L3440
            int32_t v2161 = dsmask2;	// L3441
            int32_t v2162 = v2161 >> v2159;	// L3442
            int32_t v2163 = v2162 & 1;	// L3443
            bool v2164 = v2163 == 1;	// L3444
            bool v2165 = v2160 & v2164;	// L3445
            if (v2165) {	// L3446
              uint8_t v2166 = sb_dst2[0];	// L3447
              int v2167 = v2166;	// L3448
              int32_t v2168 = drf_full2[v2167];	// L3449
              bool v2169 = v2168 == 0;	// L3450
              if (v2169) {	// L3451
                half v2170 = wb2;	// L3452
                uint8_t v2171 = sb_dst2[0];	// L3453
                int v2172 = v2171;	// L3454
                drf2[v2172] = v2170;	// L3455
                uint8_t v2173 = sb_dst2[0];	// L3456
                int v2174 = v2173;	// L3457
                drf_full2[v2174] = 1;	// L3458
              }
            } else {
              half v2175 = wb2;	// L3461
              uint8_t v2176 = sb_dst2[0];	// L3462
              int32_t v2177 = v2176;	// L3463
              int32_t v2178 = v2177 & 7;	// L3464
              int v2179 = v2178;	// L3465
              drf2[v2179] = v2175;	// L3466
            }
          }
        }
      }
    }
    int32_t pc2;	// L3472
    pc2 = -1;	// L3473
    int8_t v2181 = fetch_en2;	// L3474
    int32_t v2182 = v2181;	// L3475
    bool v2183 = v2182 == 1;	// L3476
    if (v2183) {	// L3477
      int8_t v2184 = instr_cnt2;	// L3478
      int32_t v2185 = v2184;	// L3479
      pc2 = v2185;	// L3480
    }
    int8_t v2186 = fetch_en2;	// L3482
    int32_t v2187 = v2186;	// L3483
    bool v2188 = v2187 == 1;	// L3484
    if (v2188) {	// L3485
      fe_ever2 = 1;	// L3486
    }
    int32_t instr2;	// L3488
    instr2 = 0;	// L3489
    int32_t v2190 = pc2;	// L3490
    bool v2191 = v2190 >= 0;	// L3491
    if (v2191) {	// L3492
      int32_t v2192 = pc2;	// L3493
      int v2193 = v2192;	// L3494
      int32_t v2194 = irf2[v2193];	// L3495
      instr2 = v2194;	// L3496
    }
    int32_t v2195 = instr2;	// L3498
    int32_t v2196 = v2195 & 15;	// L3499
    int32_t op2;	// L3500
    op2 = v2196;	// L3501
    int32_t v2198 = instr2;	// L3502
    int32_t v2199 = v2198 >> 4;	// L3503
    int32_t v2200 = v2199 & 15;	// L3504
    int32_t dst2;	// L3505
    dst2 = v2200;	// L3506
    int32_t v2202 = instr2;	// L3507
    int32_t v2203 = v2202 >> 8;	// L3508
    int32_t v2204 = v2203 & 15;	// L3509
    int32_t s12;	// L3510
    s12 = v2204;	// L3511
    int32_t v2206 = instr2;	// L3512
    int32_t v2207 = v2206 >> 12;	// L3513
    int32_t v2208 = v2207 & 15;	// L3514
    int32_t s22;	// L3515
    s22 = v2208;	// L3516
    half a2;	// L3517
    a2 = 0.000000;	// L3518
    half b2;	// L3519
    b2 = 0.000000;	// L3520
    int32_t v2212 = s12;	// L3521
    bool v2213 = v2212 >= 12;	// L3522
    if (v2213) {	// L3523
      int32_t v2214 = s12;	// L3524
      int32_t v2215 = v2214 & 3;	// L3525
      int v2216 = v2215;	// L3526
      half v2217 = hold_v2[v2216][0];	// L3527
      a2 = v2217;	// L3528
    } else {
      int32_t v2218 = s12;	// L3530
      int v2219 = v2218;	// L3531
      half v2220 = drf2[v2219];	// L3532
      a2 = v2220;	// L3533
    }
    int32_t v2221 = s22;	// L3535
    bool v2222 = v2221 >= 12;	// L3536
    if (v2222) {	// L3537
      int32_t v2223 = s22;	// L3538
      int32_t v2224 = v2223 & 3;	// L3539
      int v2225 = v2224;	// L3540
      half v2226 = hold_v2[v2225][0];	// L3541
      b2 = v2226;	// L3542
    } else {
      int32_t v2227 = s22;	// L3544
      int v2228 = v2227;	// L3545
      half v2229 = drf2[v2228];	// L3546
      b2 = v2229;	// L3547
    }
    int32_t a_vld2;	// L3549
    a_vld2 = 1;	// L3550
    int32_t b_vld2;	// L3551
    b_vld2 = 1;	// L3552
    int32_t v2232 = s12;	// L3553
    bool v2233 = v2232 >= 12;	// L3554
    if (v2233) {	// L3555
      a_vld2 = 0;	// L3556
      int32_t v2234 = s12;	// L3557
      int32_t v2235 = v2234 & 3;	// L3558
      int v2236 = v2235;	// L3559
      uint8_t v2237 = hold_cnt2[v2236];	// L3560
      int32_t v2238 = v2237;	// L3561
      bool v2239 = v2238 > 0;	// L3562
      if (v2239) {	// L3563
        a_vld2 = 1;	// L3564
      }
    }
    int32_t v2240 = s22;	// L3567
    bool v2241 = v2240 >= 12;	// L3568
    if (v2241) {	// L3569
      b_vld2 = 0;	// L3570
      int32_t v2242 = s22;	// L3571
      int32_t v2243 = v2242 & 3;	// L3572
      int v2244 = v2243;	// L3573
      uint8_t v2245 = hold_cnt2[v2244];	// L3574
      int32_t v2246 = v2245;	// L3575
      bool v2247 = v2246 > 0;	// L3576
      if (v2247) {	// L3577
        b_vld2 = 1;	// L3578
      }
    }
    int32_t v2248 = s12;	// L3581
    bool v2249 = v2248 < 8;	// L3582
    int32_t v2250 = dsmask2;	// L3583
    int32_t v2251 = v2250 >> v2248;	// L3584
    int32_t v2252 = v2251 & 1;	// L3585
    bool v2253 = v2252 == 1;	// L3586
    bool v2254 = v2249 & v2253;	// L3587
    if (v2254) {	// L3588
      int32_t v2255 = s12;	// L3589
      int v2256 = v2255;	// L3590
      int32_t v2257 = drf_full2[v2256];	// L3591
      bool v2258 = v2257 == 0;	// L3592
      if (v2258) {	// L3593
        a_vld2 = 0;	// L3594
      }
    }
    int32_t v2259 = s22;	// L3597
    bool v2260 = v2259 < 8;	// L3598
    int32_t v2261 = dsmask2;	// L3599
    int32_t v2262 = v2261 >> v2259;	// L3600
    int32_t v2263 = v2262 & 1;	// L3601
    bool v2264 = v2263 == 1;	// L3602
    bool v2265 = v2260 & v2264;	// L3603
    if (v2265) {	// L3604
      int32_t v2266 = s22;	// L3605
      int v2267 = v2266;	// L3606
      int32_t v2268 = drf_full2[v2267];	// L3607
      bool v2269 = v2268 == 0;	// L3608
      if (v2269) {	// L3609
        b_vld2 = 0;	// L3610
      }
    }
    int32_t binop2;	// L3613
    binop2 = 0;	// L3614
    int32_t v2271 = op2;	// L3615
    bool v2272 = v2271 == 0;	// L3616
    bool v2273 = v2271 == 1;	// L3617
    bool v2274 = v2271 == 2;	// L3618
    bool v2275 = v2271 == 8;	// L3619
    bool v2276 = v2271 == 9;	// L3620
    bool v2277 = v2272 | v2273;	// L3621
    bool v2278 = v2277 | v2274;	// L3622
    bool v2279 = v2278 | v2275;	// L3623
    bool v2280 = v2279 | v2276;	// L3624
    if (v2280) {	// L3625
      binop2 = 1;	// L3626
    }
    int32_t raw2;	// L3628
    raw2 = 0;	// L3629
    int32_t cmp_busy2;	// L3630
    cmp_busy2 = 0;	// L3631
    l_S_k_5_k4: for (int k4 = 0; k4 < 4; k4++) {	// L3632
      uint8_t v2284 = sb_v2[(k4 + 1)];	// L3633
      int32_t v2285 = v2284;	// L3634
      bool v2286 = v2285 == 1;	// L3635
      uint8_t v2287 = sb_rtr2[(k4 + 1)];	// L3636
      int32_t v2288 = v2287;	// L3637
      bool v2289 = v2288 == 0;	// L3638
      uint8_t v2290 = sb_dst2[(k4 + 1)];	// L3639
      int32_t v2291 = v2290;	// L3640
      bool v2292 = v2291 < 12;	// L3641
      bool v2293 = v2286 & v2289;	// L3642
      bool v2294 = v2293 & v2292;	// L3643
      if (v2294) {	// L3644
        int32_t v2295 = s12;	// L3645
        bool v2296 = v2295 < 12;	// L3646
        uint8_t v2297 = sb_dst2[(k4 + 1)];	// L3647
        int32_t v2298 = v2297;	// L3648
        int32_t v2299 = v2298 & 7;	// L3649
        int32_t v2300 = v2295 & 7;	// L3650
        bool v2301 = v2299 == v2300;	// L3651
        bool v2302 = v2296 & v2301;	// L3652
        if (v2302) {	// L3653
          raw2 = 1;	// L3654
        }
        int32_t v2303 = binop2;	// L3656
        bool v2304 = v2303 == 1;	// L3657
        int32_t v2305 = s22;	// L3658
        bool v2306 = v2305 < 12;	// L3659
        uint8_t v2307 = sb_dst2[(k4 + 1)];	// L3660
        int32_t v2308 = v2307;	// L3661
        int32_t v2309 = v2308 & 7;	// L3662
        int32_t v2310 = v2305 & 7;	// L3663
        bool v2311 = v2309 == v2310;	// L3664
        bool v2312 = v2304 & v2306;	// L3665
        bool v2313 = v2312 & v2311;	// L3666
        if (v2313) {	// L3667
          raw2 = 1;	// L3668
        }
      }
      uint8_t v2314 = sb_v2[(k4 + 1)];	// L3671
      int32_t v2315 = v2314;	// L3672
      bool v2316 = v2315 == 1;	// L3673
      uint8_t v2317 = sb_cmp2[(k4 + 1)];	// L3674
      int32_t v2318 = v2317;	// L3675
      bool v2319 = v2318 == 1;	// L3676
      bool v2320 = v2316 & v2319;	// L3677
      if (v2320) {	// L3678
        cmp_busy2 = 1;	// L3679
      }
    }
    int32_t is_cond2;	// L3682
    is_cond2 = 0;	// L3683
    int32_t v2322 = op2;	// L3684
    bool v2323 = v2322 >= 12;	// L3685
    ap_int<33> v2324 = v2322;	// L3686
    bool v2325 = v2324 <= 15;	// L3687
    bool v2326 = v2323 & v2325;	// L3688
    if (v2326) {	// L3689
      is_cond2 = 1;	// L3690
    }
    int32_t grant2;	// L3692
    grant2 = 0;	// L3693
    int32_t v2328 = pc2;	// L3694
    bool v2329 = v2328 >= 0;	// L3695
    if (v2329) {	// L3696
      grant2 = 1;	// L3697
    }
    int32_t v2330 = pc2;	// L3699
    bool v2331 = v2330 >= 0;	// L3700
    int32_t v2332 = a_vld2;	// L3701
    bool v2333 = v2332 == 0;	// L3702
    int32_t v2334 = binop2;	// L3703
    bool v2335 = v2334 == 1;	// L3704
    int32_t v2336 = b_vld2;	// L3705
    bool v2337 = v2336 == 0;	// L3706
    bool v2338 = v2335 & v2337;	// L3707
    bool v2339 = v2333 | v2338;	// L3708
    bool v2340 = v2331 & v2339;	// L3709
    if (v2340) {	// L3710
      grant2 = 0;	// L3711
    }
    int32_t v2341 = pc2;	// L3713
    bool v2342 = v2341 >= 0;	// L3714
    int32_t v2343 = raw2;	// L3715
    bool v2344 = v2343 == 1;	// L3716
    int32_t v2345 = is_cond2;	// L3717
    bool v2346 = v2345 == 1;	// L3718
    int32_t v2347 = cmp_busy2;	// L3719
    bool v2348 = v2347 == 1;	// L3720
    bool v2349 = v2346 & v2348;	// L3721
    bool v2350 = v2344 | v2349;	// L3722
    bool v2351 = v2342 & v2350;	// L3723
    if (v2351) {	// L3724
      grant2 = 0;	// L3725
    }
    int32_t v2352 = grant2;	// L3727
    bool v2353 = v2352 == 1;	// L3728
    if (v2353) {	// L3729
      int8_t v2354 = instr_cnt2;	// L3730
      int32_t v2355 = cfg_isz2;	// L3731
      int32_t v2356 = v2354;	// L3732
      bool v2357 = v2356 == v2355;	// L3733
      if (v2357) {	// L3734
        instr_cnt2 = 0;	// L3735
        int8_t v2358 = iter_cnt2;	// L3736
        int32_t v2359 = cfg_itsz2;	// L3737
        ap_int<33> v2360 = v2359;	// L3738
        ap_int<33> v2361 = v2360 - 1;	// L3739
        ap_int<33> v2362 = v2358;	// L3740
        bool v2363 = v2362 == v2361;	// L3741
        if (v2363) {	// L3742
          fetch_en2 = 0;	// L3743
        } else {
          int8_t v2364 = iter_cnt2;	// L3745
          ap_int<33> v2365 = v2364;	// L3746
          ap_int<33> v2366 = v2365 + 1;	// L3747
          uint8_t v2367 = v2366;	// L3748
          iter_cnt2 = v2367;	// L3749
        }
      } else {
        int8_t v2368 = instr_cnt2;	// L3752
        ap_int<33> v2369 = v2368;	// L3753
        ap_int<33> v2370 = v2369 + 1;	// L3754
        uint8_t v2371 = v2370;	// L3755
        instr_cnt2 = v2371;	// L3756
      }
    }
    int32_t c12;	// L3759
    c12 = -1;	// L3760
    int32_t c22;	// L3761
    c22 = -1;	// L3762
    int32_t v2374 = grant2;	// L3763
    bool v2375 = v2374 == 1;	// L3764
    int32_t v2376 = s12;	// L3765
    bool v2377 = v2376 >= 12;	// L3766
    bool v2378 = v2375 & v2377;	// L3767
    if (v2378) {	// L3768
      int32_t v2379 = s12;	// L3769
      int32_t v2380 = v2379 & 3;	// L3770
      c12 = v2380;	// L3771
    }
    int32_t v2381 = grant2;	// L3773
    bool v2382 = v2381 == 1;	// L3774
    int32_t v2383 = s22;	// L3775
    bool v2384 = v2383 >= 12;	// L3776
    bool v2385 = v2382 & v2384;	// L3777
    if (v2385) {	// L3778
      int32_t v2386 = s22;	// L3779
      int32_t v2387 = v2386 & 3;	// L3780
      c22 = v2387;	// L3781
    }
    int32_t v2388 = c12;	// L3783
    bool v2389 = v2388 >= 0;	// L3784
    if (v2389) {	// L3785
      int32_t v2390 = c12;	// L3786
      int v2391 = v2390;	// L3787
      half v2392 = hold_v2[v2391][1];	// L3788
      hold_v2[v2391][0] = v2392;	// L3789
      int32_t v2393 = c12;	// L3790
      int v2394 = v2393;	// L3791
      uint8_t v2395 = hold_cnt2[v2394];	// L3792
      ap_int<33> v2396 = v2395;	// L3793
      ap_int<33> v2397 = v2396 - 1;	// L3794
      uint8_t v2398 = v2397;	// L3795
      hold_cnt2[v2394] = v2398;	// L3796
    }
    int32_t v2399 = c22;	// L3798
    bool v2400 = v2399 >= 0;	// L3799
    int32_t v2401 = c12;	// L3800
    bool v2402 = v2399 != v2401;	// L3801
    bool v2403 = v2400 & v2402;	// L3802
    if (v2403) {	// L3803
      int32_t v2404 = c22;	// L3804
      int v2405 = v2404;	// L3805
      half v2406 = hold_v2[v2405][1];	// L3806
      hold_v2[v2405][0] = v2406;	// L3807
      int32_t v2407 = c22;	// L3808
      int v2408 = v2407;	// L3809
      uint8_t v2409 = hold_cnt2[v2408];	// L3810
      ap_int<33> v2410 = v2409;	// L3811
      ap_int<33> v2411 = v2410 - 1;	// L3812
      uint8_t v2412 = v2411;	// L3813
      hold_cnt2[v2408] = v2412;	// L3814
    }
    int32_t v2413 = grant2;	// L3816
    bool v2414 = v2413 == 1;	// L3817
    int32_t v2415 = s12;	// L3818
    bool v2416 = v2415 < 8;	// L3819
    int32_t v2417 = dsmask2;	// L3820
    int32_t v2418 = v2417 >> v2415;	// L3821
    int32_t v2419 = v2418 & 1;	// L3822
    bool v2420 = v2419 == 1;	// L3823
    bool v2421 = v2414 & v2416;	// L3824
    bool v2422 = v2421 & v2420;	// L3825
    if (v2422) {	// L3826
      int32_t v2423 = s12;	// L3827
      int v2424 = v2423;	// L3828
      drf_full2[v2424] = 0;	// L3829
    }
    int32_t v2425 = grant2;	// L3831
    bool v2426 = v2425 == 1;	// L3832
    int32_t v2427 = s22;	// L3833
    bool v2428 = v2427 < 8;	// L3834
    int32_t v2429 = dsmask2;	// L3835
    int32_t v2430 = v2429 >> v2427;	// L3836
    int32_t v2431 = v2430 & 1;	// L3837
    bool v2432 = v2431 == 1;	// L3838
    bool v2433 = v2426 & v2428;	// L3839
    bool v2434 = v2433 & v2432;	// L3840
    if (v2434) {	// L3841
      int32_t v2435 = s22;	// L3842
      int v2436 = v2435;	// L3843
      drf_full2[v2436] = 0;	// L3844
    }
    half res2;
#pragma HLS dependence variable=res2 type=inter dependent=false	// L3846
    res2 = 0.000000;	// L3847
    int32_t v2438 = op2;	// L3848
    bool v2439 = v2438 == 0;	// L3849
    if (v2439) {	// L3850
      half v2440 = a2;	// L3851
      half v2441 = b2;	// L3852
      half v2442 = v2440 + v2441;	// L3853
      res2 = v2442;	// L3854
    } else {
      int32_t v2443 = op2;	// L3856
      bool v2444 = v2443 == 1;	// L3857
      if (v2444) {	// L3858
        half v2445 = a2;	// L3859
        half v2446 = b2;	// L3860
        half v2447 = v2445 - v2446;	// L3861
        res2 = v2447;	// L3862
      } else {
        int32_t v2448 = op2;	// L3864
        bool v2449 = v2448 == 2;	// L3865
        if (v2449) {	// L3866
          half v2450 = a2;	// L3867
          half v2451 = b2;	// L3868
          half v2452 = v2450 * v2451;	// L3869
          res2 = v2452;	// L3870
        } else {
          int32_t v2453 = op2;	// L3872
          bool v2454 = v2453 == 8;	// L3873
          if (v2454) {	// L3874
            half v2455 = a2;	// L3875
            half v2456 = b2;	// L3876
            bool v2457 = v2455 >= v2456;	// L3877
            if (v2457) {	// L3878
              res2 = 1.000000;	// L3879
            } else {
              res2 = -1.000000;	// L3881
            }
          } else {
            int32_t v2458 = op2;	// L3884
            bool v2459 = v2458 == 9;	// L3885
            if (v2459) {	// L3886
              half v2460 = a2;	// L3887
              half v2461 = b2;	// L3888
              bool v2462 = v2460 < v2461;	// L3889
              if (v2462) {	// L3890
                res2 = 1.000000;	// L3891
              } else {
                res2 = -1.000000;	// L3893
              }
            } else {
              half v2463 = a2;	// L3896
              res2 = v2463;	// L3897
            }
          }
        }
      }
    }
    int32_t v2464 = a_vld2;	// L3903
    int32_t res_vld2;	// L3904
    res_vld2 = v2464;	// L3905
    int32_t v2466 = op2;	// L3906
    bool v2467 = v2466 == 0;	// L3907
    bool v2468 = v2466 == 1;	// L3908
    bool v2469 = v2466 == 2;	// L3909
    bool v2470 = v2466 == 8;	// L3910
    bool v2471 = v2466 == 9;	// L3911
    bool v2472 = v2467 | v2468;	// L3912
    bool v2473 = v2472 | v2469;	// L3913
    bool v2474 = v2473 | v2470;	// L3914
    bool v2475 = v2474 | v2471;	// L3915
    if (v2475) {	// L3916
      int32_t v2476 = a_vld2;	// L3917
      int32_t v2477 = b_vld2;	// L3918
      int64_t v2478 = v2476;	// L3919
      int64_t v2479 = v2477;	// L3920
      int64_t v2480 = v2478 * v2479;	// L3921
      int32_t v2481 = v2480;	// L3922
      res_vld2 = v2481;	// L3923
    }
    int32_t v2482 = grant2;	// L3925
    bool v2483 = v2482 == 0;	// L3926
    if (v2483) {	// L3927
      res_vld2 = 0;	// L3928
    }
    int32_t is_rtr2;	// L3930
    is_rtr2 = 0;	// L3931
    int32_t v2485 = op2;	// L3932
    bool v2486 = v2485 >= 4;	// L3933
    ap_int<33> v2487 = v2485;	// L3934
    bool v2488 = v2487 <= 7;	// L3935
    bool v2489 = v2486 & v2488;	// L3936
    if (v2489) {	// L3937
      is_rtr2 = 1;	// L3938
    }
    l_S_k_6_k5: for (int k5 = 0; k5 < 4; k5++) {	// L3940
      uint8_t v2491 = sb_v2[(k5 + 1)];	// L3941
      sb_v2[k5] = v2491;	// L3942
      uint8_t v2492 = sb_dst2[(k5 + 1)];	// L3943
      sb_dst2[k5] = v2492;	// L3944
      uint8_t v2493 = sb_cmp2[(k5 + 1)];	// L3945
      sb_cmp2[k5] = v2493;	// L3946
      uint8_t v2494 = sb_rtr2[(k5 + 1)];	// L3947
      sb_rtr2[k5] = v2494;	// L3948
      uint8_t v2495 = sb_inj2[(k5 + 1)];	// L3949
      sb_inj2[k5] = v2495;	// L3950
      uint8_t v2496 = sb_dir2[(k5 + 1)];	// L3951
      sb_dir2[k5] = v2496;	// L3952
      uint8_t v2497 = sb_id2[(k5 + 1)];	// L3953
      sb_id2[k5] = v2497;	// L3954
      uint8_t v2498 = sb_rvld2[(k5 + 1)];	// L3955
      sb_rvld2[k5] = v2498;	// L3956
      uint8_t v2499 = sb_ix2[(k5 + 1)];	// L3957
      sb_ix2[k5] = v2499;	// L3958
    }
    sb_v2[4] = 0;	// L3960
    int32_t v2500 = grant2;	// L3961
    bool v2501 = v2500 == 1;	// L3962
    if (v2501) {	// L3963
      half v2502 = res2;	// L3964
      int8_t v2503 = resq_wr2;	// L3965
      int v2504 = v2503;	// L3966
      resq2[v2504] = v2502;	// L3967
      int32_t cq2;	// L3968
      cq2 = 0;	// L3969
      int32_t v2506 = op2;	// L3970
      bool v2507 = v2506 == 8;	// L3971
      if (v2507) {	// L3972
        half v2508 = a2;	// L3973
        half v2509 = b2;	// L3974
        bool v2510 = v2508 >= v2509;	// L3975
        if (v2510) {	// L3976
          cq2 = 1;	// L3977
        }
      }
      int32_t v2511 = op2;	// L3980
      bool v2512 = v2511 == 9;	// L3981
      if (v2512) {	// L3982
        half v2513 = a2;	// L3983
        half v2514 = b2;	// L3984
        bool v2515 = v2513 < v2514;	// L3985
        if (v2515) {	// L3986
          cq2 = 1;	// L3987
        }
      }
      int32_t v2516 = cq2;	// L3990
      uint8_t v2517 = v2516;	// L3991
      int8_t v2518 = resq_wr2;	// L3992
      int v2519 = v2518;	// L3993
      cmpq2[v2519] = v2517;	// L3994
      sb_v2[4] = 1;	// L3995
      int32_t v2520 = dst2;	// L3996
      uint8_t v2521 = v2520;	// L3997
      sb_dst2[4] = v2521;	// L3998
      int8_t v2522 = resq_wr2;	// L3999
      sb_ix2[4] = v2522;	// L4000
      sb_cmp2[4] = 0;	// L4001
      int32_t v2523 = op2;	// L4002
      bool v2524 = v2523 == 8;	// L4003
      bool v2525 = v2523 == 9;	// L4004
      bool v2526 = v2524 | v2525;	// L4005
      if (v2526) {	// L4006
        sb_cmp2[4] = 1;	// L4007
      }
      int32_t v2527 = is_rtr2;	// L4009
      int32_t rtrf2;	// L4010
      rtrf2 = v2527;	// L4011
      int32_t v2529 = is_cond2;	// L4012
      bool v2530 = v2529 == 1;	// L4013
      if (v2530) {	// L4014
        rtrf2 = 1;	// L4015
      }
      int32_t v2531 = rtrf2;	// L4017
      uint8_t v2532 = v2531;	// L4018
      sb_rtr2[4] = v2532;	// L4019
      int32_t v2533 = is_rtr2;	// L4020
      int32_t inj2;	// L4021
      inj2 = v2533;	// L4022
      int32_t v2535 = is_cond2;	// L4023
      bool v2536 = v2535 == 1;	// L4024
      int8_t v2537 = condition_reg2;	// L4025
      int32_t v2538 = v2537;	// L4026
      bool v2539 = v2538 == 1;	// L4027
      bool v2540 = v2536 & v2539;	// L4028
      if (v2540) {	// L4029
        inj2 = 1;	// L4030
      }
      int32_t v2541 = inj2;	// L4032
      uint8_t v2542 = v2541;	// L4033
      sb_inj2[4] = v2542;	// L4034
      int32_t v2543 = op2;	// L4035
      int32_t v2544 = v2543 & 3;	// L4036
      uint8_t v2545 = v2544;	// L4037
      sb_dir2[4] = v2545;	// L4038
      int32_t v2546 = s22;	// L4039
      uint8_t v2547 = v2546;	// L4040
      sb_id2[4] = v2547;	// L4041
      int32_t v2548 = res_vld2;	// L4042
      uint8_t v2549 = v2548;	// L4043
      sb_rvld2[4] = v2549;	// L4044
      int8_t v2550 = resq_wr2;	// L4045
      ap_int<33> v2551 = v2550;	// L4046
      ap_int<33> v2552 = v2551 + 1;	// L4047
      ap_int<33> v2553 = v2552 & 7;	// L4048
      uint8_t v2554 = v2553;	// L4049
      resq_wr2 = v2554;	// L4050
    }
    ap_int<17> v2555 = tx_n2;	// L4052
    txn_r2 = v2555;	// L4053
    ap_int<17> v2556 = tx_s2;	// L4054
    txs_r2 = v2556;	// L4055
    ap_int<17> v2557 = tx_w2;	// L4056
    txw_r2 = v2557;	// L4057
    ap_int<17> v2558 = tx_e2;	// L4058
    txe_r2 = v2558;	// L4059
    int32_t v2559 = crv_vld2;	// L4060
    bool v2560 = v2559 == 1;	// L4061
    if (v2560) {	// L4062
      int32_t v2561 = crv_mode2;	// L4063
      bool v2562 = v2561 == 1;	// L4064
      if (v2562) {	// L4065
        int32_t v2563 = crv_addr2;	// L4066
        int32_t v2564 = v2563 >> 3;	// L4067
        int32_t v2565 = v2564 & 1;	// L4068
        bool v2566 = v2565 == 1;	// L4069
        if (v2566) {	// L4070
          int32_t v2567 = crv_raw2;	// L4071
          int32_t v2568 = crv_addr2;	// L4072
          int32_t v2569 = v2568 & 7;	// L4073
          int v2570 = v2569;	// L4074
          irf2[v2570] = v2567;	// L4075
        } else {
          int32_t v2571 = crv_addr2;	// L4077
          bool v2572 = v2571 == 0;	// L4078
          if (v2572) {	// L4079
            int32_t v2573 = crv_raw2;	// L4080
            int32_t v2574 = v2573 & 255;	// L4081
            dsmask2 = v2574;	// L4082
            int32_t v2575 = crv_raw2;	// L4083
            int32_t v2576 = v2575 >> 8;	// L4084
            int32_t v2577 = v2576 & 7;	// L4085
            cfg_isz2 = v2577;	// L4086
            int32_t v2578 = crv_raw2;	// L4087
            int32_t v2579 = v2578 >> 15;	// L4088
            int32_t v2580 = v2579 & 1;	// L4089
            bool v2581 = v2580 == 1;	// L4090
            if (v2581) {	// L4091
              fetch_en2 = 1;	// L4092
              instr_cnt2 = 0;	// L4093
              iter_cnt2 = 0;	// L4094
            }
          } else {
            int32_t v2582 = crv_addr2;	// L4097
            bool v2583 = v2582 == 1;	// L4098
            if (v2583) {	// L4099
              int32_t v2584 = crv_raw2;	// L4100
              int32_t v2585 = v2584 & 255;	// L4101
              cfg_itsz2 = v2585;	// L4102
            }
          }
        }
      } else {
        int32_t v2586 = crv_addr2;	// L4107
        bool v2587 = v2586 < 8;	// L4108
        int32_t v2588 = dsmask2;	// L4109
        int32_t v2589 = v2588 >> v2586;	// L4110
        int32_t v2590 = v2589 & 1;	// L4111
        bool v2591 = v2590 == 1;	// L4112
        bool v2592 = v2587 & v2591;	// L4113
        if (v2592) {	// L4114
          int32_t v2593 = crv_addr2;	// L4115
          int v2594 = v2593;	// L4116
          int32_t v2595 = drf_full2[v2594];	// L4117
          bool v2596 = v2595 == 0;	// L4118
          if (v2596) {	// L4119
            half v2597 = crv_data2;	// L4120
            int32_t v2598 = crv_addr2;	// L4121
            int v2599 = v2598;	// L4122
            drf2[v2599] = v2597;	// L4123
            int32_t v2600 = crv_addr2;	// L4124
            int v2601 = v2600;	// L4125
            drf_full2[v2601] = 1;	// L4126
          }
        } else {
          half v2602 = crv_data2;	// L4129
          int32_t v2603 = crv_addr2;	// L4130
          int v2604 = v2603;	// L4131
          drf2[v2604] = v2602;	// L4132
        }
      }
    }
    ap_int<17> v2605 = txe_r2;	// L4136
    bool v2606;
    ap_int<17> v2606_tmp = v2605;
    v2606 = v2606_tmp[0];	// L4137
    int32_t v2607 = v2606;	// L4138
    bool v2608 = v2607 == 1;	// L4139
    if (v2608) {	// L4140
      ap_int<17> v2609 = txe_r2;	// L4141
      v1762.write(v2609);	// L4142
    }
    ap_int<17> v2610 = txw_r2;	// L4144
    bool v2611;
    ap_int<17> v2611_tmp = v2610;
    v2611 = v2611_tmp[0];	// L4145
    int32_t v2612 = v2611;	// L4146
    bool v2613 = v2612 == 1;	// L4147
    if (v2613) {	// L4148
      ap_int<17> v2614 = txw_r2;	// L4149
      v1763.write(v2614);	// L4150
    }
    ap_int<17> v2615 = txs_r2;	// L4152
    bool v2616;
    ap_int<17> v2616_tmp = v2615;
    v2616 = v2616_tmp[0];	// L4153
    int32_t v2617 = v2616;	// L4154
    bool v2618 = v2617 == 1;	// L4155
    if (v2618) {	// L4156
      ap_int<17> v2619 = txs_r2;	// L4157
      v1764.write(v2619);	// L4158
    }
    ap_int<17> v2620 = txn_r2;	// L4160
    bool v2621;
    ap_int<17> v2621_tmp = v2620;
    v2621 = v2621_tmp[0];	// L4161
    int32_t v2622 = v2621;	// L4162
    bool v2623 = v2622 == 1;	// L4163
    if (v2623) {	// L4164
      ap_int<17> v2624 = txn_r2;	// L4165
      v1765.write(v2624);	// L4166
    }
  }
}

void node_0_3(
  hls::stream< ap_uint<26> >& v2625,
  hls::stream< ap_uint<26> >& v2626,
  hls::stream< ap_uint<26> >& v2627,
  hls::stream< ap_uint<26> >& v2628,
  hls::stream< ap_uint<26> >& v2629,
  hls::stream< ap_uint<26> >& v2630,
  hls::stream< ap_uint<26> >& v2631,
  hls::stream< ap_uint<26> >& v2632,
  hls::stream< ap_uint<17> >& v2633,
  hls::stream< ap_uint<17> >& v2634,
  hls::stream< ap_uint<17> >& v2635,
  hls::stream< ap_uint<17> >& v2636,
  hls::stream< ap_uint<17> >& v2637,
  hls::stream< ap_uint<17> >& v2638,
  hls::stream< ap_uint<17> >& v2639,
  hls::stream< ap_uint<17> >& v2640
) {	// L4171
  int32_t irf3[8];	// L4204
  #pragma HLS array_partition variable=irf3 complete dim=1

  for (int v2642 = 0; v2642 < 8; v2642++) {	// L4205
    irf3[v2642] = 0;	// L4205
  }
  half drf3[8];	// L4206
  #pragma HLS array_partition variable=drf3 complete dim=1

  for (int v2644 = 0; v2644 < 8; v2644++) {	// L4207
    drf3[v2644] = 0.000000;	// L4207
  }
  int32_t drf_full3[8];	// L4208
  #pragma HLS array_partition variable=drf_full3 complete dim=1

  for (int v2646 = 0; v2646 < 8; v2646++) {	// L4209
    drf_full3[v2646] = 0;	// L4209
  }
  int32_t dsmask3;	// L4210
  dsmask3 = 0;	// L4211
  int32_t crv_vld3;	// L4212
  crv_vld3 = 0;	// L4213
  half crv_data3;	// L4214
  crv_data3 = 0.000000;	// L4215
  int32_t crv_addr3;	// L4216
  crv_addr3 = 0;	// L4217
  int32_t crv_mode3;	// L4218
  crv_mode3 = 0;	// L4219
  int32_t crv_raw3;	// L4220
  crv_raw3 = 0;	// L4221
  int32_t csd_vld3;	// L4222
  csd_vld3 = 0;	// L4223
  ap_uint<26> csd_pkt3;	// L4224
  csd_pkt3 = 0;	// L4225
  int32_t csd_dir3;	// L4226
  csd_dir3 = 0;	// L4227
  int32_t row_id3;	// L4228
  row_id3 = 0;	// L4229
  int32_t col_id3;	// L4230
  col_id3 = 3;	// L4231
  ap_uint<17> txn_r3;	// L4232
  txn_r3 = 0;	// L4233
  ap_uint<17> txs_r3;	// L4234
  txs_r3 = 0;	// L4235
  ap_uint<17> txw_r3;	// L4236
  txw_r3 = 0;	// L4237
  ap_uint<17> txe_r3;	// L4238
  txe_r3 = 0;	// L4239
  half hold_v3[4][2];	// L4240
  #pragma HLS array_partition variable=hold_v3 complete dim=1
  #pragma HLS array_partition variable=hold_v3 complete dim=2

  for (int v2663 = 0; v2663 < 4; v2663++) {	// L4241
    for (int v2664 = 0; v2664 < 2; v2664++) {	// L4241
      hold_v3[v2663][v2664] = 0.000000;	// L4241
    }
  }
  uint8_t hold_cnt3[4];	// L4242
  #pragma HLS array_partition variable=hold_cnt3 complete dim=1

  for (int v2666 = 0; v2666 < 4; v2666++) {	// L4243
    hold_cnt3[v2666] = 0;	// L4243
  }
  int32_t crv_ever3;	// L4244
  crv_ever3 = 0;	// L4245
  int32_t fe_ever3;	// L4246
  fe_ever3 = 0;	// L4247
  ap_uint<26> rbuf3[4][2];	// L4248
  #pragma HLS array_partition variable=rbuf3 complete dim=1
  #pragma HLS array_partition variable=rbuf3 complete dim=2

  for (int v2670 = 0; v2670 < 4; v2670++) {	// L4249
    for (int v2671 = 0; v2671 < 2; v2671++) {	// L4249
      rbuf3[v2670][v2671] = 0;	// L4249
    }
  }
  uint8_t rbcnt3[4];	// L4250
  #pragma HLS array_partition variable=rbcnt3 complete dim=1

  for (int v2673 = 0; v2673 < 4; v2673++) {	// L4251
    rbcnt3[v2673] = 0;	// L4251
  }
  int32_t cfg_isz3;	// L4252
  cfg_isz3 = 0;	// L4253
  int32_t cfg_itsz3;	// L4254
  cfg_itsz3 = 0;	// L4255
  uint8_t fetch_en3;	// L4256
  fetch_en3 = 0;	// L4257
  uint8_t instr_cnt3;	// L4258
  instr_cnt3 = 0;	// L4259
  uint8_t iter_cnt3;	// L4260
  iter_cnt3 = 0;	// L4261
  uint8_t condition_reg3;	// L4262
  condition_reg3 = 0;	// L4263
  uint8_t sb_v3[5];	// L4264
  #pragma HLS array_partition variable=sb_v3 complete dim=1

  for (int v2681 = 0; v2681 < 5; v2681++) {	// L4265
    sb_v3[v2681] = 0;	// L4265
  }
  uint8_t sb_dst3[5];	// L4266
  #pragma HLS array_partition variable=sb_dst3 complete dim=1

  for (int v2683 = 0; v2683 < 5; v2683++) {	// L4267
    sb_dst3[v2683] = 0;	// L4267
  }
  uint8_t sb_cmp3[5];	// L4268
  #pragma HLS array_partition variable=sb_cmp3 complete dim=1

  for (int v2685 = 0; v2685 < 5; v2685++) {	// L4269
    sb_cmp3[v2685] = 0;	// L4269
  }
  uint8_t sb_rtr3[5];	// L4270
  #pragma HLS array_partition variable=sb_rtr3 complete dim=1

  for (int v2687 = 0; v2687 < 5; v2687++) {	// L4271
    sb_rtr3[v2687] = 0;	// L4271
  }
  uint8_t sb_inj3[5];	// L4272
  #pragma HLS array_partition variable=sb_inj3 complete dim=1

  for (int v2689 = 0; v2689 < 5; v2689++) {	// L4273
    sb_inj3[v2689] = 0;	// L4273
  }
  uint8_t sb_dir3[5];	// L4274
  #pragma HLS array_partition variable=sb_dir3 complete dim=1

  for (int v2691 = 0; v2691 < 5; v2691++) {	// L4275
    sb_dir3[v2691] = 0;	// L4275
  }
  uint8_t sb_id3[5];	// L4276
  #pragma HLS array_partition variable=sb_id3 complete dim=1

  for (int v2693 = 0; v2693 < 5; v2693++) {	// L4277
    sb_id3[v2693] = 0;	// L4277
  }
  uint8_t sb_rvld3[5];	// L4278
  #pragma HLS array_partition variable=sb_rvld3 complete dim=1

  for (int v2695 = 0; v2695 < 5; v2695++) {	// L4279
    sb_rvld3[v2695] = 0;	// L4279
  }
  uint8_t sb_ix3[5];	// L4280
  #pragma HLS array_partition variable=sb_ix3 complete dim=1

  for (int v2697 = 0; v2697 < 5; v2697++) {	// L4281
    sb_ix3[v2697] = 0;	// L4281
  }
  half resq3[8];	// L4282
  #pragma HLS array_partition variable=resq3 complete dim=1
#pragma HLS dependence variable=resq3 type=inter dependent=false

  for (int v2699 = 0; v2699 < 8; v2699++) {	// L4283
    resq3[v2699] = 0.000000;	// L4283
  }
  uint8_t cmpq3[8];	// L4284
  #pragma HLS array_partition variable=cmpq3 complete dim=1
#pragma HLS dependence variable=cmpq3 type=inter dependent=false

  for (int v2701 = 0; v2701 < 8; v2701++) {	// L4285
    cmpq3[v2701] = 0;	// L4285
  }
  uint8_t resq_wr3;	// L4286
  resq_wr3 = 0;	// L4287
  l_S_t_0_t3: for (int t3 = 0; t3 < 374; t3++) {	// L4288
  #pragma HLS pipeline II=1
    ap_uint<26> p_w3;	// L4289
    p_w3 = 0;	// L4290
    ap_uint<26> p_e3;	// L4291
    p_e3 = 0;	// L4292
    ap_uint<26> p_n3;	// L4293
    p_n3 = 0;	// L4294
    ap_uint<26> p_s3;	// L4295
    p_s3 = 0;	// L4296
    uint8_t v2708 = rbcnt3[0];	// L4297
    int32_t v2709 = v2708;	// L4298
    bool v2710 = v2709 < 2;	// L4299
    if (v2710) {	// L4300
      ap_uint<26> v2711;
      bool v2712 = v2625.read_nb(v2711);
	// L4301
      ap_uint<26> gw3;	// L4302
      gw3 = v2711;	// L4303
      bool okw3;	// L4304
      okw3 = v2712;	// L4305
      bool v2715 = okw3;	// L4306
      if (v2715) {	// L4307
        ap_int<26> v2716 = gw3;	// L4308
        p_w3 = v2716;	// L4309
      }
    }
    uint8_t v2717 = rbcnt3[1];	// L4312
    int32_t v2718 = v2717;	// L4313
    bool v2719 = v2718 < 2;	// L4314
    if (v2719) {	// L4315
      ap_uint<26> v2720;
      bool v2721 = v2626.read_nb(v2720);
	// L4316
      ap_uint<26> ge3;	// L4317
      ge3 = v2720;	// L4318
      bool oke3;	// L4319
      oke3 = v2721;	// L4320
      bool v2724 = oke3;	// L4321
      if (v2724) {	// L4322
        ap_int<26> v2725 = ge3;	// L4323
        p_e3 = v2725;	// L4324
      }
    }
    uint8_t v2726 = rbcnt3[2];	// L4327
    int32_t v2727 = v2726;	// L4328
    bool v2728 = v2727 < 2;	// L4329
    if (v2728) {	// L4330
      ap_uint<26> v2729;
      bool v2730 = v2627.read_nb(v2729);
	// L4331
      ap_uint<26> gn3;	// L4332
      gn3 = v2729;	// L4333
      bool okn3;	// L4334
      okn3 = v2730;	// L4335
      bool v2733 = okn3;	// L4336
      if (v2733) {	// L4337
        ap_int<26> v2734 = gn3;	// L4338
        p_n3 = v2734;	// L4339
      }
    }
    uint8_t v2735 = rbcnt3[3];	// L4342
    int32_t v2736 = v2735;	// L4343
    bool v2737 = v2736 < 2;	// L4344
    if (v2737) {	// L4345
      ap_uint<26> v2738;
      bool v2739 = v2628.read_nb(v2738);
	// L4346
      ap_uint<26> gs3;	// L4347
      gs3 = v2738;	// L4348
      bool oks3;	// L4349
      oks3 = v2739;	// L4350
      bool v2742 = oks3;	// L4351
      if (v2742) {	// L4352
        ap_int<26> v2743 = gs3;	// L4353
        p_s3 = v2743;	// L4354
      }
    }
    ap_uint<26> fin3[4];	// L4357
    for (int v2745 = 0; v2745 < 4; v2745++) {	// L4358
      fin3[v2745] = 0;	// L4358
    }
    ap_int<26> v2746 = p_w3;	// L4359
    fin3[0] = v2746;	// L4360
    ap_int<26> v2747 = p_e3;	// L4361
    fin3[1] = v2747;	// L4362
    ap_int<26> v2748 = p_n3;	// L4363
    fin3[2] = v2748;	// L4364
    ap_int<26> v2749 = p_s3;	// L4365
    fin3[3] = v2749;	// L4366
    l_S_d_0_d12: for (int d12 = 0; d12 < 4; d12++) {	// L4367
      ap_uint<26> v2751 = fin3[d12];	// L4368
      bool v2752;
      ap_int<26> v2752_tmp = v2751;
      v2752 = v2752_tmp[25];	// L4369
      int32_t v2753 = v2752;	// L4370
      bool v2754 = v2753 == 1;	// L4371
      uint8_t v2755 = rbcnt3[d12];	// L4372
      int32_t v2756 = v2755;	// L4373
      bool v2757 = v2756 < 2;	// L4374
      bool v2758 = v2754 & v2757;	// L4375
      if (v2758) {	// L4376
        ap_uint<26> v2759 = fin3[d12];	// L4377
        uint8_t v2760 = rbcnt3[d12];	// L4378
        int v2761 = v2760;	// L4379
        rbuf3[d12][v2761] = v2759;	// L4380
        uint8_t v2762 = rbcnt3[d12];	// L4381
        ap_int<33> v2763 = v2762;	// L4382
        ap_int<33> v2764 = v2763 + 1;	// L4383
        uint8_t v2765 = v2764;	// L4384
        rbcnt3[d12] = v2765;	// L4385
      }
    }
    ap_uint<26> hd3[4];	// L4388
    for (int v2767 = 0; v2767 < 4; v2767++) {	// L4389
      hd3[v2767] = 0;	// L4389
    }
    int32_t hvld3[4];	// L4390
    for (int v2769 = 0; v2769 < 4; v2769++) {	// L4391
      hvld3[v2769] = 0;	// L4391
    }
    int32_t hit3[4];	// L4392
    for (int v2771 = 0; v2771 < 4; v2771++) {	// L4393
      hit3[v2771] = 0;	// L4393
    }
    int32_t axis3[4];	// L4394
    for (int v2773 = 0; v2773 < 4; v2773++) {	// L4395
      axis3[v2773] = 0;	// L4395
    }
    int32_t v2774 = col_id3;	// L4396
    axis3[0] = v2774;	// L4397
    int32_t v2775 = col_id3;	// L4398
    axis3[1] = v2775;	// L4399
    int32_t v2776 = row_id3;	// L4400
    axis3[2] = v2776;	// L4401
    int32_t v2777 = row_id3;	// L4402
    axis3[3] = v2777;	// L4403
    l_S_d_1_d13: for (int d13 = 0; d13 < 4; d13++) {	// L4404
      uint8_t v2779 = rbcnt3[d13];	// L4405
      int32_t v2780 = v2779;	// L4406
      bool v2781 = v2780 > 0;	// L4407
      if (v2781) {	// L4408
        ap_uint<26> v2782 = rbuf3[d13][0];	// L4409
        hd3[d13] = v2782;	// L4410
        hvld3[d13] = 1;	// L4411
        ap_uint<26> v2783 = hd3[d13];	// L4412
        ap_int<4> v2784;
        ap_int<26> v2784_tmp = v2783;
        v2784 = v2784_tmp(24, 21);	// L4413
        int32_t v2785 = axis3[d13];	// L4414
        int32_t v2786 = v2784;	// L4415
        bool v2787 = v2786 == v2785;	// L4416
        if (v2787) {	// L4417
          hit3[d13] = 1;	// L4418
        }
      }
    }
    ap_uint<26> o_crv3;	// L4422
    o_crv3 = 0;	// L4423
    int32_t crv_in3;	// L4424
    crv_in3 = -1;	// L4425
    int32_t v2790 = hit3[3];	// L4426
    bool v2791 = v2790 == 1;	// L4427
    if (v2791) {	// L4428
      ap_uint<26> v2792 = hd3[3];	// L4429
      o_crv3 = v2792;	// L4430
      crv_in3 = 3;	// L4431
    } else {
      int32_t v2793 = hit3[2];	// L4433
      bool v2794 = v2793 == 1;	// L4434
      if (v2794) {	// L4435
        ap_uint<26> v2795 = hd3[2];	// L4436
        o_crv3 = v2795;	// L4437
        crv_in3 = 2;	// L4438
      } else {
        int32_t v2796 = hit3[1];	// L4440
        bool v2797 = v2796 == 1;	// L4441
        if (v2797) {	// L4442
          ap_uint<26> v2798 = hd3[1];	// L4443
          o_crv3 = v2798;	// L4444
          crv_in3 = 1;	// L4445
        } else {
          int32_t v2799 = hit3[0];	// L4447
          bool v2800 = v2799 == 1;	// L4448
          if (v2800) {	// L4449
            ap_uint<26> v2801 = hd3[0];	// L4450
            o_crv3 = v2801;	// L4451
            crv_in3 = 0;	// L4452
          }
        }
      }
    }
    int32_t pop3[4];	// L4457
    for (int v2803 = 0; v2803 < 4; v2803++) {	// L4458
      pop3[v2803] = 0;	// L4458
    }
    int32_t inj_done3;	// L4459
    inj_done3 = 0;	// L4460
    int32_t idir3;	// L4461
    idir3 = -1;	// L4462
    ap_int<26> v2806 = csd_pkt3;	// L4463
    bool v2807;
    ap_int<26> v2807_tmp = v2806;
    v2807 = v2807_tmp[25];	// L4464
    int32_t v2808 = v2807;	// L4465
    bool v2809 = v2808 == 1;	// L4466
    if (v2809) {	// L4467
      int32_t v2810 = csd_dir3;	// L4468
      ap_int<33> v2811 = v2810;	// L4469
      ap_int<33> v2812 = 3 - v2811;	// L4470
      int32_t v2813 = v2812;	// L4471
      idir3 = v2813;	// L4472
    }
    int32_t v2814 = idir3;	// L4474
    bool v2815 = v2814 == 0;	// L4475
    if (v2815) {	// L4476
      ap_int<26> v2816 = csd_pkt3;	// L4477
      bool v2817 = v2629.write_nb(v2816);
	// L4478
      if (v2817) {	// L4479
        inj_done3 = 1;	// L4480
      }
    } else {
      int32_t v2818 = hvld3[0];	// L4483
      bool v2819 = v2818 == 1;	// L4484
      int32_t v2820 = hit3[0];	// L4485
      bool v2821 = v2820 == 0;	// L4486
      bool v2822 = v2819 & v2821;	// L4487
      if (v2822) {	// L4488
        ap_uint<26> v2823 = hd3[0];	// L4489
        bool v2824 = v2629.write_nb(v2823);
	// L4490
        if (v2824) {	// L4491
          pop3[0] = 1;	// L4492
        }
      }
    }
    int32_t v2825 = idir3;	// L4496
    bool v2826 = v2825 == 1;	// L4497
    if (v2826) {	// L4498
      ap_int<26> v2827 = csd_pkt3;	// L4499
      bool v2828 = v2630.write_nb(v2827);
	// L4500
      if (v2828) {	// L4501
        inj_done3 = 1;	// L4502
      }
    } else {
      int32_t v2829 = hvld3[1];	// L4505
      bool v2830 = v2829 == 1;	// L4506
      int32_t v2831 = hit3[1];	// L4507
      bool v2832 = v2831 == 0;	// L4508
      bool v2833 = v2830 & v2832;	// L4509
      if (v2833) {	// L4510
        ap_uint<26> v2834 = hd3[1];	// L4511
        bool v2835 = v2630.write_nb(v2834);
	// L4512
        if (v2835) {	// L4513
          pop3[1] = 1;	// L4514
        }
      }
    }
    int32_t v2836 = idir3;	// L4518
    bool v2837 = v2836 == 2;	// L4519
    if (v2837) {	// L4520
      ap_int<26> v2838 = csd_pkt3;	// L4521
      bool v2839 = v2631.write_nb(v2838);
	// L4522
      if (v2839) {	// L4523
        inj_done3 = 1;	// L4524
      }
    } else {
      int32_t v2840 = hvld3[2];	// L4527
      bool v2841 = v2840 == 1;	// L4528
      int32_t v2842 = hit3[2];	// L4529
      bool v2843 = v2842 == 0;	// L4530
      bool v2844 = v2841 & v2843;	// L4531
      if (v2844) {	// L4532
        ap_uint<26> v2845 = hd3[2];	// L4533
        bool v2846 = v2631.write_nb(v2845);
	// L4534
        if (v2846) {	// L4535
          pop3[2] = 1;	// L4536
        }
      }
    }
    int32_t v2847 = idir3;	// L4540
    bool v2848 = v2847 == 3;	// L4541
    if (v2848) {	// L4542
      ap_int<26> v2849 = csd_pkt3;	// L4543
      bool v2850 = v2632.write_nb(v2849);
	// L4544
      if (v2850) {	// L4545
        inj_done3 = 1;	// L4546
      }
    } else {
      int32_t v2851 = hvld3[3];	// L4549
      bool v2852 = v2851 == 1;	// L4550
      int32_t v2853 = hit3[3];	// L4551
      bool v2854 = v2853 == 0;	// L4552
      bool v2855 = v2852 & v2854;	// L4553
      if (v2855) {	// L4554
        ap_uint<26> v2856 = hd3[3];	// L4555
        bool v2857 = v2632.write_nb(v2856);
	// L4556
        if (v2857) {	// L4557
          pop3[3] = 1;	// L4558
        }
      }
    }
    int32_t v2858 = crv_in3;	// L4562
    bool v2859 = v2858 >= 0;	// L4563
    if (v2859) {	// L4564
      int32_t v2860 = crv_in3;	// L4565
      int v2861 = v2860;	// L4566
      pop3[v2861] = 1;	// L4567
    }
    l_S_d_2_d14: for (int d14 = 0; d14 < 4; d14++) {	// L4569
      int32_t v2863 = pop3[d14];	// L4570
      bool v2864 = v2863 == 1;	// L4571
      if (v2864) {	// L4572
        l_S_sft_2_sft3: for (int sft3 = 0; sft3 < 1; sft3++) {	// L4573
          ap_uint<26> v2866 = rbuf3[d14][(sft3 + 1)];	// L4574
          rbuf3[d14][sft3] = v2866;	// L4575
        }
        uint8_t v2867 = rbcnt3[d14];	// L4577
        ap_int<33> v2868 = v2867;	// L4578
        ap_int<33> v2869 = v2868 - 1;	// L4579
        uint8_t v2870 = v2869;	// L4580
        rbcnt3[d14] = v2870;	// L4581
      }
    }
    int32_t v2871 = inj_done3;	// L4584
    bool v2872 = v2871 == 1;	// L4585
    if (v2872) {	// L4586
      csd_pkt3 = 0;	// L4587
    }
    ap_int<26> v2873 = o_crv3;	// L4589
    bool v2874;
    ap_int<26> v2874_tmp = v2873;
    v2874 = v2874_tmp[25];	// L4590
    int32_t v2875 = v2874;	// L4591
    crv_vld3 = v2875;	// L4592
    int32_t v2876 = crv_vld3;	// L4593
    bool v2877 = v2876 == 1;	// L4594
    if (v2877) {	// L4595
      crv_ever3 = 1;	// L4596
    }
    ap_int<26> v2878 = o_crv3;	// L4598
    int16_t v2879;
    ap_int<26> v2879_tmp = v2878;
    v2879 = v2879_tmp(15, 0);	// L4599
    half v2880;
    union { uint16_t from; half to;} _converter_v2879_to_v2880 = {};
    _converter_v2879_to_v2880.from = v2879;
    v2880 = _converter_v2879_to_v2880.to;	// L4600
    crv_data3 = v2880;	// L4601
    ap_int<26> v2881 = o_crv3;	// L4602
    ap_int<4> v2882;
    ap_int<26> v2882_tmp = v2881;
    v2882 = v2882_tmp(19, 16);	// L4603
    int32_t v2883 = v2882;	// L4604
    crv_addr3 = v2883;	// L4605
    ap_int<26> v2884 = o_crv3;	// L4606
    bool v2885;
    ap_int<26> v2885_tmp = v2884;
    v2885 = v2885_tmp[20];	// L4607
    int32_t v2886 = v2885;	// L4608
    crv_mode3 = v2886;	// L4609
    ap_int<26> v2887 = o_crv3;	// L4610
    int16_t v2888;
    ap_int<26> v2888_tmp = v2887;
    v2888 = v2888_tmp(15, 0);	// L4611
    int32_t v2889 = v2888;	// L4612
    crv_raw3 = v2889;	// L4613
    half rxv3[4];	// L4614
    for (int v2891 = 0; v2891 < 4; v2891++) {	// L4615
      rxv3[v2891] = 0.000000;	// L4615
    }
    int32_t rxvld3[4];	// L4616
    for (int v2893 = 0; v2893 < 4; v2893++) {	// L4617
      rxvld3[v2893] = 0;	// L4617
    }
    uint8_t v2894 = hold_cnt3[0];	// L4618
    int32_t v2895 = v2894;	// L4619
    bool v2896 = v2895 < 2;	// L4620
    if (v2896) {	// L4621
      ap_uint<17> v2897;
      bool v2898 = v2633.read_nb(v2897);
	// L4622
      ap_uint<17> sgn3;	// L4623
      sgn3 = v2897;	// L4624
      bool sqn3;	// L4625
      sqn3 = v2898;	// L4626
      bool v2901 = sqn3;	// L4627
      int32_t v2902 = v2901;	// L4628
      bool v2903 = v2902 == 1;	// L4629
      if (v2903) {	// L4630
        ap_int<17> v2904 = sgn3;	// L4631
        int16_t v2905;
        ap_int<17> v2905_tmp = v2904;
        v2905 = v2905_tmp(16, 1);	// L4632
        half v2906;
        union { uint16_t from; half to;} _converter_v2905_to_v2906 = {};
        _converter_v2905_to_v2906.from = v2905;
        v2906 = _converter_v2905_to_v2906.to;	// L4633
        rxv3[0] = v2906;	// L4634
        rxvld3[0] = 1;	// L4635
      }
    }
    uint8_t v2907 = hold_cnt3[1];	// L4638
    int32_t v2908 = v2907;	// L4639
    bool v2909 = v2908 < 2;	// L4640
    if (v2909) {	// L4641
      ap_uint<17> v2910;
      bool v2911 = v2634.read_nb(v2910);
	// L4642
      ap_uint<17> sgs3;	// L4643
      sgs3 = v2910;	// L4644
      bool sqs3;	// L4645
      sqs3 = v2911;	// L4646
      bool v2914 = sqs3;	// L4647
      int32_t v2915 = v2914;	// L4648
      bool v2916 = v2915 == 1;	// L4649
      if (v2916) {	// L4650
        ap_int<17> v2917 = sgs3;	// L4651
        int16_t v2918;
        ap_int<17> v2918_tmp = v2917;
        v2918 = v2918_tmp(16, 1);	// L4652
        half v2919;
        union { uint16_t from; half to;} _converter_v2918_to_v2919 = {};
        _converter_v2918_to_v2919.from = v2918;
        v2919 = _converter_v2918_to_v2919.to;	// L4653
        rxv3[1] = v2919;	// L4654
        rxvld3[1] = 1;	// L4655
      }
    }
    uint8_t v2920 = hold_cnt3[2];	// L4658
    int32_t v2921 = v2920;	// L4659
    bool v2922 = v2921 < 2;	// L4660
    if (v2922) {	// L4661
      ap_uint<17> v2923;
      bool v2924 = v2635.read_nb(v2923);
	// L4662
      ap_uint<17> sgw3;	// L4663
      sgw3 = v2923;	// L4664
      bool sqw3;	// L4665
      sqw3 = v2924;	// L4666
      bool v2927 = sqw3;	// L4667
      int32_t v2928 = v2927;	// L4668
      bool v2929 = v2928 == 1;	// L4669
      if (v2929) {	// L4670
        ap_int<17> v2930 = sgw3;	// L4671
        int16_t v2931;
        ap_int<17> v2931_tmp = v2930;
        v2931 = v2931_tmp(16, 1);	// L4672
        half v2932;
        union { uint16_t from; half to;} _converter_v2931_to_v2932 = {};
        _converter_v2931_to_v2932.from = v2931;
        v2932 = _converter_v2931_to_v2932.to;	// L4673
        rxv3[2] = v2932;	// L4674
        rxvld3[2] = 1;	// L4675
      }
    }
    uint8_t v2933 = hold_cnt3[3];	// L4678
    int32_t v2934 = v2933;	// L4679
    bool v2935 = v2934 < 2;	// L4680
    if (v2935) {	// L4681
      ap_uint<17> v2936;
      bool v2937 = v2636.read_nb(v2936);
	// L4682
      ap_uint<17> sge3;	// L4683
      sge3 = v2936;	// L4684
      bool sqe3;	// L4685
      sqe3 = v2937;	// L4686
      bool v2940 = sqe3;	// L4687
      int32_t v2941 = v2940;	// L4688
      bool v2942 = v2941 == 1;	// L4689
      if (v2942) {	// L4690
        ap_int<17> v2943 = sge3;	// L4691
        int16_t v2944;
        ap_int<17> v2944_tmp = v2943;
        v2944 = v2944_tmp(16, 1);	// L4692
        half v2945;
        union { uint16_t from; half to;} _converter_v2944_to_v2945 = {};
        _converter_v2944_to_v2945.from = v2944;
        v2945 = _converter_v2944_to_v2945.to;	// L4693
        rxv3[3] = v2945;	// L4694
        rxvld3[3] = 1;	// L4695
      }
    }
    l_S_d_4_d15: for (int d15 = 0; d15 < 4; d15++) {	// L4698
      int32_t v2947 = rxvld3[d15];	// L4699
      bool v2948 = v2947 == 1;	// L4700
      if (v2948) {	// L4701
        half v2949 = rxv3[d15];	// L4702
        uint8_t v2950 = hold_cnt3[d15];	// L4703
        int v2951 = v2950;	// L4704
        hold_v3[d15][v2951] = v2949;	// L4705
        uint8_t v2952 = hold_cnt3[d15];	// L4706
        ap_int<33> v2953 = v2952;	// L4707
        ap_int<33> v2954 = v2953 + 1;	// L4708
        uint8_t v2955 = v2954;	// L4709
        hold_cnt3[d15] = v2955;	// L4710
      }
    }
    ap_uint<17> tx_n3;	// L4713
    tx_n3 = 0;	// L4714
    ap_uint<17> tx_s3;	// L4715
    tx_s3 = 0;	// L4716
    ap_uint<17> tx_w3;	// L4717
    tx_w3 = 0;	// L4718
    ap_uint<17> tx_e3;	// L4719
    tx_e3 = 0;	// L4720
    uint8_t v2960 = sb_v3[0];	// L4721
    int32_t v2961 = v2960;	// L4722
    bool v2962 = v2961 == 1;	// L4723
    if (v2962) {	// L4724
      uint8_t v2963 = sb_ix3[0];	// L4725
      int v2964 = v2963;	// L4726
      half v2965 = resq3[v2964];	// L4727
      half wb3;
#pragma HLS dependence variable=wb3 type=inter dependent=false	// L4728
      wb3 = v2965;	// L4729
      uint8_t v2967 = sb_cmp3[0];	// L4730
      int32_t v2968 = v2967;	// L4731
      bool v2969 = v2968 == 1;	// L4732
      if (v2969) {	// L4733
        uint8_t v2970 = sb_ix3[0];	// L4734
        int v2971 = v2970;	// L4735
        uint8_t v2972 = cmpq3[v2971];	// L4736
        condition_reg3 = v2972;	// L4737
      }
      uint8_t v2973 = sb_rtr3[0];	// L4739
      int32_t v2974 = v2973;	// L4740
      bool v2975 = v2974 == 1;	// L4741
      if (v2975) {	// L4742
        uint8_t v2976 = sb_inj3[0];	// L4743
        int32_t v2977 = v2976;	// L4744
        bool v2978 = v2977 == 1;	// L4745
        ap_int<26> v2979 = csd_pkt3;	// L4746
        bool v2980;
        ap_int<26> v2980_tmp = v2979;
        v2980 = v2980_tmp[25];	// L4747
        int32_t v2981 = v2980;	// L4748
        bool v2982 = v2981 == 0;	// L4749
        bool v2983 = v2978 & v2982;	// L4750
        if (v2983) {	// L4751
          half v2984 = wb3;	// L4752
          uint16_t v2985;
          union { half from; uint16_t to;} _converter_v2984_to_v2985 = {};
          _converter_v2984_to_v2985.from = v2984;
          v2985 = _converter_v2984_to_v2985.to;	// L4753
          ap_int<26> v2986 = csd_pkt3;	// L4754
          ap_int<26> v2987;
          ap_int<26> v2987_tmp = v2986;
          v2987_tmp(15, 0) = v2985;
          v2987 = v2987_tmp;	// L4755
          csd_pkt3 = v2987;	// L4756
          uint8_t v2988 = sb_dst3[0];	// L4757
          ap_uint<4> v2989 = v2988;	// L4758
          ap_int<26> v2990 = csd_pkt3;	// L4759
          ap_int<26> v2991;
          ap_int<26> v2991_tmp = v2990;
          v2991_tmp(19, 16) = v2989;
          v2991 = v2991_tmp;	// L4760
          csd_pkt3 = v2991;	// L4761
          uint8_t v2992 = sb_id3[0];	// L4762
          ap_uint<4> v2993 = v2992;	// L4763
          ap_int<26> v2994 = csd_pkt3;	// L4764
          ap_int<26> v2995;
          ap_int<26> v2995_tmp = v2994;
          v2995_tmp(24, 21) = v2993;
          v2995 = v2995_tmp;	// L4765
          csd_pkt3 = v2995;	// L4766
          uint8_t v2996 = sb_rvld3[0];	// L4767
          bool v2997 = v2996;	// L4768
          ap_int<26> v2998 = csd_pkt3;	// L4769
          ap_int<26> v2999;
          ap_int<26> v2999_tmp = v2998;
          v2999_tmp[25] = v2997;          v2999 = v2999_tmp;	// L4770
          csd_pkt3 = v2999;	// L4771
          uint8_t v3000 = sb_dir3[0];	// L4772
          int32_t v3001 = v3000;	// L4773
          csd_dir3 = v3001;	// L4774
        }
      } else {
        uint8_t v3002 = sb_dst3[0];	// L4777
        int32_t v3003 = v3002;	// L4778
        bool v3004 = v3003 >= 12;	// L4779
        if (v3004) {	// L4780
          ap_uint<17> tw03;	// L4781
          tw03 = 0;	// L4782
          uint8_t v3006 = sb_rvld3[0];	// L4783
          bool v3007 = v3006;	// L4784
          ap_int<17> v3008 = tw03;	// L4785
          ap_int<17> v3009;
          ap_int<17> v3009_tmp = v3008;
          v3009_tmp[0] = v3007;          v3009 = v3009_tmp;	// L4786
          tw03 = v3009;	// L4787
          half v3010 = wb3;	// L4788
          uint16_t v3011;
          union { half from; uint16_t to;} _converter_v3010_to_v3011 = {};
          _converter_v3010_to_v3011.from = v3010;
          v3011 = _converter_v3010_to_v3011.to;	// L4789
          ap_int<17> v3012 = tw03;	// L4790
          ap_int<17> v3013;
          ap_int<17> v3013_tmp = v3012;
          v3013_tmp(16, 1) = v3011;
          v3013 = v3013_tmp;	// L4791
          tw03 = v3013;	// L4792
          uint8_t v3014 = sb_dst3[0];	// L4793
          int32_t v3015 = v3014;	// L4794
          int32_t v3016 = v3015 & 3;	// L4795
          bool v3017 = v3016 == 0;	// L4796
          if (v3017) {	// L4797
            ap_int<17> v3018 = tw03;	// L4798
            tx_n3 = v3018;	// L4799
          } else {
            uint8_t v3019 = sb_dst3[0];	// L4801
            int32_t v3020 = v3019;	// L4802
            int32_t v3021 = v3020 & 3;	// L4803
            bool v3022 = v3021 == 1;	// L4804
            if (v3022) {	// L4805
              ap_int<17> v3023 = tw03;	// L4806
              tx_s3 = v3023;	// L4807
            } else {
              uint8_t v3024 = sb_dst3[0];	// L4809
              int32_t v3025 = v3024;	// L4810
              int32_t v3026 = v3025 & 3;	// L4811
              bool v3027 = v3026 == 2;	// L4812
              if (v3027) {	// L4813
                ap_int<17> v3028 = tw03;	// L4814
                tx_w3 = v3028;	// L4815
              } else {
                ap_int<17> v3029 = tw03;	// L4817
                tx_e3 = v3029;	// L4818
              }
            }
          }
        } else {
          uint8_t v3030 = sb_rvld3[0];	// L4823
          int32_t v3031 = v3030;	// L4824
          bool v3032 = v3031 == 1;	// L4825
          if (v3032) {	// L4826
            uint8_t v3033 = sb_dst3[0];	// L4827
            int32_t v3034 = v3033;	// L4828
            bool v3035 = v3034 < 8;	// L4829
            int32_t v3036 = dsmask3;	// L4830
            int32_t v3037 = v3036 >> v3034;	// L4831
            int32_t v3038 = v3037 & 1;	// L4832
            bool v3039 = v3038 == 1;	// L4833
            bool v3040 = v3035 & v3039;	// L4834
            if (v3040) {	// L4835
              uint8_t v3041 = sb_dst3[0];	// L4836
              int v3042 = v3041;	// L4837
              int32_t v3043 = drf_full3[v3042];	// L4838
              bool v3044 = v3043 == 0;	// L4839
              if (v3044) {	// L4840
                half v3045 = wb3;	// L4841
                uint8_t v3046 = sb_dst3[0];	// L4842
                int v3047 = v3046;	// L4843
                drf3[v3047] = v3045;	// L4844
                uint8_t v3048 = sb_dst3[0];	// L4845
                int v3049 = v3048;	// L4846
                drf_full3[v3049] = 1;	// L4847
              }
            } else {
              half v3050 = wb3;	// L4850
              uint8_t v3051 = sb_dst3[0];	// L4851
              int32_t v3052 = v3051;	// L4852
              int32_t v3053 = v3052 & 7;	// L4853
              int v3054 = v3053;	// L4854
              drf3[v3054] = v3050;	// L4855
            }
          }
        }
      }
    }
    int32_t pc3;	// L4861
    pc3 = -1;	// L4862
    int8_t v3056 = fetch_en3;	// L4863
    int32_t v3057 = v3056;	// L4864
    bool v3058 = v3057 == 1;	// L4865
    if (v3058) {	// L4866
      int8_t v3059 = instr_cnt3;	// L4867
      int32_t v3060 = v3059;	// L4868
      pc3 = v3060;	// L4869
    }
    int8_t v3061 = fetch_en3;	// L4871
    int32_t v3062 = v3061;	// L4872
    bool v3063 = v3062 == 1;	// L4873
    if (v3063) {	// L4874
      fe_ever3 = 1;	// L4875
    }
    int32_t instr3;	// L4877
    instr3 = 0;	// L4878
    int32_t v3065 = pc3;	// L4879
    bool v3066 = v3065 >= 0;	// L4880
    if (v3066) {	// L4881
      int32_t v3067 = pc3;	// L4882
      int v3068 = v3067;	// L4883
      int32_t v3069 = irf3[v3068];	// L4884
      instr3 = v3069;	// L4885
    }
    int32_t v3070 = instr3;	// L4887
    int32_t v3071 = v3070 & 15;	// L4888
    int32_t op3;	// L4889
    op3 = v3071;	// L4890
    int32_t v3073 = instr3;	// L4891
    int32_t v3074 = v3073 >> 4;	// L4892
    int32_t v3075 = v3074 & 15;	// L4893
    int32_t dst3;	// L4894
    dst3 = v3075;	// L4895
    int32_t v3077 = instr3;	// L4896
    int32_t v3078 = v3077 >> 8;	// L4897
    int32_t v3079 = v3078 & 15;	// L4898
    int32_t s13;	// L4899
    s13 = v3079;	// L4900
    int32_t v3081 = instr3;	// L4901
    int32_t v3082 = v3081 >> 12;	// L4902
    int32_t v3083 = v3082 & 15;	// L4903
    int32_t s23;	// L4904
    s23 = v3083;	// L4905
    half a3;	// L4906
    a3 = 0.000000;	// L4907
    half b3;	// L4908
    b3 = 0.000000;	// L4909
    int32_t v3087 = s13;	// L4910
    bool v3088 = v3087 >= 12;	// L4911
    if (v3088) {	// L4912
      int32_t v3089 = s13;	// L4913
      int32_t v3090 = v3089 & 3;	// L4914
      int v3091 = v3090;	// L4915
      half v3092 = hold_v3[v3091][0];	// L4916
      a3 = v3092;	// L4917
    } else {
      int32_t v3093 = s13;	// L4919
      int v3094 = v3093;	// L4920
      half v3095 = drf3[v3094];	// L4921
      a3 = v3095;	// L4922
    }
    int32_t v3096 = s23;	// L4924
    bool v3097 = v3096 >= 12;	// L4925
    if (v3097) {	// L4926
      int32_t v3098 = s23;	// L4927
      int32_t v3099 = v3098 & 3;	// L4928
      int v3100 = v3099;	// L4929
      half v3101 = hold_v3[v3100][0];	// L4930
      b3 = v3101;	// L4931
    } else {
      int32_t v3102 = s23;	// L4933
      int v3103 = v3102;	// L4934
      half v3104 = drf3[v3103];	// L4935
      b3 = v3104;	// L4936
    }
    int32_t a_vld3;	// L4938
    a_vld3 = 1;	// L4939
    int32_t b_vld3;	// L4940
    b_vld3 = 1;	// L4941
    int32_t v3107 = s13;	// L4942
    bool v3108 = v3107 >= 12;	// L4943
    if (v3108) {	// L4944
      a_vld3 = 0;	// L4945
      int32_t v3109 = s13;	// L4946
      int32_t v3110 = v3109 & 3;	// L4947
      int v3111 = v3110;	// L4948
      uint8_t v3112 = hold_cnt3[v3111];	// L4949
      int32_t v3113 = v3112;	// L4950
      bool v3114 = v3113 > 0;	// L4951
      if (v3114) {	// L4952
        a_vld3 = 1;	// L4953
      }
    }
    int32_t v3115 = s23;	// L4956
    bool v3116 = v3115 >= 12;	// L4957
    if (v3116) {	// L4958
      b_vld3 = 0;	// L4959
      int32_t v3117 = s23;	// L4960
      int32_t v3118 = v3117 & 3;	// L4961
      int v3119 = v3118;	// L4962
      uint8_t v3120 = hold_cnt3[v3119];	// L4963
      int32_t v3121 = v3120;	// L4964
      bool v3122 = v3121 > 0;	// L4965
      if (v3122) {	// L4966
        b_vld3 = 1;	// L4967
      }
    }
    int32_t v3123 = s13;	// L4970
    bool v3124 = v3123 < 8;	// L4971
    int32_t v3125 = dsmask3;	// L4972
    int32_t v3126 = v3125 >> v3123;	// L4973
    int32_t v3127 = v3126 & 1;	// L4974
    bool v3128 = v3127 == 1;	// L4975
    bool v3129 = v3124 & v3128;	// L4976
    if (v3129) {	// L4977
      int32_t v3130 = s13;	// L4978
      int v3131 = v3130;	// L4979
      int32_t v3132 = drf_full3[v3131];	// L4980
      bool v3133 = v3132 == 0;	// L4981
      if (v3133) {	// L4982
        a_vld3 = 0;	// L4983
      }
    }
    int32_t v3134 = s23;	// L4986
    bool v3135 = v3134 < 8;	// L4987
    int32_t v3136 = dsmask3;	// L4988
    int32_t v3137 = v3136 >> v3134;	// L4989
    int32_t v3138 = v3137 & 1;	// L4990
    bool v3139 = v3138 == 1;	// L4991
    bool v3140 = v3135 & v3139;	// L4992
    if (v3140) {	// L4993
      int32_t v3141 = s23;	// L4994
      int v3142 = v3141;	// L4995
      int32_t v3143 = drf_full3[v3142];	// L4996
      bool v3144 = v3143 == 0;	// L4997
      if (v3144) {	// L4998
        b_vld3 = 0;	// L4999
      }
    }
    int32_t binop3;	// L5002
    binop3 = 0;	// L5003
    int32_t v3146 = op3;	// L5004
    bool v3147 = v3146 == 0;	// L5005
    bool v3148 = v3146 == 1;	// L5006
    bool v3149 = v3146 == 2;	// L5007
    bool v3150 = v3146 == 8;	// L5008
    bool v3151 = v3146 == 9;	// L5009
    bool v3152 = v3147 | v3148;	// L5010
    bool v3153 = v3152 | v3149;	// L5011
    bool v3154 = v3153 | v3150;	// L5012
    bool v3155 = v3154 | v3151;	// L5013
    if (v3155) {	// L5014
      binop3 = 1;	// L5015
    }
    int32_t raw3;	// L5017
    raw3 = 0;	// L5018
    int32_t cmp_busy3;	// L5019
    cmp_busy3 = 0;	// L5020
    l_S_k_5_k6: for (int k6 = 0; k6 < 4; k6++) {	// L5021
      uint8_t v3159 = sb_v3[(k6 + 1)];	// L5022
      int32_t v3160 = v3159;	// L5023
      bool v3161 = v3160 == 1;	// L5024
      uint8_t v3162 = sb_rtr3[(k6 + 1)];	// L5025
      int32_t v3163 = v3162;	// L5026
      bool v3164 = v3163 == 0;	// L5027
      uint8_t v3165 = sb_dst3[(k6 + 1)];	// L5028
      int32_t v3166 = v3165;	// L5029
      bool v3167 = v3166 < 12;	// L5030
      bool v3168 = v3161 & v3164;	// L5031
      bool v3169 = v3168 & v3167;	// L5032
      if (v3169) {	// L5033
        int32_t v3170 = s13;	// L5034
        bool v3171 = v3170 < 12;	// L5035
        uint8_t v3172 = sb_dst3[(k6 + 1)];	// L5036
        int32_t v3173 = v3172;	// L5037
        int32_t v3174 = v3173 & 7;	// L5038
        int32_t v3175 = v3170 & 7;	// L5039
        bool v3176 = v3174 == v3175;	// L5040
        bool v3177 = v3171 & v3176;	// L5041
        if (v3177) {	// L5042
          raw3 = 1;	// L5043
        }
        int32_t v3178 = binop3;	// L5045
        bool v3179 = v3178 == 1;	// L5046
        int32_t v3180 = s23;	// L5047
        bool v3181 = v3180 < 12;	// L5048
        uint8_t v3182 = sb_dst3[(k6 + 1)];	// L5049
        int32_t v3183 = v3182;	// L5050
        int32_t v3184 = v3183 & 7;	// L5051
        int32_t v3185 = v3180 & 7;	// L5052
        bool v3186 = v3184 == v3185;	// L5053
        bool v3187 = v3179 & v3181;	// L5054
        bool v3188 = v3187 & v3186;	// L5055
        if (v3188) {	// L5056
          raw3 = 1;	// L5057
        }
      }
      uint8_t v3189 = sb_v3[(k6 + 1)];	// L5060
      int32_t v3190 = v3189;	// L5061
      bool v3191 = v3190 == 1;	// L5062
      uint8_t v3192 = sb_cmp3[(k6 + 1)];	// L5063
      int32_t v3193 = v3192;	// L5064
      bool v3194 = v3193 == 1;	// L5065
      bool v3195 = v3191 & v3194;	// L5066
      if (v3195) {	// L5067
        cmp_busy3 = 1;	// L5068
      }
    }
    int32_t is_cond3;	// L5071
    is_cond3 = 0;	// L5072
    int32_t v3197 = op3;	// L5073
    bool v3198 = v3197 >= 12;	// L5074
    ap_int<33> v3199 = v3197;	// L5075
    bool v3200 = v3199 <= 15;	// L5076
    bool v3201 = v3198 & v3200;	// L5077
    if (v3201) {	// L5078
      is_cond3 = 1;	// L5079
    }
    int32_t grant3;	// L5081
    grant3 = 0;	// L5082
    int32_t v3203 = pc3;	// L5083
    bool v3204 = v3203 >= 0;	// L5084
    if (v3204) {	// L5085
      grant3 = 1;	// L5086
    }
    int32_t v3205 = pc3;	// L5088
    bool v3206 = v3205 >= 0;	// L5089
    int32_t v3207 = a_vld3;	// L5090
    bool v3208 = v3207 == 0;	// L5091
    int32_t v3209 = binop3;	// L5092
    bool v3210 = v3209 == 1;	// L5093
    int32_t v3211 = b_vld3;	// L5094
    bool v3212 = v3211 == 0;	// L5095
    bool v3213 = v3210 & v3212;	// L5096
    bool v3214 = v3208 | v3213;	// L5097
    bool v3215 = v3206 & v3214;	// L5098
    if (v3215) {	// L5099
      grant3 = 0;	// L5100
    }
    int32_t v3216 = pc3;	// L5102
    bool v3217 = v3216 >= 0;	// L5103
    int32_t v3218 = raw3;	// L5104
    bool v3219 = v3218 == 1;	// L5105
    int32_t v3220 = is_cond3;	// L5106
    bool v3221 = v3220 == 1;	// L5107
    int32_t v3222 = cmp_busy3;	// L5108
    bool v3223 = v3222 == 1;	// L5109
    bool v3224 = v3221 & v3223;	// L5110
    bool v3225 = v3219 | v3224;	// L5111
    bool v3226 = v3217 & v3225;	// L5112
    if (v3226) {	// L5113
      grant3 = 0;	// L5114
    }
    int32_t v3227 = grant3;	// L5116
    bool v3228 = v3227 == 1;	// L5117
    if (v3228) {	// L5118
      int8_t v3229 = instr_cnt3;	// L5119
      int32_t v3230 = cfg_isz3;	// L5120
      int32_t v3231 = v3229;	// L5121
      bool v3232 = v3231 == v3230;	// L5122
      if (v3232) {	// L5123
        instr_cnt3 = 0;	// L5124
        int8_t v3233 = iter_cnt3;	// L5125
        int32_t v3234 = cfg_itsz3;	// L5126
        ap_int<33> v3235 = v3234;	// L5127
        ap_int<33> v3236 = v3235 - 1;	// L5128
        ap_int<33> v3237 = v3233;	// L5129
        bool v3238 = v3237 == v3236;	// L5130
        if (v3238) {	// L5131
          fetch_en3 = 0;	// L5132
        } else {
          int8_t v3239 = iter_cnt3;	// L5134
          ap_int<33> v3240 = v3239;	// L5135
          ap_int<33> v3241 = v3240 + 1;	// L5136
          uint8_t v3242 = v3241;	// L5137
          iter_cnt3 = v3242;	// L5138
        }
      } else {
        int8_t v3243 = instr_cnt3;	// L5141
        ap_int<33> v3244 = v3243;	// L5142
        ap_int<33> v3245 = v3244 + 1;	// L5143
        uint8_t v3246 = v3245;	// L5144
        instr_cnt3 = v3246;	// L5145
      }
    }
    int32_t c13;	// L5148
    c13 = -1;	// L5149
    int32_t c23;	// L5150
    c23 = -1;	// L5151
    int32_t v3249 = grant3;	// L5152
    bool v3250 = v3249 == 1;	// L5153
    int32_t v3251 = s13;	// L5154
    bool v3252 = v3251 >= 12;	// L5155
    bool v3253 = v3250 & v3252;	// L5156
    if (v3253) {	// L5157
      int32_t v3254 = s13;	// L5158
      int32_t v3255 = v3254 & 3;	// L5159
      c13 = v3255;	// L5160
    }
    int32_t v3256 = grant3;	// L5162
    bool v3257 = v3256 == 1;	// L5163
    int32_t v3258 = s23;	// L5164
    bool v3259 = v3258 >= 12;	// L5165
    bool v3260 = v3257 & v3259;	// L5166
    if (v3260) {	// L5167
      int32_t v3261 = s23;	// L5168
      int32_t v3262 = v3261 & 3;	// L5169
      c23 = v3262;	// L5170
    }
    int32_t v3263 = c13;	// L5172
    bool v3264 = v3263 >= 0;	// L5173
    if (v3264) {	// L5174
      int32_t v3265 = c13;	// L5175
      int v3266 = v3265;	// L5176
      half v3267 = hold_v3[v3266][1];	// L5177
      hold_v3[v3266][0] = v3267;	// L5178
      int32_t v3268 = c13;	// L5179
      int v3269 = v3268;	// L5180
      uint8_t v3270 = hold_cnt3[v3269];	// L5181
      ap_int<33> v3271 = v3270;	// L5182
      ap_int<33> v3272 = v3271 - 1;	// L5183
      uint8_t v3273 = v3272;	// L5184
      hold_cnt3[v3269] = v3273;	// L5185
    }
    int32_t v3274 = c23;	// L5187
    bool v3275 = v3274 >= 0;	// L5188
    int32_t v3276 = c13;	// L5189
    bool v3277 = v3274 != v3276;	// L5190
    bool v3278 = v3275 & v3277;	// L5191
    if (v3278) {	// L5192
      int32_t v3279 = c23;	// L5193
      int v3280 = v3279;	// L5194
      half v3281 = hold_v3[v3280][1];	// L5195
      hold_v3[v3280][0] = v3281;	// L5196
      int32_t v3282 = c23;	// L5197
      int v3283 = v3282;	// L5198
      uint8_t v3284 = hold_cnt3[v3283];	// L5199
      ap_int<33> v3285 = v3284;	// L5200
      ap_int<33> v3286 = v3285 - 1;	// L5201
      uint8_t v3287 = v3286;	// L5202
      hold_cnt3[v3283] = v3287;	// L5203
    }
    int32_t v3288 = grant3;	// L5205
    bool v3289 = v3288 == 1;	// L5206
    int32_t v3290 = s13;	// L5207
    bool v3291 = v3290 < 8;	// L5208
    int32_t v3292 = dsmask3;	// L5209
    int32_t v3293 = v3292 >> v3290;	// L5210
    int32_t v3294 = v3293 & 1;	// L5211
    bool v3295 = v3294 == 1;	// L5212
    bool v3296 = v3289 & v3291;	// L5213
    bool v3297 = v3296 & v3295;	// L5214
    if (v3297) {	// L5215
      int32_t v3298 = s13;	// L5216
      int v3299 = v3298;	// L5217
      drf_full3[v3299] = 0;	// L5218
    }
    int32_t v3300 = grant3;	// L5220
    bool v3301 = v3300 == 1;	// L5221
    int32_t v3302 = s23;	// L5222
    bool v3303 = v3302 < 8;	// L5223
    int32_t v3304 = dsmask3;	// L5224
    int32_t v3305 = v3304 >> v3302;	// L5225
    int32_t v3306 = v3305 & 1;	// L5226
    bool v3307 = v3306 == 1;	// L5227
    bool v3308 = v3301 & v3303;	// L5228
    bool v3309 = v3308 & v3307;	// L5229
    if (v3309) {	// L5230
      int32_t v3310 = s23;	// L5231
      int v3311 = v3310;	// L5232
      drf_full3[v3311] = 0;	// L5233
    }
    half res3;
#pragma HLS dependence variable=res3 type=inter dependent=false	// L5235
    res3 = 0.000000;	// L5236
    int32_t v3313 = op3;	// L5237
    bool v3314 = v3313 == 0;	// L5238
    if (v3314) {	// L5239
      half v3315 = a3;	// L5240
      half v3316 = b3;	// L5241
      half v3317 = v3315 + v3316;	// L5242
      res3 = v3317;	// L5243
    } else {
      int32_t v3318 = op3;	// L5245
      bool v3319 = v3318 == 1;	// L5246
      if (v3319) {	// L5247
        half v3320 = a3;	// L5248
        half v3321 = b3;	// L5249
        half v3322 = v3320 - v3321;	// L5250
        res3 = v3322;	// L5251
      } else {
        int32_t v3323 = op3;	// L5253
        bool v3324 = v3323 == 2;	// L5254
        if (v3324) {	// L5255
          half v3325 = a3;	// L5256
          half v3326 = b3;	// L5257
          half v3327 = v3325 * v3326;	// L5258
          res3 = v3327;	// L5259
        } else {
          int32_t v3328 = op3;	// L5261
          bool v3329 = v3328 == 8;	// L5262
          if (v3329) {	// L5263
            half v3330 = a3;	// L5264
            half v3331 = b3;	// L5265
            bool v3332 = v3330 >= v3331;	// L5266
            if (v3332) {	// L5267
              res3 = 1.000000;	// L5268
            } else {
              res3 = -1.000000;	// L5270
            }
          } else {
            int32_t v3333 = op3;	// L5273
            bool v3334 = v3333 == 9;	// L5274
            if (v3334) {	// L5275
              half v3335 = a3;	// L5276
              half v3336 = b3;	// L5277
              bool v3337 = v3335 < v3336;	// L5278
              if (v3337) {	// L5279
                res3 = 1.000000;	// L5280
              } else {
                res3 = -1.000000;	// L5282
              }
            } else {
              half v3338 = a3;	// L5285
              res3 = v3338;	// L5286
            }
          }
        }
      }
    }
    int32_t v3339 = a_vld3;	// L5292
    int32_t res_vld3;	// L5293
    res_vld3 = v3339;	// L5294
    int32_t v3341 = op3;	// L5295
    bool v3342 = v3341 == 0;	// L5296
    bool v3343 = v3341 == 1;	// L5297
    bool v3344 = v3341 == 2;	// L5298
    bool v3345 = v3341 == 8;	// L5299
    bool v3346 = v3341 == 9;	// L5300
    bool v3347 = v3342 | v3343;	// L5301
    bool v3348 = v3347 | v3344;	// L5302
    bool v3349 = v3348 | v3345;	// L5303
    bool v3350 = v3349 | v3346;	// L5304
    if (v3350) {	// L5305
      int32_t v3351 = a_vld3;	// L5306
      int32_t v3352 = b_vld3;	// L5307
      int64_t v3353 = v3351;	// L5308
      int64_t v3354 = v3352;	// L5309
      int64_t v3355 = v3353 * v3354;	// L5310
      int32_t v3356 = v3355;	// L5311
      res_vld3 = v3356;	// L5312
    }
    int32_t v3357 = grant3;	// L5314
    bool v3358 = v3357 == 0;	// L5315
    if (v3358) {	// L5316
      res_vld3 = 0;	// L5317
    }
    int32_t is_rtr3;	// L5319
    is_rtr3 = 0;	// L5320
    int32_t v3360 = op3;	// L5321
    bool v3361 = v3360 >= 4;	// L5322
    ap_int<33> v3362 = v3360;	// L5323
    bool v3363 = v3362 <= 7;	// L5324
    bool v3364 = v3361 & v3363;	// L5325
    if (v3364) {	// L5326
      is_rtr3 = 1;	// L5327
    }
    l_S_k_6_k7: for (int k7 = 0; k7 < 4; k7++) {	// L5329
      uint8_t v3366 = sb_v3[(k7 + 1)];	// L5330
      sb_v3[k7] = v3366;	// L5331
      uint8_t v3367 = sb_dst3[(k7 + 1)];	// L5332
      sb_dst3[k7] = v3367;	// L5333
      uint8_t v3368 = sb_cmp3[(k7 + 1)];	// L5334
      sb_cmp3[k7] = v3368;	// L5335
      uint8_t v3369 = sb_rtr3[(k7 + 1)];	// L5336
      sb_rtr3[k7] = v3369;	// L5337
      uint8_t v3370 = sb_inj3[(k7 + 1)];	// L5338
      sb_inj3[k7] = v3370;	// L5339
      uint8_t v3371 = sb_dir3[(k7 + 1)];	// L5340
      sb_dir3[k7] = v3371;	// L5341
      uint8_t v3372 = sb_id3[(k7 + 1)];	// L5342
      sb_id3[k7] = v3372;	// L5343
      uint8_t v3373 = sb_rvld3[(k7 + 1)];	// L5344
      sb_rvld3[k7] = v3373;	// L5345
      uint8_t v3374 = sb_ix3[(k7 + 1)];	// L5346
      sb_ix3[k7] = v3374;	// L5347
    }
    sb_v3[4] = 0;	// L5349
    int32_t v3375 = grant3;	// L5350
    bool v3376 = v3375 == 1;	// L5351
    if (v3376) {	// L5352
      half v3377 = res3;	// L5353
      int8_t v3378 = resq_wr3;	// L5354
      int v3379 = v3378;	// L5355
      resq3[v3379] = v3377;	// L5356
      int32_t cq3;	// L5357
      cq3 = 0;	// L5358
      int32_t v3381 = op3;	// L5359
      bool v3382 = v3381 == 8;	// L5360
      if (v3382) {	// L5361
        half v3383 = a3;	// L5362
        half v3384 = b3;	// L5363
        bool v3385 = v3383 >= v3384;	// L5364
        if (v3385) {	// L5365
          cq3 = 1;	// L5366
        }
      }
      int32_t v3386 = op3;	// L5369
      bool v3387 = v3386 == 9;	// L5370
      if (v3387) {	// L5371
        half v3388 = a3;	// L5372
        half v3389 = b3;	// L5373
        bool v3390 = v3388 < v3389;	// L5374
        if (v3390) {	// L5375
          cq3 = 1;	// L5376
        }
      }
      int32_t v3391 = cq3;	// L5379
      uint8_t v3392 = v3391;	// L5380
      int8_t v3393 = resq_wr3;	// L5381
      int v3394 = v3393;	// L5382
      cmpq3[v3394] = v3392;	// L5383
      sb_v3[4] = 1;	// L5384
      int32_t v3395 = dst3;	// L5385
      uint8_t v3396 = v3395;	// L5386
      sb_dst3[4] = v3396;	// L5387
      int8_t v3397 = resq_wr3;	// L5388
      sb_ix3[4] = v3397;	// L5389
      sb_cmp3[4] = 0;	// L5390
      int32_t v3398 = op3;	// L5391
      bool v3399 = v3398 == 8;	// L5392
      bool v3400 = v3398 == 9;	// L5393
      bool v3401 = v3399 | v3400;	// L5394
      if (v3401) {	// L5395
        sb_cmp3[4] = 1;	// L5396
      }
      int32_t v3402 = is_rtr3;	// L5398
      int32_t rtrf3;	// L5399
      rtrf3 = v3402;	// L5400
      int32_t v3404 = is_cond3;	// L5401
      bool v3405 = v3404 == 1;	// L5402
      if (v3405) {	// L5403
        rtrf3 = 1;	// L5404
      }
      int32_t v3406 = rtrf3;	// L5406
      uint8_t v3407 = v3406;	// L5407
      sb_rtr3[4] = v3407;	// L5408
      int32_t v3408 = is_rtr3;	// L5409
      int32_t inj3;	// L5410
      inj3 = v3408;	// L5411
      int32_t v3410 = is_cond3;	// L5412
      bool v3411 = v3410 == 1;	// L5413
      int8_t v3412 = condition_reg3;	// L5414
      int32_t v3413 = v3412;	// L5415
      bool v3414 = v3413 == 1;	// L5416
      bool v3415 = v3411 & v3414;	// L5417
      if (v3415) {	// L5418
        inj3 = 1;	// L5419
      }
      int32_t v3416 = inj3;	// L5421
      uint8_t v3417 = v3416;	// L5422
      sb_inj3[4] = v3417;	// L5423
      int32_t v3418 = op3;	// L5424
      int32_t v3419 = v3418 & 3;	// L5425
      uint8_t v3420 = v3419;	// L5426
      sb_dir3[4] = v3420;	// L5427
      int32_t v3421 = s23;	// L5428
      uint8_t v3422 = v3421;	// L5429
      sb_id3[4] = v3422;	// L5430
      int32_t v3423 = res_vld3;	// L5431
      uint8_t v3424 = v3423;	// L5432
      sb_rvld3[4] = v3424;	// L5433
      int8_t v3425 = resq_wr3;	// L5434
      ap_int<33> v3426 = v3425;	// L5435
      ap_int<33> v3427 = v3426 + 1;	// L5436
      ap_int<33> v3428 = v3427 & 7;	// L5437
      uint8_t v3429 = v3428;	// L5438
      resq_wr3 = v3429;	// L5439
    }
    ap_int<17> v3430 = tx_n3;	// L5441
    txn_r3 = v3430;	// L5442
    ap_int<17> v3431 = tx_s3;	// L5443
    txs_r3 = v3431;	// L5444
    ap_int<17> v3432 = tx_w3;	// L5445
    txw_r3 = v3432;	// L5446
    ap_int<17> v3433 = tx_e3;	// L5447
    txe_r3 = v3433;	// L5448
    int32_t v3434 = crv_vld3;	// L5449
    bool v3435 = v3434 == 1;	// L5450
    if (v3435) {	// L5451
      int32_t v3436 = crv_mode3;	// L5452
      bool v3437 = v3436 == 1;	// L5453
      if (v3437) {	// L5454
        int32_t v3438 = crv_addr3;	// L5455
        int32_t v3439 = v3438 >> 3;	// L5456
        int32_t v3440 = v3439 & 1;	// L5457
        bool v3441 = v3440 == 1;	// L5458
        if (v3441) {	// L5459
          int32_t v3442 = crv_raw3;	// L5460
          int32_t v3443 = crv_addr3;	// L5461
          int32_t v3444 = v3443 & 7;	// L5462
          int v3445 = v3444;	// L5463
          irf3[v3445] = v3442;	// L5464
        } else {
          int32_t v3446 = crv_addr3;	// L5466
          bool v3447 = v3446 == 0;	// L5467
          if (v3447) {	// L5468
            int32_t v3448 = crv_raw3;	// L5469
            int32_t v3449 = v3448 & 255;	// L5470
            dsmask3 = v3449;	// L5471
            int32_t v3450 = crv_raw3;	// L5472
            int32_t v3451 = v3450 >> 8;	// L5473
            int32_t v3452 = v3451 & 7;	// L5474
            cfg_isz3 = v3452;	// L5475
            int32_t v3453 = crv_raw3;	// L5476
            int32_t v3454 = v3453 >> 15;	// L5477
            int32_t v3455 = v3454 & 1;	// L5478
            bool v3456 = v3455 == 1;	// L5479
            if (v3456) {	// L5480
              fetch_en3 = 1;	// L5481
              instr_cnt3 = 0;	// L5482
              iter_cnt3 = 0;	// L5483
            }
          } else {
            int32_t v3457 = crv_addr3;	// L5486
            bool v3458 = v3457 == 1;	// L5487
            if (v3458) {	// L5488
              int32_t v3459 = crv_raw3;	// L5489
              int32_t v3460 = v3459 & 255;	// L5490
              cfg_itsz3 = v3460;	// L5491
            }
          }
        }
      } else {
        int32_t v3461 = crv_addr3;	// L5496
        bool v3462 = v3461 < 8;	// L5497
        int32_t v3463 = dsmask3;	// L5498
        int32_t v3464 = v3463 >> v3461;	// L5499
        int32_t v3465 = v3464 & 1;	// L5500
        bool v3466 = v3465 == 1;	// L5501
        bool v3467 = v3462 & v3466;	// L5502
        if (v3467) {	// L5503
          int32_t v3468 = crv_addr3;	// L5504
          int v3469 = v3468;	// L5505
          int32_t v3470 = drf_full3[v3469];	// L5506
          bool v3471 = v3470 == 0;	// L5507
          if (v3471) {	// L5508
            half v3472 = crv_data3;	// L5509
            int32_t v3473 = crv_addr3;	// L5510
            int v3474 = v3473;	// L5511
            drf3[v3474] = v3472;	// L5512
            int32_t v3475 = crv_addr3;	// L5513
            int v3476 = v3475;	// L5514
            drf_full3[v3476] = 1;	// L5515
          }
        } else {
          half v3477 = crv_data3;	// L5518
          int32_t v3478 = crv_addr3;	// L5519
          int v3479 = v3478;	// L5520
          drf3[v3479] = v3477;	// L5521
        }
      }
    }
    ap_int<17> v3480 = txe_r3;	// L5525
    bool v3481;
    ap_int<17> v3481_tmp = v3480;
    v3481 = v3481_tmp[0];	// L5526
    int32_t v3482 = v3481;	// L5527
    bool v3483 = v3482 == 1;	// L5528
    if (v3483) {	// L5529
      ap_int<17> v3484 = txe_r3;	// L5530
      v2637.write(v3484);	// L5531
    }
    ap_int<17> v3485 = txw_r3;	// L5533
    bool v3486;
    ap_int<17> v3486_tmp = v3485;
    v3486 = v3486_tmp[0];	// L5534
    int32_t v3487 = v3486;	// L5535
    bool v3488 = v3487 == 1;	// L5536
    if (v3488) {	// L5537
      ap_int<17> v3489 = txw_r3;	// L5538
      v2638.write(v3489);	// L5539
    }
    ap_int<17> v3490 = txs_r3;	// L5541
    bool v3491;
    ap_int<17> v3491_tmp = v3490;
    v3491 = v3491_tmp[0];	// L5542
    int32_t v3492 = v3491;	// L5543
    bool v3493 = v3492 == 1;	// L5544
    if (v3493) {	// L5545
      ap_int<17> v3494 = txs_r3;	// L5546
      v2639.write(v3494);	// L5547
    }
    ap_int<17> v3495 = txn_r3;	// L5549
    bool v3496;
    ap_int<17> v3496_tmp = v3495;
    v3496 = v3496_tmp[0];	// L5550
    int32_t v3497 = v3496;	// L5551
    bool v3498 = v3497 == 1;	// L5552
    if (v3498) {	// L5553
      ap_int<17> v3499 = txn_r3;	// L5554
      v2640.write(v3499);	// L5555
    }
  }
}

void node_1_0(
  hls::stream< ap_uint<26> >& v3500,
  hls::stream< ap_uint<26> >& v3501,
  hls::stream< ap_uint<26> >& v3502,
  hls::stream< ap_uint<26> >& v3503,
  hls::stream< ap_uint<26> >& v3504,
  hls::stream< ap_uint<26> >& v3505,
  hls::stream< ap_uint<26> >& v3506,
  hls::stream< ap_uint<26> >& v3507,
  hls::stream< ap_uint<17> >& v3508,
  hls::stream< ap_uint<17> >& v3509,
  hls::stream< ap_uint<17> >& v3510,
  hls::stream< ap_uint<17> >& v3511,
  hls::stream< ap_uint<17> >& v3512,
  hls::stream< ap_uint<17> >& v3513,
  hls::stream< ap_uint<17> >& v3514,
  hls::stream< ap_uint<17> >& v3515
) {	// L5560
  int32_t irf4[8];	// L5593
  #pragma HLS array_partition variable=irf4 complete dim=1

  for (int v3517 = 0; v3517 < 8; v3517++) {	// L5594
    irf4[v3517] = 0;	// L5594
  }
  half drf4[8];	// L5595
  #pragma HLS array_partition variable=drf4 complete dim=1

  for (int v3519 = 0; v3519 < 8; v3519++) {	// L5596
    drf4[v3519] = 0.000000;	// L5596
  }
  int32_t drf_full4[8];	// L5597
  #pragma HLS array_partition variable=drf_full4 complete dim=1

  for (int v3521 = 0; v3521 < 8; v3521++) {	// L5598
    drf_full4[v3521] = 0;	// L5598
  }
  int32_t dsmask4;	// L5599
  dsmask4 = 0;	// L5600
  int32_t crv_vld4;	// L5601
  crv_vld4 = 0;	// L5602
  half crv_data4;	// L5603
  crv_data4 = 0.000000;	// L5604
  int32_t crv_addr4;	// L5605
  crv_addr4 = 0;	// L5606
  int32_t crv_mode4;	// L5607
  crv_mode4 = 0;	// L5608
  int32_t crv_raw4;	// L5609
  crv_raw4 = 0;	// L5610
  int32_t csd_vld4;	// L5611
  csd_vld4 = 0;	// L5612
  ap_uint<26> csd_pkt4;	// L5613
  csd_pkt4 = 0;	// L5614
  int32_t csd_dir4;	// L5615
  csd_dir4 = 0;	// L5616
  int32_t row_id4;	// L5617
  row_id4 = 1;	// L5618
  int32_t col_id4;	// L5619
  col_id4 = 0;	// L5620
  ap_uint<17> txn_r4;	// L5621
  txn_r4 = 0;	// L5622
  ap_uint<17> txs_r4;	// L5623
  txs_r4 = 0;	// L5624
  ap_uint<17> txw_r4;	// L5625
  txw_r4 = 0;	// L5626
  ap_uint<17> txe_r4;	// L5627
  txe_r4 = 0;	// L5628
  half hold_v4[4][2];	// L5629
  #pragma HLS array_partition variable=hold_v4 complete dim=1
  #pragma HLS array_partition variable=hold_v4 complete dim=2

  for (int v3538 = 0; v3538 < 4; v3538++) {	// L5630
    for (int v3539 = 0; v3539 < 2; v3539++) {	// L5630
      hold_v4[v3538][v3539] = 0.000000;	// L5630
    }
  }
  uint8_t hold_cnt4[4];	// L5631
  #pragma HLS array_partition variable=hold_cnt4 complete dim=1

  for (int v3541 = 0; v3541 < 4; v3541++) {	// L5632
    hold_cnt4[v3541] = 0;	// L5632
  }
  int32_t crv_ever4;	// L5633
  crv_ever4 = 0;	// L5634
  int32_t fe_ever4;	// L5635
  fe_ever4 = 0;	// L5636
  ap_uint<26> rbuf4[4][2];	// L5637
  #pragma HLS array_partition variable=rbuf4 complete dim=1
  #pragma HLS array_partition variable=rbuf4 complete dim=2

  for (int v3545 = 0; v3545 < 4; v3545++) {	// L5638
    for (int v3546 = 0; v3546 < 2; v3546++) {	// L5638
      rbuf4[v3545][v3546] = 0;	// L5638
    }
  }
  uint8_t rbcnt4[4];	// L5639
  #pragma HLS array_partition variable=rbcnt4 complete dim=1

  for (int v3548 = 0; v3548 < 4; v3548++) {	// L5640
    rbcnt4[v3548] = 0;	// L5640
  }
  int32_t cfg_isz4;	// L5641
  cfg_isz4 = 0;	// L5642
  int32_t cfg_itsz4;	// L5643
  cfg_itsz4 = 0;	// L5644
  uint8_t fetch_en4;	// L5645
  fetch_en4 = 0;	// L5646
  uint8_t instr_cnt4;	// L5647
  instr_cnt4 = 0;	// L5648
  uint8_t iter_cnt4;	// L5649
  iter_cnt4 = 0;	// L5650
  uint8_t condition_reg4;	// L5651
  condition_reg4 = 0;	// L5652
  uint8_t sb_v4[5];	// L5653
  #pragma HLS array_partition variable=sb_v4 complete dim=1

  for (int v3556 = 0; v3556 < 5; v3556++) {	// L5654
    sb_v4[v3556] = 0;	// L5654
  }
  uint8_t sb_dst4[5];	// L5655
  #pragma HLS array_partition variable=sb_dst4 complete dim=1

  for (int v3558 = 0; v3558 < 5; v3558++) {	// L5656
    sb_dst4[v3558] = 0;	// L5656
  }
  uint8_t sb_cmp4[5];	// L5657
  #pragma HLS array_partition variable=sb_cmp4 complete dim=1

  for (int v3560 = 0; v3560 < 5; v3560++) {	// L5658
    sb_cmp4[v3560] = 0;	// L5658
  }
  uint8_t sb_rtr4[5];	// L5659
  #pragma HLS array_partition variable=sb_rtr4 complete dim=1

  for (int v3562 = 0; v3562 < 5; v3562++) {	// L5660
    sb_rtr4[v3562] = 0;	// L5660
  }
  uint8_t sb_inj4[5];	// L5661
  #pragma HLS array_partition variable=sb_inj4 complete dim=1

  for (int v3564 = 0; v3564 < 5; v3564++) {	// L5662
    sb_inj4[v3564] = 0;	// L5662
  }
  uint8_t sb_dir4[5];	// L5663
  #pragma HLS array_partition variable=sb_dir4 complete dim=1

  for (int v3566 = 0; v3566 < 5; v3566++) {	// L5664
    sb_dir4[v3566] = 0;	// L5664
  }
  uint8_t sb_id4[5];	// L5665
  #pragma HLS array_partition variable=sb_id4 complete dim=1

  for (int v3568 = 0; v3568 < 5; v3568++) {	// L5666
    sb_id4[v3568] = 0;	// L5666
  }
  uint8_t sb_rvld4[5];	// L5667
  #pragma HLS array_partition variable=sb_rvld4 complete dim=1

  for (int v3570 = 0; v3570 < 5; v3570++) {	// L5668
    sb_rvld4[v3570] = 0;	// L5668
  }
  uint8_t sb_ix4[5];	// L5669
  #pragma HLS array_partition variable=sb_ix4 complete dim=1

  for (int v3572 = 0; v3572 < 5; v3572++) {	// L5670
    sb_ix4[v3572] = 0;	// L5670
  }
  half resq4[8];	// L5671
  #pragma HLS array_partition variable=resq4 complete dim=1
#pragma HLS dependence variable=resq4 type=inter dependent=false

  for (int v3574 = 0; v3574 < 8; v3574++) {	// L5672
    resq4[v3574] = 0.000000;	// L5672
  }
  uint8_t cmpq4[8];	// L5673
  #pragma HLS array_partition variable=cmpq4 complete dim=1
#pragma HLS dependence variable=cmpq4 type=inter dependent=false

  for (int v3576 = 0; v3576 < 8; v3576++) {	// L5674
    cmpq4[v3576] = 0;	// L5674
  }
  uint8_t resq_wr4;	// L5675
  resq_wr4 = 0;	// L5676
  l_S_t_0_t4: for (int t4 = 0; t4 < 374; t4++) {	// L5677
  #pragma HLS pipeline II=1
    ap_uint<26> p_w4;	// L5678
    p_w4 = 0;	// L5679
    ap_uint<26> p_e4;	// L5680
    p_e4 = 0;	// L5681
    ap_uint<26> p_n4;	// L5682
    p_n4 = 0;	// L5683
    ap_uint<26> p_s4;	// L5684
    p_s4 = 0;	// L5685
    uint8_t v3583 = rbcnt4[0];	// L5686
    int32_t v3584 = v3583;	// L5687
    bool v3585 = v3584 < 2;	// L5688
    if (v3585) {	// L5689
      ap_uint<26> v3586;
      bool v3587 = v3500.read_nb(v3586);
	// L5690
      ap_uint<26> gw4;	// L5691
      gw4 = v3586;	// L5692
      bool okw4;	// L5693
      okw4 = v3587;	// L5694
      bool v3590 = okw4;	// L5695
      if (v3590) {	// L5696
        ap_int<26> v3591 = gw4;	// L5697
        p_w4 = v3591;	// L5698
      }
    }
    uint8_t v3592 = rbcnt4[1];	// L5701
    int32_t v3593 = v3592;	// L5702
    bool v3594 = v3593 < 2;	// L5703
    if (v3594) {	// L5704
      ap_uint<26> v3595;
      bool v3596 = v3501.read_nb(v3595);
	// L5705
      ap_uint<26> ge4;	// L5706
      ge4 = v3595;	// L5707
      bool oke4;	// L5708
      oke4 = v3596;	// L5709
      bool v3599 = oke4;	// L5710
      if (v3599) {	// L5711
        ap_int<26> v3600 = ge4;	// L5712
        p_e4 = v3600;	// L5713
      }
    }
    uint8_t v3601 = rbcnt4[2];	// L5716
    int32_t v3602 = v3601;	// L5717
    bool v3603 = v3602 < 2;	// L5718
    if (v3603) {	// L5719
      ap_uint<26> v3604;
      bool v3605 = v3502.read_nb(v3604);
	// L5720
      ap_uint<26> gn4;	// L5721
      gn4 = v3604;	// L5722
      bool okn4;	// L5723
      okn4 = v3605;	// L5724
      bool v3608 = okn4;	// L5725
      if (v3608) {	// L5726
        ap_int<26> v3609 = gn4;	// L5727
        p_n4 = v3609;	// L5728
      }
    }
    uint8_t v3610 = rbcnt4[3];	// L5731
    int32_t v3611 = v3610;	// L5732
    bool v3612 = v3611 < 2;	// L5733
    if (v3612) {	// L5734
      ap_uint<26> v3613;
      bool v3614 = v3503.read_nb(v3613);
	// L5735
      ap_uint<26> gs4;	// L5736
      gs4 = v3613;	// L5737
      bool oks4;	// L5738
      oks4 = v3614;	// L5739
      bool v3617 = oks4;	// L5740
      if (v3617) {	// L5741
        ap_int<26> v3618 = gs4;	// L5742
        p_s4 = v3618;	// L5743
      }
    }
    ap_uint<26> fin4[4];	// L5746
    for (int v3620 = 0; v3620 < 4; v3620++) {	// L5747
      fin4[v3620] = 0;	// L5747
    }
    ap_int<26> v3621 = p_w4;	// L5748
    fin4[0] = v3621;	// L5749
    ap_int<26> v3622 = p_e4;	// L5750
    fin4[1] = v3622;	// L5751
    ap_int<26> v3623 = p_n4;	// L5752
    fin4[2] = v3623;	// L5753
    ap_int<26> v3624 = p_s4;	// L5754
    fin4[3] = v3624;	// L5755
    l_S_d_0_d16: for (int d16 = 0; d16 < 4; d16++) {	// L5756
      ap_uint<26> v3626 = fin4[d16];	// L5757
      bool v3627;
      ap_int<26> v3627_tmp = v3626;
      v3627 = v3627_tmp[25];	// L5758
      int32_t v3628 = v3627;	// L5759
      bool v3629 = v3628 == 1;	// L5760
      uint8_t v3630 = rbcnt4[d16];	// L5761
      int32_t v3631 = v3630;	// L5762
      bool v3632 = v3631 < 2;	// L5763
      bool v3633 = v3629 & v3632;	// L5764
      if (v3633) {	// L5765
        ap_uint<26> v3634 = fin4[d16];	// L5766
        uint8_t v3635 = rbcnt4[d16];	// L5767
        int v3636 = v3635;	// L5768
        rbuf4[d16][v3636] = v3634;	// L5769
        uint8_t v3637 = rbcnt4[d16];	// L5770
        ap_int<33> v3638 = v3637;	// L5771
        ap_int<33> v3639 = v3638 + 1;	// L5772
        uint8_t v3640 = v3639;	// L5773
        rbcnt4[d16] = v3640;	// L5774
      }
    }
    ap_uint<26> hd4[4];	// L5777
    for (int v3642 = 0; v3642 < 4; v3642++) {	// L5778
      hd4[v3642] = 0;	// L5778
    }
    int32_t hvld4[4];	// L5779
    for (int v3644 = 0; v3644 < 4; v3644++) {	// L5780
      hvld4[v3644] = 0;	// L5780
    }
    int32_t hit4[4];	// L5781
    for (int v3646 = 0; v3646 < 4; v3646++) {	// L5782
      hit4[v3646] = 0;	// L5782
    }
    int32_t axis4[4];	// L5783
    for (int v3648 = 0; v3648 < 4; v3648++) {	// L5784
      axis4[v3648] = 0;	// L5784
    }
    int32_t v3649 = col_id4;	// L5785
    axis4[0] = v3649;	// L5786
    int32_t v3650 = col_id4;	// L5787
    axis4[1] = v3650;	// L5788
    int32_t v3651 = row_id4;	// L5789
    axis4[2] = v3651;	// L5790
    int32_t v3652 = row_id4;	// L5791
    axis4[3] = v3652;	// L5792
    l_S_d_1_d17: for (int d17 = 0; d17 < 4; d17++) {	// L5793
      uint8_t v3654 = rbcnt4[d17];	// L5794
      int32_t v3655 = v3654;	// L5795
      bool v3656 = v3655 > 0;	// L5796
      if (v3656) {	// L5797
        ap_uint<26> v3657 = rbuf4[d17][0];	// L5798
        hd4[d17] = v3657;	// L5799
        hvld4[d17] = 1;	// L5800
        ap_uint<26> v3658 = hd4[d17];	// L5801
        ap_int<4> v3659;
        ap_int<26> v3659_tmp = v3658;
        v3659 = v3659_tmp(24, 21);	// L5802
        int32_t v3660 = axis4[d17];	// L5803
        int32_t v3661 = v3659;	// L5804
        bool v3662 = v3661 == v3660;	// L5805
        if (v3662) {	// L5806
          hit4[d17] = 1;	// L5807
        }
      }
    }
    ap_uint<26> o_crv4;	// L5811
    o_crv4 = 0;	// L5812
    int32_t crv_in4;	// L5813
    crv_in4 = -1;	// L5814
    int32_t v3665 = hit4[3];	// L5815
    bool v3666 = v3665 == 1;	// L5816
    if (v3666) {	// L5817
      ap_uint<26> v3667 = hd4[3];	// L5818
      o_crv4 = v3667;	// L5819
      crv_in4 = 3;	// L5820
    } else {
      int32_t v3668 = hit4[2];	// L5822
      bool v3669 = v3668 == 1;	// L5823
      if (v3669) {	// L5824
        ap_uint<26> v3670 = hd4[2];	// L5825
        o_crv4 = v3670;	// L5826
        crv_in4 = 2;	// L5827
      } else {
        int32_t v3671 = hit4[1];	// L5829
        bool v3672 = v3671 == 1;	// L5830
        if (v3672) {	// L5831
          ap_uint<26> v3673 = hd4[1];	// L5832
          o_crv4 = v3673;	// L5833
          crv_in4 = 1;	// L5834
        } else {
          int32_t v3674 = hit4[0];	// L5836
          bool v3675 = v3674 == 1;	// L5837
          if (v3675) {	// L5838
            ap_uint<26> v3676 = hd4[0];	// L5839
            o_crv4 = v3676;	// L5840
            crv_in4 = 0;	// L5841
          }
        }
      }
    }
    int32_t pop4[4];	// L5846
    for (int v3678 = 0; v3678 < 4; v3678++) {	// L5847
      pop4[v3678] = 0;	// L5847
    }
    int32_t inj_done4;	// L5848
    inj_done4 = 0;	// L5849
    int32_t idir4;	// L5850
    idir4 = -1;	// L5851
    ap_int<26> v3681 = csd_pkt4;	// L5852
    bool v3682;
    ap_int<26> v3682_tmp = v3681;
    v3682 = v3682_tmp[25];	// L5853
    int32_t v3683 = v3682;	// L5854
    bool v3684 = v3683 == 1;	// L5855
    if (v3684) {	// L5856
      int32_t v3685 = csd_dir4;	// L5857
      ap_int<33> v3686 = v3685;	// L5858
      ap_int<33> v3687 = 3 - v3686;	// L5859
      int32_t v3688 = v3687;	// L5860
      idir4 = v3688;	// L5861
    }
    int32_t v3689 = idir4;	// L5863
    bool v3690 = v3689 == 0;	// L5864
    if (v3690) {	// L5865
      ap_int<26> v3691 = csd_pkt4;	// L5866
      bool v3692 = v3504.write_nb(v3691);
	// L5867
      if (v3692) {	// L5868
        inj_done4 = 1;	// L5869
      }
    } else {
      int32_t v3693 = hvld4[0];	// L5872
      bool v3694 = v3693 == 1;	// L5873
      int32_t v3695 = hit4[0];	// L5874
      bool v3696 = v3695 == 0;	// L5875
      bool v3697 = v3694 & v3696;	// L5876
      if (v3697) {	// L5877
        ap_uint<26> v3698 = hd4[0];	// L5878
        bool v3699 = v3504.write_nb(v3698);
	// L5879
        if (v3699) {	// L5880
          pop4[0] = 1;	// L5881
        }
      }
    }
    int32_t v3700 = idir4;	// L5885
    bool v3701 = v3700 == 1;	// L5886
    if (v3701) {	// L5887
      ap_int<26> v3702 = csd_pkt4;	// L5888
      bool v3703 = v3505.write_nb(v3702);
	// L5889
      if (v3703) {	// L5890
        inj_done4 = 1;	// L5891
      }
    } else {
      int32_t v3704 = hvld4[1];	// L5894
      bool v3705 = v3704 == 1;	// L5895
      int32_t v3706 = hit4[1];	// L5896
      bool v3707 = v3706 == 0;	// L5897
      bool v3708 = v3705 & v3707;	// L5898
      if (v3708) {	// L5899
        ap_uint<26> v3709 = hd4[1];	// L5900
        bool v3710 = v3505.write_nb(v3709);
	// L5901
        if (v3710) {	// L5902
          pop4[1] = 1;	// L5903
        }
      }
    }
    int32_t v3711 = idir4;	// L5907
    bool v3712 = v3711 == 2;	// L5908
    if (v3712) {	// L5909
      ap_int<26> v3713 = csd_pkt4;	// L5910
      bool v3714 = v3506.write_nb(v3713);
	// L5911
      if (v3714) {	// L5912
        inj_done4 = 1;	// L5913
      }
    } else {
      int32_t v3715 = hvld4[2];	// L5916
      bool v3716 = v3715 == 1;	// L5917
      int32_t v3717 = hit4[2];	// L5918
      bool v3718 = v3717 == 0;	// L5919
      bool v3719 = v3716 & v3718;	// L5920
      if (v3719) {	// L5921
        ap_uint<26> v3720 = hd4[2];	// L5922
        bool v3721 = v3506.write_nb(v3720);
	// L5923
        if (v3721) {	// L5924
          pop4[2] = 1;	// L5925
        }
      }
    }
    int32_t v3722 = idir4;	// L5929
    bool v3723 = v3722 == 3;	// L5930
    if (v3723) {	// L5931
      ap_int<26> v3724 = csd_pkt4;	// L5932
      bool v3725 = v3507.write_nb(v3724);
	// L5933
      if (v3725) {	// L5934
        inj_done4 = 1;	// L5935
      }
    } else {
      int32_t v3726 = hvld4[3];	// L5938
      bool v3727 = v3726 == 1;	// L5939
      int32_t v3728 = hit4[3];	// L5940
      bool v3729 = v3728 == 0;	// L5941
      bool v3730 = v3727 & v3729;	// L5942
      if (v3730) {	// L5943
        ap_uint<26> v3731 = hd4[3];	// L5944
        bool v3732 = v3507.write_nb(v3731);
	// L5945
        if (v3732) {	// L5946
          pop4[3] = 1;	// L5947
        }
      }
    }
    int32_t v3733 = crv_in4;	// L5951
    bool v3734 = v3733 >= 0;	// L5952
    if (v3734) {	// L5953
      int32_t v3735 = crv_in4;	// L5954
      int v3736 = v3735;	// L5955
      pop4[v3736] = 1;	// L5956
    }
    l_S_d_2_d18: for (int d18 = 0; d18 < 4; d18++) {	// L5958
      int32_t v3738 = pop4[d18];	// L5959
      bool v3739 = v3738 == 1;	// L5960
      if (v3739) {	// L5961
        l_S_sft_2_sft4: for (int sft4 = 0; sft4 < 1; sft4++) {	// L5962
          ap_uint<26> v3741 = rbuf4[d18][(sft4 + 1)];	// L5963
          rbuf4[d18][sft4] = v3741;	// L5964
        }
        uint8_t v3742 = rbcnt4[d18];	// L5966
        ap_int<33> v3743 = v3742;	// L5967
        ap_int<33> v3744 = v3743 - 1;	// L5968
        uint8_t v3745 = v3744;	// L5969
        rbcnt4[d18] = v3745;	// L5970
      }
    }
    int32_t v3746 = inj_done4;	// L5973
    bool v3747 = v3746 == 1;	// L5974
    if (v3747) {	// L5975
      csd_pkt4 = 0;	// L5976
    }
    ap_int<26> v3748 = o_crv4;	// L5978
    bool v3749;
    ap_int<26> v3749_tmp = v3748;
    v3749 = v3749_tmp[25];	// L5979
    int32_t v3750 = v3749;	// L5980
    crv_vld4 = v3750;	// L5981
    int32_t v3751 = crv_vld4;	// L5982
    bool v3752 = v3751 == 1;	// L5983
    if (v3752) {	// L5984
      crv_ever4 = 1;	// L5985
    }
    ap_int<26> v3753 = o_crv4;	// L5987
    int16_t v3754;
    ap_int<26> v3754_tmp = v3753;
    v3754 = v3754_tmp(15, 0);	// L5988
    half v3755;
    union { uint16_t from; half to;} _converter_v3754_to_v3755 = {};
    _converter_v3754_to_v3755.from = v3754;
    v3755 = _converter_v3754_to_v3755.to;	// L5989
    crv_data4 = v3755;	// L5990
    ap_int<26> v3756 = o_crv4;	// L5991
    ap_int<4> v3757;
    ap_int<26> v3757_tmp = v3756;
    v3757 = v3757_tmp(19, 16);	// L5992
    int32_t v3758 = v3757;	// L5993
    crv_addr4 = v3758;	// L5994
    ap_int<26> v3759 = o_crv4;	// L5995
    bool v3760;
    ap_int<26> v3760_tmp = v3759;
    v3760 = v3760_tmp[20];	// L5996
    int32_t v3761 = v3760;	// L5997
    crv_mode4 = v3761;	// L5998
    ap_int<26> v3762 = o_crv4;	// L5999
    int16_t v3763;
    ap_int<26> v3763_tmp = v3762;
    v3763 = v3763_tmp(15, 0);	// L6000
    int32_t v3764 = v3763;	// L6001
    crv_raw4 = v3764;	// L6002
    half rxv4[4];	// L6003
    for (int v3766 = 0; v3766 < 4; v3766++) {	// L6004
      rxv4[v3766] = 0.000000;	// L6004
    }
    int32_t rxvld4[4];	// L6005
    for (int v3768 = 0; v3768 < 4; v3768++) {	// L6006
      rxvld4[v3768] = 0;	// L6006
    }
    uint8_t v3769 = hold_cnt4[0];	// L6007
    int32_t v3770 = v3769;	// L6008
    bool v3771 = v3770 < 2;	// L6009
    if (v3771) {	// L6010
      ap_uint<17> v3772;
      bool v3773 = v3508.read_nb(v3772);
	// L6011
      ap_uint<17> sgn4;	// L6012
      sgn4 = v3772;	// L6013
      bool sqn4;	// L6014
      sqn4 = v3773;	// L6015
      bool v3776 = sqn4;	// L6016
      int32_t v3777 = v3776;	// L6017
      bool v3778 = v3777 == 1;	// L6018
      if (v3778) {	// L6019
        ap_int<17> v3779 = sgn4;	// L6020
        int16_t v3780;
        ap_int<17> v3780_tmp = v3779;
        v3780 = v3780_tmp(16, 1);	// L6021
        half v3781;
        union { uint16_t from; half to;} _converter_v3780_to_v3781 = {};
        _converter_v3780_to_v3781.from = v3780;
        v3781 = _converter_v3780_to_v3781.to;	// L6022
        rxv4[0] = v3781;	// L6023
        rxvld4[0] = 1;	// L6024
      }
    }
    uint8_t v3782 = hold_cnt4[1];	// L6027
    int32_t v3783 = v3782;	// L6028
    bool v3784 = v3783 < 2;	// L6029
    if (v3784) {	// L6030
      ap_uint<17> v3785;
      bool v3786 = v3509.read_nb(v3785);
	// L6031
      ap_uint<17> sgs4;	// L6032
      sgs4 = v3785;	// L6033
      bool sqs4;	// L6034
      sqs4 = v3786;	// L6035
      bool v3789 = sqs4;	// L6036
      int32_t v3790 = v3789;	// L6037
      bool v3791 = v3790 == 1;	// L6038
      if (v3791) {	// L6039
        ap_int<17> v3792 = sgs4;	// L6040
        int16_t v3793;
        ap_int<17> v3793_tmp = v3792;
        v3793 = v3793_tmp(16, 1);	// L6041
        half v3794;
        union { uint16_t from; half to;} _converter_v3793_to_v3794 = {};
        _converter_v3793_to_v3794.from = v3793;
        v3794 = _converter_v3793_to_v3794.to;	// L6042
        rxv4[1] = v3794;	// L6043
        rxvld4[1] = 1;	// L6044
      }
    }
    uint8_t v3795 = hold_cnt4[2];	// L6047
    int32_t v3796 = v3795;	// L6048
    bool v3797 = v3796 < 2;	// L6049
    if (v3797) {	// L6050
      ap_uint<17> v3798;
      bool v3799 = v3510.read_nb(v3798);
	// L6051
      ap_uint<17> sgw4;	// L6052
      sgw4 = v3798;	// L6053
      bool sqw4;	// L6054
      sqw4 = v3799;	// L6055
      bool v3802 = sqw4;	// L6056
      int32_t v3803 = v3802;	// L6057
      bool v3804 = v3803 == 1;	// L6058
      if (v3804) {	// L6059
        ap_int<17> v3805 = sgw4;	// L6060
        int16_t v3806;
        ap_int<17> v3806_tmp = v3805;
        v3806 = v3806_tmp(16, 1);	// L6061
        half v3807;
        union { uint16_t from; half to;} _converter_v3806_to_v3807 = {};
        _converter_v3806_to_v3807.from = v3806;
        v3807 = _converter_v3806_to_v3807.to;	// L6062
        rxv4[2] = v3807;	// L6063
        rxvld4[2] = 1;	// L6064
      }
    }
    uint8_t v3808 = hold_cnt4[3];	// L6067
    int32_t v3809 = v3808;	// L6068
    bool v3810 = v3809 < 2;	// L6069
    if (v3810) {	// L6070
      ap_uint<17> v3811;
      bool v3812 = v3511.read_nb(v3811);
	// L6071
      ap_uint<17> sge4;	// L6072
      sge4 = v3811;	// L6073
      bool sqe4;	// L6074
      sqe4 = v3812;	// L6075
      bool v3815 = sqe4;	// L6076
      int32_t v3816 = v3815;	// L6077
      bool v3817 = v3816 == 1;	// L6078
      if (v3817) {	// L6079
        ap_int<17> v3818 = sge4;	// L6080
        int16_t v3819;
        ap_int<17> v3819_tmp = v3818;
        v3819 = v3819_tmp(16, 1);	// L6081
        half v3820;
        union { uint16_t from; half to;} _converter_v3819_to_v3820 = {};
        _converter_v3819_to_v3820.from = v3819;
        v3820 = _converter_v3819_to_v3820.to;	// L6082
        rxv4[3] = v3820;	// L6083
        rxvld4[3] = 1;	// L6084
      }
    }
    l_S_d_4_d19: for (int d19 = 0; d19 < 4; d19++) {	// L6087
      int32_t v3822 = rxvld4[d19];	// L6088
      bool v3823 = v3822 == 1;	// L6089
      if (v3823) {	// L6090
        half v3824 = rxv4[d19];	// L6091
        uint8_t v3825 = hold_cnt4[d19];	// L6092
        int v3826 = v3825;	// L6093
        hold_v4[d19][v3826] = v3824;	// L6094
        uint8_t v3827 = hold_cnt4[d19];	// L6095
        ap_int<33> v3828 = v3827;	// L6096
        ap_int<33> v3829 = v3828 + 1;	// L6097
        uint8_t v3830 = v3829;	// L6098
        hold_cnt4[d19] = v3830;	// L6099
      }
    }
    ap_uint<17> tx_n4;	// L6102
    tx_n4 = 0;	// L6103
    ap_uint<17> tx_s4;	// L6104
    tx_s4 = 0;	// L6105
    ap_uint<17> tx_w4;	// L6106
    tx_w4 = 0;	// L6107
    ap_uint<17> tx_e4;	// L6108
    tx_e4 = 0;	// L6109
    uint8_t v3835 = sb_v4[0];	// L6110
    int32_t v3836 = v3835;	// L6111
    bool v3837 = v3836 == 1;	// L6112
    if (v3837) {	// L6113
      uint8_t v3838 = sb_ix4[0];	// L6114
      int v3839 = v3838;	// L6115
      half v3840 = resq4[v3839];	// L6116
      half wb4;
#pragma HLS dependence variable=wb4 type=inter dependent=false	// L6117
      wb4 = v3840;	// L6118
      uint8_t v3842 = sb_cmp4[0];	// L6119
      int32_t v3843 = v3842;	// L6120
      bool v3844 = v3843 == 1;	// L6121
      if (v3844) {	// L6122
        uint8_t v3845 = sb_ix4[0];	// L6123
        int v3846 = v3845;	// L6124
        uint8_t v3847 = cmpq4[v3846];	// L6125
        condition_reg4 = v3847;	// L6126
      }
      uint8_t v3848 = sb_rtr4[0];	// L6128
      int32_t v3849 = v3848;	// L6129
      bool v3850 = v3849 == 1;	// L6130
      if (v3850) {	// L6131
        uint8_t v3851 = sb_inj4[0];	// L6132
        int32_t v3852 = v3851;	// L6133
        bool v3853 = v3852 == 1;	// L6134
        ap_int<26> v3854 = csd_pkt4;	// L6135
        bool v3855;
        ap_int<26> v3855_tmp = v3854;
        v3855 = v3855_tmp[25];	// L6136
        int32_t v3856 = v3855;	// L6137
        bool v3857 = v3856 == 0;	// L6138
        bool v3858 = v3853 & v3857;	// L6139
        if (v3858) {	// L6140
          half v3859 = wb4;	// L6141
          uint16_t v3860;
          union { half from; uint16_t to;} _converter_v3859_to_v3860 = {};
          _converter_v3859_to_v3860.from = v3859;
          v3860 = _converter_v3859_to_v3860.to;	// L6142
          ap_int<26> v3861 = csd_pkt4;	// L6143
          ap_int<26> v3862;
          ap_int<26> v3862_tmp = v3861;
          v3862_tmp(15, 0) = v3860;
          v3862 = v3862_tmp;	// L6144
          csd_pkt4 = v3862;	// L6145
          uint8_t v3863 = sb_dst4[0];	// L6146
          ap_uint<4> v3864 = v3863;	// L6147
          ap_int<26> v3865 = csd_pkt4;	// L6148
          ap_int<26> v3866;
          ap_int<26> v3866_tmp = v3865;
          v3866_tmp(19, 16) = v3864;
          v3866 = v3866_tmp;	// L6149
          csd_pkt4 = v3866;	// L6150
          uint8_t v3867 = sb_id4[0];	// L6151
          ap_uint<4> v3868 = v3867;	// L6152
          ap_int<26> v3869 = csd_pkt4;	// L6153
          ap_int<26> v3870;
          ap_int<26> v3870_tmp = v3869;
          v3870_tmp(24, 21) = v3868;
          v3870 = v3870_tmp;	// L6154
          csd_pkt4 = v3870;	// L6155
          uint8_t v3871 = sb_rvld4[0];	// L6156
          bool v3872 = v3871;	// L6157
          ap_int<26> v3873 = csd_pkt4;	// L6158
          ap_int<26> v3874;
          ap_int<26> v3874_tmp = v3873;
          v3874_tmp[25] = v3872;          v3874 = v3874_tmp;	// L6159
          csd_pkt4 = v3874;	// L6160
          uint8_t v3875 = sb_dir4[0];	// L6161
          int32_t v3876 = v3875;	// L6162
          csd_dir4 = v3876;	// L6163
        }
      } else {
        uint8_t v3877 = sb_dst4[0];	// L6166
        int32_t v3878 = v3877;	// L6167
        bool v3879 = v3878 >= 12;	// L6168
        if (v3879) {	// L6169
          ap_uint<17> tw04;	// L6170
          tw04 = 0;	// L6171
          uint8_t v3881 = sb_rvld4[0];	// L6172
          bool v3882 = v3881;	// L6173
          ap_int<17> v3883 = tw04;	// L6174
          ap_int<17> v3884;
          ap_int<17> v3884_tmp = v3883;
          v3884_tmp[0] = v3882;          v3884 = v3884_tmp;	// L6175
          tw04 = v3884;	// L6176
          half v3885 = wb4;	// L6177
          uint16_t v3886;
          union { half from; uint16_t to;} _converter_v3885_to_v3886 = {};
          _converter_v3885_to_v3886.from = v3885;
          v3886 = _converter_v3885_to_v3886.to;	// L6178
          ap_int<17> v3887 = tw04;	// L6179
          ap_int<17> v3888;
          ap_int<17> v3888_tmp = v3887;
          v3888_tmp(16, 1) = v3886;
          v3888 = v3888_tmp;	// L6180
          tw04 = v3888;	// L6181
          uint8_t v3889 = sb_dst4[0];	// L6182
          int32_t v3890 = v3889;	// L6183
          int32_t v3891 = v3890 & 3;	// L6184
          bool v3892 = v3891 == 0;	// L6185
          if (v3892) {	// L6186
            ap_int<17> v3893 = tw04;	// L6187
            tx_n4 = v3893;	// L6188
          } else {
            uint8_t v3894 = sb_dst4[0];	// L6190
            int32_t v3895 = v3894;	// L6191
            int32_t v3896 = v3895 & 3;	// L6192
            bool v3897 = v3896 == 1;	// L6193
            if (v3897) {	// L6194
              ap_int<17> v3898 = tw04;	// L6195
              tx_s4 = v3898;	// L6196
            } else {
              uint8_t v3899 = sb_dst4[0];	// L6198
              int32_t v3900 = v3899;	// L6199
              int32_t v3901 = v3900 & 3;	// L6200
              bool v3902 = v3901 == 2;	// L6201
              if (v3902) {	// L6202
                ap_int<17> v3903 = tw04;	// L6203
                tx_w4 = v3903;	// L6204
              } else {
                ap_int<17> v3904 = tw04;	// L6206
                tx_e4 = v3904;	// L6207
              }
            }
          }
        } else {
          uint8_t v3905 = sb_rvld4[0];	// L6212
          int32_t v3906 = v3905;	// L6213
          bool v3907 = v3906 == 1;	// L6214
          if (v3907) {	// L6215
            uint8_t v3908 = sb_dst4[0];	// L6216
            int32_t v3909 = v3908;	// L6217
            bool v3910 = v3909 < 8;	// L6218
            int32_t v3911 = dsmask4;	// L6219
            int32_t v3912 = v3911 >> v3909;	// L6220
            int32_t v3913 = v3912 & 1;	// L6221
            bool v3914 = v3913 == 1;	// L6222
            bool v3915 = v3910 & v3914;	// L6223
            if (v3915) {	// L6224
              uint8_t v3916 = sb_dst4[0];	// L6225
              int v3917 = v3916;	// L6226
              int32_t v3918 = drf_full4[v3917];	// L6227
              bool v3919 = v3918 == 0;	// L6228
              if (v3919) {	// L6229
                half v3920 = wb4;	// L6230
                uint8_t v3921 = sb_dst4[0];	// L6231
                int v3922 = v3921;	// L6232
                drf4[v3922] = v3920;	// L6233
                uint8_t v3923 = sb_dst4[0];	// L6234
                int v3924 = v3923;	// L6235
                drf_full4[v3924] = 1;	// L6236
              }
            } else {
              half v3925 = wb4;	// L6239
              uint8_t v3926 = sb_dst4[0];	// L6240
              int32_t v3927 = v3926;	// L6241
              int32_t v3928 = v3927 & 7;	// L6242
              int v3929 = v3928;	// L6243
              drf4[v3929] = v3925;	// L6244
            }
          }
        }
      }
    }
    int32_t pc4;	// L6250
    pc4 = -1;	// L6251
    int8_t v3931 = fetch_en4;	// L6252
    int32_t v3932 = v3931;	// L6253
    bool v3933 = v3932 == 1;	// L6254
    if (v3933) {	// L6255
      int8_t v3934 = instr_cnt4;	// L6256
      int32_t v3935 = v3934;	// L6257
      pc4 = v3935;	// L6258
    }
    int8_t v3936 = fetch_en4;	// L6260
    int32_t v3937 = v3936;	// L6261
    bool v3938 = v3937 == 1;	// L6262
    if (v3938) {	// L6263
      fe_ever4 = 1;	// L6264
    }
    int32_t instr4;	// L6266
    instr4 = 0;	// L6267
    int32_t v3940 = pc4;	// L6268
    bool v3941 = v3940 >= 0;	// L6269
    if (v3941) {	// L6270
      int32_t v3942 = pc4;	// L6271
      int v3943 = v3942;	// L6272
      int32_t v3944 = irf4[v3943];	// L6273
      instr4 = v3944;	// L6274
    }
    int32_t v3945 = instr4;	// L6276
    int32_t v3946 = v3945 & 15;	// L6277
    int32_t op4;	// L6278
    op4 = v3946;	// L6279
    int32_t v3948 = instr4;	// L6280
    int32_t v3949 = v3948 >> 4;	// L6281
    int32_t v3950 = v3949 & 15;	// L6282
    int32_t dst4;	// L6283
    dst4 = v3950;	// L6284
    int32_t v3952 = instr4;	// L6285
    int32_t v3953 = v3952 >> 8;	// L6286
    int32_t v3954 = v3953 & 15;	// L6287
    int32_t s14;	// L6288
    s14 = v3954;	// L6289
    int32_t v3956 = instr4;	// L6290
    int32_t v3957 = v3956 >> 12;	// L6291
    int32_t v3958 = v3957 & 15;	// L6292
    int32_t s24;	// L6293
    s24 = v3958;	// L6294
    half a4;	// L6295
    a4 = 0.000000;	// L6296
    half b4;	// L6297
    b4 = 0.000000;	// L6298
    int32_t v3962 = s14;	// L6299
    bool v3963 = v3962 >= 12;	// L6300
    if (v3963) {	// L6301
      int32_t v3964 = s14;	// L6302
      int32_t v3965 = v3964 & 3;	// L6303
      int v3966 = v3965;	// L6304
      half v3967 = hold_v4[v3966][0];	// L6305
      a4 = v3967;	// L6306
    } else {
      int32_t v3968 = s14;	// L6308
      int v3969 = v3968;	// L6309
      half v3970 = drf4[v3969];	// L6310
      a4 = v3970;	// L6311
    }
    int32_t v3971 = s24;	// L6313
    bool v3972 = v3971 >= 12;	// L6314
    if (v3972) {	// L6315
      int32_t v3973 = s24;	// L6316
      int32_t v3974 = v3973 & 3;	// L6317
      int v3975 = v3974;	// L6318
      half v3976 = hold_v4[v3975][0];	// L6319
      b4 = v3976;	// L6320
    } else {
      int32_t v3977 = s24;	// L6322
      int v3978 = v3977;	// L6323
      half v3979 = drf4[v3978];	// L6324
      b4 = v3979;	// L6325
    }
    int32_t a_vld4;	// L6327
    a_vld4 = 1;	// L6328
    int32_t b_vld4;	// L6329
    b_vld4 = 1;	// L6330
    int32_t v3982 = s14;	// L6331
    bool v3983 = v3982 >= 12;	// L6332
    if (v3983) {	// L6333
      a_vld4 = 0;	// L6334
      int32_t v3984 = s14;	// L6335
      int32_t v3985 = v3984 & 3;	// L6336
      int v3986 = v3985;	// L6337
      uint8_t v3987 = hold_cnt4[v3986];	// L6338
      int32_t v3988 = v3987;	// L6339
      bool v3989 = v3988 > 0;	// L6340
      if (v3989) {	// L6341
        a_vld4 = 1;	// L6342
      }
    }
    int32_t v3990 = s24;	// L6345
    bool v3991 = v3990 >= 12;	// L6346
    if (v3991) {	// L6347
      b_vld4 = 0;	// L6348
      int32_t v3992 = s24;	// L6349
      int32_t v3993 = v3992 & 3;	// L6350
      int v3994 = v3993;	// L6351
      uint8_t v3995 = hold_cnt4[v3994];	// L6352
      int32_t v3996 = v3995;	// L6353
      bool v3997 = v3996 > 0;	// L6354
      if (v3997) {	// L6355
        b_vld4 = 1;	// L6356
      }
    }
    int32_t v3998 = s14;	// L6359
    bool v3999 = v3998 < 8;	// L6360
    int32_t v4000 = dsmask4;	// L6361
    int32_t v4001 = v4000 >> v3998;	// L6362
    int32_t v4002 = v4001 & 1;	// L6363
    bool v4003 = v4002 == 1;	// L6364
    bool v4004 = v3999 & v4003;	// L6365
    if (v4004) {	// L6366
      int32_t v4005 = s14;	// L6367
      int v4006 = v4005;	// L6368
      int32_t v4007 = drf_full4[v4006];	// L6369
      bool v4008 = v4007 == 0;	// L6370
      if (v4008) {	// L6371
        a_vld4 = 0;	// L6372
      }
    }
    int32_t v4009 = s24;	// L6375
    bool v4010 = v4009 < 8;	// L6376
    int32_t v4011 = dsmask4;	// L6377
    int32_t v4012 = v4011 >> v4009;	// L6378
    int32_t v4013 = v4012 & 1;	// L6379
    bool v4014 = v4013 == 1;	// L6380
    bool v4015 = v4010 & v4014;	// L6381
    if (v4015) {	// L6382
      int32_t v4016 = s24;	// L6383
      int v4017 = v4016;	// L6384
      int32_t v4018 = drf_full4[v4017];	// L6385
      bool v4019 = v4018 == 0;	// L6386
      if (v4019) {	// L6387
        b_vld4 = 0;	// L6388
      }
    }
    int32_t binop4;	// L6391
    binop4 = 0;	// L6392
    int32_t v4021 = op4;	// L6393
    bool v4022 = v4021 == 0;	// L6394
    bool v4023 = v4021 == 1;	// L6395
    bool v4024 = v4021 == 2;	// L6396
    bool v4025 = v4021 == 8;	// L6397
    bool v4026 = v4021 == 9;	// L6398
    bool v4027 = v4022 | v4023;	// L6399
    bool v4028 = v4027 | v4024;	// L6400
    bool v4029 = v4028 | v4025;	// L6401
    bool v4030 = v4029 | v4026;	// L6402
    if (v4030) {	// L6403
      binop4 = 1;	// L6404
    }
    int32_t raw4;	// L6406
    raw4 = 0;	// L6407
    int32_t cmp_busy4;	// L6408
    cmp_busy4 = 0;	// L6409
    l_S_k_5_k8: for (int k8 = 0; k8 < 4; k8++) {	// L6410
      uint8_t v4034 = sb_v4[(k8 + 1)];	// L6411
      int32_t v4035 = v4034;	// L6412
      bool v4036 = v4035 == 1;	// L6413
      uint8_t v4037 = sb_rtr4[(k8 + 1)];	// L6414
      int32_t v4038 = v4037;	// L6415
      bool v4039 = v4038 == 0;	// L6416
      uint8_t v4040 = sb_dst4[(k8 + 1)];	// L6417
      int32_t v4041 = v4040;	// L6418
      bool v4042 = v4041 < 12;	// L6419
      bool v4043 = v4036 & v4039;	// L6420
      bool v4044 = v4043 & v4042;	// L6421
      if (v4044) {	// L6422
        int32_t v4045 = s14;	// L6423
        bool v4046 = v4045 < 12;	// L6424
        uint8_t v4047 = sb_dst4[(k8 + 1)];	// L6425
        int32_t v4048 = v4047;	// L6426
        int32_t v4049 = v4048 & 7;	// L6427
        int32_t v4050 = v4045 & 7;	// L6428
        bool v4051 = v4049 == v4050;	// L6429
        bool v4052 = v4046 & v4051;	// L6430
        if (v4052) {	// L6431
          raw4 = 1;	// L6432
        }
        int32_t v4053 = binop4;	// L6434
        bool v4054 = v4053 == 1;	// L6435
        int32_t v4055 = s24;	// L6436
        bool v4056 = v4055 < 12;	// L6437
        uint8_t v4057 = sb_dst4[(k8 + 1)];	// L6438
        int32_t v4058 = v4057;	// L6439
        int32_t v4059 = v4058 & 7;	// L6440
        int32_t v4060 = v4055 & 7;	// L6441
        bool v4061 = v4059 == v4060;	// L6442
        bool v4062 = v4054 & v4056;	// L6443
        bool v4063 = v4062 & v4061;	// L6444
        if (v4063) {	// L6445
          raw4 = 1;	// L6446
        }
      }
      uint8_t v4064 = sb_v4[(k8 + 1)];	// L6449
      int32_t v4065 = v4064;	// L6450
      bool v4066 = v4065 == 1;	// L6451
      uint8_t v4067 = sb_cmp4[(k8 + 1)];	// L6452
      int32_t v4068 = v4067;	// L6453
      bool v4069 = v4068 == 1;	// L6454
      bool v4070 = v4066 & v4069;	// L6455
      if (v4070) {	// L6456
        cmp_busy4 = 1;	// L6457
      }
    }
    int32_t is_cond4;	// L6460
    is_cond4 = 0;	// L6461
    int32_t v4072 = op4;	// L6462
    bool v4073 = v4072 >= 12;	// L6463
    ap_int<33> v4074 = v4072;	// L6464
    bool v4075 = v4074 <= 15;	// L6465
    bool v4076 = v4073 & v4075;	// L6466
    if (v4076) {	// L6467
      is_cond4 = 1;	// L6468
    }
    int32_t grant4;	// L6470
    grant4 = 0;	// L6471
    int32_t v4078 = pc4;	// L6472
    bool v4079 = v4078 >= 0;	// L6473
    if (v4079) {	// L6474
      grant4 = 1;	// L6475
    }
    int32_t v4080 = pc4;	// L6477
    bool v4081 = v4080 >= 0;	// L6478
    int32_t v4082 = a_vld4;	// L6479
    bool v4083 = v4082 == 0;	// L6480
    int32_t v4084 = binop4;	// L6481
    bool v4085 = v4084 == 1;	// L6482
    int32_t v4086 = b_vld4;	// L6483
    bool v4087 = v4086 == 0;	// L6484
    bool v4088 = v4085 & v4087;	// L6485
    bool v4089 = v4083 | v4088;	// L6486
    bool v4090 = v4081 & v4089;	// L6487
    if (v4090) {	// L6488
      grant4 = 0;	// L6489
    }
    int32_t v4091 = pc4;	// L6491
    bool v4092 = v4091 >= 0;	// L6492
    int32_t v4093 = raw4;	// L6493
    bool v4094 = v4093 == 1;	// L6494
    int32_t v4095 = is_cond4;	// L6495
    bool v4096 = v4095 == 1;	// L6496
    int32_t v4097 = cmp_busy4;	// L6497
    bool v4098 = v4097 == 1;	// L6498
    bool v4099 = v4096 & v4098;	// L6499
    bool v4100 = v4094 | v4099;	// L6500
    bool v4101 = v4092 & v4100;	// L6501
    if (v4101) {	// L6502
      grant4 = 0;	// L6503
    }
    int32_t v4102 = grant4;	// L6505
    bool v4103 = v4102 == 1;	// L6506
    if (v4103) {	// L6507
      int8_t v4104 = instr_cnt4;	// L6508
      int32_t v4105 = cfg_isz4;	// L6509
      int32_t v4106 = v4104;	// L6510
      bool v4107 = v4106 == v4105;	// L6511
      if (v4107) {	// L6512
        instr_cnt4 = 0;	// L6513
        int8_t v4108 = iter_cnt4;	// L6514
        int32_t v4109 = cfg_itsz4;	// L6515
        ap_int<33> v4110 = v4109;	// L6516
        ap_int<33> v4111 = v4110 - 1;	// L6517
        ap_int<33> v4112 = v4108;	// L6518
        bool v4113 = v4112 == v4111;	// L6519
        if (v4113) {	// L6520
          fetch_en4 = 0;	// L6521
        } else {
          int8_t v4114 = iter_cnt4;	// L6523
          ap_int<33> v4115 = v4114;	// L6524
          ap_int<33> v4116 = v4115 + 1;	// L6525
          uint8_t v4117 = v4116;	// L6526
          iter_cnt4 = v4117;	// L6527
        }
      } else {
        int8_t v4118 = instr_cnt4;	// L6530
        ap_int<33> v4119 = v4118;	// L6531
        ap_int<33> v4120 = v4119 + 1;	// L6532
        uint8_t v4121 = v4120;	// L6533
        instr_cnt4 = v4121;	// L6534
      }
    }
    int32_t c14;	// L6537
    c14 = -1;	// L6538
    int32_t c24;	// L6539
    c24 = -1;	// L6540
    int32_t v4124 = grant4;	// L6541
    bool v4125 = v4124 == 1;	// L6542
    int32_t v4126 = s14;	// L6543
    bool v4127 = v4126 >= 12;	// L6544
    bool v4128 = v4125 & v4127;	// L6545
    if (v4128) {	// L6546
      int32_t v4129 = s14;	// L6547
      int32_t v4130 = v4129 & 3;	// L6548
      c14 = v4130;	// L6549
    }
    int32_t v4131 = grant4;	// L6551
    bool v4132 = v4131 == 1;	// L6552
    int32_t v4133 = s24;	// L6553
    bool v4134 = v4133 >= 12;	// L6554
    bool v4135 = v4132 & v4134;	// L6555
    if (v4135) {	// L6556
      int32_t v4136 = s24;	// L6557
      int32_t v4137 = v4136 & 3;	// L6558
      c24 = v4137;	// L6559
    }
    int32_t v4138 = c14;	// L6561
    bool v4139 = v4138 >= 0;	// L6562
    if (v4139) {	// L6563
      int32_t v4140 = c14;	// L6564
      int v4141 = v4140;	// L6565
      half v4142 = hold_v4[v4141][1];	// L6566
      hold_v4[v4141][0] = v4142;	// L6567
      int32_t v4143 = c14;	// L6568
      int v4144 = v4143;	// L6569
      uint8_t v4145 = hold_cnt4[v4144];	// L6570
      ap_int<33> v4146 = v4145;	// L6571
      ap_int<33> v4147 = v4146 - 1;	// L6572
      uint8_t v4148 = v4147;	// L6573
      hold_cnt4[v4144] = v4148;	// L6574
    }
    int32_t v4149 = c24;	// L6576
    bool v4150 = v4149 >= 0;	// L6577
    int32_t v4151 = c14;	// L6578
    bool v4152 = v4149 != v4151;	// L6579
    bool v4153 = v4150 & v4152;	// L6580
    if (v4153) {	// L6581
      int32_t v4154 = c24;	// L6582
      int v4155 = v4154;	// L6583
      half v4156 = hold_v4[v4155][1];	// L6584
      hold_v4[v4155][0] = v4156;	// L6585
      int32_t v4157 = c24;	// L6586
      int v4158 = v4157;	// L6587
      uint8_t v4159 = hold_cnt4[v4158];	// L6588
      ap_int<33> v4160 = v4159;	// L6589
      ap_int<33> v4161 = v4160 - 1;	// L6590
      uint8_t v4162 = v4161;	// L6591
      hold_cnt4[v4158] = v4162;	// L6592
    }
    int32_t v4163 = grant4;	// L6594
    bool v4164 = v4163 == 1;	// L6595
    int32_t v4165 = s14;	// L6596
    bool v4166 = v4165 < 8;	// L6597
    int32_t v4167 = dsmask4;	// L6598
    int32_t v4168 = v4167 >> v4165;	// L6599
    int32_t v4169 = v4168 & 1;	// L6600
    bool v4170 = v4169 == 1;	// L6601
    bool v4171 = v4164 & v4166;	// L6602
    bool v4172 = v4171 & v4170;	// L6603
    if (v4172) {	// L6604
      int32_t v4173 = s14;	// L6605
      int v4174 = v4173;	// L6606
      drf_full4[v4174] = 0;	// L6607
    }
    int32_t v4175 = grant4;	// L6609
    bool v4176 = v4175 == 1;	// L6610
    int32_t v4177 = s24;	// L6611
    bool v4178 = v4177 < 8;	// L6612
    int32_t v4179 = dsmask4;	// L6613
    int32_t v4180 = v4179 >> v4177;	// L6614
    int32_t v4181 = v4180 & 1;	// L6615
    bool v4182 = v4181 == 1;	// L6616
    bool v4183 = v4176 & v4178;	// L6617
    bool v4184 = v4183 & v4182;	// L6618
    if (v4184) {	// L6619
      int32_t v4185 = s24;	// L6620
      int v4186 = v4185;	// L6621
      drf_full4[v4186] = 0;	// L6622
    }
    half res4;
#pragma HLS dependence variable=res4 type=inter dependent=false	// L6624
    res4 = 0.000000;	// L6625
    int32_t v4188 = op4;	// L6626
    bool v4189 = v4188 == 0;	// L6627
    if (v4189) {	// L6628
      half v4190 = a4;	// L6629
      half v4191 = b4;	// L6630
      half v4192 = v4190 + v4191;	// L6631
      res4 = v4192;	// L6632
    } else {
      int32_t v4193 = op4;	// L6634
      bool v4194 = v4193 == 1;	// L6635
      if (v4194) {	// L6636
        half v4195 = a4;	// L6637
        half v4196 = b4;	// L6638
        half v4197 = v4195 - v4196;	// L6639
        res4 = v4197;	// L6640
      } else {
        int32_t v4198 = op4;	// L6642
        bool v4199 = v4198 == 2;	// L6643
        if (v4199) {	// L6644
          half v4200 = a4;	// L6645
          half v4201 = b4;	// L6646
          half v4202 = v4200 * v4201;	// L6647
          res4 = v4202;	// L6648
        } else {
          int32_t v4203 = op4;	// L6650
          bool v4204 = v4203 == 8;	// L6651
          if (v4204) {	// L6652
            half v4205 = a4;	// L6653
            half v4206 = b4;	// L6654
            bool v4207 = v4205 >= v4206;	// L6655
            if (v4207) {	// L6656
              res4 = 1.000000;	// L6657
            } else {
              res4 = -1.000000;	// L6659
            }
          } else {
            int32_t v4208 = op4;	// L6662
            bool v4209 = v4208 == 9;	// L6663
            if (v4209) {	// L6664
              half v4210 = a4;	// L6665
              half v4211 = b4;	// L6666
              bool v4212 = v4210 < v4211;	// L6667
              if (v4212) {	// L6668
                res4 = 1.000000;	// L6669
              } else {
                res4 = -1.000000;	// L6671
              }
            } else {
              half v4213 = a4;	// L6674
              res4 = v4213;	// L6675
            }
          }
        }
      }
    }
    int32_t v4214 = a_vld4;	// L6681
    int32_t res_vld4;	// L6682
    res_vld4 = v4214;	// L6683
    int32_t v4216 = op4;	// L6684
    bool v4217 = v4216 == 0;	// L6685
    bool v4218 = v4216 == 1;	// L6686
    bool v4219 = v4216 == 2;	// L6687
    bool v4220 = v4216 == 8;	// L6688
    bool v4221 = v4216 == 9;	// L6689
    bool v4222 = v4217 | v4218;	// L6690
    bool v4223 = v4222 | v4219;	// L6691
    bool v4224 = v4223 | v4220;	// L6692
    bool v4225 = v4224 | v4221;	// L6693
    if (v4225) {	// L6694
      int32_t v4226 = a_vld4;	// L6695
      int32_t v4227 = b_vld4;	// L6696
      int64_t v4228 = v4226;	// L6697
      int64_t v4229 = v4227;	// L6698
      int64_t v4230 = v4228 * v4229;	// L6699
      int32_t v4231 = v4230;	// L6700
      res_vld4 = v4231;	// L6701
    }
    int32_t v4232 = grant4;	// L6703
    bool v4233 = v4232 == 0;	// L6704
    if (v4233) {	// L6705
      res_vld4 = 0;	// L6706
    }
    int32_t is_rtr4;	// L6708
    is_rtr4 = 0;	// L6709
    int32_t v4235 = op4;	// L6710
    bool v4236 = v4235 >= 4;	// L6711
    ap_int<33> v4237 = v4235;	// L6712
    bool v4238 = v4237 <= 7;	// L6713
    bool v4239 = v4236 & v4238;	// L6714
    if (v4239) {	// L6715
      is_rtr4 = 1;	// L6716
    }
    l_S_k_6_k9: for (int k9 = 0; k9 < 4; k9++) {	// L6718
      uint8_t v4241 = sb_v4[(k9 + 1)];	// L6719
      sb_v4[k9] = v4241;	// L6720
      uint8_t v4242 = sb_dst4[(k9 + 1)];	// L6721
      sb_dst4[k9] = v4242;	// L6722
      uint8_t v4243 = sb_cmp4[(k9 + 1)];	// L6723
      sb_cmp4[k9] = v4243;	// L6724
      uint8_t v4244 = sb_rtr4[(k9 + 1)];	// L6725
      sb_rtr4[k9] = v4244;	// L6726
      uint8_t v4245 = sb_inj4[(k9 + 1)];	// L6727
      sb_inj4[k9] = v4245;	// L6728
      uint8_t v4246 = sb_dir4[(k9 + 1)];	// L6729
      sb_dir4[k9] = v4246;	// L6730
      uint8_t v4247 = sb_id4[(k9 + 1)];	// L6731
      sb_id4[k9] = v4247;	// L6732
      uint8_t v4248 = sb_rvld4[(k9 + 1)];	// L6733
      sb_rvld4[k9] = v4248;	// L6734
      uint8_t v4249 = sb_ix4[(k9 + 1)];	// L6735
      sb_ix4[k9] = v4249;	// L6736
    }
    sb_v4[4] = 0;	// L6738
    int32_t v4250 = grant4;	// L6739
    bool v4251 = v4250 == 1;	// L6740
    if (v4251) {	// L6741
      half v4252 = res4;	// L6742
      int8_t v4253 = resq_wr4;	// L6743
      int v4254 = v4253;	// L6744
      resq4[v4254] = v4252;	// L6745
      int32_t cq4;	// L6746
      cq4 = 0;	// L6747
      int32_t v4256 = op4;	// L6748
      bool v4257 = v4256 == 8;	// L6749
      if (v4257) {	// L6750
        half v4258 = a4;	// L6751
        half v4259 = b4;	// L6752
        bool v4260 = v4258 >= v4259;	// L6753
        if (v4260) {	// L6754
          cq4 = 1;	// L6755
        }
      }
      int32_t v4261 = op4;	// L6758
      bool v4262 = v4261 == 9;	// L6759
      if (v4262) {	// L6760
        half v4263 = a4;	// L6761
        half v4264 = b4;	// L6762
        bool v4265 = v4263 < v4264;	// L6763
        if (v4265) {	// L6764
          cq4 = 1;	// L6765
        }
      }
      int32_t v4266 = cq4;	// L6768
      uint8_t v4267 = v4266;	// L6769
      int8_t v4268 = resq_wr4;	// L6770
      int v4269 = v4268;	// L6771
      cmpq4[v4269] = v4267;	// L6772
      sb_v4[4] = 1;	// L6773
      int32_t v4270 = dst4;	// L6774
      uint8_t v4271 = v4270;	// L6775
      sb_dst4[4] = v4271;	// L6776
      int8_t v4272 = resq_wr4;	// L6777
      sb_ix4[4] = v4272;	// L6778
      sb_cmp4[4] = 0;	// L6779
      int32_t v4273 = op4;	// L6780
      bool v4274 = v4273 == 8;	// L6781
      bool v4275 = v4273 == 9;	// L6782
      bool v4276 = v4274 | v4275;	// L6783
      if (v4276) {	// L6784
        sb_cmp4[4] = 1;	// L6785
      }
      int32_t v4277 = is_rtr4;	// L6787
      int32_t rtrf4;	// L6788
      rtrf4 = v4277;	// L6789
      int32_t v4279 = is_cond4;	// L6790
      bool v4280 = v4279 == 1;	// L6791
      if (v4280) {	// L6792
        rtrf4 = 1;	// L6793
      }
      int32_t v4281 = rtrf4;	// L6795
      uint8_t v4282 = v4281;	// L6796
      sb_rtr4[4] = v4282;	// L6797
      int32_t v4283 = is_rtr4;	// L6798
      int32_t inj4;	// L6799
      inj4 = v4283;	// L6800
      int32_t v4285 = is_cond4;	// L6801
      bool v4286 = v4285 == 1;	// L6802
      int8_t v4287 = condition_reg4;	// L6803
      int32_t v4288 = v4287;	// L6804
      bool v4289 = v4288 == 1;	// L6805
      bool v4290 = v4286 & v4289;	// L6806
      if (v4290) {	// L6807
        inj4 = 1;	// L6808
      }
      int32_t v4291 = inj4;	// L6810
      uint8_t v4292 = v4291;	// L6811
      sb_inj4[4] = v4292;	// L6812
      int32_t v4293 = op4;	// L6813
      int32_t v4294 = v4293 & 3;	// L6814
      uint8_t v4295 = v4294;	// L6815
      sb_dir4[4] = v4295;	// L6816
      int32_t v4296 = s24;	// L6817
      uint8_t v4297 = v4296;	// L6818
      sb_id4[4] = v4297;	// L6819
      int32_t v4298 = res_vld4;	// L6820
      uint8_t v4299 = v4298;	// L6821
      sb_rvld4[4] = v4299;	// L6822
      int8_t v4300 = resq_wr4;	// L6823
      ap_int<33> v4301 = v4300;	// L6824
      ap_int<33> v4302 = v4301 + 1;	// L6825
      ap_int<33> v4303 = v4302 & 7;	// L6826
      uint8_t v4304 = v4303;	// L6827
      resq_wr4 = v4304;	// L6828
    }
    ap_int<17> v4305 = tx_n4;	// L6830
    txn_r4 = v4305;	// L6831
    ap_int<17> v4306 = tx_s4;	// L6832
    txs_r4 = v4306;	// L6833
    ap_int<17> v4307 = tx_w4;	// L6834
    txw_r4 = v4307;	// L6835
    ap_int<17> v4308 = tx_e4;	// L6836
    txe_r4 = v4308;	// L6837
    int32_t v4309 = crv_vld4;	// L6838
    bool v4310 = v4309 == 1;	// L6839
    if (v4310) {	// L6840
      int32_t v4311 = crv_mode4;	// L6841
      bool v4312 = v4311 == 1;	// L6842
      if (v4312) {	// L6843
        int32_t v4313 = crv_addr4;	// L6844
        int32_t v4314 = v4313 >> 3;	// L6845
        int32_t v4315 = v4314 & 1;	// L6846
        bool v4316 = v4315 == 1;	// L6847
        if (v4316) {	// L6848
          int32_t v4317 = crv_raw4;	// L6849
          int32_t v4318 = crv_addr4;	// L6850
          int32_t v4319 = v4318 & 7;	// L6851
          int v4320 = v4319;	// L6852
          irf4[v4320] = v4317;	// L6853
        } else {
          int32_t v4321 = crv_addr4;	// L6855
          bool v4322 = v4321 == 0;	// L6856
          if (v4322) {	// L6857
            int32_t v4323 = crv_raw4;	// L6858
            int32_t v4324 = v4323 & 255;	// L6859
            dsmask4 = v4324;	// L6860
            int32_t v4325 = crv_raw4;	// L6861
            int32_t v4326 = v4325 >> 8;	// L6862
            int32_t v4327 = v4326 & 7;	// L6863
            cfg_isz4 = v4327;	// L6864
            int32_t v4328 = crv_raw4;	// L6865
            int32_t v4329 = v4328 >> 15;	// L6866
            int32_t v4330 = v4329 & 1;	// L6867
            bool v4331 = v4330 == 1;	// L6868
            if (v4331) {	// L6869
              fetch_en4 = 1;	// L6870
              instr_cnt4 = 0;	// L6871
              iter_cnt4 = 0;	// L6872
            }
          } else {
            int32_t v4332 = crv_addr4;	// L6875
            bool v4333 = v4332 == 1;	// L6876
            if (v4333) {	// L6877
              int32_t v4334 = crv_raw4;	// L6878
              int32_t v4335 = v4334 & 255;	// L6879
              cfg_itsz4 = v4335;	// L6880
            }
          }
        }
      } else {
        int32_t v4336 = crv_addr4;	// L6885
        bool v4337 = v4336 < 8;	// L6886
        int32_t v4338 = dsmask4;	// L6887
        int32_t v4339 = v4338 >> v4336;	// L6888
        int32_t v4340 = v4339 & 1;	// L6889
        bool v4341 = v4340 == 1;	// L6890
        bool v4342 = v4337 & v4341;	// L6891
        if (v4342) {	// L6892
          int32_t v4343 = crv_addr4;	// L6893
          int v4344 = v4343;	// L6894
          int32_t v4345 = drf_full4[v4344];	// L6895
          bool v4346 = v4345 == 0;	// L6896
          if (v4346) {	// L6897
            half v4347 = crv_data4;	// L6898
            int32_t v4348 = crv_addr4;	// L6899
            int v4349 = v4348;	// L6900
            drf4[v4349] = v4347;	// L6901
            int32_t v4350 = crv_addr4;	// L6902
            int v4351 = v4350;	// L6903
            drf_full4[v4351] = 1;	// L6904
          }
        } else {
          half v4352 = crv_data4;	// L6907
          int32_t v4353 = crv_addr4;	// L6908
          int v4354 = v4353;	// L6909
          drf4[v4354] = v4352;	// L6910
        }
      }
    }
    ap_int<17> v4355 = txe_r4;	// L6914
    bool v4356;
    ap_int<17> v4356_tmp = v4355;
    v4356 = v4356_tmp[0];	// L6915
    int32_t v4357 = v4356;	// L6916
    bool v4358 = v4357 == 1;	// L6917
    if (v4358) {	// L6918
      ap_int<17> v4359 = txe_r4;	// L6919
      v3512.write(v4359);	// L6920
    }
    ap_int<17> v4360 = txw_r4;	// L6922
    bool v4361;
    ap_int<17> v4361_tmp = v4360;
    v4361 = v4361_tmp[0];	// L6923
    int32_t v4362 = v4361;	// L6924
    bool v4363 = v4362 == 1;	// L6925
    if (v4363) {	// L6926
      ap_int<17> v4364 = txw_r4;	// L6927
      v3513.write(v4364);	// L6928
    }
    ap_int<17> v4365 = txs_r4;	// L6930
    bool v4366;
    ap_int<17> v4366_tmp = v4365;
    v4366 = v4366_tmp[0];	// L6931
    int32_t v4367 = v4366;	// L6932
    bool v4368 = v4367 == 1;	// L6933
    if (v4368) {	// L6934
      ap_int<17> v4369 = txs_r4;	// L6935
      v3514.write(v4369);	// L6936
    }
    ap_int<17> v4370 = txn_r4;	// L6938
    bool v4371;
    ap_int<17> v4371_tmp = v4370;
    v4371 = v4371_tmp[0];	// L6939
    int32_t v4372 = v4371;	// L6940
    bool v4373 = v4372 == 1;	// L6941
    if (v4373) {	// L6942
      ap_int<17> v4374 = txn_r4;	// L6943
      v3515.write(v4374);	// L6944
    }
  }
}

void node_1_1(
  hls::stream< ap_uint<26> >& v4375,
  hls::stream< ap_uint<26> >& v4376,
  hls::stream< ap_uint<26> >& v4377,
  hls::stream< ap_uint<26> >& v4378,
  hls::stream< ap_uint<26> >& v4379,
  hls::stream< ap_uint<26> >& v4380,
  hls::stream< ap_uint<26> >& v4381,
  hls::stream< ap_uint<26> >& v4382,
  hls::stream< ap_uint<17> >& v4383,
  hls::stream< ap_uint<17> >& v4384,
  hls::stream< ap_uint<17> >& v4385,
  hls::stream< ap_uint<17> >& v4386,
  hls::stream< ap_uint<17> >& v4387,
  hls::stream< ap_uint<17> >& v4388,
  hls::stream< ap_uint<17> >& v4389,
  hls::stream< ap_uint<17> >& v4390
) {	// L6949
  int32_t irf5[8];	// L6982
  #pragma HLS array_partition variable=irf5 complete dim=1

  for (int v4392 = 0; v4392 < 8; v4392++) {	// L6983
    irf5[v4392] = 0;	// L6983
  }
  half drf5[8];	// L6984
  #pragma HLS array_partition variable=drf5 complete dim=1

  for (int v4394 = 0; v4394 < 8; v4394++) {	// L6985
    drf5[v4394] = 0.000000;	// L6985
  }
  int32_t drf_full5[8];	// L6986
  #pragma HLS array_partition variable=drf_full5 complete dim=1

  for (int v4396 = 0; v4396 < 8; v4396++) {	// L6987
    drf_full5[v4396] = 0;	// L6987
  }
  int32_t dsmask5;	// L6988
  dsmask5 = 0;	// L6989
  int32_t crv_vld5;	// L6990
  crv_vld5 = 0;	// L6991
  half crv_data5;	// L6992
  crv_data5 = 0.000000;	// L6993
  int32_t crv_addr5;	// L6994
  crv_addr5 = 0;	// L6995
  int32_t crv_mode5;	// L6996
  crv_mode5 = 0;	// L6997
  int32_t crv_raw5;	// L6998
  crv_raw5 = 0;	// L6999
  int32_t csd_vld5;	// L7000
  csd_vld5 = 0;	// L7001
  ap_uint<26> csd_pkt5;	// L7002
  csd_pkt5 = 0;	// L7003
  int32_t csd_dir5;	// L7004
  csd_dir5 = 0;	// L7005
  int32_t row_id5;	// L7006
  row_id5 = 1;	// L7007
  int32_t col_id5;	// L7008
  col_id5 = 1;	// L7009
  ap_uint<17> txn_r5;	// L7010
  txn_r5 = 0;	// L7011
  ap_uint<17> txs_r5;	// L7012
  txs_r5 = 0;	// L7013
  ap_uint<17> txw_r5;	// L7014
  txw_r5 = 0;	// L7015
  ap_uint<17> txe_r5;	// L7016
  txe_r5 = 0;	// L7017
  half hold_v5[4][2];	// L7018
  #pragma HLS array_partition variable=hold_v5 complete dim=1
  #pragma HLS array_partition variable=hold_v5 complete dim=2

  for (int v4413 = 0; v4413 < 4; v4413++) {	// L7019
    for (int v4414 = 0; v4414 < 2; v4414++) {	// L7019
      hold_v5[v4413][v4414] = 0.000000;	// L7019
    }
  }
  uint8_t hold_cnt5[4];	// L7020
  #pragma HLS array_partition variable=hold_cnt5 complete dim=1

  for (int v4416 = 0; v4416 < 4; v4416++) {	// L7021
    hold_cnt5[v4416] = 0;	// L7021
  }
  int32_t crv_ever5;	// L7022
  crv_ever5 = 0;	// L7023
  int32_t fe_ever5;	// L7024
  fe_ever5 = 0;	// L7025
  ap_uint<26> rbuf5[4][2];	// L7026
  #pragma HLS array_partition variable=rbuf5 complete dim=1
  #pragma HLS array_partition variable=rbuf5 complete dim=2

  for (int v4420 = 0; v4420 < 4; v4420++) {	// L7027
    for (int v4421 = 0; v4421 < 2; v4421++) {	// L7027
      rbuf5[v4420][v4421] = 0;	// L7027
    }
  }
  uint8_t rbcnt5[4];	// L7028
  #pragma HLS array_partition variable=rbcnt5 complete dim=1

  for (int v4423 = 0; v4423 < 4; v4423++) {	// L7029
    rbcnt5[v4423] = 0;	// L7029
  }
  int32_t cfg_isz5;	// L7030
  cfg_isz5 = 0;	// L7031
  int32_t cfg_itsz5;	// L7032
  cfg_itsz5 = 0;	// L7033
  uint8_t fetch_en5;	// L7034
  fetch_en5 = 0;	// L7035
  uint8_t instr_cnt5;	// L7036
  instr_cnt5 = 0;	// L7037
  uint8_t iter_cnt5;	// L7038
  iter_cnt5 = 0;	// L7039
  uint8_t condition_reg5;	// L7040
  condition_reg5 = 0;	// L7041
  uint8_t sb_v5[5];	// L7042
  #pragma HLS array_partition variable=sb_v5 complete dim=1

  for (int v4431 = 0; v4431 < 5; v4431++) {	// L7043
    sb_v5[v4431] = 0;	// L7043
  }
  uint8_t sb_dst5[5];	// L7044
  #pragma HLS array_partition variable=sb_dst5 complete dim=1

  for (int v4433 = 0; v4433 < 5; v4433++) {	// L7045
    sb_dst5[v4433] = 0;	// L7045
  }
  uint8_t sb_cmp5[5];	// L7046
  #pragma HLS array_partition variable=sb_cmp5 complete dim=1

  for (int v4435 = 0; v4435 < 5; v4435++) {	// L7047
    sb_cmp5[v4435] = 0;	// L7047
  }
  uint8_t sb_rtr5[5];	// L7048
  #pragma HLS array_partition variable=sb_rtr5 complete dim=1

  for (int v4437 = 0; v4437 < 5; v4437++) {	// L7049
    sb_rtr5[v4437] = 0;	// L7049
  }
  uint8_t sb_inj5[5];	// L7050
  #pragma HLS array_partition variable=sb_inj5 complete dim=1

  for (int v4439 = 0; v4439 < 5; v4439++) {	// L7051
    sb_inj5[v4439] = 0;	// L7051
  }
  uint8_t sb_dir5[5];	// L7052
  #pragma HLS array_partition variable=sb_dir5 complete dim=1

  for (int v4441 = 0; v4441 < 5; v4441++) {	// L7053
    sb_dir5[v4441] = 0;	// L7053
  }
  uint8_t sb_id5[5];	// L7054
  #pragma HLS array_partition variable=sb_id5 complete dim=1

  for (int v4443 = 0; v4443 < 5; v4443++) {	// L7055
    sb_id5[v4443] = 0;	// L7055
  }
  uint8_t sb_rvld5[5];	// L7056
  #pragma HLS array_partition variable=sb_rvld5 complete dim=1

  for (int v4445 = 0; v4445 < 5; v4445++) {	// L7057
    sb_rvld5[v4445] = 0;	// L7057
  }
  uint8_t sb_ix5[5];	// L7058
  #pragma HLS array_partition variable=sb_ix5 complete dim=1

  for (int v4447 = 0; v4447 < 5; v4447++) {	// L7059
    sb_ix5[v4447] = 0;	// L7059
  }
  half resq5[8];	// L7060
  #pragma HLS array_partition variable=resq5 complete dim=1
#pragma HLS dependence variable=resq5 type=inter dependent=false

  for (int v4449 = 0; v4449 < 8; v4449++) {	// L7061
    resq5[v4449] = 0.000000;	// L7061
  }
  uint8_t cmpq5[8];	// L7062
  #pragma HLS array_partition variable=cmpq5 complete dim=1
#pragma HLS dependence variable=cmpq5 type=inter dependent=false

  for (int v4451 = 0; v4451 < 8; v4451++) {	// L7063
    cmpq5[v4451] = 0;	// L7063
  }
  uint8_t resq_wr5;	// L7064
  resq_wr5 = 0;	// L7065
  l_S_t_0_t5: for (int t5 = 0; t5 < 374; t5++) {	// L7066
  #pragma HLS pipeline II=1
    ap_uint<26> p_w5;	// L7067
    p_w5 = 0;	// L7068
    ap_uint<26> p_e5;	// L7069
    p_e5 = 0;	// L7070
    ap_uint<26> p_n5;	// L7071
    p_n5 = 0;	// L7072
    ap_uint<26> p_s5;	// L7073
    p_s5 = 0;	// L7074
    uint8_t v4458 = rbcnt5[0];	// L7075
    int32_t v4459 = v4458;	// L7076
    bool v4460 = v4459 < 2;	// L7077
    if (v4460) {	// L7078
      ap_uint<26> v4461;
      bool v4462 = v4375.read_nb(v4461);
	// L7079
      ap_uint<26> gw5;	// L7080
      gw5 = v4461;	// L7081
      bool okw5;	// L7082
      okw5 = v4462;	// L7083
      bool v4465 = okw5;	// L7084
      if (v4465) {	// L7085
        ap_int<26> v4466 = gw5;	// L7086
        p_w5 = v4466;	// L7087
      }
    }
    uint8_t v4467 = rbcnt5[1];	// L7090
    int32_t v4468 = v4467;	// L7091
    bool v4469 = v4468 < 2;	// L7092
    if (v4469) {	// L7093
      ap_uint<26> v4470;
      bool v4471 = v4376.read_nb(v4470);
	// L7094
      ap_uint<26> ge5;	// L7095
      ge5 = v4470;	// L7096
      bool oke5;	// L7097
      oke5 = v4471;	// L7098
      bool v4474 = oke5;	// L7099
      if (v4474) {	// L7100
        ap_int<26> v4475 = ge5;	// L7101
        p_e5 = v4475;	// L7102
      }
    }
    uint8_t v4476 = rbcnt5[2];	// L7105
    int32_t v4477 = v4476;	// L7106
    bool v4478 = v4477 < 2;	// L7107
    if (v4478) {	// L7108
      ap_uint<26> v4479;
      bool v4480 = v4377.read_nb(v4479);
	// L7109
      ap_uint<26> gn5;	// L7110
      gn5 = v4479;	// L7111
      bool okn5;	// L7112
      okn5 = v4480;	// L7113
      bool v4483 = okn5;	// L7114
      if (v4483) {	// L7115
        ap_int<26> v4484 = gn5;	// L7116
        p_n5 = v4484;	// L7117
      }
    }
    uint8_t v4485 = rbcnt5[3];	// L7120
    int32_t v4486 = v4485;	// L7121
    bool v4487 = v4486 < 2;	// L7122
    if (v4487) {	// L7123
      ap_uint<26> v4488;
      bool v4489 = v4378.read_nb(v4488);
	// L7124
      ap_uint<26> gs5;	// L7125
      gs5 = v4488;	// L7126
      bool oks5;	// L7127
      oks5 = v4489;	// L7128
      bool v4492 = oks5;	// L7129
      if (v4492) {	// L7130
        ap_int<26> v4493 = gs5;	// L7131
        p_s5 = v4493;	// L7132
      }
    }
    ap_uint<26> fin5[4];	// L7135
    for (int v4495 = 0; v4495 < 4; v4495++) {	// L7136
      fin5[v4495] = 0;	// L7136
    }
    ap_int<26> v4496 = p_w5;	// L7137
    fin5[0] = v4496;	// L7138
    ap_int<26> v4497 = p_e5;	// L7139
    fin5[1] = v4497;	// L7140
    ap_int<26> v4498 = p_n5;	// L7141
    fin5[2] = v4498;	// L7142
    ap_int<26> v4499 = p_s5;	// L7143
    fin5[3] = v4499;	// L7144
    l_S_d_0_d20: for (int d20 = 0; d20 < 4; d20++) {	// L7145
      ap_uint<26> v4501 = fin5[d20];	// L7146
      bool v4502;
      ap_int<26> v4502_tmp = v4501;
      v4502 = v4502_tmp[25];	// L7147
      int32_t v4503 = v4502;	// L7148
      bool v4504 = v4503 == 1;	// L7149
      uint8_t v4505 = rbcnt5[d20];	// L7150
      int32_t v4506 = v4505;	// L7151
      bool v4507 = v4506 < 2;	// L7152
      bool v4508 = v4504 & v4507;	// L7153
      if (v4508) {	// L7154
        ap_uint<26> v4509 = fin5[d20];	// L7155
        uint8_t v4510 = rbcnt5[d20];	// L7156
        int v4511 = v4510;	// L7157
        rbuf5[d20][v4511] = v4509;	// L7158
        uint8_t v4512 = rbcnt5[d20];	// L7159
        ap_int<33> v4513 = v4512;	// L7160
        ap_int<33> v4514 = v4513 + 1;	// L7161
        uint8_t v4515 = v4514;	// L7162
        rbcnt5[d20] = v4515;	// L7163
      }
    }
    ap_uint<26> hd5[4];	// L7166
    for (int v4517 = 0; v4517 < 4; v4517++) {	// L7167
      hd5[v4517] = 0;	// L7167
    }
    int32_t hvld5[4];	// L7168
    for (int v4519 = 0; v4519 < 4; v4519++) {	// L7169
      hvld5[v4519] = 0;	// L7169
    }
    int32_t hit5[4];	// L7170
    for (int v4521 = 0; v4521 < 4; v4521++) {	// L7171
      hit5[v4521] = 0;	// L7171
    }
    int32_t axis5[4];	// L7172
    for (int v4523 = 0; v4523 < 4; v4523++) {	// L7173
      axis5[v4523] = 0;	// L7173
    }
    int32_t v4524 = col_id5;	// L7174
    axis5[0] = v4524;	// L7175
    int32_t v4525 = col_id5;	// L7176
    axis5[1] = v4525;	// L7177
    int32_t v4526 = row_id5;	// L7178
    axis5[2] = v4526;	// L7179
    int32_t v4527 = row_id5;	// L7180
    axis5[3] = v4527;	// L7181
    l_S_d_1_d21: for (int d21 = 0; d21 < 4; d21++) {	// L7182
      uint8_t v4529 = rbcnt5[d21];	// L7183
      int32_t v4530 = v4529;	// L7184
      bool v4531 = v4530 > 0;	// L7185
      if (v4531) {	// L7186
        ap_uint<26> v4532 = rbuf5[d21][0];	// L7187
        hd5[d21] = v4532;	// L7188
        hvld5[d21] = 1;	// L7189
        ap_uint<26> v4533 = hd5[d21];	// L7190
        ap_int<4> v4534;
        ap_int<26> v4534_tmp = v4533;
        v4534 = v4534_tmp(24, 21);	// L7191
        int32_t v4535 = axis5[d21];	// L7192
        int32_t v4536 = v4534;	// L7193
        bool v4537 = v4536 == v4535;	// L7194
        if (v4537) {	// L7195
          hit5[d21] = 1;	// L7196
        }
      }
    }
    ap_uint<26> o_crv5;	// L7200
    o_crv5 = 0;	// L7201
    int32_t crv_in5;	// L7202
    crv_in5 = -1;	// L7203
    int32_t v4540 = hit5[3];	// L7204
    bool v4541 = v4540 == 1;	// L7205
    if (v4541) {	// L7206
      ap_uint<26> v4542 = hd5[3];	// L7207
      o_crv5 = v4542;	// L7208
      crv_in5 = 3;	// L7209
    } else {
      int32_t v4543 = hit5[2];	// L7211
      bool v4544 = v4543 == 1;	// L7212
      if (v4544) {	// L7213
        ap_uint<26> v4545 = hd5[2];	// L7214
        o_crv5 = v4545;	// L7215
        crv_in5 = 2;	// L7216
      } else {
        int32_t v4546 = hit5[1];	// L7218
        bool v4547 = v4546 == 1;	// L7219
        if (v4547) {	// L7220
          ap_uint<26> v4548 = hd5[1];	// L7221
          o_crv5 = v4548;	// L7222
          crv_in5 = 1;	// L7223
        } else {
          int32_t v4549 = hit5[0];	// L7225
          bool v4550 = v4549 == 1;	// L7226
          if (v4550) {	// L7227
            ap_uint<26> v4551 = hd5[0];	// L7228
            o_crv5 = v4551;	// L7229
            crv_in5 = 0;	// L7230
          }
        }
      }
    }
    int32_t pop5[4];	// L7235
    for (int v4553 = 0; v4553 < 4; v4553++) {	// L7236
      pop5[v4553] = 0;	// L7236
    }
    int32_t inj_done5;	// L7237
    inj_done5 = 0;	// L7238
    int32_t idir5;	// L7239
    idir5 = -1;	// L7240
    ap_int<26> v4556 = csd_pkt5;	// L7241
    bool v4557;
    ap_int<26> v4557_tmp = v4556;
    v4557 = v4557_tmp[25];	// L7242
    int32_t v4558 = v4557;	// L7243
    bool v4559 = v4558 == 1;	// L7244
    if (v4559) {	// L7245
      int32_t v4560 = csd_dir5;	// L7246
      ap_int<33> v4561 = v4560;	// L7247
      ap_int<33> v4562 = 3 - v4561;	// L7248
      int32_t v4563 = v4562;	// L7249
      idir5 = v4563;	// L7250
    }
    int32_t v4564 = idir5;	// L7252
    bool v4565 = v4564 == 0;	// L7253
    if (v4565) {	// L7254
      ap_int<26> v4566 = csd_pkt5;	// L7255
      bool v4567 = v4379.write_nb(v4566);
	// L7256
      if (v4567) {	// L7257
        inj_done5 = 1;	// L7258
      }
    } else {
      int32_t v4568 = hvld5[0];	// L7261
      bool v4569 = v4568 == 1;	// L7262
      int32_t v4570 = hit5[0];	// L7263
      bool v4571 = v4570 == 0;	// L7264
      bool v4572 = v4569 & v4571;	// L7265
      if (v4572) {	// L7266
        ap_uint<26> v4573 = hd5[0];	// L7267
        bool v4574 = v4379.write_nb(v4573);
	// L7268
        if (v4574) {	// L7269
          pop5[0] = 1;	// L7270
        }
      }
    }
    int32_t v4575 = idir5;	// L7274
    bool v4576 = v4575 == 1;	// L7275
    if (v4576) {	// L7276
      ap_int<26> v4577 = csd_pkt5;	// L7277
      bool v4578 = v4380.write_nb(v4577);
	// L7278
      if (v4578) {	// L7279
        inj_done5 = 1;	// L7280
      }
    } else {
      int32_t v4579 = hvld5[1];	// L7283
      bool v4580 = v4579 == 1;	// L7284
      int32_t v4581 = hit5[1];	// L7285
      bool v4582 = v4581 == 0;	// L7286
      bool v4583 = v4580 & v4582;	// L7287
      if (v4583) {	// L7288
        ap_uint<26> v4584 = hd5[1];	// L7289
        bool v4585 = v4380.write_nb(v4584);
	// L7290
        if (v4585) {	// L7291
          pop5[1] = 1;	// L7292
        }
      }
    }
    int32_t v4586 = idir5;	// L7296
    bool v4587 = v4586 == 2;	// L7297
    if (v4587) {	// L7298
      ap_int<26> v4588 = csd_pkt5;	// L7299
      bool v4589 = v4381.write_nb(v4588);
	// L7300
      if (v4589) {	// L7301
        inj_done5 = 1;	// L7302
      }
    } else {
      int32_t v4590 = hvld5[2];	// L7305
      bool v4591 = v4590 == 1;	// L7306
      int32_t v4592 = hit5[2];	// L7307
      bool v4593 = v4592 == 0;	// L7308
      bool v4594 = v4591 & v4593;	// L7309
      if (v4594) {	// L7310
        ap_uint<26> v4595 = hd5[2];	// L7311
        bool v4596 = v4381.write_nb(v4595);
	// L7312
        if (v4596) {	// L7313
          pop5[2] = 1;	// L7314
        }
      }
    }
    int32_t v4597 = idir5;	// L7318
    bool v4598 = v4597 == 3;	// L7319
    if (v4598) {	// L7320
      ap_int<26> v4599 = csd_pkt5;	// L7321
      bool v4600 = v4382.write_nb(v4599);
	// L7322
      if (v4600) {	// L7323
        inj_done5 = 1;	// L7324
      }
    } else {
      int32_t v4601 = hvld5[3];	// L7327
      bool v4602 = v4601 == 1;	// L7328
      int32_t v4603 = hit5[3];	// L7329
      bool v4604 = v4603 == 0;	// L7330
      bool v4605 = v4602 & v4604;	// L7331
      if (v4605) {	// L7332
        ap_uint<26> v4606 = hd5[3];	// L7333
        bool v4607 = v4382.write_nb(v4606);
	// L7334
        if (v4607) {	// L7335
          pop5[3] = 1;	// L7336
        }
      }
    }
    int32_t v4608 = crv_in5;	// L7340
    bool v4609 = v4608 >= 0;	// L7341
    if (v4609) {	// L7342
      int32_t v4610 = crv_in5;	// L7343
      int v4611 = v4610;	// L7344
      pop5[v4611] = 1;	// L7345
    }
    l_S_d_2_d22: for (int d22 = 0; d22 < 4; d22++) {	// L7347
      int32_t v4613 = pop5[d22];	// L7348
      bool v4614 = v4613 == 1;	// L7349
      if (v4614) {	// L7350
        l_S_sft_2_sft5: for (int sft5 = 0; sft5 < 1; sft5++) {	// L7351
          ap_uint<26> v4616 = rbuf5[d22][(sft5 + 1)];	// L7352
          rbuf5[d22][sft5] = v4616;	// L7353
        }
        uint8_t v4617 = rbcnt5[d22];	// L7355
        ap_int<33> v4618 = v4617;	// L7356
        ap_int<33> v4619 = v4618 - 1;	// L7357
        uint8_t v4620 = v4619;	// L7358
        rbcnt5[d22] = v4620;	// L7359
      }
    }
    int32_t v4621 = inj_done5;	// L7362
    bool v4622 = v4621 == 1;	// L7363
    if (v4622) {	// L7364
      csd_pkt5 = 0;	// L7365
    }
    ap_int<26> v4623 = o_crv5;	// L7367
    bool v4624;
    ap_int<26> v4624_tmp = v4623;
    v4624 = v4624_tmp[25];	// L7368
    int32_t v4625 = v4624;	// L7369
    crv_vld5 = v4625;	// L7370
    int32_t v4626 = crv_vld5;	// L7371
    bool v4627 = v4626 == 1;	// L7372
    if (v4627) {	// L7373
      crv_ever5 = 1;	// L7374
    }
    ap_int<26> v4628 = o_crv5;	// L7376
    int16_t v4629;
    ap_int<26> v4629_tmp = v4628;
    v4629 = v4629_tmp(15, 0);	// L7377
    half v4630;
    union { uint16_t from; half to;} _converter_v4629_to_v4630 = {};
    _converter_v4629_to_v4630.from = v4629;
    v4630 = _converter_v4629_to_v4630.to;	// L7378
    crv_data5 = v4630;	// L7379
    ap_int<26> v4631 = o_crv5;	// L7380
    ap_int<4> v4632;
    ap_int<26> v4632_tmp = v4631;
    v4632 = v4632_tmp(19, 16);	// L7381
    int32_t v4633 = v4632;	// L7382
    crv_addr5 = v4633;	// L7383
    ap_int<26> v4634 = o_crv5;	// L7384
    bool v4635;
    ap_int<26> v4635_tmp = v4634;
    v4635 = v4635_tmp[20];	// L7385
    int32_t v4636 = v4635;	// L7386
    crv_mode5 = v4636;	// L7387
    ap_int<26> v4637 = o_crv5;	// L7388
    int16_t v4638;
    ap_int<26> v4638_tmp = v4637;
    v4638 = v4638_tmp(15, 0);	// L7389
    int32_t v4639 = v4638;	// L7390
    crv_raw5 = v4639;	// L7391
    half rxv5[4];	// L7392
    for (int v4641 = 0; v4641 < 4; v4641++) {	// L7393
      rxv5[v4641] = 0.000000;	// L7393
    }
    int32_t rxvld5[4];	// L7394
    for (int v4643 = 0; v4643 < 4; v4643++) {	// L7395
      rxvld5[v4643] = 0;	// L7395
    }
    uint8_t v4644 = hold_cnt5[0];	// L7396
    int32_t v4645 = v4644;	// L7397
    bool v4646 = v4645 < 2;	// L7398
    if (v4646) {	// L7399
      ap_uint<17> v4647;
      bool v4648 = v4383.read_nb(v4647);
	// L7400
      ap_uint<17> sgn5;	// L7401
      sgn5 = v4647;	// L7402
      bool sqn5;	// L7403
      sqn5 = v4648;	// L7404
      bool v4651 = sqn5;	// L7405
      int32_t v4652 = v4651;	// L7406
      bool v4653 = v4652 == 1;	// L7407
      if (v4653) {	// L7408
        ap_int<17> v4654 = sgn5;	// L7409
        int16_t v4655;
        ap_int<17> v4655_tmp = v4654;
        v4655 = v4655_tmp(16, 1);	// L7410
        half v4656;
        union { uint16_t from; half to;} _converter_v4655_to_v4656 = {};
        _converter_v4655_to_v4656.from = v4655;
        v4656 = _converter_v4655_to_v4656.to;	// L7411
        rxv5[0] = v4656;	// L7412
        rxvld5[0] = 1;	// L7413
      }
    }
    uint8_t v4657 = hold_cnt5[1];	// L7416
    int32_t v4658 = v4657;	// L7417
    bool v4659 = v4658 < 2;	// L7418
    if (v4659) {	// L7419
      ap_uint<17> v4660;
      bool v4661 = v4384.read_nb(v4660);
	// L7420
      ap_uint<17> sgs5;	// L7421
      sgs5 = v4660;	// L7422
      bool sqs5;	// L7423
      sqs5 = v4661;	// L7424
      bool v4664 = sqs5;	// L7425
      int32_t v4665 = v4664;	// L7426
      bool v4666 = v4665 == 1;	// L7427
      if (v4666) {	// L7428
        ap_int<17> v4667 = sgs5;	// L7429
        int16_t v4668;
        ap_int<17> v4668_tmp = v4667;
        v4668 = v4668_tmp(16, 1);	// L7430
        half v4669;
        union { uint16_t from; half to;} _converter_v4668_to_v4669 = {};
        _converter_v4668_to_v4669.from = v4668;
        v4669 = _converter_v4668_to_v4669.to;	// L7431
        rxv5[1] = v4669;	// L7432
        rxvld5[1] = 1;	// L7433
      }
    }
    uint8_t v4670 = hold_cnt5[2];	// L7436
    int32_t v4671 = v4670;	// L7437
    bool v4672 = v4671 < 2;	// L7438
    if (v4672) {	// L7439
      ap_uint<17> v4673;
      bool v4674 = v4385.read_nb(v4673);
	// L7440
      ap_uint<17> sgw5;	// L7441
      sgw5 = v4673;	// L7442
      bool sqw5;	// L7443
      sqw5 = v4674;	// L7444
      bool v4677 = sqw5;	// L7445
      int32_t v4678 = v4677;	// L7446
      bool v4679 = v4678 == 1;	// L7447
      if (v4679) {	// L7448
        ap_int<17> v4680 = sgw5;	// L7449
        int16_t v4681;
        ap_int<17> v4681_tmp = v4680;
        v4681 = v4681_tmp(16, 1);	// L7450
        half v4682;
        union { uint16_t from; half to;} _converter_v4681_to_v4682 = {};
        _converter_v4681_to_v4682.from = v4681;
        v4682 = _converter_v4681_to_v4682.to;	// L7451
        rxv5[2] = v4682;	// L7452
        rxvld5[2] = 1;	// L7453
      }
    }
    uint8_t v4683 = hold_cnt5[3];	// L7456
    int32_t v4684 = v4683;	// L7457
    bool v4685 = v4684 < 2;	// L7458
    if (v4685) {	// L7459
      ap_uint<17> v4686;
      bool v4687 = v4386.read_nb(v4686);
	// L7460
      ap_uint<17> sge5;	// L7461
      sge5 = v4686;	// L7462
      bool sqe5;	// L7463
      sqe5 = v4687;	// L7464
      bool v4690 = sqe5;	// L7465
      int32_t v4691 = v4690;	// L7466
      bool v4692 = v4691 == 1;	// L7467
      if (v4692) {	// L7468
        ap_int<17> v4693 = sge5;	// L7469
        int16_t v4694;
        ap_int<17> v4694_tmp = v4693;
        v4694 = v4694_tmp(16, 1);	// L7470
        half v4695;
        union { uint16_t from; half to;} _converter_v4694_to_v4695 = {};
        _converter_v4694_to_v4695.from = v4694;
        v4695 = _converter_v4694_to_v4695.to;	// L7471
        rxv5[3] = v4695;	// L7472
        rxvld5[3] = 1;	// L7473
      }
    }
    l_S_d_4_d23: for (int d23 = 0; d23 < 4; d23++) {	// L7476
      int32_t v4697 = rxvld5[d23];	// L7477
      bool v4698 = v4697 == 1;	// L7478
      if (v4698) {	// L7479
        half v4699 = rxv5[d23];	// L7480
        uint8_t v4700 = hold_cnt5[d23];	// L7481
        int v4701 = v4700;	// L7482
        hold_v5[d23][v4701] = v4699;	// L7483
        uint8_t v4702 = hold_cnt5[d23];	// L7484
        ap_int<33> v4703 = v4702;	// L7485
        ap_int<33> v4704 = v4703 + 1;	// L7486
        uint8_t v4705 = v4704;	// L7487
        hold_cnt5[d23] = v4705;	// L7488
      }
    }
    ap_uint<17> tx_n5;	// L7491
    tx_n5 = 0;	// L7492
    ap_uint<17> tx_s5;	// L7493
    tx_s5 = 0;	// L7494
    ap_uint<17> tx_w5;	// L7495
    tx_w5 = 0;	// L7496
    ap_uint<17> tx_e5;	// L7497
    tx_e5 = 0;	// L7498
    uint8_t v4710 = sb_v5[0];	// L7499
    int32_t v4711 = v4710;	// L7500
    bool v4712 = v4711 == 1;	// L7501
    if (v4712) {	// L7502
      uint8_t v4713 = sb_ix5[0];	// L7503
      int v4714 = v4713;	// L7504
      half v4715 = resq5[v4714];	// L7505
      half wb5;
#pragma HLS dependence variable=wb5 type=inter dependent=false	// L7506
      wb5 = v4715;	// L7507
      uint8_t v4717 = sb_cmp5[0];	// L7508
      int32_t v4718 = v4717;	// L7509
      bool v4719 = v4718 == 1;	// L7510
      if (v4719) {	// L7511
        uint8_t v4720 = sb_ix5[0];	// L7512
        int v4721 = v4720;	// L7513
        uint8_t v4722 = cmpq5[v4721];	// L7514
        condition_reg5 = v4722;	// L7515
      }
      uint8_t v4723 = sb_rtr5[0];	// L7517
      int32_t v4724 = v4723;	// L7518
      bool v4725 = v4724 == 1;	// L7519
      if (v4725) {	// L7520
        uint8_t v4726 = sb_inj5[0];	// L7521
        int32_t v4727 = v4726;	// L7522
        bool v4728 = v4727 == 1;	// L7523
        ap_int<26> v4729 = csd_pkt5;	// L7524
        bool v4730;
        ap_int<26> v4730_tmp = v4729;
        v4730 = v4730_tmp[25];	// L7525
        int32_t v4731 = v4730;	// L7526
        bool v4732 = v4731 == 0;	// L7527
        bool v4733 = v4728 & v4732;	// L7528
        if (v4733) {	// L7529
          half v4734 = wb5;	// L7530
          uint16_t v4735;
          union { half from; uint16_t to;} _converter_v4734_to_v4735 = {};
          _converter_v4734_to_v4735.from = v4734;
          v4735 = _converter_v4734_to_v4735.to;	// L7531
          ap_int<26> v4736 = csd_pkt5;	// L7532
          ap_int<26> v4737;
          ap_int<26> v4737_tmp = v4736;
          v4737_tmp(15, 0) = v4735;
          v4737 = v4737_tmp;	// L7533
          csd_pkt5 = v4737;	// L7534
          uint8_t v4738 = sb_dst5[0];	// L7535
          ap_uint<4> v4739 = v4738;	// L7536
          ap_int<26> v4740 = csd_pkt5;	// L7537
          ap_int<26> v4741;
          ap_int<26> v4741_tmp = v4740;
          v4741_tmp(19, 16) = v4739;
          v4741 = v4741_tmp;	// L7538
          csd_pkt5 = v4741;	// L7539
          uint8_t v4742 = sb_id5[0];	// L7540
          ap_uint<4> v4743 = v4742;	// L7541
          ap_int<26> v4744 = csd_pkt5;	// L7542
          ap_int<26> v4745;
          ap_int<26> v4745_tmp = v4744;
          v4745_tmp(24, 21) = v4743;
          v4745 = v4745_tmp;	// L7543
          csd_pkt5 = v4745;	// L7544
          uint8_t v4746 = sb_rvld5[0];	// L7545
          bool v4747 = v4746;	// L7546
          ap_int<26> v4748 = csd_pkt5;	// L7547
          ap_int<26> v4749;
          ap_int<26> v4749_tmp = v4748;
          v4749_tmp[25] = v4747;          v4749 = v4749_tmp;	// L7548
          csd_pkt5 = v4749;	// L7549
          uint8_t v4750 = sb_dir5[0];	// L7550
          int32_t v4751 = v4750;	// L7551
          csd_dir5 = v4751;	// L7552
        }
      } else {
        uint8_t v4752 = sb_dst5[0];	// L7555
        int32_t v4753 = v4752;	// L7556
        bool v4754 = v4753 >= 12;	// L7557
        if (v4754) {	// L7558
          ap_uint<17> tw05;	// L7559
          tw05 = 0;	// L7560
          uint8_t v4756 = sb_rvld5[0];	// L7561
          bool v4757 = v4756;	// L7562
          ap_int<17> v4758 = tw05;	// L7563
          ap_int<17> v4759;
          ap_int<17> v4759_tmp = v4758;
          v4759_tmp[0] = v4757;          v4759 = v4759_tmp;	// L7564
          tw05 = v4759;	// L7565
          half v4760 = wb5;	// L7566
          uint16_t v4761;
          union { half from; uint16_t to;} _converter_v4760_to_v4761 = {};
          _converter_v4760_to_v4761.from = v4760;
          v4761 = _converter_v4760_to_v4761.to;	// L7567
          ap_int<17> v4762 = tw05;	// L7568
          ap_int<17> v4763;
          ap_int<17> v4763_tmp = v4762;
          v4763_tmp(16, 1) = v4761;
          v4763 = v4763_tmp;	// L7569
          tw05 = v4763;	// L7570
          uint8_t v4764 = sb_dst5[0];	// L7571
          int32_t v4765 = v4764;	// L7572
          int32_t v4766 = v4765 & 3;	// L7573
          bool v4767 = v4766 == 0;	// L7574
          if (v4767) {	// L7575
            ap_int<17> v4768 = tw05;	// L7576
            tx_n5 = v4768;	// L7577
          } else {
            uint8_t v4769 = sb_dst5[0];	// L7579
            int32_t v4770 = v4769;	// L7580
            int32_t v4771 = v4770 & 3;	// L7581
            bool v4772 = v4771 == 1;	// L7582
            if (v4772) {	// L7583
              ap_int<17> v4773 = tw05;	// L7584
              tx_s5 = v4773;	// L7585
            } else {
              uint8_t v4774 = sb_dst5[0];	// L7587
              int32_t v4775 = v4774;	// L7588
              int32_t v4776 = v4775 & 3;	// L7589
              bool v4777 = v4776 == 2;	// L7590
              if (v4777) {	// L7591
                ap_int<17> v4778 = tw05;	// L7592
                tx_w5 = v4778;	// L7593
              } else {
                ap_int<17> v4779 = tw05;	// L7595
                tx_e5 = v4779;	// L7596
              }
            }
          }
        } else {
          uint8_t v4780 = sb_rvld5[0];	// L7601
          int32_t v4781 = v4780;	// L7602
          bool v4782 = v4781 == 1;	// L7603
          if (v4782) {	// L7604
            uint8_t v4783 = sb_dst5[0];	// L7605
            int32_t v4784 = v4783;	// L7606
            bool v4785 = v4784 < 8;	// L7607
            int32_t v4786 = dsmask5;	// L7608
            int32_t v4787 = v4786 >> v4784;	// L7609
            int32_t v4788 = v4787 & 1;	// L7610
            bool v4789 = v4788 == 1;	// L7611
            bool v4790 = v4785 & v4789;	// L7612
            if (v4790) {	// L7613
              uint8_t v4791 = sb_dst5[0];	// L7614
              int v4792 = v4791;	// L7615
              int32_t v4793 = drf_full5[v4792];	// L7616
              bool v4794 = v4793 == 0;	// L7617
              if (v4794) {	// L7618
                half v4795 = wb5;	// L7619
                uint8_t v4796 = sb_dst5[0];	// L7620
                int v4797 = v4796;	// L7621
                drf5[v4797] = v4795;	// L7622
                uint8_t v4798 = sb_dst5[0];	// L7623
                int v4799 = v4798;	// L7624
                drf_full5[v4799] = 1;	// L7625
              }
            } else {
              half v4800 = wb5;	// L7628
              uint8_t v4801 = sb_dst5[0];	// L7629
              int32_t v4802 = v4801;	// L7630
              int32_t v4803 = v4802 & 7;	// L7631
              int v4804 = v4803;	// L7632
              drf5[v4804] = v4800;	// L7633
            }
          }
        }
      }
    }
    int32_t pc5;	// L7639
    pc5 = -1;	// L7640
    int8_t v4806 = fetch_en5;	// L7641
    int32_t v4807 = v4806;	// L7642
    bool v4808 = v4807 == 1;	// L7643
    if (v4808) {	// L7644
      int8_t v4809 = instr_cnt5;	// L7645
      int32_t v4810 = v4809;	// L7646
      pc5 = v4810;	// L7647
    }
    int8_t v4811 = fetch_en5;	// L7649
    int32_t v4812 = v4811;	// L7650
    bool v4813 = v4812 == 1;	// L7651
    if (v4813) {	// L7652
      fe_ever5 = 1;	// L7653
    }
    int32_t instr5;	// L7655
    instr5 = 0;	// L7656
    int32_t v4815 = pc5;	// L7657
    bool v4816 = v4815 >= 0;	// L7658
    if (v4816) {	// L7659
      int32_t v4817 = pc5;	// L7660
      int v4818 = v4817;	// L7661
      int32_t v4819 = irf5[v4818];	// L7662
      instr5 = v4819;	// L7663
    }
    int32_t v4820 = instr5;	// L7665
    int32_t v4821 = v4820 & 15;	// L7666
    int32_t op5;	// L7667
    op5 = v4821;	// L7668
    int32_t v4823 = instr5;	// L7669
    int32_t v4824 = v4823 >> 4;	// L7670
    int32_t v4825 = v4824 & 15;	// L7671
    int32_t dst5;	// L7672
    dst5 = v4825;	// L7673
    int32_t v4827 = instr5;	// L7674
    int32_t v4828 = v4827 >> 8;	// L7675
    int32_t v4829 = v4828 & 15;	// L7676
    int32_t s15;	// L7677
    s15 = v4829;	// L7678
    int32_t v4831 = instr5;	// L7679
    int32_t v4832 = v4831 >> 12;	// L7680
    int32_t v4833 = v4832 & 15;	// L7681
    int32_t s25;	// L7682
    s25 = v4833;	// L7683
    half a5;	// L7684
    a5 = 0.000000;	// L7685
    half b5;	// L7686
    b5 = 0.000000;	// L7687
    int32_t v4837 = s15;	// L7688
    bool v4838 = v4837 >= 12;	// L7689
    if (v4838) {	// L7690
      int32_t v4839 = s15;	// L7691
      int32_t v4840 = v4839 & 3;	// L7692
      int v4841 = v4840;	// L7693
      half v4842 = hold_v5[v4841][0];	// L7694
      a5 = v4842;	// L7695
    } else {
      int32_t v4843 = s15;	// L7697
      int v4844 = v4843;	// L7698
      half v4845 = drf5[v4844];	// L7699
      a5 = v4845;	// L7700
    }
    int32_t v4846 = s25;	// L7702
    bool v4847 = v4846 >= 12;	// L7703
    if (v4847) {	// L7704
      int32_t v4848 = s25;	// L7705
      int32_t v4849 = v4848 & 3;	// L7706
      int v4850 = v4849;	// L7707
      half v4851 = hold_v5[v4850][0];	// L7708
      b5 = v4851;	// L7709
    } else {
      int32_t v4852 = s25;	// L7711
      int v4853 = v4852;	// L7712
      half v4854 = drf5[v4853];	// L7713
      b5 = v4854;	// L7714
    }
    int32_t a_vld5;	// L7716
    a_vld5 = 1;	// L7717
    int32_t b_vld5;	// L7718
    b_vld5 = 1;	// L7719
    int32_t v4857 = s15;	// L7720
    bool v4858 = v4857 >= 12;	// L7721
    if (v4858) {	// L7722
      a_vld5 = 0;	// L7723
      int32_t v4859 = s15;	// L7724
      int32_t v4860 = v4859 & 3;	// L7725
      int v4861 = v4860;	// L7726
      uint8_t v4862 = hold_cnt5[v4861];	// L7727
      int32_t v4863 = v4862;	// L7728
      bool v4864 = v4863 > 0;	// L7729
      if (v4864) {	// L7730
        a_vld5 = 1;	// L7731
      }
    }
    int32_t v4865 = s25;	// L7734
    bool v4866 = v4865 >= 12;	// L7735
    if (v4866) {	// L7736
      b_vld5 = 0;	// L7737
      int32_t v4867 = s25;	// L7738
      int32_t v4868 = v4867 & 3;	// L7739
      int v4869 = v4868;	// L7740
      uint8_t v4870 = hold_cnt5[v4869];	// L7741
      int32_t v4871 = v4870;	// L7742
      bool v4872 = v4871 > 0;	// L7743
      if (v4872) {	// L7744
        b_vld5 = 1;	// L7745
      }
    }
    int32_t v4873 = s15;	// L7748
    bool v4874 = v4873 < 8;	// L7749
    int32_t v4875 = dsmask5;	// L7750
    int32_t v4876 = v4875 >> v4873;	// L7751
    int32_t v4877 = v4876 & 1;	// L7752
    bool v4878 = v4877 == 1;	// L7753
    bool v4879 = v4874 & v4878;	// L7754
    if (v4879) {	// L7755
      int32_t v4880 = s15;	// L7756
      int v4881 = v4880;	// L7757
      int32_t v4882 = drf_full5[v4881];	// L7758
      bool v4883 = v4882 == 0;	// L7759
      if (v4883) {	// L7760
        a_vld5 = 0;	// L7761
      }
    }
    int32_t v4884 = s25;	// L7764
    bool v4885 = v4884 < 8;	// L7765
    int32_t v4886 = dsmask5;	// L7766
    int32_t v4887 = v4886 >> v4884;	// L7767
    int32_t v4888 = v4887 & 1;	// L7768
    bool v4889 = v4888 == 1;	// L7769
    bool v4890 = v4885 & v4889;	// L7770
    if (v4890) {	// L7771
      int32_t v4891 = s25;	// L7772
      int v4892 = v4891;	// L7773
      int32_t v4893 = drf_full5[v4892];	// L7774
      bool v4894 = v4893 == 0;	// L7775
      if (v4894) {	// L7776
        b_vld5 = 0;	// L7777
      }
    }
    int32_t binop5;	// L7780
    binop5 = 0;	// L7781
    int32_t v4896 = op5;	// L7782
    bool v4897 = v4896 == 0;	// L7783
    bool v4898 = v4896 == 1;	// L7784
    bool v4899 = v4896 == 2;	// L7785
    bool v4900 = v4896 == 8;	// L7786
    bool v4901 = v4896 == 9;	// L7787
    bool v4902 = v4897 | v4898;	// L7788
    bool v4903 = v4902 | v4899;	// L7789
    bool v4904 = v4903 | v4900;	// L7790
    bool v4905 = v4904 | v4901;	// L7791
    if (v4905) {	// L7792
      binop5 = 1;	// L7793
    }
    int32_t raw5;	// L7795
    raw5 = 0;	// L7796
    int32_t cmp_busy5;	// L7797
    cmp_busy5 = 0;	// L7798
    l_S_k_5_k10: for (int k10 = 0; k10 < 4; k10++) {	// L7799
      uint8_t v4909 = sb_v5[(k10 + 1)];	// L7800
      int32_t v4910 = v4909;	// L7801
      bool v4911 = v4910 == 1;	// L7802
      uint8_t v4912 = sb_rtr5[(k10 + 1)];	// L7803
      int32_t v4913 = v4912;	// L7804
      bool v4914 = v4913 == 0;	// L7805
      uint8_t v4915 = sb_dst5[(k10 + 1)];	// L7806
      int32_t v4916 = v4915;	// L7807
      bool v4917 = v4916 < 12;	// L7808
      bool v4918 = v4911 & v4914;	// L7809
      bool v4919 = v4918 & v4917;	// L7810
      if (v4919) {	// L7811
        int32_t v4920 = s15;	// L7812
        bool v4921 = v4920 < 12;	// L7813
        uint8_t v4922 = sb_dst5[(k10 + 1)];	// L7814
        int32_t v4923 = v4922;	// L7815
        int32_t v4924 = v4923 & 7;	// L7816
        int32_t v4925 = v4920 & 7;	// L7817
        bool v4926 = v4924 == v4925;	// L7818
        bool v4927 = v4921 & v4926;	// L7819
        if (v4927) {	// L7820
          raw5 = 1;	// L7821
        }
        int32_t v4928 = binop5;	// L7823
        bool v4929 = v4928 == 1;	// L7824
        int32_t v4930 = s25;	// L7825
        bool v4931 = v4930 < 12;	// L7826
        uint8_t v4932 = sb_dst5[(k10 + 1)];	// L7827
        int32_t v4933 = v4932;	// L7828
        int32_t v4934 = v4933 & 7;	// L7829
        int32_t v4935 = v4930 & 7;	// L7830
        bool v4936 = v4934 == v4935;	// L7831
        bool v4937 = v4929 & v4931;	// L7832
        bool v4938 = v4937 & v4936;	// L7833
        if (v4938) {	// L7834
          raw5 = 1;	// L7835
        }
      }
      uint8_t v4939 = sb_v5[(k10 + 1)];	// L7838
      int32_t v4940 = v4939;	// L7839
      bool v4941 = v4940 == 1;	// L7840
      uint8_t v4942 = sb_cmp5[(k10 + 1)];	// L7841
      int32_t v4943 = v4942;	// L7842
      bool v4944 = v4943 == 1;	// L7843
      bool v4945 = v4941 & v4944;	// L7844
      if (v4945) {	// L7845
        cmp_busy5 = 1;	// L7846
      }
    }
    int32_t is_cond5;	// L7849
    is_cond5 = 0;	// L7850
    int32_t v4947 = op5;	// L7851
    bool v4948 = v4947 >= 12;	// L7852
    ap_int<33> v4949 = v4947;	// L7853
    bool v4950 = v4949 <= 15;	// L7854
    bool v4951 = v4948 & v4950;	// L7855
    if (v4951) {	// L7856
      is_cond5 = 1;	// L7857
    }
    int32_t grant5;	// L7859
    grant5 = 0;	// L7860
    int32_t v4953 = pc5;	// L7861
    bool v4954 = v4953 >= 0;	// L7862
    if (v4954) {	// L7863
      grant5 = 1;	// L7864
    }
    int32_t v4955 = pc5;	// L7866
    bool v4956 = v4955 >= 0;	// L7867
    int32_t v4957 = a_vld5;	// L7868
    bool v4958 = v4957 == 0;	// L7869
    int32_t v4959 = binop5;	// L7870
    bool v4960 = v4959 == 1;	// L7871
    int32_t v4961 = b_vld5;	// L7872
    bool v4962 = v4961 == 0;	// L7873
    bool v4963 = v4960 & v4962;	// L7874
    bool v4964 = v4958 | v4963;	// L7875
    bool v4965 = v4956 & v4964;	// L7876
    if (v4965) {	// L7877
      grant5 = 0;	// L7878
    }
    int32_t v4966 = pc5;	// L7880
    bool v4967 = v4966 >= 0;	// L7881
    int32_t v4968 = raw5;	// L7882
    bool v4969 = v4968 == 1;	// L7883
    int32_t v4970 = is_cond5;	// L7884
    bool v4971 = v4970 == 1;	// L7885
    int32_t v4972 = cmp_busy5;	// L7886
    bool v4973 = v4972 == 1;	// L7887
    bool v4974 = v4971 & v4973;	// L7888
    bool v4975 = v4969 | v4974;	// L7889
    bool v4976 = v4967 & v4975;	// L7890
    if (v4976) {	// L7891
      grant5 = 0;	// L7892
    }
    int32_t v4977 = grant5;	// L7894
    bool v4978 = v4977 == 1;	// L7895
    if (v4978) {	// L7896
      int8_t v4979 = instr_cnt5;	// L7897
      int32_t v4980 = cfg_isz5;	// L7898
      int32_t v4981 = v4979;	// L7899
      bool v4982 = v4981 == v4980;	// L7900
      if (v4982) {	// L7901
        instr_cnt5 = 0;	// L7902
        int8_t v4983 = iter_cnt5;	// L7903
        int32_t v4984 = cfg_itsz5;	// L7904
        ap_int<33> v4985 = v4984;	// L7905
        ap_int<33> v4986 = v4985 - 1;	// L7906
        ap_int<33> v4987 = v4983;	// L7907
        bool v4988 = v4987 == v4986;	// L7908
        if (v4988) {	// L7909
          fetch_en5 = 0;	// L7910
        } else {
          int8_t v4989 = iter_cnt5;	// L7912
          ap_int<33> v4990 = v4989;	// L7913
          ap_int<33> v4991 = v4990 + 1;	// L7914
          uint8_t v4992 = v4991;	// L7915
          iter_cnt5 = v4992;	// L7916
        }
      } else {
        int8_t v4993 = instr_cnt5;	// L7919
        ap_int<33> v4994 = v4993;	// L7920
        ap_int<33> v4995 = v4994 + 1;	// L7921
        uint8_t v4996 = v4995;	// L7922
        instr_cnt5 = v4996;	// L7923
      }
    }
    int32_t c15;	// L7926
    c15 = -1;	// L7927
    int32_t c25;	// L7928
    c25 = -1;	// L7929
    int32_t v4999 = grant5;	// L7930
    bool v5000 = v4999 == 1;	// L7931
    int32_t v5001 = s15;	// L7932
    bool v5002 = v5001 >= 12;	// L7933
    bool v5003 = v5000 & v5002;	// L7934
    if (v5003) {	// L7935
      int32_t v5004 = s15;	// L7936
      int32_t v5005 = v5004 & 3;	// L7937
      c15 = v5005;	// L7938
    }
    int32_t v5006 = grant5;	// L7940
    bool v5007 = v5006 == 1;	// L7941
    int32_t v5008 = s25;	// L7942
    bool v5009 = v5008 >= 12;	// L7943
    bool v5010 = v5007 & v5009;	// L7944
    if (v5010) {	// L7945
      int32_t v5011 = s25;	// L7946
      int32_t v5012 = v5011 & 3;	// L7947
      c25 = v5012;	// L7948
    }
    int32_t v5013 = c15;	// L7950
    bool v5014 = v5013 >= 0;	// L7951
    if (v5014) {	// L7952
      int32_t v5015 = c15;	// L7953
      int v5016 = v5015;	// L7954
      half v5017 = hold_v5[v5016][1];	// L7955
      hold_v5[v5016][0] = v5017;	// L7956
      int32_t v5018 = c15;	// L7957
      int v5019 = v5018;	// L7958
      uint8_t v5020 = hold_cnt5[v5019];	// L7959
      ap_int<33> v5021 = v5020;	// L7960
      ap_int<33> v5022 = v5021 - 1;	// L7961
      uint8_t v5023 = v5022;	// L7962
      hold_cnt5[v5019] = v5023;	// L7963
    }
    int32_t v5024 = c25;	// L7965
    bool v5025 = v5024 >= 0;	// L7966
    int32_t v5026 = c15;	// L7967
    bool v5027 = v5024 != v5026;	// L7968
    bool v5028 = v5025 & v5027;	// L7969
    if (v5028) {	// L7970
      int32_t v5029 = c25;	// L7971
      int v5030 = v5029;	// L7972
      half v5031 = hold_v5[v5030][1];	// L7973
      hold_v5[v5030][0] = v5031;	// L7974
      int32_t v5032 = c25;	// L7975
      int v5033 = v5032;	// L7976
      uint8_t v5034 = hold_cnt5[v5033];	// L7977
      ap_int<33> v5035 = v5034;	// L7978
      ap_int<33> v5036 = v5035 - 1;	// L7979
      uint8_t v5037 = v5036;	// L7980
      hold_cnt5[v5033] = v5037;	// L7981
    }
    int32_t v5038 = grant5;	// L7983
    bool v5039 = v5038 == 1;	// L7984
    int32_t v5040 = s15;	// L7985
    bool v5041 = v5040 < 8;	// L7986
    int32_t v5042 = dsmask5;	// L7987
    int32_t v5043 = v5042 >> v5040;	// L7988
    int32_t v5044 = v5043 & 1;	// L7989
    bool v5045 = v5044 == 1;	// L7990
    bool v5046 = v5039 & v5041;	// L7991
    bool v5047 = v5046 & v5045;	// L7992
    if (v5047) {	// L7993
      int32_t v5048 = s15;	// L7994
      int v5049 = v5048;	// L7995
      drf_full5[v5049] = 0;	// L7996
    }
    int32_t v5050 = grant5;	// L7998
    bool v5051 = v5050 == 1;	// L7999
    int32_t v5052 = s25;	// L8000
    bool v5053 = v5052 < 8;	// L8001
    int32_t v5054 = dsmask5;	// L8002
    int32_t v5055 = v5054 >> v5052;	// L8003
    int32_t v5056 = v5055 & 1;	// L8004
    bool v5057 = v5056 == 1;	// L8005
    bool v5058 = v5051 & v5053;	// L8006
    bool v5059 = v5058 & v5057;	// L8007
    if (v5059) {	// L8008
      int32_t v5060 = s25;	// L8009
      int v5061 = v5060;	// L8010
      drf_full5[v5061] = 0;	// L8011
    }
    half res5;
#pragma HLS dependence variable=res5 type=inter dependent=false	// L8013
    res5 = 0.000000;	// L8014
    int32_t v5063 = op5;	// L8015
    bool v5064 = v5063 == 0;	// L8016
    if (v5064) {	// L8017
      half v5065 = a5;	// L8018
      half v5066 = b5;	// L8019
      half v5067 = v5065 + v5066;	// L8020
      res5 = v5067;	// L8021
    } else {
      int32_t v5068 = op5;	// L8023
      bool v5069 = v5068 == 1;	// L8024
      if (v5069) {	// L8025
        half v5070 = a5;	// L8026
        half v5071 = b5;	// L8027
        half v5072 = v5070 - v5071;	// L8028
        res5 = v5072;	// L8029
      } else {
        int32_t v5073 = op5;	// L8031
        bool v5074 = v5073 == 2;	// L8032
        if (v5074) {	// L8033
          half v5075 = a5;	// L8034
          half v5076 = b5;	// L8035
          half v5077 = v5075 * v5076;	// L8036
          res5 = v5077;	// L8037
        } else {
          int32_t v5078 = op5;	// L8039
          bool v5079 = v5078 == 8;	// L8040
          if (v5079) {	// L8041
            half v5080 = a5;	// L8042
            half v5081 = b5;	// L8043
            bool v5082 = v5080 >= v5081;	// L8044
            if (v5082) {	// L8045
              res5 = 1.000000;	// L8046
            } else {
              res5 = -1.000000;	// L8048
            }
          } else {
            int32_t v5083 = op5;	// L8051
            bool v5084 = v5083 == 9;	// L8052
            if (v5084) {	// L8053
              half v5085 = a5;	// L8054
              half v5086 = b5;	// L8055
              bool v5087 = v5085 < v5086;	// L8056
              if (v5087) {	// L8057
                res5 = 1.000000;	// L8058
              } else {
                res5 = -1.000000;	// L8060
              }
            } else {
              half v5088 = a5;	// L8063
              res5 = v5088;	// L8064
            }
          }
        }
      }
    }
    int32_t v5089 = a_vld5;	// L8070
    int32_t res_vld5;	// L8071
    res_vld5 = v5089;	// L8072
    int32_t v5091 = op5;	// L8073
    bool v5092 = v5091 == 0;	// L8074
    bool v5093 = v5091 == 1;	// L8075
    bool v5094 = v5091 == 2;	// L8076
    bool v5095 = v5091 == 8;	// L8077
    bool v5096 = v5091 == 9;	// L8078
    bool v5097 = v5092 | v5093;	// L8079
    bool v5098 = v5097 | v5094;	// L8080
    bool v5099 = v5098 | v5095;	// L8081
    bool v5100 = v5099 | v5096;	// L8082
    if (v5100) {	// L8083
      int32_t v5101 = a_vld5;	// L8084
      int32_t v5102 = b_vld5;	// L8085
      int64_t v5103 = v5101;	// L8086
      int64_t v5104 = v5102;	// L8087
      int64_t v5105 = v5103 * v5104;	// L8088
      int32_t v5106 = v5105;	// L8089
      res_vld5 = v5106;	// L8090
    }
    int32_t v5107 = grant5;	// L8092
    bool v5108 = v5107 == 0;	// L8093
    if (v5108) {	// L8094
      res_vld5 = 0;	// L8095
    }
    int32_t is_rtr5;	// L8097
    is_rtr5 = 0;	// L8098
    int32_t v5110 = op5;	// L8099
    bool v5111 = v5110 >= 4;	// L8100
    ap_int<33> v5112 = v5110;	// L8101
    bool v5113 = v5112 <= 7;	// L8102
    bool v5114 = v5111 & v5113;	// L8103
    if (v5114) {	// L8104
      is_rtr5 = 1;	// L8105
    }
    l_S_k_6_k11: for (int k11 = 0; k11 < 4; k11++) {	// L8107
      uint8_t v5116 = sb_v5[(k11 + 1)];	// L8108
      sb_v5[k11] = v5116;	// L8109
      uint8_t v5117 = sb_dst5[(k11 + 1)];	// L8110
      sb_dst5[k11] = v5117;	// L8111
      uint8_t v5118 = sb_cmp5[(k11 + 1)];	// L8112
      sb_cmp5[k11] = v5118;	// L8113
      uint8_t v5119 = sb_rtr5[(k11 + 1)];	// L8114
      sb_rtr5[k11] = v5119;	// L8115
      uint8_t v5120 = sb_inj5[(k11 + 1)];	// L8116
      sb_inj5[k11] = v5120;	// L8117
      uint8_t v5121 = sb_dir5[(k11 + 1)];	// L8118
      sb_dir5[k11] = v5121;	// L8119
      uint8_t v5122 = sb_id5[(k11 + 1)];	// L8120
      sb_id5[k11] = v5122;	// L8121
      uint8_t v5123 = sb_rvld5[(k11 + 1)];	// L8122
      sb_rvld5[k11] = v5123;	// L8123
      uint8_t v5124 = sb_ix5[(k11 + 1)];	// L8124
      sb_ix5[k11] = v5124;	// L8125
    }
    sb_v5[4] = 0;	// L8127
    int32_t v5125 = grant5;	// L8128
    bool v5126 = v5125 == 1;	// L8129
    if (v5126) {	// L8130
      half v5127 = res5;	// L8131
      int8_t v5128 = resq_wr5;	// L8132
      int v5129 = v5128;	// L8133
      resq5[v5129] = v5127;	// L8134
      int32_t cq5;	// L8135
      cq5 = 0;	// L8136
      int32_t v5131 = op5;	// L8137
      bool v5132 = v5131 == 8;	// L8138
      if (v5132) {	// L8139
        half v5133 = a5;	// L8140
        half v5134 = b5;	// L8141
        bool v5135 = v5133 >= v5134;	// L8142
        if (v5135) {	// L8143
          cq5 = 1;	// L8144
        }
      }
      int32_t v5136 = op5;	// L8147
      bool v5137 = v5136 == 9;	// L8148
      if (v5137) {	// L8149
        half v5138 = a5;	// L8150
        half v5139 = b5;	// L8151
        bool v5140 = v5138 < v5139;	// L8152
        if (v5140) {	// L8153
          cq5 = 1;	// L8154
        }
      }
      int32_t v5141 = cq5;	// L8157
      uint8_t v5142 = v5141;	// L8158
      int8_t v5143 = resq_wr5;	// L8159
      int v5144 = v5143;	// L8160
      cmpq5[v5144] = v5142;	// L8161
      sb_v5[4] = 1;	// L8162
      int32_t v5145 = dst5;	// L8163
      uint8_t v5146 = v5145;	// L8164
      sb_dst5[4] = v5146;	// L8165
      int8_t v5147 = resq_wr5;	// L8166
      sb_ix5[4] = v5147;	// L8167
      sb_cmp5[4] = 0;	// L8168
      int32_t v5148 = op5;	// L8169
      bool v5149 = v5148 == 8;	// L8170
      bool v5150 = v5148 == 9;	// L8171
      bool v5151 = v5149 | v5150;	// L8172
      if (v5151) {	// L8173
        sb_cmp5[4] = 1;	// L8174
      }
      int32_t v5152 = is_rtr5;	// L8176
      int32_t rtrf5;	// L8177
      rtrf5 = v5152;	// L8178
      int32_t v5154 = is_cond5;	// L8179
      bool v5155 = v5154 == 1;	// L8180
      if (v5155) {	// L8181
        rtrf5 = 1;	// L8182
      }
      int32_t v5156 = rtrf5;	// L8184
      uint8_t v5157 = v5156;	// L8185
      sb_rtr5[4] = v5157;	// L8186
      int32_t v5158 = is_rtr5;	// L8187
      int32_t inj5;	// L8188
      inj5 = v5158;	// L8189
      int32_t v5160 = is_cond5;	// L8190
      bool v5161 = v5160 == 1;	// L8191
      int8_t v5162 = condition_reg5;	// L8192
      int32_t v5163 = v5162;	// L8193
      bool v5164 = v5163 == 1;	// L8194
      bool v5165 = v5161 & v5164;	// L8195
      if (v5165) {	// L8196
        inj5 = 1;	// L8197
      }
      int32_t v5166 = inj5;	// L8199
      uint8_t v5167 = v5166;	// L8200
      sb_inj5[4] = v5167;	// L8201
      int32_t v5168 = op5;	// L8202
      int32_t v5169 = v5168 & 3;	// L8203
      uint8_t v5170 = v5169;	// L8204
      sb_dir5[4] = v5170;	// L8205
      int32_t v5171 = s25;	// L8206
      uint8_t v5172 = v5171;	// L8207
      sb_id5[4] = v5172;	// L8208
      int32_t v5173 = res_vld5;	// L8209
      uint8_t v5174 = v5173;	// L8210
      sb_rvld5[4] = v5174;	// L8211
      int8_t v5175 = resq_wr5;	// L8212
      ap_int<33> v5176 = v5175;	// L8213
      ap_int<33> v5177 = v5176 + 1;	// L8214
      ap_int<33> v5178 = v5177 & 7;	// L8215
      uint8_t v5179 = v5178;	// L8216
      resq_wr5 = v5179;	// L8217
    }
    ap_int<17> v5180 = tx_n5;	// L8219
    txn_r5 = v5180;	// L8220
    ap_int<17> v5181 = tx_s5;	// L8221
    txs_r5 = v5181;	// L8222
    ap_int<17> v5182 = tx_w5;	// L8223
    txw_r5 = v5182;	// L8224
    ap_int<17> v5183 = tx_e5;	// L8225
    txe_r5 = v5183;	// L8226
    int32_t v5184 = crv_vld5;	// L8227
    bool v5185 = v5184 == 1;	// L8228
    if (v5185) {	// L8229
      int32_t v5186 = crv_mode5;	// L8230
      bool v5187 = v5186 == 1;	// L8231
      if (v5187) {	// L8232
        int32_t v5188 = crv_addr5;	// L8233
        int32_t v5189 = v5188 >> 3;	// L8234
        int32_t v5190 = v5189 & 1;	// L8235
        bool v5191 = v5190 == 1;	// L8236
        if (v5191) {	// L8237
          int32_t v5192 = crv_raw5;	// L8238
          int32_t v5193 = crv_addr5;	// L8239
          int32_t v5194 = v5193 & 7;	// L8240
          int v5195 = v5194;	// L8241
          irf5[v5195] = v5192;	// L8242
        } else {
          int32_t v5196 = crv_addr5;	// L8244
          bool v5197 = v5196 == 0;	// L8245
          if (v5197) {	// L8246
            int32_t v5198 = crv_raw5;	// L8247
            int32_t v5199 = v5198 & 255;	// L8248
            dsmask5 = v5199;	// L8249
            int32_t v5200 = crv_raw5;	// L8250
            int32_t v5201 = v5200 >> 8;	// L8251
            int32_t v5202 = v5201 & 7;	// L8252
            cfg_isz5 = v5202;	// L8253
            int32_t v5203 = crv_raw5;	// L8254
            int32_t v5204 = v5203 >> 15;	// L8255
            int32_t v5205 = v5204 & 1;	// L8256
            bool v5206 = v5205 == 1;	// L8257
            if (v5206) {	// L8258
              fetch_en5 = 1;	// L8259
              instr_cnt5 = 0;	// L8260
              iter_cnt5 = 0;	// L8261
            }
          } else {
            int32_t v5207 = crv_addr5;	// L8264
            bool v5208 = v5207 == 1;	// L8265
            if (v5208) {	// L8266
              int32_t v5209 = crv_raw5;	// L8267
              int32_t v5210 = v5209 & 255;	// L8268
              cfg_itsz5 = v5210;	// L8269
            }
          }
        }
      } else {
        int32_t v5211 = crv_addr5;	// L8274
        bool v5212 = v5211 < 8;	// L8275
        int32_t v5213 = dsmask5;	// L8276
        int32_t v5214 = v5213 >> v5211;	// L8277
        int32_t v5215 = v5214 & 1;	// L8278
        bool v5216 = v5215 == 1;	// L8279
        bool v5217 = v5212 & v5216;	// L8280
        if (v5217) {	// L8281
          int32_t v5218 = crv_addr5;	// L8282
          int v5219 = v5218;	// L8283
          int32_t v5220 = drf_full5[v5219];	// L8284
          bool v5221 = v5220 == 0;	// L8285
          if (v5221) {	// L8286
            half v5222 = crv_data5;	// L8287
            int32_t v5223 = crv_addr5;	// L8288
            int v5224 = v5223;	// L8289
            drf5[v5224] = v5222;	// L8290
            int32_t v5225 = crv_addr5;	// L8291
            int v5226 = v5225;	// L8292
            drf_full5[v5226] = 1;	// L8293
          }
        } else {
          half v5227 = crv_data5;	// L8296
          int32_t v5228 = crv_addr5;	// L8297
          int v5229 = v5228;	// L8298
          drf5[v5229] = v5227;	// L8299
        }
      }
    }
    ap_int<17> v5230 = txe_r5;	// L8303
    bool v5231;
    ap_int<17> v5231_tmp = v5230;
    v5231 = v5231_tmp[0];	// L8304
    int32_t v5232 = v5231;	// L8305
    bool v5233 = v5232 == 1;	// L8306
    if (v5233) {	// L8307
      ap_int<17> v5234 = txe_r5;	// L8308
      v4387.write(v5234);	// L8309
    }
    ap_int<17> v5235 = txw_r5;	// L8311
    bool v5236;
    ap_int<17> v5236_tmp = v5235;
    v5236 = v5236_tmp[0];	// L8312
    int32_t v5237 = v5236;	// L8313
    bool v5238 = v5237 == 1;	// L8314
    if (v5238) {	// L8315
      ap_int<17> v5239 = txw_r5;	// L8316
      v4388.write(v5239);	// L8317
    }
    ap_int<17> v5240 = txs_r5;	// L8319
    bool v5241;
    ap_int<17> v5241_tmp = v5240;
    v5241 = v5241_tmp[0];	// L8320
    int32_t v5242 = v5241;	// L8321
    bool v5243 = v5242 == 1;	// L8322
    if (v5243) {	// L8323
      ap_int<17> v5244 = txs_r5;	// L8324
      v4389.write(v5244);	// L8325
    }
    ap_int<17> v5245 = txn_r5;	// L8327
    bool v5246;
    ap_int<17> v5246_tmp = v5245;
    v5246 = v5246_tmp[0];	// L8328
    int32_t v5247 = v5246;	// L8329
    bool v5248 = v5247 == 1;	// L8330
    if (v5248) {	// L8331
      ap_int<17> v5249 = txn_r5;	// L8332
      v4390.write(v5249);	// L8333
    }
  }
}

void node_1_2(
  hls::stream< ap_uint<26> >& v5250,
  hls::stream< ap_uint<26> >& v5251,
  hls::stream< ap_uint<26> >& v5252,
  hls::stream< ap_uint<26> >& v5253,
  hls::stream< ap_uint<26> >& v5254,
  hls::stream< ap_uint<26> >& v5255,
  hls::stream< ap_uint<26> >& v5256,
  hls::stream< ap_uint<26> >& v5257,
  hls::stream< ap_uint<17> >& v5258,
  hls::stream< ap_uint<17> >& v5259,
  hls::stream< ap_uint<17> >& v5260,
  hls::stream< ap_uint<17> >& v5261,
  hls::stream< ap_uint<17> >& v5262,
  hls::stream< ap_uint<17> >& v5263,
  hls::stream< ap_uint<17> >& v5264,
  hls::stream< ap_uint<17> >& v5265
) {	// L8338
  int32_t irf6[8];	// L8371
  #pragma HLS array_partition variable=irf6 complete dim=1

  for (int v5267 = 0; v5267 < 8; v5267++) {	// L8372
    irf6[v5267] = 0;	// L8372
  }
  half drf6[8];	// L8373
  #pragma HLS array_partition variable=drf6 complete dim=1

  for (int v5269 = 0; v5269 < 8; v5269++) {	// L8374
    drf6[v5269] = 0.000000;	// L8374
  }
  int32_t drf_full6[8];	// L8375
  #pragma HLS array_partition variable=drf_full6 complete dim=1

  for (int v5271 = 0; v5271 < 8; v5271++) {	// L8376
    drf_full6[v5271] = 0;	// L8376
  }
  int32_t dsmask6;	// L8377
  dsmask6 = 0;	// L8378
  int32_t crv_vld6;	// L8379
  crv_vld6 = 0;	// L8380
  half crv_data6;	// L8381
  crv_data6 = 0.000000;	// L8382
  int32_t crv_addr6;	// L8383
  crv_addr6 = 0;	// L8384
  int32_t crv_mode6;	// L8385
  crv_mode6 = 0;	// L8386
  int32_t crv_raw6;	// L8387
  crv_raw6 = 0;	// L8388
  int32_t csd_vld6;	// L8389
  csd_vld6 = 0;	// L8390
  ap_uint<26> csd_pkt6;	// L8391
  csd_pkt6 = 0;	// L8392
  int32_t csd_dir6;	// L8393
  csd_dir6 = 0;	// L8394
  int32_t row_id6;	// L8395
  row_id6 = 1;	// L8396
  int32_t col_id6;	// L8397
  col_id6 = 2;	// L8398
  ap_uint<17> txn_r6;	// L8399
  txn_r6 = 0;	// L8400
  ap_uint<17> txs_r6;	// L8401
  txs_r6 = 0;	// L8402
  ap_uint<17> txw_r6;	// L8403
  txw_r6 = 0;	// L8404
  ap_uint<17> txe_r6;	// L8405
  txe_r6 = 0;	// L8406
  half hold_v6[4][2];	// L8407
  #pragma HLS array_partition variable=hold_v6 complete dim=1
  #pragma HLS array_partition variable=hold_v6 complete dim=2

  for (int v5288 = 0; v5288 < 4; v5288++) {	// L8408
    for (int v5289 = 0; v5289 < 2; v5289++) {	// L8408
      hold_v6[v5288][v5289] = 0.000000;	// L8408
    }
  }
  uint8_t hold_cnt6[4];	// L8409
  #pragma HLS array_partition variable=hold_cnt6 complete dim=1

  for (int v5291 = 0; v5291 < 4; v5291++) {	// L8410
    hold_cnt6[v5291] = 0;	// L8410
  }
  int32_t crv_ever6;	// L8411
  crv_ever6 = 0;	// L8412
  int32_t fe_ever6;	// L8413
  fe_ever6 = 0;	// L8414
  ap_uint<26> rbuf6[4][2];	// L8415
  #pragma HLS array_partition variable=rbuf6 complete dim=1
  #pragma HLS array_partition variable=rbuf6 complete dim=2

  for (int v5295 = 0; v5295 < 4; v5295++) {	// L8416
    for (int v5296 = 0; v5296 < 2; v5296++) {	// L8416
      rbuf6[v5295][v5296] = 0;	// L8416
    }
  }
  uint8_t rbcnt6[4];	// L8417
  #pragma HLS array_partition variable=rbcnt6 complete dim=1

  for (int v5298 = 0; v5298 < 4; v5298++) {	// L8418
    rbcnt6[v5298] = 0;	// L8418
  }
  int32_t cfg_isz6;	// L8419
  cfg_isz6 = 0;	// L8420
  int32_t cfg_itsz6;	// L8421
  cfg_itsz6 = 0;	// L8422
  uint8_t fetch_en6;	// L8423
  fetch_en6 = 0;	// L8424
  uint8_t instr_cnt6;	// L8425
  instr_cnt6 = 0;	// L8426
  uint8_t iter_cnt6;	// L8427
  iter_cnt6 = 0;	// L8428
  uint8_t condition_reg6;	// L8429
  condition_reg6 = 0;	// L8430
  uint8_t sb_v6[5];	// L8431
  #pragma HLS array_partition variable=sb_v6 complete dim=1

  for (int v5306 = 0; v5306 < 5; v5306++) {	// L8432
    sb_v6[v5306] = 0;	// L8432
  }
  uint8_t sb_dst6[5];	// L8433
  #pragma HLS array_partition variable=sb_dst6 complete dim=1

  for (int v5308 = 0; v5308 < 5; v5308++) {	// L8434
    sb_dst6[v5308] = 0;	// L8434
  }
  uint8_t sb_cmp6[5];	// L8435
  #pragma HLS array_partition variable=sb_cmp6 complete dim=1

  for (int v5310 = 0; v5310 < 5; v5310++) {	// L8436
    sb_cmp6[v5310] = 0;	// L8436
  }
  uint8_t sb_rtr6[5];	// L8437
  #pragma HLS array_partition variable=sb_rtr6 complete dim=1

  for (int v5312 = 0; v5312 < 5; v5312++) {	// L8438
    sb_rtr6[v5312] = 0;	// L8438
  }
  uint8_t sb_inj6[5];	// L8439
  #pragma HLS array_partition variable=sb_inj6 complete dim=1

  for (int v5314 = 0; v5314 < 5; v5314++) {	// L8440
    sb_inj6[v5314] = 0;	// L8440
  }
  uint8_t sb_dir6[5];	// L8441
  #pragma HLS array_partition variable=sb_dir6 complete dim=1

  for (int v5316 = 0; v5316 < 5; v5316++) {	// L8442
    sb_dir6[v5316] = 0;	// L8442
  }
  uint8_t sb_id6[5];	// L8443
  #pragma HLS array_partition variable=sb_id6 complete dim=1

  for (int v5318 = 0; v5318 < 5; v5318++) {	// L8444
    sb_id6[v5318] = 0;	// L8444
  }
  uint8_t sb_rvld6[5];	// L8445
  #pragma HLS array_partition variable=sb_rvld6 complete dim=1

  for (int v5320 = 0; v5320 < 5; v5320++) {	// L8446
    sb_rvld6[v5320] = 0;	// L8446
  }
  uint8_t sb_ix6[5];	// L8447
  #pragma HLS array_partition variable=sb_ix6 complete dim=1

  for (int v5322 = 0; v5322 < 5; v5322++) {	// L8448
    sb_ix6[v5322] = 0;	// L8448
  }
  half resq6[8];	// L8449
  #pragma HLS array_partition variable=resq6 complete dim=1
#pragma HLS dependence variable=resq6 type=inter dependent=false

  for (int v5324 = 0; v5324 < 8; v5324++) {	// L8450
    resq6[v5324] = 0.000000;	// L8450
  }
  uint8_t cmpq6[8];	// L8451
  #pragma HLS array_partition variable=cmpq6 complete dim=1
#pragma HLS dependence variable=cmpq6 type=inter dependent=false

  for (int v5326 = 0; v5326 < 8; v5326++) {	// L8452
    cmpq6[v5326] = 0;	// L8452
  }
  uint8_t resq_wr6;	// L8453
  resq_wr6 = 0;	// L8454
  l_S_t_0_t6: for (int t6 = 0; t6 < 374; t6++) {	// L8455
  #pragma HLS pipeline II=1
    ap_uint<26> p_w6;	// L8456
    p_w6 = 0;	// L8457
    ap_uint<26> p_e6;	// L8458
    p_e6 = 0;	// L8459
    ap_uint<26> p_n6;	// L8460
    p_n6 = 0;	// L8461
    ap_uint<26> p_s6;	// L8462
    p_s6 = 0;	// L8463
    uint8_t v5333 = rbcnt6[0];	// L8464
    int32_t v5334 = v5333;	// L8465
    bool v5335 = v5334 < 2;	// L8466
    if (v5335) {	// L8467
      ap_uint<26> v5336;
      bool v5337 = v5250.read_nb(v5336);
	// L8468
      ap_uint<26> gw6;	// L8469
      gw6 = v5336;	// L8470
      bool okw6;	// L8471
      okw6 = v5337;	// L8472
      bool v5340 = okw6;	// L8473
      if (v5340) {	// L8474
        ap_int<26> v5341 = gw6;	// L8475
        p_w6 = v5341;	// L8476
      }
    }
    uint8_t v5342 = rbcnt6[1];	// L8479
    int32_t v5343 = v5342;	// L8480
    bool v5344 = v5343 < 2;	// L8481
    if (v5344) {	// L8482
      ap_uint<26> v5345;
      bool v5346 = v5251.read_nb(v5345);
	// L8483
      ap_uint<26> ge6;	// L8484
      ge6 = v5345;	// L8485
      bool oke6;	// L8486
      oke6 = v5346;	// L8487
      bool v5349 = oke6;	// L8488
      if (v5349) {	// L8489
        ap_int<26> v5350 = ge6;	// L8490
        p_e6 = v5350;	// L8491
      }
    }
    uint8_t v5351 = rbcnt6[2];	// L8494
    int32_t v5352 = v5351;	// L8495
    bool v5353 = v5352 < 2;	// L8496
    if (v5353) {	// L8497
      ap_uint<26> v5354;
      bool v5355 = v5252.read_nb(v5354);
	// L8498
      ap_uint<26> gn6;	// L8499
      gn6 = v5354;	// L8500
      bool okn6;	// L8501
      okn6 = v5355;	// L8502
      bool v5358 = okn6;	// L8503
      if (v5358) {	// L8504
        ap_int<26> v5359 = gn6;	// L8505
        p_n6 = v5359;	// L8506
      }
    }
    uint8_t v5360 = rbcnt6[3];	// L8509
    int32_t v5361 = v5360;	// L8510
    bool v5362 = v5361 < 2;	// L8511
    if (v5362) {	// L8512
      ap_uint<26> v5363;
      bool v5364 = v5253.read_nb(v5363);
	// L8513
      ap_uint<26> gs6;	// L8514
      gs6 = v5363;	// L8515
      bool oks6;	// L8516
      oks6 = v5364;	// L8517
      bool v5367 = oks6;	// L8518
      if (v5367) {	// L8519
        ap_int<26> v5368 = gs6;	// L8520
        p_s6 = v5368;	// L8521
      }
    }
    ap_uint<26> fin6[4];	// L8524
    for (int v5370 = 0; v5370 < 4; v5370++) {	// L8525
      fin6[v5370] = 0;	// L8525
    }
    ap_int<26> v5371 = p_w6;	// L8526
    fin6[0] = v5371;	// L8527
    ap_int<26> v5372 = p_e6;	// L8528
    fin6[1] = v5372;	// L8529
    ap_int<26> v5373 = p_n6;	// L8530
    fin6[2] = v5373;	// L8531
    ap_int<26> v5374 = p_s6;	// L8532
    fin6[3] = v5374;	// L8533
    l_S_d_0_d24: for (int d24 = 0; d24 < 4; d24++) {	// L8534
      ap_uint<26> v5376 = fin6[d24];	// L8535
      bool v5377;
      ap_int<26> v5377_tmp = v5376;
      v5377 = v5377_tmp[25];	// L8536
      int32_t v5378 = v5377;	// L8537
      bool v5379 = v5378 == 1;	// L8538
      uint8_t v5380 = rbcnt6[d24];	// L8539
      int32_t v5381 = v5380;	// L8540
      bool v5382 = v5381 < 2;	// L8541
      bool v5383 = v5379 & v5382;	// L8542
      if (v5383) {	// L8543
        ap_uint<26> v5384 = fin6[d24];	// L8544
        uint8_t v5385 = rbcnt6[d24];	// L8545
        int v5386 = v5385;	// L8546
        rbuf6[d24][v5386] = v5384;	// L8547
        uint8_t v5387 = rbcnt6[d24];	// L8548
        ap_int<33> v5388 = v5387;	// L8549
        ap_int<33> v5389 = v5388 + 1;	// L8550
        uint8_t v5390 = v5389;	// L8551
        rbcnt6[d24] = v5390;	// L8552
      }
    }
    ap_uint<26> hd6[4];	// L8555
    for (int v5392 = 0; v5392 < 4; v5392++) {	// L8556
      hd6[v5392] = 0;	// L8556
    }
    int32_t hvld6[4];	// L8557
    for (int v5394 = 0; v5394 < 4; v5394++) {	// L8558
      hvld6[v5394] = 0;	// L8558
    }
    int32_t hit6[4];	// L8559
    for (int v5396 = 0; v5396 < 4; v5396++) {	// L8560
      hit6[v5396] = 0;	// L8560
    }
    int32_t axis6[4];	// L8561
    for (int v5398 = 0; v5398 < 4; v5398++) {	// L8562
      axis6[v5398] = 0;	// L8562
    }
    int32_t v5399 = col_id6;	// L8563
    axis6[0] = v5399;	// L8564
    int32_t v5400 = col_id6;	// L8565
    axis6[1] = v5400;	// L8566
    int32_t v5401 = row_id6;	// L8567
    axis6[2] = v5401;	// L8568
    int32_t v5402 = row_id6;	// L8569
    axis6[3] = v5402;	// L8570
    l_S_d_1_d25: for (int d25 = 0; d25 < 4; d25++) {	// L8571
      uint8_t v5404 = rbcnt6[d25];	// L8572
      int32_t v5405 = v5404;	// L8573
      bool v5406 = v5405 > 0;	// L8574
      if (v5406) {	// L8575
        ap_uint<26> v5407 = rbuf6[d25][0];	// L8576
        hd6[d25] = v5407;	// L8577
        hvld6[d25] = 1;	// L8578
        ap_uint<26> v5408 = hd6[d25];	// L8579
        ap_int<4> v5409;
        ap_int<26> v5409_tmp = v5408;
        v5409 = v5409_tmp(24, 21);	// L8580
        int32_t v5410 = axis6[d25];	// L8581
        int32_t v5411 = v5409;	// L8582
        bool v5412 = v5411 == v5410;	// L8583
        if (v5412) {	// L8584
          hit6[d25] = 1;	// L8585
        }
      }
    }
    ap_uint<26> o_crv6;	// L8589
    o_crv6 = 0;	// L8590
    int32_t crv_in6;	// L8591
    crv_in6 = -1;	// L8592
    int32_t v5415 = hit6[3];	// L8593
    bool v5416 = v5415 == 1;	// L8594
    if (v5416) {	// L8595
      ap_uint<26> v5417 = hd6[3];	// L8596
      o_crv6 = v5417;	// L8597
      crv_in6 = 3;	// L8598
    } else {
      int32_t v5418 = hit6[2];	// L8600
      bool v5419 = v5418 == 1;	// L8601
      if (v5419) {	// L8602
        ap_uint<26> v5420 = hd6[2];	// L8603
        o_crv6 = v5420;	// L8604
        crv_in6 = 2;	// L8605
      } else {
        int32_t v5421 = hit6[1];	// L8607
        bool v5422 = v5421 == 1;	// L8608
        if (v5422) {	// L8609
          ap_uint<26> v5423 = hd6[1];	// L8610
          o_crv6 = v5423;	// L8611
          crv_in6 = 1;	// L8612
        } else {
          int32_t v5424 = hit6[0];	// L8614
          bool v5425 = v5424 == 1;	// L8615
          if (v5425) {	// L8616
            ap_uint<26> v5426 = hd6[0];	// L8617
            o_crv6 = v5426;	// L8618
            crv_in6 = 0;	// L8619
          }
        }
      }
    }
    int32_t pop6[4];	// L8624
    for (int v5428 = 0; v5428 < 4; v5428++) {	// L8625
      pop6[v5428] = 0;	// L8625
    }
    int32_t inj_done6;	// L8626
    inj_done6 = 0;	// L8627
    int32_t idir6;	// L8628
    idir6 = -1;	// L8629
    ap_int<26> v5431 = csd_pkt6;	// L8630
    bool v5432;
    ap_int<26> v5432_tmp = v5431;
    v5432 = v5432_tmp[25];	// L8631
    int32_t v5433 = v5432;	// L8632
    bool v5434 = v5433 == 1;	// L8633
    if (v5434) {	// L8634
      int32_t v5435 = csd_dir6;	// L8635
      ap_int<33> v5436 = v5435;	// L8636
      ap_int<33> v5437 = 3 - v5436;	// L8637
      int32_t v5438 = v5437;	// L8638
      idir6 = v5438;	// L8639
    }
    int32_t v5439 = idir6;	// L8641
    bool v5440 = v5439 == 0;	// L8642
    if (v5440) {	// L8643
      ap_int<26> v5441 = csd_pkt6;	// L8644
      bool v5442 = v5254.write_nb(v5441);
	// L8645
      if (v5442) {	// L8646
        inj_done6 = 1;	// L8647
      }
    } else {
      int32_t v5443 = hvld6[0];	// L8650
      bool v5444 = v5443 == 1;	// L8651
      int32_t v5445 = hit6[0];	// L8652
      bool v5446 = v5445 == 0;	// L8653
      bool v5447 = v5444 & v5446;	// L8654
      if (v5447) {	// L8655
        ap_uint<26> v5448 = hd6[0];	// L8656
        bool v5449 = v5254.write_nb(v5448);
	// L8657
        if (v5449) {	// L8658
          pop6[0] = 1;	// L8659
        }
      }
    }
    int32_t v5450 = idir6;	// L8663
    bool v5451 = v5450 == 1;	// L8664
    if (v5451) {	// L8665
      ap_int<26> v5452 = csd_pkt6;	// L8666
      bool v5453 = v5255.write_nb(v5452);
	// L8667
      if (v5453) {	// L8668
        inj_done6 = 1;	// L8669
      }
    } else {
      int32_t v5454 = hvld6[1];	// L8672
      bool v5455 = v5454 == 1;	// L8673
      int32_t v5456 = hit6[1];	// L8674
      bool v5457 = v5456 == 0;	// L8675
      bool v5458 = v5455 & v5457;	// L8676
      if (v5458) {	// L8677
        ap_uint<26> v5459 = hd6[1];	// L8678
        bool v5460 = v5255.write_nb(v5459);
	// L8679
        if (v5460) {	// L8680
          pop6[1] = 1;	// L8681
        }
      }
    }
    int32_t v5461 = idir6;	// L8685
    bool v5462 = v5461 == 2;	// L8686
    if (v5462) {	// L8687
      ap_int<26> v5463 = csd_pkt6;	// L8688
      bool v5464 = v5256.write_nb(v5463);
	// L8689
      if (v5464) {	// L8690
        inj_done6 = 1;	// L8691
      }
    } else {
      int32_t v5465 = hvld6[2];	// L8694
      bool v5466 = v5465 == 1;	// L8695
      int32_t v5467 = hit6[2];	// L8696
      bool v5468 = v5467 == 0;	// L8697
      bool v5469 = v5466 & v5468;	// L8698
      if (v5469) {	// L8699
        ap_uint<26> v5470 = hd6[2];	// L8700
        bool v5471 = v5256.write_nb(v5470);
	// L8701
        if (v5471) {	// L8702
          pop6[2] = 1;	// L8703
        }
      }
    }
    int32_t v5472 = idir6;	// L8707
    bool v5473 = v5472 == 3;	// L8708
    if (v5473) {	// L8709
      ap_int<26> v5474 = csd_pkt6;	// L8710
      bool v5475 = v5257.write_nb(v5474);
	// L8711
      if (v5475) {	// L8712
        inj_done6 = 1;	// L8713
      }
    } else {
      int32_t v5476 = hvld6[3];	// L8716
      bool v5477 = v5476 == 1;	// L8717
      int32_t v5478 = hit6[3];	// L8718
      bool v5479 = v5478 == 0;	// L8719
      bool v5480 = v5477 & v5479;	// L8720
      if (v5480) {	// L8721
        ap_uint<26> v5481 = hd6[3];	// L8722
        bool v5482 = v5257.write_nb(v5481);
	// L8723
        if (v5482) {	// L8724
          pop6[3] = 1;	// L8725
        }
      }
    }
    int32_t v5483 = crv_in6;	// L8729
    bool v5484 = v5483 >= 0;	// L8730
    if (v5484) {	// L8731
      int32_t v5485 = crv_in6;	// L8732
      int v5486 = v5485;	// L8733
      pop6[v5486] = 1;	// L8734
    }
    l_S_d_2_d26: for (int d26 = 0; d26 < 4; d26++) {	// L8736
      int32_t v5488 = pop6[d26];	// L8737
      bool v5489 = v5488 == 1;	// L8738
      if (v5489) {	// L8739
        l_S_sft_2_sft6: for (int sft6 = 0; sft6 < 1; sft6++) {	// L8740
          ap_uint<26> v5491 = rbuf6[d26][(sft6 + 1)];	// L8741
          rbuf6[d26][sft6] = v5491;	// L8742
        }
        uint8_t v5492 = rbcnt6[d26];	// L8744
        ap_int<33> v5493 = v5492;	// L8745
        ap_int<33> v5494 = v5493 - 1;	// L8746
        uint8_t v5495 = v5494;	// L8747
        rbcnt6[d26] = v5495;	// L8748
      }
    }
    int32_t v5496 = inj_done6;	// L8751
    bool v5497 = v5496 == 1;	// L8752
    if (v5497) {	// L8753
      csd_pkt6 = 0;	// L8754
    }
    ap_int<26> v5498 = o_crv6;	// L8756
    bool v5499;
    ap_int<26> v5499_tmp = v5498;
    v5499 = v5499_tmp[25];	// L8757
    int32_t v5500 = v5499;	// L8758
    crv_vld6 = v5500;	// L8759
    int32_t v5501 = crv_vld6;	// L8760
    bool v5502 = v5501 == 1;	// L8761
    if (v5502) {	// L8762
      crv_ever6 = 1;	// L8763
    }
    ap_int<26> v5503 = o_crv6;	// L8765
    int16_t v5504;
    ap_int<26> v5504_tmp = v5503;
    v5504 = v5504_tmp(15, 0);	// L8766
    half v5505;
    union { uint16_t from; half to;} _converter_v5504_to_v5505 = {};
    _converter_v5504_to_v5505.from = v5504;
    v5505 = _converter_v5504_to_v5505.to;	// L8767
    crv_data6 = v5505;	// L8768
    ap_int<26> v5506 = o_crv6;	// L8769
    ap_int<4> v5507;
    ap_int<26> v5507_tmp = v5506;
    v5507 = v5507_tmp(19, 16);	// L8770
    int32_t v5508 = v5507;	// L8771
    crv_addr6 = v5508;	// L8772
    ap_int<26> v5509 = o_crv6;	// L8773
    bool v5510;
    ap_int<26> v5510_tmp = v5509;
    v5510 = v5510_tmp[20];	// L8774
    int32_t v5511 = v5510;	// L8775
    crv_mode6 = v5511;	// L8776
    ap_int<26> v5512 = o_crv6;	// L8777
    int16_t v5513;
    ap_int<26> v5513_tmp = v5512;
    v5513 = v5513_tmp(15, 0);	// L8778
    int32_t v5514 = v5513;	// L8779
    crv_raw6 = v5514;	// L8780
    half rxv6[4];	// L8781
    for (int v5516 = 0; v5516 < 4; v5516++) {	// L8782
      rxv6[v5516] = 0.000000;	// L8782
    }
    int32_t rxvld6[4];	// L8783
    for (int v5518 = 0; v5518 < 4; v5518++) {	// L8784
      rxvld6[v5518] = 0;	// L8784
    }
    uint8_t v5519 = hold_cnt6[0];	// L8785
    int32_t v5520 = v5519;	// L8786
    bool v5521 = v5520 < 2;	// L8787
    if (v5521) {	// L8788
      ap_uint<17> v5522;
      bool v5523 = v5258.read_nb(v5522);
	// L8789
      ap_uint<17> sgn6;	// L8790
      sgn6 = v5522;	// L8791
      bool sqn6;	// L8792
      sqn6 = v5523;	// L8793
      bool v5526 = sqn6;	// L8794
      int32_t v5527 = v5526;	// L8795
      bool v5528 = v5527 == 1;	// L8796
      if (v5528) {	// L8797
        ap_int<17> v5529 = sgn6;	// L8798
        int16_t v5530;
        ap_int<17> v5530_tmp = v5529;
        v5530 = v5530_tmp(16, 1);	// L8799
        half v5531;
        union { uint16_t from; half to;} _converter_v5530_to_v5531 = {};
        _converter_v5530_to_v5531.from = v5530;
        v5531 = _converter_v5530_to_v5531.to;	// L8800
        rxv6[0] = v5531;	// L8801
        rxvld6[0] = 1;	// L8802
      }
    }
    uint8_t v5532 = hold_cnt6[1];	// L8805
    int32_t v5533 = v5532;	// L8806
    bool v5534 = v5533 < 2;	// L8807
    if (v5534) {	// L8808
      ap_uint<17> v5535;
      bool v5536 = v5259.read_nb(v5535);
	// L8809
      ap_uint<17> sgs6;	// L8810
      sgs6 = v5535;	// L8811
      bool sqs6;	// L8812
      sqs6 = v5536;	// L8813
      bool v5539 = sqs6;	// L8814
      int32_t v5540 = v5539;	// L8815
      bool v5541 = v5540 == 1;	// L8816
      if (v5541) {	// L8817
        ap_int<17> v5542 = sgs6;	// L8818
        int16_t v5543;
        ap_int<17> v5543_tmp = v5542;
        v5543 = v5543_tmp(16, 1);	// L8819
        half v5544;
        union { uint16_t from; half to;} _converter_v5543_to_v5544 = {};
        _converter_v5543_to_v5544.from = v5543;
        v5544 = _converter_v5543_to_v5544.to;	// L8820
        rxv6[1] = v5544;	// L8821
        rxvld6[1] = 1;	// L8822
      }
    }
    uint8_t v5545 = hold_cnt6[2];	// L8825
    int32_t v5546 = v5545;	// L8826
    bool v5547 = v5546 < 2;	// L8827
    if (v5547) {	// L8828
      ap_uint<17> v5548;
      bool v5549 = v5260.read_nb(v5548);
	// L8829
      ap_uint<17> sgw6;	// L8830
      sgw6 = v5548;	// L8831
      bool sqw6;	// L8832
      sqw6 = v5549;	// L8833
      bool v5552 = sqw6;	// L8834
      int32_t v5553 = v5552;	// L8835
      bool v5554 = v5553 == 1;	// L8836
      if (v5554) {	// L8837
        ap_int<17> v5555 = sgw6;	// L8838
        int16_t v5556;
        ap_int<17> v5556_tmp = v5555;
        v5556 = v5556_tmp(16, 1);	// L8839
        half v5557;
        union { uint16_t from; half to;} _converter_v5556_to_v5557 = {};
        _converter_v5556_to_v5557.from = v5556;
        v5557 = _converter_v5556_to_v5557.to;	// L8840
        rxv6[2] = v5557;	// L8841
        rxvld6[2] = 1;	// L8842
      }
    }
    uint8_t v5558 = hold_cnt6[3];	// L8845
    int32_t v5559 = v5558;	// L8846
    bool v5560 = v5559 < 2;	// L8847
    if (v5560) {	// L8848
      ap_uint<17> v5561;
      bool v5562 = v5261.read_nb(v5561);
	// L8849
      ap_uint<17> sge6;	// L8850
      sge6 = v5561;	// L8851
      bool sqe6;	// L8852
      sqe6 = v5562;	// L8853
      bool v5565 = sqe6;	// L8854
      int32_t v5566 = v5565;	// L8855
      bool v5567 = v5566 == 1;	// L8856
      if (v5567) {	// L8857
        ap_int<17> v5568 = sge6;	// L8858
        int16_t v5569;
        ap_int<17> v5569_tmp = v5568;
        v5569 = v5569_tmp(16, 1);	// L8859
        half v5570;
        union { uint16_t from; half to;} _converter_v5569_to_v5570 = {};
        _converter_v5569_to_v5570.from = v5569;
        v5570 = _converter_v5569_to_v5570.to;	// L8860
        rxv6[3] = v5570;	// L8861
        rxvld6[3] = 1;	// L8862
      }
    }
    l_S_d_4_d27: for (int d27 = 0; d27 < 4; d27++) {	// L8865
      int32_t v5572 = rxvld6[d27];	// L8866
      bool v5573 = v5572 == 1;	// L8867
      if (v5573) {	// L8868
        half v5574 = rxv6[d27];	// L8869
        uint8_t v5575 = hold_cnt6[d27];	// L8870
        int v5576 = v5575;	// L8871
        hold_v6[d27][v5576] = v5574;	// L8872
        uint8_t v5577 = hold_cnt6[d27];	// L8873
        ap_int<33> v5578 = v5577;	// L8874
        ap_int<33> v5579 = v5578 + 1;	// L8875
        uint8_t v5580 = v5579;	// L8876
        hold_cnt6[d27] = v5580;	// L8877
      }
    }
    ap_uint<17> tx_n6;	// L8880
    tx_n6 = 0;	// L8881
    ap_uint<17> tx_s6;	// L8882
    tx_s6 = 0;	// L8883
    ap_uint<17> tx_w6;	// L8884
    tx_w6 = 0;	// L8885
    ap_uint<17> tx_e6;	// L8886
    tx_e6 = 0;	// L8887
    uint8_t v5585 = sb_v6[0];	// L8888
    int32_t v5586 = v5585;	// L8889
    bool v5587 = v5586 == 1;	// L8890
    if (v5587) {	// L8891
      uint8_t v5588 = sb_ix6[0];	// L8892
      int v5589 = v5588;	// L8893
      half v5590 = resq6[v5589];	// L8894
      half wb6;
#pragma HLS dependence variable=wb6 type=inter dependent=false	// L8895
      wb6 = v5590;	// L8896
      uint8_t v5592 = sb_cmp6[0];	// L8897
      int32_t v5593 = v5592;	// L8898
      bool v5594 = v5593 == 1;	// L8899
      if (v5594) {	// L8900
        uint8_t v5595 = sb_ix6[0];	// L8901
        int v5596 = v5595;	// L8902
        uint8_t v5597 = cmpq6[v5596];	// L8903
        condition_reg6 = v5597;	// L8904
      }
      uint8_t v5598 = sb_rtr6[0];	// L8906
      int32_t v5599 = v5598;	// L8907
      bool v5600 = v5599 == 1;	// L8908
      if (v5600) {	// L8909
        uint8_t v5601 = sb_inj6[0];	// L8910
        int32_t v5602 = v5601;	// L8911
        bool v5603 = v5602 == 1;	// L8912
        ap_int<26> v5604 = csd_pkt6;	// L8913
        bool v5605;
        ap_int<26> v5605_tmp = v5604;
        v5605 = v5605_tmp[25];	// L8914
        int32_t v5606 = v5605;	// L8915
        bool v5607 = v5606 == 0;	// L8916
        bool v5608 = v5603 & v5607;	// L8917
        if (v5608) {	// L8918
          half v5609 = wb6;	// L8919
          uint16_t v5610;
          union { half from; uint16_t to;} _converter_v5609_to_v5610 = {};
          _converter_v5609_to_v5610.from = v5609;
          v5610 = _converter_v5609_to_v5610.to;	// L8920
          ap_int<26> v5611 = csd_pkt6;	// L8921
          ap_int<26> v5612;
          ap_int<26> v5612_tmp = v5611;
          v5612_tmp(15, 0) = v5610;
          v5612 = v5612_tmp;	// L8922
          csd_pkt6 = v5612;	// L8923
          uint8_t v5613 = sb_dst6[0];	// L8924
          ap_uint<4> v5614 = v5613;	// L8925
          ap_int<26> v5615 = csd_pkt6;	// L8926
          ap_int<26> v5616;
          ap_int<26> v5616_tmp = v5615;
          v5616_tmp(19, 16) = v5614;
          v5616 = v5616_tmp;	// L8927
          csd_pkt6 = v5616;	// L8928
          uint8_t v5617 = sb_id6[0];	// L8929
          ap_uint<4> v5618 = v5617;	// L8930
          ap_int<26> v5619 = csd_pkt6;	// L8931
          ap_int<26> v5620;
          ap_int<26> v5620_tmp = v5619;
          v5620_tmp(24, 21) = v5618;
          v5620 = v5620_tmp;	// L8932
          csd_pkt6 = v5620;	// L8933
          uint8_t v5621 = sb_rvld6[0];	// L8934
          bool v5622 = v5621;	// L8935
          ap_int<26> v5623 = csd_pkt6;	// L8936
          ap_int<26> v5624;
          ap_int<26> v5624_tmp = v5623;
          v5624_tmp[25] = v5622;          v5624 = v5624_tmp;	// L8937
          csd_pkt6 = v5624;	// L8938
          uint8_t v5625 = sb_dir6[0];	// L8939
          int32_t v5626 = v5625;	// L8940
          csd_dir6 = v5626;	// L8941
        }
      } else {
        uint8_t v5627 = sb_dst6[0];	// L8944
        int32_t v5628 = v5627;	// L8945
        bool v5629 = v5628 >= 12;	// L8946
        if (v5629) {	// L8947
          ap_uint<17> tw06;	// L8948
          tw06 = 0;	// L8949
          uint8_t v5631 = sb_rvld6[0];	// L8950
          bool v5632 = v5631;	// L8951
          ap_int<17> v5633 = tw06;	// L8952
          ap_int<17> v5634;
          ap_int<17> v5634_tmp = v5633;
          v5634_tmp[0] = v5632;          v5634 = v5634_tmp;	// L8953
          tw06 = v5634;	// L8954
          half v5635 = wb6;	// L8955
          uint16_t v5636;
          union { half from; uint16_t to;} _converter_v5635_to_v5636 = {};
          _converter_v5635_to_v5636.from = v5635;
          v5636 = _converter_v5635_to_v5636.to;	// L8956
          ap_int<17> v5637 = tw06;	// L8957
          ap_int<17> v5638;
          ap_int<17> v5638_tmp = v5637;
          v5638_tmp(16, 1) = v5636;
          v5638 = v5638_tmp;	// L8958
          tw06 = v5638;	// L8959
          uint8_t v5639 = sb_dst6[0];	// L8960
          int32_t v5640 = v5639;	// L8961
          int32_t v5641 = v5640 & 3;	// L8962
          bool v5642 = v5641 == 0;	// L8963
          if (v5642) {	// L8964
            ap_int<17> v5643 = tw06;	// L8965
            tx_n6 = v5643;	// L8966
          } else {
            uint8_t v5644 = sb_dst6[0];	// L8968
            int32_t v5645 = v5644;	// L8969
            int32_t v5646 = v5645 & 3;	// L8970
            bool v5647 = v5646 == 1;	// L8971
            if (v5647) {	// L8972
              ap_int<17> v5648 = tw06;	// L8973
              tx_s6 = v5648;	// L8974
            } else {
              uint8_t v5649 = sb_dst6[0];	// L8976
              int32_t v5650 = v5649;	// L8977
              int32_t v5651 = v5650 & 3;	// L8978
              bool v5652 = v5651 == 2;	// L8979
              if (v5652) {	// L8980
                ap_int<17> v5653 = tw06;	// L8981
                tx_w6 = v5653;	// L8982
              } else {
                ap_int<17> v5654 = tw06;	// L8984
                tx_e6 = v5654;	// L8985
              }
            }
          }
        } else {
          uint8_t v5655 = sb_rvld6[0];	// L8990
          int32_t v5656 = v5655;	// L8991
          bool v5657 = v5656 == 1;	// L8992
          if (v5657) {	// L8993
            uint8_t v5658 = sb_dst6[0];	// L8994
            int32_t v5659 = v5658;	// L8995
            bool v5660 = v5659 < 8;	// L8996
            int32_t v5661 = dsmask6;	// L8997
            int32_t v5662 = v5661 >> v5659;	// L8998
            int32_t v5663 = v5662 & 1;	// L8999
            bool v5664 = v5663 == 1;	// L9000
            bool v5665 = v5660 & v5664;	// L9001
            if (v5665) {	// L9002
              uint8_t v5666 = sb_dst6[0];	// L9003
              int v5667 = v5666;	// L9004
              int32_t v5668 = drf_full6[v5667];	// L9005
              bool v5669 = v5668 == 0;	// L9006
              if (v5669) {	// L9007
                half v5670 = wb6;	// L9008
                uint8_t v5671 = sb_dst6[0];	// L9009
                int v5672 = v5671;	// L9010
                drf6[v5672] = v5670;	// L9011
                uint8_t v5673 = sb_dst6[0];	// L9012
                int v5674 = v5673;	// L9013
                drf_full6[v5674] = 1;	// L9014
              }
            } else {
              half v5675 = wb6;	// L9017
              uint8_t v5676 = sb_dst6[0];	// L9018
              int32_t v5677 = v5676;	// L9019
              int32_t v5678 = v5677 & 7;	// L9020
              int v5679 = v5678;	// L9021
              drf6[v5679] = v5675;	// L9022
            }
          }
        }
      }
    }
    int32_t pc6;	// L9028
    pc6 = -1;	// L9029
    int8_t v5681 = fetch_en6;	// L9030
    int32_t v5682 = v5681;	// L9031
    bool v5683 = v5682 == 1;	// L9032
    if (v5683) {	// L9033
      int8_t v5684 = instr_cnt6;	// L9034
      int32_t v5685 = v5684;	// L9035
      pc6 = v5685;	// L9036
    }
    int8_t v5686 = fetch_en6;	// L9038
    int32_t v5687 = v5686;	// L9039
    bool v5688 = v5687 == 1;	// L9040
    if (v5688) {	// L9041
      fe_ever6 = 1;	// L9042
    }
    int32_t instr6;	// L9044
    instr6 = 0;	// L9045
    int32_t v5690 = pc6;	// L9046
    bool v5691 = v5690 >= 0;	// L9047
    if (v5691) {	// L9048
      int32_t v5692 = pc6;	// L9049
      int v5693 = v5692;	// L9050
      int32_t v5694 = irf6[v5693];	// L9051
      instr6 = v5694;	// L9052
    }
    int32_t v5695 = instr6;	// L9054
    int32_t v5696 = v5695 & 15;	// L9055
    int32_t op6;	// L9056
    op6 = v5696;	// L9057
    int32_t v5698 = instr6;	// L9058
    int32_t v5699 = v5698 >> 4;	// L9059
    int32_t v5700 = v5699 & 15;	// L9060
    int32_t dst6;	// L9061
    dst6 = v5700;	// L9062
    int32_t v5702 = instr6;	// L9063
    int32_t v5703 = v5702 >> 8;	// L9064
    int32_t v5704 = v5703 & 15;	// L9065
    int32_t s16;	// L9066
    s16 = v5704;	// L9067
    int32_t v5706 = instr6;	// L9068
    int32_t v5707 = v5706 >> 12;	// L9069
    int32_t v5708 = v5707 & 15;	// L9070
    int32_t s26;	// L9071
    s26 = v5708;	// L9072
    half a6;	// L9073
    a6 = 0.000000;	// L9074
    half b6;	// L9075
    b6 = 0.000000;	// L9076
    int32_t v5712 = s16;	// L9077
    bool v5713 = v5712 >= 12;	// L9078
    if (v5713) {	// L9079
      int32_t v5714 = s16;	// L9080
      int32_t v5715 = v5714 & 3;	// L9081
      int v5716 = v5715;	// L9082
      half v5717 = hold_v6[v5716][0];	// L9083
      a6 = v5717;	// L9084
    } else {
      int32_t v5718 = s16;	// L9086
      int v5719 = v5718;	// L9087
      half v5720 = drf6[v5719];	// L9088
      a6 = v5720;	// L9089
    }
    int32_t v5721 = s26;	// L9091
    bool v5722 = v5721 >= 12;	// L9092
    if (v5722) {	// L9093
      int32_t v5723 = s26;	// L9094
      int32_t v5724 = v5723 & 3;	// L9095
      int v5725 = v5724;	// L9096
      half v5726 = hold_v6[v5725][0];	// L9097
      b6 = v5726;	// L9098
    } else {
      int32_t v5727 = s26;	// L9100
      int v5728 = v5727;	// L9101
      half v5729 = drf6[v5728];	// L9102
      b6 = v5729;	// L9103
    }
    int32_t a_vld6;	// L9105
    a_vld6 = 1;	// L9106
    int32_t b_vld6;	// L9107
    b_vld6 = 1;	// L9108
    int32_t v5732 = s16;	// L9109
    bool v5733 = v5732 >= 12;	// L9110
    if (v5733) {	// L9111
      a_vld6 = 0;	// L9112
      int32_t v5734 = s16;	// L9113
      int32_t v5735 = v5734 & 3;	// L9114
      int v5736 = v5735;	// L9115
      uint8_t v5737 = hold_cnt6[v5736];	// L9116
      int32_t v5738 = v5737;	// L9117
      bool v5739 = v5738 > 0;	// L9118
      if (v5739) {	// L9119
        a_vld6 = 1;	// L9120
      }
    }
    int32_t v5740 = s26;	// L9123
    bool v5741 = v5740 >= 12;	// L9124
    if (v5741) {	// L9125
      b_vld6 = 0;	// L9126
      int32_t v5742 = s26;	// L9127
      int32_t v5743 = v5742 & 3;	// L9128
      int v5744 = v5743;	// L9129
      uint8_t v5745 = hold_cnt6[v5744];	// L9130
      int32_t v5746 = v5745;	// L9131
      bool v5747 = v5746 > 0;	// L9132
      if (v5747) {	// L9133
        b_vld6 = 1;	// L9134
      }
    }
    int32_t v5748 = s16;	// L9137
    bool v5749 = v5748 < 8;	// L9138
    int32_t v5750 = dsmask6;	// L9139
    int32_t v5751 = v5750 >> v5748;	// L9140
    int32_t v5752 = v5751 & 1;	// L9141
    bool v5753 = v5752 == 1;	// L9142
    bool v5754 = v5749 & v5753;	// L9143
    if (v5754) {	// L9144
      int32_t v5755 = s16;	// L9145
      int v5756 = v5755;	// L9146
      int32_t v5757 = drf_full6[v5756];	// L9147
      bool v5758 = v5757 == 0;	// L9148
      if (v5758) {	// L9149
        a_vld6 = 0;	// L9150
      }
    }
    int32_t v5759 = s26;	// L9153
    bool v5760 = v5759 < 8;	// L9154
    int32_t v5761 = dsmask6;	// L9155
    int32_t v5762 = v5761 >> v5759;	// L9156
    int32_t v5763 = v5762 & 1;	// L9157
    bool v5764 = v5763 == 1;	// L9158
    bool v5765 = v5760 & v5764;	// L9159
    if (v5765) {	// L9160
      int32_t v5766 = s26;	// L9161
      int v5767 = v5766;	// L9162
      int32_t v5768 = drf_full6[v5767];	// L9163
      bool v5769 = v5768 == 0;	// L9164
      if (v5769) {	// L9165
        b_vld6 = 0;	// L9166
      }
    }
    int32_t binop6;	// L9169
    binop6 = 0;	// L9170
    int32_t v5771 = op6;	// L9171
    bool v5772 = v5771 == 0;	// L9172
    bool v5773 = v5771 == 1;	// L9173
    bool v5774 = v5771 == 2;	// L9174
    bool v5775 = v5771 == 8;	// L9175
    bool v5776 = v5771 == 9;	// L9176
    bool v5777 = v5772 | v5773;	// L9177
    bool v5778 = v5777 | v5774;	// L9178
    bool v5779 = v5778 | v5775;	// L9179
    bool v5780 = v5779 | v5776;	// L9180
    if (v5780) {	// L9181
      binop6 = 1;	// L9182
    }
    int32_t raw6;	// L9184
    raw6 = 0;	// L9185
    int32_t cmp_busy6;	// L9186
    cmp_busy6 = 0;	// L9187
    l_S_k_5_k12: for (int k12 = 0; k12 < 4; k12++) {	// L9188
      uint8_t v5784 = sb_v6[(k12 + 1)];	// L9189
      int32_t v5785 = v5784;	// L9190
      bool v5786 = v5785 == 1;	// L9191
      uint8_t v5787 = sb_rtr6[(k12 + 1)];	// L9192
      int32_t v5788 = v5787;	// L9193
      bool v5789 = v5788 == 0;	// L9194
      uint8_t v5790 = sb_dst6[(k12 + 1)];	// L9195
      int32_t v5791 = v5790;	// L9196
      bool v5792 = v5791 < 12;	// L9197
      bool v5793 = v5786 & v5789;	// L9198
      bool v5794 = v5793 & v5792;	// L9199
      if (v5794) {	// L9200
        int32_t v5795 = s16;	// L9201
        bool v5796 = v5795 < 12;	// L9202
        uint8_t v5797 = sb_dst6[(k12 + 1)];	// L9203
        int32_t v5798 = v5797;	// L9204
        int32_t v5799 = v5798 & 7;	// L9205
        int32_t v5800 = v5795 & 7;	// L9206
        bool v5801 = v5799 == v5800;	// L9207
        bool v5802 = v5796 & v5801;	// L9208
        if (v5802) {	// L9209
          raw6 = 1;	// L9210
        }
        int32_t v5803 = binop6;	// L9212
        bool v5804 = v5803 == 1;	// L9213
        int32_t v5805 = s26;	// L9214
        bool v5806 = v5805 < 12;	// L9215
        uint8_t v5807 = sb_dst6[(k12 + 1)];	// L9216
        int32_t v5808 = v5807;	// L9217
        int32_t v5809 = v5808 & 7;	// L9218
        int32_t v5810 = v5805 & 7;	// L9219
        bool v5811 = v5809 == v5810;	// L9220
        bool v5812 = v5804 & v5806;	// L9221
        bool v5813 = v5812 & v5811;	// L9222
        if (v5813) {	// L9223
          raw6 = 1;	// L9224
        }
      }
      uint8_t v5814 = sb_v6[(k12 + 1)];	// L9227
      int32_t v5815 = v5814;	// L9228
      bool v5816 = v5815 == 1;	// L9229
      uint8_t v5817 = sb_cmp6[(k12 + 1)];	// L9230
      int32_t v5818 = v5817;	// L9231
      bool v5819 = v5818 == 1;	// L9232
      bool v5820 = v5816 & v5819;	// L9233
      if (v5820) {	// L9234
        cmp_busy6 = 1;	// L9235
      }
    }
    int32_t is_cond6;	// L9238
    is_cond6 = 0;	// L9239
    int32_t v5822 = op6;	// L9240
    bool v5823 = v5822 >= 12;	// L9241
    ap_int<33> v5824 = v5822;	// L9242
    bool v5825 = v5824 <= 15;	// L9243
    bool v5826 = v5823 & v5825;	// L9244
    if (v5826) {	// L9245
      is_cond6 = 1;	// L9246
    }
    int32_t grant6;	// L9248
    grant6 = 0;	// L9249
    int32_t v5828 = pc6;	// L9250
    bool v5829 = v5828 >= 0;	// L9251
    if (v5829) {	// L9252
      grant6 = 1;	// L9253
    }
    int32_t v5830 = pc6;	// L9255
    bool v5831 = v5830 >= 0;	// L9256
    int32_t v5832 = a_vld6;	// L9257
    bool v5833 = v5832 == 0;	// L9258
    int32_t v5834 = binop6;	// L9259
    bool v5835 = v5834 == 1;	// L9260
    int32_t v5836 = b_vld6;	// L9261
    bool v5837 = v5836 == 0;	// L9262
    bool v5838 = v5835 & v5837;	// L9263
    bool v5839 = v5833 | v5838;	// L9264
    bool v5840 = v5831 & v5839;	// L9265
    if (v5840) {	// L9266
      grant6 = 0;	// L9267
    }
    int32_t v5841 = pc6;	// L9269
    bool v5842 = v5841 >= 0;	// L9270
    int32_t v5843 = raw6;	// L9271
    bool v5844 = v5843 == 1;	// L9272
    int32_t v5845 = is_cond6;	// L9273
    bool v5846 = v5845 == 1;	// L9274
    int32_t v5847 = cmp_busy6;	// L9275
    bool v5848 = v5847 == 1;	// L9276
    bool v5849 = v5846 & v5848;	// L9277
    bool v5850 = v5844 | v5849;	// L9278
    bool v5851 = v5842 & v5850;	// L9279
    if (v5851) {	// L9280
      grant6 = 0;	// L9281
    }
    int32_t v5852 = grant6;	// L9283
    bool v5853 = v5852 == 1;	// L9284
    if (v5853) {	// L9285
      int8_t v5854 = instr_cnt6;	// L9286
      int32_t v5855 = cfg_isz6;	// L9287
      int32_t v5856 = v5854;	// L9288
      bool v5857 = v5856 == v5855;	// L9289
      if (v5857) {	// L9290
        instr_cnt6 = 0;	// L9291
        int8_t v5858 = iter_cnt6;	// L9292
        int32_t v5859 = cfg_itsz6;	// L9293
        ap_int<33> v5860 = v5859;	// L9294
        ap_int<33> v5861 = v5860 - 1;	// L9295
        ap_int<33> v5862 = v5858;	// L9296
        bool v5863 = v5862 == v5861;	// L9297
        if (v5863) {	// L9298
          fetch_en6 = 0;	// L9299
        } else {
          int8_t v5864 = iter_cnt6;	// L9301
          ap_int<33> v5865 = v5864;	// L9302
          ap_int<33> v5866 = v5865 + 1;	// L9303
          uint8_t v5867 = v5866;	// L9304
          iter_cnt6 = v5867;	// L9305
        }
      } else {
        int8_t v5868 = instr_cnt6;	// L9308
        ap_int<33> v5869 = v5868;	// L9309
        ap_int<33> v5870 = v5869 + 1;	// L9310
        uint8_t v5871 = v5870;	// L9311
        instr_cnt6 = v5871;	// L9312
      }
    }
    int32_t c16;	// L9315
    c16 = -1;	// L9316
    int32_t c26;	// L9317
    c26 = -1;	// L9318
    int32_t v5874 = grant6;	// L9319
    bool v5875 = v5874 == 1;	// L9320
    int32_t v5876 = s16;	// L9321
    bool v5877 = v5876 >= 12;	// L9322
    bool v5878 = v5875 & v5877;	// L9323
    if (v5878) {	// L9324
      int32_t v5879 = s16;	// L9325
      int32_t v5880 = v5879 & 3;	// L9326
      c16 = v5880;	// L9327
    }
    int32_t v5881 = grant6;	// L9329
    bool v5882 = v5881 == 1;	// L9330
    int32_t v5883 = s26;	// L9331
    bool v5884 = v5883 >= 12;	// L9332
    bool v5885 = v5882 & v5884;	// L9333
    if (v5885) {	// L9334
      int32_t v5886 = s26;	// L9335
      int32_t v5887 = v5886 & 3;	// L9336
      c26 = v5887;	// L9337
    }
    int32_t v5888 = c16;	// L9339
    bool v5889 = v5888 >= 0;	// L9340
    if (v5889) {	// L9341
      int32_t v5890 = c16;	// L9342
      int v5891 = v5890;	// L9343
      half v5892 = hold_v6[v5891][1];	// L9344
      hold_v6[v5891][0] = v5892;	// L9345
      int32_t v5893 = c16;	// L9346
      int v5894 = v5893;	// L9347
      uint8_t v5895 = hold_cnt6[v5894];	// L9348
      ap_int<33> v5896 = v5895;	// L9349
      ap_int<33> v5897 = v5896 - 1;	// L9350
      uint8_t v5898 = v5897;	// L9351
      hold_cnt6[v5894] = v5898;	// L9352
    }
    int32_t v5899 = c26;	// L9354
    bool v5900 = v5899 >= 0;	// L9355
    int32_t v5901 = c16;	// L9356
    bool v5902 = v5899 != v5901;	// L9357
    bool v5903 = v5900 & v5902;	// L9358
    if (v5903) {	// L9359
      int32_t v5904 = c26;	// L9360
      int v5905 = v5904;	// L9361
      half v5906 = hold_v6[v5905][1];	// L9362
      hold_v6[v5905][0] = v5906;	// L9363
      int32_t v5907 = c26;	// L9364
      int v5908 = v5907;	// L9365
      uint8_t v5909 = hold_cnt6[v5908];	// L9366
      ap_int<33> v5910 = v5909;	// L9367
      ap_int<33> v5911 = v5910 - 1;	// L9368
      uint8_t v5912 = v5911;	// L9369
      hold_cnt6[v5908] = v5912;	// L9370
    }
    int32_t v5913 = grant6;	// L9372
    bool v5914 = v5913 == 1;	// L9373
    int32_t v5915 = s16;	// L9374
    bool v5916 = v5915 < 8;	// L9375
    int32_t v5917 = dsmask6;	// L9376
    int32_t v5918 = v5917 >> v5915;	// L9377
    int32_t v5919 = v5918 & 1;	// L9378
    bool v5920 = v5919 == 1;	// L9379
    bool v5921 = v5914 & v5916;	// L9380
    bool v5922 = v5921 & v5920;	// L9381
    if (v5922) {	// L9382
      int32_t v5923 = s16;	// L9383
      int v5924 = v5923;	// L9384
      drf_full6[v5924] = 0;	// L9385
    }
    int32_t v5925 = grant6;	// L9387
    bool v5926 = v5925 == 1;	// L9388
    int32_t v5927 = s26;	// L9389
    bool v5928 = v5927 < 8;	// L9390
    int32_t v5929 = dsmask6;	// L9391
    int32_t v5930 = v5929 >> v5927;	// L9392
    int32_t v5931 = v5930 & 1;	// L9393
    bool v5932 = v5931 == 1;	// L9394
    bool v5933 = v5926 & v5928;	// L9395
    bool v5934 = v5933 & v5932;	// L9396
    if (v5934) {	// L9397
      int32_t v5935 = s26;	// L9398
      int v5936 = v5935;	// L9399
      drf_full6[v5936] = 0;	// L9400
    }
    half res6;
#pragma HLS dependence variable=res6 type=inter dependent=false	// L9402
    res6 = 0.000000;	// L9403
    int32_t v5938 = op6;	// L9404
    bool v5939 = v5938 == 0;	// L9405
    if (v5939) {	// L9406
      half v5940 = a6;	// L9407
      half v5941 = b6;	// L9408
      half v5942 = v5940 + v5941;	// L9409
      res6 = v5942;	// L9410
    } else {
      int32_t v5943 = op6;	// L9412
      bool v5944 = v5943 == 1;	// L9413
      if (v5944) {	// L9414
        half v5945 = a6;	// L9415
        half v5946 = b6;	// L9416
        half v5947 = v5945 - v5946;	// L9417
        res6 = v5947;	// L9418
      } else {
        int32_t v5948 = op6;	// L9420
        bool v5949 = v5948 == 2;	// L9421
        if (v5949) {	// L9422
          half v5950 = a6;	// L9423
          half v5951 = b6;	// L9424
          half v5952 = v5950 * v5951;	// L9425
          res6 = v5952;	// L9426
        } else {
          int32_t v5953 = op6;	// L9428
          bool v5954 = v5953 == 8;	// L9429
          if (v5954) {	// L9430
            half v5955 = a6;	// L9431
            half v5956 = b6;	// L9432
            bool v5957 = v5955 >= v5956;	// L9433
            if (v5957) {	// L9434
              res6 = 1.000000;	// L9435
            } else {
              res6 = -1.000000;	// L9437
            }
          } else {
            int32_t v5958 = op6;	// L9440
            bool v5959 = v5958 == 9;	// L9441
            if (v5959) {	// L9442
              half v5960 = a6;	// L9443
              half v5961 = b6;	// L9444
              bool v5962 = v5960 < v5961;	// L9445
              if (v5962) {	// L9446
                res6 = 1.000000;	// L9447
              } else {
                res6 = -1.000000;	// L9449
              }
            } else {
              half v5963 = a6;	// L9452
              res6 = v5963;	// L9453
            }
          }
        }
      }
    }
    int32_t v5964 = a_vld6;	// L9459
    int32_t res_vld6;	// L9460
    res_vld6 = v5964;	// L9461
    int32_t v5966 = op6;	// L9462
    bool v5967 = v5966 == 0;	// L9463
    bool v5968 = v5966 == 1;	// L9464
    bool v5969 = v5966 == 2;	// L9465
    bool v5970 = v5966 == 8;	// L9466
    bool v5971 = v5966 == 9;	// L9467
    bool v5972 = v5967 | v5968;	// L9468
    bool v5973 = v5972 | v5969;	// L9469
    bool v5974 = v5973 | v5970;	// L9470
    bool v5975 = v5974 | v5971;	// L9471
    if (v5975) {	// L9472
      int32_t v5976 = a_vld6;	// L9473
      int32_t v5977 = b_vld6;	// L9474
      int64_t v5978 = v5976;	// L9475
      int64_t v5979 = v5977;	// L9476
      int64_t v5980 = v5978 * v5979;	// L9477
      int32_t v5981 = v5980;	// L9478
      res_vld6 = v5981;	// L9479
    }
    int32_t v5982 = grant6;	// L9481
    bool v5983 = v5982 == 0;	// L9482
    if (v5983) {	// L9483
      res_vld6 = 0;	// L9484
    }
    int32_t is_rtr6;	// L9486
    is_rtr6 = 0;	// L9487
    int32_t v5985 = op6;	// L9488
    bool v5986 = v5985 >= 4;	// L9489
    ap_int<33> v5987 = v5985;	// L9490
    bool v5988 = v5987 <= 7;	// L9491
    bool v5989 = v5986 & v5988;	// L9492
    if (v5989) {	// L9493
      is_rtr6 = 1;	// L9494
    }
    l_S_k_6_k13: for (int k13 = 0; k13 < 4; k13++) {	// L9496
      uint8_t v5991 = sb_v6[(k13 + 1)];	// L9497
      sb_v6[k13] = v5991;	// L9498
      uint8_t v5992 = sb_dst6[(k13 + 1)];	// L9499
      sb_dst6[k13] = v5992;	// L9500
      uint8_t v5993 = sb_cmp6[(k13 + 1)];	// L9501
      sb_cmp6[k13] = v5993;	// L9502
      uint8_t v5994 = sb_rtr6[(k13 + 1)];	// L9503
      sb_rtr6[k13] = v5994;	// L9504
      uint8_t v5995 = sb_inj6[(k13 + 1)];	// L9505
      sb_inj6[k13] = v5995;	// L9506
      uint8_t v5996 = sb_dir6[(k13 + 1)];	// L9507
      sb_dir6[k13] = v5996;	// L9508
      uint8_t v5997 = sb_id6[(k13 + 1)];	// L9509
      sb_id6[k13] = v5997;	// L9510
      uint8_t v5998 = sb_rvld6[(k13 + 1)];	// L9511
      sb_rvld6[k13] = v5998;	// L9512
      uint8_t v5999 = sb_ix6[(k13 + 1)];	// L9513
      sb_ix6[k13] = v5999;	// L9514
    }
    sb_v6[4] = 0;	// L9516
    int32_t v6000 = grant6;	// L9517
    bool v6001 = v6000 == 1;	// L9518
    if (v6001) {	// L9519
      half v6002 = res6;	// L9520
      int8_t v6003 = resq_wr6;	// L9521
      int v6004 = v6003;	// L9522
      resq6[v6004] = v6002;	// L9523
      int32_t cq6;	// L9524
      cq6 = 0;	// L9525
      int32_t v6006 = op6;	// L9526
      bool v6007 = v6006 == 8;	// L9527
      if (v6007) {	// L9528
        half v6008 = a6;	// L9529
        half v6009 = b6;	// L9530
        bool v6010 = v6008 >= v6009;	// L9531
        if (v6010) {	// L9532
          cq6 = 1;	// L9533
        }
      }
      int32_t v6011 = op6;	// L9536
      bool v6012 = v6011 == 9;	// L9537
      if (v6012) {	// L9538
        half v6013 = a6;	// L9539
        half v6014 = b6;	// L9540
        bool v6015 = v6013 < v6014;	// L9541
        if (v6015) {	// L9542
          cq6 = 1;	// L9543
        }
      }
      int32_t v6016 = cq6;	// L9546
      uint8_t v6017 = v6016;	// L9547
      int8_t v6018 = resq_wr6;	// L9548
      int v6019 = v6018;	// L9549
      cmpq6[v6019] = v6017;	// L9550
      sb_v6[4] = 1;	// L9551
      int32_t v6020 = dst6;	// L9552
      uint8_t v6021 = v6020;	// L9553
      sb_dst6[4] = v6021;	// L9554
      int8_t v6022 = resq_wr6;	// L9555
      sb_ix6[4] = v6022;	// L9556
      sb_cmp6[4] = 0;	// L9557
      int32_t v6023 = op6;	// L9558
      bool v6024 = v6023 == 8;	// L9559
      bool v6025 = v6023 == 9;	// L9560
      bool v6026 = v6024 | v6025;	// L9561
      if (v6026) {	// L9562
        sb_cmp6[4] = 1;	// L9563
      }
      int32_t v6027 = is_rtr6;	// L9565
      int32_t rtrf6;	// L9566
      rtrf6 = v6027;	// L9567
      int32_t v6029 = is_cond6;	// L9568
      bool v6030 = v6029 == 1;	// L9569
      if (v6030) {	// L9570
        rtrf6 = 1;	// L9571
      }
      int32_t v6031 = rtrf6;	// L9573
      uint8_t v6032 = v6031;	// L9574
      sb_rtr6[4] = v6032;	// L9575
      int32_t v6033 = is_rtr6;	// L9576
      int32_t inj6;	// L9577
      inj6 = v6033;	// L9578
      int32_t v6035 = is_cond6;	// L9579
      bool v6036 = v6035 == 1;	// L9580
      int8_t v6037 = condition_reg6;	// L9581
      int32_t v6038 = v6037;	// L9582
      bool v6039 = v6038 == 1;	// L9583
      bool v6040 = v6036 & v6039;	// L9584
      if (v6040) {	// L9585
        inj6 = 1;	// L9586
      }
      int32_t v6041 = inj6;	// L9588
      uint8_t v6042 = v6041;	// L9589
      sb_inj6[4] = v6042;	// L9590
      int32_t v6043 = op6;	// L9591
      int32_t v6044 = v6043 & 3;	// L9592
      uint8_t v6045 = v6044;	// L9593
      sb_dir6[4] = v6045;	// L9594
      int32_t v6046 = s26;	// L9595
      uint8_t v6047 = v6046;	// L9596
      sb_id6[4] = v6047;	// L9597
      int32_t v6048 = res_vld6;	// L9598
      uint8_t v6049 = v6048;	// L9599
      sb_rvld6[4] = v6049;	// L9600
      int8_t v6050 = resq_wr6;	// L9601
      ap_int<33> v6051 = v6050;	// L9602
      ap_int<33> v6052 = v6051 + 1;	// L9603
      ap_int<33> v6053 = v6052 & 7;	// L9604
      uint8_t v6054 = v6053;	// L9605
      resq_wr6 = v6054;	// L9606
    }
    ap_int<17> v6055 = tx_n6;	// L9608
    txn_r6 = v6055;	// L9609
    ap_int<17> v6056 = tx_s6;	// L9610
    txs_r6 = v6056;	// L9611
    ap_int<17> v6057 = tx_w6;	// L9612
    txw_r6 = v6057;	// L9613
    ap_int<17> v6058 = tx_e6;	// L9614
    txe_r6 = v6058;	// L9615
    int32_t v6059 = crv_vld6;	// L9616
    bool v6060 = v6059 == 1;	// L9617
    if (v6060) {	// L9618
      int32_t v6061 = crv_mode6;	// L9619
      bool v6062 = v6061 == 1;	// L9620
      if (v6062) {	// L9621
        int32_t v6063 = crv_addr6;	// L9622
        int32_t v6064 = v6063 >> 3;	// L9623
        int32_t v6065 = v6064 & 1;	// L9624
        bool v6066 = v6065 == 1;	// L9625
        if (v6066) {	// L9626
          int32_t v6067 = crv_raw6;	// L9627
          int32_t v6068 = crv_addr6;	// L9628
          int32_t v6069 = v6068 & 7;	// L9629
          int v6070 = v6069;	// L9630
          irf6[v6070] = v6067;	// L9631
        } else {
          int32_t v6071 = crv_addr6;	// L9633
          bool v6072 = v6071 == 0;	// L9634
          if (v6072) {	// L9635
            int32_t v6073 = crv_raw6;	// L9636
            int32_t v6074 = v6073 & 255;	// L9637
            dsmask6 = v6074;	// L9638
            int32_t v6075 = crv_raw6;	// L9639
            int32_t v6076 = v6075 >> 8;	// L9640
            int32_t v6077 = v6076 & 7;	// L9641
            cfg_isz6 = v6077;	// L9642
            int32_t v6078 = crv_raw6;	// L9643
            int32_t v6079 = v6078 >> 15;	// L9644
            int32_t v6080 = v6079 & 1;	// L9645
            bool v6081 = v6080 == 1;	// L9646
            if (v6081) {	// L9647
              fetch_en6 = 1;	// L9648
              instr_cnt6 = 0;	// L9649
              iter_cnt6 = 0;	// L9650
            }
          } else {
            int32_t v6082 = crv_addr6;	// L9653
            bool v6083 = v6082 == 1;	// L9654
            if (v6083) {	// L9655
              int32_t v6084 = crv_raw6;	// L9656
              int32_t v6085 = v6084 & 255;	// L9657
              cfg_itsz6 = v6085;	// L9658
            }
          }
        }
      } else {
        int32_t v6086 = crv_addr6;	// L9663
        bool v6087 = v6086 < 8;	// L9664
        int32_t v6088 = dsmask6;	// L9665
        int32_t v6089 = v6088 >> v6086;	// L9666
        int32_t v6090 = v6089 & 1;	// L9667
        bool v6091 = v6090 == 1;	// L9668
        bool v6092 = v6087 & v6091;	// L9669
        if (v6092) {	// L9670
          int32_t v6093 = crv_addr6;	// L9671
          int v6094 = v6093;	// L9672
          int32_t v6095 = drf_full6[v6094];	// L9673
          bool v6096 = v6095 == 0;	// L9674
          if (v6096) {	// L9675
            half v6097 = crv_data6;	// L9676
            int32_t v6098 = crv_addr6;	// L9677
            int v6099 = v6098;	// L9678
            drf6[v6099] = v6097;	// L9679
            int32_t v6100 = crv_addr6;	// L9680
            int v6101 = v6100;	// L9681
            drf_full6[v6101] = 1;	// L9682
          }
        } else {
          half v6102 = crv_data6;	// L9685
          int32_t v6103 = crv_addr6;	// L9686
          int v6104 = v6103;	// L9687
          drf6[v6104] = v6102;	// L9688
        }
      }
    }
    ap_int<17> v6105 = txe_r6;	// L9692
    bool v6106;
    ap_int<17> v6106_tmp = v6105;
    v6106 = v6106_tmp[0];	// L9693
    int32_t v6107 = v6106;	// L9694
    bool v6108 = v6107 == 1;	// L9695
    if (v6108) {	// L9696
      ap_int<17> v6109 = txe_r6;	// L9697
      v5262.write(v6109);	// L9698
    }
    ap_int<17> v6110 = txw_r6;	// L9700
    bool v6111;
    ap_int<17> v6111_tmp = v6110;
    v6111 = v6111_tmp[0];	// L9701
    int32_t v6112 = v6111;	// L9702
    bool v6113 = v6112 == 1;	// L9703
    if (v6113) {	// L9704
      ap_int<17> v6114 = txw_r6;	// L9705
      v5263.write(v6114);	// L9706
    }
    ap_int<17> v6115 = txs_r6;	// L9708
    bool v6116;
    ap_int<17> v6116_tmp = v6115;
    v6116 = v6116_tmp[0];	// L9709
    int32_t v6117 = v6116;	// L9710
    bool v6118 = v6117 == 1;	// L9711
    if (v6118) {	// L9712
      ap_int<17> v6119 = txs_r6;	// L9713
      v5264.write(v6119);	// L9714
    }
    ap_int<17> v6120 = txn_r6;	// L9716
    bool v6121;
    ap_int<17> v6121_tmp = v6120;
    v6121 = v6121_tmp[0];	// L9717
    int32_t v6122 = v6121;	// L9718
    bool v6123 = v6122 == 1;	// L9719
    if (v6123) {	// L9720
      ap_int<17> v6124 = txn_r6;	// L9721
      v5265.write(v6124);	// L9722
    }
  }
}

void node_1_3(
  hls::stream< ap_uint<26> >& v6125,
  hls::stream< ap_uint<26> >& v6126,
  hls::stream< ap_uint<26> >& v6127,
  hls::stream< ap_uint<26> >& v6128,
  hls::stream< ap_uint<26> >& v6129,
  hls::stream< ap_uint<26> >& v6130,
  hls::stream< ap_uint<26> >& v6131,
  hls::stream< ap_uint<26> >& v6132,
  hls::stream< ap_uint<17> >& v6133,
  hls::stream< ap_uint<17> >& v6134,
  hls::stream< ap_uint<17> >& v6135,
  hls::stream< ap_uint<17> >& v6136,
  hls::stream< ap_uint<17> >& v6137,
  hls::stream< ap_uint<17> >& v6138,
  hls::stream< ap_uint<17> >& v6139,
  hls::stream< ap_uint<17> >& v6140
) {	// L9727
  int32_t irf7[8];	// L9760
  #pragma HLS array_partition variable=irf7 complete dim=1

  for (int v6142 = 0; v6142 < 8; v6142++) {	// L9761
    irf7[v6142] = 0;	// L9761
  }
  half drf7[8];	// L9762
  #pragma HLS array_partition variable=drf7 complete dim=1

  for (int v6144 = 0; v6144 < 8; v6144++) {	// L9763
    drf7[v6144] = 0.000000;	// L9763
  }
  int32_t drf_full7[8];	// L9764
  #pragma HLS array_partition variable=drf_full7 complete dim=1

  for (int v6146 = 0; v6146 < 8; v6146++) {	// L9765
    drf_full7[v6146] = 0;	// L9765
  }
  int32_t dsmask7;	// L9766
  dsmask7 = 0;	// L9767
  int32_t crv_vld7;	// L9768
  crv_vld7 = 0;	// L9769
  half crv_data7;	// L9770
  crv_data7 = 0.000000;	// L9771
  int32_t crv_addr7;	// L9772
  crv_addr7 = 0;	// L9773
  int32_t crv_mode7;	// L9774
  crv_mode7 = 0;	// L9775
  int32_t crv_raw7;	// L9776
  crv_raw7 = 0;	// L9777
  int32_t csd_vld7;	// L9778
  csd_vld7 = 0;	// L9779
  ap_uint<26> csd_pkt7;	// L9780
  csd_pkt7 = 0;	// L9781
  int32_t csd_dir7;	// L9782
  csd_dir7 = 0;	// L9783
  int32_t row_id7;	// L9784
  row_id7 = 1;	// L9785
  int32_t col_id7;	// L9786
  col_id7 = 3;	// L9787
  ap_uint<17> txn_r7;	// L9788
  txn_r7 = 0;	// L9789
  ap_uint<17> txs_r7;	// L9790
  txs_r7 = 0;	// L9791
  ap_uint<17> txw_r7;	// L9792
  txw_r7 = 0;	// L9793
  ap_uint<17> txe_r7;	// L9794
  txe_r7 = 0;	// L9795
  half hold_v7[4][2];	// L9796
  #pragma HLS array_partition variable=hold_v7 complete dim=1
  #pragma HLS array_partition variable=hold_v7 complete dim=2

  for (int v6163 = 0; v6163 < 4; v6163++) {	// L9797
    for (int v6164 = 0; v6164 < 2; v6164++) {	// L9797
      hold_v7[v6163][v6164] = 0.000000;	// L9797
    }
  }
  uint8_t hold_cnt7[4];	// L9798
  #pragma HLS array_partition variable=hold_cnt7 complete dim=1

  for (int v6166 = 0; v6166 < 4; v6166++) {	// L9799
    hold_cnt7[v6166] = 0;	// L9799
  }
  int32_t crv_ever7;	// L9800
  crv_ever7 = 0;	// L9801
  int32_t fe_ever7;	// L9802
  fe_ever7 = 0;	// L9803
  ap_uint<26> rbuf7[4][2];	// L9804
  #pragma HLS array_partition variable=rbuf7 complete dim=1
  #pragma HLS array_partition variable=rbuf7 complete dim=2

  for (int v6170 = 0; v6170 < 4; v6170++) {	// L9805
    for (int v6171 = 0; v6171 < 2; v6171++) {	// L9805
      rbuf7[v6170][v6171] = 0;	// L9805
    }
  }
  uint8_t rbcnt7[4];	// L9806
  #pragma HLS array_partition variable=rbcnt7 complete dim=1

  for (int v6173 = 0; v6173 < 4; v6173++) {	// L9807
    rbcnt7[v6173] = 0;	// L9807
  }
  int32_t cfg_isz7;	// L9808
  cfg_isz7 = 0;	// L9809
  int32_t cfg_itsz7;	// L9810
  cfg_itsz7 = 0;	// L9811
  uint8_t fetch_en7;	// L9812
  fetch_en7 = 0;	// L9813
  uint8_t instr_cnt7;	// L9814
  instr_cnt7 = 0;	// L9815
  uint8_t iter_cnt7;	// L9816
  iter_cnt7 = 0;	// L9817
  uint8_t condition_reg7;	// L9818
  condition_reg7 = 0;	// L9819
  uint8_t sb_v7[5];	// L9820
  #pragma HLS array_partition variable=sb_v7 complete dim=1

  for (int v6181 = 0; v6181 < 5; v6181++) {	// L9821
    sb_v7[v6181] = 0;	// L9821
  }
  uint8_t sb_dst7[5];	// L9822
  #pragma HLS array_partition variable=sb_dst7 complete dim=1

  for (int v6183 = 0; v6183 < 5; v6183++) {	// L9823
    sb_dst7[v6183] = 0;	// L9823
  }
  uint8_t sb_cmp7[5];	// L9824
  #pragma HLS array_partition variable=sb_cmp7 complete dim=1

  for (int v6185 = 0; v6185 < 5; v6185++) {	// L9825
    sb_cmp7[v6185] = 0;	// L9825
  }
  uint8_t sb_rtr7[5];	// L9826
  #pragma HLS array_partition variable=sb_rtr7 complete dim=1

  for (int v6187 = 0; v6187 < 5; v6187++) {	// L9827
    sb_rtr7[v6187] = 0;	// L9827
  }
  uint8_t sb_inj7[5];	// L9828
  #pragma HLS array_partition variable=sb_inj7 complete dim=1

  for (int v6189 = 0; v6189 < 5; v6189++) {	// L9829
    sb_inj7[v6189] = 0;	// L9829
  }
  uint8_t sb_dir7[5];	// L9830
  #pragma HLS array_partition variable=sb_dir7 complete dim=1

  for (int v6191 = 0; v6191 < 5; v6191++) {	// L9831
    sb_dir7[v6191] = 0;	// L9831
  }
  uint8_t sb_id7[5];	// L9832
  #pragma HLS array_partition variable=sb_id7 complete dim=1

  for (int v6193 = 0; v6193 < 5; v6193++) {	// L9833
    sb_id7[v6193] = 0;	// L9833
  }
  uint8_t sb_rvld7[5];	// L9834
  #pragma HLS array_partition variable=sb_rvld7 complete dim=1

  for (int v6195 = 0; v6195 < 5; v6195++) {	// L9835
    sb_rvld7[v6195] = 0;	// L9835
  }
  uint8_t sb_ix7[5];	// L9836
  #pragma HLS array_partition variable=sb_ix7 complete dim=1

  for (int v6197 = 0; v6197 < 5; v6197++) {	// L9837
    sb_ix7[v6197] = 0;	// L9837
  }
  half resq7[8];	// L9838
  #pragma HLS array_partition variable=resq7 complete dim=1
#pragma HLS dependence variable=resq7 type=inter dependent=false

  for (int v6199 = 0; v6199 < 8; v6199++) {	// L9839
    resq7[v6199] = 0.000000;	// L9839
  }
  uint8_t cmpq7[8];	// L9840
  #pragma HLS array_partition variable=cmpq7 complete dim=1
#pragma HLS dependence variable=cmpq7 type=inter dependent=false

  for (int v6201 = 0; v6201 < 8; v6201++) {	// L9841
    cmpq7[v6201] = 0;	// L9841
  }
  uint8_t resq_wr7;	// L9842
  resq_wr7 = 0;	// L9843
  l_S_t_0_t7: for (int t7 = 0; t7 < 374; t7++) {	// L9844
  #pragma HLS pipeline II=1
    ap_uint<26> p_w7;	// L9845
    p_w7 = 0;	// L9846
    ap_uint<26> p_e7;	// L9847
    p_e7 = 0;	// L9848
    ap_uint<26> p_n7;	// L9849
    p_n7 = 0;	// L9850
    ap_uint<26> p_s7;	// L9851
    p_s7 = 0;	// L9852
    uint8_t v6208 = rbcnt7[0];	// L9853
    int32_t v6209 = v6208;	// L9854
    bool v6210 = v6209 < 2;	// L9855
    if (v6210) {	// L9856
      ap_uint<26> v6211;
      bool v6212 = v6125.read_nb(v6211);
	// L9857
      ap_uint<26> gw7;	// L9858
      gw7 = v6211;	// L9859
      bool okw7;	// L9860
      okw7 = v6212;	// L9861
      bool v6215 = okw7;	// L9862
      if (v6215) {	// L9863
        ap_int<26> v6216 = gw7;	// L9864
        p_w7 = v6216;	// L9865
      }
    }
    uint8_t v6217 = rbcnt7[1];	// L9868
    int32_t v6218 = v6217;	// L9869
    bool v6219 = v6218 < 2;	// L9870
    if (v6219) {	// L9871
      ap_uint<26> v6220;
      bool v6221 = v6126.read_nb(v6220);
	// L9872
      ap_uint<26> ge7;	// L9873
      ge7 = v6220;	// L9874
      bool oke7;	// L9875
      oke7 = v6221;	// L9876
      bool v6224 = oke7;	// L9877
      if (v6224) {	// L9878
        ap_int<26> v6225 = ge7;	// L9879
        p_e7 = v6225;	// L9880
      }
    }
    uint8_t v6226 = rbcnt7[2];	// L9883
    int32_t v6227 = v6226;	// L9884
    bool v6228 = v6227 < 2;	// L9885
    if (v6228) {	// L9886
      ap_uint<26> v6229;
      bool v6230 = v6127.read_nb(v6229);
	// L9887
      ap_uint<26> gn7;	// L9888
      gn7 = v6229;	// L9889
      bool okn7;	// L9890
      okn7 = v6230;	// L9891
      bool v6233 = okn7;	// L9892
      if (v6233) {	// L9893
        ap_int<26> v6234 = gn7;	// L9894
        p_n7 = v6234;	// L9895
      }
    }
    uint8_t v6235 = rbcnt7[3];	// L9898
    int32_t v6236 = v6235;	// L9899
    bool v6237 = v6236 < 2;	// L9900
    if (v6237) {	// L9901
      ap_uint<26> v6238;
      bool v6239 = v6128.read_nb(v6238);
	// L9902
      ap_uint<26> gs7;	// L9903
      gs7 = v6238;	// L9904
      bool oks7;	// L9905
      oks7 = v6239;	// L9906
      bool v6242 = oks7;	// L9907
      if (v6242) {	// L9908
        ap_int<26> v6243 = gs7;	// L9909
        p_s7 = v6243;	// L9910
      }
    }
    ap_uint<26> fin7[4];	// L9913
    for (int v6245 = 0; v6245 < 4; v6245++) {	// L9914
      fin7[v6245] = 0;	// L9914
    }
    ap_int<26> v6246 = p_w7;	// L9915
    fin7[0] = v6246;	// L9916
    ap_int<26> v6247 = p_e7;	// L9917
    fin7[1] = v6247;	// L9918
    ap_int<26> v6248 = p_n7;	// L9919
    fin7[2] = v6248;	// L9920
    ap_int<26> v6249 = p_s7;	// L9921
    fin7[3] = v6249;	// L9922
    l_S_d_0_d28: for (int d28 = 0; d28 < 4; d28++) {	// L9923
      ap_uint<26> v6251 = fin7[d28];	// L9924
      bool v6252;
      ap_int<26> v6252_tmp = v6251;
      v6252 = v6252_tmp[25];	// L9925
      int32_t v6253 = v6252;	// L9926
      bool v6254 = v6253 == 1;	// L9927
      uint8_t v6255 = rbcnt7[d28];	// L9928
      int32_t v6256 = v6255;	// L9929
      bool v6257 = v6256 < 2;	// L9930
      bool v6258 = v6254 & v6257;	// L9931
      if (v6258) {	// L9932
        ap_uint<26> v6259 = fin7[d28];	// L9933
        uint8_t v6260 = rbcnt7[d28];	// L9934
        int v6261 = v6260;	// L9935
        rbuf7[d28][v6261] = v6259;	// L9936
        uint8_t v6262 = rbcnt7[d28];	// L9937
        ap_int<33> v6263 = v6262;	// L9938
        ap_int<33> v6264 = v6263 + 1;	// L9939
        uint8_t v6265 = v6264;	// L9940
        rbcnt7[d28] = v6265;	// L9941
      }
    }
    ap_uint<26> hd7[4];	// L9944
    for (int v6267 = 0; v6267 < 4; v6267++) {	// L9945
      hd7[v6267] = 0;	// L9945
    }
    int32_t hvld7[4];	// L9946
    for (int v6269 = 0; v6269 < 4; v6269++) {	// L9947
      hvld7[v6269] = 0;	// L9947
    }
    int32_t hit7[4];	// L9948
    for (int v6271 = 0; v6271 < 4; v6271++) {	// L9949
      hit7[v6271] = 0;	// L9949
    }
    int32_t axis7[4];	// L9950
    for (int v6273 = 0; v6273 < 4; v6273++) {	// L9951
      axis7[v6273] = 0;	// L9951
    }
    int32_t v6274 = col_id7;	// L9952
    axis7[0] = v6274;	// L9953
    int32_t v6275 = col_id7;	// L9954
    axis7[1] = v6275;	// L9955
    int32_t v6276 = row_id7;	// L9956
    axis7[2] = v6276;	// L9957
    int32_t v6277 = row_id7;	// L9958
    axis7[3] = v6277;	// L9959
    l_S_d_1_d29: for (int d29 = 0; d29 < 4; d29++) {	// L9960
      uint8_t v6279 = rbcnt7[d29];	// L9961
      int32_t v6280 = v6279;	// L9962
      bool v6281 = v6280 > 0;	// L9963
      if (v6281) {	// L9964
        ap_uint<26> v6282 = rbuf7[d29][0];	// L9965
        hd7[d29] = v6282;	// L9966
        hvld7[d29] = 1;	// L9967
        ap_uint<26> v6283 = hd7[d29];	// L9968
        ap_int<4> v6284;
        ap_int<26> v6284_tmp = v6283;
        v6284 = v6284_tmp(24, 21);	// L9969
        int32_t v6285 = axis7[d29];	// L9970
        int32_t v6286 = v6284;	// L9971
        bool v6287 = v6286 == v6285;	// L9972
        if (v6287) {	// L9973
          hit7[d29] = 1;	// L9974
        }
      }
    }
    ap_uint<26> o_crv7;	// L9978
    o_crv7 = 0;	// L9979
    int32_t crv_in7;	// L9980
    crv_in7 = -1;	// L9981
    int32_t v6290 = hit7[3];	// L9982
    bool v6291 = v6290 == 1;	// L9983
    if (v6291) {	// L9984
      ap_uint<26> v6292 = hd7[3];	// L9985
      o_crv7 = v6292;	// L9986
      crv_in7 = 3;	// L9987
    } else {
      int32_t v6293 = hit7[2];	// L9989
      bool v6294 = v6293 == 1;	// L9990
      if (v6294) {	// L9991
        ap_uint<26> v6295 = hd7[2];	// L9992
        o_crv7 = v6295;	// L9993
        crv_in7 = 2;	// L9994
      } else {
        int32_t v6296 = hit7[1];	// L9996
        bool v6297 = v6296 == 1;	// L9997
        if (v6297) {	// L9998
          ap_uint<26> v6298 = hd7[1];	// L9999
          o_crv7 = v6298;	// L10000
          crv_in7 = 1;	// L10001
        } else {
          int32_t v6299 = hit7[0];	// L10003
          bool v6300 = v6299 == 1;	// L10004
          if (v6300) {	// L10005
            ap_uint<26> v6301 = hd7[0];	// L10006
            o_crv7 = v6301;	// L10007
            crv_in7 = 0;	// L10008
          }
        }
      }
    }
    int32_t pop7[4];	// L10013
    for (int v6303 = 0; v6303 < 4; v6303++) {	// L10014
      pop7[v6303] = 0;	// L10014
    }
    int32_t inj_done7;	// L10015
    inj_done7 = 0;	// L10016
    int32_t idir7;	// L10017
    idir7 = -1;	// L10018
    ap_int<26> v6306 = csd_pkt7;	// L10019
    bool v6307;
    ap_int<26> v6307_tmp = v6306;
    v6307 = v6307_tmp[25];	// L10020
    int32_t v6308 = v6307;	// L10021
    bool v6309 = v6308 == 1;	// L10022
    if (v6309) {	// L10023
      int32_t v6310 = csd_dir7;	// L10024
      ap_int<33> v6311 = v6310;	// L10025
      ap_int<33> v6312 = 3 - v6311;	// L10026
      int32_t v6313 = v6312;	// L10027
      idir7 = v6313;	// L10028
    }
    int32_t v6314 = idir7;	// L10030
    bool v6315 = v6314 == 0;	// L10031
    if (v6315) {	// L10032
      ap_int<26> v6316 = csd_pkt7;	// L10033
      bool v6317 = v6129.write_nb(v6316);
	// L10034
      if (v6317) {	// L10035
        inj_done7 = 1;	// L10036
      }
    } else {
      int32_t v6318 = hvld7[0];	// L10039
      bool v6319 = v6318 == 1;	// L10040
      int32_t v6320 = hit7[0];	// L10041
      bool v6321 = v6320 == 0;	// L10042
      bool v6322 = v6319 & v6321;	// L10043
      if (v6322) {	// L10044
        ap_uint<26> v6323 = hd7[0];	// L10045
        bool v6324 = v6129.write_nb(v6323);
	// L10046
        if (v6324) {	// L10047
          pop7[0] = 1;	// L10048
        }
      }
    }
    int32_t v6325 = idir7;	// L10052
    bool v6326 = v6325 == 1;	// L10053
    if (v6326) {	// L10054
      ap_int<26> v6327 = csd_pkt7;	// L10055
      bool v6328 = v6130.write_nb(v6327);
	// L10056
      if (v6328) {	// L10057
        inj_done7 = 1;	// L10058
      }
    } else {
      int32_t v6329 = hvld7[1];	// L10061
      bool v6330 = v6329 == 1;	// L10062
      int32_t v6331 = hit7[1];	// L10063
      bool v6332 = v6331 == 0;	// L10064
      bool v6333 = v6330 & v6332;	// L10065
      if (v6333) {	// L10066
        ap_uint<26> v6334 = hd7[1];	// L10067
        bool v6335 = v6130.write_nb(v6334);
	// L10068
        if (v6335) {	// L10069
          pop7[1] = 1;	// L10070
        }
      }
    }
    int32_t v6336 = idir7;	// L10074
    bool v6337 = v6336 == 2;	// L10075
    if (v6337) {	// L10076
      ap_int<26> v6338 = csd_pkt7;	// L10077
      bool v6339 = v6131.write_nb(v6338);
	// L10078
      if (v6339) {	// L10079
        inj_done7 = 1;	// L10080
      }
    } else {
      int32_t v6340 = hvld7[2];	// L10083
      bool v6341 = v6340 == 1;	// L10084
      int32_t v6342 = hit7[2];	// L10085
      bool v6343 = v6342 == 0;	// L10086
      bool v6344 = v6341 & v6343;	// L10087
      if (v6344) {	// L10088
        ap_uint<26> v6345 = hd7[2];	// L10089
        bool v6346 = v6131.write_nb(v6345);
	// L10090
        if (v6346) {	// L10091
          pop7[2] = 1;	// L10092
        }
      }
    }
    int32_t v6347 = idir7;	// L10096
    bool v6348 = v6347 == 3;	// L10097
    if (v6348) {	// L10098
      ap_int<26> v6349 = csd_pkt7;	// L10099
      bool v6350 = v6132.write_nb(v6349);
	// L10100
      if (v6350) {	// L10101
        inj_done7 = 1;	// L10102
      }
    } else {
      int32_t v6351 = hvld7[3];	// L10105
      bool v6352 = v6351 == 1;	// L10106
      int32_t v6353 = hit7[3];	// L10107
      bool v6354 = v6353 == 0;	// L10108
      bool v6355 = v6352 & v6354;	// L10109
      if (v6355) {	// L10110
        ap_uint<26> v6356 = hd7[3];	// L10111
        bool v6357 = v6132.write_nb(v6356);
	// L10112
        if (v6357) {	// L10113
          pop7[3] = 1;	// L10114
        }
      }
    }
    int32_t v6358 = crv_in7;	// L10118
    bool v6359 = v6358 >= 0;	// L10119
    if (v6359) {	// L10120
      int32_t v6360 = crv_in7;	// L10121
      int v6361 = v6360;	// L10122
      pop7[v6361] = 1;	// L10123
    }
    l_S_d_2_d30: for (int d30 = 0; d30 < 4; d30++) {	// L10125
      int32_t v6363 = pop7[d30];	// L10126
      bool v6364 = v6363 == 1;	// L10127
      if (v6364) {	// L10128
        l_S_sft_2_sft7: for (int sft7 = 0; sft7 < 1; sft7++) {	// L10129
          ap_uint<26> v6366 = rbuf7[d30][(sft7 + 1)];	// L10130
          rbuf7[d30][sft7] = v6366;	// L10131
        }
        uint8_t v6367 = rbcnt7[d30];	// L10133
        ap_int<33> v6368 = v6367;	// L10134
        ap_int<33> v6369 = v6368 - 1;	// L10135
        uint8_t v6370 = v6369;	// L10136
        rbcnt7[d30] = v6370;	// L10137
      }
    }
    int32_t v6371 = inj_done7;	// L10140
    bool v6372 = v6371 == 1;	// L10141
    if (v6372) {	// L10142
      csd_pkt7 = 0;	// L10143
    }
    ap_int<26> v6373 = o_crv7;	// L10145
    bool v6374;
    ap_int<26> v6374_tmp = v6373;
    v6374 = v6374_tmp[25];	// L10146
    int32_t v6375 = v6374;	// L10147
    crv_vld7 = v6375;	// L10148
    int32_t v6376 = crv_vld7;	// L10149
    bool v6377 = v6376 == 1;	// L10150
    if (v6377) {	// L10151
      crv_ever7 = 1;	// L10152
    }
    ap_int<26> v6378 = o_crv7;	// L10154
    int16_t v6379;
    ap_int<26> v6379_tmp = v6378;
    v6379 = v6379_tmp(15, 0);	// L10155
    half v6380;
    union { uint16_t from; half to;} _converter_v6379_to_v6380 = {};
    _converter_v6379_to_v6380.from = v6379;
    v6380 = _converter_v6379_to_v6380.to;	// L10156
    crv_data7 = v6380;	// L10157
    ap_int<26> v6381 = o_crv7;	// L10158
    ap_int<4> v6382;
    ap_int<26> v6382_tmp = v6381;
    v6382 = v6382_tmp(19, 16);	// L10159
    int32_t v6383 = v6382;	// L10160
    crv_addr7 = v6383;	// L10161
    ap_int<26> v6384 = o_crv7;	// L10162
    bool v6385;
    ap_int<26> v6385_tmp = v6384;
    v6385 = v6385_tmp[20];	// L10163
    int32_t v6386 = v6385;	// L10164
    crv_mode7 = v6386;	// L10165
    ap_int<26> v6387 = o_crv7;	// L10166
    int16_t v6388;
    ap_int<26> v6388_tmp = v6387;
    v6388 = v6388_tmp(15, 0);	// L10167
    int32_t v6389 = v6388;	// L10168
    crv_raw7 = v6389;	// L10169
    half rxv7[4];	// L10170
    for (int v6391 = 0; v6391 < 4; v6391++) {	// L10171
      rxv7[v6391] = 0.000000;	// L10171
    }
    int32_t rxvld7[4];	// L10172
    for (int v6393 = 0; v6393 < 4; v6393++) {	// L10173
      rxvld7[v6393] = 0;	// L10173
    }
    uint8_t v6394 = hold_cnt7[0];	// L10174
    int32_t v6395 = v6394;	// L10175
    bool v6396 = v6395 < 2;	// L10176
    if (v6396) {	// L10177
      ap_uint<17> v6397;
      bool v6398 = v6133.read_nb(v6397);
	// L10178
      ap_uint<17> sgn7;	// L10179
      sgn7 = v6397;	// L10180
      bool sqn7;	// L10181
      sqn7 = v6398;	// L10182
      bool v6401 = sqn7;	// L10183
      int32_t v6402 = v6401;	// L10184
      bool v6403 = v6402 == 1;	// L10185
      if (v6403) {	// L10186
        ap_int<17> v6404 = sgn7;	// L10187
        int16_t v6405;
        ap_int<17> v6405_tmp = v6404;
        v6405 = v6405_tmp(16, 1);	// L10188
        half v6406;
        union { uint16_t from; half to;} _converter_v6405_to_v6406 = {};
        _converter_v6405_to_v6406.from = v6405;
        v6406 = _converter_v6405_to_v6406.to;	// L10189
        rxv7[0] = v6406;	// L10190
        rxvld7[0] = 1;	// L10191
      }
    }
    uint8_t v6407 = hold_cnt7[1];	// L10194
    int32_t v6408 = v6407;	// L10195
    bool v6409 = v6408 < 2;	// L10196
    if (v6409) {	// L10197
      ap_uint<17> v6410;
      bool v6411 = v6134.read_nb(v6410);
	// L10198
      ap_uint<17> sgs7;	// L10199
      sgs7 = v6410;	// L10200
      bool sqs7;	// L10201
      sqs7 = v6411;	// L10202
      bool v6414 = sqs7;	// L10203
      int32_t v6415 = v6414;	// L10204
      bool v6416 = v6415 == 1;	// L10205
      if (v6416) {	// L10206
        ap_int<17> v6417 = sgs7;	// L10207
        int16_t v6418;
        ap_int<17> v6418_tmp = v6417;
        v6418 = v6418_tmp(16, 1);	// L10208
        half v6419;
        union { uint16_t from; half to;} _converter_v6418_to_v6419 = {};
        _converter_v6418_to_v6419.from = v6418;
        v6419 = _converter_v6418_to_v6419.to;	// L10209
        rxv7[1] = v6419;	// L10210
        rxvld7[1] = 1;	// L10211
      }
    }
    uint8_t v6420 = hold_cnt7[2];	// L10214
    int32_t v6421 = v6420;	// L10215
    bool v6422 = v6421 < 2;	// L10216
    if (v6422) {	// L10217
      ap_uint<17> v6423;
      bool v6424 = v6135.read_nb(v6423);
	// L10218
      ap_uint<17> sgw7;	// L10219
      sgw7 = v6423;	// L10220
      bool sqw7;	// L10221
      sqw7 = v6424;	// L10222
      bool v6427 = sqw7;	// L10223
      int32_t v6428 = v6427;	// L10224
      bool v6429 = v6428 == 1;	// L10225
      if (v6429) {	// L10226
        ap_int<17> v6430 = sgw7;	// L10227
        int16_t v6431;
        ap_int<17> v6431_tmp = v6430;
        v6431 = v6431_tmp(16, 1);	// L10228
        half v6432;
        union { uint16_t from; half to;} _converter_v6431_to_v6432 = {};
        _converter_v6431_to_v6432.from = v6431;
        v6432 = _converter_v6431_to_v6432.to;	// L10229
        rxv7[2] = v6432;	// L10230
        rxvld7[2] = 1;	// L10231
      }
    }
    uint8_t v6433 = hold_cnt7[3];	// L10234
    int32_t v6434 = v6433;	// L10235
    bool v6435 = v6434 < 2;	// L10236
    if (v6435) {	// L10237
      ap_uint<17> v6436;
      bool v6437 = v6136.read_nb(v6436);
	// L10238
      ap_uint<17> sge7;	// L10239
      sge7 = v6436;	// L10240
      bool sqe7;	// L10241
      sqe7 = v6437;	// L10242
      bool v6440 = sqe7;	// L10243
      int32_t v6441 = v6440;	// L10244
      bool v6442 = v6441 == 1;	// L10245
      if (v6442) {	// L10246
        ap_int<17> v6443 = sge7;	// L10247
        int16_t v6444;
        ap_int<17> v6444_tmp = v6443;
        v6444 = v6444_tmp(16, 1);	// L10248
        half v6445;
        union { uint16_t from; half to;} _converter_v6444_to_v6445 = {};
        _converter_v6444_to_v6445.from = v6444;
        v6445 = _converter_v6444_to_v6445.to;	// L10249
        rxv7[3] = v6445;	// L10250
        rxvld7[3] = 1;	// L10251
      }
    }
    l_S_d_4_d31: for (int d31 = 0; d31 < 4; d31++) {	// L10254
      int32_t v6447 = rxvld7[d31];	// L10255
      bool v6448 = v6447 == 1;	// L10256
      if (v6448) {	// L10257
        half v6449 = rxv7[d31];	// L10258
        uint8_t v6450 = hold_cnt7[d31];	// L10259
        int v6451 = v6450;	// L10260
        hold_v7[d31][v6451] = v6449;	// L10261
        uint8_t v6452 = hold_cnt7[d31];	// L10262
        ap_int<33> v6453 = v6452;	// L10263
        ap_int<33> v6454 = v6453 + 1;	// L10264
        uint8_t v6455 = v6454;	// L10265
        hold_cnt7[d31] = v6455;	// L10266
      }
    }
    ap_uint<17> tx_n7;	// L10269
    tx_n7 = 0;	// L10270
    ap_uint<17> tx_s7;	// L10271
    tx_s7 = 0;	// L10272
    ap_uint<17> tx_w7;	// L10273
    tx_w7 = 0;	// L10274
    ap_uint<17> tx_e7;	// L10275
    tx_e7 = 0;	// L10276
    uint8_t v6460 = sb_v7[0];	// L10277
    int32_t v6461 = v6460;	// L10278
    bool v6462 = v6461 == 1;	// L10279
    if (v6462) {	// L10280
      uint8_t v6463 = sb_ix7[0];	// L10281
      int v6464 = v6463;	// L10282
      half v6465 = resq7[v6464];	// L10283
      half wb7;
#pragma HLS dependence variable=wb7 type=inter dependent=false	// L10284
      wb7 = v6465;	// L10285
      uint8_t v6467 = sb_cmp7[0];	// L10286
      int32_t v6468 = v6467;	// L10287
      bool v6469 = v6468 == 1;	// L10288
      if (v6469) {	// L10289
        uint8_t v6470 = sb_ix7[0];	// L10290
        int v6471 = v6470;	// L10291
        uint8_t v6472 = cmpq7[v6471];	// L10292
        condition_reg7 = v6472;	// L10293
      }
      uint8_t v6473 = sb_rtr7[0];	// L10295
      int32_t v6474 = v6473;	// L10296
      bool v6475 = v6474 == 1;	// L10297
      if (v6475) {	// L10298
        uint8_t v6476 = sb_inj7[0];	// L10299
        int32_t v6477 = v6476;	// L10300
        bool v6478 = v6477 == 1;	// L10301
        ap_int<26> v6479 = csd_pkt7;	// L10302
        bool v6480;
        ap_int<26> v6480_tmp = v6479;
        v6480 = v6480_tmp[25];	// L10303
        int32_t v6481 = v6480;	// L10304
        bool v6482 = v6481 == 0;	// L10305
        bool v6483 = v6478 & v6482;	// L10306
        if (v6483) {	// L10307
          half v6484 = wb7;	// L10308
          uint16_t v6485;
          union { half from; uint16_t to;} _converter_v6484_to_v6485 = {};
          _converter_v6484_to_v6485.from = v6484;
          v6485 = _converter_v6484_to_v6485.to;	// L10309
          ap_int<26> v6486 = csd_pkt7;	// L10310
          ap_int<26> v6487;
          ap_int<26> v6487_tmp = v6486;
          v6487_tmp(15, 0) = v6485;
          v6487 = v6487_tmp;	// L10311
          csd_pkt7 = v6487;	// L10312
          uint8_t v6488 = sb_dst7[0];	// L10313
          ap_uint<4> v6489 = v6488;	// L10314
          ap_int<26> v6490 = csd_pkt7;	// L10315
          ap_int<26> v6491;
          ap_int<26> v6491_tmp = v6490;
          v6491_tmp(19, 16) = v6489;
          v6491 = v6491_tmp;	// L10316
          csd_pkt7 = v6491;	// L10317
          uint8_t v6492 = sb_id7[0];	// L10318
          ap_uint<4> v6493 = v6492;	// L10319
          ap_int<26> v6494 = csd_pkt7;	// L10320
          ap_int<26> v6495;
          ap_int<26> v6495_tmp = v6494;
          v6495_tmp(24, 21) = v6493;
          v6495 = v6495_tmp;	// L10321
          csd_pkt7 = v6495;	// L10322
          uint8_t v6496 = sb_rvld7[0];	// L10323
          bool v6497 = v6496;	// L10324
          ap_int<26> v6498 = csd_pkt7;	// L10325
          ap_int<26> v6499;
          ap_int<26> v6499_tmp = v6498;
          v6499_tmp[25] = v6497;          v6499 = v6499_tmp;	// L10326
          csd_pkt7 = v6499;	// L10327
          uint8_t v6500 = sb_dir7[0];	// L10328
          int32_t v6501 = v6500;	// L10329
          csd_dir7 = v6501;	// L10330
        }
      } else {
        uint8_t v6502 = sb_dst7[0];	// L10333
        int32_t v6503 = v6502;	// L10334
        bool v6504 = v6503 >= 12;	// L10335
        if (v6504) {	// L10336
          ap_uint<17> tw07;	// L10337
          tw07 = 0;	// L10338
          uint8_t v6506 = sb_rvld7[0];	// L10339
          bool v6507 = v6506;	// L10340
          ap_int<17> v6508 = tw07;	// L10341
          ap_int<17> v6509;
          ap_int<17> v6509_tmp = v6508;
          v6509_tmp[0] = v6507;          v6509 = v6509_tmp;	// L10342
          tw07 = v6509;	// L10343
          half v6510 = wb7;	// L10344
          uint16_t v6511;
          union { half from; uint16_t to;} _converter_v6510_to_v6511 = {};
          _converter_v6510_to_v6511.from = v6510;
          v6511 = _converter_v6510_to_v6511.to;	// L10345
          ap_int<17> v6512 = tw07;	// L10346
          ap_int<17> v6513;
          ap_int<17> v6513_tmp = v6512;
          v6513_tmp(16, 1) = v6511;
          v6513 = v6513_tmp;	// L10347
          tw07 = v6513;	// L10348
          uint8_t v6514 = sb_dst7[0];	// L10349
          int32_t v6515 = v6514;	// L10350
          int32_t v6516 = v6515 & 3;	// L10351
          bool v6517 = v6516 == 0;	// L10352
          if (v6517) {	// L10353
            ap_int<17> v6518 = tw07;	// L10354
            tx_n7 = v6518;	// L10355
          } else {
            uint8_t v6519 = sb_dst7[0];	// L10357
            int32_t v6520 = v6519;	// L10358
            int32_t v6521 = v6520 & 3;	// L10359
            bool v6522 = v6521 == 1;	// L10360
            if (v6522) {	// L10361
              ap_int<17> v6523 = tw07;	// L10362
              tx_s7 = v6523;	// L10363
            } else {
              uint8_t v6524 = sb_dst7[0];	// L10365
              int32_t v6525 = v6524;	// L10366
              int32_t v6526 = v6525 & 3;	// L10367
              bool v6527 = v6526 == 2;	// L10368
              if (v6527) {	// L10369
                ap_int<17> v6528 = tw07;	// L10370
                tx_w7 = v6528;	// L10371
              } else {
                ap_int<17> v6529 = tw07;	// L10373
                tx_e7 = v6529;	// L10374
              }
            }
          }
        } else {
          uint8_t v6530 = sb_rvld7[0];	// L10379
          int32_t v6531 = v6530;	// L10380
          bool v6532 = v6531 == 1;	// L10381
          if (v6532) {	// L10382
            uint8_t v6533 = sb_dst7[0];	// L10383
            int32_t v6534 = v6533;	// L10384
            bool v6535 = v6534 < 8;	// L10385
            int32_t v6536 = dsmask7;	// L10386
            int32_t v6537 = v6536 >> v6534;	// L10387
            int32_t v6538 = v6537 & 1;	// L10388
            bool v6539 = v6538 == 1;	// L10389
            bool v6540 = v6535 & v6539;	// L10390
            if (v6540) {	// L10391
              uint8_t v6541 = sb_dst7[0];	// L10392
              int v6542 = v6541;	// L10393
              int32_t v6543 = drf_full7[v6542];	// L10394
              bool v6544 = v6543 == 0;	// L10395
              if (v6544) {	// L10396
                half v6545 = wb7;	// L10397
                uint8_t v6546 = sb_dst7[0];	// L10398
                int v6547 = v6546;	// L10399
                drf7[v6547] = v6545;	// L10400
                uint8_t v6548 = sb_dst7[0];	// L10401
                int v6549 = v6548;	// L10402
                drf_full7[v6549] = 1;	// L10403
              }
            } else {
              half v6550 = wb7;	// L10406
              uint8_t v6551 = sb_dst7[0];	// L10407
              int32_t v6552 = v6551;	// L10408
              int32_t v6553 = v6552 & 7;	// L10409
              int v6554 = v6553;	// L10410
              drf7[v6554] = v6550;	// L10411
            }
          }
        }
      }
    }
    int32_t pc7;	// L10417
    pc7 = -1;	// L10418
    int8_t v6556 = fetch_en7;	// L10419
    int32_t v6557 = v6556;	// L10420
    bool v6558 = v6557 == 1;	// L10421
    if (v6558) {	// L10422
      int8_t v6559 = instr_cnt7;	// L10423
      int32_t v6560 = v6559;	// L10424
      pc7 = v6560;	// L10425
    }
    int8_t v6561 = fetch_en7;	// L10427
    int32_t v6562 = v6561;	// L10428
    bool v6563 = v6562 == 1;	// L10429
    if (v6563) {	// L10430
      fe_ever7 = 1;	// L10431
    }
    int32_t instr7;	// L10433
    instr7 = 0;	// L10434
    int32_t v6565 = pc7;	// L10435
    bool v6566 = v6565 >= 0;	// L10436
    if (v6566) {	// L10437
      int32_t v6567 = pc7;	// L10438
      int v6568 = v6567;	// L10439
      int32_t v6569 = irf7[v6568];	// L10440
      instr7 = v6569;	// L10441
    }
    int32_t v6570 = instr7;	// L10443
    int32_t v6571 = v6570 & 15;	// L10444
    int32_t op7;	// L10445
    op7 = v6571;	// L10446
    int32_t v6573 = instr7;	// L10447
    int32_t v6574 = v6573 >> 4;	// L10448
    int32_t v6575 = v6574 & 15;	// L10449
    int32_t dst7;	// L10450
    dst7 = v6575;	// L10451
    int32_t v6577 = instr7;	// L10452
    int32_t v6578 = v6577 >> 8;	// L10453
    int32_t v6579 = v6578 & 15;	// L10454
    int32_t s17;	// L10455
    s17 = v6579;	// L10456
    int32_t v6581 = instr7;	// L10457
    int32_t v6582 = v6581 >> 12;	// L10458
    int32_t v6583 = v6582 & 15;	// L10459
    int32_t s27;	// L10460
    s27 = v6583;	// L10461
    half a7;	// L10462
    a7 = 0.000000;	// L10463
    half b7;	// L10464
    b7 = 0.000000;	// L10465
    int32_t v6587 = s17;	// L10466
    bool v6588 = v6587 >= 12;	// L10467
    if (v6588) {	// L10468
      int32_t v6589 = s17;	// L10469
      int32_t v6590 = v6589 & 3;	// L10470
      int v6591 = v6590;	// L10471
      half v6592 = hold_v7[v6591][0];	// L10472
      a7 = v6592;	// L10473
    } else {
      int32_t v6593 = s17;	// L10475
      int v6594 = v6593;	// L10476
      half v6595 = drf7[v6594];	// L10477
      a7 = v6595;	// L10478
    }
    int32_t v6596 = s27;	// L10480
    bool v6597 = v6596 >= 12;	// L10481
    if (v6597) {	// L10482
      int32_t v6598 = s27;	// L10483
      int32_t v6599 = v6598 & 3;	// L10484
      int v6600 = v6599;	// L10485
      half v6601 = hold_v7[v6600][0];	// L10486
      b7 = v6601;	// L10487
    } else {
      int32_t v6602 = s27;	// L10489
      int v6603 = v6602;	// L10490
      half v6604 = drf7[v6603];	// L10491
      b7 = v6604;	// L10492
    }
    int32_t a_vld7;	// L10494
    a_vld7 = 1;	// L10495
    int32_t b_vld7;	// L10496
    b_vld7 = 1;	// L10497
    int32_t v6607 = s17;	// L10498
    bool v6608 = v6607 >= 12;	// L10499
    if (v6608) {	// L10500
      a_vld7 = 0;	// L10501
      int32_t v6609 = s17;	// L10502
      int32_t v6610 = v6609 & 3;	// L10503
      int v6611 = v6610;	// L10504
      uint8_t v6612 = hold_cnt7[v6611];	// L10505
      int32_t v6613 = v6612;	// L10506
      bool v6614 = v6613 > 0;	// L10507
      if (v6614) {	// L10508
        a_vld7 = 1;	// L10509
      }
    }
    int32_t v6615 = s27;	// L10512
    bool v6616 = v6615 >= 12;	// L10513
    if (v6616) {	// L10514
      b_vld7 = 0;	// L10515
      int32_t v6617 = s27;	// L10516
      int32_t v6618 = v6617 & 3;	// L10517
      int v6619 = v6618;	// L10518
      uint8_t v6620 = hold_cnt7[v6619];	// L10519
      int32_t v6621 = v6620;	// L10520
      bool v6622 = v6621 > 0;	// L10521
      if (v6622) {	// L10522
        b_vld7 = 1;	// L10523
      }
    }
    int32_t v6623 = s17;	// L10526
    bool v6624 = v6623 < 8;	// L10527
    int32_t v6625 = dsmask7;	// L10528
    int32_t v6626 = v6625 >> v6623;	// L10529
    int32_t v6627 = v6626 & 1;	// L10530
    bool v6628 = v6627 == 1;	// L10531
    bool v6629 = v6624 & v6628;	// L10532
    if (v6629) {	// L10533
      int32_t v6630 = s17;	// L10534
      int v6631 = v6630;	// L10535
      int32_t v6632 = drf_full7[v6631];	// L10536
      bool v6633 = v6632 == 0;	// L10537
      if (v6633) {	// L10538
        a_vld7 = 0;	// L10539
      }
    }
    int32_t v6634 = s27;	// L10542
    bool v6635 = v6634 < 8;	// L10543
    int32_t v6636 = dsmask7;	// L10544
    int32_t v6637 = v6636 >> v6634;	// L10545
    int32_t v6638 = v6637 & 1;	// L10546
    bool v6639 = v6638 == 1;	// L10547
    bool v6640 = v6635 & v6639;	// L10548
    if (v6640) {	// L10549
      int32_t v6641 = s27;	// L10550
      int v6642 = v6641;	// L10551
      int32_t v6643 = drf_full7[v6642];	// L10552
      bool v6644 = v6643 == 0;	// L10553
      if (v6644) {	// L10554
        b_vld7 = 0;	// L10555
      }
    }
    int32_t binop7;	// L10558
    binop7 = 0;	// L10559
    int32_t v6646 = op7;	// L10560
    bool v6647 = v6646 == 0;	// L10561
    bool v6648 = v6646 == 1;	// L10562
    bool v6649 = v6646 == 2;	// L10563
    bool v6650 = v6646 == 8;	// L10564
    bool v6651 = v6646 == 9;	// L10565
    bool v6652 = v6647 | v6648;	// L10566
    bool v6653 = v6652 | v6649;	// L10567
    bool v6654 = v6653 | v6650;	// L10568
    bool v6655 = v6654 | v6651;	// L10569
    if (v6655) {	// L10570
      binop7 = 1;	// L10571
    }
    int32_t raw7;	// L10573
    raw7 = 0;	// L10574
    int32_t cmp_busy7;	// L10575
    cmp_busy7 = 0;	// L10576
    l_S_k_5_k14: for (int k14 = 0; k14 < 4; k14++) {	// L10577
      uint8_t v6659 = sb_v7[(k14 + 1)];	// L10578
      int32_t v6660 = v6659;	// L10579
      bool v6661 = v6660 == 1;	// L10580
      uint8_t v6662 = sb_rtr7[(k14 + 1)];	// L10581
      int32_t v6663 = v6662;	// L10582
      bool v6664 = v6663 == 0;	// L10583
      uint8_t v6665 = sb_dst7[(k14 + 1)];	// L10584
      int32_t v6666 = v6665;	// L10585
      bool v6667 = v6666 < 12;	// L10586
      bool v6668 = v6661 & v6664;	// L10587
      bool v6669 = v6668 & v6667;	// L10588
      if (v6669) {	// L10589
        int32_t v6670 = s17;	// L10590
        bool v6671 = v6670 < 12;	// L10591
        uint8_t v6672 = sb_dst7[(k14 + 1)];	// L10592
        int32_t v6673 = v6672;	// L10593
        int32_t v6674 = v6673 & 7;	// L10594
        int32_t v6675 = v6670 & 7;	// L10595
        bool v6676 = v6674 == v6675;	// L10596
        bool v6677 = v6671 & v6676;	// L10597
        if (v6677) {	// L10598
          raw7 = 1;	// L10599
        }
        int32_t v6678 = binop7;	// L10601
        bool v6679 = v6678 == 1;	// L10602
        int32_t v6680 = s27;	// L10603
        bool v6681 = v6680 < 12;	// L10604
        uint8_t v6682 = sb_dst7[(k14 + 1)];	// L10605
        int32_t v6683 = v6682;	// L10606
        int32_t v6684 = v6683 & 7;	// L10607
        int32_t v6685 = v6680 & 7;	// L10608
        bool v6686 = v6684 == v6685;	// L10609
        bool v6687 = v6679 & v6681;	// L10610
        bool v6688 = v6687 & v6686;	// L10611
        if (v6688) {	// L10612
          raw7 = 1;	// L10613
        }
      }
      uint8_t v6689 = sb_v7[(k14 + 1)];	// L10616
      int32_t v6690 = v6689;	// L10617
      bool v6691 = v6690 == 1;	// L10618
      uint8_t v6692 = sb_cmp7[(k14 + 1)];	// L10619
      int32_t v6693 = v6692;	// L10620
      bool v6694 = v6693 == 1;	// L10621
      bool v6695 = v6691 & v6694;	// L10622
      if (v6695) {	// L10623
        cmp_busy7 = 1;	// L10624
      }
    }
    int32_t is_cond7;	// L10627
    is_cond7 = 0;	// L10628
    int32_t v6697 = op7;	// L10629
    bool v6698 = v6697 >= 12;	// L10630
    ap_int<33> v6699 = v6697;	// L10631
    bool v6700 = v6699 <= 15;	// L10632
    bool v6701 = v6698 & v6700;	// L10633
    if (v6701) {	// L10634
      is_cond7 = 1;	// L10635
    }
    int32_t grant7;	// L10637
    grant7 = 0;	// L10638
    int32_t v6703 = pc7;	// L10639
    bool v6704 = v6703 >= 0;	// L10640
    if (v6704) {	// L10641
      grant7 = 1;	// L10642
    }
    int32_t v6705 = pc7;	// L10644
    bool v6706 = v6705 >= 0;	// L10645
    int32_t v6707 = a_vld7;	// L10646
    bool v6708 = v6707 == 0;	// L10647
    int32_t v6709 = binop7;	// L10648
    bool v6710 = v6709 == 1;	// L10649
    int32_t v6711 = b_vld7;	// L10650
    bool v6712 = v6711 == 0;	// L10651
    bool v6713 = v6710 & v6712;	// L10652
    bool v6714 = v6708 | v6713;	// L10653
    bool v6715 = v6706 & v6714;	// L10654
    if (v6715) {	// L10655
      grant7 = 0;	// L10656
    }
    int32_t v6716 = pc7;	// L10658
    bool v6717 = v6716 >= 0;	// L10659
    int32_t v6718 = raw7;	// L10660
    bool v6719 = v6718 == 1;	// L10661
    int32_t v6720 = is_cond7;	// L10662
    bool v6721 = v6720 == 1;	// L10663
    int32_t v6722 = cmp_busy7;	// L10664
    bool v6723 = v6722 == 1;	// L10665
    bool v6724 = v6721 & v6723;	// L10666
    bool v6725 = v6719 | v6724;	// L10667
    bool v6726 = v6717 & v6725;	// L10668
    if (v6726) {	// L10669
      grant7 = 0;	// L10670
    }
    int32_t v6727 = grant7;	// L10672
    bool v6728 = v6727 == 1;	// L10673
    if (v6728) {	// L10674
      int8_t v6729 = instr_cnt7;	// L10675
      int32_t v6730 = cfg_isz7;	// L10676
      int32_t v6731 = v6729;	// L10677
      bool v6732 = v6731 == v6730;	// L10678
      if (v6732) {	// L10679
        instr_cnt7 = 0;	// L10680
        int8_t v6733 = iter_cnt7;	// L10681
        int32_t v6734 = cfg_itsz7;	// L10682
        ap_int<33> v6735 = v6734;	// L10683
        ap_int<33> v6736 = v6735 - 1;	// L10684
        ap_int<33> v6737 = v6733;	// L10685
        bool v6738 = v6737 == v6736;	// L10686
        if (v6738) {	// L10687
          fetch_en7 = 0;	// L10688
        } else {
          int8_t v6739 = iter_cnt7;	// L10690
          ap_int<33> v6740 = v6739;	// L10691
          ap_int<33> v6741 = v6740 + 1;	// L10692
          uint8_t v6742 = v6741;	// L10693
          iter_cnt7 = v6742;	// L10694
        }
      } else {
        int8_t v6743 = instr_cnt7;	// L10697
        ap_int<33> v6744 = v6743;	// L10698
        ap_int<33> v6745 = v6744 + 1;	// L10699
        uint8_t v6746 = v6745;	// L10700
        instr_cnt7 = v6746;	// L10701
      }
    }
    int32_t c17;	// L10704
    c17 = -1;	// L10705
    int32_t c27;	// L10706
    c27 = -1;	// L10707
    int32_t v6749 = grant7;	// L10708
    bool v6750 = v6749 == 1;	// L10709
    int32_t v6751 = s17;	// L10710
    bool v6752 = v6751 >= 12;	// L10711
    bool v6753 = v6750 & v6752;	// L10712
    if (v6753) {	// L10713
      int32_t v6754 = s17;	// L10714
      int32_t v6755 = v6754 & 3;	// L10715
      c17 = v6755;	// L10716
    }
    int32_t v6756 = grant7;	// L10718
    bool v6757 = v6756 == 1;	// L10719
    int32_t v6758 = s27;	// L10720
    bool v6759 = v6758 >= 12;	// L10721
    bool v6760 = v6757 & v6759;	// L10722
    if (v6760) {	// L10723
      int32_t v6761 = s27;	// L10724
      int32_t v6762 = v6761 & 3;	// L10725
      c27 = v6762;	// L10726
    }
    int32_t v6763 = c17;	// L10728
    bool v6764 = v6763 >= 0;	// L10729
    if (v6764) {	// L10730
      int32_t v6765 = c17;	// L10731
      int v6766 = v6765;	// L10732
      half v6767 = hold_v7[v6766][1];	// L10733
      hold_v7[v6766][0] = v6767;	// L10734
      int32_t v6768 = c17;	// L10735
      int v6769 = v6768;	// L10736
      uint8_t v6770 = hold_cnt7[v6769];	// L10737
      ap_int<33> v6771 = v6770;	// L10738
      ap_int<33> v6772 = v6771 - 1;	// L10739
      uint8_t v6773 = v6772;	// L10740
      hold_cnt7[v6769] = v6773;	// L10741
    }
    int32_t v6774 = c27;	// L10743
    bool v6775 = v6774 >= 0;	// L10744
    int32_t v6776 = c17;	// L10745
    bool v6777 = v6774 != v6776;	// L10746
    bool v6778 = v6775 & v6777;	// L10747
    if (v6778) {	// L10748
      int32_t v6779 = c27;	// L10749
      int v6780 = v6779;	// L10750
      half v6781 = hold_v7[v6780][1];	// L10751
      hold_v7[v6780][0] = v6781;	// L10752
      int32_t v6782 = c27;	// L10753
      int v6783 = v6782;	// L10754
      uint8_t v6784 = hold_cnt7[v6783];	// L10755
      ap_int<33> v6785 = v6784;	// L10756
      ap_int<33> v6786 = v6785 - 1;	// L10757
      uint8_t v6787 = v6786;	// L10758
      hold_cnt7[v6783] = v6787;	// L10759
    }
    int32_t v6788 = grant7;	// L10761
    bool v6789 = v6788 == 1;	// L10762
    int32_t v6790 = s17;	// L10763
    bool v6791 = v6790 < 8;	// L10764
    int32_t v6792 = dsmask7;	// L10765
    int32_t v6793 = v6792 >> v6790;	// L10766
    int32_t v6794 = v6793 & 1;	// L10767
    bool v6795 = v6794 == 1;	// L10768
    bool v6796 = v6789 & v6791;	// L10769
    bool v6797 = v6796 & v6795;	// L10770
    if (v6797) {	// L10771
      int32_t v6798 = s17;	// L10772
      int v6799 = v6798;	// L10773
      drf_full7[v6799] = 0;	// L10774
    }
    int32_t v6800 = grant7;	// L10776
    bool v6801 = v6800 == 1;	// L10777
    int32_t v6802 = s27;	// L10778
    bool v6803 = v6802 < 8;	// L10779
    int32_t v6804 = dsmask7;	// L10780
    int32_t v6805 = v6804 >> v6802;	// L10781
    int32_t v6806 = v6805 & 1;	// L10782
    bool v6807 = v6806 == 1;	// L10783
    bool v6808 = v6801 & v6803;	// L10784
    bool v6809 = v6808 & v6807;	// L10785
    if (v6809) {	// L10786
      int32_t v6810 = s27;	// L10787
      int v6811 = v6810;	// L10788
      drf_full7[v6811] = 0;	// L10789
    }
    half res7;
#pragma HLS dependence variable=res7 type=inter dependent=false	// L10791
    res7 = 0.000000;	// L10792
    int32_t v6813 = op7;	// L10793
    bool v6814 = v6813 == 0;	// L10794
    if (v6814) {	// L10795
      half v6815 = a7;	// L10796
      half v6816 = b7;	// L10797
      half v6817 = v6815 + v6816;	// L10798
      res7 = v6817;	// L10799
    } else {
      int32_t v6818 = op7;	// L10801
      bool v6819 = v6818 == 1;	// L10802
      if (v6819) {	// L10803
        half v6820 = a7;	// L10804
        half v6821 = b7;	// L10805
        half v6822 = v6820 - v6821;	// L10806
        res7 = v6822;	// L10807
      } else {
        int32_t v6823 = op7;	// L10809
        bool v6824 = v6823 == 2;	// L10810
        if (v6824) {	// L10811
          half v6825 = a7;	// L10812
          half v6826 = b7;	// L10813
          half v6827 = v6825 * v6826;	// L10814
          res7 = v6827;	// L10815
        } else {
          int32_t v6828 = op7;	// L10817
          bool v6829 = v6828 == 8;	// L10818
          if (v6829) {	// L10819
            half v6830 = a7;	// L10820
            half v6831 = b7;	// L10821
            bool v6832 = v6830 >= v6831;	// L10822
            if (v6832) {	// L10823
              res7 = 1.000000;	// L10824
            } else {
              res7 = -1.000000;	// L10826
            }
          } else {
            int32_t v6833 = op7;	// L10829
            bool v6834 = v6833 == 9;	// L10830
            if (v6834) {	// L10831
              half v6835 = a7;	// L10832
              half v6836 = b7;	// L10833
              bool v6837 = v6835 < v6836;	// L10834
              if (v6837) {	// L10835
                res7 = 1.000000;	// L10836
              } else {
                res7 = -1.000000;	// L10838
              }
            } else {
              half v6838 = a7;	// L10841
              res7 = v6838;	// L10842
            }
          }
        }
      }
    }
    int32_t v6839 = a_vld7;	// L10848
    int32_t res_vld7;	// L10849
    res_vld7 = v6839;	// L10850
    int32_t v6841 = op7;	// L10851
    bool v6842 = v6841 == 0;	// L10852
    bool v6843 = v6841 == 1;	// L10853
    bool v6844 = v6841 == 2;	// L10854
    bool v6845 = v6841 == 8;	// L10855
    bool v6846 = v6841 == 9;	// L10856
    bool v6847 = v6842 | v6843;	// L10857
    bool v6848 = v6847 | v6844;	// L10858
    bool v6849 = v6848 | v6845;	// L10859
    bool v6850 = v6849 | v6846;	// L10860
    if (v6850) {	// L10861
      int32_t v6851 = a_vld7;	// L10862
      int32_t v6852 = b_vld7;	// L10863
      int64_t v6853 = v6851;	// L10864
      int64_t v6854 = v6852;	// L10865
      int64_t v6855 = v6853 * v6854;	// L10866
      int32_t v6856 = v6855;	// L10867
      res_vld7 = v6856;	// L10868
    }
    int32_t v6857 = grant7;	// L10870
    bool v6858 = v6857 == 0;	// L10871
    if (v6858) {	// L10872
      res_vld7 = 0;	// L10873
    }
    int32_t is_rtr7;	// L10875
    is_rtr7 = 0;	// L10876
    int32_t v6860 = op7;	// L10877
    bool v6861 = v6860 >= 4;	// L10878
    ap_int<33> v6862 = v6860;	// L10879
    bool v6863 = v6862 <= 7;	// L10880
    bool v6864 = v6861 & v6863;	// L10881
    if (v6864) {	// L10882
      is_rtr7 = 1;	// L10883
    }
    l_S_k_6_k15: for (int k15 = 0; k15 < 4; k15++) {	// L10885
      uint8_t v6866 = sb_v7[(k15 + 1)];	// L10886
      sb_v7[k15] = v6866;	// L10887
      uint8_t v6867 = sb_dst7[(k15 + 1)];	// L10888
      sb_dst7[k15] = v6867;	// L10889
      uint8_t v6868 = sb_cmp7[(k15 + 1)];	// L10890
      sb_cmp7[k15] = v6868;	// L10891
      uint8_t v6869 = sb_rtr7[(k15 + 1)];	// L10892
      sb_rtr7[k15] = v6869;	// L10893
      uint8_t v6870 = sb_inj7[(k15 + 1)];	// L10894
      sb_inj7[k15] = v6870;	// L10895
      uint8_t v6871 = sb_dir7[(k15 + 1)];	// L10896
      sb_dir7[k15] = v6871;	// L10897
      uint8_t v6872 = sb_id7[(k15 + 1)];	// L10898
      sb_id7[k15] = v6872;	// L10899
      uint8_t v6873 = sb_rvld7[(k15 + 1)];	// L10900
      sb_rvld7[k15] = v6873;	// L10901
      uint8_t v6874 = sb_ix7[(k15 + 1)];	// L10902
      sb_ix7[k15] = v6874;	// L10903
    }
    sb_v7[4] = 0;	// L10905
    int32_t v6875 = grant7;	// L10906
    bool v6876 = v6875 == 1;	// L10907
    if (v6876) {	// L10908
      half v6877 = res7;	// L10909
      int8_t v6878 = resq_wr7;	// L10910
      int v6879 = v6878;	// L10911
      resq7[v6879] = v6877;	// L10912
      int32_t cq7;	// L10913
      cq7 = 0;	// L10914
      int32_t v6881 = op7;	// L10915
      bool v6882 = v6881 == 8;	// L10916
      if (v6882) {	// L10917
        half v6883 = a7;	// L10918
        half v6884 = b7;	// L10919
        bool v6885 = v6883 >= v6884;	// L10920
        if (v6885) {	// L10921
          cq7 = 1;	// L10922
        }
      }
      int32_t v6886 = op7;	// L10925
      bool v6887 = v6886 == 9;	// L10926
      if (v6887) {	// L10927
        half v6888 = a7;	// L10928
        half v6889 = b7;	// L10929
        bool v6890 = v6888 < v6889;	// L10930
        if (v6890) {	// L10931
          cq7 = 1;	// L10932
        }
      }
      int32_t v6891 = cq7;	// L10935
      uint8_t v6892 = v6891;	// L10936
      int8_t v6893 = resq_wr7;	// L10937
      int v6894 = v6893;	// L10938
      cmpq7[v6894] = v6892;	// L10939
      sb_v7[4] = 1;	// L10940
      int32_t v6895 = dst7;	// L10941
      uint8_t v6896 = v6895;	// L10942
      sb_dst7[4] = v6896;	// L10943
      int8_t v6897 = resq_wr7;	// L10944
      sb_ix7[4] = v6897;	// L10945
      sb_cmp7[4] = 0;	// L10946
      int32_t v6898 = op7;	// L10947
      bool v6899 = v6898 == 8;	// L10948
      bool v6900 = v6898 == 9;	// L10949
      bool v6901 = v6899 | v6900;	// L10950
      if (v6901) {	// L10951
        sb_cmp7[4] = 1;	// L10952
      }
      int32_t v6902 = is_rtr7;	// L10954
      int32_t rtrf7;	// L10955
      rtrf7 = v6902;	// L10956
      int32_t v6904 = is_cond7;	// L10957
      bool v6905 = v6904 == 1;	// L10958
      if (v6905) {	// L10959
        rtrf7 = 1;	// L10960
      }
      int32_t v6906 = rtrf7;	// L10962
      uint8_t v6907 = v6906;	// L10963
      sb_rtr7[4] = v6907;	// L10964
      int32_t v6908 = is_rtr7;	// L10965
      int32_t inj7;	// L10966
      inj7 = v6908;	// L10967
      int32_t v6910 = is_cond7;	// L10968
      bool v6911 = v6910 == 1;	// L10969
      int8_t v6912 = condition_reg7;	// L10970
      int32_t v6913 = v6912;	// L10971
      bool v6914 = v6913 == 1;	// L10972
      bool v6915 = v6911 & v6914;	// L10973
      if (v6915) {	// L10974
        inj7 = 1;	// L10975
      }
      int32_t v6916 = inj7;	// L10977
      uint8_t v6917 = v6916;	// L10978
      sb_inj7[4] = v6917;	// L10979
      int32_t v6918 = op7;	// L10980
      int32_t v6919 = v6918 & 3;	// L10981
      uint8_t v6920 = v6919;	// L10982
      sb_dir7[4] = v6920;	// L10983
      int32_t v6921 = s27;	// L10984
      uint8_t v6922 = v6921;	// L10985
      sb_id7[4] = v6922;	// L10986
      int32_t v6923 = res_vld7;	// L10987
      uint8_t v6924 = v6923;	// L10988
      sb_rvld7[4] = v6924;	// L10989
      int8_t v6925 = resq_wr7;	// L10990
      ap_int<33> v6926 = v6925;	// L10991
      ap_int<33> v6927 = v6926 + 1;	// L10992
      ap_int<33> v6928 = v6927 & 7;	// L10993
      uint8_t v6929 = v6928;	// L10994
      resq_wr7 = v6929;	// L10995
    }
    ap_int<17> v6930 = tx_n7;	// L10997
    txn_r7 = v6930;	// L10998
    ap_int<17> v6931 = tx_s7;	// L10999
    txs_r7 = v6931;	// L11000
    ap_int<17> v6932 = tx_w7;	// L11001
    txw_r7 = v6932;	// L11002
    ap_int<17> v6933 = tx_e7;	// L11003
    txe_r7 = v6933;	// L11004
    int32_t v6934 = crv_vld7;	// L11005
    bool v6935 = v6934 == 1;	// L11006
    if (v6935) {	// L11007
      int32_t v6936 = crv_mode7;	// L11008
      bool v6937 = v6936 == 1;	// L11009
      if (v6937) {	// L11010
        int32_t v6938 = crv_addr7;	// L11011
        int32_t v6939 = v6938 >> 3;	// L11012
        int32_t v6940 = v6939 & 1;	// L11013
        bool v6941 = v6940 == 1;	// L11014
        if (v6941) {	// L11015
          int32_t v6942 = crv_raw7;	// L11016
          int32_t v6943 = crv_addr7;	// L11017
          int32_t v6944 = v6943 & 7;	// L11018
          int v6945 = v6944;	// L11019
          irf7[v6945] = v6942;	// L11020
        } else {
          int32_t v6946 = crv_addr7;	// L11022
          bool v6947 = v6946 == 0;	// L11023
          if (v6947) {	// L11024
            int32_t v6948 = crv_raw7;	// L11025
            int32_t v6949 = v6948 & 255;	// L11026
            dsmask7 = v6949;	// L11027
            int32_t v6950 = crv_raw7;	// L11028
            int32_t v6951 = v6950 >> 8;	// L11029
            int32_t v6952 = v6951 & 7;	// L11030
            cfg_isz7 = v6952;	// L11031
            int32_t v6953 = crv_raw7;	// L11032
            int32_t v6954 = v6953 >> 15;	// L11033
            int32_t v6955 = v6954 & 1;	// L11034
            bool v6956 = v6955 == 1;	// L11035
            if (v6956) {	// L11036
              fetch_en7 = 1;	// L11037
              instr_cnt7 = 0;	// L11038
              iter_cnt7 = 0;	// L11039
            }
          } else {
            int32_t v6957 = crv_addr7;	// L11042
            bool v6958 = v6957 == 1;	// L11043
            if (v6958) {	// L11044
              int32_t v6959 = crv_raw7;	// L11045
              int32_t v6960 = v6959 & 255;	// L11046
              cfg_itsz7 = v6960;	// L11047
            }
          }
        }
      } else {
        int32_t v6961 = crv_addr7;	// L11052
        bool v6962 = v6961 < 8;	// L11053
        int32_t v6963 = dsmask7;	// L11054
        int32_t v6964 = v6963 >> v6961;	// L11055
        int32_t v6965 = v6964 & 1;	// L11056
        bool v6966 = v6965 == 1;	// L11057
        bool v6967 = v6962 & v6966;	// L11058
        if (v6967) {	// L11059
          int32_t v6968 = crv_addr7;	// L11060
          int v6969 = v6968;	// L11061
          int32_t v6970 = drf_full7[v6969];	// L11062
          bool v6971 = v6970 == 0;	// L11063
          if (v6971) {	// L11064
            half v6972 = crv_data7;	// L11065
            int32_t v6973 = crv_addr7;	// L11066
            int v6974 = v6973;	// L11067
            drf7[v6974] = v6972;	// L11068
            int32_t v6975 = crv_addr7;	// L11069
            int v6976 = v6975;	// L11070
            drf_full7[v6976] = 1;	// L11071
          }
        } else {
          half v6977 = crv_data7;	// L11074
          int32_t v6978 = crv_addr7;	// L11075
          int v6979 = v6978;	// L11076
          drf7[v6979] = v6977;	// L11077
        }
      }
    }
    ap_int<17> v6980 = txe_r7;	// L11081
    bool v6981;
    ap_int<17> v6981_tmp = v6980;
    v6981 = v6981_tmp[0];	// L11082
    int32_t v6982 = v6981;	// L11083
    bool v6983 = v6982 == 1;	// L11084
    if (v6983) {	// L11085
      ap_int<17> v6984 = txe_r7;	// L11086
      v6137.write(v6984);	// L11087
    }
    ap_int<17> v6985 = txw_r7;	// L11089
    bool v6986;
    ap_int<17> v6986_tmp = v6985;
    v6986 = v6986_tmp[0];	// L11090
    int32_t v6987 = v6986;	// L11091
    bool v6988 = v6987 == 1;	// L11092
    if (v6988) {	// L11093
      ap_int<17> v6989 = txw_r7;	// L11094
      v6138.write(v6989);	// L11095
    }
    ap_int<17> v6990 = txs_r7;	// L11097
    bool v6991;
    ap_int<17> v6991_tmp = v6990;
    v6991 = v6991_tmp[0];	// L11098
    int32_t v6992 = v6991;	// L11099
    bool v6993 = v6992 == 1;	// L11100
    if (v6993) {	// L11101
      ap_int<17> v6994 = txs_r7;	// L11102
      v6139.write(v6994);	// L11103
    }
    ap_int<17> v6995 = txn_r7;	// L11105
    bool v6996;
    ap_int<17> v6996_tmp = v6995;
    v6996 = v6996_tmp[0];	// L11106
    int32_t v6997 = v6996;	// L11107
    bool v6998 = v6997 == 1;	// L11108
    if (v6998) {	// L11109
      ap_int<17> v6999 = txn_r7;	// L11110
      v6140.write(v6999);	// L11111
    }
  }
}

void node_2_0(
  hls::stream< ap_uint<26> >& v7000,
  hls::stream< ap_uint<26> >& v7001,
  hls::stream< ap_uint<26> >& v7002,
  hls::stream< ap_uint<26> >& v7003,
  hls::stream< ap_uint<26> >& v7004,
  hls::stream< ap_uint<26> >& v7005,
  hls::stream< ap_uint<26> >& v7006,
  hls::stream< ap_uint<26> >& v7007,
  hls::stream< ap_uint<17> >& v7008,
  hls::stream< ap_uint<17> >& v7009,
  hls::stream< ap_uint<17> >& v7010,
  hls::stream< ap_uint<17> >& v7011,
  hls::stream< ap_uint<17> >& v7012,
  hls::stream< ap_uint<17> >& v7013,
  hls::stream< ap_uint<17> >& v7014,
  hls::stream< ap_uint<17> >& v7015
) {	// L11116
  int32_t irf8[8];	// L11149
  #pragma HLS array_partition variable=irf8 complete dim=1

  for (int v7017 = 0; v7017 < 8; v7017++) {	// L11150
    irf8[v7017] = 0;	// L11150
  }
  half drf8[8];	// L11151
  #pragma HLS array_partition variable=drf8 complete dim=1

  for (int v7019 = 0; v7019 < 8; v7019++) {	// L11152
    drf8[v7019] = 0.000000;	// L11152
  }
  int32_t drf_full8[8];	// L11153
  #pragma HLS array_partition variable=drf_full8 complete dim=1

  for (int v7021 = 0; v7021 < 8; v7021++) {	// L11154
    drf_full8[v7021] = 0;	// L11154
  }
  int32_t dsmask8;	// L11155
  dsmask8 = 0;	// L11156
  int32_t crv_vld8;	// L11157
  crv_vld8 = 0;	// L11158
  half crv_data8;	// L11159
  crv_data8 = 0.000000;	// L11160
  int32_t crv_addr8;	// L11161
  crv_addr8 = 0;	// L11162
  int32_t crv_mode8;	// L11163
  crv_mode8 = 0;	// L11164
  int32_t crv_raw8;	// L11165
  crv_raw8 = 0;	// L11166
  int32_t csd_vld8;	// L11167
  csd_vld8 = 0;	// L11168
  ap_uint<26> csd_pkt8;	// L11169
  csd_pkt8 = 0;	// L11170
  int32_t csd_dir8;	// L11171
  csd_dir8 = 0;	// L11172
  int32_t row_id8;	// L11173
  row_id8 = 2;	// L11174
  int32_t col_id8;	// L11175
  col_id8 = 0;	// L11176
  ap_uint<17> txn_r8;	// L11177
  txn_r8 = 0;	// L11178
  ap_uint<17> txs_r8;	// L11179
  txs_r8 = 0;	// L11180
  ap_uint<17> txw_r8;	// L11181
  txw_r8 = 0;	// L11182
  ap_uint<17> txe_r8;	// L11183
  txe_r8 = 0;	// L11184
  half hold_v8[4][2];	// L11185
  #pragma HLS array_partition variable=hold_v8 complete dim=1
  #pragma HLS array_partition variable=hold_v8 complete dim=2

  for (int v7038 = 0; v7038 < 4; v7038++) {	// L11186
    for (int v7039 = 0; v7039 < 2; v7039++) {	// L11186
      hold_v8[v7038][v7039] = 0.000000;	// L11186
    }
  }
  uint8_t hold_cnt8[4];	// L11187
  #pragma HLS array_partition variable=hold_cnt8 complete dim=1

  for (int v7041 = 0; v7041 < 4; v7041++) {	// L11188
    hold_cnt8[v7041] = 0;	// L11188
  }
  int32_t crv_ever8;	// L11189
  crv_ever8 = 0;	// L11190
  int32_t fe_ever8;	// L11191
  fe_ever8 = 0;	// L11192
  ap_uint<26> rbuf8[4][2];	// L11193
  #pragma HLS array_partition variable=rbuf8 complete dim=1
  #pragma HLS array_partition variable=rbuf8 complete dim=2

  for (int v7045 = 0; v7045 < 4; v7045++) {	// L11194
    for (int v7046 = 0; v7046 < 2; v7046++) {	// L11194
      rbuf8[v7045][v7046] = 0;	// L11194
    }
  }
  uint8_t rbcnt8[4];	// L11195
  #pragma HLS array_partition variable=rbcnt8 complete dim=1

  for (int v7048 = 0; v7048 < 4; v7048++) {	// L11196
    rbcnt8[v7048] = 0;	// L11196
  }
  int32_t cfg_isz8;	// L11197
  cfg_isz8 = 0;	// L11198
  int32_t cfg_itsz8;	// L11199
  cfg_itsz8 = 0;	// L11200
  uint8_t fetch_en8;	// L11201
  fetch_en8 = 0;	// L11202
  uint8_t instr_cnt8;	// L11203
  instr_cnt8 = 0;	// L11204
  uint8_t iter_cnt8;	// L11205
  iter_cnt8 = 0;	// L11206
  uint8_t condition_reg8;	// L11207
  condition_reg8 = 0;	// L11208
  uint8_t sb_v8[5];	// L11209
  #pragma HLS array_partition variable=sb_v8 complete dim=1

  for (int v7056 = 0; v7056 < 5; v7056++) {	// L11210
    sb_v8[v7056] = 0;	// L11210
  }
  uint8_t sb_dst8[5];	// L11211
  #pragma HLS array_partition variable=sb_dst8 complete dim=1

  for (int v7058 = 0; v7058 < 5; v7058++) {	// L11212
    sb_dst8[v7058] = 0;	// L11212
  }
  uint8_t sb_cmp8[5];	// L11213
  #pragma HLS array_partition variable=sb_cmp8 complete dim=1

  for (int v7060 = 0; v7060 < 5; v7060++) {	// L11214
    sb_cmp8[v7060] = 0;	// L11214
  }
  uint8_t sb_rtr8[5];	// L11215
  #pragma HLS array_partition variable=sb_rtr8 complete dim=1

  for (int v7062 = 0; v7062 < 5; v7062++) {	// L11216
    sb_rtr8[v7062] = 0;	// L11216
  }
  uint8_t sb_inj8[5];	// L11217
  #pragma HLS array_partition variable=sb_inj8 complete dim=1

  for (int v7064 = 0; v7064 < 5; v7064++) {	// L11218
    sb_inj8[v7064] = 0;	// L11218
  }
  uint8_t sb_dir8[5];	// L11219
  #pragma HLS array_partition variable=sb_dir8 complete dim=1

  for (int v7066 = 0; v7066 < 5; v7066++) {	// L11220
    sb_dir8[v7066] = 0;	// L11220
  }
  uint8_t sb_id8[5];	// L11221
  #pragma HLS array_partition variable=sb_id8 complete dim=1

  for (int v7068 = 0; v7068 < 5; v7068++) {	// L11222
    sb_id8[v7068] = 0;	// L11222
  }
  uint8_t sb_rvld8[5];	// L11223
  #pragma HLS array_partition variable=sb_rvld8 complete dim=1

  for (int v7070 = 0; v7070 < 5; v7070++) {	// L11224
    sb_rvld8[v7070] = 0;	// L11224
  }
  uint8_t sb_ix8[5];	// L11225
  #pragma HLS array_partition variable=sb_ix8 complete dim=1

  for (int v7072 = 0; v7072 < 5; v7072++) {	// L11226
    sb_ix8[v7072] = 0;	// L11226
  }
  half resq8[8];	// L11227
  #pragma HLS array_partition variable=resq8 complete dim=1
#pragma HLS dependence variable=resq8 type=inter dependent=false

  for (int v7074 = 0; v7074 < 8; v7074++) {	// L11228
    resq8[v7074] = 0.000000;	// L11228
  }
  uint8_t cmpq8[8];	// L11229
  #pragma HLS array_partition variable=cmpq8 complete dim=1
#pragma HLS dependence variable=cmpq8 type=inter dependent=false

  for (int v7076 = 0; v7076 < 8; v7076++) {	// L11230
    cmpq8[v7076] = 0;	// L11230
  }
  uint8_t resq_wr8;	// L11231
  resq_wr8 = 0;	// L11232
  l_S_t_0_t8: for (int t8 = 0; t8 < 374; t8++) {	// L11233
  #pragma HLS pipeline II=1
    ap_uint<26> p_w8;	// L11234
    p_w8 = 0;	// L11235
    ap_uint<26> p_e8;	// L11236
    p_e8 = 0;	// L11237
    ap_uint<26> p_n8;	// L11238
    p_n8 = 0;	// L11239
    ap_uint<26> p_s8;	// L11240
    p_s8 = 0;	// L11241
    uint8_t v7083 = rbcnt8[0];	// L11242
    int32_t v7084 = v7083;	// L11243
    bool v7085 = v7084 < 2;	// L11244
    if (v7085) {	// L11245
      ap_uint<26> v7086;
      bool v7087 = v7000.read_nb(v7086);
	// L11246
      ap_uint<26> gw8;	// L11247
      gw8 = v7086;	// L11248
      bool okw8;	// L11249
      okw8 = v7087;	// L11250
      bool v7090 = okw8;	// L11251
      if (v7090) {	// L11252
        ap_int<26> v7091 = gw8;	// L11253
        p_w8 = v7091;	// L11254
      }
    }
    uint8_t v7092 = rbcnt8[1];	// L11257
    int32_t v7093 = v7092;	// L11258
    bool v7094 = v7093 < 2;	// L11259
    if (v7094) {	// L11260
      ap_uint<26> v7095;
      bool v7096 = v7001.read_nb(v7095);
	// L11261
      ap_uint<26> ge8;	// L11262
      ge8 = v7095;	// L11263
      bool oke8;	// L11264
      oke8 = v7096;	// L11265
      bool v7099 = oke8;	// L11266
      if (v7099) {	// L11267
        ap_int<26> v7100 = ge8;	// L11268
        p_e8 = v7100;	// L11269
      }
    }
    uint8_t v7101 = rbcnt8[2];	// L11272
    int32_t v7102 = v7101;	// L11273
    bool v7103 = v7102 < 2;	// L11274
    if (v7103) {	// L11275
      ap_uint<26> v7104;
      bool v7105 = v7002.read_nb(v7104);
	// L11276
      ap_uint<26> gn8;	// L11277
      gn8 = v7104;	// L11278
      bool okn8;	// L11279
      okn8 = v7105;	// L11280
      bool v7108 = okn8;	// L11281
      if (v7108) {	// L11282
        ap_int<26> v7109 = gn8;	// L11283
        p_n8 = v7109;	// L11284
      }
    }
    uint8_t v7110 = rbcnt8[3];	// L11287
    int32_t v7111 = v7110;	// L11288
    bool v7112 = v7111 < 2;	// L11289
    if (v7112) {	// L11290
      ap_uint<26> v7113;
      bool v7114 = v7003.read_nb(v7113);
	// L11291
      ap_uint<26> gs8;	// L11292
      gs8 = v7113;	// L11293
      bool oks8;	// L11294
      oks8 = v7114;	// L11295
      bool v7117 = oks8;	// L11296
      if (v7117) {	// L11297
        ap_int<26> v7118 = gs8;	// L11298
        p_s8 = v7118;	// L11299
      }
    }
    ap_uint<26> fin8[4];	// L11302
    for (int v7120 = 0; v7120 < 4; v7120++) {	// L11303
      fin8[v7120] = 0;	// L11303
    }
    ap_int<26> v7121 = p_w8;	// L11304
    fin8[0] = v7121;	// L11305
    ap_int<26> v7122 = p_e8;	// L11306
    fin8[1] = v7122;	// L11307
    ap_int<26> v7123 = p_n8;	// L11308
    fin8[2] = v7123;	// L11309
    ap_int<26> v7124 = p_s8;	// L11310
    fin8[3] = v7124;	// L11311
    l_S_d_0_d32: for (int d32 = 0; d32 < 4; d32++) {	// L11312
      ap_uint<26> v7126 = fin8[d32];	// L11313
      bool v7127;
      ap_int<26> v7127_tmp = v7126;
      v7127 = v7127_tmp[25];	// L11314
      int32_t v7128 = v7127;	// L11315
      bool v7129 = v7128 == 1;	// L11316
      uint8_t v7130 = rbcnt8[d32];	// L11317
      int32_t v7131 = v7130;	// L11318
      bool v7132 = v7131 < 2;	// L11319
      bool v7133 = v7129 & v7132;	// L11320
      if (v7133) {	// L11321
        ap_uint<26> v7134 = fin8[d32];	// L11322
        uint8_t v7135 = rbcnt8[d32];	// L11323
        int v7136 = v7135;	// L11324
        rbuf8[d32][v7136] = v7134;	// L11325
        uint8_t v7137 = rbcnt8[d32];	// L11326
        ap_int<33> v7138 = v7137;	// L11327
        ap_int<33> v7139 = v7138 + 1;	// L11328
        uint8_t v7140 = v7139;	// L11329
        rbcnt8[d32] = v7140;	// L11330
      }
    }
    ap_uint<26> hd8[4];	// L11333
    for (int v7142 = 0; v7142 < 4; v7142++) {	// L11334
      hd8[v7142] = 0;	// L11334
    }
    int32_t hvld8[4];	// L11335
    for (int v7144 = 0; v7144 < 4; v7144++) {	// L11336
      hvld8[v7144] = 0;	// L11336
    }
    int32_t hit8[4];	// L11337
    for (int v7146 = 0; v7146 < 4; v7146++) {	// L11338
      hit8[v7146] = 0;	// L11338
    }
    int32_t axis8[4];	// L11339
    for (int v7148 = 0; v7148 < 4; v7148++) {	// L11340
      axis8[v7148] = 0;	// L11340
    }
    int32_t v7149 = col_id8;	// L11341
    axis8[0] = v7149;	// L11342
    int32_t v7150 = col_id8;	// L11343
    axis8[1] = v7150;	// L11344
    int32_t v7151 = row_id8;	// L11345
    axis8[2] = v7151;	// L11346
    int32_t v7152 = row_id8;	// L11347
    axis8[3] = v7152;	// L11348
    l_S_d_1_d33: for (int d33 = 0; d33 < 4; d33++) {	// L11349
      uint8_t v7154 = rbcnt8[d33];	// L11350
      int32_t v7155 = v7154;	// L11351
      bool v7156 = v7155 > 0;	// L11352
      if (v7156) {	// L11353
        ap_uint<26> v7157 = rbuf8[d33][0];	// L11354
        hd8[d33] = v7157;	// L11355
        hvld8[d33] = 1;	// L11356
        ap_uint<26> v7158 = hd8[d33];	// L11357
        ap_int<4> v7159;
        ap_int<26> v7159_tmp = v7158;
        v7159 = v7159_tmp(24, 21);	// L11358
        int32_t v7160 = axis8[d33];	// L11359
        int32_t v7161 = v7159;	// L11360
        bool v7162 = v7161 == v7160;	// L11361
        if (v7162) {	// L11362
          hit8[d33] = 1;	// L11363
        }
      }
    }
    ap_uint<26> o_crv8;	// L11367
    o_crv8 = 0;	// L11368
    int32_t crv_in8;	// L11369
    crv_in8 = -1;	// L11370
    int32_t v7165 = hit8[3];	// L11371
    bool v7166 = v7165 == 1;	// L11372
    if (v7166) {	// L11373
      ap_uint<26> v7167 = hd8[3];	// L11374
      o_crv8 = v7167;	// L11375
      crv_in8 = 3;	// L11376
    } else {
      int32_t v7168 = hit8[2];	// L11378
      bool v7169 = v7168 == 1;	// L11379
      if (v7169) {	// L11380
        ap_uint<26> v7170 = hd8[2];	// L11381
        o_crv8 = v7170;	// L11382
        crv_in8 = 2;	// L11383
      } else {
        int32_t v7171 = hit8[1];	// L11385
        bool v7172 = v7171 == 1;	// L11386
        if (v7172) {	// L11387
          ap_uint<26> v7173 = hd8[1];	// L11388
          o_crv8 = v7173;	// L11389
          crv_in8 = 1;	// L11390
        } else {
          int32_t v7174 = hit8[0];	// L11392
          bool v7175 = v7174 == 1;	// L11393
          if (v7175) {	// L11394
            ap_uint<26> v7176 = hd8[0];	// L11395
            o_crv8 = v7176;	// L11396
            crv_in8 = 0;	// L11397
          }
        }
      }
    }
    int32_t pop8[4];	// L11402
    for (int v7178 = 0; v7178 < 4; v7178++) {	// L11403
      pop8[v7178] = 0;	// L11403
    }
    int32_t inj_done8;	// L11404
    inj_done8 = 0;	// L11405
    int32_t idir8;	// L11406
    idir8 = -1;	// L11407
    ap_int<26> v7181 = csd_pkt8;	// L11408
    bool v7182;
    ap_int<26> v7182_tmp = v7181;
    v7182 = v7182_tmp[25];	// L11409
    int32_t v7183 = v7182;	// L11410
    bool v7184 = v7183 == 1;	// L11411
    if (v7184) {	// L11412
      int32_t v7185 = csd_dir8;	// L11413
      ap_int<33> v7186 = v7185;	// L11414
      ap_int<33> v7187 = 3 - v7186;	// L11415
      int32_t v7188 = v7187;	// L11416
      idir8 = v7188;	// L11417
    }
    int32_t v7189 = idir8;	// L11419
    bool v7190 = v7189 == 0;	// L11420
    if (v7190) {	// L11421
      ap_int<26> v7191 = csd_pkt8;	// L11422
      bool v7192 = v7004.write_nb(v7191);
	// L11423
      if (v7192) {	// L11424
        inj_done8 = 1;	// L11425
      }
    } else {
      int32_t v7193 = hvld8[0];	// L11428
      bool v7194 = v7193 == 1;	// L11429
      int32_t v7195 = hit8[0];	// L11430
      bool v7196 = v7195 == 0;	// L11431
      bool v7197 = v7194 & v7196;	// L11432
      if (v7197) {	// L11433
        ap_uint<26> v7198 = hd8[0];	// L11434
        bool v7199 = v7004.write_nb(v7198);
	// L11435
        if (v7199) {	// L11436
          pop8[0] = 1;	// L11437
        }
      }
    }
    int32_t v7200 = idir8;	// L11441
    bool v7201 = v7200 == 1;	// L11442
    if (v7201) {	// L11443
      ap_int<26> v7202 = csd_pkt8;	// L11444
      bool v7203 = v7005.write_nb(v7202);
	// L11445
      if (v7203) {	// L11446
        inj_done8 = 1;	// L11447
      }
    } else {
      int32_t v7204 = hvld8[1];	// L11450
      bool v7205 = v7204 == 1;	// L11451
      int32_t v7206 = hit8[1];	// L11452
      bool v7207 = v7206 == 0;	// L11453
      bool v7208 = v7205 & v7207;	// L11454
      if (v7208) {	// L11455
        ap_uint<26> v7209 = hd8[1];	// L11456
        bool v7210 = v7005.write_nb(v7209);
	// L11457
        if (v7210) {	// L11458
          pop8[1] = 1;	// L11459
        }
      }
    }
    int32_t v7211 = idir8;	// L11463
    bool v7212 = v7211 == 2;	// L11464
    if (v7212) {	// L11465
      ap_int<26> v7213 = csd_pkt8;	// L11466
      bool v7214 = v7006.write_nb(v7213);
	// L11467
      if (v7214) {	// L11468
        inj_done8 = 1;	// L11469
      }
    } else {
      int32_t v7215 = hvld8[2];	// L11472
      bool v7216 = v7215 == 1;	// L11473
      int32_t v7217 = hit8[2];	// L11474
      bool v7218 = v7217 == 0;	// L11475
      bool v7219 = v7216 & v7218;	// L11476
      if (v7219) {	// L11477
        ap_uint<26> v7220 = hd8[2];	// L11478
        bool v7221 = v7006.write_nb(v7220);
	// L11479
        if (v7221) {	// L11480
          pop8[2] = 1;	// L11481
        }
      }
    }
    int32_t v7222 = idir8;	// L11485
    bool v7223 = v7222 == 3;	// L11486
    if (v7223) {	// L11487
      ap_int<26> v7224 = csd_pkt8;	// L11488
      bool v7225 = v7007.write_nb(v7224);
	// L11489
      if (v7225) {	// L11490
        inj_done8 = 1;	// L11491
      }
    } else {
      int32_t v7226 = hvld8[3];	// L11494
      bool v7227 = v7226 == 1;	// L11495
      int32_t v7228 = hit8[3];	// L11496
      bool v7229 = v7228 == 0;	// L11497
      bool v7230 = v7227 & v7229;	// L11498
      if (v7230) {	// L11499
        ap_uint<26> v7231 = hd8[3];	// L11500
        bool v7232 = v7007.write_nb(v7231);
	// L11501
        if (v7232) {	// L11502
          pop8[3] = 1;	// L11503
        }
      }
    }
    int32_t v7233 = crv_in8;	// L11507
    bool v7234 = v7233 >= 0;	// L11508
    if (v7234) {	// L11509
      int32_t v7235 = crv_in8;	// L11510
      int v7236 = v7235;	// L11511
      pop8[v7236] = 1;	// L11512
    }
    l_S_d_2_d34: for (int d34 = 0; d34 < 4; d34++) {	// L11514
      int32_t v7238 = pop8[d34];	// L11515
      bool v7239 = v7238 == 1;	// L11516
      if (v7239) {	// L11517
        l_S_sft_2_sft8: for (int sft8 = 0; sft8 < 1; sft8++) {	// L11518
          ap_uint<26> v7241 = rbuf8[d34][(sft8 + 1)];	// L11519
          rbuf8[d34][sft8] = v7241;	// L11520
        }
        uint8_t v7242 = rbcnt8[d34];	// L11522
        ap_int<33> v7243 = v7242;	// L11523
        ap_int<33> v7244 = v7243 - 1;	// L11524
        uint8_t v7245 = v7244;	// L11525
        rbcnt8[d34] = v7245;	// L11526
      }
    }
    int32_t v7246 = inj_done8;	// L11529
    bool v7247 = v7246 == 1;	// L11530
    if (v7247) {	// L11531
      csd_pkt8 = 0;	// L11532
    }
    ap_int<26> v7248 = o_crv8;	// L11534
    bool v7249;
    ap_int<26> v7249_tmp = v7248;
    v7249 = v7249_tmp[25];	// L11535
    int32_t v7250 = v7249;	// L11536
    crv_vld8 = v7250;	// L11537
    int32_t v7251 = crv_vld8;	// L11538
    bool v7252 = v7251 == 1;	// L11539
    if (v7252) {	// L11540
      crv_ever8 = 1;	// L11541
    }
    ap_int<26> v7253 = o_crv8;	// L11543
    int16_t v7254;
    ap_int<26> v7254_tmp = v7253;
    v7254 = v7254_tmp(15, 0);	// L11544
    half v7255;
    union { uint16_t from; half to;} _converter_v7254_to_v7255 = {};
    _converter_v7254_to_v7255.from = v7254;
    v7255 = _converter_v7254_to_v7255.to;	// L11545
    crv_data8 = v7255;	// L11546
    ap_int<26> v7256 = o_crv8;	// L11547
    ap_int<4> v7257;
    ap_int<26> v7257_tmp = v7256;
    v7257 = v7257_tmp(19, 16);	// L11548
    int32_t v7258 = v7257;	// L11549
    crv_addr8 = v7258;	// L11550
    ap_int<26> v7259 = o_crv8;	// L11551
    bool v7260;
    ap_int<26> v7260_tmp = v7259;
    v7260 = v7260_tmp[20];	// L11552
    int32_t v7261 = v7260;	// L11553
    crv_mode8 = v7261;	// L11554
    ap_int<26> v7262 = o_crv8;	// L11555
    int16_t v7263;
    ap_int<26> v7263_tmp = v7262;
    v7263 = v7263_tmp(15, 0);	// L11556
    int32_t v7264 = v7263;	// L11557
    crv_raw8 = v7264;	// L11558
    half rxv8[4];	// L11559
    for (int v7266 = 0; v7266 < 4; v7266++) {	// L11560
      rxv8[v7266] = 0.000000;	// L11560
    }
    int32_t rxvld8[4];	// L11561
    for (int v7268 = 0; v7268 < 4; v7268++) {	// L11562
      rxvld8[v7268] = 0;	// L11562
    }
    uint8_t v7269 = hold_cnt8[0];	// L11563
    int32_t v7270 = v7269;	// L11564
    bool v7271 = v7270 < 2;	// L11565
    if (v7271) {	// L11566
      ap_uint<17> v7272;
      bool v7273 = v7008.read_nb(v7272);
	// L11567
      ap_uint<17> sgn8;	// L11568
      sgn8 = v7272;	// L11569
      bool sqn8;	// L11570
      sqn8 = v7273;	// L11571
      bool v7276 = sqn8;	// L11572
      int32_t v7277 = v7276;	// L11573
      bool v7278 = v7277 == 1;	// L11574
      if (v7278) {	// L11575
        ap_int<17> v7279 = sgn8;	// L11576
        int16_t v7280;
        ap_int<17> v7280_tmp = v7279;
        v7280 = v7280_tmp(16, 1);	// L11577
        half v7281;
        union { uint16_t from; half to;} _converter_v7280_to_v7281 = {};
        _converter_v7280_to_v7281.from = v7280;
        v7281 = _converter_v7280_to_v7281.to;	// L11578
        rxv8[0] = v7281;	// L11579
        rxvld8[0] = 1;	// L11580
      }
    }
    uint8_t v7282 = hold_cnt8[1];	// L11583
    int32_t v7283 = v7282;	// L11584
    bool v7284 = v7283 < 2;	// L11585
    if (v7284) {	// L11586
      ap_uint<17> v7285;
      bool v7286 = v7009.read_nb(v7285);
	// L11587
      ap_uint<17> sgs8;	// L11588
      sgs8 = v7285;	// L11589
      bool sqs8;	// L11590
      sqs8 = v7286;	// L11591
      bool v7289 = sqs8;	// L11592
      int32_t v7290 = v7289;	// L11593
      bool v7291 = v7290 == 1;	// L11594
      if (v7291) {	// L11595
        ap_int<17> v7292 = sgs8;	// L11596
        int16_t v7293;
        ap_int<17> v7293_tmp = v7292;
        v7293 = v7293_tmp(16, 1);	// L11597
        half v7294;
        union { uint16_t from; half to;} _converter_v7293_to_v7294 = {};
        _converter_v7293_to_v7294.from = v7293;
        v7294 = _converter_v7293_to_v7294.to;	// L11598
        rxv8[1] = v7294;	// L11599
        rxvld8[1] = 1;	// L11600
      }
    }
    uint8_t v7295 = hold_cnt8[2];	// L11603
    int32_t v7296 = v7295;	// L11604
    bool v7297 = v7296 < 2;	// L11605
    if (v7297) {	// L11606
      ap_uint<17> v7298;
      bool v7299 = v7010.read_nb(v7298);
	// L11607
      ap_uint<17> sgw8;	// L11608
      sgw8 = v7298;	// L11609
      bool sqw8;	// L11610
      sqw8 = v7299;	// L11611
      bool v7302 = sqw8;	// L11612
      int32_t v7303 = v7302;	// L11613
      bool v7304 = v7303 == 1;	// L11614
      if (v7304) {	// L11615
        ap_int<17> v7305 = sgw8;	// L11616
        int16_t v7306;
        ap_int<17> v7306_tmp = v7305;
        v7306 = v7306_tmp(16, 1);	// L11617
        half v7307;
        union { uint16_t from; half to;} _converter_v7306_to_v7307 = {};
        _converter_v7306_to_v7307.from = v7306;
        v7307 = _converter_v7306_to_v7307.to;	// L11618
        rxv8[2] = v7307;	// L11619
        rxvld8[2] = 1;	// L11620
      }
    }
    uint8_t v7308 = hold_cnt8[3];	// L11623
    int32_t v7309 = v7308;	// L11624
    bool v7310 = v7309 < 2;	// L11625
    if (v7310) {	// L11626
      ap_uint<17> v7311;
      bool v7312 = v7011.read_nb(v7311);
	// L11627
      ap_uint<17> sge8;	// L11628
      sge8 = v7311;	// L11629
      bool sqe8;	// L11630
      sqe8 = v7312;	// L11631
      bool v7315 = sqe8;	// L11632
      int32_t v7316 = v7315;	// L11633
      bool v7317 = v7316 == 1;	// L11634
      if (v7317) {	// L11635
        ap_int<17> v7318 = sge8;	// L11636
        int16_t v7319;
        ap_int<17> v7319_tmp = v7318;
        v7319 = v7319_tmp(16, 1);	// L11637
        half v7320;
        union { uint16_t from; half to;} _converter_v7319_to_v7320 = {};
        _converter_v7319_to_v7320.from = v7319;
        v7320 = _converter_v7319_to_v7320.to;	// L11638
        rxv8[3] = v7320;	// L11639
        rxvld8[3] = 1;	// L11640
      }
    }
    l_S_d_4_d35: for (int d35 = 0; d35 < 4; d35++) {	// L11643
      int32_t v7322 = rxvld8[d35];	// L11644
      bool v7323 = v7322 == 1;	// L11645
      if (v7323) {	// L11646
        half v7324 = rxv8[d35];	// L11647
        uint8_t v7325 = hold_cnt8[d35];	// L11648
        int v7326 = v7325;	// L11649
        hold_v8[d35][v7326] = v7324;	// L11650
        uint8_t v7327 = hold_cnt8[d35];	// L11651
        ap_int<33> v7328 = v7327;	// L11652
        ap_int<33> v7329 = v7328 + 1;	// L11653
        uint8_t v7330 = v7329;	// L11654
        hold_cnt8[d35] = v7330;	// L11655
      }
    }
    ap_uint<17> tx_n8;	// L11658
    tx_n8 = 0;	// L11659
    ap_uint<17> tx_s8;	// L11660
    tx_s8 = 0;	// L11661
    ap_uint<17> tx_w8;	// L11662
    tx_w8 = 0;	// L11663
    ap_uint<17> tx_e8;	// L11664
    tx_e8 = 0;	// L11665
    uint8_t v7335 = sb_v8[0];	// L11666
    int32_t v7336 = v7335;	// L11667
    bool v7337 = v7336 == 1;	// L11668
    if (v7337) {	// L11669
      uint8_t v7338 = sb_ix8[0];	// L11670
      int v7339 = v7338;	// L11671
      half v7340 = resq8[v7339];	// L11672
      half wb8;
#pragma HLS dependence variable=wb8 type=inter dependent=false	// L11673
      wb8 = v7340;	// L11674
      uint8_t v7342 = sb_cmp8[0];	// L11675
      int32_t v7343 = v7342;	// L11676
      bool v7344 = v7343 == 1;	// L11677
      if (v7344) {	// L11678
        uint8_t v7345 = sb_ix8[0];	// L11679
        int v7346 = v7345;	// L11680
        uint8_t v7347 = cmpq8[v7346];	// L11681
        condition_reg8 = v7347;	// L11682
      }
      uint8_t v7348 = sb_rtr8[0];	// L11684
      int32_t v7349 = v7348;	// L11685
      bool v7350 = v7349 == 1;	// L11686
      if (v7350) {	// L11687
        uint8_t v7351 = sb_inj8[0];	// L11688
        int32_t v7352 = v7351;	// L11689
        bool v7353 = v7352 == 1;	// L11690
        ap_int<26> v7354 = csd_pkt8;	// L11691
        bool v7355;
        ap_int<26> v7355_tmp = v7354;
        v7355 = v7355_tmp[25];	// L11692
        int32_t v7356 = v7355;	// L11693
        bool v7357 = v7356 == 0;	// L11694
        bool v7358 = v7353 & v7357;	// L11695
        if (v7358) {	// L11696
          half v7359 = wb8;	// L11697
          uint16_t v7360;
          union { half from; uint16_t to;} _converter_v7359_to_v7360 = {};
          _converter_v7359_to_v7360.from = v7359;
          v7360 = _converter_v7359_to_v7360.to;	// L11698
          ap_int<26> v7361 = csd_pkt8;	// L11699
          ap_int<26> v7362;
          ap_int<26> v7362_tmp = v7361;
          v7362_tmp(15, 0) = v7360;
          v7362 = v7362_tmp;	// L11700
          csd_pkt8 = v7362;	// L11701
          uint8_t v7363 = sb_dst8[0];	// L11702
          ap_uint<4> v7364 = v7363;	// L11703
          ap_int<26> v7365 = csd_pkt8;	// L11704
          ap_int<26> v7366;
          ap_int<26> v7366_tmp = v7365;
          v7366_tmp(19, 16) = v7364;
          v7366 = v7366_tmp;	// L11705
          csd_pkt8 = v7366;	// L11706
          uint8_t v7367 = sb_id8[0];	// L11707
          ap_uint<4> v7368 = v7367;	// L11708
          ap_int<26> v7369 = csd_pkt8;	// L11709
          ap_int<26> v7370;
          ap_int<26> v7370_tmp = v7369;
          v7370_tmp(24, 21) = v7368;
          v7370 = v7370_tmp;	// L11710
          csd_pkt8 = v7370;	// L11711
          uint8_t v7371 = sb_rvld8[0];	// L11712
          bool v7372 = v7371;	// L11713
          ap_int<26> v7373 = csd_pkt8;	// L11714
          ap_int<26> v7374;
          ap_int<26> v7374_tmp = v7373;
          v7374_tmp[25] = v7372;          v7374 = v7374_tmp;	// L11715
          csd_pkt8 = v7374;	// L11716
          uint8_t v7375 = sb_dir8[0];	// L11717
          int32_t v7376 = v7375;	// L11718
          csd_dir8 = v7376;	// L11719
        }
      } else {
        uint8_t v7377 = sb_dst8[0];	// L11722
        int32_t v7378 = v7377;	// L11723
        bool v7379 = v7378 >= 12;	// L11724
        if (v7379) {	// L11725
          ap_uint<17> tw08;	// L11726
          tw08 = 0;	// L11727
          uint8_t v7381 = sb_rvld8[0];	// L11728
          bool v7382 = v7381;	// L11729
          ap_int<17> v7383 = tw08;	// L11730
          ap_int<17> v7384;
          ap_int<17> v7384_tmp = v7383;
          v7384_tmp[0] = v7382;          v7384 = v7384_tmp;	// L11731
          tw08 = v7384;	// L11732
          half v7385 = wb8;	// L11733
          uint16_t v7386;
          union { half from; uint16_t to;} _converter_v7385_to_v7386 = {};
          _converter_v7385_to_v7386.from = v7385;
          v7386 = _converter_v7385_to_v7386.to;	// L11734
          ap_int<17> v7387 = tw08;	// L11735
          ap_int<17> v7388;
          ap_int<17> v7388_tmp = v7387;
          v7388_tmp(16, 1) = v7386;
          v7388 = v7388_tmp;	// L11736
          tw08 = v7388;	// L11737
          uint8_t v7389 = sb_dst8[0];	// L11738
          int32_t v7390 = v7389;	// L11739
          int32_t v7391 = v7390 & 3;	// L11740
          bool v7392 = v7391 == 0;	// L11741
          if (v7392) {	// L11742
            ap_int<17> v7393 = tw08;	// L11743
            tx_n8 = v7393;	// L11744
          } else {
            uint8_t v7394 = sb_dst8[0];	// L11746
            int32_t v7395 = v7394;	// L11747
            int32_t v7396 = v7395 & 3;	// L11748
            bool v7397 = v7396 == 1;	// L11749
            if (v7397) {	// L11750
              ap_int<17> v7398 = tw08;	// L11751
              tx_s8 = v7398;	// L11752
            } else {
              uint8_t v7399 = sb_dst8[0];	// L11754
              int32_t v7400 = v7399;	// L11755
              int32_t v7401 = v7400 & 3;	// L11756
              bool v7402 = v7401 == 2;	// L11757
              if (v7402) {	// L11758
                ap_int<17> v7403 = tw08;	// L11759
                tx_w8 = v7403;	// L11760
              } else {
                ap_int<17> v7404 = tw08;	// L11762
                tx_e8 = v7404;	// L11763
              }
            }
          }
        } else {
          uint8_t v7405 = sb_rvld8[0];	// L11768
          int32_t v7406 = v7405;	// L11769
          bool v7407 = v7406 == 1;	// L11770
          if (v7407) {	// L11771
            uint8_t v7408 = sb_dst8[0];	// L11772
            int32_t v7409 = v7408;	// L11773
            bool v7410 = v7409 < 8;	// L11774
            int32_t v7411 = dsmask8;	// L11775
            int32_t v7412 = v7411 >> v7409;	// L11776
            int32_t v7413 = v7412 & 1;	// L11777
            bool v7414 = v7413 == 1;	// L11778
            bool v7415 = v7410 & v7414;	// L11779
            if (v7415) {	// L11780
              uint8_t v7416 = sb_dst8[0];	// L11781
              int v7417 = v7416;	// L11782
              int32_t v7418 = drf_full8[v7417];	// L11783
              bool v7419 = v7418 == 0;	// L11784
              if (v7419) {	// L11785
                half v7420 = wb8;	// L11786
                uint8_t v7421 = sb_dst8[0];	// L11787
                int v7422 = v7421;	// L11788
                drf8[v7422] = v7420;	// L11789
                uint8_t v7423 = sb_dst8[0];	// L11790
                int v7424 = v7423;	// L11791
                drf_full8[v7424] = 1;	// L11792
              }
            } else {
              half v7425 = wb8;	// L11795
              uint8_t v7426 = sb_dst8[0];	// L11796
              int32_t v7427 = v7426;	// L11797
              int32_t v7428 = v7427 & 7;	// L11798
              int v7429 = v7428;	// L11799
              drf8[v7429] = v7425;	// L11800
            }
          }
        }
      }
    }
    int32_t pc8;	// L11806
    pc8 = -1;	// L11807
    int8_t v7431 = fetch_en8;	// L11808
    int32_t v7432 = v7431;	// L11809
    bool v7433 = v7432 == 1;	// L11810
    if (v7433) {	// L11811
      int8_t v7434 = instr_cnt8;	// L11812
      int32_t v7435 = v7434;	// L11813
      pc8 = v7435;	// L11814
    }
    int8_t v7436 = fetch_en8;	// L11816
    int32_t v7437 = v7436;	// L11817
    bool v7438 = v7437 == 1;	// L11818
    if (v7438) {	// L11819
      fe_ever8 = 1;	// L11820
    }
    int32_t instr8;	// L11822
    instr8 = 0;	// L11823
    int32_t v7440 = pc8;	// L11824
    bool v7441 = v7440 >= 0;	// L11825
    if (v7441) {	// L11826
      int32_t v7442 = pc8;	// L11827
      int v7443 = v7442;	// L11828
      int32_t v7444 = irf8[v7443];	// L11829
      instr8 = v7444;	// L11830
    }
    int32_t v7445 = instr8;	// L11832
    int32_t v7446 = v7445 & 15;	// L11833
    int32_t op8;	// L11834
    op8 = v7446;	// L11835
    int32_t v7448 = instr8;	// L11836
    int32_t v7449 = v7448 >> 4;	// L11837
    int32_t v7450 = v7449 & 15;	// L11838
    int32_t dst8;	// L11839
    dst8 = v7450;	// L11840
    int32_t v7452 = instr8;	// L11841
    int32_t v7453 = v7452 >> 8;	// L11842
    int32_t v7454 = v7453 & 15;	// L11843
    int32_t s18;	// L11844
    s18 = v7454;	// L11845
    int32_t v7456 = instr8;	// L11846
    int32_t v7457 = v7456 >> 12;	// L11847
    int32_t v7458 = v7457 & 15;	// L11848
    int32_t s28;	// L11849
    s28 = v7458;	// L11850
    half a8;	// L11851
    a8 = 0.000000;	// L11852
    half b8;	// L11853
    b8 = 0.000000;	// L11854
    int32_t v7462 = s18;	// L11855
    bool v7463 = v7462 >= 12;	// L11856
    if (v7463) {	// L11857
      int32_t v7464 = s18;	// L11858
      int32_t v7465 = v7464 & 3;	// L11859
      int v7466 = v7465;	// L11860
      half v7467 = hold_v8[v7466][0];	// L11861
      a8 = v7467;	// L11862
    } else {
      int32_t v7468 = s18;	// L11864
      int v7469 = v7468;	// L11865
      half v7470 = drf8[v7469];	// L11866
      a8 = v7470;	// L11867
    }
    int32_t v7471 = s28;	// L11869
    bool v7472 = v7471 >= 12;	// L11870
    if (v7472) {	// L11871
      int32_t v7473 = s28;	// L11872
      int32_t v7474 = v7473 & 3;	// L11873
      int v7475 = v7474;	// L11874
      half v7476 = hold_v8[v7475][0];	// L11875
      b8 = v7476;	// L11876
    } else {
      int32_t v7477 = s28;	// L11878
      int v7478 = v7477;	// L11879
      half v7479 = drf8[v7478];	// L11880
      b8 = v7479;	// L11881
    }
    int32_t a_vld8;	// L11883
    a_vld8 = 1;	// L11884
    int32_t b_vld8;	// L11885
    b_vld8 = 1;	// L11886
    int32_t v7482 = s18;	// L11887
    bool v7483 = v7482 >= 12;	// L11888
    if (v7483) {	// L11889
      a_vld8 = 0;	// L11890
      int32_t v7484 = s18;	// L11891
      int32_t v7485 = v7484 & 3;	// L11892
      int v7486 = v7485;	// L11893
      uint8_t v7487 = hold_cnt8[v7486];	// L11894
      int32_t v7488 = v7487;	// L11895
      bool v7489 = v7488 > 0;	// L11896
      if (v7489) {	// L11897
        a_vld8 = 1;	// L11898
      }
    }
    int32_t v7490 = s28;	// L11901
    bool v7491 = v7490 >= 12;	// L11902
    if (v7491) {	// L11903
      b_vld8 = 0;	// L11904
      int32_t v7492 = s28;	// L11905
      int32_t v7493 = v7492 & 3;	// L11906
      int v7494 = v7493;	// L11907
      uint8_t v7495 = hold_cnt8[v7494];	// L11908
      int32_t v7496 = v7495;	// L11909
      bool v7497 = v7496 > 0;	// L11910
      if (v7497) {	// L11911
        b_vld8 = 1;	// L11912
      }
    }
    int32_t v7498 = s18;	// L11915
    bool v7499 = v7498 < 8;	// L11916
    int32_t v7500 = dsmask8;	// L11917
    int32_t v7501 = v7500 >> v7498;	// L11918
    int32_t v7502 = v7501 & 1;	// L11919
    bool v7503 = v7502 == 1;	// L11920
    bool v7504 = v7499 & v7503;	// L11921
    if (v7504) {	// L11922
      int32_t v7505 = s18;	// L11923
      int v7506 = v7505;	// L11924
      int32_t v7507 = drf_full8[v7506];	// L11925
      bool v7508 = v7507 == 0;	// L11926
      if (v7508) {	// L11927
        a_vld8 = 0;	// L11928
      }
    }
    int32_t v7509 = s28;	// L11931
    bool v7510 = v7509 < 8;	// L11932
    int32_t v7511 = dsmask8;	// L11933
    int32_t v7512 = v7511 >> v7509;	// L11934
    int32_t v7513 = v7512 & 1;	// L11935
    bool v7514 = v7513 == 1;	// L11936
    bool v7515 = v7510 & v7514;	// L11937
    if (v7515) {	// L11938
      int32_t v7516 = s28;	// L11939
      int v7517 = v7516;	// L11940
      int32_t v7518 = drf_full8[v7517];	// L11941
      bool v7519 = v7518 == 0;	// L11942
      if (v7519) {	// L11943
        b_vld8 = 0;	// L11944
      }
    }
    int32_t binop8;	// L11947
    binop8 = 0;	// L11948
    int32_t v7521 = op8;	// L11949
    bool v7522 = v7521 == 0;	// L11950
    bool v7523 = v7521 == 1;	// L11951
    bool v7524 = v7521 == 2;	// L11952
    bool v7525 = v7521 == 8;	// L11953
    bool v7526 = v7521 == 9;	// L11954
    bool v7527 = v7522 | v7523;	// L11955
    bool v7528 = v7527 | v7524;	// L11956
    bool v7529 = v7528 | v7525;	// L11957
    bool v7530 = v7529 | v7526;	// L11958
    if (v7530) {	// L11959
      binop8 = 1;	// L11960
    }
    int32_t raw8;	// L11962
    raw8 = 0;	// L11963
    int32_t cmp_busy8;	// L11964
    cmp_busy8 = 0;	// L11965
    l_S_k_5_k16: for (int k16 = 0; k16 < 4; k16++) {	// L11966
      uint8_t v7534 = sb_v8[(k16 + 1)];	// L11967
      int32_t v7535 = v7534;	// L11968
      bool v7536 = v7535 == 1;	// L11969
      uint8_t v7537 = sb_rtr8[(k16 + 1)];	// L11970
      int32_t v7538 = v7537;	// L11971
      bool v7539 = v7538 == 0;	// L11972
      uint8_t v7540 = sb_dst8[(k16 + 1)];	// L11973
      int32_t v7541 = v7540;	// L11974
      bool v7542 = v7541 < 12;	// L11975
      bool v7543 = v7536 & v7539;	// L11976
      bool v7544 = v7543 & v7542;	// L11977
      if (v7544) {	// L11978
        int32_t v7545 = s18;	// L11979
        bool v7546 = v7545 < 12;	// L11980
        uint8_t v7547 = sb_dst8[(k16 + 1)];	// L11981
        int32_t v7548 = v7547;	// L11982
        int32_t v7549 = v7548 & 7;	// L11983
        int32_t v7550 = v7545 & 7;	// L11984
        bool v7551 = v7549 == v7550;	// L11985
        bool v7552 = v7546 & v7551;	// L11986
        if (v7552) {	// L11987
          raw8 = 1;	// L11988
        }
        int32_t v7553 = binop8;	// L11990
        bool v7554 = v7553 == 1;	// L11991
        int32_t v7555 = s28;	// L11992
        bool v7556 = v7555 < 12;	// L11993
        uint8_t v7557 = sb_dst8[(k16 + 1)];	// L11994
        int32_t v7558 = v7557;	// L11995
        int32_t v7559 = v7558 & 7;	// L11996
        int32_t v7560 = v7555 & 7;	// L11997
        bool v7561 = v7559 == v7560;	// L11998
        bool v7562 = v7554 & v7556;	// L11999
        bool v7563 = v7562 & v7561;	// L12000
        if (v7563) {	// L12001
          raw8 = 1;	// L12002
        }
      }
      uint8_t v7564 = sb_v8[(k16 + 1)];	// L12005
      int32_t v7565 = v7564;	// L12006
      bool v7566 = v7565 == 1;	// L12007
      uint8_t v7567 = sb_cmp8[(k16 + 1)];	// L12008
      int32_t v7568 = v7567;	// L12009
      bool v7569 = v7568 == 1;	// L12010
      bool v7570 = v7566 & v7569;	// L12011
      if (v7570) {	// L12012
        cmp_busy8 = 1;	// L12013
      }
    }
    int32_t is_cond8;	// L12016
    is_cond8 = 0;	// L12017
    int32_t v7572 = op8;	// L12018
    bool v7573 = v7572 >= 12;	// L12019
    ap_int<33> v7574 = v7572;	// L12020
    bool v7575 = v7574 <= 15;	// L12021
    bool v7576 = v7573 & v7575;	// L12022
    if (v7576) {	// L12023
      is_cond8 = 1;	// L12024
    }
    int32_t grant8;	// L12026
    grant8 = 0;	// L12027
    int32_t v7578 = pc8;	// L12028
    bool v7579 = v7578 >= 0;	// L12029
    if (v7579) {	// L12030
      grant8 = 1;	// L12031
    }
    int32_t v7580 = pc8;	// L12033
    bool v7581 = v7580 >= 0;	// L12034
    int32_t v7582 = a_vld8;	// L12035
    bool v7583 = v7582 == 0;	// L12036
    int32_t v7584 = binop8;	// L12037
    bool v7585 = v7584 == 1;	// L12038
    int32_t v7586 = b_vld8;	// L12039
    bool v7587 = v7586 == 0;	// L12040
    bool v7588 = v7585 & v7587;	// L12041
    bool v7589 = v7583 | v7588;	// L12042
    bool v7590 = v7581 & v7589;	// L12043
    if (v7590) {	// L12044
      grant8 = 0;	// L12045
    }
    int32_t v7591 = pc8;	// L12047
    bool v7592 = v7591 >= 0;	// L12048
    int32_t v7593 = raw8;	// L12049
    bool v7594 = v7593 == 1;	// L12050
    int32_t v7595 = is_cond8;	// L12051
    bool v7596 = v7595 == 1;	// L12052
    int32_t v7597 = cmp_busy8;	// L12053
    bool v7598 = v7597 == 1;	// L12054
    bool v7599 = v7596 & v7598;	// L12055
    bool v7600 = v7594 | v7599;	// L12056
    bool v7601 = v7592 & v7600;	// L12057
    if (v7601) {	// L12058
      grant8 = 0;	// L12059
    }
    int32_t v7602 = grant8;	// L12061
    bool v7603 = v7602 == 1;	// L12062
    if (v7603) {	// L12063
      int8_t v7604 = instr_cnt8;	// L12064
      int32_t v7605 = cfg_isz8;	// L12065
      int32_t v7606 = v7604;	// L12066
      bool v7607 = v7606 == v7605;	// L12067
      if (v7607) {	// L12068
        instr_cnt8 = 0;	// L12069
        int8_t v7608 = iter_cnt8;	// L12070
        int32_t v7609 = cfg_itsz8;	// L12071
        ap_int<33> v7610 = v7609;	// L12072
        ap_int<33> v7611 = v7610 - 1;	// L12073
        ap_int<33> v7612 = v7608;	// L12074
        bool v7613 = v7612 == v7611;	// L12075
        if (v7613) {	// L12076
          fetch_en8 = 0;	// L12077
        } else {
          int8_t v7614 = iter_cnt8;	// L12079
          ap_int<33> v7615 = v7614;	// L12080
          ap_int<33> v7616 = v7615 + 1;	// L12081
          uint8_t v7617 = v7616;	// L12082
          iter_cnt8 = v7617;	// L12083
        }
      } else {
        int8_t v7618 = instr_cnt8;	// L12086
        ap_int<33> v7619 = v7618;	// L12087
        ap_int<33> v7620 = v7619 + 1;	// L12088
        uint8_t v7621 = v7620;	// L12089
        instr_cnt8 = v7621;	// L12090
      }
    }
    int32_t c18;	// L12093
    c18 = -1;	// L12094
    int32_t c28;	// L12095
    c28 = -1;	// L12096
    int32_t v7624 = grant8;	// L12097
    bool v7625 = v7624 == 1;	// L12098
    int32_t v7626 = s18;	// L12099
    bool v7627 = v7626 >= 12;	// L12100
    bool v7628 = v7625 & v7627;	// L12101
    if (v7628) {	// L12102
      int32_t v7629 = s18;	// L12103
      int32_t v7630 = v7629 & 3;	// L12104
      c18 = v7630;	// L12105
    }
    int32_t v7631 = grant8;	// L12107
    bool v7632 = v7631 == 1;	// L12108
    int32_t v7633 = s28;	// L12109
    bool v7634 = v7633 >= 12;	// L12110
    bool v7635 = v7632 & v7634;	// L12111
    if (v7635) {	// L12112
      int32_t v7636 = s28;	// L12113
      int32_t v7637 = v7636 & 3;	// L12114
      c28 = v7637;	// L12115
    }
    int32_t v7638 = c18;	// L12117
    bool v7639 = v7638 >= 0;	// L12118
    if (v7639) {	// L12119
      int32_t v7640 = c18;	// L12120
      int v7641 = v7640;	// L12121
      half v7642 = hold_v8[v7641][1];	// L12122
      hold_v8[v7641][0] = v7642;	// L12123
      int32_t v7643 = c18;	// L12124
      int v7644 = v7643;	// L12125
      uint8_t v7645 = hold_cnt8[v7644];	// L12126
      ap_int<33> v7646 = v7645;	// L12127
      ap_int<33> v7647 = v7646 - 1;	// L12128
      uint8_t v7648 = v7647;	// L12129
      hold_cnt8[v7644] = v7648;	// L12130
    }
    int32_t v7649 = c28;	// L12132
    bool v7650 = v7649 >= 0;	// L12133
    int32_t v7651 = c18;	// L12134
    bool v7652 = v7649 != v7651;	// L12135
    bool v7653 = v7650 & v7652;	// L12136
    if (v7653) {	// L12137
      int32_t v7654 = c28;	// L12138
      int v7655 = v7654;	// L12139
      half v7656 = hold_v8[v7655][1];	// L12140
      hold_v8[v7655][0] = v7656;	// L12141
      int32_t v7657 = c28;	// L12142
      int v7658 = v7657;	// L12143
      uint8_t v7659 = hold_cnt8[v7658];	// L12144
      ap_int<33> v7660 = v7659;	// L12145
      ap_int<33> v7661 = v7660 - 1;	// L12146
      uint8_t v7662 = v7661;	// L12147
      hold_cnt8[v7658] = v7662;	// L12148
    }
    int32_t v7663 = grant8;	// L12150
    bool v7664 = v7663 == 1;	// L12151
    int32_t v7665 = s18;	// L12152
    bool v7666 = v7665 < 8;	// L12153
    int32_t v7667 = dsmask8;	// L12154
    int32_t v7668 = v7667 >> v7665;	// L12155
    int32_t v7669 = v7668 & 1;	// L12156
    bool v7670 = v7669 == 1;	// L12157
    bool v7671 = v7664 & v7666;	// L12158
    bool v7672 = v7671 & v7670;	// L12159
    if (v7672) {	// L12160
      int32_t v7673 = s18;	// L12161
      int v7674 = v7673;	// L12162
      drf_full8[v7674] = 0;	// L12163
    }
    int32_t v7675 = grant8;	// L12165
    bool v7676 = v7675 == 1;	// L12166
    int32_t v7677 = s28;	// L12167
    bool v7678 = v7677 < 8;	// L12168
    int32_t v7679 = dsmask8;	// L12169
    int32_t v7680 = v7679 >> v7677;	// L12170
    int32_t v7681 = v7680 & 1;	// L12171
    bool v7682 = v7681 == 1;	// L12172
    bool v7683 = v7676 & v7678;	// L12173
    bool v7684 = v7683 & v7682;	// L12174
    if (v7684) {	// L12175
      int32_t v7685 = s28;	// L12176
      int v7686 = v7685;	// L12177
      drf_full8[v7686] = 0;	// L12178
    }
    half res8;
#pragma HLS dependence variable=res8 type=inter dependent=false	// L12180
    res8 = 0.000000;	// L12181
    int32_t v7688 = op8;	// L12182
    bool v7689 = v7688 == 0;	// L12183
    if (v7689) {	// L12184
      half v7690 = a8;	// L12185
      half v7691 = b8;	// L12186
      half v7692 = v7690 + v7691;	// L12187
      res8 = v7692;	// L12188
    } else {
      int32_t v7693 = op8;	// L12190
      bool v7694 = v7693 == 1;	// L12191
      if (v7694) {	// L12192
        half v7695 = a8;	// L12193
        half v7696 = b8;	// L12194
        half v7697 = v7695 - v7696;	// L12195
        res8 = v7697;	// L12196
      } else {
        int32_t v7698 = op8;	// L12198
        bool v7699 = v7698 == 2;	// L12199
        if (v7699) {	// L12200
          half v7700 = a8;	// L12201
          half v7701 = b8;	// L12202
          half v7702 = v7700 * v7701;	// L12203
          res8 = v7702;	// L12204
        } else {
          int32_t v7703 = op8;	// L12206
          bool v7704 = v7703 == 8;	// L12207
          if (v7704) {	// L12208
            half v7705 = a8;	// L12209
            half v7706 = b8;	// L12210
            bool v7707 = v7705 >= v7706;	// L12211
            if (v7707) {	// L12212
              res8 = 1.000000;	// L12213
            } else {
              res8 = -1.000000;	// L12215
            }
          } else {
            int32_t v7708 = op8;	// L12218
            bool v7709 = v7708 == 9;	// L12219
            if (v7709) {	// L12220
              half v7710 = a8;	// L12221
              half v7711 = b8;	// L12222
              bool v7712 = v7710 < v7711;	// L12223
              if (v7712) {	// L12224
                res8 = 1.000000;	// L12225
              } else {
                res8 = -1.000000;	// L12227
              }
            } else {
              half v7713 = a8;	// L12230
              res8 = v7713;	// L12231
            }
          }
        }
      }
    }
    int32_t v7714 = a_vld8;	// L12237
    int32_t res_vld8;	// L12238
    res_vld8 = v7714;	// L12239
    int32_t v7716 = op8;	// L12240
    bool v7717 = v7716 == 0;	// L12241
    bool v7718 = v7716 == 1;	// L12242
    bool v7719 = v7716 == 2;	// L12243
    bool v7720 = v7716 == 8;	// L12244
    bool v7721 = v7716 == 9;	// L12245
    bool v7722 = v7717 | v7718;	// L12246
    bool v7723 = v7722 | v7719;	// L12247
    bool v7724 = v7723 | v7720;	// L12248
    bool v7725 = v7724 | v7721;	// L12249
    if (v7725) {	// L12250
      int32_t v7726 = a_vld8;	// L12251
      int32_t v7727 = b_vld8;	// L12252
      int64_t v7728 = v7726;	// L12253
      int64_t v7729 = v7727;	// L12254
      int64_t v7730 = v7728 * v7729;	// L12255
      int32_t v7731 = v7730;	// L12256
      res_vld8 = v7731;	// L12257
    }
    int32_t v7732 = grant8;	// L12259
    bool v7733 = v7732 == 0;	// L12260
    if (v7733) {	// L12261
      res_vld8 = 0;	// L12262
    }
    int32_t is_rtr8;	// L12264
    is_rtr8 = 0;	// L12265
    int32_t v7735 = op8;	// L12266
    bool v7736 = v7735 >= 4;	// L12267
    ap_int<33> v7737 = v7735;	// L12268
    bool v7738 = v7737 <= 7;	// L12269
    bool v7739 = v7736 & v7738;	// L12270
    if (v7739) {	// L12271
      is_rtr8 = 1;	// L12272
    }
    l_S_k_6_k17: for (int k17 = 0; k17 < 4; k17++) {	// L12274
      uint8_t v7741 = sb_v8[(k17 + 1)];	// L12275
      sb_v8[k17] = v7741;	// L12276
      uint8_t v7742 = sb_dst8[(k17 + 1)];	// L12277
      sb_dst8[k17] = v7742;	// L12278
      uint8_t v7743 = sb_cmp8[(k17 + 1)];	// L12279
      sb_cmp8[k17] = v7743;	// L12280
      uint8_t v7744 = sb_rtr8[(k17 + 1)];	// L12281
      sb_rtr8[k17] = v7744;	// L12282
      uint8_t v7745 = sb_inj8[(k17 + 1)];	// L12283
      sb_inj8[k17] = v7745;	// L12284
      uint8_t v7746 = sb_dir8[(k17 + 1)];	// L12285
      sb_dir8[k17] = v7746;	// L12286
      uint8_t v7747 = sb_id8[(k17 + 1)];	// L12287
      sb_id8[k17] = v7747;	// L12288
      uint8_t v7748 = sb_rvld8[(k17 + 1)];	// L12289
      sb_rvld8[k17] = v7748;	// L12290
      uint8_t v7749 = sb_ix8[(k17 + 1)];	// L12291
      sb_ix8[k17] = v7749;	// L12292
    }
    sb_v8[4] = 0;	// L12294
    int32_t v7750 = grant8;	// L12295
    bool v7751 = v7750 == 1;	// L12296
    if (v7751) {	// L12297
      half v7752 = res8;	// L12298
      int8_t v7753 = resq_wr8;	// L12299
      int v7754 = v7753;	// L12300
      resq8[v7754] = v7752;	// L12301
      int32_t cq8;	// L12302
      cq8 = 0;	// L12303
      int32_t v7756 = op8;	// L12304
      bool v7757 = v7756 == 8;	// L12305
      if (v7757) {	// L12306
        half v7758 = a8;	// L12307
        half v7759 = b8;	// L12308
        bool v7760 = v7758 >= v7759;	// L12309
        if (v7760) {	// L12310
          cq8 = 1;	// L12311
        }
      }
      int32_t v7761 = op8;	// L12314
      bool v7762 = v7761 == 9;	// L12315
      if (v7762) {	// L12316
        half v7763 = a8;	// L12317
        half v7764 = b8;	// L12318
        bool v7765 = v7763 < v7764;	// L12319
        if (v7765) {	// L12320
          cq8 = 1;	// L12321
        }
      }
      int32_t v7766 = cq8;	// L12324
      uint8_t v7767 = v7766;	// L12325
      int8_t v7768 = resq_wr8;	// L12326
      int v7769 = v7768;	// L12327
      cmpq8[v7769] = v7767;	// L12328
      sb_v8[4] = 1;	// L12329
      int32_t v7770 = dst8;	// L12330
      uint8_t v7771 = v7770;	// L12331
      sb_dst8[4] = v7771;	// L12332
      int8_t v7772 = resq_wr8;	// L12333
      sb_ix8[4] = v7772;	// L12334
      sb_cmp8[4] = 0;	// L12335
      int32_t v7773 = op8;	// L12336
      bool v7774 = v7773 == 8;	// L12337
      bool v7775 = v7773 == 9;	// L12338
      bool v7776 = v7774 | v7775;	// L12339
      if (v7776) {	// L12340
        sb_cmp8[4] = 1;	// L12341
      }
      int32_t v7777 = is_rtr8;	// L12343
      int32_t rtrf8;	// L12344
      rtrf8 = v7777;	// L12345
      int32_t v7779 = is_cond8;	// L12346
      bool v7780 = v7779 == 1;	// L12347
      if (v7780) {	// L12348
        rtrf8 = 1;	// L12349
      }
      int32_t v7781 = rtrf8;	// L12351
      uint8_t v7782 = v7781;	// L12352
      sb_rtr8[4] = v7782;	// L12353
      int32_t v7783 = is_rtr8;	// L12354
      int32_t inj8;	// L12355
      inj8 = v7783;	// L12356
      int32_t v7785 = is_cond8;	// L12357
      bool v7786 = v7785 == 1;	// L12358
      int8_t v7787 = condition_reg8;	// L12359
      int32_t v7788 = v7787;	// L12360
      bool v7789 = v7788 == 1;	// L12361
      bool v7790 = v7786 & v7789;	// L12362
      if (v7790) {	// L12363
        inj8 = 1;	// L12364
      }
      int32_t v7791 = inj8;	// L12366
      uint8_t v7792 = v7791;	// L12367
      sb_inj8[4] = v7792;	// L12368
      int32_t v7793 = op8;	// L12369
      int32_t v7794 = v7793 & 3;	// L12370
      uint8_t v7795 = v7794;	// L12371
      sb_dir8[4] = v7795;	// L12372
      int32_t v7796 = s28;	// L12373
      uint8_t v7797 = v7796;	// L12374
      sb_id8[4] = v7797;	// L12375
      int32_t v7798 = res_vld8;	// L12376
      uint8_t v7799 = v7798;	// L12377
      sb_rvld8[4] = v7799;	// L12378
      int8_t v7800 = resq_wr8;	// L12379
      ap_int<33> v7801 = v7800;	// L12380
      ap_int<33> v7802 = v7801 + 1;	// L12381
      ap_int<33> v7803 = v7802 & 7;	// L12382
      uint8_t v7804 = v7803;	// L12383
      resq_wr8 = v7804;	// L12384
    }
    ap_int<17> v7805 = tx_n8;	// L12386
    txn_r8 = v7805;	// L12387
    ap_int<17> v7806 = tx_s8;	// L12388
    txs_r8 = v7806;	// L12389
    ap_int<17> v7807 = tx_w8;	// L12390
    txw_r8 = v7807;	// L12391
    ap_int<17> v7808 = tx_e8;	// L12392
    txe_r8 = v7808;	// L12393
    int32_t v7809 = crv_vld8;	// L12394
    bool v7810 = v7809 == 1;	// L12395
    if (v7810) {	// L12396
      int32_t v7811 = crv_mode8;	// L12397
      bool v7812 = v7811 == 1;	// L12398
      if (v7812) {	// L12399
        int32_t v7813 = crv_addr8;	// L12400
        int32_t v7814 = v7813 >> 3;	// L12401
        int32_t v7815 = v7814 & 1;	// L12402
        bool v7816 = v7815 == 1;	// L12403
        if (v7816) {	// L12404
          int32_t v7817 = crv_raw8;	// L12405
          int32_t v7818 = crv_addr8;	// L12406
          int32_t v7819 = v7818 & 7;	// L12407
          int v7820 = v7819;	// L12408
          irf8[v7820] = v7817;	// L12409
        } else {
          int32_t v7821 = crv_addr8;	// L12411
          bool v7822 = v7821 == 0;	// L12412
          if (v7822) {	// L12413
            int32_t v7823 = crv_raw8;	// L12414
            int32_t v7824 = v7823 & 255;	// L12415
            dsmask8 = v7824;	// L12416
            int32_t v7825 = crv_raw8;	// L12417
            int32_t v7826 = v7825 >> 8;	// L12418
            int32_t v7827 = v7826 & 7;	// L12419
            cfg_isz8 = v7827;	// L12420
            int32_t v7828 = crv_raw8;	// L12421
            int32_t v7829 = v7828 >> 15;	// L12422
            int32_t v7830 = v7829 & 1;	// L12423
            bool v7831 = v7830 == 1;	// L12424
            if (v7831) {	// L12425
              fetch_en8 = 1;	// L12426
              instr_cnt8 = 0;	// L12427
              iter_cnt8 = 0;	// L12428
            }
          } else {
            int32_t v7832 = crv_addr8;	// L12431
            bool v7833 = v7832 == 1;	// L12432
            if (v7833) {	// L12433
              int32_t v7834 = crv_raw8;	// L12434
              int32_t v7835 = v7834 & 255;	// L12435
              cfg_itsz8 = v7835;	// L12436
            }
          }
        }
      } else {
        int32_t v7836 = crv_addr8;	// L12441
        bool v7837 = v7836 < 8;	// L12442
        int32_t v7838 = dsmask8;	// L12443
        int32_t v7839 = v7838 >> v7836;	// L12444
        int32_t v7840 = v7839 & 1;	// L12445
        bool v7841 = v7840 == 1;	// L12446
        bool v7842 = v7837 & v7841;	// L12447
        if (v7842) {	// L12448
          int32_t v7843 = crv_addr8;	// L12449
          int v7844 = v7843;	// L12450
          int32_t v7845 = drf_full8[v7844];	// L12451
          bool v7846 = v7845 == 0;	// L12452
          if (v7846) {	// L12453
            half v7847 = crv_data8;	// L12454
            int32_t v7848 = crv_addr8;	// L12455
            int v7849 = v7848;	// L12456
            drf8[v7849] = v7847;	// L12457
            int32_t v7850 = crv_addr8;	// L12458
            int v7851 = v7850;	// L12459
            drf_full8[v7851] = 1;	// L12460
          }
        } else {
          half v7852 = crv_data8;	// L12463
          int32_t v7853 = crv_addr8;	// L12464
          int v7854 = v7853;	// L12465
          drf8[v7854] = v7852;	// L12466
        }
      }
    }
    ap_int<17> v7855 = txe_r8;	// L12470
    bool v7856;
    ap_int<17> v7856_tmp = v7855;
    v7856 = v7856_tmp[0];	// L12471
    int32_t v7857 = v7856;	// L12472
    bool v7858 = v7857 == 1;	// L12473
    if (v7858) {	// L12474
      ap_int<17> v7859 = txe_r8;	// L12475
      v7012.write(v7859);	// L12476
    }
    ap_int<17> v7860 = txw_r8;	// L12478
    bool v7861;
    ap_int<17> v7861_tmp = v7860;
    v7861 = v7861_tmp[0];	// L12479
    int32_t v7862 = v7861;	// L12480
    bool v7863 = v7862 == 1;	// L12481
    if (v7863) {	// L12482
      ap_int<17> v7864 = txw_r8;	// L12483
      v7013.write(v7864);	// L12484
    }
    ap_int<17> v7865 = txs_r8;	// L12486
    bool v7866;
    ap_int<17> v7866_tmp = v7865;
    v7866 = v7866_tmp[0];	// L12487
    int32_t v7867 = v7866;	// L12488
    bool v7868 = v7867 == 1;	// L12489
    if (v7868) {	// L12490
      ap_int<17> v7869 = txs_r8;	// L12491
      v7014.write(v7869);	// L12492
    }
    ap_int<17> v7870 = txn_r8;	// L12494
    bool v7871;
    ap_int<17> v7871_tmp = v7870;
    v7871 = v7871_tmp[0];	// L12495
    int32_t v7872 = v7871;	// L12496
    bool v7873 = v7872 == 1;	// L12497
    if (v7873) {	// L12498
      ap_int<17> v7874 = txn_r8;	// L12499
      v7015.write(v7874);	// L12500
    }
  }
}

void node_2_1(
  hls::stream< ap_uint<26> >& v7875,
  hls::stream< ap_uint<26> >& v7876,
  hls::stream< ap_uint<26> >& v7877,
  hls::stream< ap_uint<26> >& v7878,
  hls::stream< ap_uint<26> >& v7879,
  hls::stream< ap_uint<26> >& v7880,
  hls::stream< ap_uint<26> >& v7881,
  hls::stream< ap_uint<26> >& v7882,
  hls::stream< ap_uint<17> >& v7883,
  hls::stream< ap_uint<17> >& v7884,
  hls::stream< ap_uint<17> >& v7885,
  hls::stream< ap_uint<17> >& v7886,
  hls::stream< ap_uint<17> >& v7887,
  hls::stream< ap_uint<17> >& v7888,
  hls::stream< ap_uint<17> >& v7889,
  hls::stream< ap_uint<17> >& v7890
) {	// L12505
  int32_t irf9[8];	// L12538
  #pragma HLS array_partition variable=irf9 complete dim=1

  for (int v7892 = 0; v7892 < 8; v7892++) {	// L12539
    irf9[v7892] = 0;	// L12539
  }
  half drf9[8];	// L12540
  #pragma HLS array_partition variable=drf9 complete dim=1

  for (int v7894 = 0; v7894 < 8; v7894++) {	// L12541
    drf9[v7894] = 0.000000;	// L12541
  }
  int32_t drf_full9[8];	// L12542
  #pragma HLS array_partition variable=drf_full9 complete dim=1

  for (int v7896 = 0; v7896 < 8; v7896++) {	// L12543
    drf_full9[v7896] = 0;	// L12543
  }
  int32_t dsmask9;	// L12544
  dsmask9 = 0;	// L12545
  int32_t crv_vld9;	// L12546
  crv_vld9 = 0;	// L12547
  half crv_data9;	// L12548
  crv_data9 = 0.000000;	// L12549
  int32_t crv_addr9;	// L12550
  crv_addr9 = 0;	// L12551
  int32_t crv_mode9;	// L12552
  crv_mode9 = 0;	// L12553
  int32_t crv_raw9;	// L12554
  crv_raw9 = 0;	// L12555
  int32_t csd_vld9;	// L12556
  csd_vld9 = 0;	// L12557
  ap_uint<26> csd_pkt9;	// L12558
  csd_pkt9 = 0;	// L12559
  int32_t csd_dir9;	// L12560
  csd_dir9 = 0;	// L12561
  int32_t row_id9;	// L12562
  row_id9 = 2;	// L12563
  int32_t col_id9;	// L12564
  col_id9 = 1;	// L12565
  ap_uint<17> txn_r9;	// L12566
  txn_r9 = 0;	// L12567
  ap_uint<17> txs_r9;	// L12568
  txs_r9 = 0;	// L12569
  ap_uint<17> txw_r9;	// L12570
  txw_r9 = 0;	// L12571
  ap_uint<17> txe_r9;	// L12572
  txe_r9 = 0;	// L12573
  half hold_v9[4][2];	// L12574
  #pragma HLS array_partition variable=hold_v9 complete dim=1
  #pragma HLS array_partition variable=hold_v9 complete dim=2

  for (int v7913 = 0; v7913 < 4; v7913++) {	// L12575
    for (int v7914 = 0; v7914 < 2; v7914++) {	// L12575
      hold_v9[v7913][v7914] = 0.000000;	// L12575
    }
  }
  uint8_t hold_cnt9[4];	// L12576
  #pragma HLS array_partition variable=hold_cnt9 complete dim=1

  for (int v7916 = 0; v7916 < 4; v7916++) {	// L12577
    hold_cnt9[v7916] = 0;	// L12577
  }
  int32_t crv_ever9;	// L12578
  crv_ever9 = 0;	// L12579
  int32_t fe_ever9;	// L12580
  fe_ever9 = 0;	// L12581
  ap_uint<26> rbuf9[4][2];	// L12582
  #pragma HLS array_partition variable=rbuf9 complete dim=1
  #pragma HLS array_partition variable=rbuf9 complete dim=2

  for (int v7920 = 0; v7920 < 4; v7920++) {	// L12583
    for (int v7921 = 0; v7921 < 2; v7921++) {	// L12583
      rbuf9[v7920][v7921] = 0;	// L12583
    }
  }
  uint8_t rbcnt9[4];	// L12584
  #pragma HLS array_partition variable=rbcnt9 complete dim=1

  for (int v7923 = 0; v7923 < 4; v7923++) {	// L12585
    rbcnt9[v7923] = 0;	// L12585
  }
  int32_t cfg_isz9;	// L12586
  cfg_isz9 = 0;	// L12587
  int32_t cfg_itsz9;	// L12588
  cfg_itsz9 = 0;	// L12589
  uint8_t fetch_en9;	// L12590
  fetch_en9 = 0;	// L12591
  uint8_t instr_cnt9;	// L12592
  instr_cnt9 = 0;	// L12593
  uint8_t iter_cnt9;	// L12594
  iter_cnt9 = 0;	// L12595
  uint8_t condition_reg9;	// L12596
  condition_reg9 = 0;	// L12597
  uint8_t sb_v9[5];	// L12598
  #pragma HLS array_partition variable=sb_v9 complete dim=1

  for (int v7931 = 0; v7931 < 5; v7931++) {	// L12599
    sb_v9[v7931] = 0;	// L12599
  }
  uint8_t sb_dst9[5];	// L12600
  #pragma HLS array_partition variable=sb_dst9 complete dim=1

  for (int v7933 = 0; v7933 < 5; v7933++) {	// L12601
    sb_dst9[v7933] = 0;	// L12601
  }
  uint8_t sb_cmp9[5];	// L12602
  #pragma HLS array_partition variable=sb_cmp9 complete dim=1

  for (int v7935 = 0; v7935 < 5; v7935++) {	// L12603
    sb_cmp9[v7935] = 0;	// L12603
  }
  uint8_t sb_rtr9[5];	// L12604
  #pragma HLS array_partition variable=sb_rtr9 complete dim=1

  for (int v7937 = 0; v7937 < 5; v7937++) {	// L12605
    sb_rtr9[v7937] = 0;	// L12605
  }
  uint8_t sb_inj9[5];	// L12606
  #pragma HLS array_partition variable=sb_inj9 complete dim=1

  for (int v7939 = 0; v7939 < 5; v7939++) {	// L12607
    sb_inj9[v7939] = 0;	// L12607
  }
  uint8_t sb_dir9[5];	// L12608
  #pragma HLS array_partition variable=sb_dir9 complete dim=1

  for (int v7941 = 0; v7941 < 5; v7941++) {	// L12609
    sb_dir9[v7941] = 0;	// L12609
  }
  uint8_t sb_id9[5];	// L12610
  #pragma HLS array_partition variable=sb_id9 complete dim=1

  for (int v7943 = 0; v7943 < 5; v7943++) {	// L12611
    sb_id9[v7943] = 0;	// L12611
  }
  uint8_t sb_rvld9[5];	// L12612
  #pragma HLS array_partition variable=sb_rvld9 complete dim=1

  for (int v7945 = 0; v7945 < 5; v7945++) {	// L12613
    sb_rvld9[v7945] = 0;	// L12613
  }
  uint8_t sb_ix9[5];	// L12614
  #pragma HLS array_partition variable=sb_ix9 complete dim=1

  for (int v7947 = 0; v7947 < 5; v7947++) {	// L12615
    sb_ix9[v7947] = 0;	// L12615
  }
  half resq9[8];	// L12616
  #pragma HLS array_partition variable=resq9 complete dim=1
#pragma HLS dependence variable=resq9 type=inter dependent=false

  for (int v7949 = 0; v7949 < 8; v7949++) {	// L12617
    resq9[v7949] = 0.000000;	// L12617
  }
  uint8_t cmpq9[8];	// L12618
  #pragma HLS array_partition variable=cmpq9 complete dim=1
#pragma HLS dependence variable=cmpq9 type=inter dependent=false

  for (int v7951 = 0; v7951 < 8; v7951++) {	// L12619
    cmpq9[v7951] = 0;	// L12619
  }
  uint8_t resq_wr9;	// L12620
  resq_wr9 = 0;	// L12621
  l_S_t_0_t9: for (int t9 = 0; t9 < 374; t9++) {	// L12622
  #pragma HLS pipeline II=1
    ap_uint<26> p_w9;	// L12623
    p_w9 = 0;	// L12624
    ap_uint<26> p_e9;	// L12625
    p_e9 = 0;	// L12626
    ap_uint<26> p_n9;	// L12627
    p_n9 = 0;	// L12628
    ap_uint<26> p_s9;	// L12629
    p_s9 = 0;	// L12630
    uint8_t v7958 = rbcnt9[0];	// L12631
    int32_t v7959 = v7958;	// L12632
    bool v7960 = v7959 < 2;	// L12633
    if (v7960) {	// L12634
      ap_uint<26> v7961;
      bool v7962 = v7875.read_nb(v7961);
	// L12635
      ap_uint<26> gw9;	// L12636
      gw9 = v7961;	// L12637
      bool okw9;	// L12638
      okw9 = v7962;	// L12639
      bool v7965 = okw9;	// L12640
      if (v7965) {	// L12641
        ap_int<26> v7966 = gw9;	// L12642
        p_w9 = v7966;	// L12643
      }
    }
    uint8_t v7967 = rbcnt9[1];	// L12646
    int32_t v7968 = v7967;	// L12647
    bool v7969 = v7968 < 2;	// L12648
    if (v7969) {	// L12649
      ap_uint<26> v7970;
      bool v7971 = v7876.read_nb(v7970);
	// L12650
      ap_uint<26> ge9;	// L12651
      ge9 = v7970;	// L12652
      bool oke9;	// L12653
      oke9 = v7971;	// L12654
      bool v7974 = oke9;	// L12655
      if (v7974) {	// L12656
        ap_int<26> v7975 = ge9;	// L12657
        p_e9 = v7975;	// L12658
      }
    }
    uint8_t v7976 = rbcnt9[2];	// L12661
    int32_t v7977 = v7976;	// L12662
    bool v7978 = v7977 < 2;	// L12663
    if (v7978) {	// L12664
      ap_uint<26> v7979;
      bool v7980 = v7877.read_nb(v7979);
	// L12665
      ap_uint<26> gn9;	// L12666
      gn9 = v7979;	// L12667
      bool okn9;	// L12668
      okn9 = v7980;	// L12669
      bool v7983 = okn9;	// L12670
      if (v7983) {	// L12671
        ap_int<26> v7984 = gn9;	// L12672
        p_n9 = v7984;	// L12673
      }
    }
    uint8_t v7985 = rbcnt9[3];	// L12676
    int32_t v7986 = v7985;	// L12677
    bool v7987 = v7986 < 2;	// L12678
    if (v7987) {	// L12679
      ap_uint<26> v7988;
      bool v7989 = v7878.read_nb(v7988);
	// L12680
      ap_uint<26> gs9;	// L12681
      gs9 = v7988;	// L12682
      bool oks9;	// L12683
      oks9 = v7989;	// L12684
      bool v7992 = oks9;	// L12685
      if (v7992) {	// L12686
        ap_int<26> v7993 = gs9;	// L12687
        p_s9 = v7993;	// L12688
      }
    }
    ap_uint<26> fin9[4];	// L12691
    for (int v7995 = 0; v7995 < 4; v7995++) {	// L12692
      fin9[v7995] = 0;	// L12692
    }
    ap_int<26> v7996 = p_w9;	// L12693
    fin9[0] = v7996;	// L12694
    ap_int<26> v7997 = p_e9;	// L12695
    fin9[1] = v7997;	// L12696
    ap_int<26> v7998 = p_n9;	// L12697
    fin9[2] = v7998;	// L12698
    ap_int<26> v7999 = p_s9;	// L12699
    fin9[3] = v7999;	// L12700
    l_S_d_0_d36: for (int d36 = 0; d36 < 4; d36++) {	// L12701
      ap_uint<26> v8001 = fin9[d36];	// L12702
      bool v8002;
      ap_int<26> v8002_tmp = v8001;
      v8002 = v8002_tmp[25];	// L12703
      int32_t v8003 = v8002;	// L12704
      bool v8004 = v8003 == 1;	// L12705
      uint8_t v8005 = rbcnt9[d36];	// L12706
      int32_t v8006 = v8005;	// L12707
      bool v8007 = v8006 < 2;	// L12708
      bool v8008 = v8004 & v8007;	// L12709
      if (v8008) {	// L12710
        ap_uint<26> v8009 = fin9[d36];	// L12711
        uint8_t v8010 = rbcnt9[d36];	// L12712
        int v8011 = v8010;	// L12713
        rbuf9[d36][v8011] = v8009;	// L12714
        uint8_t v8012 = rbcnt9[d36];	// L12715
        ap_int<33> v8013 = v8012;	// L12716
        ap_int<33> v8014 = v8013 + 1;	// L12717
        uint8_t v8015 = v8014;	// L12718
        rbcnt9[d36] = v8015;	// L12719
      }
    }
    ap_uint<26> hd9[4];	// L12722
    for (int v8017 = 0; v8017 < 4; v8017++) {	// L12723
      hd9[v8017] = 0;	// L12723
    }
    int32_t hvld9[4];	// L12724
    for (int v8019 = 0; v8019 < 4; v8019++) {	// L12725
      hvld9[v8019] = 0;	// L12725
    }
    int32_t hit9[4];	// L12726
    for (int v8021 = 0; v8021 < 4; v8021++) {	// L12727
      hit9[v8021] = 0;	// L12727
    }
    int32_t axis9[4];	// L12728
    for (int v8023 = 0; v8023 < 4; v8023++) {	// L12729
      axis9[v8023] = 0;	// L12729
    }
    int32_t v8024 = col_id9;	// L12730
    axis9[0] = v8024;	// L12731
    int32_t v8025 = col_id9;	// L12732
    axis9[1] = v8025;	// L12733
    int32_t v8026 = row_id9;	// L12734
    axis9[2] = v8026;	// L12735
    int32_t v8027 = row_id9;	// L12736
    axis9[3] = v8027;	// L12737
    l_S_d_1_d37: for (int d37 = 0; d37 < 4; d37++) {	// L12738
      uint8_t v8029 = rbcnt9[d37];	// L12739
      int32_t v8030 = v8029;	// L12740
      bool v8031 = v8030 > 0;	// L12741
      if (v8031) {	// L12742
        ap_uint<26> v8032 = rbuf9[d37][0];	// L12743
        hd9[d37] = v8032;	// L12744
        hvld9[d37] = 1;	// L12745
        ap_uint<26> v8033 = hd9[d37];	// L12746
        ap_int<4> v8034;
        ap_int<26> v8034_tmp = v8033;
        v8034 = v8034_tmp(24, 21);	// L12747
        int32_t v8035 = axis9[d37];	// L12748
        int32_t v8036 = v8034;	// L12749
        bool v8037 = v8036 == v8035;	// L12750
        if (v8037) {	// L12751
          hit9[d37] = 1;	// L12752
        }
      }
    }
    ap_uint<26> o_crv9;	// L12756
    o_crv9 = 0;	// L12757
    int32_t crv_in9;	// L12758
    crv_in9 = -1;	// L12759
    int32_t v8040 = hit9[3];	// L12760
    bool v8041 = v8040 == 1;	// L12761
    if (v8041) {	// L12762
      ap_uint<26> v8042 = hd9[3];	// L12763
      o_crv9 = v8042;	// L12764
      crv_in9 = 3;	// L12765
    } else {
      int32_t v8043 = hit9[2];	// L12767
      bool v8044 = v8043 == 1;	// L12768
      if (v8044) {	// L12769
        ap_uint<26> v8045 = hd9[2];	// L12770
        o_crv9 = v8045;	// L12771
        crv_in9 = 2;	// L12772
      } else {
        int32_t v8046 = hit9[1];	// L12774
        bool v8047 = v8046 == 1;	// L12775
        if (v8047) {	// L12776
          ap_uint<26> v8048 = hd9[1];	// L12777
          o_crv9 = v8048;	// L12778
          crv_in9 = 1;	// L12779
        } else {
          int32_t v8049 = hit9[0];	// L12781
          bool v8050 = v8049 == 1;	// L12782
          if (v8050) {	// L12783
            ap_uint<26> v8051 = hd9[0];	// L12784
            o_crv9 = v8051;	// L12785
            crv_in9 = 0;	// L12786
          }
        }
      }
    }
    int32_t pop9[4];	// L12791
    for (int v8053 = 0; v8053 < 4; v8053++) {	// L12792
      pop9[v8053] = 0;	// L12792
    }
    int32_t inj_done9;	// L12793
    inj_done9 = 0;	// L12794
    int32_t idir9;	// L12795
    idir9 = -1;	// L12796
    ap_int<26> v8056 = csd_pkt9;	// L12797
    bool v8057;
    ap_int<26> v8057_tmp = v8056;
    v8057 = v8057_tmp[25];	// L12798
    int32_t v8058 = v8057;	// L12799
    bool v8059 = v8058 == 1;	// L12800
    if (v8059) {	// L12801
      int32_t v8060 = csd_dir9;	// L12802
      ap_int<33> v8061 = v8060;	// L12803
      ap_int<33> v8062 = 3 - v8061;	// L12804
      int32_t v8063 = v8062;	// L12805
      idir9 = v8063;	// L12806
    }
    int32_t v8064 = idir9;	// L12808
    bool v8065 = v8064 == 0;	// L12809
    if (v8065) {	// L12810
      ap_int<26> v8066 = csd_pkt9;	// L12811
      bool v8067 = v7879.write_nb(v8066);
	// L12812
      if (v8067) {	// L12813
        inj_done9 = 1;	// L12814
      }
    } else {
      int32_t v8068 = hvld9[0];	// L12817
      bool v8069 = v8068 == 1;	// L12818
      int32_t v8070 = hit9[0];	// L12819
      bool v8071 = v8070 == 0;	// L12820
      bool v8072 = v8069 & v8071;	// L12821
      if (v8072) {	// L12822
        ap_uint<26> v8073 = hd9[0];	// L12823
        bool v8074 = v7879.write_nb(v8073);
	// L12824
        if (v8074) {	// L12825
          pop9[0] = 1;	// L12826
        }
      }
    }
    int32_t v8075 = idir9;	// L12830
    bool v8076 = v8075 == 1;	// L12831
    if (v8076) {	// L12832
      ap_int<26> v8077 = csd_pkt9;	// L12833
      bool v8078 = v7880.write_nb(v8077);
	// L12834
      if (v8078) {	// L12835
        inj_done9 = 1;	// L12836
      }
    } else {
      int32_t v8079 = hvld9[1];	// L12839
      bool v8080 = v8079 == 1;	// L12840
      int32_t v8081 = hit9[1];	// L12841
      bool v8082 = v8081 == 0;	// L12842
      bool v8083 = v8080 & v8082;	// L12843
      if (v8083) {	// L12844
        ap_uint<26> v8084 = hd9[1];	// L12845
        bool v8085 = v7880.write_nb(v8084);
	// L12846
        if (v8085) {	// L12847
          pop9[1] = 1;	// L12848
        }
      }
    }
    int32_t v8086 = idir9;	// L12852
    bool v8087 = v8086 == 2;	// L12853
    if (v8087) {	// L12854
      ap_int<26> v8088 = csd_pkt9;	// L12855
      bool v8089 = v7881.write_nb(v8088);
	// L12856
      if (v8089) {	// L12857
        inj_done9 = 1;	// L12858
      }
    } else {
      int32_t v8090 = hvld9[2];	// L12861
      bool v8091 = v8090 == 1;	// L12862
      int32_t v8092 = hit9[2];	// L12863
      bool v8093 = v8092 == 0;	// L12864
      bool v8094 = v8091 & v8093;	// L12865
      if (v8094) {	// L12866
        ap_uint<26> v8095 = hd9[2];	// L12867
        bool v8096 = v7881.write_nb(v8095);
	// L12868
        if (v8096) {	// L12869
          pop9[2] = 1;	// L12870
        }
      }
    }
    int32_t v8097 = idir9;	// L12874
    bool v8098 = v8097 == 3;	// L12875
    if (v8098) {	// L12876
      ap_int<26> v8099 = csd_pkt9;	// L12877
      bool v8100 = v7882.write_nb(v8099);
	// L12878
      if (v8100) {	// L12879
        inj_done9 = 1;	// L12880
      }
    } else {
      int32_t v8101 = hvld9[3];	// L12883
      bool v8102 = v8101 == 1;	// L12884
      int32_t v8103 = hit9[3];	// L12885
      bool v8104 = v8103 == 0;	// L12886
      bool v8105 = v8102 & v8104;	// L12887
      if (v8105) {	// L12888
        ap_uint<26> v8106 = hd9[3];	// L12889
        bool v8107 = v7882.write_nb(v8106);
	// L12890
        if (v8107) {	// L12891
          pop9[3] = 1;	// L12892
        }
      }
    }
    int32_t v8108 = crv_in9;	// L12896
    bool v8109 = v8108 >= 0;	// L12897
    if (v8109) {	// L12898
      int32_t v8110 = crv_in9;	// L12899
      int v8111 = v8110;	// L12900
      pop9[v8111] = 1;	// L12901
    }
    l_S_d_2_d38: for (int d38 = 0; d38 < 4; d38++) {	// L12903
      int32_t v8113 = pop9[d38];	// L12904
      bool v8114 = v8113 == 1;	// L12905
      if (v8114) {	// L12906
        l_S_sft_2_sft9: for (int sft9 = 0; sft9 < 1; sft9++) {	// L12907
          ap_uint<26> v8116 = rbuf9[d38][(sft9 + 1)];	// L12908
          rbuf9[d38][sft9] = v8116;	// L12909
        }
        uint8_t v8117 = rbcnt9[d38];	// L12911
        ap_int<33> v8118 = v8117;	// L12912
        ap_int<33> v8119 = v8118 - 1;	// L12913
        uint8_t v8120 = v8119;	// L12914
        rbcnt9[d38] = v8120;	// L12915
      }
    }
    int32_t v8121 = inj_done9;	// L12918
    bool v8122 = v8121 == 1;	// L12919
    if (v8122) {	// L12920
      csd_pkt9 = 0;	// L12921
    }
    ap_int<26> v8123 = o_crv9;	// L12923
    bool v8124;
    ap_int<26> v8124_tmp = v8123;
    v8124 = v8124_tmp[25];	// L12924
    int32_t v8125 = v8124;	// L12925
    crv_vld9 = v8125;	// L12926
    int32_t v8126 = crv_vld9;	// L12927
    bool v8127 = v8126 == 1;	// L12928
    if (v8127) {	// L12929
      crv_ever9 = 1;	// L12930
    }
    ap_int<26> v8128 = o_crv9;	// L12932
    int16_t v8129;
    ap_int<26> v8129_tmp = v8128;
    v8129 = v8129_tmp(15, 0);	// L12933
    half v8130;
    union { uint16_t from; half to;} _converter_v8129_to_v8130 = {};
    _converter_v8129_to_v8130.from = v8129;
    v8130 = _converter_v8129_to_v8130.to;	// L12934
    crv_data9 = v8130;	// L12935
    ap_int<26> v8131 = o_crv9;	// L12936
    ap_int<4> v8132;
    ap_int<26> v8132_tmp = v8131;
    v8132 = v8132_tmp(19, 16);	// L12937
    int32_t v8133 = v8132;	// L12938
    crv_addr9 = v8133;	// L12939
    ap_int<26> v8134 = o_crv9;	// L12940
    bool v8135;
    ap_int<26> v8135_tmp = v8134;
    v8135 = v8135_tmp[20];	// L12941
    int32_t v8136 = v8135;	// L12942
    crv_mode9 = v8136;	// L12943
    ap_int<26> v8137 = o_crv9;	// L12944
    int16_t v8138;
    ap_int<26> v8138_tmp = v8137;
    v8138 = v8138_tmp(15, 0);	// L12945
    int32_t v8139 = v8138;	// L12946
    crv_raw9 = v8139;	// L12947
    half rxv9[4];	// L12948
    for (int v8141 = 0; v8141 < 4; v8141++) {	// L12949
      rxv9[v8141] = 0.000000;	// L12949
    }
    int32_t rxvld9[4];	// L12950
    for (int v8143 = 0; v8143 < 4; v8143++) {	// L12951
      rxvld9[v8143] = 0;	// L12951
    }
    uint8_t v8144 = hold_cnt9[0];	// L12952
    int32_t v8145 = v8144;	// L12953
    bool v8146 = v8145 < 2;	// L12954
    if (v8146) {	// L12955
      ap_uint<17> v8147;
      bool v8148 = v7883.read_nb(v8147);
	// L12956
      ap_uint<17> sgn9;	// L12957
      sgn9 = v8147;	// L12958
      bool sqn9;	// L12959
      sqn9 = v8148;	// L12960
      bool v8151 = sqn9;	// L12961
      int32_t v8152 = v8151;	// L12962
      bool v8153 = v8152 == 1;	// L12963
      if (v8153) {	// L12964
        ap_int<17> v8154 = sgn9;	// L12965
        int16_t v8155;
        ap_int<17> v8155_tmp = v8154;
        v8155 = v8155_tmp(16, 1);	// L12966
        half v8156;
        union { uint16_t from; half to;} _converter_v8155_to_v8156 = {};
        _converter_v8155_to_v8156.from = v8155;
        v8156 = _converter_v8155_to_v8156.to;	// L12967
        rxv9[0] = v8156;	// L12968
        rxvld9[0] = 1;	// L12969
      }
    }
    uint8_t v8157 = hold_cnt9[1];	// L12972
    int32_t v8158 = v8157;	// L12973
    bool v8159 = v8158 < 2;	// L12974
    if (v8159) {	// L12975
      ap_uint<17> v8160;
      bool v8161 = v7884.read_nb(v8160);
	// L12976
      ap_uint<17> sgs9;	// L12977
      sgs9 = v8160;	// L12978
      bool sqs9;	// L12979
      sqs9 = v8161;	// L12980
      bool v8164 = sqs9;	// L12981
      int32_t v8165 = v8164;	// L12982
      bool v8166 = v8165 == 1;	// L12983
      if (v8166) {	// L12984
        ap_int<17> v8167 = sgs9;	// L12985
        int16_t v8168;
        ap_int<17> v8168_tmp = v8167;
        v8168 = v8168_tmp(16, 1);	// L12986
        half v8169;
        union { uint16_t from; half to;} _converter_v8168_to_v8169 = {};
        _converter_v8168_to_v8169.from = v8168;
        v8169 = _converter_v8168_to_v8169.to;	// L12987
        rxv9[1] = v8169;	// L12988
        rxvld9[1] = 1;	// L12989
      }
    }
    uint8_t v8170 = hold_cnt9[2];	// L12992
    int32_t v8171 = v8170;	// L12993
    bool v8172 = v8171 < 2;	// L12994
    if (v8172) {	// L12995
      ap_uint<17> v8173;
      bool v8174 = v7885.read_nb(v8173);
	// L12996
      ap_uint<17> sgw9;	// L12997
      sgw9 = v8173;	// L12998
      bool sqw9;	// L12999
      sqw9 = v8174;	// L13000
      bool v8177 = sqw9;	// L13001
      int32_t v8178 = v8177;	// L13002
      bool v8179 = v8178 == 1;	// L13003
      if (v8179) {	// L13004
        ap_int<17> v8180 = sgw9;	// L13005
        int16_t v8181;
        ap_int<17> v8181_tmp = v8180;
        v8181 = v8181_tmp(16, 1);	// L13006
        half v8182;
        union { uint16_t from; half to;} _converter_v8181_to_v8182 = {};
        _converter_v8181_to_v8182.from = v8181;
        v8182 = _converter_v8181_to_v8182.to;	// L13007
        rxv9[2] = v8182;	// L13008
        rxvld9[2] = 1;	// L13009
      }
    }
    uint8_t v8183 = hold_cnt9[3];	// L13012
    int32_t v8184 = v8183;	// L13013
    bool v8185 = v8184 < 2;	// L13014
    if (v8185) {	// L13015
      ap_uint<17> v8186;
      bool v8187 = v7886.read_nb(v8186);
	// L13016
      ap_uint<17> sge9;	// L13017
      sge9 = v8186;	// L13018
      bool sqe9;	// L13019
      sqe9 = v8187;	// L13020
      bool v8190 = sqe9;	// L13021
      int32_t v8191 = v8190;	// L13022
      bool v8192 = v8191 == 1;	// L13023
      if (v8192) {	// L13024
        ap_int<17> v8193 = sge9;	// L13025
        int16_t v8194;
        ap_int<17> v8194_tmp = v8193;
        v8194 = v8194_tmp(16, 1);	// L13026
        half v8195;
        union { uint16_t from; half to;} _converter_v8194_to_v8195 = {};
        _converter_v8194_to_v8195.from = v8194;
        v8195 = _converter_v8194_to_v8195.to;	// L13027
        rxv9[3] = v8195;	// L13028
        rxvld9[3] = 1;	// L13029
      }
    }
    l_S_d_4_d39: for (int d39 = 0; d39 < 4; d39++) {	// L13032
      int32_t v8197 = rxvld9[d39];	// L13033
      bool v8198 = v8197 == 1;	// L13034
      if (v8198) {	// L13035
        half v8199 = rxv9[d39];	// L13036
        uint8_t v8200 = hold_cnt9[d39];	// L13037
        int v8201 = v8200;	// L13038
        hold_v9[d39][v8201] = v8199;	// L13039
        uint8_t v8202 = hold_cnt9[d39];	// L13040
        ap_int<33> v8203 = v8202;	// L13041
        ap_int<33> v8204 = v8203 + 1;	// L13042
        uint8_t v8205 = v8204;	// L13043
        hold_cnt9[d39] = v8205;	// L13044
      }
    }
    ap_uint<17> tx_n9;	// L13047
    tx_n9 = 0;	// L13048
    ap_uint<17> tx_s9;	// L13049
    tx_s9 = 0;	// L13050
    ap_uint<17> tx_w9;	// L13051
    tx_w9 = 0;	// L13052
    ap_uint<17> tx_e9;	// L13053
    tx_e9 = 0;	// L13054
    uint8_t v8210 = sb_v9[0];	// L13055
    int32_t v8211 = v8210;	// L13056
    bool v8212 = v8211 == 1;	// L13057
    if (v8212) {	// L13058
      uint8_t v8213 = sb_ix9[0];	// L13059
      int v8214 = v8213;	// L13060
      half v8215 = resq9[v8214];	// L13061
      half wb9;
#pragma HLS dependence variable=wb9 type=inter dependent=false	// L13062
      wb9 = v8215;	// L13063
      uint8_t v8217 = sb_cmp9[0];	// L13064
      int32_t v8218 = v8217;	// L13065
      bool v8219 = v8218 == 1;	// L13066
      if (v8219) {	// L13067
        uint8_t v8220 = sb_ix9[0];	// L13068
        int v8221 = v8220;	// L13069
        uint8_t v8222 = cmpq9[v8221];	// L13070
        condition_reg9 = v8222;	// L13071
      }
      uint8_t v8223 = sb_rtr9[0];	// L13073
      int32_t v8224 = v8223;	// L13074
      bool v8225 = v8224 == 1;	// L13075
      if (v8225) {	// L13076
        uint8_t v8226 = sb_inj9[0];	// L13077
        int32_t v8227 = v8226;	// L13078
        bool v8228 = v8227 == 1;	// L13079
        ap_int<26> v8229 = csd_pkt9;	// L13080
        bool v8230;
        ap_int<26> v8230_tmp = v8229;
        v8230 = v8230_tmp[25];	// L13081
        int32_t v8231 = v8230;	// L13082
        bool v8232 = v8231 == 0;	// L13083
        bool v8233 = v8228 & v8232;	// L13084
        if (v8233) {	// L13085
          half v8234 = wb9;	// L13086
          uint16_t v8235;
          union { half from; uint16_t to;} _converter_v8234_to_v8235 = {};
          _converter_v8234_to_v8235.from = v8234;
          v8235 = _converter_v8234_to_v8235.to;	// L13087
          ap_int<26> v8236 = csd_pkt9;	// L13088
          ap_int<26> v8237;
          ap_int<26> v8237_tmp = v8236;
          v8237_tmp(15, 0) = v8235;
          v8237 = v8237_tmp;	// L13089
          csd_pkt9 = v8237;	// L13090
          uint8_t v8238 = sb_dst9[0];	// L13091
          ap_uint<4> v8239 = v8238;	// L13092
          ap_int<26> v8240 = csd_pkt9;	// L13093
          ap_int<26> v8241;
          ap_int<26> v8241_tmp = v8240;
          v8241_tmp(19, 16) = v8239;
          v8241 = v8241_tmp;	// L13094
          csd_pkt9 = v8241;	// L13095
          uint8_t v8242 = sb_id9[0];	// L13096
          ap_uint<4> v8243 = v8242;	// L13097
          ap_int<26> v8244 = csd_pkt9;	// L13098
          ap_int<26> v8245;
          ap_int<26> v8245_tmp = v8244;
          v8245_tmp(24, 21) = v8243;
          v8245 = v8245_tmp;	// L13099
          csd_pkt9 = v8245;	// L13100
          uint8_t v8246 = sb_rvld9[0];	// L13101
          bool v8247 = v8246;	// L13102
          ap_int<26> v8248 = csd_pkt9;	// L13103
          ap_int<26> v8249;
          ap_int<26> v8249_tmp = v8248;
          v8249_tmp[25] = v8247;          v8249 = v8249_tmp;	// L13104
          csd_pkt9 = v8249;	// L13105
          uint8_t v8250 = sb_dir9[0];	// L13106
          int32_t v8251 = v8250;	// L13107
          csd_dir9 = v8251;	// L13108
        }
      } else {
        uint8_t v8252 = sb_dst9[0];	// L13111
        int32_t v8253 = v8252;	// L13112
        bool v8254 = v8253 >= 12;	// L13113
        if (v8254) {	// L13114
          ap_uint<17> tw09;	// L13115
          tw09 = 0;	// L13116
          uint8_t v8256 = sb_rvld9[0];	// L13117
          bool v8257 = v8256;	// L13118
          ap_int<17> v8258 = tw09;	// L13119
          ap_int<17> v8259;
          ap_int<17> v8259_tmp = v8258;
          v8259_tmp[0] = v8257;          v8259 = v8259_tmp;	// L13120
          tw09 = v8259;	// L13121
          half v8260 = wb9;	// L13122
          uint16_t v8261;
          union { half from; uint16_t to;} _converter_v8260_to_v8261 = {};
          _converter_v8260_to_v8261.from = v8260;
          v8261 = _converter_v8260_to_v8261.to;	// L13123
          ap_int<17> v8262 = tw09;	// L13124
          ap_int<17> v8263;
          ap_int<17> v8263_tmp = v8262;
          v8263_tmp(16, 1) = v8261;
          v8263 = v8263_tmp;	// L13125
          tw09 = v8263;	// L13126
          uint8_t v8264 = sb_dst9[0];	// L13127
          int32_t v8265 = v8264;	// L13128
          int32_t v8266 = v8265 & 3;	// L13129
          bool v8267 = v8266 == 0;	// L13130
          if (v8267) {	// L13131
            ap_int<17> v8268 = tw09;	// L13132
            tx_n9 = v8268;	// L13133
          } else {
            uint8_t v8269 = sb_dst9[0];	// L13135
            int32_t v8270 = v8269;	// L13136
            int32_t v8271 = v8270 & 3;	// L13137
            bool v8272 = v8271 == 1;	// L13138
            if (v8272) {	// L13139
              ap_int<17> v8273 = tw09;	// L13140
              tx_s9 = v8273;	// L13141
            } else {
              uint8_t v8274 = sb_dst9[0];	// L13143
              int32_t v8275 = v8274;	// L13144
              int32_t v8276 = v8275 & 3;	// L13145
              bool v8277 = v8276 == 2;	// L13146
              if (v8277) {	// L13147
                ap_int<17> v8278 = tw09;	// L13148
                tx_w9 = v8278;	// L13149
              } else {
                ap_int<17> v8279 = tw09;	// L13151
                tx_e9 = v8279;	// L13152
              }
            }
          }
        } else {
          uint8_t v8280 = sb_rvld9[0];	// L13157
          int32_t v8281 = v8280;	// L13158
          bool v8282 = v8281 == 1;	// L13159
          if (v8282) {	// L13160
            uint8_t v8283 = sb_dst9[0];	// L13161
            int32_t v8284 = v8283;	// L13162
            bool v8285 = v8284 < 8;	// L13163
            int32_t v8286 = dsmask9;	// L13164
            int32_t v8287 = v8286 >> v8284;	// L13165
            int32_t v8288 = v8287 & 1;	// L13166
            bool v8289 = v8288 == 1;	// L13167
            bool v8290 = v8285 & v8289;	// L13168
            if (v8290) {	// L13169
              uint8_t v8291 = sb_dst9[0];	// L13170
              int v8292 = v8291;	// L13171
              int32_t v8293 = drf_full9[v8292];	// L13172
              bool v8294 = v8293 == 0;	// L13173
              if (v8294) {	// L13174
                half v8295 = wb9;	// L13175
                uint8_t v8296 = sb_dst9[0];	// L13176
                int v8297 = v8296;	// L13177
                drf9[v8297] = v8295;	// L13178
                uint8_t v8298 = sb_dst9[0];	// L13179
                int v8299 = v8298;	// L13180
                drf_full9[v8299] = 1;	// L13181
              }
            } else {
              half v8300 = wb9;	// L13184
              uint8_t v8301 = sb_dst9[0];	// L13185
              int32_t v8302 = v8301;	// L13186
              int32_t v8303 = v8302 & 7;	// L13187
              int v8304 = v8303;	// L13188
              drf9[v8304] = v8300;	// L13189
            }
          }
        }
      }
    }
    int32_t pc9;	// L13195
    pc9 = -1;	// L13196
    int8_t v8306 = fetch_en9;	// L13197
    int32_t v8307 = v8306;	// L13198
    bool v8308 = v8307 == 1;	// L13199
    if (v8308) {	// L13200
      int8_t v8309 = instr_cnt9;	// L13201
      int32_t v8310 = v8309;	// L13202
      pc9 = v8310;	// L13203
    }
    int8_t v8311 = fetch_en9;	// L13205
    int32_t v8312 = v8311;	// L13206
    bool v8313 = v8312 == 1;	// L13207
    if (v8313) {	// L13208
      fe_ever9 = 1;	// L13209
    }
    int32_t instr9;	// L13211
    instr9 = 0;	// L13212
    int32_t v8315 = pc9;	// L13213
    bool v8316 = v8315 >= 0;	// L13214
    if (v8316) {	// L13215
      int32_t v8317 = pc9;	// L13216
      int v8318 = v8317;	// L13217
      int32_t v8319 = irf9[v8318];	// L13218
      instr9 = v8319;	// L13219
    }
    int32_t v8320 = instr9;	// L13221
    int32_t v8321 = v8320 & 15;	// L13222
    int32_t op9;	// L13223
    op9 = v8321;	// L13224
    int32_t v8323 = instr9;	// L13225
    int32_t v8324 = v8323 >> 4;	// L13226
    int32_t v8325 = v8324 & 15;	// L13227
    int32_t dst9;	// L13228
    dst9 = v8325;	// L13229
    int32_t v8327 = instr9;	// L13230
    int32_t v8328 = v8327 >> 8;	// L13231
    int32_t v8329 = v8328 & 15;	// L13232
    int32_t s19;	// L13233
    s19 = v8329;	// L13234
    int32_t v8331 = instr9;	// L13235
    int32_t v8332 = v8331 >> 12;	// L13236
    int32_t v8333 = v8332 & 15;	// L13237
    int32_t s29;	// L13238
    s29 = v8333;	// L13239
    half a9;	// L13240
    a9 = 0.000000;	// L13241
    half b9;	// L13242
    b9 = 0.000000;	// L13243
    int32_t v8337 = s19;	// L13244
    bool v8338 = v8337 >= 12;	// L13245
    if (v8338) {	// L13246
      int32_t v8339 = s19;	// L13247
      int32_t v8340 = v8339 & 3;	// L13248
      int v8341 = v8340;	// L13249
      half v8342 = hold_v9[v8341][0];	// L13250
      a9 = v8342;	// L13251
    } else {
      int32_t v8343 = s19;	// L13253
      int v8344 = v8343;	// L13254
      half v8345 = drf9[v8344];	// L13255
      a9 = v8345;	// L13256
    }
    int32_t v8346 = s29;	// L13258
    bool v8347 = v8346 >= 12;	// L13259
    if (v8347) {	// L13260
      int32_t v8348 = s29;	// L13261
      int32_t v8349 = v8348 & 3;	// L13262
      int v8350 = v8349;	// L13263
      half v8351 = hold_v9[v8350][0];	// L13264
      b9 = v8351;	// L13265
    } else {
      int32_t v8352 = s29;	// L13267
      int v8353 = v8352;	// L13268
      half v8354 = drf9[v8353];	// L13269
      b9 = v8354;	// L13270
    }
    int32_t a_vld9;	// L13272
    a_vld9 = 1;	// L13273
    int32_t b_vld9;	// L13274
    b_vld9 = 1;	// L13275
    int32_t v8357 = s19;	// L13276
    bool v8358 = v8357 >= 12;	// L13277
    if (v8358) {	// L13278
      a_vld9 = 0;	// L13279
      int32_t v8359 = s19;	// L13280
      int32_t v8360 = v8359 & 3;	// L13281
      int v8361 = v8360;	// L13282
      uint8_t v8362 = hold_cnt9[v8361];	// L13283
      int32_t v8363 = v8362;	// L13284
      bool v8364 = v8363 > 0;	// L13285
      if (v8364) {	// L13286
        a_vld9 = 1;	// L13287
      }
    }
    int32_t v8365 = s29;	// L13290
    bool v8366 = v8365 >= 12;	// L13291
    if (v8366) {	// L13292
      b_vld9 = 0;	// L13293
      int32_t v8367 = s29;	// L13294
      int32_t v8368 = v8367 & 3;	// L13295
      int v8369 = v8368;	// L13296
      uint8_t v8370 = hold_cnt9[v8369];	// L13297
      int32_t v8371 = v8370;	// L13298
      bool v8372 = v8371 > 0;	// L13299
      if (v8372) {	// L13300
        b_vld9 = 1;	// L13301
      }
    }
    int32_t v8373 = s19;	// L13304
    bool v8374 = v8373 < 8;	// L13305
    int32_t v8375 = dsmask9;	// L13306
    int32_t v8376 = v8375 >> v8373;	// L13307
    int32_t v8377 = v8376 & 1;	// L13308
    bool v8378 = v8377 == 1;	// L13309
    bool v8379 = v8374 & v8378;	// L13310
    if (v8379) {	// L13311
      int32_t v8380 = s19;	// L13312
      int v8381 = v8380;	// L13313
      int32_t v8382 = drf_full9[v8381];	// L13314
      bool v8383 = v8382 == 0;	// L13315
      if (v8383) {	// L13316
        a_vld9 = 0;	// L13317
      }
    }
    int32_t v8384 = s29;	// L13320
    bool v8385 = v8384 < 8;	// L13321
    int32_t v8386 = dsmask9;	// L13322
    int32_t v8387 = v8386 >> v8384;	// L13323
    int32_t v8388 = v8387 & 1;	// L13324
    bool v8389 = v8388 == 1;	// L13325
    bool v8390 = v8385 & v8389;	// L13326
    if (v8390) {	// L13327
      int32_t v8391 = s29;	// L13328
      int v8392 = v8391;	// L13329
      int32_t v8393 = drf_full9[v8392];	// L13330
      bool v8394 = v8393 == 0;	// L13331
      if (v8394) {	// L13332
        b_vld9 = 0;	// L13333
      }
    }
    int32_t binop9;	// L13336
    binop9 = 0;	// L13337
    int32_t v8396 = op9;	// L13338
    bool v8397 = v8396 == 0;	// L13339
    bool v8398 = v8396 == 1;	// L13340
    bool v8399 = v8396 == 2;	// L13341
    bool v8400 = v8396 == 8;	// L13342
    bool v8401 = v8396 == 9;	// L13343
    bool v8402 = v8397 | v8398;	// L13344
    bool v8403 = v8402 | v8399;	// L13345
    bool v8404 = v8403 | v8400;	// L13346
    bool v8405 = v8404 | v8401;	// L13347
    if (v8405) {	// L13348
      binop9 = 1;	// L13349
    }
    int32_t raw9;	// L13351
    raw9 = 0;	// L13352
    int32_t cmp_busy9;	// L13353
    cmp_busy9 = 0;	// L13354
    l_S_k_5_k18: for (int k18 = 0; k18 < 4; k18++) {	// L13355
      uint8_t v8409 = sb_v9[(k18 + 1)];	// L13356
      int32_t v8410 = v8409;	// L13357
      bool v8411 = v8410 == 1;	// L13358
      uint8_t v8412 = sb_rtr9[(k18 + 1)];	// L13359
      int32_t v8413 = v8412;	// L13360
      bool v8414 = v8413 == 0;	// L13361
      uint8_t v8415 = sb_dst9[(k18 + 1)];	// L13362
      int32_t v8416 = v8415;	// L13363
      bool v8417 = v8416 < 12;	// L13364
      bool v8418 = v8411 & v8414;	// L13365
      bool v8419 = v8418 & v8417;	// L13366
      if (v8419) {	// L13367
        int32_t v8420 = s19;	// L13368
        bool v8421 = v8420 < 12;	// L13369
        uint8_t v8422 = sb_dst9[(k18 + 1)];	// L13370
        int32_t v8423 = v8422;	// L13371
        int32_t v8424 = v8423 & 7;	// L13372
        int32_t v8425 = v8420 & 7;	// L13373
        bool v8426 = v8424 == v8425;	// L13374
        bool v8427 = v8421 & v8426;	// L13375
        if (v8427) {	// L13376
          raw9 = 1;	// L13377
        }
        int32_t v8428 = binop9;	// L13379
        bool v8429 = v8428 == 1;	// L13380
        int32_t v8430 = s29;	// L13381
        bool v8431 = v8430 < 12;	// L13382
        uint8_t v8432 = sb_dst9[(k18 + 1)];	// L13383
        int32_t v8433 = v8432;	// L13384
        int32_t v8434 = v8433 & 7;	// L13385
        int32_t v8435 = v8430 & 7;	// L13386
        bool v8436 = v8434 == v8435;	// L13387
        bool v8437 = v8429 & v8431;	// L13388
        bool v8438 = v8437 & v8436;	// L13389
        if (v8438) {	// L13390
          raw9 = 1;	// L13391
        }
      }
      uint8_t v8439 = sb_v9[(k18 + 1)];	// L13394
      int32_t v8440 = v8439;	// L13395
      bool v8441 = v8440 == 1;	// L13396
      uint8_t v8442 = sb_cmp9[(k18 + 1)];	// L13397
      int32_t v8443 = v8442;	// L13398
      bool v8444 = v8443 == 1;	// L13399
      bool v8445 = v8441 & v8444;	// L13400
      if (v8445) {	// L13401
        cmp_busy9 = 1;	// L13402
      }
    }
    int32_t is_cond9;	// L13405
    is_cond9 = 0;	// L13406
    int32_t v8447 = op9;	// L13407
    bool v8448 = v8447 >= 12;	// L13408
    ap_int<33> v8449 = v8447;	// L13409
    bool v8450 = v8449 <= 15;	// L13410
    bool v8451 = v8448 & v8450;	// L13411
    if (v8451) {	// L13412
      is_cond9 = 1;	// L13413
    }
    int32_t grant9;	// L13415
    grant9 = 0;	// L13416
    int32_t v8453 = pc9;	// L13417
    bool v8454 = v8453 >= 0;	// L13418
    if (v8454) {	// L13419
      grant9 = 1;	// L13420
    }
    int32_t v8455 = pc9;	// L13422
    bool v8456 = v8455 >= 0;	// L13423
    int32_t v8457 = a_vld9;	// L13424
    bool v8458 = v8457 == 0;	// L13425
    int32_t v8459 = binop9;	// L13426
    bool v8460 = v8459 == 1;	// L13427
    int32_t v8461 = b_vld9;	// L13428
    bool v8462 = v8461 == 0;	// L13429
    bool v8463 = v8460 & v8462;	// L13430
    bool v8464 = v8458 | v8463;	// L13431
    bool v8465 = v8456 & v8464;	// L13432
    if (v8465) {	// L13433
      grant9 = 0;	// L13434
    }
    int32_t v8466 = pc9;	// L13436
    bool v8467 = v8466 >= 0;	// L13437
    int32_t v8468 = raw9;	// L13438
    bool v8469 = v8468 == 1;	// L13439
    int32_t v8470 = is_cond9;	// L13440
    bool v8471 = v8470 == 1;	// L13441
    int32_t v8472 = cmp_busy9;	// L13442
    bool v8473 = v8472 == 1;	// L13443
    bool v8474 = v8471 & v8473;	// L13444
    bool v8475 = v8469 | v8474;	// L13445
    bool v8476 = v8467 & v8475;	// L13446
    if (v8476) {	// L13447
      grant9 = 0;	// L13448
    }
    int32_t v8477 = grant9;	// L13450
    bool v8478 = v8477 == 1;	// L13451
    if (v8478) {	// L13452
      int8_t v8479 = instr_cnt9;	// L13453
      int32_t v8480 = cfg_isz9;	// L13454
      int32_t v8481 = v8479;	// L13455
      bool v8482 = v8481 == v8480;	// L13456
      if (v8482) {	// L13457
        instr_cnt9 = 0;	// L13458
        int8_t v8483 = iter_cnt9;	// L13459
        int32_t v8484 = cfg_itsz9;	// L13460
        ap_int<33> v8485 = v8484;	// L13461
        ap_int<33> v8486 = v8485 - 1;	// L13462
        ap_int<33> v8487 = v8483;	// L13463
        bool v8488 = v8487 == v8486;	// L13464
        if (v8488) {	// L13465
          fetch_en9 = 0;	// L13466
        } else {
          int8_t v8489 = iter_cnt9;	// L13468
          ap_int<33> v8490 = v8489;	// L13469
          ap_int<33> v8491 = v8490 + 1;	// L13470
          uint8_t v8492 = v8491;	// L13471
          iter_cnt9 = v8492;	// L13472
        }
      } else {
        int8_t v8493 = instr_cnt9;	// L13475
        ap_int<33> v8494 = v8493;	// L13476
        ap_int<33> v8495 = v8494 + 1;	// L13477
        uint8_t v8496 = v8495;	// L13478
        instr_cnt9 = v8496;	// L13479
      }
    }
    int32_t c19;	// L13482
    c19 = -1;	// L13483
    int32_t c29;	// L13484
    c29 = -1;	// L13485
    int32_t v8499 = grant9;	// L13486
    bool v8500 = v8499 == 1;	// L13487
    int32_t v8501 = s19;	// L13488
    bool v8502 = v8501 >= 12;	// L13489
    bool v8503 = v8500 & v8502;	// L13490
    if (v8503) {	// L13491
      int32_t v8504 = s19;	// L13492
      int32_t v8505 = v8504 & 3;	// L13493
      c19 = v8505;	// L13494
    }
    int32_t v8506 = grant9;	// L13496
    bool v8507 = v8506 == 1;	// L13497
    int32_t v8508 = s29;	// L13498
    bool v8509 = v8508 >= 12;	// L13499
    bool v8510 = v8507 & v8509;	// L13500
    if (v8510) {	// L13501
      int32_t v8511 = s29;	// L13502
      int32_t v8512 = v8511 & 3;	// L13503
      c29 = v8512;	// L13504
    }
    int32_t v8513 = c19;	// L13506
    bool v8514 = v8513 >= 0;	// L13507
    if (v8514) {	// L13508
      int32_t v8515 = c19;	// L13509
      int v8516 = v8515;	// L13510
      half v8517 = hold_v9[v8516][1];	// L13511
      hold_v9[v8516][0] = v8517;	// L13512
      int32_t v8518 = c19;	// L13513
      int v8519 = v8518;	// L13514
      uint8_t v8520 = hold_cnt9[v8519];	// L13515
      ap_int<33> v8521 = v8520;	// L13516
      ap_int<33> v8522 = v8521 - 1;	// L13517
      uint8_t v8523 = v8522;	// L13518
      hold_cnt9[v8519] = v8523;	// L13519
    }
    int32_t v8524 = c29;	// L13521
    bool v8525 = v8524 >= 0;	// L13522
    int32_t v8526 = c19;	// L13523
    bool v8527 = v8524 != v8526;	// L13524
    bool v8528 = v8525 & v8527;	// L13525
    if (v8528) {	// L13526
      int32_t v8529 = c29;	// L13527
      int v8530 = v8529;	// L13528
      half v8531 = hold_v9[v8530][1];	// L13529
      hold_v9[v8530][0] = v8531;	// L13530
      int32_t v8532 = c29;	// L13531
      int v8533 = v8532;	// L13532
      uint8_t v8534 = hold_cnt9[v8533];	// L13533
      ap_int<33> v8535 = v8534;	// L13534
      ap_int<33> v8536 = v8535 - 1;	// L13535
      uint8_t v8537 = v8536;	// L13536
      hold_cnt9[v8533] = v8537;	// L13537
    }
    int32_t v8538 = grant9;	// L13539
    bool v8539 = v8538 == 1;	// L13540
    int32_t v8540 = s19;	// L13541
    bool v8541 = v8540 < 8;	// L13542
    int32_t v8542 = dsmask9;	// L13543
    int32_t v8543 = v8542 >> v8540;	// L13544
    int32_t v8544 = v8543 & 1;	// L13545
    bool v8545 = v8544 == 1;	// L13546
    bool v8546 = v8539 & v8541;	// L13547
    bool v8547 = v8546 & v8545;	// L13548
    if (v8547) {	// L13549
      int32_t v8548 = s19;	// L13550
      int v8549 = v8548;	// L13551
      drf_full9[v8549] = 0;	// L13552
    }
    int32_t v8550 = grant9;	// L13554
    bool v8551 = v8550 == 1;	// L13555
    int32_t v8552 = s29;	// L13556
    bool v8553 = v8552 < 8;	// L13557
    int32_t v8554 = dsmask9;	// L13558
    int32_t v8555 = v8554 >> v8552;	// L13559
    int32_t v8556 = v8555 & 1;	// L13560
    bool v8557 = v8556 == 1;	// L13561
    bool v8558 = v8551 & v8553;	// L13562
    bool v8559 = v8558 & v8557;	// L13563
    if (v8559) {	// L13564
      int32_t v8560 = s29;	// L13565
      int v8561 = v8560;	// L13566
      drf_full9[v8561] = 0;	// L13567
    }
    half res9;
#pragma HLS dependence variable=res9 type=inter dependent=false	// L13569
    res9 = 0.000000;	// L13570
    int32_t v8563 = op9;	// L13571
    bool v8564 = v8563 == 0;	// L13572
    if (v8564) {	// L13573
      half v8565 = a9;	// L13574
      half v8566 = b9;	// L13575
      half v8567 = v8565 + v8566;	// L13576
      res9 = v8567;	// L13577
    } else {
      int32_t v8568 = op9;	// L13579
      bool v8569 = v8568 == 1;	// L13580
      if (v8569) {	// L13581
        half v8570 = a9;	// L13582
        half v8571 = b9;	// L13583
        half v8572 = v8570 - v8571;	// L13584
        res9 = v8572;	// L13585
      } else {
        int32_t v8573 = op9;	// L13587
        bool v8574 = v8573 == 2;	// L13588
        if (v8574) {	// L13589
          half v8575 = a9;	// L13590
          half v8576 = b9;	// L13591
          half v8577 = v8575 * v8576;	// L13592
          res9 = v8577;	// L13593
        } else {
          int32_t v8578 = op9;	// L13595
          bool v8579 = v8578 == 8;	// L13596
          if (v8579) {	// L13597
            half v8580 = a9;	// L13598
            half v8581 = b9;	// L13599
            bool v8582 = v8580 >= v8581;	// L13600
            if (v8582) {	// L13601
              res9 = 1.000000;	// L13602
            } else {
              res9 = -1.000000;	// L13604
            }
          } else {
            int32_t v8583 = op9;	// L13607
            bool v8584 = v8583 == 9;	// L13608
            if (v8584) {	// L13609
              half v8585 = a9;	// L13610
              half v8586 = b9;	// L13611
              bool v8587 = v8585 < v8586;	// L13612
              if (v8587) {	// L13613
                res9 = 1.000000;	// L13614
              } else {
                res9 = -1.000000;	// L13616
              }
            } else {
              half v8588 = a9;	// L13619
              res9 = v8588;	// L13620
            }
          }
        }
      }
    }
    int32_t v8589 = a_vld9;	// L13626
    int32_t res_vld9;	// L13627
    res_vld9 = v8589;	// L13628
    int32_t v8591 = op9;	// L13629
    bool v8592 = v8591 == 0;	// L13630
    bool v8593 = v8591 == 1;	// L13631
    bool v8594 = v8591 == 2;	// L13632
    bool v8595 = v8591 == 8;	// L13633
    bool v8596 = v8591 == 9;	// L13634
    bool v8597 = v8592 | v8593;	// L13635
    bool v8598 = v8597 | v8594;	// L13636
    bool v8599 = v8598 | v8595;	// L13637
    bool v8600 = v8599 | v8596;	// L13638
    if (v8600) {	// L13639
      int32_t v8601 = a_vld9;	// L13640
      int32_t v8602 = b_vld9;	// L13641
      int64_t v8603 = v8601;	// L13642
      int64_t v8604 = v8602;	// L13643
      int64_t v8605 = v8603 * v8604;	// L13644
      int32_t v8606 = v8605;	// L13645
      res_vld9 = v8606;	// L13646
    }
    int32_t v8607 = grant9;	// L13648
    bool v8608 = v8607 == 0;	// L13649
    if (v8608) {	// L13650
      res_vld9 = 0;	// L13651
    }
    int32_t is_rtr9;	// L13653
    is_rtr9 = 0;	// L13654
    int32_t v8610 = op9;	// L13655
    bool v8611 = v8610 >= 4;	// L13656
    ap_int<33> v8612 = v8610;	// L13657
    bool v8613 = v8612 <= 7;	// L13658
    bool v8614 = v8611 & v8613;	// L13659
    if (v8614) {	// L13660
      is_rtr9 = 1;	// L13661
    }
    l_S_k_6_k19: for (int k19 = 0; k19 < 4; k19++) {	// L13663
      uint8_t v8616 = sb_v9[(k19 + 1)];	// L13664
      sb_v9[k19] = v8616;	// L13665
      uint8_t v8617 = sb_dst9[(k19 + 1)];	// L13666
      sb_dst9[k19] = v8617;	// L13667
      uint8_t v8618 = sb_cmp9[(k19 + 1)];	// L13668
      sb_cmp9[k19] = v8618;	// L13669
      uint8_t v8619 = sb_rtr9[(k19 + 1)];	// L13670
      sb_rtr9[k19] = v8619;	// L13671
      uint8_t v8620 = sb_inj9[(k19 + 1)];	// L13672
      sb_inj9[k19] = v8620;	// L13673
      uint8_t v8621 = sb_dir9[(k19 + 1)];	// L13674
      sb_dir9[k19] = v8621;	// L13675
      uint8_t v8622 = sb_id9[(k19 + 1)];	// L13676
      sb_id9[k19] = v8622;	// L13677
      uint8_t v8623 = sb_rvld9[(k19 + 1)];	// L13678
      sb_rvld9[k19] = v8623;	// L13679
      uint8_t v8624 = sb_ix9[(k19 + 1)];	// L13680
      sb_ix9[k19] = v8624;	// L13681
    }
    sb_v9[4] = 0;	// L13683
    int32_t v8625 = grant9;	// L13684
    bool v8626 = v8625 == 1;	// L13685
    if (v8626) {	// L13686
      half v8627 = res9;	// L13687
      int8_t v8628 = resq_wr9;	// L13688
      int v8629 = v8628;	// L13689
      resq9[v8629] = v8627;	// L13690
      int32_t cq9;	// L13691
      cq9 = 0;	// L13692
      int32_t v8631 = op9;	// L13693
      bool v8632 = v8631 == 8;	// L13694
      if (v8632) {	// L13695
        half v8633 = a9;	// L13696
        half v8634 = b9;	// L13697
        bool v8635 = v8633 >= v8634;	// L13698
        if (v8635) {	// L13699
          cq9 = 1;	// L13700
        }
      }
      int32_t v8636 = op9;	// L13703
      bool v8637 = v8636 == 9;	// L13704
      if (v8637) {	// L13705
        half v8638 = a9;	// L13706
        half v8639 = b9;	// L13707
        bool v8640 = v8638 < v8639;	// L13708
        if (v8640) {	// L13709
          cq9 = 1;	// L13710
        }
      }
      int32_t v8641 = cq9;	// L13713
      uint8_t v8642 = v8641;	// L13714
      int8_t v8643 = resq_wr9;	// L13715
      int v8644 = v8643;	// L13716
      cmpq9[v8644] = v8642;	// L13717
      sb_v9[4] = 1;	// L13718
      int32_t v8645 = dst9;	// L13719
      uint8_t v8646 = v8645;	// L13720
      sb_dst9[4] = v8646;	// L13721
      int8_t v8647 = resq_wr9;	// L13722
      sb_ix9[4] = v8647;	// L13723
      sb_cmp9[4] = 0;	// L13724
      int32_t v8648 = op9;	// L13725
      bool v8649 = v8648 == 8;	// L13726
      bool v8650 = v8648 == 9;	// L13727
      bool v8651 = v8649 | v8650;	// L13728
      if (v8651) {	// L13729
        sb_cmp9[4] = 1;	// L13730
      }
      int32_t v8652 = is_rtr9;	// L13732
      int32_t rtrf9;	// L13733
      rtrf9 = v8652;	// L13734
      int32_t v8654 = is_cond9;	// L13735
      bool v8655 = v8654 == 1;	// L13736
      if (v8655) {	// L13737
        rtrf9 = 1;	// L13738
      }
      int32_t v8656 = rtrf9;	// L13740
      uint8_t v8657 = v8656;	// L13741
      sb_rtr9[4] = v8657;	// L13742
      int32_t v8658 = is_rtr9;	// L13743
      int32_t inj9;	// L13744
      inj9 = v8658;	// L13745
      int32_t v8660 = is_cond9;	// L13746
      bool v8661 = v8660 == 1;	// L13747
      int8_t v8662 = condition_reg9;	// L13748
      int32_t v8663 = v8662;	// L13749
      bool v8664 = v8663 == 1;	// L13750
      bool v8665 = v8661 & v8664;	// L13751
      if (v8665) {	// L13752
        inj9 = 1;	// L13753
      }
      int32_t v8666 = inj9;	// L13755
      uint8_t v8667 = v8666;	// L13756
      sb_inj9[4] = v8667;	// L13757
      int32_t v8668 = op9;	// L13758
      int32_t v8669 = v8668 & 3;	// L13759
      uint8_t v8670 = v8669;	// L13760
      sb_dir9[4] = v8670;	// L13761
      int32_t v8671 = s29;	// L13762
      uint8_t v8672 = v8671;	// L13763
      sb_id9[4] = v8672;	// L13764
      int32_t v8673 = res_vld9;	// L13765
      uint8_t v8674 = v8673;	// L13766
      sb_rvld9[4] = v8674;	// L13767
      int8_t v8675 = resq_wr9;	// L13768
      ap_int<33> v8676 = v8675;	// L13769
      ap_int<33> v8677 = v8676 + 1;	// L13770
      ap_int<33> v8678 = v8677 & 7;	// L13771
      uint8_t v8679 = v8678;	// L13772
      resq_wr9 = v8679;	// L13773
    }
    ap_int<17> v8680 = tx_n9;	// L13775
    txn_r9 = v8680;	// L13776
    ap_int<17> v8681 = tx_s9;	// L13777
    txs_r9 = v8681;	// L13778
    ap_int<17> v8682 = tx_w9;	// L13779
    txw_r9 = v8682;	// L13780
    ap_int<17> v8683 = tx_e9;	// L13781
    txe_r9 = v8683;	// L13782
    int32_t v8684 = crv_vld9;	// L13783
    bool v8685 = v8684 == 1;	// L13784
    if (v8685) {	// L13785
      int32_t v8686 = crv_mode9;	// L13786
      bool v8687 = v8686 == 1;	// L13787
      if (v8687) {	// L13788
        int32_t v8688 = crv_addr9;	// L13789
        int32_t v8689 = v8688 >> 3;	// L13790
        int32_t v8690 = v8689 & 1;	// L13791
        bool v8691 = v8690 == 1;	// L13792
        if (v8691) {	// L13793
          int32_t v8692 = crv_raw9;	// L13794
          int32_t v8693 = crv_addr9;	// L13795
          int32_t v8694 = v8693 & 7;	// L13796
          int v8695 = v8694;	// L13797
          irf9[v8695] = v8692;	// L13798
        } else {
          int32_t v8696 = crv_addr9;	// L13800
          bool v8697 = v8696 == 0;	// L13801
          if (v8697) {	// L13802
            int32_t v8698 = crv_raw9;	// L13803
            int32_t v8699 = v8698 & 255;	// L13804
            dsmask9 = v8699;	// L13805
            int32_t v8700 = crv_raw9;	// L13806
            int32_t v8701 = v8700 >> 8;	// L13807
            int32_t v8702 = v8701 & 7;	// L13808
            cfg_isz9 = v8702;	// L13809
            int32_t v8703 = crv_raw9;	// L13810
            int32_t v8704 = v8703 >> 15;	// L13811
            int32_t v8705 = v8704 & 1;	// L13812
            bool v8706 = v8705 == 1;	// L13813
            if (v8706) {	// L13814
              fetch_en9 = 1;	// L13815
              instr_cnt9 = 0;	// L13816
              iter_cnt9 = 0;	// L13817
            }
          } else {
            int32_t v8707 = crv_addr9;	// L13820
            bool v8708 = v8707 == 1;	// L13821
            if (v8708) {	// L13822
              int32_t v8709 = crv_raw9;	// L13823
              int32_t v8710 = v8709 & 255;	// L13824
              cfg_itsz9 = v8710;	// L13825
            }
          }
        }
      } else {
        int32_t v8711 = crv_addr9;	// L13830
        bool v8712 = v8711 < 8;	// L13831
        int32_t v8713 = dsmask9;	// L13832
        int32_t v8714 = v8713 >> v8711;	// L13833
        int32_t v8715 = v8714 & 1;	// L13834
        bool v8716 = v8715 == 1;	// L13835
        bool v8717 = v8712 & v8716;	// L13836
        if (v8717) {	// L13837
          int32_t v8718 = crv_addr9;	// L13838
          int v8719 = v8718;	// L13839
          int32_t v8720 = drf_full9[v8719];	// L13840
          bool v8721 = v8720 == 0;	// L13841
          if (v8721) {	// L13842
            half v8722 = crv_data9;	// L13843
            int32_t v8723 = crv_addr9;	// L13844
            int v8724 = v8723;	// L13845
            drf9[v8724] = v8722;	// L13846
            int32_t v8725 = crv_addr9;	// L13847
            int v8726 = v8725;	// L13848
            drf_full9[v8726] = 1;	// L13849
          }
        } else {
          half v8727 = crv_data9;	// L13852
          int32_t v8728 = crv_addr9;	// L13853
          int v8729 = v8728;	// L13854
          drf9[v8729] = v8727;	// L13855
        }
      }
    }
    ap_int<17> v8730 = txe_r9;	// L13859
    bool v8731;
    ap_int<17> v8731_tmp = v8730;
    v8731 = v8731_tmp[0];	// L13860
    int32_t v8732 = v8731;	// L13861
    bool v8733 = v8732 == 1;	// L13862
    if (v8733) {	// L13863
      ap_int<17> v8734 = txe_r9;	// L13864
      v7887.write(v8734);	// L13865
    }
    ap_int<17> v8735 = txw_r9;	// L13867
    bool v8736;
    ap_int<17> v8736_tmp = v8735;
    v8736 = v8736_tmp[0];	// L13868
    int32_t v8737 = v8736;	// L13869
    bool v8738 = v8737 == 1;	// L13870
    if (v8738) {	// L13871
      ap_int<17> v8739 = txw_r9;	// L13872
      v7888.write(v8739);	// L13873
    }
    ap_int<17> v8740 = txs_r9;	// L13875
    bool v8741;
    ap_int<17> v8741_tmp = v8740;
    v8741 = v8741_tmp[0];	// L13876
    int32_t v8742 = v8741;	// L13877
    bool v8743 = v8742 == 1;	// L13878
    if (v8743) {	// L13879
      ap_int<17> v8744 = txs_r9;	// L13880
      v7889.write(v8744);	// L13881
    }
    ap_int<17> v8745 = txn_r9;	// L13883
    bool v8746;
    ap_int<17> v8746_tmp = v8745;
    v8746 = v8746_tmp[0];	// L13884
    int32_t v8747 = v8746;	// L13885
    bool v8748 = v8747 == 1;	// L13886
    if (v8748) {	// L13887
      ap_int<17> v8749 = txn_r9;	// L13888
      v7890.write(v8749);	// L13889
    }
  }
}

void node_2_2(
  hls::stream< ap_uint<26> >& v8750,
  hls::stream< ap_uint<26> >& v8751,
  hls::stream< ap_uint<26> >& v8752,
  hls::stream< ap_uint<26> >& v8753,
  hls::stream< ap_uint<26> >& v8754,
  hls::stream< ap_uint<26> >& v8755,
  hls::stream< ap_uint<26> >& v8756,
  hls::stream< ap_uint<26> >& v8757,
  hls::stream< ap_uint<17> >& v8758,
  hls::stream< ap_uint<17> >& v8759,
  hls::stream< ap_uint<17> >& v8760,
  hls::stream< ap_uint<17> >& v8761,
  hls::stream< ap_uint<17> >& v8762,
  hls::stream< ap_uint<17> >& v8763,
  hls::stream< ap_uint<17> >& v8764,
  hls::stream< ap_uint<17> >& v8765
) {	// L13894
  int32_t irf10[8];	// L13927
  #pragma HLS array_partition variable=irf10 complete dim=1

  for (int v8767 = 0; v8767 < 8; v8767++) {	// L13928
    irf10[v8767] = 0;	// L13928
  }
  half drf10[8];	// L13929
  #pragma HLS array_partition variable=drf10 complete dim=1

  for (int v8769 = 0; v8769 < 8; v8769++) {	// L13930
    drf10[v8769] = 0.000000;	// L13930
  }
  int32_t drf_full10[8];	// L13931
  #pragma HLS array_partition variable=drf_full10 complete dim=1

  for (int v8771 = 0; v8771 < 8; v8771++) {	// L13932
    drf_full10[v8771] = 0;	// L13932
  }
  int32_t dsmask10;	// L13933
  dsmask10 = 0;	// L13934
  int32_t crv_vld10;	// L13935
  crv_vld10 = 0;	// L13936
  half crv_data10;	// L13937
  crv_data10 = 0.000000;	// L13938
  int32_t crv_addr10;	// L13939
  crv_addr10 = 0;	// L13940
  int32_t crv_mode10;	// L13941
  crv_mode10 = 0;	// L13942
  int32_t crv_raw10;	// L13943
  crv_raw10 = 0;	// L13944
  int32_t csd_vld10;	// L13945
  csd_vld10 = 0;	// L13946
  ap_uint<26> csd_pkt10;	// L13947
  csd_pkt10 = 0;	// L13948
  int32_t csd_dir10;	// L13949
  csd_dir10 = 0;	// L13950
  int32_t row_id10;	// L13951
  row_id10 = 2;	// L13952
  int32_t col_id10;	// L13953
  col_id10 = 2;	// L13954
  ap_uint<17> txn_r10;	// L13955
  txn_r10 = 0;	// L13956
  ap_uint<17> txs_r10;	// L13957
  txs_r10 = 0;	// L13958
  ap_uint<17> txw_r10;	// L13959
  txw_r10 = 0;	// L13960
  ap_uint<17> txe_r10;	// L13961
  txe_r10 = 0;	// L13962
  half hold_v10[4][2];	// L13963
  #pragma HLS array_partition variable=hold_v10 complete dim=1
  #pragma HLS array_partition variable=hold_v10 complete dim=2

  for (int v8788 = 0; v8788 < 4; v8788++) {	// L13964
    for (int v8789 = 0; v8789 < 2; v8789++) {	// L13964
      hold_v10[v8788][v8789] = 0.000000;	// L13964
    }
  }
  uint8_t hold_cnt10[4];	// L13965
  #pragma HLS array_partition variable=hold_cnt10 complete dim=1

  for (int v8791 = 0; v8791 < 4; v8791++) {	// L13966
    hold_cnt10[v8791] = 0;	// L13966
  }
  int32_t crv_ever10;	// L13967
  crv_ever10 = 0;	// L13968
  int32_t fe_ever10;	// L13969
  fe_ever10 = 0;	// L13970
  ap_uint<26> rbuf10[4][2];	// L13971
  #pragma HLS array_partition variable=rbuf10 complete dim=1
  #pragma HLS array_partition variable=rbuf10 complete dim=2

  for (int v8795 = 0; v8795 < 4; v8795++) {	// L13972
    for (int v8796 = 0; v8796 < 2; v8796++) {	// L13972
      rbuf10[v8795][v8796] = 0;	// L13972
    }
  }
  uint8_t rbcnt10[4];	// L13973
  #pragma HLS array_partition variable=rbcnt10 complete dim=1

  for (int v8798 = 0; v8798 < 4; v8798++) {	// L13974
    rbcnt10[v8798] = 0;	// L13974
  }
  int32_t cfg_isz10;	// L13975
  cfg_isz10 = 0;	// L13976
  int32_t cfg_itsz10;	// L13977
  cfg_itsz10 = 0;	// L13978
  uint8_t fetch_en10;	// L13979
  fetch_en10 = 0;	// L13980
  uint8_t instr_cnt10;	// L13981
  instr_cnt10 = 0;	// L13982
  uint8_t iter_cnt10;	// L13983
  iter_cnt10 = 0;	// L13984
  uint8_t condition_reg10;	// L13985
  condition_reg10 = 0;	// L13986
  uint8_t sb_v10[5];	// L13987
  #pragma HLS array_partition variable=sb_v10 complete dim=1

  for (int v8806 = 0; v8806 < 5; v8806++) {	// L13988
    sb_v10[v8806] = 0;	// L13988
  }
  uint8_t sb_dst10[5];	// L13989
  #pragma HLS array_partition variable=sb_dst10 complete dim=1

  for (int v8808 = 0; v8808 < 5; v8808++) {	// L13990
    sb_dst10[v8808] = 0;	// L13990
  }
  uint8_t sb_cmp10[5];	// L13991
  #pragma HLS array_partition variable=sb_cmp10 complete dim=1

  for (int v8810 = 0; v8810 < 5; v8810++) {	// L13992
    sb_cmp10[v8810] = 0;	// L13992
  }
  uint8_t sb_rtr10[5];	// L13993
  #pragma HLS array_partition variable=sb_rtr10 complete dim=1

  for (int v8812 = 0; v8812 < 5; v8812++) {	// L13994
    sb_rtr10[v8812] = 0;	// L13994
  }
  uint8_t sb_inj10[5];	// L13995
  #pragma HLS array_partition variable=sb_inj10 complete dim=1

  for (int v8814 = 0; v8814 < 5; v8814++) {	// L13996
    sb_inj10[v8814] = 0;	// L13996
  }
  uint8_t sb_dir10[5];	// L13997
  #pragma HLS array_partition variable=sb_dir10 complete dim=1

  for (int v8816 = 0; v8816 < 5; v8816++) {	// L13998
    sb_dir10[v8816] = 0;	// L13998
  }
  uint8_t sb_id10[5];	// L13999
  #pragma HLS array_partition variable=sb_id10 complete dim=1

  for (int v8818 = 0; v8818 < 5; v8818++) {	// L14000
    sb_id10[v8818] = 0;	// L14000
  }
  uint8_t sb_rvld10[5];	// L14001
  #pragma HLS array_partition variable=sb_rvld10 complete dim=1

  for (int v8820 = 0; v8820 < 5; v8820++) {	// L14002
    sb_rvld10[v8820] = 0;	// L14002
  }
  uint8_t sb_ix10[5];	// L14003
  #pragma HLS array_partition variable=sb_ix10 complete dim=1

  for (int v8822 = 0; v8822 < 5; v8822++) {	// L14004
    sb_ix10[v8822] = 0;	// L14004
  }
  half resq10[8];	// L14005
  #pragma HLS array_partition variable=resq10 complete dim=1
#pragma HLS dependence variable=resq10 type=inter dependent=false

  for (int v8824 = 0; v8824 < 8; v8824++) {	// L14006
    resq10[v8824] = 0.000000;	// L14006
  }
  uint8_t cmpq10[8];	// L14007
  #pragma HLS array_partition variable=cmpq10 complete dim=1
#pragma HLS dependence variable=cmpq10 type=inter dependent=false

  for (int v8826 = 0; v8826 < 8; v8826++) {	// L14008
    cmpq10[v8826] = 0;	// L14008
  }
  uint8_t resq_wr10;	// L14009
  resq_wr10 = 0;	// L14010
  l_S_t_0_t10: for (int t10 = 0; t10 < 374; t10++) {	// L14011
  #pragma HLS pipeline II=1
    ap_uint<26> p_w10;	// L14012
    p_w10 = 0;	// L14013
    ap_uint<26> p_e10;	// L14014
    p_e10 = 0;	// L14015
    ap_uint<26> p_n10;	// L14016
    p_n10 = 0;	// L14017
    ap_uint<26> p_s10;	// L14018
    p_s10 = 0;	// L14019
    uint8_t v8833 = rbcnt10[0];	// L14020
    int32_t v8834 = v8833;	// L14021
    bool v8835 = v8834 < 2;	// L14022
    if (v8835) {	// L14023
      ap_uint<26> v8836;
      bool v8837 = v8750.read_nb(v8836);
	// L14024
      ap_uint<26> gw10;	// L14025
      gw10 = v8836;	// L14026
      bool okw10;	// L14027
      okw10 = v8837;	// L14028
      bool v8840 = okw10;	// L14029
      if (v8840) {	// L14030
        ap_int<26> v8841 = gw10;	// L14031
        p_w10 = v8841;	// L14032
      }
    }
    uint8_t v8842 = rbcnt10[1];	// L14035
    int32_t v8843 = v8842;	// L14036
    bool v8844 = v8843 < 2;	// L14037
    if (v8844) {	// L14038
      ap_uint<26> v8845;
      bool v8846 = v8751.read_nb(v8845);
	// L14039
      ap_uint<26> ge10;	// L14040
      ge10 = v8845;	// L14041
      bool oke10;	// L14042
      oke10 = v8846;	// L14043
      bool v8849 = oke10;	// L14044
      if (v8849) {	// L14045
        ap_int<26> v8850 = ge10;	// L14046
        p_e10 = v8850;	// L14047
      }
    }
    uint8_t v8851 = rbcnt10[2];	// L14050
    int32_t v8852 = v8851;	// L14051
    bool v8853 = v8852 < 2;	// L14052
    if (v8853) {	// L14053
      ap_uint<26> v8854;
      bool v8855 = v8752.read_nb(v8854);
	// L14054
      ap_uint<26> gn10;	// L14055
      gn10 = v8854;	// L14056
      bool okn10;	// L14057
      okn10 = v8855;	// L14058
      bool v8858 = okn10;	// L14059
      if (v8858) {	// L14060
        ap_int<26> v8859 = gn10;	// L14061
        p_n10 = v8859;	// L14062
      }
    }
    uint8_t v8860 = rbcnt10[3];	// L14065
    int32_t v8861 = v8860;	// L14066
    bool v8862 = v8861 < 2;	// L14067
    if (v8862) {	// L14068
      ap_uint<26> v8863;
      bool v8864 = v8753.read_nb(v8863);
	// L14069
      ap_uint<26> gs10;	// L14070
      gs10 = v8863;	// L14071
      bool oks10;	// L14072
      oks10 = v8864;	// L14073
      bool v8867 = oks10;	// L14074
      if (v8867) {	// L14075
        ap_int<26> v8868 = gs10;	// L14076
        p_s10 = v8868;	// L14077
      }
    }
    ap_uint<26> fin10[4];	// L14080
    for (int v8870 = 0; v8870 < 4; v8870++) {	// L14081
      fin10[v8870] = 0;	// L14081
    }
    ap_int<26> v8871 = p_w10;	// L14082
    fin10[0] = v8871;	// L14083
    ap_int<26> v8872 = p_e10;	// L14084
    fin10[1] = v8872;	// L14085
    ap_int<26> v8873 = p_n10;	// L14086
    fin10[2] = v8873;	// L14087
    ap_int<26> v8874 = p_s10;	// L14088
    fin10[3] = v8874;	// L14089
    l_S_d_0_d40: for (int d40 = 0; d40 < 4; d40++) {	// L14090
      ap_uint<26> v8876 = fin10[d40];	// L14091
      bool v8877;
      ap_int<26> v8877_tmp = v8876;
      v8877 = v8877_tmp[25];	// L14092
      int32_t v8878 = v8877;	// L14093
      bool v8879 = v8878 == 1;	// L14094
      uint8_t v8880 = rbcnt10[d40];	// L14095
      int32_t v8881 = v8880;	// L14096
      bool v8882 = v8881 < 2;	// L14097
      bool v8883 = v8879 & v8882;	// L14098
      if (v8883) {	// L14099
        ap_uint<26> v8884 = fin10[d40];	// L14100
        uint8_t v8885 = rbcnt10[d40];	// L14101
        int v8886 = v8885;	// L14102
        rbuf10[d40][v8886] = v8884;	// L14103
        uint8_t v8887 = rbcnt10[d40];	// L14104
        ap_int<33> v8888 = v8887;	// L14105
        ap_int<33> v8889 = v8888 + 1;	// L14106
        uint8_t v8890 = v8889;	// L14107
        rbcnt10[d40] = v8890;	// L14108
      }
    }
    ap_uint<26> hd10[4];	// L14111
    for (int v8892 = 0; v8892 < 4; v8892++) {	// L14112
      hd10[v8892] = 0;	// L14112
    }
    int32_t hvld10[4];	// L14113
    for (int v8894 = 0; v8894 < 4; v8894++) {	// L14114
      hvld10[v8894] = 0;	// L14114
    }
    int32_t hit10[4];	// L14115
    for (int v8896 = 0; v8896 < 4; v8896++) {	// L14116
      hit10[v8896] = 0;	// L14116
    }
    int32_t axis10[4];	// L14117
    for (int v8898 = 0; v8898 < 4; v8898++) {	// L14118
      axis10[v8898] = 0;	// L14118
    }
    int32_t v8899 = col_id10;	// L14119
    axis10[0] = v8899;	// L14120
    int32_t v8900 = col_id10;	// L14121
    axis10[1] = v8900;	// L14122
    int32_t v8901 = row_id10;	// L14123
    axis10[2] = v8901;	// L14124
    int32_t v8902 = row_id10;	// L14125
    axis10[3] = v8902;	// L14126
    l_S_d_1_d41: for (int d41 = 0; d41 < 4; d41++) {	// L14127
      uint8_t v8904 = rbcnt10[d41];	// L14128
      int32_t v8905 = v8904;	// L14129
      bool v8906 = v8905 > 0;	// L14130
      if (v8906) {	// L14131
        ap_uint<26> v8907 = rbuf10[d41][0];	// L14132
        hd10[d41] = v8907;	// L14133
        hvld10[d41] = 1;	// L14134
        ap_uint<26> v8908 = hd10[d41];	// L14135
        ap_int<4> v8909;
        ap_int<26> v8909_tmp = v8908;
        v8909 = v8909_tmp(24, 21);	// L14136
        int32_t v8910 = axis10[d41];	// L14137
        int32_t v8911 = v8909;	// L14138
        bool v8912 = v8911 == v8910;	// L14139
        if (v8912) {	// L14140
          hit10[d41] = 1;	// L14141
        }
      }
    }
    ap_uint<26> o_crv10;	// L14145
    o_crv10 = 0;	// L14146
    int32_t crv_in10;	// L14147
    crv_in10 = -1;	// L14148
    int32_t v8915 = hit10[3];	// L14149
    bool v8916 = v8915 == 1;	// L14150
    if (v8916) {	// L14151
      ap_uint<26> v8917 = hd10[3];	// L14152
      o_crv10 = v8917;	// L14153
      crv_in10 = 3;	// L14154
    } else {
      int32_t v8918 = hit10[2];	// L14156
      bool v8919 = v8918 == 1;	// L14157
      if (v8919) {	// L14158
        ap_uint<26> v8920 = hd10[2];	// L14159
        o_crv10 = v8920;	// L14160
        crv_in10 = 2;	// L14161
      } else {
        int32_t v8921 = hit10[1];	// L14163
        bool v8922 = v8921 == 1;	// L14164
        if (v8922) {	// L14165
          ap_uint<26> v8923 = hd10[1];	// L14166
          o_crv10 = v8923;	// L14167
          crv_in10 = 1;	// L14168
        } else {
          int32_t v8924 = hit10[0];	// L14170
          bool v8925 = v8924 == 1;	// L14171
          if (v8925) {	// L14172
            ap_uint<26> v8926 = hd10[0];	// L14173
            o_crv10 = v8926;	// L14174
            crv_in10 = 0;	// L14175
          }
        }
      }
    }
    int32_t pop10[4];	// L14180
    for (int v8928 = 0; v8928 < 4; v8928++) {	// L14181
      pop10[v8928] = 0;	// L14181
    }
    int32_t inj_done10;	// L14182
    inj_done10 = 0;	// L14183
    int32_t idir10;	// L14184
    idir10 = -1;	// L14185
    ap_int<26> v8931 = csd_pkt10;	// L14186
    bool v8932;
    ap_int<26> v8932_tmp = v8931;
    v8932 = v8932_tmp[25];	// L14187
    int32_t v8933 = v8932;	// L14188
    bool v8934 = v8933 == 1;	// L14189
    if (v8934) {	// L14190
      int32_t v8935 = csd_dir10;	// L14191
      ap_int<33> v8936 = v8935;	// L14192
      ap_int<33> v8937 = 3 - v8936;	// L14193
      int32_t v8938 = v8937;	// L14194
      idir10 = v8938;	// L14195
    }
    int32_t v8939 = idir10;	// L14197
    bool v8940 = v8939 == 0;	// L14198
    if (v8940) {	// L14199
      ap_int<26> v8941 = csd_pkt10;	// L14200
      bool v8942 = v8754.write_nb(v8941);
	// L14201
      if (v8942) {	// L14202
        inj_done10 = 1;	// L14203
      }
    } else {
      int32_t v8943 = hvld10[0];	// L14206
      bool v8944 = v8943 == 1;	// L14207
      int32_t v8945 = hit10[0];	// L14208
      bool v8946 = v8945 == 0;	// L14209
      bool v8947 = v8944 & v8946;	// L14210
      if (v8947) {	// L14211
        ap_uint<26> v8948 = hd10[0];	// L14212
        bool v8949 = v8754.write_nb(v8948);
	// L14213
        if (v8949) {	// L14214
          pop10[0] = 1;	// L14215
        }
      }
    }
    int32_t v8950 = idir10;	// L14219
    bool v8951 = v8950 == 1;	// L14220
    if (v8951) {	// L14221
      ap_int<26> v8952 = csd_pkt10;	// L14222
      bool v8953 = v8755.write_nb(v8952);
	// L14223
      if (v8953) {	// L14224
        inj_done10 = 1;	// L14225
      }
    } else {
      int32_t v8954 = hvld10[1];	// L14228
      bool v8955 = v8954 == 1;	// L14229
      int32_t v8956 = hit10[1];	// L14230
      bool v8957 = v8956 == 0;	// L14231
      bool v8958 = v8955 & v8957;	// L14232
      if (v8958) {	// L14233
        ap_uint<26> v8959 = hd10[1];	// L14234
        bool v8960 = v8755.write_nb(v8959);
	// L14235
        if (v8960) {	// L14236
          pop10[1] = 1;	// L14237
        }
      }
    }
    int32_t v8961 = idir10;	// L14241
    bool v8962 = v8961 == 2;	// L14242
    if (v8962) {	// L14243
      ap_int<26> v8963 = csd_pkt10;	// L14244
      bool v8964 = v8756.write_nb(v8963);
	// L14245
      if (v8964) {	// L14246
        inj_done10 = 1;	// L14247
      }
    } else {
      int32_t v8965 = hvld10[2];	// L14250
      bool v8966 = v8965 == 1;	// L14251
      int32_t v8967 = hit10[2];	// L14252
      bool v8968 = v8967 == 0;	// L14253
      bool v8969 = v8966 & v8968;	// L14254
      if (v8969) {	// L14255
        ap_uint<26> v8970 = hd10[2];	// L14256
        bool v8971 = v8756.write_nb(v8970);
	// L14257
        if (v8971) {	// L14258
          pop10[2] = 1;	// L14259
        }
      }
    }
    int32_t v8972 = idir10;	// L14263
    bool v8973 = v8972 == 3;	// L14264
    if (v8973) {	// L14265
      ap_int<26> v8974 = csd_pkt10;	// L14266
      bool v8975 = v8757.write_nb(v8974);
	// L14267
      if (v8975) {	// L14268
        inj_done10 = 1;	// L14269
      }
    } else {
      int32_t v8976 = hvld10[3];	// L14272
      bool v8977 = v8976 == 1;	// L14273
      int32_t v8978 = hit10[3];	// L14274
      bool v8979 = v8978 == 0;	// L14275
      bool v8980 = v8977 & v8979;	// L14276
      if (v8980) {	// L14277
        ap_uint<26> v8981 = hd10[3];	// L14278
        bool v8982 = v8757.write_nb(v8981);
	// L14279
        if (v8982) {	// L14280
          pop10[3] = 1;	// L14281
        }
      }
    }
    int32_t v8983 = crv_in10;	// L14285
    bool v8984 = v8983 >= 0;	// L14286
    if (v8984) {	// L14287
      int32_t v8985 = crv_in10;	// L14288
      int v8986 = v8985;	// L14289
      pop10[v8986] = 1;	// L14290
    }
    l_S_d_2_d42: for (int d42 = 0; d42 < 4; d42++) {	// L14292
      int32_t v8988 = pop10[d42];	// L14293
      bool v8989 = v8988 == 1;	// L14294
      if (v8989) {	// L14295
        l_S_sft_2_sft10: for (int sft10 = 0; sft10 < 1; sft10++) {	// L14296
          ap_uint<26> v8991 = rbuf10[d42][(sft10 + 1)];	// L14297
          rbuf10[d42][sft10] = v8991;	// L14298
        }
        uint8_t v8992 = rbcnt10[d42];	// L14300
        ap_int<33> v8993 = v8992;	// L14301
        ap_int<33> v8994 = v8993 - 1;	// L14302
        uint8_t v8995 = v8994;	// L14303
        rbcnt10[d42] = v8995;	// L14304
      }
    }
    int32_t v8996 = inj_done10;	// L14307
    bool v8997 = v8996 == 1;	// L14308
    if (v8997) {	// L14309
      csd_pkt10 = 0;	// L14310
    }
    ap_int<26> v8998 = o_crv10;	// L14312
    bool v8999;
    ap_int<26> v8999_tmp = v8998;
    v8999 = v8999_tmp[25];	// L14313
    int32_t v9000 = v8999;	// L14314
    crv_vld10 = v9000;	// L14315
    int32_t v9001 = crv_vld10;	// L14316
    bool v9002 = v9001 == 1;	// L14317
    if (v9002) {	// L14318
      crv_ever10 = 1;	// L14319
    }
    ap_int<26> v9003 = o_crv10;	// L14321
    int16_t v9004;
    ap_int<26> v9004_tmp = v9003;
    v9004 = v9004_tmp(15, 0);	// L14322
    half v9005;
    union { uint16_t from; half to;} _converter_v9004_to_v9005 = {};
    _converter_v9004_to_v9005.from = v9004;
    v9005 = _converter_v9004_to_v9005.to;	// L14323
    crv_data10 = v9005;	// L14324
    ap_int<26> v9006 = o_crv10;	// L14325
    ap_int<4> v9007;
    ap_int<26> v9007_tmp = v9006;
    v9007 = v9007_tmp(19, 16);	// L14326
    int32_t v9008 = v9007;	// L14327
    crv_addr10 = v9008;	// L14328
    ap_int<26> v9009 = o_crv10;	// L14329
    bool v9010;
    ap_int<26> v9010_tmp = v9009;
    v9010 = v9010_tmp[20];	// L14330
    int32_t v9011 = v9010;	// L14331
    crv_mode10 = v9011;	// L14332
    ap_int<26> v9012 = o_crv10;	// L14333
    int16_t v9013;
    ap_int<26> v9013_tmp = v9012;
    v9013 = v9013_tmp(15, 0);	// L14334
    int32_t v9014 = v9013;	// L14335
    crv_raw10 = v9014;	// L14336
    half rxv10[4];	// L14337
    for (int v9016 = 0; v9016 < 4; v9016++) {	// L14338
      rxv10[v9016] = 0.000000;	// L14338
    }
    int32_t rxvld10[4];	// L14339
    for (int v9018 = 0; v9018 < 4; v9018++) {	// L14340
      rxvld10[v9018] = 0;	// L14340
    }
    uint8_t v9019 = hold_cnt10[0];	// L14341
    int32_t v9020 = v9019;	// L14342
    bool v9021 = v9020 < 2;	// L14343
    if (v9021) {	// L14344
      ap_uint<17> v9022;
      bool v9023 = v8758.read_nb(v9022);
	// L14345
      ap_uint<17> sgn10;	// L14346
      sgn10 = v9022;	// L14347
      bool sqn10;	// L14348
      sqn10 = v9023;	// L14349
      bool v9026 = sqn10;	// L14350
      int32_t v9027 = v9026;	// L14351
      bool v9028 = v9027 == 1;	// L14352
      if (v9028) {	// L14353
        ap_int<17> v9029 = sgn10;	// L14354
        int16_t v9030;
        ap_int<17> v9030_tmp = v9029;
        v9030 = v9030_tmp(16, 1);	// L14355
        half v9031;
        union { uint16_t from; half to;} _converter_v9030_to_v9031 = {};
        _converter_v9030_to_v9031.from = v9030;
        v9031 = _converter_v9030_to_v9031.to;	// L14356
        rxv10[0] = v9031;	// L14357
        rxvld10[0] = 1;	// L14358
      }
    }
    uint8_t v9032 = hold_cnt10[1];	// L14361
    int32_t v9033 = v9032;	// L14362
    bool v9034 = v9033 < 2;	// L14363
    if (v9034) {	// L14364
      ap_uint<17> v9035;
      bool v9036 = v8759.read_nb(v9035);
	// L14365
      ap_uint<17> sgs10;	// L14366
      sgs10 = v9035;	// L14367
      bool sqs10;	// L14368
      sqs10 = v9036;	// L14369
      bool v9039 = sqs10;	// L14370
      int32_t v9040 = v9039;	// L14371
      bool v9041 = v9040 == 1;	// L14372
      if (v9041) {	// L14373
        ap_int<17> v9042 = sgs10;	// L14374
        int16_t v9043;
        ap_int<17> v9043_tmp = v9042;
        v9043 = v9043_tmp(16, 1);	// L14375
        half v9044;
        union { uint16_t from; half to;} _converter_v9043_to_v9044 = {};
        _converter_v9043_to_v9044.from = v9043;
        v9044 = _converter_v9043_to_v9044.to;	// L14376
        rxv10[1] = v9044;	// L14377
        rxvld10[1] = 1;	// L14378
      }
    }
    uint8_t v9045 = hold_cnt10[2];	// L14381
    int32_t v9046 = v9045;	// L14382
    bool v9047 = v9046 < 2;	// L14383
    if (v9047) {	// L14384
      ap_uint<17> v9048;
      bool v9049 = v8760.read_nb(v9048);
	// L14385
      ap_uint<17> sgw10;	// L14386
      sgw10 = v9048;	// L14387
      bool sqw10;	// L14388
      sqw10 = v9049;	// L14389
      bool v9052 = sqw10;	// L14390
      int32_t v9053 = v9052;	// L14391
      bool v9054 = v9053 == 1;	// L14392
      if (v9054) {	// L14393
        ap_int<17> v9055 = sgw10;	// L14394
        int16_t v9056;
        ap_int<17> v9056_tmp = v9055;
        v9056 = v9056_tmp(16, 1);	// L14395
        half v9057;
        union { uint16_t from; half to;} _converter_v9056_to_v9057 = {};
        _converter_v9056_to_v9057.from = v9056;
        v9057 = _converter_v9056_to_v9057.to;	// L14396
        rxv10[2] = v9057;	// L14397
        rxvld10[2] = 1;	// L14398
      }
    }
    uint8_t v9058 = hold_cnt10[3];	// L14401
    int32_t v9059 = v9058;	// L14402
    bool v9060 = v9059 < 2;	// L14403
    if (v9060) {	// L14404
      ap_uint<17> v9061;
      bool v9062 = v8761.read_nb(v9061);
	// L14405
      ap_uint<17> sge10;	// L14406
      sge10 = v9061;	// L14407
      bool sqe10;	// L14408
      sqe10 = v9062;	// L14409
      bool v9065 = sqe10;	// L14410
      int32_t v9066 = v9065;	// L14411
      bool v9067 = v9066 == 1;	// L14412
      if (v9067) {	// L14413
        ap_int<17> v9068 = sge10;	// L14414
        int16_t v9069;
        ap_int<17> v9069_tmp = v9068;
        v9069 = v9069_tmp(16, 1);	// L14415
        half v9070;
        union { uint16_t from; half to;} _converter_v9069_to_v9070 = {};
        _converter_v9069_to_v9070.from = v9069;
        v9070 = _converter_v9069_to_v9070.to;	// L14416
        rxv10[3] = v9070;	// L14417
        rxvld10[3] = 1;	// L14418
      }
    }
    l_S_d_4_d43: for (int d43 = 0; d43 < 4; d43++) {	// L14421
      int32_t v9072 = rxvld10[d43];	// L14422
      bool v9073 = v9072 == 1;	// L14423
      if (v9073) {	// L14424
        half v9074 = rxv10[d43];	// L14425
        uint8_t v9075 = hold_cnt10[d43];	// L14426
        int v9076 = v9075;	// L14427
        hold_v10[d43][v9076] = v9074;	// L14428
        uint8_t v9077 = hold_cnt10[d43];	// L14429
        ap_int<33> v9078 = v9077;	// L14430
        ap_int<33> v9079 = v9078 + 1;	// L14431
        uint8_t v9080 = v9079;	// L14432
        hold_cnt10[d43] = v9080;	// L14433
      }
    }
    ap_uint<17> tx_n10;	// L14436
    tx_n10 = 0;	// L14437
    ap_uint<17> tx_s10;	// L14438
    tx_s10 = 0;	// L14439
    ap_uint<17> tx_w10;	// L14440
    tx_w10 = 0;	// L14441
    ap_uint<17> tx_e10;	// L14442
    tx_e10 = 0;	// L14443
    uint8_t v9085 = sb_v10[0];	// L14444
    int32_t v9086 = v9085;	// L14445
    bool v9087 = v9086 == 1;	// L14446
    if (v9087) {	// L14447
      uint8_t v9088 = sb_ix10[0];	// L14448
      int v9089 = v9088;	// L14449
      half v9090 = resq10[v9089];	// L14450
      half wb10;
#pragma HLS dependence variable=wb10 type=inter dependent=false	// L14451
      wb10 = v9090;	// L14452
      uint8_t v9092 = sb_cmp10[0];	// L14453
      int32_t v9093 = v9092;	// L14454
      bool v9094 = v9093 == 1;	// L14455
      if (v9094) {	// L14456
        uint8_t v9095 = sb_ix10[0];	// L14457
        int v9096 = v9095;	// L14458
        uint8_t v9097 = cmpq10[v9096];	// L14459
        condition_reg10 = v9097;	// L14460
      }
      uint8_t v9098 = sb_rtr10[0];	// L14462
      int32_t v9099 = v9098;	// L14463
      bool v9100 = v9099 == 1;	// L14464
      if (v9100) {	// L14465
        uint8_t v9101 = sb_inj10[0];	// L14466
        int32_t v9102 = v9101;	// L14467
        bool v9103 = v9102 == 1;	// L14468
        ap_int<26> v9104 = csd_pkt10;	// L14469
        bool v9105;
        ap_int<26> v9105_tmp = v9104;
        v9105 = v9105_tmp[25];	// L14470
        int32_t v9106 = v9105;	// L14471
        bool v9107 = v9106 == 0;	// L14472
        bool v9108 = v9103 & v9107;	// L14473
        if (v9108) {	// L14474
          half v9109 = wb10;	// L14475
          uint16_t v9110;
          union { half from; uint16_t to;} _converter_v9109_to_v9110 = {};
          _converter_v9109_to_v9110.from = v9109;
          v9110 = _converter_v9109_to_v9110.to;	// L14476
          ap_int<26> v9111 = csd_pkt10;	// L14477
          ap_int<26> v9112;
          ap_int<26> v9112_tmp = v9111;
          v9112_tmp(15, 0) = v9110;
          v9112 = v9112_tmp;	// L14478
          csd_pkt10 = v9112;	// L14479
          uint8_t v9113 = sb_dst10[0];	// L14480
          ap_uint<4> v9114 = v9113;	// L14481
          ap_int<26> v9115 = csd_pkt10;	// L14482
          ap_int<26> v9116;
          ap_int<26> v9116_tmp = v9115;
          v9116_tmp(19, 16) = v9114;
          v9116 = v9116_tmp;	// L14483
          csd_pkt10 = v9116;	// L14484
          uint8_t v9117 = sb_id10[0];	// L14485
          ap_uint<4> v9118 = v9117;	// L14486
          ap_int<26> v9119 = csd_pkt10;	// L14487
          ap_int<26> v9120;
          ap_int<26> v9120_tmp = v9119;
          v9120_tmp(24, 21) = v9118;
          v9120 = v9120_tmp;	// L14488
          csd_pkt10 = v9120;	// L14489
          uint8_t v9121 = sb_rvld10[0];	// L14490
          bool v9122 = v9121;	// L14491
          ap_int<26> v9123 = csd_pkt10;	// L14492
          ap_int<26> v9124;
          ap_int<26> v9124_tmp = v9123;
          v9124_tmp[25] = v9122;          v9124 = v9124_tmp;	// L14493
          csd_pkt10 = v9124;	// L14494
          uint8_t v9125 = sb_dir10[0];	// L14495
          int32_t v9126 = v9125;	// L14496
          csd_dir10 = v9126;	// L14497
        }
      } else {
        uint8_t v9127 = sb_dst10[0];	// L14500
        int32_t v9128 = v9127;	// L14501
        bool v9129 = v9128 >= 12;	// L14502
        if (v9129) {	// L14503
          ap_uint<17> tw010;	// L14504
          tw010 = 0;	// L14505
          uint8_t v9131 = sb_rvld10[0];	// L14506
          bool v9132 = v9131;	// L14507
          ap_int<17> v9133 = tw010;	// L14508
          ap_int<17> v9134;
          ap_int<17> v9134_tmp = v9133;
          v9134_tmp[0] = v9132;          v9134 = v9134_tmp;	// L14509
          tw010 = v9134;	// L14510
          half v9135 = wb10;	// L14511
          uint16_t v9136;
          union { half from; uint16_t to;} _converter_v9135_to_v9136 = {};
          _converter_v9135_to_v9136.from = v9135;
          v9136 = _converter_v9135_to_v9136.to;	// L14512
          ap_int<17> v9137 = tw010;	// L14513
          ap_int<17> v9138;
          ap_int<17> v9138_tmp = v9137;
          v9138_tmp(16, 1) = v9136;
          v9138 = v9138_tmp;	// L14514
          tw010 = v9138;	// L14515
          uint8_t v9139 = sb_dst10[0];	// L14516
          int32_t v9140 = v9139;	// L14517
          int32_t v9141 = v9140 & 3;	// L14518
          bool v9142 = v9141 == 0;	// L14519
          if (v9142) {	// L14520
            ap_int<17> v9143 = tw010;	// L14521
            tx_n10 = v9143;	// L14522
          } else {
            uint8_t v9144 = sb_dst10[0];	// L14524
            int32_t v9145 = v9144;	// L14525
            int32_t v9146 = v9145 & 3;	// L14526
            bool v9147 = v9146 == 1;	// L14527
            if (v9147) {	// L14528
              ap_int<17> v9148 = tw010;	// L14529
              tx_s10 = v9148;	// L14530
            } else {
              uint8_t v9149 = sb_dst10[0];	// L14532
              int32_t v9150 = v9149;	// L14533
              int32_t v9151 = v9150 & 3;	// L14534
              bool v9152 = v9151 == 2;	// L14535
              if (v9152) {	// L14536
                ap_int<17> v9153 = tw010;	// L14537
                tx_w10 = v9153;	// L14538
              } else {
                ap_int<17> v9154 = tw010;	// L14540
                tx_e10 = v9154;	// L14541
              }
            }
          }
        } else {
          uint8_t v9155 = sb_rvld10[0];	// L14546
          int32_t v9156 = v9155;	// L14547
          bool v9157 = v9156 == 1;	// L14548
          if (v9157) {	// L14549
            uint8_t v9158 = sb_dst10[0];	// L14550
            int32_t v9159 = v9158;	// L14551
            bool v9160 = v9159 < 8;	// L14552
            int32_t v9161 = dsmask10;	// L14553
            int32_t v9162 = v9161 >> v9159;	// L14554
            int32_t v9163 = v9162 & 1;	// L14555
            bool v9164 = v9163 == 1;	// L14556
            bool v9165 = v9160 & v9164;	// L14557
            if (v9165) {	// L14558
              uint8_t v9166 = sb_dst10[0];	// L14559
              int v9167 = v9166;	// L14560
              int32_t v9168 = drf_full10[v9167];	// L14561
              bool v9169 = v9168 == 0;	// L14562
              if (v9169) {	// L14563
                half v9170 = wb10;	// L14564
                uint8_t v9171 = sb_dst10[0];	// L14565
                int v9172 = v9171;	// L14566
                drf10[v9172] = v9170;	// L14567
                uint8_t v9173 = sb_dst10[0];	// L14568
                int v9174 = v9173;	// L14569
                drf_full10[v9174] = 1;	// L14570
              }
            } else {
              half v9175 = wb10;	// L14573
              uint8_t v9176 = sb_dst10[0];	// L14574
              int32_t v9177 = v9176;	// L14575
              int32_t v9178 = v9177 & 7;	// L14576
              int v9179 = v9178;	// L14577
              drf10[v9179] = v9175;	// L14578
            }
          }
        }
      }
    }
    int32_t pc10;	// L14584
    pc10 = -1;	// L14585
    int8_t v9181 = fetch_en10;	// L14586
    int32_t v9182 = v9181;	// L14587
    bool v9183 = v9182 == 1;	// L14588
    if (v9183) {	// L14589
      int8_t v9184 = instr_cnt10;	// L14590
      int32_t v9185 = v9184;	// L14591
      pc10 = v9185;	// L14592
    }
    int8_t v9186 = fetch_en10;	// L14594
    int32_t v9187 = v9186;	// L14595
    bool v9188 = v9187 == 1;	// L14596
    if (v9188) {	// L14597
      fe_ever10 = 1;	// L14598
    }
    int32_t instr10;	// L14600
    instr10 = 0;	// L14601
    int32_t v9190 = pc10;	// L14602
    bool v9191 = v9190 >= 0;	// L14603
    if (v9191) {	// L14604
      int32_t v9192 = pc10;	// L14605
      int v9193 = v9192;	// L14606
      int32_t v9194 = irf10[v9193];	// L14607
      instr10 = v9194;	// L14608
    }
    int32_t v9195 = instr10;	// L14610
    int32_t v9196 = v9195 & 15;	// L14611
    int32_t op10;	// L14612
    op10 = v9196;	// L14613
    int32_t v9198 = instr10;	// L14614
    int32_t v9199 = v9198 >> 4;	// L14615
    int32_t v9200 = v9199 & 15;	// L14616
    int32_t dst10;	// L14617
    dst10 = v9200;	// L14618
    int32_t v9202 = instr10;	// L14619
    int32_t v9203 = v9202 >> 8;	// L14620
    int32_t v9204 = v9203 & 15;	// L14621
    int32_t s110;	// L14622
    s110 = v9204;	// L14623
    int32_t v9206 = instr10;	// L14624
    int32_t v9207 = v9206 >> 12;	// L14625
    int32_t v9208 = v9207 & 15;	// L14626
    int32_t s210;	// L14627
    s210 = v9208;	// L14628
    half a10;	// L14629
    a10 = 0.000000;	// L14630
    half b10;	// L14631
    b10 = 0.000000;	// L14632
    int32_t v9212 = s110;	// L14633
    bool v9213 = v9212 >= 12;	// L14634
    if (v9213) {	// L14635
      int32_t v9214 = s110;	// L14636
      int32_t v9215 = v9214 & 3;	// L14637
      int v9216 = v9215;	// L14638
      half v9217 = hold_v10[v9216][0];	// L14639
      a10 = v9217;	// L14640
    } else {
      int32_t v9218 = s110;	// L14642
      int v9219 = v9218;	// L14643
      half v9220 = drf10[v9219];	// L14644
      a10 = v9220;	// L14645
    }
    int32_t v9221 = s210;	// L14647
    bool v9222 = v9221 >= 12;	// L14648
    if (v9222) {	// L14649
      int32_t v9223 = s210;	// L14650
      int32_t v9224 = v9223 & 3;	// L14651
      int v9225 = v9224;	// L14652
      half v9226 = hold_v10[v9225][0];	// L14653
      b10 = v9226;	// L14654
    } else {
      int32_t v9227 = s210;	// L14656
      int v9228 = v9227;	// L14657
      half v9229 = drf10[v9228];	// L14658
      b10 = v9229;	// L14659
    }
    int32_t a_vld10;	// L14661
    a_vld10 = 1;	// L14662
    int32_t b_vld10;	// L14663
    b_vld10 = 1;	// L14664
    int32_t v9232 = s110;	// L14665
    bool v9233 = v9232 >= 12;	// L14666
    if (v9233) {	// L14667
      a_vld10 = 0;	// L14668
      int32_t v9234 = s110;	// L14669
      int32_t v9235 = v9234 & 3;	// L14670
      int v9236 = v9235;	// L14671
      uint8_t v9237 = hold_cnt10[v9236];	// L14672
      int32_t v9238 = v9237;	// L14673
      bool v9239 = v9238 > 0;	// L14674
      if (v9239) {	// L14675
        a_vld10 = 1;	// L14676
      }
    }
    int32_t v9240 = s210;	// L14679
    bool v9241 = v9240 >= 12;	// L14680
    if (v9241) {	// L14681
      b_vld10 = 0;	// L14682
      int32_t v9242 = s210;	// L14683
      int32_t v9243 = v9242 & 3;	// L14684
      int v9244 = v9243;	// L14685
      uint8_t v9245 = hold_cnt10[v9244];	// L14686
      int32_t v9246 = v9245;	// L14687
      bool v9247 = v9246 > 0;	// L14688
      if (v9247) {	// L14689
        b_vld10 = 1;	// L14690
      }
    }
    int32_t v9248 = s110;	// L14693
    bool v9249 = v9248 < 8;	// L14694
    int32_t v9250 = dsmask10;	// L14695
    int32_t v9251 = v9250 >> v9248;	// L14696
    int32_t v9252 = v9251 & 1;	// L14697
    bool v9253 = v9252 == 1;	// L14698
    bool v9254 = v9249 & v9253;	// L14699
    if (v9254) {	// L14700
      int32_t v9255 = s110;	// L14701
      int v9256 = v9255;	// L14702
      int32_t v9257 = drf_full10[v9256];	// L14703
      bool v9258 = v9257 == 0;	// L14704
      if (v9258) {	// L14705
        a_vld10 = 0;	// L14706
      }
    }
    int32_t v9259 = s210;	// L14709
    bool v9260 = v9259 < 8;	// L14710
    int32_t v9261 = dsmask10;	// L14711
    int32_t v9262 = v9261 >> v9259;	// L14712
    int32_t v9263 = v9262 & 1;	// L14713
    bool v9264 = v9263 == 1;	// L14714
    bool v9265 = v9260 & v9264;	// L14715
    if (v9265) {	// L14716
      int32_t v9266 = s210;	// L14717
      int v9267 = v9266;	// L14718
      int32_t v9268 = drf_full10[v9267];	// L14719
      bool v9269 = v9268 == 0;	// L14720
      if (v9269) {	// L14721
        b_vld10 = 0;	// L14722
      }
    }
    int32_t binop10;	// L14725
    binop10 = 0;	// L14726
    int32_t v9271 = op10;	// L14727
    bool v9272 = v9271 == 0;	// L14728
    bool v9273 = v9271 == 1;	// L14729
    bool v9274 = v9271 == 2;	// L14730
    bool v9275 = v9271 == 8;	// L14731
    bool v9276 = v9271 == 9;	// L14732
    bool v9277 = v9272 | v9273;	// L14733
    bool v9278 = v9277 | v9274;	// L14734
    bool v9279 = v9278 | v9275;	// L14735
    bool v9280 = v9279 | v9276;	// L14736
    if (v9280) {	// L14737
      binop10 = 1;	// L14738
    }
    int32_t raw10;	// L14740
    raw10 = 0;	// L14741
    int32_t cmp_busy10;	// L14742
    cmp_busy10 = 0;	// L14743
    l_S_k_5_k20: for (int k20 = 0; k20 < 4; k20++) {	// L14744
      uint8_t v9284 = sb_v10[(k20 + 1)];	// L14745
      int32_t v9285 = v9284;	// L14746
      bool v9286 = v9285 == 1;	// L14747
      uint8_t v9287 = sb_rtr10[(k20 + 1)];	// L14748
      int32_t v9288 = v9287;	// L14749
      bool v9289 = v9288 == 0;	// L14750
      uint8_t v9290 = sb_dst10[(k20 + 1)];	// L14751
      int32_t v9291 = v9290;	// L14752
      bool v9292 = v9291 < 12;	// L14753
      bool v9293 = v9286 & v9289;	// L14754
      bool v9294 = v9293 & v9292;	// L14755
      if (v9294) {	// L14756
        int32_t v9295 = s110;	// L14757
        bool v9296 = v9295 < 12;	// L14758
        uint8_t v9297 = sb_dst10[(k20 + 1)];	// L14759
        int32_t v9298 = v9297;	// L14760
        int32_t v9299 = v9298 & 7;	// L14761
        int32_t v9300 = v9295 & 7;	// L14762
        bool v9301 = v9299 == v9300;	// L14763
        bool v9302 = v9296 & v9301;	// L14764
        if (v9302) {	// L14765
          raw10 = 1;	// L14766
        }
        int32_t v9303 = binop10;	// L14768
        bool v9304 = v9303 == 1;	// L14769
        int32_t v9305 = s210;	// L14770
        bool v9306 = v9305 < 12;	// L14771
        uint8_t v9307 = sb_dst10[(k20 + 1)];	// L14772
        int32_t v9308 = v9307;	// L14773
        int32_t v9309 = v9308 & 7;	// L14774
        int32_t v9310 = v9305 & 7;	// L14775
        bool v9311 = v9309 == v9310;	// L14776
        bool v9312 = v9304 & v9306;	// L14777
        bool v9313 = v9312 & v9311;	// L14778
        if (v9313) {	// L14779
          raw10 = 1;	// L14780
        }
      }
      uint8_t v9314 = sb_v10[(k20 + 1)];	// L14783
      int32_t v9315 = v9314;	// L14784
      bool v9316 = v9315 == 1;	// L14785
      uint8_t v9317 = sb_cmp10[(k20 + 1)];	// L14786
      int32_t v9318 = v9317;	// L14787
      bool v9319 = v9318 == 1;	// L14788
      bool v9320 = v9316 & v9319;	// L14789
      if (v9320) {	// L14790
        cmp_busy10 = 1;	// L14791
      }
    }
    int32_t is_cond10;	// L14794
    is_cond10 = 0;	// L14795
    int32_t v9322 = op10;	// L14796
    bool v9323 = v9322 >= 12;	// L14797
    ap_int<33> v9324 = v9322;	// L14798
    bool v9325 = v9324 <= 15;	// L14799
    bool v9326 = v9323 & v9325;	// L14800
    if (v9326) {	// L14801
      is_cond10 = 1;	// L14802
    }
    int32_t grant10;	// L14804
    grant10 = 0;	// L14805
    int32_t v9328 = pc10;	// L14806
    bool v9329 = v9328 >= 0;	// L14807
    if (v9329) {	// L14808
      grant10 = 1;	// L14809
    }
    int32_t v9330 = pc10;	// L14811
    bool v9331 = v9330 >= 0;	// L14812
    int32_t v9332 = a_vld10;	// L14813
    bool v9333 = v9332 == 0;	// L14814
    int32_t v9334 = binop10;	// L14815
    bool v9335 = v9334 == 1;	// L14816
    int32_t v9336 = b_vld10;	// L14817
    bool v9337 = v9336 == 0;	// L14818
    bool v9338 = v9335 & v9337;	// L14819
    bool v9339 = v9333 | v9338;	// L14820
    bool v9340 = v9331 & v9339;	// L14821
    if (v9340) {	// L14822
      grant10 = 0;	// L14823
    }
    int32_t v9341 = pc10;	// L14825
    bool v9342 = v9341 >= 0;	// L14826
    int32_t v9343 = raw10;	// L14827
    bool v9344 = v9343 == 1;	// L14828
    int32_t v9345 = is_cond10;	// L14829
    bool v9346 = v9345 == 1;	// L14830
    int32_t v9347 = cmp_busy10;	// L14831
    bool v9348 = v9347 == 1;	// L14832
    bool v9349 = v9346 & v9348;	// L14833
    bool v9350 = v9344 | v9349;	// L14834
    bool v9351 = v9342 & v9350;	// L14835
    if (v9351) {	// L14836
      grant10 = 0;	// L14837
    }
    int32_t v9352 = grant10;	// L14839
    bool v9353 = v9352 == 1;	// L14840
    if (v9353) {	// L14841
      int8_t v9354 = instr_cnt10;	// L14842
      int32_t v9355 = cfg_isz10;	// L14843
      int32_t v9356 = v9354;	// L14844
      bool v9357 = v9356 == v9355;	// L14845
      if (v9357) {	// L14846
        instr_cnt10 = 0;	// L14847
        int8_t v9358 = iter_cnt10;	// L14848
        int32_t v9359 = cfg_itsz10;	// L14849
        ap_int<33> v9360 = v9359;	// L14850
        ap_int<33> v9361 = v9360 - 1;	// L14851
        ap_int<33> v9362 = v9358;	// L14852
        bool v9363 = v9362 == v9361;	// L14853
        if (v9363) {	// L14854
          fetch_en10 = 0;	// L14855
        } else {
          int8_t v9364 = iter_cnt10;	// L14857
          ap_int<33> v9365 = v9364;	// L14858
          ap_int<33> v9366 = v9365 + 1;	// L14859
          uint8_t v9367 = v9366;	// L14860
          iter_cnt10 = v9367;	// L14861
        }
      } else {
        int8_t v9368 = instr_cnt10;	// L14864
        ap_int<33> v9369 = v9368;	// L14865
        ap_int<33> v9370 = v9369 + 1;	// L14866
        uint8_t v9371 = v9370;	// L14867
        instr_cnt10 = v9371;	// L14868
      }
    }
    int32_t c110;	// L14871
    c110 = -1;	// L14872
    int32_t c210;	// L14873
    c210 = -1;	// L14874
    int32_t v9374 = grant10;	// L14875
    bool v9375 = v9374 == 1;	// L14876
    int32_t v9376 = s110;	// L14877
    bool v9377 = v9376 >= 12;	// L14878
    bool v9378 = v9375 & v9377;	// L14879
    if (v9378) {	// L14880
      int32_t v9379 = s110;	// L14881
      int32_t v9380 = v9379 & 3;	// L14882
      c110 = v9380;	// L14883
    }
    int32_t v9381 = grant10;	// L14885
    bool v9382 = v9381 == 1;	// L14886
    int32_t v9383 = s210;	// L14887
    bool v9384 = v9383 >= 12;	// L14888
    bool v9385 = v9382 & v9384;	// L14889
    if (v9385) {	// L14890
      int32_t v9386 = s210;	// L14891
      int32_t v9387 = v9386 & 3;	// L14892
      c210 = v9387;	// L14893
    }
    int32_t v9388 = c110;	// L14895
    bool v9389 = v9388 >= 0;	// L14896
    if (v9389) {	// L14897
      int32_t v9390 = c110;	// L14898
      int v9391 = v9390;	// L14899
      half v9392 = hold_v10[v9391][1];	// L14900
      hold_v10[v9391][0] = v9392;	// L14901
      int32_t v9393 = c110;	// L14902
      int v9394 = v9393;	// L14903
      uint8_t v9395 = hold_cnt10[v9394];	// L14904
      ap_int<33> v9396 = v9395;	// L14905
      ap_int<33> v9397 = v9396 - 1;	// L14906
      uint8_t v9398 = v9397;	// L14907
      hold_cnt10[v9394] = v9398;	// L14908
    }
    int32_t v9399 = c210;	// L14910
    bool v9400 = v9399 >= 0;	// L14911
    int32_t v9401 = c110;	// L14912
    bool v9402 = v9399 != v9401;	// L14913
    bool v9403 = v9400 & v9402;	// L14914
    if (v9403) {	// L14915
      int32_t v9404 = c210;	// L14916
      int v9405 = v9404;	// L14917
      half v9406 = hold_v10[v9405][1];	// L14918
      hold_v10[v9405][0] = v9406;	// L14919
      int32_t v9407 = c210;	// L14920
      int v9408 = v9407;	// L14921
      uint8_t v9409 = hold_cnt10[v9408];	// L14922
      ap_int<33> v9410 = v9409;	// L14923
      ap_int<33> v9411 = v9410 - 1;	// L14924
      uint8_t v9412 = v9411;	// L14925
      hold_cnt10[v9408] = v9412;	// L14926
    }
    int32_t v9413 = grant10;	// L14928
    bool v9414 = v9413 == 1;	// L14929
    int32_t v9415 = s110;	// L14930
    bool v9416 = v9415 < 8;	// L14931
    int32_t v9417 = dsmask10;	// L14932
    int32_t v9418 = v9417 >> v9415;	// L14933
    int32_t v9419 = v9418 & 1;	// L14934
    bool v9420 = v9419 == 1;	// L14935
    bool v9421 = v9414 & v9416;	// L14936
    bool v9422 = v9421 & v9420;	// L14937
    if (v9422) {	// L14938
      int32_t v9423 = s110;	// L14939
      int v9424 = v9423;	// L14940
      drf_full10[v9424] = 0;	// L14941
    }
    int32_t v9425 = grant10;	// L14943
    bool v9426 = v9425 == 1;	// L14944
    int32_t v9427 = s210;	// L14945
    bool v9428 = v9427 < 8;	// L14946
    int32_t v9429 = dsmask10;	// L14947
    int32_t v9430 = v9429 >> v9427;	// L14948
    int32_t v9431 = v9430 & 1;	// L14949
    bool v9432 = v9431 == 1;	// L14950
    bool v9433 = v9426 & v9428;	// L14951
    bool v9434 = v9433 & v9432;	// L14952
    if (v9434) {	// L14953
      int32_t v9435 = s210;	// L14954
      int v9436 = v9435;	// L14955
      drf_full10[v9436] = 0;	// L14956
    }
    half res10;
#pragma HLS dependence variable=res10 type=inter dependent=false	// L14958
    res10 = 0.000000;	// L14959
    int32_t v9438 = op10;	// L14960
    bool v9439 = v9438 == 0;	// L14961
    if (v9439) {	// L14962
      half v9440 = a10;	// L14963
      half v9441 = b10;	// L14964
      half v9442 = v9440 + v9441;	// L14965
      res10 = v9442;	// L14966
    } else {
      int32_t v9443 = op10;	// L14968
      bool v9444 = v9443 == 1;	// L14969
      if (v9444) {	// L14970
        half v9445 = a10;	// L14971
        half v9446 = b10;	// L14972
        half v9447 = v9445 - v9446;	// L14973
        res10 = v9447;	// L14974
      } else {
        int32_t v9448 = op10;	// L14976
        bool v9449 = v9448 == 2;	// L14977
        if (v9449) {	// L14978
          half v9450 = a10;	// L14979
          half v9451 = b10;	// L14980
          half v9452 = v9450 * v9451;	// L14981
          res10 = v9452;	// L14982
        } else {
          int32_t v9453 = op10;	// L14984
          bool v9454 = v9453 == 8;	// L14985
          if (v9454) {	// L14986
            half v9455 = a10;	// L14987
            half v9456 = b10;	// L14988
            bool v9457 = v9455 >= v9456;	// L14989
            if (v9457) {	// L14990
              res10 = 1.000000;	// L14991
            } else {
              res10 = -1.000000;	// L14993
            }
          } else {
            int32_t v9458 = op10;	// L14996
            bool v9459 = v9458 == 9;	// L14997
            if (v9459) {	// L14998
              half v9460 = a10;	// L14999
              half v9461 = b10;	// L15000
              bool v9462 = v9460 < v9461;	// L15001
              if (v9462) {	// L15002
                res10 = 1.000000;	// L15003
              } else {
                res10 = -1.000000;	// L15005
              }
            } else {
              half v9463 = a10;	// L15008
              res10 = v9463;	// L15009
            }
          }
        }
      }
    }
    int32_t v9464 = a_vld10;	// L15015
    int32_t res_vld10;	// L15016
    res_vld10 = v9464;	// L15017
    int32_t v9466 = op10;	// L15018
    bool v9467 = v9466 == 0;	// L15019
    bool v9468 = v9466 == 1;	// L15020
    bool v9469 = v9466 == 2;	// L15021
    bool v9470 = v9466 == 8;	// L15022
    bool v9471 = v9466 == 9;	// L15023
    bool v9472 = v9467 | v9468;	// L15024
    bool v9473 = v9472 | v9469;	// L15025
    bool v9474 = v9473 | v9470;	// L15026
    bool v9475 = v9474 | v9471;	// L15027
    if (v9475) {	// L15028
      int32_t v9476 = a_vld10;	// L15029
      int32_t v9477 = b_vld10;	// L15030
      int64_t v9478 = v9476;	// L15031
      int64_t v9479 = v9477;	// L15032
      int64_t v9480 = v9478 * v9479;	// L15033
      int32_t v9481 = v9480;	// L15034
      res_vld10 = v9481;	// L15035
    }
    int32_t v9482 = grant10;	// L15037
    bool v9483 = v9482 == 0;	// L15038
    if (v9483) {	// L15039
      res_vld10 = 0;	// L15040
    }
    int32_t is_rtr10;	// L15042
    is_rtr10 = 0;	// L15043
    int32_t v9485 = op10;	// L15044
    bool v9486 = v9485 >= 4;	// L15045
    ap_int<33> v9487 = v9485;	// L15046
    bool v9488 = v9487 <= 7;	// L15047
    bool v9489 = v9486 & v9488;	// L15048
    if (v9489) {	// L15049
      is_rtr10 = 1;	// L15050
    }
    l_S_k_6_k21: for (int k21 = 0; k21 < 4; k21++) {	// L15052
      uint8_t v9491 = sb_v10[(k21 + 1)];	// L15053
      sb_v10[k21] = v9491;	// L15054
      uint8_t v9492 = sb_dst10[(k21 + 1)];	// L15055
      sb_dst10[k21] = v9492;	// L15056
      uint8_t v9493 = sb_cmp10[(k21 + 1)];	// L15057
      sb_cmp10[k21] = v9493;	// L15058
      uint8_t v9494 = sb_rtr10[(k21 + 1)];	// L15059
      sb_rtr10[k21] = v9494;	// L15060
      uint8_t v9495 = sb_inj10[(k21 + 1)];	// L15061
      sb_inj10[k21] = v9495;	// L15062
      uint8_t v9496 = sb_dir10[(k21 + 1)];	// L15063
      sb_dir10[k21] = v9496;	// L15064
      uint8_t v9497 = sb_id10[(k21 + 1)];	// L15065
      sb_id10[k21] = v9497;	// L15066
      uint8_t v9498 = sb_rvld10[(k21 + 1)];	// L15067
      sb_rvld10[k21] = v9498;	// L15068
      uint8_t v9499 = sb_ix10[(k21 + 1)];	// L15069
      sb_ix10[k21] = v9499;	// L15070
    }
    sb_v10[4] = 0;	// L15072
    int32_t v9500 = grant10;	// L15073
    bool v9501 = v9500 == 1;	// L15074
    if (v9501) {	// L15075
      half v9502 = res10;	// L15076
      int8_t v9503 = resq_wr10;	// L15077
      int v9504 = v9503;	// L15078
      resq10[v9504] = v9502;	// L15079
      int32_t cq10;	// L15080
      cq10 = 0;	// L15081
      int32_t v9506 = op10;	// L15082
      bool v9507 = v9506 == 8;	// L15083
      if (v9507) {	// L15084
        half v9508 = a10;	// L15085
        half v9509 = b10;	// L15086
        bool v9510 = v9508 >= v9509;	// L15087
        if (v9510) {	// L15088
          cq10 = 1;	// L15089
        }
      }
      int32_t v9511 = op10;	// L15092
      bool v9512 = v9511 == 9;	// L15093
      if (v9512) {	// L15094
        half v9513 = a10;	// L15095
        half v9514 = b10;	// L15096
        bool v9515 = v9513 < v9514;	// L15097
        if (v9515) {	// L15098
          cq10 = 1;	// L15099
        }
      }
      int32_t v9516 = cq10;	// L15102
      uint8_t v9517 = v9516;	// L15103
      int8_t v9518 = resq_wr10;	// L15104
      int v9519 = v9518;	// L15105
      cmpq10[v9519] = v9517;	// L15106
      sb_v10[4] = 1;	// L15107
      int32_t v9520 = dst10;	// L15108
      uint8_t v9521 = v9520;	// L15109
      sb_dst10[4] = v9521;	// L15110
      int8_t v9522 = resq_wr10;	// L15111
      sb_ix10[4] = v9522;	// L15112
      sb_cmp10[4] = 0;	// L15113
      int32_t v9523 = op10;	// L15114
      bool v9524 = v9523 == 8;	// L15115
      bool v9525 = v9523 == 9;	// L15116
      bool v9526 = v9524 | v9525;	// L15117
      if (v9526) {	// L15118
        sb_cmp10[4] = 1;	// L15119
      }
      int32_t v9527 = is_rtr10;	// L15121
      int32_t rtrf10;	// L15122
      rtrf10 = v9527;	// L15123
      int32_t v9529 = is_cond10;	// L15124
      bool v9530 = v9529 == 1;	// L15125
      if (v9530) {	// L15126
        rtrf10 = 1;	// L15127
      }
      int32_t v9531 = rtrf10;	// L15129
      uint8_t v9532 = v9531;	// L15130
      sb_rtr10[4] = v9532;	// L15131
      int32_t v9533 = is_rtr10;	// L15132
      int32_t inj10;	// L15133
      inj10 = v9533;	// L15134
      int32_t v9535 = is_cond10;	// L15135
      bool v9536 = v9535 == 1;	// L15136
      int8_t v9537 = condition_reg10;	// L15137
      int32_t v9538 = v9537;	// L15138
      bool v9539 = v9538 == 1;	// L15139
      bool v9540 = v9536 & v9539;	// L15140
      if (v9540) {	// L15141
        inj10 = 1;	// L15142
      }
      int32_t v9541 = inj10;	// L15144
      uint8_t v9542 = v9541;	// L15145
      sb_inj10[4] = v9542;	// L15146
      int32_t v9543 = op10;	// L15147
      int32_t v9544 = v9543 & 3;	// L15148
      uint8_t v9545 = v9544;	// L15149
      sb_dir10[4] = v9545;	// L15150
      int32_t v9546 = s210;	// L15151
      uint8_t v9547 = v9546;	// L15152
      sb_id10[4] = v9547;	// L15153
      int32_t v9548 = res_vld10;	// L15154
      uint8_t v9549 = v9548;	// L15155
      sb_rvld10[4] = v9549;	// L15156
      int8_t v9550 = resq_wr10;	// L15157
      ap_int<33> v9551 = v9550;	// L15158
      ap_int<33> v9552 = v9551 + 1;	// L15159
      ap_int<33> v9553 = v9552 & 7;	// L15160
      uint8_t v9554 = v9553;	// L15161
      resq_wr10 = v9554;	// L15162
    }
    ap_int<17> v9555 = tx_n10;	// L15164
    txn_r10 = v9555;	// L15165
    ap_int<17> v9556 = tx_s10;	// L15166
    txs_r10 = v9556;	// L15167
    ap_int<17> v9557 = tx_w10;	// L15168
    txw_r10 = v9557;	// L15169
    ap_int<17> v9558 = tx_e10;	// L15170
    txe_r10 = v9558;	// L15171
    int32_t v9559 = crv_vld10;	// L15172
    bool v9560 = v9559 == 1;	// L15173
    if (v9560) {	// L15174
      int32_t v9561 = crv_mode10;	// L15175
      bool v9562 = v9561 == 1;	// L15176
      if (v9562) {	// L15177
        int32_t v9563 = crv_addr10;	// L15178
        int32_t v9564 = v9563 >> 3;	// L15179
        int32_t v9565 = v9564 & 1;	// L15180
        bool v9566 = v9565 == 1;	// L15181
        if (v9566) {	// L15182
          int32_t v9567 = crv_raw10;	// L15183
          int32_t v9568 = crv_addr10;	// L15184
          int32_t v9569 = v9568 & 7;	// L15185
          int v9570 = v9569;	// L15186
          irf10[v9570] = v9567;	// L15187
        } else {
          int32_t v9571 = crv_addr10;	// L15189
          bool v9572 = v9571 == 0;	// L15190
          if (v9572) {	// L15191
            int32_t v9573 = crv_raw10;	// L15192
            int32_t v9574 = v9573 & 255;	// L15193
            dsmask10 = v9574;	// L15194
            int32_t v9575 = crv_raw10;	// L15195
            int32_t v9576 = v9575 >> 8;	// L15196
            int32_t v9577 = v9576 & 7;	// L15197
            cfg_isz10 = v9577;	// L15198
            int32_t v9578 = crv_raw10;	// L15199
            int32_t v9579 = v9578 >> 15;	// L15200
            int32_t v9580 = v9579 & 1;	// L15201
            bool v9581 = v9580 == 1;	// L15202
            if (v9581) {	// L15203
              fetch_en10 = 1;	// L15204
              instr_cnt10 = 0;	// L15205
              iter_cnt10 = 0;	// L15206
            }
          } else {
            int32_t v9582 = crv_addr10;	// L15209
            bool v9583 = v9582 == 1;	// L15210
            if (v9583) {	// L15211
              int32_t v9584 = crv_raw10;	// L15212
              int32_t v9585 = v9584 & 255;	// L15213
              cfg_itsz10 = v9585;	// L15214
            }
          }
        }
      } else {
        int32_t v9586 = crv_addr10;	// L15219
        bool v9587 = v9586 < 8;	// L15220
        int32_t v9588 = dsmask10;	// L15221
        int32_t v9589 = v9588 >> v9586;	// L15222
        int32_t v9590 = v9589 & 1;	// L15223
        bool v9591 = v9590 == 1;	// L15224
        bool v9592 = v9587 & v9591;	// L15225
        if (v9592) {	// L15226
          int32_t v9593 = crv_addr10;	// L15227
          int v9594 = v9593;	// L15228
          int32_t v9595 = drf_full10[v9594];	// L15229
          bool v9596 = v9595 == 0;	// L15230
          if (v9596) {	// L15231
            half v9597 = crv_data10;	// L15232
            int32_t v9598 = crv_addr10;	// L15233
            int v9599 = v9598;	// L15234
            drf10[v9599] = v9597;	// L15235
            int32_t v9600 = crv_addr10;	// L15236
            int v9601 = v9600;	// L15237
            drf_full10[v9601] = 1;	// L15238
          }
        } else {
          half v9602 = crv_data10;	// L15241
          int32_t v9603 = crv_addr10;	// L15242
          int v9604 = v9603;	// L15243
          drf10[v9604] = v9602;	// L15244
        }
      }
    }
    ap_int<17> v9605 = txe_r10;	// L15248
    bool v9606;
    ap_int<17> v9606_tmp = v9605;
    v9606 = v9606_tmp[0];	// L15249
    int32_t v9607 = v9606;	// L15250
    bool v9608 = v9607 == 1;	// L15251
    if (v9608) {	// L15252
      ap_int<17> v9609 = txe_r10;	// L15253
      v8762.write(v9609);	// L15254
    }
    ap_int<17> v9610 = txw_r10;	// L15256
    bool v9611;
    ap_int<17> v9611_tmp = v9610;
    v9611 = v9611_tmp[0];	// L15257
    int32_t v9612 = v9611;	// L15258
    bool v9613 = v9612 == 1;	// L15259
    if (v9613) {	// L15260
      ap_int<17> v9614 = txw_r10;	// L15261
      v8763.write(v9614);	// L15262
    }
    ap_int<17> v9615 = txs_r10;	// L15264
    bool v9616;
    ap_int<17> v9616_tmp = v9615;
    v9616 = v9616_tmp[0];	// L15265
    int32_t v9617 = v9616;	// L15266
    bool v9618 = v9617 == 1;	// L15267
    if (v9618) {	// L15268
      ap_int<17> v9619 = txs_r10;	// L15269
      v8764.write(v9619);	// L15270
    }
    ap_int<17> v9620 = txn_r10;	// L15272
    bool v9621;
    ap_int<17> v9621_tmp = v9620;
    v9621 = v9621_tmp[0];	// L15273
    int32_t v9622 = v9621;	// L15274
    bool v9623 = v9622 == 1;	// L15275
    if (v9623) {	// L15276
      ap_int<17> v9624 = txn_r10;	// L15277
      v8765.write(v9624);	// L15278
    }
  }
}

void node_2_3(
  hls::stream< ap_uint<26> >& v9625,
  hls::stream< ap_uint<26> >& v9626,
  hls::stream< ap_uint<26> >& v9627,
  hls::stream< ap_uint<26> >& v9628,
  hls::stream< ap_uint<26> >& v9629,
  hls::stream< ap_uint<26> >& v9630,
  hls::stream< ap_uint<26> >& v9631,
  hls::stream< ap_uint<26> >& v9632,
  hls::stream< ap_uint<17> >& v9633,
  hls::stream< ap_uint<17> >& v9634,
  hls::stream< ap_uint<17> >& v9635,
  hls::stream< ap_uint<17> >& v9636,
  hls::stream< ap_uint<17> >& v9637,
  hls::stream< ap_uint<17> >& v9638,
  hls::stream< ap_uint<17> >& v9639,
  hls::stream< ap_uint<17> >& v9640
) {	// L15283
  int32_t irf11[8];	// L15316
  #pragma HLS array_partition variable=irf11 complete dim=1

  for (int v9642 = 0; v9642 < 8; v9642++) {	// L15317
    irf11[v9642] = 0;	// L15317
  }
  half drf11[8];	// L15318
  #pragma HLS array_partition variable=drf11 complete dim=1

  for (int v9644 = 0; v9644 < 8; v9644++) {	// L15319
    drf11[v9644] = 0.000000;	// L15319
  }
  int32_t drf_full11[8];	// L15320
  #pragma HLS array_partition variable=drf_full11 complete dim=1

  for (int v9646 = 0; v9646 < 8; v9646++) {	// L15321
    drf_full11[v9646] = 0;	// L15321
  }
  int32_t dsmask11;	// L15322
  dsmask11 = 0;	// L15323
  int32_t crv_vld11;	// L15324
  crv_vld11 = 0;	// L15325
  half crv_data11;	// L15326
  crv_data11 = 0.000000;	// L15327
  int32_t crv_addr11;	// L15328
  crv_addr11 = 0;	// L15329
  int32_t crv_mode11;	// L15330
  crv_mode11 = 0;	// L15331
  int32_t crv_raw11;	// L15332
  crv_raw11 = 0;	// L15333
  int32_t csd_vld11;	// L15334
  csd_vld11 = 0;	// L15335
  ap_uint<26> csd_pkt11;	// L15336
  csd_pkt11 = 0;	// L15337
  int32_t csd_dir11;	// L15338
  csd_dir11 = 0;	// L15339
  int32_t row_id11;	// L15340
  row_id11 = 2;	// L15341
  int32_t col_id11;	// L15342
  col_id11 = 3;	// L15343
  ap_uint<17> txn_r11;	// L15344
  txn_r11 = 0;	// L15345
  ap_uint<17> txs_r11;	// L15346
  txs_r11 = 0;	// L15347
  ap_uint<17> txw_r11;	// L15348
  txw_r11 = 0;	// L15349
  ap_uint<17> txe_r11;	// L15350
  txe_r11 = 0;	// L15351
  half hold_v11[4][2];	// L15352
  #pragma HLS array_partition variable=hold_v11 complete dim=1
  #pragma HLS array_partition variable=hold_v11 complete dim=2

  for (int v9663 = 0; v9663 < 4; v9663++) {	// L15353
    for (int v9664 = 0; v9664 < 2; v9664++) {	// L15353
      hold_v11[v9663][v9664] = 0.000000;	// L15353
    }
  }
  uint8_t hold_cnt11[4];	// L15354
  #pragma HLS array_partition variable=hold_cnt11 complete dim=1

  for (int v9666 = 0; v9666 < 4; v9666++) {	// L15355
    hold_cnt11[v9666] = 0;	// L15355
  }
  int32_t crv_ever11;	// L15356
  crv_ever11 = 0;	// L15357
  int32_t fe_ever11;	// L15358
  fe_ever11 = 0;	// L15359
  ap_uint<26> rbuf11[4][2];	// L15360
  #pragma HLS array_partition variable=rbuf11 complete dim=1
  #pragma HLS array_partition variable=rbuf11 complete dim=2

  for (int v9670 = 0; v9670 < 4; v9670++) {	// L15361
    for (int v9671 = 0; v9671 < 2; v9671++) {	// L15361
      rbuf11[v9670][v9671] = 0;	// L15361
    }
  }
  uint8_t rbcnt11[4];	// L15362
  #pragma HLS array_partition variable=rbcnt11 complete dim=1

  for (int v9673 = 0; v9673 < 4; v9673++) {	// L15363
    rbcnt11[v9673] = 0;	// L15363
  }
  int32_t cfg_isz11;	// L15364
  cfg_isz11 = 0;	// L15365
  int32_t cfg_itsz11;	// L15366
  cfg_itsz11 = 0;	// L15367
  uint8_t fetch_en11;	// L15368
  fetch_en11 = 0;	// L15369
  uint8_t instr_cnt11;	// L15370
  instr_cnt11 = 0;	// L15371
  uint8_t iter_cnt11;	// L15372
  iter_cnt11 = 0;	// L15373
  uint8_t condition_reg11;	// L15374
  condition_reg11 = 0;	// L15375
  uint8_t sb_v11[5];	// L15376
  #pragma HLS array_partition variable=sb_v11 complete dim=1

  for (int v9681 = 0; v9681 < 5; v9681++) {	// L15377
    sb_v11[v9681] = 0;	// L15377
  }
  uint8_t sb_dst11[5];	// L15378
  #pragma HLS array_partition variable=sb_dst11 complete dim=1

  for (int v9683 = 0; v9683 < 5; v9683++) {	// L15379
    sb_dst11[v9683] = 0;	// L15379
  }
  uint8_t sb_cmp11[5];	// L15380
  #pragma HLS array_partition variable=sb_cmp11 complete dim=1

  for (int v9685 = 0; v9685 < 5; v9685++) {	// L15381
    sb_cmp11[v9685] = 0;	// L15381
  }
  uint8_t sb_rtr11[5];	// L15382
  #pragma HLS array_partition variable=sb_rtr11 complete dim=1

  for (int v9687 = 0; v9687 < 5; v9687++) {	// L15383
    sb_rtr11[v9687] = 0;	// L15383
  }
  uint8_t sb_inj11[5];	// L15384
  #pragma HLS array_partition variable=sb_inj11 complete dim=1

  for (int v9689 = 0; v9689 < 5; v9689++) {	// L15385
    sb_inj11[v9689] = 0;	// L15385
  }
  uint8_t sb_dir11[5];	// L15386
  #pragma HLS array_partition variable=sb_dir11 complete dim=1

  for (int v9691 = 0; v9691 < 5; v9691++) {	// L15387
    sb_dir11[v9691] = 0;	// L15387
  }
  uint8_t sb_id11[5];	// L15388
  #pragma HLS array_partition variable=sb_id11 complete dim=1

  for (int v9693 = 0; v9693 < 5; v9693++) {	// L15389
    sb_id11[v9693] = 0;	// L15389
  }
  uint8_t sb_rvld11[5];	// L15390
  #pragma HLS array_partition variable=sb_rvld11 complete dim=1

  for (int v9695 = 0; v9695 < 5; v9695++) {	// L15391
    sb_rvld11[v9695] = 0;	// L15391
  }
  uint8_t sb_ix11[5];	// L15392
  #pragma HLS array_partition variable=sb_ix11 complete dim=1

  for (int v9697 = 0; v9697 < 5; v9697++) {	// L15393
    sb_ix11[v9697] = 0;	// L15393
  }
  half resq11[8];	// L15394
  #pragma HLS array_partition variable=resq11 complete dim=1
#pragma HLS dependence variable=resq11 type=inter dependent=false

  for (int v9699 = 0; v9699 < 8; v9699++) {	// L15395
    resq11[v9699] = 0.000000;	// L15395
  }
  uint8_t cmpq11[8];	// L15396
  #pragma HLS array_partition variable=cmpq11 complete dim=1
#pragma HLS dependence variable=cmpq11 type=inter dependent=false

  for (int v9701 = 0; v9701 < 8; v9701++) {	// L15397
    cmpq11[v9701] = 0;	// L15397
  }
  uint8_t resq_wr11;	// L15398
  resq_wr11 = 0;	// L15399
  l_S_t_0_t11: for (int t11 = 0; t11 < 374; t11++) {	// L15400
  #pragma HLS pipeline II=1
    ap_uint<26> p_w11;	// L15401
    p_w11 = 0;	// L15402
    ap_uint<26> p_e11;	// L15403
    p_e11 = 0;	// L15404
    ap_uint<26> p_n11;	// L15405
    p_n11 = 0;	// L15406
    ap_uint<26> p_s11;	// L15407
    p_s11 = 0;	// L15408
    uint8_t v9708 = rbcnt11[0];	// L15409
    int32_t v9709 = v9708;	// L15410
    bool v9710 = v9709 < 2;	// L15411
    if (v9710) {	// L15412
      ap_uint<26> v9711;
      bool v9712 = v9625.read_nb(v9711);
	// L15413
      ap_uint<26> gw11;	// L15414
      gw11 = v9711;	// L15415
      bool okw11;	// L15416
      okw11 = v9712;	// L15417
      bool v9715 = okw11;	// L15418
      if (v9715) {	// L15419
        ap_int<26> v9716 = gw11;	// L15420
        p_w11 = v9716;	// L15421
      }
    }
    uint8_t v9717 = rbcnt11[1];	// L15424
    int32_t v9718 = v9717;	// L15425
    bool v9719 = v9718 < 2;	// L15426
    if (v9719) {	// L15427
      ap_uint<26> v9720;
      bool v9721 = v9626.read_nb(v9720);
	// L15428
      ap_uint<26> ge11;	// L15429
      ge11 = v9720;	// L15430
      bool oke11;	// L15431
      oke11 = v9721;	// L15432
      bool v9724 = oke11;	// L15433
      if (v9724) {	// L15434
        ap_int<26> v9725 = ge11;	// L15435
        p_e11 = v9725;	// L15436
      }
    }
    uint8_t v9726 = rbcnt11[2];	// L15439
    int32_t v9727 = v9726;	// L15440
    bool v9728 = v9727 < 2;	// L15441
    if (v9728) {	// L15442
      ap_uint<26> v9729;
      bool v9730 = v9627.read_nb(v9729);
	// L15443
      ap_uint<26> gn11;	// L15444
      gn11 = v9729;	// L15445
      bool okn11;	// L15446
      okn11 = v9730;	// L15447
      bool v9733 = okn11;	// L15448
      if (v9733) {	// L15449
        ap_int<26> v9734 = gn11;	// L15450
        p_n11 = v9734;	// L15451
      }
    }
    uint8_t v9735 = rbcnt11[3];	// L15454
    int32_t v9736 = v9735;	// L15455
    bool v9737 = v9736 < 2;	// L15456
    if (v9737) {	// L15457
      ap_uint<26> v9738;
      bool v9739 = v9628.read_nb(v9738);
	// L15458
      ap_uint<26> gs11;	// L15459
      gs11 = v9738;	// L15460
      bool oks11;	// L15461
      oks11 = v9739;	// L15462
      bool v9742 = oks11;	// L15463
      if (v9742) {	// L15464
        ap_int<26> v9743 = gs11;	// L15465
        p_s11 = v9743;	// L15466
      }
    }
    ap_uint<26> fin11[4];	// L15469
    for (int v9745 = 0; v9745 < 4; v9745++) {	// L15470
      fin11[v9745] = 0;	// L15470
    }
    ap_int<26> v9746 = p_w11;	// L15471
    fin11[0] = v9746;	// L15472
    ap_int<26> v9747 = p_e11;	// L15473
    fin11[1] = v9747;	// L15474
    ap_int<26> v9748 = p_n11;	// L15475
    fin11[2] = v9748;	// L15476
    ap_int<26> v9749 = p_s11;	// L15477
    fin11[3] = v9749;	// L15478
    l_S_d_0_d44: for (int d44 = 0; d44 < 4; d44++) {	// L15479
      ap_uint<26> v9751 = fin11[d44];	// L15480
      bool v9752;
      ap_int<26> v9752_tmp = v9751;
      v9752 = v9752_tmp[25];	// L15481
      int32_t v9753 = v9752;	// L15482
      bool v9754 = v9753 == 1;	// L15483
      uint8_t v9755 = rbcnt11[d44];	// L15484
      int32_t v9756 = v9755;	// L15485
      bool v9757 = v9756 < 2;	// L15486
      bool v9758 = v9754 & v9757;	// L15487
      if (v9758) {	// L15488
        ap_uint<26> v9759 = fin11[d44];	// L15489
        uint8_t v9760 = rbcnt11[d44];	// L15490
        int v9761 = v9760;	// L15491
        rbuf11[d44][v9761] = v9759;	// L15492
        uint8_t v9762 = rbcnt11[d44];	// L15493
        ap_int<33> v9763 = v9762;	// L15494
        ap_int<33> v9764 = v9763 + 1;	// L15495
        uint8_t v9765 = v9764;	// L15496
        rbcnt11[d44] = v9765;	// L15497
      }
    }
    ap_uint<26> hd11[4];	// L15500
    for (int v9767 = 0; v9767 < 4; v9767++) {	// L15501
      hd11[v9767] = 0;	// L15501
    }
    int32_t hvld11[4];	// L15502
    for (int v9769 = 0; v9769 < 4; v9769++) {	// L15503
      hvld11[v9769] = 0;	// L15503
    }
    int32_t hit11[4];	// L15504
    for (int v9771 = 0; v9771 < 4; v9771++) {	// L15505
      hit11[v9771] = 0;	// L15505
    }
    int32_t axis11[4];	// L15506
    for (int v9773 = 0; v9773 < 4; v9773++) {	// L15507
      axis11[v9773] = 0;	// L15507
    }
    int32_t v9774 = col_id11;	// L15508
    axis11[0] = v9774;	// L15509
    int32_t v9775 = col_id11;	// L15510
    axis11[1] = v9775;	// L15511
    int32_t v9776 = row_id11;	// L15512
    axis11[2] = v9776;	// L15513
    int32_t v9777 = row_id11;	// L15514
    axis11[3] = v9777;	// L15515
    l_S_d_1_d45: for (int d45 = 0; d45 < 4; d45++) {	// L15516
      uint8_t v9779 = rbcnt11[d45];	// L15517
      int32_t v9780 = v9779;	// L15518
      bool v9781 = v9780 > 0;	// L15519
      if (v9781) {	// L15520
        ap_uint<26> v9782 = rbuf11[d45][0];	// L15521
        hd11[d45] = v9782;	// L15522
        hvld11[d45] = 1;	// L15523
        ap_uint<26> v9783 = hd11[d45];	// L15524
        ap_int<4> v9784;
        ap_int<26> v9784_tmp = v9783;
        v9784 = v9784_tmp(24, 21);	// L15525
        int32_t v9785 = axis11[d45];	// L15526
        int32_t v9786 = v9784;	// L15527
        bool v9787 = v9786 == v9785;	// L15528
        if (v9787) {	// L15529
          hit11[d45] = 1;	// L15530
        }
      }
    }
    ap_uint<26> o_crv11;	// L15534
    o_crv11 = 0;	// L15535
    int32_t crv_in11;	// L15536
    crv_in11 = -1;	// L15537
    int32_t v9790 = hit11[3];	// L15538
    bool v9791 = v9790 == 1;	// L15539
    if (v9791) {	// L15540
      ap_uint<26> v9792 = hd11[3];	// L15541
      o_crv11 = v9792;	// L15542
      crv_in11 = 3;	// L15543
    } else {
      int32_t v9793 = hit11[2];	// L15545
      bool v9794 = v9793 == 1;	// L15546
      if (v9794) {	// L15547
        ap_uint<26> v9795 = hd11[2];	// L15548
        o_crv11 = v9795;	// L15549
        crv_in11 = 2;	// L15550
      } else {
        int32_t v9796 = hit11[1];	// L15552
        bool v9797 = v9796 == 1;	// L15553
        if (v9797) {	// L15554
          ap_uint<26> v9798 = hd11[1];	// L15555
          o_crv11 = v9798;	// L15556
          crv_in11 = 1;	// L15557
        } else {
          int32_t v9799 = hit11[0];	// L15559
          bool v9800 = v9799 == 1;	// L15560
          if (v9800) {	// L15561
            ap_uint<26> v9801 = hd11[0];	// L15562
            o_crv11 = v9801;	// L15563
            crv_in11 = 0;	// L15564
          }
        }
      }
    }
    int32_t pop11[4];	// L15569
    for (int v9803 = 0; v9803 < 4; v9803++) {	// L15570
      pop11[v9803] = 0;	// L15570
    }
    int32_t inj_done11;	// L15571
    inj_done11 = 0;	// L15572
    int32_t idir11;	// L15573
    idir11 = -1;	// L15574
    ap_int<26> v9806 = csd_pkt11;	// L15575
    bool v9807;
    ap_int<26> v9807_tmp = v9806;
    v9807 = v9807_tmp[25];	// L15576
    int32_t v9808 = v9807;	// L15577
    bool v9809 = v9808 == 1;	// L15578
    if (v9809) {	// L15579
      int32_t v9810 = csd_dir11;	// L15580
      ap_int<33> v9811 = v9810;	// L15581
      ap_int<33> v9812 = 3 - v9811;	// L15582
      int32_t v9813 = v9812;	// L15583
      idir11 = v9813;	// L15584
    }
    int32_t v9814 = idir11;	// L15586
    bool v9815 = v9814 == 0;	// L15587
    if (v9815) {	// L15588
      ap_int<26> v9816 = csd_pkt11;	// L15589
      bool v9817 = v9629.write_nb(v9816);
	// L15590
      if (v9817) {	// L15591
        inj_done11 = 1;	// L15592
      }
    } else {
      int32_t v9818 = hvld11[0];	// L15595
      bool v9819 = v9818 == 1;	// L15596
      int32_t v9820 = hit11[0];	// L15597
      bool v9821 = v9820 == 0;	// L15598
      bool v9822 = v9819 & v9821;	// L15599
      if (v9822) {	// L15600
        ap_uint<26> v9823 = hd11[0];	// L15601
        bool v9824 = v9629.write_nb(v9823);
	// L15602
        if (v9824) {	// L15603
          pop11[0] = 1;	// L15604
        }
      }
    }
    int32_t v9825 = idir11;	// L15608
    bool v9826 = v9825 == 1;	// L15609
    if (v9826) {	// L15610
      ap_int<26> v9827 = csd_pkt11;	// L15611
      bool v9828 = v9630.write_nb(v9827);
	// L15612
      if (v9828) {	// L15613
        inj_done11 = 1;	// L15614
      }
    } else {
      int32_t v9829 = hvld11[1];	// L15617
      bool v9830 = v9829 == 1;	// L15618
      int32_t v9831 = hit11[1];	// L15619
      bool v9832 = v9831 == 0;	// L15620
      bool v9833 = v9830 & v9832;	// L15621
      if (v9833) {	// L15622
        ap_uint<26> v9834 = hd11[1];	// L15623
        bool v9835 = v9630.write_nb(v9834);
	// L15624
        if (v9835) {	// L15625
          pop11[1] = 1;	// L15626
        }
      }
    }
    int32_t v9836 = idir11;	// L15630
    bool v9837 = v9836 == 2;	// L15631
    if (v9837) {	// L15632
      ap_int<26> v9838 = csd_pkt11;	// L15633
      bool v9839 = v9631.write_nb(v9838);
	// L15634
      if (v9839) {	// L15635
        inj_done11 = 1;	// L15636
      }
    } else {
      int32_t v9840 = hvld11[2];	// L15639
      bool v9841 = v9840 == 1;	// L15640
      int32_t v9842 = hit11[2];	// L15641
      bool v9843 = v9842 == 0;	// L15642
      bool v9844 = v9841 & v9843;	// L15643
      if (v9844) {	// L15644
        ap_uint<26> v9845 = hd11[2];	// L15645
        bool v9846 = v9631.write_nb(v9845);
	// L15646
        if (v9846) {	// L15647
          pop11[2] = 1;	// L15648
        }
      }
    }
    int32_t v9847 = idir11;	// L15652
    bool v9848 = v9847 == 3;	// L15653
    if (v9848) {	// L15654
      ap_int<26> v9849 = csd_pkt11;	// L15655
      bool v9850 = v9632.write_nb(v9849);
	// L15656
      if (v9850) {	// L15657
        inj_done11 = 1;	// L15658
      }
    } else {
      int32_t v9851 = hvld11[3];	// L15661
      bool v9852 = v9851 == 1;	// L15662
      int32_t v9853 = hit11[3];	// L15663
      bool v9854 = v9853 == 0;	// L15664
      bool v9855 = v9852 & v9854;	// L15665
      if (v9855) {	// L15666
        ap_uint<26> v9856 = hd11[3];	// L15667
        bool v9857 = v9632.write_nb(v9856);
	// L15668
        if (v9857) {	// L15669
          pop11[3] = 1;	// L15670
        }
      }
    }
    int32_t v9858 = crv_in11;	// L15674
    bool v9859 = v9858 >= 0;	// L15675
    if (v9859) {	// L15676
      int32_t v9860 = crv_in11;	// L15677
      int v9861 = v9860;	// L15678
      pop11[v9861] = 1;	// L15679
    }
    l_S_d_2_d46: for (int d46 = 0; d46 < 4; d46++) {	// L15681
      int32_t v9863 = pop11[d46];	// L15682
      bool v9864 = v9863 == 1;	// L15683
      if (v9864) {	// L15684
        l_S_sft_2_sft11: for (int sft11 = 0; sft11 < 1; sft11++) {	// L15685
          ap_uint<26> v9866 = rbuf11[d46][(sft11 + 1)];	// L15686
          rbuf11[d46][sft11] = v9866;	// L15687
        }
        uint8_t v9867 = rbcnt11[d46];	// L15689
        ap_int<33> v9868 = v9867;	// L15690
        ap_int<33> v9869 = v9868 - 1;	// L15691
        uint8_t v9870 = v9869;	// L15692
        rbcnt11[d46] = v9870;	// L15693
      }
    }
    int32_t v9871 = inj_done11;	// L15696
    bool v9872 = v9871 == 1;	// L15697
    if (v9872) {	// L15698
      csd_pkt11 = 0;	// L15699
    }
    ap_int<26> v9873 = o_crv11;	// L15701
    bool v9874;
    ap_int<26> v9874_tmp = v9873;
    v9874 = v9874_tmp[25];	// L15702
    int32_t v9875 = v9874;	// L15703
    crv_vld11 = v9875;	// L15704
    int32_t v9876 = crv_vld11;	// L15705
    bool v9877 = v9876 == 1;	// L15706
    if (v9877) {	// L15707
      crv_ever11 = 1;	// L15708
    }
    ap_int<26> v9878 = o_crv11;	// L15710
    int16_t v9879;
    ap_int<26> v9879_tmp = v9878;
    v9879 = v9879_tmp(15, 0);	// L15711
    half v9880;
    union { uint16_t from; half to;} _converter_v9879_to_v9880 = {};
    _converter_v9879_to_v9880.from = v9879;
    v9880 = _converter_v9879_to_v9880.to;	// L15712
    crv_data11 = v9880;	// L15713
    ap_int<26> v9881 = o_crv11;	// L15714
    ap_int<4> v9882;
    ap_int<26> v9882_tmp = v9881;
    v9882 = v9882_tmp(19, 16);	// L15715
    int32_t v9883 = v9882;	// L15716
    crv_addr11 = v9883;	// L15717
    ap_int<26> v9884 = o_crv11;	// L15718
    bool v9885;
    ap_int<26> v9885_tmp = v9884;
    v9885 = v9885_tmp[20];	// L15719
    int32_t v9886 = v9885;	// L15720
    crv_mode11 = v9886;	// L15721
    ap_int<26> v9887 = o_crv11;	// L15722
    int16_t v9888;
    ap_int<26> v9888_tmp = v9887;
    v9888 = v9888_tmp(15, 0);	// L15723
    int32_t v9889 = v9888;	// L15724
    crv_raw11 = v9889;	// L15725
    half rxv11[4];	// L15726
    for (int v9891 = 0; v9891 < 4; v9891++) {	// L15727
      rxv11[v9891] = 0.000000;	// L15727
    }
    int32_t rxvld11[4];	// L15728
    for (int v9893 = 0; v9893 < 4; v9893++) {	// L15729
      rxvld11[v9893] = 0;	// L15729
    }
    uint8_t v9894 = hold_cnt11[0];	// L15730
    int32_t v9895 = v9894;	// L15731
    bool v9896 = v9895 < 2;	// L15732
    if (v9896) {	// L15733
      ap_uint<17> v9897;
      bool v9898 = v9633.read_nb(v9897);
	// L15734
      ap_uint<17> sgn11;	// L15735
      sgn11 = v9897;	// L15736
      bool sqn11;	// L15737
      sqn11 = v9898;	// L15738
      bool v9901 = sqn11;	// L15739
      int32_t v9902 = v9901;	// L15740
      bool v9903 = v9902 == 1;	// L15741
      if (v9903) {	// L15742
        ap_int<17> v9904 = sgn11;	// L15743
        int16_t v9905;
        ap_int<17> v9905_tmp = v9904;
        v9905 = v9905_tmp(16, 1);	// L15744
        half v9906;
        union { uint16_t from; half to;} _converter_v9905_to_v9906 = {};
        _converter_v9905_to_v9906.from = v9905;
        v9906 = _converter_v9905_to_v9906.to;	// L15745
        rxv11[0] = v9906;	// L15746
        rxvld11[0] = 1;	// L15747
      }
    }
    uint8_t v9907 = hold_cnt11[1];	// L15750
    int32_t v9908 = v9907;	// L15751
    bool v9909 = v9908 < 2;	// L15752
    if (v9909) {	// L15753
      ap_uint<17> v9910;
      bool v9911 = v9634.read_nb(v9910);
	// L15754
      ap_uint<17> sgs11;	// L15755
      sgs11 = v9910;	// L15756
      bool sqs11;	// L15757
      sqs11 = v9911;	// L15758
      bool v9914 = sqs11;	// L15759
      int32_t v9915 = v9914;	// L15760
      bool v9916 = v9915 == 1;	// L15761
      if (v9916) {	// L15762
        ap_int<17> v9917 = sgs11;	// L15763
        int16_t v9918;
        ap_int<17> v9918_tmp = v9917;
        v9918 = v9918_tmp(16, 1);	// L15764
        half v9919;
        union { uint16_t from; half to;} _converter_v9918_to_v9919 = {};
        _converter_v9918_to_v9919.from = v9918;
        v9919 = _converter_v9918_to_v9919.to;	// L15765
        rxv11[1] = v9919;	// L15766
        rxvld11[1] = 1;	// L15767
      }
    }
    uint8_t v9920 = hold_cnt11[2];	// L15770
    int32_t v9921 = v9920;	// L15771
    bool v9922 = v9921 < 2;	// L15772
    if (v9922) {	// L15773
      ap_uint<17> v9923;
      bool v9924 = v9635.read_nb(v9923);
	// L15774
      ap_uint<17> sgw11;	// L15775
      sgw11 = v9923;	// L15776
      bool sqw11;	// L15777
      sqw11 = v9924;	// L15778
      bool v9927 = sqw11;	// L15779
      int32_t v9928 = v9927;	// L15780
      bool v9929 = v9928 == 1;	// L15781
      if (v9929) {	// L15782
        ap_int<17> v9930 = sgw11;	// L15783
        int16_t v9931;
        ap_int<17> v9931_tmp = v9930;
        v9931 = v9931_tmp(16, 1);	// L15784
        half v9932;
        union { uint16_t from; half to;} _converter_v9931_to_v9932 = {};
        _converter_v9931_to_v9932.from = v9931;
        v9932 = _converter_v9931_to_v9932.to;	// L15785
        rxv11[2] = v9932;	// L15786
        rxvld11[2] = 1;	// L15787
      }
    }
    uint8_t v9933 = hold_cnt11[3];	// L15790
    int32_t v9934 = v9933;	// L15791
    bool v9935 = v9934 < 2;	// L15792
    if (v9935) {	// L15793
      ap_uint<17> v9936;
      bool v9937 = v9636.read_nb(v9936);
	// L15794
      ap_uint<17> sge11;	// L15795
      sge11 = v9936;	// L15796
      bool sqe11;	// L15797
      sqe11 = v9937;	// L15798
      bool v9940 = sqe11;	// L15799
      int32_t v9941 = v9940;	// L15800
      bool v9942 = v9941 == 1;	// L15801
      if (v9942) {	// L15802
        ap_int<17> v9943 = sge11;	// L15803
        int16_t v9944;
        ap_int<17> v9944_tmp = v9943;
        v9944 = v9944_tmp(16, 1);	// L15804
        half v9945;
        union { uint16_t from; half to;} _converter_v9944_to_v9945 = {};
        _converter_v9944_to_v9945.from = v9944;
        v9945 = _converter_v9944_to_v9945.to;	// L15805
        rxv11[3] = v9945;	// L15806
        rxvld11[3] = 1;	// L15807
      }
    }
    l_S_d_4_d47: for (int d47 = 0; d47 < 4; d47++) {	// L15810
      int32_t v9947 = rxvld11[d47];	// L15811
      bool v9948 = v9947 == 1;	// L15812
      if (v9948) {	// L15813
        half v9949 = rxv11[d47];	// L15814
        uint8_t v9950 = hold_cnt11[d47];	// L15815
        int v9951 = v9950;	// L15816
        hold_v11[d47][v9951] = v9949;	// L15817
        uint8_t v9952 = hold_cnt11[d47];	// L15818
        ap_int<33> v9953 = v9952;	// L15819
        ap_int<33> v9954 = v9953 + 1;	// L15820
        uint8_t v9955 = v9954;	// L15821
        hold_cnt11[d47] = v9955;	// L15822
      }
    }
    ap_uint<17> tx_n11;	// L15825
    tx_n11 = 0;	// L15826
    ap_uint<17> tx_s11;	// L15827
    tx_s11 = 0;	// L15828
    ap_uint<17> tx_w11;	// L15829
    tx_w11 = 0;	// L15830
    ap_uint<17> tx_e11;	// L15831
    tx_e11 = 0;	// L15832
    uint8_t v9960 = sb_v11[0];	// L15833
    int32_t v9961 = v9960;	// L15834
    bool v9962 = v9961 == 1;	// L15835
    if (v9962) {	// L15836
      uint8_t v9963 = sb_ix11[0];	// L15837
      int v9964 = v9963;	// L15838
      half v9965 = resq11[v9964];	// L15839
      half wb11;
#pragma HLS dependence variable=wb11 type=inter dependent=false	// L15840
      wb11 = v9965;	// L15841
      uint8_t v9967 = sb_cmp11[0];	// L15842
      int32_t v9968 = v9967;	// L15843
      bool v9969 = v9968 == 1;	// L15844
      if (v9969) {	// L15845
        uint8_t v9970 = sb_ix11[0];	// L15846
        int v9971 = v9970;	// L15847
        uint8_t v9972 = cmpq11[v9971];	// L15848
        condition_reg11 = v9972;	// L15849
      }
      uint8_t v9973 = sb_rtr11[0];	// L15851
      int32_t v9974 = v9973;	// L15852
      bool v9975 = v9974 == 1;	// L15853
      if (v9975) {	// L15854
        uint8_t v9976 = sb_inj11[0];	// L15855
        int32_t v9977 = v9976;	// L15856
        bool v9978 = v9977 == 1;	// L15857
        ap_int<26> v9979 = csd_pkt11;	// L15858
        bool v9980;
        ap_int<26> v9980_tmp = v9979;
        v9980 = v9980_tmp[25];	// L15859
        int32_t v9981 = v9980;	// L15860
        bool v9982 = v9981 == 0;	// L15861
        bool v9983 = v9978 & v9982;	// L15862
        if (v9983) {	// L15863
          half v9984 = wb11;	// L15864
          uint16_t v9985;
          union { half from; uint16_t to;} _converter_v9984_to_v9985 = {};
          _converter_v9984_to_v9985.from = v9984;
          v9985 = _converter_v9984_to_v9985.to;	// L15865
          ap_int<26> v9986 = csd_pkt11;	// L15866
          ap_int<26> v9987;
          ap_int<26> v9987_tmp = v9986;
          v9987_tmp(15, 0) = v9985;
          v9987 = v9987_tmp;	// L15867
          csd_pkt11 = v9987;	// L15868
          uint8_t v9988 = sb_dst11[0];	// L15869
          ap_uint<4> v9989 = v9988;	// L15870
          ap_int<26> v9990 = csd_pkt11;	// L15871
          ap_int<26> v9991;
          ap_int<26> v9991_tmp = v9990;
          v9991_tmp(19, 16) = v9989;
          v9991 = v9991_tmp;	// L15872
          csd_pkt11 = v9991;	// L15873
          uint8_t v9992 = sb_id11[0];	// L15874
          ap_uint<4> v9993 = v9992;	// L15875
          ap_int<26> v9994 = csd_pkt11;	// L15876
          ap_int<26> v9995;
          ap_int<26> v9995_tmp = v9994;
          v9995_tmp(24, 21) = v9993;
          v9995 = v9995_tmp;	// L15877
          csd_pkt11 = v9995;	// L15878
          uint8_t v9996 = sb_rvld11[0];	// L15879
          bool v9997 = v9996;	// L15880
          ap_int<26> v9998 = csd_pkt11;	// L15881
          ap_int<26> v9999;
          ap_int<26> v9999_tmp = v9998;
          v9999_tmp[25] = v9997;          v9999 = v9999_tmp;	// L15882
          csd_pkt11 = v9999;	// L15883
          uint8_t v10000 = sb_dir11[0];	// L15884
          int32_t v10001 = v10000;	// L15885
          csd_dir11 = v10001;	// L15886
        }
      } else {
        uint8_t v10002 = sb_dst11[0];	// L15889
        int32_t v10003 = v10002;	// L15890
        bool v10004 = v10003 >= 12;	// L15891
        if (v10004) {	// L15892
          ap_uint<17> tw011;	// L15893
          tw011 = 0;	// L15894
          uint8_t v10006 = sb_rvld11[0];	// L15895
          bool v10007 = v10006;	// L15896
          ap_int<17> v10008 = tw011;	// L15897
          ap_int<17> v10009;
          ap_int<17> v10009_tmp = v10008;
          v10009_tmp[0] = v10007;          v10009 = v10009_tmp;	// L15898
          tw011 = v10009;	// L15899
          half v10010 = wb11;	// L15900
          uint16_t v10011;
          union { half from; uint16_t to;} _converter_v10010_to_v10011 = {};
          _converter_v10010_to_v10011.from = v10010;
          v10011 = _converter_v10010_to_v10011.to;	// L15901
          ap_int<17> v10012 = tw011;	// L15902
          ap_int<17> v10013;
          ap_int<17> v10013_tmp = v10012;
          v10013_tmp(16, 1) = v10011;
          v10013 = v10013_tmp;	// L15903
          tw011 = v10013;	// L15904
          uint8_t v10014 = sb_dst11[0];	// L15905
          int32_t v10015 = v10014;	// L15906
          int32_t v10016 = v10015 & 3;	// L15907
          bool v10017 = v10016 == 0;	// L15908
          if (v10017) {	// L15909
            ap_int<17> v10018 = tw011;	// L15910
            tx_n11 = v10018;	// L15911
          } else {
            uint8_t v10019 = sb_dst11[0];	// L15913
            int32_t v10020 = v10019;	// L15914
            int32_t v10021 = v10020 & 3;	// L15915
            bool v10022 = v10021 == 1;	// L15916
            if (v10022) {	// L15917
              ap_int<17> v10023 = tw011;	// L15918
              tx_s11 = v10023;	// L15919
            } else {
              uint8_t v10024 = sb_dst11[0];	// L15921
              int32_t v10025 = v10024;	// L15922
              int32_t v10026 = v10025 & 3;	// L15923
              bool v10027 = v10026 == 2;	// L15924
              if (v10027) {	// L15925
                ap_int<17> v10028 = tw011;	// L15926
                tx_w11 = v10028;	// L15927
              } else {
                ap_int<17> v10029 = tw011;	// L15929
                tx_e11 = v10029;	// L15930
              }
            }
          }
        } else {
          uint8_t v10030 = sb_rvld11[0];	// L15935
          int32_t v10031 = v10030;	// L15936
          bool v10032 = v10031 == 1;	// L15937
          if (v10032) {	// L15938
            uint8_t v10033 = sb_dst11[0];	// L15939
            int32_t v10034 = v10033;	// L15940
            bool v10035 = v10034 < 8;	// L15941
            int32_t v10036 = dsmask11;	// L15942
            int32_t v10037 = v10036 >> v10034;	// L15943
            int32_t v10038 = v10037 & 1;	// L15944
            bool v10039 = v10038 == 1;	// L15945
            bool v10040 = v10035 & v10039;	// L15946
            if (v10040) {	// L15947
              uint8_t v10041 = sb_dst11[0];	// L15948
              int v10042 = v10041;	// L15949
              int32_t v10043 = drf_full11[v10042];	// L15950
              bool v10044 = v10043 == 0;	// L15951
              if (v10044) {	// L15952
                half v10045 = wb11;	// L15953
                uint8_t v10046 = sb_dst11[0];	// L15954
                int v10047 = v10046;	// L15955
                drf11[v10047] = v10045;	// L15956
                uint8_t v10048 = sb_dst11[0];	// L15957
                int v10049 = v10048;	// L15958
                drf_full11[v10049] = 1;	// L15959
              }
            } else {
              half v10050 = wb11;	// L15962
              uint8_t v10051 = sb_dst11[0];	// L15963
              int32_t v10052 = v10051;	// L15964
              int32_t v10053 = v10052 & 7;	// L15965
              int v10054 = v10053;	// L15966
              drf11[v10054] = v10050;	// L15967
            }
          }
        }
      }
    }
    int32_t pc11;	// L15973
    pc11 = -1;	// L15974
    int8_t v10056 = fetch_en11;	// L15975
    int32_t v10057 = v10056;	// L15976
    bool v10058 = v10057 == 1;	// L15977
    if (v10058) {	// L15978
      int8_t v10059 = instr_cnt11;	// L15979
      int32_t v10060 = v10059;	// L15980
      pc11 = v10060;	// L15981
    }
    int8_t v10061 = fetch_en11;	// L15983
    int32_t v10062 = v10061;	// L15984
    bool v10063 = v10062 == 1;	// L15985
    if (v10063) {	// L15986
      fe_ever11 = 1;	// L15987
    }
    int32_t instr11;	// L15989
    instr11 = 0;	// L15990
    int32_t v10065 = pc11;	// L15991
    bool v10066 = v10065 >= 0;	// L15992
    if (v10066) {	// L15993
      int32_t v10067 = pc11;	// L15994
      int v10068 = v10067;	// L15995
      int32_t v10069 = irf11[v10068];	// L15996
      instr11 = v10069;	// L15997
    }
    int32_t v10070 = instr11;	// L15999
    int32_t v10071 = v10070 & 15;	// L16000
    int32_t op11;	// L16001
    op11 = v10071;	// L16002
    int32_t v10073 = instr11;	// L16003
    int32_t v10074 = v10073 >> 4;	// L16004
    int32_t v10075 = v10074 & 15;	// L16005
    int32_t dst11;	// L16006
    dst11 = v10075;	// L16007
    int32_t v10077 = instr11;	// L16008
    int32_t v10078 = v10077 >> 8;	// L16009
    int32_t v10079 = v10078 & 15;	// L16010
    int32_t s111;	// L16011
    s111 = v10079;	// L16012
    int32_t v10081 = instr11;	// L16013
    int32_t v10082 = v10081 >> 12;	// L16014
    int32_t v10083 = v10082 & 15;	// L16015
    int32_t s211;	// L16016
    s211 = v10083;	// L16017
    half a11;	// L16018
    a11 = 0.000000;	// L16019
    half b11;	// L16020
    b11 = 0.000000;	// L16021
    int32_t v10087 = s111;	// L16022
    bool v10088 = v10087 >= 12;	// L16023
    if (v10088) {	// L16024
      int32_t v10089 = s111;	// L16025
      int32_t v10090 = v10089 & 3;	// L16026
      int v10091 = v10090;	// L16027
      half v10092 = hold_v11[v10091][0];	// L16028
      a11 = v10092;	// L16029
    } else {
      int32_t v10093 = s111;	// L16031
      int v10094 = v10093;	// L16032
      half v10095 = drf11[v10094];	// L16033
      a11 = v10095;	// L16034
    }
    int32_t v10096 = s211;	// L16036
    bool v10097 = v10096 >= 12;	// L16037
    if (v10097) {	// L16038
      int32_t v10098 = s211;	// L16039
      int32_t v10099 = v10098 & 3;	// L16040
      int v10100 = v10099;	// L16041
      half v10101 = hold_v11[v10100][0];	// L16042
      b11 = v10101;	// L16043
    } else {
      int32_t v10102 = s211;	// L16045
      int v10103 = v10102;	// L16046
      half v10104 = drf11[v10103];	// L16047
      b11 = v10104;	// L16048
    }
    int32_t a_vld11;	// L16050
    a_vld11 = 1;	// L16051
    int32_t b_vld11;	// L16052
    b_vld11 = 1;	// L16053
    int32_t v10107 = s111;	// L16054
    bool v10108 = v10107 >= 12;	// L16055
    if (v10108) {	// L16056
      a_vld11 = 0;	// L16057
      int32_t v10109 = s111;	// L16058
      int32_t v10110 = v10109 & 3;	// L16059
      int v10111 = v10110;	// L16060
      uint8_t v10112 = hold_cnt11[v10111];	// L16061
      int32_t v10113 = v10112;	// L16062
      bool v10114 = v10113 > 0;	// L16063
      if (v10114) {	// L16064
        a_vld11 = 1;	// L16065
      }
    }
    int32_t v10115 = s211;	// L16068
    bool v10116 = v10115 >= 12;	// L16069
    if (v10116) {	// L16070
      b_vld11 = 0;	// L16071
      int32_t v10117 = s211;	// L16072
      int32_t v10118 = v10117 & 3;	// L16073
      int v10119 = v10118;	// L16074
      uint8_t v10120 = hold_cnt11[v10119];	// L16075
      int32_t v10121 = v10120;	// L16076
      bool v10122 = v10121 > 0;	// L16077
      if (v10122) {	// L16078
        b_vld11 = 1;	// L16079
      }
    }
    int32_t v10123 = s111;	// L16082
    bool v10124 = v10123 < 8;	// L16083
    int32_t v10125 = dsmask11;	// L16084
    int32_t v10126 = v10125 >> v10123;	// L16085
    int32_t v10127 = v10126 & 1;	// L16086
    bool v10128 = v10127 == 1;	// L16087
    bool v10129 = v10124 & v10128;	// L16088
    if (v10129) {	// L16089
      int32_t v10130 = s111;	// L16090
      int v10131 = v10130;	// L16091
      int32_t v10132 = drf_full11[v10131];	// L16092
      bool v10133 = v10132 == 0;	// L16093
      if (v10133) {	// L16094
        a_vld11 = 0;	// L16095
      }
    }
    int32_t v10134 = s211;	// L16098
    bool v10135 = v10134 < 8;	// L16099
    int32_t v10136 = dsmask11;	// L16100
    int32_t v10137 = v10136 >> v10134;	// L16101
    int32_t v10138 = v10137 & 1;	// L16102
    bool v10139 = v10138 == 1;	// L16103
    bool v10140 = v10135 & v10139;	// L16104
    if (v10140) {	// L16105
      int32_t v10141 = s211;	// L16106
      int v10142 = v10141;	// L16107
      int32_t v10143 = drf_full11[v10142];	// L16108
      bool v10144 = v10143 == 0;	// L16109
      if (v10144) {	// L16110
        b_vld11 = 0;	// L16111
      }
    }
    int32_t binop11;	// L16114
    binop11 = 0;	// L16115
    int32_t v10146 = op11;	// L16116
    bool v10147 = v10146 == 0;	// L16117
    bool v10148 = v10146 == 1;	// L16118
    bool v10149 = v10146 == 2;	// L16119
    bool v10150 = v10146 == 8;	// L16120
    bool v10151 = v10146 == 9;	// L16121
    bool v10152 = v10147 | v10148;	// L16122
    bool v10153 = v10152 | v10149;	// L16123
    bool v10154 = v10153 | v10150;	// L16124
    bool v10155 = v10154 | v10151;	// L16125
    if (v10155) {	// L16126
      binop11 = 1;	// L16127
    }
    int32_t raw11;	// L16129
    raw11 = 0;	// L16130
    int32_t cmp_busy11;	// L16131
    cmp_busy11 = 0;	// L16132
    l_S_k_5_k22: for (int k22 = 0; k22 < 4; k22++) {	// L16133
      uint8_t v10159 = sb_v11[(k22 + 1)];	// L16134
      int32_t v10160 = v10159;	// L16135
      bool v10161 = v10160 == 1;	// L16136
      uint8_t v10162 = sb_rtr11[(k22 + 1)];	// L16137
      int32_t v10163 = v10162;	// L16138
      bool v10164 = v10163 == 0;	// L16139
      uint8_t v10165 = sb_dst11[(k22 + 1)];	// L16140
      int32_t v10166 = v10165;	// L16141
      bool v10167 = v10166 < 12;	// L16142
      bool v10168 = v10161 & v10164;	// L16143
      bool v10169 = v10168 & v10167;	// L16144
      if (v10169) {	// L16145
        int32_t v10170 = s111;	// L16146
        bool v10171 = v10170 < 12;	// L16147
        uint8_t v10172 = sb_dst11[(k22 + 1)];	// L16148
        int32_t v10173 = v10172;	// L16149
        int32_t v10174 = v10173 & 7;	// L16150
        int32_t v10175 = v10170 & 7;	// L16151
        bool v10176 = v10174 == v10175;	// L16152
        bool v10177 = v10171 & v10176;	// L16153
        if (v10177) {	// L16154
          raw11 = 1;	// L16155
        }
        int32_t v10178 = binop11;	// L16157
        bool v10179 = v10178 == 1;	// L16158
        int32_t v10180 = s211;	// L16159
        bool v10181 = v10180 < 12;	// L16160
        uint8_t v10182 = sb_dst11[(k22 + 1)];	// L16161
        int32_t v10183 = v10182;	// L16162
        int32_t v10184 = v10183 & 7;	// L16163
        int32_t v10185 = v10180 & 7;	// L16164
        bool v10186 = v10184 == v10185;	// L16165
        bool v10187 = v10179 & v10181;	// L16166
        bool v10188 = v10187 & v10186;	// L16167
        if (v10188) {	// L16168
          raw11 = 1;	// L16169
        }
      }
      uint8_t v10189 = sb_v11[(k22 + 1)];	// L16172
      int32_t v10190 = v10189;	// L16173
      bool v10191 = v10190 == 1;	// L16174
      uint8_t v10192 = sb_cmp11[(k22 + 1)];	// L16175
      int32_t v10193 = v10192;	// L16176
      bool v10194 = v10193 == 1;	// L16177
      bool v10195 = v10191 & v10194;	// L16178
      if (v10195) {	// L16179
        cmp_busy11 = 1;	// L16180
      }
    }
    int32_t is_cond11;	// L16183
    is_cond11 = 0;	// L16184
    int32_t v10197 = op11;	// L16185
    bool v10198 = v10197 >= 12;	// L16186
    ap_int<33> v10199 = v10197;	// L16187
    bool v10200 = v10199 <= 15;	// L16188
    bool v10201 = v10198 & v10200;	// L16189
    if (v10201) {	// L16190
      is_cond11 = 1;	// L16191
    }
    int32_t grant11;	// L16193
    grant11 = 0;	// L16194
    int32_t v10203 = pc11;	// L16195
    bool v10204 = v10203 >= 0;	// L16196
    if (v10204) {	// L16197
      grant11 = 1;	// L16198
    }
    int32_t v10205 = pc11;	// L16200
    bool v10206 = v10205 >= 0;	// L16201
    int32_t v10207 = a_vld11;	// L16202
    bool v10208 = v10207 == 0;	// L16203
    int32_t v10209 = binop11;	// L16204
    bool v10210 = v10209 == 1;	// L16205
    int32_t v10211 = b_vld11;	// L16206
    bool v10212 = v10211 == 0;	// L16207
    bool v10213 = v10210 & v10212;	// L16208
    bool v10214 = v10208 | v10213;	// L16209
    bool v10215 = v10206 & v10214;	// L16210
    if (v10215) {	// L16211
      grant11 = 0;	// L16212
    }
    int32_t v10216 = pc11;	// L16214
    bool v10217 = v10216 >= 0;	// L16215
    int32_t v10218 = raw11;	// L16216
    bool v10219 = v10218 == 1;	// L16217
    int32_t v10220 = is_cond11;	// L16218
    bool v10221 = v10220 == 1;	// L16219
    int32_t v10222 = cmp_busy11;	// L16220
    bool v10223 = v10222 == 1;	// L16221
    bool v10224 = v10221 & v10223;	// L16222
    bool v10225 = v10219 | v10224;	// L16223
    bool v10226 = v10217 & v10225;	// L16224
    if (v10226) {	// L16225
      grant11 = 0;	// L16226
    }
    int32_t v10227 = grant11;	// L16228
    bool v10228 = v10227 == 1;	// L16229
    if (v10228) {	// L16230
      int8_t v10229 = instr_cnt11;	// L16231
      int32_t v10230 = cfg_isz11;	// L16232
      int32_t v10231 = v10229;	// L16233
      bool v10232 = v10231 == v10230;	// L16234
      if (v10232) {	// L16235
        instr_cnt11 = 0;	// L16236
        int8_t v10233 = iter_cnt11;	// L16237
        int32_t v10234 = cfg_itsz11;	// L16238
        ap_int<33> v10235 = v10234;	// L16239
        ap_int<33> v10236 = v10235 - 1;	// L16240
        ap_int<33> v10237 = v10233;	// L16241
        bool v10238 = v10237 == v10236;	// L16242
        if (v10238) {	// L16243
          fetch_en11 = 0;	// L16244
        } else {
          int8_t v10239 = iter_cnt11;	// L16246
          ap_int<33> v10240 = v10239;	// L16247
          ap_int<33> v10241 = v10240 + 1;	// L16248
          uint8_t v10242 = v10241;	// L16249
          iter_cnt11 = v10242;	// L16250
        }
      } else {
        int8_t v10243 = instr_cnt11;	// L16253
        ap_int<33> v10244 = v10243;	// L16254
        ap_int<33> v10245 = v10244 + 1;	// L16255
        uint8_t v10246 = v10245;	// L16256
        instr_cnt11 = v10246;	// L16257
      }
    }
    int32_t c111;	// L16260
    c111 = -1;	// L16261
    int32_t c211;	// L16262
    c211 = -1;	// L16263
    int32_t v10249 = grant11;	// L16264
    bool v10250 = v10249 == 1;	// L16265
    int32_t v10251 = s111;	// L16266
    bool v10252 = v10251 >= 12;	// L16267
    bool v10253 = v10250 & v10252;	// L16268
    if (v10253) {	// L16269
      int32_t v10254 = s111;	// L16270
      int32_t v10255 = v10254 & 3;	// L16271
      c111 = v10255;	// L16272
    }
    int32_t v10256 = grant11;	// L16274
    bool v10257 = v10256 == 1;	// L16275
    int32_t v10258 = s211;	// L16276
    bool v10259 = v10258 >= 12;	// L16277
    bool v10260 = v10257 & v10259;	// L16278
    if (v10260) {	// L16279
      int32_t v10261 = s211;	// L16280
      int32_t v10262 = v10261 & 3;	// L16281
      c211 = v10262;	// L16282
    }
    int32_t v10263 = c111;	// L16284
    bool v10264 = v10263 >= 0;	// L16285
    if (v10264) {	// L16286
      int32_t v10265 = c111;	// L16287
      int v10266 = v10265;	// L16288
      half v10267 = hold_v11[v10266][1];	// L16289
      hold_v11[v10266][0] = v10267;	// L16290
      int32_t v10268 = c111;	// L16291
      int v10269 = v10268;	// L16292
      uint8_t v10270 = hold_cnt11[v10269];	// L16293
      ap_int<33> v10271 = v10270;	// L16294
      ap_int<33> v10272 = v10271 - 1;	// L16295
      uint8_t v10273 = v10272;	// L16296
      hold_cnt11[v10269] = v10273;	// L16297
    }
    int32_t v10274 = c211;	// L16299
    bool v10275 = v10274 >= 0;	// L16300
    int32_t v10276 = c111;	// L16301
    bool v10277 = v10274 != v10276;	// L16302
    bool v10278 = v10275 & v10277;	// L16303
    if (v10278) {	// L16304
      int32_t v10279 = c211;	// L16305
      int v10280 = v10279;	// L16306
      half v10281 = hold_v11[v10280][1];	// L16307
      hold_v11[v10280][0] = v10281;	// L16308
      int32_t v10282 = c211;	// L16309
      int v10283 = v10282;	// L16310
      uint8_t v10284 = hold_cnt11[v10283];	// L16311
      ap_int<33> v10285 = v10284;	// L16312
      ap_int<33> v10286 = v10285 - 1;	// L16313
      uint8_t v10287 = v10286;	// L16314
      hold_cnt11[v10283] = v10287;	// L16315
    }
    int32_t v10288 = grant11;	// L16317
    bool v10289 = v10288 == 1;	// L16318
    int32_t v10290 = s111;	// L16319
    bool v10291 = v10290 < 8;	// L16320
    int32_t v10292 = dsmask11;	// L16321
    int32_t v10293 = v10292 >> v10290;	// L16322
    int32_t v10294 = v10293 & 1;	// L16323
    bool v10295 = v10294 == 1;	// L16324
    bool v10296 = v10289 & v10291;	// L16325
    bool v10297 = v10296 & v10295;	// L16326
    if (v10297) {	// L16327
      int32_t v10298 = s111;	// L16328
      int v10299 = v10298;	// L16329
      drf_full11[v10299] = 0;	// L16330
    }
    int32_t v10300 = grant11;	// L16332
    bool v10301 = v10300 == 1;	// L16333
    int32_t v10302 = s211;	// L16334
    bool v10303 = v10302 < 8;	// L16335
    int32_t v10304 = dsmask11;	// L16336
    int32_t v10305 = v10304 >> v10302;	// L16337
    int32_t v10306 = v10305 & 1;	// L16338
    bool v10307 = v10306 == 1;	// L16339
    bool v10308 = v10301 & v10303;	// L16340
    bool v10309 = v10308 & v10307;	// L16341
    if (v10309) {	// L16342
      int32_t v10310 = s211;	// L16343
      int v10311 = v10310;	// L16344
      drf_full11[v10311] = 0;	// L16345
    }
    half res11;
#pragma HLS dependence variable=res11 type=inter dependent=false	// L16347
    res11 = 0.000000;	// L16348
    int32_t v10313 = op11;	// L16349
    bool v10314 = v10313 == 0;	// L16350
    if (v10314) {	// L16351
      half v10315 = a11;	// L16352
      half v10316 = b11;	// L16353
      half v10317 = v10315 + v10316;	// L16354
      res11 = v10317;	// L16355
    } else {
      int32_t v10318 = op11;	// L16357
      bool v10319 = v10318 == 1;	// L16358
      if (v10319) {	// L16359
        half v10320 = a11;	// L16360
        half v10321 = b11;	// L16361
        half v10322 = v10320 - v10321;	// L16362
        res11 = v10322;	// L16363
      } else {
        int32_t v10323 = op11;	// L16365
        bool v10324 = v10323 == 2;	// L16366
        if (v10324) {	// L16367
          half v10325 = a11;	// L16368
          half v10326 = b11;	// L16369
          half v10327 = v10325 * v10326;	// L16370
          res11 = v10327;	// L16371
        } else {
          int32_t v10328 = op11;	// L16373
          bool v10329 = v10328 == 8;	// L16374
          if (v10329) {	// L16375
            half v10330 = a11;	// L16376
            half v10331 = b11;	// L16377
            bool v10332 = v10330 >= v10331;	// L16378
            if (v10332) {	// L16379
              res11 = 1.000000;	// L16380
            } else {
              res11 = -1.000000;	// L16382
            }
          } else {
            int32_t v10333 = op11;	// L16385
            bool v10334 = v10333 == 9;	// L16386
            if (v10334) {	// L16387
              half v10335 = a11;	// L16388
              half v10336 = b11;	// L16389
              bool v10337 = v10335 < v10336;	// L16390
              if (v10337) {	// L16391
                res11 = 1.000000;	// L16392
              } else {
                res11 = -1.000000;	// L16394
              }
            } else {
              half v10338 = a11;	// L16397
              res11 = v10338;	// L16398
            }
          }
        }
      }
    }
    int32_t v10339 = a_vld11;	// L16404
    int32_t res_vld11;	// L16405
    res_vld11 = v10339;	// L16406
    int32_t v10341 = op11;	// L16407
    bool v10342 = v10341 == 0;	// L16408
    bool v10343 = v10341 == 1;	// L16409
    bool v10344 = v10341 == 2;	// L16410
    bool v10345 = v10341 == 8;	// L16411
    bool v10346 = v10341 == 9;	// L16412
    bool v10347 = v10342 | v10343;	// L16413
    bool v10348 = v10347 | v10344;	// L16414
    bool v10349 = v10348 | v10345;	// L16415
    bool v10350 = v10349 | v10346;	// L16416
    if (v10350) {	// L16417
      int32_t v10351 = a_vld11;	// L16418
      int32_t v10352 = b_vld11;	// L16419
      int64_t v10353 = v10351;	// L16420
      int64_t v10354 = v10352;	// L16421
      int64_t v10355 = v10353 * v10354;	// L16422
      int32_t v10356 = v10355;	// L16423
      res_vld11 = v10356;	// L16424
    }
    int32_t v10357 = grant11;	// L16426
    bool v10358 = v10357 == 0;	// L16427
    if (v10358) {	// L16428
      res_vld11 = 0;	// L16429
    }
    int32_t is_rtr11;	// L16431
    is_rtr11 = 0;	// L16432
    int32_t v10360 = op11;	// L16433
    bool v10361 = v10360 >= 4;	// L16434
    ap_int<33> v10362 = v10360;	// L16435
    bool v10363 = v10362 <= 7;	// L16436
    bool v10364 = v10361 & v10363;	// L16437
    if (v10364) {	// L16438
      is_rtr11 = 1;	// L16439
    }
    l_S_k_6_k23: for (int k23 = 0; k23 < 4; k23++) {	// L16441
      uint8_t v10366 = sb_v11[(k23 + 1)];	// L16442
      sb_v11[k23] = v10366;	// L16443
      uint8_t v10367 = sb_dst11[(k23 + 1)];	// L16444
      sb_dst11[k23] = v10367;	// L16445
      uint8_t v10368 = sb_cmp11[(k23 + 1)];	// L16446
      sb_cmp11[k23] = v10368;	// L16447
      uint8_t v10369 = sb_rtr11[(k23 + 1)];	// L16448
      sb_rtr11[k23] = v10369;	// L16449
      uint8_t v10370 = sb_inj11[(k23 + 1)];	// L16450
      sb_inj11[k23] = v10370;	// L16451
      uint8_t v10371 = sb_dir11[(k23 + 1)];	// L16452
      sb_dir11[k23] = v10371;	// L16453
      uint8_t v10372 = sb_id11[(k23 + 1)];	// L16454
      sb_id11[k23] = v10372;	// L16455
      uint8_t v10373 = sb_rvld11[(k23 + 1)];	// L16456
      sb_rvld11[k23] = v10373;	// L16457
      uint8_t v10374 = sb_ix11[(k23 + 1)];	// L16458
      sb_ix11[k23] = v10374;	// L16459
    }
    sb_v11[4] = 0;	// L16461
    int32_t v10375 = grant11;	// L16462
    bool v10376 = v10375 == 1;	// L16463
    if (v10376) {	// L16464
      half v10377 = res11;	// L16465
      int8_t v10378 = resq_wr11;	// L16466
      int v10379 = v10378;	// L16467
      resq11[v10379] = v10377;	// L16468
      int32_t cq11;	// L16469
      cq11 = 0;	// L16470
      int32_t v10381 = op11;	// L16471
      bool v10382 = v10381 == 8;	// L16472
      if (v10382) {	// L16473
        half v10383 = a11;	// L16474
        half v10384 = b11;	// L16475
        bool v10385 = v10383 >= v10384;	// L16476
        if (v10385) {	// L16477
          cq11 = 1;	// L16478
        }
      }
      int32_t v10386 = op11;	// L16481
      bool v10387 = v10386 == 9;	// L16482
      if (v10387) {	// L16483
        half v10388 = a11;	// L16484
        half v10389 = b11;	// L16485
        bool v10390 = v10388 < v10389;	// L16486
        if (v10390) {	// L16487
          cq11 = 1;	// L16488
        }
      }
      int32_t v10391 = cq11;	// L16491
      uint8_t v10392 = v10391;	// L16492
      int8_t v10393 = resq_wr11;	// L16493
      int v10394 = v10393;	// L16494
      cmpq11[v10394] = v10392;	// L16495
      sb_v11[4] = 1;	// L16496
      int32_t v10395 = dst11;	// L16497
      uint8_t v10396 = v10395;	// L16498
      sb_dst11[4] = v10396;	// L16499
      int8_t v10397 = resq_wr11;	// L16500
      sb_ix11[4] = v10397;	// L16501
      sb_cmp11[4] = 0;	// L16502
      int32_t v10398 = op11;	// L16503
      bool v10399 = v10398 == 8;	// L16504
      bool v10400 = v10398 == 9;	// L16505
      bool v10401 = v10399 | v10400;	// L16506
      if (v10401) {	// L16507
        sb_cmp11[4] = 1;	// L16508
      }
      int32_t v10402 = is_rtr11;	// L16510
      int32_t rtrf11;	// L16511
      rtrf11 = v10402;	// L16512
      int32_t v10404 = is_cond11;	// L16513
      bool v10405 = v10404 == 1;	// L16514
      if (v10405) {	// L16515
        rtrf11 = 1;	// L16516
      }
      int32_t v10406 = rtrf11;	// L16518
      uint8_t v10407 = v10406;	// L16519
      sb_rtr11[4] = v10407;	// L16520
      int32_t v10408 = is_rtr11;	// L16521
      int32_t inj11;	// L16522
      inj11 = v10408;	// L16523
      int32_t v10410 = is_cond11;	// L16524
      bool v10411 = v10410 == 1;	// L16525
      int8_t v10412 = condition_reg11;	// L16526
      int32_t v10413 = v10412;	// L16527
      bool v10414 = v10413 == 1;	// L16528
      bool v10415 = v10411 & v10414;	// L16529
      if (v10415) {	// L16530
        inj11 = 1;	// L16531
      }
      int32_t v10416 = inj11;	// L16533
      uint8_t v10417 = v10416;	// L16534
      sb_inj11[4] = v10417;	// L16535
      int32_t v10418 = op11;	// L16536
      int32_t v10419 = v10418 & 3;	// L16537
      uint8_t v10420 = v10419;	// L16538
      sb_dir11[4] = v10420;	// L16539
      int32_t v10421 = s211;	// L16540
      uint8_t v10422 = v10421;	// L16541
      sb_id11[4] = v10422;	// L16542
      int32_t v10423 = res_vld11;	// L16543
      uint8_t v10424 = v10423;	// L16544
      sb_rvld11[4] = v10424;	// L16545
      int8_t v10425 = resq_wr11;	// L16546
      ap_int<33> v10426 = v10425;	// L16547
      ap_int<33> v10427 = v10426 + 1;	// L16548
      ap_int<33> v10428 = v10427 & 7;	// L16549
      uint8_t v10429 = v10428;	// L16550
      resq_wr11 = v10429;	// L16551
    }
    ap_int<17> v10430 = tx_n11;	// L16553
    txn_r11 = v10430;	// L16554
    ap_int<17> v10431 = tx_s11;	// L16555
    txs_r11 = v10431;	// L16556
    ap_int<17> v10432 = tx_w11;	// L16557
    txw_r11 = v10432;	// L16558
    ap_int<17> v10433 = tx_e11;	// L16559
    txe_r11 = v10433;	// L16560
    int32_t v10434 = crv_vld11;	// L16561
    bool v10435 = v10434 == 1;	// L16562
    if (v10435) {	// L16563
      int32_t v10436 = crv_mode11;	// L16564
      bool v10437 = v10436 == 1;	// L16565
      if (v10437) {	// L16566
        int32_t v10438 = crv_addr11;	// L16567
        int32_t v10439 = v10438 >> 3;	// L16568
        int32_t v10440 = v10439 & 1;	// L16569
        bool v10441 = v10440 == 1;	// L16570
        if (v10441) {	// L16571
          int32_t v10442 = crv_raw11;	// L16572
          int32_t v10443 = crv_addr11;	// L16573
          int32_t v10444 = v10443 & 7;	// L16574
          int v10445 = v10444;	// L16575
          irf11[v10445] = v10442;	// L16576
        } else {
          int32_t v10446 = crv_addr11;	// L16578
          bool v10447 = v10446 == 0;	// L16579
          if (v10447) {	// L16580
            int32_t v10448 = crv_raw11;	// L16581
            int32_t v10449 = v10448 & 255;	// L16582
            dsmask11 = v10449;	// L16583
            int32_t v10450 = crv_raw11;	// L16584
            int32_t v10451 = v10450 >> 8;	// L16585
            int32_t v10452 = v10451 & 7;	// L16586
            cfg_isz11 = v10452;	// L16587
            int32_t v10453 = crv_raw11;	// L16588
            int32_t v10454 = v10453 >> 15;	// L16589
            int32_t v10455 = v10454 & 1;	// L16590
            bool v10456 = v10455 == 1;	// L16591
            if (v10456) {	// L16592
              fetch_en11 = 1;	// L16593
              instr_cnt11 = 0;	// L16594
              iter_cnt11 = 0;	// L16595
            }
          } else {
            int32_t v10457 = crv_addr11;	// L16598
            bool v10458 = v10457 == 1;	// L16599
            if (v10458) {	// L16600
              int32_t v10459 = crv_raw11;	// L16601
              int32_t v10460 = v10459 & 255;	// L16602
              cfg_itsz11 = v10460;	// L16603
            }
          }
        }
      } else {
        int32_t v10461 = crv_addr11;	// L16608
        bool v10462 = v10461 < 8;	// L16609
        int32_t v10463 = dsmask11;	// L16610
        int32_t v10464 = v10463 >> v10461;	// L16611
        int32_t v10465 = v10464 & 1;	// L16612
        bool v10466 = v10465 == 1;	// L16613
        bool v10467 = v10462 & v10466;	// L16614
        if (v10467) {	// L16615
          int32_t v10468 = crv_addr11;	// L16616
          int v10469 = v10468;	// L16617
          int32_t v10470 = drf_full11[v10469];	// L16618
          bool v10471 = v10470 == 0;	// L16619
          if (v10471) {	// L16620
            half v10472 = crv_data11;	// L16621
            int32_t v10473 = crv_addr11;	// L16622
            int v10474 = v10473;	// L16623
            drf11[v10474] = v10472;	// L16624
            int32_t v10475 = crv_addr11;	// L16625
            int v10476 = v10475;	// L16626
            drf_full11[v10476] = 1;	// L16627
          }
        } else {
          half v10477 = crv_data11;	// L16630
          int32_t v10478 = crv_addr11;	// L16631
          int v10479 = v10478;	// L16632
          drf11[v10479] = v10477;	// L16633
        }
      }
    }
    ap_int<17> v10480 = txe_r11;	// L16637
    bool v10481;
    ap_int<17> v10481_tmp = v10480;
    v10481 = v10481_tmp[0];	// L16638
    int32_t v10482 = v10481;	// L16639
    bool v10483 = v10482 == 1;	// L16640
    if (v10483) {	// L16641
      ap_int<17> v10484 = txe_r11;	// L16642
      v9637.write(v10484);	// L16643
    }
    ap_int<17> v10485 = txw_r11;	// L16645
    bool v10486;
    ap_int<17> v10486_tmp = v10485;
    v10486 = v10486_tmp[0];	// L16646
    int32_t v10487 = v10486;	// L16647
    bool v10488 = v10487 == 1;	// L16648
    if (v10488) {	// L16649
      ap_int<17> v10489 = txw_r11;	// L16650
      v9638.write(v10489);	// L16651
    }
    ap_int<17> v10490 = txs_r11;	// L16653
    bool v10491;
    ap_int<17> v10491_tmp = v10490;
    v10491 = v10491_tmp[0];	// L16654
    int32_t v10492 = v10491;	// L16655
    bool v10493 = v10492 == 1;	// L16656
    if (v10493) {	// L16657
      ap_int<17> v10494 = txs_r11;	// L16658
      v9639.write(v10494);	// L16659
    }
    ap_int<17> v10495 = txn_r11;	// L16661
    bool v10496;
    ap_int<17> v10496_tmp = v10495;
    v10496 = v10496_tmp[0];	// L16662
    int32_t v10497 = v10496;	// L16663
    bool v10498 = v10497 == 1;	// L16664
    if (v10498) {	// L16665
      ap_int<17> v10499 = txn_r11;	// L16666
      v9640.write(v10499);	// L16667
    }
  }
}

void node_3_0(
  hls::stream< ap_uint<26> >& v10500,
  hls::stream< ap_uint<26> >& v10501,
  hls::stream< ap_uint<26> >& v10502,
  hls::stream< ap_uint<26> >& v10503,
  hls::stream< ap_uint<26> >& v10504,
  hls::stream< ap_uint<26> >& v10505,
  hls::stream< ap_uint<26> >& v10506,
  hls::stream< ap_uint<26> >& v10507,
  hls::stream< ap_uint<17> >& v10508,
  hls::stream< ap_uint<17> >& v10509,
  hls::stream< ap_uint<17> >& v10510,
  hls::stream< ap_uint<17> >& v10511,
  hls::stream< ap_uint<17> >& v10512,
  hls::stream< ap_uint<17> >& v10513,
  hls::stream< ap_uint<17> >& v10514,
  hls::stream< ap_uint<17> >& v10515
) {	// L16672
  int32_t irf12[8];	// L16705
  #pragma HLS array_partition variable=irf12 complete dim=1

  for (int v10517 = 0; v10517 < 8; v10517++) {	// L16706
    irf12[v10517] = 0;	// L16706
  }
  half drf12[8];	// L16707
  #pragma HLS array_partition variable=drf12 complete dim=1

  for (int v10519 = 0; v10519 < 8; v10519++) {	// L16708
    drf12[v10519] = 0.000000;	// L16708
  }
  int32_t drf_full12[8];	// L16709
  #pragma HLS array_partition variable=drf_full12 complete dim=1

  for (int v10521 = 0; v10521 < 8; v10521++) {	// L16710
    drf_full12[v10521] = 0;	// L16710
  }
  int32_t dsmask12;	// L16711
  dsmask12 = 0;	// L16712
  int32_t crv_vld12;	// L16713
  crv_vld12 = 0;	// L16714
  half crv_data12;	// L16715
  crv_data12 = 0.000000;	// L16716
  int32_t crv_addr12;	// L16717
  crv_addr12 = 0;	// L16718
  int32_t crv_mode12;	// L16719
  crv_mode12 = 0;	// L16720
  int32_t crv_raw12;	// L16721
  crv_raw12 = 0;	// L16722
  int32_t csd_vld12;	// L16723
  csd_vld12 = 0;	// L16724
  ap_uint<26> csd_pkt12;	// L16725
  csd_pkt12 = 0;	// L16726
  int32_t csd_dir12;	// L16727
  csd_dir12 = 0;	// L16728
  int32_t row_id12;	// L16729
  row_id12 = 3;	// L16730
  int32_t col_id12;	// L16731
  col_id12 = 0;	// L16732
  ap_uint<17> txn_r12;	// L16733
  txn_r12 = 0;	// L16734
  ap_uint<17> txs_r12;	// L16735
  txs_r12 = 0;	// L16736
  ap_uint<17> txw_r12;	// L16737
  txw_r12 = 0;	// L16738
  ap_uint<17> txe_r12;	// L16739
  txe_r12 = 0;	// L16740
  half hold_v12[4][2];	// L16741
  #pragma HLS array_partition variable=hold_v12 complete dim=1
  #pragma HLS array_partition variable=hold_v12 complete dim=2

  for (int v10538 = 0; v10538 < 4; v10538++) {	// L16742
    for (int v10539 = 0; v10539 < 2; v10539++) {	// L16742
      hold_v12[v10538][v10539] = 0.000000;	// L16742
    }
  }
  uint8_t hold_cnt12[4];	// L16743
  #pragma HLS array_partition variable=hold_cnt12 complete dim=1

  for (int v10541 = 0; v10541 < 4; v10541++) {	// L16744
    hold_cnt12[v10541] = 0;	// L16744
  }
  int32_t crv_ever12;	// L16745
  crv_ever12 = 0;	// L16746
  int32_t fe_ever12;	// L16747
  fe_ever12 = 0;	// L16748
  ap_uint<26> rbuf12[4][2];	// L16749
  #pragma HLS array_partition variable=rbuf12 complete dim=1
  #pragma HLS array_partition variable=rbuf12 complete dim=2

  for (int v10545 = 0; v10545 < 4; v10545++) {	// L16750
    for (int v10546 = 0; v10546 < 2; v10546++) {	// L16750
      rbuf12[v10545][v10546] = 0;	// L16750
    }
  }
  uint8_t rbcnt12[4];	// L16751
  #pragma HLS array_partition variable=rbcnt12 complete dim=1

  for (int v10548 = 0; v10548 < 4; v10548++) {	// L16752
    rbcnt12[v10548] = 0;	// L16752
  }
  int32_t cfg_isz12;	// L16753
  cfg_isz12 = 0;	// L16754
  int32_t cfg_itsz12;	// L16755
  cfg_itsz12 = 0;	// L16756
  uint8_t fetch_en12;	// L16757
  fetch_en12 = 0;	// L16758
  uint8_t instr_cnt12;	// L16759
  instr_cnt12 = 0;	// L16760
  uint8_t iter_cnt12;	// L16761
  iter_cnt12 = 0;	// L16762
  uint8_t condition_reg12;	// L16763
  condition_reg12 = 0;	// L16764
  uint8_t sb_v12[5];	// L16765
  #pragma HLS array_partition variable=sb_v12 complete dim=1

  for (int v10556 = 0; v10556 < 5; v10556++) {	// L16766
    sb_v12[v10556] = 0;	// L16766
  }
  uint8_t sb_dst12[5];	// L16767
  #pragma HLS array_partition variable=sb_dst12 complete dim=1

  for (int v10558 = 0; v10558 < 5; v10558++) {	// L16768
    sb_dst12[v10558] = 0;	// L16768
  }
  uint8_t sb_cmp12[5];	// L16769
  #pragma HLS array_partition variable=sb_cmp12 complete dim=1

  for (int v10560 = 0; v10560 < 5; v10560++) {	// L16770
    sb_cmp12[v10560] = 0;	// L16770
  }
  uint8_t sb_rtr12[5];	// L16771
  #pragma HLS array_partition variable=sb_rtr12 complete dim=1

  for (int v10562 = 0; v10562 < 5; v10562++) {	// L16772
    sb_rtr12[v10562] = 0;	// L16772
  }
  uint8_t sb_inj12[5];	// L16773
  #pragma HLS array_partition variable=sb_inj12 complete dim=1

  for (int v10564 = 0; v10564 < 5; v10564++) {	// L16774
    sb_inj12[v10564] = 0;	// L16774
  }
  uint8_t sb_dir12[5];	// L16775
  #pragma HLS array_partition variable=sb_dir12 complete dim=1

  for (int v10566 = 0; v10566 < 5; v10566++) {	// L16776
    sb_dir12[v10566] = 0;	// L16776
  }
  uint8_t sb_id12[5];	// L16777
  #pragma HLS array_partition variable=sb_id12 complete dim=1

  for (int v10568 = 0; v10568 < 5; v10568++) {	// L16778
    sb_id12[v10568] = 0;	// L16778
  }
  uint8_t sb_rvld12[5];	// L16779
  #pragma HLS array_partition variable=sb_rvld12 complete dim=1

  for (int v10570 = 0; v10570 < 5; v10570++) {	// L16780
    sb_rvld12[v10570] = 0;	// L16780
  }
  uint8_t sb_ix12[5];	// L16781
  #pragma HLS array_partition variable=sb_ix12 complete dim=1

  for (int v10572 = 0; v10572 < 5; v10572++) {	// L16782
    sb_ix12[v10572] = 0;	// L16782
  }
  half resq12[8];	// L16783
  #pragma HLS array_partition variable=resq12 complete dim=1
#pragma HLS dependence variable=resq12 type=inter dependent=false

  for (int v10574 = 0; v10574 < 8; v10574++) {	// L16784
    resq12[v10574] = 0.000000;	// L16784
  }
  uint8_t cmpq12[8];	// L16785
  #pragma HLS array_partition variable=cmpq12 complete dim=1
#pragma HLS dependence variable=cmpq12 type=inter dependent=false

  for (int v10576 = 0; v10576 < 8; v10576++) {	// L16786
    cmpq12[v10576] = 0;	// L16786
  }
  uint8_t resq_wr12;	// L16787
  resq_wr12 = 0;	// L16788
  l_S_t_0_t12: for (int t12 = 0; t12 < 374; t12++) {	// L16789
  #pragma HLS pipeline II=1
    ap_uint<26> p_w12;	// L16790
    p_w12 = 0;	// L16791
    ap_uint<26> p_e12;	// L16792
    p_e12 = 0;	// L16793
    ap_uint<26> p_n12;	// L16794
    p_n12 = 0;	// L16795
    ap_uint<26> p_s12;	// L16796
    p_s12 = 0;	// L16797
    uint8_t v10583 = rbcnt12[0];	// L16798
    int32_t v10584 = v10583;	// L16799
    bool v10585 = v10584 < 2;	// L16800
    if (v10585) {	// L16801
      ap_uint<26> v10586;
      bool v10587 = v10500.read_nb(v10586);
	// L16802
      ap_uint<26> gw12;	// L16803
      gw12 = v10586;	// L16804
      bool okw12;	// L16805
      okw12 = v10587;	// L16806
      bool v10590 = okw12;	// L16807
      if (v10590) {	// L16808
        ap_int<26> v10591 = gw12;	// L16809
        p_w12 = v10591;	// L16810
      }
    }
    uint8_t v10592 = rbcnt12[1];	// L16813
    int32_t v10593 = v10592;	// L16814
    bool v10594 = v10593 < 2;	// L16815
    if (v10594) {	// L16816
      ap_uint<26> v10595;
      bool v10596 = v10501.read_nb(v10595);
	// L16817
      ap_uint<26> ge12;	// L16818
      ge12 = v10595;	// L16819
      bool oke12;	// L16820
      oke12 = v10596;	// L16821
      bool v10599 = oke12;	// L16822
      if (v10599) {	// L16823
        ap_int<26> v10600 = ge12;	// L16824
        p_e12 = v10600;	// L16825
      }
    }
    uint8_t v10601 = rbcnt12[2];	// L16828
    int32_t v10602 = v10601;	// L16829
    bool v10603 = v10602 < 2;	// L16830
    if (v10603) {	// L16831
      ap_uint<26> v10604;
      bool v10605 = v10502.read_nb(v10604);
	// L16832
      ap_uint<26> gn12;	// L16833
      gn12 = v10604;	// L16834
      bool okn12;	// L16835
      okn12 = v10605;	// L16836
      bool v10608 = okn12;	// L16837
      if (v10608) {	// L16838
        ap_int<26> v10609 = gn12;	// L16839
        p_n12 = v10609;	// L16840
      }
    }
    uint8_t v10610 = rbcnt12[3];	// L16843
    int32_t v10611 = v10610;	// L16844
    bool v10612 = v10611 < 2;	// L16845
    if (v10612) {	// L16846
      ap_uint<26> v10613;
      bool v10614 = v10503.read_nb(v10613);
	// L16847
      ap_uint<26> gs12;	// L16848
      gs12 = v10613;	// L16849
      bool oks12;	// L16850
      oks12 = v10614;	// L16851
      bool v10617 = oks12;	// L16852
      if (v10617) {	// L16853
        ap_int<26> v10618 = gs12;	// L16854
        p_s12 = v10618;	// L16855
      }
    }
    ap_uint<26> fin12[4];	// L16858
    for (int v10620 = 0; v10620 < 4; v10620++) {	// L16859
      fin12[v10620] = 0;	// L16859
    }
    ap_int<26> v10621 = p_w12;	// L16860
    fin12[0] = v10621;	// L16861
    ap_int<26> v10622 = p_e12;	// L16862
    fin12[1] = v10622;	// L16863
    ap_int<26> v10623 = p_n12;	// L16864
    fin12[2] = v10623;	// L16865
    ap_int<26> v10624 = p_s12;	// L16866
    fin12[3] = v10624;	// L16867
    l_S_d_0_d48: for (int d48 = 0; d48 < 4; d48++) {	// L16868
      ap_uint<26> v10626 = fin12[d48];	// L16869
      bool v10627;
      ap_int<26> v10627_tmp = v10626;
      v10627 = v10627_tmp[25];	// L16870
      int32_t v10628 = v10627;	// L16871
      bool v10629 = v10628 == 1;	// L16872
      uint8_t v10630 = rbcnt12[d48];	// L16873
      int32_t v10631 = v10630;	// L16874
      bool v10632 = v10631 < 2;	// L16875
      bool v10633 = v10629 & v10632;	// L16876
      if (v10633) {	// L16877
        ap_uint<26> v10634 = fin12[d48];	// L16878
        uint8_t v10635 = rbcnt12[d48];	// L16879
        int v10636 = v10635;	// L16880
        rbuf12[d48][v10636] = v10634;	// L16881
        uint8_t v10637 = rbcnt12[d48];	// L16882
        ap_int<33> v10638 = v10637;	// L16883
        ap_int<33> v10639 = v10638 + 1;	// L16884
        uint8_t v10640 = v10639;	// L16885
        rbcnt12[d48] = v10640;	// L16886
      }
    }
    ap_uint<26> hd12[4];	// L16889
    for (int v10642 = 0; v10642 < 4; v10642++) {	// L16890
      hd12[v10642] = 0;	// L16890
    }
    int32_t hvld12[4];	// L16891
    for (int v10644 = 0; v10644 < 4; v10644++) {	// L16892
      hvld12[v10644] = 0;	// L16892
    }
    int32_t hit12[4];	// L16893
    for (int v10646 = 0; v10646 < 4; v10646++) {	// L16894
      hit12[v10646] = 0;	// L16894
    }
    int32_t axis12[4];	// L16895
    for (int v10648 = 0; v10648 < 4; v10648++) {	// L16896
      axis12[v10648] = 0;	// L16896
    }
    int32_t v10649 = col_id12;	// L16897
    axis12[0] = v10649;	// L16898
    int32_t v10650 = col_id12;	// L16899
    axis12[1] = v10650;	// L16900
    int32_t v10651 = row_id12;	// L16901
    axis12[2] = v10651;	// L16902
    int32_t v10652 = row_id12;	// L16903
    axis12[3] = v10652;	// L16904
    l_S_d_1_d49: for (int d49 = 0; d49 < 4; d49++) {	// L16905
      uint8_t v10654 = rbcnt12[d49];	// L16906
      int32_t v10655 = v10654;	// L16907
      bool v10656 = v10655 > 0;	// L16908
      if (v10656) {	// L16909
        ap_uint<26> v10657 = rbuf12[d49][0];	// L16910
        hd12[d49] = v10657;	// L16911
        hvld12[d49] = 1;	// L16912
        ap_uint<26> v10658 = hd12[d49];	// L16913
        ap_int<4> v10659;
        ap_int<26> v10659_tmp = v10658;
        v10659 = v10659_tmp(24, 21);	// L16914
        int32_t v10660 = axis12[d49];	// L16915
        int32_t v10661 = v10659;	// L16916
        bool v10662 = v10661 == v10660;	// L16917
        if (v10662) {	// L16918
          hit12[d49] = 1;	// L16919
        }
      }
    }
    ap_uint<26> o_crv12;	// L16923
    o_crv12 = 0;	// L16924
    int32_t crv_in12;	// L16925
    crv_in12 = -1;	// L16926
    int32_t v10665 = hit12[3];	// L16927
    bool v10666 = v10665 == 1;	// L16928
    if (v10666) {	// L16929
      ap_uint<26> v10667 = hd12[3];	// L16930
      o_crv12 = v10667;	// L16931
      crv_in12 = 3;	// L16932
    } else {
      int32_t v10668 = hit12[2];	// L16934
      bool v10669 = v10668 == 1;	// L16935
      if (v10669) {	// L16936
        ap_uint<26> v10670 = hd12[2];	// L16937
        o_crv12 = v10670;	// L16938
        crv_in12 = 2;	// L16939
      } else {
        int32_t v10671 = hit12[1];	// L16941
        bool v10672 = v10671 == 1;	// L16942
        if (v10672) {	// L16943
          ap_uint<26> v10673 = hd12[1];	// L16944
          o_crv12 = v10673;	// L16945
          crv_in12 = 1;	// L16946
        } else {
          int32_t v10674 = hit12[0];	// L16948
          bool v10675 = v10674 == 1;	// L16949
          if (v10675) {	// L16950
            ap_uint<26> v10676 = hd12[0];	// L16951
            o_crv12 = v10676;	// L16952
            crv_in12 = 0;	// L16953
          }
        }
      }
    }
    int32_t pop12[4];	// L16958
    for (int v10678 = 0; v10678 < 4; v10678++) {	// L16959
      pop12[v10678] = 0;	// L16959
    }
    int32_t inj_done12;	// L16960
    inj_done12 = 0;	// L16961
    int32_t idir12;	// L16962
    idir12 = -1;	// L16963
    ap_int<26> v10681 = csd_pkt12;	// L16964
    bool v10682;
    ap_int<26> v10682_tmp = v10681;
    v10682 = v10682_tmp[25];	// L16965
    int32_t v10683 = v10682;	// L16966
    bool v10684 = v10683 == 1;	// L16967
    if (v10684) {	// L16968
      int32_t v10685 = csd_dir12;	// L16969
      ap_int<33> v10686 = v10685;	// L16970
      ap_int<33> v10687 = 3 - v10686;	// L16971
      int32_t v10688 = v10687;	// L16972
      idir12 = v10688;	// L16973
    }
    int32_t v10689 = idir12;	// L16975
    bool v10690 = v10689 == 0;	// L16976
    if (v10690) {	// L16977
      ap_int<26> v10691 = csd_pkt12;	// L16978
      bool v10692 = v10504.write_nb(v10691);
	// L16979
      if (v10692) {	// L16980
        inj_done12 = 1;	// L16981
      }
    } else {
      int32_t v10693 = hvld12[0];	// L16984
      bool v10694 = v10693 == 1;	// L16985
      int32_t v10695 = hit12[0];	// L16986
      bool v10696 = v10695 == 0;	// L16987
      bool v10697 = v10694 & v10696;	// L16988
      if (v10697) {	// L16989
        ap_uint<26> v10698 = hd12[0];	// L16990
        bool v10699 = v10504.write_nb(v10698);
	// L16991
        if (v10699) {	// L16992
          pop12[0] = 1;	// L16993
        }
      }
    }
    int32_t v10700 = idir12;	// L16997
    bool v10701 = v10700 == 1;	// L16998
    if (v10701) {	// L16999
      ap_int<26> v10702 = csd_pkt12;	// L17000
      bool v10703 = v10505.write_nb(v10702);
	// L17001
      if (v10703) {	// L17002
        inj_done12 = 1;	// L17003
      }
    } else {
      int32_t v10704 = hvld12[1];	// L17006
      bool v10705 = v10704 == 1;	// L17007
      int32_t v10706 = hit12[1];	// L17008
      bool v10707 = v10706 == 0;	// L17009
      bool v10708 = v10705 & v10707;	// L17010
      if (v10708) {	// L17011
        ap_uint<26> v10709 = hd12[1];	// L17012
        bool v10710 = v10505.write_nb(v10709);
	// L17013
        if (v10710) {	// L17014
          pop12[1] = 1;	// L17015
        }
      }
    }
    int32_t v10711 = idir12;	// L17019
    bool v10712 = v10711 == 2;	// L17020
    if (v10712) {	// L17021
      ap_int<26> v10713 = csd_pkt12;	// L17022
      bool v10714 = v10506.write_nb(v10713);
	// L17023
      if (v10714) {	// L17024
        inj_done12 = 1;	// L17025
      }
    } else {
      int32_t v10715 = hvld12[2];	// L17028
      bool v10716 = v10715 == 1;	// L17029
      int32_t v10717 = hit12[2];	// L17030
      bool v10718 = v10717 == 0;	// L17031
      bool v10719 = v10716 & v10718;	// L17032
      if (v10719) {	// L17033
        ap_uint<26> v10720 = hd12[2];	// L17034
        bool v10721 = v10506.write_nb(v10720);
	// L17035
        if (v10721) {	// L17036
          pop12[2] = 1;	// L17037
        }
      }
    }
    int32_t v10722 = idir12;	// L17041
    bool v10723 = v10722 == 3;	// L17042
    if (v10723) {	// L17043
      ap_int<26> v10724 = csd_pkt12;	// L17044
      bool v10725 = v10507.write_nb(v10724);
	// L17045
      if (v10725) {	// L17046
        inj_done12 = 1;	// L17047
      }
    } else {
      int32_t v10726 = hvld12[3];	// L17050
      bool v10727 = v10726 == 1;	// L17051
      int32_t v10728 = hit12[3];	// L17052
      bool v10729 = v10728 == 0;	// L17053
      bool v10730 = v10727 & v10729;	// L17054
      if (v10730) {	// L17055
        ap_uint<26> v10731 = hd12[3];	// L17056
        bool v10732 = v10507.write_nb(v10731);
	// L17057
        if (v10732) {	// L17058
          pop12[3] = 1;	// L17059
        }
      }
    }
    int32_t v10733 = crv_in12;	// L17063
    bool v10734 = v10733 >= 0;	// L17064
    if (v10734) {	// L17065
      int32_t v10735 = crv_in12;	// L17066
      int v10736 = v10735;	// L17067
      pop12[v10736] = 1;	// L17068
    }
    l_S_d_2_d50: for (int d50 = 0; d50 < 4; d50++) {	// L17070
      int32_t v10738 = pop12[d50];	// L17071
      bool v10739 = v10738 == 1;	// L17072
      if (v10739) {	// L17073
        l_S_sft_2_sft12: for (int sft12 = 0; sft12 < 1; sft12++) {	// L17074
          ap_uint<26> v10741 = rbuf12[d50][(sft12 + 1)];	// L17075
          rbuf12[d50][sft12] = v10741;	// L17076
        }
        uint8_t v10742 = rbcnt12[d50];	// L17078
        ap_int<33> v10743 = v10742;	// L17079
        ap_int<33> v10744 = v10743 - 1;	// L17080
        uint8_t v10745 = v10744;	// L17081
        rbcnt12[d50] = v10745;	// L17082
      }
    }
    int32_t v10746 = inj_done12;	// L17085
    bool v10747 = v10746 == 1;	// L17086
    if (v10747) {	// L17087
      csd_pkt12 = 0;	// L17088
    }
    ap_int<26> v10748 = o_crv12;	// L17090
    bool v10749;
    ap_int<26> v10749_tmp = v10748;
    v10749 = v10749_tmp[25];	// L17091
    int32_t v10750 = v10749;	// L17092
    crv_vld12 = v10750;	// L17093
    int32_t v10751 = crv_vld12;	// L17094
    bool v10752 = v10751 == 1;	// L17095
    if (v10752) {	// L17096
      crv_ever12 = 1;	// L17097
    }
    ap_int<26> v10753 = o_crv12;	// L17099
    int16_t v10754;
    ap_int<26> v10754_tmp = v10753;
    v10754 = v10754_tmp(15, 0);	// L17100
    half v10755;
    union { uint16_t from; half to;} _converter_v10754_to_v10755 = {};
    _converter_v10754_to_v10755.from = v10754;
    v10755 = _converter_v10754_to_v10755.to;	// L17101
    crv_data12 = v10755;	// L17102
    ap_int<26> v10756 = o_crv12;	// L17103
    ap_int<4> v10757;
    ap_int<26> v10757_tmp = v10756;
    v10757 = v10757_tmp(19, 16);	// L17104
    int32_t v10758 = v10757;	// L17105
    crv_addr12 = v10758;	// L17106
    ap_int<26> v10759 = o_crv12;	// L17107
    bool v10760;
    ap_int<26> v10760_tmp = v10759;
    v10760 = v10760_tmp[20];	// L17108
    int32_t v10761 = v10760;	// L17109
    crv_mode12 = v10761;	// L17110
    ap_int<26> v10762 = o_crv12;	// L17111
    int16_t v10763;
    ap_int<26> v10763_tmp = v10762;
    v10763 = v10763_tmp(15, 0);	// L17112
    int32_t v10764 = v10763;	// L17113
    crv_raw12 = v10764;	// L17114
    half rxv12[4];	// L17115
    for (int v10766 = 0; v10766 < 4; v10766++) {	// L17116
      rxv12[v10766] = 0.000000;	// L17116
    }
    int32_t rxvld12[4];	// L17117
    for (int v10768 = 0; v10768 < 4; v10768++) {	// L17118
      rxvld12[v10768] = 0;	// L17118
    }
    uint8_t v10769 = hold_cnt12[0];	// L17119
    int32_t v10770 = v10769;	// L17120
    bool v10771 = v10770 < 2;	// L17121
    if (v10771) {	// L17122
      ap_uint<17> v10772;
      bool v10773 = v10508.read_nb(v10772);
	// L17123
      ap_uint<17> sgn12;	// L17124
      sgn12 = v10772;	// L17125
      bool sqn12;	// L17126
      sqn12 = v10773;	// L17127
      bool v10776 = sqn12;	// L17128
      int32_t v10777 = v10776;	// L17129
      bool v10778 = v10777 == 1;	// L17130
      if (v10778) {	// L17131
        ap_int<17> v10779 = sgn12;	// L17132
        int16_t v10780;
        ap_int<17> v10780_tmp = v10779;
        v10780 = v10780_tmp(16, 1);	// L17133
        half v10781;
        union { uint16_t from; half to;} _converter_v10780_to_v10781 = {};
        _converter_v10780_to_v10781.from = v10780;
        v10781 = _converter_v10780_to_v10781.to;	// L17134
        rxv12[0] = v10781;	// L17135
        rxvld12[0] = 1;	// L17136
      }
    }
    uint8_t v10782 = hold_cnt12[1];	// L17139
    int32_t v10783 = v10782;	// L17140
    bool v10784 = v10783 < 2;	// L17141
    if (v10784) {	// L17142
      ap_uint<17> v10785;
      bool v10786 = v10509.read_nb(v10785);
	// L17143
      ap_uint<17> sgs12;	// L17144
      sgs12 = v10785;	// L17145
      bool sqs12;	// L17146
      sqs12 = v10786;	// L17147
      bool v10789 = sqs12;	// L17148
      int32_t v10790 = v10789;	// L17149
      bool v10791 = v10790 == 1;	// L17150
      if (v10791) {	// L17151
        ap_int<17> v10792 = sgs12;	// L17152
        int16_t v10793;
        ap_int<17> v10793_tmp = v10792;
        v10793 = v10793_tmp(16, 1);	// L17153
        half v10794;
        union { uint16_t from; half to;} _converter_v10793_to_v10794 = {};
        _converter_v10793_to_v10794.from = v10793;
        v10794 = _converter_v10793_to_v10794.to;	// L17154
        rxv12[1] = v10794;	// L17155
        rxvld12[1] = 1;	// L17156
      }
    }
    uint8_t v10795 = hold_cnt12[2];	// L17159
    int32_t v10796 = v10795;	// L17160
    bool v10797 = v10796 < 2;	// L17161
    if (v10797) {	// L17162
      ap_uint<17> v10798;
      bool v10799 = v10510.read_nb(v10798);
	// L17163
      ap_uint<17> sgw12;	// L17164
      sgw12 = v10798;	// L17165
      bool sqw12;	// L17166
      sqw12 = v10799;	// L17167
      bool v10802 = sqw12;	// L17168
      int32_t v10803 = v10802;	// L17169
      bool v10804 = v10803 == 1;	// L17170
      if (v10804) {	// L17171
        ap_int<17> v10805 = sgw12;	// L17172
        int16_t v10806;
        ap_int<17> v10806_tmp = v10805;
        v10806 = v10806_tmp(16, 1);	// L17173
        half v10807;
        union { uint16_t from; half to;} _converter_v10806_to_v10807 = {};
        _converter_v10806_to_v10807.from = v10806;
        v10807 = _converter_v10806_to_v10807.to;	// L17174
        rxv12[2] = v10807;	// L17175
        rxvld12[2] = 1;	// L17176
      }
    }
    uint8_t v10808 = hold_cnt12[3];	// L17179
    int32_t v10809 = v10808;	// L17180
    bool v10810 = v10809 < 2;	// L17181
    if (v10810) {	// L17182
      ap_uint<17> v10811;
      bool v10812 = v10511.read_nb(v10811);
	// L17183
      ap_uint<17> sge12;	// L17184
      sge12 = v10811;	// L17185
      bool sqe12;	// L17186
      sqe12 = v10812;	// L17187
      bool v10815 = sqe12;	// L17188
      int32_t v10816 = v10815;	// L17189
      bool v10817 = v10816 == 1;	// L17190
      if (v10817) {	// L17191
        ap_int<17> v10818 = sge12;	// L17192
        int16_t v10819;
        ap_int<17> v10819_tmp = v10818;
        v10819 = v10819_tmp(16, 1);	// L17193
        half v10820;
        union { uint16_t from; half to;} _converter_v10819_to_v10820 = {};
        _converter_v10819_to_v10820.from = v10819;
        v10820 = _converter_v10819_to_v10820.to;	// L17194
        rxv12[3] = v10820;	// L17195
        rxvld12[3] = 1;	// L17196
      }
    }
    l_S_d_4_d51: for (int d51 = 0; d51 < 4; d51++) {	// L17199
      int32_t v10822 = rxvld12[d51];	// L17200
      bool v10823 = v10822 == 1;	// L17201
      if (v10823) {	// L17202
        half v10824 = rxv12[d51];	// L17203
        uint8_t v10825 = hold_cnt12[d51];	// L17204
        int v10826 = v10825;	// L17205
        hold_v12[d51][v10826] = v10824;	// L17206
        uint8_t v10827 = hold_cnt12[d51];	// L17207
        ap_int<33> v10828 = v10827;	// L17208
        ap_int<33> v10829 = v10828 + 1;	// L17209
        uint8_t v10830 = v10829;	// L17210
        hold_cnt12[d51] = v10830;	// L17211
      }
    }
    ap_uint<17> tx_n12;	// L17214
    tx_n12 = 0;	// L17215
    ap_uint<17> tx_s12;	// L17216
    tx_s12 = 0;	// L17217
    ap_uint<17> tx_w12;	// L17218
    tx_w12 = 0;	// L17219
    ap_uint<17> tx_e12;	// L17220
    tx_e12 = 0;	// L17221
    uint8_t v10835 = sb_v12[0];	// L17222
    int32_t v10836 = v10835;	// L17223
    bool v10837 = v10836 == 1;	// L17224
    if (v10837) {	// L17225
      uint8_t v10838 = sb_ix12[0];	// L17226
      int v10839 = v10838;	// L17227
      half v10840 = resq12[v10839];	// L17228
      half wb12;
#pragma HLS dependence variable=wb12 type=inter dependent=false	// L17229
      wb12 = v10840;	// L17230
      uint8_t v10842 = sb_cmp12[0];	// L17231
      int32_t v10843 = v10842;	// L17232
      bool v10844 = v10843 == 1;	// L17233
      if (v10844) {	// L17234
        uint8_t v10845 = sb_ix12[0];	// L17235
        int v10846 = v10845;	// L17236
        uint8_t v10847 = cmpq12[v10846];	// L17237
        condition_reg12 = v10847;	// L17238
      }
      uint8_t v10848 = sb_rtr12[0];	// L17240
      int32_t v10849 = v10848;	// L17241
      bool v10850 = v10849 == 1;	// L17242
      if (v10850) {	// L17243
        uint8_t v10851 = sb_inj12[0];	// L17244
        int32_t v10852 = v10851;	// L17245
        bool v10853 = v10852 == 1;	// L17246
        ap_int<26> v10854 = csd_pkt12;	// L17247
        bool v10855;
        ap_int<26> v10855_tmp = v10854;
        v10855 = v10855_tmp[25];	// L17248
        int32_t v10856 = v10855;	// L17249
        bool v10857 = v10856 == 0;	// L17250
        bool v10858 = v10853 & v10857;	// L17251
        if (v10858) {	// L17252
          half v10859 = wb12;	// L17253
          uint16_t v10860;
          union { half from; uint16_t to;} _converter_v10859_to_v10860 = {};
          _converter_v10859_to_v10860.from = v10859;
          v10860 = _converter_v10859_to_v10860.to;	// L17254
          ap_int<26> v10861 = csd_pkt12;	// L17255
          ap_int<26> v10862;
          ap_int<26> v10862_tmp = v10861;
          v10862_tmp(15, 0) = v10860;
          v10862 = v10862_tmp;	// L17256
          csd_pkt12 = v10862;	// L17257
          uint8_t v10863 = sb_dst12[0];	// L17258
          ap_uint<4> v10864 = v10863;	// L17259
          ap_int<26> v10865 = csd_pkt12;	// L17260
          ap_int<26> v10866;
          ap_int<26> v10866_tmp = v10865;
          v10866_tmp(19, 16) = v10864;
          v10866 = v10866_tmp;	// L17261
          csd_pkt12 = v10866;	// L17262
          uint8_t v10867 = sb_id12[0];	// L17263
          ap_uint<4> v10868 = v10867;	// L17264
          ap_int<26> v10869 = csd_pkt12;	// L17265
          ap_int<26> v10870;
          ap_int<26> v10870_tmp = v10869;
          v10870_tmp(24, 21) = v10868;
          v10870 = v10870_tmp;	// L17266
          csd_pkt12 = v10870;	// L17267
          uint8_t v10871 = sb_rvld12[0];	// L17268
          bool v10872 = v10871;	// L17269
          ap_int<26> v10873 = csd_pkt12;	// L17270
          ap_int<26> v10874;
          ap_int<26> v10874_tmp = v10873;
          v10874_tmp[25] = v10872;          v10874 = v10874_tmp;	// L17271
          csd_pkt12 = v10874;	// L17272
          uint8_t v10875 = sb_dir12[0];	// L17273
          int32_t v10876 = v10875;	// L17274
          csd_dir12 = v10876;	// L17275
        }
      } else {
        uint8_t v10877 = sb_dst12[0];	// L17278
        int32_t v10878 = v10877;	// L17279
        bool v10879 = v10878 >= 12;	// L17280
        if (v10879) {	// L17281
          ap_uint<17> tw012;	// L17282
          tw012 = 0;	// L17283
          uint8_t v10881 = sb_rvld12[0];	// L17284
          bool v10882 = v10881;	// L17285
          ap_int<17> v10883 = tw012;	// L17286
          ap_int<17> v10884;
          ap_int<17> v10884_tmp = v10883;
          v10884_tmp[0] = v10882;          v10884 = v10884_tmp;	// L17287
          tw012 = v10884;	// L17288
          half v10885 = wb12;	// L17289
          uint16_t v10886;
          union { half from; uint16_t to;} _converter_v10885_to_v10886 = {};
          _converter_v10885_to_v10886.from = v10885;
          v10886 = _converter_v10885_to_v10886.to;	// L17290
          ap_int<17> v10887 = tw012;	// L17291
          ap_int<17> v10888;
          ap_int<17> v10888_tmp = v10887;
          v10888_tmp(16, 1) = v10886;
          v10888 = v10888_tmp;	// L17292
          tw012 = v10888;	// L17293
          uint8_t v10889 = sb_dst12[0];	// L17294
          int32_t v10890 = v10889;	// L17295
          int32_t v10891 = v10890 & 3;	// L17296
          bool v10892 = v10891 == 0;	// L17297
          if (v10892) {	// L17298
            ap_int<17> v10893 = tw012;	// L17299
            tx_n12 = v10893;	// L17300
          } else {
            uint8_t v10894 = sb_dst12[0];	// L17302
            int32_t v10895 = v10894;	// L17303
            int32_t v10896 = v10895 & 3;	// L17304
            bool v10897 = v10896 == 1;	// L17305
            if (v10897) {	// L17306
              ap_int<17> v10898 = tw012;	// L17307
              tx_s12 = v10898;	// L17308
            } else {
              uint8_t v10899 = sb_dst12[0];	// L17310
              int32_t v10900 = v10899;	// L17311
              int32_t v10901 = v10900 & 3;	// L17312
              bool v10902 = v10901 == 2;	// L17313
              if (v10902) {	// L17314
                ap_int<17> v10903 = tw012;	// L17315
                tx_w12 = v10903;	// L17316
              } else {
                ap_int<17> v10904 = tw012;	// L17318
                tx_e12 = v10904;	// L17319
              }
            }
          }
        } else {
          uint8_t v10905 = sb_rvld12[0];	// L17324
          int32_t v10906 = v10905;	// L17325
          bool v10907 = v10906 == 1;	// L17326
          if (v10907) {	// L17327
            uint8_t v10908 = sb_dst12[0];	// L17328
            int32_t v10909 = v10908;	// L17329
            bool v10910 = v10909 < 8;	// L17330
            int32_t v10911 = dsmask12;	// L17331
            int32_t v10912 = v10911 >> v10909;	// L17332
            int32_t v10913 = v10912 & 1;	// L17333
            bool v10914 = v10913 == 1;	// L17334
            bool v10915 = v10910 & v10914;	// L17335
            if (v10915) {	// L17336
              uint8_t v10916 = sb_dst12[0];	// L17337
              int v10917 = v10916;	// L17338
              int32_t v10918 = drf_full12[v10917];	// L17339
              bool v10919 = v10918 == 0;	// L17340
              if (v10919) {	// L17341
                half v10920 = wb12;	// L17342
                uint8_t v10921 = sb_dst12[0];	// L17343
                int v10922 = v10921;	// L17344
                drf12[v10922] = v10920;	// L17345
                uint8_t v10923 = sb_dst12[0];	// L17346
                int v10924 = v10923;	// L17347
                drf_full12[v10924] = 1;	// L17348
              }
            } else {
              half v10925 = wb12;	// L17351
              uint8_t v10926 = sb_dst12[0];	// L17352
              int32_t v10927 = v10926;	// L17353
              int32_t v10928 = v10927 & 7;	// L17354
              int v10929 = v10928;	// L17355
              drf12[v10929] = v10925;	// L17356
            }
          }
        }
      }
    }
    int32_t pc12;	// L17362
    pc12 = -1;	// L17363
    int8_t v10931 = fetch_en12;	// L17364
    int32_t v10932 = v10931;	// L17365
    bool v10933 = v10932 == 1;	// L17366
    if (v10933) {	// L17367
      int8_t v10934 = instr_cnt12;	// L17368
      int32_t v10935 = v10934;	// L17369
      pc12 = v10935;	// L17370
    }
    int8_t v10936 = fetch_en12;	// L17372
    int32_t v10937 = v10936;	// L17373
    bool v10938 = v10937 == 1;	// L17374
    if (v10938) {	// L17375
      fe_ever12 = 1;	// L17376
    }
    int32_t instr12;	// L17378
    instr12 = 0;	// L17379
    int32_t v10940 = pc12;	// L17380
    bool v10941 = v10940 >= 0;	// L17381
    if (v10941) {	// L17382
      int32_t v10942 = pc12;	// L17383
      int v10943 = v10942;	// L17384
      int32_t v10944 = irf12[v10943];	// L17385
      instr12 = v10944;	// L17386
    }
    int32_t v10945 = instr12;	// L17388
    int32_t v10946 = v10945 & 15;	// L17389
    int32_t op12;	// L17390
    op12 = v10946;	// L17391
    int32_t v10948 = instr12;	// L17392
    int32_t v10949 = v10948 >> 4;	// L17393
    int32_t v10950 = v10949 & 15;	// L17394
    int32_t dst12;	// L17395
    dst12 = v10950;	// L17396
    int32_t v10952 = instr12;	// L17397
    int32_t v10953 = v10952 >> 8;	// L17398
    int32_t v10954 = v10953 & 15;	// L17399
    int32_t s112;	// L17400
    s112 = v10954;	// L17401
    int32_t v10956 = instr12;	// L17402
    int32_t v10957 = v10956 >> 12;	// L17403
    int32_t v10958 = v10957 & 15;	// L17404
    int32_t s212;	// L17405
    s212 = v10958;	// L17406
    half a12;	// L17407
    a12 = 0.000000;	// L17408
    half b12;	// L17409
    b12 = 0.000000;	// L17410
    int32_t v10962 = s112;	// L17411
    bool v10963 = v10962 >= 12;	// L17412
    if (v10963) {	// L17413
      int32_t v10964 = s112;	// L17414
      int32_t v10965 = v10964 & 3;	// L17415
      int v10966 = v10965;	// L17416
      half v10967 = hold_v12[v10966][0];	// L17417
      a12 = v10967;	// L17418
    } else {
      int32_t v10968 = s112;	// L17420
      int v10969 = v10968;	// L17421
      half v10970 = drf12[v10969];	// L17422
      a12 = v10970;	// L17423
    }
    int32_t v10971 = s212;	// L17425
    bool v10972 = v10971 >= 12;	// L17426
    if (v10972) {	// L17427
      int32_t v10973 = s212;	// L17428
      int32_t v10974 = v10973 & 3;	// L17429
      int v10975 = v10974;	// L17430
      half v10976 = hold_v12[v10975][0];	// L17431
      b12 = v10976;	// L17432
    } else {
      int32_t v10977 = s212;	// L17434
      int v10978 = v10977;	// L17435
      half v10979 = drf12[v10978];	// L17436
      b12 = v10979;	// L17437
    }
    int32_t a_vld12;	// L17439
    a_vld12 = 1;	// L17440
    int32_t b_vld12;	// L17441
    b_vld12 = 1;	// L17442
    int32_t v10982 = s112;	// L17443
    bool v10983 = v10982 >= 12;	// L17444
    if (v10983) {	// L17445
      a_vld12 = 0;	// L17446
      int32_t v10984 = s112;	// L17447
      int32_t v10985 = v10984 & 3;	// L17448
      int v10986 = v10985;	// L17449
      uint8_t v10987 = hold_cnt12[v10986];	// L17450
      int32_t v10988 = v10987;	// L17451
      bool v10989 = v10988 > 0;	// L17452
      if (v10989) {	// L17453
        a_vld12 = 1;	// L17454
      }
    }
    int32_t v10990 = s212;	// L17457
    bool v10991 = v10990 >= 12;	// L17458
    if (v10991) {	// L17459
      b_vld12 = 0;	// L17460
      int32_t v10992 = s212;	// L17461
      int32_t v10993 = v10992 & 3;	// L17462
      int v10994 = v10993;	// L17463
      uint8_t v10995 = hold_cnt12[v10994];	// L17464
      int32_t v10996 = v10995;	// L17465
      bool v10997 = v10996 > 0;	// L17466
      if (v10997) {	// L17467
        b_vld12 = 1;	// L17468
      }
    }
    int32_t v10998 = s112;	// L17471
    bool v10999 = v10998 < 8;	// L17472
    int32_t v11000 = dsmask12;	// L17473
    int32_t v11001 = v11000 >> v10998;	// L17474
    int32_t v11002 = v11001 & 1;	// L17475
    bool v11003 = v11002 == 1;	// L17476
    bool v11004 = v10999 & v11003;	// L17477
    if (v11004) {	// L17478
      int32_t v11005 = s112;	// L17479
      int v11006 = v11005;	// L17480
      int32_t v11007 = drf_full12[v11006];	// L17481
      bool v11008 = v11007 == 0;	// L17482
      if (v11008) {	// L17483
        a_vld12 = 0;	// L17484
      }
    }
    int32_t v11009 = s212;	// L17487
    bool v11010 = v11009 < 8;	// L17488
    int32_t v11011 = dsmask12;	// L17489
    int32_t v11012 = v11011 >> v11009;	// L17490
    int32_t v11013 = v11012 & 1;	// L17491
    bool v11014 = v11013 == 1;	// L17492
    bool v11015 = v11010 & v11014;	// L17493
    if (v11015) {	// L17494
      int32_t v11016 = s212;	// L17495
      int v11017 = v11016;	// L17496
      int32_t v11018 = drf_full12[v11017];	// L17497
      bool v11019 = v11018 == 0;	// L17498
      if (v11019) {	// L17499
        b_vld12 = 0;	// L17500
      }
    }
    int32_t binop12;	// L17503
    binop12 = 0;	// L17504
    int32_t v11021 = op12;	// L17505
    bool v11022 = v11021 == 0;	// L17506
    bool v11023 = v11021 == 1;	// L17507
    bool v11024 = v11021 == 2;	// L17508
    bool v11025 = v11021 == 8;	// L17509
    bool v11026 = v11021 == 9;	// L17510
    bool v11027 = v11022 | v11023;	// L17511
    bool v11028 = v11027 | v11024;	// L17512
    bool v11029 = v11028 | v11025;	// L17513
    bool v11030 = v11029 | v11026;	// L17514
    if (v11030) {	// L17515
      binop12 = 1;	// L17516
    }
    int32_t raw12;	// L17518
    raw12 = 0;	// L17519
    int32_t cmp_busy12;	// L17520
    cmp_busy12 = 0;	// L17521
    l_S_k_5_k24: for (int k24 = 0; k24 < 4; k24++) {	// L17522
      uint8_t v11034 = sb_v12[(k24 + 1)];	// L17523
      int32_t v11035 = v11034;	// L17524
      bool v11036 = v11035 == 1;	// L17525
      uint8_t v11037 = sb_rtr12[(k24 + 1)];	// L17526
      int32_t v11038 = v11037;	// L17527
      bool v11039 = v11038 == 0;	// L17528
      uint8_t v11040 = sb_dst12[(k24 + 1)];	// L17529
      int32_t v11041 = v11040;	// L17530
      bool v11042 = v11041 < 12;	// L17531
      bool v11043 = v11036 & v11039;	// L17532
      bool v11044 = v11043 & v11042;	// L17533
      if (v11044) {	// L17534
        int32_t v11045 = s112;	// L17535
        bool v11046 = v11045 < 12;	// L17536
        uint8_t v11047 = sb_dst12[(k24 + 1)];	// L17537
        int32_t v11048 = v11047;	// L17538
        int32_t v11049 = v11048 & 7;	// L17539
        int32_t v11050 = v11045 & 7;	// L17540
        bool v11051 = v11049 == v11050;	// L17541
        bool v11052 = v11046 & v11051;	// L17542
        if (v11052) {	// L17543
          raw12 = 1;	// L17544
        }
        int32_t v11053 = binop12;	// L17546
        bool v11054 = v11053 == 1;	// L17547
        int32_t v11055 = s212;	// L17548
        bool v11056 = v11055 < 12;	// L17549
        uint8_t v11057 = sb_dst12[(k24 + 1)];	// L17550
        int32_t v11058 = v11057;	// L17551
        int32_t v11059 = v11058 & 7;	// L17552
        int32_t v11060 = v11055 & 7;	// L17553
        bool v11061 = v11059 == v11060;	// L17554
        bool v11062 = v11054 & v11056;	// L17555
        bool v11063 = v11062 & v11061;	// L17556
        if (v11063) {	// L17557
          raw12 = 1;	// L17558
        }
      }
      uint8_t v11064 = sb_v12[(k24 + 1)];	// L17561
      int32_t v11065 = v11064;	// L17562
      bool v11066 = v11065 == 1;	// L17563
      uint8_t v11067 = sb_cmp12[(k24 + 1)];	// L17564
      int32_t v11068 = v11067;	// L17565
      bool v11069 = v11068 == 1;	// L17566
      bool v11070 = v11066 & v11069;	// L17567
      if (v11070) {	// L17568
        cmp_busy12 = 1;	// L17569
      }
    }
    int32_t is_cond12;	// L17572
    is_cond12 = 0;	// L17573
    int32_t v11072 = op12;	// L17574
    bool v11073 = v11072 >= 12;	// L17575
    ap_int<33> v11074 = v11072;	// L17576
    bool v11075 = v11074 <= 15;	// L17577
    bool v11076 = v11073 & v11075;	// L17578
    if (v11076) {	// L17579
      is_cond12 = 1;	// L17580
    }
    int32_t grant12;	// L17582
    grant12 = 0;	// L17583
    int32_t v11078 = pc12;	// L17584
    bool v11079 = v11078 >= 0;	// L17585
    if (v11079) {	// L17586
      grant12 = 1;	// L17587
    }
    int32_t v11080 = pc12;	// L17589
    bool v11081 = v11080 >= 0;	// L17590
    int32_t v11082 = a_vld12;	// L17591
    bool v11083 = v11082 == 0;	// L17592
    int32_t v11084 = binop12;	// L17593
    bool v11085 = v11084 == 1;	// L17594
    int32_t v11086 = b_vld12;	// L17595
    bool v11087 = v11086 == 0;	// L17596
    bool v11088 = v11085 & v11087;	// L17597
    bool v11089 = v11083 | v11088;	// L17598
    bool v11090 = v11081 & v11089;	// L17599
    if (v11090) {	// L17600
      grant12 = 0;	// L17601
    }
    int32_t v11091 = pc12;	// L17603
    bool v11092 = v11091 >= 0;	// L17604
    int32_t v11093 = raw12;	// L17605
    bool v11094 = v11093 == 1;	// L17606
    int32_t v11095 = is_cond12;	// L17607
    bool v11096 = v11095 == 1;	// L17608
    int32_t v11097 = cmp_busy12;	// L17609
    bool v11098 = v11097 == 1;	// L17610
    bool v11099 = v11096 & v11098;	// L17611
    bool v11100 = v11094 | v11099;	// L17612
    bool v11101 = v11092 & v11100;	// L17613
    if (v11101) {	// L17614
      grant12 = 0;	// L17615
    }
    int32_t v11102 = grant12;	// L17617
    bool v11103 = v11102 == 1;	// L17618
    if (v11103) {	// L17619
      int8_t v11104 = instr_cnt12;	// L17620
      int32_t v11105 = cfg_isz12;	// L17621
      int32_t v11106 = v11104;	// L17622
      bool v11107 = v11106 == v11105;	// L17623
      if (v11107) {	// L17624
        instr_cnt12 = 0;	// L17625
        int8_t v11108 = iter_cnt12;	// L17626
        int32_t v11109 = cfg_itsz12;	// L17627
        ap_int<33> v11110 = v11109;	// L17628
        ap_int<33> v11111 = v11110 - 1;	// L17629
        ap_int<33> v11112 = v11108;	// L17630
        bool v11113 = v11112 == v11111;	// L17631
        if (v11113) {	// L17632
          fetch_en12 = 0;	// L17633
        } else {
          int8_t v11114 = iter_cnt12;	// L17635
          ap_int<33> v11115 = v11114;	// L17636
          ap_int<33> v11116 = v11115 + 1;	// L17637
          uint8_t v11117 = v11116;	// L17638
          iter_cnt12 = v11117;	// L17639
        }
      } else {
        int8_t v11118 = instr_cnt12;	// L17642
        ap_int<33> v11119 = v11118;	// L17643
        ap_int<33> v11120 = v11119 + 1;	// L17644
        uint8_t v11121 = v11120;	// L17645
        instr_cnt12 = v11121;	// L17646
      }
    }
    int32_t c112;	// L17649
    c112 = -1;	// L17650
    int32_t c212;	// L17651
    c212 = -1;	// L17652
    int32_t v11124 = grant12;	// L17653
    bool v11125 = v11124 == 1;	// L17654
    int32_t v11126 = s112;	// L17655
    bool v11127 = v11126 >= 12;	// L17656
    bool v11128 = v11125 & v11127;	// L17657
    if (v11128) {	// L17658
      int32_t v11129 = s112;	// L17659
      int32_t v11130 = v11129 & 3;	// L17660
      c112 = v11130;	// L17661
    }
    int32_t v11131 = grant12;	// L17663
    bool v11132 = v11131 == 1;	// L17664
    int32_t v11133 = s212;	// L17665
    bool v11134 = v11133 >= 12;	// L17666
    bool v11135 = v11132 & v11134;	// L17667
    if (v11135) {	// L17668
      int32_t v11136 = s212;	// L17669
      int32_t v11137 = v11136 & 3;	// L17670
      c212 = v11137;	// L17671
    }
    int32_t v11138 = c112;	// L17673
    bool v11139 = v11138 >= 0;	// L17674
    if (v11139) {	// L17675
      int32_t v11140 = c112;	// L17676
      int v11141 = v11140;	// L17677
      half v11142 = hold_v12[v11141][1];	// L17678
      hold_v12[v11141][0] = v11142;	// L17679
      int32_t v11143 = c112;	// L17680
      int v11144 = v11143;	// L17681
      uint8_t v11145 = hold_cnt12[v11144];	// L17682
      ap_int<33> v11146 = v11145;	// L17683
      ap_int<33> v11147 = v11146 - 1;	// L17684
      uint8_t v11148 = v11147;	// L17685
      hold_cnt12[v11144] = v11148;	// L17686
    }
    int32_t v11149 = c212;	// L17688
    bool v11150 = v11149 >= 0;	// L17689
    int32_t v11151 = c112;	// L17690
    bool v11152 = v11149 != v11151;	// L17691
    bool v11153 = v11150 & v11152;	// L17692
    if (v11153) {	// L17693
      int32_t v11154 = c212;	// L17694
      int v11155 = v11154;	// L17695
      half v11156 = hold_v12[v11155][1];	// L17696
      hold_v12[v11155][0] = v11156;	// L17697
      int32_t v11157 = c212;	// L17698
      int v11158 = v11157;	// L17699
      uint8_t v11159 = hold_cnt12[v11158];	// L17700
      ap_int<33> v11160 = v11159;	// L17701
      ap_int<33> v11161 = v11160 - 1;	// L17702
      uint8_t v11162 = v11161;	// L17703
      hold_cnt12[v11158] = v11162;	// L17704
    }
    int32_t v11163 = grant12;	// L17706
    bool v11164 = v11163 == 1;	// L17707
    int32_t v11165 = s112;	// L17708
    bool v11166 = v11165 < 8;	// L17709
    int32_t v11167 = dsmask12;	// L17710
    int32_t v11168 = v11167 >> v11165;	// L17711
    int32_t v11169 = v11168 & 1;	// L17712
    bool v11170 = v11169 == 1;	// L17713
    bool v11171 = v11164 & v11166;	// L17714
    bool v11172 = v11171 & v11170;	// L17715
    if (v11172) {	// L17716
      int32_t v11173 = s112;	// L17717
      int v11174 = v11173;	// L17718
      drf_full12[v11174] = 0;	// L17719
    }
    int32_t v11175 = grant12;	// L17721
    bool v11176 = v11175 == 1;	// L17722
    int32_t v11177 = s212;	// L17723
    bool v11178 = v11177 < 8;	// L17724
    int32_t v11179 = dsmask12;	// L17725
    int32_t v11180 = v11179 >> v11177;	// L17726
    int32_t v11181 = v11180 & 1;	// L17727
    bool v11182 = v11181 == 1;	// L17728
    bool v11183 = v11176 & v11178;	// L17729
    bool v11184 = v11183 & v11182;	// L17730
    if (v11184) {	// L17731
      int32_t v11185 = s212;	// L17732
      int v11186 = v11185;	// L17733
      drf_full12[v11186] = 0;	// L17734
    }
    half res12;
#pragma HLS dependence variable=res12 type=inter dependent=false	// L17736
    res12 = 0.000000;	// L17737
    int32_t v11188 = op12;	// L17738
    bool v11189 = v11188 == 0;	// L17739
    if (v11189) {	// L17740
      half v11190 = a12;	// L17741
      half v11191 = b12;	// L17742
      half v11192 = v11190 + v11191;	// L17743
      res12 = v11192;	// L17744
    } else {
      int32_t v11193 = op12;	// L17746
      bool v11194 = v11193 == 1;	// L17747
      if (v11194) {	// L17748
        half v11195 = a12;	// L17749
        half v11196 = b12;	// L17750
        half v11197 = v11195 - v11196;	// L17751
        res12 = v11197;	// L17752
      } else {
        int32_t v11198 = op12;	// L17754
        bool v11199 = v11198 == 2;	// L17755
        if (v11199) {	// L17756
          half v11200 = a12;	// L17757
          half v11201 = b12;	// L17758
          half v11202 = v11200 * v11201;	// L17759
          res12 = v11202;	// L17760
        } else {
          int32_t v11203 = op12;	// L17762
          bool v11204 = v11203 == 8;	// L17763
          if (v11204) {	// L17764
            half v11205 = a12;	// L17765
            half v11206 = b12;	// L17766
            bool v11207 = v11205 >= v11206;	// L17767
            if (v11207) {	// L17768
              res12 = 1.000000;	// L17769
            } else {
              res12 = -1.000000;	// L17771
            }
          } else {
            int32_t v11208 = op12;	// L17774
            bool v11209 = v11208 == 9;	// L17775
            if (v11209) {	// L17776
              half v11210 = a12;	// L17777
              half v11211 = b12;	// L17778
              bool v11212 = v11210 < v11211;	// L17779
              if (v11212) {	// L17780
                res12 = 1.000000;	// L17781
              } else {
                res12 = -1.000000;	// L17783
              }
            } else {
              half v11213 = a12;	// L17786
              res12 = v11213;	// L17787
            }
          }
        }
      }
    }
    int32_t v11214 = a_vld12;	// L17793
    int32_t res_vld12;	// L17794
    res_vld12 = v11214;	// L17795
    int32_t v11216 = op12;	// L17796
    bool v11217 = v11216 == 0;	// L17797
    bool v11218 = v11216 == 1;	// L17798
    bool v11219 = v11216 == 2;	// L17799
    bool v11220 = v11216 == 8;	// L17800
    bool v11221 = v11216 == 9;	// L17801
    bool v11222 = v11217 | v11218;	// L17802
    bool v11223 = v11222 | v11219;	// L17803
    bool v11224 = v11223 | v11220;	// L17804
    bool v11225 = v11224 | v11221;	// L17805
    if (v11225) {	// L17806
      int32_t v11226 = a_vld12;	// L17807
      int32_t v11227 = b_vld12;	// L17808
      int64_t v11228 = v11226;	// L17809
      int64_t v11229 = v11227;	// L17810
      int64_t v11230 = v11228 * v11229;	// L17811
      int32_t v11231 = v11230;	// L17812
      res_vld12 = v11231;	// L17813
    }
    int32_t v11232 = grant12;	// L17815
    bool v11233 = v11232 == 0;	// L17816
    if (v11233) {	// L17817
      res_vld12 = 0;	// L17818
    }
    int32_t is_rtr12;	// L17820
    is_rtr12 = 0;	// L17821
    int32_t v11235 = op12;	// L17822
    bool v11236 = v11235 >= 4;	// L17823
    ap_int<33> v11237 = v11235;	// L17824
    bool v11238 = v11237 <= 7;	// L17825
    bool v11239 = v11236 & v11238;	// L17826
    if (v11239) {	// L17827
      is_rtr12 = 1;	// L17828
    }
    l_S_k_6_k25: for (int k25 = 0; k25 < 4; k25++) {	// L17830
      uint8_t v11241 = sb_v12[(k25 + 1)];	// L17831
      sb_v12[k25] = v11241;	// L17832
      uint8_t v11242 = sb_dst12[(k25 + 1)];	// L17833
      sb_dst12[k25] = v11242;	// L17834
      uint8_t v11243 = sb_cmp12[(k25 + 1)];	// L17835
      sb_cmp12[k25] = v11243;	// L17836
      uint8_t v11244 = sb_rtr12[(k25 + 1)];	// L17837
      sb_rtr12[k25] = v11244;	// L17838
      uint8_t v11245 = sb_inj12[(k25 + 1)];	// L17839
      sb_inj12[k25] = v11245;	// L17840
      uint8_t v11246 = sb_dir12[(k25 + 1)];	// L17841
      sb_dir12[k25] = v11246;	// L17842
      uint8_t v11247 = sb_id12[(k25 + 1)];	// L17843
      sb_id12[k25] = v11247;	// L17844
      uint8_t v11248 = sb_rvld12[(k25 + 1)];	// L17845
      sb_rvld12[k25] = v11248;	// L17846
      uint8_t v11249 = sb_ix12[(k25 + 1)];	// L17847
      sb_ix12[k25] = v11249;	// L17848
    }
    sb_v12[4] = 0;	// L17850
    int32_t v11250 = grant12;	// L17851
    bool v11251 = v11250 == 1;	// L17852
    if (v11251) {	// L17853
      half v11252 = res12;	// L17854
      int8_t v11253 = resq_wr12;	// L17855
      int v11254 = v11253;	// L17856
      resq12[v11254] = v11252;	// L17857
      int32_t cq12;	// L17858
      cq12 = 0;	// L17859
      int32_t v11256 = op12;	// L17860
      bool v11257 = v11256 == 8;	// L17861
      if (v11257) {	// L17862
        half v11258 = a12;	// L17863
        half v11259 = b12;	// L17864
        bool v11260 = v11258 >= v11259;	// L17865
        if (v11260) {	// L17866
          cq12 = 1;	// L17867
        }
      }
      int32_t v11261 = op12;	// L17870
      bool v11262 = v11261 == 9;	// L17871
      if (v11262) {	// L17872
        half v11263 = a12;	// L17873
        half v11264 = b12;	// L17874
        bool v11265 = v11263 < v11264;	// L17875
        if (v11265) {	// L17876
          cq12 = 1;	// L17877
        }
      }
      int32_t v11266 = cq12;	// L17880
      uint8_t v11267 = v11266;	// L17881
      int8_t v11268 = resq_wr12;	// L17882
      int v11269 = v11268;	// L17883
      cmpq12[v11269] = v11267;	// L17884
      sb_v12[4] = 1;	// L17885
      int32_t v11270 = dst12;	// L17886
      uint8_t v11271 = v11270;	// L17887
      sb_dst12[4] = v11271;	// L17888
      int8_t v11272 = resq_wr12;	// L17889
      sb_ix12[4] = v11272;	// L17890
      sb_cmp12[4] = 0;	// L17891
      int32_t v11273 = op12;	// L17892
      bool v11274 = v11273 == 8;	// L17893
      bool v11275 = v11273 == 9;	// L17894
      bool v11276 = v11274 | v11275;	// L17895
      if (v11276) {	// L17896
        sb_cmp12[4] = 1;	// L17897
      }
      int32_t v11277 = is_rtr12;	// L17899
      int32_t rtrf12;	// L17900
      rtrf12 = v11277;	// L17901
      int32_t v11279 = is_cond12;	// L17902
      bool v11280 = v11279 == 1;	// L17903
      if (v11280) {	// L17904
        rtrf12 = 1;	// L17905
      }
      int32_t v11281 = rtrf12;	// L17907
      uint8_t v11282 = v11281;	// L17908
      sb_rtr12[4] = v11282;	// L17909
      int32_t v11283 = is_rtr12;	// L17910
      int32_t inj12;	// L17911
      inj12 = v11283;	// L17912
      int32_t v11285 = is_cond12;	// L17913
      bool v11286 = v11285 == 1;	// L17914
      int8_t v11287 = condition_reg12;	// L17915
      int32_t v11288 = v11287;	// L17916
      bool v11289 = v11288 == 1;	// L17917
      bool v11290 = v11286 & v11289;	// L17918
      if (v11290) {	// L17919
        inj12 = 1;	// L17920
      }
      int32_t v11291 = inj12;	// L17922
      uint8_t v11292 = v11291;	// L17923
      sb_inj12[4] = v11292;	// L17924
      int32_t v11293 = op12;	// L17925
      int32_t v11294 = v11293 & 3;	// L17926
      uint8_t v11295 = v11294;	// L17927
      sb_dir12[4] = v11295;	// L17928
      int32_t v11296 = s212;	// L17929
      uint8_t v11297 = v11296;	// L17930
      sb_id12[4] = v11297;	// L17931
      int32_t v11298 = res_vld12;	// L17932
      uint8_t v11299 = v11298;	// L17933
      sb_rvld12[4] = v11299;	// L17934
      int8_t v11300 = resq_wr12;	// L17935
      ap_int<33> v11301 = v11300;	// L17936
      ap_int<33> v11302 = v11301 + 1;	// L17937
      ap_int<33> v11303 = v11302 & 7;	// L17938
      uint8_t v11304 = v11303;	// L17939
      resq_wr12 = v11304;	// L17940
    }
    ap_int<17> v11305 = tx_n12;	// L17942
    txn_r12 = v11305;	// L17943
    ap_int<17> v11306 = tx_s12;	// L17944
    txs_r12 = v11306;	// L17945
    ap_int<17> v11307 = tx_w12;	// L17946
    txw_r12 = v11307;	// L17947
    ap_int<17> v11308 = tx_e12;	// L17948
    txe_r12 = v11308;	// L17949
    int32_t v11309 = crv_vld12;	// L17950
    bool v11310 = v11309 == 1;	// L17951
    if (v11310) {	// L17952
      int32_t v11311 = crv_mode12;	// L17953
      bool v11312 = v11311 == 1;	// L17954
      if (v11312) {	// L17955
        int32_t v11313 = crv_addr12;	// L17956
        int32_t v11314 = v11313 >> 3;	// L17957
        int32_t v11315 = v11314 & 1;	// L17958
        bool v11316 = v11315 == 1;	// L17959
        if (v11316) {	// L17960
          int32_t v11317 = crv_raw12;	// L17961
          int32_t v11318 = crv_addr12;	// L17962
          int32_t v11319 = v11318 & 7;	// L17963
          int v11320 = v11319;	// L17964
          irf12[v11320] = v11317;	// L17965
        } else {
          int32_t v11321 = crv_addr12;	// L17967
          bool v11322 = v11321 == 0;	// L17968
          if (v11322) {	// L17969
            int32_t v11323 = crv_raw12;	// L17970
            int32_t v11324 = v11323 & 255;	// L17971
            dsmask12 = v11324;	// L17972
            int32_t v11325 = crv_raw12;	// L17973
            int32_t v11326 = v11325 >> 8;	// L17974
            int32_t v11327 = v11326 & 7;	// L17975
            cfg_isz12 = v11327;	// L17976
            int32_t v11328 = crv_raw12;	// L17977
            int32_t v11329 = v11328 >> 15;	// L17978
            int32_t v11330 = v11329 & 1;	// L17979
            bool v11331 = v11330 == 1;	// L17980
            if (v11331) {	// L17981
              fetch_en12 = 1;	// L17982
              instr_cnt12 = 0;	// L17983
              iter_cnt12 = 0;	// L17984
            }
          } else {
            int32_t v11332 = crv_addr12;	// L17987
            bool v11333 = v11332 == 1;	// L17988
            if (v11333) {	// L17989
              int32_t v11334 = crv_raw12;	// L17990
              int32_t v11335 = v11334 & 255;	// L17991
              cfg_itsz12 = v11335;	// L17992
            }
          }
        }
      } else {
        int32_t v11336 = crv_addr12;	// L17997
        bool v11337 = v11336 < 8;	// L17998
        int32_t v11338 = dsmask12;	// L17999
        int32_t v11339 = v11338 >> v11336;	// L18000
        int32_t v11340 = v11339 & 1;	// L18001
        bool v11341 = v11340 == 1;	// L18002
        bool v11342 = v11337 & v11341;	// L18003
        if (v11342) {	// L18004
          int32_t v11343 = crv_addr12;	// L18005
          int v11344 = v11343;	// L18006
          int32_t v11345 = drf_full12[v11344];	// L18007
          bool v11346 = v11345 == 0;	// L18008
          if (v11346) {	// L18009
            half v11347 = crv_data12;	// L18010
            int32_t v11348 = crv_addr12;	// L18011
            int v11349 = v11348;	// L18012
            drf12[v11349] = v11347;	// L18013
            int32_t v11350 = crv_addr12;	// L18014
            int v11351 = v11350;	// L18015
            drf_full12[v11351] = 1;	// L18016
          }
        } else {
          half v11352 = crv_data12;	// L18019
          int32_t v11353 = crv_addr12;	// L18020
          int v11354 = v11353;	// L18021
          drf12[v11354] = v11352;	// L18022
        }
      }
    }
    ap_int<17> v11355 = txe_r12;	// L18026
    bool v11356;
    ap_int<17> v11356_tmp = v11355;
    v11356 = v11356_tmp[0];	// L18027
    int32_t v11357 = v11356;	// L18028
    bool v11358 = v11357 == 1;	// L18029
    if (v11358) {	// L18030
      ap_int<17> v11359 = txe_r12;	// L18031
      v10512.write(v11359);	// L18032
    }
    ap_int<17> v11360 = txw_r12;	// L18034
    bool v11361;
    ap_int<17> v11361_tmp = v11360;
    v11361 = v11361_tmp[0];	// L18035
    int32_t v11362 = v11361;	// L18036
    bool v11363 = v11362 == 1;	// L18037
    if (v11363) {	// L18038
      ap_int<17> v11364 = txw_r12;	// L18039
      v10513.write(v11364);	// L18040
    }
    ap_int<17> v11365 = txs_r12;	// L18042
    bool v11366;
    ap_int<17> v11366_tmp = v11365;
    v11366 = v11366_tmp[0];	// L18043
    int32_t v11367 = v11366;	// L18044
    bool v11368 = v11367 == 1;	// L18045
    if (v11368) {	// L18046
      ap_int<17> v11369 = txs_r12;	// L18047
      v10514.write(v11369);	// L18048
    }
    ap_int<17> v11370 = txn_r12;	// L18050
    bool v11371;
    ap_int<17> v11371_tmp = v11370;
    v11371 = v11371_tmp[0];	// L18051
    int32_t v11372 = v11371;	// L18052
    bool v11373 = v11372 == 1;	// L18053
    if (v11373) {	// L18054
      ap_int<17> v11374 = txn_r12;	// L18055
      v10515.write(v11374);	// L18056
    }
  }
}

void node_3_1(
  hls::stream< ap_uint<26> >& v11375,
  hls::stream< ap_uint<26> >& v11376,
  hls::stream< ap_uint<26> >& v11377,
  hls::stream< ap_uint<26> >& v11378,
  hls::stream< ap_uint<26> >& v11379,
  hls::stream< ap_uint<26> >& v11380,
  hls::stream< ap_uint<26> >& v11381,
  hls::stream< ap_uint<26> >& v11382,
  hls::stream< ap_uint<17> >& v11383,
  hls::stream< ap_uint<17> >& v11384,
  hls::stream< ap_uint<17> >& v11385,
  hls::stream< ap_uint<17> >& v11386,
  hls::stream< ap_uint<17> >& v11387,
  hls::stream< ap_uint<17> >& v11388,
  hls::stream< ap_uint<17> >& v11389,
  hls::stream< ap_uint<17> >& v11390
) {	// L18061
  int32_t irf13[8];	// L18094
  #pragma HLS array_partition variable=irf13 complete dim=1

  for (int v11392 = 0; v11392 < 8; v11392++) {	// L18095
    irf13[v11392] = 0;	// L18095
  }
  half drf13[8];	// L18096
  #pragma HLS array_partition variable=drf13 complete dim=1

  for (int v11394 = 0; v11394 < 8; v11394++) {	// L18097
    drf13[v11394] = 0.000000;	// L18097
  }
  int32_t drf_full13[8];	// L18098
  #pragma HLS array_partition variable=drf_full13 complete dim=1

  for (int v11396 = 0; v11396 < 8; v11396++) {	// L18099
    drf_full13[v11396] = 0;	// L18099
  }
  int32_t dsmask13;	// L18100
  dsmask13 = 0;	// L18101
  int32_t crv_vld13;	// L18102
  crv_vld13 = 0;	// L18103
  half crv_data13;	// L18104
  crv_data13 = 0.000000;	// L18105
  int32_t crv_addr13;	// L18106
  crv_addr13 = 0;	// L18107
  int32_t crv_mode13;	// L18108
  crv_mode13 = 0;	// L18109
  int32_t crv_raw13;	// L18110
  crv_raw13 = 0;	// L18111
  int32_t csd_vld13;	// L18112
  csd_vld13 = 0;	// L18113
  ap_uint<26> csd_pkt13;	// L18114
  csd_pkt13 = 0;	// L18115
  int32_t csd_dir13;	// L18116
  csd_dir13 = 0;	// L18117
  int32_t row_id13;	// L18118
  row_id13 = 3;	// L18119
  int32_t col_id13;	// L18120
  col_id13 = 1;	// L18121
  ap_uint<17> txn_r13;	// L18122
  txn_r13 = 0;	// L18123
  ap_uint<17> txs_r13;	// L18124
  txs_r13 = 0;	// L18125
  ap_uint<17> txw_r13;	// L18126
  txw_r13 = 0;	// L18127
  ap_uint<17> txe_r13;	// L18128
  txe_r13 = 0;	// L18129
  half hold_v13[4][2];	// L18130
  #pragma HLS array_partition variable=hold_v13 complete dim=1
  #pragma HLS array_partition variable=hold_v13 complete dim=2

  for (int v11413 = 0; v11413 < 4; v11413++) {	// L18131
    for (int v11414 = 0; v11414 < 2; v11414++) {	// L18131
      hold_v13[v11413][v11414] = 0.000000;	// L18131
    }
  }
  uint8_t hold_cnt13[4];	// L18132
  #pragma HLS array_partition variable=hold_cnt13 complete dim=1

  for (int v11416 = 0; v11416 < 4; v11416++) {	// L18133
    hold_cnt13[v11416] = 0;	// L18133
  }
  int32_t crv_ever13;	// L18134
  crv_ever13 = 0;	// L18135
  int32_t fe_ever13;	// L18136
  fe_ever13 = 0;	// L18137
  ap_uint<26> rbuf13[4][2];	// L18138
  #pragma HLS array_partition variable=rbuf13 complete dim=1
  #pragma HLS array_partition variable=rbuf13 complete dim=2

  for (int v11420 = 0; v11420 < 4; v11420++) {	// L18139
    for (int v11421 = 0; v11421 < 2; v11421++) {	// L18139
      rbuf13[v11420][v11421] = 0;	// L18139
    }
  }
  uint8_t rbcnt13[4];	// L18140
  #pragma HLS array_partition variable=rbcnt13 complete dim=1

  for (int v11423 = 0; v11423 < 4; v11423++) {	// L18141
    rbcnt13[v11423] = 0;	// L18141
  }
  int32_t cfg_isz13;	// L18142
  cfg_isz13 = 0;	// L18143
  int32_t cfg_itsz13;	// L18144
  cfg_itsz13 = 0;	// L18145
  uint8_t fetch_en13;	// L18146
  fetch_en13 = 0;	// L18147
  uint8_t instr_cnt13;	// L18148
  instr_cnt13 = 0;	// L18149
  uint8_t iter_cnt13;	// L18150
  iter_cnt13 = 0;	// L18151
  uint8_t condition_reg13;	// L18152
  condition_reg13 = 0;	// L18153
  uint8_t sb_v13[5];	// L18154
  #pragma HLS array_partition variable=sb_v13 complete dim=1

  for (int v11431 = 0; v11431 < 5; v11431++) {	// L18155
    sb_v13[v11431] = 0;	// L18155
  }
  uint8_t sb_dst13[5];	// L18156
  #pragma HLS array_partition variable=sb_dst13 complete dim=1

  for (int v11433 = 0; v11433 < 5; v11433++) {	// L18157
    sb_dst13[v11433] = 0;	// L18157
  }
  uint8_t sb_cmp13[5];	// L18158
  #pragma HLS array_partition variable=sb_cmp13 complete dim=1

  for (int v11435 = 0; v11435 < 5; v11435++) {	// L18159
    sb_cmp13[v11435] = 0;	// L18159
  }
  uint8_t sb_rtr13[5];	// L18160
  #pragma HLS array_partition variable=sb_rtr13 complete dim=1

  for (int v11437 = 0; v11437 < 5; v11437++) {	// L18161
    sb_rtr13[v11437] = 0;	// L18161
  }
  uint8_t sb_inj13[5];	// L18162
  #pragma HLS array_partition variable=sb_inj13 complete dim=1

  for (int v11439 = 0; v11439 < 5; v11439++) {	// L18163
    sb_inj13[v11439] = 0;	// L18163
  }
  uint8_t sb_dir13[5];	// L18164
  #pragma HLS array_partition variable=sb_dir13 complete dim=1

  for (int v11441 = 0; v11441 < 5; v11441++) {	// L18165
    sb_dir13[v11441] = 0;	// L18165
  }
  uint8_t sb_id13[5];	// L18166
  #pragma HLS array_partition variable=sb_id13 complete dim=1

  for (int v11443 = 0; v11443 < 5; v11443++) {	// L18167
    sb_id13[v11443] = 0;	// L18167
  }
  uint8_t sb_rvld13[5];	// L18168
  #pragma HLS array_partition variable=sb_rvld13 complete dim=1

  for (int v11445 = 0; v11445 < 5; v11445++) {	// L18169
    sb_rvld13[v11445] = 0;	// L18169
  }
  uint8_t sb_ix13[5];	// L18170
  #pragma HLS array_partition variable=sb_ix13 complete dim=1

  for (int v11447 = 0; v11447 < 5; v11447++) {	// L18171
    sb_ix13[v11447] = 0;	// L18171
  }
  half resq13[8];	// L18172
  #pragma HLS array_partition variable=resq13 complete dim=1
#pragma HLS dependence variable=resq13 type=inter dependent=false

  for (int v11449 = 0; v11449 < 8; v11449++) {	// L18173
    resq13[v11449] = 0.000000;	// L18173
  }
  uint8_t cmpq13[8];	// L18174
  #pragma HLS array_partition variable=cmpq13 complete dim=1
#pragma HLS dependence variable=cmpq13 type=inter dependent=false

  for (int v11451 = 0; v11451 < 8; v11451++) {	// L18175
    cmpq13[v11451] = 0;	// L18175
  }
  uint8_t resq_wr13;	// L18176
  resq_wr13 = 0;	// L18177
  l_S_t_0_t13: for (int t13 = 0; t13 < 374; t13++) {	// L18178
  #pragma HLS pipeline II=1
    ap_uint<26> p_w13;	// L18179
    p_w13 = 0;	// L18180
    ap_uint<26> p_e13;	// L18181
    p_e13 = 0;	// L18182
    ap_uint<26> p_n13;	// L18183
    p_n13 = 0;	// L18184
    ap_uint<26> p_s13;	// L18185
    p_s13 = 0;	// L18186
    uint8_t v11458 = rbcnt13[0];	// L18187
    int32_t v11459 = v11458;	// L18188
    bool v11460 = v11459 < 2;	// L18189
    if (v11460) {	// L18190
      ap_uint<26> v11461;
      bool v11462 = v11375.read_nb(v11461);
	// L18191
      ap_uint<26> gw13;	// L18192
      gw13 = v11461;	// L18193
      bool okw13;	// L18194
      okw13 = v11462;	// L18195
      bool v11465 = okw13;	// L18196
      if (v11465) {	// L18197
        ap_int<26> v11466 = gw13;	// L18198
        p_w13 = v11466;	// L18199
      }
    }
    uint8_t v11467 = rbcnt13[1];	// L18202
    int32_t v11468 = v11467;	// L18203
    bool v11469 = v11468 < 2;	// L18204
    if (v11469) {	// L18205
      ap_uint<26> v11470;
      bool v11471 = v11376.read_nb(v11470);
	// L18206
      ap_uint<26> ge13;	// L18207
      ge13 = v11470;	// L18208
      bool oke13;	// L18209
      oke13 = v11471;	// L18210
      bool v11474 = oke13;	// L18211
      if (v11474) {	// L18212
        ap_int<26> v11475 = ge13;	// L18213
        p_e13 = v11475;	// L18214
      }
    }
    uint8_t v11476 = rbcnt13[2];	// L18217
    int32_t v11477 = v11476;	// L18218
    bool v11478 = v11477 < 2;	// L18219
    if (v11478) {	// L18220
      ap_uint<26> v11479;
      bool v11480 = v11377.read_nb(v11479);
	// L18221
      ap_uint<26> gn13;	// L18222
      gn13 = v11479;	// L18223
      bool okn13;	// L18224
      okn13 = v11480;	// L18225
      bool v11483 = okn13;	// L18226
      if (v11483) {	// L18227
        ap_int<26> v11484 = gn13;	// L18228
        p_n13 = v11484;	// L18229
      }
    }
    uint8_t v11485 = rbcnt13[3];	// L18232
    int32_t v11486 = v11485;	// L18233
    bool v11487 = v11486 < 2;	// L18234
    if (v11487) {	// L18235
      ap_uint<26> v11488;
      bool v11489 = v11378.read_nb(v11488);
	// L18236
      ap_uint<26> gs13;	// L18237
      gs13 = v11488;	// L18238
      bool oks13;	// L18239
      oks13 = v11489;	// L18240
      bool v11492 = oks13;	// L18241
      if (v11492) {	// L18242
        ap_int<26> v11493 = gs13;	// L18243
        p_s13 = v11493;	// L18244
      }
    }
    ap_uint<26> fin13[4];	// L18247
    for (int v11495 = 0; v11495 < 4; v11495++) {	// L18248
      fin13[v11495] = 0;	// L18248
    }
    ap_int<26> v11496 = p_w13;	// L18249
    fin13[0] = v11496;	// L18250
    ap_int<26> v11497 = p_e13;	// L18251
    fin13[1] = v11497;	// L18252
    ap_int<26> v11498 = p_n13;	// L18253
    fin13[2] = v11498;	// L18254
    ap_int<26> v11499 = p_s13;	// L18255
    fin13[3] = v11499;	// L18256
    l_S_d_0_d52: for (int d52 = 0; d52 < 4; d52++) {	// L18257
      ap_uint<26> v11501 = fin13[d52];	// L18258
      bool v11502;
      ap_int<26> v11502_tmp = v11501;
      v11502 = v11502_tmp[25];	// L18259
      int32_t v11503 = v11502;	// L18260
      bool v11504 = v11503 == 1;	// L18261
      uint8_t v11505 = rbcnt13[d52];	// L18262
      int32_t v11506 = v11505;	// L18263
      bool v11507 = v11506 < 2;	// L18264
      bool v11508 = v11504 & v11507;	// L18265
      if (v11508) {	// L18266
        ap_uint<26> v11509 = fin13[d52];	// L18267
        uint8_t v11510 = rbcnt13[d52];	// L18268
        int v11511 = v11510;	// L18269
        rbuf13[d52][v11511] = v11509;	// L18270
        uint8_t v11512 = rbcnt13[d52];	// L18271
        ap_int<33> v11513 = v11512;	// L18272
        ap_int<33> v11514 = v11513 + 1;	// L18273
        uint8_t v11515 = v11514;	// L18274
        rbcnt13[d52] = v11515;	// L18275
      }
    }
    ap_uint<26> hd13[4];	// L18278
    for (int v11517 = 0; v11517 < 4; v11517++) {	// L18279
      hd13[v11517] = 0;	// L18279
    }
    int32_t hvld13[4];	// L18280
    for (int v11519 = 0; v11519 < 4; v11519++) {	// L18281
      hvld13[v11519] = 0;	// L18281
    }
    int32_t hit13[4];	// L18282
    for (int v11521 = 0; v11521 < 4; v11521++) {	// L18283
      hit13[v11521] = 0;	// L18283
    }
    int32_t axis13[4];	// L18284
    for (int v11523 = 0; v11523 < 4; v11523++) {	// L18285
      axis13[v11523] = 0;	// L18285
    }
    int32_t v11524 = col_id13;	// L18286
    axis13[0] = v11524;	// L18287
    int32_t v11525 = col_id13;	// L18288
    axis13[1] = v11525;	// L18289
    int32_t v11526 = row_id13;	// L18290
    axis13[2] = v11526;	// L18291
    int32_t v11527 = row_id13;	// L18292
    axis13[3] = v11527;	// L18293
    l_S_d_1_d53: for (int d53 = 0; d53 < 4; d53++) {	// L18294
      uint8_t v11529 = rbcnt13[d53];	// L18295
      int32_t v11530 = v11529;	// L18296
      bool v11531 = v11530 > 0;	// L18297
      if (v11531) {	// L18298
        ap_uint<26> v11532 = rbuf13[d53][0];	// L18299
        hd13[d53] = v11532;	// L18300
        hvld13[d53] = 1;	// L18301
        ap_uint<26> v11533 = hd13[d53];	// L18302
        ap_int<4> v11534;
        ap_int<26> v11534_tmp = v11533;
        v11534 = v11534_tmp(24, 21);	// L18303
        int32_t v11535 = axis13[d53];	// L18304
        int32_t v11536 = v11534;	// L18305
        bool v11537 = v11536 == v11535;	// L18306
        if (v11537) {	// L18307
          hit13[d53] = 1;	// L18308
        }
      }
    }
    ap_uint<26> o_crv13;	// L18312
    o_crv13 = 0;	// L18313
    int32_t crv_in13;	// L18314
    crv_in13 = -1;	// L18315
    int32_t v11540 = hit13[3];	// L18316
    bool v11541 = v11540 == 1;	// L18317
    if (v11541) {	// L18318
      ap_uint<26> v11542 = hd13[3];	// L18319
      o_crv13 = v11542;	// L18320
      crv_in13 = 3;	// L18321
    } else {
      int32_t v11543 = hit13[2];	// L18323
      bool v11544 = v11543 == 1;	// L18324
      if (v11544) {	// L18325
        ap_uint<26> v11545 = hd13[2];	// L18326
        o_crv13 = v11545;	// L18327
        crv_in13 = 2;	// L18328
      } else {
        int32_t v11546 = hit13[1];	// L18330
        bool v11547 = v11546 == 1;	// L18331
        if (v11547) {	// L18332
          ap_uint<26> v11548 = hd13[1];	// L18333
          o_crv13 = v11548;	// L18334
          crv_in13 = 1;	// L18335
        } else {
          int32_t v11549 = hit13[0];	// L18337
          bool v11550 = v11549 == 1;	// L18338
          if (v11550) {	// L18339
            ap_uint<26> v11551 = hd13[0];	// L18340
            o_crv13 = v11551;	// L18341
            crv_in13 = 0;	// L18342
          }
        }
      }
    }
    int32_t pop13[4];	// L18347
    for (int v11553 = 0; v11553 < 4; v11553++) {	// L18348
      pop13[v11553] = 0;	// L18348
    }
    int32_t inj_done13;	// L18349
    inj_done13 = 0;	// L18350
    int32_t idir13;	// L18351
    idir13 = -1;	// L18352
    ap_int<26> v11556 = csd_pkt13;	// L18353
    bool v11557;
    ap_int<26> v11557_tmp = v11556;
    v11557 = v11557_tmp[25];	// L18354
    int32_t v11558 = v11557;	// L18355
    bool v11559 = v11558 == 1;	// L18356
    if (v11559) {	// L18357
      int32_t v11560 = csd_dir13;	// L18358
      ap_int<33> v11561 = v11560;	// L18359
      ap_int<33> v11562 = 3 - v11561;	// L18360
      int32_t v11563 = v11562;	// L18361
      idir13 = v11563;	// L18362
    }
    int32_t v11564 = idir13;	// L18364
    bool v11565 = v11564 == 0;	// L18365
    if (v11565) {	// L18366
      ap_int<26> v11566 = csd_pkt13;	// L18367
      bool v11567 = v11379.write_nb(v11566);
	// L18368
      if (v11567) {	// L18369
        inj_done13 = 1;	// L18370
      }
    } else {
      int32_t v11568 = hvld13[0];	// L18373
      bool v11569 = v11568 == 1;	// L18374
      int32_t v11570 = hit13[0];	// L18375
      bool v11571 = v11570 == 0;	// L18376
      bool v11572 = v11569 & v11571;	// L18377
      if (v11572) {	// L18378
        ap_uint<26> v11573 = hd13[0];	// L18379
        bool v11574 = v11379.write_nb(v11573);
	// L18380
        if (v11574) {	// L18381
          pop13[0] = 1;	// L18382
        }
      }
    }
    int32_t v11575 = idir13;	// L18386
    bool v11576 = v11575 == 1;	// L18387
    if (v11576) {	// L18388
      ap_int<26> v11577 = csd_pkt13;	// L18389
      bool v11578 = v11380.write_nb(v11577);
	// L18390
      if (v11578) {	// L18391
        inj_done13 = 1;	// L18392
      }
    } else {
      int32_t v11579 = hvld13[1];	// L18395
      bool v11580 = v11579 == 1;	// L18396
      int32_t v11581 = hit13[1];	// L18397
      bool v11582 = v11581 == 0;	// L18398
      bool v11583 = v11580 & v11582;	// L18399
      if (v11583) {	// L18400
        ap_uint<26> v11584 = hd13[1];	// L18401
        bool v11585 = v11380.write_nb(v11584);
	// L18402
        if (v11585) {	// L18403
          pop13[1] = 1;	// L18404
        }
      }
    }
    int32_t v11586 = idir13;	// L18408
    bool v11587 = v11586 == 2;	// L18409
    if (v11587) {	// L18410
      ap_int<26> v11588 = csd_pkt13;	// L18411
      bool v11589 = v11381.write_nb(v11588);
	// L18412
      if (v11589) {	// L18413
        inj_done13 = 1;	// L18414
      }
    } else {
      int32_t v11590 = hvld13[2];	// L18417
      bool v11591 = v11590 == 1;	// L18418
      int32_t v11592 = hit13[2];	// L18419
      bool v11593 = v11592 == 0;	// L18420
      bool v11594 = v11591 & v11593;	// L18421
      if (v11594) {	// L18422
        ap_uint<26> v11595 = hd13[2];	// L18423
        bool v11596 = v11381.write_nb(v11595);
	// L18424
        if (v11596) {	// L18425
          pop13[2] = 1;	// L18426
        }
      }
    }
    int32_t v11597 = idir13;	// L18430
    bool v11598 = v11597 == 3;	// L18431
    if (v11598) {	// L18432
      ap_int<26> v11599 = csd_pkt13;	// L18433
      bool v11600 = v11382.write_nb(v11599);
	// L18434
      if (v11600) {	// L18435
        inj_done13 = 1;	// L18436
      }
    } else {
      int32_t v11601 = hvld13[3];	// L18439
      bool v11602 = v11601 == 1;	// L18440
      int32_t v11603 = hit13[3];	// L18441
      bool v11604 = v11603 == 0;	// L18442
      bool v11605 = v11602 & v11604;	// L18443
      if (v11605) {	// L18444
        ap_uint<26> v11606 = hd13[3];	// L18445
        bool v11607 = v11382.write_nb(v11606);
	// L18446
        if (v11607) {	// L18447
          pop13[3] = 1;	// L18448
        }
      }
    }
    int32_t v11608 = crv_in13;	// L18452
    bool v11609 = v11608 >= 0;	// L18453
    if (v11609) {	// L18454
      int32_t v11610 = crv_in13;	// L18455
      int v11611 = v11610;	// L18456
      pop13[v11611] = 1;	// L18457
    }
    l_S_d_2_d54: for (int d54 = 0; d54 < 4; d54++) {	// L18459
      int32_t v11613 = pop13[d54];	// L18460
      bool v11614 = v11613 == 1;	// L18461
      if (v11614) {	// L18462
        l_S_sft_2_sft13: for (int sft13 = 0; sft13 < 1; sft13++) {	// L18463
          ap_uint<26> v11616 = rbuf13[d54][(sft13 + 1)];	// L18464
          rbuf13[d54][sft13] = v11616;	// L18465
        }
        uint8_t v11617 = rbcnt13[d54];	// L18467
        ap_int<33> v11618 = v11617;	// L18468
        ap_int<33> v11619 = v11618 - 1;	// L18469
        uint8_t v11620 = v11619;	// L18470
        rbcnt13[d54] = v11620;	// L18471
      }
    }
    int32_t v11621 = inj_done13;	// L18474
    bool v11622 = v11621 == 1;	// L18475
    if (v11622) {	// L18476
      csd_pkt13 = 0;	// L18477
    }
    ap_int<26> v11623 = o_crv13;	// L18479
    bool v11624;
    ap_int<26> v11624_tmp = v11623;
    v11624 = v11624_tmp[25];	// L18480
    int32_t v11625 = v11624;	// L18481
    crv_vld13 = v11625;	// L18482
    int32_t v11626 = crv_vld13;	// L18483
    bool v11627 = v11626 == 1;	// L18484
    if (v11627) {	// L18485
      crv_ever13 = 1;	// L18486
    }
    ap_int<26> v11628 = o_crv13;	// L18488
    int16_t v11629;
    ap_int<26> v11629_tmp = v11628;
    v11629 = v11629_tmp(15, 0);	// L18489
    half v11630;
    union { uint16_t from; half to;} _converter_v11629_to_v11630 = {};
    _converter_v11629_to_v11630.from = v11629;
    v11630 = _converter_v11629_to_v11630.to;	// L18490
    crv_data13 = v11630;	// L18491
    ap_int<26> v11631 = o_crv13;	// L18492
    ap_int<4> v11632;
    ap_int<26> v11632_tmp = v11631;
    v11632 = v11632_tmp(19, 16);	// L18493
    int32_t v11633 = v11632;	// L18494
    crv_addr13 = v11633;	// L18495
    ap_int<26> v11634 = o_crv13;	// L18496
    bool v11635;
    ap_int<26> v11635_tmp = v11634;
    v11635 = v11635_tmp[20];	// L18497
    int32_t v11636 = v11635;	// L18498
    crv_mode13 = v11636;	// L18499
    ap_int<26> v11637 = o_crv13;	// L18500
    int16_t v11638;
    ap_int<26> v11638_tmp = v11637;
    v11638 = v11638_tmp(15, 0);	// L18501
    int32_t v11639 = v11638;	// L18502
    crv_raw13 = v11639;	// L18503
    half rxv13[4];	// L18504
    for (int v11641 = 0; v11641 < 4; v11641++) {	// L18505
      rxv13[v11641] = 0.000000;	// L18505
    }
    int32_t rxvld13[4];	// L18506
    for (int v11643 = 0; v11643 < 4; v11643++) {	// L18507
      rxvld13[v11643] = 0;	// L18507
    }
    uint8_t v11644 = hold_cnt13[0];	// L18508
    int32_t v11645 = v11644;	// L18509
    bool v11646 = v11645 < 2;	// L18510
    if (v11646) {	// L18511
      ap_uint<17> v11647;
      bool v11648 = v11383.read_nb(v11647);
	// L18512
      ap_uint<17> sgn13;	// L18513
      sgn13 = v11647;	// L18514
      bool sqn13;	// L18515
      sqn13 = v11648;	// L18516
      bool v11651 = sqn13;	// L18517
      int32_t v11652 = v11651;	// L18518
      bool v11653 = v11652 == 1;	// L18519
      if (v11653) {	// L18520
        ap_int<17> v11654 = sgn13;	// L18521
        int16_t v11655;
        ap_int<17> v11655_tmp = v11654;
        v11655 = v11655_tmp(16, 1);	// L18522
        half v11656;
        union { uint16_t from; half to;} _converter_v11655_to_v11656 = {};
        _converter_v11655_to_v11656.from = v11655;
        v11656 = _converter_v11655_to_v11656.to;	// L18523
        rxv13[0] = v11656;	// L18524
        rxvld13[0] = 1;	// L18525
      }
    }
    uint8_t v11657 = hold_cnt13[1];	// L18528
    int32_t v11658 = v11657;	// L18529
    bool v11659 = v11658 < 2;	// L18530
    if (v11659) {	// L18531
      ap_uint<17> v11660;
      bool v11661 = v11384.read_nb(v11660);
	// L18532
      ap_uint<17> sgs13;	// L18533
      sgs13 = v11660;	// L18534
      bool sqs13;	// L18535
      sqs13 = v11661;	// L18536
      bool v11664 = sqs13;	// L18537
      int32_t v11665 = v11664;	// L18538
      bool v11666 = v11665 == 1;	// L18539
      if (v11666) {	// L18540
        ap_int<17> v11667 = sgs13;	// L18541
        int16_t v11668;
        ap_int<17> v11668_tmp = v11667;
        v11668 = v11668_tmp(16, 1);	// L18542
        half v11669;
        union { uint16_t from; half to;} _converter_v11668_to_v11669 = {};
        _converter_v11668_to_v11669.from = v11668;
        v11669 = _converter_v11668_to_v11669.to;	// L18543
        rxv13[1] = v11669;	// L18544
        rxvld13[1] = 1;	// L18545
      }
    }
    uint8_t v11670 = hold_cnt13[2];	// L18548
    int32_t v11671 = v11670;	// L18549
    bool v11672 = v11671 < 2;	// L18550
    if (v11672) {	// L18551
      ap_uint<17> v11673;
      bool v11674 = v11385.read_nb(v11673);
	// L18552
      ap_uint<17> sgw13;	// L18553
      sgw13 = v11673;	// L18554
      bool sqw13;	// L18555
      sqw13 = v11674;	// L18556
      bool v11677 = sqw13;	// L18557
      int32_t v11678 = v11677;	// L18558
      bool v11679 = v11678 == 1;	// L18559
      if (v11679) {	// L18560
        ap_int<17> v11680 = sgw13;	// L18561
        int16_t v11681;
        ap_int<17> v11681_tmp = v11680;
        v11681 = v11681_tmp(16, 1);	// L18562
        half v11682;
        union { uint16_t from; half to;} _converter_v11681_to_v11682 = {};
        _converter_v11681_to_v11682.from = v11681;
        v11682 = _converter_v11681_to_v11682.to;	// L18563
        rxv13[2] = v11682;	// L18564
        rxvld13[2] = 1;	// L18565
      }
    }
    uint8_t v11683 = hold_cnt13[3];	// L18568
    int32_t v11684 = v11683;	// L18569
    bool v11685 = v11684 < 2;	// L18570
    if (v11685) {	// L18571
      ap_uint<17> v11686;
      bool v11687 = v11386.read_nb(v11686);
	// L18572
      ap_uint<17> sge13;	// L18573
      sge13 = v11686;	// L18574
      bool sqe13;	// L18575
      sqe13 = v11687;	// L18576
      bool v11690 = sqe13;	// L18577
      int32_t v11691 = v11690;	// L18578
      bool v11692 = v11691 == 1;	// L18579
      if (v11692) {	// L18580
        ap_int<17> v11693 = sge13;	// L18581
        int16_t v11694;
        ap_int<17> v11694_tmp = v11693;
        v11694 = v11694_tmp(16, 1);	// L18582
        half v11695;
        union { uint16_t from; half to;} _converter_v11694_to_v11695 = {};
        _converter_v11694_to_v11695.from = v11694;
        v11695 = _converter_v11694_to_v11695.to;	// L18583
        rxv13[3] = v11695;	// L18584
        rxvld13[3] = 1;	// L18585
      }
    }
    l_S_d_4_d55: for (int d55 = 0; d55 < 4; d55++) {	// L18588
      int32_t v11697 = rxvld13[d55];	// L18589
      bool v11698 = v11697 == 1;	// L18590
      if (v11698) {	// L18591
        half v11699 = rxv13[d55];	// L18592
        uint8_t v11700 = hold_cnt13[d55];	// L18593
        int v11701 = v11700;	// L18594
        hold_v13[d55][v11701] = v11699;	// L18595
        uint8_t v11702 = hold_cnt13[d55];	// L18596
        ap_int<33> v11703 = v11702;	// L18597
        ap_int<33> v11704 = v11703 + 1;	// L18598
        uint8_t v11705 = v11704;	// L18599
        hold_cnt13[d55] = v11705;	// L18600
      }
    }
    ap_uint<17> tx_n13;	// L18603
    tx_n13 = 0;	// L18604
    ap_uint<17> tx_s13;	// L18605
    tx_s13 = 0;	// L18606
    ap_uint<17> tx_w13;	// L18607
    tx_w13 = 0;	// L18608
    ap_uint<17> tx_e13;	// L18609
    tx_e13 = 0;	// L18610
    uint8_t v11710 = sb_v13[0];	// L18611
    int32_t v11711 = v11710;	// L18612
    bool v11712 = v11711 == 1;	// L18613
    if (v11712) {	// L18614
      uint8_t v11713 = sb_ix13[0];	// L18615
      int v11714 = v11713;	// L18616
      half v11715 = resq13[v11714];	// L18617
      half wb13;
#pragma HLS dependence variable=wb13 type=inter dependent=false	// L18618
      wb13 = v11715;	// L18619
      uint8_t v11717 = sb_cmp13[0];	// L18620
      int32_t v11718 = v11717;	// L18621
      bool v11719 = v11718 == 1;	// L18622
      if (v11719) {	// L18623
        uint8_t v11720 = sb_ix13[0];	// L18624
        int v11721 = v11720;	// L18625
        uint8_t v11722 = cmpq13[v11721];	// L18626
        condition_reg13 = v11722;	// L18627
      }
      uint8_t v11723 = sb_rtr13[0];	// L18629
      int32_t v11724 = v11723;	// L18630
      bool v11725 = v11724 == 1;	// L18631
      if (v11725) {	// L18632
        uint8_t v11726 = sb_inj13[0];	// L18633
        int32_t v11727 = v11726;	// L18634
        bool v11728 = v11727 == 1;	// L18635
        ap_int<26> v11729 = csd_pkt13;	// L18636
        bool v11730;
        ap_int<26> v11730_tmp = v11729;
        v11730 = v11730_tmp[25];	// L18637
        int32_t v11731 = v11730;	// L18638
        bool v11732 = v11731 == 0;	// L18639
        bool v11733 = v11728 & v11732;	// L18640
        if (v11733) {	// L18641
          half v11734 = wb13;	// L18642
          uint16_t v11735;
          union { half from; uint16_t to;} _converter_v11734_to_v11735 = {};
          _converter_v11734_to_v11735.from = v11734;
          v11735 = _converter_v11734_to_v11735.to;	// L18643
          ap_int<26> v11736 = csd_pkt13;	// L18644
          ap_int<26> v11737;
          ap_int<26> v11737_tmp = v11736;
          v11737_tmp(15, 0) = v11735;
          v11737 = v11737_tmp;	// L18645
          csd_pkt13 = v11737;	// L18646
          uint8_t v11738 = sb_dst13[0];	// L18647
          ap_uint<4> v11739 = v11738;	// L18648
          ap_int<26> v11740 = csd_pkt13;	// L18649
          ap_int<26> v11741;
          ap_int<26> v11741_tmp = v11740;
          v11741_tmp(19, 16) = v11739;
          v11741 = v11741_tmp;	// L18650
          csd_pkt13 = v11741;	// L18651
          uint8_t v11742 = sb_id13[0];	// L18652
          ap_uint<4> v11743 = v11742;	// L18653
          ap_int<26> v11744 = csd_pkt13;	// L18654
          ap_int<26> v11745;
          ap_int<26> v11745_tmp = v11744;
          v11745_tmp(24, 21) = v11743;
          v11745 = v11745_tmp;	// L18655
          csd_pkt13 = v11745;	// L18656
          uint8_t v11746 = sb_rvld13[0];	// L18657
          bool v11747 = v11746;	// L18658
          ap_int<26> v11748 = csd_pkt13;	// L18659
          ap_int<26> v11749;
          ap_int<26> v11749_tmp = v11748;
          v11749_tmp[25] = v11747;          v11749 = v11749_tmp;	// L18660
          csd_pkt13 = v11749;	// L18661
          uint8_t v11750 = sb_dir13[0];	// L18662
          int32_t v11751 = v11750;	// L18663
          csd_dir13 = v11751;	// L18664
        }
      } else {
        uint8_t v11752 = sb_dst13[0];	// L18667
        int32_t v11753 = v11752;	// L18668
        bool v11754 = v11753 >= 12;	// L18669
        if (v11754) {	// L18670
          ap_uint<17> tw013;	// L18671
          tw013 = 0;	// L18672
          uint8_t v11756 = sb_rvld13[0];	// L18673
          bool v11757 = v11756;	// L18674
          ap_int<17> v11758 = tw013;	// L18675
          ap_int<17> v11759;
          ap_int<17> v11759_tmp = v11758;
          v11759_tmp[0] = v11757;          v11759 = v11759_tmp;	// L18676
          tw013 = v11759;	// L18677
          half v11760 = wb13;	// L18678
          uint16_t v11761;
          union { half from; uint16_t to;} _converter_v11760_to_v11761 = {};
          _converter_v11760_to_v11761.from = v11760;
          v11761 = _converter_v11760_to_v11761.to;	// L18679
          ap_int<17> v11762 = tw013;	// L18680
          ap_int<17> v11763;
          ap_int<17> v11763_tmp = v11762;
          v11763_tmp(16, 1) = v11761;
          v11763 = v11763_tmp;	// L18681
          tw013 = v11763;	// L18682
          uint8_t v11764 = sb_dst13[0];	// L18683
          int32_t v11765 = v11764;	// L18684
          int32_t v11766 = v11765 & 3;	// L18685
          bool v11767 = v11766 == 0;	// L18686
          if (v11767) {	// L18687
            ap_int<17> v11768 = tw013;	// L18688
            tx_n13 = v11768;	// L18689
          } else {
            uint8_t v11769 = sb_dst13[0];	// L18691
            int32_t v11770 = v11769;	// L18692
            int32_t v11771 = v11770 & 3;	// L18693
            bool v11772 = v11771 == 1;	// L18694
            if (v11772) {	// L18695
              ap_int<17> v11773 = tw013;	// L18696
              tx_s13 = v11773;	// L18697
            } else {
              uint8_t v11774 = sb_dst13[0];	// L18699
              int32_t v11775 = v11774;	// L18700
              int32_t v11776 = v11775 & 3;	// L18701
              bool v11777 = v11776 == 2;	// L18702
              if (v11777) {	// L18703
                ap_int<17> v11778 = tw013;	// L18704
                tx_w13 = v11778;	// L18705
              } else {
                ap_int<17> v11779 = tw013;	// L18707
                tx_e13 = v11779;	// L18708
              }
            }
          }
        } else {
          uint8_t v11780 = sb_rvld13[0];	// L18713
          int32_t v11781 = v11780;	// L18714
          bool v11782 = v11781 == 1;	// L18715
          if (v11782) {	// L18716
            uint8_t v11783 = sb_dst13[0];	// L18717
            int32_t v11784 = v11783;	// L18718
            bool v11785 = v11784 < 8;	// L18719
            int32_t v11786 = dsmask13;	// L18720
            int32_t v11787 = v11786 >> v11784;	// L18721
            int32_t v11788 = v11787 & 1;	// L18722
            bool v11789 = v11788 == 1;	// L18723
            bool v11790 = v11785 & v11789;	// L18724
            if (v11790) {	// L18725
              uint8_t v11791 = sb_dst13[0];	// L18726
              int v11792 = v11791;	// L18727
              int32_t v11793 = drf_full13[v11792];	// L18728
              bool v11794 = v11793 == 0;	// L18729
              if (v11794) {	// L18730
                half v11795 = wb13;	// L18731
                uint8_t v11796 = sb_dst13[0];	// L18732
                int v11797 = v11796;	// L18733
                drf13[v11797] = v11795;	// L18734
                uint8_t v11798 = sb_dst13[0];	// L18735
                int v11799 = v11798;	// L18736
                drf_full13[v11799] = 1;	// L18737
              }
            } else {
              half v11800 = wb13;	// L18740
              uint8_t v11801 = sb_dst13[0];	// L18741
              int32_t v11802 = v11801;	// L18742
              int32_t v11803 = v11802 & 7;	// L18743
              int v11804 = v11803;	// L18744
              drf13[v11804] = v11800;	// L18745
            }
          }
        }
      }
    }
    int32_t pc13;	// L18751
    pc13 = -1;	// L18752
    int8_t v11806 = fetch_en13;	// L18753
    int32_t v11807 = v11806;	// L18754
    bool v11808 = v11807 == 1;	// L18755
    if (v11808) {	// L18756
      int8_t v11809 = instr_cnt13;	// L18757
      int32_t v11810 = v11809;	// L18758
      pc13 = v11810;	// L18759
    }
    int8_t v11811 = fetch_en13;	// L18761
    int32_t v11812 = v11811;	// L18762
    bool v11813 = v11812 == 1;	// L18763
    if (v11813) {	// L18764
      fe_ever13 = 1;	// L18765
    }
    int32_t instr13;	// L18767
    instr13 = 0;	// L18768
    int32_t v11815 = pc13;	// L18769
    bool v11816 = v11815 >= 0;	// L18770
    if (v11816) {	// L18771
      int32_t v11817 = pc13;	// L18772
      int v11818 = v11817;	// L18773
      int32_t v11819 = irf13[v11818];	// L18774
      instr13 = v11819;	// L18775
    }
    int32_t v11820 = instr13;	// L18777
    int32_t v11821 = v11820 & 15;	// L18778
    int32_t op13;	// L18779
    op13 = v11821;	// L18780
    int32_t v11823 = instr13;	// L18781
    int32_t v11824 = v11823 >> 4;	// L18782
    int32_t v11825 = v11824 & 15;	// L18783
    int32_t dst13;	// L18784
    dst13 = v11825;	// L18785
    int32_t v11827 = instr13;	// L18786
    int32_t v11828 = v11827 >> 8;	// L18787
    int32_t v11829 = v11828 & 15;	// L18788
    int32_t s113;	// L18789
    s113 = v11829;	// L18790
    int32_t v11831 = instr13;	// L18791
    int32_t v11832 = v11831 >> 12;	// L18792
    int32_t v11833 = v11832 & 15;	// L18793
    int32_t s213;	// L18794
    s213 = v11833;	// L18795
    half a13;	// L18796
    a13 = 0.000000;	// L18797
    half b13;	// L18798
    b13 = 0.000000;	// L18799
    int32_t v11837 = s113;	// L18800
    bool v11838 = v11837 >= 12;	// L18801
    if (v11838) {	// L18802
      int32_t v11839 = s113;	// L18803
      int32_t v11840 = v11839 & 3;	// L18804
      int v11841 = v11840;	// L18805
      half v11842 = hold_v13[v11841][0];	// L18806
      a13 = v11842;	// L18807
    } else {
      int32_t v11843 = s113;	// L18809
      int v11844 = v11843;	// L18810
      half v11845 = drf13[v11844];	// L18811
      a13 = v11845;	// L18812
    }
    int32_t v11846 = s213;	// L18814
    bool v11847 = v11846 >= 12;	// L18815
    if (v11847) {	// L18816
      int32_t v11848 = s213;	// L18817
      int32_t v11849 = v11848 & 3;	// L18818
      int v11850 = v11849;	// L18819
      half v11851 = hold_v13[v11850][0];	// L18820
      b13 = v11851;	// L18821
    } else {
      int32_t v11852 = s213;	// L18823
      int v11853 = v11852;	// L18824
      half v11854 = drf13[v11853];	// L18825
      b13 = v11854;	// L18826
    }
    int32_t a_vld13;	// L18828
    a_vld13 = 1;	// L18829
    int32_t b_vld13;	// L18830
    b_vld13 = 1;	// L18831
    int32_t v11857 = s113;	// L18832
    bool v11858 = v11857 >= 12;	// L18833
    if (v11858) {	// L18834
      a_vld13 = 0;	// L18835
      int32_t v11859 = s113;	// L18836
      int32_t v11860 = v11859 & 3;	// L18837
      int v11861 = v11860;	// L18838
      uint8_t v11862 = hold_cnt13[v11861];	// L18839
      int32_t v11863 = v11862;	// L18840
      bool v11864 = v11863 > 0;	// L18841
      if (v11864) {	// L18842
        a_vld13 = 1;	// L18843
      }
    }
    int32_t v11865 = s213;	// L18846
    bool v11866 = v11865 >= 12;	// L18847
    if (v11866) {	// L18848
      b_vld13 = 0;	// L18849
      int32_t v11867 = s213;	// L18850
      int32_t v11868 = v11867 & 3;	// L18851
      int v11869 = v11868;	// L18852
      uint8_t v11870 = hold_cnt13[v11869];	// L18853
      int32_t v11871 = v11870;	// L18854
      bool v11872 = v11871 > 0;	// L18855
      if (v11872) {	// L18856
        b_vld13 = 1;	// L18857
      }
    }
    int32_t v11873 = s113;	// L18860
    bool v11874 = v11873 < 8;	// L18861
    int32_t v11875 = dsmask13;	// L18862
    int32_t v11876 = v11875 >> v11873;	// L18863
    int32_t v11877 = v11876 & 1;	// L18864
    bool v11878 = v11877 == 1;	// L18865
    bool v11879 = v11874 & v11878;	// L18866
    if (v11879) {	// L18867
      int32_t v11880 = s113;	// L18868
      int v11881 = v11880;	// L18869
      int32_t v11882 = drf_full13[v11881];	// L18870
      bool v11883 = v11882 == 0;	// L18871
      if (v11883) {	// L18872
        a_vld13 = 0;	// L18873
      }
    }
    int32_t v11884 = s213;	// L18876
    bool v11885 = v11884 < 8;	// L18877
    int32_t v11886 = dsmask13;	// L18878
    int32_t v11887 = v11886 >> v11884;	// L18879
    int32_t v11888 = v11887 & 1;	// L18880
    bool v11889 = v11888 == 1;	// L18881
    bool v11890 = v11885 & v11889;	// L18882
    if (v11890) {	// L18883
      int32_t v11891 = s213;	// L18884
      int v11892 = v11891;	// L18885
      int32_t v11893 = drf_full13[v11892];	// L18886
      bool v11894 = v11893 == 0;	// L18887
      if (v11894) {	// L18888
        b_vld13 = 0;	// L18889
      }
    }
    int32_t binop13;	// L18892
    binop13 = 0;	// L18893
    int32_t v11896 = op13;	// L18894
    bool v11897 = v11896 == 0;	// L18895
    bool v11898 = v11896 == 1;	// L18896
    bool v11899 = v11896 == 2;	// L18897
    bool v11900 = v11896 == 8;	// L18898
    bool v11901 = v11896 == 9;	// L18899
    bool v11902 = v11897 | v11898;	// L18900
    bool v11903 = v11902 | v11899;	// L18901
    bool v11904 = v11903 | v11900;	// L18902
    bool v11905 = v11904 | v11901;	// L18903
    if (v11905) {	// L18904
      binop13 = 1;	// L18905
    }
    int32_t raw13;	// L18907
    raw13 = 0;	// L18908
    int32_t cmp_busy13;	// L18909
    cmp_busy13 = 0;	// L18910
    l_S_k_5_k26: for (int k26 = 0; k26 < 4; k26++) {	// L18911
      uint8_t v11909 = sb_v13[(k26 + 1)];	// L18912
      int32_t v11910 = v11909;	// L18913
      bool v11911 = v11910 == 1;	// L18914
      uint8_t v11912 = sb_rtr13[(k26 + 1)];	// L18915
      int32_t v11913 = v11912;	// L18916
      bool v11914 = v11913 == 0;	// L18917
      uint8_t v11915 = sb_dst13[(k26 + 1)];	// L18918
      int32_t v11916 = v11915;	// L18919
      bool v11917 = v11916 < 12;	// L18920
      bool v11918 = v11911 & v11914;	// L18921
      bool v11919 = v11918 & v11917;	// L18922
      if (v11919) {	// L18923
        int32_t v11920 = s113;	// L18924
        bool v11921 = v11920 < 12;	// L18925
        uint8_t v11922 = sb_dst13[(k26 + 1)];	// L18926
        int32_t v11923 = v11922;	// L18927
        int32_t v11924 = v11923 & 7;	// L18928
        int32_t v11925 = v11920 & 7;	// L18929
        bool v11926 = v11924 == v11925;	// L18930
        bool v11927 = v11921 & v11926;	// L18931
        if (v11927) {	// L18932
          raw13 = 1;	// L18933
        }
        int32_t v11928 = binop13;	// L18935
        bool v11929 = v11928 == 1;	// L18936
        int32_t v11930 = s213;	// L18937
        bool v11931 = v11930 < 12;	// L18938
        uint8_t v11932 = sb_dst13[(k26 + 1)];	// L18939
        int32_t v11933 = v11932;	// L18940
        int32_t v11934 = v11933 & 7;	// L18941
        int32_t v11935 = v11930 & 7;	// L18942
        bool v11936 = v11934 == v11935;	// L18943
        bool v11937 = v11929 & v11931;	// L18944
        bool v11938 = v11937 & v11936;	// L18945
        if (v11938) {	// L18946
          raw13 = 1;	// L18947
        }
      }
      uint8_t v11939 = sb_v13[(k26 + 1)];	// L18950
      int32_t v11940 = v11939;	// L18951
      bool v11941 = v11940 == 1;	// L18952
      uint8_t v11942 = sb_cmp13[(k26 + 1)];	// L18953
      int32_t v11943 = v11942;	// L18954
      bool v11944 = v11943 == 1;	// L18955
      bool v11945 = v11941 & v11944;	// L18956
      if (v11945) {	// L18957
        cmp_busy13 = 1;	// L18958
      }
    }
    int32_t is_cond13;	// L18961
    is_cond13 = 0;	// L18962
    int32_t v11947 = op13;	// L18963
    bool v11948 = v11947 >= 12;	// L18964
    ap_int<33> v11949 = v11947;	// L18965
    bool v11950 = v11949 <= 15;	// L18966
    bool v11951 = v11948 & v11950;	// L18967
    if (v11951) {	// L18968
      is_cond13 = 1;	// L18969
    }
    int32_t grant13;	// L18971
    grant13 = 0;	// L18972
    int32_t v11953 = pc13;	// L18973
    bool v11954 = v11953 >= 0;	// L18974
    if (v11954) {	// L18975
      grant13 = 1;	// L18976
    }
    int32_t v11955 = pc13;	// L18978
    bool v11956 = v11955 >= 0;	// L18979
    int32_t v11957 = a_vld13;	// L18980
    bool v11958 = v11957 == 0;	// L18981
    int32_t v11959 = binop13;	// L18982
    bool v11960 = v11959 == 1;	// L18983
    int32_t v11961 = b_vld13;	// L18984
    bool v11962 = v11961 == 0;	// L18985
    bool v11963 = v11960 & v11962;	// L18986
    bool v11964 = v11958 | v11963;	// L18987
    bool v11965 = v11956 & v11964;	// L18988
    if (v11965) {	// L18989
      grant13 = 0;	// L18990
    }
    int32_t v11966 = pc13;	// L18992
    bool v11967 = v11966 >= 0;	// L18993
    int32_t v11968 = raw13;	// L18994
    bool v11969 = v11968 == 1;	// L18995
    int32_t v11970 = is_cond13;	// L18996
    bool v11971 = v11970 == 1;	// L18997
    int32_t v11972 = cmp_busy13;	// L18998
    bool v11973 = v11972 == 1;	// L18999
    bool v11974 = v11971 & v11973;	// L19000
    bool v11975 = v11969 | v11974;	// L19001
    bool v11976 = v11967 & v11975;	// L19002
    if (v11976) {	// L19003
      grant13 = 0;	// L19004
    }
    int32_t v11977 = grant13;	// L19006
    bool v11978 = v11977 == 1;	// L19007
    if (v11978) {	// L19008
      int8_t v11979 = instr_cnt13;	// L19009
      int32_t v11980 = cfg_isz13;	// L19010
      int32_t v11981 = v11979;	// L19011
      bool v11982 = v11981 == v11980;	// L19012
      if (v11982) {	// L19013
        instr_cnt13 = 0;	// L19014
        int8_t v11983 = iter_cnt13;	// L19015
        int32_t v11984 = cfg_itsz13;	// L19016
        ap_int<33> v11985 = v11984;	// L19017
        ap_int<33> v11986 = v11985 - 1;	// L19018
        ap_int<33> v11987 = v11983;	// L19019
        bool v11988 = v11987 == v11986;	// L19020
        if (v11988) {	// L19021
          fetch_en13 = 0;	// L19022
        } else {
          int8_t v11989 = iter_cnt13;	// L19024
          ap_int<33> v11990 = v11989;	// L19025
          ap_int<33> v11991 = v11990 + 1;	// L19026
          uint8_t v11992 = v11991;	// L19027
          iter_cnt13 = v11992;	// L19028
        }
      } else {
        int8_t v11993 = instr_cnt13;	// L19031
        ap_int<33> v11994 = v11993;	// L19032
        ap_int<33> v11995 = v11994 + 1;	// L19033
        uint8_t v11996 = v11995;	// L19034
        instr_cnt13 = v11996;	// L19035
      }
    }
    int32_t c113;	// L19038
    c113 = -1;	// L19039
    int32_t c213;	// L19040
    c213 = -1;	// L19041
    int32_t v11999 = grant13;	// L19042
    bool v12000 = v11999 == 1;	// L19043
    int32_t v12001 = s113;	// L19044
    bool v12002 = v12001 >= 12;	// L19045
    bool v12003 = v12000 & v12002;	// L19046
    if (v12003) {	// L19047
      int32_t v12004 = s113;	// L19048
      int32_t v12005 = v12004 & 3;	// L19049
      c113 = v12005;	// L19050
    }
    int32_t v12006 = grant13;	// L19052
    bool v12007 = v12006 == 1;	// L19053
    int32_t v12008 = s213;	// L19054
    bool v12009 = v12008 >= 12;	// L19055
    bool v12010 = v12007 & v12009;	// L19056
    if (v12010) {	// L19057
      int32_t v12011 = s213;	// L19058
      int32_t v12012 = v12011 & 3;	// L19059
      c213 = v12012;	// L19060
    }
    int32_t v12013 = c113;	// L19062
    bool v12014 = v12013 >= 0;	// L19063
    if (v12014) {	// L19064
      int32_t v12015 = c113;	// L19065
      int v12016 = v12015;	// L19066
      half v12017 = hold_v13[v12016][1];	// L19067
      hold_v13[v12016][0] = v12017;	// L19068
      int32_t v12018 = c113;	// L19069
      int v12019 = v12018;	// L19070
      uint8_t v12020 = hold_cnt13[v12019];	// L19071
      ap_int<33> v12021 = v12020;	// L19072
      ap_int<33> v12022 = v12021 - 1;	// L19073
      uint8_t v12023 = v12022;	// L19074
      hold_cnt13[v12019] = v12023;	// L19075
    }
    int32_t v12024 = c213;	// L19077
    bool v12025 = v12024 >= 0;	// L19078
    int32_t v12026 = c113;	// L19079
    bool v12027 = v12024 != v12026;	// L19080
    bool v12028 = v12025 & v12027;	// L19081
    if (v12028) {	// L19082
      int32_t v12029 = c213;	// L19083
      int v12030 = v12029;	// L19084
      half v12031 = hold_v13[v12030][1];	// L19085
      hold_v13[v12030][0] = v12031;	// L19086
      int32_t v12032 = c213;	// L19087
      int v12033 = v12032;	// L19088
      uint8_t v12034 = hold_cnt13[v12033];	// L19089
      ap_int<33> v12035 = v12034;	// L19090
      ap_int<33> v12036 = v12035 - 1;	// L19091
      uint8_t v12037 = v12036;	// L19092
      hold_cnt13[v12033] = v12037;	// L19093
    }
    int32_t v12038 = grant13;	// L19095
    bool v12039 = v12038 == 1;	// L19096
    int32_t v12040 = s113;	// L19097
    bool v12041 = v12040 < 8;	// L19098
    int32_t v12042 = dsmask13;	// L19099
    int32_t v12043 = v12042 >> v12040;	// L19100
    int32_t v12044 = v12043 & 1;	// L19101
    bool v12045 = v12044 == 1;	// L19102
    bool v12046 = v12039 & v12041;	// L19103
    bool v12047 = v12046 & v12045;	// L19104
    if (v12047) {	// L19105
      int32_t v12048 = s113;	// L19106
      int v12049 = v12048;	// L19107
      drf_full13[v12049] = 0;	// L19108
    }
    int32_t v12050 = grant13;	// L19110
    bool v12051 = v12050 == 1;	// L19111
    int32_t v12052 = s213;	// L19112
    bool v12053 = v12052 < 8;	// L19113
    int32_t v12054 = dsmask13;	// L19114
    int32_t v12055 = v12054 >> v12052;	// L19115
    int32_t v12056 = v12055 & 1;	// L19116
    bool v12057 = v12056 == 1;	// L19117
    bool v12058 = v12051 & v12053;	// L19118
    bool v12059 = v12058 & v12057;	// L19119
    if (v12059) {	// L19120
      int32_t v12060 = s213;	// L19121
      int v12061 = v12060;	// L19122
      drf_full13[v12061] = 0;	// L19123
    }
    half res13;
#pragma HLS dependence variable=res13 type=inter dependent=false	// L19125
    res13 = 0.000000;	// L19126
    int32_t v12063 = op13;	// L19127
    bool v12064 = v12063 == 0;	// L19128
    if (v12064) {	// L19129
      half v12065 = a13;	// L19130
      half v12066 = b13;	// L19131
      half v12067 = v12065 + v12066;	// L19132
      res13 = v12067;	// L19133
    } else {
      int32_t v12068 = op13;	// L19135
      bool v12069 = v12068 == 1;	// L19136
      if (v12069) {	// L19137
        half v12070 = a13;	// L19138
        half v12071 = b13;	// L19139
        half v12072 = v12070 - v12071;	// L19140
        res13 = v12072;	// L19141
      } else {
        int32_t v12073 = op13;	// L19143
        bool v12074 = v12073 == 2;	// L19144
        if (v12074) {	// L19145
          half v12075 = a13;	// L19146
          half v12076 = b13;	// L19147
          half v12077 = v12075 * v12076;	// L19148
          res13 = v12077;	// L19149
        } else {
          int32_t v12078 = op13;	// L19151
          bool v12079 = v12078 == 8;	// L19152
          if (v12079) {	// L19153
            half v12080 = a13;	// L19154
            half v12081 = b13;	// L19155
            bool v12082 = v12080 >= v12081;	// L19156
            if (v12082) {	// L19157
              res13 = 1.000000;	// L19158
            } else {
              res13 = -1.000000;	// L19160
            }
          } else {
            int32_t v12083 = op13;	// L19163
            bool v12084 = v12083 == 9;	// L19164
            if (v12084) {	// L19165
              half v12085 = a13;	// L19166
              half v12086 = b13;	// L19167
              bool v12087 = v12085 < v12086;	// L19168
              if (v12087) {	// L19169
                res13 = 1.000000;	// L19170
              } else {
                res13 = -1.000000;	// L19172
              }
            } else {
              half v12088 = a13;	// L19175
              res13 = v12088;	// L19176
            }
          }
        }
      }
    }
    int32_t v12089 = a_vld13;	// L19182
    int32_t res_vld13;	// L19183
    res_vld13 = v12089;	// L19184
    int32_t v12091 = op13;	// L19185
    bool v12092 = v12091 == 0;	// L19186
    bool v12093 = v12091 == 1;	// L19187
    bool v12094 = v12091 == 2;	// L19188
    bool v12095 = v12091 == 8;	// L19189
    bool v12096 = v12091 == 9;	// L19190
    bool v12097 = v12092 | v12093;	// L19191
    bool v12098 = v12097 | v12094;	// L19192
    bool v12099 = v12098 | v12095;	// L19193
    bool v12100 = v12099 | v12096;	// L19194
    if (v12100) {	// L19195
      int32_t v12101 = a_vld13;	// L19196
      int32_t v12102 = b_vld13;	// L19197
      int64_t v12103 = v12101;	// L19198
      int64_t v12104 = v12102;	// L19199
      int64_t v12105 = v12103 * v12104;	// L19200
      int32_t v12106 = v12105;	// L19201
      res_vld13 = v12106;	// L19202
    }
    int32_t v12107 = grant13;	// L19204
    bool v12108 = v12107 == 0;	// L19205
    if (v12108) {	// L19206
      res_vld13 = 0;	// L19207
    }
    int32_t is_rtr13;	// L19209
    is_rtr13 = 0;	// L19210
    int32_t v12110 = op13;	// L19211
    bool v12111 = v12110 >= 4;	// L19212
    ap_int<33> v12112 = v12110;	// L19213
    bool v12113 = v12112 <= 7;	// L19214
    bool v12114 = v12111 & v12113;	// L19215
    if (v12114) {	// L19216
      is_rtr13 = 1;	// L19217
    }
    l_S_k_6_k27: for (int k27 = 0; k27 < 4; k27++) {	// L19219
      uint8_t v12116 = sb_v13[(k27 + 1)];	// L19220
      sb_v13[k27] = v12116;	// L19221
      uint8_t v12117 = sb_dst13[(k27 + 1)];	// L19222
      sb_dst13[k27] = v12117;	// L19223
      uint8_t v12118 = sb_cmp13[(k27 + 1)];	// L19224
      sb_cmp13[k27] = v12118;	// L19225
      uint8_t v12119 = sb_rtr13[(k27 + 1)];	// L19226
      sb_rtr13[k27] = v12119;	// L19227
      uint8_t v12120 = sb_inj13[(k27 + 1)];	// L19228
      sb_inj13[k27] = v12120;	// L19229
      uint8_t v12121 = sb_dir13[(k27 + 1)];	// L19230
      sb_dir13[k27] = v12121;	// L19231
      uint8_t v12122 = sb_id13[(k27 + 1)];	// L19232
      sb_id13[k27] = v12122;	// L19233
      uint8_t v12123 = sb_rvld13[(k27 + 1)];	// L19234
      sb_rvld13[k27] = v12123;	// L19235
      uint8_t v12124 = sb_ix13[(k27 + 1)];	// L19236
      sb_ix13[k27] = v12124;	// L19237
    }
    sb_v13[4] = 0;	// L19239
    int32_t v12125 = grant13;	// L19240
    bool v12126 = v12125 == 1;	// L19241
    if (v12126) {	// L19242
      half v12127 = res13;	// L19243
      int8_t v12128 = resq_wr13;	// L19244
      int v12129 = v12128;	// L19245
      resq13[v12129] = v12127;	// L19246
      int32_t cq13;	// L19247
      cq13 = 0;	// L19248
      int32_t v12131 = op13;	// L19249
      bool v12132 = v12131 == 8;	// L19250
      if (v12132) {	// L19251
        half v12133 = a13;	// L19252
        half v12134 = b13;	// L19253
        bool v12135 = v12133 >= v12134;	// L19254
        if (v12135) {	// L19255
          cq13 = 1;	// L19256
        }
      }
      int32_t v12136 = op13;	// L19259
      bool v12137 = v12136 == 9;	// L19260
      if (v12137) {	// L19261
        half v12138 = a13;	// L19262
        half v12139 = b13;	// L19263
        bool v12140 = v12138 < v12139;	// L19264
        if (v12140) {	// L19265
          cq13 = 1;	// L19266
        }
      }
      int32_t v12141 = cq13;	// L19269
      uint8_t v12142 = v12141;	// L19270
      int8_t v12143 = resq_wr13;	// L19271
      int v12144 = v12143;	// L19272
      cmpq13[v12144] = v12142;	// L19273
      sb_v13[4] = 1;	// L19274
      int32_t v12145 = dst13;	// L19275
      uint8_t v12146 = v12145;	// L19276
      sb_dst13[4] = v12146;	// L19277
      int8_t v12147 = resq_wr13;	// L19278
      sb_ix13[4] = v12147;	// L19279
      sb_cmp13[4] = 0;	// L19280
      int32_t v12148 = op13;	// L19281
      bool v12149 = v12148 == 8;	// L19282
      bool v12150 = v12148 == 9;	// L19283
      bool v12151 = v12149 | v12150;	// L19284
      if (v12151) {	// L19285
        sb_cmp13[4] = 1;	// L19286
      }
      int32_t v12152 = is_rtr13;	// L19288
      int32_t rtrf13;	// L19289
      rtrf13 = v12152;	// L19290
      int32_t v12154 = is_cond13;	// L19291
      bool v12155 = v12154 == 1;	// L19292
      if (v12155) {	// L19293
        rtrf13 = 1;	// L19294
      }
      int32_t v12156 = rtrf13;	// L19296
      uint8_t v12157 = v12156;	// L19297
      sb_rtr13[4] = v12157;	// L19298
      int32_t v12158 = is_rtr13;	// L19299
      int32_t inj13;	// L19300
      inj13 = v12158;	// L19301
      int32_t v12160 = is_cond13;	// L19302
      bool v12161 = v12160 == 1;	// L19303
      int8_t v12162 = condition_reg13;	// L19304
      int32_t v12163 = v12162;	// L19305
      bool v12164 = v12163 == 1;	// L19306
      bool v12165 = v12161 & v12164;	// L19307
      if (v12165) {	// L19308
        inj13 = 1;	// L19309
      }
      int32_t v12166 = inj13;	// L19311
      uint8_t v12167 = v12166;	// L19312
      sb_inj13[4] = v12167;	// L19313
      int32_t v12168 = op13;	// L19314
      int32_t v12169 = v12168 & 3;	// L19315
      uint8_t v12170 = v12169;	// L19316
      sb_dir13[4] = v12170;	// L19317
      int32_t v12171 = s213;	// L19318
      uint8_t v12172 = v12171;	// L19319
      sb_id13[4] = v12172;	// L19320
      int32_t v12173 = res_vld13;	// L19321
      uint8_t v12174 = v12173;	// L19322
      sb_rvld13[4] = v12174;	// L19323
      int8_t v12175 = resq_wr13;	// L19324
      ap_int<33> v12176 = v12175;	// L19325
      ap_int<33> v12177 = v12176 + 1;	// L19326
      ap_int<33> v12178 = v12177 & 7;	// L19327
      uint8_t v12179 = v12178;	// L19328
      resq_wr13 = v12179;	// L19329
    }
    ap_int<17> v12180 = tx_n13;	// L19331
    txn_r13 = v12180;	// L19332
    ap_int<17> v12181 = tx_s13;	// L19333
    txs_r13 = v12181;	// L19334
    ap_int<17> v12182 = tx_w13;	// L19335
    txw_r13 = v12182;	// L19336
    ap_int<17> v12183 = tx_e13;	// L19337
    txe_r13 = v12183;	// L19338
    int32_t v12184 = crv_vld13;	// L19339
    bool v12185 = v12184 == 1;	// L19340
    if (v12185) {	// L19341
      int32_t v12186 = crv_mode13;	// L19342
      bool v12187 = v12186 == 1;	// L19343
      if (v12187) {	// L19344
        int32_t v12188 = crv_addr13;	// L19345
        int32_t v12189 = v12188 >> 3;	// L19346
        int32_t v12190 = v12189 & 1;	// L19347
        bool v12191 = v12190 == 1;	// L19348
        if (v12191) {	// L19349
          int32_t v12192 = crv_raw13;	// L19350
          int32_t v12193 = crv_addr13;	// L19351
          int32_t v12194 = v12193 & 7;	// L19352
          int v12195 = v12194;	// L19353
          irf13[v12195] = v12192;	// L19354
        } else {
          int32_t v12196 = crv_addr13;	// L19356
          bool v12197 = v12196 == 0;	// L19357
          if (v12197) {	// L19358
            int32_t v12198 = crv_raw13;	// L19359
            int32_t v12199 = v12198 & 255;	// L19360
            dsmask13 = v12199;	// L19361
            int32_t v12200 = crv_raw13;	// L19362
            int32_t v12201 = v12200 >> 8;	// L19363
            int32_t v12202 = v12201 & 7;	// L19364
            cfg_isz13 = v12202;	// L19365
            int32_t v12203 = crv_raw13;	// L19366
            int32_t v12204 = v12203 >> 15;	// L19367
            int32_t v12205 = v12204 & 1;	// L19368
            bool v12206 = v12205 == 1;	// L19369
            if (v12206) {	// L19370
              fetch_en13 = 1;	// L19371
              instr_cnt13 = 0;	// L19372
              iter_cnt13 = 0;	// L19373
            }
          } else {
            int32_t v12207 = crv_addr13;	// L19376
            bool v12208 = v12207 == 1;	// L19377
            if (v12208) {	// L19378
              int32_t v12209 = crv_raw13;	// L19379
              int32_t v12210 = v12209 & 255;	// L19380
              cfg_itsz13 = v12210;	// L19381
            }
          }
        }
      } else {
        int32_t v12211 = crv_addr13;	// L19386
        bool v12212 = v12211 < 8;	// L19387
        int32_t v12213 = dsmask13;	// L19388
        int32_t v12214 = v12213 >> v12211;	// L19389
        int32_t v12215 = v12214 & 1;	// L19390
        bool v12216 = v12215 == 1;	// L19391
        bool v12217 = v12212 & v12216;	// L19392
        if (v12217) {	// L19393
          int32_t v12218 = crv_addr13;	// L19394
          int v12219 = v12218;	// L19395
          int32_t v12220 = drf_full13[v12219];	// L19396
          bool v12221 = v12220 == 0;	// L19397
          if (v12221) {	// L19398
            half v12222 = crv_data13;	// L19399
            int32_t v12223 = crv_addr13;	// L19400
            int v12224 = v12223;	// L19401
            drf13[v12224] = v12222;	// L19402
            int32_t v12225 = crv_addr13;	// L19403
            int v12226 = v12225;	// L19404
            drf_full13[v12226] = 1;	// L19405
          }
        } else {
          half v12227 = crv_data13;	// L19408
          int32_t v12228 = crv_addr13;	// L19409
          int v12229 = v12228;	// L19410
          drf13[v12229] = v12227;	// L19411
        }
      }
    }
    ap_int<17> v12230 = txe_r13;	// L19415
    bool v12231;
    ap_int<17> v12231_tmp = v12230;
    v12231 = v12231_tmp[0];	// L19416
    int32_t v12232 = v12231;	// L19417
    bool v12233 = v12232 == 1;	// L19418
    if (v12233) {	// L19419
      ap_int<17> v12234 = txe_r13;	// L19420
      v11387.write(v12234);	// L19421
    }
    ap_int<17> v12235 = txw_r13;	// L19423
    bool v12236;
    ap_int<17> v12236_tmp = v12235;
    v12236 = v12236_tmp[0];	// L19424
    int32_t v12237 = v12236;	// L19425
    bool v12238 = v12237 == 1;	// L19426
    if (v12238) {	// L19427
      ap_int<17> v12239 = txw_r13;	// L19428
      v11388.write(v12239);	// L19429
    }
    ap_int<17> v12240 = txs_r13;	// L19431
    bool v12241;
    ap_int<17> v12241_tmp = v12240;
    v12241 = v12241_tmp[0];	// L19432
    int32_t v12242 = v12241;	// L19433
    bool v12243 = v12242 == 1;	// L19434
    if (v12243) {	// L19435
      ap_int<17> v12244 = txs_r13;	// L19436
      v11389.write(v12244);	// L19437
    }
    ap_int<17> v12245 = txn_r13;	// L19439
    bool v12246;
    ap_int<17> v12246_tmp = v12245;
    v12246 = v12246_tmp[0];	// L19440
    int32_t v12247 = v12246;	// L19441
    bool v12248 = v12247 == 1;	// L19442
    if (v12248) {	// L19443
      ap_int<17> v12249 = txn_r13;	// L19444
      v11390.write(v12249);	// L19445
    }
  }
}

void node_3_2(
  hls::stream< ap_uint<26> >& v12250,
  hls::stream< ap_uint<26> >& v12251,
  hls::stream< ap_uint<26> >& v12252,
  hls::stream< ap_uint<26> >& v12253,
  hls::stream< ap_uint<26> >& v12254,
  hls::stream< ap_uint<26> >& v12255,
  hls::stream< ap_uint<26> >& v12256,
  hls::stream< ap_uint<26> >& v12257,
  hls::stream< ap_uint<17> >& v12258,
  hls::stream< ap_uint<17> >& v12259,
  hls::stream< ap_uint<17> >& v12260,
  hls::stream< ap_uint<17> >& v12261,
  hls::stream< ap_uint<17> >& v12262,
  hls::stream< ap_uint<17> >& v12263,
  hls::stream< ap_uint<17> >& v12264,
  hls::stream< ap_uint<17> >& v12265
) {	// L19450
  int32_t irf14[8];	// L19483
  #pragma HLS array_partition variable=irf14 complete dim=1

  for (int v12267 = 0; v12267 < 8; v12267++) {	// L19484
    irf14[v12267] = 0;	// L19484
  }
  half drf14[8];	// L19485
  #pragma HLS array_partition variable=drf14 complete dim=1

  for (int v12269 = 0; v12269 < 8; v12269++) {	// L19486
    drf14[v12269] = 0.000000;	// L19486
  }
  int32_t drf_full14[8];	// L19487
  #pragma HLS array_partition variable=drf_full14 complete dim=1

  for (int v12271 = 0; v12271 < 8; v12271++) {	// L19488
    drf_full14[v12271] = 0;	// L19488
  }
  int32_t dsmask14;	// L19489
  dsmask14 = 0;	// L19490
  int32_t crv_vld14;	// L19491
  crv_vld14 = 0;	// L19492
  half crv_data14;	// L19493
  crv_data14 = 0.000000;	// L19494
  int32_t crv_addr14;	// L19495
  crv_addr14 = 0;	// L19496
  int32_t crv_mode14;	// L19497
  crv_mode14 = 0;	// L19498
  int32_t crv_raw14;	// L19499
  crv_raw14 = 0;	// L19500
  int32_t csd_vld14;	// L19501
  csd_vld14 = 0;	// L19502
  ap_uint<26> csd_pkt14;	// L19503
  csd_pkt14 = 0;	// L19504
  int32_t csd_dir14;	// L19505
  csd_dir14 = 0;	// L19506
  int32_t row_id14;	// L19507
  row_id14 = 3;	// L19508
  int32_t col_id14;	// L19509
  col_id14 = 2;	// L19510
  ap_uint<17> txn_r14;	// L19511
  txn_r14 = 0;	// L19512
  ap_uint<17> txs_r14;	// L19513
  txs_r14 = 0;	// L19514
  ap_uint<17> txw_r14;	// L19515
  txw_r14 = 0;	// L19516
  ap_uint<17> txe_r14;	// L19517
  txe_r14 = 0;	// L19518
  half hold_v14[4][2];	// L19519
  #pragma HLS array_partition variable=hold_v14 complete dim=1
  #pragma HLS array_partition variable=hold_v14 complete dim=2

  for (int v12288 = 0; v12288 < 4; v12288++) {	// L19520
    for (int v12289 = 0; v12289 < 2; v12289++) {	// L19520
      hold_v14[v12288][v12289] = 0.000000;	// L19520
    }
  }
  uint8_t hold_cnt14[4];	// L19521
  #pragma HLS array_partition variable=hold_cnt14 complete dim=1

  for (int v12291 = 0; v12291 < 4; v12291++) {	// L19522
    hold_cnt14[v12291] = 0;	// L19522
  }
  int32_t crv_ever14;	// L19523
  crv_ever14 = 0;	// L19524
  int32_t fe_ever14;	// L19525
  fe_ever14 = 0;	// L19526
  ap_uint<26> rbuf14[4][2];	// L19527
  #pragma HLS array_partition variable=rbuf14 complete dim=1
  #pragma HLS array_partition variable=rbuf14 complete dim=2

  for (int v12295 = 0; v12295 < 4; v12295++) {	// L19528
    for (int v12296 = 0; v12296 < 2; v12296++) {	// L19528
      rbuf14[v12295][v12296] = 0;	// L19528
    }
  }
  uint8_t rbcnt14[4];	// L19529
  #pragma HLS array_partition variable=rbcnt14 complete dim=1

  for (int v12298 = 0; v12298 < 4; v12298++) {	// L19530
    rbcnt14[v12298] = 0;	// L19530
  }
  int32_t cfg_isz14;	// L19531
  cfg_isz14 = 0;	// L19532
  int32_t cfg_itsz14;	// L19533
  cfg_itsz14 = 0;	// L19534
  uint8_t fetch_en14;	// L19535
  fetch_en14 = 0;	// L19536
  uint8_t instr_cnt14;	// L19537
  instr_cnt14 = 0;	// L19538
  uint8_t iter_cnt14;	// L19539
  iter_cnt14 = 0;	// L19540
  uint8_t condition_reg14;	// L19541
  condition_reg14 = 0;	// L19542
  uint8_t sb_v14[5];	// L19543
  #pragma HLS array_partition variable=sb_v14 complete dim=1

  for (int v12306 = 0; v12306 < 5; v12306++) {	// L19544
    sb_v14[v12306] = 0;	// L19544
  }
  uint8_t sb_dst14[5];	// L19545
  #pragma HLS array_partition variable=sb_dst14 complete dim=1

  for (int v12308 = 0; v12308 < 5; v12308++) {	// L19546
    sb_dst14[v12308] = 0;	// L19546
  }
  uint8_t sb_cmp14[5];	// L19547
  #pragma HLS array_partition variable=sb_cmp14 complete dim=1

  for (int v12310 = 0; v12310 < 5; v12310++) {	// L19548
    sb_cmp14[v12310] = 0;	// L19548
  }
  uint8_t sb_rtr14[5];	// L19549
  #pragma HLS array_partition variable=sb_rtr14 complete dim=1

  for (int v12312 = 0; v12312 < 5; v12312++) {	// L19550
    sb_rtr14[v12312] = 0;	// L19550
  }
  uint8_t sb_inj14[5];	// L19551
  #pragma HLS array_partition variable=sb_inj14 complete dim=1

  for (int v12314 = 0; v12314 < 5; v12314++) {	// L19552
    sb_inj14[v12314] = 0;	// L19552
  }
  uint8_t sb_dir14[5];	// L19553
  #pragma HLS array_partition variable=sb_dir14 complete dim=1

  for (int v12316 = 0; v12316 < 5; v12316++) {	// L19554
    sb_dir14[v12316] = 0;	// L19554
  }
  uint8_t sb_id14[5];	// L19555
  #pragma HLS array_partition variable=sb_id14 complete dim=1

  for (int v12318 = 0; v12318 < 5; v12318++) {	// L19556
    sb_id14[v12318] = 0;	// L19556
  }
  uint8_t sb_rvld14[5];	// L19557
  #pragma HLS array_partition variable=sb_rvld14 complete dim=1

  for (int v12320 = 0; v12320 < 5; v12320++) {	// L19558
    sb_rvld14[v12320] = 0;	// L19558
  }
  uint8_t sb_ix14[5];	// L19559
  #pragma HLS array_partition variable=sb_ix14 complete dim=1

  for (int v12322 = 0; v12322 < 5; v12322++) {	// L19560
    sb_ix14[v12322] = 0;	// L19560
  }
  half resq14[8];	// L19561
  #pragma HLS array_partition variable=resq14 complete dim=1
#pragma HLS dependence variable=resq14 type=inter dependent=false

  for (int v12324 = 0; v12324 < 8; v12324++) {	// L19562
    resq14[v12324] = 0.000000;	// L19562
  }
  uint8_t cmpq14[8];	// L19563
  #pragma HLS array_partition variable=cmpq14 complete dim=1
#pragma HLS dependence variable=cmpq14 type=inter dependent=false

  for (int v12326 = 0; v12326 < 8; v12326++) {	// L19564
    cmpq14[v12326] = 0;	// L19564
  }
  uint8_t resq_wr14;	// L19565
  resq_wr14 = 0;	// L19566
  l_S_t_0_t14: for (int t14 = 0; t14 < 374; t14++) {	// L19567
  #pragma HLS pipeline II=1
    ap_uint<26> p_w14;	// L19568
    p_w14 = 0;	// L19569
    ap_uint<26> p_e14;	// L19570
    p_e14 = 0;	// L19571
    ap_uint<26> p_n14;	// L19572
    p_n14 = 0;	// L19573
    ap_uint<26> p_s14;	// L19574
    p_s14 = 0;	// L19575
    uint8_t v12333 = rbcnt14[0];	// L19576
    int32_t v12334 = v12333;	// L19577
    bool v12335 = v12334 < 2;	// L19578
    if (v12335) {	// L19579
      ap_uint<26> v12336;
      bool v12337 = v12250.read_nb(v12336);
	// L19580
      ap_uint<26> gw14;	// L19581
      gw14 = v12336;	// L19582
      bool okw14;	// L19583
      okw14 = v12337;	// L19584
      bool v12340 = okw14;	// L19585
      if (v12340) {	// L19586
        ap_int<26> v12341 = gw14;	// L19587
        p_w14 = v12341;	// L19588
      }
    }
    uint8_t v12342 = rbcnt14[1];	// L19591
    int32_t v12343 = v12342;	// L19592
    bool v12344 = v12343 < 2;	// L19593
    if (v12344) {	// L19594
      ap_uint<26> v12345;
      bool v12346 = v12251.read_nb(v12345);
	// L19595
      ap_uint<26> ge14;	// L19596
      ge14 = v12345;	// L19597
      bool oke14;	// L19598
      oke14 = v12346;	// L19599
      bool v12349 = oke14;	// L19600
      if (v12349) {	// L19601
        ap_int<26> v12350 = ge14;	// L19602
        p_e14 = v12350;	// L19603
      }
    }
    uint8_t v12351 = rbcnt14[2];	// L19606
    int32_t v12352 = v12351;	// L19607
    bool v12353 = v12352 < 2;	// L19608
    if (v12353) {	// L19609
      ap_uint<26> v12354;
      bool v12355 = v12252.read_nb(v12354);
	// L19610
      ap_uint<26> gn14;	// L19611
      gn14 = v12354;	// L19612
      bool okn14;	// L19613
      okn14 = v12355;	// L19614
      bool v12358 = okn14;	// L19615
      if (v12358) {	// L19616
        ap_int<26> v12359 = gn14;	// L19617
        p_n14 = v12359;	// L19618
      }
    }
    uint8_t v12360 = rbcnt14[3];	// L19621
    int32_t v12361 = v12360;	// L19622
    bool v12362 = v12361 < 2;	// L19623
    if (v12362) {	// L19624
      ap_uint<26> v12363;
      bool v12364 = v12253.read_nb(v12363);
	// L19625
      ap_uint<26> gs14;	// L19626
      gs14 = v12363;	// L19627
      bool oks14;	// L19628
      oks14 = v12364;	// L19629
      bool v12367 = oks14;	// L19630
      if (v12367) {	// L19631
        ap_int<26> v12368 = gs14;	// L19632
        p_s14 = v12368;	// L19633
      }
    }
    ap_uint<26> fin14[4];	// L19636
    for (int v12370 = 0; v12370 < 4; v12370++) {	// L19637
      fin14[v12370] = 0;	// L19637
    }
    ap_int<26> v12371 = p_w14;	// L19638
    fin14[0] = v12371;	// L19639
    ap_int<26> v12372 = p_e14;	// L19640
    fin14[1] = v12372;	// L19641
    ap_int<26> v12373 = p_n14;	// L19642
    fin14[2] = v12373;	// L19643
    ap_int<26> v12374 = p_s14;	// L19644
    fin14[3] = v12374;	// L19645
    l_S_d_0_d56: for (int d56 = 0; d56 < 4; d56++) {	// L19646
      ap_uint<26> v12376 = fin14[d56];	// L19647
      bool v12377;
      ap_int<26> v12377_tmp = v12376;
      v12377 = v12377_tmp[25];	// L19648
      int32_t v12378 = v12377;	// L19649
      bool v12379 = v12378 == 1;	// L19650
      uint8_t v12380 = rbcnt14[d56];	// L19651
      int32_t v12381 = v12380;	// L19652
      bool v12382 = v12381 < 2;	// L19653
      bool v12383 = v12379 & v12382;	// L19654
      if (v12383) {	// L19655
        ap_uint<26> v12384 = fin14[d56];	// L19656
        uint8_t v12385 = rbcnt14[d56];	// L19657
        int v12386 = v12385;	// L19658
        rbuf14[d56][v12386] = v12384;	// L19659
        uint8_t v12387 = rbcnt14[d56];	// L19660
        ap_int<33> v12388 = v12387;	// L19661
        ap_int<33> v12389 = v12388 + 1;	// L19662
        uint8_t v12390 = v12389;	// L19663
        rbcnt14[d56] = v12390;	// L19664
      }
    }
    ap_uint<26> hd14[4];	// L19667
    for (int v12392 = 0; v12392 < 4; v12392++) {	// L19668
      hd14[v12392] = 0;	// L19668
    }
    int32_t hvld14[4];	// L19669
    for (int v12394 = 0; v12394 < 4; v12394++) {	// L19670
      hvld14[v12394] = 0;	// L19670
    }
    int32_t hit14[4];	// L19671
    for (int v12396 = 0; v12396 < 4; v12396++) {	// L19672
      hit14[v12396] = 0;	// L19672
    }
    int32_t axis14[4];	// L19673
    for (int v12398 = 0; v12398 < 4; v12398++) {	// L19674
      axis14[v12398] = 0;	// L19674
    }
    int32_t v12399 = col_id14;	// L19675
    axis14[0] = v12399;	// L19676
    int32_t v12400 = col_id14;	// L19677
    axis14[1] = v12400;	// L19678
    int32_t v12401 = row_id14;	// L19679
    axis14[2] = v12401;	// L19680
    int32_t v12402 = row_id14;	// L19681
    axis14[3] = v12402;	// L19682
    l_S_d_1_d57: for (int d57 = 0; d57 < 4; d57++) {	// L19683
      uint8_t v12404 = rbcnt14[d57];	// L19684
      int32_t v12405 = v12404;	// L19685
      bool v12406 = v12405 > 0;	// L19686
      if (v12406) {	// L19687
        ap_uint<26> v12407 = rbuf14[d57][0];	// L19688
        hd14[d57] = v12407;	// L19689
        hvld14[d57] = 1;	// L19690
        ap_uint<26> v12408 = hd14[d57];	// L19691
        ap_int<4> v12409;
        ap_int<26> v12409_tmp = v12408;
        v12409 = v12409_tmp(24, 21);	// L19692
        int32_t v12410 = axis14[d57];	// L19693
        int32_t v12411 = v12409;	// L19694
        bool v12412 = v12411 == v12410;	// L19695
        if (v12412) {	// L19696
          hit14[d57] = 1;	// L19697
        }
      }
    }
    ap_uint<26> o_crv14;	// L19701
    o_crv14 = 0;	// L19702
    int32_t crv_in14;	// L19703
    crv_in14 = -1;	// L19704
    int32_t v12415 = hit14[3];	// L19705
    bool v12416 = v12415 == 1;	// L19706
    if (v12416) {	// L19707
      ap_uint<26> v12417 = hd14[3];	// L19708
      o_crv14 = v12417;	// L19709
      crv_in14 = 3;	// L19710
    } else {
      int32_t v12418 = hit14[2];	// L19712
      bool v12419 = v12418 == 1;	// L19713
      if (v12419) {	// L19714
        ap_uint<26> v12420 = hd14[2];	// L19715
        o_crv14 = v12420;	// L19716
        crv_in14 = 2;	// L19717
      } else {
        int32_t v12421 = hit14[1];	// L19719
        bool v12422 = v12421 == 1;	// L19720
        if (v12422) {	// L19721
          ap_uint<26> v12423 = hd14[1];	// L19722
          o_crv14 = v12423;	// L19723
          crv_in14 = 1;	// L19724
        } else {
          int32_t v12424 = hit14[0];	// L19726
          bool v12425 = v12424 == 1;	// L19727
          if (v12425) {	// L19728
            ap_uint<26> v12426 = hd14[0];	// L19729
            o_crv14 = v12426;	// L19730
            crv_in14 = 0;	// L19731
          }
        }
      }
    }
    int32_t pop14[4];	// L19736
    for (int v12428 = 0; v12428 < 4; v12428++) {	// L19737
      pop14[v12428] = 0;	// L19737
    }
    int32_t inj_done14;	// L19738
    inj_done14 = 0;	// L19739
    int32_t idir14;	// L19740
    idir14 = -1;	// L19741
    ap_int<26> v12431 = csd_pkt14;	// L19742
    bool v12432;
    ap_int<26> v12432_tmp = v12431;
    v12432 = v12432_tmp[25];	// L19743
    int32_t v12433 = v12432;	// L19744
    bool v12434 = v12433 == 1;	// L19745
    if (v12434) {	// L19746
      int32_t v12435 = csd_dir14;	// L19747
      ap_int<33> v12436 = v12435;	// L19748
      ap_int<33> v12437 = 3 - v12436;	// L19749
      int32_t v12438 = v12437;	// L19750
      idir14 = v12438;	// L19751
    }
    int32_t v12439 = idir14;	// L19753
    bool v12440 = v12439 == 0;	// L19754
    if (v12440) {	// L19755
      ap_int<26> v12441 = csd_pkt14;	// L19756
      bool v12442 = v12254.write_nb(v12441);
	// L19757
      if (v12442) {	// L19758
        inj_done14 = 1;	// L19759
      }
    } else {
      int32_t v12443 = hvld14[0];	// L19762
      bool v12444 = v12443 == 1;	// L19763
      int32_t v12445 = hit14[0];	// L19764
      bool v12446 = v12445 == 0;	// L19765
      bool v12447 = v12444 & v12446;	// L19766
      if (v12447) {	// L19767
        ap_uint<26> v12448 = hd14[0];	// L19768
        bool v12449 = v12254.write_nb(v12448);
	// L19769
        if (v12449) {	// L19770
          pop14[0] = 1;	// L19771
        }
      }
    }
    int32_t v12450 = idir14;	// L19775
    bool v12451 = v12450 == 1;	// L19776
    if (v12451) {	// L19777
      ap_int<26> v12452 = csd_pkt14;	// L19778
      bool v12453 = v12255.write_nb(v12452);
	// L19779
      if (v12453) {	// L19780
        inj_done14 = 1;	// L19781
      }
    } else {
      int32_t v12454 = hvld14[1];	// L19784
      bool v12455 = v12454 == 1;	// L19785
      int32_t v12456 = hit14[1];	// L19786
      bool v12457 = v12456 == 0;	// L19787
      bool v12458 = v12455 & v12457;	// L19788
      if (v12458) {	// L19789
        ap_uint<26> v12459 = hd14[1];	// L19790
        bool v12460 = v12255.write_nb(v12459);
	// L19791
        if (v12460) {	// L19792
          pop14[1] = 1;	// L19793
        }
      }
    }
    int32_t v12461 = idir14;	// L19797
    bool v12462 = v12461 == 2;	// L19798
    if (v12462) {	// L19799
      ap_int<26> v12463 = csd_pkt14;	// L19800
      bool v12464 = v12256.write_nb(v12463);
	// L19801
      if (v12464) {	// L19802
        inj_done14 = 1;	// L19803
      }
    } else {
      int32_t v12465 = hvld14[2];	// L19806
      bool v12466 = v12465 == 1;	// L19807
      int32_t v12467 = hit14[2];	// L19808
      bool v12468 = v12467 == 0;	// L19809
      bool v12469 = v12466 & v12468;	// L19810
      if (v12469) {	// L19811
        ap_uint<26> v12470 = hd14[2];	// L19812
        bool v12471 = v12256.write_nb(v12470);
	// L19813
        if (v12471) {	// L19814
          pop14[2] = 1;	// L19815
        }
      }
    }
    int32_t v12472 = idir14;	// L19819
    bool v12473 = v12472 == 3;	// L19820
    if (v12473) {	// L19821
      ap_int<26> v12474 = csd_pkt14;	// L19822
      bool v12475 = v12257.write_nb(v12474);
	// L19823
      if (v12475) {	// L19824
        inj_done14 = 1;	// L19825
      }
    } else {
      int32_t v12476 = hvld14[3];	// L19828
      bool v12477 = v12476 == 1;	// L19829
      int32_t v12478 = hit14[3];	// L19830
      bool v12479 = v12478 == 0;	// L19831
      bool v12480 = v12477 & v12479;	// L19832
      if (v12480) {	// L19833
        ap_uint<26> v12481 = hd14[3];	// L19834
        bool v12482 = v12257.write_nb(v12481);
	// L19835
        if (v12482) {	// L19836
          pop14[3] = 1;	// L19837
        }
      }
    }
    int32_t v12483 = crv_in14;	// L19841
    bool v12484 = v12483 >= 0;	// L19842
    if (v12484) {	// L19843
      int32_t v12485 = crv_in14;	// L19844
      int v12486 = v12485;	// L19845
      pop14[v12486] = 1;	// L19846
    }
    l_S_d_2_d58: for (int d58 = 0; d58 < 4; d58++) {	// L19848
      int32_t v12488 = pop14[d58];	// L19849
      bool v12489 = v12488 == 1;	// L19850
      if (v12489) {	// L19851
        l_S_sft_2_sft14: for (int sft14 = 0; sft14 < 1; sft14++) {	// L19852
          ap_uint<26> v12491 = rbuf14[d58][(sft14 + 1)];	// L19853
          rbuf14[d58][sft14] = v12491;	// L19854
        }
        uint8_t v12492 = rbcnt14[d58];	// L19856
        ap_int<33> v12493 = v12492;	// L19857
        ap_int<33> v12494 = v12493 - 1;	// L19858
        uint8_t v12495 = v12494;	// L19859
        rbcnt14[d58] = v12495;	// L19860
      }
    }
    int32_t v12496 = inj_done14;	// L19863
    bool v12497 = v12496 == 1;	// L19864
    if (v12497) {	// L19865
      csd_pkt14 = 0;	// L19866
    }
    ap_int<26> v12498 = o_crv14;	// L19868
    bool v12499;
    ap_int<26> v12499_tmp = v12498;
    v12499 = v12499_tmp[25];	// L19869
    int32_t v12500 = v12499;	// L19870
    crv_vld14 = v12500;	// L19871
    int32_t v12501 = crv_vld14;	// L19872
    bool v12502 = v12501 == 1;	// L19873
    if (v12502) {	// L19874
      crv_ever14 = 1;	// L19875
    }
    ap_int<26> v12503 = o_crv14;	// L19877
    int16_t v12504;
    ap_int<26> v12504_tmp = v12503;
    v12504 = v12504_tmp(15, 0);	// L19878
    half v12505;
    union { uint16_t from; half to;} _converter_v12504_to_v12505 = {};
    _converter_v12504_to_v12505.from = v12504;
    v12505 = _converter_v12504_to_v12505.to;	// L19879
    crv_data14 = v12505;	// L19880
    ap_int<26> v12506 = o_crv14;	// L19881
    ap_int<4> v12507;
    ap_int<26> v12507_tmp = v12506;
    v12507 = v12507_tmp(19, 16);	// L19882
    int32_t v12508 = v12507;	// L19883
    crv_addr14 = v12508;	// L19884
    ap_int<26> v12509 = o_crv14;	// L19885
    bool v12510;
    ap_int<26> v12510_tmp = v12509;
    v12510 = v12510_tmp[20];	// L19886
    int32_t v12511 = v12510;	// L19887
    crv_mode14 = v12511;	// L19888
    ap_int<26> v12512 = o_crv14;	// L19889
    int16_t v12513;
    ap_int<26> v12513_tmp = v12512;
    v12513 = v12513_tmp(15, 0);	// L19890
    int32_t v12514 = v12513;	// L19891
    crv_raw14 = v12514;	// L19892
    half rxv14[4];	// L19893
    for (int v12516 = 0; v12516 < 4; v12516++) {	// L19894
      rxv14[v12516] = 0.000000;	// L19894
    }
    int32_t rxvld14[4];	// L19895
    for (int v12518 = 0; v12518 < 4; v12518++) {	// L19896
      rxvld14[v12518] = 0;	// L19896
    }
    uint8_t v12519 = hold_cnt14[0];	// L19897
    int32_t v12520 = v12519;	// L19898
    bool v12521 = v12520 < 2;	// L19899
    if (v12521) {	// L19900
      ap_uint<17> v12522;
      bool v12523 = v12258.read_nb(v12522);
	// L19901
      ap_uint<17> sgn14;	// L19902
      sgn14 = v12522;	// L19903
      bool sqn14;	// L19904
      sqn14 = v12523;	// L19905
      bool v12526 = sqn14;	// L19906
      int32_t v12527 = v12526;	// L19907
      bool v12528 = v12527 == 1;	// L19908
      if (v12528) {	// L19909
        ap_int<17> v12529 = sgn14;	// L19910
        int16_t v12530;
        ap_int<17> v12530_tmp = v12529;
        v12530 = v12530_tmp(16, 1);	// L19911
        half v12531;
        union { uint16_t from; half to;} _converter_v12530_to_v12531 = {};
        _converter_v12530_to_v12531.from = v12530;
        v12531 = _converter_v12530_to_v12531.to;	// L19912
        rxv14[0] = v12531;	// L19913
        rxvld14[0] = 1;	// L19914
      }
    }
    uint8_t v12532 = hold_cnt14[1];	// L19917
    int32_t v12533 = v12532;	// L19918
    bool v12534 = v12533 < 2;	// L19919
    if (v12534) {	// L19920
      ap_uint<17> v12535;
      bool v12536 = v12259.read_nb(v12535);
	// L19921
      ap_uint<17> sgs14;	// L19922
      sgs14 = v12535;	// L19923
      bool sqs14;	// L19924
      sqs14 = v12536;	// L19925
      bool v12539 = sqs14;	// L19926
      int32_t v12540 = v12539;	// L19927
      bool v12541 = v12540 == 1;	// L19928
      if (v12541) {	// L19929
        ap_int<17> v12542 = sgs14;	// L19930
        int16_t v12543;
        ap_int<17> v12543_tmp = v12542;
        v12543 = v12543_tmp(16, 1);	// L19931
        half v12544;
        union { uint16_t from; half to;} _converter_v12543_to_v12544 = {};
        _converter_v12543_to_v12544.from = v12543;
        v12544 = _converter_v12543_to_v12544.to;	// L19932
        rxv14[1] = v12544;	// L19933
        rxvld14[1] = 1;	// L19934
      }
    }
    uint8_t v12545 = hold_cnt14[2];	// L19937
    int32_t v12546 = v12545;	// L19938
    bool v12547 = v12546 < 2;	// L19939
    if (v12547) {	// L19940
      ap_uint<17> v12548;
      bool v12549 = v12260.read_nb(v12548);
	// L19941
      ap_uint<17> sgw14;	// L19942
      sgw14 = v12548;	// L19943
      bool sqw14;	// L19944
      sqw14 = v12549;	// L19945
      bool v12552 = sqw14;	// L19946
      int32_t v12553 = v12552;	// L19947
      bool v12554 = v12553 == 1;	// L19948
      if (v12554) {	// L19949
        ap_int<17> v12555 = sgw14;	// L19950
        int16_t v12556;
        ap_int<17> v12556_tmp = v12555;
        v12556 = v12556_tmp(16, 1);	// L19951
        half v12557;
        union { uint16_t from; half to;} _converter_v12556_to_v12557 = {};
        _converter_v12556_to_v12557.from = v12556;
        v12557 = _converter_v12556_to_v12557.to;	// L19952
        rxv14[2] = v12557;	// L19953
        rxvld14[2] = 1;	// L19954
      }
    }
    uint8_t v12558 = hold_cnt14[3];	// L19957
    int32_t v12559 = v12558;	// L19958
    bool v12560 = v12559 < 2;	// L19959
    if (v12560) {	// L19960
      ap_uint<17> v12561;
      bool v12562 = v12261.read_nb(v12561);
	// L19961
      ap_uint<17> sge14;	// L19962
      sge14 = v12561;	// L19963
      bool sqe14;	// L19964
      sqe14 = v12562;	// L19965
      bool v12565 = sqe14;	// L19966
      int32_t v12566 = v12565;	// L19967
      bool v12567 = v12566 == 1;	// L19968
      if (v12567) {	// L19969
        ap_int<17> v12568 = sge14;	// L19970
        int16_t v12569;
        ap_int<17> v12569_tmp = v12568;
        v12569 = v12569_tmp(16, 1);	// L19971
        half v12570;
        union { uint16_t from; half to;} _converter_v12569_to_v12570 = {};
        _converter_v12569_to_v12570.from = v12569;
        v12570 = _converter_v12569_to_v12570.to;	// L19972
        rxv14[3] = v12570;	// L19973
        rxvld14[3] = 1;	// L19974
      }
    }
    l_S_d_4_d59: for (int d59 = 0; d59 < 4; d59++) {	// L19977
      int32_t v12572 = rxvld14[d59];	// L19978
      bool v12573 = v12572 == 1;	// L19979
      if (v12573) {	// L19980
        half v12574 = rxv14[d59];	// L19981
        uint8_t v12575 = hold_cnt14[d59];	// L19982
        int v12576 = v12575;	// L19983
        hold_v14[d59][v12576] = v12574;	// L19984
        uint8_t v12577 = hold_cnt14[d59];	// L19985
        ap_int<33> v12578 = v12577;	// L19986
        ap_int<33> v12579 = v12578 + 1;	// L19987
        uint8_t v12580 = v12579;	// L19988
        hold_cnt14[d59] = v12580;	// L19989
      }
    }
    ap_uint<17> tx_n14;	// L19992
    tx_n14 = 0;	// L19993
    ap_uint<17> tx_s14;	// L19994
    tx_s14 = 0;	// L19995
    ap_uint<17> tx_w14;	// L19996
    tx_w14 = 0;	// L19997
    ap_uint<17> tx_e14;	// L19998
    tx_e14 = 0;	// L19999
    uint8_t v12585 = sb_v14[0];	// L20000
    int32_t v12586 = v12585;	// L20001
    bool v12587 = v12586 == 1;	// L20002
    if (v12587) {	// L20003
      uint8_t v12588 = sb_ix14[0];	// L20004
      int v12589 = v12588;	// L20005
      half v12590 = resq14[v12589];	// L20006
      half wb14;
#pragma HLS dependence variable=wb14 type=inter dependent=false	// L20007
      wb14 = v12590;	// L20008
      uint8_t v12592 = sb_cmp14[0];	// L20009
      int32_t v12593 = v12592;	// L20010
      bool v12594 = v12593 == 1;	// L20011
      if (v12594) {	// L20012
        uint8_t v12595 = sb_ix14[0];	// L20013
        int v12596 = v12595;	// L20014
        uint8_t v12597 = cmpq14[v12596];	// L20015
        condition_reg14 = v12597;	// L20016
      }
      uint8_t v12598 = sb_rtr14[0];	// L20018
      int32_t v12599 = v12598;	// L20019
      bool v12600 = v12599 == 1;	// L20020
      if (v12600) {	// L20021
        uint8_t v12601 = sb_inj14[0];	// L20022
        int32_t v12602 = v12601;	// L20023
        bool v12603 = v12602 == 1;	// L20024
        ap_int<26> v12604 = csd_pkt14;	// L20025
        bool v12605;
        ap_int<26> v12605_tmp = v12604;
        v12605 = v12605_tmp[25];	// L20026
        int32_t v12606 = v12605;	// L20027
        bool v12607 = v12606 == 0;	// L20028
        bool v12608 = v12603 & v12607;	// L20029
        if (v12608) {	// L20030
          half v12609 = wb14;	// L20031
          uint16_t v12610;
          union { half from; uint16_t to;} _converter_v12609_to_v12610 = {};
          _converter_v12609_to_v12610.from = v12609;
          v12610 = _converter_v12609_to_v12610.to;	// L20032
          ap_int<26> v12611 = csd_pkt14;	// L20033
          ap_int<26> v12612;
          ap_int<26> v12612_tmp = v12611;
          v12612_tmp(15, 0) = v12610;
          v12612 = v12612_tmp;	// L20034
          csd_pkt14 = v12612;	// L20035
          uint8_t v12613 = sb_dst14[0];	// L20036
          ap_uint<4> v12614 = v12613;	// L20037
          ap_int<26> v12615 = csd_pkt14;	// L20038
          ap_int<26> v12616;
          ap_int<26> v12616_tmp = v12615;
          v12616_tmp(19, 16) = v12614;
          v12616 = v12616_tmp;	// L20039
          csd_pkt14 = v12616;	// L20040
          uint8_t v12617 = sb_id14[0];	// L20041
          ap_uint<4> v12618 = v12617;	// L20042
          ap_int<26> v12619 = csd_pkt14;	// L20043
          ap_int<26> v12620;
          ap_int<26> v12620_tmp = v12619;
          v12620_tmp(24, 21) = v12618;
          v12620 = v12620_tmp;	// L20044
          csd_pkt14 = v12620;	// L20045
          uint8_t v12621 = sb_rvld14[0];	// L20046
          bool v12622 = v12621;	// L20047
          ap_int<26> v12623 = csd_pkt14;	// L20048
          ap_int<26> v12624;
          ap_int<26> v12624_tmp = v12623;
          v12624_tmp[25] = v12622;          v12624 = v12624_tmp;	// L20049
          csd_pkt14 = v12624;	// L20050
          uint8_t v12625 = sb_dir14[0];	// L20051
          int32_t v12626 = v12625;	// L20052
          csd_dir14 = v12626;	// L20053
        }
      } else {
        uint8_t v12627 = sb_dst14[0];	// L20056
        int32_t v12628 = v12627;	// L20057
        bool v12629 = v12628 >= 12;	// L20058
        if (v12629) {	// L20059
          ap_uint<17> tw014;	// L20060
          tw014 = 0;	// L20061
          uint8_t v12631 = sb_rvld14[0];	// L20062
          bool v12632 = v12631;	// L20063
          ap_int<17> v12633 = tw014;	// L20064
          ap_int<17> v12634;
          ap_int<17> v12634_tmp = v12633;
          v12634_tmp[0] = v12632;          v12634 = v12634_tmp;	// L20065
          tw014 = v12634;	// L20066
          half v12635 = wb14;	// L20067
          uint16_t v12636;
          union { half from; uint16_t to;} _converter_v12635_to_v12636 = {};
          _converter_v12635_to_v12636.from = v12635;
          v12636 = _converter_v12635_to_v12636.to;	// L20068
          ap_int<17> v12637 = tw014;	// L20069
          ap_int<17> v12638;
          ap_int<17> v12638_tmp = v12637;
          v12638_tmp(16, 1) = v12636;
          v12638 = v12638_tmp;	// L20070
          tw014 = v12638;	// L20071
          uint8_t v12639 = sb_dst14[0];	// L20072
          int32_t v12640 = v12639;	// L20073
          int32_t v12641 = v12640 & 3;	// L20074
          bool v12642 = v12641 == 0;	// L20075
          if (v12642) {	// L20076
            ap_int<17> v12643 = tw014;	// L20077
            tx_n14 = v12643;	// L20078
          } else {
            uint8_t v12644 = sb_dst14[0];	// L20080
            int32_t v12645 = v12644;	// L20081
            int32_t v12646 = v12645 & 3;	// L20082
            bool v12647 = v12646 == 1;	// L20083
            if (v12647) {	// L20084
              ap_int<17> v12648 = tw014;	// L20085
              tx_s14 = v12648;	// L20086
            } else {
              uint8_t v12649 = sb_dst14[0];	// L20088
              int32_t v12650 = v12649;	// L20089
              int32_t v12651 = v12650 & 3;	// L20090
              bool v12652 = v12651 == 2;	// L20091
              if (v12652) {	// L20092
                ap_int<17> v12653 = tw014;	// L20093
                tx_w14 = v12653;	// L20094
              } else {
                ap_int<17> v12654 = tw014;	// L20096
                tx_e14 = v12654;	// L20097
              }
            }
          }
        } else {
          uint8_t v12655 = sb_rvld14[0];	// L20102
          int32_t v12656 = v12655;	// L20103
          bool v12657 = v12656 == 1;	// L20104
          if (v12657) {	// L20105
            uint8_t v12658 = sb_dst14[0];	// L20106
            int32_t v12659 = v12658;	// L20107
            bool v12660 = v12659 < 8;	// L20108
            int32_t v12661 = dsmask14;	// L20109
            int32_t v12662 = v12661 >> v12659;	// L20110
            int32_t v12663 = v12662 & 1;	// L20111
            bool v12664 = v12663 == 1;	// L20112
            bool v12665 = v12660 & v12664;	// L20113
            if (v12665) {	// L20114
              uint8_t v12666 = sb_dst14[0];	// L20115
              int v12667 = v12666;	// L20116
              int32_t v12668 = drf_full14[v12667];	// L20117
              bool v12669 = v12668 == 0;	// L20118
              if (v12669) {	// L20119
                half v12670 = wb14;	// L20120
                uint8_t v12671 = sb_dst14[0];	// L20121
                int v12672 = v12671;	// L20122
                drf14[v12672] = v12670;	// L20123
                uint8_t v12673 = sb_dst14[0];	// L20124
                int v12674 = v12673;	// L20125
                drf_full14[v12674] = 1;	// L20126
              }
            } else {
              half v12675 = wb14;	// L20129
              uint8_t v12676 = sb_dst14[0];	// L20130
              int32_t v12677 = v12676;	// L20131
              int32_t v12678 = v12677 & 7;	// L20132
              int v12679 = v12678;	// L20133
              drf14[v12679] = v12675;	// L20134
            }
          }
        }
      }
    }
    int32_t pc14;	// L20140
    pc14 = -1;	// L20141
    int8_t v12681 = fetch_en14;	// L20142
    int32_t v12682 = v12681;	// L20143
    bool v12683 = v12682 == 1;	// L20144
    if (v12683) {	// L20145
      int8_t v12684 = instr_cnt14;	// L20146
      int32_t v12685 = v12684;	// L20147
      pc14 = v12685;	// L20148
    }
    int8_t v12686 = fetch_en14;	// L20150
    int32_t v12687 = v12686;	// L20151
    bool v12688 = v12687 == 1;	// L20152
    if (v12688) {	// L20153
      fe_ever14 = 1;	// L20154
    }
    int32_t instr14;	// L20156
    instr14 = 0;	// L20157
    int32_t v12690 = pc14;	// L20158
    bool v12691 = v12690 >= 0;	// L20159
    if (v12691) {	// L20160
      int32_t v12692 = pc14;	// L20161
      int v12693 = v12692;	// L20162
      int32_t v12694 = irf14[v12693];	// L20163
      instr14 = v12694;	// L20164
    }
    int32_t v12695 = instr14;	// L20166
    int32_t v12696 = v12695 & 15;	// L20167
    int32_t op14;	// L20168
    op14 = v12696;	// L20169
    int32_t v12698 = instr14;	// L20170
    int32_t v12699 = v12698 >> 4;	// L20171
    int32_t v12700 = v12699 & 15;	// L20172
    int32_t dst14;	// L20173
    dst14 = v12700;	// L20174
    int32_t v12702 = instr14;	// L20175
    int32_t v12703 = v12702 >> 8;	// L20176
    int32_t v12704 = v12703 & 15;	// L20177
    int32_t s114;	// L20178
    s114 = v12704;	// L20179
    int32_t v12706 = instr14;	// L20180
    int32_t v12707 = v12706 >> 12;	// L20181
    int32_t v12708 = v12707 & 15;	// L20182
    int32_t s214;	// L20183
    s214 = v12708;	// L20184
    half a14;	// L20185
    a14 = 0.000000;	// L20186
    half b14;	// L20187
    b14 = 0.000000;	// L20188
    int32_t v12712 = s114;	// L20189
    bool v12713 = v12712 >= 12;	// L20190
    if (v12713) {	// L20191
      int32_t v12714 = s114;	// L20192
      int32_t v12715 = v12714 & 3;	// L20193
      int v12716 = v12715;	// L20194
      half v12717 = hold_v14[v12716][0];	// L20195
      a14 = v12717;	// L20196
    } else {
      int32_t v12718 = s114;	// L20198
      int v12719 = v12718;	// L20199
      half v12720 = drf14[v12719];	// L20200
      a14 = v12720;	// L20201
    }
    int32_t v12721 = s214;	// L20203
    bool v12722 = v12721 >= 12;	// L20204
    if (v12722) {	// L20205
      int32_t v12723 = s214;	// L20206
      int32_t v12724 = v12723 & 3;	// L20207
      int v12725 = v12724;	// L20208
      half v12726 = hold_v14[v12725][0];	// L20209
      b14 = v12726;	// L20210
    } else {
      int32_t v12727 = s214;	// L20212
      int v12728 = v12727;	// L20213
      half v12729 = drf14[v12728];	// L20214
      b14 = v12729;	// L20215
    }
    int32_t a_vld14;	// L20217
    a_vld14 = 1;	// L20218
    int32_t b_vld14;	// L20219
    b_vld14 = 1;	// L20220
    int32_t v12732 = s114;	// L20221
    bool v12733 = v12732 >= 12;	// L20222
    if (v12733) {	// L20223
      a_vld14 = 0;	// L20224
      int32_t v12734 = s114;	// L20225
      int32_t v12735 = v12734 & 3;	// L20226
      int v12736 = v12735;	// L20227
      uint8_t v12737 = hold_cnt14[v12736];	// L20228
      int32_t v12738 = v12737;	// L20229
      bool v12739 = v12738 > 0;	// L20230
      if (v12739) {	// L20231
        a_vld14 = 1;	// L20232
      }
    }
    int32_t v12740 = s214;	// L20235
    bool v12741 = v12740 >= 12;	// L20236
    if (v12741) {	// L20237
      b_vld14 = 0;	// L20238
      int32_t v12742 = s214;	// L20239
      int32_t v12743 = v12742 & 3;	// L20240
      int v12744 = v12743;	// L20241
      uint8_t v12745 = hold_cnt14[v12744];	// L20242
      int32_t v12746 = v12745;	// L20243
      bool v12747 = v12746 > 0;	// L20244
      if (v12747) {	// L20245
        b_vld14 = 1;	// L20246
      }
    }
    int32_t v12748 = s114;	// L20249
    bool v12749 = v12748 < 8;	// L20250
    int32_t v12750 = dsmask14;	// L20251
    int32_t v12751 = v12750 >> v12748;	// L20252
    int32_t v12752 = v12751 & 1;	// L20253
    bool v12753 = v12752 == 1;	// L20254
    bool v12754 = v12749 & v12753;	// L20255
    if (v12754) {	// L20256
      int32_t v12755 = s114;	// L20257
      int v12756 = v12755;	// L20258
      int32_t v12757 = drf_full14[v12756];	// L20259
      bool v12758 = v12757 == 0;	// L20260
      if (v12758) {	// L20261
        a_vld14 = 0;	// L20262
      }
    }
    int32_t v12759 = s214;	// L20265
    bool v12760 = v12759 < 8;	// L20266
    int32_t v12761 = dsmask14;	// L20267
    int32_t v12762 = v12761 >> v12759;	// L20268
    int32_t v12763 = v12762 & 1;	// L20269
    bool v12764 = v12763 == 1;	// L20270
    bool v12765 = v12760 & v12764;	// L20271
    if (v12765) {	// L20272
      int32_t v12766 = s214;	// L20273
      int v12767 = v12766;	// L20274
      int32_t v12768 = drf_full14[v12767];	// L20275
      bool v12769 = v12768 == 0;	// L20276
      if (v12769) {	// L20277
        b_vld14 = 0;	// L20278
      }
    }
    int32_t binop14;	// L20281
    binop14 = 0;	// L20282
    int32_t v12771 = op14;	// L20283
    bool v12772 = v12771 == 0;	// L20284
    bool v12773 = v12771 == 1;	// L20285
    bool v12774 = v12771 == 2;	// L20286
    bool v12775 = v12771 == 8;	// L20287
    bool v12776 = v12771 == 9;	// L20288
    bool v12777 = v12772 | v12773;	// L20289
    bool v12778 = v12777 | v12774;	// L20290
    bool v12779 = v12778 | v12775;	// L20291
    bool v12780 = v12779 | v12776;	// L20292
    if (v12780) {	// L20293
      binop14 = 1;	// L20294
    }
    int32_t raw14;	// L20296
    raw14 = 0;	// L20297
    int32_t cmp_busy14;	// L20298
    cmp_busy14 = 0;	// L20299
    l_S_k_5_k28: for (int k28 = 0; k28 < 4; k28++) {	// L20300
      uint8_t v12784 = sb_v14[(k28 + 1)];	// L20301
      int32_t v12785 = v12784;	// L20302
      bool v12786 = v12785 == 1;	// L20303
      uint8_t v12787 = sb_rtr14[(k28 + 1)];	// L20304
      int32_t v12788 = v12787;	// L20305
      bool v12789 = v12788 == 0;	// L20306
      uint8_t v12790 = sb_dst14[(k28 + 1)];	// L20307
      int32_t v12791 = v12790;	// L20308
      bool v12792 = v12791 < 12;	// L20309
      bool v12793 = v12786 & v12789;	// L20310
      bool v12794 = v12793 & v12792;	// L20311
      if (v12794) {	// L20312
        int32_t v12795 = s114;	// L20313
        bool v12796 = v12795 < 12;	// L20314
        uint8_t v12797 = sb_dst14[(k28 + 1)];	// L20315
        int32_t v12798 = v12797;	// L20316
        int32_t v12799 = v12798 & 7;	// L20317
        int32_t v12800 = v12795 & 7;	// L20318
        bool v12801 = v12799 == v12800;	// L20319
        bool v12802 = v12796 & v12801;	// L20320
        if (v12802) {	// L20321
          raw14 = 1;	// L20322
        }
        int32_t v12803 = binop14;	// L20324
        bool v12804 = v12803 == 1;	// L20325
        int32_t v12805 = s214;	// L20326
        bool v12806 = v12805 < 12;	// L20327
        uint8_t v12807 = sb_dst14[(k28 + 1)];	// L20328
        int32_t v12808 = v12807;	// L20329
        int32_t v12809 = v12808 & 7;	// L20330
        int32_t v12810 = v12805 & 7;	// L20331
        bool v12811 = v12809 == v12810;	// L20332
        bool v12812 = v12804 & v12806;	// L20333
        bool v12813 = v12812 & v12811;	// L20334
        if (v12813) {	// L20335
          raw14 = 1;	// L20336
        }
      }
      uint8_t v12814 = sb_v14[(k28 + 1)];	// L20339
      int32_t v12815 = v12814;	// L20340
      bool v12816 = v12815 == 1;	// L20341
      uint8_t v12817 = sb_cmp14[(k28 + 1)];	// L20342
      int32_t v12818 = v12817;	// L20343
      bool v12819 = v12818 == 1;	// L20344
      bool v12820 = v12816 & v12819;	// L20345
      if (v12820) {	// L20346
        cmp_busy14 = 1;	// L20347
      }
    }
    int32_t is_cond14;	// L20350
    is_cond14 = 0;	// L20351
    int32_t v12822 = op14;	// L20352
    bool v12823 = v12822 >= 12;	// L20353
    ap_int<33> v12824 = v12822;	// L20354
    bool v12825 = v12824 <= 15;	// L20355
    bool v12826 = v12823 & v12825;	// L20356
    if (v12826) {	// L20357
      is_cond14 = 1;	// L20358
    }
    int32_t grant14;	// L20360
    grant14 = 0;	// L20361
    int32_t v12828 = pc14;	// L20362
    bool v12829 = v12828 >= 0;	// L20363
    if (v12829) {	// L20364
      grant14 = 1;	// L20365
    }
    int32_t v12830 = pc14;	// L20367
    bool v12831 = v12830 >= 0;	// L20368
    int32_t v12832 = a_vld14;	// L20369
    bool v12833 = v12832 == 0;	// L20370
    int32_t v12834 = binop14;	// L20371
    bool v12835 = v12834 == 1;	// L20372
    int32_t v12836 = b_vld14;	// L20373
    bool v12837 = v12836 == 0;	// L20374
    bool v12838 = v12835 & v12837;	// L20375
    bool v12839 = v12833 | v12838;	// L20376
    bool v12840 = v12831 & v12839;	// L20377
    if (v12840) {	// L20378
      grant14 = 0;	// L20379
    }
    int32_t v12841 = pc14;	// L20381
    bool v12842 = v12841 >= 0;	// L20382
    int32_t v12843 = raw14;	// L20383
    bool v12844 = v12843 == 1;	// L20384
    int32_t v12845 = is_cond14;	// L20385
    bool v12846 = v12845 == 1;	// L20386
    int32_t v12847 = cmp_busy14;	// L20387
    bool v12848 = v12847 == 1;	// L20388
    bool v12849 = v12846 & v12848;	// L20389
    bool v12850 = v12844 | v12849;	// L20390
    bool v12851 = v12842 & v12850;	// L20391
    if (v12851) {	// L20392
      grant14 = 0;	// L20393
    }
    int32_t v12852 = grant14;	// L20395
    bool v12853 = v12852 == 1;	// L20396
    if (v12853) {	// L20397
      int8_t v12854 = instr_cnt14;	// L20398
      int32_t v12855 = cfg_isz14;	// L20399
      int32_t v12856 = v12854;	// L20400
      bool v12857 = v12856 == v12855;	// L20401
      if (v12857) {	// L20402
        instr_cnt14 = 0;	// L20403
        int8_t v12858 = iter_cnt14;	// L20404
        int32_t v12859 = cfg_itsz14;	// L20405
        ap_int<33> v12860 = v12859;	// L20406
        ap_int<33> v12861 = v12860 - 1;	// L20407
        ap_int<33> v12862 = v12858;	// L20408
        bool v12863 = v12862 == v12861;	// L20409
        if (v12863) {	// L20410
          fetch_en14 = 0;	// L20411
        } else {
          int8_t v12864 = iter_cnt14;	// L20413
          ap_int<33> v12865 = v12864;	// L20414
          ap_int<33> v12866 = v12865 + 1;	// L20415
          uint8_t v12867 = v12866;	// L20416
          iter_cnt14 = v12867;	// L20417
        }
      } else {
        int8_t v12868 = instr_cnt14;	// L20420
        ap_int<33> v12869 = v12868;	// L20421
        ap_int<33> v12870 = v12869 + 1;	// L20422
        uint8_t v12871 = v12870;	// L20423
        instr_cnt14 = v12871;	// L20424
      }
    }
    int32_t c114;	// L20427
    c114 = -1;	// L20428
    int32_t c214;	// L20429
    c214 = -1;	// L20430
    int32_t v12874 = grant14;	// L20431
    bool v12875 = v12874 == 1;	// L20432
    int32_t v12876 = s114;	// L20433
    bool v12877 = v12876 >= 12;	// L20434
    bool v12878 = v12875 & v12877;	// L20435
    if (v12878) {	// L20436
      int32_t v12879 = s114;	// L20437
      int32_t v12880 = v12879 & 3;	// L20438
      c114 = v12880;	// L20439
    }
    int32_t v12881 = grant14;	// L20441
    bool v12882 = v12881 == 1;	// L20442
    int32_t v12883 = s214;	// L20443
    bool v12884 = v12883 >= 12;	// L20444
    bool v12885 = v12882 & v12884;	// L20445
    if (v12885) {	// L20446
      int32_t v12886 = s214;	// L20447
      int32_t v12887 = v12886 & 3;	// L20448
      c214 = v12887;	// L20449
    }
    int32_t v12888 = c114;	// L20451
    bool v12889 = v12888 >= 0;	// L20452
    if (v12889) {	// L20453
      int32_t v12890 = c114;	// L20454
      int v12891 = v12890;	// L20455
      half v12892 = hold_v14[v12891][1];	// L20456
      hold_v14[v12891][0] = v12892;	// L20457
      int32_t v12893 = c114;	// L20458
      int v12894 = v12893;	// L20459
      uint8_t v12895 = hold_cnt14[v12894];	// L20460
      ap_int<33> v12896 = v12895;	// L20461
      ap_int<33> v12897 = v12896 - 1;	// L20462
      uint8_t v12898 = v12897;	// L20463
      hold_cnt14[v12894] = v12898;	// L20464
    }
    int32_t v12899 = c214;	// L20466
    bool v12900 = v12899 >= 0;	// L20467
    int32_t v12901 = c114;	// L20468
    bool v12902 = v12899 != v12901;	// L20469
    bool v12903 = v12900 & v12902;	// L20470
    if (v12903) {	// L20471
      int32_t v12904 = c214;	// L20472
      int v12905 = v12904;	// L20473
      half v12906 = hold_v14[v12905][1];	// L20474
      hold_v14[v12905][0] = v12906;	// L20475
      int32_t v12907 = c214;	// L20476
      int v12908 = v12907;	// L20477
      uint8_t v12909 = hold_cnt14[v12908];	// L20478
      ap_int<33> v12910 = v12909;	// L20479
      ap_int<33> v12911 = v12910 - 1;	// L20480
      uint8_t v12912 = v12911;	// L20481
      hold_cnt14[v12908] = v12912;	// L20482
    }
    int32_t v12913 = grant14;	// L20484
    bool v12914 = v12913 == 1;	// L20485
    int32_t v12915 = s114;	// L20486
    bool v12916 = v12915 < 8;	// L20487
    int32_t v12917 = dsmask14;	// L20488
    int32_t v12918 = v12917 >> v12915;	// L20489
    int32_t v12919 = v12918 & 1;	// L20490
    bool v12920 = v12919 == 1;	// L20491
    bool v12921 = v12914 & v12916;	// L20492
    bool v12922 = v12921 & v12920;	// L20493
    if (v12922) {	// L20494
      int32_t v12923 = s114;	// L20495
      int v12924 = v12923;	// L20496
      drf_full14[v12924] = 0;	// L20497
    }
    int32_t v12925 = grant14;	// L20499
    bool v12926 = v12925 == 1;	// L20500
    int32_t v12927 = s214;	// L20501
    bool v12928 = v12927 < 8;	// L20502
    int32_t v12929 = dsmask14;	// L20503
    int32_t v12930 = v12929 >> v12927;	// L20504
    int32_t v12931 = v12930 & 1;	// L20505
    bool v12932 = v12931 == 1;	// L20506
    bool v12933 = v12926 & v12928;	// L20507
    bool v12934 = v12933 & v12932;	// L20508
    if (v12934) {	// L20509
      int32_t v12935 = s214;	// L20510
      int v12936 = v12935;	// L20511
      drf_full14[v12936] = 0;	// L20512
    }
    half res14;
#pragma HLS dependence variable=res14 type=inter dependent=false	// L20514
    res14 = 0.000000;	// L20515
    int32_t v12938 = op14;	// L20516
    bool v12939 = v12938 == 0;	// L20517
    if (v12939) {	// L20518
      half v12940 = a14;	// L20519
      half v12941 = b14;	// L20520
      half v12942 = v12940 + v12941;	// L20521
      res14 = v12942;	// L20522
    } else {
      int32_t v12943 = op14;	// L20524
      bool v12944 = v12943 == 1;	// L20525
      if (v12944) {	// L20526
        half v12945 = a14;	// L20527
        half v12946 = b14;	// L20528
        half v12947 = v12945 - v12946;	// L20529
        res14 = v12947;	// L20530
      } else {
        int32_t v12948 = op14;	// L20532
        bool v12949 = v12948 == 2;	// L20533
        if (v12949) {	// L20534
          half v12950 = a14;	// L20535
          half v12951 = b14;	// L20536
          half v12952 = v12950 * v12951;	// L20537
          res14 = v12952;	// L20538
        } else {
          int32_t v12953 = op14;	// L20540
          bool v12954 = v12953 == 8;	// L20541
          if (v12954) {	// L20542
            half v12955 = a14;	// L20543
            half v12956 = b14;	// L20544
            bool v12957 = v12955 >= v12956;	// L20545
            if (v12957) {	// L20546
              res14 = 1.000000;	// L20547
            } else {
              res14 = -1.000000;	// L20549
            }
          } else {
            int32_t v12958 = op14;	// L20552
            bool v12959 = v12958 == 9;	// L20553
            if (v12959) {	// L20554
              half v12960 = a14;	// L20555
              half v12961 = b14;	// L20556
              bool v12962 = v12960 < v12961;	// L20557
              if (v12962) {	// L20558
                res14 = 1.000000;	// L20559
              } else {
                res14 = -1.000000;	// L20561
              }
            } else {
              half v12963 = a14;	// L20564
              res14 = v12963;	// L20565
            }
          }
        }
      }
    }
    int32_t v12964 = a_vld14;	// L20571
    int32_t res_vld14;	// L20572
    res_vld14 = v12964;	// L20573
    int32_t v12966 = op14;	// L20574
    bool v12967 = v12966 == 0;	// L20575
    bool v12968 = v12966 == 1;	// L20576
    bool v12969 = v12966 == 2;	// L20577
    bool v12970 = v12966 == 8;	// L20578
    bool v12971 = v12966 == 9;	// L20579
    bool v12972 = v12967 | v12968;	// L20580
    bool v12973 = v12972 | v12969;	// L20581
    bool v12974 = v12973 | v12970;	// L20582
    bool v12975 = v12974 | v12971;	// L20583
    if (v12975) {	// L20584
      int32_t v12976 = a_vld14;	// L20585
      int32_t v12977 = b_vld14;	// L20586
      int64_t v12978 = v12976;	// L20587
      int64_t v12979 = v12977;	// L20588
      int64_t v12980 = v12978 * v12979;	// L20589
      int32_t v12981 = v12980;	// L20590
      res_vld14 = v12981;	// L20591
    }
    int32_t v12982 = grant14;	// L20593
    bool v12983 = v12982 == 0;	// L20594
    if (v12983) {	// L20595
      res_vld14 = 0;	// L20596
    }
    int32_t is_rtr14;	// L20598
    is_rtr14 = 0;	// L20599
    int32_t v12985 = op14;	// L20600
    bool v12986 = v12985 >= 4;	// L20601
    ap_int<33> v12987 = v12985;	// L20602
    bool v12988 = v12987 <= 7;	// L20603
    bool v12989 = v12986 & v12988;	// L20604
    if (v12989) {	// L20605
      is_rtr14 = 1;	// L20606
    }
    l_S_k_6_k29: for (int k29 = 0; k29 < 4; k29++) {	// L20608
      uint8_t v12991 = sb_v14[(k29 + 1)];	// L20609
      sb_v14[k29] = v12991;	// L20610
      uint8_t v12992 = sb_dst14[(k29 + 1)];	// L20611
      sb_dst14[k29] = v12992;	// L20612
      uint8_t v12993 = sb_cmp14[(k29 + 1)];	// L20613
      sb_cmp14[k29] = v12993;	// L20614
      uint8_t v12994 = sb_rtr14[(k29 + 1)];	// L20615
      sb_rtr14[k29] = v12994;	// L20616
      uint8_t v12995 = sb_inj14[(k29 + 1)];	// L20617
      sb_inj14[k29] = v12995;	// L20618
      uint8_t v12996 = sb_dir14[(k29 + 1)];	// L20619
      sb_dir14[k29] = v12996;	// L20620
      uint8_t v12997 = sb_id14[(k29 + 1)];	// L20621
      sb_id14[k29] = v12997;	// L20622
      uint8_t v12998 = sb_rvld14[(k29 + 1)];	// L20623
      sb_rvld14[k29] = v12998;	// L20624
      uint8_t v12999 = sb_ix14[(k29 + 1)];	// L20625
      sb_ix14[k29] = v12999;	// L20626
    }
    sb_v14[4] = 0;	// L20628
    int32_t v13000 = grant14;	// L20629
    bool v13001 = v13000 == 1;	// L20630
    if (v13001) {	// L20631
      half v13002 = res14;	// L20632
      int8_t v13003 = resq_wr14;	// L20633
      int v13004 = v13003;	// L20634
      resq14[v13004] = v13002;	// L20635
      int32_t cq14;	// L20636
      cq14 = 0;	// L20637
      int32_t v13006 = op14;	// L20638
      bool v13007 = v13006 == 8;	// L20639
      if (v13007) {	// L20640
        half v13008 = a14;	// L20641
        half v13009 = b14;	// L20642
        bool v13010 = v13008 >= v13009;	// L20643
        if (v13010) {	// L20644
          cq14 = 1;	// L20645
        }
      }
      int32_t v13011 = op14;	// L20648
      bool v13012 = v13011 == 9;	// L20649
      if (v13012) {	// L20650
        half v13013 = a14;	// L20651
        half v13014 = b14;	// L20652
        bool v13015 = v13013 < v13014;	// L20653
        if (v13015) {	// L20654
          cq14 = 1;	// L20655
        }
      }
      int32_t v13016 = cq14;	// L20658
      uint8_t v13017 = v13016;	// L20659
      int8_t v13018 = resq_wr14;	// L20660
      int v13019 = v13018;	// L20661
      cmpq14[v13019] = v13017;	// L20662
      sb_v14[4] = 1;	// L20663
      int32_t v13020 = dst14;	// L20664
      uint8_t v13021 = v13020;	// L20665
      sb_dst14[4] = v13021;	// L20666
      int8_t v13022 = resq_wr14;	// L20667
      sb_ix14[4] = v13022;	// L20668
      sb_cmp14[4] = 0;	// L20669
      int32_t v13023 = op14;	// L20670
      bool v13024 = v13023 == 8;	// L20671
      bool v13025 = v13023 == 9;	// L20672
      bool v13026 = v13024 | v13025;	// L20673
      if (v13026) {	// L20674
        sb_cmp14[4] = 1;	// L20675
      }
      int32_t v13027 = is_rtr14;	// L20677
      int32_t rtrf14;	// L20678
      rtrf14 = v13027;	// L20679
      int32_t v13029 = is_cond14;	// L20680
      bool v13030 = v13029 == 1;	// L20681
      if (v13030) {	// L20682
        rtrf14 = 1;	// L20683
      }
      int32_t v13031 = rtrf14;	// L20685
      uint8_t v13032 = v13031;	// L20686
      sb_rtr14[4] = v13032;	// L20687
      int32_t v13033 = is_rtr14;	// L20688
      int32_t inj14;	// L20689
      inj14 = v13033;	// L20690
      int32_t v13035 = is_cond14;	// L20691
      bool v13036 = v13035 == 1;	// L20692
      int8_t v13037 = condition_reg14;	// L20693
      int32_t v13038 = v13037;	// L20694
      bool v13039 = v13038 == 1;	// L20695
      bool v13040 = v13036 & v13039;	// L20696
      if (v13040) {	// L20697
        inj14 = 1;	// L20698
      }
      int32_t v13041 = inj14;	// L20700
      uint8_t v13042 = v13041;	// L20701
      sb_inj14[4] = v13042;	// L20702
      int32_t v13043 = op14;	// L20703
      int32_t v13044 = v13043 & 3;	// L20704
      uint8_t v13045 = v13044;	// L20705
      sb_dir14[4] = v13045;	// L20706
      int32_t v13046 = s214;	// L20707
      uint8_t v13047 = v13046;	// L20708
      sb_id14[4] = v13047;	// L20709
      int32_t v13048 = res_vld14;	// L20710
      uint8_t v13049 = v13048;	// L20711
      sb_rvld14[4] = v13049;	// L20712
      int8_t v13050 = resq_wr14;	// L20713
      ap_int<33> v13051 = v13050;	// L20714
      ap_int<33> v13052 = v13051 + 1;	// L20715
      ap_int<33> v13053 = v13052 & 7;	// L20716
      uint8_t v13054 = v13053;	// L20717
      resq_wr14 = v13054;	// L20718
    }
    ap_int<17> v13055 = tx_n14;	// L20720
    txn_r14 = v13055;	// L20721
    ap_int<17> v13056 = tx_s14;	// L20722
    txs_r14 = v13056;	// L20723
    ap_int<17> v13057 = tx_w14;	// L20724
    txw_r14 = v13057;	// L20725
    ap_int<17> v13058 = tx_e14;	// L20726
    txe_r14 = v13058;	// L20727
    int32_t v13059 = crv_vld14;	// L20728
    bool v13060 = v13059 == 1;	// L20729
    if (v13060) {	// L20730
      int32_t v13061 = crv_mode14;	// L20731
      bool v13062 = v13061 == 1;	// L20732
      if (v13062) {	// L20733
        int32_t v13063 = crv_addr14;	// L20734
        int32_t v13064 = v13063 >> 3;	// L20735
        int32_t v13065 = v13064 & 1;	// L20736
        bool v13066 = v13065 == 1;	// L20737
        if (v13066) {	// L20738
          int32_t v13067 = crv_raw14;	// L20739
          int32_t v13068 = crv_addr14;	// L20740
          int32_t v13069 = v13068 & 7;	// L20741
          int v13070 = v13069;	// L20742
          irf14[v13070] = v13067;	// L20743
        } else {
          int32_t v13071 = crv_addr14;	// L20745
          bool v13072 = v13071 == 0;	// L20746
          if (v13072) {	// L20747
            int32_t v13073 = crv_raw14;	// L20748
            int32_t v13074 = v13073 & 255;	// L20749
            dsmask14 = v13074;	// L20750
            int32_t v13075 = crv_raw14;	// L20751
            int32_t v13076 = v13075 >> 8;	// L20752
            int32_t v13077 = v13076 & 7;	// L20753
            cfg_isz14 = v13077;	// L20754
            int32_t v13078 = crv_raw14;	// L20755
            int32_t v13079 = v13078 >> 15;	// L20756
            int32_t v13080 = v13079 & 1;	// L20757
            bool v13081 = v13080 == 1;	// L20758
            if (v13081) {	// L20759
              fetch_en14 = 1;	// L20760
              instr_cnt14 = 0;	// L20761
              iter_cnt14 = 0;	// L20762
            }
          } else {
            int32_t v13082 = crv_addr14;	// L20765
            bool v13083 = v13082 == 1;	// L20766
            if (v13083) {	// L20767
              int32_t v13084 = crv_raw14;	// L20768
              int32_t v13085 = v13084 & 255;	// L20769
              cfg_itsz14 = v13085;	// L20770
            }
          }
        }
      } else {
        int32_t v13086 = crv_addr14;	// L20775
        bool v13087 = v13086 < 8;	// L20776
        int32_t v13088 = dsmask14;	// L20777
        int32_t v13089 = v13088 >> v13086;	// L20778
        int32_t v13090 = v13089 & 1;	// L20779
        bool v13091 = v13090 == 1;	// L20780
        bool v13092 = v13087 & v13091;	// L20781
        if (v13092) {	// L20782
          int32_t v13093 = crv_addr14;	// L20783
          int v13094 = v13093;	// L20784
          int32_t v13095 = drf_full14[v13094];	// L20785
          bool v13096 = v13095 == 0;	// L20786
          if (v13096) {	// L20787
            half v13097 = crv_data14;	// L20788
            int32_t v13098 = crv_addr14;	// L20789
            int v13099 = v13098;	// L20790
            drf14[v13099] = v13097;	// L20791
            int32_t v13100 = crv_addr14;	// L20792
            int v13101 = v13100;	// L20793
            drf_full14[v13101] = 1;	// L20794
          }
        } else {
          half v13102 = crv_data14;	// L20797
          int32_t v13103 = crv_addr14;	// L20798
          int v13104 = v13103;	// L20799
          drf14[v13104] = v13102;	// L20800
        }
      }
    }
    ap_int<17> v13105 = txe_r14;	// L20804
    bool v13106;
    ap_int<17> v13106_tmp = v13105;
    v13106 = v13106_tmp[0];	// L20805
    int32_t v13107 = v13106;	// L20806
    bool v13108 = v13107 == 1;	// L20807
    if (v13108) {	// L20808
      ap_int<17> v13109 = txe_r14;	// L20809
      v12262.write(v13109);	// L20810
    }
    ap_int<17> v13110 = txw_r14;	// L20812
    bool v13111;
    ap_int<17> v13111_tmp = v13110;
    v13111 = v13111_tmp[0];	// L20813
    int32_t v13112 = v13111;	// L20814
    bool v13113 = v13112 == 1;	// L20815
    if (v13113) {	// L20816
      ap_int<17> v13114 = txw_r14;	// L20817
      v12263.write(v13114);	// L20818
    }
    ap_int<17> v13115 = txs_r14;	// L20820
    bool v13116;
    ap_int<17> v13116_tmp = v13115;
    v13116 = v13116_tmp[0];	// L20821
    int32_t v13117 = v13116;	// L20822
    bool v13118 = v13117 == 1;	// L20823
    if (v13118) {	// L20824
      ap_int<17> v13119 = txs_r14;	// L20825
      v12264.write(v13119);	// L20826
    }
    ap_int<17> v13120 = txn_r14;	// L20828
    bool v13121;
    ap_int<17> v13121_tmp = v13120;
    v13121 = v13121_tmp[0];	// L20829
    int32_t v13122 = v13121;	// L20830
    bool v13123 = v13122 == 1;	// L20831
    if (v13123) {	// L20832
      ap_int<17> v13124 = txn_r14;	// L20833
      v12265.write(v13124);	// L20834
    }
  }
}

void node_3_3(
  hls::stream< ap_uint<26> >& v13125,
  hls::stream< ap_uint<26> >& v13126,
  hls::stream< ap_uint<26> >& v13127,
  hls::stream< ap_uint<26> >& v13128,
  hls::stream< ap_uint<26> >& v13129,
  hls::stream< ap_uint<26> >& v13130,
  hls::stream< ap_uint<26> >& v13131,
  hls::stream< ap_uint<26> >& v13132,
  hls::stream< ap_uint<17> >& v13133,
  hls::stream< ap_uint<17> >& v13134,
  hls::stream< ap_uint<17> >& v13135,
  hls::stream< ap_uint<17> >& v13136,
  hls::stream< ap_uint<17> >& v13137,
  hls::stream< ap_uint<17> >& v13138,
  hls::stream< ap_uint<17> >& v13139,
  hls::stream< ap_uint<17> >& v13140
) {	// L20839
  int32_t irf15[8];	// L20872
  #pragma HLS array_partition variable=irf15 complete dim=1

  for (int v13142 = 0; v13142 < 8; v13142++) {	// L20873
    irf15[v13142] = 0;	// L20873
  }
  half drf15[8];	// L20874
  #pragma HLS array_partition variable=drf15 complete dim=1

  for (int v13144 = 0; v13144 < 8; v13144++) {	// L20875
    drf15[v13144] = 0.000000;	// L20875
  }
  int32_t drf_full15[8];	// L20876
  #pragma HLS array_partition variable=drf_full15 complete dim=1

  for (int v13146 = 0; v13146 < 8; v13146++) {	// L20877
    drf_full15[v13146] = 0;	// L20877
  }
  int32_t dsmask15;	// L20878
  dsmask15 = 0;	// L20879
  int32_t crv_vld15;	// L20880
  crv_vld15 = 0;	// L20881
  half crv_data15;	// L20882
  crv_data15 = 0.000000;	// L20883
  int32_t crv_addr15;	// L20884
  crv_addr15 = 0;	// L20885
  int32_t crv_mode15;	// L20886
  crv_mode15 = 0;	// L20887
  int32_t crv_raw15;	// L20888
  crv_raw15 = 0;	// L20889
  int32_t csd_vld15;	// L20890
  csd_vld15 = 0;	// L20891
  ap_uint<26> csd_pkt15;	// L20892
  csd_pkt15 = 0;	// L20893
  int32_t csd_dir15;	// L20894
  csd_dir15 = 0;	// L20895
  int32_t row_id15;	// L20896
  row_id15 = 3;	// L20897
  int32_t col_id15;	// L20898
  col_id15 = 3;	// L20899
  ap_uint<17> txn_r15;	// L20900
  txn_r15 = 0;	// L20901
  ap_uint<17> txs_r15;	// L20902
  txs_r15 = 0;	// L20903
  ap_uint<17> txw_r15;	// L20904
  txw_r15 = 0;	// L20905
  ap_uint<17> txe_r15;	// L20906
  txe_r15 = 0;	// L20907
  half hold_v15[4][2];	// L20908
  #pragma HLS array_partition variable=hold_v15 complete dim=1
  #pragma HLS array_partition variable=hold_v15 complete dim=2

  for (int v13163 = 0; v13163 < 4; v13163++) {	// L20909
    for (int v13164 = 0; v13164 < 2; v13164++) {	// L20909
      hold_v15[v13163][v13164] = 0.000000;	// L20909
    }
  }
  uint8_t hold_cnt15[4];	// L20910
  #pragma HLS array_partition variable=hold_cnt15 complete dim=1

  for (int v13166 = 0; v13166 < 4; v13166++) {	// L20911
    hold_cnt15[v13166] = 0;	// L20911
  }
  int32_t crv_ever15;	// L20912
  crv_ever15 = 0;	// L20913
  int32_t fe_ever15;	// L20914
  fe_ever15 = 0;	// L20915
  ap_uint<26> rbuf15[4][2];	// L20916
  #pragma HLS array_partition variable=rbuf15 complete dim=1
  #pragma HLS array_partition variable=rbuf15 complete dim=2

  for (int v13170 = 0; v13170 < 4; v13170++) {	// L20917
    for (int v13171 = 0; v13171 < 2; v13171++) {	// L20917
      rbuf15[v13170][v13171] = 0;	// L20917
    }
  }
  uint8_t rbcnt15[4];	// L20918
  #pragma HLS array_partition variable=rbcnt15 complete dim=1

  for (int v13173 = 0; v13173 < 4; v13173++) {	// L20919
    rbcnt15[v13173] = 0;	// L20919
  }
  int32_t cfg_isz15;	// L20920
  cfg_isz15 = 0;	// L20921
  int32_t cfg_itsz15;	// L20922
  cfg_itsz15 = 0;	// L20923
  uint8_t fetch_en15;	// L20924
  fetch_en15 = 0;	// L20925
  uint8_t instr_cnt15;	// L20926
  instr_cnt15 = 0;	// L20927
  uint8_t iter_cnt15;	// L20928
  iter_cnt15 = 0;	// L20929
  uint8_t condition_reg15;	// L20930
  condition_reg15 = 0;	// L20931
  uint8_t sb_v15[5];	// L20932
  #pragma HLS array_partition variable=sb_v15 complete dim=1

  for (int v13181 = 0; v13181 < 5; v13181++) {	// L20933
    sb_v15[v13181] = 0;	// L20933
  }
  uint8_t sb_dst15[5];	// L20934
  #pragma HLS array_partition variable=sb_dst15 complete dim=1

  for (int v13183 = 0; v13183 < 5; v13183++) {	// L20935
    sb_dst15[v13183] = 0;	// L20935
  }
  uint8_t sb_cmp15[5];	// L20936
  #pragma HLS array_partition variable=sb_cmp15 complete dim=1

  for (int v13185 = 0; v13185 < 5; v13185++) {	// L20937
    sb_cmp15[v13185] = 0;	// L20937
  }
  uint8_t sb_rtr15[5];	// L20938
  #pragma HLS array_partition variable=sb_rtr15 complete dim=1

  for (int v13187 = 0; v13187 < 5; v13187++) {	// L20939
    sb_rtr15[v13187] = 0;	// L20939
  }
  uint8_t sb_inj15[5];	// L20940
  #pragma HLS array_partition variable=sb_inj15 complete dim=1

  for (int v13189 = 0; v13189 < 5; v13189++) {	// L20941
    sb_inj15[v13189] = 0;	// L20941
  }
  uint8_t sb_dir15[5];	// L20942
  #pragma HLS array_partition variable=sb_dir15 complete dim=1

  for (int v13191 = 0; v13191 < 5; v13191++) {	// L20943
    sb_dir15[v13191] = 0;	// L20943
  }
  uint8_t sb_id15[5];	// L20944
  #pragma HLS array_partition variable=sb_id15 complete dim=1

  for (int v13193 = 0; v13193 < 5; v13193++) {	// L20945
    sb_id15[v13193] = 0;	// L20945
  }
  uint8_t sb_rvld15[5];	// L20946
  #pragma HLS array_partition variable=sb_rvld15 complete dim=1

  for (int v13195 = 0; v13195 < 5; v13195++) {	// L20947
    sb_rvld15[v13195] = 0;	// L20947
  }
  uint8_t sb_ix15[5];	// L20948
  #pragma HLS array_partition variable=sb_ix15 complete dim=1

  for (int v13197 = 0; v13197 < 5; v13197++) {	// L20949
    sb_ix15[v13197] = 0;	// L20949
  }
  half resq15[8];	// L20950
  #pragma HLS array_partition variable=resq15 complete dim=1
#pragma HLS dependence variable=resq15 type=inter dependent=false

  for (int v13199 = 0; v13199 < 8; v13199++) {	// L20951
    resq15[v13199] = 0.000000;	// L20951
  }
  uint8_t cmpq15[8];	// L20952
  #pragma HLS array_partition variable=cmpq15 complete dim=1
#pragma HLS dependence variable=cmpq15 type=inter dependent=false

  for (int v13201 = 0; v13201 < 8; v13201++) {	// L20953
    cmpq15[v13201] = 0;	// L20953
  }
  uint8_t resq_wr15;	// L20954
  resq_wr15 = 0;	// L20955
  l_S_t_0_t15: for (int t15 = 0; t15 < 374; t15++) {	// L20956
  #pragma HLS pipeline II=1
    ap_uint<26> p_w15;	// L20957
    p_w15 = 0;	// L20958
    ap_uint<26> p_e15;	// L20959
    p_e15 = 0;	// L20960
    ap_uint<26> p_n15;	// L20961
    p_n15 = 0;	// L20962
    ap_uint<26> p_s15;	// L20963
    p_s15 = 0;	// L20964
    uint8_t v13208 = rbcnt15[0];	// L20965
    int32_t v13209 = v13208;	// L20966
    bool v13210 = v13209 < 2;	// L20967
    if (v13210) {	// L20968
      ap_uint<26> v13211;
      bool v13212 = v13125.read_nb(v13211);
	// L20969
      ap_uint<26> gw15;	// L20970
      gw15 = v13211;	// L20971
      bool okw15;	// L20972
      okw15 = v13212;	// L20973
      bool v13215 = okw15;	// L20974
      if (v13215) {	// L20975
        ap_int<26> v13216 = gw15;	// L20976
        p_w15 = v13216;	// L20977
      }
    }
    uint8_t v13217 = rbcnt15[1];	// L20980
    int32_t v13218 = v13217;	// L20981
    bool v13219 = v13218 < 2;	// L20982
    if (v13219) {	// L20983
      ap_uint<26> v13220;
      bool v13221 = v13126.read_nb(v13220);
	// L20984
      ap_uint<26> ge15;	// L20985
      ge15 = v13220;	// L20986
      bool oke15;	// L20987
      oke15 = v13221;	// L20988
      bool v13224 = oke15;	// L20989
      if (v13224) {	// L20990
        ap_int<26> v13225 = ge15;	// L20991
        p_e15 = v13225;	// L20992
      }
    }
    uint8_t v13226 = rbcnt15[2];	// L20995
    int32_t v13227 = v13226;	// L20996
    bool v13228 = v13227 < 2;	// L20997
    if (v13228) {	// L20998
      ap_uint<26> v13229;
      bool v13230 = v13127.read_nb(v13229);
	// L20999
      ap_uint<26> gn15;	// L21000
      gn15 = v13229;	// L21001
      bool okn15;	// L21002
      okn15 = v13230;	// L21003
      bool v13233 = okn15;	// L21004
      if (v13233) {	// L21005
        ap_int<26> v13234 = gn15;	// L21006
        p_n15 = v13234;	// L21007
      }
    }
    uint8_t v13235 = rbcnt15[3];	// L21010
    int32_t v13236 = v13235;	// L21011
    bool v13237 = v13236 < 2;	// L21012
    if (v13237) {	// L21013
      ap_uint<26> v13238;
      bool v13239 = v13128.read_nb(v13238);
	// L21014
      ap_uint<26> gs15;	// L21015
      gs15 = v13238;	// L21016
      bool oks15;	// L21017
      oks15 = v13239;	// L21018
      bool v13242 = oks15;	// L21019
      if (v13242) {	// L21020
        ap_int<26> v13243 = gs15;	// L21021
        p_s15 = v13243;	// L21022
      }
    }
    ap_uint<26> fin15[4];	// L21025
    for (int v13245 = 0; v13245 < 4; v13245++) {	// L21026
      fin15[v13245] = 0;	// L21026
    }
    ap_int<26> v13246 = p_w15;	// L21027
    fin15[0] = v13246;	// L21028
    ap_int<26> v13247 = p_e15;	// L21029
    fin15[1] = v13247;	// L21030
    ap_int<26> v13248 = p_n15;	// L21031
    fin15[2] = v13248;	// L21032
    ap_int<26> v13249 = p_s15;	// L21033
    fin15[3] = v13249;	// L21034
    l_S_d_0_d60: for (int d60 = 0; d60 < 4; d60++) {	// L21035
      ap_uint<26> v13251 = fin15[d60];	// L21036
      bool v13252;
      ap_int<26> v13252_tmp = v13251;
      v13252 = v13252_tmp[25];	// L21037
      int32_t v13253 = v13252;	// L21038
      bool v13254 = v13253 == 1;	// L21039
      uint8_t v13255 = rbcnt15[d60];	// L21040
      int32_t v13256 = v13255;	// L21041
      bool v13257 = v13256 < 2;	// L21042
      bool v13258 = v13254 & v13257;	// L21043
      if (v13258) {	// L21044
        ap_uint<26> v13259 = fin15[d60];	// L21045
        uint8_t v13260 = rbcnt15[d60];	// L21046
        int v13261 = v13260;	// L21047
        rbuf15[d60][v13261] = v13259;	// L21048
        uint8_t v13262 = rbcnt15[d60];	// L21049
        ap_int<33> v13263 = v13262;	// L21050
        ap_int<33> v13264 = v13263 + 1;	// L21051
        uint8_t v13265 = v13264;	// L21052
        rbcnt15[d60] = v13265;	// L21053
      }
    }
    ap_uint<26> hd15[4];	// L21056
    for (int v13267 = 0; v13267 < 4; v13267++) {	// L21057
      hd15[v13267] = 0;	// L21057
    }
    int32_t hvld15[4];	// L21058
    for (int v13269 = 0; v13269 < 4; v13269++) {	// L21059
      hvld15[v13269] = 0;	// L21059
    }
    int32_t hit15[4];	// L21060
    for (int v13271 = 0; v13271 < 4; v13271++) {	// L21061
      hit15[v13271] = 0;	// L21061
    }
    int32_t axis15[4];	// L21062
    for (int v13273 = 0; v13273 < 4; v13273++) {	// L21063
      axis15[v13273] = 0;	// L21063
    }
    int32_t v13274 = col_id15;	// L21064
    axis15[0] = v13274;	// L21065
    int32_t v13275 = col_id15;	// L21066
    axis15[1] = v13275;	// L21067
    int32_t v13276 = row_id15;	// L21068
    axis15[2] = v13276;	// L21069
    int32_t v13277 = row_id15;	// L21070
    axis15[3] = v13277;	// L21071
    l_S_d_1_d61: for (int d61 = 0; d61 < 4; d61++) {	// L21072
      uint8_t v13279 = rbcnt15[d61];	// L21073
      int32_t v13280 = v13279;	// L21074
      bool v13281 = v13280 > 0;	// L21075
      if (v13281) {	// L21076
        ap_uint<26> v13282 = rbuf15[d61][0];	// L21077
        hd15[d61] = v13282;	// L21078
        hvld15[d61] = 1;	// L21079
        ap_uint<26> v13283 = hd15[d61];	// L21080
        ap_int<4> v13284;
        ap_int<26> v13284_tmp = v13283;
        v13284 = v13284_tmp(24, 21);	// L21081
        int32_t v13285 = axis15[d61];	// L21082
        int32_t v13286 = v13284;	// L21083
        bool v13287 = v13286 == v13285;	// L21084
        if (v13287) {	// L21085
          hit15[d61] = 1;	// L21086
        }
      }
    }
    ap_uint<26> o_crv15;	// L21090
    o_crv15 = 0;	// L21091
    int32_t crv_in15;	// L21092
    crv_in15 = -1;	// L21093
    int32_t v13290 = hit15[3];	// L21094
    bool v13291 = v13290 == 1;	// L21095
    if (v13291) {	// L21096
      ap_uint<26> v13292 = hd15[3];	// L21097
      o_crv15 = v13292;	// L21098
      crv_in15 = 3;	// L21099
    } else {
      int32_t v13293 = hit15[2];	// L21101
      bool v13294 = v13293 == 1;	// L21102
      if (v13294) {	// L21103
        ap_uint<26> v13295 = hd15[2];	// L21104
        o_crv15 = v13295;	// L21105
        crv_in15 = 2;	// L21106
      } else {
        int32_t v13296 = hit15[1];	// L21108
        bool v13297 = v13296 == 1;	// L21109
        if (v13297) {	// L21110
          ap_uint<26> v13298 = hd15[1];	// L21111
          o_crv15 = v13298;	// L21112
          crv_in15 = 1;	// L21113
        } else {
          int32_t v13299 = hit15[0];	// L21115
          bool v13300 = v13299 == 1;	// L21116
          if (v13300) {	// L21117
            ap_uint<26> v13301 = hd15[0];	// L21118
            o_crv15 = v13301;	// L21119
            crv_in15 = 0;	// L21120
          }
        }
      }
    }
    int32_t pop15[4];	// L21125
    for (int v13303 = 0; v13303 < 4; v13303++) {	// L21126
      pop15[v13303] = 0;	// L21126
    }
    int32_t inj_done15;	// L21127
    inj_done15 = 0;	// L21128
    int32_t idir15;	// L21129
    idir15 = -1;	// L21130
    ap_int<26> v13306 = csd_pkt15;	// L21131
    bool v13307;
    ap_int<26> v13307_tmp = v13306;
    v13307 = v13307_tmp[25];	// L21132
    int32_t v13308 = v13307;	// L21133
    bool v13309 = v13308 == 1;	// L21134
    if (v13309) {	// L21135
      int32_t v13310 = csd_dir15;	// L21136
      ap_int<33> v13311 = v13310;	// L21137
      ap_int<33> v13312 = 3 - v13311;	// L21138
      int32_t v13313 = v13312;	// L21139
      idir15 = v13313;	// L21140
    }
    int32_t v13314 = idir15;	// L21142
    bool v13315 = v13314 == 0;	// L21143
    if (v13315) {	// L21144
      ap_int<26> v13316 = csd_pkt15;	// L21145
      bool v13317 = v13129.write_nb(v13316);
	// L21146
      if (v13317) {	// L21147
        inj_done15 = 1;	// L21148
      }
    } else {
      int32_t v13318 = hvld15[0];	// L21151
      bool v13319 = v13318 == 1;	// L21152
      int32_t v13320 = hit15[0];	// L21153
      bool v13321 = v13320 == 0;	// L21154
      bool v13322 = v13319 & v13321;	// L21155
      if (v13322) {	// L21156
        ap_uint<26> v13323 = hd15[0];	// L21157
        bool v13324 = v13129.write_nb(v13323);
	// L21158
        if (v13324) {	// L21159
          pop15[0] = 1;	// L21160
        }
      }
    }
    int32_t v13325 = idir15;	// L21164
    bool v13326 = v13325 == 1;	// L21165
    if (v13326) {	// L21166
      ap_int<26> v13327 = csd_pkt15;	// L21167
      bool v13328 = v13130.write_nb(v13327);
	// L21168
      if (v13328) {	// L21169
        inj_done15 = 1;	// L21170
      }
    } else {
      int32_t v13329 = hvld15[1];	// L21173
      bool v13330 = v13329 == 1;	// L21174
      int32_t v13331 = hit15[1];	// L21175
      bool v13332 = v13331 == 0;	// L21176
      bool v13333 = v13330 & v13332;	// L21177
      if (v13333) {	// L21178
        ap_uint<26> v13334 = hd15[1];	// L21179
        bool v13335 = v13130.write_nb(v13334);
	// L21180
        if (v13335) {	// L21181
          pop15[1] = 1;	// L21182
        }
      }
    }
    int32_t v13336 = idir15;	// L21186
    bool v13337 = v13336 == 2;	// L21187
    if (v13337) {	// L21188
      ap_int<26> v13338 = csd_pkt15;	// L21189
      bool v13339 = v13131.write_nb(v13338);
	// L21190
      if (v13339) {	// L21191
        inj_done15 = 1;	// L21192
      }
    } else {
      int32_t v13340 = hvld15[2];	// L21195
      bool v13341 = v13340 == 1;	// L21196
      int32_t v13342 = hit15[2];	// L21197
      bool v13343 = v13342 == 0;	// L21198
      bool v13344 = v13341 & v13343;	// L21199
      if (v13344) {	// L21200
        ap_uint<26> v13345 = hd15[2];	// L21201
        bool v13346 = v13131.write_nb(v13345);
	// L21202
        if (v13346) {	// L21203
          pop15[2] = 1;	// L21204
        }
      }
    }
    int32_t v13347 = idir15;	// L21208
    bool v13348 = v13347 == 3;	// L21209
    if (v13348) {	// L21210
      ap_int<26> v13349 = csd_pkt15;	// L21211
      bool v13350 = v13132.write_nb(v13349);
	// L21212
      if (v13350) {	// L21213
        inj_done15 = 1;	// L21214
      }
    } else {
      int32_t v13351 = hvld15[3];	// L21217
      bool v13352 = v13351 == 1;	// L21218
      int32_t v13353 = hit15[3];	// L21219
      bool v13354 = v13353 == 0;	// L21220
      bool v13355 = v13352 & v13354;	// L21221
      if (v13355) {	// L21222
        ap_uint<26> v13356 = hd15[3];	// L21223
        bool v13357 = v13132.write_nb(v13356);
	// L21224
        if (v13357) {	// L21225
          pop15[3] = 1;	// L21226
        }
      }
    }
    int32_t v13358 = crv_in15;	// L21230
    bool v13359 = v13358 >= 0;	// L21231
    if (v13359) {	// L21232
      int32_t v13360 = crv_in15;	// L21233
      int v13361 = v13360;	// L21234
      pop15[v13361] = 1;	// L21235
    }
    l_S_d_2_d62: for (int d62 = 0; d62 < 4; d62++) {	// L21237
      int32_t v13363 = pop15[d62];	// L21238
      bool v13364 = v13363 == 1;	// L21239
      if (v13364) {	// L21240
        l_S_sft_2_sft15: for (int sft15 = 0; sft15 < 1; sft15++) {	// L21241
          ap_uint<26> v13366 = rbuf15[d62][(sft15 + 1)];	// L21242
          rbuf15[d62][sft15] = v13366;	// L21243
        }
        uint8_t v13367 = rbcnt15[d62];	// L21245
        ap_int<33> v13368 = v13367;	// L21246
        ap_int<33> v13369 = v13368 - 1;	// L21247
        uint8_t v13370 = v13369;	// L21248
        rbcnt15[d62] = v13370;	// L21249
      }
    }
    int32_t v13371 = inj_done15;	// L21252
    bool v13372 = v13371 == 1;	// L21253
    if (v13372) {	// L21254
      csd_pkt15 = 0;	// L21255
    }
    ap_int<26> v13373 = o_crv15;	// L21257
    bool v13374;
    ap_int<26> v13374_tmp = v13373;
    v13374 = v13374_tmp[25];	// L21258
    int32_t v13375 = v13374;	// L21259
    crv_vld15 = v13375;	// L21260
    int32_t v13376 = crv_vld15;	// L21261
    bool v13377 = v13376 == 1;	// L21262
    if (v13377) {	// L21263
      crv_ever15 = 1;	// L21264
    }
    ap_int<26> v13378 = o_crv15;	// L21266
    int16_t v13379;
    ap_int<26> v13379_tmp = v13378;
    v13379 = v13379_tmp(15, 0);	// L21267
    half v13380;
    union { uint16_t from; half to;} _converter_v13379_to_v13380 = {};
    _converter_v13379_to_v13380.from = v13379;
    v13380 = _converter_v13379_to_v13380.to;	// L21268
    crv_data15 = v13380;	// L21269
    ap_int<26> v13381 = o_crv15;	// L21270
    ap_int<4> v13382;
    ap_int<26> v13382_tmp = v13381;
    v13382 = v13382_tmp(19, 16);	// L21271
    int32_t v13383 = v13382;	// L21272
    crv_addr15 = v13383;	// L21273
    ap_int<26> v13384 = o_crv15;	// L21274
    bool v13385;
    ap_int<26> v13385_tmp = v13384;
    v13385 = v13385_tmp[20];	// L21275
    int32_t v13386 = v13385;	// L21276
    crv_mode15 = v13386;	// L21277
    ap_int<26> v13387 = o_crv15;	// L21278
    int16_t v13388;
    ap_int<26> v13388_tmp = v13387;
    v13388 = v13388_tmp(15, 0);	// L21279
    int32_t v13389 = v13388;	// L21280
    crv_raw15 = v13389;	// L21281
    half rxv15[4];	// L21282
    for (int v13391 = 0; v13391 < 4; v13391++) {	// L21283
      rxv15[v13391] = 0.000000;	// L21283
    }
    int32_t rxvld15[4];	// L21284
    for (int v13393 = 0; v13393 < 4; v13393++) {	// L21285
      rxvld15[v13393] = 0;	// L21285
    }
    uint8_t v13394 = hold_cnt15[0];	// L21286
    int32_t v13395 = v13394;	// L21287
    bool v13396 = v13395 < 2;	// L21288
    if (v13396) {	// L21289
      ap_uint<17> v13397;
      bool v13398 = v13133.read_nb(v13397);
	// L21290
      ap_uint<17> sgn15;	// L21291
      sgn15 = v13397;	// L21292
      bool sqn15;	// L21293
      sqn15 = v13398;	// L21294
      bool v13401 = sqn15;	// L21295
      int32_t v13402 = v13401;	// L21296
      bool v13403 = v13402 == 1;	// L21297
      if (v13403) {	// L21298
        ap_int<17> v13404 = sgn15;	// L21299
        int16_t v13405;
        ap_int<17> v13405_tmp = v13404;
        v13405 = v13405_tmp(16, 1);	// L21300
        half v13406;
        union { uint16_t from; half to;} _converter_v13405_to_v13406 = {};
        _converter_v13405_to_v13406.from = v13405;
        v13406 = _converter_v13405_to_v13406.to;	// L21301
        rxv15[0] = v13406;	// L21302
        rxvld15[0] = 1;	// L21303
      }
    }
    uint8_t v13407 = hold_cnt15[1];	// L21306
    int32_t v13408 = v13407;	// L21307
    bool v13409 = v13408 < 2;	// L21308
    if (v13409) {	// L21309
      ap_uint<17> v13410;
      bool v13411 = v13134.read_nb(v13410);
	// L21310
      ap_uint<17> sgs15;	// L21311
      sgs15 = v13410;	// L21312
      bool sqs15;	// L21313
      sqs15 = v13411;	// L21314
      bool v13414 = sqs15;	// L21315
      int32_t v13415 = v13414;	// L21316
      bool v13416 = v13415 == 1;	// L21317
      if (v13416) {	// L21318
        ap_int<17> v13417 = sgs15;	// L21319
        int16_t v13418;
        ap_int<17> v13418_tmp = v13417;
        v13418 = v13418_tmp(16, 1);	// L21320
        half v13419;
        union { uint16_t from; half to;} _converter_v13418_to_v13419 = {};
        _converter_v13418_to_v13419.from = v13418;
        v13419 = _converter_v13418_to_v13419.to;	// L21321
        rxv15[1] = v13419;	// L21322
        rxvld15[1] = 1;	// L21323
      }
    }
    uint8_t v13420 = hold_cnt15[2];	// L21326
    int32_t v13421 = v13420;	// L21327
    bool v13422 = v13421 < 2;	// L21328
    if (v13422) {	// L21329
      ap_uint<17> v13423;
      bool v13424 = v13135.read_nb(v13423);
	// L21330
      ap_uint<17> sgw15;	// L21331
      sgw15 = v13423;	// L21332
      bool sqw15;	// L21333
      sqw15 = v13424;	// L21334
      bool v13427 = sqw15;	// L21335
      int32_t v13428 = v13427;	// L21336
      bool v13429 = v13428 == 1;	// L21337
      if (v13429) {	// L21338
        ap_int<17> v13430 = sgw15;	// L21339
        int16_t v13431;
        ap_int<17> v13431_tmp = v13430;
        v13431 = v13431_tmp(16, 1);	// L21340
        half v13432;
        union { uint16_t from; half to;} _converter_v13431_to_v13432 = {};
        _converter_v13431_to_v13432.from = v13431;
        v13432 = _converter_v13431_to_v13432.to;	// L21341
        rxv15[2] = v13432;	// L21342
        rxvld15[2] = 1;	// L21343
      }
    }
    uint8_t v13433 = hold_cnt15[3];	// L21346
    int32_t v13434 = v13433;	// L21347
    bool v13435 = v13434 < 2;	// L21348
    if (v13435) {	// L21349
      ap_uint<17> v13436;
      bool v13437 = v13136.read_nb(v13436);
	// L21350
      ap_uint<17> sge15;	// L21351
      sge15 = v13436;	// L21352
      bool sqe15;	// L21353
      sqe15 = v13437;	// L21354
      bool v13440 = sqe15;	// L21355
      int32_t v13441 = v13440;	// L21356
      bool v13442 = v13441 == 1;	// L21357
      if (v13442) {	// L21358
        ap_int<17> v13443 = sge15;	// L21359
        int16_t v13444;
        ap_int<17> v13444_tmp = v13443;
        v13444 = v13444_tmp(16, 1);	// L21360
        half v13445;
        union { uint16_t from; half to;} _converter_v13444_to_v13445 = {};
        _converter_v13444_to_v13445.from = v13444;
        v13445 = _converter_v13444_to_v13445.to;	// L21361
        rxv15[3] = v13445;	// L21362
        rxvld15[3] = 1;	// L21363
      }
    }
    l_S_d_4_d63: for (int d63 = 0; d63 < 4; d63++) {	// L21366
      int32_t v13447 = rxvld15[d63];	// L21367
      bool v13448 = v13447 == 1;	// L21368
      if (v13448) {	// L21369
        half v13449 = rxv15[d63];	// L21370
        uint8_t v13450 = hold_cnt15[d63];	// L21371
        int v13451 = v13450;	// L21372
        hold_v15[d63][v13451] = v13449;	// L21373
        uint8_t v13452 = hold_cnt15[d63];	// L21374
        ap_int<33> v13453 = v13452;	// L21375
        ap_int<33> v13454 = v13453 + 1;	// L21376
        uint8_t v13455 = v13454;	// L21377
        hold_cnt15[d63] = v13455;	// L21378
      }
    }
    ap_uint<17> tx_n15;	// L21381
    tx_n15 = 0;	// L21382
    ap_uint<17> tx_s15;	// L21383
    tx_s15 = 0;	// L21384
    ap_uint<17> tx_w15;	// L21385
    tx_w15 = 0;	// L21386
    ap_uint<17> tx_e15;	// L21387
    tx_e15 = 0;	// L21388
    uint8_t v13460 = sb_v15[0];	// L21389
    int32_t v13461 = v13460;	// L21390
    bool v13462 = v13461 == 1;	// L21391
    if (v13462) {	// L21392
      uint8_t v13463 = sb_ix15[0];	// L21393
      int v13464 = v13463;	// L21394
      half v13465 = resq15[v13464];	// L21395
      half wb15;
#pragma HLS dependence variable=wb15 type=inter dependent=false	// L21396
      wb15 = v13465;	// L21397
      uint8_t v13467 = sb_cmp15[0];	// L21398
      int32_t v13468 = v13467;	// L21399
      bool v13469 = v13468 == 1;	// L21400
      if (v13469) {	// L21401
        uint8_t v13470 = sb_ix15[0];	// L21402
        int v13471 = v13470;	// L21403
        uint8_t v13472 = cmpq15[v13471];	// L21404
        condition_reg15 = v13472;	// L21405
      }
      uint8_t v13473 = sb_rtr15[0];	// L21407
      int32_t v13474 = v13473;	// L21408
      bool v13475 = v13474 == 1;	// L21409
      if (v13475) {	// L21410
        uint8_t v13476 = sb_inj15[0];	// L21411
        int32_t v13477 = v13476;	// L21412
        bool v13478 = v13477 == 1;	// L21413
        ap_int<26> v13479 = csd_pkt15;	// L21414
        bool v13480;
        ap_int<26> v13480_tmp = v13479;
        v13480 = v13480_tmp[25];	// L21415
        int32_t v13481 = v13480;	// L21416
        bool v13482 = v13481 == 0;	// L21417
        bool v13483 = v13478 & v13482;	// L21418
        if (v13483) {	// L21419
          half v13484 = wb15;	// L21420
          uint16_t v13485;
          union { half from; uint16_t to;} _converter_v13484_to_v13485 = {};
          _converter_v13484_to_v13485.from = v13484;
          v13485 = _converter_v13484_to_v13485.to;	// L21421
          ap_int<26> v13486 = csd_pkt15;	// L21422
          ap_int<26> v13487;
          ap_int<26> v13487_tmp = v13486;
          v13487_tmp(15, 0) = v13485;
          v13487 = v13487_tmp;	// L21423
          csd_pkt15 = v13487;	// L21424
          uint8_t v13488 = sb_dst15[0];	// L21425
          ap_uint<4> v13489 = v13488;	// L21426
          ap_int<26> v13490 = csd_pkt15;	// L21427
          ap_int<26> v13491;
          ap_int<26> v13491_tmp = v13490;
          v13491_tmp(19, 16) = v13489;
          v13491 = v13491_tmp;	// L21428
          csd_pkt15 = v13491;	// L21429
          uint8_t v13492 = sb_id15[0];	// L21430
          ap_uint<4> v13493 = v13492;	// L21431
          ap_int<26> v13494 = csd_pkt15;	// L21432
          ap_int<26> v13495;
          ap_int<26> v13495_tmp = v13494;
          v13495_tmp(24, 21) = v13493;
          v13495 = v13495_tmp;	// L21433
          csd_pkt15 = v13495;	// L21434
          uint8_t v13496 = sb_rvld15[0];	// L21435
          bool v13497 = v13496;	// L21436
          ap_int<26> v13498 = csd_pkt15;	// L21437
          ap_int<26> v13499;
          ap_int<26> v13499_tmp = v13498;
          v13499_tmp[25] = v13497;          v13499 = v13499_tmp;	// L21438
          csd_pkt15 = v13499;	// L21439
          uint8_t v13500 = sb_dir15[0];	// L21440
          int32_t v13501 = v13500;	// L21441
          csd_dir15 = v13501;	// L21442
        }
      } else {
        uint8_t v13502 = sb_dst15[0];	// L21445
        int32_t v13503 = v13502;	// L21446
        bool v13504 = v13503 >= 12;	// L21447
        if (v13504) {	// L21448
          ap_uint<17> tw015;	// L21449
          tw015 = 0;	// L21450
          uint8_t v13506 = sb_rvld15[0];	// L21451
          bool v13507 = v13506;	// L21452
          ap_int<17> v13508 = tw015;	// L21453
          ap_int<17> v13509;
          ap_int<17> v13509_tmp = v13508;
          v13509_tmp[0] = v13507;          v13509 = v13509_tmp;	// L21454
          tw015 = v13509;	// L21455
          half v13510 = wb15;	// L21456
          uint16_t v13511;
          union { half from; uint16_t to;} _converter_v13510_to_v13511 = {};
          _converter_v13510_to_v13511.from = v13510;
          v13511 = _converter_v13510_to_v13511.to;	// L21457
          ap_int<17> v13512 = tw015;	// L21458
          ap_int<17> v13513;
          ap_int<17> v13513_tmp = v13512;
          v13513_tmp(16, 1) = v13511;
          v13513 = v13513_tmp;	// L21459
          tw015 = v13513;	// L21460
          uint8_t v13514 = sb_dst15[0];	// L21461
          int32_t v13515 = v13514;	// L21462
          int32_t v13516 = v13515 & 3;	// L21463
          bool v13517 = v13516 == 0;	// L21464
          if (v13517) {	// L21465
            ap_int<17> v13518 = tw015;	// L21466
            tx_n15 = v13518;	// L21467
          } else {
            uint8_t v13519 = sb_dst15[0];	// L21469
            int32_t v13520 = v13519;	// L21470
            int32_t v13521 = v13520 & 3;	// L21471
            bool v13522 = v13521 == 1;	// L21472
            if (v13522) {	// L21473
              ap_int<17> v13523 = tw015;	// L21474
              tx_s15 = v13523;	// L21475
            } else {
              uint8_t v13524 = sb_dst15[0];	// L21477
              int32_t v13525 = v13524;	// L21478
              int32_t v13526 = v13525 & 3;	// L21479
              bool v13527 = v13526 == 2;	// L21480
              if (v13527) {	// L21481
                ap_int<17> v13528 = tw015;	// L21482
                tx_w15 = v13528;	// L21483
              } else {
                ap_int<17> v13529 = tw015;	// L21485
                tx_e15 = v13529;	// L21486
              }
            }
          }
        } else {
          uint8_t v13530 = sb_rvld15[0];	// L21491
          int32_t v13531 = v13530;	// L21492
          bool v13532 = v13531 == 1;	// L21493
          if (v13532) {	// L21494
            uint8_t v13533 = sb_dst15[0];	// L21495
            int32_t v13534 = v13533;	// L21496
            bool v13535 = v13534 < 8;	// L21497
            int32_t v13536 = dsmask15;	// L21498
            int32_t v13537 = v13536 >> v13534;	// L21499
            int32_t v13538 = v13537 & 1;	// L21500
            bool v13539 = v13538 == 1;	// L21501
            bool v13540 = v13535 & v13539;	// L21502
            if (v13540) {	// L21503
              uint8_t v13541 = sb_dst15[0];	// L21504
              int v13542 = v13541;	// L21505
              int32_t v13543 = drf_full15[v13542];	// L21506
              bool v13544 = v13543 == 0;	// L21507
              if (v13544) {	// L21508
                half v13545 = wb15;	// L21509
                uint8_t v13546 = sb_dst15[0];	// L21510
                int v13547 = v13546;	// L21511
                drf15[v13547] = v13545;	// L21512
                uint8_t v13548 = sb_dst15[0];	// L21513
                int v13549 = v13548;	// L21514
                drf_full15[v13549] = 1;	// L21515
              }
            } else {
              half v13550 = wb15;	// L21518
              uint8_t v13551 = sb_dst15[0];	// L21519
              int32_t v13552 = v13551;	// L21520
              int32_t v13553 = v13552 & 7;	// L21521
              int v13554 = v13553;	// L21522
              drf15[v13554] = v13550;	// L21523
            }
          }
        }
      }
    }
    int32_t pc15;	// L21529
    pc15 = -1;	// L21530
    int8_t v13556 = fetch_en15;	// L21531
    int32_t v13557 = v13556;	// L21532
    bool v13558 = v13557 == 1;	// L21533
    if (v13558) {	// L21534
      int8_t v13559 = instr_cnt15;	// L21535
      int32_t v13560 = v13559;	// L21536
      pc15 = v13560;	// L21537
    }
    int8_t v13561 = fetch_en15;	// L21539
    int32_t v13562 = v13561;	// L21540
    bool v13563 = v13562 == 1;	// L21541
    if (v13563) {	// L21542
      fe_ever15 = 1;	// L21543
    }
    int32_t instr15;	// L21545
    instr15 = 0;	// L21546
    int32_t v13565 = pc15;	// L21547
    bool v13566 = v13565 >= 0;	// L21548
    if (v13566) {	// L21549
      int32_t v13567 = pc15;	// L21550
      int v13568 = v13567;	// L21551
      int32_t v13569 = irf15[v13568];	// L21552
      instr15 = v13569;	// L21553
    }
    int32_t v13570 = instr15;	// L21555
    int32_t v13571 = v13570 & 15;	// L21556
    int32_t op15;	// L21557
    op15 = v13571;	// L21558
    int32_t v13573 = instr15;	// L21559
    int32_t v13574 = v13573 >> 4;	// L21560
    int32_t v13575 = v13574 & 15;	// L21561
    int32_t dst15;	// L21562
    dst15 = v13575;	// L21563
    int32_t v13577 = instr15;	// L21564
    int32_t v13578 = v13577 >> 8;	// L21565
    int32_t v13579 = v13578 & 15;	// L21566
    int32_t s115;	// L21567
    s115 = v13579;	// L21568
    int32_t v13581 = instr15;	// L21569
    int32_t v13582 = v13581 >> 12;	// L21570
    int32_t v13583 = v13582 & 15;	// L21571
    int32_t s215;	// L21572
    s215 = v13583;	// L21573
    half a15;	// L21574
    a15 = 0.000000;	// L21575
    half b15;	// L21576
    b15 = 0.000000;	// L21577
    int32_t v13587 = s115;	// L21578
    bool v13588 = v13587 >= 12;	// L21579
    if (v13588) {	// L21580
      int32_t v13589 = s115;	// L21581
      int32_t v13590 = v13589 & 3;	// L21582
      int v13591 = v13590;	// L21583
      half v13592 = hold_v15[v13591][0];	// L21584
      a15 = v13592;	// L21585
    } else {
      int32_t v13593 = s115;	// L21587
      int v13594 = v13593;	// L21588
      half v13595 = drf15[v13594];	// L21589
      a15 = v13595;	// L21590
    }
    int32_t v13596 = s215;	// L21592
    bool v13597 = v13596 >= 12;	// L21593
    if (v13597) {	// L21594
      int32_t v13598 = s215;	// L21595
      int32_t v13599 = v13598 & 3;	// L21596
      int v13600 = v13599;	// L21597
      half v13601 = hold_v15[v13600][0];	// L21598
      b15 = v13601;	// L21599
    } else {
      int32_t v13602 = s215;	// L21601
      int v13603 = v13602;	// L21602
      half v13604 = drf15[v13603];	// L21603
      b15 = v13604;	// L21604
    }
    int32_t a_vld15;	// L21606
    a_vld15 = 1;	// L21607
    int32_t b_vld15;	// L21608
    b_vld15 = 1;	// L21609
    int32_t v13607 = s115;	// L21610
    bool v13608 = v13607 >= 12;	// L21611
    if (v13608) {	// L21612
      a_vld15 = 0;	// L21613
      int32_t v13609 = s115;	// L21614
      int32_t v13610 = v13609 & 3;	// L21615
      int v13611 = v13610;	// L21616
      uint8_t v13612 = hold_cnt15[v13611];	// L21617
      int32_t v13613 = v13612;	// L21618
      bool v13614 = v13613 > 0;	// L21619
      if (v13614) {	// L21620
        a_vld15 = 1;	// L21621
      }
    }
    int32_t v13615 = s215;	// L21624
    bool v13616 = v13615 >= 12;	// L21625
    if (v13616) {	// L21626
      b_vld15 = 0;	// L21627
      int32_t v13617 = s215;	// L21628
      int32_t v13618 = v13617 & 3;	// L21629
      int v13619 = v13618;	// L21630
      uint8_t v13620 = hold_cnt15[v13619];	// L21631
      int32_t v13621 = v13620;	// L21632
      bool v13622 = v13621 > 0;	// L21633
      if (v13622) {	// L21634
        b_vld15 = 1;	// L21635
      }
    }
    int32_t v13623 = s115;	// L21638
    bool v13624 = v13623 < 8;	// L21639
    int32_t v13625 = dsmask15;	// L21640
    int32_t v13626 = v13625 >> v13623;	// L21641
    int32_t v13627 = v13626 & 1;	// L21642
    bool v13628 = v13627 == 1;	// L21643
    bool v13629 = v13624 & v13628;	// L21644
    if (v13629) {	// L21645
      int32_t v13630 = s115;	// L21646
      int v13631 = v13630;	// L21647
      int32_t v13632 = drf_full15[v13631];	// L21648
      bool v13633 = v13632 == 0;	// L21649
      if (v13633) {	// L21650
        a_vld15 = 0;	// L21651
      }
    }
    int32_t v13634 = s215;	// L21654
    bool v13635 = v13634 < 8;	// L21655
    int32_t v13636 = dsmask15;	// L21656
    int32_t v13637 = v13636 >> v13634;	// L21657
    int32_t v13638 = v13637 & 1;	// L21658
    bool v13639 = v13638 == 1;	// L21659
    bool v13640 = v13635 & v13639;	// L21660
    if (v13640) {	// L21661
      int32_t v13641 = s215;	// L21662
      int v13642 = v13641;	// L21663
      int32_t v13643 = drf_full15[v13642];	// L21664
      bool v13644 = v13643 == 0;	// L21665
      if (v13644) {	// L21666
        b_vld15 = 0;	// L21667
      }
    }
    int32_t binop15;	// L21670
    binop15 = 0;	// L21671
    int32_t v13646 = op15;	// L21672
    bool v13647 = v13646 == 0;	// L21673
    bool v13648 = v13646 == 1;	// L21674
    bool v13649 = v13646 == 2;	// L21675
    bool v13650 = v13646 == 8;	// L21676
    bool v13651 = v13646 == 9;	// L21677
    bool v13652 = v13647 | v13648;	// L21678
    bool v13653 = v13652 | v13649;	// L21679
    bool v13654 = v13653 | v13650;	// L21680
    bool v13655 = v13654 | v13651;	// L21681
    if (v13655) {	// L21682
      binop15 = 1;	// L21683
    }
    int32_t raw15;	// L21685
    raw15 = 0;	// L21686
    int32_t cmp_busy15;	// L21687
    cmp_busy15 = 0;	// L21688
    l_S_k_5_k30: for (int k30 = 0; k30 < 4; k30++) {	// L21689
      uint8_t v13659 = sb_v15[(k30 + 1)];	// L21690
      int32_t v13660 = v13659;	// L21691
      bool v13661 = v13660 == 1;	// L21692
      uint8_t v13662 = sb_rtr15[(k30 + 1)];	// L21693
      int32_t v13663 = v13662;	// L21694
      bool v13664 = v13663 == 0;	// L21695
      uint8_t v13665 = sb_dst15[(k30 + 1)];	// L21696
      int32_t v13666 = v13665;	// L21697
      bool v13667 = v13666 < 12;	// L21698
      bool v13668 = v13661 & v13664;	// L21699
      bool v13669 = v13668 & v13667;	// L21700
      if (v13669) {	// L21701
        int32_t v13670 = s115;	// L21702
        bool v13671 = v13670 < 12;	// L21703
        uint8_t v13672 = sb_dst15[(k30 + 1)];	// L21704
        int32_t v13673 = v13672;	// L21705
        int32_t v13674 = v13673 & 7;	// L21706
        int32_t v13675 = v13670 & 7;	// L21707
        bool v13676 = v13674 == v13675;	// L21708
        bool v13677 = v13671 & v13676;	// L21709
        if (v13677) {	// L21710
          raw15 = 1;	// L21711
        }
        int32_t v13678 = binop15;	// L21713
        bool v13679 = v13678 == 1;	// L21714
        int32_t v13680 = s215;	// L21715
        bool v13681 = v13680 < 12;	// L21716
        uint8_t v13682 = sb_dst15[(k30 + 1)];	// L21717
        int32_t v13683 = v13682;	// L21718
        int32_t v13684 = v13683 & 7;	// L21719
        int32_t v13685 = v13680 & 7;	// L21720
        bool v13686 = v13684 == v13685;	// L21721
        bool v13687 = v13679 & v13681;	// L21722
        bool v13688 = v13687 & v13686;	// L21723
        if (v13688) {	// L21724
          raw15 = 1;	// L21725
        }
      }
      uint8_t v13689 = sb_v15[(k30 + 1)];	// L21728
      int32_t v13690 = v13689;	// L21729
      bool v13691 = v13690 == 1;	// L21730
      uint8_t v13692 = sb_cmp15[(k30 + 1)];	// L21731
      int32_t v13693 = v13692;	// L21732
      bool v13694 = v13693 == 1;	// L21733
      bool v13695 = v13691 & v13694;	// L21734
      if (v13695) {	// L21735
        cmp_busy15 = 1;	// L21736
      }
    }
    int32_t is_cond15;	// L21739
    is_cond15 = 0;	// L21740
    int32_t v13697 = op15;	// L21741
    bool v13698 = v13697 >= 12;	// L21742
    ap_int<33> v13699 = v13697;	// L21743
    bool v13700 = v13699 <= 15;	// L21744
    bool v13701 = v13698 & v13700;	// L21745
    if (v13701) {	// L21746
      is_cond15 = 1;	// L21747
    }
    int32_t grant15;	// L21749
    grant15 = 0;	// L21750
    int32_t v13703 = pc15;	// L21751
    bool v13704 = v13703 >= 0;	// L21752
    if (v13704) {	// L21753
      grant15 = 1;	// L21754
    }
    int32_t v13705 = pc15;	// L21756
    bool v13706 = v13705 >= 0;	// L21757
    int32_t v13707 = a_vld15;	// L21758
    bool v13708 = v13707 == 0;	// L21759
    int32_t v13709 = binop15;	// L21760
    bool v13710 = v13709 == 1;	// L21761
    int32_t v13711 = b_vld15;	// L21762
    bool v13712 = v13711 == 0;	// L21763
    bool v13713 = v13710 & v13712;	// L21764
    bool v13714 = v13708 | v13713;	// L21765
    bool v13715 = v13706 & v13714;	// L21766
    if (v13715) {	// L21767
      grant15 = 0;	// L21768
    }
    int32_t v13716 = pc15;	// L21770
    bool v13717 = v13716 >= 0;	// L21771
    int32_t v13718 = raw15;	// L21772
    bool v13719 = v13718 == 1;	// L21773
    int32_t v13720 = is_cond15;	// L21774
    bool v13721 = v13720 == 1;	// L21775
    int32_t v13722 = cmp_busy15;	// L21776
    bool v13723 = v13722 == 1;	// L21777
    bool v13724 = v13721 & v13723;	// L21778
    bool v13725 = v13719 | v13724;	// L21779
    bool v13726 = v13717 & v13725;	// L21780
    if (v13726) {	// L21781
      grant15 = 0;	// L21782
    }
    int32_t v13727 = grant15;	// L21784
    bool v13728 = v13727 == 1;	// L21785
    if (v13728) {	// L21786
      int8_t v13729 = instr_cnt15;	// L21787
      int32_t v13730 = cfg_isz15;	// L21788
      int32_t v13731 = v13729;	// L21789
      bool v13732 = v13731 == v13730;	// L21790
      if (v13732) {	// L21791
        instr_cnt15 = 0;	// L21792
        int8_t v13733 = iter_cnt15;	// L21793
        int32_t v13734 = cfg_itsz15;	// L21794
        ap_int<33> v13735 = v13734;	// L21795
        ap_int<33> v13736 = v13735 - 1;	// L21796
        ap_int<33> v13737 = v13733;	// L21797
        bool v13738 = v13737 == v13736;	// L21798
        if (v13738) {	// L21799
          fetch_en15 = 0;	// L21800
        } else {
          int8_t v13739 = iter_cnt15;	// L21802
          ap_int<33> v13740 = v13739;	// L21803
          ap_int<33> v13741 = v13740 + 1;	// L21804
          uint8_t v13742 = v13741;	// L21805
          iter_cnt15 = v13742;	// L21806
        }
      } else {
        int8_t v13743 = instr_cnt15;	// L21809
        ap_int<33> v13744 = v13743;	// L21810
        ap_int<33> v13745 = v13744 + 1;	// L21811
        uint8_t v13746 = v13745;	// L21812
        instr_cnt15 = v13746;	// L21813
      }
    }
    int32_t c115;	// L21816
    c115 = -1;	// L21817
    int32_t c215;	// L21818
    c215 = -1;	// L21819
    int32_t v13749 = grant15;	// L21820
    bool v13750 = v13749 == 1;	// L21821
    int32_t v13751 = s115;	// L21822
    bool v13752 = v13751 >= 12;	// L21823
    bool v13753 = v13750 & v13752;	// L21824
    if (v13753) {	// L21825
      int32_t v13754 = s115;	// L21826
      int32_t v13755 = v13754 & 3;	// L21827
      c115 = v13755;	// L21828
    }
    int32_t v13756 = grant15;	// L21830
    bool v13757 = v13756 == 1;	// L21831
    int32_t v13758 = s215;	// L21832
    bool v13759 = v13758 >= 12;	// L21833
    bool v13760 = v13757 & v13759;	// L21834
    if (v13760) {	// L21835
      int32_t v13761 = s215;	// L21836
      int32_t v13762 = v13761 & 3;	// L21837
      c215 = v13762;	// L21838
    }
    int32_t v13763 = c115;	// L21840
    bool v13764 = v13763 >= 0;	// L21841
    if (v13764) {	// L21842
      int32_t v13765 = c115;	// L21843
      int v13766 = v13765;	// L21844
      half v13767 = hold_v15[v13766][1];	// L21845
      hold_v15[v13766][0] = v13767;	// L21846
      int32_t v13768 = c115;	// L21847
      int v13769 = v13768;	// L21848
      uint8_t v13770 = hold_cnt15[v13769];	// L21849
      ap_int<33> v13771 = v13770;	// L21850
      ap_int<33> v13772 = v13771 - 1;	// L21851
      uint8_t v13773 = v13772;	// L21852
      hold_cnt15[v13769] = v13773;	// L21853
    }
    int32_t v13774 = c215;	// L21855
    bool v13775 = v13774 >= 0;	// L21856
    int32_t v13776 = c115;	// L21857
    bool v13777 = v13774 != v13776;	// L21858
    bool v13778 = v13775 & v13777;	// L21859
    if (v13778) {	// L21860
      int32_t v13779 = c215;	// L21861
      int v13780 = v13779;	// L21862
      half v13781 = hold_v15[v13780][1];	// L21863
      hold_v15[v13780][0] = v13781;	// L21864
      int32_t v13782 = c215;	// L21865
      int v13783 = v13782;	// L21866
      uint8_t v13784 = hold_cnt15[v13783];	// L21867
      ap_int<33> v13785 = v13784;	// L21868
      ap_int<33> v13786 = v13785 - 1;	// L21869
      uint8_t v13787 = v13786;	// L21870
      hold_cnt15[v13783] = v13787;	// L21871
    }
    int32_t v13788 = grant15;	// L21873
    bool v13789 = v13788 == 1;	// L21874
    int32_t v13790 = s115;	// L21875
    bool v13791 = v13790 < 8;	// L21876
    int32_t v13792 = dsmask15;	// L21877
    int32_t v13793 = v13792 >> v13790;	// L21878
    int32_t v13794 = v13793 & 1;	// L21879
    bool v13795 = v13794 == 1;	// L21880
    bool v13796 = v13789 & v13791;	// L21881
    bool v13797 = v13796 & v13795;	// L21882
    if (v13797) {	// L21883
      int32_t v13798 = s115;	// L21884
      int v13799 = v13798;	// L21885
      drf_full15[v13799] = 0;	// L21886
    }
    int32_t v13800 = grant15;	// L21888
    bool v13801 = v13800 == 1;	// L21889
    int32_t v13802 = s215;	// L21890
    bool v13803 = v13802 < 8;	// L21891
    int32_t v13804 = dsmask15;	// L21892
    int32_t v13805 = v13804 >> v13802;	// L21893
    int32_t v13806 = v13805 & 1;	// L21894
    bool v13807 = v13806 == 1;	// L21895
    bool v13808 = v13801 & v13803;	// L21896
    bool v13809 = v13808 & v13807;	// L21897
    if (v13809) {	// L21898
      int32_t v13810 = s215;	// L21899
      int v13811 = v13810;	// L21900
      drf_full15[v13811] = 0;	// L21901
    }
    half res15;
#pragma HLS dependence variable=res15 type=inter dependent=false	// L21903
    res15 = 0.000000;	// L21904
    int32_t v13813 = op15;	// L21905
    bool v13814 = v13813 == 0;	// L21906
    if (v13814) {	// L21907
      half v13815 = a15;	// L21908
      half v13816 = b15;	// L21909
      half v13817 = v13815 + v13816;	// L21910
      res15 = v13817;	// L21911
    } else {
      int32_t v13818 = op15;	// L21913
      bool v13819 = v13818 == 1;	// L21914
      if (v13819) {	// L21915
        half v13820 = a15;	// L21916
        half v13821 = b15;	// L21917
        half v13822 = v13820 - v13821;	// L21918
        res15 = v13822;	// L21919
      } else {
        int32_t v13823 = op15;	// L21921
        bool v13824 = v13823 == 2;	// L21922
        if (v13824) {	// L21923
          half v13825 = a15;	// L21924
          half v13826 = b15;	// L21925
          half v13827 = v13825 * v13826;	// L21926
          res15 = v13827;	// L21927
        } else {
          int32_t v13828 = op15;	// L21929
          bool v13829 = v13828 == 8;	// L21930
          if (v13829) {	// L21931
            half v13830 = a15;	// L21932
            half v13831 = b15;	// L21933
            bool v13832 = v13830 >= v13831;	// L21934
            if (v13832) {	// L21935
              res15 = 1.000000;	// L21936
            } else {
              res15 = -1.000000;	// L21938
            }
          } else {
            int32_t v13833 = op15;	// L21941
            bool v13834 = v13833 == 9;	// L21942
            if (v13834) {	// L21943
              half v13835 = a15;	// L21944
              half v13836 = b15;	// L21945
              bool v13837 = v13835 < v13836;	// L21946
              if (v13837) {	// L21947
                res15 = 1.000000;	// L21948
              } else {
                res15 = -1.000000;	// L21950
              }
            } else {
              half v13838 = a15;	// L21953
              res15 = v13838;	// L21954
            }
          }
        }
      }
    }
    int32_t v13839 = a_vld15;	// L21960
    int32_t res_vld15;	// L21961
    res_vld15 = v13839;	// L21962
    int32_t v13841 = op15;	// L21963
    bool v13842 = v13841 == 0;	// L21964
    bool v13843 = v13841 == 1;	// L21965
    bool v13844 = v13841 == 2;	// L21966
    bool v13845 = v13841 == 8;	// L21967
    bool v13846 = v13841 == 9;	// L21968
    bool v13847 = v13842 | v13843;	// L21969
    bool v13848 = v13847 | v13844;	// L21970
    bool v13849 = v13848 | v13845;	// L21971
    bool v13850 = v13849 | v13846;	// L21972
    if (v13850) {	// L21973
      int32_t v13851 = a_vld15;	// L21974
      int32_t v13852 = b_vld15;	// L21975
      int64_t v13853 = v13851;	// L21976
      int64_t v13854 = v13852;	// L21977
      int64_t v13855 = v13853 * v13854;	// L21978
      int32_t v13856 = v13855;	// L21979
      res_vld15 = v13856;	// L21980
    }
    int32_t v13857 = grant15;	// L21982
    bool v13858 = v13857 == 0;	// L21983
    if (v13858) {	// L21984
      res_vld15 = 0;	// L21985
    }
    int32_t is_rtr15;	// L21987
    is_rtr15 = 0;	// L21988
    int32_t v13860 = op15;	// L21989
    bool v13861 = v13860 >= 4;	// L21990
    ap_int<33> v13862 = v13860;	// L21991
    bool v13863 = v13862 <= 7;	// L21992
    bool v13864 = v13861 & v13863;	// L21993
    if (v13864) {	// L21994
      is_rtr15 = 1;	// L21995
    }
    l_S_k_6_k31: for (int k31 = 0; k31 < 4; k31++) {	// L21997
      uint8_t v13866 = sb_v15[(k31 + 1)];	// L21998
      sb_v15[k31] = v13866;	// L21999
      uint8_t v13867 = sb_dst15[(k31 + 1)];	// L22000
      sb_dst15[k31] = v13867;	// L22001
      uint8_t v13868 = sb_cmp15[(k31 + 1)];	// L22002
      sb_cmp15[k31] = v13868;	// L22003
      uint8_t v13869 = sb_rtr15[(k31 + 1)];	// L22004
      sb_rtr15[k31] = v13869;	// L22005
      uint8_t v13870 = sb_inj15[(k31 + 1)];	// L22006
      sb_inj15[k31] = v13870;	// L22007
      uint8_t v13871 = sb_dir15[(k31 + 1)];	// L22008
      sb_dir15[k31] = v13871;	// L22009
      uint8_t v13872 = sb_id15[(k31 + 1)];	// L22010
      sb_id15[k31] = v13872;	// L22011
      uint8_t v13873 = sb_rvld15[(k31 + 1)];	// L22012
      sb_rvld15[k31] = v13873;	// L22013
      uint8_t v13874 = sb_ix15[(k31 + 1)];	// L22014
      sb_ix15[k31] = v13874;	// L22015
    }
    sb_v15[4] = 0;	// L22017
    int32_t v13875 = grant15;	// L22018
    bool v13876 = v13875 == 1;	// L22019
    if (v13876) {	// L22020
      half v13877 = res15;	// L22021
      int8_t v13878 = resq_wr15;	// L22022
      int v13879 = v13878;	// L22023
      resq15[v13879] = v13877;	// L22024
      int32_t cq15;	// L22025
      cq15 = 0;	// L22026
      int32_t v13881 = op15;	// L22027
      bool v13882 = v13881 == 8;	// L22028
      if (v13882) {	// L22029
        half v13883 = a15;	// L22030
        half v13884 = b15;	// L22031
        bool v13885 = v13883 >= v13884;	// L22032
        if (v13885) {	// L22033
          cq15 = 1;	// L22034
        }
      }
      int32_t v13886 = op15;	// L22037
      bool v13887 = v13886 == 9;	// L22038
      if (v13887) {	// L22039
        half v13888 = a15;	// L22040
        half v13889 = b15;	// L22041
        bool v13890 = v13888 < v13889;	// L22042
        if (v13890) {	// L22043
          cq15 = 1;	// L22044
        }
      }
      int32_t v13891 = cq15;	// L22047
      uint8_t v13892 = v13891;	// L22048
      int8_t v13893 = resq_wr15;	// L22049
      int v13894 = v13893;	// L22050
      cmpq15[v13894] = v13892;	// L22051
      sb_v15[4] = 1;	// L22052
      int32_t v13895 = dst15;	// L22053
      uint8_t v13896 = v13895;	// L22054
      sb_dst15[4] = v13896;	// L22055
      int8_t v13897 = resq_wr15;	// L22056
      sb_ix15[4] = v13897;	// L22057
      sb_cmp15[4] = 0;	// L22058
      int32_t v13898 = op15;	// L22059
      bool v13899 = v13898 == 8;	// L22060
      bool v13900 = v13898 == 9;	// L22061
      bool v13901 = v13899 | v13900;	// L22062
      if (v13901) {	// L22063
        sb_cmp15[4] = 1;	// L22064
      }
      int32_t v13902 = is_rtr15;	// L22066
      int32_t rtrf15;	// L22067
      rtrf15 = v13902;	// L22068
      int32_t v13904 = is_cond15;	// L22069
      bool v13905 = v13904 == 1;	// L22070
      if (v13905) {	// L22071
        rtrf15 = 1;	// L22072
      }
      int32_t v13906 = rtrf15;	// L22074
      uint8_t v13907 = v13906;	// L22075
      sb_rtr15[4] = v13907;	// L22076
      int32_t v13908 = is_rtr15;	// L22077
      int32_t inj15;	// L22078
      inj15 = v13908;	// L22079
      int32_t v13910 = is_cond15;	// L22080
      bool v13911 = v13910 == 1;	// L22081
      int8_t v13912 = condition_reg15;	// L22082
      int32_t v13913 = v13912;	// L22083
      bool v13914 = v13913 == 1;	// L22084
      bool v13915 = v13911 & v13914;	// L22085
      if (v13915) {	// L22086
        inj15 = 1;	// L22087
      }
      int32_t v13916 = inj15;	// L22089
      uint8_t v13917 = v13916;	// L22090
      sb_inj15[4] = v13917;	// L22091
      int32_t v13918 = op15;	// L22092
      int32_t v13919 = v13918 & 3;	// L22093
      uint8_t v13920 = v13919;	// L22094
      sb_dir15[4] = v13920;	// L22095
      int32_t v13921 = s215;	// L22096
      uint8_t v13922 = v13921;	// L22097
      sb_id15[4] = v13922;	// L22098
      int32_t v13923 = res_vld15;	// L22099
      uint8_t v13924 = v13923;	// L22100
      sb_rvld15[4] = v13924;	// L22101
      int8_t v13925 = resq_wr15;	// L22102
      ap_int<33> v13926 = v13925;	// L22103
      ap_int<33> v13927 = v13926 + 1;	// L22104
      ap_int<33> v13928 = v13927 & 7;	// L22105
      uint8_t v13929 = v13928;	// L22106
      resq_wr15 = v13929;	// L22107
    }
    ap_int<17> v13930 = tx_n15;	// L22109
    txn_r15 = v13930;	// L22110
    ap_int<17> v13931 = tx_s15;	// L22111
    txs_r15 = v13931;	// L22112
    ap_int<17> v13932 = tx_w15;	// L22113
    txw_r15 = v13932;	// L22114
    ap_int<17> v13933 = tx_e15;	// L22115
    txe_r15 = v13933;	// L22116
    int32_t v13934 = crv_vld15;	// L22117
    bool v13935 = v13934 == 1;	// L22118
    if (v13935) {	// L22119
      int32_t v13936 = crv_mode15;	// L22120
      bool v13937 = v13936 == 1;	// L22121
      if (v13937) {	// L22122
        int32_t v13938 = crv_addr15;	// L22123
        int32_t v13939 = v13938 >> 3;	// L22124
        int32_t v13940 = v13939 & 1;	// L22125
        bool v13941 = v13940 == 1;	// L22126
        if (v13941) {	// L22127
          int32_t v13942 = crv_raw15;	// L22128
          int32_t v13943 = crv_addr15;	// L22129
          int32_t v13944 = v13943 & 7;	// L22130
          int v13945 = v13944;	// L22131
          irf15[v13945] = v13942;	// L22132
        } else {
          int32_t v13946 = crv_addr15;	// L22134
          bool v13947 = v13946 == 0;	// L22135
          if (v13947) {	// L22136
            int32_t v13948 = crv_raw15;	// L22137
            int32_t v13949 = v13948 & 255;	// L22138
            dsmask15 = v13949;	// L22139
            int32_t v13950 = crv_raw15;	// L22140
            int32_t v13951 = v13950 >> 8;	// L22141
            int32_t v13952 = v13951 & 7;	// L22142
            cfg_isz15 = v13952;	// L22143
            int32_t v13953 = crv_raw15;	// L22144
            int32_t v13954 = v13953 >> 15;	// L22145
            int32_t v13955 = v13954 & 1;	// L22146
            bool v13956 = v13955 == 1;	// L22147
            if (v13956) {	// L22148
              fetch_en15 = 1;	// L22149
              instr_cnt15 = 0;	// L22150
              iter_cnt15 = 0;	// L22151
            }
          } else {
            int32_t v13957 = crv_addr15;	// L22154
            bool v13958 = v13957 == 1;	// L22155
            if (v13958) {	// L22156
              int32_t v13959 = crv_raw15;	// L22157
              int32_t v13960 = v13959 & 255;	// L22158
              cfg_itsz15 = v13960;	// L22159
            }
          }
        }
      } else {
        int32_t v13961 = crv_addr15;	// L22164
        bool v13962 = v13961 < 8;	// L22165
        int32_t v13963 = dsmask15;	// L22166
        int32_t v13964 = v13963 >> v13961;	// L22167
        int32_t v13965 = v13964 & 1;	// L22168
        bool v13966 = v13965 == 1;	// L22169
        bool v13967 = v13962 & v13966;	// L22170
        if (v13967) {	// L22171
          int32_t v13968 = crv_addr15;	// L22172
          int v13969 = v13968;	// L22173
          int32_t v13970 = drf_full15[v13969];	// L22174
          bool v13971 = v13970 == 0;	// L22175
          if (v13971) {	// L22176
            half v13972 = crv_data15;	// L22177
            int32_t v13973 = crv_addr15;	// L22178
            int v13974 = v13973;	// L22179
            drf15[v13974] = v13972;	// L22180
            int32_t v13975 = crv_addr15;	// L22181
            int v13976 = v13975;	// L22182
            drf_full15[v13976] = 1;	// L22183
          }
        } else {
          half v13977 = crv_data15;	// L22186
          int32_t v13978 = crv_addr15;	// L22187
          int v13979 = v13978;	// L22188
          drf15[v13979] = v13977;	// L22189
        }
      }
    }
    ap_int<17> v13980 = txe_r15;	// L22193
    bool v13981;
    ap_int<17> v13981_tmp = v13980;
    v13981 = v13981_tmp[0];	// L22194
    int32_t v13982 = v13981;	// L22195
    bool v13983 = v13982 == 1;	// L22196
    if (v13983) {	// L22197
      ap_int<17> v13984 = txe_r15;	// L22198
      v13137.write(v13984);	// L22199
    }
    ap_int<17> v13985 = txw_r15;	// L22201
    bool v13986;
    ap_int<17> v13986_tmp = v13985;
    v13986 = v13986_tmp[0];	// L22202
    int32_t v13987 = v13986;	// L22203
    bool v13988 = v13987 == 1;	// L22204
    if (v13988) {	// L22205
      ap_int<17> v13989 = txw_r15;	// L22206
      v13138.write(v13989);	// L22207
    }
    ap_int<17> v13990 = txs_r15;	// L22209
    bool v13991;
    ap_int<17> v13991_tmp = v13990;
    v13991 = v13991_tmp[0];	// L22210
    int32_t v13992 = v13991;	// L22211
    bool v13993 = v13992 == 1;	// L22212
    if (v13993) {	// L22213
      ap_int<17> v13994 = txs_r15;	// L22214
      v13139.write(v13994);	// L22215
    }
    ap_int<17> v13995 = txn_r15;	// L22217
    bool v13996;
    ap_int<17> v13996_tmp = v13995;
    v13996 = v13996_tmp[0];	// L22218
    int32_t v13997 = v13996;	// L22219
    bool v13998 = v13997 == 1;	// L22220
    if (v13998) {	// L22221
      ap_int<17> v13999 = txn_r15;	// L22222
      v13140.write(v13999);	// L22223
    }
  }
}

void drv_w_0(
  half v14000[4][374],
  int32_t v14001[4][374],
  hls::stream< ap_uint<17> >& v14002,
  hls::stream< ap_uint<17> >& v14003,
  hls::stream< ap_uint<17> >& v14004,
  hls::stream< ap_uint<17> >& v14005
) {	// L22228
  int32_t sp_w[4];	// L22239
  for (int v14007 = 0; v14007 < 4; v14007++) {	// L22240
    sp_w[v14007] = 0;	// L22240
  }
  l_S_t_0_t16: for (int t16 = 0; t16 < 374; t16++) {	// L22241
    int32_t v14009 = sp_w[0];	// L22242
    bool v14010 = v14009 < 374;	// L22243
    if (v14010) {	// L22244
      int32_t v14011 = sp_w[0];	// L22245
      int v14012 = v14011;	// L22246
      int32_t v14013 = v14001[0][v14012];	// L22247
      bool v14014 = v14013 == 0;	// L22248
      if (v14014) {	// L22249
        int32_t v14015 = sp_w[0];	// L22250
        ap_int<33> v14016 = v14015;	// L22251
        ap_int<33> v14017 = v14016 + 1;	// L22252
        int32_t v14018 = v14017;	// L22253
        sp_w[0] = v14018;	// L22254
      } else {
        ap_uint<17> w;	// L22256
        w = 0;	// L22257
        ap_int<17> v14020 = w;	// L22258
        ap_int<17> v14021;
        ap_int<17> v14021_tmp = v14020;
        v14021_tmp[0] = 1;        v14021 = v14021_tmp;	// L22259
        w = v14021;	// L22260
        int32_t v14022 = sp_w[0];	// L22261
        int v14023 = v14022;	// L22262
        half v14024 = v14000[0][v14023];	// L22263
        uint16_t v14025;
        union { half from; uint16_t to;} _converter_v14024_to_v14025 = {};
        _converter_v14024_to_v14025.from = v14024;
        v14025 = _converter_v14024_to_v14025.to;	// L22264
        ap_int<17> v14026 = w;	// L22265
        ap_int<17> v14027;
        ap_int<17> v14027_tmp = v14026;
        v14027_tmp(16, 1) = v14025;
        v14027 = v14027_tmp;	// L22266
        w = v14027;	// L22267
        ap_int<17> v14028 = w;	// L22268
        bool v14029 = v14002.write_nb(v14028);
	// L22269
        if (v14029) {	// L22270
          int32_t v14030 = sp_w[0];	// L22271
          ap_int<33> v14031 = v14030;	// L22272
          ap_int<33> v14032 = v14031 + 1;	// L22273
          int32_t v14033 = v14032;	// L22274
          sp_w[0] = v14033;	// L22275
        }
      }
    }
    int32_t v14034 = sp_w[1];	// L22279
    bool v14035 = v14034 < 374;	// L22280
    if (v14035) {	// L22281
      int32_t v14036 = sp_w[1];	// L22282
      int v14037 = v14036;	// L22283
      int32_t v14038 = v14001[1][v14037];	// L22284
      bool v14039 = v14038 == 0;	// L22285
      if (v14039) {	// L22286
        int32_t v14040 = sp_w[1];	// L22287
        ap_int<33> v14041 = v14040;	// L22288
        ap_int<33> v14042 = v14041 + 1;	// L22289
        int32_t v14043 = v14042;	// L22290
        sp_w[1] = v14043;	// L22291
      } else {
        ap_uint<17> w1;	// L22293
        w1 = 0;	// L22294
        ap_int<17> v14045 = w1;	// L22295
        ap_int<17> v14046;
        ap_int<17> v14046_tmp = v14045;
        v14046_tmp[0] = 1;        v14046 = v14046_tmp;	// L22296
        w1 = v14046;	// L22297
        int32_t v14047 = sp_w[1];	// L22298
        int v14048 = v14047;	// L22299
        half v14049 = v14000[1][v14048];	// L22300
        uint16_t v14050;
        union { half from; uint16_t to;} _converter_v14049_to_v14050 = {};
        _converter_v14049_to_v14050.from = v14049;
        v14050 = _converter_v14049_to_v14050.to;	// L22301
        ap_int<17> v14051 = w1;	// L22302
        ap_int<17> v14052;
        ap_int<17> v14052_tmp = v14051;
        v14052_tmp(16, 1) = v14050;
        v14052 = v14052_tmp;	// L22303
        w1 = v14052;	// L22304
        ap_int<17> v14053 = w1;	// L22305
        bool v14054 = v14003.write_nb(v14053);
	// L22306
        if (v14054) {	// L22307
          int32_t v14055 = sp_w[1];	// L22308
          ap_int<33> v14056 = v14055;	// L22309
          ap_int<33> v14057 = v14056 + 1;	// L22310
          int32_t v14058 = v14057;	// L22311
          sp_w[1] = v14058;	// L22312
        }
      }
    }
    int32_t v14059 = sp_w[2];	// L22316
    bool v14060 = v14059 < 374;	// L22317
    if (v14060) {	// L22318
      int32_t v14061 = sp_w[2];	// L22319
      int v14062 = v14061;	// L22320
      int32_t v14063 = v14001[2][v14062];	// L22321
      bool v14064 = v14063 == 0;	// L22322
      if (v14064) {	// L22323
        int32_t v14065 = sp_w[2];	// L22324
        ap_int<33> v14066 = v14065;	// L22325
        ap_int<33> v14067 = v14066 + 1;	// L22326
        int32_t v14068 = v14067;	// L22327
        sp_w[2] = v14068;	// L22328
      } else {
        ap_uint<17> w2;	// L22330
        w2 = 0;	// L22331
        ap_int<17> v14070 = w2;	// L22332
        ap_int<17> v14071;
        ap_int<17> v14071_tmp = v14070;
        v14071_tmp[0] = 1;        v14071 = v14071_tmp;	// L22333
        w2 = v14071;	// L22334
        int32_t v14072 = sp_w[2];	// L22335
        int v14073 = v14072;	// L22336
        half v14074 = v14000[2][v14073];	// L22337
        uint16_t v14075;
        union { half from; uint16_t to;} _converter_v14074_to_v14075 = {};
        _converter_v14074_to_v14075.from = v14074;
        v14075 = _converter_v14074_to_v14075.to;	// L22338
        ap_int<17> v14076 = w2;	// L22339
        ap_int<17> v14077;
        ap_int<17> v14077_tmp = v14076;
        v14077_tmp(16, 1) = v14075;
        v14077 = v14077_tmp;	// L22340
        w2 = v14077;	// L22341
        ap_int<17> v14078 = w2;	// L22342
        bool v14079 = v14004.write_nb(v14078);
	// L22343
        if (v14079) {	// L22344
          int32_t v14080 = sp_w[2];	// L22345
          ap_int<33> v14081 = v14080;	// L22346
          ap_int<33> v14082 = v14081 + 1;	// L22347
          int32_t v14083 = v14082;	// L22348
          sp_w[2] = v14083;	// L22349
        }
      }
    }
    int32_t v14084 = sp_w[3];	// L22353
    bool v14085 = v14084 < 374;	// L22354
    if (v14085) {	// L22355
      int32_t v14086 = sp_w[3];	// L22356
      int v14087 = v14086;	// L22357
      int32_t v14088 = v14001[3][v14087];	// L22358
      bool v14089 = v14088 == 0;	// L22359
      if (v14089) {	// L22360
        int32_t v14090 = sp_w[3];	// L22361
        ap_int<33> v14091 = v14090;	// L22362
        ap_int<33> v14092 = v14091 + 1;	// L22363
        int32_t v14093 = v14092;	// L22364
        sp_w[3] = v14093;	// L22365
      } else {
        ap_uint<17> w3;	// L22367
        w3 = 0;	// L22368
        ap_int<17> v14095 = w3;	// L22369
        ap_int<17> v14096;
        ap_int<17> v14096_tmp = v14095;
        v14096_tmp[0] = 1;        v14096 = v14096_tmp;	// L22370
        w3 = v14096;	// L22371
        int32_t v14097 = sp_w[3];	// L22372
        int v14098 = v14097;	// L22373
        half v14099 = v14000[3][v14098];	// L22374
        uint16_t v14100;
        union { half from; uint16_t to;} _converter_v14099_to_v14100 = {};
        _converter_v14099_to_v14100.from = v14099;
        v14100 = _converter_v14099_to_v14100.to;	// L22375
        ap_int<17> v14101 = w3;	// L22376
        ap_int<17> v14102;
        ap_int<17> v14102_tmp = v14101;
        v14102_tmp(16, 1) = v14100;
        v14102 = v14102_tmp;	// L22377
        w3 = v14102;	// L22378
        ap_int<17> v14103 = w3;	// L22379
        bool v14104 = v14005.write_nb(v14103);
	// L22380
        if (v14104) {	// L22381
          int32_t v14105 = sp_w[3];	// L22382
          ap_int<33> v14106 = v14105;	// L22383
          ap_int<33> v14107 = v14106 + 1;	// L22384
          int32_t v14108 = v14107;	// L22385
          sp_w[3] = v14108;	// L22386
        }
      }
    }
  }
}

void drv_e_0(
  half v14109[4][374],
  int32_t v14110[4][374],
  hls::stream< ap_uint<17> >& v14111,
  hls::stream< ap_uint<17> >& v14112,
  hls::stream< ap_uint<17> >& v14113,
  hls::stream< ap_uint<17> >& v14114
) {	// L22393
  int32_t sp_e[4];	// L22404
  for (int v14116 = 0; v14116 < 4; v14116++) {	// L22405
    sp_e[v14116] = 0;	// L22405
  }
  l_S_t_0_t17: for (int t17 = 0; t17 < 374; t17++) {	// L22406
    int32_t v14118 = sp_e[0];	// L22407
    bool v14119 = v14118 < 374;	// L22408
    if (v14119) {	// L22409
      int32_t v14120 = sp_e[0];	// L22410
      int v14121 = v14120;	// L22411
      int32_t v14122 = v14110[0][v14121];	// L22412
      bool v14123 = v14122 == 0;	// L22413
      if (v14123) {	// L22414
        int32_t v14124 = sp_e[0];	// L22415
        ap_int<33> v14125 = v14124;	// L22416
        ap_int<33> v14126 = v14125 + 1;	// L22417
        int32_t v14127 = v14126;	// L22418
        sp_e[0] = v14127;	// L22419
      } else {
        ap_uint<17> w4;	// L22421
        w4 = 0;	// L22422
        ap_int<17> v14129 = w4;	// L22423
        ap_int<17> v14130;
        ap_int<17> v14130_tmp = v14129;
        v14130_tmp[0] = 1;        v14130 = v14130_tmp;	// L22424
        w4 = v14130;	// L22425
        int32_t v14131 = sp_e[0];	// L22426
        int v14132 = v14131;	// L22427
        half v14133 = v14109[0][v14132];	// L22428
        uint16_t v14134;
        union { half from; uint16_t to;} _converter_v14133_to_v14134 = {};
        _converter_v14133_to_v14134.from = v14133;
        v14134 = _converter_v14133_to_v14134.to;	// L22429
        ap_int<17> v14135 = w4;	// L22430
        ap_int<17> v14136;
        ap_int<17> v14136_tmp = v14135;
        v14136_tmp(16, 1) = v14134;
        v14136 = v14136_tmp;	// L22431
        w4 = v14136;	// L22432
        ap_int<17> v14137 = w4;	// L22433
        bool v14138 = v14111.write_nb(v14137);
	// L22434
        if (v14138) {	// L22435
          int32_t v14139 = sp_e[0];	// L22436
          ap_int<33> v14140 = v14139;	// L22437
          ap_int<33> v14141 = v14140 + 1;	// L22438
          int32_t v14142 = v14141;	// L22439
          sp_e[0] = v14142;	// L22440
        }
      }
    }
    int32_t v14143 = sp_e[1];	// L22444
    bool v14144 = v14143 < 374;	// L22445
    if (v14144) {	// L22446
      int32_t v14145 = sp_e[1];	// L22447
      int v14146 = v14145;	// L22448
      int32_t v14147 = v14110[1][v14146];	// L22449
      bool v14148 = v14147 == 0;	// L22450
      if (v14148) {	// L22451
        int32_t v14149 = sp_e[1];	// L22452
        ap_int<33> v14150 = v14149;	// L22453
        ap_int<33> v14151 = v14150 + 1;	// L22454
        int32_t v14152 = v14151;	// L22455
        sp_e[1] = v14152;	// L22456
      } else {
        ap_uint<17> w5;	// L22458
        w5 = 0;	// L22459
        ap_int<17> v14154 = w5;	// L22460
        ap_int<17> v14155;
        ap_int<17> v14155_tmp = v14154;
        v14155_tmp[0] = 1;        v14155 = v14155_tmp;	// L22461
        w5 = v14155;	// L22462
        int32_t v14156 = sp_e[1];	// L22463
        int v14157 = v14156;	// L22464
        half v14158 = v14109[1][v14157];	// L22465
        uint16_t v14159;
        union { half from; uint16_t to;} _converter_v14158_to_v14159 = {};
        _converter_v14158_to_v14159.from = v14158;
        v14159 = _converter_v14158_to_v14159.to;	// L22466
        ap_int<17> v14160 = w5;	// L22467
        ap_int<17> v14161;
        ap_int<17> v14161_tmp = v14160;
        v14161_tmp(16, 1) = v14159;
        v14161 = v14161_tmp;	// L22468
        w5 = v14161;	// L22469
        ap_int<17> v14162 = w5;	// L22470
        bool v14163 = v14112.write_nb(v14162);
	// L22471
        if (v14163) {	// L22472
          int32_t v14164 = sp_e[1];	// L22473
          ap_int<33> v14165 = v14164;	// L22474
          ap_int<33> v14166 = v14165 + 1;	// L22475
          int32_t v14167 = v14166;	// L22476
          sp_e[1] = v14167;	// L22477
        }
      }
    }
    int32_t v14168 = sp_e[2];	// L22481
    bool v14169 = v14168 < 374;	// L22482
    if (v14169) {	// L22483
      int32_t v14170 = sp_e[2];	// L22484
      int v14171 = v14170;	// L22485
      int32_t v14172 = v14110[2][v14171];	// L22486
      bool v14173 = v14172 == 0;	// L22487
      if (v14173) {	// L22488
        int32_t v14174 = sp_e[2];	// L22489
        ap_int<33> v14175 = v14174;	// L22490
        ap_int<33> v14176 = v14175 + 1;	// L22491
        int32_t v14177 = v14176;	// L22492
        sp_e[2] = v14177;	// L22493
      } else {
        ap_uint<17> w6;	// L22495
        w6 = 0;	// L22496
        ap_int<17> v14179 = w6;	// L22497
        ap_int<17> v14180;
        ap_int<17> v14180_tmp = v14179;
        v14180_tmp[0] = 1;        v14180 = v14180_tmp;	// L22498
        w6 = v14180;	// L22499
        int32_t v14181 = sp_e[2];	// L22500
        int v14182 = v14181;	// L22501
        half v14183 = v14109[2][v14182];	// L22502
        uint16_t v14184;
        union { half from; uint16_t to;} _converter_v14183_to_v14184 = {};
        _converter_v14183_to_v14184.from = v14183;
        v14184 = _converter_v14183_to_v14184.to;	// L22503
        ap_int<17> v14185 = w6;	// L22504
        ap_int<17> v14186;
        ap_int<17> v14186_tmp = v14185;
        v14186_tmp(16, 1) = v14184;
        v14186 = v14186_tmp;	// L22505
        w6 = v14186;	// L22506
        ap_int<17> v14187 = w6;	// L22507
        bool v14188 = v14113.write_nb(v14187);
	// L22508
        if (v14188) {	// L22509
          int32_t v14189 = sp_e[2];	// L22510
          ap_int<33> v14190 = v14189;	// L22511
          ap_int<33> v14191 = v14190 + 1;	// L22512
          int32_t v14192 = v14191;	// L22513
          sp_e[2] = v14192;	// L22514
        }
      }
    }
    int32_t v14193 = sp_e[3];	// L22518
    bool v14194 = v14193 < 374;	// L22519
    if (v14194) {	// L22520
      int32_t v14195 = sp_e[3];	// L22521
      int v14196 = v14195;	// L22522
      int32_t v14197 = v14110[3][v14196];	// L22523
      bool v14198 = v14197 == 0;	// L22524
      if (v14198) {	// L22525
        int32_t v14199 = sp_e[3];	// L22526
        ap_int<33> v14200 = v14199;	// L22527
        ap_int<33> v14201 = v14200 + 1;	// L22528
        int32_t v14202 = v14201;	// L22529
        sp_e[3] = v14202;	// L22530
      } else {
        ap_uint<17> w7;	// L22532
        w7 = 0;	// L22533
        ap_int<17> v14204 = w7;	// L22534
        ap_int<17> v14205;
        ap_int<17> v14205_tmp = v14204;
        v14205_tmp[0] = 1;        v14205 = v14205_tmp;	// L22535
        w7 = v14205;	// L22536
        int32_t v14206 = sp_e[3];	// L22537
        int v14207 = v14206;	// L22538
        half v14208 = v14109[3][v14207];	// L22539
        uint16_t v14209;
        union { half from; uint16_t to;} _converter_v14208_to_v14209 = {};
        _converter_v14208_to_v14209.from = v14208;
        v14209 = _converter_v14208_to_v14209.to;	// L22540
        ap_int<17> v14210 = w7;	// L22541
        ap_int<17> v14211;
        ap_int<17> v14211_tmp = v14210;
        v14211_tmp(16, 1) = v14209;
        v14211 = v14211_tmp;	// L22542
        w7 = v14211;	// L22543
        ap_int<17> v14212 = w7;	// L22544
        bool v14213 = v14114.write_nb(v14212);
	// L22545
        if (v14213) {	// L22546
          int32_t v14214 = sp_e[3];	// L22547
          ap_int<33> v14215 = v14214;	// L22548
          ap_int<33> v14216 = v14215 + 1;	// L22549
          int32_t v14217 = v14216;	// L22550
          sp_e[3] = v14217;	// L22551
        }
      }
    }
  }
}

void drv_n_0(
  half v14218[4][374],
  int32_t v14219[4][374],
  hls::stream< ap_uint<17> >& v14220,
  hls::stream< ap_uint<17> >& v14221,
  hls::stream< ap_uint<17> >& v14222,
  hls::stream< ap_uint<17> >& v14223
) {	// L22558
  int32_t sp_n[4];	// L22569
  for (int v14225 = 0; v14225 < 4; v14225++) {	// L22570
    sp_n[v14225] = 0;	// L22570
  }
  l_S_t_0_t18: for (int t18 = 0; t18 < 374; t18++) {	// L22571
    int32_t v14227 = sp_n[0];	// L22572
    bool v14228 = v14227 < 374;	// L22573
    if (v14228) {	// L22574
      int32_t v14229 = sp_n[0];	// L22575
      int v14230 = v14229;	// L22576
      int32_t v14231 = v14219[0][v14230];	// L22577
      bool v14232 = v14231 == 0;	// L22578
      if (v14232) {	// L22579
        int32_t v14233 = sp_n[0];	// L22580
        ap_int<33> v14234 = v14233;	// L22581
        ap_int<33> v14235 = v14234 + 1;	// L22582
        int32_t v14236 = v14235;	// L22583
        sp_n[0] = v14236;	// L22584
      } else {
        ap_uint<17> w8;	// L22586
        w8 = 0;	// L22587
        ap_int<17> v14238 = w8;	// L22588
        ap_int<17> v14239;
        ap_int<17> v14239_tmp = v14238;
        v14239_tmp[0] = 1;        v14239 = v14239_tmp;	// L22589
        w8 = v14239;	// L22590
        int32_t v14240 = sp_n[0];	// L22591
        int v14241 = v14240;	// L22592
        half v14242 = v14218[0][v14241];	// L22593
        uint16_t v14243;
        union { half from; uint16_t to;} _converter_v14242_to_v14243 = {};
        _converter_v14242_to_v14243.from = v14242;
        v14243 = _converter_v14242_to_v14243.to;	// L22594
        ap_int<17> v14244 = w8;	// L22595
        ap_int<17> v14245;
        ap_int<17> v14245_tmp = v14244;
        v14245_tmp(16, 1) = v14243;
        v14245 = v14245_tmp;	// L22596
        w8 = v14245;	// L22597
        ap_int<17> v14246 = w8;	// L22598
        bool v14247 = v14220.write_nb(v14246);
	// L22599
        if (v14247) {	// L22600
          int32_t v14248 = sp_n[0];	// L22601
          ap_int<33> v14249 = v14248;	// L22602
          ap_int<33> v14250 = v14249 + 1;	// L22603
          int32_t v14251 = v14250;	// L22604
          sp_n[0] = v14251;	// L22605
        }
      }
    }
    int32_t v14252 = sp_n[1];	// L22609
    bool v14253 = v14252 < 374;	// L22610
    if (v14253) {	// L22611
      int32_t v14254 = sp_n[1];	// L22612
      int v14255 = v14254;	// L22613
      int32_t v14256 = v14219[1][v14255];	// L22614
      bool v14257 = v14256 == 0;	// L22615
      if (v14257) {	// L22616
        int32_t v14258 = sp_n[1];	// L22617
        ap_int<33> v14259 = v14258;	// L22618
        ap_int<33> v14260 = v14259 + 1;	// L22619
        int32_t v14261 = v14260;	// L22620
        sp_n[1] = v14261;	// L22621
      } else {
        ap_uint<17> w9;	// L22623
        w9 = 0;	// L22624
        ap_int<17> v14263 = w9;	// L22625
        ap_int<17> v14264;
        ap_int<17> v14264_tmp = v14263;
        v14264_tmp[0] = 1;        v14264 = v14264_tmp;	// L22626
        w9 = v14264;	// L22627
        int32_t v14265 = sp_n[1];	// L22628
        int v14266 = v14265;	// L22629
        half v14267 = v14218[1][v14266];	// L22630
        uint16_t v14268;
        union { half from; uint16_t to;} _converter_v14267_to_v14268 = {};
        _converter_v14267_to_v14268.from = v14267;
        v14268 = _converter_v14267_to_v14268.to;	// L22631
        ap_int<17> v14269 = w9;	// L22632
        ap_int<17> v14270;
        ap_int<17> v14270_tmp = v14269;
        v14270_tmp(16, 1) = v14268;
        v14270 = v14270_tmp;	// L22633
        w9 = v14270;	// L22634
        ap_int<17> v14271 = w9;	// L22635
        bool v14272 = v14221.write_nb(v14271);
	// L22636
        if (v14272) {	// L22637
          int32_t v14273 = sp_n[1];	// L22638
          ap_int<33> v14274 = v14273;	// L22639
          ap_int<33> v14275 = v14274 + 1;	// L22640
          int32_t v14276 = v14275;	// L22641
          sp_n[1] = v14276;	// L22642
        }
      }
    }
    int32_t v14277 = sp_n[2];	// L22646
    bool v14278 = v14277 < 374;	// L22647
    if (v14278) {	// L22648
      int32_t v14279 = sp_n[2];	// L22649
      int v14280 = v14279;	// L22650
      int32_t v14281 = v14219[2][v14280];	// L22651
      bool v14282 = v14281 == 0;	// L22652
      if (v14282) {	// L22653
        int32_t v14283 = sp_n[2];	// L22654
        ap_int<33> v14284 = v14283;	// L22655
        ap_int<33> v14285 = v14284 + 1;	// L22656
        int32_t v14286 = v14285;	// L22657
        sp_n[2] = v14286;	// L22658
      } else {
        ap_uint<17> w10;	// L22660
        w10 = 0;	// L22661
        ap_int<17> v14288 = w10;	// L22662
        ap_int<17> v14289;
        ap_int<17> v14289_tmp = v14288;
        v14289_tmp[0] = 1;        v14289 = v14289_tmp;	// L22663
        w10 = v14289;	// L22664
        int32_t v14290 = sp_n[2];	// L22665
        int v14291 = v14290;	// L22666
        half v14292 = v14218[2][v14291];	// L22667
        uint16_t v14293;
        union { half from; uint16_t to;} _converter_v14292_to_v14293 = {};
        _converter_v14292_to_v14293.from = v14292;
        v14293 = _converter_v14292_to_v14293.to;	// L22668
        ap_int<17> v14294 = w10;	// L22669
        ap_int<17> v14295;
        ap_int<17> v14295_tmp = v14294;
        v14295_tmp(16, 1) = v14293;
        v14295 = v14295_tmp;	// L22670
        w10 = v14295;	// L22671
        ap_int<17> v14296 = w10;	// L22672
        bool v14297 = v14222.write_nb(v14296);
	// L22673
        if (v14297) {	// L22674
          int32_t v14298 = sp_n[2];	// L22675
          ap_int<33> v14299 = v14298;	// L22676
          ap_int<33> v14300 = v14299 + 1;	// L22677
          int32_t v14301 = v14300;	// L22678
          sp_n[2] = v14301;	// L22679
        }
      }
    }
    int32_t v14302 = sp_n[3];	// L22683
    bool v14303 = v14302 < 374;	// L22684
    if (v14303) {	// L22685
      int32_t v14304 = sp_n[3];	// L22686
      int v14305 = v14304;	// L22687
      int32_t v14306 = v14219[3][v14305];	// L22688
      bool v14307 = v14306 == 0;	// L22689
      if (v14307) {	// L22690
        int32_t v14308 = sp_n[3];	// L22691
        ap_int<33> v14309 = v14308;	// L22692
        ap_int<33> v14310 = v14309 + 1;	// L22693
        int32_t v14311 = v14310;	// L22694
        sp_n[3] = v14311;	// L22695
      } else {
        ap_uint<17> w11;	// L22697
        w11 = 0;	// L22698
        ap_int<17> v14313 = w11;	// L22699
        ap_int<17> v14314;
        ap_int<17> v14314_tmp = v14313;
        v14314_tmp[0] = 1;        v14314 = v14314_tmp;	// L22700
        w11 = v14314;	// L22701
        int32_t v14315 = sp_n[3];	// L22702
        int v14316 = v14315;	// L22703
        half v14317 = v14218[3][v14316];	// L22704
        uint16_t v14318;
        union { half from; uint16_t to;} _converter_v14317_to_v14318 = {};
        _converter_v14317_to_v14318.from = v14317;
        v14318 = _converter_v14317_to_v14318.to;	// L22705
        ap_int<17> v14319 = w11;	// L22706
        ap_int<17> v14320;
        ap_int<17> v14320_tmp = v14319;
        v14320_tmp(16, 1) = v14318;
        v14320 = v14320_tmp;	// L22707
        w11 = v14320;	// L22708
        ap_int<17> v14321 = w11;	// L22709
        bool v14322 = v14223.write_nb(v14321);
	// L22710
        if (v14322) {	// L22711
          int32_t v14323 = sp_n[3];	// L22712
          ap_int<33> v14324 = v14323;	// L22713
          ap_int<33> v14325 = v14324 + 1;	// L22714
          int32_t v14326 = v14325;	// L22715
          sp_n[3] = v14326;	// L22716
        }
      }
    }
  }
}

void drv_s_0(
  half v14327[4][374],
  int32_t v14328[4][374],
  hls::stream< ap_uint<17> >& v14329,
  hls::stream< ap_uint<17> >& v14330,
  hls::stream< ap_uint<17> >& v14331,
  hls::stream< ap_uint<17> >& v14332
) {	// L22723
  int32_t sp_s[4];	// L22734
  for (int v14334 = 0; v14334 < 4; v14334++) {	// L22735
    sp_s[v14334] = 0;	// L22735
  }
  l_S_t_0_t19: for (int t19 = 0; t19 < 374; t19++) {	// L22736
    int32_t v14336 = sp_s[0];	// L22737
    bool v14337 = v14336 < 374;	// L22738
    if (v14337) {	// L22739
      int32_t v14338 = sp_s[0];	// L22740
      int v14339 = v14338;	// L22741
      int32_t v14340 = v14328[0][v14339];	// L22742
      bool v14341 = v14340 == 0;	// L22743
      if (v14341) {	// L22744
        int32_t v14342 = sp_s[0];	// L22745
        ap_int<33> v14343 = v14342;	// L22746
        ap_int<33> v14344 = v14343 + 1;	// L22747
        int32_t v14345 = v14344;	// L22748
        sp_s[0] = v14345;	// L22749
      } else {
        ap_uint<17> w12;	// L22751
        w12 = 0;	// L22752
        ap_int<17> v14347 = w12;	// L22753
        ap_int<17> v14348;
        ap_int<17> v14348_tmp = v14347;
        v14348_tmp[0] = 1;        v14348 = v14348_tmp;	// L22754
        w12 = v14348;	// L22755
        int32_t v14349 = sp_s[0];	// L22756
        int v14350 = v14349;	// L22757
        half v14351 = v14327[0][v14350];	// L22758
        uint16_t v14352;
        union { half from; uint16_t to;} _converter_v14351_to_v14352 = {};
        _converter_v14351_to_v14352.from = v14351;
        v14352 = _converter_v14351_to_v14352.to;	// L22759
        ap_int<17> v14353 = w12;	// L22760
        ap_int<17> v14354;
        ap_int<17> v14354_tmp = v14353;
        v14354_tmp(16, 1) = v14352;
        v14354 = v14354_tmp;	// L22761
        w12 = v14354;	// L22762
        ap_int<17> v14355 = w12;	// L22763
        bool v14356 = v14329.write_nb(v14355);
	// L22764
        if (v14356) {	// L22765
          int32_t v14357 = sp_s[0];	// L22766
          ap_int<33> v14358 = v14357;	// L22767
          ap_int<33> v14359 = v14358 + 1;	// L22768
          int32_t v14360 = v14359;	// L22769
          sp_s[0] = v14360;	// L22770
        }
      }
    }
    int32_t v14361 = sp_s[1];	// L22774
    bool v14362 = v14361 < 374;	// L22775
    if (v14362) {	// L22776
      int32_t v14363 = sp_s[1];	// L22777
      int v14364 = v14363;	// L22778
      int32_t v14365 = v14328[1][v14364];	// L22779
      bool v14366 = v14365 == 0;	// L22780
      if (v14366) {	// L22781
        int32_t v14367 = sp_s[1];	// L22782
        ap_int<33> v14368 = v14367;	// L22783
        ap_int<33> v14369 = v14368 + 1;	// L22784
        int32_t v14370 = v14369;	// L22785
        sp_s[1] = v14370;	// L22786
      } else {
        ap_uint<17> w13;	// L22788
        w13 = 0;	// L22789
        ap_int<17> v14372 = w13;	// L22790
        ap_int<17> v14373;
        ap_int<17> v14373_tmp = v14372;
        v14373_tmp[0] = 1;        v14373 = v14373_tmp;	// L22791
        w13 = v14373;	// L22792
        int32_t v14374 = sp_s[1];	// L22793
        int v14375 = v14374;	// L22794
        half v14376 = v14327[1][v14375];	// L22795
        uint16_t v14377;
        union { half from; uint16_t to;} _converter_v14376_to_v14377 = {};
        _converter_v14376_to_v14377.from = v14376;
        v14377 = _converter_v14376_to_v14377.to;	// L22796
        ap_int<17> v14378 = w13;	// L22797
        ap_int<17> v14379;
        ap_int<17> v14379_tmp = v14378;
        v14379_tmp(16, 1) = v14377;
        v14379 = v14379_tmp;	// L22798
        w13 = v14379;	// L22799
        ap_int<17> v14380 = w13;	// L22800
        bool v14381 = v14330.write_nb(v14380);
	// L22801
        if (v14381) {	// L22802
          int32_t v14382 = sp_s[1];	// L22803
          ap_int<33> v14383 = v14382;	// L22804
          ap_int<33> v14384 = v14383 + 1;	// L22805
          int32_t v14385 = v14384;	// L22806
          sp_s[1] = v14385;	// L22807
        }
      }
    }
    int32_t v14386 = sp_s[2];	// L22811
    bool v14387 = v14386 < 374;	// L22812
    if (v14387) {	// L22813
      int32_t v14388 = sp_s[2];	// L22814
      int v14389 = v14388;	// L22815
      int32_t v14390 = v14328[2][v14389];	// L22816
      bool v14391 = v14390 == 0;	// L22817
      if (v14391) {	// L22818
        int32_t v14392 = sp_s[2];	// L22819
        ap_int<33> v14393 = v14392;	// L22820
        ap_int<33> v14394 = v14393 + 1;	// L22821
        int32_t v14395 = v14394;	// L22822
        sp_s[2] = v14395;	// L22823
      } else {
        ap_uint<17> w14;	// L22825
        w14 = 0;	// L22826
        ap_int<17> v14397 = w14;	// L22827
        ap_int<17> v14398;
        ap_int<17> v14398_tmp = v14397;
        v14398_tmp[0] = 1;        v14398 = v14398_tmp;	// L22828
        w14 = v14398;	// L22829
        int32_t v14399 = sp_s[2];	// L22830
        int v14400 = v14399;	// L22831
        half v14401 = v14327[2][v14400];	// L22832
        uint16_t v14402;
        union { half from; uint16_t to;} _converter_v14401_to_v14402 = {};
        _converter_v14401_to_v14402.from = v14401;
        v14402 = _converter_v14401_to_v14402.to;	// L22833
        ap_int<17> v14403 = w14;	// L22834
        ap_int<17> v14404;
        ap_int<17> v14404_tmp = v14403;
        v14404_tmp(16, 1) = v14402;
        v14404 = v14404_tmp;	// L22835
        w14 = v14404;	// L22836
        ap_int<17> v14405 = w14;	// L22837
        bool v14406 = v14331.write_nb(v14405);
	// L22838
        if (v14406) {	// L22839
          int32_t v14407 = sp_s[2];	// L22840
          ap_int<33> v14408 = v14407;	// L22841
          ap_int<33> v14409 = v14408 + 1;	// L22842
          int32_t v14410 = v14409;	// L22843
          sp_s[2] = v14410;	// L22844
        }
      }
    }
    int32_t v14411 = sp_s[3];	// L22848
    bool v14412 = v14411 < 374;	// L22849
    if (v14412) {	// L22850
      int32_t v14413 = sp_s[3];	// L22851
      int v14414 = v14413;	// L22852
      int32_t v14415 = v14328[3][v14414];	// L22853
      bool v14416 = v14415 == 0;	// L22854
      if (v14416) {	// L22855
        int32_t v14417 = sp_s[3];	// L22856
        ap_int<33> v14418 = v14417;	// L22857
        ap_int<33> v14419 = v14418 + 1;	// L22858
        int32_t v14420 = v14419;	// L22859
        sp_s[3] = v14420;	// L22860
      } else {
        ap_uint<17> w15;	// L22862
        w15 = 0;	// L22863
        ap_int<17> v14422 = w15;	// L22864
        ap_int<17> v14423;
        ap_int<17> v14423_tmp = v14422;
        v14423_tmp[0] = 1;        v14423 = v14423_tmp;	// L22865
        w15 = v14423;	// L22866
        int32_t v14424 = sp_s[3];	// L22867
        int v14425 = v14424;	// L22868
        half v14426 = v14327[3][v14425];	// L22869
        uint16_t v14427;
        union { half from; uint16_t to;} _converter_v14426_to_v14427 = {};
        _converter_v14426_to_v14427.from = v14426;
        v14427 = _converter_v14426_to_v14427.to;	// L22870
        ap_int<17> v14428 = w15;	// L22871
        ap_int<17> v14429;
        ap_int<17> v14429_tmp = v14428;
        v14429_tmp(16, 1) = v14427;
        v14429 = v14429_tmp;	// L22872
        w15 = v14429;	// L22873
        ap_int<17> v14430 = w15;	// L22874
        bool v14431 = v14332.write_nb(v14430);
	// L22875
        if (v14431) {	// L22876
          int32_t v14432 = sp_s[3];	// L22877
          ap_int<33> v14433 = v14432;	// L22878
          ap_int<33> v14434 = v14433 + 1;	// L22879
          int32_t v14435 = v14434;	// L22880
          sp_s[3] = v14435;	// L22881
        }
      }
    }
  }
}

void col_w_0(
  half v14436[4][374],
  hls::stream< ap_uint<17> >& v14437,
  hls::stream< ap_uint<17> >& v14438,
  hls::stream< ap_uint<17> >& v14439,
  hls::stream< ap_uint<17> >& v14440
) {	// L22888
  int32_t k32[4];	// L22898
  for (int v14442 = 0; v14442 < 4; v14442++) {	// L22899
    k32[v14442] = 0;	// L22899
  }
  int32_t seen[4];	// L22900
  for (int v14444 = 0; v14444 < 4; v14444++) {	// L22901
    seen[v14444] = 0;	// L22901
  }
  l_S_t_0_t20: for (int t20 = 0; t20 < 374; t20++) {	// L22902
    ap_uint<17> v14446;
    bool v14447 = v14437.read_nb(v14446);
	// L22903
    ap_uint<17> cwv;	// L22904
    cwv = v14446;	// L22905
    bool cwk;	// L22906
    cwk = v14447;	// L22907
    bool v14450 = cwk;	// L22908
    int32_t v14451 = v14450;	// L22909
    bool v14452 = v14451 == 1;	// L22910
    if (v14452) {	// L22911
      int32_t v14453 = seen[0];	// L22912
      ap_int<33> v14454 = v14453;	// L22913
      ap_int<33> v14455 = v14454 + 1;	// L22914
      int32_t v14456 = v14455;	// L22915
      seen[0] = v14456;	// L22916
      int32_t v14457 = k32[0];	// L22917
      ap_int<33> v14458 = v14457;	// L22918
      bool v14459 = v14458 < 373;	// L22919
      if (v14459) {	// L22920
        ap_int<17> v14460 = cwv;	// L22921
        int16_t v14461;
        ap_int<17> v14461_tmp = v14460;
        v14461 = v14461_tmp(16, 1);	// L22922
        half v14462;
        union { uint16_t from; half to;} _converter_v14461_to_v14462 = {};
        _converter_v14461_to_v14462.from = v14461;
        v14462 = _converter_v14461_to_v14462.to;	// L22923
        int32_t v14463 = k32[0];	// L22924
        int v14464 = v14463;	// L22925
        v14436[0][v14464] = v14462;	// L22926
        int32_t v14465 = k32[0];	// L22927
        ap_int<33> v14466 = v14465;	// L22928
        ap_int<33> v14467 = v14466 + 1;	// L22929
        int32_t v14468 = v14467;	// L22930
        k32[0] = v14468;	// L22931
      }
    }
    ap_uint<17> v14469;
    bool v14470 = v14438.read_nb(v14469);
	// L22934
    ap_uint<17> cwv1;	// L22935
    cwv1 = v14469;	// L22936
    bool cwk1;	// L22937
    cwk1 = v14470;	// L22938
    bool v14473 = cwk1;	// L22939
    int32_t v14474 = v14473;	// L22940
    bool v14475 = v14474 == 1;	// L22941
    if (v14475) {	// L22942
      int32_t v14476 = seen[1];	// L22943
      ap_int<33> v14477 = v14476;	// L22944
      ap_int<33> v14478 = v14477 + 1;	// L22945
      int32_t v14479 = v14478;	// L22946
      seen[1] = v14479;	// L22947
      int32_t v14480 = k32[1];	// L22948
      ap_int<33> v14481 = v14480;	// L22949
      bool v14482 = v14481 < 373;	// L22950
      if (v14482) {	// L22951
        ap_int<17> v14483 = cwv1;	// L22952
        int16_t v14484;
        ap_int<17> v14484_tmp = v14483;
        v14484 = v14484_tmp(16, 1);	// L22953
        half v14485;
        union { uint16_t from; half to;} _converter_v14484_to_v14485 = {};
        _converter_v14484_to_v14485.from = v14484;
        v14485 = _converter_v14484_to_v14485.to;	// L22954
        int32_t v14486 = k32[1];	// L22955
        int v14487 = v14486;	// L22956
        v14436[1][v14487] = v14485;	// L22957
        int32_t v14488 = k32[1];	// L22958
        ap_int<33> v14489 = v14488;	// L22959
        ap_int<33> v14490 = v14489 + 1;	// L22960
        int32_t v14491 = v14490;	// L22961
        k32[1] = v14491;	// L22962
      }
    }
    ap_uint<17> v14492;
    bool v14493 = v14439.read_nb(v14492);
	// L22965
    ap_uint<17> cwv2;	// L22966
    cwv2 = v14492;	// L22967
    bool cwk2;	// L22968
    cwk2 = v14493;	// L22969
    bool v14496 = cwk2;	// L22970
    int32_t v14497 = v14496;	// L22971
    bool v14498 = v14497 == 1;	// L22972
    if (v14498) {	// L22973
      int32_t v14499 = seen[2];	// L22974
      ap_int<33> v14500 = v14499;	// L22975
      ap_int<33> v14501 = v14500 + 1;	// L22976
      int32_t v14502 = v14501;	// L22977
      seen[2] = v14502;	// L22978
      int32_t v14503 = k32[2];	// L22979
      ap_int<33> v14504 = v14503;	// L22980
      bool v14505 = v14504 < 373;	// L22981
      if (v14505) {	// L22982
        ap_int<17> v14506 = cwv2;	// L22983
        int16_t v14507;
        ap_int<17> v14507_tmp = v14506;
        v14507 = v14507_tmp(16, 1);	// L22984
        half v14508;
        union { uint16_t from; half to;} _converter_v14507_to_v14508 = {};
        _converter_v14507_to_v14508.from = v14507;
        v14508 = _converter_v14507_to_v14508.to;	// L22985
        int32_t v14509 = k32[2];	// L22986
        int v14510 = v14509;	// L22987
        v14436[2][v14510] = v14508;	// L22988
        int32_t v14511 = k32[2];	// L22989
        ap_int<33> v14512 = v14511;	// L22990
        ap_int<33> v14513 = v14512 + 1;	// L22991
        int32_t v14514 = v14513;	// L22992
        k32[2] = v14514;	// L22993
      }
    }
    ap_uint<17> v14515;
    bool v14516 = v14440.read_nb(v14515);
	// L22996
    ap_uint<17> cwv3;	// L22997
    cwv3 = v14515;	// L22998
    bool cwk3;	// L22999
    cwk3 = v14516;	// L23000
    bool v14519 = cwk3;	// L23001
    int32_t v14520 = v14519;	// L23002
    bool v14521 = v14520 == 1;	// L23003
    if (v14521) {	// L23004
      int32_t v14522 = seen[3];	// L23005
      ap_int<33> v14523 = v14522;	// L23006
      ap_int<33> v14524 = v14523 + 1;	// L23007
      int32_t v14525 = v14524;	// L23008
      seen[3] = v14525;	// L23009
      int32_t v14526 = k32[3];	// L23010
      ap_int<33> v14527 = v14526;	// L23011
      bool v14528 = v14527 < 373;	// L23012
      if (v14528) {	// L23013
        ap_int<17> v14529 = cwv3;	// L23014
        int16_t v14530;
        ap_int<17> v14530_tmp = v14529;
        v14530 = v14530_tmp(16, 1);	// L23015
        half v14531;
        union { uint16_t from; half to;} _converter_v14530_to_v14531 = {};
        _converter_v14530_to_v14531.from = v14530;
        v14531 = _converter_v14530_to_v14531.to;	// L23016
        int32_t v14532 = k32[3];	// L23017
        int v14533 = v14532;	// L23018
        v14436[3][v14533] = v14531;	// L23019
        int32_t v14534 = k32[3];	// L23020
        ap_int<33> v14535 = v14534;	// L23021
        ap_int<33> v14536 = v14535 + 1;	// L23022
        int32_t v14537 = v14536;	// L23023
        k32[3] = v14537;	// L23024
      }
    }
  }
  int32_t v14538 = seen[0];	// L23028
  half v14539 = v14538;	// L23029
  v14436[0][373] = v14539;	// L23030
  int32_t v14540 = seen[1];	// L23031
  half v14541 = v14540;	// L23032
  v14436[1][373] = v14541;	// L23033
  int32_t v14542 = seen[2];	// L23034
  half v14543 = v14542;	// L23035
  v14436[2][373] = v14543;	// L23036
  int32_t v14544 = seen[3];	// L23037
  half v14545 = v14544;	// L23038
  v14436[3][373] = v14545;	// L23039
}

void col_e_0(
  half v14546[4][374],
  hls::stream< ap_uint<17> >& v14547,
  hls::stream< ap_uint<17> >& v14548,
  hls::stream< ap_uint<17> >& v14549,
  hls::stream< ap_uint<17> >& v14550
) {	// L23042
  ap_uint<17> v14551 = v14547.read();	// L23045
  ap_uint<17> v;	// L23046
  v = v14551;	// L23047
  ap_int<17> v14553 = v;	// L23048
  int16_t v14554;
  ap_int<17> v14554_tmp = v14553;
  v14554 = v14554_tmp(16, 1);	// L23049
  half v14555;
  union { uint16_t from; half to;} _converter_v14554_to_v14555 = {};
  _converter_v14554_to_v14555.from = v14554;
  v14555 = _converter_v14554_to_v14555.to;	// L23050
  v14546[0][0] = v14555;	// L23051
  ap_uint<17> v14556 = v14548.read();	// L23052
  ap_uint<17> v1;	// L23053
  v1 = v14556;	// L23054
  ap_int<17> v14558 = v1;	// L23055
  int16_t v14559;
  ap_int<17> v14559_tmp = v14558;
  v14559 = v14559_tmp(16, 1);	// L23056
  half v14560;
  union { uint16_t from; half to;} _converter_v14559_to_v14560 = {};
  _converter_v14559_to_v14560.from = v14559;
  v14560 = _converter_v14559_to_v14560.to;	// L23057
  v14546[1][0] = v14560;	// L23058
  ap_uint<17> v14561 = v14549.read();	// L23059
  ap_uint<17> v2;	// L23060
  v2 = v14561;	// L23061
  ap_int<17> v14563 = v2;	// L23062
  int16_t v14564;
  ap_int<17> v14564_tmp = v14563;
  v14564 = v14564_tmp(16, 1);	// L23063
  half v14565;
  union { uint16_t from; half to;} _converter_v14564_to_v14565 = {};
  _converter_v14564_to_v14565.from = v14564;
  v14565 = _converter_v14564_to_v14565.to;	// L23064
  v14546[2][0] = v14565;	// L23065
  ap_uint<17> v14566 = v14550.read();	// L23066
  ap_uint<17> v3;	// L23067
  v3 = v14566;	// L23068
  ap_int<17> v14568 = v3;	// L23069
  int16_t v14569;
  ap_int<17> v14569_tmp = v14568;
  v14569 = v14569_tmp(16, 1);	// L23070
  half v14570;
  union { uint16_t from; half to;} _converter_v14569_to_v14570 = {};
  _converter_v14569_to_v14570.from = v14569;
  v14570 = _converter_v14569_to_v14570.to;	// L23071
  v14546[3][0] = v14570;	// L23072
}

void col_n_0(
  half v14571[4][374],
  hls::stream< ap_uint<17> >& v14572,
  hls::stream< ap_uint<17> >& v14573,
  hls::stream< ap_uint<17> >& v14574,
  hls::stream< ap_uint<17> >& v14575
) {	// L23075
  int32_t k33[4];	// L23085
  for (int v14577 = 0; v14577 < 4; v14577++) {	// L23086
    k33[v14577] = 0;	// L23086
  }
  int32_t seen1[4];	// L23087
  for (int v14579 = 0; v14579 < 4; v14579++) {	// L23088
    seen1[v14579] = 0;	// L23088
  }
  l_S_t_0_t21: for (int t21 = 0; t21 < 374; t21++) {	// L23089
    ap_uint<17> v14581;
    bool v14582 = v14572.read_nb(v14581);
	// L23090
    ap_uint<17> cnv;	// L23091
    cnv = v14581;	// L23092
    bool cnk;	// L23093
    cnk = v14582;	// L23094
    bool v14585 = cnk;	// L23095
    int32_t v14586 = v14585;	// L23096
    bool v14587 = v14586 == 1;	// L23097
    if (v14587) {	// L23098
      int32_t v14588 = seen1[0];	// L23099
      ap_int<33> v14589 = v14588;	// L23100
      ap_int<33> v14590 = v14589 + 1;	// L23101
      int32_t v14591 = v14590;	// L23102
      seen1[0] = v14591;	// L23103
      int32_t v14592 = k33[0];	// L23104
      ap_int<33> v14593 = v14592;	// L23105
      bool v14594 = v14593 < 373;	// L23106
      if (v14594) {	// L23107
        ap_int<17> v14595 = cnv;	// L23108
        int16_t v14596;
        ap_int<17> v14596_tmp = v14595;
        v14596 = v14596_tmp(16, 1);	// L23109
        half v14597;
        union { uint16_t from; half to;} _converter_v14596_to_v14597 = {};
        _converter_v14596_to_v14597.from = v14596;
        v14597 = _converter_v14596_to_v14597.to;	// L23110
        int32_t v14598 = k33[0];	// L23111
        int v14599 = v14598;	// L23112
        v14571[0][v14599] = v14597;	// L23113
        int32_t v14600 = k33[0];	// L23114
        ap_int<33> v14601 = v14600;	// L23115
        ap_int<33> v14602 = v14601 + 1;	// L23116
        int32_t v14603 = v14602;	// L23117
        k33[0] = v14603;	// L23118
      }
    }
    ap_uint<17> v14604;
    bool v14605 = v14573.read_nb(v14604);
	// L23121
    ap_uint<17> cnv1;	// L23122
    cnv1 = v14604;	// L23123
    bool cnk1;	// L23124
    cnk1 = v14605;	// L23125
    bool v14608 = cnk1;	// L23126
    int32_t v14609 = v14608;	// L23127
    bool v14610 = v14609 == 1;	// L23128
    if (v14610) {	// L23129
      int32_t v14611 = seen1[1];	// L23130
      ap_int<33> v14612 = v14611;	// L23131
      ap_int<33> v14613 = v14612 + 1;	// L23132
      int32_t v14614 = v14613;	// L23133
      seen1[1] = v14614;	// L23134
      int32_t v14615 = k33[1];	// L23135
      ap_int<33> v14616 = v14615;	// L23136
      bool v14617 = v14616 < 373;	// L23137
      if (v14617) {	// L23138
        ap_int<17> v14618 = cnv1;	// L23139
        int16_t v14619;
        ap_int<17> v14619_tmp = v14618;
        v14619 = v14619_tmp(16, 1);	// L23140
        half v14620;
        union { uint16_t from; half to;} _converter_v14619_to_v14620 = {};
        _converter_v14619_to_v14620.from = v14619;
        v14620 = _converter_v14619_to_v14620.to;	// L23141
        int32_t v14621 = k33[1];	// L23142
        int v14622 = v14621;	// L23143
        v14571[1][v14622] = v14620;	// L23144
        int32_t v14623 = k33[1];	// L23145
        ap_int<33> v14624 = v14623;	// L23146
        ap_int<33> v14625 = v14624 + 1;	// L23147
        int32_t v14626 = v14625;	// L23148
        k33[1] = v14626;	// L23149
      }
    }
    ap_uint<17> v14627;
    bool v14628 = v14574.read_nb(v14627);
	// L23152
    ap_uint<17> cnv2;	// L23153
    cnv2 = v14627;	// L23154
    bool cnk2;	// L23155
    cnk2 = v14628;	// L23156
    bool v14631 = cnk2;	// L23157
    int32_t v14632 = v14631;	// L23158
    bool v14633 = v14632 == 1;	// L23159
    if (v14633) {	// L23160
      int32_t v14634 = seen1[2];	// L23161
      ap_int<33> v14635 = v14634;	// L23162
      ap_int<33> v14636 = v14635 + 1;	// L23163
      int32_t v14637 = v14636;	// L23164
      seen1[2] = v14637;	// L23165
      int32_t v14638 = k33[2];	// L23166
      ap_int<33> v14639 = v14638;	// L23167
      bool v14640 = v14639 < 373;	// L23168
      if (v14640) {	// L23169
        ap_int<17> v14641 = cnv2;	// L23170
        int16_t v14642;
        ap_int<17> v14642_tmp = v14641;
        v14642 = v14642_tmp(16, 1);	// L23171
        half v14643;
        union { uint16_t from; half to;} _converter_v14642_to_v14643 = {};
        _converter_v14642_to_v14643.from = v14642;
        v14643 = _converter_v14642_to_v14643.to;	// L23172
        int32_t v14644 = k33[2];	// L23173
        int v14645 = v14644;	// L23174
        v14571[2][v14645] = v14643;	// L23175
        int32_t v14646 = k33[2];	// L23176
        ap_int<33> v14647 = v14646;	// L23177
        ap_int<33> v14648 = v14647 + 1;	// L23178
        int32_t v14649 = v14648;	// L23179
        k33[2] = v14649;	// L23180
      }
    }
    ap_uint<17> v14650;
    bool v14651 = v14575.read_nb(v14650);
	// L23183
    ap_uint<17> cnv3;	// L23184
    cnv3 = v14650;	// L23185
    bool cnk3;	// L23186
    cnk3 = v14651;	// L23187
    bool v14654 = cnk3;	// L23188
    int32_t v14655 = v14654;	// L23189
    bool v14656 = v14655 == 1;	// L23190
    if (v14656) {	// L23191
      int32_t v14657 = seen1[3];	// L23192
      ap_int<33> v14658 = v14657;	// L23193
      ap_int<33> v14659 = v14658 + 1;	// L23194
      int32_t v14660 = v14659;	// L23195
      seen1[3] = v14660;	// L23196
      int32_t v14661 = k33[3];	// L23197
      ap_int<33> v14662 = v14661;	// L23198
      bool v14663 = v14662 < 373;	// L23199
      if (v14663) {	// L23200
        ap_int<17> v14664 = cnv3;	// L23201
        int16_t v14665;
        ap_int<17> v14665_tmp = v14664;
        v14665 = v14665_tmp(16, 1);	// L23202
        half v14666;
        union { uint16_t from; half to;} _converter_v14665_to_v14666 = {};
        _converter_v14665_to_v14666.from = v14665;
        v14666 = _converter_v14665_to_v14666.to;	// L23203
        int32_t v14667 = k33[3];	// L23204
        int v14668 = v14667;	// L23205
        v14571[3][v14668] = v14666;	// L23206
        int32_t v14669 = k33[3];	// L23207
        ap_int<33> v14670 = v14669;	// L23208
        ap_int<33> v14671 = v14670 + 1;	// L23209
        int32_t v14672 = v14671;	// L23210
        k33[3] = v14672;	// L23211
      }
    }
  }
  int32_t v14673 = seen1[0];	// L23215
  half v14674 = v14673;	// L23216
  v14571[0][373] = v14674;	// L23217
  int32_t v14675 = seen1[1];	// L23218
  half v14676 = v14675;	// L23219
  v14571[1][373] = v14676;	// L23220
  int32_t v14677 = seen1[2];	// L23221
  half v14678 = v14677;	// L23222
  v14571[2][373] = v14678;	// L23223
  int32_t v14679 = seen1[3];	// L23224
  half v14680 = v14679;	// L23225
  v14571[3][373] = v14680;	// L23226
}

void col_s_0(
  half v14681[4][374],
  hls::stream< ap_uint<17> >& v14682,
  hls::stream< ap_uint<17> >& v14683,
  hls::stream< ap_uint<17> >& v14684,
  hls::stream< ap_uint<17> >& v14685
) {	// L23229
  ap_uint<17> v14686 = v14682.read();	// L23232
  ap_uint<17> v4;	// L23233
  v4 = v14686;	// L23234
  ap_int<17> v14688 = v4;	// L23235
  int16_t v14689;
  ap_int<17> v14689_tmp = v14688;
  v14689 = v14689_tmp(16, 1);	// L23236
  half v14690;
  union { uint16_t from; half to;} _converter_v14689_to_v14690 = {};
  _converter_v14689_to_v14690.from = v14689;
  v14690 = _converter_v14689_to_v14690.to;	// L23237
  v14681[0][0] = v14690;	// L23238
  ap_uint<17> v14691 = v14683.read();	// L23239
  ap_uint<17> v5;	// L23240
  v5 = v14691;	// L23241
  ap_int<17> v14693 = v5;	// L23242
  int16_t v14694;
  ap_int<17> v14694_tmp = v14693;
  v14694 = v14694_tmp(16, 1);	// L23243
  half v14695;
  union { uint16_t from; half to;} _converter_v14694_to_v14695 = {};
  _converter_v14694_to_v14695.from = v14694;
  v14695 = _converter_v14694_to_v14695.to;	// L23244
  v14681[1][0] = v14695;	// L23245
  ap_uint<17> v14696 = v14684.read();	// L23246
  ap_uint<17> v6;	// L23247
  v6 = v14696;	// L23248
  ap_int<17> v14698 = v6;	// L23249
  int16_t v14699;
  ap_int<17> v14699_tmp = v14698;
  v14699 = v14699_tmp(16, 1);	// L23250
  half v14700;
  union { uint16_t from; half to;} _converter_v14699_to_v14700 = {};
  _converter_v14699_to_v14700.from = v14699;
  v14700 = _converter_v14699_to_v14700.to;	// L23251
  v14681[2][0] = v14700;	// L23252
  ap_uint<17> v14701 = v14685.read();	// L23253
  ap_uint<17> v7;	// L23254
  v7 = v14701;	// L23255
  ap_int<17> v14703 = v7;	// L23256
  int16_t v14704;
  ap_int<17> v14704_tmp = v14703;
  v14704 = v14704_tmp(16, 1);	// L23257
  half v14705;
  union { uint16_t from; half to;} _converter_v14704_to_v14705 = {};
  _converter_v14704_to_v14705.from = v14704;
  v14705 = _converter_v14704_to_v14705.to;	// L23258
  v14681[3][0] = v14705;	// L23259
}

void rdrv_w_0(
  int32_t v14706[4][374],
  hls::stream< ap_uint<26> >& v14707,
  hls::stream< ap_uint<26> >& v14708,
  hls::stream< ap_uint<26> >& v14709,
  hls::stream< ap_uint<26> >& v14710
) {	// L23262
  int32_t sp[4];	// L23272
  for (int v14712 = 0; v14712 < 4; v14712++) {	// L23273
    sp[v14712] = 0;	// L23273
  }
  l_S_t_0_t22: for (int t22 = 0; t22 < 374; t22++) {	// L23274
    int32_t v14714 = sp[0];	// L23275
    bool v14715 = v14714 < 374;	// L23276
    if (v14715) {	// L23277
      ap_uint<26> cand;	// L23278
      cand = 0;	// L23279
      int32_t v14717 = sp[0];	// L23280
      int v14718 = v14717;	// L23281
      int32_t v14719 = v14706[0][v14718];	// L23282
      ap_uint<26> v14720 = v14719;	// L23283
      ap_int<26> v14721 = cand;	// L23284
      ap_int<26> v14722;
      ap_int<26> v14722_tmp = v14721;
      v14722_tmp(25, 0) = v14720;
      v14722 = v14722_tmp;	// L23285
      cand = v14722;	// L23286
      ap_int<26> v14723 = cand;	// L23287
      bool v14724;
      ap_int<26> v14724_tmp = v14723;
      v14724 = v14724_tmp[25];	// L23288
      int32_t v14725 = v14724;	// L23289
      bool v14726 = v14725 == 0;	// L23290
      if (v14726) {	// L23291
        int32_t v14727 = sp[0];	// L23292
        ap_int<33> v14728 = v14727;	// L23293
        ap_int<33> v14729 = v14728 + 1;	// L23294
        int32_t v14730 = v14729;	// L23295
        sp[0] = v14730;	// L23296
      } else {
        ap_int<26> v14731 = cand;	// L23298
        bool v14732 = v14707.write_nb(v14731);
	// L23299
        if (v14732) {	// L23300
          int32_t v14733 = sp[0];	// L23301
          ap_int<33> v14734 = v14733;	// L23302
          ap_int<33> v14735 = v14734 + 1;	// L23303
          int32_t v14736 = v14735;	// L23304
          sp[0] = v14736;	// L23305
        }
      }
    }
    int32_t v14737 = sp[1];	// L23309
    bool v14738 = v14737 < 374;	// L23310
    if (v14738) {	// L23311
      ap_uint<26> cand1;	// L23312
      cand1 = 0;	// L23313
      int32_t v14740 = sp[1];	// L23314
      int v14741 = v14740;	// L23315
      int32_t v14742 = v14706[1][v14741];	// L23316
      ap_uint<26> v14743 = v14742;	// L23317
      ap_int<26> v14744 = cand1;	// L23318
      ap_int<26> v14745;
      ap_int<26> v14745_tmp = v14744;
      v14745_tmp(25, 0) = v14743;
      v14745 = v14745_tmp;	// L23319
      cand1 = v14745;	// L23320
      ap_int<26> v14746 = cand1;	// L23321
      bool v14747;
      ap_int<26> v14747_tmp = v14746;
      v14747 = v14747_tmp[25];	// L23322
      int32_t v14748 = v14747;	// L23323
      bool v14749 = v14748 == 0;	// L23324
      if (v14749) {	// L23325
        int32_t v14750 = sp[1];	// L23326
        ap_int<33> v14751 = v14750;	// L23327
        ap_int<33> v14752 = v14751 + 1;	// L23328
        int32_t v14753 = v14752;	// L23329
        sp[1] = v14753;	// L23330
      } else {
        ap_int<26> v14754 = cand1;	// L23332
        bool v14755 = v14708.write_nb(v14754);
	// L23333
        if (v14755) {	// L23334
          int32_t v14756 = sp[1];	// L23335
          ap_int<33> v14757 = v14756;	// L23336
          ap_int<33> v14758 = v14757 + 1;	// L23337
          int32_t v14759 = v14758;	// L23338
          sp[1] = v14759;	// L23339
        }
      }
    }
    int32_t v14760 = sp[2];	// L23343
    bool v14761 = v14760 < 374;	// L23344
    if (v14761) {	// L23345
      ap_uint<26> cand2;	// L23346
      cand2 = 0;	// L23347
      int32_t v14763 = sp[2];	// L23348
      int v14764 = v14763;	// L23349
      int32_t v14765 = v14706[2][v14764];	// L23350
      ap_uint<26> v14766 = v14765;	// L23351
      ap_int<26> v14767 = cand2;	// L23352
      ap_int<26> v14768;
      ap_int<26> v14768_tmp = v14767;
      v14768_tmp(25, 0) = v14766;
      v14768 = v14768_tmp;	// L23353
      cand2 = v14768;	// L23354
      ap_int<26> v14769 = cand2;	// L23355
      bool v14770;
      ap_int<26> v14770_tmp = v14769;
      v14770 = v14770_tmp[25];	// L23356
      int32_t v14771 = v14770;	// L23357
      bool v14772 = v14771 == 0;	// L23358
      if (v14772) {	// L23359
        int32_t v14773 = sp[2];	// L23360
        ap_int<33> v14774 = v14773;	// L23361
        ap_int<33> v14775 = v14774 + 1;	// L23362
        int32_t v14776 = v14775;	// L23363
        sp[2] = v14776;	// L23364
      } else {
        ap_int<26> v14777 = cand2;	// L23366
        bool v14778 = v14709.write_nb(v14777);
	// L23367
        if (v14778) {	// L23368
          int32_t v14779 = sp[2];	// L23369
          ap_int<33> v14780 = v14779;	// L23370
          ap_int<33> v14781 = v14780 + 1;	// L23371
          int32_t v14782 = v14781;	// L23372
          sp[2] = v14782;	// L23373
        }
      }
    }
    int32_t v14783 = sp[3];	// L23377
    bool v14784 = v14783 < 374;	// L23378
    if (v14784) {	// L23379
      ap_uint<26> cand3;	// L23380
      cand3 = 0;	// L23381
      int32_t v14786 = sp[3];	// L23382
      int v14787 = v14786;	// L23383
      int32_t v14788 = v14706[3][v14787];	// L23384
      ap_uint<26> v14789 = v14788;	// L23385
      ap_int<26> v14790 = cand3;	// L23386
      ap_int<26> v14791;
      ap_int<26> v14791_tmp = v14790;
      v14791_tmp(25, 0) = v14789;
      v14791 = v14791_tmp;	// L23387
      cand3 = v14791;	// L23388
      ap_int<26> v14792 = cand3;	// L23389
      bool v14793;
      ap_int<26> v14793_tmp = v14792;
      v14793 = v14793_tmp[25];	// L23390
      int32_t v14794 = v14793;	// L23391
      bool v14795 = v14794 == 0;	// L23392
      if (v14795) {	// L23393
        int32_t v14796 = sp[3];	// L23394
        ap_int<33> v14797 = v14796;	// L23395
        ap_int<33> v14798 = v14797 + 1;	// L23396
        int32_t v14799 = v14798;	// L23397
        sp[3] = v14799;	// L23398
      } else {
        ap_int<26> v14800 = cand3;	// L23400
        bool v14801 = v14710.write_nb(v14800);
	// L23401
        if (v14801) {	// L23402
          int32_t v14802 = sp[3];	// L23403
          ap_int<33> v14803 = v14802;	// L23404
          ap_int<33> v14804 = v14803 + 1;	// L23405
          int32_t v14805 = v14804;	// L23406
          sp[3] = v14805;	// L23407
        }
      }
    }
  }
}

void rdrv_e_0(
  int32_t v14806[4][374],
  hls::stream< ap_uint<26> >& v14807,
  hls::stream< ap_uint<26> >& v14808,
  hls::stream< ap_uint<26> >& v14809,
  hls::stream< ap_uint<26> >& v14810
) {	// L23414
  int32_t sp1[4];	// L23424
  for (int v14812 = 0; v14812 < 4; v14812++) {	// L23425
    sp1[v14812] = 0;	// L23425
  }
  l_S_t_0_t23: for (int t23 = 0; t23 < 374; t23++) {	// L23426
    int32_t v14814 = sp1[0];	// L23427
    bool v14815 = v14814 < 374;	// L23428
    if (v14815) {	// L23429
      ap_uint<26> cand4;	// L23430
      cand4 = 0;	// L23431
      int32_t v14817 = sp1[0];	// L23432
      int v14818 = v14817;	// L23433
      int32_t v14819 = v14806[0][v14818];	// L23434
      ap_uint<26> v14820 = v14819;	// L23435
      ap_int<26> v14821 = cand4;	// L23436
      ap_int<26> v14822;
      ap_int<26> v14822_tmp = v14821;
      v14822_tmp(25, 0) = v14820;
      v14822 = v14822_tmp;	// L23437
      cand4 = v14822;	// L23438
      ap_int<26> v14823 = cand4;	// L23439
      bool v14824;
      ap_int<26> v14824_tmp = v14823;
      v14824 = v14824_tmp[25];	// L23440
      int32_t v14825 = v14824;	// L23441
      bool v14826 = v14825 == 0;	// L23442
      if (v14826) {	// L23443
        int32_t v14827 = sp1[0];	// L23444
        ap_int<33> v14828 = v14827;	// L23445
        ap_int<33> v14829 = v14828 + 1;	// L23446
        int32_t v14830 = v14829;	// L23447
        sp1[0] = v14830;	// L23448
      } else {
        ap_int<26> v14831 = cand4;	// L23450
        bool v14832 = v14807.write_nb(v14831);
	// L23451
        if (v14832) {	// L23452
          int32_t v14833 = sp1[0];	// L23453
          ap_int<33> v14834 = v14833;	// L23454
          ap_int<33> v14835 = v14834 + 1;	// L23455
          int32_t v14836 = v14835;	// L23456
          sp1[0] = v14836;	// L23457
        }
      }
    }
    int32_t v14837 = sp1[1];	// L23461
    bool v14838 = v14837 < 374;	// L23462
    if (v14838) {	// L23463
      ap_uint<26> cand5;	// L23464
      cand5 = 0;	// L23465
      int32_t v14840 = sp1[1];	// L23466
      int v14841 = v14840;	// L23467
      int32_t v14842 = v14806[1][v14841];	// L23468
      ap_uint<26> v14843 = v14842;	// L23469
      ap_int<26> v14844 = cand5;	// L23470
      ap_int<26> v14845;
      ap_int<26> v14845_tmp = v14844;
      v14845_tmp(25, 0) = v14843;
      v14845 = v14845_tmp;	// L23471
      cand5 = v14845;	// L23472
      ap_int<26> v14846 = cand5;	// L23473
      bool v14847;
      ap_int<26> v14847_tmp = v14846;
      v14847 = v14847_tmp[25];	// L23474
      int32_t v14848 = v14847;	// L23475
      bool v14849 = v14848 == 0;	// L23476
      if (v14849) {	// L23477
        int32_t v14850 = sp1[1];	// L23478
        ap_int<33> v14851 = v14850;	// L23479
        ap_int<33> v14852 = v14851 + 1;	// L23480
        int32_t v14853 = v14852;	// L23481
        sp1[1] = v14853;	// L23482
      } else {
        ap_int<26> v14854 = cand5;	// L23484
        bool v14855 = v14808.write_nb(v14854);
	// L23485
        if (v14855) {	// L23486
          int32_t v14856 = sp1[1];	// L23487
          ap_int<33> v14857 = v14856;	// L23488
          ap_int<33> v14858 = v14857 + 1;	// L23489
          int32_t v14859 = v14858;	// L23490
          sp1[1] = v14859;	// L23491
        }
      }
    }
    int32_t v14860 = sp1[2];	// L23495
    bool v14861 = v14860 < 374;	// L23496
    if (v14861) {	// L23497
      ap_uint<26> cand6;	// L23498
      cand6 = 0;	// L23499
      int32_t v14863 = sp1[2];	// L23500
      int v14864 = v14863;	// L23501
      int32_t v14865 = v14806[2][v14864];	// L23502
      ap_uint<26> v14866 = v14865;	// L23503
      ap_int<26> v14867 = cand6;	// L23504
      ap_int<26> v14868;
      ap_int<26> v14868_tmp = v14867;
      v14868_tmp(25, 0) = v14866;
      v14868 = v14868_tmp;	// L23505
      cand6 = v14868;	// L23506
      ap_int<26> v14869 = cand6;	// L23507
      bool v14870;
      ap_int<26> v14870_tmp = v14869;
      v14870 = v14870_tmp[25];	// L23508
      int32_t v14871 = v14870;	// L23509
      bool v14872 = v14871 == 0;	// L23510
      if (v14872) {	// L23511
        int32_t v14873 = sp1[2];	// L23512
        ap_int<33> v14874 = v14873;	// L23513
        ap_int<33> v14875 = v14874 + 1;	// L23514
        int32_t v14876 = v14875;	// L23515
        sp1[2] = v14876;	// L23516
      } else {
        ap_int<26> v14877 = cand6;	// L23518
        bool v14878 = v14809.write_nb(v14877);
	// L23519
        if (v14878) {	// L23520
          int32_t v14879 = sp1[2];	// L23521
          ap_int<33> v14880 = v14879;	// L23522
          ap_int<33> v14881 = v14880 + 1;	// L23523
          int32_t v14882 = v14881;	// L23524
          sp1[2] = v14882;	// L23525
        }
      }
    }
    int32_t v14883 = sp1[3];	// L23529
    bool v14884 = v14883 < 374;	// L23530
    if (v14884) {	// L23531
      ap_uint<26> cand7;	// L23532
      cand7 = 0;	// L23533
      int32_t v14886 = sp1[3];	// L23534
      int v14887 = v14886;	// L23535
      int32_t v14888 = v14806[3][v14887];	// L23536
      ap_uint<26> v14889 = v14888;	// L23537
      ap_int<26> v14890 = cand7;	// L23538
      ap_int<26> v14891;
      ap_int<26> v14891_tmp = v14890;
      v14891_tmp(25, 0) = v14889;
      v14891 = v14891_tmp;	// L23539
      cand7 = v14891;	// L23540
      ap_int<26> v14892 = cand7;	// L23541
      bool v14893;
      ap_int<26> v14893_tmp = v14892;
      v14893 = v14893_tmp[25];	// L23542
      int32_t v14894 = v14893;	// L23543
      bool v14895 = v14894 == 0;	// L23544
      if (v14895) {	// L23545
        int32_t v14896 = sp1[3];	// L23546
        ap_int<33> v14897 = v14896;	// L23547
        ap_int<33> v14898 = v14897 + 1;	// L23548
        int32_t v14899 = v14898;	// L23549
        sp1[3] = v14899;	// L23550
      } else {
        ap_int<26> v14900 = cand7;	// L23552
        bool v14901 = v14810.write_nb(v14900);
	// L23553
        if (v14901) {	// L23554
          int32_t v14902 = sp1[3];	// L23555
          ap_int<33> v14903 = v14902;	// L23556
          ap_int<33> v14904 = v14903 + 1;	// L23557
          int32_t v14905 = v14904;	// L23558
          sp1[3] = v14905;	// L23559
        }
      }
    }
  }
}

void rdrv_n_0(
  int32_t v14906[4][374],
  hls::stream< ap_uint<26> >& v14907,
  hls::stream< ap_uint<26> >& v14908,
  hls::stream< ap_uint<26> >& v14909,
  hls::stream< ap_uint<26> >& v14910
) {	// L23566
  int32_t sp2[4];	// L23576
  for (int v14912 = 0; v14912 < 4; v14912++) {	// L23577
    sp2[v14912] = 0;	// L23577
  }
  l_S_t_0_t24: for (int t24 = 0; t24 < 374; t24++) {	// L23578
    int32_t v14914 = sp2[0];	// L23579
    bool v14915 = v14914 < 374;	// L23580
    if (v14915) {	// L23581
      ap_uint<26> cand8;	// L23582
      cand8 = 0;	// L23583
      int32_t v14917 = sp2[0];	// L23584
      int v14918 = v14917;	// L23585
      int32_t v14919 = v14906[0][v14918];	// L23586
      ap_uint<26> v14920 = v14919;	// L23587
      ap_int<26> v14921 = cand8;	// L23588
      ap_int<26> v14922;
      ap_int<26> v14922_tmp = v14921;
      v14922_tmp(25, 0) = v14920;
      v14922 = v14922_tmp;	// L23589
      cand8 = v14922;	// L23590
      ap_int<26> v14923 = cand8;	// L23591
      bool v14924;
      ap_int<26> v14924_tmp = v14923;
      v14924 = v14924_tmp[25];	// L23592
      int32_t v14925 = v14924;	// L23593
      bool v14926 = v14925 == 0;	// L23594
      if (v14926) {	// L23595
        int32_t v14927 = sp2[0];	// L23596
        ap_int<33> v14928 = v14927;	// L23597
        ap_int<33> v14929 = v14928 + 1;	// L23598
        int32_t v14930 = v14929;	// L23599
        sp2[0] = v14930;	// L23600
      } else {
        ap_int<26> v14931 = cand8;	// L23602
        bool v14932 = v14907.write_nb(v14931);
	// L23603
        if (v14932) {	// L23604
          int32_t v14933 = sp2[0];	// L23605
          ap_int<33> v14934 = v14933;	// L23606
          ap_int<33> v14935 = v14934 + 1;	// L23607
          int32_t v14936 = v14935;	// L23608
          sp2[0] = v14936;	// L23609
        }
      }
    }
    int32_t v14937 = sp2[1];	// L23613
    bool v14938 = v14937 < 374;	// L23614
    if (v14938) {	// L23615
      ap_uint<26> cand9;	// L23616
      cand9 = 0;	// L23617
      int32_t v14940 = sp2[1];	// L23618
      int v14941 = v14940;	// L23619
      int32_t v14942 = v14906[1][v14941];	// L23620
      ap_uint<26> v14943 = v14942;	// L23621
      ap_int<26> v14944 = cand9;	// L23622
      ap_int<26> v14945;
      ap_int<26> v14945_tmp = v14944;
      v14945_tmp(25, 0) = v14943;
      v14945 = v14945_tmp;	// L23623
      cand9 = v14945;	// L23624
      ap_int<26> v14946 = cand9;	// L23625
      bool v14947;
      ap_int<26> v14947_tmp = v14946;
      v14947 = v14947_tmp[25];	// L23626
      int32_t v14948 = v14947;	// L23627
      bool v14949 = v14948 == 0;	// L23628
      if (v14949) {	// L23629
        int32_t v14950 = sp2[1];	// L23630
        ap_int<33> v14951 = v14950;	// L23631
        ap_int<33> v14952 = v14951 + 1;	// L23632
        int32_t v14953 = v14952;	// L23633
        sp2[1] = v14953;	// L23634
      } else {
        ap_int<26> v14954 = cand9;	// L23636
        bool v14955 = v14908.write_nb(v14954);
	// L23637
        if (v14955) {	// L23638
          int32_t v14956 = sp2[1];	// L23639
          ap_int<33> v14957 = v14956;	// L23640
          ap_int<33> v14958 = v14957 + 1;	// L23641
          int32_t v14959 = v14958;	// L23642
          sp2[1] = v14959;	// L23643
        }
      }
    }
    int32_t v14960 = sp2[2];	// L23647
    bool v14961 = v14960 < 374;	// L23648
    if (v14961) {	// L23649
      ap_uint<26> cand10;	// L23650
      cand10 = 0;	// L23651
      int32_t v14963 = sp2[2];	// L23652
      int v14964 = v14963;	// L23653
      int32_t v14965 = v14906[2][v14964];	// L23654
      ap_uint<26> v14966 = v14965;	// L23655
      ap_int<26> v14967 = cand10;	// L23656
      ap_int<26> v14968;
      ap_int<26> v14968_tmp = v14967;
      v14968_tmp(25, 0) = v14966;
      v14968 = v14968_tmp;	// L23657
      cand10 = v14968;	// L23658
      ap_int<26> v14969 = cand10;	// L23659
      bool v14970;
      ap_int<26> v14970_tmp = v14969;
      v14970 = v14970_tmp[25];	// L23660
      int32_t v14971 = v14970;	// L23661
      bool v14972 = v14971 == 0;	// L23662
      if (v14972) {	// L23663
        int32_t v14973 = sp2[2];	// L23664
        ap_int<33> v14974 = v14973;	// L23665
        ap_int<33> v14975 = v14974 + 1;	// L23666
        int32_t v14976 = v14975;	// L23667
        sp2[2] = v14976;	// L23668
      } else {
        ap_int<26> v14977 = cand10;	// L23670
        bool v14978 = v14909.write_nb(v14977);
	// L23671
        if (v14978) {	// L23672
          int32_t v14979 = sp2[2];	// L23673
          ap_int<33> v14980 = v14979;	// L23674
          ap_int<33> v14981 = v14980 + 1;	// L23675
          int32_t v14982 = v14981;	// L23676
          sp2[2] = v14982;	// L23677
        }
      }
    }
    int32_t v14983 = sp2[3];	// L23681
    bool v14984 = v14983 < 374;	// L23682
    if (v14984) {	// L23683
      ap_uint<26> cand11;	// L23684
      cand11 = 0;	// L23685
      int32_t v14986 = sp2[3];	// L23686
      int v14987 = v14986;	// L23687
      int32_t v14988 = v14906[3][v14987];	// L23688
      ap_uint<26> v14989 = v14988;	// L23689
      ap_int<26> v14990 = cand11;	// L23690
      ap_int<26> v14991;
      ap_int<26> v14991_tmp = v14990;
      v14991_tmp(25, 0) = v14989;
      v14991 = v14991_tmp;	// L23691
      cand11 = v14991;	// L23692
      ap_int<26> v14992 = cand11;	// L23693
      bool v14993;
      ap_int<26> v14993_tmp = v14992;
      v14993 = v14993_tmp[25];	// L23694
      int32_t v14994 = v14993;	// L23695
      bool v14995 = v14994 == 0;	// L23696
      if (v14995) {	// L23697
        int32_t v14996 = sp2[3];	// L23698
        ap_int<33> v14997 = v14996;	// L23699
        ap_int<33> v14998 = v14997 + 1;	// L23700
        int32_t v14999 = v14998;	// L23701
        sp2[3] = v14999;	// L23702
      } else {
        ap_int<26> v15000 = cand11;	// L23704
        bool v15001 = v14910.write_nb(v15000);
	// L23705
        if (v15001) {	// L23706
          int32_t v15002 = sp2[3];	// L23707
          ap_int<33> v15003 = v15002;	// L23708
          ap_int<33> v15004 = v15003 + 1;	// L23709
          int32_t v15005 = v15004;	// L23710
          sp2[3] = v15005;	// L23711
        }
      }
    }
  }
}

void rdrv_s_0(
  int32_t v15006[4][374],
  hls::stream< ap_uint<26> >& v15007,
  hls::stream< ap_uint<26> >& v15008,
  hls::stream< ap_uint<26> >& v15009,
  hls::stream< ap_uint<26> >& v15010
) {	// L23718
  int32_t sp3[4];	// L23728
  for (int v15012 = 0; v15012 < 4; v15012++) {	// L23729
    sp3[v15012] = 0;	// L23729
  }
  l_S_t_0_t25: for (int t25 = 0; t25 < 374; t25++) {	// L23730
    int32_t v15014 = sp3[0];	// L23731
    bool v15015 = v15014 < 374;	// L23732
    if (v15015) {	// L23733
      ap_uint<26> cand12;	// L23734
      cand12 = 0;	// L23735
      int32_t v15017 = sp3[0];	// L23736
      int v15018 = v15017;	// L23737
      int32_t v15019 = v15006[0][v15018];	// L23738
      ap_uint<26> v15020 = v15019;	// L23739
      ap_int<26> v15021 = cand12;	// L23740
      ap_int<26> v15022;
      ap_int<26> v15022_tmp = v15021;
      v15022_tmp(25, 0) = v15020;
      v15022 = v15022_tmp;	// L23741
      cand12 = v15022;	// L23742
      ap_int<26> v15023 = cand12;	// L23743
      bool v15024;
      ap_int<26> v15024_tmp = v15023;
      v15024 = v15024_tmp[25];	// L23744
      int32_t v15025 = v15024;	// L23745
      bool v15026 = v15025 == 0;	// L23746
      if (v15026) {	// L23747
        int32_t v15027 = sp3[0];	// L23748
        ap_int<33> v15028 = v15027;	// L23749
        ap_int<33> v15029 = v15028 + 1;	// L23750
        int32_t v15030 = v15029;	// L23751
        sp3[0] = v15030;	// L23752
      } else {
        ap_int<26> v15031 = cand12;	// L23754
        bool v15032 = v15007.write_nb(v15031);
	// L23755
        if (v15032) {	// L23756
          int32_t v15033 = sp3[0];	// L23757
          ap_int<33> v15034 = v15033;	// L23758
          ap_int<33> v15035 = v15034 + 1;	// L23759
          int32_t v15036 = v15035;	// L23760
          sp3[0] = v15036;	// L23761
        }
      }
    }
    int32_t v15037 = sp3[1];	// L23765
    bool v15038 = v15037 < 374;	// L23766
    if (v15038) {	// L23767
      ap_uint<26> cand13;	// L23768
      cand13 = 0;	// L23769
      int32_t v15040 = sp3[1];	// L23770
      int v15041 = v15040;	// L23771
      int32_t v15042 = v15006[1][v15041];	// L23772
      ap_uint<26> v15043 = v15042;	// L23773
      ap_int<26> v15044 = cand13;	// L23774
      ap_int<26> v15045;
      ap_int<26> v15045_tmp = v15044;
      v15045_tmp(25, 0) = v15043;
      v15045 = v15045_tmp;	// L23775
      cand13 = v15045;	// L23776
      ap_int<26> v15046 = cand13;	// L23777
      bool v15047;
      ap_int<26> v15047_tmp = v15046;
      v15047 = v15047_tmp[25];	// L23778
      int32_t v15048 = v15047;	// L23779
      bool v15049 = v15048 == 0;	// L23780
      if (v15049) {	// L23781
        int32_t v15050 = sp3[1];	// L23782
        ap_int<33> v15051 = v15050;	// L23783
        ap_int<33> v15052 = v15051 + 1;	// L23784
        int32_t v15053 = v15052;	// L23785
        sp3[1] = v15053;	// L23786
      } else {
        ap_int<26> v15054 = cand13;	// L23788
        bool v15055 = v15008.write_nb(v15054);
	// L23789
        if (v15055) {	// L23790
          int32_t v15056 = sp3[1];	// L23791
          ap_int<33> v15057 = v15056;	// L23792
          ap_int<33> v15058 = v15057 + 1;	// L23793
          int32_t v15059 = v15058;	// L23794
          sp3[1] = v15059;	// L23795
        }
      }
    }
    int32_t v15060 = sp3[2];	// L23799
    bool v15061 = v15060 < 374;	// L23800
    if (v15061) {	// L23801
      ap_uint<26> cand14;	// L23802
      cand14 = 0;	// L23803
      int32_t v15063 = sp3[2];	// L23804
      int v15064 = v15063;	// L23805
      int32_t v15065 = v15006[2][v15064];	// L23806
      ap_uint<26> v15066 = v15065;	// L23807
      ap_int<26> v15067 = cand14;	// L23808
      ap_int<26> v15068;
      ap_int<26> v15068_tmp = v15067;
      v15068_tmp(25, 0) = v15066;
      v15068 = v15068_tmp;	// L23809
      cand14 = v15068;	// L23810
      ap_int<26> v15069 = cand14;	// L23811
      bool v15070;
      ap_int<26> v15070_tmp = v15069;
      v15070 = v15070_tmp[25];	// L23812
      int32_t v15071 = v15070;	// L23813
      bool v15072 = v15071 == 0;	// L23814
      if (v15072) {	// L23815
        int32_t v15073 = sp3[2];	// L23816
        ap_int<33> v15074 = v15073;	// L23817
        ap_int<33> v15075 = v15074 + 1;	// L23818
        int32_t v15076 = v15075;	// L23819
        sp3[2] = v15076;	// L23820
      } else {
        ap_int<26> v15077 = cand14;	// L23822
        bool v15078 = v15009.write_nb(v15077);
	// L23823
        if (v15078) {	// L23824
          int32_t v15079 = sp3[2];	// L23825
          ap_int<33> v15080 = v15079;	// L23826
          ap_int<33> v15081 = v15080 + 1;	// L23827
          int32_t v15082 = v15081;	// L23828
          sp3[2] = v15082;	// L23829
        }
      }
    }
    int32_t v15083 = sp3[3];	// L23833
    bool v15084 = v15083 < 374;	// L23834
    if (v15084) {	// L23835
      ap_uint<26> cand15;	// L23836
      cand15 = 0;	// L23837
      int32_t v15086 = sp3[3];	// L23838
      int v15087 = v15086;	// L23839
      int32_t v15088 = v15006[3][v15087];	// L23840
      ap_uint<26> v15089 = v15088;	// L23841
      ap_int<26> v15090 = cand15;	// L23842
      ap_int<26> v15091;
      ap_int<26> v15091_tmp = v15090;
      v15091_tmp(25, 0) = v15089;
      v15091 = v15091_tmp;	// L23843
      cand15 = v15091;	// L23844
      ap_int<26> v15092 = cand15;	// L23845
      bool v15093;
      ap_int<26> v15093_tmp = v15092;
      v15093 = v15093_tmp[25];	// L23846
      int32_t v15094 = v15093;	// L23847
      bool v15095 = v15094 == 0;	// L23848
      if (v15095) {	// L23849
        int32_t v15096 = sp3[3];	// L23850
        ap_int<33> v15097 = v15096;	// L23851
        ap_int<33> v15098 = v15097 + 1;	// L23852
        int32_t v15099 = v15098;	// L23853
        sp3[3] = v15099;	// L23854
      } else {
        ap_int<26> v15100 = cand15;	// L23856
        bool v15101 = v15010.write_nb(v15100);
	// L23857
        if (v15101) {	// L23858
          int32_t v15102 = sp3[3];	// L23859
          ap_int<33> v15103 = v15102;	// L23860
          ap_int<33> v15104 = v15103 + 1;	// L23861
          int32_t v15105 = v15104;	// L23862
          sp3[3] = v15105;	// L23863
        }
      }
    }
  }
}

void rclc_w_0(
  int32_t v15106[4][374],
  hls::stream< ap_uint<26> >& v15107,
  hls::stream< ap_uint<26> >& v15108,
  hls::stream< ap_uint<26> >& v15109,
  hls::stream< ap_uint<26> >& v15110
) {	// L23870
  int32_t k34[4];	// L23881
  for (int v15112 = 0; v15112 < 4; v15112++) {	// L23882
    k34[v15112] = 0;	// L23882
  }
  int32_t seen2[4];	// L23883
  for (int v15114 = 0; v15114 < 4; v15114++) {	// L23884
    seen2[v15114] = 0;	// L23884
  }
  l_S_t_0_t26: for (int t26 = 0; t26 < 374; t26++) {	// L23885
    ap_uint<26> v15116;
    bool v15117 = v15107.read_nb(v15116);
	// L23886
    ap_uint<26> pw;	// L23887
    pw = v15116;	// L23888
    bool okp;	// L23889
    okp = v15117;	// L23890
    bool v15120 = okp;	// L23891
    ap_int<26> v15121 = pw;	// L23892
    bool v15122;
    ap_int<26> v15122_tmp = v15121;
    v15122 = v15122_tmp[25];	// L23893
    int32_t v15123 = v15122;	// L23894
    bool v15124 = v15123 == 1;	// L23895
    bool v15125 = v15120 & v15124;	// L23896
    if (v15125) {	// L23897
      int32_t v15126 = seen2[0];	// L23898
      ap_int<33> v15127 = v15126;	// L23899
      ap_int<33> v15128 = v15127 + 1;	// L23900
      int32_t v15129 = v15128;	// L23901
      seen2[0] = v15129;	// L23902
      int32_t v15130 = k34[0];	// L23903
      ap_int<33> v15131 = v15130;	// L23904
      bool v15132 = v15131 < 373;	// L23905
      if (v15132) {	// L23906
        ap_int<26> v15133 = pw;	// L23907
        int32_t v15134 = v15133;	// L23908
        int32_t v15135 = v15134 & 67108863;	// L23909
        int32_t v15136 = k34[0];	// L23910
        int v15137 = v15136;	// L23911
        v15106[0][v15137] = v15135;	// L23912
        int32_t v15138 = k34[0];	// L23913
        ap_int<33> v15139 = v15138;	// L23914
        ap_int<33> v15140 = v15139 + 1;	// L23915
        int32_t v15141 = v15140;	// L23916
        k34[0] = v15141;	// L23917
      }
    }
    ap_uint<26> v15142;
    bool v15143 = v15108.read_nb(v15142);
	// L23920
    ap_uint<26> pw1;	// L23921
    pw1 = v15142;	// L23922
    bool okp1;	// L23923
    okp1 = v15143;	// L23924
    bool v15146 = okp1;	// L23925
    ap_int<26> v15147 = pw1;	// L23926
    bool v15148;
    ap_int<26> v15148_tmp = v15147;
    v15148 = v15148_tmp[25];	// L23927
    int32_t v15149 = v15148;	// L23928
    bool v15150 = v15149 == 1;	// L23929
    bool v15151 = v15146 & v15150;	// L23930
    if (v15151) {	// L23931
      int32_t v15152 = seen2[1];	// L23932
      ap_int<33> v15153 = v15152;	// L23933
      ap_int<33> v15154 = v15153 + 1;	// L23934
      int32_t v15155 = v15154;	// L23935
      seen2[1] = v15155;	// L23936
      int32_t v15156 = k34[1];	// L23937
      ap_int<33> v15157 = v15156;	// L23938
      bool v15158 = v15157 < 373;	// L23939
      if (v15158) {	// L23940
        ap_int<26> v15159 = pw1;	// L23941
        int32_t v15160 = v15159;	// L23942
        int32_t v15161 = v15160 & 67108863;	// L23943
        int32_t v15162 = k34[1];	// L23944
        int v15163 = v15162;	// L23945
        v15106[1][v15163] = v15161;	// L23946
        int32_t v15164 = k34[1];	// L23947
        ap_int<33> v15165 = v15164;	// L23948
        ap_int<33> v15166 = v15165 + 1;	// L23949
        int32_t v15167 = v15166;	// L23950
        k34[1] = v15167;	// L23951
      }
    }
    ap_uint<26> v15168;
    bool v15169 = v15109.read_nb(v15168);
	// L23954
    ap_uint<26> pw2;	// L23955
    pw2 = v15168;	// L23956
    bool okp2;	// L23957
    okp2 = v15169;	// L23958
    bool v15172 = okp2;	// L23959
    ap_int<26> v15173 = pw2;	// L23960
    bool v15174;
    ap_int<26> v15174_tmp = v15173;
    v15174 = v15174_tmp[25];	// L23961
    int32_t v15175 = v15174;	// L23962
    bool v15176 = v15175 == 1;	// L23963
    bool v15177 = v15172 & v15176;	// L23964
    if (v15177) {	// L23965
      int32_t v15178 = seen2[2];	// L23966
      ap_int<33> v15179 = v15178;	// L23967
      ap_int<33> v15180 = v15179 + 1;	// L23968
      int32_t v15181 = v15180;	// L23969
      seen2[2] = v15181;	// L23970
      int32_t v15182 = k34[2];	// L23971
      ap_int<33> v15183 = v15182;	// L23972
      bool v15184 = v15183 < 373;	// L23973
      if (v15184) {	// L23974
        ap_int<26> v15185 = pw2;	// L23975
        int32_t v15186 = v15185;	// L23976
        int32_t v15187 = v15186 & 67108863;	// L23977
        int32_t v15188 = k34[2];	// L23978
        int v15189 = v15188;	// L23979
        v15106[2][v15189] = v15187;	// L23980
        int32_t v15190 = k34[2];	// L23981
        ap_int<33> v15191 = v15190;	// L23982
        ap_int<33> v15192 = v15191 + 1;	// L23983
        int32_t v15193 = v15192;	// L23984
        k34[2] = v15193;	// L23985
      }
    }
    ap_uint<26> v15194;
    bool v15195 = v15110.read_nb(v15194);
	// L23988
    ap_uint<26> pw3;	// L23989
    pw3 = v15194;	// L23990
    bool okp3;	// L23991
    okp3 = v15195;	// L23992
    bool v15198 = okp3;	// L23993
    ap_int<26> v15199 = pw3;	// L23994
    bool v15200;
    ap_int<26> v15200_tmp = v15199;
    v15200 = v15200_tmp[25];	// L23995
    int32_t v15201 = v15200;	// L23996
    bool v15202 = v15201 == 1;	// L23997
    bool v15203 = v15198 & v15202;	// L23998
    if (v15203) {	// L23999
      int32_t v15204 = seen2[3];	// L24000
      ap_int<33> v15205 = v15204;	// L24001
      ap_int<33> v15206 = v15205 + 1;	// L24002
      int32_t v15207 = v15206;	// L24003
      seen2[3] = v15207;	// L24004
      int32_t v15208 = k34[3];	// L24005
      ap_int<33> v15209 = v15208;	// L24006
      bool v15210 = v15209 < 373;	// L24007
      if (v15210) {	// L24008
        ap_int<26> v15211 = pw3;	// L24009
        int32_t v15212 = v15211;	// L24010
        int32_t v15213 = v15212 & 67108863;	// L24011
        int32_t v15214 = k34[3];	// L24012
        int v15215 = v15214;	// L24013
        v15106[3][v15215] = v15213;	// L24014
        int32_t v15216 = k34[3];	// L24015
        ap_int<33> v15217 = v15216;	// L24016
        ap_int<33> v15218 = v15217 + 1;	// L24017
        int32_t v15219 = v15218;	// L24018
        k34[3] = v15219;	// L24019
      }
    }
  }
  int32_t v15220 = seen2[0];	// L24023
  v15106[0][373] = v15220;	// L24024
  int32_t v15221 = seen2[1];	// L24025
  v15106[1][373] = v15221;	// L24026
  int32_t v15222 = seen2[2];	// L24027
  v15106[2][373] = v15222;	// L24028
  int32_t v15223 = seen2[3];	// L24029
  v15106[3][373] = v15223;	// L24030
}

void rclc_e_0(
  int32_t v15224[4][374],
  hls::stream< ap_uint<26> >& v15225,
  hls::stream< ap_uint<26> >& v15226,
  hls::stream< ap_uint<26> >& v15227,
  hls::stream< ap_uint<26> >& v15228
) {	// L24033
  int32_t k35[4];	// L24044
  for (int v15230 = 0; v15230 < 4; v15230++) {	// L24045
    k35[v15230] = 0;	// L24045
  }
  int32_t seen3[4];	// L24046
  for (int v15232 = 0; v15232 < 4; v15232++) {	// L24047
    seen3[v15232] = 0;	// L24047
  }
  l_S_t_0_t27: for (int t27 = 0; t27 < 374; t27++) {	// L24048
    ap_uint<26> v15234;
    bool v15235 = v15225.read_nb(v15234);
	// L24049
    ap_uint<26> pw4;	// L24050
    pw4 = v15234;	// L24051
    bool okp4;	// L24052
    okp4 = v15235;	// L24053
    bool v15238 = okp4;	// L24054
    ap_int<26> v15239 = pw4;	// L24055
    bool v15240;
    ap_int<26> v15240_tmp = v15239;
    v15240 = v15240_tmp[25];	// L24056
    int32_t v15241 = v15240;	// L24057
    bool v15242 = v15241 == 1;	// L24058
    bool v15243 = v15238 & v15242;	// L24059
    if (v15243) {	// L24060
      int32_t v15244 = seen3[0];	// L24061
      ap_int<33> v15245 = v15244;	// L24062
      ap_int<33> v15246 = v15245 + 1;	// L24063
      int32_t v15247 = v15246;	// L24064
      seen3[0] = v15247;	// L24065
      int32_t v15248 = k35[0];	// L24066
      ap_int<33> v15249 = v15248;	// L24067
      bool v15250 = v15249 < 373;	// L24068
      if (v15250) {	// L24069
        ap_int<26> v15251 = pw4;	// L24070
        int32_t v15252 = v15251;	// L24071
        int32_t v15253 = v15252 & 67108863;	// L24072
        int32_t v15254 = k35[0];	// L24073
        int v15255 = v15254;	// L24074
        v15224[0][v15255] = v15253;	// L24075
        int32_t v15256 = k35[0];	// L24076
        ap_int<33> v15257 = v15256;	// L24077
        ap_int<33> v15258 = v15257 + 1;	// L24078
        int32_t v15259 = v15258;	// L24079
        k35[0] = v15259;	// L24080
      }
    }
    ap_uint<26> v15260;
    bool v15261 = v15226.read_nb(v15260);
	// L24083
    ap_uint<26> pw5;	// L24084
    pw5 = v15260;	// L24085
    bool okp5;	// L24086
    okp5 = v15261;	// L24087
    bool v15264 = okp5;	// L24088
    ap_int<26> v15265 = pw5;	// L24089
    bool v15266;
    ap_int<26> v15266_tmp = v15265;
    v15266 = v15266_tmp[25];	// L24090
    int32_t v15267 = v15266;	// L24091
    bool v15268 = v15267 == 1;	// L24092
    bool v15269 = v15264 & v15268;	// L24093
    if (v15269) {	// L24094
      int32_t v15270 = seen3[1];	// L24095
      ap_int<33> v15271 = v15270;	// L24096
      ap_int<33> v15272 = v15271 + 1;	// L24097
      int32_t v15273 = v15272;	// L24098
      seen3[1] = v15273;	// L24099
      int32_t v15274 = k35[1];	// L24100
      ap_int<33> v15275 = v15274;	// L24101
      bool v15276 = v15275 < 373;	// L24102
      if (v15276) {	// L24103
        ap_int<26> v15277 = pw5;	// L24104
        int32_t v15278 = v15277;	// L24105
        int32_t v15279 = v15278 & 67108863;	// L24106
        int32_t v15280 = k35[1];	// L24107
        int v15281 = v15280;	// L24108
        v15224[1][v15281] = v15279;	// L24109
        int32_t v15282 = k35[1];	// L24110
        ap_int<33> v15283 = v15282;	// L24111
        ap_int<33> v15284 = v15283 + 1;	// L24112
        int32_t v15285 = v15284;	// L24113
        k35[1] = v15285;	// L24114
      }
    }
    ap_uint<26> v15286;
    bool v15287 = v15227.read_nb(v15286);
	// L24117
    ap_uint<26> pw6;	// L24118
    pw6 = v15286;	// L24119
    bool okp6;	// L24120
    okp6 = v15287;	// L24121
    bool v15290 = okp6;	// L24122
    ap_int<26> v15291 = pw6;	// L24123
    bool v15292;
    ap_int<26> v15292_tmp = v15291;
    v15292 = v15292_tmp[25];	// L24124
    int32_t v15293 = v15292;	// L24125
    bool v15294 = v15293 == 1;	// L24126
    bool v15295 = v15290 & v15294;	// L24127
    if (v15295) {	// L24128
      int32_t v15296 = seen3[2];	// L24129
      ap_int<33> v15297 = v15296;	// L24130
      ap_int<33> v15298 = v15297 + 1;	// L24131
      int32_t v15299 = v15298;	// L24132
      seen3[2] = v15299;	// L24133
      int32_t v15300 = k35[2];	// L24134
      ap_int<33> v15301 = v15300;	// L24135
      bool v15302 = v15301 < 373;	// L24136
      if (v15302) {	// L24137
        ap_int<26> v15303 = pw6;	// L24138
        int32_t v15304 = v15303;	// L24139
        int32_t v15305 = v15304 & 67108863;	// L24140
        int32_t v15306 = k35[2];	// L24141
        int v15307 = v15306;	// L24142
        v15224[2][v15307] = v15305;	// L24143
        int32_t v15308 = k35[2];	// L24144
        ap_int<33> v15309 = v15308;	// L24145
        ap_int<33> v15310 = v15309 + 1;	// L24146
        int32_t v15311 = v15310;	// L24147
        k35[2] = v15311;	// L24148
      }
    }
    ap_uint<26> v15312;
    bool v15313 = v15228.read_nb(v15312);
	// L24151
    ap_uint<26> pw7;	// L24152
    pw7 = v15312;	// L24153
    bool okp7;	// L24154
    okp7 = v15313;	// L24155
    bool v15316 = okp7;	// L24156
    ap_int<26> v15317 = pw7;	// L24157
    bool v15318;
    ap_int<26> v15318_tmp = v15317;
    v15318 = v15318_tmp[25];	// L24158
    int32_t v15319 = v15318;	// L24159
    bool v15320 = v15319 == 1;	// L24160
    bool v15321 = v15316 & v15320;	// L24161
    if (v15321) {	// L24162
      int32_t v15322 = seen3[3];	// L24163
      ap_int<33> v15323 = v15322;	// L24164
      ap_int<33> v15324 = v15323 + 1;	// L24165
      int32_t v15325 = v15324;	// L24166
      seen3[3] = v15325;	// L24167
      int32_t v15326 = k35[3];	// L24168
      ap_int<33> v15327 = v15326;	// L24169
      bool v15328 = v15327 < 373;	// L24170
      if (v15328) {	// L24171
        ap_int<26> v15329 = pw7;	// L24172
        int32_t v15330 = v15329;	// L24173
        int32_t v15331 = v15330 & 67108863;	// L24174
        int32_t v15332 = k35[3];	// L24175
        int v15333 = v15332;	// L24176
        v15224[3][v15333] = v15331;	// L24177
        int32_t v15334 = k35[3];	// L24178
        ap_int<33> v15335 = v15334;	// L24179
        ap_int<33> v15336 = v15335 + 1;	// L24180
        int32_t v15337 = v15336;	// L24181
        k35[3] = v15337;	// L24182
      }
    }
  }
  int32_t v15338 = seen3[0];	// L24186
  v15224[0][373] = v15338;	// L24187
  int32_t v15339 = seen3[1];	// L24188
  v15224[1][373] = v15339;	// L24189
  int32_t v15340 = seen3[2];	// L24190
  v15224[2][373] = v15340;	// L24191
  int32_t v15341 = seen3[3];	// L24192
  v15224[3][373] = v15341;	// L24193
}

void rclc_n_0(
  int32_t v15342[4][374],
  hls::stream< ap_uint<26> >& v15343,
  hls::stream< ap_uint<26> >& v15344,
  hls::stream< ap_uint<26> >& v15345,
  hls::stream< ap_uint<26> >& v15346
) {	// L24196
  int32_t k36[4];	// L24207
  for (int v15348 = 0; v15348 < 4; v15348++) {	// L24208
    k36[v15348] = 0;	// L24208
  }
  int32_t seen4[4];	// L24209
  for (int v15350 = 0; v15350 < 4; v15350++) {	// L24210
    seen4[v15350] = 0;	// L24210
  }
  l_S_t_0_t28: for (int t28 = 0; t28 < 374; t28++) {	// L24211
    ap_uint<26> v15352;
    bool v15353 = v15343.read_nb(v15352);
	// L24212
    ap_uint<26> pw8;	// L24213
    pw8 = v15352;	// L24214
    bool okp8;	// L24215
    okp8 = v15353;	// L24216
    bool v15356 = okp8;	// L24217
    ap_int<26> v15357 = pw8;	// L24218
    bool v15358;
    ap_int<26> v15358_tmp = v15357;
    v15358 = v15358_tmp[25];	// L24219
    int32_t v15359 = v15358;	// L24220
    bool v15360 = v15359 == 1;	// L24221
    bool v15361 = v15356 & v15360;	// L24222
    if (v15361) {	// L24223
      int32_t v15362 = seen4[0];	// L24224
      ap_int<33> v15363 = v15362;	// L24225
      ap_int<33> v15364 = v15363 + 1;	// L24226
      int32_t v15365 = v15364;	// L24227
      seen4[0] = v15365;	// L24228
      int32_t v15366 = k36[0];	// L24229
      ap_int<33> v15367 = v15366;	// L24230
      bool v15368 = v15367 < 373;	// L24231
      if (v15368) {	// L24232
        ap_int<26> v15369 = pw8;	// L24233
        int32_t v15370 = v15369;	// L24234
        int32_t v15371 = v15370 & 67108863;	// L24235
        int32_t v15372 = k36[0];	// L24236
        int v15373 = v15372;	// L24237
        v15342[0][v15373] = v15371;	// L24238
        int32_t v15374 = k36[0];	// L24239
        ap_int<33> v15375 = v15374;	// L24240
        ap_int<33> v15376 = v15375 + 1;	// L24241
        int32_t v15377 = v15376;	// L24242
        k36[0] = v15377;	// L24243
      }
    }
    ap_uint<26> v15378;
    bool v15379 = v15344.read_nb(v15378);
	// L24246
    ap_uint<26> pw9;	// L24247
    pw9 = v15378;	// L24248
    bool okp9;	// L24249
    okp9 = v15379;	// L24250
    bool v15382 = okp9;	// L24251
    ap_int<26> v15383 = pw9;	// L24252
    bool v15384;
    ap_int<26> v15384_tmp = v15383;
    v15384 = v15384_tmp[25];	// L24253
    int32_t v15385 = v15384;	// L24254
    bool v15386 = v15385 == 1;	// L24255
    bool v15387 = v15382 & v15386;	// L24256
    if (v15387) {	// L24257
      int32_t v15388 = seen4[1];	// L24258
      ap_int<33> v15389 = v15388;	// L24259
      ap_int<33> v15390 = v15389 + 1;	// L24260
      int32_t v15391 = v15390;	// L24261
      seen4[1] = v15391;	// L24262
      int32_t v15392 = k36[1];	// L24263
      ap_int<33> v15393 = v15392;	// L24264
      bool v15394 = v15393 < 373;	// L24265
      if (v15394) {	// L24266
        ap_int<26> v15395 = pw9;	// L24267
        int32_t v15396 = v15395;	// L24268
        int32_t v15397 = v15396 & 67108863;	// L24269
        int32_t v15398 = k36[1];	// L24270
        int v15399 = v15398;	// L24271
        v15342[1][v15399] = v15397;	// L24272
        int32_t v15400 = k36[1];	// L24273
        ap_int<33> v15401 = v15400;	// L24274
        ap_int<33> v15402 = v15401 + 1;	// L24275
        int32_t v15403 = v15402;	// L24276
        k36[1] = v15403;	// L24277
      }
    }
    ap_uint<26> v15404;
    bool v15405 = v15345.read_nb(v15404);
	// L24280
    ap_uint<26> pw10;	// L24281
    pw10 = v15404;	// L24282
    bool okp10;	// L24283
    okp10 = v15405;	// L24284
    bool v15408 = okp10;	// L24285
    ap_int<26> v15409 = pw10;	// L24286
    bool v15410;
    ap_int<26> v15410_tmp = v15409;
    v15410 = v15410_tmp[25];	// L24287
    int32_t v15411 = v15410;	// L24288
    bool v15412 = v15411 == 1;	// L24289
    bool v15413 = v15408 & v15412;	// L24290
    if (v15413) {	// L24291
      int32_t v15414 = seen4[2];	// L24292
      ap_int<33> v15415 = v15414;	// L24293
      ap_int<33> v15416 = v15415 + 1;	// L24294
      int32_t v15417 = v15416;	// L24295
      seen4[2] = v15417;	// L24296
      int32_t v15418 = k36[2];	// L24297
      ap_int<33> v15419 = v15418;	// L24298
      bool v15420 = v15419 < 373;	// L24299
      if (v15420) {	// L24300
        ap_int<26> v15421 = pw10;	// L24301
        int32_t v15422 = v15421;	// L24302
        int32_t v15423 = v15422 & 67108863;	// L24303
        int32_t v15424 = k36[2];	// L24304
        int v15425 = v15424;	// L24305
        v15342[2][v15425] = v15423;	// L24306
        int32_t v15426 = k36[2];	// L24307
        ap_int<33> v15427 = v15426;	// L24308
        ap_int<33> v15428 = v15427 + 1;	// L24309
        int32_t v15429 = v15428;	// L24310
        k36[2] = v15429;	// L24311
      }
    }
    ap_uint<26> v15430;
    bool v15431 = v15346.read_nb(v15430);
	// L24314
    ap_uint<26> pw11;	// L24315
    pw11 = v15430;	// L24316
    bool okp11;	// L24317
    okp11 = v15431;	// L24318
    bool v15434 = okp11;	// L24319
    ap_int<26> v15435 = pw11;	// L24320
    bool v15436;
    ap_int<26> v15436_tmp = v15435;
    v15436 = v15436_tmp[25];	// L24321
    int32_t v15437 = v15436;	// L24322
    bool v15438 = v15437 == 1;	// L24323
    bool v15439 = v15434 & v15438;	// L24324
    if (v15439) {	// L24325
      int32_t v15440 = seen4[3];	// L24326
      ap_int<33> v15441 = v15440;	// L24327
      ap_int<33> v15442 = v15441 + 1;	// L24328
      int32_t v15443 = v15442;	// L24329
      seen4[3] = v15443;	// L24330
      int32_t v15444 = k36[3];	// L24331
      ap_int<33> v15445 = v15444;	// L24332
      bool v15446 = v15445 < 373;	// L24333
      if (v15446) {	// L24334
        ap_int<26> v15447 = pw11;	// L24335
        int32_t v15448 = v15447;	// L24336
        int32_t v15449 = v15448 & 67108863;	// L24337
        int32_t v15450 = k36[3];	// L24338
        int v15451 = v15450;	// L24339
        v15342[3][v15451] = v15449;	// L24340
        int32_t v15452 = k36[3];	// L24341
        ap_int<33> v15453 = v15452;	// L24342
        ap_int<33> v15454 = v15453 + 1;	// L24343
        int32_t v15455 = v15454;	// L24344
        k36[3] = v15455;	// L24345
      }
    }
  }
  int32_t v15456 = seen4[0];	// L24349
  v15342[0][373] = v15456;	// L24350
  int32_t v15457 = seen4[1];	// L24351
  v15342[1][373] = v15457;	// L24352
  int32_t v15458 = seen4[2];	// L24353
  v15342[2][373] = v15458;	// L24354
  int32_t v15459 = seen4[3];	// L24355
  v15342[3][373] = v15459;	// L24356
}

void rclc_s_0(
  int32_t v15460[4][374],
  hls::stream< ap_uint<26> >& v15461,
  hls::stream< ap_uint<26> >& v15462,
  hls::stream< ap_uint<26> >& v15463,
  hls::stream< ap_uint<26> >& v15464
) {	// L24359
  int32_t k37[4];	// L24370
  for (int v15466 = 0; v15466 < 4; v15466++) {	// L24371
    k37[v15466] = 0;	// L24371
  }
  int32_t seen5[4];	// L24372
  for (int v15468 = 0; v15468 < 4; v15468++) {	// L24373
    seen5[v15468] = 0;	// L24373
  }
  l_S_t_0_t29: for (int t29 = 0; t29 < 374; t29++) {	// L24374
    ap_uint<26> v15470;
    bool v15471 = v15461.read_nb(v15470);
	// L24375
    ap_uint<26> pw12;	// L24376
    pw12 = v15470;	// L24377
    bool okp12;	// L24378
    okp12 = v15471;	// L24379
    bool v15474 = okp12;	// L24380
    ap_int<26> v15475 = pw12;	// L24381
    bool v15476;
    ap_int<26> v15476_tmp = v15475;
    v15476 = v15476_tmp[25];	// L24382
    int32_t v15477 = v15476;	// L24383
    bool v15478 = v15477 == 1;	// L24384
    bool v15479 = v15474 & v15478;	// L24385
    if (v15479) {	// L24386
      int32_t v15480 = seen5[0];	// L24387
      ap_int<33> v15481 = v15480;	// L24388
      ap_int<33> v15482 = v15481 + 1;	// L24389
      int32_t v15483 = v15482;	// L24390
      seen5[0] = v15483;	// L24391
      int32_t v15484 = k37[0];	// L24392
      ap_int<33> v15485 = v15484;	// L24393
      bool v15486 = v15485 < 373;	// L24394
      if (v15486) {	// L24395
        ap_int<26> v15487 = pw12;	// L24396
        int32_t v15488 = v15487;	// L24397
        int32_t v15489 = v15488 & 67108863;	// L24398
        int32_t v15490 = k37[0];	// L24399
        int v15491 = v15490;	// L24400
        v15460[0][v15491] = v15489;	// L24401
        int32_t v15492 = k37[0];	// L24402
        ap_int<33> v15493 = v15492;	// L24403
        ap_int<33> v15494 = v15493 + 1;	// L24404
        int32_t v15495 = v15494;	// L24405
        k37[0] = v15495;	// L24406
      }
    }
    ap_uint<26> v15496;
    bool v15497 = v15462.read_nb(v15496);
	// L24409
    ap_uint<26> pw13;	// L24410
    pw13 = v15496;	// L24411
    bool okp13;	// L24412
    okp13 = v15497;	// L24413
    bool v15500 = okp13;	// L24414
    ap_int<26> v15501 = pw13;	// L24415
    bool v15502;
    ap_int<26> v15502_tmp = v15501;
    v15502 = v15502_tmp[25];	// L24416
    int32_t v15503 = v15502;	// L24417
    bool v15504 = v15503 == 1;	// L24418
    bool v15505 = v15500 & v15504;	// L24419
    if (v15505) {	// L24420
      int32_t v15506 = seen5[1];	// L24421
      ap_int<33> v15507 = v15506;	// L24422
      ap_int<33> v15508 = v15507 + 1;	// L24423
      int32_t v15509 = v15508;	// L24424
      seen5[1] = v15509;	// L24425
      int32_t v15510 = k37[1];	// L24426
      ap_int<33> v15511 = v15510;	// L24427
      bool v15512 = v15511 < 373;	// L24428
      if (v15512) {	// L24429
        ap_int<26> v15513 = pw13;	// L24430
        int32_t v15514 = v15513;	// L24431
        int32_t v15515 = v15514 & 67108863;	// L24432
        int32_t v15516 = k37[1];	// L24433
        int v15517 = v15516;	// L24434
        v15460[1][v15517] = v15515;	// L24435
        int32_t v15518 = k37[1];	// L24436
        ap_int<33> v15519 = v15518;	// L24437
        ap_int<33> v15520 = v15519 + 1;	// L24438
        int32_t v15521 = v15520;	// L24439
        k37[1] = v15521;	// L24440
      }
    }
    ap_uint<26> v15522;
    bool v15523 = v15463.read_nb(v15522);
	// L24443
    ap_uint<26> pw14;	// L24444
    pw14 = v15522;	// L24445
    bool okp14;	// L24446
    okp14 = v15523;	// L24447
    bool v15526 = okp14;	// L24448
    ap_int<26> v15527 = pw14;	// L24449
    bool v15528;
    ap_int<26> v15528_tmp = v15527;
    v15528 = v15528_tmp[25];	// L24450
    int32_t v15529 = v15528;	// L24451
    bool v15530 = v15529 == 1;	// L24452
    bool v15531 = v15526 & v15530;	// L24453
    if (v15531) {	// L24454
      int32_t v15532 = seen5[2];	// L24455
      ap_int<33> v15533 = v15532;	// L24456
      ap_int<33> v15534 = v15533 + 1;	// L24457
      int32_t v15535 = v15534;	// L24458
      seen5[2] = v15535;	// L24459
      int32_t v15536 = k37[2];	// L24460
      ap_int<33> v15537 = v15536;	// L24461
      bool v15538 = v15537 < 373;	// L24462
      if (v15538) {	// L24463
        ap_int<26> v15539 = pw14;	// L24464
        int32_t v15540 = v15539;	// L24465
        int32_t v15541 = v15540 & 67108863;	// L24466
        int32_t v15542 = k37[2];	// L24467
        int v15543 = v15542;	// L24468
        v15460[2][v15543] = v15541;	// L24469
        int32_t v15544 = k37[2];	// L24470
        ap_int<33> v15545 = v15544;	// L24471
        ap_int<33> v15546 = v15545 + 1;	// L24472
        int32_t v15547 = v15546;	// L24473
        k37[2] = v15547;	// L24474
      }
    }
    ap_uint<26> v15548;
    bool v15549 = v15464.read_nb(v15548);
	// L24477
    ap_uint<26> pw15;	// L24478
    pw15 = v15548;	// L24479
    bool okp15;	// L24480
    okp15 = v15549;	// L24481
    bool v15552 = okp15;	// L24482
    ap_int<26> v15553 = pw15;	// L24483
    bool v15554;
    ap_int<26> v15554_tmp = v15553;
    v15554 = v15554_tmp[25];	// L24484
    int32_t v15555 = v15554;	// L24485
    bool v15556 = v15555 == 1;	// L24486
    bool v15557 = v15552 & v15556;	// L24487
    if (v15557) {	// L24488
      int32_t v15558 = seen5[3];	// L24489
      ap_int<33> v15559 = v15558;	// L24490
      ap_int<33> v15560 = v15559 + 1;	// L24491
      int32_t v15561 = v15560;	// L24492
      seen5[3] = v15561;	// L24493
      int32_t v15562 = k37[3];	// L24494
      ap_int<33> v15563 = v15562;	// L24495
      bool v15564 = v15563 < 373;	// L24496
      if (v15564) {	// L24497
        ap_int<26> v15565 = pw15;	// L24498
        int32_t v15566 = v15565;	// L24499
        int32_t v15567 = v15566 & 67108863;	// L24500
        int32_t v15568 = k37[3];	// L24501
        int v15569 = v15568;	// L24502
        v15460[3][v15569] = v15567;	// L24503
        int32_t v15570 = k37[3];	// L24504
        ap_int<33> v15571 = v15570;	// L24505
        ap_int<33> v15572 = v15571 + 1;	// L24506
        int32_t v15573 = v15572;	// L24507
        k37[3] = v15573;	// L24508
      }
    }
  }
  int32_t v15574 = seen5[0];	// L24512
  v15460[0][373] = v15574;	// L24513
  int32_t v15575 = seen5[1];	// L24514
  v15460[1][373] = v15575;	// L24515
  int32_t v15576 = seen5[2];	// L24516
  v15460[2][373] = v15576;	// L24517
  int32_t v15577 = seen5[3];	// L24518
  v15460[3][373] = v15577;	// L24519
}

/// This is top function.
void top(
  half v15578[4][374],
  int32_t v15579[4][374],
  half v15580[4][374],
  int32_t v15581[4][374],
  half v15582[4][374],
  int32_t v15583[4][374],
  half v15584[4][374],
  int32_t v15585[4][374],
  half v15586[4][374],
  half v15587[4][374],
  half v15588[4][374],
  half v15589[4][374],
  int32_t v15590[4][374],
  int32_t v15591[4][374],
  int32_t v15592[4][374],
  int32_t v15593[4][374],
  int32_t v15594[4][374],
  int32_t v15595[4][374],
  int32_t v15596[4][374],
  int32_t v15597[4][374]
) {	// L24522
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v15598;
  #pragma HLS stream variable=v15598 depth=8	// L24523
  hls::stream< ap_uint<17> > v15599;
  #pragma HLS stream variable=v15599 depth=8	// L24524
  hls::stream< ap_uint<17> > v15600;
  #pragma HLS stream variable=v15600 depth=8	// L24525
  hls::stream< ap_uint<17> > v15601;
  #pragma HLS stream variable=v15601 depth=8	// L24526
  hls::stream< ap_uint<17> > v15602;
  #pragma HLS stream variable=v15602 depth=8	// L24527
  hls::stream< ap_uint<17> > v15603;
  #pragma HLS stream variable=v15603 depth=8	// L24528
  hls::stream< ap_uint<17> > v15604;
  #pragma HLS stream variable=v15604 depth=8	// L24529
  hls::stream< ap_uint<17> > v15605;
  #pragma HLS stream variable=v15605 depth=8	// L24530
  hls::stream< ap_uint<17> > v15606;
  #pragma HLS stream variable=v15606 depth=8	// L24531
  hls::stream< ap_uint<17> > v15607;
  #pragma HLS stream variable=v15607 depth=8	// L24532
  hls::stream< ap_uint<17> > v15608;
  #pragma HLS stream variable=v15608 depth=8	// L24533
  hls::stream< ap_uint<17> > v15609;
  #pragma HLS stream variable=v15609 depth=8	// L24534
  hls::stream< ap_uint<17> > v15610;
  #pragma HLS stream variable=v15610 depth=8	// L24535
  hls::stream< ap_uint<17> > v15611;
  #pragma HLS stream variable=v15611 depth=8	// L24536
  hls::stream< ap_uint<17> > v15612;
  #pragma HLS stream variable=v15612 depth=8	// L24537
  hls::stream< ap_uint<17> > v15613;
  #pragma HLS stream variable=v15613 depth=8	// L24538
  hls::stream< ap_uint<17> > v15614;
  #pragma HLS stream variable=v15614 depth=8	// L24539
  hls::stream< ap_uint<17> > v15615;
  #pragma HLS stream variable=v15615 depth=8	// L24540
  hls::stream< ap_uint<17> > v15616;
  #pragma HLS stream variable=v15616 depth=8	// L24541
  hls::stream< ap_uint<17> > v15617;
  #pragma HLS stream variable=v15617 depth=8	// L24542
  hls::stream< ap_uint<17> > v15618;
  #pragma HLS stream variable=v15618 depth=8	// L24543
  hls::stream< ap_uint<17> > v15619;
  #pragma HLS stream variable=v15619 depth=8	// L24544
  hls::stream< ap_uint<17> > v15620;
  #pragma HLS stream variable=v15620 depth=8	// L24545
  hls::stream< ap_uint<17> > v15621;
  #pragma HLS stream variable=v15621 depth=8	// L24546
  hls::stream< ap_uint<17> > v15622;
  #pragma HLS stream variable=v15622 depth=8	// L24547
  hls::stream< ap_uint<17> > v15623;
  #pragma HLS stream variable=v15623 depth=8	// L24548
  hls::stream< ap_uint<17> > v15624;
  #pragma HLS stream variable=v15624 depth=8	// L24549
  hls::stream< ap_uint<17> > v15625;
  #pragma HLS stream variable=v15625 depth=8	// L24550
  hls::stream< ap_uint<17> > v15626;
  #pragma HLS stream variable=v15626 depth=8	// L24551
  hls::stream< ap_uint<17> > v15627;
  #pragma HLS stream variable=v15627 depth=8	// L24552
  hls::stream< ap_uint<17> > v15628;
  #pragma HLS stream variable=v15628 depth=8	// L24553
  hls::stream< ap_uint<17> > v15629;
  #pragma HLS stream variable=v15629 depth=8	// L24554
  hls::stream< ap_uint<17> > v15630;
  #pragma HLS stream variable=v15630 depth=8	// L24555
  hls::stream< ap_uint<17> > v15631;
  #pragma HLS stream variable=v15631 depth=8	// L24556
  hls::stream< ap_uint<17> > v15632;
  #pragma HLS stream variable=v15632 depth=8	// L24557
  hls::stream< ap_uint<17> > v15633;
  #pragma HLS stream variable=v15633 depth=8	// L24558
  hls::stream< ap_uint<17> > v15634;
  #pragma HLS stream variable=v15634 depth=8	// L24559
  hls::stream< ap_uint<17> > v15635;
  #pragma HLS stream variable=v15635 depth=8	// L24560
  hls::stream< ap_uint<17> > v15636;
  #pragma HLS stream variable=v15636 depth=8	// L24561
  hls::stream< ap_uint<17> > v15637;
  #pragma HLS stream variable=v15637 depth=8	// L24562
  hls::stream< ap_uint<17> > v15638;
  #pragma HLS stream variable=v15638 depth=8	// L24563
  hls::stream< ap_uint<17> > v15639;
  #pragma HLS stream variable=v15639 depth=8	// L24564
  hls::stream< ap_uint<17> > v15640;
  #pragma HLS stream variable=v15640 depth=8	// L24565
  hls::stream< ap_uint<17> > v15641;
  #pragma HLS stream variable=v15641 depth=8	// L24566
  hls::stream< ap_uint<17> > v15642;
  #pragma HLS stream variable=v15642 depth=8	// L24567
  hls::stream< ap_uint<17> > v15643;
  #pragma HLS stream variable=v15643 depth=8	// L24568
  hls::stream< ap_uint<17> > v15644;
  #pragma HLS stream variable=v15644 depth=8	// L24569
  hls::stream< ap_uint<17> > v15645;
  #pragma HLS stream variable=v15645 depth=8	// L24570
  hls::stream< ap_uint<17> > v15646;
  #pragma HLS stream variable=v15646 depth=8	// L24571
  hls::stream< ap_uint<17> > v15647;
  #pragma HLS stream variable=v15647 depth=8	// L24572
  hls::stream< ap_uint<17> > v15648;
  #pragma HLS stream variable=v15648 depth=8	// L24573
  hls::stream< ap_uint<17> > v15649;
  #pragma HLS stream variable=v15649 depth=8	// L24574
  hls::stream< ap_uint<17> > v15650;
  #pragma HLS stream variable=v15650 depth=8	// L24575
  hls::stream< ap_uint<17> > v15651;
  #pragma HLS stream variable=v15651 depth=8	// L24576
  hls::stream< ap_uint<17> > v15652;
  #pragma HLS stream variable=v15652 depth=8	// L24577
  hls::stream< ap_uint<17> > v15653;
  #pragma HLS stream variable=v15653 depth=8	// L24578
  hls::stream< ap_uint<17> > v15654;
  #pragma HLS stream variable=v15654 depth=8	// L24579
  hls::stream< ap_uint<17> > v15655;
  #pragma HLS stream variable=v15655 depth=8	// L24580
  hls::stream< ap_uint<17> > v15656;
  #pragma HLS stream variable=v15656 depth=8	// L24581
  hls::stream< ap_uint<17> > v15657;
  #pragma HLS stream variable=v15657 depth=8	// L24582
  hls::stream< ap_uint<17> > v15658;
  #pragma HLS stream variable=v15658 depth=8	// L24583
  hls::stream< ap_uint<17> > v15659;
  #pragma HLS stream variable=v15659 depth=8	// L24584
  hls::stream< ap_uint<17> > v15660;
  #pragma HLS stream variable=v15660 depth=8	// L24585
  hls::stream< ap_uint<17> > v15661;
  #pragma HLS stream variable=v15661 depth=8	// L24586
  hls::stream< ap_uint<17> > v15662;
  #pragma HLS stream variable=v15662 depth=8	// L24587
  hls::stream< ap_uint<17> > v15663;
  #pragma HLS stream variable=v15663 depth=8	// L24588
  hls::stream< ap_uint<17> > v15664;
  #pragma HLS stream variable=v15664 depth=8	// L24589
  hls::stream< ap_uint<17> > v15665;
  #pragma HLS stream variable=v15665 depth=8	// L24590
  hls::stream< ap_uint<17> > v15666;
  #pragma HLS stream variable=v15666 depth=8	// L24591
  hls::stream< ap_uint<17> > v15667;
  #pragma HLS stream variable=v15667 depth=8	// L24592
  hls::stream< ap_uint<17> > v15668;
  #pragma HLS stream variable=v15668 depth=8	// L24593
  hls::stream< ap_uint<17> > v15669;
  #pragma HLS stream variable=v15669 depth=8	// L24594
  hls::stream< ap_uint<17> > v15670;
  #pragma HLS stream variable=v15670 depth=8	// L24595
  hls::stream< ap_uint<17> > v15671;
  #pragma HLS stream variable=v15671 depth=8	// L24596
  hls::stream< ap_uint<17> > v15672;
  #pragma HLS stream variable=v15672 depth=8	// L24597
  hls::stream< ap_uint<17> > v15673;
  #pragma HLS stream variable=v15673 depth=8	// L24598
  hls::stream< ap_uint<17> > v15674;
  #pragma HLS stream variable=v15674 depth=8	// L24599
  hls::stream< ap_uint<17> > v15675;
  #pragma HLS stream variable=v15675 depth=8	// L24600
  hls::stream< ap_uint<17> > v15676;
  #pragma HLS stream variable=v15676 depth=8	// L24601
  hls::stream< ap_uint<17> > v15677;
  #pragma HLS stream variable=v15677 depth=8	// L24602
  hls::stream< ap_uint<26> > v15678;
  #pragma HLS stream variable=v15678 depth=8	// L24603
  hls::stream< ap_uint<26> > v15679;
  #pragma HLS stream variable=v15679 depth=8	// L24604
  hls::stream< ap_uint<26> > v15680;
  #pragma HLS stream variable=v15680 depth=8	// L24605
  hls::stream< ap_uint<26> > v15681;
  #pragma HLS stream variable=v15681 depth=8	// L24606
  hls::stream< ap_uint<26> > v15682;
  #pragma HLS stream variable=v15682 depth=8	// L24607
  hls::stream< ap_uint<26> > v15683;
  #pragma HLS stream variable=v15683 depth=8	// L24608
  hls::stream< ap_uint<26> > v15684;
  #pragma HLS stream variable=v15684 depth=8	// L24609
  hls::stream< ap_uint<26> > v15685;
  #pragma HLS stream variable=v15685 depth=8	// L24610
  hls::stream< ap_uint<26> > v15686;
  #pragma HLS stream variable=v15686 depth=8	// L24611
  hls::stream< ap_uint<26> > v15687;
  #pragma HLS stream variable=v15687 depth=8	// L24612
  hls::stream< ap_uint<26> > v15688;
  #pragma HLS stream variable=v15688 depth=8	// L24613
  hls::stream< ap_uint<26> > v15689;
  #pragma HLS stream variable=v15689 depth=8	// L24614
  hls::stream< ap_uint<26> > v15690;
  #pragma HLS stream variable=v15690 depth=8	// L24615
  hls::stream< ap_uint<26> > v15691;
  #pragma HLS stream variable=v15691 depth=8	// L24616
  hls::stream< ap_uint<26> > v15692;
  #pragma HLS stream variable=v15692 depth=8	// L24617
  hls::stream< ap_uint<26> > v15693;
  #pragma HLS stream variable=v15693 depth=8	// L24618
  hls::stream< ap_uint<26> > v15694;
  #pragma HLS stream variable=v15694 depth=8	// L24619
  hls::stream< ap_uint<26> > v15695;
  #pragma HLS stream variable=v15695 depth=8	// L24620
  hls::stream< ap_uint<26> > v15696;
  #pragma HLS stream variable=v15696 depth=8	// L24621
  hls::stream< ap_uint<26> > v15697;
  #pragma HLS stream variable=v15697 depth=8	// L24622
  hls::stream< ap_uint<26> > v15698;
  #pragma HLS stream variable=v15698 depth=8	// L24623
  hls::stream< ap_uint<26> > v15699;
  #pragma HLS stream variable=v15699 depth=8	// L24624
  hls::stream< ap_uint<26> > v15700;
  #pragma HLS stream variable=v15700 depth=8	// L24625
  hls::stream< ap_uint<26> > v15701;
  #pragma HLS stream variable=v15701 depth=8	// L24626
  hls::stream< ap_uint<26> > v15702;
  #pragma HLS stream variable=v15702 depth=8	// L24627
  hls::stream< ap_uint<26> > v15703;
  #pragma HLS stream variable=v15703 depth=8	// L24628
  hls::stream< ap_uint<26> > v15704;
  #pragma HLS stream variable=v15704 depth=8	// L24629
  hls::stream< ap_uint<26> > v15705;
  #pragma HLS stream variable=v15705 depth=8	// L24630
  hls::stream< ap_uint<26> > v15706;
  #pragma HLS stream variable=v15706 depth=8	// L24631
  hls::stream< ap_uint<26> > v15707;
  #pragma HLS stream variable=v15707 depth=8	// L24632
  hls::stream< ap_uint<26> > v15708;
  #pragma HLS stream variable=v15708 depth=8	// L24633
  hls::stream< ap_uint<26> > v15709;
  #pragma HLS stream variable=v15709 depth=8	// L24634
  hls::stream< ap_uint<26> > v15710;
  #pragma HLS stream variable=v15710 depth=8	// L24635
  hls::stream< ap_uint<26> > v15711;
  #pragma HLS stream variable=v15711 depth=8	// L24636
  hls::stream< ap_uint<26> > v15712;
  #pragma HLS stream variable=v15712 depth=8	// L24637
  hls::stream< ap_uint<26> > v15713;
  #pragma HLS stream variable=v15713 depth=8	// L24638
  hls::stream< ap_uint<26> > v15714;
  #pragma HLS stream variable=v15714 depth=8	// L24639
  hls::stream< ap_uint<26> > v15715;
  #pragma HLS stream variable=v15715 depth=8	// L24640
  hls::stream< ap_uint<26> > v15716;
  #pragma HLS stream variable=v15716 depth=8	// L24641
  hls::stream< ap_uint<26> > v15717;
  #pragma HLS stream variable=v15717 depth=8	// L24642
  hls::stream< ap_uint<26> > v15718;
  #pragma HLS stream variable=v15718 depth=8	// L24643
  hls::stream< ap_uint<26> > v15719;
  #pragma HLS stream variable=v15719 depth=8	// L24644
  hls::stream< ap_uint<26> > v15720;
  #pragma HLS stream variable=v15720 depth=8	// L24645
  hls::stream< ap_uint<26> > v15721;
  #pragma HLS stream variable=v15721 depth=8	// L24646
  hls::stream< ap_uint<26> > v15722;
  #pragma HLS stream variable=v15722 depth=8	// L24647
  hls::stream< ap_uint<26> > v15723;
  #pragma HLS stream variable=v15723 depth=8	// L24648
  hls::stream< ap_uint<26> > v15724;
  #pragma HLS stream variable=v15724 depth=8	// L24649
  hls::stream< ap_uint<26> > v15725;
  #pragma HLS stream variable=v15725 depth=8	// L24650
  hls::stream< ap_uint<26> > v15726;
  #pragma HLS stream variable=v15726 depth=8	// L24651
  hls::stream< ap_uint<26> > v15727;
  #pragma HLS stream variable=v15727 depth=8	// L24652
  hls::stream< ap_uint<26> > v15728;
  #pragma HLS stream variable=v15728 depth=8	// L24653
  hls::stream< ap_uint<26> > v15729;
  #pragma HLS stream variable=v15729 depth=8	// L24654
  hls::stream< ap_uint<26> > v15730;
  #pragma HLS stream variable=v15730 depth=8	// L24655
  hls::stream< ap_uint<26> > v15731;
  #pragma HLS stream variable=v15731 depth=8	// L24656
  hls::stream< ap_uint<26> > v15732;
  #pragma HLS stream variable=v15732 depth=8	// L24657
  hls::stream< ap_uint<26> > v15733;
  #pragma HLS stream variable=v15733 depth=8	// L24658
  hls::stream< ap_uint<26> > v15734;
  #pragma HLS stream variable=v15734 depth=8	// L24659
  hls::stream< ap_uint<26> > v15735;
  #pragma HLS stream variable=v15735 depth=8	// L24660
  hls::stream< ap_uint<26> > v15736;
  #pragma HLS stream variable=v15736 depth=8	// L24661
  hls::stream< ap_uint<26> > v15737;
  #pragma HLS stream variable=v15737 depth=8	// L24662
  hls::stream< ap_uint<26> > v15738;
  #pragma HLS stream variable=v15738 depth=8	// L24663
  hls::stream< ap_uint<26> > v15739;
  #pragma HLS stream variable=v15739 depth=8	// L24664
  hls::stream< ap_uint<26> > v15740;
  #pragma HLS stream variable=v15740 depth=8	// L24665
  hls::stream< ap_uint<26> > v15741;
  #pragma HLS stream variable=v15741 depth=8	// L24666
  hls::stream< ap_uint<26> > v15742;
  #pragma HLS stream variable=v15742 depth=8	// L24667
  hls::stream< ap_uint<26> > v15743;
  #pragma HLS stream variable=v15743 depth=8	// L24668
  hls::stream< ap_uint<26> > v15744;
  #pragma HLS stream variable=v15744 depth=8	// L24669
  hls::stream< ap_uint<26> > v15745;
  #pragma HLS stream variable=v15745 depth=8	// L24670
  hls::stream< ap_uint<26> > v15746;
  #pragma HLS stream variable=v15746 depth=8	// L24671
  hls::stream< ap_uint<26> > v15747;
  #pragma HLS stream variable=v15747 depth=8	// L24672
  hls::stream< ap_uint<26> > v15748;
  #pragma HLS stream variable=v15748 depth=8	// L24673
  hls::stream< ap_uint<26> > v15749;
  #pragma HLS stream variable=v15749 depth=8	// L24674
  hls::stream< ap_uint<26> > v15750;
  #pragma HLS stream variable=v15750 depth=8	// L24675
  hls::stream< ap_uint<26> > v15751;
  #pragma HLS stream variable=v15751 depth=8	// L24676
  hls::stream< ap_uint<26> > v15752;
  #pragma HLS stream variable=v15752 depth=8	// L24677
  hls::stream< ap_uint<26> > v15753;
  #pragma HLS stream variable=v15753 depth=8	// L24678
  hls::stream< ap_uint<26> > v15754;
  #pragma HLS stream variable=v15754 depth=8	// L24679
  hls::stream< ap_uint<26> > v15755;
  #pragma HLS stream variable=v15755 depth=8	// L24680
  hls::stream< ap_uint<26> > v15756;
  #pragma HLS stream variable=v15756 depth=8	// L24681
  hls::stream< ap_uint<26> > v15757;
  #pragma HLS stream variable=v15757 depth=8	// L24682
  node_0_0(v15678, v15699, v15718, v15742, v15679, v15698, v15722, v15738, v15638, v15662, v15598, v15619, v15599, v15618, v15642, v15658);	// L24683
  node_0_1(v15679, v15700, v15719, v15743, v15680, v15699, v15723, v15739, v15639, v15663, v15599, v15620, v15600, v15619, v15643, v15659);	// L24684
  node_0_2(v15680, v15701, v15720, v15744, v15681, v15700, v15724, v15740, v15640, v15664, v15600, v15621, v15601, v15620, v15644, v15660);	// L24685
  node_0_3(v15681, v15702, v15721, v15745, v15682, v15701, v15725, v15741, v15641, v15665, v15601, v15622, v15602, v15621, v15645, v15661);	// L24686
  node_1_0(v15683, v15704, v15722, v15746, v15684, v15703, v15726, v15742, v15642, v15666, v15603, v15624, v15604, v15623, v15646, v15662);	// L24687
  node_1_1(v15684, v15705, v15723, v15747, v15685, v15704, v15727, v15743, v15643, v15667, v15604, v15625, v15605, v15624, v15647, v15663);	// L24688
  node_1_2(v15685, v15706, v15724, v15748, v15686, v15705, v15728, v15744, v15644, v15668, v15605, v15626, v15606, v15625, v15648, v15664);	// L24689
  node_1_3(v15686, v15707, v15725, v15749, v15687, v15706, v15729, v15745, v15645, v15669, v15606, v15627, v15607, v15626, v15649, v15665);	// L24690
  node_2_0(v15688, v15709, v15726, v15750, v15689, v15708, v15730, v15746, v15646, v15670, v15608, v15629, v15609, v15628, v15650, v15666);	// L24691
  node_2_1(v15689, v15710, v15727, v15751, v15690, v15709, v15731, v15747, v15647, v15671, v15609, v15630, v15610, v15629, v15651, v15667);	// L24692
  node_2_2(v15690, v15711, v15728, v15752, v15691, v15710, v15732, v15748, v15648, v15672, v15610, v15631, v15611, v15630, v15652, v15668);	// L24693
  node_2_3(v15691, v15712, v15729, v15753, v15692, v15711, v15733, v15749, v15649, v15673, v15611, v15632, v15612, v15631, v15653, v15669);	// L24694
  node_3_0(v15693, v15714, v15730, v15754, v15694, v15713, v15734, v15750, v15650, v15674, v15613, v15634, v15614, v15633, v15654, v15670);	// L24695
  node_3_1(v15694, v15715, v15731, v15755, v15695, v15714, v15735, v15751, v15651, v15675, v15614, v15635, v15615, v15634, v15655, v15671);	// L24696
  node_3_2(v15695, v15716, v15732, v15756, v15696, v15715, v15736, v15752, v15652, v15676, v15615, v15636, v15616, v15635, v15656, v15672);	// L24697
  node_3_3(v15696, v15717, v15733, v15757, v15697, v15716, v15737, v15753, v15653, v15677, v15616, v15637, v15617, v15636, v15657, v15673);	// L24698
  drv_w_0(v15578, v15579, v15598, v15603, v15608, v15613);	// L24699
  drv_e_0(v15580, v15581, v15622, v15627, v15632, v15637);	// L24700
  drv_n_0(v15582, v15583, v15638, v15639, v15640, v15641);	// L24701
  drv_s_0(v15584, v15585, v15674, v15675, v15676, v15677);	// L24702
  col_w_0(v15586, v15618, v15623, v15628, v15633);	// L24703
  col_e_0(v15587, v15602, v15607, v15612, v15617);	// L24704
  col_n_0(v15588, v15658, v15659, v15660, v15661);	// L24705
  col_s_0(v15589, v15654, v15655, v15656, v15657);	// L24706
  rdrv_w_0(v15590, v15678, v15683, v15688, v15693);	// L24707
  rdrv_e_0(v15591, v15702, v15707, v15712, v15717);	// L24708
  rdrv_n_0(v15592, v15718, v15719, v15720, v15721);	// L24709
  rdrv_s_0(v15593, v15754, v15755, v15756, v15757);	// L24710
  rclc_w_0(v15594, v15698, v15703, v15708, v15713);	// L24711
  rclc_e_0(v15595, v15682, v15687, v15692, v15697);	// L24712
  rclc_n_0(v15596, v15738, v15739, v15740, v15741);	// L24713
  rclc_s_0(v15597, v15734, v15735, v15736, v15737);	// L24714
}

