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
  int32_t v0[1][1],
  hls::stream< ap_uint<26> >& v1,
  hls::stream< ap_uint<26> >& v2,
  hls::stream< ap_uint<26> >& v3,
  hls::stream< ap_uint<26> >& v4,
  hls::stream< ap_uint<17> >& v5,
  hls::stream< ap_uint<17> >& v6,
  hls::stream< ap_uint<17> >& v7,
  hls::stream< ap_uint<17> >& v8,
  hls::stream< int32_t >& v9,
  hls::stream< int32_t >& v10,
  hls::stream< int32_t >& v11,
  hls::stream< int32_t >& v12,
  hls::stream< int32_t >& v13,
  hls::stream< int32_t >& v14,
  hls::stream< int32_t >& v15,
  hls::stream< int32_t >& v16,
  hls::stream< ap_uint<26> >& v17,
  hls::stream< ap_uint<26> >& v18,
  hls::stream< ap_uint<26> >& v19,
  hls::stream< ap_uint<26> >& v20,
  hls::stream< int32_t >& v21,
  hls::stream< int32_t >& v22,
  hls::stream< int32_t >& v23,
  hls::stream< int32_t >& v24,
  hls::stream< int32_t >& v25,
  hls::stream< int32_t >& v26,
  hls::stream< int32_t >& v27,
  hls::stream< int32_t >& v28,
  hls::stream< ap_uint<17> >& v29,
  hls::stream< ap_uint<17> >& v30,
  hls::stream< ap_uint<17> >& v31,
  hls::stream< ap_uint<17> >& v32
) {	// L2
  int32_t irf[8];	// L39
  for (int v34 = 0; v34 < 8; v34++) {	// L40
    irf[v34] = 0;	// L40
  }
  int16_t drf[8];	// L41
  for (int v36 = 0; v36 < 8; v36++) {	// L42
    drf[v36] = 0;	// L42
  }
  int32_t drf_full[8];	// L43
  for (int v38 = 0; v38 < 8; v38++) {	// L44
    drf_full[v38] = 0;	// L44
  }
  int32_t dsmask;	// L45
  dsmask = 0;	// L46
  int32_t crv_vld;	// L47
  crv_vld = 0;	// L48
  int16_t crv_data;	// L49
  crv_data = 0;	// L50
  int32_t crv_addr;	// L51
  crv_addr = 0;	// L52
  int32_t crv_mode;	// L53
  crv_mode = 0;	// L54
  int32_t crv_raw;	// L55
  crv_raw = 0;	// L56
  int32_t csd_vld;	// L57
  csd_vld = 0;	// L58
  ap_uint<26> csd_pkt;	// L59
  csd_pkt = 0;	// L60
  int32_t csd_dir;	// L61
  csd_dir = 0;	// L62
  int32_t row_id;	// L63
  row_id = 0;	// L64
  int32_t col_id;	// L65
  col_id = 0;	// L66
  ap_uint<26> oe_r;	// L67
  oe_r = 0;	// L68
  ap_uint<26> ow_r;	// L69
  ow_r = 0;	// L70
  ap_uint<26> on_r;	// L71
  on_r = 0;	// L72
  ap_uint<26> os_r;	// L73
  os_r = 0;	// L74
  ap_uint<17> txn_r;	// L75
  txn_r = 0;	// L76
  ap_uint<17> txs_r;	// L77
  txs_r = 0;	// L78
  ap_uint<17> txw_r;	// L79
  txw_r = 0;	// L80
  ap_uint<17> txe_r;	// L81
  txe_r = 0;	// L82
  int16_t hold_v[4][2];	// L83
  for (int v59 = 0; v59 < 4; v59++) {	// L84
    for (int v60 = 0; v60 < 2; v60++) {	// L84
      hold_v[v59][v60] = 0;	// L84
    }
  }
  uint8_t hold_cnt[4];	// L85
  for (int v62 = 0; v62 < 4; v62++) {	// L86
    hold_cnt[v62] = 0;	// L86
  }
  ap_uint<26> rbuf[4][2];	// L87
  for (int v64 = 0; v64 < 4; v64++) {	// L88
    for (int v65 = 0; v65 < 2; v65++) {	// L88
      rbuf[v64][v65] = 0;	// L88
    }
  }
  uint8_t rbcnt[4];	// L89
  for (int v67 = 0; v67 < 4; v67++) {	// L90
    rbcnt[v67] = 0;	// L90
  }
  uint8_t rcred[4];	// L91
  for (int v69 = 0; v69 < 4; v69++) {	// L92
    rcred[v69] = 0;	// L92
  }
  uint8_t cre_r;	// L93
  cre_r = 2;	// L94
  uint8_t crw_r;	// L95
  crw_r = 2;	// L96
  uint8_t crs_r;	// L97
  crs_r = 2;	// L98
  uint8_t crn_r;	// L99
  crn_r = 2;	// L100
  int32_t scred[4];	// L101
  for (int v75 = 0; v75 < 4; v75++) {	// L102
    scred[v75] = 0;	// L102
  }
  int32_t txp_v[4];	// L103
  for (int v77 = 0; v77 < 4; v77++) {	// L104
    txp_v[v77] = 0;	// L104
  }
  int16_t txp_d[4];	// L105
  for (int v79 = 0; v79 < 4; v79++) {	// L106
    txp_d[v79] = 0;	// L106
  }
  int32_t txp_r[4];	// L107
  for (int v81 = 0; v81 < 4; v81++) {	// L108
    txp_r[v81] = 0;	// L108
  }
  int32_t sc_r[4];	// L109
  for (int v83 = 0; v83 < 4; v83++) {	// L110
    sc_r[v83] = 2;	// L110
  }
  int32_t cfg_isz;	// L111
  cfg_isz = 0;	// L112
  int32_t cfg_itsz;	// L113
  cfg_itsz = 0;	// L114
  uint8_t fetch_en;	// L115
  fetch_en = 0;	// L116
  uint8_t instr_cnt;	// L117
  instr_cnt = 0;	// L118
  uint8_t iter_cnt;	// L119
  iter_cnt = 0;	// L120
  uint8_t condition_reg;	// L121
  condition_reg = 0;	// L122
  uint8_t sb_v[5];	// L123
  for (int v91 = 0; v91 < 5; v91++) {	// L124
    sb_v[v91] = 0;	// L124
  }
  uint8_t sb_dst[5];	// L125
  for (int v93 = 0; v93 < 5; v93++) {	// L126
    sb_dst[v93] = 0;	// L126
  }
  uint8_t sb_cmp[5];	// L127
  for (int v95 = 0; v95 < 5; v95++) {	// L128
    sb_cmp[v95] = 0;	// L128
  }
  uint8_t sb_rtr[5];	// L129
  for (int v97 = 0; v97 < 5; v97++) {	// L130
    sb_rtr[v97] = 0;	// L130
  }
  uint8_t sb_inj[5];	// L131
  for (int v99 = 0; v99 < 5; v99++) {	// L132
    sb_inj[v99] = 0;	// L132
  }
  uint8_t sb_dir[5];	// L133
  for (int v101 = 0; v101 < 5; v101++) {	// L134
    sb_dir[v101] = 0;	// L134
  }
  uint8_t sb_id[5];	// L135
  for (int v103 = 0; v103 < 5; v103++) {	// L136
    sb_id[v103] = 0;	// L136
  }
  uint8_t sb_rvld[5];	// L137
  for (int v105 = 0; v105 < 5; v105++) {	// L138
    sb_rvld[v105] = 0;	// L138
  }
  uint8_t sb_ix[5];	// L139
  for (int v107 = 0; v107 < 5; v107++) {	// L140
    sb_ix[v107] = 0;	// L140
  }
  uint8_t sb_long[5];	// L141
  for (int v109 = 0; v109 < 5; v109++) {	// L142
    sb_long[v109] = 0;	// L142
  }
  int16_t resq[8];	// L143
  for (int v111 = 0; v111 < 8; v111++) {	// L144
    resq[v111] = 0;	// L144
  }
  uint8_t cmpq[8];	// L145
  for (int v113 = 0; v113 < 8; v113++) {	// L146
    cmpq[v113] = 0;	// L146
  }
  uint8_t resq_wr;	// L147
  resq_wr = 0;	// L148
  ap_uint<26> zpkt;	// L149
  zpkt = 0;	// L150
  ap_uint<17> zsys;	// L151
  zsys = 0;	// L152
  int32_t zcr;	// L153
  zcr = 0;	// L154
  int32_t v118 = v0[0][0];	// L155
  ap_int<33> v119 = v118;	// L156
  ap_int<33> v120 = v119 - 1;	// L157
  int v121 = v120;	// L158
  for (int v122 = 0; v122 < v121; v122 += 1) {	// L159
    ap_int<26> v123 = zpkt;	// L160
    v1.write(v123);	// L161
    ap_int<26> v124 = zpkt;	// L162
    v2.write(v124);	// L163
    ap_int<26> v125 = zpkt;	// L164
    v3.write(v125);	// L165
    ap_int<26> v126 = zpkt;	// L166
    v4.write(v126);	// L167
    ap_int<17> v127 = zsys;	// L168
    v5.write(v127);	// L169
    ap_int<17> v128 = zsys;	// L170
    v6.write(v128);	// L171
    ap_int<17> v129 = zsys;	// L172
    v7.write(v129);	// L173
    ap_int<17> v130 = zsys;	// L174
    v8.write(v130);	// L175
    int32_t v131 = zcr;	// L176
    v9.write(v131);	// L177
    int32_t v132 = zcr;	// L178
    v10.write(v132);	// L179
    int32_t v133 = zcr;	// L180
    v11.write(v133);	// L181
    int32_t v134 = zcr;	// L182
    v12.write(v134);	// L183
    int32_t v135 = zcr;	// L184
    v13.write(v135);	// L185
    int32_t v136 = zcr;	// L186
    v14.write(v136);	// L187
    int32_t v137 = zcr;	// L188
    v15.write(v137);	// L189
    int32_t v138 = zcr;	// L190
    v16.write(v138);	// L191
  }
  ap_int<26> v139 = oe_r;	// L193
  v1.write(v139);	// L194
  ap_int<26> v140 = ow_r;	// L195
  v2.write(v140);	// L196
  ap_int<26> v141 = os_r;	// L197
  v3.write(v141);	// L198
  ap_int<26> v142 = on_r;	// L199
  v4.write(v142);	// L200
  ap_int<17> v143 = txe_r;	// L201
  v5.write(v143);	// L202
  ap_int<17> v144 = txw_r;	// L203
  v6.write(v144);	// L204
  ap_int<17> v145 = txs_r;	// L205
  v7.write(v145);	// L206
  ap_int<17> v146 = txn_r;	// L207
  v8.write(v146);	// L208
  int8_t v147 = cre_r;	// L209
  v9.write(v147);	// L210
  int8_t v148 = crw_r;	// L211
  v10.write(v148);	// L212
  int8_t v149 = crs_r;	// L213
  v11.write(v149);	// L214
  int8_t v150 = crn_r;	// L215
  v12.write(v150);	// L216
  int32_t v151 = sc_r[0];	// L217
  v15.write(v151);	// L218
  int32_t v152 = sc_r[1];	// L219
  v16.write(v152);	// L220
  int32_t v153 = sc_r[2];	// L221
  v13.write(v153);	// L222
  int32_t v154 = sc_r[3];	// L223
  v14.write(v154);	// L224
  l_S_t_1_t: for (int t = 0; t < 2000; t++) {	// L225
  #pragma HLS pipeline II=1
  #pragma HLS array_partition variable=cmpq complete dim=1
  #pragma HLS array_partition variable=drf complete dim=1
  #pragma HLS array_partition variable=drf_full complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2
  #pragma HLS array_partition variable=rbcnt complete dim=1
  #pragma HLS array_partition variable=rcred complete dim=1
  #pragma HLS array_partition variable=scred complete dim=1
  #pragma HLS array_partition variable=hold_cnt complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2
  #pragma HLS array_partition variable=irf complete dim=1
  #pragma HLS array_partition variable=resq complete dim=1
  #pragma HLS array_partition variable=sb_cmp complete dim=1
  #pragma HLS array_partition variable=sb_dir complete dim=1
  #pragma HLS array_partition variable=sb_dst complete dim=1
  #pragma HLS array_partition variable=sb_id complete dim=1
  #pragma HLS array_partition variable=sb_inj complete dim=1
  #pragma HLS array_partition variable=sb_ix complete dim=1
  #pragma HLS array_partition variable=sb_long complete dim=1
  #pragma HLS array_partition variable=sb_rtr complete dim=1
  #pragma HLS array_partition variable=sb_rvld complete dim=1
  #pragma HLS array_partition variable=sb_v complete dim=1
  #pragma HLS array_partition variable=txp_d complete dim=1
  #pragma HLS array_partition variable=txp_v complete dim=1
    ap_uint<26> v156 = v17.read();	// L226
    ap_uint<26> p_w;	// L227
    p_w = v156;	// L228
    ap_uint<26> v158 = v18.read();	// L229
    ap_uint<26> p_e;	// L230
    p_e = v158;	// L231
    ap_uint<26> v160 = v19.read();	// L232
    ap_uint<26> p_n;	// L233
    p_n = v160;	// L234
    ap_uint<26> v162 = v20.read();	// L235
    ap_uint<26> p_s;	// L236
    p_s = v162;	// L237
    int32_t v164 = v21.read();	// L238
    uint8_t v165 = rcred[0];	// L239
    ap_int<33> v166 = v165;	// L240
    ap_int<33> v167 = v164;	// L241
    ap_int<33> v168 = v166 + v167;	// L242
    uint8_t v169 = v168;	// L243
    rcred[0] = v169;	// L244
    int32_t v170 = v22.read();	// L245
    uint8_t v171 = rcred[1];	// L246
    ap_int<33> v172 = v171;	// L247
    ap_int<33> v173 = v170;	// L248
    ap_int<33> v174 = v172 + v173;	// L249
    uint8_t v175 = v174;	// L250
    rcred[1] = v175;	// L251
    int32_t v176 = v23.read();	// L252
    uint8_t v177 = rcred[2];	// L253
    ap_int<33> v178 = v177;	// L254
    ap_int<33> v179 = v176;	// L255
    ap_int<33> v180 = v178 + v179;	// L256
    uint8_t v181 = v180;	// L257
    rcred[2] = v181;	// L258
    int32_t v182 = v24.read();	// L259
    uint8_t v183 = rcred[3];	// L260
    ap_int<33> v184 = v183;	// L261
    ap_int<33> v185 = v182;	// L262
    ap_int<33> v186 = v184 + v185;	// L263
    uint8_t v187 = v186;	// L264
    rcred[3] = v187;	// L265
    int32_t v188 = v25.read();	// L266
    int32_t v189 = scred[0];	// L267
    ap_int<33> v190 = v189;	// L268
    ap_int<33> v191 = v188;	// L269
    ap_int<33> v192 = v190 + v191;	// L270
    int32_t v193 = v192;	// L271
    scred[0] = v193;	// L272
    int32_t v194 = v26.read();	// L273
    int32_t v195 = scred[1];	// L274
    ap_int<33> v196 = v195;	// L275
    ap_int<33> v197 = v194;	// L276
    ap_int<33> v198 = v196 + v197;	// L277
    int32_t v199 = v198;	// L278
    scred[1] = v199;	// L279
    int32_t v200 = v27.read();	// L280
    int32_t v201 = scred[2];	// L281
    ap_int<33> v202 = v201;	// L282
    ap_int<33> v203 = v200;	// L283
    ap_int<33> v204 = v202 + v203;	// L284
    int32_t v205 = v204;	// L285
    scred[2] = v205;	// L286
    int32_t v206 = v28.read();	// L287
    int32_t v207 = scred[3];	// L288
    ap_int<33> v208 = v207;	// L289
    ap_int<33> v209 = v206;	// L290
    ap_int<33> v210 = v208 + v209;	// L291
    int32_t v211 = v210;	// L292
    scred[3] = v211;	// L293
    ap_uint<26> fin[4];	// L294
    for (int v213 = 0; v213 < 4; v213++) {	// L295
      fin[v213] = 0;	// L295
    }
    ap_int<26> v214 = p_w;	// L296
    fin[0] = v214;	// L297
    ap_int<26> v215 = p_e;	// L298
    fin[1] = v215;	// L299
    ap_int<26> v216 = p_n;	// L300
    fin[2] = v216;	// L301
    ap_int<26> v217 = p_s;	// L302
    fin[3] = v217;	// L303
    l_S_d_1_d: for (int d = 0; d < 4; d++) {	// L304
      ap_uint<26> v219 = fin[d];	// L305
      bool v220;
      ap_int<26> v220_tmp = v219;
      v220 = v220_tmp[25];	// L306
      int32_t v221 = v220;	// L307
      bool v222 = v221 == 1;	// L308
      uint8_t v223 = rbcnt[d];	// L309
      int32_t v224 = v223;	// L310
      bool v225 = v224 < 2;	// L311
      bool v226 = v222 & v225;	// L312
      if (v226) {	// L313
        ap_uint<26> v227 = fin[d];	// L314
        uint8_t v228 = rbcnt[d];	// L315
        int v229 = v228;	// L316
        rbuf[d][v229] = v227;	// L317
        uint8_t v230 = rbcnt[d];	// L318
        ap_int<33> v231 = v230;	// L319
        ap_int<33> v232 = v231 + 1;	// L320
        uint8_t v233 = v232;	// L321
        rbcnt[d] = v233;	// L322
      }
    }
    ap_uint<26> hd[4];	// L325
    for (int v235 = 0; v235 < 4; v235++) {	// L326
      hd[v235] = 0;	// L326
    }
    int32_t hvld[4];	// L327
    for (int v237 = 0; v237 < 4; v237++) {	// L328
      hvld[v237] = 0;	// L328
    }
    int32_t hit[4];	// L329
    for (int v239 = 0; v239 < 4; v239++) {	// L330
      hit[v239] = 0;	// L330
    }
    int32_t axis[4];	// L331
    for (int v241 = 0; v241 < 4; v241++) {	// L332
      axis[v241] = 0;	// L332
    }
    int32_t v242 = col_id;	// L333
    axis[0] = v242;	// L334
    int32_t v243 = col_id;	// L335
    axis[1] = v243;	// L336
    int32_t v244 = row_id;	// L337
    axis[2] = v244;	// L338
    int32_t v245 = row_id;	// L339
    axis[3] = v245;	// L340
    l_S_d_2_d1: for (int d1 = 0; d1 < 4; d1++) {	// L341
      uint8_t v247 = rbcnt[d1];	// L342
      int32_t v248 = v247;	// L343
      bool v249 = v248 > 0;	// L344
      if (v249) {	// L345
        ap_uint<26> v250 = rbuf[d1][0];	// L346
        hd[d1] = v250;	// L347
        hvld[d1] = 1;	// L348
        ap_uint<26> v251 = hd[d1];	// L349
        ap_int<4> v252;
        ap_int<26> v252_tmp = v251;
        v252 = v252_tmp(24, 21);	// L350
        int32_t v253 = axis[d1];	// L351
        int32_t v254 = v252;	// L352
        bool v255 = v254 == v253;	// L353
        if (v255) {	// L354
          hit[d1] = 1;	// L355
        }
      }
    }
    ap_uint<26> o_crv;	// L359
    o_crv = 0;	// L360
    int32_t crv_in;	// L361
    crv_in = -1;	// L362
    int32_t v258 = hit[3];	// L363
    bool v259 = v258 == 1;	// L364
    if (v259) {	// L365
      ap_uint<26> v260 = hd[3];	// L366
      o_crv = v260;	// L367
      crv_in = 3;	// L368
    } else {
      int32_t v261 = hit[2];	// L370
      bool v262 = v261 == 1;	// L371
      if (v262) {	// L372
        ap_uint<26> v263 = hd[2];	// L373
        o_crv = v263;	// L374
        crv_in = 2;	// L375
      } else {
        int32_t v264 = hit[1];	// L377
        bool v265 = v264 == 1;	// L378
        if (v265) {	// L379
          ap_uint<26> v266 = hd[1];	// L380
          o_crv = v266;	// L381
          crv_in = 1;	// L382
        } else {
          int32_t v267 = hit[0];	// L384
          bool v268 = v267 == 1;	// L385
          if (v268) {	// L386
            ap_uint<26> v269 = hd[0];	// L387
            o_crv = v269;	// L388
            crv_in = 0;	// L389
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L394
    for (int v271 = 0; v271 < 4; v271++) {	// L395
      o_out[v271] = 0;	// L395
    }
    int32_t pop[4];	// L396
    for (int v273 = 0; v273 < 4; v273++) {	// L397
      pop[v273] = 0;	// L397
    }
    int32_t inj_done;	// L398
    inj_done = 0;	// L399
    int32_t idir;	// L400
    idir = -1;	// L401
    ap_int<26> v276 = csd_pkt;	// L402
    bool v277;
    ap_int<26> v277_tmp = v276;
    v277 = v277_tmp[25];	// L403
    int32_t v278 = v277;	// L404
    bool v279 = v278 == 1;	// L405
    if (v279) {	// L406
      int32_t v280 = csd_dir;	// L407
      ap_int<33> v281 = v280;	// L408
      ap_int<33> v282 = 3 - v281;	// L409
      int32_t v283 = v282;	// L410
      idir = v283;	// L411
    }
    l_S_o_3_o: for (int o = 0; o < 4; o++) {	// L413
      uint8_t v285 = rcred[o];	// L414
      int32_t v286 = v285;	// L415
      bool v287 = v286 > 0;	// L416
      if (v287) {	// L417
        int32_t v288 = idir;	// L418
        ap_int<33> v289 = v288;	// L419
        ap_int<33> v290 = o;	// L420
        bool v291 = v289 == v290;	// L421
        if (v291) {	// L422
          ap_int<26> v292 = csd_pkt;	// L423
          o_out[o] = v292;	// L424
          uint8_t v293 = rcred[o];	// L425
          ap_int<33> v294 = v293;	// L426
          ap_int<33> v295 = v294 - 1;	// L427
          uint8_t v296 = v295;	// L428
          rcred[o] = v296;	// L429
          inj_done = 1;	// L430
        } else {
          int32_t v297 = hvld[o];	// L432
          bool v298 = v297 == 1;	// L433
          int32_t v299 = hit[o];	// L434
          bool v300 = v299 == 0;	// L435
          bool v301 = v298 & v300;	// L436
          if (v301) {	// L437
            ap_uint<26> v302 = hd[o];	// L438
            o_out[o] = v302;	// L439
            uint8_t v303 = rcred[o];	// L440
            ap_int<33> v304 = v303;	// L441
            ap_int<33> v305 = v304 - 1;	// L442
            uint8_t v306 = v305;	// L443
            rcred[o] = v306;	// L444
            pop[o] = 1;	// L445
          }
        }
      }
    }
    int32_t v307 = crv_in;	// L450
    bool v308 = v307 >= 0;	// L451
    if (v308) {	// L452
      int32_t v309 = crv_in;	// L453
      int v310 = v309;	// L454
      pop[v310] = 1;	// L455
    }
    int32_t ret[4];	// L457
    for (int v312 = 0; v312 < 4; v312++) {	// L458
      ret[v312] = 0;	// L458
    }
    l_S_d_4_d2: for (int d2 = 0; d2 < 4; d2++) {	// L459
      int32_t v314 = pop[d2];	// L460
      bool v315 = v314 == 1;	// L461
      if (v315) {	// L462
        l_S_sft_4_sft: for (int sft = 0; sft < 1; sft++) {	// L463
          ap_uint<26> v317 = rbuf[d2][(sft + 1)];	// L464
          rbuf[d2][sft] = v317;	// L465
        }
        uint8_t v318 = rbcnt[d2];	// L467
        ap_int<33> v319 = v318;	// L468
        ap_int<33> v320 = v319 - 1;	// L469
        uint8_t v321 = v320;	// L470
        rbcnt[d2] = v321;	// L471
        ret[d2] = 1;	// L472
      }
    }
    int32_t v322 = ret[0];	// L475
    uint8_t v323 = v322;	// L476
    cre_r = v323;	// L477
    int32_t v324 = ret[1];	// L478
    uint8_t v325 = v324;	// L479
    crw_r = v325;	// L480
    int32_t v326 = ret[2];	// L481
    uint8_t v327 = v326;	// L482
    crs_r = v327;	// L483
    int32_t v328 = ret[3];	// L484
    uint8_t v329 = v328;	// L485
    crn_r = v329;	// L486
    ap_uint<26> v330 = o_out[0];	// L487
    oe_r = v330;	// L488
    ap_uint<26> v331 = o_out[1];	// L489
    ow_r = v331;	// L490
    ap_uint<26> v332 = o_out[2];	// L491
    os_r = v332;	// L492
    ap_uint<26> v333 = o_out[3];	// L493
    on_r = v333;	// L494
    int32_t v334 = inj_done;	// L495
    bool v335 = v334 == 1;	// L496
    if (v335) {	// L497
      csd_pkt = 0;	// L498
    }
    ap_int<26> v336 = o_crv;	// L500
    bool v337;
    ap_int<26> v337_tmp = v336;
    v337 = v337_tmp[25];	// L501
    int32_t v338 = v337;	// L502
    crv_vld = v338;	// L503
    ap_int<26> v339 = o_crv;	// L504
    int16_t v340;
    ap_int<26> v340_tmp = v339;
    v340 = v340_tmp(15, 0);	// L505
    crv_data = v340;	// L506
    ap_int<26> v341 = o_crv;	// L507
    ap_int<4> v342;
    ap_int<26> v342_tmp = v341;
    v342 = v342_tmp(19, 16);	// L508
    int32_t v343 = v342;	// L509
    crv_addr = v343;	// L510
    ap_int<26> v344 = o_crv;	// L511
    bool v345;
    ap_int<26> v345_tmp = v344;
    v345 = v345_tmp[20];	// L512
    int32_t v346 = v345;	// L513
    crv_mode = v346;	// L514
    ap_int<26> v347 = o_crv;	// L515
    int16_t v348;
    ap_int<26> v348_tmp = v347;
    v348 = v348_tmp(15, 0);	// L516
    int32_t v349 = v348;	// L517
    crv_raw = v349;	// L518
    ap_uint<17> v350 = v29.read();	// L519
    ap_uint<17> rx_w;	// L520
    rx_w = v350;	// L521
    ap_uint<17> v352 = v30.read();	// L522
    ap_uint<17> rx_e;	// L523
    rx_e = v352;	// L524
    ap_uint<17> v354 = v31.read();	// L525
    ap_uint<17> rx_n;	// L526
    rx_n = v354;	// L527
    ap_uint<17> v356 = v32.read();	// L528
    ap_uint<17> rx_s;	// L529
    rx_s = v356;	// L530
    int16_t rxv[4];	// L531
    for (int v359 = 0; v359 < 4; v359++) {	// L532
      rxv[v359] = 0;	// L532
    }
    int32_t rxvld[4];	// L533
    for (int v361 = 0; v361 < 4; v361++) {	// L534
      rxvld[v361] = 0;	// L534
    }
    ap_int<17> v362 = rx_n;	// L535
    int16_t v363;
    ap_int<17> v363_tmp = v362;
    v363 = v363_tmp(16, 1);	// L536
    rxv[0] = v363;	// L537
    ap_int<17> v364 = rx_n;	// L538
    bool v365;
    ap_int<17> v365_tmp = v364;
    v365 = v365_tmp[0];	// L539
    int32_t v366 = v365;	// L540
    rxvld[0] = v366;	// L541
    ap_int<17> v367 = rx_s;	// L542
    int16_t v368;
    ap_int<17> v368_tmp = v367;
    v368 = v368_tmp(16, 1);	// L543
    rxv[1] = v368;	// L544
    ap_int<17> v369 = rx_s;	// L545
    bool v370;
    ap_int<17> v370_tmp = v369;
    v370 = v370_tmp[0];	// L546
    int32_t v371 = v370;	// L547
    rxvld[1] = v371;	// L548
    ap_int<17> v372 = rx_w;	// L549
    int16_t v373;
    ap_int<17> v373_tmp = v372;
    v373 = v373_tmp(16, 1);	// L550
    rxv[2] = v373;	// L551
    ap_int<17> v374 = rx_w;	// L552
    bool v375;
    ap_int<17> v375_tmp = v374;
    v375 = v375_tmp[0];	// L553
    int32_t v376 = v375;	// L554
    rxvld[2] = v376;	// L555
    ap_int<17> v377 = rx_e;	// L556
    int16_t v378;
    ap_int<17> v378_tmp = v377;
    v378 = v378_tmp(16, 1);	// L557
    rxv[3] = v378;	// L558
    ap_int<17> v379 = rx_e;	// L559
    bool v380;
    ap_int<17> v380_tmp = v379;
    v380 = v380_tmp[0];	// L560
    int32_t v381 = v380;	// L561
    rxvld[3] = v381;	// L562
    l_S_d_6_d3: for (int d3 = 0; d3 < 4; d3++) {	// L563
      int32_t v383 = rxvld[d3];	// L564
      bool v384 = v383 == 1;	// L565
      uint8_t v385 = hold_cnt[d3];	// L566
      int32_t v386 = v385;	// L567
      bool v387 = v386 < 2;	// L568
      bool v388 = v384 & v387;	// L569
      if (v388) {	// L570
        int16_t v389 = rxv[d3];	// L571
        uint8_t v390 = hold_cnt[d3];	// L572
        int v391 = v390;	// L573
        hold_v[d3][v391] = v389;	// L574
        uint8_t v392 = hold_cnt[d3];	// L575
        ap_int<33> v393 = v392;	// L576
        ap_int<33> v394 = v393 + 1;	// L577
        uint8_t v395 = v394;	// L578
        hold_cnt[d3] = v395;	// L579
      }
    }
    int32_t retire_ok;	// L582
    retire_ok = 1;	// L583
    uint8_t v397 = sb_v[0];	// L584
    int32_t v398 = v397;	// L585
    bool v399 = v398 == 1;	// L586
    uint8_t v400 = sb_rtr[0];	// L587
    int32_t v401 = v400;	// L588
    bool v402 = v401 == 0;	// L589
    uint8_t v403 = sb_dst[0];	// L590
    int32_t v404 = v403;	// L591
    bool v405 = v404 >= 12;	// L592
    bool v406 = v399 & v402;	// L593
    bool v407 = v406 & v405;	// L594
    if (v407) {	// L595
      uint8_t v408 = sb_rvld[0];	// L596
      int32_t v409 = v408;	// L597
      bool v410 = v409 == 1;	// L598
      uint8_t v411 = sb_dst[0];	// L599
      int32_t v412 = v411;	// L600
      int32_t v413 = v412 & 3;	// L601
      int v414 = v413;	// L602
      int32_t v415 = txp_v[v414];	// L603
      bool v416 = v415 == 1;	// L604
      bool v417 = v410 & v416;	// L605
      if (v417) {	// L606
        retire_ok = 0;	// L607
      }
    }
    uint8_t v418 = sb_v[0];	// L610
    int32_t v419 = v418;	// L611
    bool v420 = v419 == 1;	// L612
    int32_t v421 = retire_ok;	// L613
    bool v422 = v421 == 1;	// L614
    bool v423 = v420 & v422;	// L615
    if (v423) {	// L616
      uint8_t v424 = sb_ix[0];	// L617
      int v425 = v424;	// L618
      int16_t v426 = resq[v425];	// L619
      int16_t wb;	// L620
      wb = v426;	// L621
      uint8_t v428 = sb_cmp[0];	// L622
      int32_t v429 = v428;	// L623
      bool v430 = v429 == 1;	// L624
      if (v430) {	// L625
        uint8_t v431 = sb_ix[0];	// L626
        int v432 = v431;	// L627
        uint8_t v433 = cmpq[v432];	// L628
        condition_reg = v433;	// L629
      }
      uint8_t v434 = sb_rtr[0];	// L631
      int32_t v435 = v434;	// L632
      bool v436 = v435 == 1;	// L633
      if (v436) {	// L634
        uint8_t v437 = sb_inj[0];	// L635
        int32_t v438 = v437;	// L636
        bool v439 = v438 == 1;	// L637
        ap_int<26> v440 = csd_pkt;	// L638
        bool v441;
        ap_int<26> v441_tmp = v440;
        v441 = v441_tmp[25];	// L639
        int32_t v442 = v441;	// L640
        bool v443 = v442 == 0;	// L641
        bool v444 = v439 & v443;	// L642
        if (v444) {	// L643
          int16_t v445 = wb;	// L644
          ap_int<26> v446 = csd_pkt;	// L645
          ap_int<26> v447;
          ap_int<26> v447_tmp = v446;
          v447_tmp(15, 0) = v445;
          v447 = v447_tmp;	// L646
          csd_pkt = v447;	// L647
          uint8_t v448 = sb_dst[0];	// L648
          ap_uint<4> v449 = v448;	// L649
          ap_int<26> v450 = csd_pkt;	// L650
          ap_int<26> v451;
          ap_int<26> v451_tmp = v450;
          v451_tmp(19, 16) = v449;
          v451 = v451_tmp;	// L651
          csd_pkt = v451;	// L652
          uint8_t v452 = sb_id[0];	// L653
          ap_uint<4> v453 = v452;	// L654
          ap_int<26> v454 = csd_pkt;	// L655
          ap_int<26> v455;
          ap_int<26> v455_tmp = v454;
          v455_tmp(24, 21) = v453;
          v455 = v455_tmp;	// L656
          csd_pkt = v455;	// L657
          uint8_t v456 = sb_rvld[0];	// L658
          bool v457 = v456;	// L659
          ap_int<26> v458 = csd_pkt;	// L660
          ap_int<26> v459;
          ap_int<26> v459_tmp = v458;
          v459_tmp[25] = v457;          v459 = v459_tmp;	// L661
          csd_pkt = v459;	// L662
          uint8_t v460 = sb_dir[0];	// L663
          int32_t v461 = v460;	// L664
          csd_dir = v461;	// L665
        }
      } else {
        uint8_t v462 = sb_dst[0];	// L668
        int32_t v463 = v462;	// L669
        bool v464 = v463 >= 12;	// L670
        if (v464) {	// L671
          uint8_t v465 = sb_rvld[0];	// L672
          int32_t v466 = v465;	// L673
          bool v467 = v466 == 1;	// L674
          if (v467) {	// L675
            uint8_t v468 = sb_dst[0];	// L676
            int32_t v469 = v468;	// L677
            int32_t v470 = v469 & 3;	// L678
            int v471 = v470;	// L679
            txp_v[v471] = 1;	// L680
            int16_t v472 = wb;	// L681
            uint8_t v473 = sb_dst[0];	// L682
            int32_t v474 = v473;	// L683
            int32_t v475 = v474 & 3;	// L684
            int v476 = v475;	// L685
            txp_d[v476] = v472;	// L686
            uint8_t v477 = sb_dst[0];	// L687
            int32_t v478 = v477;	// L688
            int32_t v479 = v478 & 3;	// L689
            int v480 = v479;	// L690
            txp_r[v480] = 1;	// L691
          }
        } else {
          uint8_t v481 = sb_rvld[0];	// L694
          int32_t v482 = v481;	// L695
          bool v483 = v482 == 1;	// L696
          if (v483) {	// L697
            uint8_t v484 = sb_dst[0];	// L698
            int32_t v485 = v484;	// L699
            bool v486 = v485 < 8;	// L700
            int32_t v487 = dsmask;	// L701
            int32_t v488 = v487 >> v485;	// L704
            int32_t v489 = v488 & 1;	// L705
            bool v490 = v489 == 1;	// L706
            bool v491 = v486 & v490;	// L707
            if (v491) {	// L708
              uint8_t v492 = sb_dst[0];	// L709
              int v493 = v492;	// L710
              int32_t v494 = drf_full[v493];	// L711
              bool v495 = v494 == 0;	// L712
              if (v495) {	// L713
                int16_t v496 = wb;	// L714
                uint8_t v497 = sb_dst[0];	// L715
                int v498 = v497;	// L716
                drf[v498] = v496;	// L717
                uint8_t v499 = sb_dst[0];	// L718
                int v500 = v499;	// L719
                drf_full[v500] = 1;	// L720
              }
            } else {
              int16_t v501 = wb;	// L723
              uint8_t v502 = sb_dst[0];	// L724
              int32_t v503 = v502;	// L725
              int32_t v504 = v503 & 7;	// L726
              int v505 = v504;	// L727
              drf[v505] = v501;	// L728
            }
          }
        }
      }
    }
    int32_t pc;	// L734
    pc = -1;	// L735
    int8_t v507 = fetch_en;	// L736
    int32_t v508 = v507;	// L737
    bool v509 = v508 == 1;	// L738
    if (v509) {	// L739
      int8_t v510 = instr_cnt;	// L740
      int32_t v511 = v510;	// L741
      pc = v511;	// L742
    }
    int32_t instr;	// L744
    instr = 0;	// L745
    int32_t v513 = pc;	// L746
    bool v514 = v513 >= 0;	// L747
    if (v514) {	// L748
      int32_t v515 = pc;	// L749
      int v516 = v515;	// L750
      int32_t v517 = irf[v516];	// L751
      instr = v517;	// L752
    }
    int32_t v518 = instr;	// L754
    int32_t v519 = v518 & 15;	// L755
    int32_t op;	// L756
    op = v519;	// L757
    int32_t v521 = instr;	// L758
    int32_t v522 = v521 >> 4;	// L759
    int32_t v523 = v522 & 15;	// L760
    int32_t dst;	// L761
    dst = v523;	// L762
    int32_t v525 = instr;	// L763
    int32_t v526 = v525 >> 8;	// L764
    int32_t v527 = v526 & 15;	// L765
    int32_t s1;	// L766
    s1 = v527;	// L767
    int32_t v529 = instr;	// L768
    int32_t v530 = v529 >> 12;	// L769
    int32_t v531 = v530 & 15;	// L770
    int32_t s2;	// L771
    s2 = v531;	// L772
    int16_t a;	// L773
    a = 0;	// L774
    int16_t b;	// L775
    b = 0;	// L776
    int32_t v535 = s1;	// L777
    bool v536 = v535 >= 12;	// L778
    if (v536) {	// L779
      int32_t v537 = s1;	// L780
      int32_t v538 = v537 & 3;	// L781
      int v539 = v538;	// L782
      int16_t v540 = hold_v[v539][0];	// L783
      a = v540;	// L784
    } else {
      int32_t v541 = s1;	// L786
      int v542 = v541;	// L787
      int16_t v543 = drf[v542];	// L788
      a = v543;	// L789
    }
    int32_t v544 = s2;	// L791
    bool v545 = v544 >= 12;	// L792
    if (v545) {	// L793
      int32_t v546 = s2;	// L794
      int32_t v547 = v546 & 3;	// L795
      int v548 = v547;	// L796
      int16_t v549 = hold_v[v548][0];	// L797
      b = v549;	// L798
    } else {
      int32_t v550 = s2;	// L800
      int v551 = v550;	// L801
      int16_t v552 = drf[v551];	// L802
      b = v552;	// L803
    }
    int32_t a_vld;	// L805
    a_vld = 1;	// L806
    int32_t b_vld;	// L807
    b_vld = 1;	// L808
    int32_t v555 = s1;	// L809
    bool v556 = v555 >= 12;	// L810
    if (v556) {	// L811
      a_vld = 0;	// L812
      int32_t v557 = s1;	// L813
      int32_t v558 = v557 & 3;	// L814
      int v559 = v558;	// L815
      uint8_t v560 = hold_cnt[v559];	// L816
      int32_t v561 = v560;	// L817
      bool v562 = v561 > 0;	// L818
      if (v562) {	// L819
        a_vld = 1;	// L820
      }
    }
    int32_t v563 = s2;	// L823
    bool v564 = v563 >= 12;	// L824
    if (v564) {	// L825
      b_vld = 0;	// L826
      int32_t v565 = s2;	// L827
      int32_t v566 = v565 & 3;	// L828
      int v567 = v566;	// L829
      uint8_t v568 = hold_cnt[v567];	// L830
      int32_t v569 = v568;	// L831
      bool v570 = v569 > 0;	// L832
      if (v570) {	// L833
        b_vld = 1;	// L834
      }
    }
    int32_t v571 = s1;	// L837
    bool v572 = v571 < 8;	// L838
    int32_t v573 = dsmask;	// L839
    int32_t v574 = v573 >> v571;	// L841
    int32_t v575 = v574 & 1;	// L842
    bool v576 = v575 == 1;	// L843
    bool v577 = v572 & v576;	// L844
    if (v577) {	// L845
      int32_t v578 = s1;	// L846
      int v579 = v578;	// L847
      int32_t v580 = drf_full[v579];	// L848
      bool v581 = v580 == 0;	// L849
      if (v581) {	// L850
        a_vld = 0;	// L851
      }
    }
    int32_t v582 = s2;	// L854
    bool v583 = v582 < 8;	// L855
    int32_t v584 = dsmask;	// L856
    int32_t v585 = v584 >> v582;	// L858
    int32_t v586 = v585 & 1;	// L859
    bool v587 = v586 == 1;	// L860
    bool v588 = v583 & v587;	// L861
    if (v588) {	// L862
      int32_t v589 = s2;	// L863
      int v590 = v589;	// L864
      int32_t v591 = drf_full[v590];	// L865
      bool v592 = v591 == 0;	// L866
      if (v592) {	// L867
        b_vld = 0;	// L868
      }
    }
    int32_t binop;	// L871
    binop = 0;	// L872
    int32_t v594 = op;	// L873
    bool v595 = v594 == 0;	// L874
    bool v596 = v594 == 1;	// L876
    bool v597 = v594 == 2;	// L878
    bool v598 = v594 == 8;	// L880
    bool v599 = v594 == 9;	// L882
    bool v600 = v595 | v596;	// L883
    bool v601 = v600 | v597;	// L884
    bool v602 = v601 | v598;	// L885
    bool v603 = v602 | v599;	// L886
    if (v603) {	// L887
      binop = 1;	// L888
    }
    int32_t raw;	// L890
    raw = 0;	// L891
    int32_t cmp_busy;	// L892
    cmp_busy = 0;	// L893
    int32_t fwd_a;	// L894
    fwd_a = 0;	// L895
    int32_t fwd_a_ix;	// L896
    fwd_a_ix = 0;	// L897
    int32_t raw_a;	// L898
    raw_a = 0;	// L899
    int32_t fwd_b;	// L900
    fwd_b = 0;	// L901
    int32_t fwd_b_ix;	// L902
    fwd_b_ix = 0;	// L903
    int32_t raw_b;	// L904
    raw_b = 0;	// L905
    l_S_k_7_k: for (int k = 0; k < 4; k++) {	// L906
      ap_int<34> v613 = k;	// L907
      ap_int<34> v614 = v613 + 1;	// L908
      int32_t v615 = v614;	// L909
      int32_t kk;	// L910
      kk = v615;	// L911
      int32_t v617 = kk;	// L912
      ap_int<34> v618 = v617;	// L913
      ap_int<34> v619 = 4 - v618;	// L914
      int32_t v620 = v619;	// L915
      int32_t inflight;	// L916
      inflight = v620;	// L917
      int32_t need;	// L918
      need = 0;	// L919
      int32_t v623 = kk;	// L920
      int v624 = v623;	// L921
      uint8_t v625 = sb_long[v624];	// L922
      int32_t v626 = v625;	// L923
      bool v627 = v626 == 1;	// L924
      if (v627) {	// L925
        need = 0;	// L926
      }
      int32_t rdy;	// L928
      rdy = 0;	// L929
      int32_t v629 = inflight;	// L930
      int32_t v630 = need;	// L931
      bool v631 = v629 >= v630;	// L932
      if (v631) {	// L933
        rdy = 1;	// L934
      }
      int32_t v632 = kk;	// L936
      int v633 = v632;	// L937
      uint8_t v634 = sb_v[v633];	// L938
      int32_t v635 = v634;	// L939
      bool v636 = v635 == 1;	// L940
      uint8_t v637 = sb_rtr[v633];	// L943
      int32_t v638 = v637;	// L944
      bool v639 = v638 == 0;	// L945
      uint8_t v640 = sb_dst[v633];	// L948
      int32_t v641 = v640;	// L949
      bool v642 = v641 < 12;	// L950
      bool v643 = v636 & v639;	// L951
      bool v644 = v643 & v642;	// L952
      if (v644) {	// L953
        int32_t v645 = s1;	// L954
        bool v646 = v645 < 12;	// L955
        int32_t v647 = kk;	// L956
        int v648 = v647;	// L957
        uint8_t v649 = sb_dst[v648];	// L958
        int32_t v650 = v649;	// L959
        int32_t v651 = v650 & 7;	// L960
        int32_t v652 = v645 & 7;	// L962
        bool v653 = v651 == v652;	// L963
        bool v654 = v646 & v653;	// L964
        if (v654) {	// L965
          int32_t v655 = rdy;	// L966
          bool v656 = v655 == 1;	// L967
          if (v656) {	// L968
            fwd_a = 1;	// L969
            int32_t v657 = kk;	// L970
            int v658 = v657;	// L971
            uint8_t v659 = sb_ix[v658];	// L972
            int32_t v660 = v659;	// L973
            fwd_a_ix = v660;	// L974
            raw_a = 0;	// L975
          } else {
            fwd_a = 0;	// L977
            raw_a = 1;	// L978
          }
        }
        int32_t v661 = binop;	// L981
        bool v662 = v661 == 1;	// L982
        int32_t v663 = s2;	// L983
        bool v664 = v663 < 12;	// L984
        int32_t v665 = kk;	// L985
        int v666 = v665;	// L986
        uint8_t v667 = sb_dst[v666];	// L987
        int32_t v668 = v667;	// L988
        int32_t v669 = v668 & 7;	// L989
        int32_t v670 = v663 & 7;	// L991
        bool v671 = v669 == v670;	// L992
        bool v672 = v662 & v664;	// L993
        bool v673 = v672 & v671;	// L994
        if (v673) {	// L995
          int32_t v674 = rdy;	// L996
          bool v675 = v674 == 1;	// L997
          if (v675) {	// L998
            fwd_b = 1;	// L999
            int32_t v676 = kk;	// L1000
            int v677 = v676;	// L1001
            uint8_t v678 = sb_ix[v677];	// L1002
            int32_t v679 = v678;	// L1003
            fwd_b_ix = v679;	// L1004
            raw_b = 0;	// L1005
          } else {
            fwd_b = 0;	// L1007
            raw_b = 1;	// L1008
          }
        }
      }
      int32_t v680 = kk;	// L1012
      int v681 = v680;	// L1013
      uint8_t v682 = sb_v[v681];	// L1014
      int32_t v683 = v682;	// L1015
      bool v684 = v683 == 1;	// L1016
      uint8_t v685 = sb_cmp[v681];	// L1019
      int32_t v686 = v685;	// L1020
      bool v687 = v686 == 1;	// L1021
      bool v688 = v684 & v687;	// L1022
      if (v688) {	// L1023
        cmp_busy = 1;	// L1024
      }
    }
    int32_t v689 = raw_a;	// L1027
    raw = v689;	// L1028
    int32_t v690 = binop;	// L1029
    bool v691 = v690 == 1;	// L1030
    int32_t v692 = raw_b;	// L1031
    bool v693 = v692 == 1;	// L1032
    bool v694 = v691 & v693;	// L1033
    if (v694) {	// L1034
      raw = 1;	// L1035
    }
    int32_t v695 = fwd_a;	// L1037
    bool v696 = v695 == 1;	// L1038
    if (v696) {	// L1039
      int32_t v697 = fwd_a_ix;	// L1040
      int v698 = v697;	// L1041
      int16_t v699 = resq[v698];	// L1042
      a = v699;	// L1043
      a_vld = 1;	// L1044
    }
    int32_t v700 = fwd_b;	// L1046
    bool v701 = v700 == 1;	// L1047
    if (v701) {	// L1048
      int32_t v702 = fwd_b_ix;	// L1049
      int v703 = v702;	// L1050
      int16_t v704 = resq[v703];	// L1051
      b = v704;	// L1052
      b_vld = 1;	// L1053
    }
    int32_t is_cond;	// L1055
    is_cond = 0;	// L1056
    int32_t v706 = op;	// L1057
    bool v707 = v706 >= 12;	// L1058
    ap_int<33> v708 = v706;	// L1060
    bool v709 = v708 <= 15;	// L1061
    bool v710 = v707 & v709;	// L1062
    if (v710) {	// L1063
      is_cond = 1;	// L1064
    }
    int32_t grant;	// L1066
    grant = 0;	// L1067
    int32_t v712 = pc;	// L1068
    bool v713 = v712 >= 0;	// L1069
    if (v713) {	// L1070
      grant = 1;	// L1071
    }
    int32_t v714 = pc;	// L1073
    bool v715 = v714 >= 0;	// L1074
    int32_t v716 = a_vld;	// L1075
    bool v717 = v716 == 0;	// L1076
    int32_t v718 = binop;	// L1077
    bool v719 = v718 == 1;	// L1078
    int32_t v720 = b_vld;	// L1079
    bool v721 = v720 == 0;	// L1080
    bool v722 = v719 & v721;	// L1081
    bool v723 = v717 | v722;	// L1082
    bool v724 = v715 & v723;	// L1083
    if (v724) {	// L1084
      grant = 0;	// L1085
    }
    int32_t v725 = pc;	// L1087
    bool v726 = v725 >= 0;	// L1088
    int32_t v727 = raw;	// L1089
    bool v728 = v727 == 1;	// L1090
    int32_t v729 = is_cond;	// L1091
    bool v730 = v729 == 1;	// L1092
    int32_t v731 = cmp_busy;	// L1093
    bool v732 = v731 == 1;	// L1094
    bool v733 = v730 & v732;	// L1095
    bool v734 = v728 | v733;	// L1096
    bool v735 = v726 & v734;	// L1097
    if (v735) {	// L1098
      grant = 0;	// L1099
    }
    int32_t v736 = retire_ok;	// L1101
    bool v737 = v736 == 0;	// L1102
    if (v737) {	// L1103
      grant = 0;	// L1104
    }
    int32_t v738 = grant;	// L1106
    bool v739 = v738 == 1;	// L1107
    if (v739) {	// L1108
      int8_t v740 = instr_cnt;	// L1109
      int32_t v741 = cfg_isz;	// L1110
      int32_t v742 = v740;	// L1111
      bool v743 = v742 == v741;	// L1112
      if (v743) {	// L1113
        instr_cnt = 0;	// L1114
        int8_t v744 = iter_cnt;	// L1115
        int32_t v745 = cfg_itsz;	// L1116
        ap_int<33> v746 = v745;	// L1117
        ap_int<33> v747 = v746 - 1;	// L1118
        ap_int<33> v748 = v744;	// L1119
        bool v749 = v748 == v747;	// L1120
        if (v749) {	// L1121
          fetch_en = 0;	// L1122
        } else {
          int8_t v750 = iter_cnt;	// L1124
          ap_int<33> v751 = v750;	// L1125
          ap_int<33> v752 = v751 + 1;	// L1126
          uint8_t v753 = v752;	// L1127
          iter_cnt = v753;	// L1128
        }
      } else {
        int8_t v754 = instr_cnt;	// L1131
        ap_int<33> v755 = v754;	// L1132
        ap_int<33> v756 = v755 + 1;	// L1133
        uint8_t v757 = v756;	// L1134
        instr_cnt = v757;	// L1135
      }
    }
    int32_t c1;	// L1138
    c1 = -1;	// L1139
    int32_t c2;	// L1140
    c2 = -1;	// L1141
    int32_t v760 = grant;	// L1142
    bool v761 = v760 == 1;	// L1143
    int32_t v762 = s1;	// L1144
    bool v763 = v762 >= 12;	// L1145
    bool v764 = v761 & v763;	// L1146
    if (v764) {	// L1147
      int32_t v765 = s1;	// L1148
      int32_t v766 = v765 & 3;	// L1149
      c1 = v766;	// L1150
    }
    int32_t v767 = grant;	// L1152
    bool v768 = v767 == 1;	// L1153
    int32_t v769 = s2;	// L1154
    bool v770 = v769 >= 12;	// L1155
    bool v771 = v768 & v770;	// L1156
    if (v771) {	// L1157
      int32_t v772 = s2;	// L1158
      int32_t v773 = v772 & 3;	// L1159
      c2 = v773;	// L1160
    }
    int32_t v774 = c1;	// L1162
    bool v775 = v774 >= 0;	// L1163
    if (v775) {	// L1164
      int32_t v776 = c1;	// L1165
      int v777 = v776;	// L1166
      int16_t v778 = hold_v[v777][1];	// L1167
      hold_v[v777][0] = v778;	// L1170
      int32_t v779 = c1;	// L1171
      int v780 = v779;	// L1172
      uint8_t v781 = hold_cnt[v780];	// L1173
      ap_int<33> v782 = v781;	// L1174
      ap_int<33> v783 = v782 - 1;	// L1175
      uint8_t v784 = v783;	// L1176
      hold_cnt[v780] = v784;	// L1179
    }
    int32_t v785 = c2;	// L1181
    bool v786 = v785 >= 0;	// L1182
    int32_t v787 = c1;	// L1184
    bool v788 = v785 != v787;	// L1185
    bool v789 = v786 & v788;	// L1186
    if (v789) {	// L1187
      int32_t v790 = c2;	// L1188
      int v791 = v790;	// L1189
      int16_t v792 = hold_v[v791][1];	// L1190
      hold_v[v791][0] = v792;	// L1193
      int32_t v793 = c2;	// L1194
      int v794 = v793;	// L1195
      uint8_t v795 = hold_cnt[v794];	// L1196
      ap_int<33> v796 = v795;	// L1197
      ap_int<33> v797 = v796 - 1;	// L1198
      uint8_t v798 = v797;	// L1199
      hold_cnt[v794] = v798;	// L1202
    }
    l_S_d_8_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1204
      sc_r[d4] = 0;	// L1205
    }
    int32_t v800 = c1;	// L1207
    bool v801 = v800 >= 0;	// L1208
    if (v801) {	// L1209
      int32_t v802 = c1;	// L1210
      int v803 = v802;	// L1211
      sc_r[v803] = 1;	// L1212
    }
    int32_t v804 = c2;	// L1214
    bool v805 = v804 >= 0;	// L1215
    int32_t v806 = c1;	// L1217
    bool v807 = v804 != v806;	// L1218
    bool v808 = v805 & v807;	// L1219
    if (v808) {	// L1220
      int32_t v809 = c2;	// L1221
      int v810 = v809;	// L1222
      sc_r[v810] = 1;	// L1223
    }
    int32_t v811 = grant;	// L1225
    bool v812 = v811 == 1;	// L1226
    int32_t v813 = s1;	// L1227
    bool v814 = v813 < 8;	// L1228
    int32_t v815 = dsmask;	// L1229
    int32_t v816 = v815 >> v813;	// L1231
    int32_t v817 = v816 & 1;	// L1232
    bool v818 = v817 == 1;	// L1233
    bool v819 = v812 & v814;	// L1234
    bool v820 = v819 & v818;	// L1235
    if (v820) {	// L1236
      int32_t v821 = s1;	// L1237
      int v822 = v821;	// L1238
      drf_full[v822] = 0;	// L1239
    }
    int32_t v823 = grant;	// L1241
    bool v824 = v823 == 1;	// L1242
    int32_t v825 = s2;	// L1243
    bool v826 = v825 < 8;	// L1244
    int32_t v827 = dsmask;	// L1245
    int32_t v828 = v827 >> v825;	// L1247
    int32_t v829 = v828 & 1;	// L1248
    bool v830 = v829 == 1;	// L1249
    bool v831 = v824 & v826;	// L1250
    bool v832 = v831 & v830;	// L1251
    if (v832) {	// L1252
      int32_t v833 = s2;	// L1253
      int v834 = v833;	// L1254
      drf_full[v834] = 0;	// L1255
    }
    int16_t res;	// L1257
    res = 0;	// L1258
    int32_t v836 = op;	// L1259
    bool v837 = v836 == 0;	// L1260
    if (v837) {	// L1261
      int16_t v838 = a;	// L1262
      int16_t v839 = b;	// L1263
      ap_int<17> v840 = v838;	// L1264
      ap_int<17> v841 = v839;	// L1265
      ap_int<17> v842 = v840 + v841;	// L1266
      int16_t v843 = v842;	// L1267
      res = v843;	// L1268
    } else {
      int32_t v844 = op;	// L1270
      bool v845 = v844 == 1;	// L1271
      if (v845) {	// L1272
        int16_t v846 = a;	// L1273
        int16_t v847 = b;	// L1274
        ap_int<17> v848 = v846;	// L1275
        ap_int<17> v849 = v847;	// L1276
        ap_int<17> v850 = v848 - v849;	// L1277
        int16_t v851 = v850;	// L1278
        res = v851;	// L1279
      } else {
        int32_t v852 = op;	// L1281
        bool v853 = v852 == 2;	// L1282
        if (v853) {	// L1283
          int16_t v854 = a;	// L1284
          int16_t v855 = b;	// L1285
          int32_t v856 = v854;	// L1286
          int32_t v857 = v855;	// L1287
          int32_t v858 = v856 * v857;	// L1288
          int16_t v859 = v858;	// L1289
          res = v859;	// L1290
        } else {
          int32_t v860 = op;	// L1292
          bool v861 = v860 == 8;	// L1293
          if (v861) {	// L1294
            int16_t v862 = a;	// L1295
            int16_t v863 = b;	// L1296
            bool v864 = v862 >= v863;	// L1297
            if (v864) {	// L1298
              res = 1;	// L1299
            } else {
              res = -1;	// L1301
            }
          } else {
            int32_t v865 = op;	// L1304
            bool v866 = v865 == 9;	// L1305
            if (v866) {	// L1306
              int16_t v867 = a;	// L1307
              int16_t v868 = b;	// L1308
              bool v869 = v867 < v868;	// L1309
              if (v869) {	// L1310
                res = 1;	// L1311
              } else {
                res = -1;	// L1313
              }
            } else {
              int16_t v870 = a;	// L1316
              res = v870;	// L1317
            }
          }
        }
      }
    }
    int32_t v871 = a_vld;	// L1323
    int32_t res_vld;	// L1324
    res_vld = v871;	// L1325
    int32_t v873 = op;	// L1326
    bool v874 = v873 == 0;	// L1327
    bool v875 = v873 == 1;	// L1329
    bool v876 = v873 == 2;	// L1331
    bool v877 = v873 == 8;	// L1333
    bool v878 = v873 == 9;	// L1335
    bool v879 = v874 | v875;	// L1336
    bool v880 = v879 | v876;	// L1337
    bool v881 = v880 | v877;	// L1338
    bool v882 = v881 | v878;	// L1339
    if (v882) {	// L1340
      int32_t v883 = a_vld;	// L1341
      int32_t v884 = b_vld;	// L1342
      int64_t v885 = v883;	// L1343
      int64_t v886 = v884;	// L1344
      int64_t v887 = v885 * v886;	// L1345
      int32_t v888 = v887;	// L1346
      res_vld = v888;	// L1347
    }
    int32_t v889 = grant;	// L1349
    bool v890 = v889 == 0;	// L1350
    if (v890) {	// L1351
      res_vld = 0;	// L1352
    }
    int32_t is_rtr;	// L1354
    is_rtr = 0;	// L1355
    int32_t v892 = op;	// L1356
    bool v893 = v892 >= 4;	// L1357
    ap_int<33> v894 = v892;	// L1359
    bool v895 = v894 <= 7;	// L1360
    bool v896 = v893 & v895;	// L1361
    if (v896) {	// L1362
      is_rtr = 1;	// L1363
    }
    int32_t v897 = retire_ok;	// L1365
    bool v898 = v897 == 1;	// L1366
    if (v898) {	// L1367
      l_S_k_9_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1368
        uint8_t v900 = sb_v[(k1 + 1)];	// L1369
        sb_v[k1] = v900;	// L1370
        uint8_t v901 = sb_dst[(k1 + 1)];	// L1371
        sb_dst[k1] = v901;	// L1372
        uint8_t v902 = sb_cmp[(k1 + 1)];	// L1373
        sb_cmp[k1] = v902;	// L1374
        uint8_t v903 = sb_rtr[(k1 + 1)];	// L1375
        sb_rtr[k1] = v903;	// L1376
        uint8_t v904 = sb_inj[(k1 + 1)];	// L1377
        sb_inj[k1] = v904;	// L1378
        uint8_t v905 = sb_dir[(k1 + 1)];	// L1379
        sb_dir[k1] = v905;	// L1380
        uint8_t v906 = sb_id[(k1 + 1)];	// L1381
        sb_id[k1] = v906;	// L1382
        uint8_t v907 = sb_rvld[(k1 + 1)];	// L1383
        sb_rvld[k1] = v907;	// L1384
        uint8_t v908 = sb_ix[(k1 + 1)];	// L1385
        sb_ix[k1] = v908;	// L1386
        uint8_t v909 = sb_long[(k1 + 1)];	// L1387
        sb_long[k1] = v909;	// L1388
      }
      sb_v[4] = 0;	// L1390
    }
    int32_t v910 = grant;	// L1392
    bool v911 = v910 == 1;	// L1393
    if (v911) {	// L1394
      int16_t v912 = res;	// L1395
      int8_t v913 = resq_wr;	// L1396
      int v914 = v913;	// L1397
      resq[v914] = v912;	// L1398
      int32_t cq;	// L1399
      cq = 0;	// L1400
      int32_t v916 = op;	// L1401
      bool v917 = v916 == 8;	// L1402
      if (v917) {	// L1403
        int16_t v918 = a;	// L1404
        int16_t v919 = b;	// L1405
        bool v920 = v918 >= v919;	// L1406
        if (v920) {	// L1407
          cq = 1;	// L1408
        }
      }
      int32_t v921 = op;	// L1411
      bool v922 = v921 == 9;	// L1412
      if (v922) {	// L1413
        int16_t v923 = a;	// L1414
        int16_t v924 = b;	// L1415
        bool v925 = v923 < v924;	// L1416
        if (v925) {	// L1417
          cq = 1;	// L1418
        }
      }
      int32_t v926 = cq;	// L1421
      uint8_t v927 = v926;	// L1422
      int8_t v928 = resq_wr;	// L1423
      int v929 = v928;	// L1424
      cmpq[v929] = v927;	// L1425
      sb_v[4] = 1;	// L1426
      int32_t v930 = dst;	// L1427
      uint8_t v931 = v930;	// L1428
      sb_dst[4] = v931;	// L1429
      int8_t v932 = resq_wr;	// L1430
      sb_ix[4] = v932;	// L1431
      int32_t v933 = binop;	// L1432
      uint8_t v934 = v933;	// L1433
      sb_long[4] = v934;	// L1434
      sb_cmp[4] = 0;	// L1435
      int32_t v935 = op;	// L1436
      bool v936 = v935 == 8;	// L1437
      bool v937 = v935 == 9;	// L1439
      bool v938 = v936 | v937;	// L1440
      if (v938) {	// L1441
        sb_cmp[4] = 1;	// L1442
      }
      int32_t v939 = is_rtr;	// L1444
      int32_t rtrf;	// L1445
      rtrf = v939;	// L1446
      int32_t v941 = is_cond;	// L1447
      bool v942 = v941 == 1;	// L1448
      if (v942) {	// L1449
        rtrf = 1;	// L1450
      }
      int32_t v943 = rtrf;	// L1452
      uint8_t v944 = v943;	// L1453
      sb_rtr[4] = v944;	// L1454
      int32_t v945 = is_rtr;	// L1455
      int32_t inj;	// L1456
      inj = v945;	// L1457
      int32_t v947 = is_cond;	// L1458
      bool v948 = v947 == 1;	// L1459
      int8_t v949 = condition_reg;	// L1460
      int32_t v950 = v949;	// L1461
      bool v951 = v950 == 1;	// L1462
      bool v952 = v948 & v951;	// L1463
      if (v952) {	// L1464
        inj = 1;	// L1465
      }
      int32_t v953 = inj;	// L1467
      uint8_t v954 = v953;	// L1468
      sb_inj[4] = v954;	// L1469
      int32_t v955 = op;	// L1470
      int32_t v956 = v955 & 3;	// L1471
      uint8_t v957 = v956;	// L1472
      sb_dir[4] = v957;	// L1473
      int32_t v958 = s2;	// L1474
      uint8_t v959 = v958;	// L1475
      sb_id[4] = v959;	// L1476
      int32_t v960 = res_vld;	// L1477
      uint8_t v961 = v960;	// L1478
      sb_rvld[4] = v961;	// L1479
      int8_t v962 = resq_wr;	// L1480
      ap_int<33> v963 = v962;	// L1481
      ap_int<33> v964 = v963 + 1;	// L1482
      ap_int<33> v965 = v964 & 7;	// L1483
      uint8_t v966 = v965;	// L1484
      resq_wr = v966;	// L1485
    }
    txn_r = 0;	// L1487
    txs_r = 0;	// L1488
    txw_r = 0;	// L1489
    txe_r = 0;	// L1490
    int32_t v967 = txp_v[0];	// L1491
    bool v968 = v967 == 1;	// L1492
    int32_t v969 = scred[0];	// L1493
    bool v970 = v969 > 0;	// L1494
    bool v971 = v968 & v970;	// L1495
    if (v971) {	// L1496
      ap_uint<17> twn;	// L1497
      twn = 0;	// L1498
      ap_int<17> v973 = twn;	// L1499
      ap_int<17> v974;
      ap_int<17> v974_tmp = v973;
      v974_tmp[0] = 1;      v974 = v974_tmp;	// L1500
      twn = v974;	// L1501
      int16_t v975 = txp_d[0];	// L1502
      ap_int<17> v976 = twn;	// L1503
      ap_int<17> v977;
      ap_int<17> v977_tmp = v976;
      v977_tmp(16, 1) = v975;
      v977 = v977_tmp;	// L1504
      twn = v977;	// L1505
      ap_int<17> v978 = twn;	// L1506
      txn_r = v978;	// L1507
      txp_v[0] = 0;	// L1508
      int32_t v979 = scred[0];	// L1509
      ap_int<33> v980 = v979;	// L1510
      ap_int<33> v981 = v980 - 1;	// L1511
      int32_t v982 = v981;	// L1512
      scred[0] = v982;	// L1513
    }
    int32_t v983 = txp_v[1];	// L1515
    bool v984 = v983 == 1;	// L1516
    int32_t v985 = scred[1];	// L1517
    bool v986 = v985 > 0;	// L1518
    bool v987 = v984 & v986;	// L1519
    if (v987) {	// L1520
      ap_uint<17> tws;	// L1521
      tws = 0;	// L1522
      ap_int<17> v989 = tws;	// L1523
      ap_int<17> v990;
      ap_int<17> v990_tmp = v989;
      v990_tmp[0] = 1;      v990 = v990_tmp;	// L1524
      tws = v990;	// L1525
      int16_t v991 = txp_d[1];	// L1526
      ap_int<17> v992 = tws;	// L1527
      ap_int<17> v993;
      ap_int<17> v993_tmp = v992;
      v993_tmp(16, 1) = v991;
      v993 = v993_tmp;	// L1528
      tws = v993;	// L1529
      ap_int<17> v994 = tws;	// L1530
      txs_r = v994;	// L1531
      txp_v[1] = 0;	// L1532
      int32_t v995 = scred[1];	// L1533
      ap_int<33> v996 = v995;	// L1534
      ap_int<33> v997 = v996 - 1;	// L1535
      int32_t v998 = v997;	// L1536
      scred[1] = v998;	// L1537
    }
    int32_t v999 = txp_v[2];	// L1539
    bool v1000 = v999 == 1;	// L1540
    int32_t v1001 = scred[2];	// L1541
    bool v1002 = v1001 > 0;	// L1542
    bool v1003 = v1000 & v1002;	// L1543
    if (v1003) {	// L1544
      ap_uint<17> tww;	// L1545
      tww = 0;	// L1546
      ap_int<17> v1005 = tww;	// L1547
      ap_int<17> v1006;
      ap_int<17> v1006_tmp = v1005;
      v1006_tmp[0] = 1;      v1006 = v1006_tmp;	// L1548
      tww = v1006;	// L1549
      int16_t v1007 = txp_d[2];	// L1550
      ap_int<17> v1008 = tww;	// L1551
      ap_int<17> v1009;
      ap_int<17> v1009_tmp = v1008;
      v1009_tmp(16, 1) = v1007;
      v1009 = v1009_tmp;	// L1552
      tww = v1009;	// L1553
      ap_int<17> v1010 = tww;	// L1554
      txw_r = v1010;	// L1555
      txp_v[2] = 0;	// L1556
      int32_t v1011 = scred[2];	// L1557
      ap_int<33> v1012 = v1011;	// L1558
      ap_int<33> v1013 = v1012 - 1;	// L1559
      int32_t v1014 = v1013;	// L1560
      scred[2] = v1014;	// L1561
    }
    int32_t v1015 = txp_v[3];	// L1563
    bool v1016 = v1015 == 1;	// L1564
    int32_t v1017 = scred[3];	// L1565
    bool v1018 = v1017 > 0;	// L1566
    bool v1019 = v1016 & v1018;	// L1567
    if (v1019) {	// L1568
      ap_uint<17> twe;	// L1569
      twe = 0;	// L1570
      ap_int<17> v1021 = twe;	// L1571
      ap_int<17> v1022;
      ap_int<17> v1022_tmp = v1021;
      v1022_tmp[0] = 1;      v1022 = v1022_tmp;	// L1572
      twe = v1022;	// L1573
      int16_t v1023 = txp_d[3];	// L1574
      ap_int<17> v1024 = twe;	// L1575
      ap_int<17> v1025;
      ap_int<17> v1025_tmp = v1024;
      v1025_tmp(16, 1) = v1023;
      v1025 = v1025_tmp;	// L1576
      twe = v1025;	// L1577
      ap_int<17> v1026 = twe;	// L1578
      txe_r = v1026;	// L1579
      txp_v[3] = 0;	// L1580
      int32_t v1027 = scred[3];	// L1581
      ap_int<33> v1028 = v1027;	// L1582
      ap_int<33> v1029 = v1028 - 1;	// L1583
      int32_t v1030 = v1029;	// L1584
      scred[3] = v1030;	// L1585
    }
    int32_t v1031 = crv_vld;	// L1587
    bool v1032 = v1031 == 1;	// L1588
    if (v1032) {	// L1589
      int32_t v1033 = crv_mode;	// L1590
      bool v1034 = v1033 == 1;	// L1591
      if (v1034) {	// L1592
        int32_t v1035 = crv_addr;	// L1593
        int32_t v1036 = v1035 >> 3;	// L1594
        int32_t v1037 = v1036 & 1;	// L1595
        bool v1038 = v1037 == 1;	// L1596
        if (v1038) {	// L1597
          int32_t v1039 = crv_raw;	// L1598
          int32_t v1040 = crv_addr;	// L1599
          int32_t v1041 = v1040 & 7;	// L1600
          int v1042 = v1041;	// L1601
          irf[v1042] = v1039;	// L1602
        } else {
          int32_t v1043 = crv_addr;	// L1604
          bool v1044 = v1043 == 0;	// L1605
          if (v1044) {	// L1606
            int32_t v1045 = crv_raw;	// L1607
            int32_t v1046 = v1045 & 255;	// L1608
            dsmask = v1046;	// L1609
            int32_t v1047 = crv_raw;	// L1610
            int32_t v1048 = v1047 >> 8;	// L1611
            int32_t v1049 = v1048 & 7;	// L1612
            cfg_isz = v1049;	// L1613
            int32_t v1050 = crv_raw;	// L1614
            int32_t v1051 = v1050 >> 15;	// L1615
            int32_t v1052 = v1051 & 1;	// L1616
            bool v1053 = v1052 == 1;	// L1617
            if (v1053) {	// L1618
              fetch_en = 1;	// L1619
              instr_cnt = 0;	// L1620
              iter_cnt = 0;	// L1621
            }
          } else {
            int32_t v1054 = crv_addr;	// L1624
            bool v1055 = v1054 == 1;	// L1625
            if (v1055) {	// L1626
              int32_t v1056 = crv_raw;	// L1627
              int32_t v1057 = v1056 & 255;	// L1628
              cfg_itsz = v1057;	// L1629
            }
          }
        }
      } else {
        int32_t v1058 = crv_addr;	// L1634
        int32_t v1059 = v1058 >> 2;	// L1635
        int32_t v1060 = v1059 & 3;	// L1636
        bool v1061 = v1060 == 3;	// L1637
        if (v1061) {	// L1638
          int32_t v1062 = crv_addr;	// L1639
          int32_t v1063 = v1062 & 3;	// L1640
          int v1064 = v1063;	// L1641
          txp_v[v1064] = 1;	// L1642
          int16_t v1065 = crv_data;	// L1643
          int32_t v1066 = crv_addr;	// L1644
          int32_t v1067 = v1066 & 3;	// L1645
          int v1068 = v1067;	// L1646
          txp_d[v1068] = v1065;	// L1647
          int32_t v1069 = crv_addr;	// L1648
          int32_t v1070 = v1069 & 3;	// L1649
          int v1071 = v1070;	// L1650
          txp_r[v1071] = 1;	// L1651
        } else {
          int32_t v1072 = crv_addr;	// L1653
          bool v1073 = v1072 < 8;	// L1654
          int32_t v1074 = dsmask;	// L1655
          int32_t v1075 = v1074 >> v1072;	// L1657
          int32_t v1076 = v1075 & 1;	// L1658
          bool v1077 = v1076 == 1;	// L1659
          bool v1078 = v1073 & v1077;	// L1660
          if (v1078) {	// L1661
            int32_t v1079 = crv_addr;	// L1662
            int v1080 = v1079;	// L1663
            int32_t v1081 = drf_full[v1080];	// L1664
            bool v1082 = v1081 == 0;	// L1665
            if (v1082) {	// L1666
              int16_t v1083 = crv_data;	// L1667
              int32_t v1084 = crv_addr;	// L1668
              int v1085 = v1084;	// L1669
              drf[v1085] = v1083;	// L1670
              int32_t v1086 = crv_addr;	// L1671
              int v1087 = v1086;	// L1672
              drf_full[v1087] = 1;	// L1673
            }
          } else {
            int16_t v1088 = crv_data;	// L1676
            int32_t v1089 = crv_addr;	// L1677
            int v1090 = v1089;	// L1678
            drf[v1090] = v1088;	// L1679
            int32_t v1091 = crv_addr;	// L1680
            int v1092 = v1091;	// L1681
            drf_full[v1092] = 1;	// L1682
          }
        }
      }
    }
    ap_int<26> v1093 = oe_r;	// L1687
    v1.write(v1093);	// L1688
    ap_int<26> v1094 = ow_r;	// L1689
    v2.write(v1094);	// L1690
    ap_int<26> v1095 = os_r;	// L1691
    v3.write(v1095);	// L1692
    ap_int<26> v1096 = on_r;	// L1693
    v4.write(v1096);	// L1694
    ap_int<17> v1097 = txe_r;	// L1695
    v5.write(v1097);	// L1696
    ap_int<17> v1098 = txw_r;	// L1697
    v6.write(v1098);	// L1698
    ap_int<17> v1099 = txs_r;	// L1699
    v7.write(v1099);	// L1700
    ap_int<17> v1100 = txn_r;	// L1701
    v8.write(v1100);	// L1702
    int8_t v1101 = cre_r;	// L1703
    v9.write(v1101);	// L1704
    int8_t v1102 = crw_r;	// L1705
    v10.write(v1102);	// L1706
    int8_t v1103 = crs_r;	// L1707
    v11.write(v1103);	// L1708
    int8_t v1104 = crn_r;	// L1709
    v12.write(v1104);	// L1710
    int32_t v1105 = sc_r[0];	// L1711
    v15.write(v1105);	// L1712
    int32_t v1106 = sc_r[1];	// L1713
    v16.write(v1106);	// L1714
    int32_t v1107 = sc_r[2];	// L1715
    v13.write(v1107);	// L1716
    int32_t v1108 = sc_r[3];	// L1717
    v14.write(v1108);	// L1718
  }
}

void drv_w_0(
  int16_t v1109[1][2000],
  int32_t v1110[1][2000],
  int32_t v1111[1][1],
  hls::stream< ap_uint<17> >& v1112,
  hls::stream< int32_t >& v1113
) {
  #pragma HLS array_partition variable=v1109 complete dim=1
  #pragma HLS array_partition variable=v1110 complete dim=1	// L1722
  int32_t dcred[1];	// L1734
  for (int v1115 = 0; v1115 < 1; v1115++) {	// L1735
    dcred[v1115] = 0;	// L1735
  }
  int32_t rp[1];	// L1736
  for (int v1117 = 0; v1117 < 1; v1117++) {	// L1737
    rp[v1117] = 0;	// L1737
  }
  int32_t wcnt[1];	// L1738
  for (int v1119 = 0; v1119 < 1; v1119++) {	// L1739
    wcnt[v1119] = 0;	// L1739
  }
  int16_t win_d[1][4];	// L1740
  for (int v1121 = 0; v1121 < 1; v1121++) {	// L1741
    for (int v1122 = 0; v1122 < 4; v1122++) {	// L1741
      win_d[v1121][v1122] = 0;	// L1741
    }
  }
  int32_t win_f[1][4];	// L1742
  for (int v1124 = 0; v1124 < 1; v1124++) {	// L1743
    for (int v1125 = 0; v1125 < 4; v1125++) {	// L1743
      win_f[v1124][v1125] = 0;	// L1743
    }
  }
  int32_t win_s[1][4];	// L1744
  for (int v1127 = 0; v1127 < 1; v1127++) {	// L1745
    for (int v1128 = 0; v1128 < 4; v1128++) {	// L1745
      win_s[v1127][v1128] = 0;	// L1745
    }
  }
  ap_uint<17> zw;	// L1746
  zw = 0;	// L1747
  int32_t v1130 = v1111[0][0];	// L1748
  ap_int<33> v1131 = v1130;	// L1749
  ap_int<33> v1132 = v1131 - 1;	// L1750
  int v1133 = v1132;	// L1751
  for (int v1134 = 0; v1134 < v1133; v1134 += 1) {	// L1752
    ap_int<17> v1135 = zw;	// L1753
    v1112.write(v1135);	// L1754
  }
  l_S__pf_1__pf: for (int _pf = 0; _pf < 2; _pf++) {	// L1756
    int32_t v1137 = rp[0];	// L1757
    bool v1138 = v1137 < 2000;	// L1758
    if (v1138) {	// L1759
      int32_t v1139 = rp[0];	// L1760
      int v1140 = v1139;	// L1761
      int16_t v1141 = v1109[0][v1140];	// L1762
      int32_t v1142 = wcnt[0];	// L1763
      int v1143 = v1142;	// L1764
      win_d[0][v1143] = v1141;	// L1765
      int32_t v1144 = rp[0];	// L1766
      int v1145 = v1144;	// L1767
      int32_t v1146 = v1110[0][v1145];	// L1768
      int32_t v1147 = wcnt[0];	// L1769
      int v1148 = v1147;	// L1770
      win_f[0][v1148] = v1146;	// L1771
      int32_t v1149 = rp[0];	// L1772
      int32_t v1150 = wcnt[0];	// L1773
      int v1151 = v1150;	// L1774
      win_s[0][v1151] = v1149;	// L1775
      int32_t v1152 = wcnt[0];	// L1776
      ap_int<33> v1153 = v1152;	// L1777
      ap_int<33> v1154 = v1153 + 1;	// L1778
      int32_t v1155 = v1154;	// L1779
      wcnt[0] = v1155;	// L1780
      int32_t v1156 = rp[0];	// L1781
      ap_int<33> v1157 = v1156;	// L1782
      ap_int<33> v1158 = v1157 + 1;	// L1783
      int32_t v1159 = v1158;	// L1784
      rp[0] = v1159;	// L1785
    }
  }
  l_S_t_2_t1: for (int t1 = 0; t1 < 2000; t1++) {	// L1788
  #pragma HLS pipeline II=1
    int32_t v1161 = v1113.read();	// L1789
    int32_t cin;	// L1790
    cin = v1161;	// L1791
    int32_t v1163 = cin;	// L1792
    int32_t v1164 = dcred[0];	// L1793
    ap_int<33> v1165 = v1164;	// L1794
    ap_int<33> v1166 = v1163;	// L1795
    ap_int<33> v1167 = v1165 + v1166;	// L1796
    int32_t v1168 = v1167;	// L1797
    dcred[0] = v1168;	// L1798
    ap_uint<17> w;	// L1799
    w = 0;	// L1800
    int32_t popd;	// L1801
    popd = 0;	// L1802
    int32_t v1171 = wcnt[0];	// L1803
    bool v1172 = v1171 > 0;	// L1804
    int32_t v1173 = win_s[0][0];	// L1805
    ap_int<33> v1174 = t1;	// L1806
    ap_int<33> v1175 = v1173;	// L1807
    bool v1176 = v1174 >= v1175;	// L1808
    bool v1177 = v1172 & v1176;	// L1809
    if (v1177) {	// L1810
      int32_t v1178 = win_f[0][0];	// L1811
      bool v1179 = v1178 == 0;	// L1812
      if (v1179) {	// L1813
        popd = 1;	// L1814
      } else {
        int32_t v1180 = dcred[0];	// L1816
        bool v1181 = v1180 > 0;	// L1817
        if (v1181) {	// L1818
          ap_int<17> v1182 = w;	// L1819
          ap_int<17> v1183;
          ap_int<17> v1183_tmp = v1182;
          v1183_tmp[0] = 1;          v1183 = v1183_tmp;	// L1820
          w = v1183;	// L1821
          int16_t v1184 = win_d[0][0];	// L1822
          ap_int<17> v1185 = w;	// L1823
          ap_int<17> v1186;
          ap_int<17> v1186_tmp = v1185;
          v1186_tmp(16, 1) = v1184;
          v1186 = v1186_tmp;	// L1824
          w = v1186;	// L1825
          int32_t v1187 = dcred[0];	// L1826
          ap_int<33> v1188 = v1187;	// L1827
          ap_int<33> v1189 = v1188 - 1;	// L1828
          int32_t v1190 = v1189;	// L1829
          dcred[0] = v1190;	// L1830
          popd = 1;	// L1831
        }
      }
    }
    int32_t v1191 = popd;	// L1835
    bool v1192 = v1191 == 1;	// L1836
    if (v1192) {	// L1837
      l_S_sft_2_sft1: for (int sft1 = 0; sft1 < 3; sft1++) {	// L1838
        int16_t v1194 = win_d[0][(sft1 + 1)];	// L1839
        win_d[0][sft1] = v1194;	// L1840
        int32_t v1195 = win_f[0][(sft1 + 1)];	// L1841
        win_f[0][sft1] = v1195;	// L1842
        int32_t v1196 = win_s[0][(sft1 + 1)];	// L1843
        win_s[0][sft1] = v1196;	// L1844
      }
      int32_t v1197 = wcnt[0];	// L1846
      ap_int<33> v1198 = v1197;	// L1847
      ap_int<33> v1199 = v1198 - 1;	// L1848
      int32_t v1200 = v1199;	// L1849
      wcnt[0] = v1200;	// L1850
    }
    int32_t v1201 = rp[0];	// L1852
    bool v1202 = v1201 < 2000;	// L1853
    int32_t v1203 = wcnt[0];	// L1854
    bool v1204 = v1203 < 4;	// L1855
    bool v1205 = v1202 & v1204;	// L1856
    if (v1205) {	// L1857
      int32_t v1206 = rp[0];	// L1858
      int v1207 = v1206;	// L1859
      int16_t v1208 = v1109[0][v1207];	// L1860
      int32_t v1209 = wcnt[0];	// L1861
      int v1210 = v1209;	// L1862
      win_d[0][v1210] = v1208;	// L1863
      int32_t v1211 = rp[0];	// L1864
      int v1212 = v1211;	// L1865
      int32_t v1213 = v1110[0][v1212];	// L1866
      int32_t v1214 = wcnt[0];	// L1867
      int v1215 = v1214;	// L1868
      win_f[0][v1215] = v1213;	// L1869
      int32_t v1216 = rp[0];	// L1870
      int32_t v1217 = wcnt[0];	// L1871
      int v1218 = v1217;	// L1872
      win_s[0][v1218] = v1216;	// L1873
      int32_t v1219 = wcnt[0];	// L1874
      ap_int<33> v1220 = v1219;	// L1875
      ap_int<33> v1221 = v1220 + 1;	// L1876
      int32_t v1222 = v1221;	// L1877
      wcnt[0] = v1222;	// L1878
      int32_t v1223 = rp[0];	// L1879
      ap_int<33> v1224 = v1223;	// L1880
      ap_int<33> v1225 = v1224 + 1;	// L1881
      int32_t v1226 = v1225;	// L1882
      rp[0] = v1226;	// L1883
    }
    ap_int<17> v1227 = w;	// L1885
    v1112.write(v1227);	// L1886
  }
}

void drv_e_0(
  int16_t v1228[1][2000],
  int32_t v1229[1][2000],
  int32_t v1230[1][1],
  hls::stream< ap_uint<17> >& v1231,
  hls::stream< int32_t >& v1232
) {
  #pragma HLS array_partition variable=v1228 complete dim=1
  #pragma HLS array_partition variable=v1229 complete dim=1	// L1890
  int32_t dcred1[1];	// L1902
  for (int v1234 = 0; v1234 < 1; v1234++) {	// L1903
    dcred1[v1234] = 0;	// L1903
  }
  int32_t rp1[1];	// L1904
  for (int v1236 = 0; v1236 < 1; v1236++) {	// L1905
    rp1[v1236] = 0;	// L1905
  }
  int32_t wcnt1[1];	// L1906
  for (int v1238 = 0; v1238 < 1; v1238++) {	// L1907
    wcnt1[v1238] = 0;	// L1907
  }
  int16_t win_d1[1][4];	// L1908
  for (int v1240 = 0; v1240 < 1; v1240++) {	// L1909
    for (int v1241 = 0; v1241 < 4; v1241++) {	// L1909
      win_d1[v1240][v1241] = 0;	// L1909
    }
  }
  int32_t win_f1[1][4];	// L1910
  for (int v1243 = 0; v1243 < 1; v1243++) {	// L1911
    for (int v1244 = 0; v1244 < 4; v1244++) {	// L1911
      win_f1[v1243][v1244] = 0;	// L1911
    }
  }
  int32_t win_s1[1][4];	// L1912
  for (int v1246 = 0; v1246 < 1; v1246++) {	// L1913
    for (int v1247 = 0; v1247 < 4; v1247++) {	// L1913
      win_s1[v1246][v1247] = 0;	// L1913
    }
  }
  ap_uint<17> zw1;	// L1914
  zw1 = 0;	// L1915
  int32_t v1249 = v1230[0][0];	// L1916
  ap_int<33> v1250 = v1249;	// L1917
  ap_int<33> v1251 = v1250 - 1;	// L1918
  int v1252 = v1251;	// L1919
  for (int v1253 = 0; v1253 < v1252; v1253 += 1) {	// L1920
    ap_int<17> v1254 = zw1;	// L1921
    v1231.write(v1254);	// L1922
  }
  l_S__pf_1__pf1: for (int _pf1 = 0; _pf1 < 2; _pf1++) {	// L1924
    int32_t v1256 = rp1[0];	// L1925
    bool v1257 = v1256 < 2000;	// L1926
    if (v1257) {	// L1927
      int32_t v1258 = rp1[0];	// L1928
      int v1259 = v1258;	// L1929
      int16_t v1260 = v1228[0][v1259];	// L1930
      int32_t v1261 = wcnt1[0];	// L1931
      int v1262 = v1261;	// L1932
      win_d1[0][v1262] = v1260;	// L1933
      int32_t v1263 = rp1[0];	// L1934
      int v1264 = v1263;	// L1935
      int32_t v1265 = v1229[0][v1264];	// L1936
      int32_t v1266 = wcnt1[0];	// L1937
      int v1267 = v1266;	// L1938
      win_f1[0][v1267] = v1265;	// L1939
      int32_t v1268 = rp1[0];	// L1940
      int32_t v1269 = wcnt1[0];	// L1941
      int v1270 = v1269;	// L1942
      win_s1[0][v1270] = v1268;	// L1943
      int32_t v1271 = wcnt1[0];	// L1944
      ap_int<33> v1272 = v1271;	// L1945
      ap_int<33> v1273 = v1272 + 1;	// L1946
      int32_t v1274 = v1273;	// L1947
      wcnt1[0] = v1274;	// L1948
      int32_t v1275 = rp1[0];	// L1949
      ap_int<33> v1276 = v1275;	// L1950
      ap_int<33> v1277 = v1276 + 1;	// L1951
      int32_t v1278 = v1277;	// L1952
      rp1[0] = v1278;	// L1953
    }
  }
  l_S_t_2_t2: for (int t2 = 0; t2 < 2000; t2++) {	// L1956
  #pragma HLS pipeline II=1
    int32_t v1280 = v1232.read();	// L1957
    int32_t cin1;	// L1958
    cin1 = v1280;	// L1959
    int32_t v1282 = cin1;	// L1960
    int32_t v1283 = dcred1[0];	// L1961
    ap_int<33> v1284 = v1283;	// L1962
    ap_int<33> v1285 = v1282;	// L1963
    ap_int<33> v1286 = v1284 + v1285;	// L1964
    int32_t v1287 = v1286;	// L1965
    dcred1[0] = v1287;	// L1966
    ap_uint<17> w1;	// L1967
    w1 = 0;	// L1968
    int32_t popd1;	// L1969
    popd1 = 0;	// L1970
    int32_t v1290 = wcnt1[0];	// L1971
    bool v1291 = v1290 > 0;	// L1972
    int32_t v1292 = win_s1[0][0];	// L1973
    ap_int<33> v1293 = t2;	// L1974
    ap_int<33> v1294 = v1292;	// L1975
    bool v1295 = v1293 >= v1294;	// L1976
    bool v1296 = v1291 & v1295;	// L1977
    if (v1296) {	// L1978
      int32_t v1297 = win_f1[0][0];	// L1979
      bool v1298 = v1297 == 0;	// L1980
      if (v1298) {	// L1981
        popd1 = 1;	// L1982
      } else {
        int32_t v1299 = dcred1[0];	// L1984
        bool v1300 = v1299 > 0;	// L1985
        if (v1300) {	// L1986
          ap_int<17> v1301 = w1;	// L1987
          ap_int<17> v1302;
          ap_int<17> v1302_tmp = v1301;
          v1302_tmp[0] = 1;          v1302 = v1302_tmp;	// L1988
          w1 = v1302;	// L1989
          int16_t v1303 = win_d1[0][0];	// L1990
          ap_int<17> v1304 = w1;	// L1991
          ap_int<17> v1305;
          ap_int<17> v1305_tmp = v1304;
          v1305_tmp(16, 1) = v1303;
          v1305 = v1305_tmp;	// L1992
          w1 = v1305;	// L1993
          int32_t v1306 = dcred1[0];	// L1994
          ap_int<33> v1307 = v1306;	// L1995
          ap_int<33> v1308 = v1307 - 1;	// L1996
          int32_t v1309 = v1308;	// L1997
          dcred1[0] = v1309;	// L1998
          popd1 = 1;	// L1999
        }
      }
    }
    int32_t v1310 = popd1;	// L2003
    bool v1311 = v1310 == 1;	// L2004
    if (v1311) {	// L2005
      l_S_sft_2_sft2: for (int sft2 = 0; sft2 < 3; sft2++) {	// L2006
        int16_t v1313 = win_d1[0][(sft2 + 1)];	// L2007
        win_d1[0][sft2] = v1313;	// L2008
        int32_t v1314 = win_f1[0][(sft2 + 1)];	// L2009
        win_f1[0][sft2] = v1314;	// L2010
        int32_t v1315 = win_s1[0][(sft2 + 1)];	// L2011
        win_s1[0][sft2] = v1315;	// L2012
      }
      int32_t v1316 = wcnt1[0];	// L2014
      ap_int<33> v1317 = v1316;	// L2015
      ap_int<33> v1318 = v1317 - 1;	// L2016
      int32_t v1319 = v1318;	// L2017
      wcnt1[0] = v1319;	// L2018
    }
    int32_t v1320 = rp1[0];	// L2020
    bool v1321 = v1320 < 2000;	// L2021
    int32_t v1322 = wcnt1[0];	// L2022
    bool v1323 = v1322 < 4;	// L2023
    bool v1324 = v1321 & v1323;	// L2024
    if (v1324) {	// L2025
      int32_t v1325 = rp1[0];	// L2026
      int v1326 = v1325;	// L2027
      int16_t v1327 = v1228[0][v1326];	// L2028
      int32_t v1328 = wcnt1[0];	// L2029
      int v1329 = v1328;	// L2030
      win_d1[0][v1329] = v1327;	// L2031
      int32_t v1330 = rp1[0];	// L2032
      int v1331 = v1330;	// L2033
      int32_t v1332 = v1229[0][v1331];	// L2034
      int32_t v1333 = wcnt1[0];	// L2035
      int v1334 = v1333;	// L2036
      win_f1[0][v1334] = v1332;	// L2037
      int32_t v1335 = rp1[0];	// L2038
      int32_t v1336 = wcnt1[0];	// L2039
      int v1337 = v1336;	// L2040
      win_s1[0][v1337] = v1335;	// L2041
      int32_t v1338 = wcnt1[0];	// L2042
      ap_int<33> v1339 = v1338;	// L2043
      ap_int<33> v1340 = v1339 + 1;	// L2044
      int32_t v1341 = v1340;	// L2045
      wcnt1[0] = v1341;	// L2046
      int32_t v1342 = rp1[0];	// L2047
      ap_int<33> v1343 = v1342;	// L2048
      ap_int<33> v1344 = v1343 + 1;	// L2049
      int32_t v1345 = v1344;	// L2050
      rp1[0] = v1345;	// L2051
    }
    ap_int<17> v1346 = w1;	// L2053
    v1231.write(v1346);	// L2054
  }
}

void drv_n_0(
  int16_t v1347[1][2000],
  int32_t v1348[1][2000],
  int32_t v1349[1][1],
  hls::stream< ap_uint<17> >& v1350,
  hls::stream< int32_t >& v1351
) {
  #pragma HLS array_partition variable=v1347 complete dim=1
  #pragma HLS array_partition variable=v1348 complete dim=1	// L2058
  int32_t dcred2[1];	// L2070
  for (int v1353 = 0; v1353 < 1; v1353++) {	// L2071
    dcred2[v1353] = 0;	// L2071
  }
  int32_t rp2[1];	// L2072
  for (int v1355 = 0; v1355 < 1; v1355++) {	// L2073
    rp2[v1355] = 0;	// L2073
  }
  int32_t wcnt2[1];	// L2074
  for (int v1357 = 0; v1357 < 1; v1357++) {	// L2075
    wcnt2[v1357] = 0;	// L2075
  }
  int16_t win_d2[1][4];	// L2076
  for (int v1359 = 0; v1359 < 1; v1359++) {	// L2077
    for (int v1360 = 0; v1360 < 4; v1360++) {	// L2077
      win_d2[v1359][v1360] = 0;	// L2077
    }
  }
  int32_t win_f2[1][4];	// L2078
  for (int v1362 = 0; v1362 < 1; v1362++) {	// L2079
    for (int v1363 = 0; v1363 < 4; v1363++) {	// L2079
      win_f2[v1362][v1363] = 0;	// L2079
    }
  }
  int32_t win_s2[1][4];	// L2080
  for (int v1365 = 0; v1365 < 1; v1365++) {	// L2081
    for (int v1366 = 0; v1366 < 4; v1366++) {	// L2081
      win_s2[v1365][v1366] = 0;	// L2081
    }
  }
  ap_uint<17> zw2;	// L2082
  zw2 = 0;	// L2083
  int32_t v1368 = v1349[0][0];	// L2084
  ap_int<33> v1369 = v1368;	// L2085
  ap_int<33> v1370 = v1369 - 1;	// L2086
  int v1371 = v1370;	// L2087
  for (int v1372 = 0; v1372 < v1371; v1372 += 1) {	// L2088
    ap_int<17> v1373 = zw2;	// L2089
    v1350.write(v1373);	// L2090
  }
  l_S__pf_1__pf2: for (int _pf2 = 0; _pf2 < 2; _pf2++) {	// L2092
    int32_t v1375 = rp2[0];	// L2093
    bool v1376 = v1375 < 2000;	// L2094
    if (v1376) {	// L2095
      int32_t v1377 = rp2[0];	// L2096
      int v1378 = v1377;	// L2097
      int16_t v1379 = v1347[0][v1378];	// L2098
      int32_t v1380 = wcnt2[0];	// L2099
      int v1381 = v1380;	// L2100
      win_d2[0][v1381] = v1379;	// L2101
      int32_t v1382 = rp2[0];	// L2102
      int v1383 = v1382;	// L2103
      int32_t v1384 = v1348[0][v1383];	// L2104
      int32_t v1385 = wcnt2[0];	// L2105
      int v1386 = v1385;	// L2106
      win_f2[0][v1386] = v1384;	// L2107
      int32_t v1387 = rp2[0];	// L2108
      int32_t v1388 = wcnt2[0];	// L2109
      int v1389 = v1388;	// L2110
      win_s2[0][v1389] = v1387;	// L2111
      int32_t v1390 = wcnt2[0];	// L2112
      ap_int<33> v1391 = v1390;	// L2113
      ap_int<33> v1392 = v1391 + 1;	// L2114
      int32_t v1393 = v1392;	// L2115
      wcnt2[0] = v1393;	// L2116
      int32_t v1394 = rp2[0];	// L2117
      ap_int<33> v1395 = v1394;	// L2118
      ap_int<33> v1396 = v1395 + 1;	// L2119
      int32_t v1397 = v1396;	// L2120
      rp2[0] = v1397;	// L2121
    }
  }
  l_S_t_2_t3: for (int t3 = 0; t3 < 2000; t3++) {	// L2124
  #pragma HLS pipeline II=1
    int32_t v1399 = v1351.read();	// L2125
    int32_t cin2;	// L2126
    cin2 = v1399;	// L2127
    int32_t v1401 = cin2;	// L2128
    int32_t v1402 = dcred2[0];	// L2129
    ap_int<33> v1403 = v1402;	// L2130
    ap_int<33> v1404 = v1401;	// L2131
    ap_int<33> v1405 = v1403 + v1404;	// L2132
    int32_t v1406 = v1405;	// L2133
    dcred2[0] = v1406;	// L2134
    ap_uint<17> w2;	// L2135
    w2 = 0;	// L2136
    int32_t popd2;	// L2137
    popd2 = 0;	// L2138
    int32_t v1409 = wcnt2[0];	// L2139
    bool v1410 = v1409 > 0;	// L2140
    int32_t v1411 = win_s2[0][0];	// L2141
    ap_int<33> v1412 = t3;	// L2142
    ap_int<33> v1413 = v1411;	// L2143
    bool v1414 = v1412 >= v1413;	// L2144
    bool v1415 = v1410 & v1414;	// L2145
    if (v1415) {	// L2146
      int32_t v1416 = win_f2[0][0];	// L2147
      bool v1417 = v1416 == 0;	// L2148
      if (v1417) {	// L2149
        popd2 = 1;	// L2150
      } else {
        int32_t v1418 = dcred2[0];	// L2152
        bool v1419 = v1418 > 0;	// L2153
        if (v1419) {	// L2154
          ap_int<17> v1420 = w2;	// L2155
          ap_int<17> v1421;
          ap_int<17> v1421_tmp = v1420;
          v1421_tmp[0] = 1;          v1421 = v1421_tmp;	// L2156
          w2 = v1421;	// L2157
          int16_t v1422 = win_d2[0][0];	// L2158
          ap_int<17> v1423 = w2;	// L2159
          ap_int<17> v1424;
          ap_int<17> v1424_tmp = v1423;
          v1424_tmp(16, 1) = v1422;
          v1424 = v1424_tmp;	// L2160
          w2 = v1424;	// L2161
          int32_t v1425 = dcred2[0];	// L2162
          ap_int<33> v1426 = v1425;	// L2163
          ap_int<33> v1427 = v1426 - 1;	// L2164
          int32_t v1428 = v1427;	// L2165
          dcred2[0] = v1428;	// L2166
          popd2 = 1;	// L2167
        }
      }
    }
    int32_t v1429 = popd2;	// L2171
    bool v1430 = v1429 == 1;	// L2172
    if (v1430) {	// L2173
      l_S_sft_2_sft3: for (int sft3 = 0; sft3 < 3; sft3++) {	// L2174
        int16_t v1432 = win_d2[0][(sft3 + 1)];	// L2175
        win_d2[0][sft3] = v1432;	// L2176
        int32_t v1433 = win_f2[0][(sft3 + 1)];	// L2177
        win_f2[0][sft3] = v1433;	// L2178
        int32_t v1434 = win_s2[0][(sft3 + 1)];	// L2179
        win_s2[0][sft3] = v1434;	// L2180
      }
      int32_t v1435 = wcnt2[0];	// L2182
      ap_int<33> v1436 = v1435;	// L2183
      ap_int<33> v1437 = v1436 - 1;	// L2184
      int32_t v1438 = v1437;	// L2185
      wcnt2[0] = v1438;	// L2186
    }
    int32_t v1439 = rp2[0];	// L2188
    bool v1440 = v1439 < 2000;	// L2189
    int32_t v1441 = wcnt2[0];	// L2190
    bool v1442 = v1441 < 4;	// L2191
    bool v1443 = v1440 & v1442;	// L2192
    if (v1443) {	// L2193
      int32_t v1444 = rp2[0];	// L2194
      int v1445 = v1444;	// L2195
      int16_t v1446 = v1347[0][v1445];	// L2196
      int32_t v1447 = wcnt2[0];	// L2197
      int v1448 = v1447;	// L2198
      win_d2[0][v1448] = v1446;	// L2199
      int32_t v1449 = rp2[0];	// L2200
      int v1450 = v1449;	// L2201
      int32_t v1451 = v1348[0][v1450];	// L2202
      int32_t v1452 = wcnt2[0];	// L2203
      int v1453 = v1452;	// L2204
      win_f2[0][v1453] = v1451;	// L2205
      int32_t v1454 = rp2[0];	// L2206
      int32_t v1455 = wcnt2[0];	// L2207
      int v1456 = v1455;	// L2208
      win_s2[0][v1456] = v1454;	// L2209
      int32_t v1457 = wcnt2[0];	// L2210
      ap_int<33> v1458 = v1457;	// L2211
      ap_int<33> v1459 = v1458 + 1;	// L2212
      int32_t v1460 = v1459;	// L2213
      wcnt2[0] = v1460;	// L2214
      int32_t v1461 = rp2[0];	// L2215
      ap_int<33> v1462 = v1461;	// L2216
      ap_int<33> v1463 = v1462 + 1;	// L2217
      int32_t v1464 = v1463;	// L2218
      rp2[0] = v1464;	// L2219
    }
    ap_int<17> v1465 = w2;	// L2221
    v1350.write(v1465);	// L2222
  }
}

void drv_s_0(
  int16_t v1466[1][2000],
  int32_t v1467[1][2000],
  int32_t v1468[1][1],
  hls::stream< ap_uint<17> >& v1469,
  hls::stream< int32_t >& v1470
) {
  #pragma HLS array_partition variable=v1466 complete dim=1
  #pragma HLS array_partition variable=v1467 complete dim=1	// L2226
  int32_t dcred3[1];	// L2238
  for (int v1472 = 0; v1472 < 1; v1472++) {	// L2239
    dcred3[v1472] = 0;	// L2239
  }
  int32_t rp3[1];	// L2240
  for (int v1474 = 0; v1474 < 1; v1474++) {	// L2241
    rp3[v1474] = 0;	// L2241
  }
  int32_t wcnt3[1];	// L2242
  for (int v1476 = 0; v1476 < 1; v1476++) {	// L2243
    wcnt3[v1476] = 0;	// L2243
  }
  int16_t win_d3[1][4];	// L2244
  for (int v1478 = 0; v1478 < 1; v1478++) {	// L2245
    for (int v1479 = 0; v1479 < 4; v1479++) {	// L2245
      win_d3[v1478][v1479] = 0;	// L2245
    }
  }
  int32_t win_f3[1][4];	// L2246
  for (int v1481 = 0; v1481 < 1; v1481++) {	// L2247
    for (int v1482 = 0; v1482 < 4; v1482++) {	// L2247
      win_f3[v1481][v1482] = 0;	// L2247
    }
  }
  int32_t win_s3[1][4];	// L2248
  for (int v1484 = 0; v1484 < 1; v1484++) {	// L2249
    for (int v1485 = 0; v1485 < 4; v1485++) {	// L2249
      win_s3[v1484][v1485] = 0;	// L2249
    }
  }
  ap_uint<17> zw3;	// L2250
  zw3 = 0;	// L2251
  int32_t v1487 = v1468[0][0];	// L2252
  ap_int<33> v1488 = v1487;	// L2253
  ap_int<33> v1489 = v1488 - 1;	// L2254
  int v1490 = v1489;	// L2255
  for (int v1491 = 0; v1491 < v1490; v1491 += 1) {	// L2256
    ap_int<17> v1492 = zw3;	// L2257
    v1469.write(v1492);	// L2258
  }
  l_S__pf_1__pf3: for (int _pf3 = 0; _pf3 < 2; _pf3++) {	// L2260
    int32_t v1494 = rp3[0];	// L2261
    bool v1495 = v1494 < 2000;	// L2262
    if (v1495) {	// L2263
      int32_t v1496 = rp3[0];	// L2264
      int v1497 = v1496;	// L2265
      int16_t v1498 = v1466[0][v1497];	// L2266
      int32_t v1499 = wcnt3[0];	// L2267
      int v1500 = v1499;	// L2268
      win_d3[0][v1500] = v1498;	// L2269
      int32_t v1501 = rp3[0];	// L2270
      int v1502 = v1501;	// L2271
      int32_t v1503 = v1467[0][v1502];	// L2272
      int32_t v1504 = wcnt3[0];	// L2273
      int v1505 = v1504;	// L2274
      win_f3[0][v1505] = v1503;	// L2275
      int32_t v1506 = rp3[0];	// L2276
      int32_t v1507 = wcnt3[0];	// L2277
      int v1508 = v1507;	// L2278
      win_s3[0][v1508] = v1506;	// L2279
      int32_t v1509 = wcnt3[0];	// L2280
      ap_int<33> v1510 = v1509;	// L2281
      ap_int<33> v1511 = v1510 + 1;	// L2282
      int32_t v1512 = v1511;	// L2283
      wcnt3[0] = v1512;	// L2284
      int32_t v1513 = rp3[0];	// L2285
      ap_int<33> v1514 = v1513;	// L2286
      ap_int<33> v1515 = v1514 + 1;	// L2287
      int32_t v1516 = v1515;	// L2288
      rp3[0] = v1516;	// L2289
    }
  }
  l_S_t_2_t4: for (int t4 = 0; t4 < 2000; t4++) {	// L2292
  #pragma HLS pipeline II=1
    int32_t v1518 = v1470.read();	// L2293
    int32_t cin3;	// L2294
    cin3 = v1518;	// L2295
    int32_t v1520 = cin3;	// L2296
    int32_t v1521 = dcred3[0];	// L2297
    ap_int<33> v1522 = v1521;	// L2298
    ap_int<33> v1523 = v1520;	// L2299
    ap_int<33> v1524 = v1522 + v1523;	// L2300
    int32_t v1525 = v1524;	// L2301
    dcred3[0] = v1525;	// L2302
    ap_uint<17> w3;	// L2303
    w3 = 0;	// L2304
    int32_t popd3;	// L2305
    popd3 = 0;	// L2306
    int32_t v1528 = wcnt3[0];	// L2307
    bool v1529 = v1528 > 0;	// L2308
    int32_t v1530 = win_s3[0][0];	// L2309
    ap_int<33> v1531 = t4;	// L2310
    ap_int<33> v1532 = v1530;	// L2311
    bool v1533 = v1531 >= v1532;	// L2312
    bool v1534 = v1529 & v1533;	// L2313
    if (v1534) {	// L2314
      int32_t v1535 = win_f3[0][0];	// L2315
      bool v1536 = v1535 == 0;	// L2316
      if (v1536) {	// L2317
        popd3 = 1;	// L2318
      } else {
        int32_t v1537 = dcred3[0];	// L2320
        bool v1538 = v1537 > 0;	// L2321
        if (v1538) {	// L2322
          ap_int<17> v1539 = w3;	// L2323
          ap_int<17> v1540;
          ap_int<17> v1540_tmp = v1539;
          v1540_tmp[0] = 1;          v1540 = v1540_tmp;	// L2324
          w3 = v1540;	// L2325
          int16_t v1541 = win_d3[0][0];	// L2326
          ap_int<17> v1542 = w3;	// L2327
          ap_int<17> v1543;
          ap_int<17> v1543_tmp = v1542;
          v1543_tmp(16, 1) = v1541;
          v1543 = v1543_tmp;	// L2328
          w3 = v1543;	// L2329
          int32_t v1544 = dcred3[0];	// L2330
          ap_int<33> v1545 = v1544;	// L2331
          ap_int<33> v1546 = v1545 - 1;	// L2332
          int32_t v1547 = v1546;	// L2333
          dcred3[0] = v1547;	// L2334
          popd3 = 1;	// L2335
        }
      }
    }
    int32_t v1548 = popd3;	// L2339
    bool v1549 = v1548 == 1;	// L2340
    if (v1549) {	// L2341
      l_S_sft_2_sft4: for (int sft4 = 0; sft4 < 3; sft4++) {	// L2342
        int16_t v1551 = win_d3[0][(sft4 + 1)];	// L2343
        win_d3[0][sft4] = v1551;	// L2344
        int32_t v1552 = win_f3[0][(sft4 + 1)];	// L2345
        win_f3[0][sft4] = v1552;	// L2346
        int32_t v1553 = win_s3[0][(sft4 + 1)];	// L2347
        win_s3[0][sft4] = v1553;	// L2348
      }
      int32_t v1554 = wcnt3[0];	// L2350
      ap_int<33> v1555 = v1554;	// L2351
      ap_int<33> v1556 = v1555 - 1;	// L2352
      int32_t v1557 = v1556;	// L2353
      wcnt3[0] = v1557;	// L2354
    }
    int32_t v1558 = rp3[0];	// L2356
    bool v1559 = v1558 < 2000;	// L2357
    int32_t v1560 = wcnt3[0];	// L2358
    bool v1561 = v1560 < 4;	// L2359
    bool v1562 = v1559 & v1561;	// L2360
    if (v1562) {	// L2361
      int32_t v1563 = rp3[0];	// L2362
      int v1564 = v1563;	// L2363
      int16_t v1565 = v1466[0][v1564];	// L2364
      int32_t v1566 = wcnt3[0];	// L2365
      int v1567 = v1566;	// L2366
      win_d3[0][v1567] = v1565;	// L2367
      int32_t v1568 = rp3[0];	// L2368
      int v1569 = v1568;	// L2369
      int32_t v1570 = v1467[0][v1569];	// L2370
      int32_t v1571 = wcnt3[0];	// L2371
      int v1572 = v1571;	// L2372
      win_f3[0][v1572] = v1570;	// L2373
      int32_t v1573 = rp3[0];	// L2374
      int32_t v1574 = wcnt3[0];	// L2375
      int v1575 = v1574;	// L2376
      win_s3[0][v1575] = v1573;	// L2377
      int32_t v1576 = wcnt3[0];	// L2378
      ap_int<33> v1577 = v1576;	// L2379
      ap_int<33> v1578 = v1577 + 1;	// L2380
      int32_t v1579 = v1578;	// L2381
      wcnt3[0] = v1579;	// L2382
      int32_t v1580 = rp3[0];	// L2383
      ap_int<33> v1581 = v1580;	// L2384
      ap_int<33> v1582 = v1581 + 1;	// L2385
      int32_t v1583 = v1582;	// L2386
      rp3[0] = v1583;	// L2387
    }
    ap_int<17> v1584 = w3;	// L2389
    v1469.write(v1584);	// L2390
  }
}

void col_w_0(
  int16_t v1585[1][2000],
  int32_t v1586[1][1],
  hls::stream< int32_t >& v1587,
  hls::stream< ap_uint<17> >& v1588
) {
  #pragma HLS array_partition variable=v1585 complete dim=1	// L2394
  int32_t k2[1];	// L2403
  for (int v1590 = 0; v1590 < 1; v1590++) {	// L2404
    k2[v1590] = 0;	// L2404
  }
  int32_t cret[1];	// L2405
  for (int v1592 = 0; v1592 < 1; v1592++) {	// L2406
    cret[v1592] = 0;	// L2406
  }
  int32_t zc;	// L2407
  zc = 0;	// L2408
  int32_t v1594 = v1586[0][0];	// L2409
  ap_int<33> v1595 = v1594;	// L2410
  ap_int<33> v1596 = v1595 - 1;	// L2411
  int v1597 = v1596;	// L2412
  for (int v1598 = 0; v1598 < v1597; v1598 += 1) {	// L2413
    int32_t v1599 = zc;	// L2414
    v1587.write(v1599);	// L2415
  }
  cret[0] = 2;	// L2417
  int32_t v1600 = cret[0];	// L2418
  v1587.write(v1600);	// L2419
  l_S_t_1_t5: for (int t5 = 0; t5 < 2000; t5++) {	// L2420
  #pragma HLS pipeline II=1
    ap_uint<17> v1602 = v1588.read();	// L2421
    ap_uint<17> w4;	// L2422
    w4 = v1602;	// L2423
    cret[0] = 0;	// L2424
    ap_int<17> v1604 = w4;	// L2425
    bool v1605;
    ap_int<17> v1605_tmp = v1604;
    v1605 = v1605_tmp[0];	// L2426
    int32_t v1606 = v1605;	// L2427
    bool v1607 = v1606 == 1;	// L2428
    if (v1607) {	// L2429
      cret[0] = 1;	// L2430
      int32_t v1608 = k2[0];	// L2431
      bool v1609 = v1608 < 2000;	// L2432
      if (v1609) {	// L2433
        ap_int<17> v1610 = w4;	// L2434
        int16_t v1611;
        ap_int<17> v1611_tmp = v1610;
        v1611 = v1611_tmp(16, 1);	// L2435
        int32_t v1612 = k2[0];	// L2436
        int v1613 = v1612;	// L2437
        v1585[0][v1613] = v1611;	// L2438
        int32_t v1614 = k2[0];	// L2439
        ap_int<33> v1615 = v1614;	// L2440
        ap_int<33> v1616 = v1615 + 1;	// L2441
        int32_t v1617 = v1616;	// L2442
        k2[0] = v1617;	// L2443
      }
    }
    int32_t v1618 = cret[0];	// L2446
    v1587.write(v1618);	// L2447
  }
}

void col_e_0(
  int16_t v1619[1][2000],
  int32_t v1620[1][1],
  hls::stream< int32_t >& v1621,
  hls::stream< ap_uint<17> >& v1622
) {
  #pragma HLS array_partition variable=v1619 complete dim=1	// L2451
  int32_t k3[1];	// L2460
  for (int v1624 = 0; v1624 < 1; v1624++) {	// L2461
    k3[v1624] = 0;	// L2461
  }
  int32_t cret1[1];	// L2462
  for (int v1626 = 0; v1626 < 1; v1626++) {	// L2463
    cret1[v1626] = 0;	// L2463
  }
  int32_t zc1;	// L2464
  zc1 = 0;	// L2465
  int32_t v1628 = v1620[0][0];	// L2466
  ap_int<33> v1629 = v1628;	// L2467
  ap_int<33> v1630 = v1629 - 1;	// L2468
  int v1631 = v1630;	// L2469
  for (int v1632 = 0; v1632 < v1631; v1632 += 1) {	// L2470
    int32_t v1633 = zc1;	// L2471
    v1621.write(v1633);	// L2472
  }
  cret1[0] = 2;	// L2474
  int32_t v1634 = cret1[0];	// L2475
  v1621.write(v1634);	// L2476
  l_S_t_1_t6: for (int t6 = 0; t6 < 2000; t6++) {	// L2477
  #pragma HLS pipeline II=1
    ap_uint<17> v1636 = v1622.read();	// L2478
    ap_uint<17> w5;	// L2479
    w5 = v1636;	// L2480
    cret1[0] = 0;	// L2481
    ap_int<17> v1638 = w5;	// L2482
    bool v1639;
    ap_int<17> v1639_tmp = v1638;
    v1639 = v1639_tmp[0];	// L2483
    int32_t v1640 = v1639;	// L2484
    bool v1641 = v1640 == 1;	// L2485
    if (v1641) {	// L2486
      cret1[0] = 1;	// L2487
      int32_t v1642 = k3[0];	// L2488
      bool v1643 = v1642 < 2000;	// L2489
      if (v1643) {	// L2490
        ap_int<17> v1644 = w5;	// L2491
        int16_t v1645;
        ap_int<17> v1645_tmp = v1644;
        v1645 = v1645_tmp(16, 1);	// L2492
        int32_t v1646 = k3[0];	// L2493
        int v1647 = v1646;	// L2494
        v1619[0][v1647] = v1645;	// L2495
        int32_t v1648 = k3[0];	// L2496
        ap_int<33> v1649 = v1648;	// L2497
        ap_int<33> v1650 = v1649 + 1;	// L2498
        int32_t v1651 = v1650;	// L2499
        k3[0] = v1651;	// L2500
      }
    }
    int32_t v1652 = cret1[0];	// L2503
    v1621.write(v1652);	// L2504
  }
}

void col_n_0(
  int16_t v1653[1][2000],
  int32_t v1654[1][1],
  hls::stream< int32_t >& v1655,
  hls::stream< ap_uint<17> >& v1656
) {
  #pragma HLS array_partition variable=v1653 complete dim=1	// L2508
  int32_t k4[1];	// L2517
  for (int v1658 = 0; v1658 < 1; v1658++) {	// L2518
    k4[v1658] = 0;	// L2518
  }
  int32_t cret2[1];	// L2519
  for (int v1660 = 0; v1660 < 1; v1660++) {	// L2520
    cret2[v1660] = 0;	// L2520
  }
  int32_t zc2;	// L2521
  zc2 = 0;	// L2522
  int32_t v1662 = v1654[0][0];	// L2523
  ap_int<33> v1663 = v1662;	// L2524
  ap_int<33> v1664 = v1663 - 1;	// L2525
  int v1665 = v1664;	// L2526
  for (int v1666 = 0; v1666 < v1665; v1666 += 1) {	// L2527
    int32_t v1667 = zc2;	// L2528
    v1655.write(v1667);	// L2529
  }
  cret2[0] = 2;	// L2531
  int32_t v1668 = cret2[0];	// L2532
  v1655.write(v1668);	// L2533
  l_S_t_1_t7: for (int t7 = 0; t7 < 2000; t7++) {	// L2534
  #pragma HLS pipeline II=1
    ap_uint<17> v1670 = v1656.read();	// L2535
    ap_uint<17> w6;	// L2536
    w6 = v1670;	// L2537
    cret2[0] = 0;	// L2538
    ap_int<17> v1672 = w6;	// L2539
    bool v1673;
    ap_int<17> v1673_tmp = v1672;
    v1673 = v1673_tmp[0];	// L2540
    int32_t v1674 = v1673;	// L2541
    bool v1675 = v1674 == 1;	// L2542
    if (v1675) {	// L2543
      cret2[0] = 1;	// L2544
      int32_t v1676 = k4[0];	// L2545
      bool v1677 = v1676 < 2000;	// L2546
      if (v1677) {	// L2547
        ap_int<17> v1678 = w6;	// L2548
        int16_t v1679;
        ap_int<17> v1679_tmp = v1678;
        v1679 = v1679_tmp(16, 1);	// L2549
        int32_t v1680 = k4[0];	// L2550
        int v1681 = v1680;	// L2551
        v1653[0][v1681] = v1679;	// L2552
        int32_t v1682 = k4[0];	// L2553
        ap_int<33> v1683 = v1682;	// L2554
        ap_int<33> v1684 = v1683 + 1;	// L2555
        int32_t v1685 = v1684;	// L2556
        k4[0] = v1685;	// L2557
      }
    }
    int32_t v1686 = cret2[0];	// L2560
    v1655.write(v1686);	// L2561
  }
}

void col_s_0(
  int16_t v1687[1][2000],
  int32_t v1688[1][1],
  hls::stream< int32_t >& v1689,
  hls::stream< ap_uint<17> >& v1690
) {
  #pragma HLS array_partition variable=v1687 complete dim=1	// L2565
  int32_t k5[1];	// L2574
  for (int v1692 = 0; v1692 < 1; v1692++) {	// L2575
    k5[v1692] = 0;	// L2575
  }
  int32_t cret3[1];	// L2576
  for (int v1694 = 0; v1694 < 1; v1694++) {	// L2577
    cret3[v1694] = 0;	// L2577
  }
  int32_t zc3;	// L2578
  zc3 = 0;	// L2579
  int32_t v1696 = v1688[0][0];	// L2580
  ap_int<33> v1697 = v1696;	// L2581
  ap_int<33> v1698 = v1697 - 1;	// L2582
  int v1699 = v1698;	// L2583
  for (int v1700 = 0; v1700 < v1699; v1700 += 1) {	// L2584
    int32_t v1701 = zc3;	// L2585
    v1689.write(v1701);	// L2586
  }
  cret3[0] = 2;	// L2588
  int32_t v1702 = cret3[0];	// L2589
  v1689.write(v1702);	// L2590
  l_S_t_1_t8: for (int t8 = 0; t8 < 2000; t8++) {	// L2591
  #pragma HLS pipeline II=1
    ap_uint<17> v1704 = v1690.read();	// L2592
    ap_uint<17> w7;	// L2593
    w7 = v1704;	// L2594
    cret3[0] = 0;	// L2595
    ap_int<17> v1706 = w7;	// L2596
    bool v1707;
    ap_int<17> v1707_tmp = v1706;
    v1707 = v1707_tmp[0];	// L2597
    int32_t v1708 = v1707;	// L2598
    bool v1709 = v1708 == 1;	// L2599
    if (v1709) {	// L2600
      cret3[0] = 1;	// L2601
      int32_t v1710 = k5[0];	// L2602
      bool v1711 = v1710 < 2000;	// L2603
      if (v1711) {	// L2604
        ap_int<17> v1712 = w7;	// L2605
        int16_t v1713;
        ap_int<17> v1713_tmp = v1712;
        v1713 = v1713_tmp(16, 1);	// L2606
        int32_t v1714 = k5[0];	// L2607
        int v1715 = v1714;	// L2608
        v1687[0][v1715] = v1713;	// L2609
        int32_t v1716 = k5[0];	// L2610
        ap_int<33> v1717 = v1716;	// L2611
        ap_int<33> v1718 = v1717 + 1;	// L2612
        int32_t v1719 = v1718;	// L2613
        k5[0] = v1719;	// L2614
      }
    }
    int32_t v1720 = cret3[0];	// L2617
    v1689.write(v1720);	// L2618
  }
}

void rdrv_w_0(
  int32_t v1721[1][2000],
  int32_t v1722[1][1],
  hls::stream< ap_uint<26> >& v1723,
  hls::stream< int32_t >& v1724
) {
  #pragma HLS array_partition variable=v1721 complete dim=1	// L2622
  int32_t dcred4[1];	// L2632
  for (int v1726 = 0; v1726 < 1; v1726++) {	// L2633
    dcred4[v1726] = 0;	// L2633
  }
  int32_t rp4[1];	// L2634
  for (int v1728 = 0; v1728 < 1; v1728++) {	// L2635
    rp4[v1728] = 0;	// L2635
  }
  int32_t wcnt4[1];	// L2636
  for (int v1730 = 0; v1730 < 1; v1730++) {	// L2637
    wcnt4[v1730] = 0;	// L2637
  }
  ap_uint<26> win_p[1][4];	// L2638
  for (int v1732 = 0; v1732 < 1; v1732++) {	// L2639
    for (int v1733 = 0; v1733 < 4; v1733++) {	// L2639
      win_p[v1732][v1733] = 0;	// L2639
    }
  }
  ap_uint<26> zp;	// L2640
  zp = 0;	// L2641
  int32_t v1735 = v1722[0][0];	// L2642
  ap_int<33> v1736 = v1735;	// L2643
  ap_int<33> v1737 = v1736 - 1;	// L2644
  int v1738 = v1737;	// L2645
  for (int v1739 = 0; v1739 < v1738; v1739 += 1) {	// L2646
    ap_int<26> v1740 = zp;	// L2647
    v1723.write(v1740);	// L2648
  }
  l_S__pf_1__pf4: for (int _pf4 = 0; _pf4 < 2; _pf4++) {	// L2650
    int32_t v1742 = rp4[0];	// L2651
    bool v1743 = v1742 < 2000;	// L2652
    if (v1743) {	// L2653
      ap_uint<26> cnd;	// L2654
      cnd = 0;	// L2655
      int32_t v1745 = rp4[0];	// L2656
      int v1746 = v1745;	// L2657
      int32_t v1747 = v1721[0][v1746];	// L2658
      ap_uint<26> v1748 = v1747;	// L2659
      ap_int<26> v1749 = cnd;	// L2660
      ap_int<26> v1750;
      ap_int<26> v1750_tmp = v1749;
      v1750_tmp(25, 0) = v1748;
      v1750 = v1750_tmp;	// L2661
      cnd = v1750;	// L2662
      ap_int<26> v1751 = cnd;	// L2663
      int32_t v1752 = wcnt4[0];	// L2664
      int v1753 = v1752;	// L2665
      win_p[0][v1753] = v1751;	// L2666
      int32_t v1754 = wcnt4[0];	// L2667
      ap_int<33> v1755 = v1754;	// L2668
      ap_int<33> v1756 = v1755 + 1;	// L2669
      int32_t v1757 = v1756;	// L2670
      wcnt4[0] = v1757;	// L2671
      int32_t v1758 = rp4[0];	// L2672
      ap_int<33> v1759 = v1758;	// L2673
      ap_int<33> v1760 = v1759 + 1;	// L2674
      int32_t v1761 = v1760;	// L2675
      rp4[0] = v1761;	// L2676
    }
  }
  l_S_t_2_t9: for (int t9 = 0; t9 < 2000; t9++) {	// L2679
  #pragma HLS pipeline II=1
    int32_t v1763 = v1724.read();	// L2680
    int32_t cin4;	// L2681
    cin4 = v1763;	// L2682
    int32_t v1765 = cin4;	// L2683
    int32_t v1766 = dcred4[0];	// L2684
    ap_int<33> v1767 = v1766;	// L2685
    ap_int<33> v1768 = v1765;	// L2686
    ap_int<33> v1769 = v1767 + v1768;	// L2687
    int32_t v1770 = v1769;	// L2688
    dcred4[0] = v1770;	// L2689
    ap_uint<26> pw;	// L2690
    pw = 0;	// L2691
    ap_uint<26> v1772 = win_p[0][0];	// L2692
    ap_uint<26> hp;	// L2693
    hp = v1772;	// L2694
    int32_t popd4;	// L2695
    popd4 = 0;	// L2696
    int32_t v1775 = wcnt4[0];	// L2697
    bool v1776 = v1775 > 0;	// L2698
    if (v1776) {	// L2699
      ap_int<26> v1777 = hp;	// L2700
      bool v1778;
      ap_int<26> v1778_tmp = v1777;
      v1778 = v1778_tmp[25];	// L2701
      int32_t v1779 = v1778;	// L2702
      bool v1780 = v1779 == 0;	// L2703
      if (v1780) {	// L2704
        popd4 = 1;	// L2705
      } else {
        int32_t v1781 = dcred4[0];	// L2707
        bool v1782 = v1781 > 0;	// L2708
        if (v1782) {	// L2709
          ap_int<26> v1783 = hp;	// L2710
          pw = v1783;	// L2711
          int32_t v1784 = dcred4[0];	// L2712
          ap_int<33> v1785 = v1784;	// L2713
          ap_int<33> v1786 = v1785 - 1;	// L2714
          int32_t v1787 = v1786;	// L2715
          dcred4[0] = v1787;	// L2716
          popd4 = 1;	// L2717
        }
      }
    }
    int32_t v1788 = popd4;	// L2721
    bool v1789 = v1788 == 1;	// L2722
    if (v1789) {	// L2723
      l_S_sft_2_sft5: for (int sft5 = 0; sft5 < 3; sft5++) {	// L2724
        ap_uint<26> v1791 = win_p[0][(sft5 + 1)];	// L2725
        win_p[0][sft5] = v1791;	// L2726
      }
      int32_t v1792 = wcnt4[0];	// L2728
      ap_int<33> v1793 = v1792;	// L2729
      ap_int<33> v1794 = v1793 - 1;	// L2730
      int32_t v1795 = v1794;	// L2731
      wcnt4[0] = v1795;	// L2732
    }
    int32_t v1796 = rp4[0];	// L2734
    bool v1797 = v1796 < 2000;	// L2735
    int32_t v1798 = wcnt4[0];	// L2736
    bool v1799 = v1798 < 4;	// L2737
    bool v1800 = v1797 & v1799;	// L2738
    if (v1800) {	// L2739
      ap_uint<26> cnd2;	// L2740
      cnd2 = 0;	// L2741
      int32_t v1802 = rp4[0];	// L2742
      int v1803 = v1802;	// L2743
      int32_t v1804 = v1721[0][v1803];	// L2744
      ap_uint<26> v1805 = v1804;	// L2745
      ap_int<26> v1806 = cnd2;	// L2746
      ap_int<26> v1807;
      ap_int<26> v1807_tmp = v1806;
      v1807_tmp(25, 0) = v1805;
      v1807 = v1807_tmp;	// L2747
      cnd2 = v1807;	// L2748
      ap_int<26> v1808 = cnd2;	// L2749
      int32_t v1809 = wcnt4[0];	// L2750
      int v1810 = v1809;	// L2751
      win_p[0][v1810] = v1808;	// L2752
      int32_t v1811 = wcnt4[0];	// L2753
      ap_int<33> v1812 = v1811;	// L2754
      ap_int<33> v1813 = v1812 + 1;	// L2755
      int32_t v1814 = v1813;	// L2756
      wcnt4[0] = v1814;	// L2757
      int32_t v1815 = rp4[0];	// L2758
      ap_int<33> v1816 = v1815;	// L2759
      ap_int<33> v1817 = v1816 + 1;	// L2760
      int32_t v1818 = v1817;	// L2761
      rp4[0] = v1818;	// L2762
    }
    ap_int<26> v1819 = pw;	// L2764
    v1723.write(v1819);	// L2765
  }
}

void rdrv_e_0(
  int32_t v1820[1][2000],
  int32_t v1821[1][1],
  hls::stream< ap_uint<26> >& v1822,
  hls::stream< int32_t >& v1823
) {
  #pragma HLS array_partition variable=v1820 complete dim=1	// L2769
  int32_t dcred5[1];	// L2779
  for (int v1825 = 0; v1825 < 1; v1825++) {	// L2780
    dcred5[v1825] = 0;	// L2780
  }
  int32_t rp5[1];	// L2781
  for (int v1827 = 0; v1827 < 1; v1827++) {	// L2782
    rp5[v1827] = 0;	// L2782
  }
  int32_t wcnt5[1];	// L2783
  for (int v1829 = 0; v1829 < 1; v1829++) {	// L2784
    wcnt5[v1829] = 0;	// L2784
  }
  ap_uint<26> win_p1[1][4];	// L2785
  for (int v1831 = 0; v1831 < 1; v1831++) {	// L2786
    for (int v1832 = 0; v1832 < 4; v1832++) {	// L2786
      win_p1[v1831][v1832] = 0;	// L2786
    }
  }
  ap_uint<26> zp1;	// L2787
  zp1 = 0;	// L2788
  int32_t v1834 = v1821[0][0];	// L2789
  ap_int<33> v1835 = v1834;	// L2790
  ap_int<33> v1836 = v1835 - 1;	// L2791
  int v1837 = v1836;	// L2792
  for (int v1838 = 0; v1838 < v1837; v1838 += 1) {	// L2793
    ap_int<26> v1839 = zp1;	// L2794
    v1822.write(v1839);	// L2795
  }
  l_S__pf_1__pf5: for (int _pf5 = 0; _pf5 < 2; _pf5++) {	// L2797
    int32_t v1841 = rp5[0];	// L2798
    bool v1842 = v1841 < 2000;	// L2799
    if (v1842) {	// L2800
      ap_uint<26> cnd1;	// L2801
      cnd1 = 0;	// L2802
      int32_t v1844 = rp5[0];	// L2803
      int v1845 = v1844;	// L2804
      int32_t v1846 = v1820[0][v1845];	// L2805
      ap_uint<26> v1847 = v1846;	// L2806
      ap_int<26> v1848 = cnd1;	// L2807
      ap_int<26> v1849;
      ap_int<26> v1849_tmp = v1848;
      v1849_tmp(25, 0) = v1847;
      v1849 = v1849_tmp;	// L2808
      cnd1 = v1849;	// L2809
      ap_int<26> v1850 = cnd1;	// L2810
      int32_t v1851 = wcnt5[0];	// L2811
      int v1852 = v1851;	// L2812
      win_p1[0][v1852] = v1850;	// L2813
      int32_t v1853 = wcnt5[0];	// L2814
      ap_int<33> v1854 = v1853;	// L2815
      ap_int<33> v1855 = v1854 + 1;	// L2816
      int32_t v1856 = v1855;	// L2817
      wcnt5[0] = v1856;	// L2818
      int32_t v1857 = rp5[0];	// L2819
      ap_int<33> v1858 = v1857;	// L2820
      ap_int<33> v1859 = v1858 + 1;	// L2821
      int32_t v1860 = v1859;	// L2822
      rp5[0] = v1860;	// L2823
    }
  }
  l_S_t_2_t10: for (int t10 = 0; t10 < 2000; t10++) {	// L2826
  #pragma HLS pipeline II=1
    int32_t v1862 = v1823.read();	// L2827
    int32_t cin5;	// L2828
    cin5 = v1862;	// L2829
    int32_t v1864 = cin5;	// L2830
    int32_t v1865 = dcred5[0];	// L2831
    ap_int<33> v1866 = v1865;	// L2832
    ap_int<33> v1867 = v1864;	// L2833
    ap_int<33> v1868 = v1866 + v1867;	// L2834
    int32_t v1869 = v1868;	// L2835
    dcred5[0] = v1869;	// L2836
    ap_uint<26> pw1;	// L2837
    pw1 = 0;	// L2838
    ap_uint<26> v1871 = win_p1[0][0];	// L2839
    ap_uint<26> hp1;	// L2840
    hp1 = v1871;	// L2841
    int32_t popd5;	// L2842
    popd5 = 0;	// L2843
    int32_t v1874 = wcnt5[0];	// L2844
    bool v1875 = v1874 > 0;	// L2845
    if (v1875) {	// L2846
      ap_int<26> v1876 = hp1;	// L2847
      bool v1877;
      ap_int<26> v1877_tmp = v1876;
      v1877 = v1877_tmp[25];	// L2848
      int32_t v1878 = v1877;	// L2849
      bool v1879 = v1878 == 0;	// L2850
      if (v1879) {	// L2851
        popd5 = 1;	// L2852
      } else {
        int32_t v1880 = dcred5[0];	// L2854
        bool v1881 = v1880 > 0;	// L2855
        if (v1881) {	// L2856
          ap_int<26> v1882 = hp1;	// L2857
          pw1 = v1882;	// L2858
          int32_t v1883 = dcred5[0];	// L2859
          ap_int<33> v1884 = v1883;	// L2860
          ap_int<33> v1885 = v1884 - 1;	// L2861
          int32_t v1886 = v1885;	// L2862
          dcred5[0] = v1886;	// L2863
          popd5 = 1;	// L2864
        }
      }
    }
    int32_t v1887 = popd5;	// L2868
    bool v1888 = v1887 == 1;	// L2869
    if (v1888) {	// L2870
      l_S_sft_2_sft6: for (int sft6 = 0; sft6 < 3; sft6++) {	// L2871
        ap_uint<26> v1890 = win_p1[0][(sft6 + 1)];	// L2872
        win_p1[0][sft6] = v1890;	// L2873
      }
      int32_t v1891 = wcnt5[0];	// L2875
      ap_int<33> v1892 = v1891;	// L2876
      ap_int<33> v1893 = v1892 - 1;	// L2877
      int32_t v1894 = v1893;	// L2878
      wcnt5[0] = v1894;	// L2879
    }
    int32_t v1895 = rp5[0];	// L2881
    bool v1896 = v1895 < 2000;	// L2882
    int32_t v1897 = wcnt5[0];	// L2883
    bool v1898 = v1897 < 4;	// L2884
    bool v1899 = v1896 & v1898;	// L2885
    if (v1899) {	// L2886
      ap_uint<26> cnd21;	// L2887
      cnd21 = 0;	// L2888
      int32_t v1901 = rp5[0];	// L2889
      int v1902 = v1901;	// L2890
      int32_t v1903 = v1820[0][v1902];	// L2891
      ap_uint<26> v1904 = v1903;	// L2892
      ap_int<26> v1905 = cnd21;	// L2893
      ap_int<26> v1906;
      ap_int<26> v1906_tmp = v1905;
      v1906_tmp(25, 0) = v1904;
      v1906 = v1906_tmp;	// L2894
      cnd21 = v1906;	// L2895
      ap_int<26> v1907 = cnd21;	// L2896
      int32_t v1908 = wcnt5[0];	// L2897
      int v1909 = v1908;	// L2898
      win_p1[0][v1909] = v1907;	// L2899
      int32_t v1910 = wcnt5[0];	// L2900
      ap_int<33> v1911 = v1910;	// L2901
      ap_int<33> v1912 = v1911 + 1;	// L2902
      int32_t v1913 = v1912;	// L2903
      wcnt5[0] = v1913;	// L2904
      int32_t v1914 = rp5[0];	// L2905
      ap_int<33> v1915 = v1914;	// L2906
      ap_int<33> v1916 = v1915 + 1;	// L2907
      int32_t v1917 = v1916;	// L2908
      rp5[0] = v1917;	// L2909
    }
    ap_int<26> v1918 = pw1;	// L2911
    v1822.write(v1918);	// L2912
  }
}

void rdrv_n_0(
  int32_t v1919[1][2000],
  int32_t v1920[1][1],
  hls::stream< ap_uint<26> >& v1921,
  hls::stream< int32_t >& v1922
) {
  #pragma HLS array_partition variable=v1919 complete dim=1	// L2916
  int32_t dcred6[1];	// L2926
  for (int v1924 = 0; v1924 < 1; v1924++) {	// L2927
    dcred6[v1924] = 0;	// L2927
  }
  int32_t rp6[1];	// L2928
  for (int v1926 = 0; v1926 < 1; v1926++) {	// L2929
    rp6[v1926] = 0;	// L2929
  }
  int32_t wcnt6[1];	// L2930
  for (int v1928 = 0; v1928 < 1; v1928++) {	// L2931
    wcnt6[v1928] = 0;	// L2931
  }
  ap_uint<26> win_p2[1][4];	// L2932
  for (int v1930 = 0; v1930 < 1; v1930++) {	// L2933
    for (int v1931 = 0; v1931 < 4; v1931++) {	// L2933
      win_p2[v1930][v1931] = 0;	// L2933
    }
  }
  ap_uint<26> zp2;	// L2934
  zp2 = 0;	// L2935
  int32_t v1933 = v1920[0][0];	// L2936
  ap_int<33> v1934 = v1933;	// L2937
  ap_int<33> v1935 = v1934 - 1;	// L2938
  int v1936 = v1935;	// L2939
  for (int v1937 = 0; v1937 < v1936; v1937 += 1) {	// L2940
    ap_int<26> v1938 = zp2;	// L2941
    v1921.write(v1938);	// L2942
  }
  l_S__pf_1__pf6: for (int _pf6 = 0; _pf6 < 2; _pf6++) {	// L2944
    int32_t v1940 = rp6[0];	// L2945
    bool v1941 = v1940 < 2000;	// L2946
    if (v1941) {	// L2947
      ap_uint<26> cnd2;	// L2948
      cnd2 = 0;	// L2949
      int32_t v1943 = rp6[0];	// L2950
      int v1944 = v1943;	// L2951
      int32_t v1945 = v1919[0][v1944];	// L2952
      ap_uint<26> v1946 = v1945;	// L2953
      ap_int<26> v1947 = cnd2;	// L2954
      ap_int<26> v1948;
      ap_int<26> v1948_tmp = v1947;
      v1948_tmp(25, 0) = v1946;
      v1948 = v1948_tmp;	// L2955
      cnd2 = v1948;	// L2956
      ap_int<26> v1949 = cnd2;	// L2957
      int32_t v1950 = wcnt6[0];	// L2958
      int v1951 = v1950;	// L2959
      win_p2[0][v1951] = v1949;	// L2960
      int32_t v1952 = wcnt6[0];	// L2961
      ap_int<33> v1953 = v1952;	// L2962
      ap_int<33> v1954 = v1953 + 1;	// L2963
      int32_t v1955 = v1954;	// L2964
      wcnt6[0] = v1955;	// L2965
      int32_t v1956 = rp6[0];	// L2966
      ap_int<33> v1957 = v1956;	// L2967
      ap_int<33> v1958 = v1957 + 1;	// L2968
      int32_t v1959 = v1958;	// L2969
      rp6[0] = v1959;	// L2970
    }
  }
  l_S_t_2_t11: for (int t11 = 0; t11 < 2000; t11++) {	// L2973
  #pragma HLS pipeline II=1
    int32_t v1961 = v1922.read();	// L2974
    int32_t cin6;	// L2975
    cin6 = v1961;	// L2976
    int32_t v1963 = cin6;	// L2977
    int32_t v1964 = dcred6[0];	// L2978
    ap_int<33> v1965 = v1964;	// L2979
    ap_int<33> v1966 = v1963;	// L2980
    ap_int<33> v1967 = v1965 + v1966;	// L2981
    int32_t v1968 = v1967;	// L2982
    dcred6[0] = v1968;	// L2983
    ap_uint<26> pw2;	// L2984
    pw2 = 0;	// L2985
    ap_uint<26> v1970 = win_p2[0][0];	// L2986
    ap_uint<26> hp2;	// L2987
    hp2 = v1970;	// L2988
    int32_t popd6;	// L2989
    popd6 = 0;	// L2990
    int32_t v1973 = wcnt6[0];	// L2991
    bool v1974 = v1973 > 0;	// L2992
    if (v1974) {	// L2993
      ap_int<26> v1975 = hp2;	// L2994
      bool v1976;
      ap_int<26> v1976_tmp = v1975;
      v1976 = v1976_tmp[25];	// L2995
      int32_t v1977 = v1976;	// L2996
      bool v1978 = v1977 == 0;	// L2997
      if (v1978) {	// L2998
        popd6 = 1;	// L2999
      } else {
        int32_t v1979 = dcred6[0];	// L3001
        bool v1980 = v1979 > 0;	// L3002
        if (v1980) {	// L3003
          ap_int<26> v1981 = hp2;	// L3004
          pw2 = v1981;	// L3005
          int32_t v1982 = dcred6[0];	// L3006
          ap_int<33> v1983 = v1982;	// L3007
          ap_int<33> v1984 = v1983 - 1;	// L3008
          int32_t v1985 = v1984;	// L3009
          dcred6[0] = v1985;	// L3010
          popd6 = 1;	// L3011
        }
      }
    }
    int32_t v1986 = popd6;	// L3015
    bool v1987 = v1986 == 1;	// L3016
    if (v1987) {	// L3017
      l_S_sft_2_sft7: for (int sft7 = 0; sft7 < 3; sft7++) {	// L3018
        ap_uint<26> v1989 = win_p2[0][(sft7 + 1)];	// L3019
        win_p2[0][sft7] = v1989;	// L3020
      }
      int32_t v1990 = wcnt6[0];	// L3022
      ap_int<33> v1991 = v1990;	// L3023
      ap_int<33> v1992 = v1991 - 1;	// L3024
      int32_t v1993 = v1992;	// L3025
      wcnt6[0] = v1993;	// L3026
    }
    int32_t v1994 = rp6[0];	// L3028
    bool v1995 = v1994 < 2000;	// L3029
    int32_t v1996 = wcnt6[0];	// L3030
    bool v1997 = v1996 < 4;	// L3031
    bool v1998 = v1995 & v1997;	// L3032
    if (v1998) {	// L3033
      ap_uint<26> cnd22;	// L3034
      cnd22 = 0;	// L3035
      int32_t v2000 = rp6[0];	// L3036
      int v2001 = v2000;	// L3037
      int32_t v2002 = v1919[0][v2001];	// L3038
      ap_uint<26> v2003 = v2002;	// L3039
      ap_int<26> v2004 = cnd22;	// L3040
      ap_int<26> v2005;
      ap_int<26> v2005_tmp = v2004;
      v2005_tmp(25, 0) = v2003;
      v2005 = v2005_tmp;	// L3041
      cnd22 = v2005;	// L3042
      ap_int<26> v2006 = cnd22;	// L3043
      int32_t v2007 = wcnt6[0];	// L3044
      int v2008 = v2007;	// L3045
      win_p2[0][v2008] = v2006;	// L3046
      int32_t v2009 = wcnt6[0];	// L3047
      ap_int<33> v2010 = v2009;	// L3048
      ap_int<33> v2011 = v2010 + 1;	// L3049
      int32_t v2012 = v2011;	// L3050
      wcnt6[0] = v2012;	// L3051
      int32_t v2013 = rp6[0];	// L3052
      ap_int<33> v2014 = v2013;	// L3053
      ap_int<33> v2015 = v2014 + 1;	// L3054
      int32_t v2016 = v2015;	// L3055
      rp6[0] = v2016;	// L3056
    }
    ap_int<26> v2017 = pw2;	// L3058
    v1921.write(v2017);	// L3059
  }
}

void rdrv_s_0(
  int32_t v2018[1][2000],
  int32_t v2019[1][1],
  hls::stream< ap_uint<26> >& v2020,
  hls::stream< int32_t >& v2021
) {
  #pragma HLS array_partition variable=v2018 complete dim=1	// L3063
  int32_t dcred7[1];	// L3073
  for (int v2023 = 0; v2023 < 1; v2023++) {	// L3074
    dcred7[v2023] = 0;	// L3074
  }
  int32_t rp7[1];	// L3075
  for (int v2025 = 0; v2025 < 1; v2025++) {	// L3076
    rp7[v2025] = 0;	// L3076
  }
  int32_t wcnt7[1];	// L3077
  for (int v2027 = 0; v2027 < 1; v2027++) {	// L3078
    wcnt7[v2027] = 0;	// L3078
  }
  ap_uint<26> win_p3[1][4];	// L3079
  for (int v2029 = 0; v2029 < 1; v2029++) {	// L3080
    for (int v2030 = 0; v2030 < 4; v2030++) {	// L3080
      win_p3[v2029][v2030] = 0;	// L3080
    }
  }
  ap_uint<26> zp3;	// L3081
  zp3 = 0;	// L3082
  int32_t v2032 = v2019[0][0];	// L3083
  ap_int<33> v2033 = v2032;	// L3084
  ap_int<33> v2034 = v2033 - 1;	// L3085
  int v2035 = v2034;	// L3086
  for (int v2036 = 0; v2036 < v2035; v2036 += 1) {	// L3087
    ap_int<26> v2037 = zp3;	// L3088
    v2020.write(v2037);	// L3089
  }
  l_S__pf_1__pf7: for (int _pf7 = 0; _pf7 < 2; _pf7++) {	// L3091
    int32_t v2039 = rp7[0];	// L3092
    bool v2040 = v2039 < 2000;	// L3093
    if (v2040) {	// L3094
      ap_uint<26> cnd3;	// L3095
      cnd3 = 0;	// L3096
      int32_t v2042 = rp7[0];	// L3097
      int v2043 = v2042;	// L3098
      int32_t v2044 = v2018[0][v2043];	// L3099
      ap_uint<26> v2045 = v2044;	// L3100
      ap_int<26> v2046 = cnd3;	// L3101
      ap_int<26> v2047;
      ap_int<26> v2047_tmp = v2046;
      v2047_tmp(25, 0) = v2045;
      v2047 = v2047_tmp;	// L3102
      cnd3 = v2047;	// L3103
      ap_int<26> v2048 = cnd3;	// L3104
      int32_t v2049 = wcnt7[0];	// L3105
      int v2050 = v2049;	// L3106
      win_p3[0][v2050] = v2048;	// L3107
      int32_t v2051 = wcnt7[0];	// L3108
      ap_int<33> v2052 = v2051;	// L3109
      ap_int<33> v2053 = v2052 + 1;	// L3110
      int32_t v2054 = v2053;	// L3111
      wcnt7[0] = v2054;	// L3112
      int32_t v2055 = rp7[0];	// L3113
      ap_int<33> v2056 = v2055;	// L3114
      ap_int<33> v2057 = v2056 + 1;	// L3115
      int32_t v2058 = v2057;	// L3116
      rp7[0] = v2058;	// L3117
    }
  }
  l_S_t_2_t12: for (int t12 = 0; t12 < 2000; t12++) {	// L3120
  #pragma HLS pipeline II=1
    int32_t v2060 = v2021.read();	// L3121
    int32_t cin7;	// L3122
    cin7 = v2060;	// L3123
    int32_t v2062 = cin7;	// L3124
    int32_t v2063 = dcred7[0];	// L3125
    ap_int<33> v2064 = v2063;	// L3126
    ap_int<33> v2065 = v2062;	// L3127
    ap_int<33> v2066 = v2064 + v2065;	// L3128
    int32_t v2067 = v2066;	// L3129
    dcred7[0] = v2067;	// L3130
    ap_uint<26> pw3;	// L3131
    pw3 = 0;	// L3132
    ap_uint<26> v2069 = win_p3[0][0];	// L3133
    ap_uint<26> hp3;	// L3134
    hp3 = v2069;	// L3135
    int32_t popd7;	// L3136
    popd7 = 0;	// L3137
    int32_t v2072 = wcnt7[0];	// L3138
    bool v2073 = v2072 > 0;	// L3139
    if (v2073) {	// L3140
      ap_int<26> v2074 = hp3;	// L3141
      bool v2075;
      ap_int<26> v2075_tmp = v2074;
      v2075 = v2075_tmp[25];	// L3142
      int32_t v2076 = v2075;	// L3143
      bool v2077 = v2076 == 0;	// L3144
      if (v2077) {	// L3145
        popd7 = 1;	// L3146
      } else {
        int32_t v2078 = dcred7[0];	// L3148
        bool v2079 = v2078 > 0;	// L3149
        if (v2079) {	// L3150
          ap_int<26> v2080 = hp3;	// L3151
          pw3 = v2080;	// L3152
          int32_t v2081 = dcred7[0];	// L3153
          ap_int<33> v2082 = v2081;	// L3154
          ap_int<33> v2083 = v2082 - 1;	// L3155
          int32_t v2084 = v2083;	// L3156
          dcred7[0] = v2084;	// L3157
          popd7 = 1;	// L3158
        }
      }
    }
    int32_t v2085 = popd7;	// L3162
    bool v2086 = v2085 == 1;	// L3163
    if (v2086) {	// L3164
      l_S_sft_2_sft8: for (int sft8 = 0; sft8 < 3; sft8++) {	// L3165
        ap_uint<26> v2088 = win_p3[0][(sft8 + 1)];	// L3166
        win_p3[0][sft8] = v2088;	// L3167
      }
      int32_t v2089 = wcnt7[0];	// L3169
      ap_int<33> v2090 = v2089;	// L3170
      ap_int<33> v2091 = v2090 - 1;	// L3171
      int32_t v2092 = v2091;	// L3172
      wcnt7[0] = v2092;	// L3173
    }
    int32_t v2093 = rp7[0];	// L3175
    bool v2094 = v2093 < 2000;	// L3176
    int32_t v2095 = wcnt7[0];	// L3177
    bool v2096 = v2095 < 4;	// L3178
    bool v2097 = v2094 & v2096;	// L3179
    if (v2097) {	// L3180
      ap_uint<26> cnd23;	// L3181
      cnd23 = 0;	// L3182
      int32_t v2099 = rp7[0];	// L3183
      int v2100 = v2099;	// L3184
      int32_t v2101 = v2018[0][v2100];	// L3185
      ap_uint<26> v2102 = v2101;	// L3186
      ap_int<26> v2103 = cnd23;	// L3187
      ap_int<26> v2104;
      ap_int<26> v2104_tmp = v2103;
      v2104_tmp(25, 0) = v2102;
      v2104 = v2104_tmp;	// L3188
      cnd23 = v2104;	// L3189
      ap_int<26> v2105 = cnd23;	// L3190
      int32_t v2106 = wcnt7[0];	// L3191
      int v2107 = v2106;	// L3192
      win_p3[0][v2107] = v2105;	// L3193
      int32_t v2108 = wcnt7[0];	// L3194
      ap_int<33> v2109 = v2108;	// L3195
      ap_int<33> v2110 = v2109 + 1;	// L3196
      int32_t v2111 = v2110;	// L3197
      wcnt7[0] = v2111;	// L3198
      int32_t v2112 = rp7[0];	// L3199
      ap_int<33> v2113 = v2112;	// L3200
      ap_int<33> v2114 = v2113 + 1;	// L3201
      int32_t v2115 = v2114;	// L3202
      rp7[0] = v2115;	// L3203
    }
    ap_int<26> v2116 = pw3;	// L3205
    v2020.write(v2116);	// L3206
  }
}

void rclc_w_0(
  int32_t v2117[1][2000],
  int32_t v2118[1][1],
  hls::stream< int32_t >& v2119,
  hls::stream< ap_uint<26> >& v2120
) {
  #pragma HLS array_partition variable=v2117 complete dim=1	// L3210
  int32_t k6[1];	// L3220
  for (int v2122 = 0; v2122 < 1; v2122++) {	// L3221
    k6[v2122] = 0;	// L3221
  }
  int32_t cret4[1];	// L3222
  for (int v2124 = 0; v2124 < 1; v2124++) {	// L3223
    cret4[v2124] = 0;	// L3223
  }
  int32_t zc4;	// L3224
  zc4 = 0;	// L3225
  int32_t v2126 = v2118[0][0];	// L3226
  ap_int<33> v2127 = v2126;	// L3227
  ap_int<33> v2128 = v2127 - 1;	// L3228
  int v2129 = v2128;	// L3229
  for (int v2130 = 0; v2130 < v2129; v2130 += 1) {	// L3230
    int32_t v2131 = zc4;	// L3231
    v2119.write(v2131);	// L3232
  }
  cret4[0] = 2;	// L3234
  int32_t v2132 = cret4[0];	// L3235
  v2119.write(v2132);	// L3236
  l_S_t_1_t13: for (int t13 = 0; t13 < 2000; t13++) {	// L3237
  #pragma HLS pipeline II=1
    ap_uint<26> v2134 = v2120.read();	// L3238
    ap_uint<26> pw4;	// L3239
    pw4 = v2134;	// L3240
    cret4[0] = 0;	// L3241
    ap_int<26> v2136 = pw4;	// L3242
    bool v2137;
    ap_int<26> v2137_tmp = v2136;
    v2137 = v2137_tmp[25];	// L3243
    int32_t v2138 = v2137;	// L3244
    bool v2139 = v2138 == 1;	// L3245
    if (v2139) {	// L3246
      cret4[0] = 1;	// L3247
      int32_t v2140 = k6[0];	// L3248
      bool v2141 = v2140 < 2000;	// L3249
      if (v2141) {	// L3250
        ap_int<26> v2142 = pw4;	// L3251
        int32_t v2143 = v2142;	// L3252
        int32_t v2144 = v2143 & 67108863;	// L3253
        int32_t v2145 = k6[0];	// L3254
        int v2146 = v2145;	// L3255
        v2117[0][v2146] = v2144;	// L3256
        int32_t v2147 = k6[0];	// L3257
        ap_int<33> v2148 = v2147;	// L3258
        ap_int<33> v2149 = v2148 + 1;	// L3259
        int32_t v2150 = v2149;	// L3260
        k6[0] = v2150;	// L3261
      }
    }
    int32_t v2151 = cret4[0];	// L3264
    v2119.write(v2151);	// L3265
  }
}

void rclc_e_0(
  int32_t v2152[1][2000],
  int32_t v2153[1][1],
  hls::stream< int32_t >& v2154,
  hls::stream< ap_uint<26> >& v2155
) {
  #pragma HLS array_partition variable=v2152 complete dim=1	// L3269
  int32_t k7[1];	// L3279
  for (int v2157 = 0; v2157 < 1; v2157++) {	// L3280
    k7[v2157] = 0;	// L3280
  }
  int32_t cret5[1];	// L3281
  for (int v2159 = 0; v2159 < 1; v2159++) {	// L3282
    cret5[v2159] = 0;	// L3282
  }
  int32_t zc5;	// L3283
  zc5 = 0;	// L3284
  int32_t v2161 = v2153[0][0];	// L3285
  ap_int<33> v2162 = v2161;	// L3286
  ap_int<33> v2163 = v2162 - 1;	// L3287
  int v2164 = v2163;	// L3288
  for (int v2165 = 0; v2165 < v2164; v2165 += 1) {	// L3289
    int32_t v2166 = zc5;	// L3290
    v2154.write(v2166);	// L3291
  }
  cret5[0] = 2;	// L3293
  int32_t v2167 = cret5[0];	// L3294
  v2154.write(v2167);	// L3295
  l_S_t_1_t14: for (int t14 = 0; t14 < 2000; t14++) {	// L3296
  #pragma HLS pipeline II=1
    ap_uint<26> v2169 = v2155.read();	// L3297
    ap_uint<26> pw5;	// L3298
    pw5 = v2169;	// L3299
    cret5[0] = 0;	// L3300
    ap_int<26> v2171 = pw5;	// L3301
    bool v2172;
    ap_int<26> v2172_tmp = v2171;
    v2172 = v2172_tmp[25];	// L3302
    int32_t v2173 = v2172;	// L3303
    bool v2174 = v2173 == 1;	// L3304
    if (v2174) {	// L3305
      cret5[0] = 1;	// L3306
      int32_t v2175 = k7[0];	// L3307
      bool v2176 = v2175 < 2000;	// L3308
      if (v2176) {	// L3309
        ap_int<26> v2177 = pw5;	// L3310
        int32_t v2178 = v2177;	// L3311
        int32_t v2179 = v2178 & 67108863;	// L3312
        int32_t v2180 = k7[0];	// L3313
        int v2181 = v2180;	// L3314
        v2152[0][v2181] = v2179;	// L3315
        int32_t v2182 = k7[0];	// L3316
        ap_int<33> v2183 = v2182;	// L3317
        ap_int<33> v2184 = v2183 + 1;	// L3318
        int32_t v2185 = v2184;	// L3319
        k7[0] = v2185;	// L3320
      }
    }
    int32_t v2186 = cret5[0];	// L3323
    v2154.write(v2186);	// L3324
  }
}

void rclc_n_0(
  int32_t v2187[1][2000],
  int32_t v2188[1][1],
  hls::stream< int32_t >& v2189,
  hls::stream< ap_uint<26> >& v2190
) {
  #pragma HLS array_partition variable=v2187 complete dim=1	// L3328
  int32_t k8[1];	// L3338
  for (int v2192 = 0; v2192 < 1; v2192++) {	// L3339
    k8[v2192] = 0;	// L3339
  }
  int32_t cret6[1];	// L3340
  for (int v2194 = 0; v2194 < 1; v2194++) {	// L3341
    cret6[v2194] = 0;	// L3341
  }
  int32_t zc6;	// L3342
  zc6 = 0;	// L3343
  int32_t v2196 = v2188[0][0];	// L3344
  ap_int<33> v2197 = v2196;	// L3345
  ap_int<33> v2198 = v2197 - 1;	// L3346
  int v2199 = v2198;	// L3347
  for (int v2200 = 0; v2200 < v2199; v2200 += 1) {	// L3348
    int32_t v2201 = zc6;	// L3349
    v2189.write(v2201);	// L3350
  }
  cret6[0] = 2;	// L3352
  int32_t v2202 = cret6[0];	// L3353
  v2189.write(v2202);	// L3354
  l_S_t_1_t15: for (int t15 = 0; t15 < 2000; t15++) {	// L3355
  #pragma HLS pipeline II=1
    ap_uint<26> v2204 = v2190.read();	// L3356
    ap_uint<26> pw6;	// L3357
    pw6 = v2204;	// L3358
    cret6[0] = 0;	// L3359
    ap_int<26> v2206 = pw6;	// L3360
    bool v2207;
    ap_int<26> v2207_tmp = v2206;
    v2207 = v2207_tmp[25];	// L3361
    int32_t v2208 = v2207;	// L3362
    bool v2209 = v2208 == 1;	// L3363
    if (v2209) {	// L3364
      cret6[0] = 1;	// L3365
      int32_t v2210 = k8[0];	// L3366
      bool v2211 = v2210 < 2000;	// L3367
      if (v2211) {	// L3368
        ap_int<26> v2212 = pw6;	// L3369
        int32_t v2213 = v2212;	// L3370
        int32_t v2214 = v2213 & 67108863;	// L3371
        int32_t v2215 = k8[0];	// L3372
        int v2216 = v2215;	// L3373
        v2187[0][v2216] = v2214;	// L3374
        int32_t v2217 = k8[0];	// L3375
        ap_int<33> v2218 = v2217;	// L3376
        ap_int<33> v2219 = v2218 + 1;	// L3377
        int32_t v2220 = v2219;	// L3378
        k8[0] = v2220;	// L3379
      }
    }
    int32_t v2221 = cret6[0];	// L3382
    v2189.write(v2221);	// L3383
  }
}

void rclc_s_0(
  int32_t v2222[1][2000],
  int32_t v2223[1][1],
  hls::stream< int32_t >& v2224,
  hls::stream< ap_uint<26> >& v2225
) {
  #pragma HLS array_partition variable=v2222 complete dim=1	// L3387
  int32_t k9[1];	// L3397
  for (int v2227 = 0; v2227 < 1; v2227++) {	// L3398
    k9[v2227] = 0;	// L3398
  }
  int32_t cret7[1];	// L3399
  for (int v2229 = 0; v2229 < 1; v2229++) {	// L3400
    cret7[v2229] = 0;	// L3400
  }
  int32_t zc7;	// L3401
  zc7 = 0;	// L3402
  int32_t v2231 = v2223[0][0];	// L3403
  ap_int<33> v2232 = v2231;	// L3404
  ap_int<33> v2233 = v2232 - 1;	// L3405
  int v2234 = v2233;	// L3406
  for (int v2235 = 0; v2235 < v2234; v2235 += 1) {	// L3407
    int32_t v2236 = zc7;	// L3408
    v2224.write(v2236);	// L3409
  }
  cret7[0] = 2;	// L3411
  int32_t v2237 = cret7[0];	// L3412
  v2224.write(v2237);	// L3413
  l_S_t_1_t16: for (int t16 = 0; t16 < 2000; t16++) {	// L3414
  #pragma HLS pipeline II=1
    ap_uint<26> v2239 = v2225.read();	// L3415
    ap_uint<26> pw7;	// L3416
    pw7 = v2239;	// L3417
    cret7[0] = 0;	// L3418
    ap_int<26> v2241 = pw7;	// L3419
    bool v2242;
    ap_int<26> v2242_tmp = v2241;
    v2242 = v2242_tmp[25];	// L3420
    int32_t v2243 = v2242;	// L3421
    bool v2244 = v2243 == 1;	// L3422
    if (v2244) {	// L3423
      cret7[0] = 1;	// L3424
      int32_t v2245 = k9[0];	// L3425
      bool v2246 = v2245 < 2000;	// L3426
      if (v2246) {	// L3427
        ap_int<26> v2247 = pw7;	// L3428
        int32_t v2248 = v2247;	// L3429
        int32_t v2249 = v2248 & 67108863;	// L3430
        int32_t v2250 = k9[0];	// L3431
        int v2251 = v2250;	// L3432
        v2222[0][v2251] = v2249;	// L3433
        int32_t v2252 = k9[0];	// L3434
        ap_int<33> v2253 = v2252;	// L3435
        ap_int<33> v2254 = v2253 + 1;	// L3436
        int32_t v2255 = v2254;	// L3437
        k9[0] = v2255;	// L3438
      }
    }
    int32_t v2256 = cret7[0];	// L3441
    v2224.write(v2256);	// L3442
  }
}

/// This is top function.
void top(
  int32_t v2257[1][1],
  int16_t v2258[1][2000],
  int32_t v2259[1][2000],
  int16_t v2260[1][2000],
  int32_t v2261[1][2000],
  int16_t v2262[1][2000],
  int32_t v2263[1][2000],
  int16_t v2264[1][2000],
  int32_t v2265[1][2000],
  int16_t v2266[1][2000],
  int16_t v2267[1][2000],
  int16_t v2268[1][2000],
  int16_t v2269[1][2000],
  int32_t v2270[1][2000],
  int32_t v2271[1][2000],
  int32_t v2272[1][2000],
  int32_t v2273[1][2000],
  int32_t v2274[1][2000],
  int32_t v2275[1][2000],
  int32_t v2276[1][2000],
  int32_t v2277[1][2000]
) {	// L3446
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v2278;
  #pragma HLS stream variable=v2278 depth=8	// L3447
  hls::stream< ap_uint<17> > v2279;
  #pragma HLS stream variable=v2279 depth=8	// L3448
  hls::stream< ap_uint<17> > v2280;
  #pragma HLS stream variable=v2280 depth=8	// L3449
  hls::stream< ap_uint<17> > v2281;
  #pragma HLS stream variable=v2281 depth=8	// L3450
  hls::stream< ap_uint<17> > v2282;
  #pragma HLS stream variable=v2282 depth=8	// L3451
  hls::stream< ap_uint<17> > v2283;
  #pragma HLS stream variable=v2283 depth=8	// L3452
  hls::stream< ap_uint<17> > v2284;
  #pragma HLS stream variable=v2284 depth=8	// L3453
  hls::stream< ap_uint<17> > v2285;
  #pragma HLS stream variable=v2285 depth=8	// L3454
  hls::stream< ap_uint<26> > v2286;
  #pragma HLS stream variable=v2286 depth=8	// L3455
  hls::stream< ap_uint<26> > v2287;
  #pragma HLS stream variable=v2287 depth=8	// L3456
  hls::stream< ap_uint<26> > v2288;
  #pragma HLS stream variable=v2288 depth=8	// L3457
  hls::stream< ap_uint<26> > v2289;
  #pragma HLS stream variable=v2289 depth=8	// L3458
  hls::stream< ap_uint<26> > v2290;
  #pragma HLS stream variable=v2290 depth=8	// L3459
  hls::stream< ap_uint<26> > v2291;
  #pragma HLS stream variable=v2291 depth=8	// L3460
  hls::stream< ap_uint<26> > v2292;
  #pragma HLS stream variable=v2292 depth=8	// L3461
  hls::stream< ap_uint<26> > v2293;
  #pragma HLS stream variable=v2293 depth=8	// L3462
  hls::stream< int32_t > v2294;
  #pragma HLS stream variable=v2294 depth=8	// L3463
  hls::stream< int32_t > v2295;
  #pragma HLS stream variable=v2295 depth=8	// L3464
  hls::stream< int32_t > v2296;
  #pragma HLS stream variable=v2296 depth=8	// L3465
  hls::stream< int32_t > v2297;
  #pragma HLS stream variable=v2297 depth=8	// L3466
  hls::stream< int32_t > v2298;
  #pragma HLS stream variable=v2298 depth=8	// L3467
  hls::stream< int32_t > v2299;
  #pragma HLS stream variable=v2299 depth=8	// L3468
  hls::stream< int32_t > v2300;
  #pragma HLS stream variable=v2300 depth=8	// L3469
  hls::stream< int32_t > v2301;
  #pragma HLS stream variable=v2301 depth=8	// L3470
  hls::stream< int32_t > v2302;
  #pragma HLS stream variable=v2302 depth=8	// L3471
  hls::stream< int32_t > v2303;
  #pragma HLS stream variable=v2303 depth=8	// L3472
  hls::stream< int32_t > v2304;
  #pragma HLS stream variable=v2304 depth=8	// L3473
  hls::stream< int32_t > v2305;
  #pragma HLS stream variable=v2305 depth=8	// L3474
  hls::stream< int32_t > v2306;
  #pragma HLS stream variable=v2306 depth=8	// L3475
  hls::stream< int32_t > v2307;
  #pragma HLS stream variable=v2307 depth=8	// L3476
  hls::stream< int32_t > v2308;
  #pragma HLS stream variable=v2308 depth=8	// L3477
  hls::stream< int32_t > v2309;
  #pragma HLS stream variable=v2309 depth=8	// L3478
  node_0_0(v2257, v2287, v2288, v2291, v2292, v2279, v2280, v2283, v2284, v2294, v2297, v2298, v2301, v2302, v2305, v2306, v2309, v2286, v2289, v2290, v2293, v2295, v2296, v2299, v2300, v2308, v2307, v2304, v2303, v2278, v2281, v2282, v2285);	// L3479
  drv_w_0(v2258, v2259, v2257, v2278, v2302);	// L3480
  drv_e_0(v2260, v2261, v2257, v2281, v2305);	// L3481
  drv_n_0(v2262, v2263, v2257, v2282, v2306);	// L3482
  drv_s_0(v2264, v2265, v2257, v2285, v2309);	// L3483
  col_w_0(v2266, v2257, v2304, v2280);	// L3484
  col_e_0(v2267, v2257, v2303, v2279);	// L3485
  col_n_0(v2268, v2257, v2308, v2284);	// L3486
  col_s_0(v2269, v2257, v2307, v2283);	// L3487
  rdrv_w_0(v2270, v2257, v2286, v2294);	// L3488
  rdrv_e_0(v2271, v2257, v2289, v2297);	// L3489
  rdrv_n_0(v2272, v2257, v2290, v2298);	// L3490
  rdrv_s_0(v2273, v2257, v2293, v2301);	// L3491
  rclc_w_0(v2274, v2257, v2296, v2288);	// L3492
  rclc_e_0(v2275, v2257, v2295, v2287);	// L3493
  rclc_n_0(v2276, v2257, v2300, v2292);	// L3494
  rclc_s_0(v2277, v2257, v2299, v2291);	// L3495
}

