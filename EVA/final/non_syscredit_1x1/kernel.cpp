
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
  int32_t v0[1][1][200],
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
  hls::stream< ap_uint<26> >& v13,
  hls::stream< ap_uint<26> >& v14,
  hls::stream< ap_uint<26> >& v15,
  hls::stream< ap_uint<26> >& v16,
  hls::stream< int32_t >& v17,
  hls::stream< int32_t >& v18,
  hls::stream< int32_t >& v19,
  hls::stream< int32_t >& v20,
  hls::stream< ap_uint<17> >& v21,
  hls::stream< ap_uint<17> >& v22,
  hls::stream< ap_uint<17> >& v23,
  hls::stream< ap_uint<17> >& v24
) {	// L4
  int32_t irf[8];	// L47
  #pragma HLS array_partition variable=irf complete dim=1

  for (int v26 = 0; v26 < 8; v26++) {	// L48
    irf[v26] = 0;	// L48
  }
  half drf[8];	// L49
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v28 = 0; v28 < 8; v28++) {	// L50
    drf[v28] = 0.000000;	// L50
  }
  int32_t drf_full[8];	// L51
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v30 = 0; v30 < 8; v30++) {	// L52
    drf_full[v30] = 0;	// L52
  }
  int32_t dsmask;	// L53
  dsmask = 0;	// L54
  int32_t crv_vld;	// L55
  crv_vld = 0;	// L56
  half crv_data;	// L57
  crv_data = 0.000000;	// L58
  int32_t crv_addr;	// L59
  crv_addr = 0;	// L60
  int32_t crv_mode;	// L61
  crv_mode = 0;	// L62
  int32_t crv_raw;	// L63
  crv_raw = 0;	// L64
  int32_t csd_vld;	// L65
  csd_vld = 0;	// L66
  ap_uint<26> csd_pkt;	// L67
  csd_pkt = 0;	// L68
  int32_t csd_dir;	// L69
  csd_dir = 0;	// L70
  int32_t row_id;	// L71
  row_id = 0;	// L72
  int32_t col_id;	// L73
  col_id = 0;	// L74
  ap_uint<26> oe_r;	// L75
  oe_r = 0;	// L76
  ap_uint<26> ow_r;	// L77
  ow_r = 0;	// L78
  ap_uint<26> on_r;	// L79
  on_r = 0;	// L80
  ap_uint<26> os_r;	// L81
  os_r = 0;	// L82
  ap_uint<17> txn_r;	// L83
  txn_r = 0;	// L84
  ap_uint<17> txs_r;	// L85
  txs_r = 0;	// L86
  ap_uint<17> txw_r;	// L87
  txw_r = 0;	// L88
  ap_uint<17> txe_r;	// L89
  txe_r = 0;	// L90
  half hold_v[4][2];	// L91
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v51 = 0; v51 < 4; v51++) {	// L92
    for (int v52 = 0; v52 < 2; v52++) {	// L92
      hold_v[v51][v52] = 0.000000;	// L92
    }
  }
  uint8_t hold_cnt[4];	// L93
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v54 = 0; v54 < 4; v54++) {	// L94
    hold_cnt[v54] = 0;	// L94
  }
  ap_uint<26> rbuf[4][2];	// L95
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v56 = 0; v56 < 4; v56++) {	// L96
    for (int v57 = 0; v57 < 2; v57++) {	// L96
      rbuf[v56][v57] = 0;	// L96
    }
  }
  uint8_t rbcnt[4];	// L97
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v59 = 0; v59 < 4; v59++) {	// L98
    rbcnt[v59] = 0;	// L98
  }
  uint8_t rcred[4];	// L99
  #pragma HLS array_partition variable=rcred complete dim=1

  for (int v61 = 0; v61 < 4; v61++) {	// L100
    rcred[v61] = 0;	// L100
  }
  uint8_t cre_r;	// L101
  cre_r = 2;	// L102
  uint8_t crw_r;	// L103
  crw_r = 2;	// L104
  uint8_t crs_r;	// L105
  crs_r = 2;	// L106
  uint8_t crn_r;	// L107
  crn_r = 2;	// L108
  int32_t cfg_isz;	// L109
  cfg_isz = 0;	// L110
  int32_t cfg_itsz;	// L111
  cfg_itsz = 0;	// L112
  uint8_t fetch_en;	// L113
  fetch_en = 0;	// L114
  uint8_t instr_cnt;	// L115
  instr_cnt = 0;	// L116
  uint8_t iter_cnt;	// L117
  iter_cnt = 0;	// L118
  uint8_t condition_reg;	// L119
  condition_reg = 0;	// L120
  uint8_t sb_v[5];	// L121
  #pragma HLS array_partition variable=sb_v complete dim=1

  for (int v73 = 0; v73 < 5; v73++) {	// L122
    sb_v[v73] = 0;	// L122
  }
  uint8_t sb_dst[5];	// L123
  #pragma HLS array_partition variable=sb_dst complete dim=1

  for (int v75 = 0; v75 < 5; v75++) {	// L124
    sb_dst[v75] = 0;	// L124
  }
  uint8_t sb_cmp[5];	// L125
  #pragma HLS array_partition variable=sb_cmp complete dim=1

  for (int v77 = 0; v77 < 5; v77++) {	// L126
    sb_cmp[v77] = 0;	// L126
  }
  uint8_t sb_rtr[5];	// L127
  #pragma HLS array_partition variable=sb_rtr complete dim=1

  for (int v79 = 0; v79 < 5; v79++) {	// L128
    sb_rtr[v79] = 0;	// L128
  }
  uint8_t sb_inj[5];	// L129
  #pragma HLS array_partition variable=sb_inj complete dim=1

  for (int v81 = 0; v81 < 5; v81++) {	// L130
    sb_inj[v81] = 0;	// L130
  }
  uint8_t sb_dir[5];	// L131
  #pragma HLS array_partition variable=sb_dir complete dim=1

  for (int v83 = 0; v83 < 5; v83++) {	// L132
    sb_dir[v83] = 0;	// L132
  }
  uint8_t sb_id[5];	// L133
  #pragma HLS array_partition variable=sb_id complete dim=1

  for (int v85 = 0; v85 < 5; v85++) {	// L134
    sb_id[v85] = 0;	// L134
  }
  uint8_t sb_rvld[5];	// L135
  #pragma HLS array_partition variable=sb_rvld complete dim=1

  for (int v87 = 0; v87 < 5; v87++) {	// L136
    sb_rvld[v87] = 0;	// L136
  }
  uint8_t sb_ix[5];	// L137
  #pragma HLS array_partition variable=sb_ix complete dim=1

  for (int v89 = 0; v89 < 5; v89++) {	// L138
    sb_ix[v89] = 0;	// L138
  }
  uint8_t sb_long[5];	// L139
  #pragma HLS array_partition variable=sb_long complete dim=1

  for (int v91 = 0; v91 < 5; v91++) {	// L140
    sb_long[v91] = 0;	// L140
  }
  half resq[8];	// L141
  #pragma HLS array_partition variable=resq complete dim=1
#pragma HLS dependence variable=resq type=inter dependent=false

  for (int v93 = 0; v93 < 8; v93++) {	// L142
    resq[v93] = 0.000000;	// L142
  }
  half resq_fwd[8];	// L143
  #pragma HLS array_partition variable=resq_fwd complete dim=1

  for (int v95 = 0; v95 < 8; v95++) {	// L144
    resq_fwd[v95] = 0.000000;	// L144
  }
  uint8_t cmpq[8];	// L145
  #pragma HLS array_partition variable=cmpq complete dim=1
#pragma HLS dependence variable=cmpq type=inter dependent=false

  for (int v97 = 0; v97 < 8; v97++) {	// L146
    cmpq[v97] = 0;	// L146
  }
  uint8_t resq_wr;	// L147
  resq_wr = 0;	// L148
  ap_uint<26> zpkt;	// L149
  zpkt = 0;	// L150
  ap_uint<17> zsys;	// L151
  zsys = 0;	// L152
  int32_t zcr;	// L153
  zcr = 0;	// L154
  ap_int<26> v102 = zpkt;	// L155
  v1.write(v102);	// L156
  ap_int<26> v103 = zpkt;	// L157
  v2.write(v103);	// L158
  ap_int<26> v104 = zpkt;	// L159
  v3.write(v104);	// L160
  ap_int<26> v105 = zpkt;	// L161
  v4.write(v105);	// L162
  ap_int<17> v106 = zsys;	// L163
  v5.write(v106);	// L164
  ap_int<17> v107 = zsys;	// L165
  v6.write(v107);	// L166
  ap_int<17> v108 = zsys;	// L167
  v7.write(v108);	// L168
  ap_int<17> v109 = zsys;	// L169
  v8.write(v109);	// L170
  int32_t v110 = zcr;	// L171
  v9.write(v110);	// L172
  int32_t v111 = zcr;	// L173
  v10.write(v111);	// L174
  int32_t v112 = zcr;	// L175
  v11.write(v112);	// L176
  int32_t v113 = zcr;	// L177
  v12.write(v113);	// L178
  ap_int<26> v114 = zpkt;	// L179
  v1.write(v114);	// L180
  ap_int<26> v115 = zpkt;	// L181
  v2.write(v115);	// L182
  ap_int<26> v116 = zpkt;	// L183
  v3.write(v116);	// L184
  ap_int<26> v117 = zpkt;	// L185
  v4.write(v117);	// L186
  ap_int<17> v118 = zsys;	// L187
  v5.write(v118);	// L188
  ap_int<17> v119 = zsys;	// L189
  v6.write(v119);	// L190
  ap_int<17> v120 = zsys;	// L191
  v7.write(v120);	// L192
  ap_int<17> v121 = zsys;	// L193
  v8.write(v121);	// L194
  int32_t v122 = zcr;	// L195
  v9.write(v122);	// L196
  int32_t v123 = zcr;	// L197
  v10.write(v123);	// L198
  int32_t v124 = zcr;	// L199
  v11.write(v124);	// L200
  int32_t v125 = zcr;	// L201
  v12.write(v125);	// L202
  ap_int<26> v126 = zpkt;	// L203
  v1.write(v126);	// L204
  ap_int<26> v127 = zpkt;	// L205
  v2.write(v127);	// L206
  ap_int<26> v128 = zpkt;	// L207
  v3.write(v128);	// L208
  ap_int<26> v129 = zpkt;	// L209
  v4.write(v129);	// L210
  ap_int<17> v130 = zsys;	// L211
  v5.write(v130);	// L212
  ap_int<17> v131 = zsys;	// L213
  v6.write(v131);	// L214
  ap_int<17> v132 = zsys;	// L215
  v7.write(v132);	// L216
  ap_int<17> v133 = zsys;	// L217
  v8.write(v133);	// L218
  int32_t v134 = zcr;	// L219
  v9.write(v134);	// L220
  int32_t v135 = zcr;	// L221
  v10.write(v135);	// L222
  int32_t v136 = zcr;	// L223
  v11.write(v136);	// L224
  int32_t v137 = zcr;	// L225
  v12.write(v137);	// L226
  ap_int<26> v138 = zpkt;	// L227
  v1.write(v138);	// L228
  ap_int<26> v139 = zpkt;	// L229
  v2.write(v139);	// L230
  ap_int<26> v140 = zpkt;	// L231
  v3.write(v140);	// L232
  ap_int<26> v141 = zpkt;	// L233
  v4.write(v141);	// L234
  ap_int<17> v142 = zsys;	// L235
  v5.write(v142);	// L236
  ap_int<17> v143 = zsys;	// L237
  v6.write(v143);	// L238
  ap_int<17> v144 = zsys;	// L239
  v7.write(v144);	// L240
  ap_int<17> v145 = zsys;	// L241
  v8.write(v145);	// L242
  int32_t v146 = zcr;	// L243
  v9.write(v146);	// L244
  int32_t v147 = zcr;	// L245
  v10.write(v147);	// L246
  int32_t v148 = zcr;	// L247
  v11.write(v148);	// L248
  int32_t v149 = zcr;	// L249
  v12.write(v149);	// L250
  ap_int<26> v150 = zpkt;	// L251
  v1.write(v150);	// L252
  ap_int<26> v151 = zpkt;	// L253
  v2.write(v151);	// L254
  ap_int<26> v152 = zpkt;	// L255
  v3.write(v152);	// L256
  ap_int<26> v153 = zpkt;	// L257
  v4.write(v153);	// L258
  ap_int<17> v154 = zsys;	// L259
  v5.write(v154);	// L260
  ap_int<17> v155 = zsys;	// L261
  v6.write(v155);	// L262
  ap_int<17> v156 = zsys;	// L263
  v7.write(v156);	// L264
  ap_int<17> v157 = zsys;	// L265
  v8.write(v157);	// L266
  int32_t v158 = zcr;	// L267
  v9.write(v158);	// L268
  int32_t v159 = zcr;	// L269
  v10.write(v159);	// L270
  int32_t v160 = zcr;	// L271
  v11.write(v160);	// L272
  int32_t v161 = zcr;	// L273
  v12.write(v161);	// L274
  ap_int<26> v162 = oe_r;	// L275
  v1.write(v162);	// L276
  ap_int<26> v163 = ow_r;	// L277
  v2.write(v163);	// L278
  ap_int<26> v164 = os_r;	// L279
  v3.write(v164);	// L280
  ap_int<26> v165 = on_r;	// L281
  v4.write(v165);	// L282
  ap_int<17> v166 = txe_r;	// L283
  v5.write(v166);	// L284
  ap_int<17> v167 = txw_r;	// L285
  v6.write(v167);	// L286
  ap_int<17> v168 = txs_r;	// L287
  v7.write(v168);	// L288
  ap_int<17> v169 = txn_r;	// L289
  v8.write(v169);	// L290
  int8_t v170 = cre_r;	// L291
  v9.write(v170);	// L292
  int8_t v171 = crw_r;	// L293
  v10.write(v171);	// L294
  int8_t v172 = crs_r;	// L295
  v11.write(v172);	// L296
  int8_t v173 = crn_r;	// L297
  v12.write(v173);	// L298
  l_S_t_0_t: for (int t = 0; t < 200; t++) {	// L299
  #pragma HLS pipeline II=1
    ap_uint<26> v175 = v13.read();	// L300
    ap_uint<26> p_w;	// L301
    p_w = v175;	// L302
    ap_uint<26> v177 = v14.read();	// L303
    ap_uint<26> p_e;	// L304
    p_e = v177;	// L305
    ap_uint<26> v179 = v15.read();	// L306
    ap_uint<26> p_n;	// L307
    p_n = v179;	// L308
    ap_uint<26> v181 = v16.read();	// L309
    ap_uint<26> p_s;	// L310
    p_s = v181;	// L311
    int32_t v183 = v17.read();	// L312
    uint8_t v184 = rcred[0];	// L313
    ap_int<33> v185 = v184;	// L314
    ap_int<33> v186 = v183;	// L315
    ap_int<33> v187 = v185 + v186;	// L316
    uint8_t v188 = v187;	// L317
    rcred[0] = v188;	// L318
    int32_t v189 = v18.read();	// L319
    uint8_t v190 = rcred[1];	// L320
    ap_int<33> v191 = v190;	// L321
    ap_int<33> v192 = v189;	// L322
    ap_int<33> v193 = v191 + v192;	// L323
    uint8_t v194 = v193;	// L324
    rcred[1] = v194;	// L325
    int32_t v195 = v19.read();	// L326
    uint8_t v196 = rcred[2];	// L327
    ap_int<33> v197 = v196;	// L328
    ap_int<33> v198 = v195;	// L329
    ap_int<33> v199 = v197 + v198;	// L330
    uint8_t v200 = v199;	// L331
    rcred[2] = v200;	// L332
    int32_t v201 = v20.read();	// L333
    uint8_t v202 = rcred[3];	// L334
    ap_int<33> v203 = v202;	// L335
    ap_int<33> v204 = v201;	// L336
    ap_int<33> v205 = v203 + v204;	// L337
    uint8_t v206 = v205;	// L338
    rcred[3] = v206;	// L339
    ap_uint<26> fin[4];	// L340
    for (int v208 = 0; v208 < 4; v208++) {	// L341
      fin[v208] = 0;	// L341
    }
    ap_int<26> v209 = p_w;	// L342
    fin[0] = v209;	// L343
    ap_int<26> v210 = p_e;	// L344
    fin[1] = v210;	// L345
    ap_int<26> v211 = p_n;	// L346
    fin[2] = v211;	// L347
    ap_int<26> v212 = p_s;	// L348
    fin[3] = v212;	// L349
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L350
      ap_uint<26> v214 = fin[d];	// L351
      bool v215;
      ap_int<26> v215_tmp = v214;
      v215 = v215_tmp[25];	// L352
      int32_t v216 = v215;	// L353
      bool v217 = v216 == 1;	// L354
      uint8_t v218 = rbcnt[d];	// L355
      int32_t v219 = v218;	// L356
      bool v220 = v219 < 2;	// L357
      bool v221 = v217 & v220;	// L358
      if (v221) {	// L359
        ap_uint<26> v222 = fin[d];	// L360
        uint8_t v223 = rbcnt[d];	// L361
        int v224 = v223;	// L362
        rbuf[d][v224] = v222;	// L363
        uint8_t v225 = rbcnt[d];	// L364
        ap_int<33> v226 = v225;	// L365
        ap_int<33> v227 = v226 + 1;	// L366
        uint8_t v228 = v227;	// L367
        rbcnt[d] = v228;	// L368
      }
    }
    ap_uint<26> hd[4];	// L371
    for (int v230 = 0; v230 < 4; v230++) {	// L372
      hd[v230] = 0;	// L372
    }
    int32_t hvld[4];	// L373
    for (int v232 = 0; v232 < 4; v232++) {	// L374
      hvld[v232] = 0;	// L374
    }
    int32_t hit[4];	// L375
    for (int v234 = 0; v234 < 4; v234++) {	// L376
      hit[v234] = 0;	// L376
    }
    int32_t axis[4];	// L377
    for (int v236 = 0; v236 < 4; v236++) {	// L378
      axis[v236] = 0;	// L378
    }
    int32_t v237 = col_id;	// L379
    axis[0] = v237;	// L380
    int32_t v238 = col_id;	// L381
    axis[1] = v238;	// L382
    int32_t v239 = row_id;	// L383
    axis[2] = v239;	// L384
    int32_t v240 = row_id;	// L385
    axis[3] = v240;	// L386
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L387
      uint8_t v242 = rbcnt[d1];	// L388
      int32_t v243 = v242;	// L389
      bool v244 = v243 > 0;	// L390
      if (v244) {	// L391
        ap_uint<26> v245 = rbuf[d1][0];	// L392
        hd[d1] = v245;	// L393
        hvld[d1] = 1;	// L394
        ap_uint<26> v246 = hd[d1];	// L395
        ap_int<4> v247;
        ap_int<26> v247_tmp = v246;
        v247 = v247_tmp(24, 21);	// L396
        int32_t v248 = axis[d1];	// L397
        int32_t v249 = v247;	// L398
        bool v250 = v249 == v248;	// L399
        if (v250) {	// L400
          hit[d1] = 1;	// L401
        }
      }
    }
    ap_uint<26> o_crv;	// L405
    o_crv = 0;	// L406
    int32_t crv_in;	// L407
    crv_in = -1;	// L408
    int32_t v253 = hit[3];	// L409
    bool v254 = v253 == 1;	// L410
    if (v254) {	// L411
      ap_uint<26> v255 = hd[3];	// L412
      o_crv = v255;	// L413
      crv_in = 3;	// L414
    } else {
      int32_t v256 = hit[2];	// L416
      bool v257 = v256 == 1;	// L417
      if (v257) {	// L418
        ap_uint<26> v258 = hd[2];	// L419
        o_crv = v258;	// L420
        crv_in = 2;	// L421
      } else {
        int32_t v259 = hit[1];	// L423
        bool v260 = v259 == 1;	// L424
        if (v260) {	// L425
          ap_uint<26> v261 = hd[1];	// L426
          o_crv = v261;	// L427
          crv_in = 1;	// L428
        } else {
          int32_t v262 = hit[0];	// L430
          bool v263 = v262 == 1;	// L431
          if (v263) {	// L432
            ap_uint<26> v264 = hd[0];	// L433
            o_crv = v264;	// L434
            crv_in = 0;	// L435
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L440
    for (int v266 = 0; v266 < 4; v266++) {	// L441
      o_out[v266] = 0;	// L441
    }
    int32_t pop[4];	// L442
    for (int v268 = 0; v268 < 4; v268++) {	// L443
      pop[v268] = 0;	// L443
    }
    int32_t inj_done;	// L444
    inj_done = 0;	// L445
    int32_t idir;	// L446
    idir = -1;	// L447
    ap_int<26> v271 = csd_pkt;	// L448
    bool v272;
    ap_int<26> v272_tmp = v271;
    v272 = v272_tmp[25];	// L449
    int32_t v273 = v272;	// L450
    bool v274 = v273 == 1;	// L451
    if (v274) {	// L452
      int32_t v275 = csd_dir;	// L453
      ap_int<33> v276 = v275;	// L454
      ap_int<33> v277 = 3 - v276;	// L455
      int32_t v278 = v277;	// L456
      idir = v278;	// L457
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L459
      uint8_t v280 = rcred[o];	// L460
      int32_t v281 = v280;	// L461
      bool v282 = v281 > 0;	// L462
      if (v282) {	// L463
        int32_t v283 = idir;	// L464
        ap_int<33> v284 = v283;	// L465
        ap_int<33> v285 = o;	// L466
        bool v286 = v284 == v285;	// L467
        if (v286) {	// L468
          ap_int<26> v287 = csd_pkt;	// L469
          o_out[o] = v287;	// L470
          uint8_t v288 = rcred[o];	// L471
          ap_int<33> v289 = v288;	// L472
          ap_int<33> v290 = v289 - 1;	// L473
          uint8_t v291 = v290;	// L474
          rcred[o] = v291;	// L475
          inj_done = 1;	// L476
        } else {
          int32_t v292 = hvld[o];	// L478
          bool v293 = v292 == 1;	// L479
          int32_t v294 = hit[o];	// L480
          bool v295 = v294 == 0;	// L481
          bool v296 = v293 & v295;	// L482
          if (v296) {	// L483
            ap_uint<26> v297 = hd[o];	// L484
            o_out[o] = v297;	// L485
            uint8_t v298 = rcred[o];	// L486
            ap_int<33> v299 = v298;	// L487
            ap_int<33> v300 = v299 - 1;	// L488
            uint8_t v301 = v300;	// L489
            rcred[o] = v301;	// L490
            pop[o] = 1;	// L491
          }
        }
      }
    }
    int32_t v302 = crv_in;	// L496
    bool v303 = v302 >= 0;	// L497
    if (v303) {	// L498
      int32_t v304 = crv_in;	// L499
      int v305 = v304;	// L500
      pop[v305] = 1;	// L501
    }
    int32_t ret[4];	// L503
    for (int v307 = 0; v307 < 4; v307++) {	// L504
      ret[v307] = 0;	// L504
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L505
      int32_t v309 = pop[d2];	// L506
      bool v310 = v309 == 1;	// L507
      if (v310) {	// L508
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L509
          ap_uint<26> v312 = rbuf[d2][(sft + 1)];	// L510
          rbuf[d2][sft] = v312;	// L511
        }
        uint8_t v313 = rbcnt[d2];	// L513
        ap_int<33> v314 = v313;	// L514
        ap_int<33> v315 = v314 - 1;	// L515
        uint8_t v316 = v315;	// L516
        rbcnt[d2] = v316;	// L517
        ret[d2] = 1;	// L518
      }
    }
    int32_t v317 = ret[0];	// L521
    uint8_t v318 = v317;	// L522
    cre_r = v318;	// L523
    int32_t v319 = ret[1];	// L524
    uint8_t v320 = v319;	// L525
    crw_r = v320;	// L526
    int32_t v321 = ret[2];	// L527
    uint8_t v322 = v321;	// L528
    crs_r = v322;	// L529
    int32_t v323 = ret[3];	// L530
    uint8_t v324 = v323;	// L531
    crn_r = v324;	// L532
    ap_uint<26> v325 = o_out[0];	// L533
    oe_r = v325;	// L534
    ap_uint<26> v326 = o_out[1];	// L535
    ow_r = v326;	// L536
    ap_uint<26> v327 = o_out[2];	// L537
    os_r = v327;	// L538
    ap_uint<26> v328 = o_out[3];	// L539
    on_r = v328;	// L540
    int32_t v329 = inj_done;	// L541
    bool v330 = v329 == 1;	// L542
    if (v330) {	// L543
      csd_pkt = 0;	// L544
    }
    ap_int<26> v331 = o_crv;	// L546
    bool v332;
    ap_int<26> v332_tmp = v331;
    v332 = v332_tmp[25];	// L547
    int32_t v333 = v332;	// L548
    crv_vld = v333;	// L549
    ap_int<26> v334 = o_crv;	// L550
    int16_t v335;
    ap_int<26> v335_tmp = v334;
    v335 = v335_tmp(15, 0);	// L551
    half v336;
    union { uint16_t from; half to;} _converter_v335_to_v336 = {};
    _converter_v335_to_v336.from = v335;
    v336 = _converter_v335_to_v336.to;	// L552
    crv_data = v336;	// L553
    ap_int<26> v337 = o_crv;	// L554
    ap_int<4> v338;
    ap_int<26> v338_tmp = v337;
    v338 = v338_tmp(19, 16);	// L555
    int32_t v339 = v338;	// L556
    crv_addr = v339;	// L557
    ap_int<26> v340 = o_crv;	// L558
    bool v341;
    ap_int<26> v341_tmp = v340;
    v341 = v341_tmp[20];	// L559
    int32_t v342 = v341;	// L560
    crv_mode = v342;	// L561
    ap_int<26> v343 = o_crv;	// L562
    int16_t v344;
    ap_int<26> v344_tmp = v343;
    v344 = v344_tmp(15, 0);	// L563
    int32_t v345 = v344;	// L564
    crv_raw = v345;	// L565
    ap_uint<17> v346 = v21.read();	// L566
    ap_uint<17> rx_w;	// L567
    rx_w = v346;	// L568
    ap_uint<17> v348 = v22.read();	// L569
    ap_uint<17> rx_e;	// L570
    rx_e = v348;	// L571
    ap_uint<17> v350 = v23.read();	// L572
    ap_uint<17> rx_n;	// L573
    rx_n = v350;	// L574
    ap_uint<17> v352 = v24.read();	// L575
    ap_uint<17> rx_s;	// L576
    rx_s = v352;	// L577
    half rxv[4];	// L578
    for (int v355 = 0; v355 < 4; v355++) {	// L579
      rxv[v355] = 0.000000;	// L579
    }
    int32_t rxvld[4];	// L580
    for (int v357 = 0; v357 < 4; v357++) {	// L581
      rxvld[v357] = 0;	// L581
    }
    ap_int<17> v358 = rx_n;	// L582
    int16_t v359;
    ap_int<17> v359_tmp = v358;
    v359 = v359_tmp(16, 1);	// L583
    half v360;
    union { uint16_t from; half to;} _converter_v359_to_v360 = {};
    _converter_v359_to_v360.from = v359;
    v360 = _converter_v359_to_v360.to;	// L584
    rxv[0] = v360;	// L585
    ap_int<17> v361 = rx_n;	// L586
    bool v362;
    ap_int<17> v362_tmp = v361;
    v362 = v362_tmp[0];	// L587
    int32_t v363 = v362;	// L588
    rxvld[0] = v363;	// L589
    ap_int<17> v364 = rx_s;	// L590
    int16_t v365;
    ap_int<17> v365_tmp = v364;
    v365 = v365_tmp(16, 1);	// L591
    half v366;
    union { uint16_t from; half to;} _converter_v365_to_v366 = {};
    _converter_v365_to_v366.from = v365;
    v366 = _converter_v365_to_v366.to;	// L592
    rxv[1] = v366;	// L593
    ap_int<17> v367 = rx_s;	// L594
    bool v368;
    ap_int<17> v368_tmp = v367;
    v368 = v368_tmp[0];	// L595
    int32_t v369 = v368;	// L596
    rxvld[1] = v369;	// L597
    ap_int<17> v370 = rx_w;	// L598
    int16_t v371;
    ap_int<17> v371_tmp = v370;
    v371 = v371_tmp(16, 1);	// L599
    half v372;
    union { uint16_t from; half to;} _converter_v371_to_v372 = {};
    _converter_v371_to_v372.from = v371;
    v372 = _converter_v371_to_v372.to;	// L600
    rxv[2] = v372;	// L601
    ap_int<17> v373 = rx_w;	// L602
    bool v374;
    ap_int<17> v374_tmp = v373;
    v374 = v374_tmp[0];	// L603
    int32_t v375 = v374;	// L604
    rxvld[2] = v375;	// L605
    ap_int<17> v376 = rx_e;	// L606
    int16_t v377;
    ap_int<17> v377_tmp = v376;
    v377 = v377_tmp(16, 1);	// L607
    half v378;
    union { uint16_t from; half to;} _converter_v377_to_v378 = {};
    _converter_v377_to_v378.from = v377;
    v378 = _converter_v377_to_v378.to;	// L608
    rxv[3] = v378;	// L609
    ap_int<17> v379 = rx_e;	// L610
    bool v380;
    ap_int<17> v380_tmp = v379;
    v380 = v380_tmp[0];	// L611
    int32_t v381 = v380;	// L612
    rxvld[3] = v381;	// L613
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L614
      int32_t v383 = rxvld[d3];	// L615
      bool v384 = v383 == 1;	// L616
      uint8_t v385 = hold_cnt[d3];	// L617
      int32_t v386 = v385;	// L618
      bool v387 = v386 < 2;	// L619
      bool v388 = v384 & v387;	// L620
      if (v388) {	// L621
        half v389 = rxv[d3];	// L622
        uint8_t v390 = hold_cnt[d3];	// L623
        int v391 = v390;	// L624
        hold_v[d3][v391] = v389;	// L625
        uint8_t v392 = hold_cnt[d3];	// L626
        ap_int<33> v393 = v392;	// L627
        ap_int<33> v394 = v393 + 1;	// L628
        uint8_t v395 = v394;	// L629
        hold_cnt[d3] = v395;	// L630
      }
    }
    ap_uint<17> tx_n;	// L633
    tx_n = 0;	// L634
    ap_uint<17> tx_s;	// L635
    tx_s = 0;	// L636
    ap_uint<17> tx_w;	// L637
    tx_w = 0;	// L638
    ap_uint<17> tx_e;	// L639
    tx_e = 0;	// L640
    uint8_t v400 = sb_v[0];	// L641
    int32_t v401 = v400;	// L642
    bool v402 = v401 == 1;	// L643
    if (v402) {	// L644
      uint8_t v403 = sb_ix[0];	// L645
      int v404 = v403;	// L646
      half v405 = resq[v404];	// L647
      half wb;
#pragma HLS dependence variable=wb type=inter dependent=false	// L648
      wb = v405;	// L649
      uint8_t v407 = sb_cmp[0];	// L650
      int32_t v408 = v407;	// L651
      bool v409 = v408 == 1;	// L652
      if (v409) {	// L653
        uint8_t v410 = sb_ix[0];	// L654
        int v411 = v410;	// L655
        uint8_t v412 = cmpq[v411];	// L656
        condition_reg = v412;	// L657
      }
      uint8_t v413 = sb_rtr[0];	// L659
      int32_t v414 = v413;	// L660
      bool v415 = v414 == 1;	// L661
      if (v415) {	// L662
        uint8_t v416 = sb_inj[0];	// L663
        int32_t v417 = v416;	// L664
        bool v418 = v417 == 1;	// L665
        ap_int<26> v419 = csd_pkt;	// L666
        bool v420;
        ap_int<26> v420_tmp = v419;
        v420 = v420_tmp[25];	// L667
        int32_t v421 = v420;	// L668
        bool v422 = v421 == 0;	// L669
        bool v423 = v418 & v422;	// L670
        if (v423) {	// L671
          half v424 = wb;	// L672
          uint16_t v425;
          union { half from; uint16_t to;} _converter_v424_to_v425 = {};
          _converter_v424_to_v425.from = v424;
          v425 = _converter_v424_to_v425.to;	// L673
          ap_int<26> v426 = csd_pkt;	// L674
          ap_int<26> v427;
          ap_int<26> v427_tmp = v426;
          v427_tmp(15, 0) = v425;
          v427 = v427_tmp;	// L675
          csd_pkt = v427;	// L676
          uint8_t v428 = sb_dst[0];	// L677
          ap_uint<4> v429 = v428;	// L678
          ap_int<26> v430 = csd_pkt;	// L679
          ap_int<26> v431;
          ap_int<26> v431_tmp = v430;
          v431_tmp(19, 16) = v429;
          v431 = v431_tmp;	// L680
          csd_pkt = v431;	// L681
          uint8_t v432 = sb_id[0];	// L682
          ap_uint<4> v433 = v432;	// L683
          ap_int<26> v434 = csd_pkt;	// L684
          ap_int<26> v435;
          ap_int<26> v435_tmp = v434;
          v435_tmp(24, 21) = v433;
          v435 = v435_tmp;	// L685
          csd_pkt = v435;	// L686
          uint8_t v436 = sb_rvld[0];	// L687
          bool v437 = v436;	// L688
          ap_int<26> v438 = csd_pkt;	// L689
          ap_int<26> v439;
          ap_int<26> v439_tmp = v438;
          v439_tmp[25] = v437;          v439 = v439_tmp;	// L690
          csd_pkt = v439;	// L691
          uint8_t v440 = sb_dir[0];	// L692
          int32_t v441 = v440;	// L693
          csd_dir = v441;	// L694
        }
      } else {
        uint8_t v442 = sb_dst[0];	// L697
        int32_t v443 = v442;	// L698
        bool v444 = v443 >= 12;	// L699
        if (v444) {	// L700
          ap_uint<17> tw0;	// L701
          tw0 = 0;	// L702
          uint8_t v446 = sb_rvld[0];	// L703
          bool v447 = v446;	// L704
          ap_int<17> v448 = tw0;	// L705
          ap_int<17> v449;
          ap_int<17> v449_tmp = v448;
          v449_tmp[0] = v447;          v449 = v449_tmp;	// L706
          tw0 = v449;	// L707
          half v450 = wb;	// L708
          uint16_t v451;
          union { half from; uint16_t to;} _converter_v450_to_v451 = {};
          _converter_v450_to_v451.from = v450;
          v451 = _converter_v450_to_v451.to;	// L709
          ap_int<17> v452 = tw0;	// L710
          ap_int<17> v453;
          ap_int<17> v453_tmp = v452;
          v453_tmp(16, 1) = v451;
          v453 = v453_tmp;	// L711
          tw0 = v453;	// L712
          uint8_t v454 = sb_dst[0];	// L713
          int32_t v455 = v454;	// L714
          int32_t v456 = v455 & 3;	// L715
          bool v457 = v456 == 0;	// L716
          if (v457) {	// L717
            ap_int<17> v458 = tw0;	// L718
            tx_n = v458;	// L719
          } else {
            uint8_t v459 = sb_dst[0];	// L721
            int32_t v460 = v459;	// L722
            int32_t v461 = v460 & 3;	// L723
            bool v462 = v461 == 1;	// L724
            if (v462) {	// L725
              ap_int<17> v463 = tw0;	// L726
              tx_s = v463;	// L727
            } else {
              uint8_t v464 = sb_dst[0];	// L729
              int32_t v465 = v464;	// L730
              int32_t v466 = v465 & 3;	// L731
              bool v467 = v466 == 2;	// L732
              if (v467) {	// L733
                ap_int<17> v468 = tw0;	// L734
                tx_w = v468;	// L735
              } else {
                ap_int<17> v469 = tw0;	// L737
                tx_e = v469;	// L738
              }
            }
          }
        } else {
          uint8_t v470 = sb_rvld[0];	// L743
          int32_t v471 = v470;	// L744
          bool v472 = v471 == 1;	// L745
          if (v472) {	// L746
            uint8_t v473 = sb_dst[0];	// L747
            int32_t v474 = v473;	// L748
            bool v475 = v474 < 8;	// L749
            int32_t v476 = dsmask;	// L750
            int32_t v477 = v476 >> v474;	// L751
            int32_t v478 = v477 & 1;	// L752
            bool v479 = v478 == 1;	// L753
            bool v480 = v475 & v479;	// L754
            if (v480) {	// L755
              uint8_t v481 = sb_dst[0];	// L756
              int v482 = v481;	// L757
              int32_t v483 = drf_full[v482];	// L758
              bool v484 = v483 == 0;	// L759
              if (v484) {	// L760
                half v485 = wb;	// L761
                uint8_t v486 = sb_dst[0];	// L762
                int v487 = v486;	// L763
                drf[v487] = v485;	// L764
                uint8_t v488 = sb_dst[0];	// L765
                int v489 = v488;	// L766
                drf_full[v489] = 1;	// L767
              }
            } else {
              half v490 = wb;	// L770
              uint8_t v491 = sb_dst[0];	// L771
              int32_t v492 = v491;	// L772
              int32_t v493 = v492 & 7;	// L773
              int v494 = v493;	// L774
              drf[v494] = v490;	// L775
            }
          }
        }
      }
    }
    int32_t pc;	// L781
    pc = -1;	// L782
    int8_t v496 = fetch_en;	// L783
    int32_t v497 = v496;	// L784
    bool v498 = v497 == 1;	// L785
    if (v498) {	// L786
      int8_t v499 = instr_cnt;	// L787
      int32_t v500 = v499;	// L788
      pc = v500;	// L789
    }
    int32_t instr;	// L791
    instr = 0;	// L792
    int32_t v502 = pc;	// L793
    bool v503 = v502 >= 0;	// L794
    if (v503) {	// L795
      int32_t v504 = pc;	// L796
      int v505 = v504;	// L797
      int32_t v506 = irf[v505];	// L798
      instr = v506;	// L799
    }
    int32_t v507 = instr;	// L801
    int32_t v508 = v507 & 15;	// L802
    int32_t op;	// L803
    op = v508;	// L804
    int32_t v510 = instr;	// L805
    int32_t v511 = v510 >> 4;	// L806
    int32_t v512 = v511 & 15;	// L807
    int32_t dst;	// L808
    dst = v512;	// L809
    int32_t v514 = instr;	// L810
    int32_t v515 = v514 >> 8;	// L811
    int32_t v516 = v515 & 15;	// L812
    int32_t s1;	// L813
    s1 = v516;	// L814
    int32_t v518 = instr;	// L815
    int32_t v519 = v518 >> 12;	// L816
    int32_t v520 = v519 & 15;	// L817
    int32_t s2;	// L818
    s2 = v520;	// L819
    half a;	// L820
    a = 0.000000;	// L821
    half b;	// L822
    b = 0.000000;	// L823
    int32_t v524 = s1;	// L824
    bool v525 = v524 >= 12;	// L825
    if (v525) {	// L826
      int32_t v526 = s1;	// L827
      int32_t v527 = v526 & 3;	// L828
      int v528 = v527;	// L829
      half v529 = hold_v[v528][0];	// L830
      a = v529;	// L831
    } else {
      int32_t v530 = s1;	// L833
      int v531 = v530;	// L834
      half v532 = drf[v531];	// L835
      a = v532;	// L836
    }
    int32_t v533 = s2;	// L838
    bool v534 = v533 >= 12;	// L839
    if (v534) {	// L840
      int32_t v535 = s2;	// L841
      int32_t v536 = v535 & 3;	// L842
      int v537 = v536;	// L843
      half v538 = hold_v[v537][0];	// L844
      b = v538;	// L845
    } else {
      int32_t v539 = s2;	// L847
      int v540 = v539;	// L848
      half v541 = drf[v540];	// L849
      b = v541;	// L850
    }
    int32_t a_vld;	// L852
    a_vld = 1;	// L853
    int32_t b_vld;	// L854
    b_vld = 1;	// L855
    int32_t v544 = s1;	// L856
    bool v545 = v544 >= 12;	// L857
    if (v545) {	// L858
      a_vld = 0;	// L859
      int32_t v546 = s1;	// L860
      int32_t v547 = v546 & 3;	// L861
      int v548 = v547;	// L862
      uint8_t v549 = hold_cnt[v548];	// L863
      int32_t v550 = v549;	// L864
      bool v551 = v550 > 0;	// L865
      if (v551) {	// L866
        a_vld = 1;	// L867
      }
    }
    int32_t v552 = s2;	// L870
    bool v553 = v552 >= 12;	// L871
    if (v553) {	// L872
      b_vld = 0;	// L873
      int32_t v554 = s2;	// L874
      int32_t v555 = v554 & 3;	// L875
      int v556 = v555;	// L876
      uint8_t v557 = hold_cnt[v556];	// L877
      int32_t v558 = v557;	// L878
      bool v559 = v558 > 0;	// L879
      if (v559) {	// L880
        b_vld = 1;	// L881
      }
    }
    int32_t v560 = s1;	// L884
    bool v561 = v560 < 8;	// L885
    int32_t v562 = dsmask;	// L886
    int32_t v563 = v562 >> v560;	// L887
    int32_t v564 = v563 & 1;	// L888
    bool v565 = v564 == 1;	// L889
    bool v566 = v561 & v565;	// L890
    if (v566) {	// L891
      int32_t v567 = s1;	// L892
      int v568 = v567;	// L893
      int32_t v569 = drf_full[v568];	// L894
      bool v570 = v569 == 0;	// L895
      if (v570) {	// L896
        a_vld = 0;	// L897
      }
    }
    int32_t v571 = s2;	// L900
    bool v572 = v571 < 8;	// L901
    int32_t v573 = dsmask;	// L902
    int32_t v574 = v573 >> v571;	// L903
    int32_t v575 = v574 & 1;	// L904
    bool v576 = v575 == 1;	// L905
    bool v577 = v572 & v576;	// L906
    if (v577) {	// L907
      int32_t v578 = s2;	// L908
      int v579 = v578;	// L909
      int32_t v580 = drf_full[v579];	// L910
      bool v581 = v580 == 0;	// L911
      if (v581) {	// L912
        b_vld = 0;	// L913
      }
    }
    int32_t binop;	// L916
    binop = 0;	// L917
    int32_t v583 = op;	// L918
    bool v584 = v583 == 0;	// L919
    bool v585 = v583 == 1;	// L920
    bool v586 = v583 == 2;	// L921
    bool v587 = v583 == 8;	// L922
    bool v588 = v583 == 9;	// L923
    bool v589 = v584 | v585;	// L924
    bool v590 = v589 | v586;	// L925
    bool v591 = v590 | v587;	// L926
    bool v592 = v591 | v588;	// L927
    if (v592) {	// L928
      binop = 1;	// L929
    }
    int32_t raw;	// L931
    raw = 0;	// L932
    int32_t cmp_busy;	// L933
    cmp_busy = 0;	// L934
    int32_t fwd_a;	// L935
    fwd_a = 0;	// L936
    int32_t fwd_a_ix;	// L937
    fwd_a_ix = 0;	// L938
    int32_t raw_a;	// L939
    raw_a = 0;	// L940
    int32_t fwd_b;	// L941
    fwd_b = 0;	// L942
    int32_t fwd_b_ix;	// L943
    fwd_b_ix = 0;	// L944
    int32_t raw_b;	// L945
    raw_b = 0;	// L946
    l_S_k_6_k: for (int k = 0; k < 4; k++) {	// L947
      ap_int<34> v602 = k;	// L948
      ap_int<34> v603 = v602 + 1;	// L949
      int32_t v604 = v603;	// L950
      int32_t kk;	// L951
      kk = v604;	// L952
      int32_t v606 = kk;	// L953
      ap_int<34> v607 = v606;	// L954
      ap_int<34> v608 = 4 - v607;	// L955
      int32_t v609 = v608;	// L956
      int32_t inflight;	// L957
      inflight = v609;	// L958
      int32_t need;	// L959
      need = 0;	// L960
      int32_t v612 = kk;	// L961
      int v613 = v612;	// L962
      uint8_t v614 = sb_long[v613];	// L963
      int32_t v615 = v614;	// L964
      bool v616 = v615 == 1;	// L965
      if (v616) {	// L966
        need = 1;	// L967
      }
      int32_t rdy;	// L969
      rdy = 0;	// L970
      int32_t v618 = inflight;	// L971
      int32_t v619 = need;	// L972
      bool v620 = v618 >= v619;	// L973
      if (v620) {	// L974
        rdy = 1;	// L975
      }
      int32_t v621 = kk;	// L977
      int v622 = v621;	// L978
      uint8_t v623 = sb_v[v622];	// L979
      int32_t v624 = v623;	// L980
      bool v625 = v624 == 1;	// L981
      uint8_t v626 = sb_rtr[v622];	// L982
      int32_t v627 = v626;	// L983
      bool v628 = v627 == 0;	// L984
      uint8_t v629 = sb_dst[v622];	// L985
      int32_t v630 = v629;	// L986
      bool v631 = v630 < 12;	// L987
      bool v632 = v625 & v628;	// L988
      bool v633 = v632 & v631;	// L989
      if (v633) {	// L990
        int32_t v634 = s1;	// L991
        bool v635 = v634 < 12;	// L992
        int32_t v636 = kk;	// L993
        int v637 = v636;	// L994
        uint8_t v638 = sb_dst[v637];	// L995
        int32_t v639 = v638;	// L996
        int32_t v640 = v639 & 7;	// L997
        int32_t v641 = v634 & 7;	// L998
        bool v642 = v640 == v641;	// L999
        bool v643 = v635 & v642;	// L1000
        if (v643) {	// L1001
          int32_t v644 = rdy;	// L1002
          bool v645 = v644 == 1;	// L1003
          if (v645) {	// L1004
            fwd_a = 1;	// L1005
            int32_t v646 = kk;	// L1006
            int v647 = v646;	// L1007
            uint8_t v648 = sb_ix[v647];	// L1008
            int32_t v649 = v648;	// L1009
            fwd_a_ix = v649;	// L1010
            raw_a = 0;	// L1011
          } else {
            fwd_a = 0;	// L1013
            raw_a = 1;	// L1014
          }
        }
        int32_t v650 = binop;	// L1017
        bool v651 = v650 == 1;	// L1018
        int32_t v652 = s2;	// L1019
        bool v653 = v652 < 12;	// L1020
        int32_t v654 = kk;	// L1021
        int v655 = v654;	// L1022
        uint8_t v656 = sb_dst[v655];	// L1023
        int32_t v657 = v656;	// L1024
        int32_t v658 = v657 & 7;	// L1025
        int32_t v659 = v652 & 7;	// L1026
        bool v660 = v658 == v659;	// L1027
        bool v661 = v651 & v653;	// L1028
        bool v662 = v661 & v660;	// L1029
        if (v662) {	// L1030
          int32_t v663 = rdy;	// L1031
          bool v664 = v663 == 1;	// L1032
          if (v664) {	// L1033
            fwd_b = 1;	// L1034
            int32_t v665 = kk;	// L1035
            int v666 = v665;	// L1036
            uint8_t v667 = sb_ix[v666];	// L1037
            int32_t v668 = v667;	// L1038
            fwd_b_ix = v668;	// L1039
            raw_b = 0;	// L1040
          } else {
            fwd_b = 0;	// L1042
            raw_b = 1;	// L1043
          }
        }
      }
      int32_t v669 = kk;	// L1047
      int v670 = v669;	// L1048
      uint8_t v671 = sb_v[v670];	// L1049
      int32_t v672 = v671;	// L1050
      bool v673 = v672 == 1;	// L1051
      uint8_t v674 = sb_cmp[v670];	// L1052
      int32_t v675 = v674;	// L1053
      bool v676 = v675 == 1;	// L1054
      bool v677 = v673 & v676;	// L1055
      if (v677) {	// L1056
        cmp_busy = 1;	// L1057
      }
    }
    int32_t v678 = raw_a;	// L1060
    raw = v678;	// L1061
    int32_t v679 = binop;	// L1062
    bool v680 = v679 == 1;	// L1063
    int32_t v681 = raw_b;	// L1064
    bool v682 = v681 == 1;	// L1065
    bool v683 = v680 & v682;	// L1066
    if (v683) {	// L1067
      raw = 1;	// L1068
    }
    int32_t v684 = fwd_a;	// L1070
    bool v685 = v684 == 1;	// L1071
    if (v685) {	// L1072
      int32_t v686 = fwd_a_ix;	// L1073
      int v687 = v686;	// L1074
      half v688 = resq[v687];	// L1075
      a = v688;	// L1076
      a_vld = 1;	// L1077
    }
    int32_t v689 = fwd_b;	// L1079
    bool v690 = v689 == 1;	// L1080
    if (v690) {	// L1081
      int32_t v691 = fwd_b_ix;	// L1082
      int v692 = v691;	// L1083
      half v693 = resq[v692];	// L1084
      b = v693;	// L1085
      b_vld = 1;	// L1086
    }
    int32_t is_cond;	// L1088
    is_cond = 0;	// L1089
    int32_t v695 = op;	// L1090
    bool v696 = v695 >= 12;	// L1091
    ap_int<33> v697 = v695;	// L1092
    bool v698 = v697 <= 15;	// L1093
    bool v699 = v696 & v698;	// L1094
    if (v699) {	// L1095
      is_cond = 1;	// L1096
    }
    int32_t grant;	// L1098
    grant = 0;	// L1099
    int32_t v701 = pc;	// L1100
    bool v702 = v701 >= 0;	// L1101
    if (v702) {	// L1102
      grant = 1;	// L1103
    }
    int32_t v703 = pc;	// L1105
    bool v704 = v703 >= 0;	// L1106
    int32_t v705 = a_vld;	// L1107
    bool v706 = v705 == 0;	// L1108
    int32_t v707 = binop;	// L1109
    bool v708 = v707 == 1;	// L1110
    int32_t v709 = b_vld;	// L1111
    bool v710 = v709 == 0;	// L1112
    bool v711 = v708 & v710;	// L1113
    bool v712 = v706 | v711;	// L1114
    bool v713 = v704 & v712;	// L1115
    if (v713) {	// L1116
      grant = 0;	// L1117
    }
    int32_t v714 = pc;	// L1119
    bool v715 = v714 >= 0;	// L1120
    int32_t v716 = raw;	// L1121
    bool v717 = v716 == 1;	// L1122
    int32_t v718 = is_cond;	// L1123
    bool v719 = v718 == 1;	// L1124
    int32_t v720 = cmp_busy;	// L1125
    bool v721 = v720 == 1;	// L1126
    bool v722 = v719 & v721;	// L1127
    bool v723 = v717 | v722;	// L1128
    bool v724 = v715 & v723;	// L1129
    if (v724) {	// L1130
      grant = 0;	// L1131
    }
    int32_t dpk;	// L1133
    dpk = 0;	// L1134
    int32_t v726 = grant;	// L1135
    bool v727 = v726 == 1;	// L1136
    if (v727) {	// L1137
      dpk = 1;	// L1138
    }
    int32_t v728 = dpk;	// L1140
    int32_t v729 = pc;	// L1141
    ap_int<33> v730 = v729;	// L1142
    ap_int<33> v731 = v730 + 1;	// L1143
    ap_int<33> v732 = v731 << 1;	// L1144
    ap_int<33> v733 = v728;	// L1145
    ap_int<33> v734 = v733 | v732;	// L1146
    int32_t v735 = v734;	// L1147
    dpk = v735;	// L1148
    int32_t v736 = a_vld;	// L1149
    bool v737 = v736 == 1;	// L1150
    if (v737) {	// L1151
      int32_t v738 = dpk;	// L1152
      int32_t v739 = v738 | 32;	// L1153
      dpk = v739;	// L1154
    }
    int32_t v740 = b_vld;	// L1156
    bool v741 = v740 == 1;	// L1157
    if (v741) {	// L1158
      int32_t v742 = dpk;	// L1159
      int32_t v743 = v742 | 64;	// L1160
      dpk = v743;	// L1161
    }
    int32_t v744 = raw;	// L1163
    bool v745 = v744 == 1;	// L1164
    if (v745) {	// L1165
      int32_t v746 = dpk;	// L1166
      int32_t v747 = v746 | 128;	// L1167
      dpk = v747;	// L1168
    }
    int32_t v748 = fwd_a;	// L1170
    bool v749 = v748 == 1;	// L1171
    if (v749) {	// L1172
      int32_t v750 = dpk;	// L1173
      int32_t v751 = v750 | 256;	// L1174
      dpk = v751;	// L1175
    }
    int32_t v752 = fwd_b;	// L1177
    bool v753 = v752 == 1;	// L1178
    if (v753) {	// L1179
      int32_t v754 = dpk;	// L1180
      int32_t v755 = v754 | 512;	// L1181
      dpk = v755;	// L1182
    }
    uint8_t v756 = hold_cnt[2];	// L1184
    int32_t v757 = v756;	// L1185
    int32_t hw;	// L1186
    hw = v757;	// L1187
    uint8_t v759 = hold_cnt[0];	// L1188
    int32_t v760 = v759;	// L1189
    int32_t hn;	// L1190
    hn = v760;	// L1191
    int32_t v762 = dpk;	// L1192
    int32_t v763 = hw;	// L1193
    int32_t v764 = v763 & 3;	// L1194
    int32_t v765 = v764 << 10;	// L1195
    int32_t v766 = v762 | v765;	// L1196
    dpk = v766;	// L1197
    int32_t v767 = dpk;	// L1198
    int32_t v768 = hn;	// L1199
    int32_t v769 = v768 & 3;	// L1200
    int32_t v770 = v769 << 12;	// L1201
    int32_t v771 = v767 | v770;	// L1202
    dpk = v771;	// L1203
    int32_t v772 = dpk;	// L1204
    int32_t v773 = op;	// L1205
    int32_t v774 = v773 & 15;	// L1206
    int32_t v775 = v774 << 14;	// L1207
    int32_t v776 = v772 | v775;	// L1208
    dpk = v776;	// L1209
    int32_t v777 = dpk;	// L1210
    v0[0][0][t] = v777;	// L1211
    int32_t v778 = grant;	// L1212
    bool v779 = v778 == 1;	// L1213
    if (v779) {	// L1214
      int8_t v780 = instr_cnt;	// L1215
      int32_t v781 = cfg_isz;	// L1216
      int32_t v782 = v780;	// L1217
      bool v783 = v782 == v781;	// L1218
      if (v783) {	// L1219
        instr_cnt = 0;	// L1220
        int8_t v784 = iter_cnt;	// L1221
        int32_t v785 = cfg_itsz;	// L1222
        ap_int<33> v786 = v785;	// L1223
        ap_int<33> v787 = v786 - 1;	// L1224
        ap_int<33> v788 = v784;	// L1225
        bool v789 = v788 == v787;	// L1226
        if (v789) {	// L1227
          fetch_en = 0;	// L1228
        } else {
          int8_t v790 = iter_cnt;	// L1230
          ap_int<33> v791 = v790;	// L1231
          ap_int<33> v792 = v791 + 1;	// L1232
          uint8_t v793 = v792;	// L1233
          iter_cnt = v793;	// L1234
        }
      } else {
        int8_t v794 = instr_cnt;	// L1237
        ap_int<33> v795 = v794;	// L1238
        ap_int<33> v796 = v795 + 1;	// L1239
        uint8_t v797 = v796;	// L1240
        instr_cnt = v797;	// L1241
      }
    }
    int32_t c1;	// L1244
    c1 = -1;	// L1245
    int32_t c2;	// L1246
    c2 = -1;	// L1247
    int32_t v800 = grant;	// L1248
    bool v801 = v800 == 1;	// L1249
    int32_t v802 = s1;	// L1250
    bool v803 = v802 >= 12;	// L1251
    bool v804 = v801 & v803;	// L1252
    if (v804) {	// L1253
      int32_t v805 = s1;	// L1254
      int32_t v806 = v805 & 3;	// L1255
      c1 = v806;	// L1256
    }
    int32_t v807 = grant;	// L1258
    bool v808 = v807 == 1;	// L1259
    int32_t v809 = s2;	// L1260
    bool v810 = v809 >= 12;	// L1261
    bool v811 = v808 & v810;	// L1262
    if (v811) {	// L1263
      int32_t v812 = s2;	// L1264
      int32_t v813 = v812 & 3;	// L1265
      c2 = v813;	// L1266
    }
    int32_t v814 = c1;	// L1268
    bool v815 = v814 >= 0;	// L1269
    if (v815) {	// L1270
      int32_t v816 = c1;	// L1271
      int v817 = v816;	// L1272
      half v818 = hold_v[v817][1];	// L1273
      hold_v[v817][0] = v818;	// L1274
      int32_t v819 = c1;	// L1275
      int v820 = v819;	// L1276
      uint8_t v821 = hold_cnt[v820];	// L1277
      ap_int<33> v822 = v821;	// L1278
      ap_int<33> v823 = v822 - 1;	// L1279
      uint8_t v824 = v823;	// L1280
      hold_cnt[v820] = v824;	// L1281
    }
    int32_t v825 = c2;	// L1283
    bool v826 = v825 >= 0;	// L1284
    int32_t v827 = c1;	// L1285
    bool v828 = v825 != v827;	// L1286
    bool v829 = v826 & v828;	// L1287
    if (v829) {	// L1288
      int32_t v830 = c2;	// L1289
      int v831 = v830;	// L1290
      half v832 = hold_v[v831][1];	// L1291
      hold_v[v831][0] = v832;	// L1292
      int32_t v833 = c2;	// L1293
      int v834 = v833;	// L1294
      uint8_t v835 = hold_cnt[v834];	// L1295
      ap_int<33> v836 = v835;	// L1296
      ap_int<33> v837 = v836 - 1;	// L1297
      uint8_t v838 = v837;	// L1298
      hold_cnt[v834] = v838;	// L1299
    }
    int32_t v839 = grant;	// L1301
    bool v840 = v839 == 1;	// L1302
    int32_t v841 = s1;	// L1303
    bool v842 = v841 < 8;	// L1304
    int32_t v843 = dsmask;	// L1305
    int32_t v844 = v843 >> v841;	// L1306
    int32_t v845 = v844 & 1;	// L1307
    bool v846 = v845 == 1;	// L1308
    bool v847 = v840 & v842;	// L1309
    bool v848 = v847 & v846;	// L1310
    if (v848) {	// L1311
      int32_t v849 = s1;	// L1312
      int v850 = v849;	// L1313
      drf_full[v850] = 0;	// L1314
    }
    int32_t v851 = grant;	// L1316
    bool v852 = v851 == 1;	// L1317
    int32_t v853 = s2;	// L1318
    bool v854 = v853 < 8;	// L1319
    int32_t v855 = dsmask;	// L1320
    int32_t v856 = v855 >> v853;	// L1321
    int32_t v857 = v856 & 1;	// L1322
    bool v858 = v857 == 1;	// L1323
    bool v859 = v852 & v854;	// L1324
    bool v860 = v859 & v858;	// L1325
    if (v860) {	// L1326
      int32_t v861 = s2;	// L1327
      int v862 = v861;	// L1328
      drf_full[v862] = 0;	// L1329
    }
    half res;
#pragma HLS dependence variable=res type=inter dependent=false	// L1331
    res = 0.000000;	// L1332
    int32_t v864 = op;	// L1333
    bool v865 = v864 == 0;	// L1334
    if (v865) {	// L1335
      half v866 = a;	// L1336
      half v867 = b;	// L1337
      half v868 = v866 + v867;
#pragma HLS bind_op variable=v868 op=hadd impl=fabric latency=2	// L1338
      res = v868;	// L1339
    } else {
      int32_t v869 = op;	// L1341
      bool v870 = v869 == 1;	// L1342
      if (v870) {	// L1343
        half v871 = a;	// L1344
        half v872 = b;	// L1345
        half v873 = v871 - v872;
#pragma HLS bind_op variable=v873 op=hsub impl=fabric latency=2	// L1346
        res = v873;	// L1347
      } else {
        int32_t v874 = op;	// L1349
        bool v875 = v874 == 2;	// L1350
        if (v875) {	// L1351
          half v876 = a;	// L1352
          half v877 = b;	// L1353
          half v878 = v876 * v877;
#pragma HLS bind_op variable=v878 op=hmul impl=maxdsp latency=2	// L1354
          res = v878;	// L1355
        } else {
          int32_t v879 = op;	// L1357
          bool v880 = v879 == 8;	// L1358
          if (v880) {	// L1359
            half v881 = a;	// L1360
            half v882 = b;	// L1361
            bool v883 = v881 >= v882;	// L1362
            if (v883) {	// L1363
              res = 1.000000;	// L1364
            } else {
              res = -1.000000;	// L1366
            }
          } else {
            int32_t v884 = op;	// L1369
            bool v885 = v884 == 9;	// L1370
            if (v885) {	// L1371
              half v886 = a;	// L1372
              half v887 = b;	// L1373
              bool v888 = v886 < v887;	// L1374
              if (v888) {	// L1375
                res = 1.000000;	// L1376
              } else {
                res = -1.000000;	// L1378
              }
            } else {
              half v889 = a;	// L1381
              res = v889;	// L1382
            }
          }
        }
      }
    }
    int32_t v890 = a_vld;	// L1388
    int32_t res_vld;	// L1389
    res_vld = v890;	// L1390
    int32_t v892 = op;	// L1391
    bool v893 = v892 == 0;	// L1392
    bool v894 = v892 == 1;	// L1393
    bool v895 = v892 == 2;	// L1394
    bool v896 = v892 == 8;	// L1395
    bool v897 = v892 == 9;	// L1396
    bool v898 = v893 | v894;	// L1397
    bool v899 = v898 | v895;	// L1398
    bool v900 = v899 | v896;	// L1399
    bool v901 = v900 | v897;	// L1400
    if (v901) {	// L1401
      int32_t v902 = a_vld;	// L1402
      int32_t v903 = b_vld;	// L1403
      int64_t v904 = v902;	// L1404
      int64_t v905 = v903;	// L1405
      int64_t v906 = v904 * v905;	// L1406
      int32_t v907 = v906;	// L1407
      res_vld = v907;	// L1408
    }
    int32_t v908 = grant;	// L1410
    bool v909 = v908 == 0;	// L1411
    if (v909) {	// L1412
      res_vld = 0;	// L1413
    }
    int32_t is_rtr;	// L1415
    is_rtr = 0;	// L1416
    int32_t v911 = op;	// L1417
    bool v912 = v911 >= 4;	// L1418
    ap_int<33> v913 = v911;	// L1419
    bool v914 = v913 <= 7;	// L1420
    bool v915 = v912 & v914;	// L1421
    if (v915) {	// L1422
      is_rtr = 1;	// L1423
    }
    l_S_k_7_k1: for (int k1 = 0; k1 < 4; k1++) {	// L1425
      uint8_t v917 = sb_v[(k1 + 1)];	// L1426
      sb_v[k1] = v917;	// L1427
      uint8_t v918 = sb_dst[(k1 + 1)];	// L1428
      sb_dst[k1] = v918;	// L1429
      uint8_t v919 = sb_cmp[(k1 + 1)];	// L1430
      sb_cmp[k1] = v919;	// L1431
      uint8_t v920 = sb_rtr[(k1 + 1)];	// L1432
      sb_rtr[k1] = v920;	// L1433
      uint8_t v921 = sb_inj[(k1 + 1)];	// L1434
      sb_inj[k1] = v921;	// L1435
      uint8_t v922 = sb_dir[(k1 + 1)];	// L1436
      sb_dir[k1] = v922;	// L1437
      uint8_t v923 = sb_id[(k1 + 1)];	// L1438
      sb_id[k1] = v923;	// L1439
      uint8_t v924 = sb_rvld[(k1 + 1)];	// L1440
      sb_rvld[k1] = v924;	// L1441
      uint8_t v925 = sb_ix[(k1 + 1)];	// L1442
      sb_ix[k1] = v925;	// L1443
      uint8_t v926 = sb_long[(k1 + 1)];	// L1444
      sb_long[k1] = v926;	// L1445
    }
    sb_v[4] = 0;	// L1447
    int32_t v927 = grant;	// L1448
    bool v928 = v927 == 1;	// L1449
    if (v928) {	// L1450
      half v929 = res;	// L1451
      int8_t v930 = resq_wr;	// L1452
      int v931 = v930;	// L1453
      resq[v931] = v929;	// L1454
      int32_t cq;	// L1455
      cq = 0;	// L1456
      int32_t v933 = op;	// L1457
      bool v934 = v933 == 8;	// L1458
      if (v934) {	// L1459
        half v935 = a;	// L1460
        half v936 = b;	// L1461
        bool v937 = v935 >= v936;	// L1462
        if (v937) {	// L1463
          cq = 1;	// L1464
        }
      }
      int32_t v938 = op;	// L1467
      bool v939 = v938 == 9;	// L1468
      if (v939) {	// L1469
        half v940 = a;	// L1470
        half v941 = b;	// L1471
        bool v942 = v940 < v941;	// L1472
        if (v942) {	// L1473
          cq = 1;	// L1474
        }
      }
      int32_t v943 = cq;	// L1477
      uint8_t v944 = v943;	// L1478
      int8_t v945 = resq_wr;	// L1479
      int v946 = v945;	// L1480
      cmpq[v946] = v944;	// L1481
      sb_v[4] = 1;	// L1482
      int32_t v947 = dst;	// L1483
      uint8_t v948 = v947;	// L1484
      sb_dst[4] = v948;	// L1485
      int8_t v949 = resq_wr;	// L1486
      sb_ix[4] = v949;	// L1487
      int32_t v950 = binop;	// L1488
      uint8_t v951 = v950;	// L1489
      sb_long[4] = v951;	// L1490
      sb_cmp[4] = 0;	// L1491
      int32_t v952 = op;	// L1492
      bool v953 = v952 == 8;	// L1493
      bool v954 = v952 == 9;	// L1494
      bool v955 = v953 | v954;	// L1495
      if (v955) {	// L1496
        sb_cmp[4] = 1;	// L1497
      }
      int32_t v956 = is_rtr;	// L1499
      int32_t rtrf;	// L1500
      rtrf = v956;	// L1501
      int32_t v958 = is_cond;	// L1502
      bool v959 = v958 == 1;	// L1503
      if (v959) {	// L1504
        rtrf = 1;	// L1505
      }
      int32_t v960 = rtrf;	// L1507
      uint8_t v961 = v960;	// L1508
      sb_rtr[4] = v961;	// L1509
      int32_t v962 = is_rtr;	// L1510
      int32_t inj;	// L1511
      inj = v962;	// L1512
      int32_t v964 = is_cond;	// L1513
      bool v965 = v964 == 1;	// L1514
      int8_t v966 = condition_reg;	// L1515
      int32_t v967 = v966;	// L1516
      bool v968 = v967 == 1;	// L1517
      bool v969 = v965 & v968;	// L1518
      if (v969) {	// L1519
        inj = 1;	// L1520
      }
      int32_t v970 = inj;	// L1522
      uint8_t v971 = v970;	// L1523
      sb_inj[4] = v971;	// L1524
      int32_t v972 = op;	// L1525
      int32_t v973 = v972 & 3;	// L1526
      uint8_t v974 = v973;	// L1527
      sb_dir[4] = v974;	// L1528
      int32_t v975 = s2;	// L1529
      uint8_t v976 = v975;	// L1530
      sb_id[4] = v976;	// L1531
      int32_t v977 = res_vld;	// L1532
      uint8_t v978 = v977;	// L1533
      sb_rvld[4] = v978;	// L1534
      int8_t v979 = resq_wr;	// L1535
      ap_int<33> v980 = v979;	// L1536
      ap_int<33> v981 = v980 + 1;	// L1537
      ap_int<33> v982 = v981 & 7;	// L1538
      uint8_t v983 = v982;	// L1539
      resq_wr = v983;	// L1540
    }
    ap_int<17> v984 = tx_n;	// L1542
    txn_r = v984;	// L1543
    ap_int<17> v985 = tx_s;	// L1544
    txs_r = v985;	// L1545
    ap_int<17> v986 = tx_w;	// L1546
    txw_r = v986;	// L1547
    ap_int<17> v987 = tx_e;	// L1548
    txe_r = v987;	// L1549
    int32_t v988 = crv_vld;	// L1550
    bool v989 = v988 == 1;	// L1551
    if (v989) {	// L1552
      int32_t v990 = crv_mode;	// L1553
      bool v991 = v990 == 1;	// L1554
      if (v991) {	// L1555
        int32_t v992 = crv_addr;	// L1556
        int32_t v993 = v992 >> 3;	// L1557
        int32_t v994 = v993 & 1;	// L1558
        bool v995 = v994 == 1;	// L1559
        if (v995) {	// L1560
          int32_t v996 = crv_raw;	// L1561
          int32_t v997 = crv_addr;	// L1562
          int32_t v998 = v997 & 7;	// L1563
          int v999 = v998;	// L1564
          irf[v999] = v996;	// L1565
        } else {
          int32_t v1000 = crv_addr;	// L1567
          bool v1001 = v1000 == 0;	// L1568
          if (v1001) {	// L1569
            int32_t v1002 = crv_raw;	// L1570
            int32_t v1003 = v1002 & 255;	// L1571
            dsmask = v1003;	// L1572
            int32_t v1004 = crv_raw;	// L1573
            int32_t v1005 = v1004 >> 8;	// L1574
            int32_t v1006 = v1005 & 7;	// L1575
            cfg_isz = v1006;	// L1576
            int32_t v1007 = crv_raw;	// L1577
            int32_t v1008 = v1007 >> 15;	// L1578
            int32_t v1009 = v1008 & 1;	// L1579
            bool v1010 = v1009 == 1;	// L1580
            if (v1010) {	// L1581
              fetch_en = 1;	// L1582
              instr_cnt = 0;	// L1583
              iter_cnt = 0;	// L1584
            }
          } else {
            int32_t v1011 = crv_addr;	// L1587
            bool v1012 = v1011 == 1;	// L1588
            if (v1012) {	// L1589
              int32_t v1013 = crv_raw;	// L1590
              int32_t v1014 = v1013 & 255;	// L1591
              cfg_itsz = v1014;	// L1592
            }
          }
        }
      } else {
        int32_t v1015 = crv_addr;	// L1597
        bool v1016 = v1015 < 8;	// L1598
        int32_t v1017 = dsmask;	// L1599
        int32_t v1018 = v1017 >> v1015;	// L1600
        int32_t v1019 = v1018 & 1;	// L1601
        bool v1020 = v1019 == 1;	// L1602
        bool v1021 = v1016 & v1020;	// L1603
        if (v1021) {	// L1604
          int32_t v1022 = crv_addr;	// L1605
          int v1023 = v1022;	// L1606
          int32_t v1024 = drf_full[v1023];	// L1607
          bool v1025 = v1024 == 0;	// L1608
          if (v1025) {	// L1609
            half v1026 = crv_data;	// L1610
            int32_t v1027 = crv_addr;	// L1611
            int v1028 = v1027;	// L1612
            drf[v1028] = v1026;	// L1613
            int32_t v1029 = crv_addr;	// L1614
            int v1030 = v1029;	// L1615
            drf_full[v1030] = 1;	// L1616
          }
        } else {
          half v1031 = crv_data;	// L1619
          int32_t v1032 = crv_addr;	// L1620
          int v1033 = v1032;	// L1621
          drf[v1033] = v1031;	// L1622
        }
      }
    }
    ap_int<26> v1034 = oe_r;	// L1626
    v1.write(v1034);	// L1627
    ap_int<26> v1035 = ow_r;	// L1628
    v2.write(v1035);	// L1629
    ap_int<26> v1036 = os_r;	// L1630
    v3.write(v1036);	// L1631
    ap_int<26> v1037 = on_r;	// L1632
    v4.write(v1037);	// L1633
    ap_int<17> v1038 = txe_r;	// L1634
    v5.write(v1038);	// L1635
    ap_int<17> v1039 = txw_r;	// L1636
    v6.write(v1039);	// L1637
    ap_int<17> v1040 = txs_r;	// L1638
    v7.write(v1040);	// L1639
    ap_int<17> v1041 = txn_r;	// L1640
    v8.write(v1041);	// L1641
    int8_t v1042 = cre_r;	// L1642
    v9.write(v1042);	// L1643
    int8_t v1043 = crw_r;	// L1644
    v10.write(v1043);	// L1645
    int8_t v1044 = crs_r;	// L1646
    v11.write(v1044);	// L1647
    int8_t v1045 = crn_r;	// L1648
    v12.write(v1045);	// L1649
  }
}

void drv_w_0(
  half v1046[1][200],
  int32_t v1047[1][200],
  hls::stream< ap_uint<17> >& v1048
) {	// L1653
  ap_uint<17> zw;	// L1659
  zw = 0;	// L1660
  ap_int<17> v1050 = zw;	// L1661
  v1048.write(v1050);	// L1662
  ap_int<17> v1051 = zw;	// L1663
  v1048.write(v1051);	// L1664
  ap_int<17> v1052 = zw;	// L1665
  v1048.write(v1052);	// L1666
  ap_int<17> v1053 = zw;	// L1667
  v1048.write(v1053);	// L1668
  ap_int<17> v1054 = zw;	// L1669
  v1048.write(v1054);	// L1670
  l_S_t_0_t1: for (int t1 = 0; t1 < 200; t1++) {	// L1671
    ap_uint<17> w;	// L1672
    w = 0;	// L1673
    ap_int<33> v1057 = t1;	// L1674
    bool v1058 = v1057 < 200;	// L1675
    if (v1058) {	// L1676
      int32_t v1059 = v1047[0][t1];	// L1677
      bool v1060 = v1059;	// L1678
      ap_int<17> v1061 = w;	// L1679
      ap_int<17> v1062;
      ap_int<17> v1062_tmp = v1061;
      v1062_tmp[0] = v1060;      v1062 = v1062_tmp;	// L1680
      w = v1062;	// L1681
      half v1063 = v1046[0][t1];	// L1682
      uint16_t v1064;
      union { half from; uint16_t to;} _converter_v1063_to_v1064 = {};
      _converter_v1063_to_v1064.from = v1063;
      v1064 = _converter_v1063_to_v1064.to;	// L1683
      ap_int<17> v1065 = w;	// L1684
      ap_int<17> v1066;
      ap_int<17> v1066_tmp = v1065;
      v1066_tmp(16, 1) = v1064;
      v1066 = v1066_tmp;	// L1685
      w = v1066;	// L1686
    }
    ap_int<17> v1067 = w;	// L1688
    v1048.write(v1067);	// L1689
  }
}

void drv_e_0(
  half v1068[1][200],
  int32_t v1069[1][200],
  hls::stream< ap_uint<17> >& v1070
) {	// L1693
  ap_uint<17> zw1;	// L1699
  zw1 = 0;	// L1700
  ap_int<17> v1072 = zw1;	// L1701
  v1070.write(v1072);	// L1702
  ap_int<17> v1073 = zw1;	// L1703
  v1070.write(v1073);	// L1704
  ap_int<17> v1074 = zw1;	// L1705
  v1070.write(v1074);	// L1706
  ap_int<17> v1075 = zw1;	// L1707
  v1070.write(v1075);	// L1708
  ap_int<17> v1076 = zw1;	// L1709
  v1070.write(v1076);	// L1710
  l_S_t_0_t2: for (int t2 = 0; t2 < 200; t2++) {	// L1711
    ap_uint<17> w1;	// L1712
    w1 = 0;	// L1713
    ap_int<33> v1079 = t2;	// L1714
    bool v1080 = v1079 < 200;	// L1715
    if (v1080) {	// L1716
      int32_t v1081 = v1069[0][t2];	// L1717
      bool v1082 = v1081;	// L1718
      ap_int<17> v1083 = w1;	// L1719
      ap_int<17> v1084;
      ap_int<17> v1084_tmp = v1083;
      v1084_tmp[0] = v1082;      v1084 = v1084_tmp;	// L1720
      w1 = v1084;	// L1721
      half v1085 = v1068[0][t2];	// L1722
      uint16_t v1086;
      union { half from; uint16_t to;} _converter_v1085_to_v1086 = {};
      _converter_v1085_to_v1086.from = v1085;
      v1086 = _converter_v1085_to_v1086.to;	// L1723
      ap_int<17> v1087 = w1;	// L1724
      ap_int<17> v1088;
      ap_int<17> v1088_tmp = v1087;
      v1088_tmp(16, 1) = v1086;
      v1088 = v1088_tmp;	// L1725
      w1 = v1088;	// L1726
    }
    ap_int<17> v1089 = w1;	// L1728
    v1070.write(v1089);	// L1729
  }
}

void drv_n_0(
  half v1090[1][200],
  int32_t v1091[1][200],
  hls::stream< ap_uint<17> >& v1092
) {	// L1733
  ap_uint<17> zw2;	// L1739
  zw2 = 0;	// L1740
  ap_int<17> v1094 = zw2;	// L1741
  v1092.write(v1094);	// L1742
  ap_int<17> v1095 = zw2;	// L1743
  v1092.write(v1095);	// L1744
  ap_int<17> v1096 = zw2;	// L1745
  v1092.write(v1096);	// L1746
  ap_int<17> v1097 = zw2;	// L1747
  v1092.write(v1097);	// L1748
  ap_int<17> v1098 = zw2;	// L1749
  v1092.write(v1098);	// L1750
  l_S_t_0_t3: for (int t3 = 0; t3 < 200; t3++) {	// L1751
    ap_uint<17> w2;	// L1752
    w2 = 0;	// L1753
    ap_int<33> v1101 = t3;	// L1754
    bool v1102 = v1101 < 200;	// L1755
    if (v1102) {	// L1756
      int32_t v1103 = v1091[0][t3];	// L1757
      bool v1104 = v1103;	// L1758
      ap_int<17> v1105 = w2;	// L1759
      ap_int<17> v1106;
      ap_int<17> v1106_tmp = v1105;
      v1106_tmp[0] = v1104;      v1106 = v1106_tmp;	// L1760
      w2 = v1106;	// L1761
      half v1107 = v1090[0][t3];	// L1762
      uint16_t v1108;
      union { half from; uint16_t to;} _converter_v1107_to_v1108 = {};
      _converter_v1107_to_v1108.from = v1107;
      v1108 = _converter_v1107_to_v1108.to;	// L1763
      ap_int<17> v1109 = w2;	// L1764
      ap_int<17> v1110;
      ap_int<17> v1110_tmp = v1109;
      v1110_tmp(16, 1) = v1108;
      v1110 = v1110_tmp;	// L1765
      w2 = v1110;	// L1766
    }
    ap_int<17> v1111 = w2;	// L1768
    v1092.write(v1111);	// L1769
  }
}

void drv_s_0(
  half v1112[1][200],
  int32_t v1113[1][200],
  hls::stream< ap_uint<17> >& v1114
) {	// L1773
  ap_uint<17> zw3;	// L1779
  zw3 = 0;	// L1780
  ap_int<17> v1116 = zw3;	// L1781
  v1114.write(v1116);	// L1782
  ap_int<17> v1117 = zw3;	// L1783
  v1114.write(v1117);	// L1784
  ap_int<17> v1118 = zw3;	// L1785
  v1114.write(v1118);	// L1786
  ap_int<17> v1119 = zw3;	// L1787
  v1114.write(v1119);	// L1788
  ap_int<17> v1120 = zw3;	// L1789
  v1114.write(v1120);	// L1790
  l_S_t_0_t4: for (int t4 = 0; t4 < 200; t4++) {	// L1791
    ap_uint<17> w3;	// L1792
    w3 = 0;	// L1793
    ap_int<33> v1123 = t4;	// L1794
    bool v1124 = v1123 < 200;	// L1795
    if (v1124) {	// L1796
      int32_t v1125 = v1113[0][t4];	// L1797
      bool v1126 = v1125;	// L1798
      ap_int<17> v1127 = w3;	// L1799
      ap_int<17> v1128;
      ap_int<17> v1128_tmp = v1127;
      v1128_tmp[0] = v1126;      v1128 = v1128_tmp;	// L1800
      w3 = v1128;	// L1801
      half v1129 = v1112[0][t4];	// L1802
      uint16_t v1130;
      union { half from; uint16_t to;} _converter_v1129_to_v1130 = {};
      _converter_v1129_to_v1130.from = v1129;
      v1130 = _converter_v1129_to_v1130.to;	// L1803
      ap_int<17> v1131 = w3;	// L1804
      ap_int<17> v1132;
      ap_int<17> v1132_tmp = v1131;
      v1132_tmp(16, 1) = v1130;
      v1132 = v1132_tmp;	// L1805
      w3 = v1132;	// L1806
    }
    ap_int<17> v1133 = w3;	// L1808
    v1114.write(v1133);	// L1809
  }
}

void col_w_0(
  half v1134[1][200],
  hls::stream< ap_uint<17> >& v1135
) {	// L1813
  int32_t k2[1];	// L1821
  for (int v1137 = 0; v1137 < 1; v1137++) {	// L1822
    k2[v1137] = 0;	// L1822
  }
  l_S_t_0_t5: for (int t5 = 0; t5 < 200; t5++) {	// L1823
    ap_uint<17> v1139 = v1135.read();	// L1824
    ap_uint<17> w4;	// L1825
    w4 = v1139;	// L1826
    ap_int<17> v1141 = w4;	// L1827
    bool v1142;
    ap_int<17> v1142_tmp = v1141;
    v1142 = v1142_tmp[0];	// L1828
    int32_t v1143 = v1142;	// L1829
    bool v1144 = v1143 == 1;	// L1830
    int32_t v1145 = k2[0];	// L1831
    bool v1146 = v1145 < 200;	// L1832
    bool v1147 = v1144 & v1146;	// L1833
    if (v1147) {	// L1834
      ap_int<17> v1148 = w4;	// L1835
      int16_t v1149;
      ap_int<17> v1149_tmp = v1148;
      v1149 = v1149_tmp(16, 1);	// L1836
      half v1150;
      union { uint16_t from; half to;} _converter_v1149_to_v1150 = {};
      _converter_v1149_to_v1150.from = v1149;
      v1150 = _converter_v1149_to_v1150.to;	// L1837
      int32_t v1151 = k2[0];	// L1838
      int v1152 = v1151;	// L1839
      v1134[0][v1152] = v1150;	// L1840
      int32_t v1153 = k2[0];	// L1841
      ap_int<33> v1154 = v1153;	// L1842
      ap_int<33> v1155 = v1154 + 1;	// L1843
      int32_t v1156 = v1155;	// L1844
      k2[0] = v1156;	// L1845
    }
  }
}

void col_e_0(
  half v1157[1][200],
  int32_t v1158[1][200],
  hls::stream< ap_uint<17> >& v1159
) {	// L1850
  int32_t k3[1];	// L1858
  for (int v1161 = 0; v1161 < 1; v1161++) {	// L1859
    k3[v1161] = 0;	// L1859
  }
  l_S_t_0_t6: for (int t6 = 0; t6 < 200; t6++) {	// L1860
    ap_uint<17> v1163 = v1159.read();	// L1861
    ap_uint<17> w5;	// L1862
    w5 = v1163;	// L1863
    ap_int<17> v1165 = w5;	// L1864
    bool v1166;
    ap_int<17> v1166_tmp = v1165;
    v1166 = v1166_tmp[0];	// L1865
    int32_t v1167 = v1166;	// L1866
    bool v1168 = v1167 == 1;	// L1867
    int32_t v1169 = k3[0];	// L1868
    bool v1170 = v1169 < 200;	// L1869
    bool v1171 = v1168 & v1170;	// L1870
    if (v1171) {	// L1871
      ap_int<17> v1172 = w5;	// L1872
      int16_t v1173;
      ap_int<17> v1173_tmp = v1172;
      v1173 = v1173_tmp(16, 1);	// L1873
      half v1174;
      union { uint16_t from; half to;} _converter_v1173_to_v1174 = {};
      _converter_v1173_to_v1174.from = v1173;
      v1174 = _converter_v1173_to_v1174.to;	// L1874
      int32_t v1175 = k3[0];	// L1875
      int v1176 = v1175;	// L1876
      v1157[0][v1176] = v1174;	// L1877
      int32_t v1177 = t6;	// L1878
      int32_t v1178 = k3[0];	// L1879
      int v1179 = v1178;	// L1880
      v1158[0][v1179] = v1177;	// L1881
      int32_t v1180 = k3[0];	// L1882
      ap_int<33> v1181 = v1180;	// L1883
      ap_int<33> v1182 = v1181 + 1;	// L1884
      int32_t v1183 = v1182;	// L1885
      k3[0] = v1183;	// L1886
    }
  }
}

void col_n_0(
  half v1184[1][200],
  hls::stream< ap_uint<17> >& v1185
) {	// L1891
  int32_t k4[1];	// L1899
  for (int v1187 = 0; v1187 < 1; v1187++) {	// L1900
    k4[v1187] = 0;	// L1900
  }
  l_S_t_0_t7: for (int t7 = 0; t7 < 200; t7++) {	// L1901
    ap_uint<17> v1189 = v1185.read();	// L1902
    ap_uint<17> w6;	// L1903
    w6 = v1189;	// L1904
    ap_int<17> v1191 = w6;	// L1905
    bool v1192;
    ap_int<17> v1192_tmp = v1191;
    v1192 = v1192_tmp[0];	// L1906
    int32_t v1193 = v1192;	// L1907
    bool v1194 = v1193 == 1;	// L1908
    int32_t v1195 = k4[0];	// L1909
    bool v1196 = v1195 < 200;	// L1910
    bool v1197 = v1194 & v1196;	// L1911
    if (v1197) {	// L1912
      ap_int<17> v1198 = w6;	// L1913
      int16_t v1199;
      ap_int<17> v1199_tmp = v1198;
      v1199 = v1199_tmp(16, 1);	// L1914
      half v1200;
      union { uint16_t from; half to;} _converter_v1199_to_v1200 = {};
      _converter_v1199_to_v1200.from = v1199;
      v1200 = _converter_v1199_to_v1200.to;	// L1915
      int32_t v1201 = k4[0];	// L1916
      int v1202 = v1201;	// L1917
      v1184[0][v1202] = v1200;	// L1918
      int32_t v1203 = k4[0];	// L1919
      ap_int<33> v1204 = v1203;	// L1920
      ap_int<33> v1205 = v1204 + 1;	// L1921
      int32_t v1206 = v1205;	// L1922
      k4[0] = v1206;	// L1923
    }
  }
}

void col_s_0(
  half v1207[1][200],
  int32_t v1208[1][200],
  hls::stream< ap_uint<17> >& v1209
) {	// L1928
  int32_t k5[1];	// L1936
  for (int v1211 = 0; v1211 < 1; v1211++) {	// L1937
    k5[v1211] = 0;	// L1937
  }
  l_S_t_0_t8: for (int t8 = 0; t8 < 200; t8++) {	// L1938
    ap_uint<17> v1213 = v1209.read();	// L1939
    ap_uint<17> w7;	// L1940
    w7 = v1213;	// L1941
    ap_int<17> v1215 = w7;	// L1942
    bool v1216;
    ap_int<17> v1216_tmp = v1215;
    v1216 = v1216_tmp[0];	// L1943
    int32_t v1217 = v1216;	// L1944
    bool v1218 = v1217 == 1;	// L1945
    int32_t v1219 = k5[0];	// L1946
    bool v1220 = v1219 < 200;	// L1947
    bool v1221 = v1218 & v1220;	// L1948
    if (v1221) {	// L1949
      ap_int<17> v1222 = w7;	// L1950
      int16_t v1223;
      ap_int<17> v1223_tmp = v1222;
      v1223 = v1223_tmp(16, 1);	// L1951
      half v1224;
      union { uint16_t from; half to;} _converter_v1223_to_v1224 = {};
      _converter_v1223_to_v1224.from = v1223;
      v1224 = _converter_v1223_to_v1224.to;	// L1952
      int32_t v1225 = k5[0];	// L1953
      int v1226 = v1225;	// L1954
      v1207[0][v1226] = v1224;	// L1955
      int32_t v1227 = t8;	// L1956
      int32_t v1228 = k5[0];	// L1957
      int v1229 = v1228;	// L1958
      v1208[0][v1229] = v1227;	// L1959
      int32_t v1230 = k5[0];	// L1960
      ap_int<33> v1231 = v1230;	// L1961
      ap_int<33> v1232 = v1231 + 1;	// L1962
      int32_t v1233 = v1232;	// L1963
      k5[0] = v1233;	// L1964
    }
  }
}

void rdrv_w_0(
  int32_t v1234[1][200],
  hls::stream< ap_uint<26> >& v1235,
  hls::stream< int32_t >& v1236
) {	// L1969
  int32_t dcred[1];	// L1976
  for (int v1238 = 0; v1238 < 1; v1238++) {	// L1977
    dcred[v1238] = 0;	// L1977
  }
  int32_t sp[1];	// L1978
  for (int v1240 = 0; v1240 < 1; v1240++) {	// L1979
    sp[v1240] = 0;	// L1979
  }
  ap_uint<26> zp;	// L1980
  zp = 0;	// L1981
  ap_int<26> v1242 = zp;	// L1982
  v1235.write(v1242);	// L1983
  ap_int<26> v1243 = zp;	// L1984
  v1235.write(v1243);	// L1985
  ap_int<26> v1244 = zp;	// L1986
  v1235.write(v1244);	// L1987
  ap_int<26> v1245 = zp;	// L1988
  v1235.write(v1245);	// L1989
  ap_int<26> v1246 = zp;	// L1990
  v1235.write(v1246);	// L1991
  l_S_t_0_t9: for (int t9 = 0; t9 < 200; t9++) {	// L1992
    int32_t v1248 = v1236.read();	// L1993
    int32_t v1249 = dcred[0];	// L1994
    ap_int<33> v1250 = v1249;	// L1995
    ap_int<33> v1251 = v1248;	// L1996
    ap_int<33> v1252 = v1250 + v1251;	// L1997
    int32_t v1253 = v1252;	// L1998
    dcred[0] = v1253;	// L1999
    ap_uint<26> pw;	// L2000
    pw = 0;	// L2001
    int32_t v1255 = sp[0];	// L2002
    bool v1256 = v1255 < 200;	// L2003
    if (v1256) {	// L2004
      ap_uint<26> cand;	// L2005
      cand = 0;	// L2006
      int32_t v1258 = sp[0];	// L2007
      int v1259 = v1258;	// L2008
      int32_t v1260 = v1234[0][v1259];	// L2009
      ap_uint<26> v1261 = v1260;	// L2010
      ap_int<26> v1262 = cand;	// L2011
      ap_int<26> v1263;
      ap_int<26> v1263_tmp = v1262;
      v1263_tmp(25, 0) = v1261;
      v1263 = v1263_tmp;	// L2012
      cand = v1263;	// L2013
      ap_int<26> v1264 = cand;	// L2014
      bool v1265;
      ap_int<26> v1265_tmp = v1264;
      v1265 = v1265_tmp[25];	// L2015
      int32_t v1266 = v1265;	// L2016
      bool v1267 = v1266 == 0;	// L2017
      if (v1267) {	// L2018
        int32_t v1268 = sp[0];	// L2019
        ap_int<33> v1269 = v1268;	// L2020
        ap_int<33> v1270 = v1269 + 1;	// L2021
        int32_t v1271 = v1270;	// L2022
        sp[0] = v1271;	// L2023
      } else {
        int32_t v1272 = dcred[0];	// L2025
        bool v1273 = v1272 > 0;	// L2026
        if (v1273) {	// L2027
          ap_int<26> v1274 = cand;	// L2028
          pw = v1274;	// L2029
          int32_t v1275 = dcred[0];	// L2030
          ap_int<33> v1276 = v1275;	// L2031
          ap_int<33> v1277 = v1276 - 1;	// L2032
          int32_t v1278 = v1277;	// L2033
          dcred[0] = v1278;	// L2034
          int32_t v1279 = sp[0];	// L2035
          ap_int<33> v1280 = v1279;	// L2036
          ap_int<33> v1281 = v1280 + 1;	// L2037
          int32_t v1282 = v1281;	// L2038
          sp[0] = v1282;	// L2039
        }
      }
    }
    ap_int<26> v1283 = pw;	// L2043
    v1235.write(v1283);	// L2044
  }
}

void rdrv_e_0(
  int32_t v1284[1][200],
  hls::stream< ap_uint<26> >& v1285,
  hls::stream< int32_t >& v1286
) {	// L2048
  int32_t dcred1[1];	// L2055
  for (int v1288 = 0; v1288 < 1; v1288++) {	// L2056
    dcred1[v1288] = 0;	// L2056
  }
  int32_t sp1[1];	// L2057
  for (int v1290 = 0; v1290 < 1; v1290++) {	// L2058
    sp1[v1290] = 0;	// L2058
  }
  ap_uint<26> zp1;	// L2059
  zp1 = 0;	// L2060
  ap_int<26> v1292 = zp1;	// L2061
  v1285.write(v1292);	// L2062
  ap_int<26> v1293 = zp1;	// L2063
  v1285.write(v1293);	// L2064
  ap_int<26> v1294 = zp1;	// L2065
  v1285.write(v1294);	// L2066
  ap_int<26> v1295 = zp1;	// L2067
  v1285.write(v1295);	// L2068
  ap_int<26> v1296 = zp1;	// L2069
  v1285.write(v1296);	// L2070
  l_S_t_0_t10: for (int t10 = 0; t10 < 200; t10++) {	// L2071
    int32_t v1298 = v1286.read();	// L2072
    int32_t v1299 = dcred1[0];	// L2073
    ap_int<33> v1300 = v1299;	// L2074
    ap_int<33> v1301 = v1298;	// L2075
    ap_int<33> v1302 = v1300 + v1301;	// L2076
    int32_t v1303 = v1302;	// L2077
    dcred1[0] = v1303;	// L2078
    ap_uint<26> pw1;	// L2079
    pw1 = 0;	// L2080
    int32_t v1305 = sp1[0];	// L2081
    bool v1306 = v1305 < 200;	// L2082
    if (v1306) {	// L2083
      ap_uint<26> cand1;	// L2084
      cand1 = 0;	// L2085
      int32_t v1308 = sp1[0];	// L2086
      int v1309 = v1308;	// L2087
      int32_t v1310 = v1284[0][v1309];	// L2088
      ap_uint<26> v1311 = v1310;	// L2089
      ap_int<26> v1312 = cand1;	// L2090
      ap_int<26> v1313;
      ap_int<26> v1313_tmp = v1312;
      v1313_tmp(25, 0) = v1311;
      v1313 = v1313_tmp;	// L2091
      cand1 = v1313;	// L2092
      ap_int<26> v1314 = cand1;	// L2093
      bool v1315;
      ap_int<26> v1315_tmp = v1314;
      v1315 = v1315_tmp[25];	// L2094
      int32_t v1316 = v1315;	// L2095
      bool v1317 = v1316 == 0;	// L2096
      if (v1317) {	// L2097
        int32_t v1318 = sp1[0];	// L2098
        ap_int<33> v1319 = v1318;	// L2099
        ap_int<33> v1320 = v1319 + 1;	// L2100
        int32_t v1321 = v1320;	// L2101
        sp1[0] = v1321;	// L2102
      } else {
        int32_t v1322 = dcred1[0];	// L2104
        bool v1323 = v1322 > 0;	// L2105
        if (v1323) {	// L2106
          ap_int<26> v1324 = cand1;	// L2107
          pw1 = v1324;	// L2108
          int32_t v1325 = dcred1[0];	// L2109
          ap_int<33> v1326 = v1325;	// L2110
          ap_int<33> v1327 = v1326 - 1;	// L2111
          int32_t v1328 = v1327;	// L2112
          dcred1[0] = v1328;	// L2113
          int32_t v1329 = sp1[0];	// L2114
          ap_int<33> v1330 = v1329;	// L2115
          ap_int<33> v1331 = v1330 + 1;	// L2116
          int32_t v1332 = v1331;	// L2117
          sp1[0] = v1332;	// L2118
        }
      }
    }
    ap_int<26> v1333 = pw1;	// L2122
    v1285.write(v1333);	// L2123
  }
}

void rdrv_n_0(
  int32_t v1334[1][200],
  hls::stream< ap_uint<26> >& v1335,
  hls::stream< int32_t >& v1336
) {	// L2127
  int32_t dcred2[1];	// L2134
  for (int v1338 = 0; v1338 < 1; v1338++) {	// L2135
    dcred2[v1338] = 0;	// L2135
  }
  int32_t sp2[1];	// L2136
  for (int v1340 = 0; v1340 < 1; v1340++) {	// L2137
    sp2[v1340] = 0;	// L2137
  }
  ap_uint<26> zp2;	// L2138
  zp2 = 0;	// L2139
  ap_int<26> v1342 = zp2;	// L2140
  v1335.write(v1342);	// L2141
  ap_int<26> v1343 = zp2;	// L2142
  v1335.write(v1343);	// L2143
  ap_int<26> v1344 = zp2;	// L2144
  v1335.write(v1344);	// L2145
  ap_int<26> v1345 = zp2;	// L2146
  v1335.write(v1345);	// L2147
  ap_int<26> v1346 = zp2;	// L2148
  v1335.write(v1346);	// L2149
  l_S_t_0_t11: for (int t11 = 0; t11 < 200; t11++) {	// L2150
    int32_t v1348 = v1336.read();	// L2151
    int32_t v1349 = dcred2[0];	// L2152
    ap_int<33> v1350 = v1349;	// L2153
    ap_int<33> v1351 = v1348;	// L2154
    ap_int<33> v1352 = v1350 + v1351;	// L2155
    int32_t v1353 = v1352;	// L2156
    dcred2[0] = v1353;	// L2157
    ap_uint<26> pw2;	// L2158
    pw2 = 0;	// L2159
    int32_t v1355 = sp2[0];	// L2160
    bool v1356 = v1355 < 200;	// L2161
    if (v1356) {	// L2162
      ap_uint<26> cand2;	// L2163
      cand2 = 0;	// L2164
      int32_t v1358 = sp2[0];	// L2165
      int v1359 = v1358;	// L2166
      int32_t v1360 = v1334[0][v1359];	// L2167
      ap_uint<26> v1361 = v1360;	// L2168
      ap_int<26> v1362 = cand2;	// L2169
      ap_int<26> v1363;
      ap_int<26> v1363_tmp = v1362;
      v1363_tmp(25, 0) = v1361;
      v1363 = v1363_tmp;	// L2170
      cand2 = v1363;	// L2171
      ap_int<26> v1364 = cand2;	// L2172
      bool v1365;
      ap_int<26> v1365_tmp = v1364;
      v1365 = v1365_tmp[25];	// L2173
      int32_t v1366 = v1365;	// L2174
      bool v1367 = v1366 == 0;	// L2175
      if (v1367) {	// L2176
        int32_t v1368 = sp2[0];	// L2177
        ap_int<33> v1369 = v1368;	// L2178
        ap_int<33> v1370 = v1369 + 1;	// L2179
        int32_t v1371 = v1370;	// L2180
        sp2[0] = v1371;	// L2181
      } else {
        int32_t v1372 = dcred2[0];	// L2183
        bool v1373 = v1372 > 0;	// L2184
        if (v1373) {	// L2185
          ap_int<26> v1374 = cand2;	// L2186
          pw2 = v1374;	// L2187
          int32_t v1375 = dcred2[0];	// L2188
          ap_int<33> v1376 = v1375;	// L2189
          ap_int<33> v1377 = v1376 - 1;	// L2190
          int32_t v1378 = v1377;	// L2191
          dcred2[0] = v1378;	// L2192
          int32_t v1379 = sp2[0];	// L2193
          ap_int<33> v1380 = v1379;	// L2194
          ap_int<33> v1381 = v1380 + 1;	// L2195
          int32_t v1382 = v1381;	// L2196
          sp2[0] = v1382;	// L2197
        }
      }
    }
    ap_int<26> v1383 = pw2;	// L2201
    v1335.write(v1383);	// L2202
  }
}

void rdrv_s_0(
  int32_t v1384[1][200],
  hls::stream< ap_uint<26> >& v1385,
  hls::stream< int32_t >& v1386
) {	// L2206
  int32_t dcred3[1];	// L2213
  for (int v1388 = 0; v1388 < 1; v1388++) {	// L2214
    dcred3[v1388] = 0;	// L2214
  }
  int32_t sp3[1];	// L2215
  for (int v1390 = 0; v1390 < 1; v1390++) {	// L2216
    sp3[v1390] = 0;	// L2216
  }
  ap_uint<26> zp3;	// L2217
  zp3 = 0;	// L2218
  ap_int<26> v1392 = zp3;	// L2219
  v1385.write(v1392);	// L2220
  ap_int<26> v1393 = zp3;	// L2221
  v1385.write(v1393);	// L2222
  ap_int<26> v1394 = zp3;	// L2223
  v1385.write(v1394);	// L2224
  ap_int<26> v1395 = zp3;	// L2225
  v1385.write(v1395);	// L2226
  ap_int<26> v1396 = zp3;	// L2227
  v1385.write(v1396);	// L2228
  l_S_t_0_t12: for (int t12 = 0; t12 < 200; t12++) {	// L2229
    int32_t v1398 = v1386.read();	// L2230
    int32_t v1399 = dcred3[0];	// L2231
    ap_int<33> v1400 = v1399;	// L2232
    ap_int<33> v1401 = v1398;	// L2233
    ap_int<33> v1402 = v1400 + v1401;	// L2234
    int32_t v1403 = v1402;	// L2235
    dcred3[0] = v1403;	// L2236
    ap_uint<26> pw3;	// L2237
    pw3 = 0;	// L2238
    int32_t v1405 = sp3[0];	// L2239
    bool v1406 = v1405 < 200;	// L2240
    if (v1406) {	// L2241
      ap_uint<26> cand3;	// L2242
      cand3 = 0;	// L2243
      int32_t v1408 = sp3[0];	// L2244
      int v1409 = v1408;	// L2245
      int32_t v1410 = v1384[0][v1409];	// L2246
      ap_uint<26> v1411 = v1410;	// L2247
      ap_int<26> v1412 = cand3;	// L2248
      ap_int<26> v1413;
      ap_int<26> v1413_tmp = v1412;
      v1413_tmp(25, 0) = v1411;
      v1413 = v1413_tmp;	// L2249
      cand3 = v1413;	// L2250
      ap_int<26> v1414 = cand3;	// L2251
      bool v1415;
      ap_int<26> v1415_tmp = v1414;
      v1415 = v1415_tmp[25];	// L2252
      int32_t v1416 = v1415;	// L2253
      bool v1417 = v1416 == 0;	// L2254
      if (v1417) {	// L2255
        int32_t v1418 = sp3[0];	// L2256
        ap_int<33> v1419 = v1418;	// L2257
        ap_int<33> v1420 = v1419 + 1;	// L2258
        int32_t v1421 = v1420;	// L2259
        sp3[0] = v1421;	// L2260
      } else {
        int32_t v1422 = dcred3[0];	// L2262
        bool v1423 = v1422 > 0;	// L2263
        if (v1423) {	// L2264
          ap_int<26> v1424 = cand3;	// L2265
          pw3 = v1424;	// L2266
          int32_t v1425 = dcred3[0];	// L2267
          ap_int<33> v1426 = v1425;	// L2268
          ap_int<33> v1427 = v1426 - 1;	// L2269
          int32_t v1428 = v1427;	// L2270
          dcred3[0] = v1428;	// L2271
          int32_t v1429 = sp3[0];	// L2272
          ap_int<33> v1430 = v1429;	// L2273
          ap_int<33> v1431 = v1430 + 1;	// L2274
          int32_t v1432 = v1431;	// L2275
          sp3[0] = v1432;	// L2276
        }
      }
    }
    ap_int<26> v1433 = pw3;	// L2280
    v1385.write(v1433);	// L2281
  }
}

void rclc_w_0(
  int32_t v1434[1][200],
  hls::stream< int32_t >& v1435,
  hls::stream< ap_uint<26> >& v1436
) {	// L2285
  int32_t k6[1];	// L2294
  for (int v1438 = 0; v1438 < 1; v1438++) {	// L2295
    k6[v1438] = 0;	// L2295
  }
  int32_t cret[1];	// L2296
  for (int v1440 = 0; v1440 < 1; v1440++) {	// L2297
    cret[v1440] = 0;	// L2297
  }
  int32_t zc;	// L2298
  zc = 0;	// L2299
  int32_t v1442 = zc;	// L2300
  v1435.write(v1442);	// L2301
  int32_t v1443 = zc;	// L2302
  v1435.write(v1443);	// L2303
  int32_t v1444 = zc;	// L2304
  v1435.write(v1444);	// L2305
  int32_t v1445 = zc;	// L2306
  v1435.write(v1445);	// L2307
  int32_t v1446 = zc;	// L2308
  v1435.write(v1446);	// L2309
  cret[0] = 2;	// L2310
  int32_t v1447 = cret[0];	// L2311
  v1435.write(v1447);	// L2312
  l_S_t_0_t13: for (int t13 = 0; t13 < 200; t13++) {	// L2313
    ap_uint<26> v1449 = v1436.read();	// L2314
    ap_uint<26> pw4;	// L2315
    pw4 = v1449;	// L2316
    cret[0] = 0;	// L2317
    ap_int<26> v1451 = pw4;	// L2318
    bool v1452;
    ap_int<26> v1452_tmp = v1451;
    v1452 = v1452_tmp[25];	// L2319
    int32_t v1453 = v1452;	// L2320
    bool v1454 = v1453 == 1;	// L2321
    if (v1454) {	// L2322
      cret[0] = 1;	// L2323
      int32_t v1455 = k6[0];	// L2324
      bool v1456 = v1455 < 200;	// L2325
      if (v1456) {	// L2326
        ap_int<26> v1457 = pw4;	// L2327
        int32_t v1458 = v1457;	// L2328
        int32_t v1459 = v1458 & 67108863;	// L2329
        int32_t v1460 = k6[0];	// L2330
        int v1461 = v1460;	// L2331
        v1434[0][v1461] = v1459;	// L2332
        int32_t v1462 = k6[0];	// L2333
        ap_int<33> v1463 = v1462;	// L2334
        ap_int<33> v1464 = v1463 + 1;	// L2335
        int32_t v1465 = v1464;	// L2336
        k6[0] = v1465;	// L2337
      }
    }
    int32_t v1466 = cret[0];	// L2340
    v1435.write(v1466);	// L2341
  }
}

void rclc_e_0(
  int32_t v1467[1][200],
  hls::stream< int32_t >& v1468,
  hls::stream< ap_uint<26> >& v1469
) {	// L2345
  int32_t k7[1];	// L2354
  for (int v1471 = 0; v1471 < 1; v1471++) {	// L2355
    k7[v1471] = 0;	// L2355
  }
  int32_t cret1[1];	// L2356
  for (int v1473 = 0; v1473 < 1; v1473++) {	// L2357
    cret1[v1473] = 0;	// L2357
  }
  int32_t zc1;	// L2358
  zc1 = 0;	// L2359
  int32_t v1475 = zc1;	// L2360
  v1468.write(v1475);	// L2361
  int32_t v1476 = zc1;	// L2362
  v1468.write(v1476);	// L2363
  int32_t v1477 = zc1;	// L2364
  v1468.write(v1477);	// L2365
  int32_t v1478 = zc1;	// L2366
  v1468.write(v1478);	// L2367
  int32_t v1479 = zc1;	// L2368
  v1468.write(v1479);	// L2369
  cret1[0] = 2;	// L2370
  int32_t v1480 = cret1[0];	// L2371
  v1468.write(v1480);	// L2372
  l_S_t_0_t14: for (int t14 = 0; t14 < 200; t14++) {	// L2373
    ap_uint<26> v1482 = v1469.read();	// L2374
    ap_uint<26> pw5;	// L2375
    pw5 = v1482;	// L2376
    cret1[0] = 0;	// L2377
    ap_int<26> v1484 = pw5;	// L2378
    bool v1485;
    ap_int<26> v1485_tmp = v1484;
    v1485 = v1485_tmp[25];	// L2379
    int32_t v1486 = v1485;	// L2380
    bool v1487 = v1486 == 1;	// L2381
    if (v1487) {	// L2382
      cret1[0] = 1;	// L2383
      int32_t v1488 = k7[0];	// L2384
      bool v1489 = v1488 < 200;	// L2385
      if (v1489) {	// L2386
        ap_int<26> v1490 = pw5;	// L2387
        int32_t v1491 = v1490;	// L2388
        int32_t v1492 = v1491 & 67108863;	// L2389
        int32_t v1493 = k7[0];	// L2390
        int v1494 = v1493;	// L2391
        v1467[0][v1494] = v1492;	// L2392
        int32_t v1495 = k7[0];	// L2393
        ap_int<33> v1496 = v1495;	// L2394
        ap_int<33> v1497 = v1496 + 1;	// L2395
        int32_t v1498 = v1497;	// L2396
        k7[0] = v1498;	// L2397
      }
    }
    int32_t v1499 = cret1[0];	// L2400
    v1468.write(v1499);	// L2401
  }
}

void rclc_n_0(
  int32_t v1500[1][200],
  hls::stream< int32_t >& v1501,
  hls::stream< ap_uint<26> >& v1502
) {	// L2405
  int32_t k8[1];	// L2414
  for (int v1504 = 0; v1504 < 1; v1504++) {	// L2415
    k8[v1504] = 0;	// L2415
  }
  int32_t cret2[1];	// L2416
  for (int v1506 = 0; v1506 < 1; v1506++) {	// L2417
    cret2[v1506] = 0;	// L2417
  }
  int32_t zc2;	// L2418
  zc2 = 0;	// L2419
  int32_t v1508 = zc2;	// L2420
  v1501.write(v1508);	// L2421
  int32_t v1509 = zc2;	// L2422
  v1501.write(v1509);	// L2423
  int32_t v1510 = zc2;	// L2424
  v1501.write(v1510);	// L2425
  int32_t v1511 = zc2;	// L2426
  v1501.write(v1511);	// L2427
  int32_t v1512 = zc2;	// L2428
  v1501.write(v1512);	// L2429
  cret2[0] = 2;	// L2430
  int32_t v1513 = cret2[0];	// L2431
  v1501.write(v1513);	// L2432
  l_S_t_0_t15: for (int t15 = 0; t15 < 200; t15++) {	// L2433
    ap_uint<26> v1515 = v1502.read();	// L2434
    ap_uint<26> pw6;	// L2435
    pw6 = v1515;	// L2436
    cret2[0] = 0;	// L2437
    ap_int<26> v1517 = pw6;	// L2438
    bool v1518;
    ap_int<26> v1518_tmp = v1517;
    v1518 = v1518_tmp[25];	// L2439
    int32_t v1519 = v1518;	// L2440
    bool v1520 = v1519 == 1;	// L2441
    if (v1520) {	// L2442
      cret2[0] = 1;	// L2443
      int32_t v1521 = k8[0];	// L2444
      bool v1522 = v1521 < 200;	// L2445
      if (v1522) {	// L2446
        ap_int<26> v1523 = pw6;	// L2447
        int32_t v1524 = v1523;	// L2448
        int32_t v1525 = v1524 & 67108863;	// L2449
        int32_t v1526 = k8[0];	// L2450
        int v1527 = v1526;	// L2451
        v1500[0][v1527] = v1525;	// L2452
        int32_t v1528 = k8[0];	// L2453
        ap_int<33> v1529 = v1528;	// L2454
        ap_int<33> v1530 = v1529 + 1;	// L2455
        int32_t v1531 = v1530;	// L2456
        k8[0] = v1531;	// L2457
      }
    }
    int32_t v1532 = cret2[0];	// L2460
    v1501.write(v1532);	// L2461
  }
}

void rclc_s_0(
  int32_t v1533[1][200],
  hls::stream< int32_t >& v1534,
  hls::stream< ap_uint<26> >& v1535
) {	// L2465
  int32_t k9[1];	// L2474
  for (int v1537 = 0; v1537 < 1; v1537++) {	// L2475
    k9[v1537] = 0;	// L2475
  }
  int32_t cret3[1];	// L2476
  for (int v1539 = 0; v1539 < 1; v1539++) {	// L2477
    cret3[v1539] = 0;	// L2477
  }
  int32_t zc3;	// L2478
  zc3 = 0;	// L2479
  int32_t v1541 = zc3;	// L2480
  v1534.write(v1541);	// L2481
  int32_t v1542 = zc3;	// L2482
  v1534.write(v1542);	// L2483
  int32_t v1543 = zc3;	// L2484
  v1534.write(v1543);	// L2485
  int32_t v1544 = zc3;	// L2486
  v1534.write(v1544);	// L2487
  int32_t v1545 = zc3;	// L2488
  v1534.write(v1545);	// L2489
  cret3[0] = 2;	// L2490
  int32_t v1546 = cret3[0];	// L2491
  v1534.write(v1546);	// L2492
  l_S_t_0_t16: for (int t16 = 0; t16 < 200; t16++) {	// L2493
    ap_uint<26> v1548 = v1535.read();	// L2494
    ap_uint<26> pw7;	// L2495
    pw7 = v1548;	// L2496
    cret3[0] = 0;	// L2497
    ap_int<26> v1550 = pw7;	// L2498
    bool v1551;
    ap_int<26> v1551_tmp = v1550;
    v1551 = v1551_tmp[25];	// L2499
    int32_t v1552 = v1551;	// L2500
    bool v1553 = v1552 == 1;	// L2501
    if (v1553) {	// L2502
      cret3[0] = 1;	// L2503
      int32_t v1554 = k9[0];	// L2504
      bool v1555 = v1554 < 200;	// L2505
      if (v1555) {	// L2506
        ap_int<26> v1556 = pw7;	// L2507
        int32_t v1557 = v1556;	// L2508
        int32_t v1558 = v1557 & 67108863;	// L2509
        int32_t v1559 = k9[0];	// L2510
        int v1560 = v1559;	// L2511
        v1533[0][v1560] = v1558;	// L2512
        int32_t v1561 = k9[0];	// L2513
        ap_int<33> v1562 = v1561;	// L2514
        ap_int<33> v1563 = v1562 + 1;	// L2515
        int32_t v1564 = v1563;	// L2516
        k9[0] = v1564;	// L2517
      }
    }
    int32_t v1565 = cret3[0];	// L2520
    v1534.write(v1565);	// L2521
  }
}

/// This is top function.
void top(
  int32_t v1566[1][1][200],
  half v1567[1][200],
  int32_t v1568[1][200],
  half v1569[1][200],
  int32_t v1570[1][200],
  half v1571[1][200],
  int32_t v1572[1][200],
  half v1573[1][200],
  int32_t v1574[1][200],
  half v1575[1][200],
  half v1576[1][200],
  int32_t v1577[1][200],
  half v1578[1][200],
  half v1579[1][200],
  int32_t v1580[1][200],
  int32_t v1581[1][200],
  int32_t v1582[1][200],
  int32_t v1583[1][200],
  int32_t v1584[1][200],
  int32_t v1585[1][200],
  int32_t v1586[1][200],
  int32_t v1587[1][200],
  int32_t v1588[1][200]
) {	// L2525
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v1589;
  #pragma HLS stream variable=v1589 depth=8	// L2526
  hls::stream< ap_uint<17> > v1590;
  #pragma HLS stream variable=v1590 depth=8	// L2527
  hls::stream< ap_uint<17> > v1591;
  #pragma HLS stream variable=v1591 depth=8	// L2528
  hls::stream< ap_uint<17> > v1592;
  #pragma HLS stream variable=v1592 depth=8	// L2529
  hls::stream< ap_uint<17> > v1593;
  #pragma HLS stream variable=v1593 depth=8	// L2530
  hls::stream< ap_uint<17> > v1594;
  #pragma HLS stream variable=v1594 depth=8	// L2531
  hls::stream< ap_uint<17> > v1595;
  #pragma HLS stream variable=v1595 depth=8	// L2532
  hls::stream< ap_uint<17> > v1596;
  #pragma HLS stream variable=v1596 depth=8	// L2533
  hls::stream< ap_uint<26> > v1597;
  #pragma HLS stream variable=v1597 depth=8	// L2534
  hls::stream< ap_uint<26> > v1598;
  #pragma HLS stream variable=v1598 depth=8	// L2535
  hls::stream< ap_uint<26> > v1599;
  #pragma HLS stream variable=v1599 depth=8	// L2536
  hls::stream< ap_uint<26> > v1600;
  #pragma HLS stream variable=v1600 depth=8	// L2537
  hls::stream< ap_uint<26> > v1601;
  #pragma HLS stream variable=v1601 depth=8	// L2538
  hls::stream< ap_uint<26> > v1602;
  #pragma HLS stream variable=v1602 depth=8	// L2539
  hls::stream< ap_uint<26> > v1603;
  #pragma HLS stream variable=v1603 depth=8	// L2540
  hls::stream< ap_uint<26> > v1604;
  #pragma HLS stream variable=v1604 depth=8	// L2541
  hls::stream< int32_t > v1605;
  #pragma HLS stream variable=v1605 depth=8	// L2542
  hls::stream< int32_t > v1606;
  #pragma HLS stream variable=v1606 depth=8	// L2543
  hls::stream< int32_t > v1607;
  #pragma HLS stream variable=v1607 depth=8	// L2544
  hls::stream< int32_t > v1608;
  #pragma HLS stream variable=v1608 depth=8	// L2545
  hls::stream< int32_t > v1609;
  #pragma HLS stream variable=v1609 depth=8	// L2546
  hls::stream< int32_t > v1610;
  #pragma HLS stream variable=v1610 depth=8	// L2547
  hls::stream< int32_t > v1611;
  #pragma HLS stream variable=v1611 depth=8	// L2548
  hls::stream< int32_t > v1612;
  #pragma HLS stream variable=v1612 depth=8	// L2549
  node_0_0(v1566, v1598, v1599, v1602, v1603, v1590, v1591, v1594, v1595, v1605, v1608, v1609, v1612, v1597, v1600, v1601, v1604, v1606, v1607, v1610, v1611, v1589, v1592, v1593, v1596);	// L2550
  drv_w_0(v1567, v1568, v1589);	// L2551
  drv_e_0(v1569, v1570, v1592);	// L2552
  drv_n_0(v1571, v1572, v1593);	// L2553
  drv_s_0(v1573, v1574, v1596);	// L2554
  col_w_0(v1575, v1591);	// L2555
  col_e_0(v1576, v1577, v1590);	// L2556
  col_n_0(v1578, v1595);	// L2557
  col_s_0(v1579, v1580, v1594);	// L2558
  rdrv_w_0(v1581, v1597, v1605);	// L2559
  rdrv_e_0(v1582, v1600, v1608);	// L2560
  rdrv_n_0(v1583, v1601, v1609);	// L2561
  rdrv_s_0(v1584, v1604, v1612);	// L2562
  rclc_w_0(v1585, v1607, v1599);	// L2563
  rclc_e_0(v1586, v1606, v1598);	// L2564
  rclc_n_0(v1587, v1611, v1603);	// L2565
  rclc_s_0(v1588, v1610, v1602);	// L2566
}

