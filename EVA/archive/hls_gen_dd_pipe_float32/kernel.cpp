
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
  hls::stream< ap_uint<17> >& v4,
  hls::stream< ap_uint<17> >& v5,
  hls::stream< ap_uint<17> >& v6,
  hls::stream< ap_uint<17> >& v7,
  hls::stream< int32_t >& v8,
  hls::stream< int32_t >& v9,
  hls::stream< int32_t >& v10,
  hls::stream< int32_t >& v11,
  hls::stream< ap_uint<26> >& v12,
  hls::stream< ap_uint<26> >& v13,
  hls::stream< ap_uint<26> >& v14,
  hls::stream< ap_uint<26> >& v15,
  hls::stream< int32_t >& v16,
  hls::stream< int32_t >& v17,
  hls::stream< int32_t >& v18,
  hls::stream< int32_t >& v19,
  hls::stream< ap_uint<17> >& v20,
  hls::stream< ap_uint<17> >& v21,
  hls::stream< ap_uint<17> >& v22,
  hls::stream< ap_uint<17> >& v23
) {	// L4
  int32_t irf[8];	// L35
  for (int v25 = 0; v25 < 8; v25++) {	// L36
    irf[v25] = 0;	// L36
  }
  half drf[8];	// L37
  #pragma HLS array_partition variable=drf complete dim=1

  for (int v27 = 0; v27 < 8; v27++) {	// L38
    drf[v27] = (double)0.000000;	// L38
  }
  int32_t drf_full[8];	// L39
  #pragma HLS array_partition variable=drf_full complete dim=1

  for (int v29 = 0; v29 < 8; v29++) {	// L40
    drf_full[v29] = 0;	// L40
  }
  int32_t dsmask;	// L41
  dsmask = 0;	// L42
  int32_t crv_vld;	// L43
  crv_vld = 0;	// L44
  half crv_data;	// L45
  crv_data = (double)0.000000;	// L46
  int32_t crv_addr;	// L47
  crv_addr = 0;	// L48
  int32_t crv_mode;	// L49
  crv_mode = 0;	// L50
  int32_t crv_raw;	// L51
  crv_raw = 0;	// L52
  int32_t csd_vld;	// L53
  csd_vld = 0;	// L54
  ap_uint<26> csd_pkt;	// L55
  csd_pkt = 0;	// L56
  int32_t csd_dir;	// L57
  csd_dir = 0;	// L58
  int32_t row_id;	// L59
  row_id = 0;	// L60
  int32_t col_id;	// L61
  col_id = 0;	// L62
  ap_uint<26> oe_r;	// L63
  oe_r = 0;	// L64
  ap_uint<26> ow_r;	// L65
  ow_r = 0;	// L66
  ap_uint<26> on_r;	// L67
  on_r = 0;	// L68
  ap_uint<26> os_r;	// L69
  os_r = 0;	// L70
  ap_uint<17> txn_r;	// L71
  txn_r = 0;	// L72
  ap_uint<17> txs_r;	// L73
  txs_r = 0;	// L74
  ap_uint<17> txw_r;	// L75
  txw_r = 0;	// L76
  ap_uint<17> txe_r;	// L77
  txe_r = 0;	// L78
  half hold_v[4][2];	// L79
  #pragma HLS array_partition variable=hold_v complete dim=1
  #pragma HLS array_partition variable=hold_v complete dim=2

  for (int v50 = 0; v50 < 4; v50++) {	// L80
    for (int v51 = 0; v51 < 2; v51++) {	// L80
      hold_v[v50][v51] = (double)0.000000;	// L80
    }
  }
  int32_t hold_cnt[4];	// L81
  #pragma HLS array_partition variable=hold_cnt complete dim=1

  for (int v53 = 0; v53 < 4; v53++) {	// L82
    hold_cnt[v53] = 0;	// L82
  }
  ap_uint<26> rbuf[4][2];	// L83
  #pragma HLS array_partition variable=rbuf complete dim=1
  #pragma HLS array_partition variable=rbuf complete dim=2

  for (int v55 = 0; v55 < 4; v55++) {	// L84
    for (int v56 = 0; v56 < 2; v56++) {	// L84
      rbuf[v55][v56] = 0;	// L84
    }
  }
  int32_t rbcnt[4];	// L85
  #pragma HLS array_partition variable=rbcnt complete dim=1

  for (int v58 = 0; v58 < 4; v58++) {	// L86
    rbcnt[v58] = 0;	// L86
  }
  int32_t rcred[4];	// L87
  #pragma HLS array_partition variable=rcred complete dim=1

  for (int v60 = 0; v60 < 4; v60++) {	// L88
    rcred[v60] = 0;	// L88
  }
  int32_t cre_r;	// L89
  cre_r = 2;	// L90
  int32_t crw_r;	// L91
  crw_r = 2;	// L92
  int32_t crs_r;	// L93
  crs_r = 2;	// L94
  int32_t crn_r;	// L95
  crn_r = 2;	// L96
  int32_t cfg_isz;	// L97
  cfg_isz = 0;	// L98
  int32_t cfg_itsz;	// L99
  cfg_itsz = 0;	// L100
  int32_t fetch_en;	// L101
  fetch_en = 0;	// L102
  int32_t instr_cnt;	// L103
  instr_cnt = 0;	// L104
  int32_t iter_cnt;	// L105
  iter_cnt = 0;	// L106
  int32_t condition_reg;	// L107
  condition_reg = 0;	// L108
  l_S_t_0_t: for (int t = 0; t < 8; t++) {	// L109
  #pragma HLS pipeline II=1
    ap_int<26> v72 = oe_r;	// L110
    v0.write(v72);	// L111
    ap_int<26> v73 = ow_r;	// L112
    v1.write(v73);	// L113
    ap_int<26> v74 = os_r;	// L114
    v2.write(v74);	// L115
    ap_int<26> v75 = on_r;	// L116
    v3.write(v75);	// L117
    ap_int<17> v76 = txe_r;	// L118
    v4.write(v76);	// L119
    ap_int<17> v77 = txw_r;	// L120
    v5.write(v77);	// L121
    ap_int<17> v78 = txs_r;	// L122
    v6.write(v78);	// L123
    ap_int<17> v79 = txn_r;	// L124
    v7.write(v79);	// L125
    int32_t v80 = cre_r;	// L126
    v8.write(v80);	// L127
    int32_t v81 = crw_r;	// L128
    v9.write(v81);	// L129
    int32_t v82 = crs_r;	// L130
    v10.write(v82);	// L131
    int32_t v83 = crn_r;	// L132
    v11.write(v83);	// L133
    ap_uint<26> v84 = v12.read();	// L134
    ap_uint<26> p_w;	// L135
    p_w = v84;	// L136
    ap_uint<26> v86 = v13.read();	// L137
    ap_uint<26> p_e;	// L138
    p_e = v86;	// L139
    ap_uint<26> v88 = v14.read();	// L140
    ap_uint<26> p_n;	// L141
    p_n = v88;	// L142
    ap_uint<26> v90 = v15.read();	// L143
    ap_uint<26> p_s;	// L144
    p_s = v90;	// L145
    int32_t v92 = v16.read();	// L146
    int32_t v93 = rcred[0];	// L147
    ap_int<33> v94 = v93;	// L148
    ap_int<33> v95 = v92;	// L149
    ap_int<33> v96 = v94 + v95;	// L150
    int32_t v97 = v96;	// L151
    rcred[0] = v97;	// L152
    int32_t v98 = v17.read();	// L153
    int32_t v99 = rcred[1];	// L154
    ap_int<33> v100 = v99;	// L155
    ap_int<33> v101 = v98;	// L156
    ap_int<33> v102 = v100 + v101;	// L157
    int32_t v103 = v102;	// L158
    rcred[1] = v103;	// L159
    int32_t v104 = v18.read();	// L160
    int32_t v105 = rcred[2];	// L161
    ap_int<33> v106 = v105;	// L162
    ap_int<33> v107 = v104;	// L163
    ap_int<33> v108 = v106 + v107;	// L164
    int32_t v109 = v108;	// L165
    rcred[2] = v109;	// L166
    int32_t v110 = v19.read();	// L167
    int32_t v111 = rcred[3];	// L168
    ap_int<33> v112 = v111;	// L169
    ap_int<33> v113 = v110;	// L170
    ap_int<33> v114 = v112 + v113;	// L171
    int32_t v115 = v114;	// L172
    rcred[3] = v115;	// L173
    ap_uint<26> fin[4];	// L174
    for (int v117 = 0; v117 < 4; v117++) {	// L175
      fin[v117] = 0;	// L175
    }
    ap_int<26> v118 = p_w;	// L176
    fin[0] = v118;	// L177
    ap_int<26> v119 = p_e;	// L178
    fin[1] = v119;	// L179
    ap_int<26> v120 = p_n;	// L180
    fin[2] = v120;	// L181
    ap_int<26> v121 = p_s;	// L182
    fin[3] = v121;	// L183
    l_S_d_0_d: for (int d = 0; d < 4; d++) {	// L184
      ap_uint<26> v123 = fin[d];	// L185
      bool v124;
      ap_int<26> v124_tmp = v123;
      v124 = v124_tmp[25];	// L186
      int32_t v125 = v124;	// L187
      bool v126 = v125 == 1;	// L188
      int32_t v127 = rbcnt[d];	// L189
      bool v128 = v127 < 2;	// L190
      bool v129 = v126 & v128;	// L191
      if (v129) {	// L192
        ap_uint<26> v130 = fin[d];	// L193
        int32_t v131 = rbcnt[d];	// L194
        int v132 = v131;	// L195
        rbuf[d][v132] = v130;	// L196
        int32_t v133 = rbcnt[d];	// L197
        ap_int<33> v134 = v133;	// L198
        ap_int<33> v135 = v134 + 1;	// L199
        int32_t v136 = v135;	// L200
        rbcnt[d] = v136;	// L201
      }
    }
    ap_uint<26> hd[4];	// L204
    for (int v138 = 0; v138 < 4; v138++) {	// L205
      hd[v138] = 0;	// L205
    }
    int32_t hvld[4];	// L206
    for (int v140 = 0; v140 < 4; v140++) {	// L207
      hvld[v140] = 0;	// L207
    }
    int32_t hit[4];	// L208
    for (int v142 = 0; v142 < 4; v142++) {	// L209
      hit[v142] = 0;	// L209
    }
    int32_t axis[4];	// L210
    for (int v144 = 0; v144 < 4; v144++) {	// L211
      axis[v144] = 0;	// L211
    }
    int32_t v145 = col_id;	// L212
    axis[0] = v145;	// L213
    int32_t v146 = col_id;	// L214
    axis[1] = v146;	// L215
    int32_t v147 = row_id;	// L216
    axis[2] = v147;	// L217
    int32_t v148 = row_id;	// L218
    axis[3] = v148;	// L219
    l_S_d_1_d1: for (int d1 = 0; d1 < 4; d1++) {	// L220
      int32_t v150 = rbcnt[d1];	// L221
      bool v151 = v150 > 0;	// L222
      if (v151) {	// L223
        ap_uint<26> v152 = rbuf[d1][0];	// L224
        hd[d1] = v152;	// L225
        hvld[d1] = 1;	// L226
        ap_uint<26> v153 = hd[d1];	// L227
        ap_int<4> v154;
        ap_int<26> v154_tmp = v153;
        v154 = v154_tmp(24, 21);	// L228
        int32_t v155 = axis[d1];	// L229
        int32_t v156 = v154;	// L230
        bool v157 = v156 == v155;	// L231
        if (v157) {	// L232
          hit[d1] = 1;	// L233
        }
      }
    }
    ap_uint<26> o_crv;	// L237
    o_crv = 0;	// L238
    int32_t crv_in;	// L239
    crv_in = -1;	// L240
    int32_t v160 = hit[3];	// L241
    bool v161 = v160 == 1;	// L242
    if (v161) {	// L243
      ap_uint<26> v162 = hd[3];	// L244
      o_crv = v162;	// L245
      crv_in = 3;	// L246
    } else {
      int32_t v163 = hit[2];	// L248
      bool v164 = v163 == 1;	// L249
      if (v164) {	// L250
        ap_uint<26> v165 = hd[2];	// L251
        o_crv = v165;	// L252
        crv_in = 2;	// L253
      } else {
        int32_t v166 = hit[1];	// L255
        bool v167 = v166 == 1;	// L256
        if (v167) {	// L257
          ap_uint<26> v168 = hd[1];	// L258
          o_crv = v168;	// L259
          crv_in = 1;	// L260
        } else {
          int32_t v169 = hit[0];	// L262
          bool v170 = v169 == 1;	// L263
          if (v170) {	// L264
            ap_uint<26> v171 = hd[0];	// L265
            o_crv = v171;	// L266
            crv_in = 0;	// L267
          }
        }
      }
    }
    ap_uint<26> o_out[4];	// L272
    for (int v173 = 0; v173 < 4; v173++) {	// L273
      o_out[v173] = 0;	// L273
    }
    int32_t pop[4];	// L274
    for (int v175 = 0; v175 < 4; v175++) {	// L275
      pop[v175] = 0;	// L275
    }
    int32_t inj_done;	// L276
    inj_done = 0;	// L277
    int32_t idir;	// L278
    idir = -1;	// L279
    ap_int<26> v178 = csd_pkt;	// L280
    bool v179;
    ap_int<26> v179_tmp = v178;
    v179 = v179_tmp[25];	// L281
    int32_t v180 = v179;	// L282
    bool v181 = v180 == 1;	// L283
    if (v181) {	// L284
      int32_t v182 = csd_dir;	// L285
      ap_int<33> v183 = v182;	// L286
      ap_int<33> v184 = 3 - v183;	// L287
      int32_t v185 = v184;	// L288
      idir = v185;	// L289
    }
    l_S_o_2_o: for (int o = 0; o < 4; o++) {	// L291
      int32_t v187 = rcred[o];	// L292
      bool v188 = v187 > 0;	// L293
      if (v188) {	// L294
        int32_t v189 = idir;	// L295
        ap_int<33> v190 = v189;	// L296
        ap_int<33> v191 = o;	// L297
        bool v192 = v190 == v191;	// L298
        if (v192) {	// L299
          ap_int<26> v193 = csd_pkt;	// L300
          o_out[o] = v193;	// L301
          int32_t v194 = rcred[o];	// L302
          ap_int<33> v195 = v194;	// L303
          ap_int<33> v196 = v195 - 1;	// L304
          int32_t v197 = v196;	// L305
          rcred[o] = v197;	// L306
          inj_done = 1;	// L307
        } else {
          int32_t v198 = hvld[o];	// L309
          bool v199 = v198 == 1;	// L310
          int32_t v200 = hit[o];	// L311
          bool v201 = v200 == 0;	// L312
          bool v202 = v199 & v201;	// L313
          if (v202) {	// L314
            ap_uint<26> v203 = hd[o];	// L315
            o_out[o] = v203;	// L316
            int32_t v204 = rcred[o];	// L317
            ap_int<33> v205 = v204;	// L318
            ap_int<33> v206 = v205 - 1;	// L319
            int32_t v207 = v206;	// L320
            rcred[o] = v207;	// L321
            pop[o] = 1;	// L322
          }
        }
      }
    }
    int32_t v208 = crv_in;	// L327
    bool v209 = v208 >= 0;	// L328
    if (v209) {	// L329
      int32_t v210 = crv_in;	// L330
      int v211 = v210;	// L331
      pop[v211] = 1;	// L332
    }
    int32_t ret[4];	// L334
    for (int v213 = 0; v213 < 4; v213++) {	// L335
      ret[v213] = 0;	// L335
    }
    l_S_d_3_d2: for (int d2 = 0; d2 < 4; d2++) {	// L336
      int32_t v215 = pop[d2];	// L337
      bool v216 = v215 == 1;	// L338
      if (v216) {	// L339
        l_S_sft_3_sft: for (int sft = 0; sft < 1; sft++) {	// L340
          ap_uint<26> v218 = rbuf[d2][(sft + 1)];	// L341
          rbuf[d2][sft] = v218;	// L342
        }
        int32_t v219 = rbcnt[d2];	// L344
        ap_int<33> v220 = v219;	// L345
        ap_int<33> v221 = v220 - 1;	// L346
        int32_t v222 = v221;	// L347
        rbcnt[d2] = v222;	// L348
        ret[d2] = 1;	// L349
      }
    }
    int32_t v223 = ret[0];	// L352
    cre_r = v223;	// L353
    int32_t v224 = ret[1];	// L354
    crw_r = v224;	// L355
    int32_t v225 = ret[2];	// L356
    crs_r = v225;	// L357
    int32_t v226 = ret[3];	// L358
    crn_r = v226;	// L359
    ap_uint<26> v227 = o_out[0];	// L360
    oe_r = v227;	// L361
    ap_uint<26> v228 = o_out[1];	// L362
    ow_r = v228;	// L363
    ap_uint<26> v229 = o_out[2];	// L364
    os_r = v229;	// L365
    ap_uint<26> v230 = o_out[3];	// L366
    on_r = v230;	// L367
    int32_t v231 = inj_done;	// L368
    bool v232 = v231 == 1;	// L369
    if (v232) {	// L370
      csd_pkt = 0;	// L371
    }
    ap_int<26> v233 = o_crv;	// L373
    bool v234;
    ap_int<26> v234_tmp = v233;
    v234 = v234_tmp[25];	// L374
    int32_t v235 = v234;	// L375
    crv_vld = v235;	// L376
    ap_int<26> v236 = o_crv;	// L377
    int16_t v237;
    ap_int<26> v237_tmp = v236;
    v237 = v237_tmp(15, 0);	// L378
    half v238;
    union { uint16_t from; half to;} _converter_v237_to_v238;
    _converter_v237_to_v238.from = v237;
    v238 = _converter_v237_to_v238.to;	// L379
    crv_data = v238;	// L380
    ap_int<26> v239 = o_crv;	// L381
    ap_int<4> v240;
    ap_int<26> v240_tmp = v239;
    v240 = v240_tmp(19, 16);	// L382
    int32_t v241 = v240;	// L383
    crv_addr = v241;	// L384
    ap_int<26> v242 = o_crv;	// L385
    bool v243;
    ap_int<26> v243_tmp = v242;
    v243 = v243_tmp[20];	// L386
    int32_t v244 = v243;	// L387
    crv_mode = v244;	// L388
    ap_int<26> v245 = o_crv;	// L389
    int16_t v246;
    ap_int<26> v246_tmp = v245;
    v246 = v246_tmp(15, 0);	// L390
    int32_t v247 = v246;	// L391
    crv_raw = v247;	// L392
    ap_uint<17> v248 = v20.read();	// L393
    ap_uint<17> rx_w;	// L394
    rx_w = v248;	// L395
    ap_uint<17> v250 = v21.read();	// L396
    ap_uint<17> rx_e;	// L397
    rx_e = v250;	// L398
    ap_uint<17> v252 = v22.read();	// L399
    ap_uint<17> rx_n;	// L400
    rx_n = v252;	// L401
    ap_uint<17> v254 = v23.read();	// L402
    ap_uint<17> rx_s;	// L403
    rx_s = v254;	// L404
    half rxv[4];	// L405
    for (int v257 = 0; v257 < 4; v257++) {	// L406
      rxv[v257] = (double)0.000000;	// L406
    }
    int32_t rxvld[4];	// L407
    for (int v259 = 0; v259 < 4; v259++) {	// L408
      rxvld[v259] = 0;	// L408
    }
    ap_int<17> v260 = rx_n;	// L409
    int16_t v261;
    ap_int<17> v261_tmp = v260;
    v261 = v261_tmp(16, 1);	// L410
    half v262;
    union { uint16_t from; half to;} _converter_v261_to_v262;
    _converter_v261_to_v262.from = v261;
    v262 = _converter_v261_to_v262.to;	// L411
    rxv[0] = v262;	// L412
    ap_int<17> v263 = rx_n;	// L413
    bool v264;
    ap_int<17> v264_tmp = v263;
    v264 = v264_tmp[0];	// L414
    int32_t v265 = v264;	// L415
    rxvld[0] = v265;	// L416
    ap_int<17> v266 = rx_s;	// L417
    int16_t v267;
    ap_int<17> v267_tmp = v266;
    v267 = v267_tmp(16, 1);	// L418
    half v268;
    union { uint16_t from; half to;} _converter_v267_to_v268;
    _converter_v267_to_v268.from = v267;
    v268 = _converter_v267_to_v268.to;	// L419
    rxv[1] = v268;	// L420
    ap_int<17> v269 = rx_s;	// L421
    bool v270;
    ap_int<17> v270_tmp = v269;
    v270 = v270_tmp[0];	// L422
    int32_t v271 = v270;	// L423
    rxvld[1] = v271;	// L424
    ap_int<17> v272 = rx_w;	// L425
    int16_t v273;
    ap_int<17> v273_tmp = v272;
    v273 = v273_tmp(16, 1);	// L426
    half v274;
    union { uint16_t from; half to;} _converter_v273_to_v274;
    _converter_v273_to_v274.from = v273;
    v274 = _converter_v273_to_v274.to;	// L427
    rxv[2] = v274;	// L428
    ap_int<17> v275 = rx_w;	// L429
    bool v276;
    ap_int<17> v276_tmp = v275;
    v276 = v276_tmp[0];	// L430
    int32_t v277 = v276;	// L431
    rxvld[2] = v277;	// L432
    ap_int<17> v278 = rx_e;	// L433
    int16_t v279;
    ap_int<17> v279_tmp = v278;
    v279 = v279_tmp(16, 1);	// L434
    half v280;
    union { uint16_t from; half to;} _converter_v279_to_v280;
    _converter_v279_to_v280.from = v279;
    v280 = _converter_v279_to_v280.to;	// L435
    rxv[3] = v280;	// L436
    ap_int<17> v281 = rx_e;	// L437
    bool v282;
    ap_int<17> v282_tmp = v281;
    v282 = v282_tmp[0];	// L438
    int32_t v283 = v282;	// L439
    rxvld[3] = v283;	// L440
    l_S_d_5_d3: for (int d3 = 0; d3 < 4; d3++) {	// L441
      int32_t v285 = rxvld[d3];	// L442
      bool v286 = v285 == 1;	// L443
      int32_t v287 = hold_cnt[d3];	// L444
      bool v288 = v287 < 2;	// L445
      bool v289 = v286 & v288;	// L446
      if (v289) {	// L447
        half v290 = rxv[d3];	// L448
        int32_t v291 = hold_cnt[d3];	// L449
        int v292 = v291;	// L450
        hold_v[d3][v292] = v290;	// L451
        int32_t v293 = hold_cnt[d3];	// L452
        ap_int<33> v294 = v293;	// L453
        ap_int<33> v295 = v294 + 1;	// L454
        int32_t v296 = v295;	// L455
        hold_cnt[d3] = v296;	// L456
      }
    }
    int32_t pc;	// L459
    pc = -1;	// L460
    int32_t v298 = fetch_en;	// L461
    bool v299 = v298 == 1;	// L462
    if (v299) {	// L463
      int32_t v300 = instr_cnt;	// L464
      pc = v300;	// L465
    }
    int32_t instr;	// L467
    instr = 0;	// L468
    int32_t v302 = pc;	// L469
    bool v303 = v302 >= 0;	// L470
    if (v303) {	// L471
      int32_t v304 = pc;	// L472
      int v305 = v304;	// L473
      int32_t v306 = irf[v305];	// L474
      instr = v306;	// L475
    }
    int32_t v307 = instr;	// L477
    int32_t v308 = v307 & 15;	// L478
    int32_t op;	// L479
    op = v308;	// L480
    int32_t v310 = instr;	// L481
    int32_t v311 = v310 >> 4;	// L482
    int32_t v312 = v311 & 15;	// L483
    int32_t dst;	// L484
    dst = v312;	// L485
    int32_t v314 = instr;	// L486
    int32_t v315 = v314 >> 8;	// L487
    int32_t v316 = v315 & 15;	// L488
    int32_t s1;	// L489
    s1 = v316;	// L490
    int32_t v318 = instr;	// L491
    int32_t v319 = v318 >> 12;	// L492
    int32_t v320 = v319 & 15;	// L493
    int32_t s2;	// L494
    s2 = v320;	// L495
    half a;	// L496
    a = (double)0.000000;	// L497
    half b;	// L498
    b = (double)0.000000;	// L499
    int32_t v324 = s1;	// L500
    bool v325 = v324 >= 12;	// L501
    if (v325) {	// L502
      int32_t v326 = s1;	// L503
      int32_t v327 = v326 & 3;	// L504
      int v328 = v327;	// L505
      half v329 = hold_v[v328][0];	// L506
      a = v329;	// L507
    } else {
      int32_t v330 = s1;	// L509
      int v331 = v330;	// L510
      half v332 = drf[v331];	// L511
      a = v332;	// L512
    }
    int32_t v333 = s2;	// L514
    bool v334 = v333 >= 12;	// L515
    if (v334) {	// L516
      int32_t v335 = s2;	// L517
      int32_t v336 = v335 & 3;	// L518
      int v337 = v336;	// L519
      half v338 = hold_v[v337][0];	// L520
      b = v338;	// L521
    } else {
      int32_t v339 = s2;	// L523
      int v340 = v339;	// L524
      half v341 = drf[v340];	// L525
      b = v341;	// L526
    }
    int32_t a_vld;	// L528
    a_vld = 1;	// L529
    int32_t b_vld;	// L530
    b_vld = 1;	// L531
    int32_t v344 = s1;	// L532
    bool v345 = v344 >= 12;	// L533
    if (v345) {	// L534
      a_vld = 0;	// L535
      int32_t v346 = s1;	// L536
      int32_t v347 = v346 & 3;	// L537
      int v348 = v347;	// L538
      int32_t v349 = hold_cnt[v348];	// L539
      bool v350 = v349 > 0;	// L540
      if (v350) {	// L541
        a_vld = 1;	// L542
      }
    }
    int32_t v351 = s2;	// L545
    bool v352 = v351 >= 12;	// L546
    if (v352) {	// L547
      b_vld = 0;	// L548
      int32_t v353 = s2;	// L549
      int32_t v354 = v353 & 3;	// L550
      int v355 = v354;	// L551
      int32_t v356 = hold_cnt[v355];	// L552
      bool v357 = v356 > 0;	// L553
      if (v357) {	// L554
        b_vld = 1;	// L555
      }
    }
    int32_t v358 = s1;	// L558
    bool v359 = v358 < 8;	// L559
    int32_t v360 = dsmask;	// L560
    int32_t v361 = v360 >> v358;	// L561
    int32_t v362 = v361 & 1;	// L562
    bool v363 = v362 == 1;	// L563
    bool v364 = v359 & v363;	// L564
    if (v364) {	// L565
      int32_t v365 = s1;	// L566
      int v366 = v365;	// L567
      int32_t v367 = drf_full[v366];	// L568
      bool v368 = v367 == 0;	// L569
      if (v368) {	// L570
        a_vld = 0;	// L571
      }
    }
    int32_t v369 = s2;	// L574
    bool v370 = v369 < 8;	// L575
    int32_t v371 = dsmask;	// L576
    int32_t v372 = v371 >> v369;	// L577
    int32_t v373 = v372 & 1;	// L578
    bool v374 = v373 == 1;	// L579
    bool v375 = v370 & v374;	// L580
    if (v375) {	// L581
      int32_t v376 = s2;	// L582
      int v377 = v376;	// L583
      int32_t v378 = drf_full[v377];	// L584
      bool v379 = v378 == 0;	// L585
      if (v379) {	// L586
        b_vld = 0;	// L587
      }
    }
    int32_t binop;	// L590
    binop = 0;	// L591
    int32_t v381 = op;	// L592
    bool v382 = v381 == 0;	// L593
    bool v383 = v381 == 1;	// L594
    bool v384 = v381 == 2;	// L595
    bool v385 = v381 == 8;	// L596
    bool v386 = v381 == 9;	// L597
    bool v387 = v382 | v383;	// L598
    bool v388 = v387 | v384;	// L599
    bool v389 = v388 | v385;	// L600
    bool v390 = v389 | v386;	// L601
    if (v390) {	// L602
      binop = 1;	// L603
    }
    int32_t grant;	// L605
    grant = 0;	// L606
    int32_t v392 = pc;	// L607
    bool v393 = v392 >= 0;	// L608
    if (v393) {	// L609
      grant = 1;	// L610
    }
    int32_t v394 = pc;	// L612
    bool v395 = v394 >= 0;	// L613
    int32_t v396 = a_vld;	// L614
    bool v397 = v396 == 0;	// L615
    int32_t v398 = binop;	// L616
    bool v399 = v398 == 1;	// L617
    int32_t v400 = b_vld;	// L618
    bool v401 = v400 == 0;	// L619
    bool v402 = v399 & v401;	// L620
    bool v403 = v397 | v402;	// L621
    bool v404 = v395 & v403;	// L622
    if (v404) {	// L623
      grant = 0;	// L624
    }
    int32_t v405 = grant;	// L626
    bool v406 = v405 == 1;	// L627
    if (v406) {	// L628
      int32_t v407 = instr_cnt;	// L629
      int32_t v408 = cfg_isz;	// L630
      bool v409 = v407 == v408;	// L631
      if (v409) {	// L632
        instr_cnt = 0;	// L633
        int32_t v410 = iter_cnt;	// L634
        int32_t v411 = cfg_itsz;	// L635
        ap_int<33> v412 = v411;	// L636
        ap_int<33> v413 = v412 - 1;	// L637
        ap_int<33> v414 = v410;	// L638
        bool v415 = v414 == v413;	// L639
        if (v415) {	// L640
          fetch_en = 0;	// L641
        } else {
          int32_t v416 = iter_cnt;	// L643
          ap_int<33> v417 = v416;	// L644
          ap_int<33> v418 = v417 + 1;	// L645
          int32_t v419 = v418;	// L646
          iter_cnt = v419;	// L647
        }
      } else {
        int32_t v420 = instr_cnt;	// L650
        ap_int<33> v421 = v420;	// L651
        ap_int<33> v422 = v421 + 1;	// L652
        int32_t v423 = v422;	// L653
        instr_cnt = v423;	// L654
      }
    }
    int32_t c1;	// L657
    c1 = -1;	// L658
    int32_t c2;	// L659
    c2 = -1;	// L660
    int32_t v426 = grant;	// L661
    bool v427 = v426 == 1;	// L662
    int32_t v428 = s1;	// L663
    bool v429 = v428 >= 12;	// L664
    bool v430 = v427 & v429;	// L665
    if (v430) {	// L666
      int32_t v431 = s1;	// L667
      int32_t v432 = v431 & 3;	// L668
      c1 = v432;	// L669
    }
    int32_t v433 = grant;	// L671
    bool v434 = v433 == 1;	// L672
    int32_t v435 = s2;	// L673
    bool v436 = v435 >= 12;	// L674
    bool v437 = v434 & v436;	// L675
    if (v437) {	// L676
      int32_t v438 = s2;	// L677
      int32_t v439 = v438 & 3;	// L678
      c2 = v439;	// L679
    }
    int32_t v440 = c1;	// L681
    bool v441 = v440 >= 0;	// L682
    if (v441) {	// L683
      int32_t v442 = c1;	// L684
      int v443 = v442;	// L685
      half v444 = hold_v[v443][1];	// L686
      hold_v[v443][0] = v444;	// L687
      int32_t v445 = c1;	// L688
      int v446 = v445;	// L689
      int32_t v447 = hold_cnt[v446];	// L690
      ap_int<33> v448 = v447;	// L691
      ap_int<33> v449 = v448 - 1;	// L692
      int32_t v450 = v449;	// L693
      hold_cnt[v446] = v450;	// L694
    }
    int32_t v451 = c2;	// L696
    bool v452 = v451 >= 0;	// L697
    int32_t v453 = c1;	// L698
    bool v454 = v451 != v453;	// L699
    bool v455 = v452 & v454;	// L700
    if (v455) {	// L701
      int32_t v456 = c2;	// L702
      int v457 = v456;	// L703
      half v458 = hold_v[v457][1];	// L704
      hold_v[v457][0] = v458;	// L705
      int32_t v459 = c2;	// L706
      int v460 = v459;	// L707
      int32_t v461 = hold_cnt[v460];	// L708
      ap_int<33> v462 = v461;	// L709
      ap_int<33> v463 = v462 - 1;	// L710
      int32_t v464 = v463;	// L711
      hold_cnt[v460] = v464;	// L712
    }
    int32_t v465 = grant;	// L714
    bool v466 = v465 == 1;	// L715
    int32_t v467 = s1;	// L716
    bool v468 = v467 < 8;	// L717
    int32_t v469 = dsmask;	// L718
    int32_t v470 = v469 >> v467;	// L719
    int32_t v471 = v470 & 1;	// L720
    bool v472 = v471 == 1;	// L721
    bool v473 = v466 & v468;	// L722
    bool v474 = v473 & v472;	// L723
    if (v474) {	// L724
      int32_t v475 = s1;	// L725
      int v476 = v475;	// L726
      drf_full[v476] = 0;	// L727
    }
    int32_t v477 = grant;	// L729
    bool v478 = v477 == 1;	// L730
    int32_t v479 = s2;	// L731
    bool v480 = v479 < 8;	// L732
    int32_t v481 = dsmask;	// L733
    int32_t v482 = v481 >> v479;	// L734
    int32_t v483 = v482 & 1;	// L735
    bool v484 = v483 == 1;	// L736
    bool v485 = v478 & v480;	// L737
    bool v486 = v485 & v484;	// L738
    if (v486) {	// L739
      int32_t v487 = s2;	// L740
      int v488 = v487;	// L741
      drf_full[v488] = 0;	// L742
    }
    half res;	// L744
    res = (double)0.000000;	// L745
    int32_t v490 = op;	// L746
    bool v491 = v490 == 0;	// L747
    if (v491) {	// L748
      half v492 = a;	// L749
      half v493 = b;	// L750
      half v494 = v492 + v493;	// L751
      res = v494;	// L752
    } else {
      int32_t v495 = op;	// L754
      bool v496 = v495 == 1;	// L755
      if (v496) {	// L756
        half v497 = a;	// L757
        half v498 = b;	// L758
        half v499 = v497 - v498;	// L759
        res = v499;	// L760
      } else {
        int32_t v500 = op;	// L762
        bool v501 = v500 == 2;	// L763
        if (v501) {	// L764
          half v502 = a;	// L765
          half v503 = b;	// L766
          half v504 = v502 * v503;	// L767
          res = v504;	// L768
        } else {
          int32_t v505 = op;	// L770
          bool v506 = v505 == 8;	// L771
          if (v506) {	// L772
            half v507 = a;	// L773
            half v508 = b;	// L774
            bool v509 = v507 >= v508;	// L775
            if (v509) {	// L776
              res = (double)1.000000;	// L777
            } else {
              res = (double)-1.000000;	// L779
            }
          } else {
            int32_t v510 = op;	// L782
            bool v511 = v510 == 9;	// L783
            if (v511) {	// L784
              half v512 = a;	// L785
              half v513 = b;	// L786
              bool v514 = v512 < v513;	// L787
              if (v514) {	// L788
                res = (double)1.000000;	// L789
              } else {
                res = (double)-1.000000;	// L791
              }
            } else {
              half v515 = a;	// L794
              res = v515;	// L795
            }
          }
        }
      }
    }
    int32_t v516 = a_vld;	// L801
    int32_t res_vld;	// L802
    res_vld = v516;	// L803
    int32_t v518 = op;	// L804
    bool v519 = v518 == 0;	// L805
    bool v520 = v518 == 1;	// L806
    bool v521 = v518 == 2;	// L807
    bool v522 = v518 == 8;	// L808
    bool v523 = v518 == 9;	// L809
    bool v524 = v519 | v520;	// L810
    bool v525 = v524 | v521;	// L811
    bool v526 = v525 | v522;	// L812
    bool v527 = v526 | v523;	// L813
    if (v527) {	// L814
      int32_t v528 = a_vld;	// L815
      int32_t v529 = b_vld;	// L816
      int64_t v530 = v528;	// L817
      int64_t v531 = v529;	// L818
      int64_t v532 = v530 * v531;	// L819
      int32_t v533 = v532;	// L820
      res_vld = v533;	// L821
    }
    int32_t v534 = grant;	// L823
    bool v535 = v534 == 0;	// L824
    if (v535) {	// L825
      res_vld = 0;	// L826
    }
    int32_t v536 = grant;	// L828
    bool v537 = v536 == 1;	// L829
    int32_t v538 = op;	// L830
    bool v539 = v538 == 8;	// L831
    bool v540 = v537 & v539;	// L832
    if (v540) {	// L833
      condition_reg = 0;	// L834
      half v541 = a;	// L835
      half v542 = b;	// L836
      bool v543 = v541 >= v542;	// L837
      if (v543) {	// L838
        condition_reg = 1;	// L839
      }
    }
    int32_t v544 = grant;	// L842
    bool v545 = v544 == 1;	// L843
    int32_t v546 = op;	// L844
    bool v547 = v546 == 9;	// L845
    bool v548 = v545 & v547;	// L846
    if (v548) {	// L847
      condition_reg = 0;	// L848
      half v549 = a;	// L849
      half v550 = b;	// L850
      bool v551 = v549 < v550;	// L851
      if (v551) {	// L852
        condition_reg = 1;	// L853
      }
    }
    ap_uint<17> tx_n;	// L856
    tx_n = 0;	// L857
    ap_uint<17> tx_s;	// L858
    tx_s = 0;	// L859
    ap_uint<17> tx_w;	// L860
    tx_w = 0;	// L861
    ap_uint<17> tx_e;	// L862
    tx_e = 0;	// L863
    int32_t is_rtr;	// L864
    is_rtr = 0;	// L865
    int32_t do_inj;	// L866
    do_inj = 0;	// L867
    int32_t v558 = op;	// L868
    bool v559 = v558 >= 4;	// L869
    ap_int<33> v560 = v558;	// L870
    bool v561 = v560 <= 7;	// L871
    bool v562 = v559 & v561;	// L872
    if (v562) {	// L873
      is_rtr = 1;	// L874
      do_inj = 1;	// L875
    }
    int32_t v563 = op;	// L877
    bool v564 = v563 >= 12;	// L878
    ap_int<33> v565 = v563;	// L879
    bool v566 = v565 <= 15;	// L880
    bool v567 = v564 & v566;	// L881
    if (v567) {	// L882
      is_rtr = 1;	// L883
      int32_t v568 = condition_reg;	// L884
      bool v569 = v568 == 1;	// L885
      if (v569) {	// L886
        do_inj = 1;	// L887
      }
    }
    int32_t v570 = is_rtr;	// L890
    bool v571 = v570 == 1;	// L891
    if (v571) {	// L892
      int32_t v572 = do_inj;	// L893
      bool v573 = v572 == 1;	// L894
      ap_int<26> v574 = csd_pkt;	// L895
      bool v575;
      ap_int<26> v575_tmp = v574;
      v575 = v575_tmp[25];	// L896
      int32_t v576 = v575;	// L897
      bool v577 = v576 == 0;	// L898
      bool v578 = v573 & v577;	// L899
      if (v578) {	// L900
        half v579 = res;	// L901
        uint16_t v580;
        union { half from; uint16_t to;} _converter_v579_to_v580;
        _converter_v579_to_v580.from = v579;
        v580 = _converter_v579_to_v580.to;	// L902
        ap_int<26> v581 = csd_pkt;	// L903
        ap_int<26> v582;
        ap_int<26> v582_tmp = v581;
        v582_tmp(15, 0) = v580;
        v582 = v582_tmp;	// L904
        csd_pkt = v582;	// L905
        int32_t v583 = dst;	// L906
        ap_uint<4> v584 = v583;	// L907
        ap_int<26> v585 = csd_pkt;	// L908
        ap_int<26> v586;
        ap_int<26> v586_tmp = v585;
        v586_tmp(19, 16) = v584;
        v586 = v586_tmp;	// L909
        csd_pkt = v586;	// L910
        int32_t v587 = s2;	// L911
        ap_uint<4> v588 = v587;	// L912
        ap_int<26> v589 = csd_pkt;	// L913
        ap_int<26> v590;
        ap_int<26> v590_tmp = v589;
        v590_tmp(24, 21) = v588;
        v590 = v590_tmp;	// L914
        csd_pkt = v590;	// L915
        int32_t v591 = res_vld;	// L916
        bool v592 = v591;	// L917
        ap_int<26> v593 = csd_pkt;	// L918
        ap_int<26> v594;
        ap_int<26> v594_tmp = v593;
        v594_tmp[25] = v592;        v594 = v594_tmp;	// L919
        csd_pkt = v594;	// L920
        int32_t v595 = op;	// L921
        int32_t v596 = v595 & 3;	// L922
        csd_dir = v596;	// L923
      }
    } else {
      int32_t v597 = dst;	// L926
      bool v598 = v597 >= 12;	// L927
      if (v598) {	// L928
        ap_uint<17> tw;	// L929
        tw = 0;	// L930
        int32_t v600 = res_vld;	// L931
        bool v601 = v600;	// L932
        ap_int<17> v602 = tw;	// L933
        ap_int<17> v603;
        ap_int<17> v603_tmp = v602;
        v603_tmp[0] = v601;        v603 = v603_tmp;	// L934
        tw = v603;	// L935
        half v604 = res;	// L936
        uint16_t v605;
        union { half from; uint16_t to;} _converter_v604_to_v605;
        _converter_v604_to_v605.from = v604;
        v605 = _converter_v604_to_v605.to;	// L937
        ap_int<17> v606 = tw;	// L938
        ap_int<17> v607;
        ap_int<17> v607_tmp = v606;
        v607_tmp(16, 1) = v605;
        v607 = v607_tmp;	// L939
        tw = v607;	// L940
        int32_t v608 = dst;	// L941
        int32_t v609 = v608 & 3;	// L942
        bool v610 = v609 == 0;	// L943
        if (v610) {	// L944
          ap_int<17> v611 = tw;	// L945
          tx_n = v611;	// L946
        } else {
          int32_t v612 = dst;	// L948
          int32_t v613 = v612 & 3;	// L949
          bool v614 = v613 == 1;	// L950
          if (v614) {	// L951
            ap_int<17> v615 = tw;	// L952
            tx_s = v615;	// L953
          } else {
            int32_t v616 = dst;	// L955
            int32_t v617 = v616 & 3;	// L956
            bool v618 = v617 == 2;	// L957
            if (v618) {	// L958
              ap_int<17> v619 = tw;	// L959
              tx_w = v619;	// L960
            } else {
              ap_int<17> v620 = tw;	// L962
              tx_e = v620;	// L963
            }
          }
        }
      } else {
        int32_t v621 = res_vld;	// L968
        bool v622 = v621 == 1;	// L969
        if (v622) {	// L970
          int32_t v623 = dst;	// L971
          bool v624 = v623 < 8;	// L972
          int32_t v625 = dsmask;	// L973
          int32_t v626 = v625 >> v623;	// L974
          int32_t v627 = v626 & 1;	// L975
          bool v628 = v627 == 1;	// L976
          bool v629 = v624 & v628;	// L977
          if (v629) {	// L978
            int32_t v630 = dst;	// L979
            int v631 = v630;	// L980
            int32_t v632 = drf_full[v631];	// L981
            bool v633 = v632 == 0;	// L982
            if (v633) {	// L983
              half v634 = res;	// L984
              int32_t v635 = dst;	// L985
              int v636 = v635;	// L986
              drf[v636] = v634;	// L987
              int32_t v637 = dst;	// L988
              int v638 = v637;	// L989
              drf_full[v638] = 1;	// L990
            }
          } else {
            half v639 = res;	// L993
            int32_t v640 = dst;	// L994
            int v641 = v640;	// L995
            drf[v641] = v639;	// L996
          }
        }
      }
    }
    ap_int<17> v642 = tx_n;	// L1001
    txn_r = v642;	// L1002
    ap_int<17> v643 = tx_s;	// L1003
    txs_r = v643;	// L1004
    ap_int<17> v644 = tx_w;	// L1005
    txw_r = v644;	// L1006
    ap_int<17> v645 = tx_e;	// L1007
    txe_r = v645;	// L1008
    int32_t v646 = crv_vld;	// L1009
    bool v647 = v646 == 1;	// L1010
    if (v647) {	// L1011
      int32_t v648 = crv_mode;	// L1012
      bool v649 = v648 == 1;	// L1013
      if (v649) {	// L1014
        int32_t v650 = crv_addr;	// L1015
        int32_t v651 = v650 >> 3;	// L1016
        int32_t v652 = v651 & 1;	// L1017
        bool v653 = v652 == 1;	// L1018
        if (v653) {	// L1019
          int32_t v654 = crv_raw;	// L1020
          int32_t v655 = crv_addr;	// L1021
          int32_t v656 = v655 & 7;	// L1022
          int v657 = v656;	// L1023
          irf[v657] = v654;	// L1024
        } else {
          int32_t v658 = crv_addr;	// L1026
          bool v659 = v658 == 0;	// L1027
          if (v659) {	// L1028
            int32_t v660 = crv_raw;	// L1029
            int32_t v661 = v660 & 255;	// L1030
            dsmask = v661;	// L1031
            int32_t v662 = crv_raw;	// L1032
            int32_t v663 = v662 >> 8;	// L1033
            int32_t v664 = v663 & 7;	// L1034
            cfg_isz = v664;	// L1035
            int32_t v665 = crv_raw;	// L1036
            int32_t v666 = v665 >> 15;	// L1037
            int32_t v667 = v666 & 1;	// L1038
            bool v668 = v667 == 1;	// L1039
            if (v668) {	// L1040
              fetch_en = 1;	// L1041
              instr_cnt = 0;	// L1042
              iter_cnt = 0;	// L1043
            }
          } else {
            int32_t v669 = crv_addr;	// L1046
            bool v670 = v669 == 1;	// L1047
            if (v670) {	// L1048
              int32_t v671 = crv_raw;	// L1049
              int32_t v672 = v671 & 255;	// L1050
              cfg_itsz = v672;	// L1051
            }
          }
        }
      } else {
        int32_t v673 = crv_addr;	// L1056
        bool v674 = v673 < 8;	// L1057
        int32_t v675 = dsmask;	// L1058
        int32_t v676 = v675 >> v673;	// L1059
        int32_t v677 = v676 & 1;	// L1060
        bool v678 = v677 == 1;	// L1061
        bool v679 = v674 & v678;	// L1062
        if (v679) {	// L1063
          int32_t v680 = crv_addr;	// L1064
          int v681 = v680;	// L1065
          int32_t v682 = drf_full[v681];	// L1066
          bool v683 = v682 == 0;	// L1067
          if (v683) {	// L1068
            half v684 = crv_data;	// L1069
            int32_t v685 = crv_addr;	// L1070
            int v686 = v685;	// L1071
            drf[v686] = v684;	// L1072
            int32_t v687 = crv_addr;	// L1073
            int v688 = v687;	// L1074
            drf_full[v688] = 1;	// L1075
          }
        } else {
          half v689 = crv_data;	// L1078
          int32_t v690 = crv_addr;	// L1079
          int v691 = v690;	// L1080
          drf[v691] = v689;	// L1081
        }
      }
    }
  }
}

void node_0_1(
  hls::stream< ap_uint<26> >& v692,
  hls::stream< ap_uint<26> >& v693,
  hls::stream< ap_uint<26> >& v694,
  hls::stream< ap_uint<26> >& v695,
  hls::stream< ap_uint<17> >& v696,
  hls::stream< ap_uint<17> >& v697,
  hls::stream< ap_uint<17> >& v698,
  hls::stream< ap_uint<17> >& v699,
  hls::stream< int32_t >& v700,
  hls::stream< int32_t >& v701,
  hls::stream< int32_t >& v702,
  hls::stream< int32_t >& v703,
  hls::stream< ap_uint<26> >& v704,
  hls::stream< ap_uint<26> >& v705,
  hls::stream< ap_uint<26> >& v706,
  hls::stream< ap_uint<26> >& v707,
  hls::stream< int32_t >& v708,
  hls::stream< int32_t >& v709,
  hls::stream< int32_t >& v710,
  hls::stream< int32_t >& v711,
  hls::stream< ap_uint<17> >& v712,
  hls::stream< ap_uint<17> >& v713,
  hls::stream< ap_uint<17> >& v714,
  hls::stream< ap_uint<17> >& v715
) {	// L1088
  int32_t irf1[8];	// L1119
  for (int v717 = 0; v717 < 8; v717++) {	// L1120
    irf1[v717] = 0;	// L1120
  }
  half drf1[8];	// L1121
  #pragma HLS array_partition variable=drf1 complete dim=1

  for (int v719 = 0; v719 < 8; v719++) {	// L1122
    drf1[v719] = (double)0.000000;	// L1122
  }
  int32_t drf_full1[8];	// L1123
  #pragma HLS array_partition variable=drf_full1 complete dim=1

  for (int v721 = 0; v721 < 8; v721++) {	// L1124
    drf_full1[v721] = 0;	// L1124
  }
  int32_t dsmask1;	// L1125
  dsmask1 = 0;	// L1126
  int32_t crv_vld1;	// L1127
  crv_vld1 = 0;	// L1128
  half crv_data1;	// L1129
  crv_data1 = (double)0.000000;	// L1130
  int32_t crv_addr1;	// L1131
  crv_addr1 = 0;	// L1132
  int32_t crv_mode1;	// L1133
  crv_mode1 = 0;	// L1134
  int32_t crv_raw1;	// L1135
  crv_raw1 = 0;	// L1136
  int32_t csd_vld1;	// L1137
  csd_vld1 = 0;	// L1138
  ap_uint<26> csd_pkt1;	// L1139
  csd_pkt1 = 0;	// L1140
  int32_t csd_dir1;	// L1141
  csd_dir1 = 0;	// L1142
  int32_t row_id1;	// L1143
  row_id1 = 0;	// L1144
  int32_t col_id1;	// L1145
  col_id1 = 1;	// L1146
  ap_uint<26> oe_r1;	// L1147
  oe_r1 = 0;	// L1148
  ap_uint<26> ow_r1;	// L1149
  ow_r1 = 0;	// L1150
  ap_uint<26> on_r1;	// L1151
  on_r1 = 0;	// L1152
  ap_uint<26> os_r1;	// L1153
  os_r1 = 0;	// L1154
  ap_uint<17> txn_r1;	// L1155
  txn_r1 = 0;	// L1156
  ap_uint<17> txs_r1;	// L1157
  txs_r1 = 0;	// L1158
  ap_uint<17> txw_r1;	// L1159
  txw_r1 = 0;	// L1160
  ap_uint<17> txe_r1;	// L1161
  txe_r1 = 0;	// L1162
  half hold_v1[4][2];	// L1163
  #pragma HLS array_partition variable=hold_v1 complete dim=1
  #pragma HLS array_partition variable=hold_v1 complete dim=2

  for (int v742 = 0; v742 < 4; v742++) {	// L1164
    for (int v743 = 0; v743 < 2; v743++) {	// L1164
      hold_v1[v742][v743] = (double)0.000000;	// L1164
    }
  }
  int32_t hold_cnt1[4];	// L1165
  #pragma HLS array_partition variable=hold_cnt1 complete dim=1

  for (int v745 = 0; v745 < 4; v745++) {	// L1166
    hold_cnt1[v745] = 0;	// L1166
  }
  ap_uint<26> rbuf1[4][2];	// L1167
  #pragma HLS array_partition variable=rbuf1 complete dim=1
  #pragma HLS array_partition variable=rbuf1 complete dim=2

  for (int v747 = 0; v747 < 4; v747++) {	// L1168
    for (int v748 = 0; v748 < 2; v748++) {	// L1168
      rbuf1[v747][v748] = 0;	// L1168
    }
  }
  int32_t rbcnt1[4];	// L1169
  #pragma HLS array_partition variable=rbcnt1 complete dim=1

  for (int v750 = 0; v750 < 4; v750++) {	// L1170
    rbcnt1[v750] = 0;	// L1170
  }
  int32_t rcred1[4];	// L1171
  #pragma HLS array_partition variable=rcred1 complete dim=1

  for (int v752 = 0; v752 < 4; v752++) {	// L1172
    rcred1[v752] = 0;	// L1172
  }
  int32_t cre_r1;	// L1173
  cre_r1 = 2;	// L1174
  int32_t crw_r1;	// L1175
  crw_r1 = 2;	// L1176
  int32_t crs_r1;	// L1177
  crs_r1 = 2;	// L1178
  int32_t crn_r1;	// L1179
  crn_r1 = 2;	// L1180
  int32_t cfg_isz1;	// L1181
  cfg_isz1 = 0;	// L1182
  int32_t cfg_itsz1;	// L1183
  cfg_itsz1 = 0;	// L1184
  int32_t fetch_en1;	// L1185
  fetch_en1 = 0;	// L1186
  int32_t instr_cnt1;	// L1187
  instr_cnt1 = 0;	// L1188
  int32_t iter_cnt1;	// L1189
  iter_cnt1 = 0;	// L1190
  int32_t condition_reg1;	// L1191
  condition_reg1 = 0;	// L1192
  l_S_t_0_t1: for (int t1 = 0; t1 < 8; t1++) {	// L1193
  #pragma HLS pipeline II=1
    ap_int<26> v764 = oe_r1;	// L1194
    v692.write(v764);	// L1195
    ap_int<26> v765 = ow_r1;	// L1196
    v693.write(v765);	// L1197
    ap_int<26> v766 = os_r1;	// L1198
    v694.write(v766);	// L1199
    ap_int<26> v767 = on_r1;	// L1200
    v695.write(v767);	// L1201
    ap_int<17> v768 = txe_r1;	// L1202
    v696.write(v768);	// L1203
    ap_int<17> v769 = txw_r1;	// L1204
    v697.write(v769);	// L1205
    ap_int<17> v770 = txs_r1;	// L1206
    v698.write(v770);	// L1207
    ap_int<17> v771 = txn_r1;	// L1208
    v699.write(v771);	// L1209
    int32_t v772 = cre_r1;	// L1210
    v700.write(v772);	// L1211
    int32_t v773 = crw_r1;	// L1212
    v701.write(v773);	// L1213
    int32_t v774 = crs_r1;	// L1214
    v702.write(v774);	// L1215
    int32_t v775 = crn_r1;	// L1216
    v703.write(v775);	// L1217
    ap_uint<26> v776 = v704.read();	// L1218
    ap_uint<26> p_w1;	// L1219
    p_w1 = v776;	// L1220
    ap_uint<26> v778 = v705.read();	// L1221
    ap_uint<26> p_e1;	// L1222
    p_e1 = v778;	// L1223
    ap_uint<26> v780 = v706.read();	// L1224
    ap_uint<26> p_n1;	// L1225
    p_n1 = v780;	// L1226
    ap_uint<26> v782 = v707.read();	// L1227
    ap_uint<26> p_s1;	// L1228
    p_s1 = v782;	// L1229
    int32_t v784 = v708.read();	// L1230
    int32_t v785 = rcred1[0];	// L1231
    ap_int<33> v786 = v785;	// L1232
    ap_int<33> v787 = v784;	// L1233
    ap_int<33> v788 = v786 + v787;	// L1234
    int32_t v789 = v788;	// L1235
    rcred1[0] = v789;	// L1236
    int32_t v790 = v709.read();	// L1237
    int32_t v791 = rcred1[1];	// L1238
    ap_int<33> v792 = v791;	// L1239
    ap_int<33> v793 = v790;	// L1240
    ap_int<33> v794 = v792 + v793;	// L1241
    int32_t v795 = v794;	// L1242
    rcred1[1] = v795;	// L1243
    int32_t v796 = v710.read();	// L1244
    int32_t v797 = rcred1[2];	// L1245
    ap_int<33> v798 = v797;	// L1246
    ap_int<33> v799 = v796;	// L1247
    ap_int<33> v800 = v798 + v799;	// L1248
    int32_t v801 = v800;	// L1249
    rcred1[2] = v801;	// L1250
    int32_t v802 = v711.read();	// L1251
    int32_t v803 = rcred1[3];	// L1252
    ap_int<33> v804 = v803;	// L1253
    ap_int<33> v805 = v802;	// L1254
    ap_int<33> v806 = v804 + v805;	// L1255
    int32_t v807 = v806;	// L1256
    rcred1[3] = v807;	// L1257
    ap_uint<26> fin1[4];	// L1258
    for (int v809 = 0; v809 < 4; v809++) {	// L1259
      fin1[v809] = 0;	// L1259
    }
    ap_int<26> v810 = p_w1;	// L1260
    fin1[0] = v810;	// L1261
    ap_int<26> v811 = p_e1;	// L1262
    fin1[1] = v811;	// L1263
    ap_int<26> v812 = p_n1;	// L1264
    fin1[2] = v812;	// L1265
    ap_int<26> v813 = p_s1;	// L1266
    fin1[3] = v813;	// L1267
    l_S_d_0_d4: for (int d4 = 0; d4 < 4; d4++) {	// L1268
      ap_uint<26> v815 = fin1[d4];	// L1269
      bool v816;
      ap_int<26> v816_tmp = v815;
      v816 = v816_tmp[25];	// L1270
      int32_t v817 = v816;	// L1271
      bool v818 = v817 == 1;	// L1272
      int32_t v819 = rbcnt1[d4];	// L1273
      bool v820 = v819 < 2;	// L1274
      bool v821 = v818 & v820;	// L1275
      if (v821) {	// L1276
        ap_uint<26> v822 = fin1[d4];	// L1277
        int32_t v823 = rbcnt1[d4];	// L1278
        int v824 = v823;	// L1279
        rbuf1[d4][v824] = v822;	// L1280
        int32_t v825 = rbcnt1[d4];	// L1281
        ap_int<33> v826 = v825;	// L1282
        ap_int<33> v827 = v826 + 1;	// L1283
        int32_t v828 = v827;	// L1284
        rbcnt1[d4] = v828;	// L1285
      }
    }
    ap_uint<26> hd1[4];	// L1288
    for (int v830 = 0; v830 < 4; v830++) {	// L1289
      hd1[v830] = 0;	// L1289
    }
    int32_t hvld1[4];	// L1290
    for (int v832 = 0; v832 < 4; v832++) {	// L1291
      hvld1[v832] = 0;	// L1291
    }
    int32_t hit1[4];	// L1292
    for (int v834 = 0; v834 < 4; v834++) {	// L1293
      hit1[v834] = 0;	// L1293
    }
    int32_t axis1[4];	// L1294
    for (int v836 = 0; v836 < 4; v836++) {	// L1295
      axis1[v836] = 0;	// L1295
    }
    int32_t v837 = col_id1;	// L1296
    axis1[0] = v837;	// L1297
    int32_t v838 = col_id1;	// L1298
    axis1[1] = v838;	// L1299
    int32_t v839 = row_id1;	// L1300
    axis1[2] = v839;	// L1301
    int32_t v840 = row_id1;	// L1302
    axis1[3] = v840;	// L1303
    l_S_d_1_d5: for (int d5 = 0; d5 < 4; d5++) {	// L1304
      int32_t v842 = rbcnt1[d5];	// L1305
      bool v843 = v842 > 0;	// L1306
      if (v843) {	// L1307
        ap_uint<26> v844 = rbuf1[d5][0];	// L1308
        hd1[d5] = v844;	// L1309
        hvld1[d5] = 1;	// L1310
        ap_uint<26> v845 = hd1[d5];	// L1311
        ap_int<4> v846;
        ap_int<26> v846_tmp = v845;
        v846 = v846_tmp(24, 21);	// L1312
        int32_t v847 = axis1[d5];	// L1313
        int32_t v848 = v846;	// L1314
        bool v849 = v848 == v847;	// L1315
        if (v849) {	// L1316
          hit1[d5] = 1;	// L1317
        }
      }
    }
    ap_uint<26> o_crv1;	// L1321
    o_crv1 = 0;	// L1322
    int32_t crv_in1;	// L1323
    crv_in1 = -1;	// L1324
    int32_t v852 = hit1[3];	// L1325
    bool v853 = v852 == 1;	// L1326
    if (v853) {	// L1327
      ap_uint<26> v854 = hd1[3];	// L1328
      o_crv1 = v854;	// L1329
      crv_in1 = 3;	// L1330
    } else {
      int32_t v855 = hit1[2];	// L1332
      bool v856 = v855 == 1;	// L1333
      if (v856) {	// L1334
        ap_uint<26> v857 = hd1[2];	// L1335
        o_crv1 = v857;	// L1336
        crv_in1 = 2;	// L1337
      } else {
        int32_t v858 = hit1[1];	// L1339
        bool v859 = v858 == 1;	// L1340
        if (v859) {	// L1341
          ap_uint<26> v860 = hd1[1];	// L1342
          o_crv1 = v860;	// L1343
          crv_in1 = 1;	// L1344
        } else {
          int32_t v861 = hit1[0];	// L1346
          bool v862 = v861 == 1;	// L1347
          if (v862) {	// L1348
            ap_uint<26> v863 = hd1[0];	// L1349
            o_crv1 = v863;	// L1350
            crv_in1 = 0;	// L1351
          }
        }
      }
    }
    ap_uint<26> o_out1[4];	// L1356
    for (int v865 = 0; v865 < 4; v865++) {	// L1357
      o_out1[v865] = 0;	// L1357
    }
    int32_t pop1[4];	// L1358
    for (int v867 = 0; v867 < 4; v867++) {	// L1359
      pop1[v867] = 0;	// L1359
    }
    int32_t inj_done1;	// L1360
    inj_done1 = 0;	// L1361
    int32_t idir1;	// L1362
    idir1 = -1;	// L1363
    ap_int<26> v870 = csd_pkt1;	// L1364
    bool v871;
    ap_int<26> v871_tmp = v870;
    v871 = v871_tmp[25];	// L1365
    int32_t v872 = v871;	// L1366
    bool v873 = v872 == 1;	// L1367
    if (v873) {	// L1368
      int32_t v874 = csd_dir1;	// L1369
      ap_int<33> v875 = v874;	// L1370
      ap_int<33> v876 = 3 - v875;	// L1371
      int32_t v877 = v876;	// L1372
      idir1 = v877;	// L1373
    }
    l_S_o_2_o1: for (int o1 = 0; o1 < 4; o1++) {	// L1375
      int32_t v879 = rcred1[o1];	// L1376
      bool v880 = v879 > 0;	// L1377
      if (v880) {	// L1378
        int32_t v881 = idir1;	// L1379
        ap_int<33> v882 = v881;	// L1380
        ap_int<33> v883 = o1;	// L1381
        bool v884 = v882 == v883;	// L1382
        if (v884) {	// L1383
          ap_int<26> v885 = csd_pkt1;	// L1384
          o_out1[o1] = v885;	// L1385
          int32_t v886 = rcred1[o1];	// L1386
          ap_int<33> v887 = v886;	// L1387
          ap_int<33> v888 = v887 - 1;	// L1388
          int32_t v889 = v888;	// L1389
          rcred1[o1] = v889;	// L1390
          inj_done1 = 1;	// L1391
        } else {
          int32_t v890 = hvld1[o1];	// L1393
          bool v891 = v890 == 1;	// L1394
          int32_t v892 = hit1[o1];	// L1395
          bool v893 = v892 == 0;	// L1396
          bool v894 = v891 & v893;	// L1397
          if (v894) {	// L1398
            ap_uint<26> v895 = hd1[o1];	// L1399
            o_out1[o1] = v895;	// L1400
            int32_t v896 = rcred1[o1];	// L1401
            ap_int<33> v897 = v896;	// L1402
            ap_int<33> v898 = v897 - 1;	// L1403
            int32_t v899 = v898;	// L1404
            rcred1[o1] = v899;	// L1405
            pop1[o1] = 1;	// L1406
          }
        }
      }
    }
    int32_t v900 = crv_in1;	// L1411
    bool v901 = v900 >= 0;	// L1412
    if (v901) {	// L1413
      int32_t v902 = crv_in1;	// L1414
      int v903 = v902;	// L1415
      pop1[v903] = 1;	// L1416
    }
    int32_t ret1[4];	// L1418
    for (int v905 = 0; v905 < 4; v905++) {	// L1419
      ret1[v905] = 0;	// L1419
    }
    l_S_d_3_d6: for (int d6 = 0; d6 < 4; d6++) {	// L1420
      int32_t v907 = pop1[d6];	// L1421
      bool v908 = v907 == 1;	// L1422
      if (v908) {	// L1423
        l_S_sft_3_sft1: for (int sft1 = 0; sft1 < 1; sft1++) {	// L1424
          ap_uint<26> v910 = rbuf1[d6][(sft1 + 1)];	// L1425
          rbuf1[d6][sft1] = v910;	// L1426
        }
        int32_t v911 = rbcnt1[d6];	// L1428
        ap_int<33> v912 = v911;	// L1429
        ap_int<33> v913 = v912 - 1;	// L1430
        int32_t v914 = v913;	// L1431
        rbcnt1[d6] = v914;	// L1432
        ret1[d6] = 1;	// L1433
      }
    }
    int32_t v915 = ret1[0];	// L1436
    cre_r1 = v915;	// L1437
    int32_t v916 = ret1[1];	// L1438
    crw_r1 = v916;	// L1439
    int32_t v917 = ret1[2];	// L1440
    crs_r1 = v917;	// L1441
    int32_t v918 = ret1[3];	// L1442
    crn_r1 = v918;	// L1443
    ap_uint<26> v919 = o_out1[0];	// L1444
    oe_r1 = v919;	// L1445
    ap_uint<26> v920 = o_out1[1];	// L1446
    ow_r1 = v920;	// L1447
    ap_uint<26> v921 = o_out1[2];	// L1448
    os_r1 = v921;	// L1449
    ap_uint<26> v922 = o_out1[3];	// L1450
    on_r1 = v922;	// L1451
    int32_t v923 = inj_done1;	// L1452
    bool v924 = v923 == 1;	// L1453
    if (v924) {	// L1454
      csd_pkt1 = 0;	// L1455
    }
    ap_int<26> v925 = o_crv1;	// L1457
    bool v926;
    ap_int<26> v926_tmp = v925;
    v926 = v926_tmp[25];	// L1458
    int32_t v927 = v926;	// L1459
    crv_vld1 = v927;	// L1460
    ap_int<26> v928 = o_crv1;	// L1461
    int16_t v929;
    ap_int<26> v929_tmp = v928;
    v929 = v929_tmp(15, 0);	// L1462
    half v930;
    union { uint16_t from; half to;} _converter_v929_to_v930;
    _converter_v929_to_v930.from = v929;
    v930 = _converter_v929_to_v930.to;	// L1463
    crv_data1 = v930;	// L1464
    ap_int<26> v931 = o_crv1;	// L1465
    ap_int<4> v932;
    ap_int<26> v932_tmp = v931;
    v932 = v932_tmp(19, 16);	// L1466
    int32_t v933 = v932;	// L1467
    crv_addr1 = v933;	// L1468
    ap_int<26> v934 = o_crv1;	// L1469
    bool v935;
    ap_int<26> v935_tmp = v934;
    v935 = v935_tmp[20];	// L1470
    int32_t v936 = v935;	// L1471
    crv_mode1 = v936;	// L1472
    ap_int<26> v937 = o_crv1;	// L1473
    int16_t v938;
    ap_int<26> v938_tmp = v937;
    v938 = v938_tmp(15, 0);	// L1474
    int32_t v939 = v938;	// L1475
    crv_raw1 = v939;	// L1476
    ap_uint<17> v940 = v712.read();	// L1477
    ap_uint<17> rx_w1;	// L1478
    rx_w1 = v940;	// L1479
    ap_uint<17> v942 = v713.read();	// L1480
    ap_uint<17> rx_e1;	// L1481
    rx_e1 = v942;	// L1482
    ap_uint<17> v944 = v714.read();	// L1483
    ap_uint<17> rx_n1;	// L1484
    rx_n1 = v944;	// L1485
    ap_uint<17> v946 = v715.read();	// L1486
    ap_uint<17> rx_s1;	// L1487
    rx_s1 = v946;	// L1488
    half rxv1[4];	// L1489
    for (int v949 = 0; v949 < 4; v949++) {	// L1490
      rxv1[v949] = (double)0.000000;	// L1490
    }
    int32_t rxvld1[4];	// L1491
    for (int v951 = 0; v951 < 4; v951++) {	// L1492
      rxvld1[v951] = 0;	// L1492
    }
    ap_int<17> v952 = rx_n1;	// L1493
    int16_t v953;
    ap_int<17> v953_tmp = v952;
    v953 = v953_tmp(16, 1);	// L1494
    half v954;
    union { uint16_t from; half to;} _converter_v953_to_v954;
    _converter_v953_to_v954.from = v953;
    v954 = _converter_v953_to_v954.to;	// L1495
    rxv1[0] = v954;	// L1496
    ap_int<17> v955 = rx_n1;	// L1497
    bool v956;
    ap_int<17> v956_tmp = v955;
    v956 = v956_tmp[0];	// L1498
    int32_t v957 = v956;	// L1499
    rxvld1[0] = v957;	// L1500
    ap_int<17> v958 = rx_s1;	// L1501
    int16_t v959;
    ap_int<17> v959_tmp = v958;
    v959 = v959_tmp(16, 1);	// L1502
    half v960;
    union { uint16_t from; half to;} _converter_v959_to_v960;
    _converter_v959_to_v960.from = v959;
    v960 = _converter_v959_to_v960.to;	// L1503
    rxv1[1] = v960;	// L1504
    ap_int<17> v961 = rx_s1;	// L1505
    bool v962;
    ap_int<17> v962_tmp = v961;
    v962 = v962_tmp[0];	// L1506
    int32_t v963 = v962;	// L1507
    rxvld1[1] = v963;	// L1508
    ap_int<17> v964 = rx_w1;	// L1509
    int16_t v965;
    ap_int<17> v965_tmp = v964;
    v965 = v965_tmp(16, 1);	// L1510
    half v966;
    union { uint16_t from; half to;} _converter_v965_to_v966;
    _converter_v965_to_v966.from = v965;
    v966 = _converter_v965_to_v966.to;	// L1511
    rxv1[2] = v966;	// L1512
    ap_int<17> v967 = rx_w1;	// L1513
    bool v968;
    ap_int<17> v968_tmp = v967;
    v968 = v968_tmp[0];	// L1514
    int32_t v969 = v968;	// L1515
    rxvld1[2] = v969;	// L1516
    ap_int<17> v970 = rx_e1;	// L1517
    int16_t v971;
    ap_int<17> v971_tmp = v970;
    v971 = v971_tmp(16, 1);	// L1518
    half v972;
    union { uint16_t from; half to;} _converter_v971_to_v972;
    _converter_v971_to_v972.from = v971;
    v972 = _converter_v971_to_v972.to;	// L1519
    rxv1[3] = v972;	// L1520
    ap_int<17> v973 = rx_e1;	// L1521
    bool v974;
    ap_int<17> v974_tmp = v973;
    v974 = v974_tmp[0];	// L1522
    int32_t v975 = v974;	// L1523
    rxvld1[3] = v975;	// L1524
    l_S_d_5_d7: for (int d7 = 0; d7 < 4; d7++) {	// L1525
      int32_t v977 = rxvld1[d7];	// L1526
      bool v978 = v977 == 1;	// L1527
      int32_t v979 = hold_cnt1[d7];	// L1528
      bool v980 = v979 < 2;	// L1529
      bool v981 = v978 & v980;	// L1530
      if (v981) {	// L1531
        half v982 = rxv1[d7];	// L1532
        int32_t v983 = hold_cnt1[d7];	// L1533
        int v984 = v983;	// L1534
        hold_v1[d7][v984] = v982;	// L1535
        int32_t v985 = hold_cnt1[d7];	// L1536
        ap_int<33> v986 = v985;	// L1537
        ap_int<33> v987 = v986 + 1;	// L1538
        int32_t v988 = v987;	// L1539
        hold_cnt1[d7] = v988;	// L1540
      }
    }
    int32_t pc1;	// L1543
    pc1 = -1;	// L1544
    int32_t v990 = fetch_en1;	// L1545
    bool v991 = v990 == 1;	// L1546
    if (v991) {	// L1547
      int32_t v992 = instr_cnt1;	// L1548
      pc1 = v992;	// L1549
    }
    int32_t instr1;	// L1551
    instr1 = 0;	// L1552
    int32_t v994 = pc1;	// L1553
    bool v995 = v994 >= 0;	// L1554
    if (v995) {	// L1555
      int32_t v996 = pc1;	// L1556
      int v997 = v996;	// L1557
      int32_t v998 = irf1[v997];	// L1558
      instr1 = v998;	// L1559
    }
    int32_t v999 = instr1;	// L1561
    int32_t v1000 = v999 & 15;	// L1562
    int32_t op1;	// L1563
    op1 = v1000;	// L1564
    int32_t v1002 = instr1;	// L1565
    int32_t v1003 = v1002 >> 4;	// L1566
    int32_t v1004 = v1003 & 15;	// L1567
    int32_t dst1;	// L1568
    dst1 = v1004;	// L1569
    int32_t v1006 = instr1;	// L1570
    int32_t v1007 = v1006 >> 8;	// L1571
    int32_t v1008 = v1007 & 15;	// L1572
    int32_t s11;	// L1573
    s11 = v1008;	// L1574
    int32_t v1010 = instr1;	// L1575
    int32_t v1011 = v1010 >> 12;	// L1576
    int32_t v1012 = v1011 & 15;	// L1577
    int32_t s21;	// L1578
    s21 = v1012;	// L1579
    half a1;	// L1580
    a1 = (double)0.000000;	// L1581
    half b1;	// L1582
    b1 = (double)0.000000;	// L1583
    int32_t v1016 = s11;	// L1584
    bool v1017 = v1016 >= 12;	// L1585
    if (v1017) {	// L1586
      int32_t v1018 = s11;	// L1587
      int32_t v1019 = v1018 & 3;	// L1588
      int v1020 = v1019;	// L1589
      half v1021 = hold_v1[v1020][0];	// L1590
      a1 = v1021;	// L1591
    } else {
      int32_t v1022 = s11;	// L1593
      int v1023 = v1022;	// L1594
      half v1024 = drf1[v1023];	// L1595
      a1 = v1024;	// L1596
    }
    int32_t v1025 = s21;	// L1598
    bool v1026 = v1025 >= 12;	// L1599
    if (v1026) {	// L1600
      int32_t v1027 = s21;	// L1601
      int32_t v1028 = v1027 & 3;	// L1602
      int v1029 = v1028;	// L1603
      half v1030 = hold_v1[v1029][0];	// L1604
      b1 = v1030;	// L1605
    } else {
      int32_t v1031 = s21;	// L1607
      int v1032 = v1031;	// L1608
      half v1033 = drf1[v1032];	// L1609
      b1 = v1033;	// L1610
    }
    int32_t a_vld1;	// L1612
    a_vld1 = 1;	// L1613
    int32_t b_vld1;	// L1614
    b_vld1 = 1;	// L1615
    int32_t v1036 = s11;	// L1616
    bool v1037 = v1036 >= 12;	// L1617
    if (v1037) {	// L1618
      a_vld1 = 0;	// L1619
      int32_t v1038 = s11;	// L1620
      int32_t v1039 = v1038 & 3;	// L1621
      int v1040 = v1039;	// L1622
      int32_t v1041 = hold_cnt1[v1040];	// L1623
      bool v1042 = v1041 > 0;	// L1624
      if (v1042) {	// L1625
        a_vld1 = 1;	// L1626
      }
    }
    int32_t v1043 = s21;	// L1629
    bool v1044 = v1043 >= 12;	// L1630
    if (v1044) {	// L1631
      b_vld1 = 0;	// L1632
      int32_t v1045 = s21;	// L1633
      int32_t v1046 = v1045 & 3;	// L1634
      int v1047 = v1046;	// L1635
      int32_t v1048 = hold_cnt1[v1047];	// L1636
      bool v1049 = v1048 > 0;	// L1637
      if (v1049) {	// L1638
        b_vld1 = 1;	// L1639
      }
    }
    int32_t v1050 = s11;	// L1642
    bool v1051 = v1050 < 8;	// L1643
    int32_t v1052 = dsmask1;	// L1644
    int32_t v1053 = v1052 >> v1050;	// L1645
    int32_t v1054 = v1053 & 1;	// L1646
    bool v1055 = v1054 == 1;	// L1647
    bool v1056 = v1051 & v1055;	// L1648
    if (v1056) {	// L1649
      int32_t v1057 = s11;	// L1650
      int v1058 = v1057;	// L1651
      int32_t v1059 = drf_full1[v1058];	// L1652
      bool v1060 = v1059 == 0;	// L1653
      if (v1060) {	// L1654
        a_vld1 = 0;	// L1655
      }
    }
    int32_t v1061 = s21;	// L1658
    bool v1062 = v1061 < 8;	// L1659
    int32_t v1063 = dsmask1;	// L1660
    int32_t v1064 = v1063 >> v1061;	// L1661
    int32_t v1065 = v1064 & 1;	// L1662
    bool v1066 = v1065 == 1;	// L1663
    bool v1067 = v1062 & v1066;	// L1664
    if (v1067) {	// L1665
      int32_t v1068 = s21;	// L1666
      int v1069 = v1068;	// L1667
      int32_t v1070 = drf_full1[v1069];	// L1668
      bool v1071 = v1070 == 0;	// L1669
      if (v1071) {	// L1670
        b_vld1 = 0;	// L1671
      }
    }
    int32_t binop1;	// L1674
    binop1 = 0;	// L1675
    int32_t v1073 = op1;	// L1676
    bool v1074 = v1073 == 0;	// L1677
    bool v1075 = v1073 == 1;	// L1678
    bool v1076 = v1073 == 2;	// L1679
    bool v1077 = v1073 == 8;	// L1680
    bool v1078 = v1073 == 9;	// L1681
    bool v1079 = v1074 | v1075;	// L1682
    bool v1080 = v1079 | v1076;	// L1683
    bool v1081 = v1080 | v1077;	// L1684
    bool v1082 = v1081 | v1078;	// L1685
    if (v1082) {	// L1686
      binop1 = 1;	// L1687
    }
    int32_t grant1;	// L1689
    grant1 = 0;	// L1690
    int32_t v1084 = pc1;	// L1691
    bool v1085 = v1084 >= 0;	// L1692
    if (v1085) {	// L1693
      grant1 = 1;	// L1694
    }
    int32_t v1086 = pc1;	// L1696
    bool v1087 = v1086 >= 0;	// L1697
    int32_t v1088 = a_vld1;	// L1698
    bool v1089 = v1088 == 0;	// L1699
    int32_t v1090 = binop1;	// L1700
    bool v1091 = v1090 == 1;	// L1701
    int32_t v1092 = b_vld1;	// L1702
    bool v1093 = v1092 == 0;	// L1703
    bool v1094 = v1091 & v1093;	// L1704
    bool v1095 = v1089 | v1094;	// L1705
    bool v1096 = v1087 & v1095;	// L1706
    if (v1096) {	// L1707
      grant1 = 0;	// L1708
    }
    int32_t v1097 = grant1;	// L1710
    bool v1098 = v1097 == 1;	// L1711
    if (v1098) {	// L1712
      int32_t v1099 = instr_cnt1;	// L1713
      int32_t v1100 = cfg_isz1;	// L1714
      bool v1101 = v1099 == v1100;	// L1715
      if (v1101) {	// L1716
        instr_cnt1 = 0;	// L1717
        int32_t v1102 = iter_cnt1;	// L1718
        int32_t v1103 = cfg_itsz1;	// L1719
        ap_int<33> v1104 = v1103;	// L1720
        ap_int<33> v1105 = v1104 - 1;	// L1721
        ap_int<33> v1106 = v1102;	// L1722
        bool v1107 = v1106 == v1105;	// L1723
        if (v1107) {	// L1724
          fetch_en1 = 0;	// L1725
        } else {
          int32_t v1108 = iter_cnt1;	// L1727
          ap_int<33> v1109 = v1108;	// L1728
          ap_int<33> v1110 = v1109 + 1;	// L1729
          int32_t v1111 = v1110;	// L1730
          iter_cnt1 = v1111;	// L1731
        }
      } else {
        int32_t v1112 = instr_cnt1;	// L1734
        ap_int<33> v1113 = v1112;	// L1735
        ap_int<33> v1114 = v1113 + 1;	// L1736
        int32_t v1115 = v1114;	// L1737
        instr_cnt1 = v1115;	// L1738
      }
    }
    int32_t c11;	// L1741
    c11 = -1;	// L1742
    int32_t c21;	// L1743
    c21 = -1;	// L1744
    int32_t v1118 = grant1;	// L1745
    bool v1119 = v1118 == 1;	// L1746
    int32_t v1120 = s11;	// L1747
    bool v1121 = v1120 >= 12;	// L1748
    bool v1122 = v1119 & v1121;	// L1749
    if (v1122) {	// L1750
      int32_t v1123 = s11;	// L1751
      int32_t v1124 = v1123 & 3;	// L1752
      c11 = v1124;	// L1753
    }
    int32_t v1125 = grant1;	// L1755
    bool v1126 = v1125 == 1;	// L1756
    int32_t v1127 = s21;	// L1757
    bool v1128 = v1127 >= 12;	// L1758
    bool v1129 = v1126 & v1128;	// L1759
    if (v1129) {	// L1760
      int32_t v1130 = s21;	// L1761
      int32_t v1131 = v1130 & 3;	// L1762
      c21 = v1131;	// L1763
    }
    int32_t v1132 = c11;	// L1765
    bool v1133 = v1132 >= 0;	// L1766
    if (v1133) {	// L1767
      int32_t v1134 = c11;	// L1768
      int v1135 = v1134;	// L1769
      half v1136 = hold_v1[v1135][1];	// L1770
      hold_v1[v1135][0] = v1136;	// L1771
      int32_t v1137 = c11;	// L1772
      int v1138 = v1137;	// L1773
      int32_t v1139 = hold_cnt1[v1138];	// L1774
      ap_int<33> v1140 = v1139;	// L1775
      ap_int<33> v1141 = v1140 - 1;	// L1776
      int32_t v1142 = v1141;	// L1777
      hold_cnt1[v1138] = v1142;	// L1778
    }
    int32_t v1143 = c21;	// L1780
    bool v1144 = v1143 >= 0;	// L1781
    int32_t v1145 = c11;	// L1782
    bool v1146 = v1143 != v1145;	// L1783
    bool v1147 = v1144 & v1146;	// L1784
    if (v1147) {	// L1785
      int32_t v1148 = c21;	// L1786
      int v1149 = v1148;	// L1787
      half v1150 = hold_v1[v1149][1];	// L1788
      hold_v1[v1149][0] = v1150;	// L1789
      int32_t v1151 = c21;	// L1790
      int v1152 = v1151;	// L1791
      int32_t v1153 = hold_cnt1[v1152];	// L1792
      ap_int<33> v1154 = v1153;	// L1793
      ap_int<33> v1155 = v1154 - 1;	// L1794
      int32_t v1156 = v1155;	// L1795
      hold_cnt1[v1152] = v1156;	// L1796
    }
    int32_t v1157 = grant1;	// L1798
    bool v1158 = v1157 == 1;	// L1799
    int32_t v1159 = s11;	// L1800
    bool v1160 = v1159 < 8;	// L1801
    int32_t v1161 = dsmask1;	// L1802
    int32_t v1162 = v1161 >> v1159;	// L1803
    int32_t v1163 = v1162 & 1;	// L1804
    bool v1164 = v1163 == 1;	// L1805
    bool v1165 = v1158 & v1160;	// L1806
    bool v1166 = v1165 & v1164;	// L1807
    if (v1166) {	// L1808
      int32_t v1167 = s11;	// L1809
      int v1168 = v1167;	// L1810
      drf_full1[v1168] = 0;	// L1811
    }
    int32_t v1169 = grant1;	// L1813
    bool v1170 = v1169 == 1;	// L1814
    int32_t v1171 = s21;	// L1815
    bool v1172 = v1171 < 8;	// L1816
    int32_t v1173 = dsmask1;	// L1817
    int32_t v1174 = v1173 >> v1171;	// L1818
    int32_t v1175 = v1174 & 1;	// L1819
    bool v1176 = v1175 == 1;	// L1820
    bool v1177 = v1170 & v1172;	// L1821
    bool v1178 = v1177 & v1176;	// L1822
    if (v1178) {	// L1823
      int32_t v1179 = s21;	// L1824
      int v1180 = v1179;	// L1825
      drf_full1[v1180] = 0;	// L1826
    }
    half res1;	// L1828
    res1 = (double)0.000000;	// L1829
    int32_t v1182 = op1;	// L1830
    bool v1183 = v1182 == 0;	// L1831
    if (v1183) {	// L1832
      half v1184 = a1;	// L1833
      half v1185 = b1;	// L1834
      half v1186 = v1184 + v1185;	// L1835
      res1 = v1186;	// L1836
    } else {
      int32_t v1187 = op1;	// L1838
      bool v1188 = v1187 == 1;	// L1839
      if (v1188) {	// L1840
        half v1189 = a1;	// L1841
        half v1190 = b1;	// L1842
        half v1191 = v1189 - v1190;	// L1843
        res1 = v1191;	// L1844
      } else {
        int32_t v1192 = op1;	// L1846
        bool v1193 = v1192 == 2;	// L1847
        if (v1193) {	// L1848
          half v1194 = a1;	// L1849
          half v1195 = b1;	// L1850
          half v1196 = v1194 * v1195;	// L1851
          res1 = v1196;	// L1852
        } else {
          int32_t v1197 = op1;	// L1854
          bool v1198 = v1197 == 8;	// L1855
          if (v1198) {	// L1856
            half v1199 = a1;	// L1857
            half v1200 = b1;	// L1858
            bool v1201 = v1199 >= v1200;	// L1859
            if (v1201) {	// L1860
              res1 = (double)1.000000;	// L1861
            } else {
              res1 = (double)-1.000000;	// L1863
            }
          } else {
            int32_t v1202 = op1;	// L1866
            bool v1203 = v1202 == 9;	// L1867
            if (v1203) {	// L1868
              half v1204 = a1;	// L1869
              half v1205 = b1;	// L1870
              bool v1206 = v1204 < v1205;	// L1871
              if (v1206) {	// L1872
                res1 = (double)1.000000;	// L1873
              } else {
                res1 = (double)-1.000000;	// L1875
              }
            } else {
              half v1207 = a1;	// L1878
              res1 = v1207;	// L1879
            }
          }
        }
      }
    }
    int32_t v1208 = a_vld1;	// L1885
    int32_t res_vld1;	// L1886
    res_vld1 = v1208;	// L1887
    int32_t v1210 = op1;	// L1888
    bool v1211 = v1210 == 0;	// L1889
    bool v1212 = v1210 == 1;	// L1890
    bool v1213 = v1210 == 2;	// L1891
    bool v1214 = v1210 == 8;	// L1892
    bool v1215 = v1210 == 9;	// L1893
    bool v1216 = v1211 | v1212;	// L1894
    bool v1217 = v1216 | v1213;	// L1895
    bool v1218 = v1217 | v1214;	// L1896
    bool v1219 = v1218 | v1215;	// L1897
    if (v1219) {	// L1898
      int32_t v1220 = a_vld1;	// L1899
      int32_t v1221 = b_vld1;	// L1900
      int64_t v1222 = v1220;	// L1901
      int64_t v1223 = v1221;	// L1902
      int64_t v1224 = v1222 * v1223;	// L1903
      int32_t v1225 = v1224;	// L1904
      res_vld1 = v1225;	// L1905
    }
    int32_t v1226 = grant1;	// L1907
    bool v1227 = v1226 == 0;	// L1908
    if (v1227) {	// L1909
      res_vld1 = 0;	// L1910
    }
    int32_t v1228 = grant1;	// L1912
    bool v1229 = v1228 == 1;	// L1913
    int32_t v1230 = op1;	// L1914
    bool v1231 = v1230 == 8;	// L1915
    bool v1232 = v1229 & v1231;	// L1916
    if (v1232) {	// L1917
      condition_reg1 = 0;	// L1918
      half v1233 = a1;	// L1919
      half v1234 = b1;	// L1920
      bool v1235 = v1233 >= v1234;	// L1921
      if (v1235) {	// L1922
        condition_reg1 = 1;	// L1923
      }
    }
    int32_t v1236 = grant1;	// L1926
    bool v1237 = v1236 == 1;	// L1927
    int32_t v1238 = op1;	// L1928
    bool v1239 = v1238 == 9;	// L1929
    bool v1240 = v1237 & v1239;	// L1930
    if (v1240) {	// L1931
      condition_reg1 = 0;	// L1932
      half v1241 = a1;	// L1933
      half v1242 = b1;	// L1934
      bool v1243 = v1241 < v1242;	// L1935
      if (v1243) {	// L1936
        condition_reg1 = 1;	// L1937
      }
    }
    ap_uint<17> tx_n1;	// L1940
    tx_n1 = 0;	// L1941
    ap_uint<17> tx_s1;	// L1942
    tx_s1 = 0;	// L1943
    ap_uint<17> tx_w1;	// L1944
    tx_w1 = 0;	// L1945
    ap_uint<17> tx_e1;	// L1946
    tx_e1 = 0;	// L1947
    int32_t is_rtr1;	// L1948
    is_rtr1 = 0;	// L1949
    int32_t do_inj1;	// L1950
    do_inj1 = 0;	// L1951
    int32_t v1250 = op1;	// L1952
    bool v1251 = v1250 >= 4;	// L1953
    ap_int<33> v1252 = v1250;	// L1954
    bool v1253 = v1252 <= 7;	// L1955
    bool v1254 = v1251 & v1253;	// L1956
    if (v1254) {	// L1957
      is_rtr1 = 1;	// L1958
      do_inj1 = 1;	// L1959
    }
    int32_t v1255 = op1;	// L1961
    bool v1256 = v1255 >= 12;	// L1962
    ap_int<33> v1257 = v1255;	// L1963
    bool v1258 = v1257 <= 15;	// L1964
    bool v1259 = v1256 & v1258;	// L1965
    if (v1259) {	// L1966
      is_rtr1 = 1;	// L1967
      int32_t v1260 = condition_reg1;	// L1968
      bool v1261 = v1260 == 1;	// L1969
      if (v1261) {	// L1970
        do_inj1 = 1;	// L1971
      }
    }
    int32_t v1262 = is_rtr1;	// L1974
    bool v1263 = v1262 == 1;	// L1975
    if (v1263) {	// L1976
      int32_t v1264 = do_inj1;	// L1977
      bool v1265 = v1264 == 1;	// L1978
      ap_int<26> v1266 = csd_pkt1;	// L1979
      bool v1267;
      ap_int<26> v1267_tmp = v1266;
      v1267 = v1267_tmp[25];	// L1980
      int32_t v1268 = v1267;	// L1981
      bool v1269 = v1268 == 0;	// L1982
      bool v1270 = v1265 & v1269;	// L1983
      if (v1270) {	// L1984
        half v1271 = res1;	// L1985
        uint16_t v1272;
        union { half from; uint16_t to;} _converter_v1271_to_v1272;
        _converter_v1271_to_v1272.from = v1271;
        v1272 = _converter_v1271_to_v1272.to;	// L1986
        ap_int<26> v1273 = csd_pkt1;	// L1987
        ap_int<26> v1274;
        ap_int<26> v1274_tmp = v1273;
        v1274_tmp(15, 0) = v1272;
        v1274 = v1274_tmp;	// L1988
        csd_pkt1 = v1274;	// L1989
        int32_t v1275 = dst1;	// L1990
        ap_uint<4> v1276 = v1275;	// L1991
        ap_int<26> v1277 = csd_pkt1;	// L1992
        ap_int<26> v1278;
        ap_int<26> v1278_tmp = v1277;
        v1278_tmp(19, 16) = v1276;
        v1278 = v1278_tmp;	// L1993
        csd_pkt1 = v1278;	// L1994
        int32_t v1279 = s21;	// L1995
        ap_uint<4> v1280 = v1279;	// L1996
        ap_int<26> v1281 = csd_pkt1;	// L1997
        ap_int<26> v1282;
        ap_int<26> v1282_tmp = v1281;
        v1282_tmp(24, 21) = v1280;
        v1282 = v1282_tmp;	// L1998
        csd_pkt1 = v1282;	// L1999
        int32_t v1283 = res_vld1;	// L2000
        bool v1284 = v1283;	// L2001
        ap_int<26> v1285 = csd_pkt1;	// L2002
        ap_int<26> v1286;
        ap_int<26> v1286_tmp = v1285;
        v1286_tmp[25] = v1284;        v1286 = v1286_tmp;	// L2003
        csd_pkt1 = v1286;	// L2004
        int32_t v1287 = op1;	// L2005
        int32_t v1288 = v1287 & 3;	// L2006
        csd_dir1 = v1288;	// L2007
      }
    } else {
      int32_t v1289 = dst1;	// L2010
      bool v1290 = v1289 >= 12;	// L2011
      if (v1290) {	// L2012
        ap_uint<17> tw1;	// L2013
        tw1 = 0;	// L2014
        int32_t v1292 = res_vld1;	// L2015
        bool v1293 = v1292;	// L2016
        ap_int<17> v1294 = tw1;	// L2017
        ap_int<17> v1295;
        ap_int<17> v1295_tmp = v1294;
        v1295_tmp[0] = v1293;        v1295 = v1295_tmp;	// L2018
        tw1 = v1295;	// L2019
        half v1296 = res1;	// L2020
        uint16_t v1297;
        union { half from; uint16_t to;} _converter_v1296_to_v1297;
        _converter_v1296_to_v1297.from = v1296;
        v1297 = _converter_v1296_to_v1297.to;	// L2021
        ap_int<17> v1298 = tw1;	// L2022
        ap_int<17> v1299;
        ap_int<17> v1299_tmp = v1298;
        v1299_tmp(16, 1) = v1297;
        v1299 = v1299_tmp;	// L2023
        tw1 = v1299;	// L2024
        int32_t v1300 = dst1;	// L2025
        int32_t v1301 = v1300 & 3;	// L2026
        bool v1302 = v1301 == 0;	// L2027
        if (v1302) {	// L2028
          ap_int<17> v1303 = tw1;	// L2029
          tx_n1 = v1303;	// L2030
        } else {
          int32_t v1304 = dst1;	// L2032
          int32_t v1305 = v1304 & 3;	// L2033
          bool v1306 = v1305 == 1;	// L2034
          if (v1306) {	// L2035
            ap_int<17> v1307 = tw1;	// L2036
            tx_s1 = v1307;	// L2037
          } else {
            int32_t v1308 = dst1;	// L2039
            int32_t v1309 = v1308 & 3;	// L2040
            bool v1310 = v1309 == 2;	// L2041
            if (v1310) {	// L2042
              ap_int<17> v1311 = tw1;	// L2043
              tx_w1 = v1311;	// L2044
            } else {
              ap_int<17> v1312 = tw1;	// L2046
              tx_e1 = v1312;	// L2047
            }
          }
        }
      } else {
        int32_t v1313 = res_vld1;	// L2052
        bool v1314 = v1313 == 1;	// L2053
        if (v1314) {	// L2054
          int32_t v1315 = dst1;	// L2055
          bool v1316 = v1315 < 8;	// L2056
          int32_t v1317 = dsmask1;	// L2057
          int32_t v1318 = v1317 >> v1315;	// L2058
          int32_t v1319 = v1318 & 1;	// L2059
          bool v1320 = v1319 == 1;	// L2060
          bool v1321 = v1316 & v1320;	// L2061
          if (v1321) {	// L2062
            int32_t v1322 = dst1;	// L2063
            int v1323 = v1322;	// L2064
            int32_t v1324 = drf_full1[v1323];	// L2065
            bool v1325 = v1324 == 0;	// L2066
            if (v1325) {	// L2067
              half v1326 = res1;	// L2068
              int32_t v1327 = dst1;	// L2069
              int v1328 = v1327;	// L2070
              drf1[v1328] = v1326;	// L2071
              int32_t v1329 = dst1;	// L2072
              int v1330 = v1329;	// L2073
              drf_full1[v1330] = 1;	// L2074
            }
          } else {
            half v1331 = res1;	// L2077
            int32_t v1332 = dst1;	// L2078
            int v1333 = v1332;	// L2079
            drf1[v1333] = v1331;	// L2080
          }
        }
      }
    }
    ap_int<17> v1334 = tx_n1;	// L2085
    txn_r1 = v1334;	// L2086
    ap_int<17> v1335 = tx_s1;	// L2087
    txs_r1 = v1335;	// L2088
    ap_int<17> v1336 = tx_w1;	// L2089
    txw_r1 = v1336;	// L2090
    ap_int<17> v1337 = tx_e1;	// L2091
    txe_r1 = v1337;	// L2092
    int32_t v1338 = crv_vld1;	// L2093
    bool v1339 = v1338 == 1;	// L2094
    if (v1339) {	// L2095
      int32_t v1340 = crv_mode1;	// L2096
      bool v1341 = v1340 == 1;	// L2097
      if (v1341) {	// L2098
        int32_t v1342 = crv_addr1;	// L2099
        int32_t v1343 = v1342 >> 3;	// L2100
        int32_t v1344 = v1343 & 1;	// L2101
        bool v1345 = v1344 == 1;	// L2102
        if (v1345) {	// L2103
          int32_t v1346 = crv_raw1;	// L2104
          int32_t v1347 = crv_addr1;	// L2105
          int32_t v1348 = v1347 & 7;	// L2106
          int v1349 = v1348;	// L2107
          irf1[v1349] = v1346;	// L2108
        } else {
          int32_t v1350 = crv_addr1;	// L2110
          bool v1351 = v1350 == 0;	// L2111
          if (v1351) {	// L2112
            int32_t v1352 = crv_raw1;	// L2113
            int32_t v1353 = v1352 & 255;	// L2114
            dsmask1 = v1353;	// L2115
            int32_t v1354 = crv_raw1;	// L2116
            int32_t v1355 = v1354 >> 8;	// L2117
            int32_t v1356 = v1355 & 7;	// L2118
            cfg_isz1 = v1356;	// L2119
            int32_t v1357 = crv_raw1;	// L2120
            int32_t v1358 = v1357 >> 15;	// L2121
            int32_t v1359 = v1358 & 1;	// L2122
            bool v1360 = v1359 == 1;	// L2123
            if (v1360) {	// L2124
              fetch_en1 = 1;	// L2125
              instr_cnt1 = 0;	// L2126
              iter_cnt1 = 0;	// L2127
            }
          } else {
            int32_t v1361 = crv_addr1;	// L2130
            bool v1362 = v1361 == 1;	// L2131
            if (v1362) {	// L2132
              int32_t v1363 = crv_raw1;	// L2133
              int32_t v1364 = v1363 & 255;	// L2134
              cfg_itsz1 = v1364;	// L2135
            }
          }
        }
      } else {
        int32_t v1365 = crv_addr1;	// L2140
        bool v1366 = v1365 < 8;	// L2141
        int32_t v1367 = dsmask1;	// L2142
        int32_t v1368 = v1367 >> v1365;	// L2143
        int32_t v1369 = v1368 & 1;	// L2144
        bool v1370 = v1369 == 1;	// L2145
        bool v1371 = v1366 & v1370;	// L2146
        if (v1371) {	// L2147
          int32_t v1372 = crv_addr1;	// L2148
          int v1373 = v1372;	// L2149
          int32_t v1374 = drf_full1[v1373];	// L2150
          bool v1375 = v1374 == 0;	// L2151
          if (v1375) {	// L2152
            half v1376 = crv_data1;	// L2153
            int32_t v1377 = crv_addr1;	// L2154
            int v1378 = v1377;	// L2155
            drf1[v1378] = v1376;	// L2156
            int32_t v1379 = crv_addr1;	// L2157
            int v1380 = v1379;	// L2158
            drf_full1[v1380] = 1;	// L2159
          }
        } else {
          half v1381 = crv_data1;	// L2162
          int32_t v1382 = crv_addr1;	// L2163
          int v1383 = v1382;	// L2164
          drf1[v1383] = v1381;	// L2165
        }
      }
    }
  }
}

void node_0_2(
  hls::stream< ap_uint<26> >& v1384,
  hls::stream< ap_uint<26> >& v1385,
  hls::stream< ap_uint<26> >& v1386,
  hls::stream< ap_uint<26> >& v1387,
  hls::stream< ap_uint<17> >& v1388,
  hls::stream< ap_uint<17> >& v1389,
  hls::stream< ap_uint<17> >& v1390,
  hls::stream< ap_uint<17> >& v1391,
  hls::stream< int32_t >& v1392,
  hls::stream< int32_t >& v1393,
  hls::stream< int32_t >& v1394,
  hls::stream< int32_t >& v1395,
  hls::stream< ap_uint<26> >& v1396,
  hls::stream< ap_uint<26> >& v1397,
  hls::stream< ap_uint<26> >& v1398,
  hls::stream< ap_uint<26> >& v1399,
  hls::stream< int32_t >& v1400,
  hls::stream< int32_t >& v1401,
  hls::stream< int32_t >& v1402,
  hls::stream< int32_t >& v1403,
  hls::stream< ap_uint<17> >& v1404,
  hls::stream< ap_uint<17> >& v1405,
  hls::stream< ap_uint<17> >& v1406,
  hls::stream< ap_uint<17> >& v1407
) {	// L2172
  int32_t irf2[8];	// L2203
  for (int v1409 = 0; v1409 < 8; v1409++) {	// L2204
    irf2[v1409] = 0;	// L2204
  }
  half drf2[8];	// L2205
  #pragma HLS array_partition variable=drf2 complete dim=1

  for (int v1411 = 0; v1411 < 8; v1411++) {	// L2206
    drf2[v1411] = (double)0.000000;	// L2206
  }
  int32_t drf_full2[8];	// L2207
  #pragma HLS array_partition variable=drf_full2 complete dim=1

  for (int v1413 = 0; v1413 < 8; v1413++) {	// L2208
    drf_full2[v1413] = 0;	// L2208
  }
  int32_t dsmask2;	// L2209
  dsmask2 = 0;	// L2210
  int32_t crv_vld2;	// L2211
  crv_vld2 = 0;	// L2212
  half crv_data2;	// L2213
  crv_data2 = (double)0.000000;	// L2214
  int32_t crv_addr2;	// L2215
  crv_addr2 = 0;	// L2216
  int32_t crv_mode2;	// L2217
  crv_mode2 = 0;	// L2218
  int32_t crv_raw2;	// L2219
  crv_raw2 = 0;	// L2220
  int32_t csd_vld2;	// L2221
  csd_vld2 = 0;	// L2222
  ap_uint<26> csd_pkt2;	// L2223
  csd_pkt2 = 0;	// L2224
  int32_t csd_dir2;	// L2225
  csd_dir2 = 0;	// L2226
  int32_t row_id2;	// L2227
  row_id2 = 0;	// L2228
  int32_t col_id2;	// L2229
  col_id2 = 2;	// L2230
  ap_uint<26> oe_r2;	// L2231
  oe_r2 = 0;	// L2232
  ap_uint<26> ow_r2;	// L2233
  ow_r2 = 0;	// L2234
  ap_uint<26> on_r2;	// L2235
  on_r2 = 0;	// L2236
  ap_uint<26> os_r2;	// L2237
  os_r2 = 0;	// L2238
  ap_uint<17> txn_r2;	// L2239
  txn_r2 = 0;	// L2240
  ap_uint<17> txs_r2;	// L2241
  txs_r2 = 0;	// L2242
  ap_uint<17> txw_r2;	// L2243
  txw_r2 = 0;	// L2244
  ap_uint<17> txe_r2;	// L2245
  txe_r2 = 0;	// L2246
  half hold_v2[4][2];	// L2247
  #pragma HLS array_partition variable=hold_v2 complete dim=1
  #pragma HLS array_partition variable=hold_v2 complete dim=2

  for (int v1434 = 0; v1434 < 4; v1434++) {	// L2248
    for (int v1435 = 0; v1435 < 2; v1435++) {	// L2248
      hold_v2[v1434][v1435] = (double)0.000000;	// L2248
    }
  }
  int32_t hold_cnt2[4];	// L2249
  #pragma HLS array_partition variable=hold_cnt2 complete dim=1

  for (int v1437 = 0; v1437 < 4; v1437++) {	// L2250
    hold_cnt2[v1437] = 0;	// L2250
  }
  ap_uint<26> rbuf2[4][2];	// L2251
  #pragma HLS array_partition variable=rbuf2 complete dim=1
  #pragma HLS array_partition variable=rbuf2 complete dim=2

  for (int v1439 = 0; v1439 < 4; v1439++) {	// L2252
    for (int v1440 = 0; v1440 < 2; v1440++) {	// L2252
      rbuf2[v1439][v1440] = 0;	// L2252
    }
  }
  int32_t rbcnt2[4];	// L2253
  #pragma HLS array_partition variable=rbcnt2 complete dim=1

  for (int v1442 = 0; v1442 < 4; v1442++) {	// L2254
    rbcnt2[v1442] = 0;	// L2254
  }
  int32_t rcred2[4];	// L2255
  #pragma HLS array_partition variable=rcred2 complete dim=1

  for (int v1444 = 0; v1444 < 4; v1444++) {	// L2256
    rcred2[v1444] = 0;	// L2256
  }
  int32_t cre_r2;	// L2257
  cre_r2 = 2;	// L2258
  int32_t crw_r2;	// L2259
  crw_r2 = 2;	// L2260
  int32_t crs_r2;	// L2261
  crs_r2 = 2;	// L2262
  int32_t crn_r2;	// L2263
  crn_r2 = 2;	// L2264
  int32_t cfg_isz2;	// L2265
  cfg_isz2 = 0;	// L2266
  int32_t cfg_itsz2;	// L2267
  cfg_itsz2 = 0;	// L2268
  int32_t fetch_en2;	// L2269
  fetch_en2 = 0;	// L2270
  int32_t instr_cnt2;	// L2271
  instr_cnt2 = 0;	// L2272
  int32_t iter_cnt2;	// L2273
  iter_cnt2 = 0;	// L2274
  int32_t condition_reg2;	// L2275
  condition_reg2 = 0;	// L2276
  l_S_t_0_t2: for (int t2 = 0; t2 < 8; t2++) {	// L2277
  #pragma HLS pipeline II=1
    ap_int<26> v1456 = oe_r2;	// L2278
    v1384.write(v1456);	// L2279
    ap_int<26> v1457 = ow_r2;	// L2280
    v1385.write(v1457);	// L2281
    ap_int<26> v1458 = os_r2;	// L2282
    v1386.write(v1458);	// L2283
    ap_int<26> v1459 = on_r2;	// L2284
    v1387.write(v1459);	// L2285
    ap_int<17> v1460 = txe_r2;	// L2286
    v1388.write(v1460);	// L2287
    ap_int<17> v1461 = txw_r2;	// L2288
    v1389.write(v1461);	// L2289
    ap_int<17> v1462 = txs_r2;	// L2290
    v1390.write(v1462);	// L2291
    ap_int<17> v1463 = txn_r2;	// L2292
    v1391.write(v1463);	// L2293
    int32_t v1464 = cre_r2;	// L2294
    v1392.write(v1464);	// L2295
    int32_t v1465 = crw_r2;	// L2296
    v1393.write(v1465);	// L2297
    int32_t v1466 = crs_r2;	// L2298
    v1394.write(v1466);	// L2299
    int32_t v1467 = crn_r2;	// L2300
    v1395.write(v1467);	// L2301
    ap_uint<26> v1468 = v1396.read();	// L2302
    ap_uint<26> p_w2;	// L2303
    p_w2 = v1468;	// L2304
    ap_uint<26> v1470 = v1397.read();	// L2305
    ap_uint<26> p_e2;	// L2306
    p_e2 = v1470;	// L2307
    ap_uint<26> v1472 = v1398.read();	// L2308
    ap_uint<26> p_n2;	// L2309
    p_n2 = v1472;	// L2310
    ap_uint<26> v1474 = v1399.read();	// L2311
    ap_uint<26> p_s2;	// L2312
    p_s2 = v1474;	// L2313
    int32_t v1476 = v1400.read();	// L2314
    int32_t v1477 = rcred2[0];	// L2315
    ap_int<33> v1478 = v1477;	// L2316
    ap_int<33> v1479 = v1476;	// L2317
    ap_int<33> v1480 = v1478 + v1479;	// L2318
    int32_t v1481 = v1480;	// L2319
    rcred2[0] = v1481;	// L2320
    int32_t v1482 = v1401.read();	// L2321
    int32_t v1483 = rcred2[1];	// L2322
    ap_int<33> v1484 = v1483;	// L2323
    ap_int<33> v1485 = v1482;	// L2324
    ap_int<33> v1486 = v1484 + v1485;	// L2325
    int32_t v1487 = v1486;	// L2326
    rcred2[1] = v1487;	// L2327
    int32_t v1488 = v1402.read();	// L2328
    int32_t v1489 = rcred2[2];	// L2329
    ap_int<33> v1490 = v1489;	// L2330
    ap_int<33> v1491 = v1488;	// L2331
    ap_int<33> v1492 = v1490 + v1491;	// L2332
    int32_t v1493 = v1492;	// L2333
    rcred2[2] = v1493;	// L2334
    int32_t v1494 = v1403.read();	// L2335
    int32_t v1495 = rcred2[3];	// L2336
    ap_int<33> v1496 = v1495;	// L2337
    ap_int<33> v1497 = v1494;	// L2338
    ap_int<33> v1498 = v1496 + v1497;	// L2339
    int32_t v1499 = v1498;	// L2340
    rcred2[3] = v1499;	// L2341
    ap_uint<26> fin2[4];	// L2342
    for (int v1501 = 0; v1501 < 4; v1501++) {	// L2343
      fin2[v1501] = 0;	// L2343
    }
    ap_int<26> v1502 = p_w2;	// L2344
    fin2[0] = v1502;	// L2345
    ap_int<26> v1503 = p_e2;	// L2346
    fin2[1] = v1503;	// L2347
    ap_int<26> v1504 = p_n2;	// L2348
    fin2[2] = v1504;	// L2349
    ap_int<26> v1505 = p_s2;	// L2350
    fin2[3] = v1505;	// L2351
    l_S_d_0_d8: for (int d8 = 0; d8 < 4; d8++) {	// L2352
      ap_uint<26> v1507 = fin2[d8];	// L2353
      bool v1508;
      ap_int<26> v1508_tmp = v1507;
      v1508 = v1508_tmp[25];	// L2354
      int32_t v1509 = v1508;	// L2355
      bool v1510 = v1509 == 1;	// L2356
      int32_t v1511 = rbcnt2[d8];	// L2357
      bool v1512 = v1511 < 2;	// L2358
      bool v1513 = v1510 & v1512;	// L2359
      if (v1513) {	// L2360
        ap_uint<26> v1514 = fin2[d8];	// L2361
        int32_t v1515 = rbcnt2[d8];	// L2362
        int v1516 = v1515;	// L2363
        rbuf2[d8][v1516] = v1514;	// L2364
        int32_t v1517 = rbcnt2[d8];	// L2365
        ap_int<33> v1518 = v1517;	// L2366
        ap_int<33> v1519 = v1518 + 1;	// L2367
        int32_t v1520 = v1519;	// L2368
        rbcnt2[d8] = v1520;	// L2369
      }
    }
    ap_uint<26> hd2[4];	// L2372
    for (int v1522 = 0; v1522 < 4; v1522++) {	// L2373
      hd2[v1522] = 0;	// L2373
    }
    int32_t hvld2[4];	// L2374
    for (int v1524 = 0; v1524 < 4; v1524++) {	// L2375
      hvld2[v1524] = 0;	// L2375
    }
    int32_t hit2[4];	// L2376
    for (int v1526 = 0; v1526 < 4; v1526++) {	// L2377
      hit2[v1526] = 0;	// L2377
    }
    int32_t axis2[4];	// L2378
    for (int v1528 = 0; v1528 < 4; v1528++) {	// L2379
      axis2[v1528] = 0;	// L2379
    }
    int32_t v1529 = col_id2;	// L2380
    axis2[0] = v1529;	// L2381
    int32_t v1530 = col_id2;	// L2382
    axis2[1] = v1530;	// L2383
    int32_t v1531 = row_id2;	// L2384
    axis2[2] = v1531;	// L2385
    int32_t v1532 = row_id2;	// L2386
    axis2[3] = v1532;	// L2387
    l_S_d_1_d9: for (int d9 = 0; d9 < 4; d9++) {	// L2388
      int32_t v1534 = rbcnt2[d9];	// L2389
      bool v1535 = v1534 > 0;	// L2390
      if (v1535) {	// L2391
        ap_uint<26> v1536 = rbuf2[d9][0];	// L2392
        hd2[d9] = v1536;	// L2393
        hvld2[d9] = 1;	// L2394
        ap_uint<26> v1537 = hd2[d9];	// L2395
        ap_int<4> v1538;
        ap_int<26> v1538_tmp = v1537;
        v1538 = v1538_tmp(24, 21);	// L2396
        int32_t v1539 = axis2[d9];	// L2397
        int32_t v1540 = v1538;	// L2398
        bool v1541 = v1540 == v1539;	// L2399
        if (v1541) {	// L2400
          hit2[d9] = 1;	// L2401
        }
      }
    }
    ap_uint<26> o_crv2;	// L2405
    o_crv2 = 0;	// L2406
    int32_t crv_in2;	// L2407
    crv_in2 = -1;	// L2408
    int32_t v1544 = hit2[3];	// L2409
    bool v1545 = v1544 == 1;	// L2410
    if (v1545) {	// L2411
      ap_uint<26> v1546 = hd2[3];	// L2412
      o_crv2 = v1546;	// L2413
      crv_in2 = 3;	// L2414
    } else {
      int32_t v1547 = hit2[2];	// L2416
      bool v1548 = v1547 == 1;	// L2417
      if (v1548) {	// L2418
        ap_uint<26> v1549 = hd2[2];	// L2419
        o_crv2 = v1549;	// L2420
        crv_in2 = 2;	// L2421
      } else {
        int32_t v1550 = hit2[1];	// L2423
        bool v1551 = v1550 == 1;	// L2424
        if (v1551) {	// L2425
          ap_uint<26> v1552 = hd2[1];	// L2426
          o_crv2 = v1552;	// L2427
          crv_in2 = 1;	// L2428
        } else {
          int32_t v1553 = hit2[0];	// L2430
          bool v1554 = v1553 == 1;	// L2431
          if (v1554) {	// L2432
            ap_uint<26> v1555 = hd2[0];	// L2433
            o_crv2 = v1555;	// L2434
            crv_in2 = 0;	// L2435
          }
        }
      }
    }
    ap_uint<26> o_out2[4];	// L2440
    for (int v1557 = 0; v1557 < 4; v1557++) {	// L2441
      o_out2[v1557] = 0;	// L2441
    }
    int32_t pop2[4];	// L2442
    for (int v1559 = 0; v1559 < 4; v1559++) {	// L2443
      pop2[v1559] = 0;	// L2443
    }
    int32_t inj_done2;	// L2444
    inj_done2 = 0;	// L2445
    int32_t idir2;	// L2446
    idir2 = -1;	// L2447
    ap_int<26> v1562 = csd_pkt2;	// L2448
    bool v1563;
    ap_int<26> v1563_tmp = v1562;
    v1563 = v1563_tmp[25];	// L2449
    int32_t v1564 = v1563;	// L2450
    bool v1565 = v1564 == 1;	// L2451
    if (v1565) {	// L2452
      int32_t v1566 = csd_dir2;	// L2453
      ap_int<33> v1567 = v1566;	// L2454
      ap_int<33> v1568 = 3 - v1567;	// L2455
      int32_t v1569 = v1568;	// L2456
      idir2 = v1569;	// L2457
    }
    l_S_o_2_o2: for (int o2 = 0; o2 < 4; o2++) {	// L2459
      int32_t v1571 = rcred2[o2];	// L2460
      bool v1572 = v1571 > 0;	// L2461
      if (v1572) {	// L2462
        int32_t v1573 = idir2;	// L2463
        ap_int<33> v1574 = v1573;	// L2464
        ap_int<33> v1575 = o2;	// L2465
        bool v1576 = v1574 == v1575;	// L2466
        if (v1576) {	// L2467
          ap_int<26> v1577 = csd_pkt2;	// L2468
          o_out2[o2] = v1577;	// L2469
          int32_t v1578 = rcred2[o2];	// L2470
          ap_int<33> v1579 = v1578;	// L2471
          ap_int<33> v1580 = v1579 - 1;	// L2472
          int32_t v1581 = v1580;	// L2473
          rcred2[o2] = v1581;	// L2474
          inj_done2 = 1;	// L2475
        } else {
          int32_t v1582 = hvld2[o2];	// L2477
          bool v1583 = v1582 == 1;	// L2478
          int32_t v1584 = hit2[o2];	// L2479
          bool v1585 = v1584 == 0;	// L2480
          bool v1586 = v1583 & v1585;	// L2481
          if (v1586) {	// L2482
            ap_uint<26> v1587 = hd2[o2];	// L2483
            o_out2[o2] = v1587;	// L2484
            int32_t v1588 = rcred2[o2];	// L2485
            ap_int<33> v1589 = v1588;	// L2486
            ap_int<33> v1590 = v1589 - 1;	// L2487
            int32_t v1591 = v1590;	// L2488
            rcred2[o2] = v1591;	// L2489
            pop2[o2] = 1;	// L2490
          }
        }
      }
    }
    int32_t v1592 = crv_in2;	// L2495
    bool v1593 = v1592 >= 0;	// L2496
    if (v1593) {	// L2497
      int32_t v1594 = crv_in2;	// L2498
      int v1595 = v1594;	// L2499
      pop2[v1595] = 1;	// L2500
    }
    int32_t ret2[4];	// L2502
    for (int v1597 = 0; v1597 < 4; v1597++) {	// L2503
      ret2[v1597] = 0;	// L2503
    }
    l_S_d_3_d10: for (int d10 = 0; d10 < 4; d10++) {	// L2504
      int32_t v1599 = pop2[d10];	// L2505
      bool v1600 = v1599 == 1;	// L2506
      if (v1600) {	// L2507
        l_S_sft_3_sft2: for (int sft2 = 0; sft2 < 1; sft2++) {	// L2508
          ap_uint<26> v1602 = rbuf2[d10][(sft2 + 1)];	// L2509
          rbuf2[d10][sft2] = v1602;	// L2510
        }
        int32_t v1603 = rbcnt2[d10];	// L2512
        ap_int<33> v1604 = v1603;	// L2513
        ap_int<33> v1605 = v1604 - 1;	// L2514
        int32_t v1606 = v1605;	// L2515
        rbcnt2[d10] = v1606;	// L2516
        ret2[d10] = 1;	// L2517
      }
    }
    int32_t v1607 = ret2[0];	// L2520
    cre_r2 = v1607;	// L2521
    int32_t v1608 = ret2[1];	// L2522
    crw_r2 = v1608;	// L2523
    int32_t v1609 = ret2[2];	// L2524
    crs_r2 = v1609;	// L2525
    int32_t v1610 = ret2[3];	// L2526
    crn_r2 = v1610;	// L2527
    ap_uint<26> v1611 = o_out2[0];	// L2528
    oe_r2 = v1611;	// L2529
    ap_uint<26> v1612 = o_out2[1];	// L2530
    ow_r2 = v1612;	// L2531
    ap_uint<26> v1613 = o_out2[2];	// L2532
    os_r2 = v1613;	// L2533
    ap_uint<26> v1614 = o_out2[3];	// L2534
    on_r2 = v1614;	// L2535
    int32_t v1615 = inj_done2;	// L2536
    bool v1616 = v1615 == 1;	// L2537
    if (v1616) {	// L2538
      csd_pkt2 = 0;	// L2539
    }
    ap_int<26> v1617 = o_crv2;	// L2541
    bool v1618;
    ap_int<26> v1618_tmp = v1617;
    v1618 = v1618_tmp[25];	// L2542
    int32_t v1619 = v1618;	// L2543
    crv_vld2 = v1619;	// L2544
    ap_int<26> v1620 = o_crv2;	// L2545
    int16_t v1621;
    ap_int<26> v1621_tmp = v1620;
    v1621 = v1621_tmp(15, 0);	// L2546
    half v1622;
    union { uint16_t from; half to;} _converter_v1621_to_v1622;
    _converter_v1621_to_v1622.from = v1621;
    v1622 = _converter_v1621_to_v1622.to;	// L2547
    crv_data2 = v1622;	// L2548
    ap_int<26> v1623 = o_crv2;	// L2549
    ap_int<4> v1624;
    ap_int<26> v1624_tmp = v1623;
    v1624 = v1624_tmp(19, 16);	// L2550
    int32_t v1625 = v1624;	// L2551
    crv_addr2 = v1625;	// L2552
    ap_int<26> v1626 = o_crv2;	// L2553
    bool v1627;
    ap_int<26> v1627_tmp = v1626;
    v1627 = v1627_tmp[20];	// L2554
    int32_t v1628 = v1627;	// L2555
    crv_mode2 = v1628;	// L2556
    ap_int<26> v1629 = o_crv2;	// L2557
    int16_t v1630;
    ap_int<26> v1630_tmp = v1629;
    v1630 = v1630_tmp(15, 0);	// L2558
    int32_t v1631 = v1630;	// L2559
    crv_raw2 = v1631;	// L2560
    ap_uint<17> v1632 = v1404.read();	// L2561
    ap_uint<17> rx_w2;	// L2562
    rx_w2 = v1632;	// L2563
    ap_uint<17> v1634 = v1405.read();	// L2564
    ap_uint<17> rx_e2;	// L2565
    rx_e2 = v1634;	// L2566
    ap_uint<17> v1636 = v1406.read();	// L2567
    ap_uint<17> rx_n2;	// L2568
    rx_n2 = v1636;	// L2569
    ap_uint<17> v1638 = v1407.read();	// L2570
    ap_uint<17> rx_s2;	// L2571
    rx_s2 = v1638;	// L2572
    half rxv2[4];	// L2573
    for (int v1641 = 0; v1641 < 4; v1641++) {	// L2574
      rxv2[v1641] = (double)0.000000;	// L2574
    }
    int32_t rxvld2[4];	// L2575
    for (int v1643 = 0; v1643 < 4; v1643++) {	// L2576
      rxvld2[v1643] = 0;	// L2576
    }
    ap_int<17> v1644 = rx_n2;	// L2577
    int16_t v1645;
    ap_int<17> v1645_tmp = v1644;
    v1645 = v1645_tmp(16, 1);	// L2578
    half v1646;
    union { uint16_t from; half to;} _converter_v1645_to_v1646;
    _converter_v1645_to_v1646.from = v1645;
    v1646 = _converter_v1645_to_v1646.to;	// L2579
    rxv2[0] = v1646;	// L2580
    ap_int<17> v1647 = rx_n2;	// L2581
    bool v1648;
    ap_int<17> v1648_tmp = v1647;
    v1648 = v1648_tmp[0];	// L2582
    int32_t v1649 = v1648;	// L2583
    rxvld2[0] = v1649;	// L2584
    ap_int<17> v1650 = rx_s2;	// L2585
    int16_t v1651;
    ap_int<17> v1651_tmp = v1650;
    v1651 = v1651_tmp(16, 1);	// L2586
    half v1652;
    union { uint16_t from; half to;} _converter_v1651_to_v1652;
    _converter_v1651_to_v1652.from = v1651;
    v1652 = _converter_v1651_to_v1652.to;	// L2587
    rxv2[1] = v1652;	// L2588
    ap_int<17> v1653 = rx_s2;	// L2589
    bool v1654;
    ap_int<17> v1654_tmp = v1653;
    v1654 = v1654_tmp[0];	// L2590
    int32_t v1655 = v1654;	// L2591
    rxvld2[1] = v1655;	// L2592
    ap_int<17> v1656 = rx_w2;	// L2593
    int16_t v1657;
    ap_int<17> v1657_tmp = v1656;
    v1657 = v1657_tmp(16, 1);	// L2594
    half v1658;
    union { uint16_t from; half to;} _converter_v1657_to_v1658;
    _converter_v1657_to_v1658.from = v1657;
    v1658 = _converter_v1657_to_v1658.to;	// L2595
    rxv2[2] = v1658;	// L2596
    ap_int<17> v1659 = rx_w2;	// L2597
    bool v1660;
    ap_int<17> v1660_tmp = v1659;
    v1660 = v1660_tmp[0];	// L2598
    int32_t v1661 = v1660;	// L2599
    rxvld2[2] = v1661;	// L2600
    ap_int<17> v1662 = rx_e2;	// L2601
    int16_t v1663;
    ap_int<17> v1663_tmp = v1662;
    v1663 = v1663_tmp(16, 1);	// L2602
    half v1664;
    union { uint16_t from; half to;} _converter_v1663_to_v1664;
    _converter_v1663_to_v1664.from = v1663;
    v1664 = _converter_v1663_to_v1664.to;	// L2603
    rxv2[3] = v1664;	// L2604
    ap_int<17> v1665 = rx_e2;	// L2605
    bool v1666;
    ap_int<17> v1666_tmp = v1665;
    v1666 = v1666_tmp[0];	// L2606
    int32_t v1667 = v1666;	// L2607
    rxvld2[3] = v1667;	// L2608
    l_S_d_5_d11: for (int d11 = 0; d11 < 4; d11++) {	// L2609
      int32_t v1669 = rxvld2[d11];	// L2610
      bool v1670 = v1669 == 1;	// L2611
      int32_t v1671 = hold_cnt2[d11];	// L2612
      bool v1672 = v1671 < 2;	// L2613
      bool v1673 = v1670 & v1672;	// L2614
      if (v1673) {	// L2615
        half v1674 = rxv2[d11];	// L2616
        int32_t v1675 = hold_cnt2[d11];	// L2617
        int v1676 = v1675;	// L2618
        hold_v2[d11][v1676] = v1674;	// L2619
        int32_t v1677 = hold_cnt2[d11];	// L2620
        ap_int<33> v1678 = v1677;	// L2621
        ap_int<33> v1679 = v1678 + 1;	// L2622
        int32_t v1680 = v1679;	// L2623
        hold_cnt2[d11] = v1680;	// L2624
      }
    }
    int32_t pc2;	// L2627
    pc2 = -1;	// L2628
    int32_t v1682 = fetch_en2;	// L2629
    bool v1683 = v1682 == 1;	// L2630
    if (v1683) {	// L2631
      int32_t v1684 = instr_cnt2;	// L2632
      pc2 = v1684;	// L2633
    }
    int32_t instr2;	// L2635
    instr2 = 0;	// L2636
    int32_t v1686 = pc2;	// L2637
    bool v1687 = v1686 >= 0;	// L2638
    if (v1687) {	// L2639
      int32_t v1688 = pc2;	// L2640
      int v1689 = v1688;	// L2641
      int32_t v1690 = irf2[v1689];	// L2642
      instr2 = v1690;	// L2643
    }
    int32_t v1691 = instr2;	// L2645
    int32_t v1692 = v1691 & 15;	// L2646
    int32_t op2;	// L2647
    op2 = v1692;	// L2648
    int32_t v1694 = instr2;	// L2649
    int32_t v1695 = v1694 >> 4;	// L2650
    int32_t v1696 = v1695 & 15;	// L2651
    int32_t dst2;	// L2652
    dst2 = v1696;	// L2653
    int32_t v1698 = instr2;	// L2654
    int32_t v1699 = v1698 >> 8;	// L2655
    int32_t v1700 = v1699 & 15;	// L2656
    int32_t s12;	// L2657
    s12 = v1700;	// L2658
    int32_t v1702 = instr2;	// L2659
    int32_t v1703 = v1702 >> 12;	// L2660
    int32_t v1704 = v1703 & 15;	// L2661
    int32_t s22;	// L2662
    s22 = v1704;	// L2663
    half a2;	// L2664
    a2 = (double)0.000000;	// L2665
    half b2;	// L2666
    b2 = (double)0.000000;	// L2667
    int32_t v1708 = s12;	// L2668
    bool v1709 = v1708 >= 12;	// L2669
    if (v1709) {	// L2670
      int32_t v1710 = s12;	// L2671
      int32_t v1711 = v1710 & 3;	// L2672
      int v1712 = v1711;	// L2673
      half v1713 = hold_v2[v1712][0];	// L2674
      a2 = v1713;	// L2675
    } else {
      int32_t v1714 = s12;	// L2677
      int v1715 = v1714;	// L2678
      half v1716 = drf2[v1715];	// L2679
      a2 = v1716;	// L2680
    }
    int32_t v1717 = s22;	// L2682
    bool v1718 = v1717 >= 12;	// L2683
    if (v1718) {	// L2684
      int32_t v1719 = s22;	// L2685
      int32_t v1720 = v1719 & 3;	// L2686
      int v1721 = v1720;	// L2687
      half v1722 = hold_v2[v1721][0];	// L2688
      b2 = v1722;	// L2689
    } else {
      int32_t v1723 = s22;	// L2691
      int v1724 = v1723;	// L2692
      half v1725 = drf2[v1724];	// L2693
      b2 = v1725;	// L2694
    }
    int32_t a_vld2;	// L2696
    a_vld2 = 1;	// L2697
    int32_t b_vld2;	// L2698
    b_vld2 = 1;	// L2699
    int32_t v1728 = s12;	// L2700
    bool v1729 = v1728 >= 12;	// L2701
    if (v1729) {	// L2702
      a_vld2 = 0;	// L2703
      int32_t v1730 = s12;	// L2704
      int32_t v1731 = v1730 & 3;	// L2705
      int v1732 = v1731;	// L2706
      int32_t v1733 = hold_cnt2[v1732];	// L2707
      bool v1734 = v1733 > 0;	// L2708
      if (v1734) {	// L2709
        a_vld2 = 1;	// L2710
      }
    }
    int32_t v1735 = s22;	// L2713
    bool v1736 = v1735 >= 12;	// L2714
    if (v1736) {	// L2715
      b_vld2 = 0;	// L2716
      int32_t v1737 = s22;	// L2717
      int32_t v1738 = v1737 & 3;	// L2718
      int v1739 = v1738;	// L2719
      int32_t v1740 = hold_cnt2[v1739];	// L2720
      bool v1741 = v1740 > 0;	// L2721
      if (v1741) {	// L2722
        b_vld2 = 1;	// L2723
      }
    }
    int32_t v1742 = s12;	// L2726
    bool v1743 = v1742 < 8;	// L2727
    int32_t v1744 = dsmask2;	// L2728
    int32_t v1745 = v1744 >> v1742;	// L2729
    int32_t v1746 = v1745 & 1;	// L2730
    bool v1747 = v1746 == 1;	// L2731
    bool v1748 = v1743 & v1747;	// L2732
    if (v1748) {	// L2733
      int32_t v1749 = s12;	// L2734
      int v1750 = v1749;	// L2735
      int32_t v1751 = drf_full2[v1750];	// L2736
      bool v1752 = v1751 == 0;	// L2737
      if (v1752) {	// L2738
        a_vld2 = 0;	// L2739
      }
    }
    int32_t v1753 = s22;	// L2742
    bool v1754 = v1753 < 8;	// L2743
    int32_t v1755 = dsmask2;	// L2744
    int32_t v1756 = v1755 >> v1753;	// L2745
    int32_t v1757 = v1756 & 1;	// L2746
    bool v1758 = v1757 == 1;	// L2747
    bool v1759 = v1754 & v1758;	// L2748
    if (v1759) {	// L2749
      int32_t v1760 = s22;	// L2750
      int v1761 = v1760;	// L2751
      int32_t v1762 = drf_full2[v1761];	// L2752
      bool v1763 = v1762 == 0;	// L2753
      if (v1763) {	// L2754
        b_vld2 = 0;	// L2755
      }
    }
    int32_t binop2;	// L2758
    binop2 = 0;	// L2759
    int32_t v1765 = op2;	// L2760
    bool v1766 = v1765 == 0;	// L2761
    bool v1767 = v1765 == 1;	// L2762
    bool v1768 = v1765 == 2;	// L2763
    bool v1769 = v1765 == 8;	// L2764
    bool v1770 = v1765 == 9;	// L2765
    bool v1771 = v1766 | v1767;	// L2766
    bool v1772 = v1771 | v1768;	// L2767
    bool v1773 = v1772 | v1769;	// L2768
    bool v1774 = v1773 | v1770;	// L2769
    if (v1774) {	// L2770
      binop2 = 1;	// L2771
    }
    int32_t grant2;	// L2773
    grant2 = 0;	// L2774
    int32_t v1776 = pc2;	// L2775
    bool v1777 = v1776 >= 0;	// L2776
    if (v1777) {	// L2777
      grant2 = 1;	// L2778
    }
    int32_t v1778 = pc2;	// L2780
    bool v1779 = v1778 >= 0;	// L2781
    int32_t v1780 = a_vld2;	// L2782
    bool v1781 = v1780 == 0;	// L2783
    int32_t v1782 = binop2;	// L2784
    bool v1783 = v1782 == 1;	// L2785
    int32_t v1784 = b_vld2;	// L2786
    bool v1785 = v1784 == 0;	// L2787
    bool v1786 = v1783 & v1785;	// L2788
    bool v1787 = v1781 | v1786;	// L2789
    bool v1788 = v1779 & v1787;	// L2790
    if (v1788) {	// L2791
      grant2 = 0;	// L2792
    }
    int32_t v1789 = grant2;	// L2794
    bool v1790 = v1789 == 1;	// L2795
    if (v1790) {	// L2796
      int32_t v1791 = instr_cnt2;	// L2797
      int32_t v1792 = cfg_isz2;	// L2798
      bool v1793 = v1791 == v1792;	// L2799
      if (v1793) {	// L2800
        instr_cnt2 = 0;	// L2801
        int32_t v1794 = iter_cnt2;	// L2802
        int32_t v1795 = cfg_itsz2;	// L2803
        ap_int<33> v1796 = v1795;	// L2804
        ap_int<33> v1797 = v1796 - 1;	// L2805
        ap_int<33> v1798 = v1794;	// L2806
        bool v1799 = v1798 == v1797;	// L2807
        if (v1799) {	// L2808
          fetch_en2 = 0;	// L2809
        } else {
          int32_t v1800 = iter_cnt2;	// L2811
          ap_int<33> v1801 = v1800;	// L2812
          ap_int<33> v1802 = v1801 + 1;	// L2813
          int32_t v1803 = v1802;	// L2814
          iter_cnt2 = v1803;	// L2815
        }
      } else {
        int32_t v1804 = instr_cnt2;	// L2818
        ap_int<33> v1805 = v1804;	// L2819
        ap_int<33> v1806 = v1805 + 1;	// L2820
        int32_t v1807 = v1806;	// L2821
        instr_cnt2 = v1807;	// L2822
      }
    }
    int32_t c12;	// L2825
    c12 = -1;	// L2826
    int32_t c22;	// L2827
    c22 = -1;	// L2828
    int32_t v1810 = grant2;	// L2829
    bool v1811 = v1810 == 1;	// L2830
    int32_t v1812 = s12;	// L2831
    bool v1813 = v1812 >= 12;	// L2832
    bool v1814 = v1811 & v1813;	// L2833
    if (v1814) {	// L2834
      int32_t v1815 = s12;	// L2835
      int32_t v1816 = v1815 & 3;	// L2836
      c12 = v1816;	// L2837
    }
    int32_t v1817 = grant2;	// L2839
    bool v1818 = v1817 == 1;	// L2840
    int32_t v1819 = s22;	// L2841
    bool v1820 = v1819 >= 12;	// L2842
    bool v1821 = v1818 & v1820;	// L2843
    if (v1821) {	// L2844
      int32_t v1822 = s22;	// L2845
      int32_t v1823 = v1822 & 3;	// L2846
      c22 = v1823;	// L2847
    }
    int32_t v1824 = c12;	// L2849
    bool v1825 = v1824 >= 0;	// L2850
    if (v1825) {	// L2851
      int32_t v1826 = c12;	// L2852
      int v1827 = v1826;	// L2853
      half v1828 = hold_v2[v1827][1];	// L2854
      hold_v2[v1827][0] = v1828;	// L2855
      int32_t v1829 = c12;	// L2856
      int v1830 = v1829;	// L2857
      int32_t v1831 = hold_cnt2[v1830];	// L2858
      ap_int<33> v1832 = v1831;	// L2859
      ap_int<33> v1833 = v1832 - 1;	// L2860
      int32_t v1834 = v1833;	// L2861
      hold_cnt2[v1830] = v1834;	// L2862
    }
    int32_t v1835 = c22;	// L2864
    bool v1836 = v1835 >= 0;	// L2865
    int32_t v1837 = c12;	// L2866
    bool v1838 = v1835 != v1837;	// L2867
    bool v1839 = v1836 & v1838;	// L2868
    if (v1839) {	// L2869
      int32_t v1840 = c22;	// L2870
      int v1841 = v1840;	// L2871
      half v1842 = hold_v2[v1841][1];	// L2872
      hold_v2[v1841][0] = v1842;	// L2873
      int32_t v1843 = c22;	// L2874
      int v1844 = v1843;	// L2875
      int32_t v1845 = hold_cnt2[v1844];	// L2876
      ap_int<33> v1846 = v1845;	// L2877
      ap_int<33> v1847 = v1846 - 1;	// L2878
      int32_t v1848 = v1847;	// L2879
      hold_cnt2[v1844] = v1848;	// L2880
    }
    int32_t v1849 = grant2;	// L2882
    bool v1850 = v1849 == 1;	// L2883
    int32_t v1851 = s12;	// L2884
    bool v1852 = v1851 < 8;	// L2885
    int32_t v1853 = dsmask2;	// L2886
    int32_t v1854 = v1853 >> v1851;	// L2887
    int32_t v1855 = v1854 & 1;	// L2888
    bool v1856 = v1855 == 1;	// L2889
    bool v1857 = v1850 & v1852;	// L2890
    bool v1858 = v1857 & v1856;	// L2891
    if (v1858) {	// L2892
      int32_t v1859 = s12;	// L2893
      int v1860 = v1859;	// L2894
      drf_full2[v1860] = 0;	// L2895
    }
    int32_t v1861 = grant2;	// L2897
    bool v1862 = v1861 == 1;	// L2898
    int32_t v1863 = s22;	// L2899
    bool v1864 = v1863 < 8;	// L2900
    int32_t v1865 = dsmask2;	// L2901
    int32_t v1866 = v1865 >> v1863;	// L2902
    int32_t v1867 = v1866 & 1;	// L2903
    bool v1868 = v1867 == 1;	// L2904
    bool v1869 = v1862 & v1864;	// L2905
    bool v1870 = v1869 & v1868;	// L2906
    if (v1870) {	// L2907
      int32_t v1871 = s22;	// L2908
      int v1872 = v1871;	// L2909
      drf_full2[v1872] = 0;	// L2910
    }
    half res2;	// L2912
    res2 = (double)0.000000;	// L2913
    int32_t v1874 = op2;	// L2914
    bool v1875 = v1874 == 0;	// L2915
    if (v1875) {	// L2916
      half v1876 = a2;	// L2917
      half v1877 = b2;	// L2918
      half v1878 = v1876 + v1877;	// L2919
      res2 = v1878;	// L2920
    } else {
      int32_t v1879 = op2;	// L2922
      bool v1880 = v1879 == 1;	// L2923
      if (v1880) {	// L2924
        half v1881 = a2;	// L2925
        half v1882 = b2;	// L2926
        half v1883 = v1881 - v1882;	// L2927
        res2 = v1883;	// L2928
      } else {
        int32_t v1884 = op2;	// L2930
        bool v1885 = v1884 == 2;	// L2931
        if (v1885) {	// L2932
          half v1886 = a2;	// L2933
          half v1887 = b2;	// L2934
          half v1888 = v1886 * v1887;	// L2935
          res2 = v1888;	// L2936
        } else {
          int32_t v1889 = op2;	// L2938
          bool v1890 = v1889 == 8;	// L2939
          if (v1890) {	// L2940
            half v1891 = a2;	// L2941
            half v1892 = b2;	// L2942
            bool v1893 = v1891 >= v1892;	// L2943
            if (v1893) {	// L2944
              res2 = (double)1.000000;	// L2945
            } else {
              res2 = (double)-1.000000;	// L2947
            }
          } else {
            int32_t v1894 = op2;	// L2950
            bool v1895 = v1894 == 9;	// L2951
            if (v1895) {	// L2952
              half v1896 = a2;	// L2953
              half v1897 = b2;	// L2954
              bool v1898 = v1896 < v1897;	// L2955
              if (v1898) {	// L2956
                res2 = (double)1.000000;	// L2957
              } else {
                res2 = (double)-1.000000;	// L2959
              }
            } else {
              half v1899 = a2;	// L2962
              res2 = v1899;	// L2963
            }
          }
        }
      }
    }
    int32_t v1900 = a_vld2;	// L2969
    int32_t res_vld2;	// L2970
    res_vld2 = v1900;	// L2971
    int32_t v1902 = op2;	// L2972
    bool v1903 = v1902 == 0;	// L2973
    bool v1904 = v1902 == 1;	// L2974
    bool v1905 = v1902 == 2;	// L2975
    bool v1906 = v1902 == 8;	// L2976
    bool v1907 = v1902 == 9;	// L2977
    bool v1908 = v1903 | v1904;	// L2978
    bool v1909 = v1908 | v1905;	// L2979
    bool v1910 = v1909 | v1906;	// L2980
    bool v1911 = v1910 | v1907;	// L2981
    if (v1911) {	// L2982
      int32_t v1912 = a_vld2;	// L2983
      int32_t v1913 = b_vld2;	// L2984
      int64_t v1914 = v1912;	// L2985
      int64_t v1915 = v1913;	// L2986
      int64_t v1916 = v1914 * v1915;	// L2987
      int32_t v1917 = v1916;	// L2988
      res_vld2 = v1917;	// L2989
    }
    int32_t v1918 = grant2;	// L2991
    bool v1919 = v1918 == 0;	// L2992
    if (v1919) {	// L2993
      res_vld2 = 0;	// L2994
    }
    int32_t v1920 = grant2;	// L2996
    bool v1921 = v1920 == 1;	// L2997
    int32_t v1922 = op2;	// L2998
    bool v1923 = v1922 == 8;	// L2999
    bool v1924 = v1921 & v1923;	// L3000
    if (v1924) {	// L3001
      condition_reg2 = 0;	// L3002
      half v1925 = a2;	// L3003
      half v1926 = b2;	// L3004
      bool v1927 = v1925 >= v1926;	// L3005
      if (v1927) {	// L3006
        condition_reg2 = 1;	// L3007
      }
    }
    int32_t v1928 = grant2;	// L3010
    bool v1929 = v1928 == 1;	// L3011
    int32_t v1930 = op2;	// L3012
    bool v1931 = v1930 == 9;	// L3013
    bool v1932 = v1929 & v1931;	// L3014
    if (v1932) {	// L3015
      condition_reg2 = 0;	// L3016
      half v1933 = a2;	// L3017
      half v1934 = b2;	// L3018
      bool v1935 = v1933 < v1934;	// L3019
      if (v1935) {	// L3020
        condition_reg2 = 1;	// L3021
      }
    }
    ap_uint<17> tx_n2;	// L3024
    tx_n2 = 0;	// L3025
    ap_uint<17> tx_s2;	// L3026
    tx_s2 = 0;	// L3027
    ap_uint<17> tx_w2;	// L3028
    tx_w2 = 0;	// L3029
    ap_uint<17> tx_e2;	// L3030
    tx_e2 = 0;	// L3031
    int32_t is_rtr2;	// L3032
    is_rtr2 = 0;	// L3033
    int32_t do_inj2;	// L3034
    do_inj2 = 0;	// L3035
    int32_t v1942 = op2;	// L3036
    bool v1943 = v1942 >= 4;	// L3037
    ap_int<33> v1944 = v1942;	// L3038
    bool v1945 = v1944 <= 7;	// L3039
    bool v1946 = v1943 & v1945;	// L3040
    if (v1946) {	// L3041
      is_rtr2 = 1;	// L3042
      do_inj2 = 1;	// L3043
    }
    int32_t v1947 = op2;	// L3045
    bool v1948 = v1947 >= 12;	// L3046
    ap_int<33> v1949 = v1947;	// L3047
    bool v1950 = v1949 <= 15;	// L3048
    bool v1951 = v1948 & v1950;	// L3049
    if (v1951) {	// L3050
      is_rtr2 = 1;	// L3051
      int32_t v1952 = condition_reg2;	// L3052
      bool v1953 = v1952 == 1;	// L3053
      if (v1953) {	// L3054
        do_inj2 = 1;	// L3055
      }
    }
    int32_t v1954 = is_rtr2;	// L3058
    bool v1955 = v1954 == 1;	// L3059
    if (v1955) {	// L3060
      int32_t v1956 = do_inj2;	// L3061
      bool v1957 = v1956 == 1;	// L3062
      ap_int<26> v1958 = csd_pkt2;	// L3063
      bool v1959;
      ap_int<26> v1959_tmp = v1958;
      v1959 = v1959_tmp[25];	// L3064
      int32_t v1960 = v1959;	// L3065
      bool v1961 = v1960 == 0;	// L3066
      bool v1962 = v1957 & v1961;	// L3067
      if (v1962) {	// L3068
        half v1963 = res2;	// L3069
        uint16_t v1964;
        union { half from; uint16_t to;} _converter_v1963_to_v1964;
        _converter_v1963_to_v1964.from = v1963;
        v1964 = _converter_v1963_to_v1964.to;	// L3070
        ap_int<26> v1965 = csd_pkt2;	// L3071
        ap_int<26> v1966;
        ap_int<26> v1966_tmp = v1965;
        v1966_tmp(15, 0) = v1964;
        v1966 = v1966_tmp;	// L3072
        csd_pkt2 = v1966;	// L3073
        int32_t v1967 = dst2;	// L3074
        ap_uint<4> v1968 = v1967;	// L3075
        ap_int<26> v1969 = csd_pkt2;	// L3076
        ap_int<26> v1970;
        ap_int<26> v1970_tmp = v1969;
        v1970_tmp(19, 16) = v1968;
        v1970 = v1970_tmp;	// L3077
        csd_pkt2 = v1970;	// L3078
        int32_t v1971 = s22;	// L3079
        ap_uint<4> v1972 = v1971;	// L3080
        ap_int<26> v1973 = csd_pkt2;	// L3081
        ap_int<26> v1974;
        ap_int<26> v1974_tmp = v1973;
        v1974_tmp(24, 21) = v1972;
        v1974 = v1974_tmp;	// L3082
        csd_pkt2 = v1974;	// L3083
        int32_t v1975 = res_vld2;	// L3084
        bool v1976 = v1975;	// L3085
        ap_int<26> v1977 = csd_pkt2;	// L3086
        ap_int<26> v1978;
        ap_int<26> v1978_tmp = v1977;
        v1978_tmp[25] = v1976;        v1978 = v1978_tmp;	// L3087
        csd_pkt2 = v1978;	// L3088
        int32_t v1979 = op2;	// L3089
        int32_t v1980 = v1979 & 3;	// L3090
        csd_dir2 = v1980;	// L3091
      }
    } else {
      int32_t v1981 = dst2;	// L3094
      bool v1982 = v1981 >= 12;	// L3095
      if (v1982) {	// L3096
        ap_uint<17> tw2;	// L3097
        tw2 = 0;	// L3098
        int32_t v1984 = res_vld2;	// L3099
        bool v1985 = v1984;	// L3100
        ap_int<17> v1986 = tw2;	// L3101
        ap_int<17> v1987;
        ap_int<17> v1987_tmp = v1986;
        v1987_tmp[0] = v1985;        v1987 = v1987_tmp;	// L3102
        tw2 = v1987;	// L3103
        half v1988 = res2;	// L3104
        uint16_t v1989;
        union { half from; uint16_t to;} _converter_v1988_to_v1989;
        _converter_v1988_to_v1989.from = v1988;
        v1989 = _converter_v1988_to_v1989.to;	// L3105
        ap_int<17> v1990 = tw2;	// L3106
        ap_int<17> v1991;
        ap_int<17> v1991_tmp = v1990;
        v1991_tmp(16, 1) = v1989;
        v1991 = v1991_tmp;	// L3107
        tw2 = v1991;	// L3108
        int32_t v1992 = dst2;	// L3109
        int32_t v1993 = v1992 & 3;	// L3110
        bool v1994 = v1993 == 0;	// L3111
        if (v1994) {	// L3112
          ap_int<17> v1995 = tw2;	// L3113
          tx_n2 = v1995;	// L3114
        } else {
          int32_t v1996 = dst2;	// L3116
          int32_t v1997 = v1996 & 3;	// L3117
          bool v1998 = v1997 == 1;	// L3118
          if (v1998) {	// L3119
            ap_int<17> v1999 = tw2;	// L3120
            tx_s2 = v1999;	// L3121
          } else {
            int32_t v2000 = dst2;	// L3123
            int32_t v2001 = v2000 & 3;	// L3124
            bool v2002 = v2001 == 2;	// L3125
            if (v2002) {	// L3126
              ap_int<17> v2003 = tw2;	// L3127
              tx_w2 = v2003;	// L3128
            } else {
              ap_int<17> v2004 = tw2;	// L3130
              tx_e2 = v2004;	// L3131
            }
          }
        }
      } else {
        int32_t v2005 = res_vld2;	// L3136
        bool v2006 = v2005 == 1;	// L3137
        if (v2006) {	// L3138
          int32_t v2007 = dst2;	// L3139
          bool v2008 = v2007 < 8;	// L3140
          int32_t v2009 = dsmask2;	// L3141
          int32_t v2010 = v2009 >> v2007;	// L3142
          int32_t v2011 = v2010 & 1;	// L3143
          bool v2012 = v2011 == 1;	// L3144
          bool v2013 = v2008 & v2012;	// L3145
          if (v2013) {	// L3146
            int32_t v2014 = dst2;	// L3147
            int v2015 = v2014;	// L3148
            int32_t v2016 = drf_full2[v2015];	// L3149
            bool v2017 = v2016 == 0;	// L3150
            if (v2017) {	// L3151
              half v2018 = res2;	// L3152
              int32_t v2019 = dst2;	// L3153
              int v2020 = v2019;	// L3154
              drf2[v2020] = v2018;	// L3155
              int32_t v2021 = dst2;	// L3156
              int v2022 = v2021;	// L3157
              drf_full2[v2022] = 1;	// L3158
            }
          } else {
            half v2023 = res2;	// L3161
            int32_t v2024 = dst2;	// L3162
            int v2025 = v2024;	// L3163
            drf2[v2025] = v2023;	// L3164
          }
        }
      }
    }
    ap_int<17> v2026 = tx_n2;	// L3169
    txn_r2 = v2026;	// L3170
    ap_int<17> v2027 = tx_s2;	// L3171
    txs_r2 = v2027;	// L3172
    ap_int<17> v2028 = tx_w2;	// L3173
    txw_r2 = v2028;	// L3174
    ap_int<17> v2029 = tx_e2;	// L3175
    txe_r2 = v2029;	// L3176
    int32_t v2030 = crv_vld2;	// L3177
    bool v2031 = v2030 == 1;	// L3178
    if (v2031) {	// L3179
      int32_t v2032 = crv_mode2;	// L3180
      bool v2033 = v2032 == 1;	// L3181
      if (v2033) {	// L3182
        int32_t v2034 = crv_addr2;	// L3183
        int32_t v2035 = v2034 >> 3;	// L3184
        int32_t v2036 = v2035 & 1;	// L3185
        bool v2037 = v2036 == 1;	// L3186
        if (v2037) {	// L3187
          int32_t v2038 = crv_raw2;	// L3188
          int32_t v2039 = crv_addr2;	// L3189
          int32_t v2040 = v2039 & 7;	// L3190
          int v2041 = v2040;	// L3191
          irf2[v2041] = v2038;	// L3192
        } else {
          int32_t v2042 = crv_addr2;	// L3194
          bool v2043 = v2042 == 0;	// L3195
          if (v2043) {	// L3196
            int32_t v2044 = crv_raw2;	// L3197
            int32_t v2045 = v2044 & 255;	// L3198
            dsmask2 = v2045;	// L3199
            int32_t v2046 = crv_raw2;	// L3200
            int32_t v2047 = v2046 >> 8;	// L3201
            int32_t v2048 = v2047 & 7;	// L3202
            cfg_isz2 = v2048;	// L3203
            int32_t v2049 = crv_raw2;	// L3204
            int32_t v2050 = v2049 >> 15;	// L3205
            int32_t v2051 = v2050 & 1;	// L3206
            bool v2052 = v2051 == 1;	// L3207
            if (v2052) {	// L3208
              fetch_en2 = 1;	// L3209
              instr_cnt2 = 0;	// L3210
              iter_cnt2 = 0;	// L3211
            }
          } else {
            int32_t v2053 = crv_addr2;	// L3214
            bool v2054 = v2053 == 1;	// L3215
            if (v2054) {	// L3216
              int32_t v2055 = crv_raw2;	// L3217
              int32_t v2056 = v2055 & 255;	// L3218
              cfg_itsz2 = v2056;	// L3219
            }
          }
        }
      } else {
        int32_t v2057 = crv_addr2;	// L3224
        bool v2058 = v2057 < 8;	// L3225
        int32_t v2059 = dsmask2;	// L3226
        int32_t v2060 = v2059 >> v2057;	// L3227
        int32_t v2061 = v2060 & 1;	// L3228
        bool v2062 = v2061 == 1;	// L3229
        bool v2063 = v2058 & v2062;	// L3230
        if (v2063) {	// L3231
          int32_t v2064 = crv_addr2;	// L3232
          int v2065 = v2064;	// L3233
          int32_t v2066 = drf_full2[v2065];	// L3234
          bool v2067 = v2066 == 0;	// L3235
          if (v2067) {	// L3236
            half v2068 = crv_data2;	// L3237
            int32_t v2069 = crv_addr2;	// L3238
            int v2070 = v2069;	// L3239
            drf2[v2070] = v2068;	// L3240
            int32_t v2071 = crv_addr2;	// L3241
            int v2072 = v2071;	// L3242
            drf_full2[v2072] = 1;	// L3243
          }
        } else {
          half v2073 = crv_data2;	// L3246
          int32_t v2074 = crv_addr2;	// L3247
          int v2075 = v2074;	// L3248
          drf2[v2075] = v2073;	// L3249
        }
      }
    }
  }
}

void node_0_3(
  hls::stream< ap_uint<26> >& v2076,
  hls::stream< ap_uint<26> >& v2077,
  hls::stream< ap_uint<26> >& v2078,
  hls::stream< ap_uint<26> >& v2079,
  hls::stream< ap_uint<17> >& v2080,
  hls::stream< ap_uint<17> >& v2081,
  hls::stream< ap_uint<17> >& v2082,
  hls::stream< ap_uint<17> >& v2083,
  hls::stream< int32_t >& v2084,
  hls::stream< int32_t >& v2085,
  hls::stream< int32_t >& v2086,
  hls::stream< int32_t >& v2087,
  hls::stream< ap_uint<26> >& v2088,
  hls::stream< ap_uint<26> >& v2089,
  hls::stream< ap_uint<26> >& v2090,
  hls::stream< ap_uint<26> >& v2091,
  hls::stream< int32_t >& v2092,
  hls::stream< int32_t >& v2093,
  hls::stream< int32_t >& v2094,
  hls::stream< int32_t >& v2095,
  hls::stream< ap_uint<17> >& v2096,
  hls::stream< ap_uint<17> >& v2097,
  hls::stream< ap_uint<17> >& v2098,
  hls::stream< ap_uint<17> >& v2099
) {	// L3256
  int32_t irf3[8];	// L3287
  for (int v2101 = 0; v2101 < 8; v2101++) {	// L3288
    irf3[v2101] = 0;	// L3288
  }
  half drf3[8];	// L3289
  #pragma HLS array_partition variable=drf3 complete dim=1

  for (int v2103 = 0; v2103 < 8; v2103++) {	// L3290
    drf3[v2103] = (double)0.000000;	// L3290
  }
  int32_t drf_full3[8];	// L3291
  #pragma HLS array_partition variable=drf_full3 complete dim=1

  for (int v2105 = 0; v2105 < 8; v2105++) {	// L3292
    drf_full3[v2105] = 0;	// L3292
  }
  int32_t dsmask3;	// L3293
  dsmask3 = 0;	// L3294
  int32_t crv_vld3;	// L3295
  crv_vld3 = 0;	// L3296
  half crv_data3;	// L3297
  crv_data3 = (double)0.000000;	// L3298
  int32_t crv_addr3;	// L3299
  crv_addr3 = 0;	// L3300
  int32_t crv_mode3;	// L3301
  crv_mode3 = 0;	// L3302
  int32_t crv_raw3;	// L3303
  crv_raw3 = 0;	// L3304
  int32_t csd_vld3;	// L3305
  csd_vld3 = 0;	// L3306
  ap_uint<26> csd_pkt3;	// L3307
  csd_pkt3 = 0;	// L3308
  int32_t csd_dir3;	// L3309
  csd_dir3 = 0;	// L3310
  int32_t row_id3;	// L3311
  row_id3 = 0;	// L3312
  int32_t col_id3;	// L3313
  col_id3 = 3;	// L3314
  ap_uint<26> oe_r3;	// L3315
  oe_r3 = 0;	// L3316
  ap_uint<26> ow_r3;	// L3317
  ow_r3 = 0;	// L3318
  ap_uint<26> on_r3;	// L3319
  on_r3 = 0;	// L3320
  ap_uint<26> os_r3;	// L3321
  os_r3 = 0;	// L3322
  ap_uint<17> txn_r3;	// L3323
  txn_r3 = 0;	// L3324
  ap_uint<17> txs_r3;	// L3325
  txs_r3 = 0;	// L3326
  ap_uint<17> txw_r3;	// L3327
  txw_r3 = 0;	// L3328
  ap_uint<17> txe_r3;	// L3329
  txe_r3 = 0;	// L3330
  half hold_v3[4][2];	// L3331
  #pragma HLS array_partition variable=hold_v3 complete dim=1
  #pragma HLS array_partition variable=hold_v3 complete dim=2

  for (int v2126 = 0; v2126 < 4; v2126++) {	// L3332
    for (int v2127 = 0; v2127 < 2; v2127++) {	// L3332
      hold_v3[v2126][v2127] = (double)0.000000;	// L3332
    }
  }
  int32_t hold_cnt3[4];	// L3333
  #pragma HLS array_partition variable=hold_cnt3 complete dim=1

  for (int v2129 = 0; v2129 < 4; v2129++) {	// L3334
    hold_cnt3[v2129] = 0;	// L3334
  }
  ap_uint<26> rbuf3[4][2];	// L3335
  #pragma HLS array_partition variable=rbuf3 complete dim=1
  #pragma HLS array_partition variable=rbuf3 complete dim=2

  for (int v2131 = 0; v2131 < 4; v2131++) {	// L3336
    for (int v2132 = 0; v2132 < 2; v2132++) {	// L3336
      rbuf3[v2131][v2132] = 0;	// L3336
    }
  }
  int32_t rbcnt3[4];	// L3337
  #pragma HLS array_partition variable=rbcnt3 complete dim=1

  for (int v2134 = 0; v2134 < 4; v2134++) {	// L3338
    rbcnt3[v2134] = 0;	// L3338
  }
  int32_t rcred3[4];	// L3339
  #pragma HLS array_partition variable=rcred3 complete dim=1

  for (int v2136 = 0; v2136 < 4; v2136++) {	// L3340
    rcred3[v2136] = 0;	// L3340
  }
  int32_t cre_r3;	// L3341
  cre_r3 = 2;	// L3342
  int32_t crw_r3;	// L3343
  crw_r3 = 2;	// L3344
  int32_t crs_r3;	// L3345
  crs_r3 = 2;	// L3346
  int32_t crn_r3;	// L3347
  crn_r3 = 2;	// L3348
  int32_t cfg_isz3;	// L3349
  cfg_isz3 = 0;	// L3350
  int32_t cfg_itsz3;	// L3351
  cfg_itsz3 = 0;	// L3352
  int32_t fetch_en3;	// L3353
  fetch_en3 = 0;	// L3354
  int32_t instr_cnt3;	// L3355
  instr_cnt3 = 0;	// L3356
  int32_t iter_cnt3;	// L3357
  iter_cnt3 = 0;	// L3358
  int32_t condition_reg3;	// L3359
  condition_reg3 = 0;	// L3360
  l_S_t_0_t3: for (int t3 = 0; t3 < 8; t3++) {	// L3361
  #pragma HLS pipeline II=1
    ap_int<26> v2148 = oe_r3;	// L3362
    v2076.write(v2148);	// L3363
    ap_int<26> v2149 = ow_r3;	// L3364
    v2077.write(v2149);	// L3365
    ap_int<26> v2150 = os_r3;	// L3366
    v2078.write(v2150);	// L3367
    ap_int<26> v2151 = on_r3;	// L3368
    v2079.write(v2151);	// L3369
    ap_int<17> v2152 = txe_r3;	// L3370
    v2080.write(v2152);	// L3371
    ap_int<17> v2153 = txw_r3;	// L3372
    v2081.write(v2153);	// L3373
    ap_int<17> v2154 = txs_r3;	// L3374
    v2082.write(v2154);	// L3375
    ap_int<17> v2155 = txn_r3;	// L3376
    v2083.write(v2155);	// L3377
    int32_t v2156 = cre_r3;	// L3378
    v2084.write(v2156);	// L3379
    int32_t v2157 = crw_r3;	// L3380
    v2085.write(v2157);	// L3381
    int32_t v2158 = crs_r3;	// L3382
    v2086.write(v2158);	// L3383
    int32_t v2159 = crn_r3;	// L3384
    v2087.write(v2159);	// L3385
    ap_uint<26> v2160 = v2088.read();	// L3386
    ap_uint<26> p_w3;	// L3387
    p_w3 = v2160;	// L3388
    ap_uint<26> v2162 = v2089.read();	// L3389
    ap_uint<26> p_e3;	// L3390
    p_e3 = v2162;	// L3391
    ap_uint<26> v2164 = v2090.read();	// L3392
    ap_uint<26> p_n3;	// L3393
    p_n3 = v2164;	// L3394
    ap_uint<26> v2166 = v2091.read();	// L3395
    ap_uint<26> p_s3;	// L3396
    p_s3 = v2166;	// L3397
    int32_t v2168 = v2092.read();	// L3398
    int32_t v2169 = rcred3[0];	// L3399
    ap_int<33> v2170 = v2169;	// L3400
    ap_int<33> v2171 = v2168;	// L3401
    ap_int<33> v2172 = v2170 + v2171;	// L3402
    int32_t v2173 = v2172;	// L3403
    rcred3[0] = v2173;	// L3404
    int32_t v2174 = v2093.read();	// L3405
    int32_t v2175 = rcred3[1];	// L3406
    ap_int<33> v2176 = v2175;	// L3407
    ap_int<33> v2177 = v2174;	// L3408
    ap_int<33> v2178 = v2176 + v2177;	// L3409
    int32_t v2179 = v2178;	// L3410
    rcred3[1] = v2179;	// L3411
    int32_t v2180 = v2094.read();	// L3412
    int32_t v2181 = rcred3[2];	// L3413
    ap_int<33> v2182 = v2181;	// L3414
    ap_int<33> v2183 = v2180;	// L3415
    ap_int<33> v2184 = v2182 + v2183;	// L3416
    int32_t v2185 = v2184;	// L3417
    rcred3[2] = v2185;	// L3418
    int32_t v2186 = v2095.read();	// L3419
    int32_t v2187 = rcred3[3];	// L3420
    ap_int<33> v2188 = v2187;	// L3421
    ap_int<33> v2189 = v2186;	// L3422
    ap_int<33> v2190 = v2188 + v2189;	// L3423
    int32_t v2191 = v2190;	// L3424
    rcred3[3] = v2191;	// L3425
    ap_uint<26> fin3[4];	// L3426
    for (int v2193 = 0; v2193 < 4; v2193++) {	// L3427
      fin3[v2193] = 0;	// L3427
    }
    ap_int<26> v2194 = p_w3;	// L3428
    fin3[0] = v2194;	// L3429
    ap_int<26> v2195 = p_e3;	// L3430
    fin3[1] = v2195;	// L3431
    ap_int<26> v2196 = p_n3;	// L3432
    fin3[2] = v2196;	// L3433
    ap_int<26> v2197 = p_s3;	// L3434
    fin3[3] = v2197;	// L3435
    l_S_d_0_d12: for (int d12 = 0; d12 < 4; d12++) {	// L3436
      ap_uint<26> v2199 = fin3[d12];	// L3437
      bool v2200;
      ap_int<26> v2200_tmp = v2199;
      v2200 = v2200_tmp[25];	// L3438
      int32_t v2201 = v2200;	// L3439
      bool v2202 = v2201 == 1;	// L3440
      int32_t v2203 = rbcnt3[d12];	// L3441
      bool v2204 = v2203 < 2;	// L3442
      bool v2205 = v2202 & v2204;	// L3443
      if (v2205) {	// L3444
        ap_uint<26> v2206 = fin3[d12];	// L3445
        int32_t v2207 = rbcnt3[d12];	// L3446
        int v2208 = v2207;	// L3447
        rbuf3[d12][v2208] = v2206;	// L3448
        int32_t v2209 = rbcnt3[d12];	// L3449
        ap_int<33> v2210 = v2209;	// L3450
        ap_int<33> v2211 = v2210 + 1;	// L3451
        int32_t v2212 = v2211;	// L3452
        rbcnt3[d12] = v2212;	// L3453
      }
    }
    ap_uint<26> hd3[4];	// L3456
    for (int v2214 = 0; v2214 < 4; v2214++) {	// L3457
      hd3[v2214] = 0;	// L3457
    }
    int32_t hvld3[4];	// L3458
    for (int v2216 = 0; v2216 < 4; v2216++) {	// L3459
      hvld3[v2216] = 0;	// L3459
    }
    int32_t hit3[4];	// L3460
    for (int v2218 = 0; v2218 < 4; v2218++) {	// L3461
      hit3[v2218] = 0;	// L3461
    }
    int32_t axis3[4];	// L3462
    for (int v2220 = 0; v2220 < 4; v2220++) {	// L3463
      axis3[v2220] = 0;	// L3463
    }
    int32_t v2221 = col_id3;	// L3464
    axis3[0] = v2221;	// L3465
    int32_t v2222 = col_id3;	// L3466
    axis3[1] = v2222;	// L3467
    int32_t v2223 = row_id3;	// L3468
    axis3[2] = v2223;	// L3469
    int32_t v2224 = row_id3;	// L3470
    axis3[3] = v2224;	// L3471
    l_S_d_1_d13: for (int d13 = 0; d13 < 4; d13++) {	// L3472
      int32_t v2226 = rbcnt3[d13];	// L3473
      bool v2227 = v2226 > 0;	// L3474
      if (v2227) {	// L3475
        ap_uint<26> v2228 = rbuf3[d13][0];	// L3476
        hd3[d13] = v2228;	// L3477
        hvld3[d13] = 1;	// L3478
        ap_uint<26> v2229 = hd3[d13];	// L3479
        ap_int<4> v2230;
        ap_int<26> v2230_tmp = v2229;
        v2230 = v2230_tmp(24, 21);	// L3480
        int32_t v2231 = axis3[d13];	// L3481
        int32_t v2232 = v2230;	// L3482
        bool v2233 = v2232 == v2231;	// L3483
        if (v2233) {	// L3484
          hit3[d13] = 1;	// L3485
        }
      }
    }
    ap_uint<26> o_crv3;	// L3489
    o_crv3 = 0;	// L3490
    int32_t crv_in3;	// L3491
    crv_in3 = -1;	// L3492
    int32_t v2236 = hit3[3];	// L3493
    bool v2237 = v2236 == 1;	// L3494
    if (v2237) {	// L3495
      ap_uint<26> v2238 = hd3[3];	// L3496
      o_crv3 = v2238;	// L3497
      crv_in3 = 3;	// L3498
    } else {
      int32_t v2239 = hit3[2];	// L3500
      bool v2240 = v2239 == 1;	// L3501
      if (v2240) {	// L3502
        ap_uint<26> v2241 = hd3[2];	// L3503
        o_crv3 = v2241;	// L3504
        crv_in3 = 2;	// L3505
      } else {
        int32_t v2242 = hit3[1];	// L3507
        bool v2243 = v2242 == 1;	// L3508
        if (v2243) {	// L3509
          ap_uint<26> v2244 = hd3[1];	// L3510
          o_crv3 = v2244;	// L3511
          crv_in3 = 1;	// L3512
        } else {
          int32_t v2245 = hit3[0];	// L3514
          bool v2246 = v2245 == 1;	// L3515
          if (v2246) {	// L3516
            ap_uint<26> v2247 = hd3[0];	// L3517
            o_crv3 = v2247;	// L3518
            crv_in3 = 0;	// L3519
          }
        }
      }
    }
    ap_uint<26> o_out3[4];	// L3524
    for (int v2249 = 0; v2249 < 4; v2249++) {	// L3525
      o_out3[v2249] = 0;	// L3525
    }
    int32_t pop3[4];	// L3526
    for (int v2251 = 0; v2251 < 4; v2251++) {	// L3527
      pop3[v2251] = 0;	// L3527
    }
    int32_t inj_done3;	// L3528
    inj_done3 = 0;	// L3529
    int32_t idir3;	// L3530
    idir3 = -1;	// L3531
    ap_int<26> v2254 = csd_pkt3;	// L3532
    bool v2255;
    ap_int<26> v2255_tmp = v2254;
    v2255 = v2255_tmp[25];	// L3533
    int32_t v2256 = v2255;	// L3534
    bool v2257 = v2256 == 1;	// L3535
    if (v2257) {	// L3536
      int32_t v2258 = csd_dir3;	// L3537
      ap_int<33> v2259 = v2258;	// L3538
      ap_int<33> v2260 = 3 - v2259;	// L3539
      int32_t v2261 = v2260;	// L3540
      idir3 = v2261;	// L3541
    }
    l_S_o_2_o3: for (int o3 = 0; o3 < 4; o3++) {	// L3543
      int32_t v2263 = rcred3[o3];	// L3544
      bool v2264 = v2263 > 0;	// L3545
      if (v2264) {	// L3546
        int32_t v2265 = idir3;	// L3547
        ap_int<33> v2266 = v2265;	// L3548
        ap_int<33> v2267 = o3;	// L3549
        bool v2268 = v2266 == v2267;	// L3550
        if (v2268) {	// L3551
          ap_int<26> v2269 = csd_pkt3;	// L3552
          o_out3[o3] = v2269;	// L3553
          int32_t v2270 = rcred3[o3];	// L3554
          ap_int<33> v2271 = v2270;	// L3555
          ap_int<33> v2272 = v2271 - 1;	// L3556
          int32_t v2273 = v2272;	// L3557
          rcred3[o3] = v2273;	// L3558
          inj_done3 = 1;	// L3559
        } else {
          int32_t v2274 = hvld3[o3];	// L3561
          bool v2275 = v2274 == 1;	// L3562
          int32_t v2276 = hit3[o3];	// L3563
          bool v2277 = v2276 == 0;	// L3564
          bool v2278 = v2275 & v2277;	// L3565
          if (v2278) {	// L3566
            ap_uint<26> v2279 = hd3[o3];	// L3567
            o_out3[o3] = v2279;	// L3568
            int32_t v2280 = rcred3[o3];	// L3569
            ap_int<33> v2281 = v2280;	// L3570
            ap_int<33> v2282 = v2281 - 1;	// L3571
            int32_t v2283 = v2282;	// L3572
            rcred3[o3] = v2283;	// L3573
            pop3[o3] = 1;	// L3574
          }
        }
      }
    }
    int32_t v2284 = crv_in3;	// L3579
    bool v2285 = v2284 >= 0;	// L3580
    if (v2285) {	// L3581
      int32_t v2286 = crv_in3;	// L3582
      int v2287 = v2286;	// L3583
      pop3[v2287] = 1;	// L3584
    }
    int32_t ret3[4];	// L3586
    for (int v2289 = 0; v2289 < 4; v2289++) {	// L3587
      ret3[v2289] = 0;	// L3587
    }
    l_S_d_3_d14: for (int d14 = 0; d14 < 4; d14++) {	// L3588
      int32_t v2291 = pop3[d14];	// L3589
      bool v2292 = v2291 == 1;	// L3590
      if (v2292) {	// L3591
        l_S_sft_3_sft3: for (int sft3 = 0; sft3 < 1; sft3++) {	// L3592
          ap_uint<26> v2294 = rbuf3[d14][(sft3 + 1)];	// L3593
          rbuf3[d14][sft3] = v2294;	// L3594
        }
        int32_t v2295 = rbcnt3[d14];	// L3596
        ap_int<33> v2296 = v2295;	// L3597
        ap_int<33> v2297 = v2296 - 1;	// L3598
        int32_t v2298 = v2297;	// L3599
        rbcnt3[d14] = v2298;	// L3600
        ret3[d14] = 1;	// L3601
      }
    }
    int32_t v2299 = ret3[0];	// L3604
    cre_r3 = v2299;	// L3605
    int32_t v2300 = ret3[1];	// L3606
    crw_r3 = v2300;	// L3607
    int32_t v2301 = ret3[2];	// L3608
    crs_r3 = v2301;	// L3609
    int32_t v2302 = ret3[3];	// L3610
    crn_r3 = v2302;	// L3611
    ap_uint<26> v2303 = o_out3[0];	// L3612
    oe_r3 = v2303;	// L3613
    ap_uint<26> v2304 = o_out3[1];	// L3614
    ow_r3 = v2304;	// L3615
    ap_uint<26> v2305 = o_out3[2];	// L3616
    os_r3 = v2305;	// L3617
    ap_uint<26> v2306 = o_out3[3];	// L3618
    on_r3 = v2306;	// L3619
    int32_t v2307 = inj_done3;	// L3620
    bool v2308 = v2307 == 1;	// L3621
    if (v2308) {	// L3622
      csd_pkt3 = 0;	// L3623
    }
    ap_int<26> v2309 = o_crv3;	// L3625
    bool v2310;
    ap_int<26> v2310_tmp = v2309;
    v2310 = v2310_tmp[25];	// L3626
    int32_t v2311 = v2310;	// L3627
    crv_vld3 = v2311;	// L3628
    ap_int<26> v2312 = o_crv3;	// L3629
    int16_t v2313;
    ap_int<26> v2313_tmp = v2312;
    v2313 = v2313_tmp(15, 0);	// L3630
    half v2314;
    union { uint16_t from; half to;} _converter_v2313_to_v2314;
    _converter_v2313_to_v2314.from = v2313;
    v2314 = _converter_v2313_to_v2314.to;	// L3631
    crv_data3 = v2314;	// L3632
    ap_int<26> v2315 = o_crv3;	// L3633
    ap_int<4> v2316;
    ap_int<26> v2316_tmp = v2315;
    v2316 = v2316_tmp(19, 16);	// L3634
    int32_t v2317 = v2316;	// L3635
    crv_addr3 = v2317;	// L3636
    ap_int<26> v2318 = o_crv3;	// L3637
    bool v2319;
    ap_int<26> v2319_tmp = v2318;
    v2319 = v2319_tmp[20];	// L3638
    int32_t v2320 = v2319;	// L3639
    crv_mode3 = v2320;	// L3640
    ap_int<26> v2321 = o_crv3;	// L3641
    int16_t v2322;
    ap_int<26> v2322_tmp = v2321;
    v2322 = v2322_tmp(15, 0);	// L3642
    int32_t v2323 = v2322;	// L3643
    crv_raw3 = v2323;	// L3644
    ap_uint<17> v2324 = v2096.read();	// L3645
    ap_uint<17> rx_w3;	// L3646
    rx_w3 = v2324;	// L3647
    ap_uint<17> v2326 = v2097.read();	// L3648
    ap_uint<17> rx_e3;	// L3649
    rx_e3 = v2326;	// L3650
    ap_uint<17> v2328 = v2098.read();	// L3651
    ap_uint<17> rx_n3;	// L3652
    rx_n3 = v2328;	// L3653
    ap_uint<17> v2330 = v2099.read();	// L3654
    ap_uint<17> rx_s3;	// L3655
    rx_s3 = v2330;	// L3656
    half rxv3[4];	// L3657
    for (int v2333 = 0; v2333 < 4; v2333++) {	// L3658
      rxv3[v2333] = (double)0.000000;	// L3658
    }
    int32_t rxvld3[4];	// L3659
    for (int v2335 = 0; v2335 < 4; v2335++) {	// L3660
      rxvld3[v2335] = 0;	// L3660
    }
    ap_int<17> v2336 = rx_n3;	// L3661
    int16_t v2337;
    ap_int<17> v2337_tmp = v2336;
    v2337 = v2337_tmp(16, 1);	// L3662
    half v2338;
    union { uint16_t from; half to;} _converter_v2337_to_v2338;
    _converter_v2337_to_v2338.from = v2337;
    v2338 = _converter_v2337_to_v2338.to;	// L3663
    rxv3[0] = v2338;	// L3664
    ap_int<17> v2339 = rx_n3;	// L3665
    bool v2340;
    ap_int<17> v2340_tmp = v2339;
    v2340 = v2340_tmp[0];	// L3666
    int32_t v2341 = v2340;	// L3667
    rxvld3[0] = v2341;	// L3668
    ap_int<17> v2342 = rx_s3;	// L3669
    int16_t v2343;
    ap_int<17> v2343_tmp = v2342;
    v2343 = v2343_tmp(16, 1);	// L3670
    half v2344;
    union { uint16_t from; half to;} _converter_v2343_to_v2344;
    _converter_v2343_to_v2344.from = v2343;
    v2344 = _converter_v2343_to_v2344.to;	// L3671
    rxv3[1] = v2344;	// L3672
    ap_int<17> v2345 = rx_s3;	// L3673
    bool v2346;
    ap_int<17> v2346_tmp = v2345;
    v2346 = v2346_tmp[0];	// L3674
    int32_t v2347 = v2346;	// L3675
    rxvld3[1] = v2347;	// L3676
    ap_int<17> v2348 = rx_w3;	// L3677
    int16_t v2349;
    ap_int<17> v2349_tmp = v2348;
    v2349 = v2349_tmp(16, 1);	// L3678
    half v2350;
    union { uint16_t from; half to;} _converter_v2349_to_v2350;
    _converter_v2349_to_v2350.from = v2349;
    v2350 = _converter_v2349_to_v2350.to;	// L3679
    rxv3[2] = v2350;	// L3680
    ap_int<17> v2351 = rx_w3;	// L3681
    bool v2352;
    ap_int<17> v2352_tmp = v2351;
    v2352 = v2352_tmp[0];	// L3682
    int32_t v2353 = v2352;	// L3683
    rxvld3[2] = v2353;	// L3684
    ap_int<17> v2354 = rx_e3;	// L3685
    int16_t v2355;
    ap_int<17> v2355_tmp = v2354;
    v2355 = v2355_tmp(16, 1);	// L3686
    half v2356;
    union { uint16_t from; half to;} _converter_v2355_to_v2356;
    _converter_v2355_to_v2356.from = v2355;
    v2356 = _converter_v2355_to_v2356.to;	// L3687
    rxv3[3] = v2356;	// L3688
    ap_int<17> v2357 = rx_e3;	// L3689
    bool v2358;
    ap_int<17> v2358_tmp = v2357;
    v2358 = v2358_tmp[0];	// L3690
    int32_t v2359 = v2358;	// L3691
    rxvld3[3] = v2359;	// L3692
    l_S_d_5_d15: for (int d15 = 0; d15 < 4; d15++) {	// L3693
      int32_t v2361 = rxvld3[d15];	// L3694
      bool v2362 = v2361 == 1;	// L3695
      int32_t v2363 = hold_cnt3[d15];	// L3696
      bool v2364 = v2363 < 2;	// L3697
      bool v2365 = v2362 & v2364;	// L3698
      if (v2365) {	// L3699
        half v2366 = rxv3[d15];	// L3700
        int32_t v2367 = hold_cnt3[d15];	// L3701
        int v2368 = v2367;	// L3702
        hold_v3[d15][v2368] = v2366;	// L3703
        int32_t v2369 = hold_cnt3[d15];	// L3704
        ap_int<33> v2370 = v2369;	// L3705
        ap_int<33> v2371 = v2370 + 1;	// L3706
        int32_t v2372 = v2371;	// L3707
        hold_cnt3[d15] = v2372;	// L3708
      }
    }
    int32_t pc3;	// L3711
    pc3 = -1;	// L3712
    int32_t v2374 = fetch_en3;	// L3713
    bool v2375 = v2374 == 1;	// L3714
    if (v2375) {	// L3715
      int32_t v2376 = instr_cnt3;	// L3716
      pc3 = v2376;	// L3717
    }
    int32_t instr3;	// L3719
    instr3 = 0;	// L3720
    int32_t v2378 = pc3;	// L3721
    bool v2379 = v2378 >= 0;	// L3722
    if (v2379) {	// L3723
      int32_t v2380 = pc3;	// L3724
      int v2381 = v2380;	// L3725
      int32_t v2382 = irf3[v2381];	// L3726
      instr3 = v2382;	// L3727
    }
    int32_t v2383 = instr3;	// L3729
    int32_t v2384 = v2383 & 15;	// L3730
    int32_t op3;	// L3731
    op3 = v2384;	// L3732
    int32_t v2386 = instr3;	// L3733
    int32_t v2387 = v2386 >> 4;	// L3734
    int32_t v2388 = v2387 & 15;	// L3735
    int32_t dst3;	// L3736
    dst3 = v2388;	// L3737
    int32_t v2390 = instr3;	// L3738
    int32_t v2391 = v2390 >> 8;	// L3739
    int32_t v2392 = v2391 & 15;	// L3740
    int32_t s13;	// L3741
    s13 = v2392;	// L3742
    int32_t v2394 = instr3;	// L3743
    int32_t v2395 = v2394 >> 12;	// L3744
    int32_t v2396 = v2395 & 15;	// L3745
    int32_t s23;	// L3746
    s23 = v2396;	// L3747
    half a3;	// L3748
    a3 = (double)0.000000;	// L3749
    half b3;	// L3750
    b3 = (double)0.000000;	// L3751
    int32_t v2400 = s13;	// L3752
    bool v2401 = v2400 >= 12;	// L3753
    if (v2401) {	// L3754
      int32_t v2402 = s13;	// L3755
      int32_t v2403 = v2402 & 3;	// L3756
      int v2404 = v2403;	// L3757
      half v2405 = hold_v3[v2404][0];	// L3758
      a3 = v2405;	// L3759
    } else {
      int32_t v2406 = s13;	// L3761
      int v2407 = v2406;	// L3762
      half v2408 = drf3[v2407];	// L3763
      a3 = v2408;	// L3764
    }
    int32_t v2409 = s23;	// L3766
    bool v2410 = v2409 >= 12;	// L3767
    if (v2410) {	// L3768
      int32_t v2411 = s23;	// L3769
      int32_t v2412 = v2411 & 3;	// L3770
      int v2413 = v2412;	// L3771
      half v2414 = hold_v3[v2413][0];	// L3772
      b3 = v2414;	// L3773
    } else {
      int32_t v2415 = s23;	// L3775
      int v2416 = v2415;	// L3776
      half v2417 = drf3[v2416];	// L3777
      b3 = v2417;	// L3778
    }
    int32_t a_vld3;	// L3780
    a_vld3 = 1;	// L3781
    int32_t b_vld3;	// L3782
    b_vld3 = 1;	// L3783
    int32_t v2420 = s13;	// L3784
    bool v2421 = v2420 >= 12;	// L3785
    if (v2421) {	// L3786
      a_vld3 = 0;	// L3787
      int32_t v2422 = s13;	// L3788
      int32_t v2423 = v2422 & 3;	// L3789
      int v2424 = v2423;	// L3790
      int32_t v2425 = hold_cnt3[v2424];	// L3791
      bool v2426 = v2425 > 0;	// L3792
      if (v2426) {	// L3793
        a_vld3 = 1;	// L3794
      }
    }
    int32_t v2427 = s23;	// L3797
    bool v2428 = v2427 >= 12;	// L3798
    if (v2428) {	// L3799
      b_vld3 = 0;	// L3800
      int32_t v2429 = s23;	// L3801
      int32_t v2430 = v2429 & 3;	// L3802
      int v2431 = v2430;	// L3803
      int32_t v2432 = hold_cnt3[v2431];	// L3804
      bool v2433 = v2432 > 0;	// L3805
      if (v2433) {	// L3806
        b_vld3 = 1;	// L3807
      }
    }
    int32_t v2434 = s13;	// L3810
    bool v2435 = v2434 < 8;	// L3811
    int32_t v2436 = dsmask3;	// L3812
    int32_t v2437 = v2436 >> v2434;	// L3813
    int32_t v2438 = v2437 & 1;	// L3814
    bool v2439 = v2438 == 1;	// L3815
    bool v2440 = v2435 & v2439;	// L3816
    if (v2440) {	// L3817
      int32_t v2441 = s13;	// L3818
      int v2442 = v2441;	// L3819
      int32_t v2443 = drf_full3[v2442];	// L3820
      bool v2444 = v2443 == 0;	// L3821
      if (v2444) {	// L3822
        a_vld3 = 0;	// L3823
      }
    }
    int32_t v2445 = s23;	// L3826
    bool v2446 = v2445 < 8;	// L3827
    int32_t v2447 = dsmask3;	// L3828
    int32_t v2448 = v2447 >> v2445;	// L3829
    int32_t v2449 = v2448 & 1;	// L3830
    bool v2450 = v2449 == 1;	// L3831
    bool v2451 = v2446 & v2450;	// L3832
    if (v2451) {	// L3833
      int32_t v2452 = s23;	// L3834
      int v2453 = v2452;	// L3835
      int32_t v2454 = drf_full3[v2453];	// L3836
      bool v2455 = v2454 == 0;	// L3837
      if (v2455) {	// L3838
        b_vld3 = 0;	// L3839
      }
    }
    int32_t binop3;	// L3842
    binop3 = 0;	// L3843
    int32_t v2457 = op3;	// L3844
    bool v2458 = v2457 == 0;	// L3845
    bool v2459 = v2457 == 1;	// L3846
    bool v2460 = v2457 == 2;	// L3847
    bool v2461 = v2457 == 8;	// L3848
    bool v2462 = v2457 == 9;	// L3849
    bool v2463 = v2458 | v2459;	// L3850
    bool v2464 = v2463 | v2460;	// L3851
    bool v2465 = v2464 | v2461;	// L3852
    bool v2466 = v2465 | v2462;	// L3853
    if (v2466) {	// L3854
      binop3 = 1;	// L3855
    }
    int32_t grant3;	// L3857
    grant3 = 0;	// L3858
    int32_t v2468 = pc3;	// L3859
    bool v2469 = v2468 >= 0;	// L3860
    if (v2469) {	// L3861
      grant3 = 1;	// L3862
    }
    int32_t v2470 = pc3;	// L3864
    bool v2471 = v2470 >= 0;	// L3865
    int32_t v2472 = a_vld3;	// L3866
    bool v2473 = v2472 == 0;	// L3867
    int32_t v2474 = binop3;	// L3868
    bool v2475 = v2474 == 1;	// L3869
    int32_t v2476 = b_vld3;	// L3870
    bool v2477 = v2476 == 0;	// L3871
    bool v2478 = v2475 & v2477;	// L3872
    bool v2479 = v2473 | v2478;	// L3873
    bool v2480 = v2471 & v2479;	// L3874
    if (v2480) {	// L3875
      grant3 = 0;	// L3876
    }
    int32_t v2481 = grant3;	// L3878
    bool v2482 = v2481 == 1;	// L3879
    if (v2482) {	// L3880
      int32_t v2483 = instr_cnt3;	// L3881
      int32_t v2484 = cfg_isz3;	// L3882
      bool v2485 = v2483 == v2484;	// L3883
      if (v2485) {	// L3884
        instr_cnt3 = 0;	// L3885
        int32_t v2486 = iter_cnt3;	// L3886
        int32_t v2487 = cfg_itsz3;	// L3887
        ap_int<33> v2488 = v2487;	// L3888
        ap_int<33> v2489 = v2488 - 1;	// L3889
        ap_int<33> v2490 = v2486;	// L3890
        bool v2491 = v2490 == v2489;	// L3891
        if (v2491) {	// L3892
          fetch_en3 = 0;	// L3893
        } else {
          int32_t v2492 = iter_cnt3;	// L3895
          ap_int<33> v2493 = v2492;	// L3896
          ap_int<33> v2494 = v2493 + 1;	// L3897
          int32_t v2495 = v2494;	// L3898
          iter_cnt3 = v2495;	// L3899
        }
      } else {
        int32_t v2496 = instr_cnt3;	// L3902
        ap_int<33> v2497 = v2496;	// L3903
        ap_int<33> v2498 = v2497 + 1;	// L3904
        int32_t v2499 = v2498;	// L3905
        instr_cnt3 = v2499;	// L3906
      }
    }
    int32_t c13;	// L3909
    c13 = -1;	// L3910
    int32_t c23;	// L3911
    c23 = -1;	// L3912
    int32_t v2502 = grant3;	// L3913
    bool v2503 = v2502 == 1;	// L3914
    int32_t v2504 = s13;	// L3915
    bool v2505 = v2504 >= 12;	// L3916
    bool v2506 = v2503 & v2505;	// L3917
    if (v2506) {	// L3918
      int32_t v2507 = s13;	// L3919
      int32_t v2508 = v2507 & 3;	// L3920
      c13 = v2508;	// L3921
    }
    int32_t v2509 = grant3;	// L3923
    bool v2510 = v2509 == 1;	// L3924
    int32_t v2511 = s23;	// L3925
    bool v2512 = v2511 >= 12;	// L3926
    bool v2513 = v2510 & v2512;	// L3927
    if (v2513) {	// L3928
      int32_t v2514 = s23;	// L3929
      int32_t v2515 = v2514 & 3;	// L3930
      c23 = v2515;	// L3931
    }
    int32_t v2516 = c13;	// L3933
    bool v2517 = v2516 >= 0;	// L3934
    if (v2517) {	// L3935
      int32_t v2518 = c13;	// L3936
      int v2519 = v2518;	// L3937
      half v2520 = hold_v3[v2519][1];	// L3938
      hold_v3[v2519][0] = v2520;	// L3939
      int32_t v2521 = c13;	// L3940
      int v2522 = v2521;	// L3941
      int32_t v2523 = hold_cnt3[v2522];	// L3942
      ap_int<33> v2524 = v2523;	// L3943
      ap_int<33> v2525 = v2524 - 1;	// L3944
      int32_t v2526 = v2525;	// L3945
      hold_cnt3[v2522] = v2526;	// L3946
    }
    int32_t v2527 = c23;	// L3948
    bool v2528 = v2527 >= 0;	// L3949
    int32_t v2529 = c13;	// L3950
    bool v2530 = v2527 != v2529;	// L3951
    bool v2531 = v2528 & v2530;	// L3952
    if (v2531) {	// L3953
      int32_t v2532 = c23;	// L3954
      int v2533 = v2532;	// L3955
      half v2534 = hold_v3[v2533][1];	// L3956
      hold_v3[v2533][0] = v2534;	// L3957
      int32_t v2535 = c23;	// L3958
      int v2536 = v2535;	// L3959
      int32_t v2537 = hold_cnt3[v2536];	// L3960
      ap_int<33> v2538 = v2537;	// L3961
      ap_int<33> v2539 = v2538 - 1;	// L3962
      int32_t v2540 = v2539;	// L3963
      hold_cnt3[v2536] = v2540;	// L3964
    }
    int32_t v2541 = grant3;	// L3966
    bool v2542 = v2541 == 1;	// L3967
    int32_t v2543 = s13;	// L3968
    bool v2544 = v2543 < 8;	// L3969
    int32_t v2545 = dsmask3;	// L3970
    int32_t v2546 = v2545 >> v2543;	// L3971
    int32_t v2547 = v2546 & 1;	// L3972
    bool v2548 = v2547 == 1;	// L3973
    bool v2549 = v2542 & v2544;	// L3974
    bool v2550 = v2549 & v2548;	// L3975
    if (v2550) {	// L3976
      int32_t v2551 = s13;	// L3977
      int v2552 = v2551;	// L3978
      drf_full3[v2552] = 0;	// L3979
    }
    int32_t v2553 = grant3;	// L3981
    bool v2554 = v2553 == 1;	// L3982
    int32_t v2555 = s23;	// L3983
    bool v2556 = v2555 < 8;	// L3984
    int32_t v2557 = dsmask3;	// L3985
    int32_t v2558 = v2557 >> v2555;	// L3986
    int32_t v2559 = v2558 & 1;	// L3987
    bool v2560 = v2559 == 1;	// L3988
    bool v2561 = v2554 & v2556;	// L3989
    bool v2562 = v2561 & v2560;	// L3990
    if (v2562) {	// L3991
      int32_t v2563 = s23;	// L3992
      int v2564 = v2563;	// L3993
      drf_full3[v2564] = 0;	// L3994
    }
    half res3;	// L3996
    res3 = (double)0.000000;	// L3997
    int32_t v2566 = op3;	// L3998
    bool v2567 = v2566 == 0;	// L3999
    if (v2567) {	// L4000
      half v2568 = a3;	// L4001
      half v2569 = b3;	// L4002
      half v2570 = v2568 + v2569;	// L4003
      res3 = v2570;	// L4004
    } else {
      int32_t v2571 = op3;	// L4006
      bool v2572 = v2571 == 1;	// L4007
      if (v2572) {	// L4008
        half v2573 = a3;	// L4009
        half v2574 = b3;	// L4010
        half v2575 = v2573 - v2574;	// L4011
        res3 = v2575;	// L4012
      } else {
        int32_t v2576 = op3;	// L4014
        bool v2577 = v2576 == 2;	// L4015
        if (v2577) {	// L4016
          half v2578 = a3;	// L4017
          half v2579 = b3;	// L4018
          half v2580 = v2578 * v2579;	// L4019
          res3 = v2580;	// L4020
        } else {
          int32_t v2581 = op3;	// L4022
          bool v2582 = v2581 == 8;	// L4023
          if (v2582) {	// L4024
            half v2583 = a3;	// L4025
            half v2584 = b3;	// L4026
            bool v2585 = v2583 >= v2584;	// L4027
            if (v2585) {	// L4028
              res3 = (double)1.000000;	// L4029
            } else {
              res3 = (double)-1.000000;	// L4031
            }
          } else {
            int32_t v2586 = op3;	// L4034
            bool v2587 = v2586 == 9;	// L4035
            if (v2587) {	// L4036
              half v2588 = a3;	// L4037
              half v2589 = b3;	// L4038
              bool v2590 = v2588 < v2589;	// L4039
              if (v2590) {	// L4040
                res3 = (double)1.000000;	// L4041
              } else {
                res3 = (double)-1.000000;	// L4043
              }
            } else {
              half v2591 = a3;	// L4046
              res3 = v2591;	// L4047
            }
          }
        }
      }
    }
    int32_t v2592 = a_vld3;	// L4053
    int32_t res_vld3;	// L4054
    res_vld3 = v2592;	// L4055
    int32_t v2594 = op3;	// L4056
    bool v2595 = v2594 == 0;	// L4057
    bool v2596 = v2594 == 1;	// L4058
    bool v2597 = v2594 == 2;	// L4059
    bool v2598 = v2594 == 8;	// L4060
    bool v2599 = v2594 == 9;	// L4061
    bool v2600 = v2595 | v2596;	// L4062
    bool v2601 = v2600 | v2597;	// L4063
    bool v2602 = v2601 | v2598;	// L4064
    bool v2603 = v2602 | v2599;	// L4065
    if (v2603) {	// L4066
      int32_t v2604 = a_vld3;	// L4067
      int32_t v2605 = b_vld3;	// L4068
      int64_t v2606 = v2604;	// L4069
      int64_t v2607 = v2605;	// L4070
      int64_t v2608 = v2606 * v2607;	// L4071
      int32_t v2609 = v2608;	// L4072
      res_vld3 = v2609;	// L4073
    }
    int32_t v2610 = grant3;	// L4075
    bool v2611 = v2610 == 0;	// L4076
    if (v2611) {	// L4077
      res_vld3 = 0;	// L4078
    }
    int32_t v2612 = grant3;	// L4080
    bool v2613 = v2612 == 1;	// L4081
    int32_t v2614 = op3;	// L4082
    bool v2615 = v2614 == 8;	// L4083
    bool v2616 = v2613 & v2615;	// L4084
    if (v2616) {	// L4085
      condition_reg3 = 0;	// L4086
      half v2617 = a3;	// L4087
      half v2618 = b3;	// L4088
      bool v2619 = v2617 >= v2618;	// L4089
      if (v2619) {	// L4090
        condition_reg3 = 1;	// L4091
      }
    }
    int32_t v2620 = grant3;	// L4094
    bool v2621 = v2620 == 1;	// L4095
    int32_t v2622 = op3;	// L4096
    bool v2623 = v2622 == 9;	// L4097
    bool v2624 = v2621 & v2623;	// L4098
    if (v2624) {	// L4099
      condition_reg3 = 0;	// L4100
      half v2625 = a3;	// L4101
      half v2626 = b3;	// L4102
      bool v2627 = v2625 < v2626;	// L4103
      if (v2627) {	// L4104
        condition_reg3 = 1;	// L4105
      }
    }
    ap_uint<17> tx_n3;	// L4108
    tx_n3 = 0;	// L4109
    ap_uint<17> tx_s3;	// L4110
    tx_s3 = 0;	// L4111
    ap_uint<17> tx_w3;	// L4112
    tx_w3 = 0;	// L4113
    ap_uint<17> tx_e3;	// L4114
    tx_e3 = 0;	// L4115
    int32_t is_rtr3;	// L4116
    is_rtr3 = 0;	// L4117
    int32_t do_inj3;	// L4118
    do_inj3 = 0;	// L4119
    int32_t v2634 = op3;	// L4120
    bool v2635 = v2634 >= 4;	// L4121
    ap_int<33> v2636 = v2634;	// L4122
    bool v2637 = v2636 <= 7;	// L4123
    bool v2638 = v2635 & v2637;	// L4124
    if (v2638) {	// L4125
      is_rtr3 = 1;	// L4126
      do_inj3 = 1;	// L4127
    }
    int32_t v2639 = op3;	// L4129
    bool v2640 = v2639 >= 12;	// L4130
    ap_int<33> v2641 = v2639;	// L4131
    bool v2642 = v2641 <= 15;	// L4132
    bool v2643 = v2640 & v2642;	// L4133
    if (v2643) {	// L4134
      is_rtr3 = 1;	// L4135
      int32_t v2644 = condition_reg3;	// L4136
      bool v2645 = v2644 == 1;	// L4137
      if (v2645) {	// L4138
        do_inj3 = 1;	// L4139
      }
    }
    int32_t v2646 = is_rtr3;	// L4142
    bool v2647 = v2646 == 1;	// L4143
    if (v2647) {	// L4144
      int32_t v2648 = do_inj3;	// L4145
      bool v2649 = v2648 == 1;	// L4146
      ap_int<26> v2650 = csd_pkt3;	// L4147
      bool v2651;
      ap_int<26> v2651_tmp = v2650;
      v2651 = v2651_tmp[25];	// L4148
      int32_t v2652 = v2651;	// L4149
      bool v2653 = v2652 == 0;	// L4150
      bool v2654 = v2649 & v2653;	// L4151
      if (v2654) {	// L4152
        half v2655 = res3;	// L4153
        uint16_t v2656;
        union { half from; uint16_t to;} _converter_v2655_to_v2656;
        _converter_v2655_to_v2656.from = v2655;
        v2656 = _converter_v2655_to_v2656.to;	// L4154
        ap_int<26> v2657 = csd_pkt3;	// L4155
        ap_int<26> v2658;
        ap_int<26> v2658_tmp = v2657;
        v2658_tmp(15, 0) = v2656;
        v2658 = v2658_tmp;	// L4156
        csd_pkt3 = v2658;	// L4157
        int32_t v2659 = dst3;	// L4158
        ap_uint<4> v2660 = v2659;	// L4159
        ap_int<26> v2661 = csd_pkt3;	// L4160
        ap_int<26> v2662;
        ap_int<26> v2662_tmp = v2661;
        v2662_tmp(19, 16) = v2660;
        v2662 = v2662_tmp;	// L4161
        csd_pkt3 = v2662;	// L4162
        int32_t v2663 = s23;	// L4163
        ap_uint<4> v2664 = v2663;	// L4164
        ap_int<26> v2665 = csd_pkt3;	// L4165
        ap_int<26> v2666;
        ap_int<26> v2666_tmp = v2665;
        v2666_tmp(24, 21) = v2664;
        v2666 = v2666_tmp;	// L4166
        csd_pkt3 = v2666;	// L4167
        int32_t v2667 = res_vld3;	// L4168
        bool v2668 = v2667;	// L4169
        ap_int<26> v2669 = csd_pkt3;	// L4170
        ap_int<26> v2670;
        ap_int<26> v2670_tmp = v2669;
        v2670_tmp[25] = v2668;        v2670 = v2670_tmp;	// L4171
        csd_pkt3 = v2670;	// L4172
        int32_t v2671 = op3;	// L4173
        int32_t v2672 = v2671 & 3;	// L4174
        csd_dir3 = v2672;	// L4175
      }
    } else {
      int32_t v2673 = dst3;	// L4178
      bool v2674 = v2673 >= 12;	// L4179
      if (v2674) {	// L4180
        ap_uint<17> tw3;	// L4181
        tw3 = 0;	// L4182
        int32_t v2676 = res_vld3;	// L4183
        bool v2677 = v2676;	// L4184
        ap_int<17> v2678 = tw3;	// L4185
        ap_int<17> v2679;
        ap_int<17> v2679_tmp = v2678;
        v2679_tmp[0] = v2677;        v2679 = v2679_tmp;	// L4186
        tw3 = v2679;	// L4187
        half v2680 = res3;	// L4188
        uint16_t v2681;
        union { half from; uint16_t to;} _converter_v2680_to_v2681;
        _converter_v2680_to_v2681.from = v2680;
        v2681 = _converter_v2680_to_v2681.to;	// L4189
        ap_int<17> v2682 = tw3;	// L4190
        ap_int<17> v2683;
        ap_int<17> v2683_tmp = v2682;
        v2683_tmp(16, 1) = v2681;
        v2683 = v2683_tmp;	// L4191
        tw3 = v2683;	// L4192
        int32_t v2684 = dst3;	// L4193
        int32_t v2685 = v2684 & 3;	// L4194
        bool v2686 = v2685 == 0;	// L4195
        if (v2686) {	// L4196
          ap_int<17> v2687 = tw3;	// L4197
          tx_n3 = v2687;	// L4198
        } else {
          int32_t v2688 = dst3;	// L4200
          int32_t v2689 = v2688 & 3;	// L4201
          bool v2690 = v2689 == 1;	// L4202
          if (v2690) {	// L4203
            ap_int<17> v2691 = tw3;	// L4204
            tx_s3 = v2691;	// L4205
          } else {
            int32_t v2692 = dst3;	// L4207
            int32_t v2693 = v2692 & 3;	// L4208
            bool v2694 = v2693 == 2;	// L4209
            if (v2694) {	// L4210
              ap_int<17> v2695 = tw3;	// L4211
              tx_w3 = v2695;	// L4212
            } else {
              ap_int<17> v2696 = tw3;	// L4214
              tx_e3 = v2696;	// L4215
            }
          }
        }
      } else {
        int32_t v2697 = res_vld3;	// L4220
        bool v2698 = v2697 == 1;	// L4221
        if (v2698) {	// L4222
          int32_t v2699 = dst3;	// L4223
          bool v2700 = v2699 < 8;	// L4224
          int32_t v2701 = dsmask3;	// L4225
          int32_t v2702 = v2701 >> v2699;	// L4226
          int32_t v2703 = v2702 & 1;	// L4227
          bool v2704 = v2703 == 1;	// L4228
          bool v2705 = v2700 & v2704;	// L4229
          if (v2705) {	// L4230
            int32_t v2706 = dst3;	// L4231
            int v2707 = v2706;	// L4232
            int32_t v2708 = drf_full3[v2707];	// L4233
            bool v2709 = v2708 == 0;	// L4234
            if (v2709) {	// L4235
              half v2710 = res3;	// L4236
              int32_t v2711 = dst3;	// L4237
              int v2712 = v2711;	// L4238
              drf3[v2712] = v2710;	// L4239
              int32_t v2713 = dst3;	// L4240
              int v2714 = v2713;	// L4241
              drf_full3[v2714] = 1;	// L4242
            }
          } else {
            half v2715 = res3;	// L4245
            int32_t v2716 = dst3;	// L4246
            int v2717 = v2716;	// L4247
            drf3[v2717] = v2715;	// L4248
          }
        }
      }
    }
    ap_int<17> v2718 = tx_n3;	// L4253
    txn_r3 = v2718;	// L4254
    ap_int<17> v2719 = tx_s3;	// L4255
    txs_r3 = v2719;	// L4256
    ap_int<17> v2720 = tx_w3;	// L4257
    txw_r3 = v2720;	// L4258
    ap_int<17> v2721 = tx_e3;	// L4259
    txe_r3 = v2721;	// L4260
    int32_t v2722 = crv_vld3;	// L4261
    bool v2723 = v2722 == 1;	// L4262
    if (v2723) {	// L4263
      int32_t v2724 = crv_mode3;	// L4264
      bool v2725 = v2724 == 1;	// L4265
      if (v2725) {	// L4266
        int32_t v2726 = crv_addr3;	// L4267
        int32_t v2727 = v2726 >> 3;	// L4268
        int32_t v2728 = v2727 & 1;	// L4269
        bool v2729 = v2728 == 1;	// L4270
        if (v2729) {	// L4271
          int32_t v2730 = crv_raw3;	// L4272
          int32_t v2731 = crv_addr3;	// L4273
          int32_t v2732 = v2731 & 7;	// L4274
          int v2733 = v2732;	// L4275
          irf3[v2733] = v2730;	// L4276
        } else {
          int32_t v2734 = crv_addr3;	// L4278
          bool v2735 = v2734 == 0;	// L4279
          if (v2735) {	// L4280
            int32_t v2736 = crv_raw3;	// L4281
            int32_t v2737 = v2736 & 255;	// L4282
            dsmask3 = v2737;	// L4283
            int32_t v2738 = crv_raw3;	// L4284
            int32_t v2739 = v2738 >> 8;	// L4285
            int32_t v2740 = v2739 & 7;	// L4286
            cfg_isz3 = v2740;	// L4287
            int32_t v2741 = crv_raw3;	// L4288
            int32_t v2742 = v2741 >> 15;	// L4289
            int32_t v2743 = v2742 & 1;	// L4290
            bool v2744 = v2743 == 1;	// L4291
            if (v2744) {	// L4292
              fetch_en3 = 1;	// L4293
              instr_cnt3 = 0;	// L4294
              iter_cnt3 = 0;	// L4295
            }
          } else {
            int32_t v2745 = crv_addr3;	// L4298
            bool v2746 = v2745 == 1;	// L4299
            if (v2746) {	// L4300
              int32_t v2747 = crv_raw3;	// L4301
              int32_t v2748 = v2747 & 255;	// L4302
              cfg_itsz3 = v2748;	// L4303
            }
          }
        }
      } else {
        int32_t v2749 = crv_addr3;	// L4308
        bool v2750 = v2749 < 8;	// L4309
        int32_t v2751 = dsmask3;	// L4310
        int32_t v2752 = v2751 >> v2749;	// L4311
        int32_t v2753 = v2752 & 1;	// L4312
        bool v2754 = v2753 == 1;	// L4313
        bool v2755 = v2750 & v2754;	// L4314
        if (v2755) {	// L4315
          int32_t v2756 = crv_addr3;	// L4316
          int v2757 = v2756;	// L4317
          int32_t v2758 = drf_full3[v2757];	// L4318
          bool v2759 = v2758 == 0;	// L4319
          if (v2759) {	// L4320
            half v2760 = crv_data3;	// L4321
            int32_t v2761 = crv_addr3;	// L4322
            int v2762 = v2761;	// L4323
            drf3[v2762] = v2760;	// L4324
            int32_t v2763 = crv_addr3;	// L4325
            int v2764 = v2763;	// L4326
            drf_full3[v2764] = 1;	// L4327
          }
        } else {
          half v2765 = crv_data3;	// L4330
          int32_t v2766 = crv_addr3;	// L4331
          int v2767 = v2766;	// L4332
          drf3[v2767] = v2765;	// L4333
        }
      }
    }
  }
}

void node_1_0(
  hls::stream< ap_uint<26> >& v2768,
  hls::stream< ap_uint<26> >& v2769,
  hls::stream< ap_uint<26> >& v2770,
  hls::stream< ap_uint<26> >& v2771,
  hls::stream< ap_uint<17> >& v2772,
  hls::stream< ap_uint<17> >& v2773,
  hls::stream< ap_uint<17> >& v2774,
  hls::stream< ap_uint<17> >& v2775,
  hls::stream< int32_t >& v2776,
  hls::stream< int32_t >& v2777,
  hls::stream< int32_t >& v2778,
  hls::stream< int32_t >& v2779,
  hls::stream< ap_uint<26> >& v2780,
  hls::stream< ap_uint<26> >& v2781,
  hls::stream< ap_uint<26> >& v2782,
  hls::stream< ap_uint<26> >& v2783,
  hls::stream< int32_t >& v2784,
  hls::stream< int32_t >& v2785,
  hls::stream< int32_t >& v2786,
  hls::stream< int32_t >& v2787,
  hls::stream< ap_uint<17> >& v2788,
  hls::stream< ap_uint<17> >& v2789,
  hls::stream< ap_uint<17> >& v2790,
  hls::stream< ap_uint<17> >& v2791
) {	// L4340
  int32_t irf4[8];	// L4371
  for (int v2793 = 0; v2793 < 8; v2793++) {	// L4372
    irf4[v2793] = 0;	// L4372
  }
  half drf4[8];	// L4373
  #pragma HLS array_partition variable=drf4 complete dim=1

  for (int v2795 = 0; v2795 < 8; v2795++) {	// L4374
    drf4[v2795] = (double)0.000000;	// L4374
  }
  int32_t drf_full4[8];	// L4375
  #pragma HLS array_partition variable=drf_full4 complete dim=1

  for (int v2797 = 0; v2797 < 8; v2797++) {	// L4376
    drf_full4[v2797] = 0;	// L4376
  }
  int32_t dsmask4;	// L4377
  dsmask4 = 0;	// L4378
  int32_t crv_vld4;	// L4379
  crv_vld4 = 0;	// L4380
  half crv_data4;	// L4381
  crv_data4 = (double)0.000000;	// L4382
  int32_t crv_addr4;	// L4383
  crv_addr4 = 0;	// L4384
  int32_t crv_mode4;	// L4385
  crv_mode4 = 0;	// L4386
  int32_t crv_raw4;	// L4387
  crv_raw4 = 0;	// L4388
  int32_t csd_vld4;	// L4389
  csd_vld4 = 0;	// L4390
  ap_uint<26> csd_pkt4;	// L4391
  csd_pkt4 = 0;	// L4392
  int32_t csd_dir4;	// L4393
  csd_dir4 = 0;	// L4394
  int32_t row_id4;	// L4395
  row_id4 = 1;	// L4396
  int32_t col_id4;	// L4397
  col_id4 = 0;	// L4398
  ap_uint<26> oe_r4;	// L4399
  oe_r4 = 0;	// L4400
  ap_uint<26> ow_r4;	// L4401
  ow_r4 = 0;	// L4402
  ap_uint<26> on_r4;	// L4403
  on_r4 = 0;	// L4404
  ap_uint<26> os_r4;	// L4405
  os_r4 = 0;	// L4406
  ap_uint<17> txn_r4;	// L4407
  txn_r4 = 0;	// L4408
  ap_uint<17> txs_r4;	// L4409
  txs_r4 = 0;	// L4410
  ap_uint<17> txw_r4;	// L4411
  txw_r4 = 0;	// L4412
  ap_uint<17> txe_r4;	// L4413
  txe_r4 = 0;	// L4414
  half hold_v4[4][2];	// L4415
  #pragma HLS array_partition variable=hold_v4 complete dim=1
  #pragma HLS array_partition variable=hold_v4 complete dim=2

  for (int v2818 = 0; v2818 < 4; v2818++) {	// L4416
    for (int v2819 = 0; v2819 < 2; v2819++) {	// L4416
      hold_v4[v2818][v2819] = (double)0.000000;	// L4416
    }
  }
  int32_t hold_cnt4[4];	// L4417
  #pragma HLS array_partition variable=hold_cnt4 complete dim=1

  for (int v2821 = 0; v2821 < 4; v2821++) {	// L4418
    hold_cnt4[v2821] = 0;	// L4418
  }
  ap_uint<26> rbuf4[4][2];	// L4419
  #pragma HLS array_partition variable=rbuf4 complete dim=1
  #pragma HLS array_partition variable=rbuf4 complete dim=2

  for (int v2823 = 0; v2823 < 4; v2823++) {	// L4420
    for (int v2824 = 0; v2824 < 2; v2824++) {	// L4420
      rbuf4[v2823][v2824] = 0;	// L4420
    }
  }
  int32_t rbcnt4[4];	// L4421
  #pragma HLS array_partition variable=rbcnt4 complete dim=1

  for (int v2826 = 0; v2826 < 4; v2826++) {	// L4422
    rbcnt4[v2826] = 0;	// L4422
  }
  int32_t rcred4[4];	// L4423
  #pragma HLS array_partition variable=rcred4 complete dim=1

  for (int v2828 = 0; v2828 < 4; v2828++) {	// L4424
    rcred4[v2828] = 0;	// L4424
  }
  int32_t cre_r4;	// L4425
  cre_r4 = 2;	// L4426
  int32_t crw_r4;	// L4427
  crw_r4 = 2;	// L4428
  int32_t crs_r4;	// L4429
  crs_r4 = 2;	// L4430
  int32_t crn_r4;	// L4431
  crn_r4 = 2;	// L4432
  int32_t cfg_isz4;	// L4433
  cfg_isz4 = 0;	// L4434
  int32_t cfg_itsz4;	// L4435
  cfg_itsz4 = 0;	// L4436
  int32_t fetch_en4;	// L4437
  fetch_en4 = 0;	// L4438
  int32_t instr_cnt4;	// L4439
  instr_cnt4 = 0;	// L4440
  int32_t iter_cnt4;	// L4441
  iter_cnt4 = 0;	// L4442
  int32_t condition_reg4;	// L4443
  condition_reg4 = 0;	// L4444
  l_S_t_0_t4: for (int t4 = 0; t4 < 8; t4++) {	// L4445
  #pragma HLS pipeline II=1
    ap_int<26> v2840 = oe_r4;	// L4446
    v2768.write(v2840);	// L4447
    ap_int<26> v2841 = ow_r4;	// L4448
    v2769.write(v2841);	// L4449
    ap_int<26> v2842 = os_r4;	// L4450
    v2770.write(v2842);	// L4451
    ap_int<26> v2843 = on_r4;	// L4452
    v2771.write(v2843);	// L4453
    ap_int<17> v2844 = txe_r4;	// L4454
    v2772.write(v2844);	// L4455
    ap_int<17> v2845 = txw_r4;	// L4456
    v2773.write(v2845);	// L4457
    ap_int<17> v2846 = txs_r4;	// L4458
    v2774.write(v2846);	// L4459
    ap_int<17> v2847 = txn_r4;	// L4460
    v2775.write(v2847);	// L4461
    int32_t v2848 = cre_r4;	// L4462
    v2776.write(v2848);	// L4463
    int32_t v2849 = crw_r4;	// L4464
    v2777.write(v2849);	// L4465
    int32_t v2850 = crs_r4;	// L4466
    v2778.write(v2850);	// L4467
    int32_t v2851 = crn_r4;	// L4468
    v2779.write(v2851);	// L4469
    ap_uint<26> v2852 = v2780.read();	// L4470
    ap_uint<26> p_w4;	// L4471
    p_w4 = v2852;	// L4472
    ap_uint<26> v2854 = v2781.read();	// L4473
    ap_uint<26> p_e4;	// L4474
    p_e4 = v2854;	// L4475
    ap_uint<26> v2856 = v2782.read();	// L4476
    ap_uint<26> p_n4;	// L4477
    p_n4 = v2856;	// L4478
    ap_uint<26> v2858 = v2783.read();	// L4479
    ap_uint<26> p_s4;	// L4480
    p_s4 = v2858;	// L4481
    int32_t v2860 = v2784.read();	// L4482
    int32_t v2861 = rcred4[0];	// L4483
    ap_int<33> v2862 = v2861;	// L4484
    ap_int<33> v2863 = v2860;	// L4485
    ap_int<33> v2864 = v2862 + v2863;	// L4486
    int32_t v2865 = v2864;	// L4487
    rcred4[0] = v2865;	// L4488
    int32_t v2866 = v2785.read();	// L4489
    int32_t v2867 = rcred4[1];	// L4490
    ap_int<33> v2868 = v2867;	// L4491
    ap_int<33> v2869 = v2866;	// L4492
    ap_int<33> v2870 = v2868 + v2869;	// L4493
    int32_t v2871 = v2870;	// L4494
    rcred4[1] = v2871;	// L4495
    int32_t v2872 = v2786.read();	// L4496
    int32_t v2873 = rcred4[2];	// L4497
    ap_int<33> v2874 = v2873;	// L4498
    ap_int<33> v2875 = v2872;	// L4499
    ap_int<33> v2876 = v2874 + v2875;	// L4500
    int32_t v2877 = v2876;	// L4501
    rcred4[2] = v2877;	// L4502
    int32_t v2878 = v2787.read();	// L4503
    int32_t v2879 = rcred4[3];	// L4504
    ap_int<33> v2880 = v2879;	// L4505
    ap_int<33> v2881 = v2878;	// L4506
    ap_int<33> v2882 = v2880 + v2881;	// L4507
    int32_t v2883 = v2882;	// L4508
    rcred4[3] = v2883;	// L4509
    ap_uint<26> fin4[4];	// L4510
    for (int v2885 = 0; v2885 < 4; v2885++) {	// L4511
      fin4[v2885] = 0;	// L4511
    }
    ap_int<26> v2886 = p_w4;	// L4512
    fin4[0] = v2886;	// L4513
    ap_int<26> v2887 = p_e4;	// L4514
    fin4[1] = v2887;	// L4515
    ap_int<26> v2888 = p_n4;	// L4516
    fin4[2] = v2888;	// L4517
    ap_int<26> v2889 = p_s4;	// L4518
    fin4[3] = v2889;	// L4519
    l_S_d_0_d16: for (int d16 = 0; d16 < 4; d16++) {	// L4520
      ap_uint<26> v2891 = fin4[d16];	// L4521
      bool v2892;
      ap_int<26> v2892_tmp = v2891;
      v2892 = v2892_tmp[25];	// L4522
      int32_t v2893 = v2892;	// L4523
      bool v2894 = v2893 == 1;	// L4524
      int32_t v2895 = rbcnt4[d16];	// L4525
      bool v2896 = v2895 < 2;	// L4526
      bool v2897 = v2894 & v2896;	// L4527
      if (v2897) {	// L4528
        ap_uint<26> v2898 = fin4[d16];	// L4529
        int32_t v2899 = rbcnt4[d16];	// L4530
        int v2900 = v2899;	// L4531
        rbuf4[d16][v2900] = v2898;	// L4532
        int32_t v2901 = rbcnt4[d16];	// L4533
        ap_int<33> v2902 = v2901;	// L4534
        ap_int<33> v2903 = v2902 + 1;	// L4535
        int32_t v2904 = v2903;	// L4536
        rbcnt4[d16] = v2904;	// L4537
      }
    }
    ap_uint<26> hd4[4];	// L4540
    for (int v2906 = 0; v2906 < 4; v2906++) {	// L4541
      hd4[v2906] = 0;	// L4541
    }
    int32_t hvld4[4];	// L4542
    for (int v2908 = 0; v2908 < 4; v2908++) {	// L4543
      hvld4[v2908] = 0;	// L4543
    }
    int32_t hit4[4];	// L4544
    for (int v2910 = 0; v2910 < 4; v2910++) {	// L4545
      hit4[v2910] = 0;	// L4545
    }
    int32_t axis4[4];	// L4546
    for (int v2912 = 0; v2912 < 4; v2912++) {	// L4547
      axis4[v2912] = 0;	// L4547
    }
    int32_t v2913 = col_id4;	// L4548
    axis4[0] = v2913;	// L4549
    int32_t v2914 = col_id4;	// L4550
    axis4[1] = v2914;	// L4551
    int32_t v2915 = row_id4;	// L4552
    axis4[2] = v2915;	// L4553
    int32_t v2916 = row_id4;	// L4554
    axis4[3] = v2916;	// L4555
    l_S_d_1_d17: for (int d17 = 0; d17 < 4; d17++) {	// L4556
      int32_t v2918 = rbcnt4[d17];	// L4557
      bool v2919 = v2918 > 0;	// L4558
      if (v2919) {	// L4559
        ap_uint<26> v2920 = rbuf4[d17][0];	// L4560
        hd4[d17] = v2920;	// L4561
        hvld4[d17] = 1;	// L4562
        ap_uint<26> v2921 = hd4[d17];	// L4563
        ap_int<4> v2922;
        ap_int<26> v2922_tmp = v2921;
        v2922 = v2922_tmp(24, 21);	// L4564
        int32_t v2923 = axis4[d17];	// L4565
        int32_t v2924 = v2922;	// L4566
        bool v2925 = v2924 == v2923;	// L4567
        if (v2925) {	// L4568
          hit4[d17] = 1;	// L4569
        }
      }
    }
    ap_uint<26> o_crv4;	// L4573
    o_crv4 = 0;	// L4574
    int32_t crv_in4;	// L4575
    crv_in4 = -1;	// L4576
    int32_t v2928 = hit4[3];	// L4577
    bool v2929 = v2928 == 1;	// L4578
    if (v2929) {	// L4579
      ap_uint<26> v2930 = hd4[3];	// L4580
      o_crv4 = v2930;	// L4581
      crv_in4 = 3;	// L4582
    } else {
      int32_t v2931 = hit4[2];	// L4584
      bool v2932 = v2931 == 1;	// L4585
      if (v2932) {	// L4586
        ap_uint<26> v2933 = hd4[2];	// L4587
        o_crv4 = v2933;	// L4588
        crv_in4 = 2;	// L4589
      } else {
        int32_t v2934 = hit4[1];	// L4591
        bool v2935 = v2934 == 1;	// L4592
        if (v2935) {	// L4593
          ap_uint<26> v2936 = hd4[1];	// L4594
          o_crv4 = v2936;	// L4595
          crv_in4 = 1;	// L4596
        } else {
          int32_t v2937 = hit4[0];	// L4598
          bool v2938 = v2937 == 1;	// L4599
          if (v2938) {	// L4600
            ap_uint<26> v2939 = hd4[0];	// L4601
            o_crv4 = v2939;	// L4602
            crv_in4 = 0;	// L4603
          }
        }
      }
    }
    ap_uint<26> o_out4[4];	// L4608
    for (int v2941 = 0; v2941 < 4; v2941++) {	// L4609
      o_out4[v2941] = 0;	// L4609
    }
    int32_t pop4[4];	// L4610
    for (int v2943 = 0; v2943 < 4; v2943++) {	// L4611
      pop4[v2943] = 0;	// L4611
    }
    int32_t inj_done4;	// L4612
    inj_done4 = 0;	// L4613
    int32_t idir4;	// L4614
    idir4 = -1;	// L4615
    ap_int<26> v2946 = csd_pkt4;	// L4616
    bool v2947;
    ap_int<26> v2947_tmp = v2946;
    v2947 = v2947_tmp[25];	// L4617
    int32_t v2948 = v2947;	// L4618
    bool v2949 = v2948 == 1;	// L4619
    if (v2949) {	// L4620
      int32_t v2950 = csd_dir4;	// L4621
      ap_int<33> v2951 = v2950;	// L4622
      ap_int<33> v2952 = 3 - v2951;	// L4623
      int32_t v2953 = v2952;	// L4624
      idir4 = v2953;	// L4625
    }
    l_S_o_2_o4: for (int o4 = 0; o4 < 4; o4++) {	// L4627
      int32_t v2955 = rcred4[o4];	// L4628
      bool v2956 = v2955 > 0;	// L4629
      if (v2956) {	// L4630
        int32_t v2957 = idir4;	// L4631
        ap_int<33> v2958 = v2957;	// L4632
        ap_int<33> v2959 = o4;	// L4633
        bool v2960 = v2958 == v2959;	// L4634
        if (v2960) {	// L4635
          ap_int<26> v2961 = csd_pkt4;	// L4636
          o_out4[o4] = v2961;	// L4637
          int32_t v2962 = rcred4[o4];	// L4638
          ap_int<33> v2963 = v2962;	// L4639
          ap_int<33> v2964 = v2963 - 1;	// L4640
          int32_t v2965 = v2964;	// L4641
          rcred4[o4] = v2965;	// L4642
          inj_done4 = 1;	// L4643
        } else {
          int32_t v2966 = hvld4[o4];	// L4645
          bool v2967 = v2966 == 1;	// L4646
          int32_t v2968 = hit4[o4];	// L4647
          bool v2969 = v2968 == 0;	// L4648
          bool v2970 = v2967 & v2969;	// L4649
          if (v2970) {	// L4650
            ap_uint<26> v2971 = hd4[o4];	// L4651
            o_out4[o4] = v2971;	// L4652
            int32_t v2972 = rcred4[o4];	// L4653
            ap_int<33> v2973 = v2972;	// L4654
            ap_int<33> v2974 = v2973 - 1;	// L4655
            int32_t v2975 = v2974;	// L4656
            rcred4[o4] = v2975;	// L4657
            pop4[o4] = 1;	// L4658
          }
        }
      }
    }
    int32_t v2976 = crv_in4;	// L4663
    bool v2977 = v2976 >= 0;	// L4664
    if (v2977) {	// L4665
      int32_t v2978 = crv_in4;	// L4666
      int v2979 = v2978;	// L4667
      pop4[v2979] = 1;	// L4668
    }
    int32_t ret4[4];	// L4670
    for (int v2981 = 0; v2981 < 4; v2981++) {	// L4671
      ret4[v2981] = 0;	// L4671
    }
    l_S_d_3_d18: for (int d18 = 0; d18 < 4; d18++) {	// L4672
      int32_t v2983 = pop4[d18];	// L4673
      bool v2984 = v2983 == 1;	// L4674
      if (v2984) {	// L4675
        l_S_sft_3_sft4: for (int sft4 = 0; sft4 < 1; sft4++) {	// L4676
          ap_uint<26> v2986 = rbuf4[d18][(sft4 + 1)];	// L4677
          rbuf4[d18][sft4] = v2986;	// L4678
        }
        int32_t v2987 = rbcnt4[d18];	// L4680
        ap_int<33> v2988 = v2987;	// L4681
        ap_int<33> v2989 = v2988 - 1;	// L4682
        int32_t v2990 = v2989;	// L4683
        rbcnt4[d18] = v2990;	// L4684
        ret4[d18] = 1;	// L4685
      }
    }
    int32_t v2991 = ret4[0];	// L4688
    cre_r4 = v2991;	// L4689
    int32_t v2992 = ret4[1];	// L4690
    crw_r4 = v2992;	// L4691
    int32_t v2993 = ret4[2];	// L4692
    crs_r4 = v2993;	// L4693
    int32_t v2994 = ret4[3];	// L4694
    crn_r4 = v2994;	// L4695
    ap_uint<26> v2995 = o_out4[0];	// L4696
    oe_r4 = v2995;	// L4697
    ap_uint<26> v2996 = o_out4[1];	// L4698
    ow_r4 = v2996;	// L4699
    ap_uint<26> v2997 = o_out4[2];	// L4700
    os_r4 = v2997;	// L4701
    ap_uint<26> v2998 = o_out4[3];	// L4702
    on_r4 = v2998;	// L4703
    int32_t v2999 = inj_done4;	// L4704
    bool v3000 = v2999 == 1;	// L4705
    if (v3000) {	// L4706
      csd_pkt4 = 0;	// L4707
    }
    ap_int<26> v3001 = o_crv4;	// L4709
    bool v3002;
    ap_int<26> v3002_tmp = v3001;
    v3002 = v3002_tmp[25];	// L4710
    int32_t v3003 = v3002;	// L4711
    crv_vld4 = v3003;	// L4712
    ap_int<26> v3004 = o_crv4;	// L4713
    int16_t v3005;
    ap_int<26> v3005_tmp = v3004;
    v3005 = v3005_tmp(15, 0);	// L4714
    half v3006;
    union { uint16_t from; half to;} _converter_v3005_to_v3006;
    _converter_v3005_to_v3006.from = v3005;
    v3006 = _converter_v3005_to_v3006.to;	// L4715
    crv_data4 = v3006;	// L4716
    ap_int<26> v3007 = o_crv4;	// L4717
    ap_int<4> v3008;
    ap_int<26> v3008_tmp = v3007;
    v3008 = v3008_tmp(19, 16);	// L4718
    int32_t v3009 = v3008;	// L4719
    crv_addr4 = v3009;	// L4720
    ap_int<26> v3010 = o_crv4;	// L4721
    bool v3011;
    ap_int<26> v3011_tmp = v3010;
    v3011 = v3011_tmp[20];	// L4722
    int32_t v3012 = v3011;	// L4723
    crv_mode4 = v3012;	// L4724
    ap_int<26> v3013 = o_crv4;	// L4725
    int16_t v3014;
    ap_int<26> v3014_tmp = v3013;
    v3014 = v3014_tmp(15, 0);	// L4726
    int32_t v3015 = v3014;	// L4727
    crv_raw4 = v3015;	// L4728
    ap_uint<17> v3016 = v2788.read();	// L4729
    ap_uint<17> rx_w4;	// L4730
    rx_w4 = v3016;	// L4731
    ap_uint<17> v3018 = v2789.read();	// L4732
    ap_uint<17> rx_e4;	// L4733
    rx_e4 = v3018;	// L4734
    ap_uint<17> v3020 = v2790.read();	// L4735
    ap_uint<17> rx_n4;	// L4736
    rx_n4 = v3020;	// L4737
    ap_uint<17> v3022 = v2791.read();	// L4738
    ap_uint<17> rx_s4;	// L4739
    rx_s4 = v3022;	// L4740
    half rxv4[4];	// L4741
    for (int v3025 = 0; v3025 < 4; v3025++) {	// L4742
      rxv4[v3025] = (double)0.000000;	// L4742
    }
    int32_t rxvld4[4];	// L4743
    for (int v3027 = 0; v3027 < 4; v3027++) {	// L4744
      rxvld4[v3027] = 0;	// L4744
    }
    ap_int<17> v3028 = rx_n4;	// L4745
    int16_t v3029;
    ap_int<17> v3029_tmp = v3028;
    v3029 = v3029_tmp(16, 1);	// L4746
    half v3030;
    union { uint16_t from; half to;} _converter_v3029_to_v3030;
    _converter_v3029_to_v3030.from = v3029;
    v3030 = _converter_v3029_to_v3030.to;	// L4747
    rxv4[0] = v3030;	// L4748
    ap_int<17> v3031 = rx_n4;	// L4749
    bool v3032;
    ap_int<17> v3032_tmp = v3031;
    v3032 = v3032_tmp[0];	// L4750
    int32_t v3033 = v3032;	// L4751
    rxvld4[0] = v3033;	// L4752
    ap_int<17> v3034 = rx_s4;	// L4753
    int16_t v3035;
    ap_int<17> v3035_tmp = v3034;
    v3035 = v3035_tmp(16, 1);	// L4754
    half v3036;
    union { uint16_t from; half to;} _converter_v3035_to_v3036;
    _converter_v3035_to_v3036.from = v3035;
    v3036 = _converter_v3035_to_v3036.to;	// L4755
    rxv4[1] = v3036;	// L4756
    ap_int<17> v3037 = rx_s4;	// L4757
    bool v3038;
    ap_int<17> v3038_tmp = v3037;
    v3038 = v3038_tmp[0];	// L4758
    int32_t v3039 = v3038;	// L4759
    rxvld4[1] = v3039;	// L4760
    ap_int<17> v3040 = rx_w4;	// L4761
    int16_t v3041;
    ap_int<17> v3041_tmp = v3040;
    v3041 = v3041_tmp(16, 1);	// L4762
    half v3042;
    union { uint16_t from; half to;} _converter_v3041_to_v3042;
    _converter_v3041_to_v3042.from = v3041;
    v3042 = _converter_v3041_to_v3042.to;	// L4763
    rxv4[2] = v3042;	// L4764
    ap_int<17> v3043 = rx_w4;	// L4765
    bool v3044;
    ap_int<17> v3044_tmp = v3043;
    v3044 = v3044_tmp[0];	// L4766
    int32_t v3045 = v3044;	// L4767
    rxvld4[2] = v3045;	// L4768
    ap_int<17> v3046 = rx_e4;	// L4769
    int16_t v3047;
    ap_int<17> v3047_tmp = v3046;
    v3047 = v3047_tmp(16, 1);	// L4770
    half v3048;
    union { uint16_t from; half to;} _converter_v3047_to_v3048;
    _converter_v3047_to_v3048.from = v3047;
    v3048 = _converter_v3047_to_v3048.to;	// L4771
    rxv4[3] = v3048;	// L4772
    ap_int<17> v3049 = rx_e4;	// L4773
    bool v3050;
    ap_int<17> v3050_tmp = v3049;
    v3050 = v3050_tmp[0];	// L4774
    int32_t v3051 = v3050;	// L4775
    rxvld4[3] = v3051;	// L4776
    l_S_d_5_d19: for (int d19 = 0; d19 < 4; d19++) {	// L4777
      int32_t v3053 = rxvld4[d19];	// L4778
      bool v3054 = v3053 == 1;	// L4779
      int32_t v3055 = hold_cnt4[d19];	// L4780
      bool v3056 = v3055 < 2;	// L4781
      bool v3057 = v3054 & v3056;	// L4782
      if (v3057) {	// L4783
        half v3058 = rxv4[d19];	// L4784
        int32_t v3059 = hold_cnt4[d19];	// L4785
        int v3060 = v3059;	// L4786
        hold_v4[d19][v3060] = v3058;	// L4787
        int32_t v3061 = hold_cnt4[d19];	// L4788
        ap_int<33> v3062 = v3061;	// L4789
        ap_int<33> v3063 = v3062 + 1;	// L4790
        int32_t v3064 = v3063;	// L4791
        hold_cnt4[d19] = v3064;	// L4792
      }
    }
    int32_t pc4;	// L4795
    pc4 = -1;	// L4796
    int32_t v3066 = fetch_en4;	// L4797
    bool v3067 = v3066 == 1;	// L4798
    if (v3067) {	// L4799
      int32_t v3068 = instr_cnt4;	// L4800
      pc4 = v3068;	// L4801
    }
    int32_t instr4;	// L4803
    instr4 = 0;	// L4804
    int32_t v3070 = pc4;	// L4805
    bool v3071 = v3070 >= 0;	// L4806
    if (v3071) {	// L4807
      int32_t v3072 = pc4;	// L4808
      int v3073 = v3072;	// L4809
      int32_t v3074 = irf4[v3073];	// L4810
      instr4 = v3074;	// L4811
    }
    int32_t v3075 = instr4;	// L4813
    int32_t v3076 = v3075 & 15;	// L4814
    int32_t op4;	// L4815
    op4 = v3076;	// L4816
    int32_t v3078 = instr4;	// L4817
    int32_t v3079 = v3078 >> 4;	// L4818
    int32_t v3080 = v3079 & 15;	// L4819
    int32_t dst4;	// L4820
    dst4 = v3080;	// L4821
    int32_t v3082 = instr4;	// L4822
    int32_t v3083 = v3082 >> 8;	// L4823
    int32_t v3084 = v3083 & 15;	// L4824
    int32_t s14;	// L4825
    s14 = v3084;	// L4826
    int32_t v3086 = instr4;	// L4827
    int32_t v3087 = v3086 >> 12;	// L4828
    int32_t v3088 = v3087 & 15;	// L4829
    int32_t s24;	// L4830
    s24 = v3088;	// L4831
    half a4;	// L4832
    a4 = (double)0.000000;	// L4833
    half b4;	// L4834
    b4 = (double)0.000000;	// L4835
    int32_t v3092 = s14;	// L4836
    bool v3093 = v3092 >= 12;	// L4837
    if (v3093) {	// L4838
      int32_t v3094 = s14;	// L4839
      int32_t v3095 = v3094 & 3;	// L4840
      int v3096 = v3095;	// L4841
      half v3097 = hold_v4[v3096][0];	// L4842
      a4 = v3097;	// L4843
    } else {
      int32_t v3098 = s14;	// L4845
      int v3099 = v3098;	// L4846
      half v3100 = drf4[v3099];	// L4847
      a4 = v3100;	// L4848
    }
    int32_t v3101 = s24;	// L4850
    bool v3102 = v3101 >= 12;	// L4851
    if (v3102) {	// L4852
      int32_t v3103 = s24;	// L4853
      int32_t v3104 = v3103 & 3;	// L4854
      int v3105 = v3104;	// L4855
      half v3106 = hold_v4[v3105][0];	// L4856
      b4 = v3106;	// L4857
    } else {
      int32_t v3107 = s24;	// L4859
      int v3108 = v3107;	// L4860
      half v3109 = drf4[v3108];	// L4861
      b4 = v3109;	// L4862
    }
    int32_t a_vld4;	// L4864
    a_vld4 = 1;	// L4865
    int32_t b_vld4;	// L4866
    b_vld4 = 1;	// L4867
    int32_t v3112 = s14;	// L4868
    bool v3113 = v3112 >= 12;	// L4869
    if (v3113) {	// L4870
      a_vld4 = 0;	// L4871
      int32_t v3114 = s14;	// L4872
      int32_t v3115 = v3114 & 3;	// L4873
      int v3116 = v3115;	// L4874
      int32_t v3117 = hold_cnt4[v3116];	// L4875
      bool v3118 = v3117 > 0;	// L4876
      if (v3118) {	// L4877
        a_vld4 = 1;	// L4878
      }
    }
    int32_t v3119 = s24;	// L4881
    bool v3120 = v3119 >= 12;	// L4882
    if (v3120) {	// L4883
      b_vld4 = 0;	// L4884
      int32_t v3121 = s24;	// L4885
      int32_t v3122 = v3121 & 3;	// L4886
      int v3123 = v3122;	// L4887
      int32_t v3124 = hold_cnt4[v3123];	// L4888
      bool v3125 = v3124 > 0;	// L4889
      if (v3125) {	// L4890
        b_vld4 = 1;	// L4891
      }
    }
    int32_t v3126 = s14;	// L4894
    bool v3127 = v3126 < 8;	// L4895
    int32_t v3128 = dsmask4;	// L4896
    int32_t v3129 = v3128 >> v3126;	// L4897
    int32_t v3130 = v3129 & 1;	// L4898
    bool v3131 = v3130 == 1;	// L4899
    bool v3132 = v3127 & v3131;	// L4900
    if (v3132) {	// L4901
      int32_t v3133 = s14;	// L4902
      int v3134 = v3133;	// L4903
      int32_t v3135 = drf_full4[v3134];	// L4904
      bool v3136 = v3135 == 0;	// L4905
      if (v3136) {	// L4906
        a_vld4 = 0;	// L4907
      }
    }
    int32_t v3137 = s24;	// L4910
    bool v3138 = v3137 < 8;	// L4911
    int32_t v3139 = dsmask4;	// L4912
    int32_t v3140 = v3139 >> v3137;	// L4913
    int32_t v3141 = v3140 & 1;	// L4914
    bool v3142 = v3141 == 1;	// L4915
    bool v3143 = v3138 & v3142;	// L4916
    if (v3143) {	// L4917
      int32_t v3144 = s24;	// L4918
      int v3145 = v3144;	// L4919
      int32_t v3146 = drf_full4[v3145];	// L4920
      bool v3147 = v3146 == 0;	// L4921
      if (v3147) {	// L4922
        b_vld4 = 0;	// L4923
      }
    }
    int32_t binop4;	// L4926
    binop4 = 0;	// L4927
    int32_t v3149 = op4;	// L4928
    bool v3150 = v3149 == 0;	// L4929
    bool v3151 = v3149 == 1;	// L4930
    bool v3152 = v3149 == 2;	// L4931
    bool v3153 = v3149 == 8;	// L4932
    bool v3154 = v3149 == 9;	// L4933
    bool v3155 = v3150 | v3151;	// L4934
    bool v3156 = v3155 | v3152;	// L4935
    bool v3157 = v3156 | v3153;	// L4936
    bool v3158 = v3157 | v3154;	// L4937
    if (v3158) {	// L4938
      binop4 = 1;	// L4939
    }
    int32_t grant4;	// L4941
    grant4 = 0;	// L4942
    int32_t v3160 = pc4;	// L4943
    bool v3161 = v3160 >= 0;	// L4944
    if (v3161) {	// L4945
      grant4 = 1;	// L4946
    }
    int32_t v3162 = pc4;	// L4948
    bool v3163 = v3162 >= 0;	// L4949
    int32_t v3164 = a_vld4;	// L4950
    bool v3165 = v3164 == 0;	// L4951
    int32_t v3166 = binop4;	// L4952
    bool v3167 = v3166 == 1;	// L4953
    int32_t v3168 = b_vld4;	// L4954
    bool v3169 = v3168 == 0;	// L4955
    bool v3170 = v3167 & v3169;	// L4956
    bool v3171 = v3165 | v3170;	// L4957
    bool v3172 = v3163 & v3171;	// L4958
    if (v3172) {	// L4959
      grant4 = 0;	// L4960
    }
    int32_t v3173 = grant4;	// L4962
    bool v3174 = v3173 == 1;	// L4963
    if (v3174) {	// L4964
      int32_t v3175 = instr_cnt4;	// L4965
      int32_t v3176 = cfg_isz4;	// L4966
      bool v3177 = v3175 == v3176;	// L4967
      if (v3177) {	// L4968
        instr_cnt4 = 0;	// L4969
        int32_t v3178 = iter_cnt4;	// L4970
        int32_t v3179 = cfg_itsz4;	// L4971
        ap_int<33> v3180 = v3179;	// L4972
        ap_int<33> v3181 = v3180 - 1;	// L4973
        ap_int<33> v3182 = v3178;	// L4974
        bool v3183 = v3182 == v3181;	// L4975
        if (v3183) {	// L4976
          fetch_en4 = 0;	// L4977
        } else {
          int32_t v3184 = iter_cnt4;	// L4979
          ap_int<33> v3185 = v3184;	// L4980
          ap_int<33> v3186 = v3185 + 1;	// L4981
          int32_t v3187 = v3186;	// L4982
          iter_cnt4 = v3187;	// L4983
        }
      } else {
        int32_t v3188 = instr_cnt4;	// L4986
        ap_int<33> v3189 = v3188;	// L4987
        ap_int<33> v3190 = v3189 + 1;	// L4988
        int32_t v3191 = v3190;	// L4989
        instr_cnt4 = v3191;	// L4990
      }
    }
    int32_t c14;	// L4993
    c14 = -1;	// L4994
    int32_t c24;	// L4995
    c24 = -1;	// L4996
    int32_t v3194 = grant4;	// L4997
    bool v3195 = v3194 == 1;	// L4998
    int32_t v3196 = s14;	// L4999
    bool v3197 = v3196 >= 12;	// L5000
    bool v3198 = v3195 & v3197;	// L5001
    if (v3198) {	// L5002
      int32_t v3199 = s14;	// L5003
      int32_t v3200 = v3199 & 3;	// L5004
      c14 = v3200;	// L5005
    }
    int32_t v3201 = grant4;	// L5007
    bool v3202 = v3201 == 1;	// L5008
    int32_t v3203 = s24;	// L5009
    bool v3204 = v3203 >= 12;	// L5010
    bool v3205 = v3202 & v3204;	// L5011
    if (v3205) {	// L5012
      int32_t v3206 = s24;	// L5013
      int32_t v3207 = v3206 & 3;	// L5014
      c24 = v3207;	// L5015
    }
    int32_t v3208 = c14;	// L5017
    bool v3209 = v3208 >= 0;	// L5018
    if (v3209) {	// L5019
      int32_t v3210 = c14;	// L5020
      int v3211 = v3210;	// L5021
      half v3212 = hold_v4[v3211][1];	// L5022
      hold_v4[v3211][0] = v3212;	// L5023
      int32_t v3213 = c14;	// L5024
      int v3214 = v3213;	// L5025
      int32_t v3215 = hold_cnt4[v3214];	// L5026
      ap_int<33> v3216 = v3215;	// L5027
      ap_int<33> v3217 = v3216 - 1;	// L5028
      int32_t v3218 = v3217;	// L5029
      hold_cnt4[v3214] = v3218;	// L5030
    }
    int32_t v3219 = c24;	// L5032
    bool v3220 = v3219 >= 0;	// L5033
    int32_t v3221 = c14;	// L5034
    bool v3222 = v3219 != v3221;	// L5035
    bool v3223 = v3220 & v3222;	// L5036
    if (v3223) {	// L5037
      int32_t v3224 = c24;	// L5038
      int v3225 = v3224;	// L5039
      half v3226 = hold_v4[v3225][1];	// L5040
      hold_v4[v3225][0] = v3226;	// L5041
      int32_t v3227 = c24;	// L5042
      int v3228 = v3227;	// L5043
      int32_t v3229 = hold_cnt4[v3228];	// L5044
      ap_int<33> v3230 = v3229;	// L5045
      ap_int<33> v3231 = v3230 - 1;	// L5046
      int32_t v3232 = v3231;	// L5047
      hold_cnt4[v3228] = v3232;	// L5048
    }
    int32_t v3233 = grant4;	// L5050
    bool v3234 = v3233 == 1;	// L5051
    int32_t v3235 = s14;	// L5052
    bool v3236 = v3235 < 8;	// L5053
    int32_t v3237 = dsmask4;	// L5054
    int32_t v3238 = v3237 >> v3235;	// L5055
    int32_t v3239 = v3238 & 1;	// L5056
    bool v3240 = v3239 == 1;	// L5057
    bool v3241 = v3234 & v3236;	// L5058
    bool v3242 = v3241 & v3240;	// L5059
    if (v3242) {	// L5060
      int32_t v3243 = s14;	// L5061
      int v3244 = v3243;	// L5062
      drf_full4[v3244] = 0;	// L5063
    }
    int32_t v3245 = grant4;	// L5065
    bool v3246 = v3245 == 1;	// L5066
    int32_t v3247 = s24;	// L5067
    bool v3248 = v3247 < 8;	// L5068
    int32_t v3249 = dsmask4;	// L5069
    int32_t v3250 = v3249 >> v3247;	// L5070
    int32_t v3251 = v3250 & 1;	// L5071
    bool v3252 = v3251 == 1;	// L5072
    bool v3253 = v3246 & v3248;	// L5073
    bool v3254 = v3253 & v3252;	// L5074
    if (v3254) {	// L5075
      int32_t v3255 = s24;	// L5076
      int v3256 = v3255;	// L5077
      drf_full4[v3256] = 0;	// L5078
    }
    half res4;	// L5080
    res4 = (double)0.000000;	// L5081
    int32_t v3258 = op4;	// L5082
    bool v3259 = v3258 == 0;	// L5083
    if (v3259) {	// L5084
      half v3260 = a4;	// L5085
      half v3261 = b4;	// L5086
      half v3262 = v3260 + v3261;	// L5087
      res4 = v3262;	// L5088
    } else {
      int32_t v3263 = op4;	// L5090
      bool v3264 = v3263 == 1;	// L5091
      if (v3264) {	// L5092
        half v3265 = a4;	// L5093
        half v3266 = b4;	// L5094
        half v3267 = v3265 - v3266;	// L5095
        res4 = v3267;	// L5096
      } else {
        int32_t v3268 = op4;	// L5098
        bool v3269 = v3268 == 2;	// L5099
        if (v3269) {	// L5100
          half v3270 = a4;	// L5101
          half v3271 = b4;	// L5102
          half v3272 = v3270 * v3271;	// L5103
          res4 = v3272;	// L5104
        } else {
          int32_t v3273 = op4;	// L5106
          bool v3274 = v3273 == 8;	// L5107
          if (v3274) {	// L5108
            half v3275 = a4;	// L5109
            half v3276 = b4;	// L5110
            bool v3277 = v3275 >= v3276;	// L5111
            if (v3277) {	// L5112
              res4 = (double)1.000000;	// L5113
            } else {
              res4 = (double)-1.000000;	// L5115
            }
          } else {
            int32_t v3278 = op4;	// L5118
            bool v3279 = v3278 == 9;	// L5119
            if (v3279) {	// L5120
              half v3280 = a4;	// L5121
              half v3281 = b4;	// L5122
              bool v3282 = v3280 < v3281;	// L5123
              if (v3282) {	// L5124
                res4 = (double)1.000000;	// L5125
              } else {
                res4 = (double)-1.000000;	// L5127
              }
            } else {
              half v3283 = a4;	// L5130
              res4 = v3283;	// L5131
            }
          }
        }
      }
    }
    int32_t v3284 = a_vld4;	// L5137
    int32_t res_vld4;	// L5138
    res_vld4 = v3284;	// L5139
    int32_t v3286 = op4;	// L5140
    bool v3287 = v3286 == 0;	// L5141
    bool v3288 = v3286 == 1;	// L5142
    bool v3289 = v3286 == 2;	// L5143
    bool v3290 = v3286 == 8;	// L5144
    bool v3291 = v3286 == 9;	// L5145
    bool v3292 = v3287 | v3288;	// L5146
    bool v3293 = v3292 | v3289;	// L5147
    bool v3294 = v3293 | v3290;	// L5148
    bool v3295 = v3294 | v3291;	// L5149
    if (v3295) {	// L5150
      int32_t v3296 = a_vld4;	// L5151
      int32_t v3297 = b_vld4;	// L5152
      int64_t v3298 = v3296;	// L5153
      int64_t v3299 = v3297;	// L5154
      int64_t v3300 = v3298 * v3299;	// L5155
      int32_t v3301 = v3300;	// L5156
      res_vld4 = v3301;	// L5157
    }
    int32_t v3302 = grant4;	// L5159
    bool v3303 = v3302 == 0;	// L5160
    if (v3303) {	// L5161
      res_vld4 = 0;	// L5162
    }
    int32_t v3304 = grant4;	// L5164
    bool v3305 = v3304 == 1;	// L5165
    int32_t v3306 = op4;	// L5166
    bool v3307 = v3306 == 8;	// L5167
    bool v3308 = v3305 & v3307;	// L5168
    if (v3308) {	// L5169
      condition_reg4 = 0;	// L5170
      half v3309 = a4;	// L5171
      half v3310 = b4;	// L5172
      bool v3311 = v3309 >= v3310;	// L5173
      if (v3311) {	// L5174
        condition_reg4 = 1;	// L5175
      }
    }
    int32_t v3312 = grant4;	// L5178
    bool v3313 = v3312 == 1;	// L5179
    int32_t v3314 = op4;	// L5180
    bool v3315 = v3314 == 9;	// L5181
    bool v3316 = v3313 & v3315;	// L5182
    if (v3316) {	// L5183
      condition_reg4 = 0;	// L5184
      half v3317 = a4;	// L5185
      half v3318 = b4;	// L5186
      bool v3319 = v3317 < v3318;	// L5187
      if (v3319) {	// L5188
        condition_reg4 = 1;	// L5189
      }
    }
    ap_uint<17> tx_n4;	// L5192
    tx_n4 = 0;	// L5193
    ap_uint<17> tx_s4;	// L5194
    tx_s4 = 0;	// L5195
    ap_uint<17> tx_w4;	// L5196
    tx_w4 = 0;	// L5197
    ap_uint<17> tx_e4;	// L5198
    tx_e4 = 0;	// L5199
    int32_t is_rtr4;	// L5200
    is_rtr4 = 0;	// L5201
    int32_t do_inj4;	// L5202
    do_inj4 = 0;	// L5203
    int32_t v3326 = op4;	// L5204
    bool v3327 = v3326 >= 4;	// L5205
    ap_int<33> v3328 = v3326;	// L5206
    bool v3329 = v3328 <= 7;	// L5207
    bool v3330 = v3327 & v3329;	// L5208
    if (v3330) {	// L5209
      is_rtr4 = 1;	// L5210
      do_inj4 = 1;	// L5211
    }
    int32_t v3331 = op4;	// L5213
    bool v3332 = v3331 >= 12;	// L5214
    ap_int<33> v3333 = v3331;	// L5215
    bool v3334 = v3333 <= 15;	// L5216
    bool v3335 = v3332 & v3334;	// L5217
    if (v3335) {	// L5218
      is_rtr4 = 1;	// L5219
      int32_t v3336 = condition_reg4;	// L5220
      bool v3337 = v3336 == 1;	// L5221
      if (v3337) {	// L5222
        do_inj4 = 1;	// L5223
      }
    }
    int32_t v3338 = is_rtr4;	// L5226
    bool v3339 = v3338 == 1;	// L5227
    if (v3339) {	// L5228
      int32_t v3340 = do_inj4;	// L5229
      bool v3341 = v3340 == 1;	// L5230
      ap_int<26> v3342 = csd_pkt4;	// L5231
      bool v3343;
      ap_int<26> v3343_tmp = v3342;
      v3343 = v3343_tmp[25];	// L5232
      int32_t v3344 = v3343;	// L5233
      bool v3345 = v3344 == 0;	// L5234
      bool v3346 = v3341 & v3345;	// L5235
      if (v3346) {	// L5236
        half v3347 = res4;	// L5237
        uint16_t v3348;
        union { half from; uint16_t to;} _converter_v3347_to_v3348;
        _converter_v3347_to_v3348.from = v3347;
        v3348 = _converter_v3347_to_v3348.to;	// L5238
        ap_int<26> v3349 = csd_pkt4;	// L5239
        ap_int<26> v3350;
        ap_int<26> v3350_tmp = v3349;
        v3350_tmp(15, 0) = v3348;
        v3350 = v3350_tmp;	// L5240
        csd_pkt4 = v3350;	// L5241
        int32_t v3351 = dst4;	// L5242
        ap_uint<4> v3352 = v3351;	// L5243
        ap_int<26> v3353 = csd_pkt4;	// L5244
        ap_int<26> v3354;
        ap_int<26> v3354_tmp = v3353;
        v3354_tmp(19, 16) = v3352;
        v3354 = v3354_tmp;	// L5245
        csd_pkt4 = v3354;	// L5246
        int32_t v3355 = s24;	// L5247
        ap_uint<4> v3356 = v3355;	// L5248
        ap_int<26> v3357 = csd_pkt4;	// L5249
        ap_int<26> v3358;
        ap_int<26> v3358_tmp = v3357;
        v3358_tmp(24, 21) = v3356;
        v3358 = v3358_tmp;	// L5250
        csd_pkt4 = v3358;	// L5251
        int32_t v3359 = res_vld4;	// L5252
        bool v3360 = v3359;	// L5253
        ap_int<26> v3361 = csd_pkt4;	// L5254
        ap_int<26> v3362;
        ap_int<26> v3362_tmp = v3361;
        v3362_tmp[25] = v3360;        v3362 = v3362_tmp;	// L5255
        csd_pkt4 = v3362;	// L5256
        int32_t v3363 = op4;	// L5257
        int32_t v3364 = v3363 & 3;	// L5258
        csd_dir4 = v3364;	// L5259
      }
    } else {
      int32_t v3365 = dst4;	// L5262
      bool v3366 = v3365 >= 12;	// L5263
      if (v3366) {	// L5264
        ap_uint<17> tw4;	// L5265
        tw4 = 0;	// L5266
        int32_t v3368 = res_vld4;	// L5267
        bool v3369 = v3368;	// L5268
        ap_int<17> v3370 = tw4;	// L5269
        ap_int<17> v3371;
        ap_int<17> v3371_tmp = v3370;
        v3371_tmp[0] = v3369;        v3371 = v3371_tmp;	// L5270
        tw4 = v3371;	// L5271
        half v3372 = res4;	// L5272
        uint16_t v3373;
        union { half from; uint16_t to;} _converter_v3372_to_v3373;
        _converter_v3372_to_v3373.from = v3372;
        v3373 = _converter_v3372_to_v3373.to;	// L5273
        ap_int<17> v3374 = tw4;	// L5274
        ap_int<17> v3375;
        ap_int<17> v3375_tmp = v3374;
        v3375_tmp(16, 1) = v3373;
        v3375 = v3375_tmp;	// L5275
        tw4 = v3375;	// L5276
        int32_t v3376 = dst4;	// L5277
        int32_t v3377 = v3376 & 3;	// L5278
        bool v3378 = v3377 == 0;	// L5279
        if (v3378) {	// L5280
          ap_int<17> v3379 = tw4;	// L5281
          tx_n4 = v3379;	// L5282
        } else {
          int32_t v3380 = dst4;	// L5284
          int32_t v3381 = v3380 & 3;	// L5285
          bool v3382 = v3381 == 1;	// L5286
          if (v3382) {	// L5287
            ap_int<17> v3383 = tw4;	// L5288
            tx_s4 = v3383;	// L5289
          } else {
            int32_t v3384 = dst4;	// L5291
            int32_t v3385 = v3384 & 3;	// L5292
            bool v3386 = v3385 == 2;	// L5293
            if (v3386) {	// L5294
              ap_int<17> v3387 = tw4;	// L5295
              tx_w4 = v3387;	// L5296
            } else {
              ap_int<17> v3388 = tw4;	// L5298
              tx_e4 = v3388;	// L5299
            }
          }
        }
      } else {
        int32_t v3389 = res_vld4;	// L5304
        bool v3390 = v3389 == 1;	// L5305
        if (v3390) {	// L5306
          int32_t v3391 = dst4;	// L5307
          bool v3392 = v3391 < 8;	// L5308
          int32_t v3393 = dsmask4;	// L5309
          int32_t v3394 = v3393 >> v3391;	// L5310
          int32_t v3395 = v3394 & 1;	// L5311
          bool v3396 = v3395 == 1;	// L5312
          bool v3397 = v3392 & v3396;	// L5313
          if (v3397) {	// L5314
            int32_t v3398 = dst4;	// L5315
            int v3399 = v3398;	// L5316
            int32_t v3400 = drf_full4[v3399];	// L5317
            bool v3401 = v3400 == 0;	// L5318
            if (v3401) {	// L5319
              half v3402 = res4;	// L5320
              int32_t v3403 = dst4;	// L5321
              int v3404 = v3403;	// L5322
              drf4[v3404] = v3402;	// L5323
              int32_t v3405 = dst4;	// L5324
              int v3406 = v3405;	// L5325
              drf_full4[v3406] = 1;	// L5326
            }
          } else {
            half v3407 = res4;	// L5329
            int32_t v3408 = dst4;	// L5330
            int v3409 = v3408;	// L5331
            drf4[v3409] = v3407;	// L5332
          }
        }
      }
    }
    ap_int<17> v3410 = tx_n4;	// L5337
    txn_r4 = v3410;	// L5338
    ap_int<17> v3411 = tx_s4;	// L5339
    txs_r4 = v3411;	// L5340
    ap_int<17> v3412 = tx_w4;	// L5341
    txw_r4 = v3412;	// L5342
    ap_int<17> v3413 = tx_e4;	// L5343
    txe_r4 = v3413;	// L5344
    int32_t v3414 = crv_vld4;	// L5345
    bool v3415 = v3414 == 1;	// L5346
    if (v3415) {	// L5347
      int32_t v3416 = crv_mode4;	// L5348
      bool v3417 = v3416 == 1;	// L5349
      if (v3417) {	// L5350
        int32_t v3418 = crv_addr4;	// L5351
        int32_t v3419 = v3418 >> 3;	// L5352
        int32_t v3420 = v3419 & 1;	// L5353
        bool v3421 = v3420 == 1;	// L5354
        if (v3421) {	// L5355
          int32_t v3422 = crv_raw4;	// L5356
          int32_t v3423 = crv_addr4;	// L5357
          int32_t v3424 = v3423 & 7;	// L5358
          int v3425 = v3424;	// L5359
          irf4[v3425] = v3422;	// L5360
        } else {
          int32_t v3426 = crv_addr4;	// L5362
          bool v3427 = v3426 == 0;	// L5363
          if (v3427) {	// L5364
            int32_t v3428 = crv_raw4;	// L5365
            int32_t v3429 = v3428 & 255;	// L5366
            dsmask4 = v3429;	// L5367
            int32_t v3430 = crv_raw4;	// L5368
            int32_t v3431 = v3430 >> 8;	// L5369
            int32_t v3432 = v3431 & 7;	// L5370
            cfg_isz4 = v3432;	// L5371
            int32_t v3433 = crv_raw4;	// L5372
            int32_t v3434 = v3433 >> 15;	// L5373
            int32_t v3435 = v3434 & 1;	// L5374
            bool v3436 = v3435 == 1;	// L5375
            if (v3436) {	// L5376
              fetch_en4 = 1;	// L5377
              instr_cnt4 = 0;	// L5378
              iter_cnt4 = 0;	// L5379
            }
          } else {
            int32_t v3437 = crv_addr4;	// L5382
            bool v3438 = v3437 == 1;	// L5383
            if (v3438) {	// L5384
              int32_t v3439 = crv_raw4;	// L5385
              int32_t v3440 = v3439 & 255;	// L5386
              cfg_itsz4 = v3440;	// L5387
            }
          }
        }
      } else {
        int32_t v3441 = crv_addr4;	// L5392
        bool v3442 = v3441 < 8;	// L5393
        int32_t v3443 = dsmask4;	// L5394
        int32_t v3444 = v3443 >> v3441;	// L5395
        int32_t v3445 = v3444 & 1;	// L5396
        bool v3446 = v3445 == 1;	// L5397
        bool v3447 = v3442 & v3446;	// L5398
        if (v3447) {	// L5399
          int32_t v3448 = crv_addr4;	// L5400
          int v3449 = v3448;	// L5401
          int32_t v3450 = drf_full4[v3449];	// L5402
          bool v3451 = v3450 == 0;	// L5403
          if (v3451) {	// L5404
            half v3452 = crv_data4;	// L5405
            int32_t v3453 = crv_addr4;	// L5406
            int v3454 = v3453;	// L5407
            drf4[v3454] = v3452;	// L5408
            int32_t v3455 = crv_addr4;	// L5409
            int v3456 = v3455;	// L5410
            drf_full4[v3456] = 1;	// L5411
          }
        } else {
          half v3457 = crv_data4;	// L5414
          int32_t v3458 = crv_addr4;	// L5415
          int v3459 = v3458;	// L5416
          drf4[v3459] = v3457;	// L5417
        }
      }
    }
  }
}

void node_1_1(
  hls::stream< ap_uint<26> >& v3460,
  hls::stream< ap_uint<26> >& v3461,
  hls::stream< ap_uint<26> >& v3462,
  hls::stream< ap_uint<26> >& v3463,
  hls::stream< ap_uint<17> >& v3464,
  hls::stream< ap_uint<17> >& v3465,
  hls::stream< ap_uint<17> >& v3466,
  hls::stream< ap_uint<17> >& v3467,
  hls::stream< int32_t >& v3468,
  hls::stream< int32_t >& v3469,
  hls::stream< int32_t >& v3470,
  hls::stream< int32_t >& v3471,
  hls::stream< ap_uint<26> >& v3472,
  hls::stream< ap_uint<26> >& v3473,
  hls::stream< ap_uint<26> >& v3474,
  hls::stream< ap_uint<26> >& v3475,
  hls::stream< int32_t >& v3476,
  hls::stream< int32_t >& v3477,
  hls::stream< int32_t >& v3478,
  hls::stream< int32_t >& v3479,
  hls::stream< ap_uint<17> >& v3480,
  hls::stream< ap_uint<17> >& v3481,
  hls::stream< ap_uint<17> >& v3482,
  hls::stream< ap_uint<17> >& v3483
) {	// L5424
  int32_t irf5[8];	// L5455
  for (int v3485 = 0; v3485 < 8; v3485++) {	// L5456
    irf5[v3485] = 0;	// L5456
  }
  half drf5[8];	// L5457
  #pragma HLS array_partition variable=drf5 complete dim=1

  for (int v3487 = 0; v3487 < 8; v3487++) {	// L5458
    drf5[v3487] = (double)0.000000;	// L5458
  }
  int32_t drf_full5[8];	// L5459
  #pragma HLS array_partition variable=drf_full5 complete dim=1

  for (int v3489 = 0; v3489 < 8; v3489++) {	// L5460
    drf_full5[v3489] = 0;	// L5460
  }
  int32_t dsmask5;	// L5461
  dsmask5 = 0;	// L5462
  int32_t crv_vld5;	// L5463
  crv_vld5 = 0;	// L5464
  half crv_data5;	// L5465
  crv_data5 = (double)0.000000;	// L5466
  int32_t crv_addr5;	// L5467
  crv_addr5 = 0;	// L5468
  int32_t crv_mode5;	// L5469
  crv_mode5 = 0;	// L5470
  int32_t crv_raw5;	// L5471
  crv_raw5 = 0;	// L5472
  int32_t csd_vld5;	// L5473
  csd_vld5 = 0;	// L5474
  ap_uint<26> csd_pkt5;	// L5475
  csd_pkt5 = 0;	// L5476
  int32_t csd_dir5;	// L5477
  csd_dir5 = 0;	// L5478
  int32_t row_id5;	// L5479
  row_id5 = 1;	// L5480
  int32_t col_id5;	// L5481
  col_id5 = 1;	// L5482
  ap_uint<26> oe_r5;	// L5483
  oe_r5 = 0;	// L5484
  ap_uint<26> ow_r5;	// L5485
  ow_r5 = 0;	// L5486
  ap_uint<26> on_r5;	// L5487
  on_r5 = 0;	// L5488
  ap_uint<26> os_r5;	// L5489
  os_r5 = 0;	// L5490
  ap_uint<17> txn_r5;	// L5491
  txn_r5 = 0;	// L5492
  ap_uint<17> txs_r5;	// L5493
  txs_r5 = 0;	// L5494
  ap_uint<17> txw_r5;	// L5495
  txw_r5 = 0;	// L5496
  ap_uint<17> txe_r5;	// L5497
  txe_r5 = 0;	// L5498
  half hold_v5[4][2];	// L5499
  #pragma HLS array_partition variable=hold_v5 complete dim=1
  #pragma HLS array_partition variable=hold_v5 complete dim=2

  for (int v3510 = 0; v3510 < 4; v3510++) {	// L5500
    for (int v3511 = 0; v3511 < 2; v3511++) {	// L5500
      hold_v5[v3510][v3511] = (double)0.000000;	// L5500
    }
  }
  int32_t hold_cnt5[4];	// L5501
  #pragma HLS array_partition variable=hold_cnt5 complete dim=1

  for (int v3513 = 0; v3513 < 4; v3513++) {	// L5502
    hold_cnt5[v3513] = 0;	// L5502
  }
  ap_uint<26> rbuf5[4][2];	// L5503
  #pragma HLS array_partition variable=rbuf5 complete dim=1
  #pragma HLS array_partition variable=rbuf5 complete dim=2

  for (int v3515 = 0; v3515 < 4; v3515++) {	// L5504
    for (int v3516 = 0; v3516 < 2; v3516++) {	// L5504
      rbuf5[v3515][v3516] = 0;	// L5504
    }
  }
  int32_t rbcnt5[4];	// L5505
  #pragma HLS array_partition variable=rbcnt5 complete dim=1

  for (int v3518 = 0; v3518 < 4; v3518++) {	// L5506
    rbcnt5[v3518] = 0;	// L5506
  }
  int32_t rcred5[4];	// L5507
  #pragma HLS array_partition variable=rcred5 complete dim=1

  for (int v3520 = 0; v3520 < 4; v3520++) {	// L5508
    rcred5[v3520] = 0;	// L5508
  }
  int32_t cre_r5;	// L5509
  cre_r5 = 2;	// L5510
  int32_t crw_r5;	// L5511
  crw_r5 = 2;	// L5512
  int32_t crs_r5;	// L5513
  crs_r5 = 2;	// L5514
  int32_t crn_r5;	// L5515
  crn_r5 = 2;	// L5516
  int32_t cfg_isz5;	// L5517
  cfg_isz5 = 0;	// L5518
  int32_t cfg_itsz5;	// L5519
  cfg_itsz5 = 0;	// L5520
  int32_t fetch_en5;	// L5521
  fetch_en5 = 0;	// L5522
  int32_t instr_cnt5;	// L5523
  instr_cnt5 = 0;	// L5524
  int32_t iter_cnt5;	// L5525
  iter_cnt5 = 0;	// L5526
  int32_t condition_reg5;	// L5527
  condition_reg5 = 0;	// L5528
  l_S_t_0_t5: for (int t5 = 0; t5 < 8; t5++) {	// L5529
  #pragma HLS pipeline II=1
    ap_int<26> v3532 = oe_r5;	// L5530
    v3460.write(v3532);	// L5531
    ap_int<26> v3533 = ow_r5;	// L5532
    v3461.write(v3533);	// L5533
    ap_int<26> v3534 = os_r5;	// L5534
    v3462.write(v3534);	// L5535
    ap_int<26> v3535 = on_r5;	// L5536
    v3463.write(v3535);	// L5537
    ap_int<17> v3536 = txe_r5;	// L5538
    v3464.write(v3536);	// L5539
    ap_int<17> v3537 = txw_r5;	// L5540
    v3465.write(v3537);	// L5541
    ap_int<17> v3538 = txs_r5;	// L5542
    v3466.write(v3538);	// L5543
    ap_int<17> v3539 = txn_r5;	// L5544
    v3467.write(v3539);	// L5545
    int32_t v3540 = cre_r5;	// L5546
    v3468.write(v3540);	// L5547
    int32_t v3541 = crw_r5;	// L5548
    v3469.write(v3541);	// L5549
    int32_t v3542 = crs_r5;	// L5550
    v3470.write(v3542);	// L5551
    int32_t v3543 = crn_r5;	// L5552
    v3471.write(v3543);	// L5553
    ap_uint<26> v3544 = v3472.read();	// L5554
    ap_uint<26> p_w5;	// L5555
    p_w5 = v3544;	// L5556
    ap_uint<26> v3546 = v3473.read();	// L5557
    ap_uint<26> p_e5;	// L5558
    p_e5 = v3546;	// L5559
    ap_uint<26> v3548 = v3474.read();	// L5560
    ap_uint<26> p_n5;	// L5561
    p_n5 = v3548;	// L5562
    ap_uint<26> v3550 = v3475.read();	// L5563
    ap_uint<26> p_s5;	// L5564
    p_s5 = v3550;	// L5565
    int32_t v3552 = v3476.read();	// L5566
    int32_t v3553 = rcred5[0];	// L5567
    ap_int<33> v3554 = v3553;	// L5568
    ap_int<33> v3555 = v3552;	// L5569
    ap_int<33> v3556 = v3554 + v3555;	// L5570
    int32_t v3557 = v3556;	// L5571
    rcred5[0] = v3557;	// L5572
    int32_t v3558 = v3477.read();	// L5573
    int32_t v3559 = rcred5[1];	// L5574
    ap_int<33> v3560 = v3559;	// L5575
    ap_int<33> v3561 = v3558;	// L5576
    ap_int<33> v3562 = v3560 + v3561;	// L5577
    int32_t v3563 = v3562;	// L5578
    rcred5[1] = v3563;	// L5579
    int32_t v3564 = v3478.read();	// L5580
    int32_t v3565 = rcred5[2];	// L5581
    ap_int<33> v3566 = v3565;	// L5582
    ap_int<33> v3567 = v3564;	// L5583
    ap_int<33> v3568 = v3566 + v3567;	// L5584
    int32_t v3569 = v3568;	// L5585
    rcred5[2] = v3569;	// L5586
    int32_t v3570 = v3479.read();	// L5587
    int32_t v3571 = rcred5[3];	// L5588
    ap_int<33> v3572 = v3571;	// L5589
    ap_int<33> v3573 = v3570;	// L5590
    ap_int<33> v3574 = v3572 + v3573;	// L5591
    int32_t v3575 = v3574;	// L5592
    rcred5[3] = v3575;	// L5593
    ap_uint<26> fin5[4];	// L5594
    for (int v3577 = 0; v3577 < 4; v3577++) {	// L5595
      fin5[v3577] = 0;	// L5595
    }
    ap_int<26> v3578 = p_w5;	// L5596
    fin5[0] = v3578;	// L5597
    ap_int<26> v3579 = p_e5;	// L5598
    fin5[1] = v3579;	// L5599
    ap_int<26> v3580 = p_n5;	// L5600
    fin5[2] = v3580;	// L5601
    ap_int<26> v3581 = p_s5;	// L5602
    fin5[3] = v3581;	// L5603
    l_S_d_0_d20: for (int d20 = 0; d20 < 4; d20++) {	// L5604
      ap_uint<26> v3583 = fin5[d20];	// L5605
      bool v3584;
      ap_int<26> v3584_tmp = v3583;
      v3584 = v3584_tmp[25];	// L5606
      int32_t v3585 = v3584;	// L5607
      bool v3586 = v3585 == 1;	// L5608
      int32_t v3587 = rbcnt5[d20];	// L5609
      bool v3588 = v3587 < 2;	// L5610
      bool v3589 = v3586 & v3588;	// L5611
      if (v3589) {	// L5612
        ap_uint<26> v3590 = fin5[d20];	// L5613
        int32_t v3591 = rbcnt5[d20];	// L5614
        int v3592 = v3591;	// L5615
        rbuf5[d20][v3592] = v3590;	// L5616
        int32_t v3593 = rbcnt5[d20];	// L5617
        ap_int<33> v3594 = v3593;	// L5618
        ap_int<33> v3595 = v3594 + 1;	// L5619
        int32_t v3596 = v3595;	// L5620
        rbcnt5[d20] = v3596;	// L5621
      }
    }
    ap_uint<26> hd5[4];	// L5624
    for (int v3598 = 0; v3598 < 4; v3598++) {	// L5625
      hd5[v3598] = 0;	// L5625
    }
    int32_t hvld5[4];	// L5626
    for (int v3600 = 0; v3600 < 4; v3600++) {	// L5627
      hvld5[v3600] = 0;	// L5627
    }
    int32_t hit5[4];	// L5628
    for (int v3602 = 0; v3602 < 4; v3602++) {	// L5629
      hit5[v3602] = 0;	// L5629
    }
    int32_t axis5[4];	// L5630
    for (int v3604 = 0; v3604 < 4; v3604++) {	// L5631
      axis5[v3604] = 0;	// L5631
    }
    int32_t v3605 = col_id5;	// L5632
    axis5[0] = v3605;	// L5633
    int32_t v3606 = col_id5;	// L5634
    axis5[1] = v3606;	// L5635
    int32_t v3607 = row_id5;	// L5636
    axis5[2] = v3607;	// L5637
    int32_t v3608 = row_id5;	// L5638
    axis5[3] = v3608;	// L5639
    l_S_d_1_d21: for (int d21 = 0; d21 < 4; d21++) {	// L5640
      int32_t v3610 = rbcnt5[d21];	// L5641
      bool v3611 = v3610 > 0;	// L5642
      if (v3611) {	// L5643
        ap_uint<26> v3612 = rbuf5[d21][0];	// L5644
        hd5[d21] = v3612;	// L5645
        hvld5[d21] = 1;	// L5646
        ap_uint<26> v3613 = hd5[d21];	// L5647
        ap_int<4> v3614;
        ap_int<26> v3614_tmp = v3613;
        v3614 = v3614_tmp(24, 21);	// L5648
        int32_t v3615 = axis5[d21];	// L5649
        int32_t v3616 = v3614;	// L5650
        bool v3617 = v3616 == v3615;	// L5651
        if (v3617) {	// L5652
          hit5[d21] = 1;	// L5653
        }
      }
    }
    ap_uint<26> o_crv5;	// L5657
    o_crv5 = 0;	// L5658
    int32_t crv_in5;	// L5659
    crv_in5 = -1;	// L5660
    int32_t v3620 = hit5[3];	// L5661
    bool v3621 = v3620 == 1;	// L5662
    if (v3621) {	// L5663
      ap_uint<26> v3622 = hd5[3];	// L5664
      o_crv5 = v3622;	// L5665
      crv_in5 = 3;	// L5666
    } else {
      int32_t v3623 = hit5[2];	// L5668
      bool v3624 = v3623 == 1;	// L5669
      if (v3624) {	// L5670
        ap_uint<26> v3625 = hd5[2];	// L5671
        o_crv5 = v3625;	// L5672
        crv_in5 = 2;	// L5673
      } else {
        int32_t v3626 = hit5[1];	// L5675
        bool v3627 = v3626 == 1;	// L5676
        if (v3627) {	// L5677
          ap_uint<26> v3628 = hd5[1];	// L5678
          o_crv5 = v3628;	// L5679
          crv_in5 = 1;	// L5680
        } else {
          int32_t v3629 = hit5[0];	// L5682
          bool v3630 = v3629 == 1;	// L5683
          if (v3630) {	// L5684
            ap_uint<26> v3631 = hd5[0];	// L5685
            o_crv5 = v3631;	// L5686
            crv_in5 = 0;	// L5687
          }
        }
      }
    }
    ap_uint<26> o_out5[4];	// L5692
    for (int v3633 = 0; v3633 < 4; v3633++) {	// L5693
      o_out5[v3633] = 0;	// L5693
    }
    int32_t pop5[4];	// L5694
    for (int v3635 = 0; v3635 < 4; v3635++) {	// L5695
      pop5[v3635] = 0;	// L5695
    }
    int32_t inj_done5;	// L5696
    inj_done5 = 0;	// L5697
    int32_t idir5;	// L5698
    idir5 = -1;	// L5699
    ap_int<26> v3638 = csd_pkt5;	// L5700
    bool v3639;
    ap_int<26> v3639_tmp = v3638;
    v3639 = v3639_tmp[25];	// L5701
    int32_t v3640 = v3639;	// L5702
    bool v3641 = v3640 == 1;	// L5703
    if (v3641) {	// L5704
      int32_t v3642 = csd_dir5;	// L5705
      ap_int<33> v3643 = v3642;	// L5706
      ap_int<33> v3644 = 3 - v3643;	// L5707
      int32_t v3645 = v3644;	// L5708
      idir5 = v3645;	// L5709
    }
    l_S_o_2_o5: for (int o5 = 0; o5 < 4; o5++) {	// L5711
      int32_t v3647 = rcred5[o5];	// L5712
      bool v3648 = v3647 > 0;	// L5713
      if (v3648) {	// L5714
        int32_t v3649 = idir5;	// L5715
        ap_int<33> v3650 = v3649;	// L5716
        ap_int<33> v3651 = o5;	// L5717
        bool v3652 = v3650 == v3651;	// L5718
        if (v3652) {	// L5719
          ap_int<26> v3653 = csd_pkt5;	// L5720
          o_out5[o5] = v3653;	// L5721
          int32_t v3654 = rcred5[o5];	// L5722
          ap_int<33> v3655 = v3654;	// L5723
          ap_int<33> v3656 = v3655 - 1;	// L5724
          int32_t v3657 = v3656;	// L5725
          rcred5[o5] = v3657;	// L5726
          inj_done5 = 1;	// L5727
        } else {
          int32_t v3658 = hvld5[o5];	// L5729
          bool v3659 = v3658 == 1;	// L5730
          int32_t v3660 = hit5[o5];	// L5731
          bool v3661 = v3660 == 0;	// L5732
          bool v3662 = v3659 & v3661;	// L5733
          if (v3662) {	// L5734
            ap_uint<26> v3663 = hd5[o5];	// L5735
            o_out5[o5] = v3663;	// L5736
            int32_t v3664 = rcred5[o5];	// L5737
            ap_int<33> v3665 = v3664;	// L5738
            ap_int<33> v3666 = v3665 - 1;	// L5739
            int32_t v3667 = v3666;	// L5740
            rcred5[o5] = v3667;	// L5741
            pop5[o5] = 1;	// L5742
          }
        }
      }
    }
    int32_t v3668 = crv_in5;	// L5747
    bool v3669 = v3668 >= 0;	// L5748
    if (v3669) {	// L5749
      int32_t v3670 = crv_in5;	// L5750
      int v3671 = v3670;	// L5751
      pop5[v3671] = 1;	// L5752
    }
    int32_t ret5[4];	// L5754
    for (int v3673 = 0; v3673 < 4; v3673++) {	// L5755
      ret5[v3673] = 0;	// L5755
    }
    l_S_d_3_d22: for (int d22 = 0; d22 < 4; d22++) {	// L5756
      int32_t v3675 = pop5[d22];	// L5757
      bool v3676 = v3675 == 1;	// L5758
      if (v3676) {	// L5759
        l_S_sft_3_sft5: for (int sft5 = 0; sft5 < 1; sft5++) {	// L5760
          ap_uint<26> v3678 = rbuf5[d22][(sft5 + 1)];	// L5761
          rbuf5[d22][sft5] = v3678;	// L5762
        }
        int32_t v3679 = rbcnt5[d22];	// L5764
        ap_int<33> v3680 = v3679;	// L5765
        ap_int<33> v3681 = v3680 - 1;	// L5766
        int32_t v3682 = v3681;	// L5767
        rbcnt5[d22] = v3682;	// L5768
        ret5[d22] = 1;	// L5769
      }
    }
    int32_t v3683 = ret5[0];	// L5772
    cre_r5 = v3683;	// L5773
    int32_t v3684 = ret5[1];	// L5774
    crw_r5 = v3684;	// L5775
    int32_t v3685 = ret5[2];	// L5776
    crs_r5 = v3685;	// L5777
    int32_t v3686 = ret5[3];	// L5778
    crn_r5 = v3686;	// L5779
    ap_uint<26> v3687 = o_out5[0];	// L5780
    oe_r5 = v3687;	// L5781
    ap_uint<26> v3688 = o_out5[1];	// L5782
    ow_r5 = v3688;	// L5783
    ap_uint<26> v3689 = o_out5[2];	// L5784
    os_r5 = v3689;	// L5785
    ap_uint<26> v3690 = o_out5[3];	// L5786
    on_r5 = v3690;	// L5787
    int32_t v3691 = inj_done5;	// L5788
    bool v3692 = v3691 == 1;	// L5789
    if (v3692) {	// L5790
      csd_pkt5 = 0;	// L5791
    }
    ap_int<26> v3693 = o_crv5;	// L5793
    bool v3694;
    ap_int<26> v3694_tmp = v3693;
    v3694 = v3694_tmp[25];	// L5794
    int32_t v3695 = v3694;	// L5795
    crv_vld5 = v3695;	// L5796
    ap_int<26> v3696 = o_crv5;	// L5797
    int16_t v3697;
    ap_int<26> v3697_tmp = v3696;
    v3697 = v3697_tmp(15, 0);	// L5798
    half v3698;
    union { uint16_t from; half to;} _converter_v3697_to_v3698;
    _converter_v3697_to_v3698.from = v3697;
    v3698 = _converter_v3697_to_v3698.to;	// L5799
    crv_data5 = v3698;	// L5800
    ap_int<26> v3699 = o_crv5;	// L5801
    ap_int<4> v3700;
    ap_int<26> v3700_tmp = v3699;
    v3700 = v3700_tmp(19, 16);	// L5802
    int32_t v3701 = v3700;	// L5803
    crv_addr5 = v3701;	// L5804
    ap_int<26> v3702 = o_crv5;	// L5805
    bool v3703;
    ap_int<26> v3703_tmp = v3702;
    v3703 = v3703_tmp[20];	// L5806
    int32_t v3704 = v3703;	// L5807
    crv_mode5 = v3704;	// L5808
    ap_int<26> v3705 = o_crv5;	// L5809
    int16_t v3706;
    ap_int<26> v3706_tmp = v3705;
    v3706 = v3706_tmp(15, 0);	// L5810
    int32_t v3707 = v3706;	// L5811
    crv_raw5 = v3707;	// L5812
    ap_uint<17> v3708 = v3480.read();	// L5813
    ap_uint<17> rx_w5;	// L5814
    rx_w5 = v3708;	// L5815
    ap_uint<17> v3710 = v3481.read();	// L5816
    ap_uint<17> rx_e5;	// L5817
    rx_e5 = v3710;	// L5818
    ap_uint<17> v3712 = v3482.read();	// L5819
    ap_uint<17> rx_n5;	// L5820
    rx_n5 = v3712;	// L5821
    ap_uint<17> v3714 = v3483.read();	// L5822
    ap_uint<17> rx_s5;	// L5823
    rx_s5 = v3714;	// L5824
    half rxv5[4];	// L5825
    for (int v3717 = 0; v3717 < 4; v3717++) {	// L5826
      rxv5[v3717] = (double)0.000000;	// L5826
    }
    int32_t rxvld5[4];	// L5827
    for (int v3719 = 0; v3719 < 4; v3719++) {	// L5828
      rxvld5[v3719] = 0;	// L5828
    }
    ap_int<17> v3720 = rx_n5;	// L5829
    int16_t v3721;
    ap_int<17> v3721_tmp = v3720;
    v3721 = v3721_tmp(16, 1);	// L5830
    half v3722;
    union { uint16_t from; half to;} _converter_v3721_to_v3722;
    _converter_v3721_to_v3722.from = v3721;
    v3722 = _converter_v3721_to_v3722.to;	// L5831
    rxv5[0] = v3722;	// L5832
    ap_int<17> v3723 = rx_n5;	// L5833
    bool v3724;
    ap_int<17> v3724_tmp = v3723;
    v3724 = v3724_tmp[0];	// L5834
    int32_t v3725 = v3724;	// L5835
    rxvld5[0] = v3725;	// L5836
    ap_int<17> v3726 = rx_s5;	// L5837
    int16_t v3727;
    ap_int<17> v3727_tmp = v3726;
    v3727 = v3727_tmp(16, 1);	// L5838
    half v3728;
    union { uint16_t from; half to;} _converter_v3727_to_v3728;
    _converter_v3727_to_v3728.from = v3727;
    v3728 = _converter_v3727_to_v3728.to;	// L5839
    rxv5[1] = v3728;	// L5840
    ap_int<17> v3729 = rx_s5;	// L5841
    bool v3730;
    ap_int<17> v3730_tmp = v3729;
    v3730 = v3730_tmp[0];	// L5842
    int32_t v3731 = v3730;	// L5843
    rxvld5[1] = v3731;	// L5844
    ap_int<17> v3732 = rx_w5;	// L5845
    int16_t v3733;
    ap_int<17> v3733_tmp = v3732;
    v3733 = v3733_tmp(16, 1);	// L5846
    half v3734;
    union { uint16_t from; half to;} _converter_v3733_to_v3734;
    _converter_v3733_to_v3734.from = v3733;
    v3734 = _converter_v3733_to_v3734.to;	// L5847
    rxv5[2] = v3734;	// L5848
    ap_int<17> v3735 = rx_w5;	// L5849
    bool v3736;
    ap_int<17> v3736_tmp = v3735;
    v3736 = v3736_tmp[0];	// L5850
    int32_t v3737 = v3736;	// L5851
    rxvld5[2] = v3737;	// L5852
    ap_int<17> v3738 = rx_e5;	// L5853
    int16_t v3739;
    ap_int<17> v3739_tmp = v3738;
    v3739 = v3739_tmp(16, 1);	// L5854
    half v3740;
    union { uint16_t from; half to;} _converter_v3739_to_v3740;
    _converter_v3739_to_v3740.from = v3739;
    v3740 = _converter_v3739_to_v3740.to;	// L5855
    rxv5[3] = v3740;	// L5856
    ap_int<17> v3741 = rx_e5;	// L5857
    bool v3742;
    ap_int<17> v3742_tmp = v3741;
    v3742 = v3742_tmp[0];	// L5858
    int32_t v3743 = v3742;	// L5859
    rxvld5[3] = v3743;	// L5860
    l_S_d_5_d23: for (int d23 = 0; d23 < 4; d23++) {	// L5861
      int32_t v3745 = rxvld5[d23];	// L5862
      bool v3746 = v3745 == 1;	// L5863
      int32_t v3747 = hold_cnt5[d23];	// L5864
      bool v3748 = v3747 < 2;	// L5865
      bool v3749 = v3746 & v3748;	// L5866
      if (v3749) {	// L5867
        half v3750 = rxv5[d23];	// L5868
        int32_t v3751 = hold_cnt5[d23];	// L5869
        int v3752 = v3751;	// L5870
        hold_v5[d23][v3752] = v3750;	// L5871
        int32_t v3753 = hold_cnt5[d23];	// L5872
        ap_int<33> v3754 = v3753;	// L5873
        ap_int<33> v3755 = v3754 + 1;	// L5874
        int32_t v3756 = v3755;	// L5875
        hold_cnt5[d23] = v3756;	// L5876
      }
    }
    int32_t pc5;	// L5879
    pc5 = -1;	// L5880
    int32_t v3758 = fetch_en5;	// L5881
    bool v3759 = v3758 == 1;	// L5882
    if (v3759) {	// L5883
      int32_t v3760 = instr_cnt5;	// L5884
      pc5 = v3760;	// L5885
    }
    int32_t instr5;	// L5887
    instr5 = 0;	// L5888
    int32_t v3762 = pc5;	// L5889
    bool v3763 = v3762 >= 0;	// L5890
    if (v3763) {	// L5891
      int32_t v3764 = pc5;	// L5892
      int v3765 = v3764;	// L5893
      int32_t v3766 = irf5[v3765];	// L5894
      instr5 = v3766;	// L5895
    }
    int32_t v3767 = instr5;	// L5897
    int32_t v3768 = v3767 & 15;	// L5898
    int32_t op5;	// L5899
    op5 = v3768;	// L5900
    int32_t v3770 = instr5;	// L5901
    int32_t v3771 = v3770 >> 4;	// L5902
    int32_t v3772 = v3771 & 15;	// L5903
    int32_t dst5;	// L5904
    dst5 = v3772;	// L5905
    int32_t v3774 = instr5;	// L5906
    int32_t v3775 = v3774 >> 8;	// L5907
    int32_t v3776 = v3775 & 15;	// L5908
    int32_t s15;	// L5909
    s15 = v3776;	// L5910
    int32_t v3778 = instr5;	// L5911
    int32_t v3779 = v3778 >> 12;	// L5912
    int32_t v3780 = v3779 & 15;	// L5913
    int32_t s25;	// L5914
    s25 = v3780;	// L5915
    half a5;	// L5916
    a5 = (double)0.000000;	// L5917
    half b5;	// L5918
    b5 = (double)0.000000;	// L5919
    int32_t v3784 = s15;	// L5920
    bool v3785 = v3784 >= 12;	// L5921
    if (v3785) {	// L5922
      int32_t v3786 = s15;	// L5923
      int32_t v3787 = v3786 & 3;	// L5924
      int v3788 = v3787;	// L5925
      half v3789 = hold_v5[v3788][0];	// L5926
      a5 = v3789;	// L5927
    } else {
      int32_t v3790 = s15;	// L5929
      int v3791 = v3790;	// L5930
      half v3792 = drf5[v3791];	// L5931
      a5 = v3792;	// L5932
    }
    int32_t v3793 = s25;	// L5934
    bool v3794 = v3793 >= 12;	// L5935
    if (v3794) {	// L5936
      int32_t v3795 = s25;	// L5937
      int32_t v3796 = v3795 & 3;	// L5938
      int v3797 = v3796;	// L5939
      half v3798 = hold_v5[v3797][0];	// L5940
      b5 = v3798;	// L5941
    } else {
      int32_t v3799 = s25;	// L5943
      int v3800 = v3799;	// L5944
      half v3801 = drf5[v3800];	// L5945
      b5 = v3801;	// L5946
    }
    int32_t a_vld5;	// L5948
    a_vld5 = 1;	// L5949
    int32_t b_vld5;	// L5950
    b_vld5 = 1;	// L5951
    int32_t v3804 = s15;	// L5952
    bool v3805 = v3804 >= 12;	// L5953
    if (v3805) {	// L5954
      a_vld5 = 0;	// L5955
      int32_t v3806 = s15;	// L5956
      int32_t v3807 = v3806 & 3;	// L5957
      int v3808 = v3807;	// L5958
      int32_t v3809 = hold_cnt5[v3808];	// L5959
      bool v3810 = v3809 > 0;	// L5960
      if (v3810) {	// L5961
        a_vld5 = 1;	// L5962
      }
    }
    int32_t v3811 = s25;	// L5965
    bool v3812 = v3811 >= 12;	// L5966
    if (v3812) {	// L5967
      b_vld5 = 0;	// L5968
      int32_t v3813 = s25;	// L5969
      int32_t v3814 = v3813 & 3;	// L5970
      int v3815 = v3814;	// L5971
      int32_t v3816 = hold_cnt5[v3815];	// L5972
      bool v3817 = v3816 > 0;	// L5973
      if (v3817) {	// L5974
        b_vld5 = 1;	// L5975
      }
    }
    int32_t v3818 = s15;	// L5978
    bool v3819 = v3818 < 8;	// L5979
    int32_t v3820 = dsmask5;	// L5980
    int32_t v3821 = v3820 >> v3818;	// L5981
    int32_t v3822 = v3821 & 1;	// L5982
    bool v3823 = v3822 == 1;	// L5983
    bool v3824 = v3819 & v3823;	// L5984
    if (v3824) {	// L5985
      int32_t v3825 = s15;	// L5986
      int v3826 = v3825;	// L5987
      int32_t v3827 = drf_full5[v3826];	// L5988
      bool v3828 = v3827 == 0;	// L5989
      if (v3828) {	// L5990
        a_vld5 = 0;	// L5991
      }
    }
    int32_t v3829 = s25;	// L5994
    bool v3830 = v3829 < 8;	// L5995
    int32_t v3831 = dsmask5;	// L5996
    int32_t v3832 = v3831 >> v3829;	// L5997
    int32_t v3833 = v3832 & 1;	// L5998
    bool v3834 = v3833 == 1;	// L5999
    bool v3835 = v3830 & v3834;	// L6000
    if (v3835) {	// L6001
      int32_t v3836 = s25;	// L6002
      int v3837 = v3836;	// L6003
      int32_t v3838 = drf_full5[v3837];	// L6004
      bool v3839 = v3838 == 0;	// L6005
      if (v3839) {	// L6006
        b_vld5 = 0;	// L6007
      }
    }
    int32_t binop5;	// L6010
    binop5 = 0;	// L6011
    int32_t v3841 = op5;	// L6012
    bool v3842 = v3841 == 0;	// L6013
    bool v3843 = v3841 == 1;	// L6014
    bool v3844 = v3841 == 2;	// L6015
    bool v3845 = v3841 == 8;	// L6016
    bool v3846 = v3841 == 9;	// L6017
    bool v3847 = v3842 | v3843;	// L6018
    bool v3848 = v3847 | v3844;	// L6019
    bool v3849 = v3848 | v3845;	// L6020
    bool v3850 = v3849 | v3846;	// L6021
    if (v3850) {	// L6022
      binop5 = 1;	// L6023
    }
    int32_t grant5;	// L6025
    grant5 = 0;	// L6026
    int32_t v3852 = pc5;	// L6027
    bool v3853 = v3852 >= 0;	// L6028
    if (v3853) {	// L6029
      grant5 = 1;	// L6030
    }
    int32_t v3854 = pc5;	// L6032
    bool v3855 = v3854 >= 0;	// L6033
    int32_t v3856 = a_vld5;	// L6034
    bool v3857 = v3856 == 0;	// L6035
    int32_t v3858 = binop5;	// L6036
    bool v3859 = v3858 == 1;	// L6037
    int32_t v3860 = b_vld5;	// L6038
    bool v3861 = v3860 == 0;	// L6039
    bool v3862 = v3859 & v3861;	// L6040
    bool v3863 = v3857 | v3862;	// L6041
    bool v3864 = v3855 & v3863;	// L6042
    if (v3864) {	// L6043
      grant5 = 0;	// L6044
    }
    int32_t v3865 = grant5;	// L6046
    bool v3866 = v3865 == 1;	// L6047
    if (v3866) {	// L6048
      int32_t v3867 = instr_cnt5;	// L6049
      int32_t v3868 = cfg_isz5;	// L6050
      bool v3869 = v3867 == v3868;	// L6051
      if (v3869) {	// L6052
        instr_cnt5 = 0;	// L6053
        int32_t v3870 = iter_cnt5;	// L6054
        int32_t v3871 = cfg_itsz5;	// L6055
        ap_int<33> v3872 = v3871;	// L6056
        ap_int<33> v3873 = v3872 - 1;	// L6057
        ap_int<33> v3874 = v3870;	// L6058
        bool v3875 = v3874 == v3873;	// L6059
        if (v3875) {	// L6060
          fetch_en5 = 0;	// L6061
        } else {
          int32_t v3876 = iter_cnt5;	// L6063
          ap_int<33> v3877 = v3876;	// L6064
          ap_int<33> v3878 = v3877 + 1;	// L6065
          int32_t v3879 = v3878;	// L6066
          iter_cnt5 = v3879;	// L6067
        }
      } else {
        int32_t v3880 = instr_cnt5;	// L6070
        ap_int<33> v3881 = v3880;	// L6071
        ap_int<33> v3882 = v3881 + 1;	// L6072
        int32_t v3883 = v3882;	// L6073
        instr_cnt5 = v3883;	// L6074
      }
    }
    int32_t c15;	// L6077
    c15 = -1;	// L6078
    int32_t c25;	// L6079
    c25 = -1;	// L6080
    int32_t v3886 = grant5;	// L6081
    bool v3887 = v3886 == 1;	// L6082
    int32_t v3888 = s15;	// L6083
    bool v3889 = v3888 >= 12;	// L6084
    bool v3890 = v3887 & v3889;	// L6085
    if (v3890) {	// L6086
      int32_t v3891 = s15;	// L6087
      int32_t v3892 = v3891 & 3;	// L6088
      c15 = v3892;	// L6089
    }
    int32_t v3893 = grant5;	// L6091
    bool v3894 = v3893 == 1;	// L6092
    int32_t v3895 = s25;	// L6093
    bool v3896 = v3895 >= 12;	// L6094
    bool v3897 = v3894 & v3896;	// L6095
    if (v3897) {	// L6096
      int32_t v3898 = s25;	// L6097
      int32_t v3899 = v3898 & 3;	// L6098
      c25 = v3899;	// L6099
    }
    int32_t v3900 = c15;	// L6101
    bool v3901 = v3900 >= 0;	// L6102
    if (v3901) {	// L6103
      int32_t v3902 = c15;	// L6104
      int v3903 = v3902;	// L6105
      half v3904 = hold_v5[v3903][1];	// L6106
      hold_v5[v3903][0] = v3904;	// L6107
      int32_t v3905 = c15;	// L6108
      int v3906 = v3905;	// L6109
      int32_t v3907 = hold_cnt5[v3906];	// L6110
      ap_int<33> v3908 = v3907;	// L6111
      ap_int<33> v3909 = v3908 - 1;	// L6112
      int32_t v3910 = v3909;	// L6113
      hold_cnt5[v3906] = v3910;	// L6114
    }
    int32_t v3911 = c25;	// L6116
    bool v3912 = v3911 >= 0;	// L6117
    int32_t v3913 = c15;	// L6118
    bool v3914 = v3911 != v3913;	// L6119
    bool v3915 = v3912 & v3914;	// L6120
    if (v3915) {	// L6121
      int32_t v3916 = c25;	// L6122
      int v3917 = v3916;	// L6123
      half v3918 = hold_v5[v3917][1];	// L6124
      hold_v5[v3917][0] = v3918;	// L6125
      int32_t v3919 = c25;	// L6126
      int v3920 = v3919;	// L6127
      int32_t v3921 = hold_cnt5[v3920];	// L6128
      ap_int<33> v3922 = v3921;	// L6129
      ap_int<33> v3923 = v3922 - 1;	// L6130
      int32_t v3924 = v3923;	// L6131
      hold_cnt5[v3920] = v3924;	// L6132
    }
    int32_t v3925 = grant5;	// L6134
    bool v3926 = v3925 == 1;	// L6135
    int32_t v3927 = s15;	// L6136
    bool v3928 = v3927 < 8;	// L6137
    int32_t v3929 = dsmask5;	// L6138
    int32_t v3930 = v3929 >> v3927;	// L6139
    int32_t v3931 = v3930 & 1;	// L6140
    bool v3932 = v3931 == 1;	// L6141
    bool v3933 = v3926 & v3928;	// L6142
    bool v3934 = v3933 & v3932;	// L6143
    if (v3934) {	// L6144
      int32_t v3935 = s15;	// L6145
      int v3936 = v3935;	// L6146
      drf_full5[v3936] = 0;	// L6147
    }
    int32_t v3937 = grant5;	// L6149
    bool v3938 = v3937 == 1;	// L6150
    int32_t v3939 = s25;	// L6151
    bool v3940 = v3939 < 8;	// L6152
    int32_t v3941 = dsmask5;	// L6153
    int32_t v3942 = v3941 >> v3939;	// L6154
    int32_t v3943 = v3942 & 1;	// L6155
    bool v3944 = v3943 == 1;	// L6156
    bool v3945 = v3938 & v3940;	// L6157
    bool v3946 = v3945 & v3944;	// L6158
    if (v3946) {	// L6159
      int32_t v3947 = s25;	// L6160
      int v3948 = v3947;	// L6161
      drf_full5[v3948] = 0;	// L6162
    }
    half res5;	// L6164
    res5 = (double)0.000000;	// L6165
    int32_t v3950 = op5;	// L6166
    bool v3951 = v3950 == 0;	// L6167
    if (v3951) {	// L6168
      half v3952 = a5;	// L6169
      half v3953 = b5;	// L6170
      half v3954 = v3952 + v3953;	// L6171
      res5 = v3954;	// L6172
    } else {
      int32_t v3955 = op5;	// L6174
      bool v3956 = v3955 == 1;	// L6175
      if (v3956) {	// L6176
        half v3957 = a5;	// L6177
        half v3958 = b5;	// L6178
        half v3959 = v3957 - v3958;	// L6179
        res5 = v3959;	// L6180
      } else {
        int32_t v3960 = op5;	// L6182
        bool v3961 = v3960 == 2;	// L6183
        if (v3961) {	// L6184
          half v3962 = a5;	// L6185
          half v3963 = b5;	// L6186
          half v3964 = v3962 * v3963;	// L6187
          res5 = v3964;	// L6188
        } else {
          int32_t v3965 = op5;	// L6190
          bool v3966 = v3965 == 8;	// L6191
          if (v3966) {	// L6192
            half v3967 = a5;	// L6193
            half v3968 = b5;	// L6194
            bool v3969 = v3967 >= v3968;	// L6195
            if (v3969) {	// L6196
              res5 = (double)1.000000;	// L6197
            } else {
              res5 = (double)-1.000000;	// L6199
            }
          } else {
            int32_t v3970 = op5;	// L6202
            bool v3971 = v3970 == 9;	// L6203
            if (v3971) {	// L6204
              half v3972 = a5;	// L6205
              half v3973 = b5;	// L6206
              bool v3974 = v3972 < v3973;	// L6207
              if (v3974) {	// L6208
                res5 = (double)1.000000;	// L6209
              } else {
                res5 = (double)-1.000000;	// L6211
              }
            } else {
              half v3975 = a5;	// L6214
              res5 = v3975;	// L6215
            }
          }
        }
      }
    }
    int32_t v3976 = a_vld5;	// L6221
    int32_t res_vld5;	// L6222
    res_vld5 = v3976;	// L6223
    int32_t v3978 = op5;	// L6224
    bool v3979 = v3978 == 0;	// L6225
    bool v3980 = v3978 == 1;	// L6226
    bool v3981 = v3978 == 2;	// L6227
    bool v3982 = v3978 == 8;	// L6228
    bool v3983 = v3978 == 9;	// L6229
    bool v3984 = v3979 | v3980;	// L6230
    bool v3985 = v3984 | v3981;	// L6231
    bool v3986 = v3985 | v3982;	// L6232
    bool v3987 = v3986 | v3983;	// L6233
    if (v3987) {	// L6234
      int32_t v3988 = a_vld5;	// L6235
      int32_t v3989 = b_vld5;	// L6236
      int64_t v3990 = v3988;	// L6237
      int64_t v3991 = v3989;	// L6238
      int64_t v3992 = v3990 * v3991;	// L6239
      int32_t v3993 = v3992;	// L6240
      res_vld5 = v3993;	// L6241
    }
    int32_t v3994 = grant5;	// L6243
    bool v3995 = v3994 == 0;	// L6244
    if (v3995) {	// L6245
      res_vld5 = 0;	// L6246
    }
    int32_t v3996 = grant5;	// L6248
    bool v3997 = v3996 == 1;	// L6249
    int32_t v3998 = op5;	// L6250
    bool v3999 = v3998 == 8;	// L6251
    bool v4000 = v3997 & v3999;	// L6252
    if (v4000) {	// L6253
      condition_reg5 = 0;	// L6254
      half v4001 = a5;	// L6255
      half v4002 = b5;	// L6256
      bool v4003 = v4001 >= v4002;	// L6257
      if (v4003) {	// L6258
        condition_reg5 = 1;	// L6259
      }
    }
    int32_t v4004 = grant5;	// L6262
    bool v4005 = v4004 == 1;	// L6263
    int32_t v4006 = op5;	// L6264
    bool v4007 = v4006 == 9;	// L6265
    bool v4008 = v4005 & v4007;	// L6266
    if (v4008) {	// L6267
      condition_reg5 = 0;	// L6268
      half v4009 = a5;	// L6269
      half v4010 = b5;	// L6270
      bool v4011 = v4009 < v4010;	// L6271
      if (v4011) {	// L6272
        condition_reg5 = 1;	// L6273
      }
    }
    ap_uint<17> tx_n5;	// L6276
    tx_n5 = 0;	// L6277
    ap_uint<17> tx_s5;	// L6278
    tx_s5 = 0;	// L6279
    ap_uint<17> tx_w5;	// L6280
    tx_w5 = 0;	// L6281
    ap_uint<17> tx_e5;	// L6282
    tx_e5 = 0;	// L6283
    int32_t is_rtr5;	// L6284
    is_rtr5 = 0;	// L6285
    int32_t do_inj5;	// L6286
    do_inj5 = 0;	// L6287
    int32_t v4018 = op5;	// L6288
    bool v4019 = v4018 >= 4;	// L6289
    ap_int<33> v4020 = v4018;	// L6290
    bool v4021 = v4020 <= 7;	// L6291
    bool v4022 = v4019 & v4021;	// L6292
    if (v4022) {	// L6293
      is_rtr5 = 1;	// L6294
      do_inj5 = 1;	// L6295
    }
    int32_t v4023 = op5;	// L6297
    bool v4024 = v4023 >= 12;	// L6298
    ap_int<33> v4025 = v4023;	// L6299
    bool v4026 = v4025 <= 15;	// L6300
    bool v4027 = v4024 & v4026;	// L6301
    if (v4027) {	// L6302
      is_rtr5 = 1;	// L6303
      int32_t v4028 = condition_reg5;	// L6304
      bool v4029 = v4028 == 1;	// L6305
      if (v4029) {	// L6306
        do_inj5 = 1;	// L6307
      }
    }
    int32_t v4030 = is_rtr5;	// L6310
    bool v4031 = v4030 == 1;	// L6311
    if (v4031) {	// L6312
      int32_t v4032 = do_inj5;	// L6313
      bool v4033 = v4032 == 1;	// L6314
      ap_int<26> v4034 = csd_pkt5;	// L6315
      bool v4035;
      ap_int<26> v4035_tmp = v4034;
      v4035 = v4035_tmp[25];	// L6316
      int32_t v4036 = v4035;	// L6317
      bool v4037 = v4036 == 0;	// L6318
      bool v4038 = v4033 & v4037;	// L6319
      if (v4038) {	// L6320
        half v4039 = res5;	// L6321
        uint16_t v4040;
        union { half from; uint16_t to;} _converter_v4039_to_v4040;
        _converter_v4039_to_v4040.from = v4039;
        v4040 = _converter_v4039_to_v4040.to;	// L6322
        ap_int<26> v4041 = csd_pkt5;	// L6323
        ap_int<26> v4042;
        ap_int<26> v4042_tmp = v4041;
        v4042_tmp(15, 0) = v4040;
        v4042 = v4042_tmp;	// L6324
        csd_pkt5 = v4042;	// L6325
        int32_t v4043 = dst5;	// L6326
        ap_uint<4> v4044 = v4043;	// L6327
        ap_int<26> v4045 = csd_pkt5;	// L6328
        ap_int<26> v4046;
        ap_int<26> v4046_tmp = v4045;
        v4046_tmp(19, 16) = v4044;
        v4046 = v4046_tmp;	// L6329
        csd_pkt5 = v4046;	// L6330
        int32_t v4047 = s25;	// L6331
        ap_uint<4> v4048 = v4047;	// L6332
        ap_int<26> v4049 = csd_pkt5;	// L6333
        ap_int<26> v4050;
        ap_int<26> v4050_tmp = v4049;
        v4050_tmp(24, 21) = v4048;
        v4050 = v4050_tmp;	// L6334
        csd_pkt5 = v4050;	// L6335
        int32_t v4051 = res_vld5;	// L6336
        bool v4052 = v4051;	// L6337
        ap_int<26> v4053 = csd_pkt5;	// L6338
        ap_int<26> v4054;
        ap_int<26> v4054_tmp = v4053;
        v4054_tmp[25] = v4052;        v4054 = v4054_tmp;	// L6339
        csd_pkt5 = v4054;	// L6340
        int32_t v4055 = op5;	// L6341
        int32_t v4056 = v4055 & 3;	// L6342
        csd_dir5 = v4056;	// L6343
      }
    } else {
      int32_t v4057 = dst5;	// L6346
      bool v4058 = v4057 >= 12;	// L6347
      if (v4058) {	// L6348
        ap_uint<17> tw5;	// L6349
        tw5 = 0;	// L6350
        int32_t v4060 = res_vld5;	// L6351
        bool v4061 = v4060;	// L6352
        ap_int<17> v4062 = tw5;	// L6353
        ap_int<17> v4063;
        ap_int<17> v4063_tmp = v4062;
        v4063_tmp[0] = v4061;        v4063 = v4063_tmp;	// L6354
        tw5 = v4063;	// L6355
        half v4064 = res5;	// L6356
        uint16_t v4065;
        union { half from; uint16_t to;} _converter_v4064_to_v4065;
        _converter_v4064_to_v4065.from = v4064;
        v4065 = _converter_v4064_to_v4065.to;	// L6357
        ap_int<17> v4066 = tw5;	// L6358
        ap_int<17> v4067;
        ap_int<17> v4067_tmp = v4066;
        v4067_tmp(16, 1) = v4065;
        v4067 = v4067_tmp;	// L6359
        tw5 = v4067;	// L6360
        int32_t v4068 = dst5;	// L6361
        int32_t v4069 = v4068 & 3;	// L6362
        bool v4070 = v4069 == 0;	// L6363
        if (v4070) {	// L6364
          ap_int<17> v4071 = tw5;	// L6365
          tx_n5 = v4071;	// L6366
        } else {
          int32_t v4072 = dst5;	// L6368
          int32_t v4073 = v4072 & 3;	// L6369
          bool v4074 = v4073 == 1;	// L6370
          if (v4074) {	// L6371
            ap_int<17> v4075 = tw5;	// L6372
            tx_s5 = v4075;	// L6373
          } else {
            int32_t v4076 = dst5;	// L6375
            int32_t v4077 = v4076 & 3;	// L6376
            bool v4078 = v4077 == 2;	// L6377
            if (v4078) {	// L6378
              ap_int<17> v4079 = tw5;	// L6379
              tx_w5 = v4079;	// L6380
            } else {
              ap_int<17> v4080 = tw5;	// L6382
              tx_e5 = v4080;	// L6383
            }
          }
        }
      } else {
        int32_t v4081 = res_vld5;	// L6388
        bool v4082 = v4081 == 1;	// L6389
        if (v4082) {	// L6390
          int32_t v4083 = dst5;	// L6391
          bool v4084 = v4083 < 8;	// L6392
          int32_t v4085 = dsmask5;	// L6393
          int32_t v4086 = v4085 >> v4083;	// L6394
          int32_t v4087 = v4086 & 1;	// L6395
          bool v4088 = v4087 == 1;	// L6396
          bool v4089 = v4084 & v4088;	// L6397
          if (v4089) {	// L6398
            int32_t v4090 = dst5;	// L6399
            int v4091 = v4090;	// L6400
            int32_t v4092 = drf_full5[v4091];	// L6401
            bool v4093 = v4092 == 0;	// L6402
            if (v4093) {	// L6403
              half v4094 = res5;	// L6404
              int32_t v4095 = dst5;	// L6405
              int v4096 = v4095;	// L6406
              drf5[v4096] = v4094;	// L6407
              int32_t v4097 = dst5;	// L6408
              int v4098 = v4097;	// L6409
              drf_full5[v4098] = 1;	// L6410
            }
          } else {
            half v4099 = res5;	// L6413
            int32_t v4100 = dst5;	// L6414
            int v4101 = v4100;	// L6415
            drf5[v4101] = v4099;	// L6416
          }
        }
      }
    }
    ap_int<17> v4102 = tx_n5;	// L6421
    txn_r5 = v4102;	// L6422
    ap_int<17> v4103 = tx_s5;	// L6423
    txs_r5 = v4103;	// L6424
    ap_int<17> v4104 = tx_w5;	// L6425
    txw_r5 = v4104;	// L6426
    ap_int<17> v4105 = tx_e5;	// L6427
    txe_r5 = v4105;	// L6428
    int32_t v4106 = crv_vld5;	// L6429
    bool v4107 = v4106 == 1;	// L6430
    if (v4107) {	// L6431
      int32_t v4108 = crv_mode5;	// L6432
      bool v4109 = v4108 == 1;	// L6433
      if (v4109) {	// L6434
        int32_t v4110 = crv_addr5;	// L6435
        int32_t v4111 = v4110 >> 3;	// L6436
        int32_t v4112 = v4111 & 1;	// L6437
        bool v4113 = v4112 == 1;	// L6438
        if (v4113) {	// L6439
          int32_t v4114 = crv_raw5;	// L6440
          int32_t v4115 = crv_addr5;	// L6441
          int32_t v4116 = v4115 & 7;	// L6442
          int v4117 = v4116;	// L6443
          irf5[v4117] = v4114;	// L6444
        } else {
          int32_t v4118 = crv_addr5;	// L6446
          bool v4119 = v4118 == 0;	// L6447
          if (v4119) {	// L6448
            int32_t v4120 = crv_raw5;	// L6449
            int32_t v4121 = v4120 & 255;	// L6450
            dsmask5 = v4121;	// L6451
            int32_t v4122 = crv_raw5;	// L6452
            int32_t v4123 = v4122 >> 8;	// L6453
            int32_t v4124 = v4123 & 7;	// L6454
            cfg_isz5 = v4124;	// L6455
            int32_t v4125 = crv_raw5;	// L6456
            int32_t v4126 = v4125 >> 15;	// L6457
            int32_t v4127 = v4126 & 1;	// L6458
            bool v4128 = v4127 == 1;	// L6459
            if (v4128) {	// L6460
              fetch_en5 = 1;	// L6461
              instr_cnt5 = 0;	// L6462
              iter_cnt5 = 0;	// L6463
            }
          } else {
            int32_t v4129 = crv_addr5;	// L6466
            bool v4130 = v4129 == 1;	// L6467
            if (v4130) {	// L6468
              int32_t v4131 = crv_raw5;	// L6469
              int32_t v4132 = v4131 & 255;	// L6470
              cfg_itsz5 = v4132;	// L6471
            }
          }
        }
      } else {
        int32_t v4133 = crv_addr5;	// L6476
        bool v4134 = v4133 < 8;	// L6477
        int32_t v4135 = dsmask5;	// L6478
        int32_t v4136 = v4135 >> v4133;	// L6479
        int32_t v4137 = v4136 & 1;	// L6480
        bool v4138 = v4137 == 1;	// L6481
        bool v4139 = v4134 & v4138;	// L6482
        if (v4139) {	// L6483
          int32_t v4140 = crv_addr5;	// L6484
          int v4141 = v4140;	// L6485
          int32_t v4142 = drf_full5[v4141];	// L6486
          bool v4143 = v4142 == 0;	// L6487
          if (v4143) {	// L6488
            half v4144 = crv_data5;	// L6489
            int32_t v4145 = crv_addr5;	// L6490
            int v4146 = v4145;	// L6491
            drf5[v4146] = v4144;	// L6492
            int32_t v4147 = crv_addr5;	// L6493
            int v4148 = v4147;	// L6494
            drf_full5[v4148] = 1;	// L6495
          }
        } else {
          half v4149 = crv_data5;	// L6498
          int32_t v4150 = crv_addr5;	// L6499
          int v4151 = v4150;	// L6500
          drf5[v4151] = v4149;	// L6501
        }
      }
    }
  }
}

void node_1_2(
  hls::stream< ap_uint<26> >& v4152,
  hls::stream< ap_uint<26> >& v4153,
  hls::stream< ap_uint<26> >& v4154,
  hls::stream< ap_uint<26> >& v4155,
  hls::stream< ap_uint<17> >& v4156,
  hls::stream< ap_uint<17> >& v4157,
  hls::stream< ap_uint<17> >& v4158,
  hls::stream< ap_uint<17> >& v4159,
  hls::stream< int32_t >& v4160,
  hls::stream< int32_t >& v4161,
  hls::stream< int32_t >& v4162,
  hls::stream< int32_t >& v4163,
  hls::stream< ap_uint<26> >& v4164,
  hls::stream< ap_uint<26> >& v4165,
  hls::stream< ap_uint<26> >& v4166,
  hls::stream< ap_uint<26> >& v4167,
  hls::stream< int32_t >& v4168,
  hls::stream< int32_t >& v4169,
  hls::stream< int32_t >& v4170,
  hls::stream< int32_t >& v4171,
  hls::stream< ap_uint<17> >& v4172,
  hls::stream< ap_uint<17> >& v4173,
  hls::stream< ap_uint<17> >& v4174,
  hls::stream< ap_uint<17> >& v4175
) {	// L6508
  int32_t irf6[8];	// L6539
  for (int v4177 = 0; v4177 < 8; v4177++) {	// L6540
    irf6[v4177] = 0;	// L6540
  }
  half drf6[8];	// L6541
  #pragma HLS array_partition variable=drf6 complete dim=1

  for (int v4179 = 0; v4179 < 8; v4179++) {	// L6542
    drf6[v4179] = (double)0.000000;	// L6542
  }
  int32_t drf_full6[8];	// L6543
  #pragma HLS array_partition variable=drf_full6 complete dim=1

  for (int v4181 = 0; v4181 < 8; v4181++) {	// L6544
    drf_full6[v4181] = 0;	// L6544
  }
  int32_t dsmask6;	// L6545
  dsmask6 = 0;	// L6546
  int32_t crv_vld6;	// L6547
  crv_vld6 = 0;	// L6548
  half crv_data6;	// L6549
  crv_data6 = (double)0.000000;	// L6550
  int32_t crv_addr6;	// L6551
  crv_addr6 = 0;	// L6552
  int32_t crv_mode6;	// L6553
  crv_mode6 = 0;	// L6554
  int32_t crv_raw6;	// L6555
  crv_raw6 = 0;	// L6556
  int32_t csd_vld6;	// L6557
  csd_vld6 = 0;	// L6558
  ap_uint<26> csd_pkt6;	// L6559
  csd_pkt6 = 0;	// L6560
  int32_t csd_dir6;	// L6561
  csd_dir6 = 0;	// L6562
  int32_t row_id6;	// L6563
  row_id6 = 1;	// L6564
  int32_t col_id6;	// L6565
  col_id6 = 2;	// L6566
  ap_uint<26> oe_r6;	// L6567
  oe_r6 = 0;	// L6568
  ap_uint<26> ow_r6;	// L6569
  ow_r6 = 0;	// L6570
  ap_uint<26> on_r6;	// L6571
  on_r6 = 0;	// L6572
  ap_uint<26> os_r6;	// L6573
  os_r6 = 0;	// L6574
  ap_uint<17> txn_r6;	// L6575
  txn_r6 = 0;	// L6576
  ap_uint<17> txs_r6;	// L6577
  txs_r6 = 0;	// L6578
  ap_uint<17> txw_r6;	// L6579
  txw_r6 = 0;	// L6580
  ap_uint<17> txe_r6;	// L6581
  txe_r6 = 0;	// L6582
  half hold_v6[4][2];	// L6583
  #pragma HLS array_partition variable=hold_v6 complete dim=1
  #pragma HLS array_partition variable=hold_v6 complete dim=2

  for (int v4202 = 0; v4202 < 4; v4202++) {	// L6584
    for (int v4203 = 0; v4203 < 2; v4203++) {	// L6584
      hold_v6[v4202][v4203] = (double)0.000000;	// L6584
    }
  }
  int32_t hold_cnt6[4];	// L6585
  #pragma HLS array_partition variable=hold_cnt6 complete dim=1

  for (int v4205 = 0; v4205 < 4; v4205++) {	// L6586
    hold_cnt6[v4205] = 0;	// L6586
  }
  ap_uint<26> rbuf6[4][2];	// L6587
  #pragma HLS array_partition variable=rbuf6 complete dim=1
  #pragma HLS array_partition variable=rbuf6 complete dim=2

  for (int v4207 = 0; v4207 < 4; v4207++) {	// L6588
    for (int v4208 = 0; v4208 < 2; v4208++) {	// L6588
      rbuf6[v4207][v4208] = 0;	// L6588
    }
  }
  int32_t rbcnt6[4];	// L6589
  #pragma HLS array_partition variable=rbcnt6 complete dim=1

  for (int v4210 = 0; v4210 < 4; v4210++) {	// L6590
    rbcnt6[v4210] = 0;	// L6590
  }
  int32_t rcred6[4];	// L6591
  #pragma HLS array_partition variable=rcred6 complete dim=1

  for (int v4212 = 0; v4212 < 4; v4212++) {	// L6592
    rcred6[v4212] = 0;	// L6592
  }
  int32_t cre_r6;	// L6593
  cre_r6 = 2;	// L6594
  int32_t crw_r6;	// L6595
  crw_r6 = 2;	// L6596
  int32_t crs_r6;	// L6597
  crs_r6 = 2;	// L6598
  int32_t crn_r6;	// L6599
  crn_r6 = 2;	// L6600
  int32_t cfg_isz6;	// L6601
  cfg_isz6 = 0;	// L6602
  int32_t cfg_itsz6;	// L6603
  cfg_itsz6 = 0;	// L6604
  int32_t fetch_en6;	// L6605
  fetch_en6 = 0;	// L6606
  int32_t instr_cnt6;	// L6607
  instr_cnt6 = 0;	// L6608
  int32_t iter_cnt6;	// L6609
  iter_cnt6 = 0;	// L6610
  int32_t condition_reg6;	// L6611
  condition_reg6 = 0;	// L6612
  l_S_t_0_t6: for (int t6 = 0; t6 < 8; t6++) {	// L6613
  #pragma HLS pipeline II=1
    ap_int<26> v4224 = oe_r6;	// L6614
    v4152.write(v4224);	// L6615
    ap_int<26> v4225 = ow_r6;	// L6616
    v4153.write(v4225);	// L6617
    ap_int<26> v4226 = os_r6;	// L6618
    v4154.write(v4226);	// L6619
    ap_int<26> v4227 = on_r6;	// L6620
    v4155.write(v4227);	// L6621
    ap_int<17> v4228 = txe_r6;	// L6622
    v4156.write(v4228);	// L6623
    ap_int<17> v4229 = txw_r6;	// L6624
    v4157.write(v4229);	// L6625
    ap_int<17> v4230 = txs_r6;	// L6626
    v4158.write(v4230);	// L6627
    ap_int<17> v4231 = txn_r6;	// L6628
    v4159.write(v4231);	// L6629
    int32_t v4232 = cre_r6;	// L6630
    v4160.write(v4232);	// L6631
    int32_t v4233 = crw_r6;	// L6632
    v4161.write(v4233);	// L6633
    int32_t v4234 = crs_r6;	// L6634
    v4162.write(v4234);	// L6635
    int32_t v4235 = crn_r6;	// L6636
    v4163.write(v4235);	// L6637
    ap_uint<26> v4236 = v4164.read();	// L6638
    ap_uint<26> p_w6;	// L6639
    p_w6 = v4236;	// L6640
    ap_uint<26> v4238 = v4165.read();	// L6641
    ap_uint<26> p_e6;	// L6642
    p_e6 = v4238;	// L6643
    ap_uint<26> v4240 = v4166.read();	// L6644
    ap_uint<26> p_n6;	// L6645
    p_n6 = v4240;	// L6646
    ap_uint<26> v4242 = v4167.read();	// L6647
    ap_uint<26> p_s6;	// L6648
    p_s6 = v4242;	// L6649
    int32_t v4244 = v4168.read();	// L6650
    int32_t v4245 = rcred6[0];	// L6651
    ap_int<33> v4246 = v4245;	// L6652
    ap_int<33> v4247 = v4244;	// L6653
    ap_int<33> v4248 = v4246 + v4247;	// L6654
    int32_t v4249 = v4248;	// L6655
    rcred6[0] = v4249;	// L6656
    int32_t v4250 = v4169.read();	// L6657
    int32_t v4251 = rcred6[1];	// L6658
    ap_int<33> v4252 = v4251;	// L6659
    ap_int<33> v4253 = v4250;	// L6660
    ap_int<33> v4254 = v4252 + v4253;	// L6661
    int32_t v4255 = v4254;	// L6662
    rcred6[1] = v4255;	// L6663
    int32_t v4256 = v4170.read();	// L6664
    int32_t v4257 = rcred6[2];	// L6665
    ap_int<33> v4258 = v4257;	// L6666
    ap_int<33> v4259 = v4256;	// L6667
    ap_int<33> v4260 = v4258 + v4259;	// L6668
    int32_t v4261 = v4260;	// L6669
    rcred6[2] = v4261;	// L6670
    int32_t v4262 = v4171.read();	// L6671
    int32_t v4263 = rcred6[3];	// L6672
    ap_int<33> v4264 = v4263;	// L6673
    ap_int<33> v4265 = v4262;	// L6674
    ap_int<33> v4266 = v4264 + v4265;	// L6675
    int32_t v4267 = v4266;	// L6676
    rcred6[3] = v4267;	// L6677
    ap_uint<26> fin6[4];	// L6678
    for (int v4269 = 0; v4269 < 4; v4269++) {	// L6679
      fin6[v4269] = 0;	// L6679
    }
    ap_int<26> v4270 = p_w6;	// L6680
    fin6[0] = v4270;	// L6681
    ap_int<26> v4271 = p_e6;	// L6682
    fin6[1] = v4271;	// L6683
    ap_int<26> v4272 = p_n6;	// L6684
    fin6[2] = v4272;	// L6685
    ap_int<26> v4273 = p_s6;	// L6686
    fin6[3] = v4273;	// L6687
    l_S_d_0_d24: for (int d24 = 0; d24 < 4; d24++) {	// L6688
      ap_uint<26> v4275 = fin6[d24];	// L6689
      bool v4276;
      ap_int<26> v4276_tmp = v4275;
      v4276 = v4276_tmp[25];	// L6690
      int32_t v4277 = v4276;	// L6691
      bool v4278 = v4277 == 1;	// L6692
      int32_t v4279 = rbcnt6[d24];	// L6693
      bool v4280 = v4279 < 2;	// L6694
      bool v4281 = v4278 & v4280;	// L6695
      if (v4281) {	// L6696
        ap_uint<26> v4282 = fin6[d24];	// L6697
        int32_t v4283 = rbcnt6[d24];	// L6698
        int v4284 = v4283;	// L6699
        rbuf6[d24][v4284] = v4282;	// L6700
        int32_t v4285 = rbcnt6[d24];	// L6701
        ap_int<33> v4286 = v4285;	// L6702
        ap_int<33> v4287 = v4286 + 1;	// L6703
        int32_t v4288 = v4287;	// L6704
        rbcnt6[d24] = v4288;	// L6705
      }
    }
    ap_uint<26> hd6[4];	// L6708
    for (int v4290 = 0; v4290 < 4; v4290++) {	// L6709
      hd6[v4290] = 0;	// L6709
    }
    int32_t hvld6[4];	// L6710
    for (int v4292 = 0; v4292 < 4; v4292++) {	// L6711
      hvld6[v4292] = 0;	// L6711
    }
    int32_t hit6[4];	// L6712
    for (int v4294 = 0; v4294 < 4; v4294++) {	// L6713
      hit6[v4294] = 0;	// L6713
    }
    int32_t axis6[4];	// L6714
    for (int v4296 = 0; v4296 < 4; v4296++) {	// L6715
      axis6[v4296] = 0;	// L6715
    }
    int32_t v4297 = col_id6;	// L6716
    axis6[0] = v4297;	// L6717
    int32_t v4298 = col_id6;	// L6718
    axis6[1] = v4298;	// L6719
    int32_t v4299 = row_id6;	// L6720
    axis6[2] = v4299;	// L6721
    int32_t v4300 = row_id6;	// L6722
    axis6[3] = v4300;	// L6723
    l_S_d_1_d25: for (int d25 = 0; d25 < 4; d25++) {	// L6724
      int32_t v4302 = rbcnt6[d25];	// L6725
      bool v4303 = v4302 > 0;	// L6726
      if (v4303) {	// L6727
        ap_uint<26> v4304 = rbuf6[d25][0];	// L6728
        hd6[d25] = v4304;	// L6729
        hvld6[d25] = 1;	// L6730
        ap_uint<26> v4305 = hd6[d25];	// L6731
        ap_int<4> v4306;
        ap_int<26> v4306_tmp = v4305;
        v4306 = v4306_tmp(24, 21);	// L6732
        int32_t v4307 = axis6[d25];	// L6733
        int32_t v4308 = v4306;	// L6734
        bool v4309 = v4308 == v4307;	// L6735
        if (v4309) {	// L6736
          hit6[d25] = 1;	// L6737
        }
      }
    }
    ap_uint<26> o_crv6;	// L6741
    o_crv6 = 0;	// L6742
    int32_t crv_in6;	// L6743
    crv_in6 = -1;	// L6744
    int32_t v4312 = hit6[3];	// L6745
    bool v4313 = v4312 == 1;	// L6746
    if (v4313) {	// L6747
      ap_uint<26> v4314 = hd6[3];	// L6748
      o_crv6 = v4314;	// L6749
      crv_in6 = 3;	// L6750
    } else {
      int32_t v4315 = hit6[2];	// L6752
      bool v4316 = v4315 == 1;	// L6753
      if (v4316) {	// L6754
        ap_uint<26> v4317 = hd6[2];	// L6755
        o_crv6 = v4317;	// L6756
        crv_in6 = 2;	// L6757
      } else {
        int32_t v4318 = hit6[1];	// L6759
        bool v4319 = v4318 == 1;	// L6760
        if (v4319) {	// L6761
          ap_uint<26> v4320 = hd6[1];	// L6762
          o_crv6 = v4320;	// L6763
          crv_in6 = 1;	// L6764
        } else {
          int32_t v4321 = hit6[0];	// L6766
          bool v4322 = v4321 == 1;	// L6767
          if (v4322) {	// L6768
            ap_uint<26> v4323 = hd6[0];	// L6769
            o_crv6 = v4323;	// L6770
            crv_in6 = 0;	// L6771
          }
        }
      }
    }
    ap_uint<26> o_out6[4];	// L6776
    for (int v4325 = 0; v4325 < 4; v4325++) {	// L6777
      o_out6[v4325] = 0;	// L6777
    }
    int32_t pop6[4];	// L6778
    for (int v4327 = 0; v4327 < 4; v4327++) {	// L6779
      pop6[v4327] = 0;	// L6779
    }
    int32_t inj_done6;	// L6780
    inj_done6 = 0;	// L6781
    int32_t idir6;	// L6782
    idir6 = -1;	// L6783
    ap_int<26> v4330 = csd_pkt6;	// L6784
    bool v4331;
    ap_int<26> v4331_tmp = v4330;
    v4331 = v4331_tmp[25];	// L6785
    int32_t v4332 = v4331;	// L6786
    bool v4333 = v4332 == 1;	// L6787
    if (v4333) {	// L6788
      int32_t v4334 = csd_dir6;	// L6789
      ap_int<33> v4335 = v4334;	// L6790
      ap_int<33> v4336 = 3 - v4335;	// L6791
      int32_t v4337 = v4336;	// L6792
      idir6 = v4337;	// L6793
    }
    l_S_o_2_o6: for (int o6 = 0; o6 < 4; o6++) {	// L6795
      int32_t v4339 = rcred6[o6];	// L6796
      bool v4340 = v4339 > 0;	// L6797
      if (v4340) {	// L6798
        int32_t v4341 = idir6;	// L6799
        ap_int<33> v4342 = v4341;	// L6800
        ap_int<33> v4343 = o6;	// L6801
        bool v4344 = v4342 == v4343;	// L6802
        if (v4344) {	// L6803
          ap_int<26> v4345 = csd_pkt6;	// L6804
          o_out6[o6] = v4345;	// L6805
          int32_t v4346 = rcred6[o6];	// L6806
          ap_int<33> v4347 = v4346;	// L6807
          ap_int<33> v4348 = v4347 - 1;	// L6808
          int32_t v4349 = v4348;	// L6809
          rcred6[o6] = v4349;	// L6810
          inj_done6 = 1;	// L6811
        } else {
          int32_t v4350 = hvld6[o6];	// L6813
          bool v4351 = v4350 == 1;	// L6814
          int32_t v4352 = hit6[o6];	// L6815
          bool v4353 = v4352 == 0;	// L6816
          bool v4354 = v4351 & v4353;	// L6817
          if (v4354) {	// L6818
            ap_uint<26> v4355 = hd6[o6];	// L6819
            o_out6[o6] = v4355;	// L6820
            int32_t v4356 = rcred6[o6];	// L6821
            ap_int<33> v4357 = v4356;	// L6822
            ap_int<33> v4358 = v4357 - 1;	// L6823
            int32_t v4359 = v4358;	// L6824
            rcred6[o6] = v4359;	// L6825
            pop6[o6] = 1;	// L6826
          }
        }
      }
    }
    int32_t v4360 = crv_in6;	// L6831
    bool v4361 = v4360 >= 0;	// L6832
    if (v4361) {	// L6833
      int32_t v4362 = crv_in6;	// L6834
      int v4363 = v4362;	// L6835
      pop6[v4363] = 1;	// L6836
    }
    int32_t ret6[4];	// L6838
    for (int v4365 = 0; v4365 < 4; v4365++) {	// L6839
      ret6[v4365] = 0;	// L6839
    }
    l_S_d_3_d26: for (int d26 = 0; d26 < 4; d26++) {	// L6840
      int32_t v4367 = pop6[d26];	// L6841
      bool v4368 = v4367 == 1;	// L6842
      if (v4368) {	// L6843
        l_S_sft_3_sft6: for (int sft6 = 0; sft6 < 1; sft6++) {	// L6844
          ap_uint<26> v4370 = rbuf6[d26][(sft6 + 1)];	// L6845
          rbuf6[d26][sft6] = v4370;	// L6846
        }
        int32_t v4371 = rbcnt6[d26];	// L6848
        ap_int<33> v4372 = v4371;	// L6849
        ap_int<33> v4373 = v4372 - 1;	// L6850
        int32_t v4374 = v4373;	// L6851
        rbcnt6[d26] = v4374;	// L6852
        ret6[d26] = 1;	// L6853
      }
    }
    int32_t v4375 = ret6[0];	// L6856
    cre_r6 = v4375;	// L6857
    int32_t v4376 = ret6[1];	// L6858
    crw_r6 = v4376;	// L6859
    int32_t v4377 = ret6[2];	// L6860
    crs_r6 = v4377;	// L6861
    int32_t v4378 = ret6[3];	// L6862
    crn_r6 = v4378;	// L6863
    ap_uint<26> v4379 = o_out6[0];	// L6864
    oe_r6 = v4379;	// L6865
    ap_uint<26> v4380 = o_out6[1];	// L6866
    ow_r6 = v4380;	// L6867
    ap_uint<26> v4381 = o_out6[2];	// L6868
    os_r6 = v4381;	// L6869
    ap_uint<26> v4382 = o_out6[3];	// L6870
    on_r6 = v4382;	// L6871
    int32_t v4383 = inj_done6;	// L6872
    bool v4384 = v4383 == 1;	// L6873
    if (v4384) {	// L6874
      csd_pkt6 = 0;	// L6875
    }
    ap_int<26> v4385 = o_crv6;	// L6877
    bool v4386;
    ap_int<26> v4386_tmp = v4385;
    v4386 = v4386_tmp[25];	// L6878
    int32_t v4387 = v4386;	// L6879
    crv_vld6 = v4387;	// L6880
    ap_int<26> v4388 = o_crv6;	// L6881
    int16_t v4389;
    ap_int<26> v4389_tmp = v4388;
    v4389 = v4389_tmp(15, 0);	// L6882
    half v4390;
    union { uint16_t from; half to;} _converter_v4389_to_v4390;
    _converter_v4389_to_v4390.from = v4389;
    v4390 = _converter_v4389_to_v4390.to;	// L6883
    crv_data6 = v4390;	// L6884
    ap_int<26> v4391 = o_crv6;	// L6885
    ap_int<4> v4392;
    ap_int<26> v4392_tmp = v4391;
    v4392 = v4392_tmp(19, 16);	// L6886
    int32_t v4393 = v4392;	// L6887
    crv_addr6 = v4393;	// L6888
    ap_int<26> v4394 = o_crv6;	// L6889
    bool v4395;
    ap_int<26> v4395_tmp = v4394;
    v4395 = v4395_tmp[20];	// L6890
    int32_t v4396 = v4395;	// L6891
    crv_mode6 = v4396;	// L6892
    ap_int<26> v4397 = o_crv6;	// L6893
    int16_t v4398;
    ap_int<26> v4398_tmp = v4397;
    v4398 = v4398_tmp(15, 0);	// L6894
    int32_t v4399 = v4398;	// L6895
    crv_raw6 = v4399;	// L6896
    ap_uint<17> v4400 = v4172.read();	// L6897
    ap_uint<17> rx_w6;	// L6898
    rx_w6 = v4400;	// L6899
    ap_uint<17> v4402 = v4173.read();	// L6900
    ap_uint<17> rx_e6;	// L6901
    rx_e6 = v4402;	// L6902
    ap_uint<17> v4404 = v4174.read();	// L6903
    ap_uint<17> rx_n6;	// L6904
    rx_n6 = v4404;	// L6905
    ap_uint<17> v4406 = v4175.read();	// L6906
    ap_uint<17> rx_s6;	// L6907
    rx_s6 = v4406;	// L6908
    half rxv6[4];	// L6909
    for (int v4409 = 0; v4409 < 4; v4409++) {	// L6910
      rxv6[v4409] = (double)0.000000;	// L6910
    }
    int32_t rxvld6[4];	// L6911
    for (int v4411 = 0; v4411 < 4; v4411++) {	// L6912
      rxvld6[v4411] = 0;	// L6912
    }
    ap_int<17> v4412 = rx_n6;	// L6913
    int16_t v4413;
    ap_int<17> v4413_tmp = v4412;
    v4413 = v4413_tmp(16, 1);	// L6914
    half v4414;
    union { uint16_t from; half to;} _converter_v4413_to_v4414;
    _converter_v4413_to_v4414.from = v4413;
    v4414 = _converter_v4413_to_v4414.to;	// L6915
    rxv6[0] = v4414;	// L6916
    ap_int<17> v4415 = rx_n6;	// L6917
    bool v4416;
    ap_int<17> v4416_tmp = v4415;
    v4416 = v4416_tmp[0];	// L6918
    int32_t v4417 = v4416;	// L6919
    rxvld6[0] = v4417;	// L6920
    ap_int<17> v4418 = rx_s6;	// L6921
    int16_t v4419;
    ap_int<17> v4419_tmp = v4418;
    v4419 = v4419_tmp(16, 1);	// L6922
    half v4420;
    union { uint16_t from; half to;} _converter_v4419_to_v4420;
    _converter_v4419_to_v4420.from = v4419;
    v4420 = _converter_v4419_to_v4420.to;	// L6923
    rxv6[1] = v4420;	// L6924
    ap_int<17> v4421 = rx_s6;	// L6925
    bool v4422;
    ap_int<17> v4422_tmp = v4421;
    v4422 = v4422_tmp[0];	// L6926
    int32_t v4423 = v4422;	// L6927
    rxvld6[1] = v4423;	// L6928
    ap_int<17> v4424 = rx_w6;	// L6929
    int16_t v4425;
    ap_int<17> v4425_tmp = v4424;
    v4425 = v4425_tmp(16, 1);	// L6930
    half v4426;
    union { uint16_t from; half to;} _converter_v4425_to_v4426;
    _converter_v4425_to_v4426.from = v4425;
    v4426 = _converter_v4425_to_v4426.to;	// L6931
    rxv6[2] = v4426;	// L6932
    ap_int<17> v4427 = rx_w6;	// L6933
    bool v4428;
    ap_int<17> v4428_tmp = v4427;
    v4428 = v4428_tmp[0];	// L6934
    int32_t v4429 = v4428;	// L6935
    rxvld6[2] = v4429;	// L6936
    ap_int<17> v4430 = rx_e6;	// L6937
    int16_t v4431;
    ap_int<17> v4431_tmp = v4430;
    v4431 = v4431_tmp(16, 1);	// L6938
    half v4432;
    union { uint16_t from; half to;} _converter_v4431_to_v4432;
    _converter_v4431_to_v4432.from = v4431;
    v4432 = _converter_v4431_to_v4432.to;	// L6939
    rxv6[3] = v4432;	// L6940
    ap_int<17> v4433 = rx_e6;	// L6941
    bool v4434;
    ap_int<17> v4434_tmp = v4433;
    v4434 = v4434_tmp[0];	// L6942
    int32_t v4435 = v4434;	// L6943
    rxvld6[3] = v4435;	// L6944
    l_S_d_5_d27: for (int d27 = 0; d27 < 4; d27++) {	// L6945
      int32_t v4437 = rxvld6[d27];	// L6946
      bool v4438 = v4437 == 1;	// L6947
      int32_t v4439 = hold_cnt6[d27];	// L6948
      bool v4440 = v4439 < 2;	// L6949
      bool v4441 = v4438 & v4440;	// L6950
      if (v4441) {	// L6951
        half v4442 = rxv6[d27];	// L6952
        int32_t v4443 = hold_cnt6[d27];	// L6953
        int v4444 = v4443;	// L6954
        hold_v6[d27][v4444] = v4442;	// L6955
        int32_t v4445 = hold_cnt6[d27];	// L6956
        ap_int<33> v4446 = v4445;	// L6957
        ap_int<33> v4447 = v4446 + 1;	// L6958
        int32_t v4448 = v4447;	// L6959
        hold_cnt6[d27] = v4448;	// L6960
      }
    }
    int32_t pc6;	// L6963
    pc6 = -1;	// L6964
    int32_t v4450 = fetch_en6;	// L6965
    bool v4451 = v4450 == 1;	// L6966
    if (v4451) {	// L6967
      int32_t v4452 = instr_cnt6;	// L6968
      pc6 = v4452;	// L6969
    }
    int32_t instr6;	// L6971
    instr6 = 0;	// L6972
    int32_t v4454 = pc6;	// L6973
    bool v4455 = v4454 >= 0;	// L6974
    if (v4455) {	// L6975
      int32_t v4456 = pc6;	// L6976
      int v4457 = v4456;	// L6977
      int32_t v4458 = irf6[v4457];	// L6978
      instr6 = v4458;	// L6979
    }
    int32_t v4459 = instr6;	// L6981
    int32_t v4460 = v4459 & 15;	// L6982
    int32_t op6;	// L6983
    op6 = v4460;	// L6984
    int32_t v4462 = instr6;	// L6985
    int32_t v4463 = v4462 >> 4;	// L6986
    int32_t v4464 = v4463 & 15;	// L6987
    int32_t dst6;	// L6988
    dst6 = v4464;	// L6989
    int32_t v4466 = instr6;	// L6990
    int32_t v4467 = v4466 >> 8;	// L6991
    int32_t v4468 = v4467 & 15;	// L6992
    int32_t s16;	// L6993
    s16 = v4468;	// L6994
    int32_t v4470 = instr6;	// L6995
    int32_t v4471 = v4470 >> 12;	// L6996
    int32_t v4472 = v4471 & 15;	// L6997
    int32_t s26;	// L6998
    s26 = v4472;	// L6999
    half a6;	// L7000
    a6 = (double)0.000000;	// L7001
    half b6;	// L7002
    b6 = (double)0.000000;	// L7003
    int32_t v4476 = s16;	// L7004
    bool v4477 = v4476 >= 12;	// L7005
    if (v4477) {	// L7006
      int32_t v4478 = s16;	// L7007
      int32_t v4479 = v4478 & 3;	// L7008
      int v4480 = v4479;	// L7009
      half v4481 = hold_v6[v4480][0];	// L7010
      a6 = v4481;	// L7011
    } else {
      int32_t v4482 = s16;	// L7013
      int v4483 = v4482;	// L7014
      half v4484 = drf6[v4483];	// L7015
      a6 = v4484;	// L7016
    }
    int32_t v4485 = s26;	// L7018
    bool v4486 = v4485 >= 12;	// L7019
    if (v4486) {	// L7020
      int32_t v4487 = s26;	// L7021
      int32_t v4488 = v4487 & 3;	// L7022
      int v4489 = v4488;	// L7023
      half v4490 = hold_v6[v4489][0];	// L7024
      b6 = v4490;	// L7025
    } else {
      int32_t v4491 = s26;	// L7027
      int v4492 = v4491;	// L7028
      half v4493 = drf6[v4492];	// L7029
      b6 = v4493;	// L7030
    }
    int32_t a_vld6;	// L7032
    a_vld6 = 1;	// L7033
    int32_t b_vld6;	// L7034
    b_vld6 = 1;	// L7035
    int32_t v4496 = s16;	// L7036
    bool v4497 = v4496 >= 12;	// L7037
    if (v4497) {	// L7038
      a_vld6 = 0;	// L7039
      int32_t v4498 = s16;	// L7040
      int32_t v4499 = v4498 & 3;	// L7041
      int v4500 = v4499;	// L7042
      int32_t v4501 = hold_cnt6[v4500];	// L7043
      bool v4502 = v4501 > 0;	// L7044
      if (v4502) {	// L7045
        a_vld6 = 1;	// L7046
      }
    }
    int32_t v4503 = s26;	// L7049
    bool v4504 = v4503 >= 12;	// L7050
    if (v4504) {	// L7051
      b_vld6 = 0;	// L7052
      int32_t v4505 = s26;	// L7053
      int32_t v4506 = v4505 & 3;	// L7054
      int v4507 = v4506;	// L7055
      int32_t v4508 = hold_cnt6[v4507];	// L7056
      bool v4509 = v4508 > 0;	// L7057
      if (v4509) {	// L7058
        b_vld6 = 1;	// L7059
      }
    }
    int32_t v4510 = s16;	// L7062
    bool v4511 = v4510 < 8;	// L7063
    int32_t v4512 = dsmask6;	// L7064
    int32_t v4513 = v4512 >> v4510;	// L7065
    int32_t v4514 = v4513 & 1;	// L7066
    bool v4515 = v4514 == 1;	// L7067
    bool v4516 = v4511 & v4515;	// L7068
    if (v4516) {	// L7069
      int32_t v4517 = s16;	// L7070
      int v4518 = v4517;	// L7071
      int32_t v4519 = drf_full6[v4518];	// L7072
      bool v4520 = v4519 == 0;	// L7073
      if (v4520) {	// L7074
        a_vld6 = 0;	// L7075
      }
    }
    int32_t v4521 = s26;	// L7078
    bool v4522 = v4521 < 8;	// L7079
    int32_t v4523 = dsmask6;	// L7080
    int32_t v4524 = v4523 >> v4521;	// L7081
    int32_t v4525 = v4524 & 1;	// L7082
    bool v4526 = v4525 == 1;	// L7083
    bool v4527 = v4522 & v4526;	// L7084
    if (v4527) {	// L7085
      int32_t v4528 = s26;	// L7086
      int v4529 = v4528;	// L7087
      int32_t v4530 = drf_full6[v4529];	// L7088
      bool v4531 = v4530 == 0;	// L7089
      if (v4531) {	// L7090
        b_vld6 = 0;	// L7091
      }
    }
    int32_t binop6;	// L7094
    binop6 = 0;	// L7095
    int32_t v4533 = op6;	// L7096
    bool v4534 = v4533 == 0;	// L7097
    bool v4535 = v4533 == 1;	// L7098
    bool v4536 = v4533 == 2;	// L7099
    bool v4537 = v4533 == 8;	// L7100
    bool v4538 = v4533 == 9;	// L7101
    bool v4539 = v4534 | v4535;	// L7102
    bool v4540 = v4539 | v4536;	// L7103
    bool v4541 = v4540 | v4537;	// L7104
    bool v4542 = v4541 | v4538;	// L7105
    if (v4542) {	// L7106
      binop6 = 1;	// L7107
    }
    int32_t grant6;	// L7109
    grant6 = 0;	// L7110
    int32_t v4544 = pc6;	// L7111
    bool v4545 = v4544 >= 0;	// L7112
    if (v4545) {	// L7113
      grant6 = 1;	// L7114
    }
    int32_t v4546 = pc6;	// L7116
    bool v4547 = v4546 >= 0;	// L7117
    int32_t v4548 = a_vld6;	// L7118
    bool v4549 = v4548 == 0;	// L7119
    int32_t v4550 = binop6;	// L7120
    bool v4551 = v4550 == 1;	// L7121
    int32_t v4552 = b_vld6;	// L7122
    bool v4553 = v4552 == 0;	// L7123
    bool v4554 = v4551 & v4553;	// L7124
    bool v4555 = v4549 | v4554;	// L7125
    bool v4556 = v4547 & v4555;	// L7126
    if (v4556) {	// L7127
      grant6 = 0;	// L7128
    }
    int32_t v4557 = grant6;	// L7130
    bool v4558 = v4557 == 1;	// L7131
    if (v4558) {	// L7132
      int32_t v4559 = instr_cnt6;	// L7133
      int32_t v4560 = cfg_isz6;	// L7134
      bool v4561 = v4559 == v4560;	// L7135
      if (v4561) {	// L7136
        instr_cnt6 = 0;	// L7137
        int32_t v4562 = iter_cnt6;	// L7138
        int32_t v4563 = cfg_itsz6;	// L7139
        ap_int<33> v4564 = v4563;	// L7140
        ap_int<33> v4565 = v4564 - 1;	// L7141
        ap_int<33> v4566 = v4562;	// L7142
        bool v4567 = v4566 == v4565;	// L7143
        if (v4567) {	// L7144
          fetch_en6 = 0;	// L7145
        } else {
          int32_t v4568 = iter_cnt6;	// L7147
          ap_int<33> v4569 = v4568;	// L7148
          ap_int<33> v4570 = v4569 + 1;	// L7149
          int32_t v4571 = v4570;	// L7150
          iter_cnt6 = v4571;	// L7151
        }
      } else {
        int32_t v4572 = instr_cnt6;	// L7154
        ap_int<33> v4573 = v4572;	// L7155
        ap_int<33> v4574 = v4573 + 1;	// L7156
        int32_t v4575 = v4574;	// L7157
        instr_cnt6 = v4575;	// L7158
      }
    }
    int32_t c16;	// L7161
    c16 = -1;	// L7162
    int32_t c26;	// L7163
    c26 = -1;	// L7164
    int32_t v4578 = grant6;	// L7165
    bool v4579 = v4578 == 1;	// L7166
    int32_t v4580 = s16;	// L7167
    bool v4581 = v4580 >= 12;	// L7168
    bool v4582 = v4579 & v4581;	// L7169
    if (v4582) {	// L7170
      int32_t v4583 = s16;	// L7171
      int32_t v4584 = v4583 & 3;	// L7172
      c16 = v4584;	// L7173
    }
    int32_t v4585 = grant6;	// L7175
    bool v4586 = v4585 == 1;	// L7176
    int32_t v4587 = s26;	// L7177
    bool v4588 = v4587 >= 12;	// L7178
    bool v4589 = v4586 & v4588;	// L7179
    if (v4589) {	// L7180
      int32_t v4590 = s26;	// L7181
      int32_t v4591 = v4590 & 3;	// L7182
      c26 = v4591;	// L7183
    }
    int32_t v4592 = c16;	// L7185
    bool v4593 = v4592 >= 0;	// L7186
    if (v4593) {	// L7187
      int32_t v4594 = c16;	// L7188
      int v4595 = v4594;	// L7189
      half v4596 = hold_v6[v4595][1];	// L7190
      hold_v6[v4595][0] = v4596;	// L7191
      int32_t v4597 = c16;	// L7192
      int v4598 = v4597;	// L7193
      int32_t v4599 = hold_cnt6[v4598];	// L7194
      ap_int<33> v4600 = v4599;	// L7195
      ap_int<33> v4601 = v4600 - 1;	// L7196
      int32_t v4602 = v4601;	// L7197
      hold_cnt6[v4598] = v4602;	// L7198
    }
    int32_t v4603 = c26;	// L7200
    bool v4604 = v4603 >= 0;	// L7201
    int32_t v4605 = c16;	// L7202
    bool v4606 = v4603 != v4605;	// L7203
    bool v4607 = v4604 & v4606;	// L7204
    if (v4607) {	// L7205
      int32_t v4608 = c26;	// L7206
      int v4609 = v4608;	// L7207
      half v4610 = hold_v6[v4609][1];	// L7208
      hold_v6[v4609][0] = v4610;	// L7209
      int32_t v4611 = c26;	// L7210
      int v4612 = v4611;	// L7211
      int32_t v4613 = hold_cnt6[v4612];	// L7212
      ap_int<33> v4614 = v4613;	// L7213
      ap_int<33> v4615 = v4614 - 1;	// L7214
      int32_t v4616 = v4615;	// L7215
      hold_cnt6[v4612] = v4616;	// L7216
    }
    int32_t v4617 = grant6;	// L7218
    bool v4618 = v4617 == 1;	// L7219
    int32_t v4619 = s16;	// L7220
    bool v4620 = v4619 < 8;	// L7221
    int32_t v4621 = dsmask6;	// L7222
    int32_t v4622 = v4621 >> v4619;	// L7223
    int32_t v4623 = v4622 & 1;	// L7224
    bool v4624 = v4623 == 1;	// L7225
    bool v4625 = v4618 & v4620;	// L7226
    bool v4626 = v4625 & v4624;	// L7227
    if (v4626) {	// L7228
      int32_t v4627 = s16;	// L7229
      int v4628 = v4627;	// L7230
      drf_full6[v4628] = 0;	// L7231
    }
    int32_t v4629 = grant6;	// L7233
    bool v4630 = v4629 == 1;	// L7234
    int32_t v4631 = s26;	// L7235
    bool v4632 = v4631 < 8;	// L7236
    int32_t v4633 = dsmask6;	// L7237
    int32_t v4634 = v4633 >> v4631;	// L7238
    int32_t v4635 = v4634 & 1;	// L7239
    bool v4636 = v4635 == 1;	// L7240
    bool v4637 = v4630 & v4632;	// L7241
    bool v4638 = v4637 & v4636;	// L7242
    if (v4638) {	// L7243
      int32_t v4639 = s26;	// L7244
      int v4640 = v4639;	// L7245
      drf_full6[v4640] = 0;	// L7246
    }
    half res6;	// L7248
    res6 = (double)0.000000;	// L7249
    int32_t v4642 = op6;	// L7250
    bool v4643 = v4642 == 0;	// L7251
    if (v4643) {	// L7252
      half v4644 = a6;	// L7253
      half v4645 = b6;	// L7254
      half v4646 = v4644 + v4645;	// L7255
      res6 = v4646;	// L7256
    } else {
      int32_t v4647 = op6;	// L7258
      bool v4648 = v4647 == 1;	// L7259
      if (v4648) {	// L7260
        half v4649 = a6;	// L7261
        half v4650 = b6;	// L7262
        half v4651 = v4649 - v4650;	// L7263
        res6 = v4651;	// L7264
      } else {
        int32_t v4652 = op6;	// L7266
        bool v4653 = v4652 == 2;	// L7267
        if (v4653) {	// L7268
          half v4654 = a6;	// L7269
          half v4655 = b6;	// L7270
          half v4656 = v4654 * v4655;	// L7271
          res6 = v4656;	// L7272
        } else {
          int32_t v4657 = op6;	// L7274
          bool v4658 = v4657 == 8;	// L7275
          if (v4658) {	// L7276
            half v4659 = a6;	// L7277
            half v4660 = b6;	// L7278
            bool v4661 = v4659 >= v4660;	// L7279
            if (v4661) {	// L7280
              res6 = (double)1.000000;	// L7281
            } else {
              res6 = (double)-1.000000;	// L7283
            }
          } else {
            int32_t v4662 = op6;	// L7286
            bool v4663 = v4662 == 9;	// L7287
            if (v4663) {	// L7288
              half v4664 = a6;	// L7289
              half v4665 = b6;	// L7290
              bool v4666 = v4664 < v4665;	// L7291
              if (v4666) {	// L7292
                res6 = (double)1.000000;	// L7293
              } else {
                res6 = (double)-1.000000;	// L7295
              }
            } else {
              half v4667 = a6;	// L7298
              res6 = v4667;	// L7299
            }
          }
        }
      }
    }
    int32_t v4668 = a_vld6;	// L7305
    int32_t res_vld6;	// L7306
    res_vld6 = v4668;	// L7307
    int32_t v4670 = op6;	// L7308
    bool v4671 = v4670 == 0;	// L7309
    bool v4672 = v4670 == 1;	// L7310
    bool v4673 = v4670 == 2;	// L7311
    bool v4674 = v4670 == 8;	// L7312
    bool v4675 = v4670 == 9;	// L7313
    bool v4676 = v4671 | v4672;	// L7314
    bool v4677 = v4676 | v4673;	// L7315
    bool v4678 = v4677 | v4674;	// L7316
    bool v4679 = v4678 | v4675;	// L7317
    if (v4679) {	// L7318
      int32_t v4680 = a_vld6;	// L7319
      int32_t v4681 = b_vld6;	// L7320
      int64_t v4682 = v4680;	// L7321
      int64_t v4683 = v4681;	// L7322
      int64_t v4684 = v4682 * v4683;	// L7323
      int32_t v4685 = v4684;	// L7324
      res_vld6 = v4685;	// L7325
    }
    int32_t v4686 = grant6;	// L7327
    bool v4687 = v4686 == 0;	// L7328
    if (v4687) {	// L7329
      res_vld6 = 0;	// L7330
    }
    int32_t v4688 = grant6;	// L7332
    bool v4689 = v4688 == 1;	// L7333
    int32_t v4690 = op6;	// L7334
    bool v4691 = v4690 == 8;	// L7335
    bool v4692 = v4689 & v4691;	// L7336
    if (v4692) {	// L7337
      condition_reg6 = 0;	// L7338
      half v4693 = a6;	// L7339
      half v4694 = b6;	// L7340
      bool v4695 = v4693 >= v4694;	// L7341
      if (v4695) {	// L7342
        condition_reg6 = 1;	// L7343
      }
    }
    int32_t v4696 = grant6;	// L7346
    bool v4697 = v4696 == 1;	// L7347
    int32_t v4698 = op6;	// L7348
    bool v4699 = v4698 == 9;	// L7349
    bool v4700 = v4697 & v4699;	// L7350
    if (v4700) {	// L7351
      condition_reg6 = 0;	// L7352
      half v4701 = a6;	// L7353
      half v4702 = b6;	// L7354
      bool v4703 = v4701 < v4702;	// L7355
      if (v4703) {	// L7356
        condition_reg6 = 1;	// L7357
      }
    }
    ap_uint<17> tx_n6;	// L7360
    tx_n6 = 0;	// L7361
    ap_uint<17> tx_s6;	// L7362
    tx_s6 = 0;	// L7363
    ap_uint<17> tx_w6;	// L7364
    tx_w6 = 0;	// L7365
    ap_uint<17> tx_e6;	// L7366
    tx_e6 = 0;	// L7367
    int32_t is_rtr6;	// L7368
    is_rtr6 = 0;	// L7369
    int32_t do_inj6;	// L7370
    do_inj6 = 0;	// L7371
    int32_t v4710 = op6;	// L7372
    bool v4711 = v4710 >= 4;	// L7373
    ap_int<33> v4712 = v4710;	// L7374
    bool v4713 = v4712 <= 7;	// L7375
    bool v4714 = v4711 & v4713;	// L7376
    if (v4714) {	// L7377
      is_rtr6 = 1;	// L7378
      do_inj6 = 1;	// L7379
    }
    int32_t v4715 = op6;	// L7381
    bool v4716 = v4715 >= 12;	// L7382
    ap_int<33> v4717 = v4715;	// L7383
    bool v4718 = v4717 <= 15;	// L7384
    bool v4719 = v4716 & v4718;	// L7385
    if (v4719) {	// L7386
      is_rtr6 = 1;	// L7387
      int32_t v4720 = condition_reg6;	// L7388
      bool v4721 = v4720 == 1;	// L7389
      if (v4721) {	// L7390
        do_inj6 = 1;	// L7391
      }
    }
    int32_t v4722 = is_rtr6;	// L7394
    bool v4723 = v4722 == 1;	// L7395
    if (v4723) {	// L7396
      int32_t v4724 = do_inj6;	// L7397
      bool v4725 = v4724 == 1;	// L7398
      ap_int<26> v4726 = csd_pkt6;	// L7399
      bool v4727;
      ap_int<26> v4727_tmp = v4726;
      v4727 = v4727_tmp[25];	// L7400
      int32_t v4728 = v4727;	// L7401
      bool v4729 = v4728 == 0;	// L7402
      bool v4730 = v4725 & v4729;	// L7403
      if (v4730) {	// L7404
        half v4731 = res6;	// L7405
        uint16_t v4732;
        union { half from; uint16_t to;} _converter_v4731_to_v4732;
        _converter_v4731_to_v4732.from = v4731;
        v4732 = _converter_v4731_to_v4732.to;	// L7406
        ap_int<26> v4733 = csd_pkt6;	// L7407
        ap_int<26> v4734;
        ap_int<26> v4734_tmp = v4733;
        v4734_tmp(15, 0) = v4732;
        v4734 = v4734_tmp;	// L7408
        csd_pkt6 = v4734;	// L7409
        int32_t v4735 = dst6;	// L7410
        ap_uint<4> v4736 = v4735;	// L7411
        ap_int<26> v4737 = csd_pkt6;	// L7412
        ap_int<26> v4738;
        ap_int<26> v4738_tmp = v4737;
        v4738_tmp(19, 16) = v4736;
        v4738 = v4738_tmp;	// L7413
        csd_pkt6 = v4738;	// L7414
        int32_t v4739 = s26;	// L7415
        ap_uint<4> v4740 = v4739;	// L7416
        ap_int<26> v4741 = csd_pkt6;	// L7417
        ap_int<26> v4742;
        ap_int<26> v4742_tmp = v4741;
        v4742_tmp(24, 21) = v4740;
        v4742 = v4742_tmp;	// L7418
        csd_pkt6 = v4742;	// L7419
        int32_t v4743 = res_vld6;	// L7420
        bool v4744 = v4743;	// L7421
        ap_int<26> v4745 = csd_pkt6;	// L7422
        ap_int<26> v4746;
        ap_int<26> v4746_tmp = v4745;
        v4746_tmp[25] = v4744;        v4746 = v4746_tmp;	// L7423
        csd_pkt6 = v4746;	// L7424
        int32_t v4747 = op6;	// L7425
        int32_t v4748 = v4747 & 3;	// L7426
        csd_dir6 = v4748;	// L7427
      }
    } else {
      int32_t v4749 = dst6;	// L7430
      bool v4750 = v4749 >= 12;	// L7431
      if (v4750) {	// L7432
        ap_uint<17> tw6;	// L7433
        tw6 = 0;	// L7434
        int32_t v4752 = res_vld6;	// L7435
        bool v4753 = v4752;	// L7436
        ap_int<17> v4754 = tw6;	// L7437
        ap_int<17> v4755;
        ap_int<17> v4755_tmp = v4754;
        v4755_tmp[0] = v4753;        v4755 = v4755_tmp;	// L7438
        tw6 = v4755;	// L7439
        half v4756 = res6;	// L7440
        uint16_t v4757;
        union { half from; uint16_t to;} _converter_v4756_to_v4757;
        _converter_v4756_to_v4757.from = v4756;
        v4757 = _converter_v4756_to_v4757.to;	// L7441
        ap_int<17> v4758 = tw6;	// L7442
        ap_int<17> v4759;
        ap_int<17> v4759_tmp = v4758;
        v4759_tmp(16, 1) = v4757;
        v4759 = v4759_tmp;	// L7443
        tw6 = v4759;	// L7444
        int32_t v4760 = dst6;	// L7445
        int32_t v4761 = v4760 & 3;	// L7446
        bool v4762 = v4761 == 0;	// L7447
        if (v4762) {	// L7448
          ap_int<17> v4763 = tw6;	// L7449
          tx_n6 = v4763;	// L7450
        } else {
          int32_t v4764 = dst6;	// L7452
          int32_t v4765 = v4764 & 3;	// L7453
          bool v4766 = v4765 == 1;	// L7454
          if (v4766) {	// L7455
            ap_int<17> v4767 = tw6;	// L7456
            tx_s6 = v4767;	// L7457
          } else {
            int32_t v4768 = dst6;	// L7459
            int32_t v4769 = v4768 & 3;	// L7460
            bool v4770 = v4769 == 2;	// L7461
            if (v4770) {	// L7462
              ap_int<17> v4771 = tw6;	// L7463
              tx_w6 = v4771;	// L7464
            } else {
              ap_int<17> v4772 = tw6;	// L7466
              tx_e6 = v4772;	// L7467
            }
          }
        }
      } else {
        int32_t v4773 = res_vld6;	// L7472
        bool v4774 = v4773 == 1;	// L7473
        if (v4774) {	// L7474
          int32_t v4775 = dst6;	// L7475
          bool v4776 = v4775 < 8;	// L7476
          int32_t v4777 = dsmask6;	// L7477
          int32_t v4778 = v4777 >> v4775;	// L7478
          int32_t v4779 = v4778 & 1;	// L7479
          bool v4780 = v4779 == 1;	// L7480
          bool v4781 = v4776 & v4780;	// L7481
          if (v4781) {	// L7482
            int32_t v4782 = dst6;	// L7483
            int v4783 = v4782;	// L7484
            int32_t v4784 = drf_full6[v4783];	// L7485
            bool v4785 = v4784 == 0;	// L7486
            if (v4785) {	// L7487
              half v4786 = res6;	// L7488
              int32_t v4787 = dst6;	// L7489
              int v4788 = v4787;	// L7490
              drf6[v4788] = v4786;	// L7491
              int32_t v4789 = dst6;	// L7492
              int v4790 = v4789;	// L7493
              drf_full6[v4790] = 1;	// L7494
            }
          } else {
            half v4791 = res6;	// L7497
            int32_t v4792 = dst6;	// L7498
            int v4793 = v4792;	// L7499
            drf6[v4793] = v4791;	// L7500
          }
        }
      }
    }
    ap_int<17> v4794 = tx_n6;	// L7505
    txn_r6 = v4794;	// L7506
    ap_int<17> v4795 = tx_s6;	// L7507
    txs_r6 = v4795;	// L7508
    ap_int<17> v4796 = tx_w6;	// L7509
    txw_r6 = v4796;	// L7510
    ap_int<17> v4797 = tx_e6;	// L7511
    txe_r6 = v4797;	// L7512
    int32_t v4798 = crv_vld6;	// L7513
    bool v4799 = v4798 == 1;	// L7514
    if (v4799) {	// L7515
      int32_t v4800 = crv_mode6;	// L7516
      bool v4801 = v4800 == 1;	// L7517
      if (v4801) {	// L7518
        int32_t v4802 = crv_addr6;	// L7519
        int32_t v4803 = v4802 >> 3;	// L7520
        int32_t v4804 = v4803 & 1;	// L7521
        bool v4805 = v4804 == 1;	// L7522
        if (v4805) {	// L7523
          int32_t v4806 = crv_raw6;	// L7524
          int32_t v4807 = crv_addr6;	// L7525
          int32_t v4808 = v4807 & 7;	// L7526
          int v4809 = v4808;	// L7527
          irf6[v4809] = v4806;	// L7528
        } else {
          int32_t v4810 = crv_addr6;	// L7530
          bool v4811 = v4810 == 0;	// L7531
          if (v4811) {	// L7532
            int32_t v4812 = crv_raw6;	// L7533
            int32_t v4813 = v4812 & 255;	// L7534
            dsmask6 = v4813;	// L7535
            int32_t v4814 = crv_raw6;	// L7536
            int32_t v4815 = v4814 >> 8;	// L7537
            int32_t v4816 = v4815 & 7;	// L7538
            cfg_isz6 = v4816;	// L7539
            int32_t v4817 = crv_raw6;	// L7540
            int32_t v4818 = v4817 >> 15;	// L7541
            int32_t v4819 = v4818 & 1;	// L7542
            bool v4820 = v4819 == 1;	// L7543
            if (v4820) {	// L7544
              fetch_en6 = 1;	// L7545
              instr_cnt6 = 0;	// L7546
              iter_cnt6 = 0;	// L7547
            }
          } else {
            int32_t v4821 = crv_addr6;	// L7550
            bool v4822 = v4821 == 1;	// L7551
            if (v4822) {	// L7552
              int32_t v4823 = crv_raw6;	// L7553
              int32_t v4824 = v4823 & 255;	// L7554
              cfg_itsz6 = v4824;	// L7555
            }
          }
        }
      } else {
        int32_t v4825 = crv_addr6;	// L7560
        bool v4826 = v4825 < 8;	// L7561
        int32_t v4827 = dsmask6;	// L7562
        int32_t v4828 = v4827 >> v4825;	// L7563
        int32_t v4829 = v4828 & 1;	// L7564
        bool v4830 = v4829 == 1;	// L7565
        bool v4831 = v4826 & v4830;	// L7566
        if (v4831) {	// L7567
          int32_t v4832 = crv_addr6;	// L7568
          int v4833 = v4832;	// L7569
          int32_t v4834 = drf_full6[v4833];	// L7570
          bool v4835 = v4834 == 0;	// L7571
          if (v4835) {	// L7572
            half v4836 = crv_data6;	// L7573
            int32_t v4837 = crv_addr6;	// L7574
            int v4838 = v4837;	// L7575
            drf6[v4838] = v4836;	// L7576
            int32_t v4839 = crv_addr6;	// L7577
            int v4840 = v4839;	// L7578
            drf_full6[v4840] = 1;	// L7579
          }
        } else {
          half v4841 = crv_data6;	// L7582
          int32_t v4842 = crv_addr6;	// L7583
          int v4843 = v4842;	// L7584
          drf6[v4843] = v4841;	// L7585
        }
      }
    }
  }
}

void node_1_3(
  hls::stream< ap_uint<26> >& v4844,
  hls::stream< ap_uint<26> >& v4845,
  hls::stream< ap_uint<26> >& v4846,
  hls::stream< ap_uint<26> >& v4847,
  hls::stream< ap_uint<17> >& v4848,
  hls::stream< ap_uint<17> >& v4849,
  hls::stream< ap_uint<17> >& v4850,
  hls::stream< ap_uint<17> >& v4851,
  hls::stream< int32_t >& v4852,
  hls::stream< int32_t >& v4853,
  hls::stream< int32_t >& v4854,
  hls::stream< int32_t >& v4855,
  hls::stream< ap_uint<26> >& v4856,
  hls::stream< ap_uint<26> >& v4857,
  hls::stream< ap_uint<26> >& v4858,
  hls::stream< ap_uint<26> >& v4859,
  hls::stream< int32_t >& v4860,
  hls::stream< int32_t >& v4861,
  hls::stream< int32_t >& v4862,
  hls::stream< int32_t >& v4863,
  hls::stream< ap_uint<17> >& v4864,
  hls::stream< ap_uint<17> >& v4865,
  hls::stream< ap_uint<17> >& v4866,
  hls::stream< ap_uint<17> >& v4867
) {	// L7592
  int32_t irf7[8];	// L7623
  for (int v4869 = 0; v4869 < 8; v4869++) {	// L7624
    irf7[v4869] = 0;	// L7624
  }
  half drf7[8];	// L7625
  #pragma HLS array_partition variable=drf7 complete dim=1

  for (int v4871 = 0; v4871 < 8; v4871++) {	// L7626
    drf7[v4871] = (double)0.000000;	// L7626
  }
  int32_t drf_full7[8];	// L7627
  #pragma HLS array_partition variable=drf_full7 complete dim=1

  for (int v4873 = 0; v4873 < 8; v4873++) {	// L7628
    drf_full7[v4873] = 0;	// L7628
  }
  int32_t dsmask7;	// L7629
  dsmask7 = 0;	// L7630
  int32_t crv_vld7;	// L7631
  crv_vld7 = 0;	// L7632
  half crv_data7;	// L7633
  crv_data7 = (double)0.000000;	// L7634
  int32_t crv_addr7;	// L7635
  crv_addr7 = 0;	// L7636
  int32_t crv_mode7;	// L7637
  crv_mode7 = 0;	// L7638
  int32_t crv_raw7;	// L7639
  crv_raw7 = 0;	// L7640
  int32_t csd_vld7;	// L7641
  csd_vld7 = 0;	// L7642
  ap_uint<26> csd_pkt7;	// L7643
  csd_pkt7 = 0;	// L7644
  int32_t csd_dir7;	// L7645
  csd_dir7 = 0;	// L7646
  int32_t row_id7;	// L7647
  row_id7 = 1;	// L7648
  int32_t col_id7;	// L7649
  col_id7 = 3;	// L7650
  ap_uint<26> oe_r7;	// L7651
  oe_r7 = 0;	// L7652
  ap_uint<26> ow_r7;	// L7653
  ow_r7 = 0;	// L7654
  ap_uint<26> on_r7;	// L7655
  on_r7 = 0;	// L7656
  ap_uint<26> os_r7;	// L7657
  os_r7 = 0;	// L7658
  ap_uint<17> txn_r7;	// L7659
  txn_r7 = 0;	// L7660
  ap_uint<17> txs_r7;	// L7661
  txs_r7 = 0;	// L7662
  ap_uint<17> txw_r7;	// L7663
  txw_r7 = 0;	// L7664
  ap_uint<17> txe_r7;	// L7665
  txe_r7 = 0;	// L7666
  half hold_v7[4][2];	// L7667
  #pragma HLS array_partition variable=hold_v7 complete dim=1
  #pragma HLS array_partition variable=hold_v7 complete dim=2

  for (int v4894 = 0; v4894 < 4; v4894++) {	// L7668
    for (int v4895 = 0; v4895 < 2; v4895++) {	// L7668
      hold_v7[v4894][v4895] = (double)0.000000;	// L7668
    }
  }
  int32_t hold_cnt7[4];	// L7669
  #pragma HLS array_partition variable=hold_cnt7 complete dim=1

  for (int v4897 = 0; v4897 < 4; v4897++) {	// L7670
    hold_cnt7[v4897] = 0;	// L7670
  }
  ap_uint<26> rbuf7[4][2];	// L7671
  #pragma HLS array_partition variable=rbuf7 complete dim=1
  #pragma HLS array_partition variable=rbuf7 complete dim=2

  for (int v4899 = 0; v4899 < 4; v4899++) {	// L7672
    for (int v4900 = 0; v4900 < 2; v4900++) {	// L7672
      rbuf7[v4899][v4900] = 0;	// L7672
    }
  }
  int32_t rbcnt7[4];	// L7673
  #pragma HLS array_partition variable=rbcnt7 complete dim=1

  for (int v4902 = 0; v4902 < 4; v4902++) {	// L7674
    rbcnt7[v4902] = 0;	// L7674
  }
  int32_t rcred7[4];	// L7675
  #pragma HLS array_partition variable=rcred7 complete dim=1

  for (int v4904 = 0; v4904 < 4; v4904++) {	// L7676
    rcred7[v4904] = 0;	// L7676
  }
  int32_t cre_r7;	// L7677
  cre_r7 = 2;	// L7678
  int32_t crw_r7;	// L7679
  crw_r7 = 2;	// L7680
  int32_t crs_r7;	// L7681
  crs_r7 = 2;	// L7682
  int32_t crn_r7;	// L7683
  crn_r7 = 2;	// L7684
  int32_t cfg_isz7;	// L7685
  cfg_isz7 = 0;	// L7686
  int32_t cfg_itsz7;	// L7687
  cfg_itsz7 = 0;	// L7688
  int32_t fetch_en7;	// L7689
  fetch_en7 = 0;	// L7690
  int32_t instr_cnt7;	// L7691
  instr_cnt7 = 0;	// L7692
  int32_t iter_cnt7;	// L7693
  iter_cnt7 = 0;	// L7694
  int32_t condition_reg7;	// L7695
  condition_reg7 = 0;	// L7696
  l_S_t_0_t7: for (int t7 = 0; t7 < 8; t7++) {	// L7697
  #pragma HLS pipeline II=1
    ap_int<26> v4916 = oe_r7;	// L7698
    v4844.write(v4916);	// L7699
    ap_int<26> v4917 = ow_r7;	// L7700
    v4845.write(v4917);	// L7701
    ap_int<26> v4918 = os_r7;	// L7702
    v4846.write(v4918);	// L7703
    ap_int<26> v4919 = on_r7;	// L7704
    v4847.write(v4919);	// L7705
    ap_int<17> v4920 = txe_r7;	// L7706
    v4848.write(v4920);	// L7707
    ap_int<17> v4921 = txw_r7;	// L7708
    v4849.write(v4921);	// L7709
    ap_int<17> v4922 = txs_r7;	// L7710
    v4850.write(v4922);	// L7711
    ap_int<17> v4923 = txn_r7;	// L7712
    v4851.write(v4923);	// L7713
    int32_t v4924 = cre_r7;	// L7714
    v4852.write(v4924);	// L7715
    int32_t v4925 = crw_r7;	// L7716
    v4853.write(v4925);	// L7717
    int32_t v4926 = crs_r7;	// L7718
    v4854.write(v4926);	// L7719
    int32_t v4927 = crn_r7;	// L7720
    v4855.write(v4927);	// L7721
    ap_uint<26> v4928 = v4856.read();	// L7722
    ap_uint<26> p_w7;	// L7723
    p_w7 = v4928;	// L7724
    ap_uint<26> v4930 = v4857.read();	// L7725
    ap_uint<26> p_e7;	// L7726
    p_e7 = v4930;	// L7727
    ap_uint<26> v4932 = v4858.read();	// L7728
    ap_uint<26> p_n7;	// L7729
    p_n7 = v4932;	// L7730
    ap_uint<26> v4934 = v4859.read();	// L7731
    ap_uint<26> p_s7;	// L7732
    p_s7 = v4934;	// L7733
    int32_t v4936 = v4860.read();	// L7734
    int32_t v4937 = rcred7[0];	// L7735
    ap_int<33> v4938 = v4937;	// L7736
    ap_int<33> v4939 = v4936;	// L7737
    ap_int<33> v4940 = v4938 + v4939;	// L7738
    int32_t v4941 = v4940;	// L7739
    rcred7[0] = v4941;	// L7740
    int32_t v4942 = v4861.read();	// L7741
    int32_t v4943 = rcred7[1];	// L7742
    ap_int<33> v4944 = v4943;	// L7743
    ap_int<33> v4945 = v4942;	// L7744
    ap_int<33> v4946 = v4944 + v4945;	// L7745
    int32_t v4947 = v4946;	// L7746
    rcred7[1] = v4947;	// L7747
    int32_t v4948 = v4862.read();	// L7748
    int32_t v4949 = rcred7[2];	// L7749
    ap_int<33> v4950 = v4949;	// L7750
    ap_int<33> v4951 = v4948;	// L7751
    ap_int<33> v4952 = v4950 + v4951;	// L7752
    int32_t v4953 = v4952;	// L7753
    rcred7[2] = v4953;	// L7754
    int32_t v4954 = v4863.read();	// L7755
    int32_t v4955 = rcred7[3];	// L7756
    ap_int<33> v4956 = v4955;	// L7757
    ap_int<33> v4957 = v4954;	// L7758
    ap_int<33> v4958 = v4956 + v4957;	// L7759
    int32_t v4959 = v4958;	// L7760
    rcred7[3] = v4959;	// L7761
    ap_uint<26> fin7[4];	// L7762
    for (int v4961 = 0; v4961 < 4; v4961++) {	// L7763
      fin7[v4961] = 0;	// L7763
    }
    ap_int<26> v4962 = p_w7;	// L7764
    fin7[0] = v4962;	// L7765
    ap_int<26> v4963 = p_e7;	// L7766
    fin7[1] = v4963;	// L7767
    ap_int<26> v4964 = p_n7;	// L7768
    fin7[2] = v4964;	// L7769
    ap_int<26> v4965 = p_s7;	// L7770
    fin7[3] = v4965;	// L7771
    l_S_d_0_d28: for (int d28 = 0; d28 < 4; d28++) {	// L7772
      ap_uint<26> v4967 = fin7[d28];	// L7773
      bool v4968;
      ap_int<26> v4968_tmp = v4967;
      v4968 = v4968_tmp[25];	// L7774
      int32_t v4969 = v4968;	// L7775
      bool v4970 = v4969 == 1;	// L7776
      int32_t v4971 = rbcnt7[d28];	// L7777
      bool v4972 = v4971 < 2;	// L7778
      bool v4973 = v4970 & v4972;	// L7779
      if (v4973) {	// L7780
        ap_uint<26> v4974 = fin7[d28];	// L7781
        int32_t v4975 = rbcnt7[d28];	// L7782
        int v4976 = v4975;	// L7783
        rbuf7[d28][v4976] = v4974;	// L7784
        int32_t v4977 = rbcnt7[d28];	// L7785
        ap_int<33> v4978 = v4977;	// L7786
        ap_int<33> v4979 = v4978 + 1;	// L7787
        int32_t v4980 = v4979;	// L7788
        rbcnt7[d28] = v4980;	// L7789
      }
    }
    ap_uint<26> hd7[4];	// L7792
    for (int v4982 = 0; v4982 < 4; v4982++) {	// L7793
      hd7[v4982] = 0;	// L7793
    }
    int32_t hvld7[4];	// L7794
    for (int v4984 = 0; v4984 < 4; v4984++) {	// L7795
      hvld7[v4984] = 0;	// L7795
    }
    int32_t hit7[4];	// L7796
    for (int v4986 = 0; v4986 < 4; v4986++) {	// L7797
      hit7[v4986] = 0;	// L7797
    }
    int32_t axis7[4];	// L7798
    for (int v4988 = 0; v4988 < 4; v4988++) {	// L7799
      axis7[v4988] = 0;	// L7799
    }
    int32_t v4989 = col_id7;	// L7800
    axis7[0] = v4989;	// L7801
    int32_t v4990 = col_id7;	// L7802
    axis7[1] = v4990;	// L7803
    int32_t v4991 = row_id7;	// L7804
    axis7[2] = v4991;	// L7805
    int32_t v4992 = row_id7;	// L7806
    axis7[3] = v4992;	// L7807
    l_S_d_1_d29: for (int d29 = 0; d29 < 4; d29++) {	// L7808
      int32_t v4994 = rbcnt7[d29];	// L7809
      bool v4995 = v4994 > 0;	// L7810
      if (v4995) {	// L7811
        ap_uint<26> v4996 = rbuf7[d29][0];	// L7812
        hd7[d29] = v4996;	// L7813
        hvld7[d29] = 1;	// L7814
        ap_uint<26> v4997 = hd7[d29];	// L7815
        ap_int<4> v4998;
        ap_int<26> v4998_tmp = v4997;
        v4998 = v4998_tmp(24, 21);	// L7816
        int32_t v4999 = axis7[d29];	// L7817
        int32_t v5000 = v4998;	// L7818
        bool v5001 = v5000 == v4999;	// L7819
        if (v5001) {	// L7820
          hit7[d29] = 1;	// L7821
        }
      }
    }
    ap_uint<26> o_crv7;	// L7825
    o_crv7 = 0;	// L7826
    int32_t crv_in7;	// L7827
    crv_in7 = -1;	// L7828
    int32_t v5004 = hit7[3];	// L7829
    bool v5005 = v5004 == 1;	// L7830
    if (v5005) {	// L7831
      ap_uint<26> v5006 = hd7[3];	// L7832
      o_crv7 = v5006;	// L7833
      crv_in7 = 3;	// L7834
    } else {
      int32_t v5007 = hit7[2];	// L7836
      bool v5008 = v5007 == 1;	// L7837
      if (v5008) {	// L7838
        ap_uint<26> v5009 = hd7[2];	// L7839
        o_crv7 = v5009;	// L7840
        crv_in7 = 2;	// L7841
      } else {
        int32_t v5010 = hit7[1];	// L7843
        bool v5011 = v5010 == 1;	// L7844
        if (v5011) {	// L7845
          ap_uint<26> v5012 = hd7[1];	// L7846
          o_crv7 = v5012;	// L7847
          crv_in7 = 1;	// L7848
        } else {
          int32_t v5013 = hit7[0];	// L7850
          bool v5014 = v5013 == 1;	// L7851
          if (v5014) {	// L7852
            ap_uint<26> v5015 = hd7[0];	// L7853
            o_crv7 = v5015;	// L7854
            crv_in7 = 0;	// L7855
          }
        }
      }
    }
    ap_uint<26> o_out7[4];	// L7860
    for (int v5017 = 0; v5017 < 4; v5017++) {	// L7861
      o_out7[v5017] = 0;	// L7861
    }
    int32_t pop7[4];	// L7862
    for (int v5019 = 0; v5019 < 4; v5019++) {	// L7863
      pop7[v5019] = 0;	// L7863
    }
    int32_t inj_done7;	// L7864
    inj_done7 = 0;	// L7865
    int32_t idir7;	// L7866
    idir7 = -1;	// L7867
    ap_int<26> v5022 = csd_pkt7;	// L7868
    bool v5023;
    ap_int<26> v5023_tmp = v5022;
    v5023 = v5023_tmp[25];	// L7869
    int32_t v5024 = v5023;	// L7870
    bool v5025 = v5024 == 1;	// L7871
    if (v5025) {	// L7872
      int32_t v5026 = csd_dir7;	// L7873
      ap_int<33> v5027 = v5026;	// L7874
      ap_int<33> v5028 = 3 - v5027;	// L7875
      int32_t v5029 = v5028;	// L7876
      idir7 = v5029;	// L7877
    }
    l_S_o_2_o7: for (int o7 = 0; o7 < 4; o7++) {	// L7879
      int32_t v5031 = rcred7[o7];	// L7880
      bool v5032 = v5031 > 0;	// L7881
      if (v5032) {	// L7882
        int32_t v5033 = idir7;	// L7883
        ap_int<33> v5034 = v5033;	// L7884
        ap_int<33> v5035 = o7;	// L7885
        bool v5036 = v5034 == v5035;	// L7886
        if (v5036) {	// L7887
          ap_int<26> v5037 = csd_pkt7;	// L7888
          o_out7[o7] = v5037;	// L7889
          int32_t v5038 = rcred7[o7];	// L7890
          ap_int<33> v5039 = v5038;	// L7891
          ap_int<33> v5040 = v5039 - 1;	// L7892
          int32_t v5041 = v5040;	// L7893
          rcred7[o7] = v5041;	// L7894
          inj_done7 = 1;	// L7895
        } else {
          int32_t v5042 = hvld7[o7];	// L7897
          bool v5043 = v5042 == 1;	// L7898
          int32_t v5044 = hit7[o7];	// L7899
          bool v5045 = v5044 == 0;	// L7900
          bool v5046 = v5043 & v5045;	// L7901
          if (v5046) {	// L7902
            ap_uint<26> v5047 = hd7[o7];	// L7903
            o_out7[o7] = v5047;	// L7904
            int32_t v5048 = rcred7[o7];	// L7905
            ap_int<33> v5049 = v5048;	// L7906
            ap_int<33> v5050 = v5049 - 1;	// L7907
            int32_t v5051 = v5050;	// L7908
            rcred7[o7] = v5051;	// L7909
            pop7[o7] = 1;	// L7910
          }
        }
      }
    }
    int32_t v5052 = crv_in7;	// L7915
    bool v5053 = v5052 >= 0;	// L7916
    if (v5053) {	// L7917
      int32_t v5054 = crv_in7;	// L7918
      int v5055 = v5054;	// L7919
      pop7[v5055] = 1;	// L7920
    }
    int32_t ret7[4];	// L7922
    for (int v5057 = 0; v5057 < 4; v5057++) {	// L7923
      ret7[v5057] = 0;	// L7923
    }
    l_S_d_3_d30: for (int d30 = 0; d30 < 4; d30++) {	// L7924
      int32_t v5059 = pop7[d30];	// L7925
      bool v5060 = v5059 == 1;	// L7926
      if (v5060) {	// L7927
        l_S_sft_3_sft7: for (int sft7 = 0; sft7 < 1; sft7++) {	// L7928
          ap_uint<26> v5062 = rbuf7[d30][(sft7 + 1)];	// L7929
          rbuf7[d30][sft7] = v5062;	// L7930
        }
        int32_t v5063 = rbcnt7[d30];	// L7932
        ap_int<33> v5064 = v5063;	// L7933
        ap_int<33> v5065 = v5064 - 1;	// L7934
        int32_t v5066 = v5065;	// L7935
        rbcnt7[d30] = v5066;	// L7936
        ret7[d30] = 1;	// L7937
      }
    }
    int32_t v5067 = ret7[0];	// L7940
    cre_r7 = v5067;	// L7941
    int32_t v5068 = ret7[1];	// L7942
    crw_r7 = v5068;	// L7943
    int32_t v5069 = ret7[2];	// L7944
    crs_r7 = v5069;	// L7945
    int32_t v5070 = ret7[3];	// L7946
    crn_r7 = v5070;	// L7947
    ap_uint<26> v5071 = o_out7[0];	// L7948
    oe_r7 = v5071;	// L7949
    ap_uint<26> v5072 = o_out7[1];	// L7950
    ow_r7 = v5072;	// L7951
    ap_uint<26> v5073 = o_out7[2];	// L7952
    os_r7 = v5073;	// L7953
    ap_uint<26> v5074 = o_out7[3];	// L7954
    on_r7 = v5074;	// L7955
    int32_t v5075 = inj_done7;	// L7956
    bool v5076 = v5075 == 1;	// L7957
    if (v5076) {	// L7958
      csd_pkt7 = 0;	// L7959
    }
    ap_int<26> v5077 = o_crv7;	// L7961
    bool v5078;
    ap_int<26> v5078_tmp = v5077;
    v5078 = v5078_tmp[25];	// L7962
    int32_t v5079 = v5078;	// L7963
    crv_vld7 = v5079;	// L7964
    ap_int<26> v5080 = o_crv7;	// L7965
    int16_t v5081;
    ap_int<26> v5081_tmp = v5080;
    v5081 = v5081_tmp(15, 0);	// L7966
    half v5082;
    union { uint16_t from; half to;} _converter_v5081_to_v5082;
    _converter_v5081_to_v5082.from = v5081;
    v5082 = _converter_v5081_to_v5082.to;	// L7967
    crv_data7 = v5082;	// L7968
    ap_int<26> v5083 = o_crv7;	// L7969
    ap_int<4> v5084;
    ap_int<26> v5084_tmp = v5083;
    v5084 = v5084_tmp(19, 16);	// L7970
    int32_t v5085 = v5084;	// L7971
    crv_addr7 = v5085;	// L7972
    ap_int<26> v5086 = o_crv7;	// L7973
    bool v5087;
    ap_int<26> v5087_tmp = v5086;
    v5087 = v5087_tmp[20];	// L7974
    int32_t v5088 = v5087;	// L7975
    crv_mode7 = v5088;	// L7976
    ap_int<26> v5089 = o_crv7;	// L7977
    int16_t v5090;
    ap_int<26> v5090_tmp = v5089;
    v5090 = v5090_tmp(15, 0);	// L7978
    int32_t v5091 = v5090;	// L7979
    crv_raw7 = v5091;	// L7980
    ap_uint<17> v5092 = v4864.read();	// L7981
    ap_uint<17> rx_w7;	// L7982
    rx_w7 = v5092;	// L7983
    ap_uint<17> v5094 = v4865.read();	// L7984
    ap_uint<17> rx_e7;	// L7985
    rx_e7 = v5094;	// L7986
    ap_uint<17> v5096 = v4866.read();	// L7987
    ap_uint<17> rx_n7;	// L7988
    rx_n7 = v5096;	// L7989
    ap_uint<17> v5098 = v4867.read();	// L7990
    ap_uint<17> rx_s7;	// L7991
    rx_s7 = v5098;	// L7992
    half rxv7[4];	// L7993
    for (int v5101 = 0; v5101 < 4; v5101++) {	// L7994
      rxv7[v5101] = (double)0.000000;	// L7994
    }
    int32_t rxvld7[4];	// L7995
    for (int v5103 = 0; v5103 < 4; v5103++) {	// L7996
      rxvld7[v5103] = 0;	// L7996
    }
    ap_int<17> v5104 = rx_n7;	// L7997
    int16_t v5105;
    ap_int<17> v5105_tmp = v5104;
    v5105 = v5105_tmp(16, 1);	// L7998
    half v5106;
    union { uint16_t from; half to;} _converter_v5105_to_v5106;
    _converter_v5105_to_v5106.from = v5105;
    v5106 = _converter_v5105_to_v5106.to;	// L7999
    rxv7[0] = v5106;	// L8000
    ap_int<17> v5107 = rx_n7;	// L8001
    bool v5108;
    ap_int<17> v5108_tmp = v5107;
    v5108 = v5108_tmp[0];	// L8002
    int32_t v5109 = v5108;	// L8003
    rxvld7[0] = v5109;	// L8004
    ap_int<17> v5110 = rx_s7;	// L8005
    int16_t v5111;
    ap_int<17> v5111_tmp = v5110;
    v5111 = v5111_tmp(16, 1);	// L8006
    half v5112;
    union { uint16_t from; half to;} _converter_v5111_to_v5112;
    _converter_v5111_to_v5112.from = v5111;
    v5112 = _converter_v5111_to_v5112.to;	// L8007
    rxv7[1] = v5112;	// L8008
    ap_int<17> v5113 = rx_s7;	// L8009
    bool v5114;
    ap_int<17> v5114_tmp = v5113;
    v5114 = v5114_tmp[0];	// L8010
    int32_t v5115 = v5114;	// L8011
    rxvld7[1] = v5115;	// L8012
    ap_int<17> v5116 = rx_w7;	// L8013
    int16_t v5117;
    ap_int<17> v5117_tmp = v5116;
    v5117 = v5117_tmp(16, 1);	// L8014
    half v5118;
    union { uint16_t from; half to;} _converter_v5117_to_v5118;
    _converter_v5117_to_v5118.from = v5117;
    v5118 = _converter_v5117_to_v5118.to;	// L8015
    rxv7[2] = v5118;	// L8016
    ap_int<17> v5119 = rx_w7;	// L8017
    bool v5120;
    ap_int<17> v5120_tmp = v5119;
    v5120 = v5120_tmp[0];	// L8018
    int32_t v5121 = v5120;	// L8019
    rxvld7[2] = v5121;	// L8020
    ap_int<17> v5122 = rx_e7;	// L8021
    int16_t v5123;
    ap_int<17> v5123_tmp = v5122;
    v5123 = v5123_tmp(16, 1);	// L8022
    half v5124;
    union { uint16_t from; half to;} _converter_v5123_to_v5124;
    _converter_v5123_to_v5124.from = v5123;
    v5124 = _converter_v5123_to_v5124.to;	// L8023
    rxv7[3] = v5124;	// L8024
    ap_int<17> v5125 = rx_e7;	// L8025
    bool v5126;
    ap_int<17> v5126_tmp = v5125;
    v5126 = v5126_tmp[0];	// L8026
    int32_t v5127 = v5126;	// L8027
    rxvld7[3] = v5127;	// L8028
    l_S_d_5_d31: for (int d31 = 0; d31 < 4; d31++) {	// L8029
      int32_t v5129 = rxvld7[d31];	// L8030
      bool v5130 = v5129 == 1;	// L8031
      int32_t v5131 = hold_cnt7[d31];	// L8032
      bool v5132 = v5131 < 2;	// L8033
      bool v5133 = v5130 & v5132;	// L8034
      if (v5133) {	// L8035
        half v5134 = rxv7[d31];	// L8036
        int32_t v5135 = hold_cnt7[d31];	// L8037
        int v5136 = v5135;	// L8038
        hold_v7[d31][v5136] = v5134;	// L8039
        int32_t v5137 = hold_cnt7[d31];	// L8040
        ap_int<33> v5138 = v5137;	// L8041
        ap_int<33> v5139 = v5138 + 1;	// L8042
        int32_t v5140 = v5139;	// L8043
        hold_cnt7[d31] = v5140;	// L8044
      }
    }
    int32_t pc7;	// L8047
    pc7 = -1;	// L8048
    int32_t v5142 = fetch_en7;	// L8049
    bool v5143 = v5142 == 1;	// L8050
    if (v5143) {	// L8051
      int32_t v5144 = instr_cnt7;	// L8052
      pc7 = v5144;	// L8053
    }
    int32_t instr7;	// L8055
    instr7 = 0;	// L8056
    int32_t v5146 = pc7;	// L8057
    bool v5147 = v5146 >= 0;	// L8058
    if (v5147) {	// L8059
      int32_t v5148 = pc7;	// L8060
      int v5149 = v5148;	// L8061
      int32_t v5150 = irf7[v5149];	// L8062
      instr7 = v5150;	// L8063
    }
    int32_t v5151 = instr7;	// L8065
    int32_t v5152 = v5151 & 15;	// L8066
    int32_t op7;	// L8067
    op7 = v5152;	// L8068
    int32_t v5154 = instr7;	// L8069
    int32_t v5155 = v5154 >> 4;	// L8070
    int32_t v5156 = v5155 & 15;	// L8071
    int32_t dst7;	// L8072
    dst7 = v5156;	// L8073
    int32_t v5158 = instr7;	// L8074
    int32_t v5159 = v5158 >> 8;	// L8075
    int32_t v5160 = v5159 & 15;	// L8076
    int32_t s17;	// L8077
    s17 = v5160;	// L8078
    int32_t v5162 = instr7;	// L8079
    int32_t v5163 = v5162 >> 12;	// L8080
    int32_t v5164 = v5163 & 15;	// L8081
    int32_t s27;	// L8082
    s27 = v5164;	// L8083
    half a7;	// L8084
    a7 = (double)0.000000;	// L8085
    half b7;	// L8086
    b7 = (double)0.000000;	// L8087
    int32_t v5168 = s17;	// L8088
    bool v5169 = v5168 >= 12;	// L8089
    if (v5169) {	// L8090
      int32_t v5170 = s17;	// L8091
      int32_t v5171 = v5170 & 3;	// L8092
      int v5172 = v5171;	// L8093
      half v5173 = hold_v7[v5172][0];	// L8094
      a7 = v5173;	// L8095
    } else {
      int32_t v5174 = s17;	// L8097
      int v5175 = v5174;	// L8098
      half v5176 = drf7[v5175];	// L8099
      a7 = v5176;	// L8100
    }
    int32_t v5177 = s27;	// L8102
    bool v5178 = v5177 >= 12;	// L8103
    if (v5178) {	// L8104
      int32_t v5179 = s27;	// L8105
      int32_t v5180 = v5179 & 3;	// L8106
      int v5181 = v5180;	// L8107
      half v5182 = hold_v7[v5181][0];	// L8108
      b7 = v5182;	// L8109
    } else {
      int32_t v5183 = s27;	// L8111
      int v5184 = v5183;	// L8112
      half v5185 = drf7[v5184];	// L8113
      b7 = v5185;	// L8114
    }
    int32_t a_vld7;	// L8116
    a_vld7 = 1;	// L8117
    int32_t b_vld7;	// L8118
    b_vld7 = 1;	// L8119
    int32_t v5188 = s17;	// L8120
    bool v5189 = v5188 >= 12;	// L8121
    if (v5189) {	// L8122
      a_vld7 = 0;	// L8123
      int32_t v5190 = s17;	// L8124
      int32_t v5191 = v5190 & 3;	// L8125
      int v5192 = v5191;	// L8126
      int32_t v5193 = hold_cnt7[v5192];	// L8127
      bool v5194 = v5193 > 0;	// L8128
      if (v5194) {	// L8129
        a_vld7 = 1;	// L8130
      }
    }
    int32_t v5195 = s27;	// L8133
    bool v5196 = v5195 >= 12;	// L8134
    if (v5196) {	// L8135
      b_vld7 = 0;	// L8136
      int32_t v5197 = s27;	// L8137
      int32_t v5198 = v5197 & 3;	// L8138
      int v5199 = v5198;	// L8139
      int32_t v5200 = hold_cnt7[v5199];	// L8140
      bool v5201 = v5200 > 0;	// L8141
      if (v5201) {	// L8142
        b_vld7 = 1;	// L8143
      }
    }
    int32_t v5202 = s17;	// L8146
    bool v5203 = v5202 < 8;	// L8147
    int32_t v5204 = dsmask7;	// L8148
    int32_t v5205 = v5204 >> v5202;	// L8149
    int32_t v5206 = v5205 & 1;	// L8150
    bool v5207 = v5206 == 1;	// L8151
    bool v5208 = v5203 & v5207;	// L8152
    if (v5208) {	// L8153
      int32_t v5209 = s17;	// L8154
      int v5210 = v5209;	// L8155
      int32_t v5211 = drf_full7[v5210];	// L8156
      bool v5212 = v5211 == 0;	// L8157
      if (v5212) {	// L8158
        a_vld7 = 0;	// L8159
      }
    }
    int32_t v5213 = s27;	// L8162
    bool v5214 = v5213 < 8;	// L8163
    int32_t v5215 = dsmask7;	// L8164
    int32_t v5216 = v5215 >> v5213;	// L8165
    int32_t v5217 = v5216 & 1;	// L8166
    bool v5218 = v5217 == 1;	// L8167
    bool v5219 = v5214 & v5218;	// L8168
    if (v5219) {	// L8169
      int32_t v5220 = s27;	// L8170
      int v5221 = v5220;	// L8171
      int32_t v5222 = drf_full7[v5221];	// L8172
      bool v5223 = v5222 == 0;	// L8173
      if (v5223) {	// L8174
        b_vld7 = 0;	// L8175
      }
    }
    int32_t binop7;	// L8178
    binop7 = 0;	// L8179
    int32_t v5225 = op7;	// L8180
    bool v5226 = v5225 == 0;	// L8181
    bool v5227 = v5225 == 1;	// L8182
    bool v5228 = v5225 == 2;	// L8183
    bool v5229 = v5225 == 8;	// L8184
    bool v5230 = v5225 == 9;	// L8185
    bool v5231 = v5226 | v5227;	// L8186
    bool v5232 = v5231 | v5228;	// L8187
    bool v5233 = v5232 | v5229;	// L8188
    bool v5234 = v5233 | v5230;	// L8189
    if (v5234) {	// L8190
      binop7 = 1;	// L8191
    }
    int32_t grant7;	// L8193
    grant7 = 0;	// L8194
    int32_t v5236 = pc7;	// L8195
    bool v5237 = v5236 >= 0;	// L8196
    if (v5237) {	// L8197
      grant7 = 1;	// L8198
    }
    int32_t v5238 = pc7;	// L8200
    bool v5239 = v5238 >= 0;	// L8201
    int32_t v5240 = a_vld7;	// L8202
    bool v5241 = v5240 == 0;	// L8203
    int32_t v5242 = binop7;	// L8204
    bool v5243 = v5242 == 1;	// L8205
    int32_t v5244 = b_vld7;	// L8206
    bool v5245 = v5244 == 0;	// L8207
    bool v5246 = v5243 & v5245;	// L8208
    bool v5247 = v5241 | v5246;	// L8209
    bool v5248 = v5239 & v5247;	// L8210
    if (v5248) {	// L8211
      grant7 = 0;	// L8212
    }
    int32_t v5249 = grant7;	// L8214
    bool v5250 = v5249 == 1;	// L8215
    if (v5250) {	// L8216
      int32_t v5251 = instr_cnt7;	// L8217
      int32_t v5252 = cfg_isz7;	// L8218
      bool v5253 = v5251 == v5252;	// L8219
      if (v5253) {	// L8220
        instr_cnt7 = 0;	// L8221
        int32_t v5254 = iter_cnt7;	// L8222
        int32_t v5255 = cfg_itsz7;	// L8223
        ap_int<33> v5256 = v5255;	// L8224
        ap_int<33> v5257 = v5256 - 1;	// L8225
        ap_int<33> v5258 = v5254;	// L8226
        bool v5259 = v5258 == v5257;	// L8227
        if (v5259) {	// L8228
          fetch_en7 = 0;	// L8229
        } else {
          int32_t v5260 = iter_cnt7;	// L8231
          ap_int<33> v5261 = v5260;	// L8232
          ap_int<33> v5262 = v5261 + 1;	// L8233
          int32_t v5263 = v5262;	// L8234
          iter_cnt7 = v5263;	// L8235
        }
      } else {
        int32_t v5264 = instr_cnt7;	// L8238
        ap_int<33> v5265 = v5264;	// L8239
        ap_int<33> v5266 = v5265 + 1;	// L8240
        int32_t v5267 = v5266;	// L8241
        instr_cnt7 = v5267;	// L8242
      }
    }
    int32_t c17;	// L8245
    c17 = -1;	// L8246
    int32_t c27;	// L8247
    c27 = -1;	// L8248
    int32_t v5270 = grant7;	// L8249
    bool v5271 = v5270 == 1;	// L8250
    int32_t v5272 = s17;	// L8251
    bool v5273 = v5272 >= 12;	// L8252
    bool v5274 = v5271 & v5273;	// L8253
    if (v5274) {	// L8254
      int32_t v5275 = s17;	// L8255
      int32_t v5276 = v5275 & 3;	// L8256
      c17 = v5276;	// L8257
    }
    int32_t v5277 = grant7;	// L8259
    bool v5278 = v5277 == 1;	// L8260
    int32_t v5279 = s27;	// L8261
    bool v5280 = v5279 >= 12;	// L8262
    bool v5281 = v5278 & v5280;	// L8263
    if (v5281) {	// L8264
      int32_t v5282 = s27;	// L8265
      int32_t v5283 = v5282 & 3;	// L8266
      c27 = v5283;	// L8267
    }
    int32_t v5284 = c17;	// L8269
    bool v5285 = v5284 >= 0;	// L8270
    if (v5285) {	// L8271
      int32_t v5286 = c17;	// L8272
      int v5287 = v5286;	// L8273
      half v5288 = hold_v7[v5287][1];	// L8274
      hold_v7[v5287][0] = v5288;	// L8275
      int32_t v5289 = c17;	// L8276
      int v5290 = v5289;	// L8277
      int32_t v5291 = hold_cnt7[v5290];	// L8278
      ap_int<33> v5292 = v5291;	// L8279
      ap_int<33> v5293 = v5292 - 1;	// L8280
      int32_t v5294 = v5293;	// L8281
      hold_cnt7[v5290] = v5294;	// L8282
    }
    int32_t v5295 = c27;	// L8284
    bool v5296 = v5295 >= 0;	// L8285
    int32_t v5297 = c17;	// L8286
    bool v5298 = v5295 != v5297;	// L8287
    bool v5299 = v5296 & v5298;	// L8288
    if (v5299) {	// L8289
      int32_t v5300 = c27;	// L8290
      int v5301 = v5300;	// L8291
      half v5302 = hold_v7[v5301][1];	// L8292
      hold_v7[v5301][0] = v5302;	// L8293
      int32_t v5303 = c27;	// L8294
      int v5304 = v5303;	// L8295
      int32_t v5305 = hold_cnt7[v5304];	// L8296
      ap_int<33> v5306 = v5305;	// L8297
      ap_int<33> v5307 = v5306 - 1;	// L8298
      int32_t v5308 = v5307;	// L8299
      hold_cnt7[v5304] = v5308;	// L8300
    }
    int32_t v5309 = grant7;	// L8302
    bool v5310 = v5309 == 1;	// L8303
    int32_t v5311 = s17;	// L8304
    bool v5312 = v5311 < 8;	// L8305
    int32_t v5313 = dsmask7;	// L8306
    int32_t v5314 = v5313 >> v5311;	// L8307
    int32_t v5315 = v5314 & 1;	// L8308
    bool v5316 = v5315 == 1;	// L8309
    bool v5317 = v5310 & v5312;	// L8310
    bool v5318 = v5317 & v5316;	// L8311
    if (v5318) {	// L8312
      int32_t v5319 = s17;	// L8313
      int v5320 = v5319;	// L8314
      drf_full7[v5320] = 0;	// L8315
    }
    int32_t v5321 = grant7;	// L8317
    bool v5322 = v5321 == 1;	// L8318
    int32_t v5323 = s27;	// L8319
    bool v5324 = v5323 < 8;	// L8320
    int32_t v5325 = dsmask7;	// L8321
    int32_t v5326 = v5325 >> v5323;	// L8322
    int32_t v5327 = v5326 & 1;	// L8323
    bool v5328 = v5327 == 1;	// L8324
    bool v5329 = v5322 & v5324;	// L8325
    bool v5330 = v5329 & v5328;	// L8326
    if (v5330) {	// L8327
      int32_t v5331 = s27;	// L8328
      int v5332 = v5331;	// L8329
      drf_full7[v5332] = 0;	// L8330
    }
    half res7;	// L8332
    res7 = (double)0.000000;	// L8333
    int32_t v5334 = op7;	// L8334
    bool v5335 = v5334 == 0;	// L8335
    if (v5335) {	// L8336
      half v5336 = a7;	// L8337
      half v5337 = b7;	// L8338
      half v5338 = v5336 + v5337;	// L8339
      res7 = v5338;	// L8340
    } else {
      int32_t v5339 = op7;	// L8342
      bool v5340 = v5339 == 1;	// L8343
      if (v5340) {	// L8344
        half v5341 = a7;	// L8345
        half v5342 = b7;	// L8346
        half v5343 = v5341 - v5342;	// L8347
        res7 = v5343;	// L8348
      } else {
        int32_t v5344 = op7;	// L8350
        bool v5345 = v5344 == 2;	// L8351
        if (v5345) {	// L8352
          half v5346 = a7;	// L8353
          half v5347 = b7;	// L8354
          half v5348 = v5346 * v5347;	// L8355
          res7 = v5348;	// L8356
        } else {
          int32_t v5349 = op7;	// L8358
          bool v5350 = v5349 == 8;	// L8359
          if (v5350) {	// L8360
            half v5351 = a7;	// L8361
            half v5352 = b7;	// L8362
            bool v5353 = v5351 >= v5352;	// L8363
            if (v5353) {	// L8364
              res7 = (double)1.000000;	// L8365
            } else {
              res7 = (double)-1.000000;	// L8367
            }
          } else {
            int32_t v5354 = op7;	// L8370
            bool v5355 = v5354 == 9;	// L8371
            if (v5355) {	// L8372
              half v5356 = a7;	// L8373
              half v5357 = b7;	// L8374
              bool v5358 = v5356 < v5357;	// L8375
              if (v5358) {	// L8376
                res7 = (double)1.000000;	// L8377
              } else {
                res7 = (double)-1.000000;	// L8379
              }
            } else {
              half v5359 = a7;	// L8382
              res7 = v5359;	// L8383
            }
          }
        }
      }
    }
    int32_t v5360 = a_vld7;	// L8389
    int32_t res_vld7;	// L8390
    res_vld7 = v5360;	// L8391
    int32_t v5362 = op7;	// L8392
    bool v5363 = v5362 == 0;	// L8393
    bool v5364 = v5362 == 1;	// L8394
    bool v5365 = v5362 == 2;	// L8395
    bool v5366 = v5362 == 8;	// L8396
    bool v5367 = v5362 == 9;	// L8397
    bool v5368 = v5363 | v5364;	// L8398
    bool v5369 = v5368 | v5365;	// L8399
    bool v5370 = v5369 | v5366;	// L8400
    bool v5371 = v5370 | v5367;	// L8401
    if (v5371) {	// L8402
      int32_t v5372 = a_vld7;	// L8403
      int32_t v5373 = b_vld7;	// L8404
      int64_t v5374 = v5372;	// L8405
      int64_t v5375 = v5373;	// L8406
      int64_t v5376 = v5374 * v5375;	// L8407
      int32_t v5377 = v5376;	// L8408
      res_vld7 = v5377;	// L8409
    }
    int32_t v5378 = grant7;	// L8411
    bool v5379 = v5378 == 0;	// L8412
    if (v5379) {	// L8413
      res_vld7 = 0;	// L8414
    }
    int32_t v5380 = grant7;	// L8416
    bool v5381 = v5380 == 1;	// L8417
    int32_t v5382 = op7;	// L8418
    bool v5383 = v5382 == 8;	// L8419
    bool v5384 = v5381 & v5383;	// L8420
    if (v5384) {	// L8421
      condition_reg7 = 0;	// L8422
      half v5385 = a7;	// L8423
      half v5386 = b7;	// L8424
      bool v5387 = v5385 >= v5386;	// L8425
      if (v5387) {	// L8426
        condition_reg7 = 1;	// L8427
      }
    }
    int32_t v5388 = grant7;	// L8430
    bool v5389 = v5388 == 1;	// L8431
    int32_t v5390 = op7;	// L8432
    bool v5391 = v5390 == 9;	// L8433
    bool v5392 = v5389 & v5391;	// L8434
    if (v5392) {	// L8435
      condition_reg7 = 0;	// L8436
      half v5393 = a7;	// L8437
      half v5394 = b7;	// L8438
      bool v5395 = v5393 < v5394;	// L8439
      if (v5395) {	// L8440
        condition_reg7 = 1;	// L8441
      }
    }
    ap_uint<17> tx_n7;	// L8444
    tx_n7 = 0;	// L8445
    ap_uint<17> tx_s7;	// L8446
    tx_s7 = 0;	// L8447
    ap_uint<17> tx_w7;	// L8448
    tx_w7 = 0;	// L8449
    ap_uint<17> tx_e7;	// L8450
    tx_e7 = 0;	// L8451
    int32_t is_rtr7;	// L8452
    is_rtr7 = 0;	// L8453
    int32_t do_inj7;	// L8454
    do_inj7 = 0;	// L8455
    int32_t v5402 = op7;	// L8456
    bool v5403 = v5402 >= 4;	// L8457
    ap_int<33> v5404 = v5402;	// L8458
    bool v5405 = v5404 <= 7;	// L8459
    bool v5406 = v5403 & v5405;	// L8460
    if (v5406) {	// L8461
      is_rtr7 = 1;	// L8462
      do_inj7 = 1;	// L8463
    }
    int32_t v5407 = op7;	// L8465
    bool v5408 = v5407 >= 12;	// L8466
    ap_int<33> v5409 = v5407;	// L8467
    bool v5410 = v5409 <= 15;	// L8468
    bool v5411 = v5408 & v5410;	// L8469
    if (v5411) {	// L8470
      is_rtr7 = 1;	// L8471
      int32_t v5412 = condition_reg7;	// L8472
      bool v5413 = v5412 == 1;	// L8473
      if (v5413) {	// L8474
        do_inj7 = 1;	// L8475
      }
    }
    int32_t v5414 = is_rtr7;	// L8478
    bool v5415 = v5414 == 1;	// L8479
    if (v5415) {	// L8480
      int32_t v5416 = do_inj7;	// L8481
      bool v5417 = v5416 == 1;	// L8482
      ap_int<26> v5418 = csd_pkt7;	// L8483
      bool v5419;
      ap_int<26> v5419_tmp = v5418;
      v5419 = v5419_tmp[25];	// L8484
      int32_t v5420 = v5419;	// L8485
      bool v5421 = v5420 == 0;	// L8486
      bool v5422 = v5417 & v5421;	// L8487
      if (v5422) {	// L8488
        half v5423 = res7;	// L8489
        uint16_t v5424;
        union { half from; uint16_t to;} _converter_v5423_to_v5424;
        _converter_v5423_to_v5424.from = v5423;
        v5424 = _converter_v5423_to_v5424.to;	// L8490
        ap_int<26> v5425 = csd_pkt7;	// L8491
        ap_int<26> v5426;
        ap_int<26> v5426_tmp = v5425;
        v5426_tmp(15, 0) = v5424;
        v5426 = v5426_tmp;	// L8492
        csd_pkt7 = v5426;	// L8493
        int32_t v5427 = dst7;	// L8494
        ap_uint<4> v5428 = v5427;	// L8495
        ap_int<26> v5429 = csd_pkt7;	// L8496
        ap_int<26> v5430;
        ap_int<26> v5430_tmp = v5429;
        v5430_tmp(19, 16) = v5428;
        v5430 = v5430_tmp;	// L8497
        csd_pkt7 = v5430;	// L8498
        int32_t v5431 = s27;	// L8499
        ap_uint<4> v5432 = v5431;	// L8500
        ap_int<26> v5433 = csd_pkt7;	// L8501
        ap_int<26> v5434;
        ap_int<26> v5434_tmp = v5433;
        v5434_tmp(24, 21) = v5432;
        v5434 = v5434_tmp;	// L8502
        csd_pkt7 = v5434;	// L8503
        int32_t v5435 = res_vld7;	// L8504
        bool v5436 = v5435;	// L8505
        ap_int<26> v5437 = csd_pkt7;	// L8506
        ap_int<26> v5438;
        ap_int<26> v5438_tmp = v5437;
        v5438_tmp[25] = v5436;        v5438 = v5438_tmp;	// L8507
        csd_pkt7 = v5438;	// L8508
        int32_t v5439 = op7;	// L8509
        int32_t v5440 = v5439 & 3;	// L8510
        csd_dir7 = v5440;	// L8511
      }
    } else {
      int32_t v5441 = dst7;	// L8514
      bool v5442 = v5441 >= 12;	// L8515
      if (v5442) {	// L8516
        ap_uint<17> tw7;	// L8517
        tw7 = 0;	// L8518
        int32_t v5444 = res_vld7;	// L8519
        bool v5445 = v5444;	// L8520
        ap_int<17> v5446 = tw7;	// L8521
        ap_int<17> v5447;
        ap_int<17> v5447_tmp = v5446;
        v5447_tmp[0] = v5445;        v5447 = v5447_tmp;	// L8522
        tw7 = v5447;	// L8523
        half v5448 = res7;	// L8524
        uint16_t v5449;
        union { half from; uint16_t to;} _converter_v5448_to_v5449;
        _converter_v5448_to_v5449.from = v5448;
        v5449 = _converter_v5448_to_v5449.to;	// L8525
        ap_int<17> v5450 = tw7;	// L8526
        ap_int<17> v5451;
        ap_int<17> v5451_tmp = v5450;
        v5451_tmp(16, 1) = v5449;
        v5451 = v5451_tmp;	// L8527
        tw7 = v5451;	// L8528
        int32_t v5452 = dst7;	// L8529
        int32_t v5453 = v5452 & 3;	// L8530
        bool v5454 = v5453 == 0;	// L8531
        if (v5454) {	// L8532
          ap_int<17> v5455 = tw7;	// L8533
          tx_n7 = v5455;	// L8534
        } else {
          int32_t v5456 = dst7;	// L8536
          int32_t v5457 = v5456 & 3;	// L8537
          bool v5458 = v5457 == 1;	// L8538
          if (v5458) {	// L8539
            ap_int<17> v5459 = tw7;	// L8540
            tx_s7 = v5459;	// L8541
          } else {
            int32_t v5460 = dst7;	// L8543
            int32_t v5461 = v5460 & 3;	// L8544
            bool v5462 = v5461 == 2;	// L8545
            if (v5462) {	// L8546
              ap_int<17> v5463 = tw7;	// L8547
              tx_w7 = v5463;	// L8548
            } else {
              ap_int<17> v5464 = tw7;	// L8550
              tx_e7 = v5464;	// L8551
            }
          }
        }
      } else {
        int32_t v5465 = res_vld7;	// L8556
        bool v5466 = v5465 == 1;	// L8557
        if (v5466) {	// L8558
          int32_t v5467 = dst7;	// L8559
          bool v5468 = v5467 < 8;	// L8560
          int32_t v5469 = dsmask7;	// L8561
          int32_t v5470 = v5469 >> v5467;	// L8562
          int32_t v5471 = v5470 & 1;	// L8563
          bool v5472 = v5471 == 1;	// L8564
          bool v5473 = v5468 & v5472;	// L8565
          if (v5473) {	// L8566
            int32_t v5474 = dst7;	// L8567
            int v5475 = v5474;	// L8568
            int32_t v5476 = drf_full7[v5475];	// L8569
            bool v5477 = v5476 == 0;	// L8570
            if (v5477) {	// L8571
              half v5478 = res7;	// L8572
              int32_t v5479 = dst7;	// L8573
              int v5480 = v5479;	// L8574
              drf7[v5480] = v5478;	// L8575
              int32_t v5481 = dst7;	// L8576
              int v5482 = v5481;	// L8577
              drf_full7[v5482] = 1;	// L8578
            }
          } else {
            half v5483 = res7;	// L8581
            int32_t v5484 = dst7;	// L8582
            int v5485 = v5484;	// L8583
            drf7[v5485] = v5483;	// L8584
          }
        }
      }
    }
    ap_int<17> v5486 = tx_n7;	// L8589
    txn_r7 = v5486;	// L8590
    ap_int<17> v5487 = tx_s7;	// L8591
    txs_r7 = v5487;	// L8592
    ap_int<17> v5488 = tx_w7;	// L8593
    txw_r7 = v5488;	// L8594
    ap_int<17> v5489 = tx_e7;	// L8595
    txe_r7 = v5489;	// L8596
    int32_t v5490 = crv_vld7;	// L8597
    bool v5491 = v5490 == 1;	// L8598
    if (v5491) {	// L8599
      int32_t v5492 = crv_mode7;	// L8600
      bool v5493 = v5492 == 1;	// L8601
      if (v5493) {	// L8602
        int32_t v5494 = crv_addr7;	// L8603
        int32_t v5495 = v5494 >> 3;	// L8604
        int32_t v5496 = v5495 & 1;	// L8605
        bool v5497 = v5496 == 1;	// L8606
        if (v5497) {	// L8607
          int32_t v5498 = crv_raw7;	// L8608
          int32_t v5499 = crv_addr7;	// L8609
          int32_t v5500 = v5499 & 7;	// L8610
          int v5501 = v5500;	// L8611
          irf7[v5501] = v5498;	// L8612
        } else {
          int32_t v5502 = crv_addr7;	// L8614
          bool v5503 = v5502 == 0;	// L8615
          if (v5503) {	// L8616
            int32_t v5504 = crv_raw7;	// L8617
            int32_t v5505 = v5504 & 255;	// L8618
            dsmask7 = v5505;	// L8619
            int32_t v5506 = crv_raw7;	// L8620
            int32_t v5507 = v5506 >> 8;	// L8621
            int32_t v5508 = v5507 & 7;	// L8622
            cfg_isz7 = v5508;	// L8623
            int32_t v5509 = crv_raw7;	// L8624
            int32_t v5510 = v5509 >> 15;	// L8625
            int32_t v5511 = v5510 & 1;	// L8626
            bool v5512 = v5511 == 1;	// L8627
            if (v5512) {	// L8628
              fetch_en7 = 1;	// L8629
              instr_cnt7 = 0;	// L8630
              iter_cnt7 = 0;	// L8631
            }
          } else {
            int32_t v5513 = crv_addr7;	// L8634
            bool v5514 = v5513 == 1;	// L8635
            if (v5514) {	// L8636
              int32_t v5515 = crv_raw7;	// L8637
              int32_t v5516 = v5515 & 255;	// L8638
              cfg_itsz7 = v5516;	// L8639
            }
          }
        }
      } else {
        int32_t v5517 = crv_addr7;	// L8644
        bool v5518 = v5517 < 8;	// L8645
        int32_t v5519 = dsmask7;	// L8646
        int32_t v5520 = v5519 >> v5517;	// L8647
        int32_t v5521 = v5520 & 1;	// L8648
        bool v5522 = v5521 == 1;	// L8649
        bool v5523 = v5518 & v5522;	// L8650
        if (v5523) {	// L8651
          int32_t v5524 = crv_addr7;	// L8652
          int v5525 = v5524;	// L8653
          int32_t v5526 = drf_full7[v5525];	// L8654
          bool v5527 = v5526 == 0;	// L8655
          if (v5527) {	// L8656
            half v5528 = crv_data7;	// L8657
            int32_t v5529 = crv_addr7;	// L8658
            int v5530 = v5529;	// L8659
            drf7[v5530] = v5528;	// L8660
            int32_t v5531 = crv_addr7;	// L8661
            int v5532 = v5531;	// L8662
            drf_full7[v5532] = 1;	// L8663
          }
        } else {
          half v5533 = crv_data7;	// L8666
          int32_t v5534 = crv_addr7;	// L8667
          int v5535 = v5534;	// L8668
          drf7[v5535] = v5533;	// L8669
        }
      }
    }
  }
}

void node_2_0(
  hls::stream< ap_uint<26> >& v5536,
  hls::stream< ap_uint<26> >& v5537,
  hls::stream< ap_uint<26> >& v5538,
  hls::stream< ap_uint<26> >& v5539,
  hls::stream< ap_uint<17> >& v5540,
  hls::stream< ap_uint<17> >& v5541,
  hls::stream< ap_uint<17> >& v5542,
  hls::stream< ap_uint<17> >& v5543,
  hls::stream< int32_t >& v5544,
  hls::stream< int32_t >& v5545,
  hls::stream< int32_t >& v5546,
  hls::stream< int32_t >& v5547,
  hls::stream< ap_uint<26> >& v5548,
  hls::stream< ap_uint<26> >& v5549,
  hls::stream< ap_uint<26> >& v5550,
  hls::stream< ap_uint<26> >& v5551,
  hls::stream< int32_t >& v5552,
  hls::stream< int32_t >& v5553,
  hls::stream< int32_t >& v5554,
  hls::stream< int32_t >& v5555,
  hls::stream< ap_uint<17> >& v5556,
  hls::stream< ap_uint<17> >& v5557,
  hls::stream< ap_uint<17> >& v5558,
  hls::stream< ap_uint<17> >& v5559
) {	// L8676
  int32_t irf8[8];	// L8707
  for (int v5561 = 0; v5561 < 8; v5561++) {	// L8708
    irf8[v5561] = 0;	// L8708
  }
  half drf8[8];	// L8709
  #pragma HLS array_partition variable=drf8 complete dim=1

  for (int v5563 = 0; v5563 < 8; v5563++) {	// L8710
    drf8[v5563] = (double)0.000000;	// L8710
  }
  int32_t drf_full8[8];	// L8711
  #pragma HLS array_partition variable=drf_full8 complete dim=1

  for (int v5565 = 0; v5565 < 8; v5565++) {	// L8712
    drf_full8[v5565] = 0;	// L8712
  }
  int32_t dsmask8;	// L8713
  dsmask8 = 0;	// L8714
  int32_t crv_vld8;	// L8715
  crv_vld8 = 0;	// L8716
  half crv_data8;	// L8717
  crv_data8 = (double)0.000000;	// L8718
  int32_t crv_addr8;	// L8719
  crv_addr8 = 0;	// L8720
  int32_t crv_mode8;	// L8721
  crv_mode8 = 0;	// L8722
  int32_t crv_raw8;	// L8723
  crv_raw8 = 0;	// L8724
  int32_t csd_vld8;	// L8725
  csd_vld8 = 0;	// L8726
  ap_uint<26> csd_pkt8;	// L8727
  csd_pkt8 = 0;	// L8728
  int32_t csd_dir8;	// L8729
  csd_dir8 = 0;	// L8730
  int32_t row_id8;	// L8731
  row_id8 = 2;	// L8732
  int32_t col_id8;	// L8733
  col_id8 = 0;	// L8734
  ap_uint<26> oe_r8;	// L8735
  oe_r8 = 0;	// L8736
  ap_uint<26> ow_r8;	// L8737
  ow_r8 = 0;	// L8738
  ap_uint<26> on_r8;	// L8739
  on_r8 = 0;	// L8740
  ap_uint<26> os_r8;	// L8741
  os_r8 = 0;	// L8742
  ap_uint<17> txn_r8;	// L8743
  txn_r8 = 0;	// L8744
  ap_uint<17> txs_r8;	// L8745
  txs_r8 = 0;	// L8746
  ap_uint<17> txw_r8;	// L8747
  txw_r8 = 0;	// L8748
  ap_uint<17> txe_r8;	// L8749
  txe_r8 = 0;	// L8750
  half hold_v8[4][2];	// L8751
  #pragma HLS array_partition variable=hold_v8 complete dim=1
  #pragma HLS array_partition variable=hold_v8 complete dim=2

  for (int v5586 = 0; v5586 < 4; v5586++) {	// L8752
    for (int v5587 = 0; v5587 < 2; v5587++) {	// L8752
      hold_v8[v5586][v5587] = (double)0.000000;	// L8752
    }
  }
  int32_t hold_cnt8[4];	// L8753
  #pragma HLS array_partition variable=hold_cnt8 complete dim=1

  for (int v5589 = 0; v5589 < 4; v5589++) {	// L8754
    hold_cnt8[v5589] = 0;	// L8754
  }
  ap_uint<26> rbuf8[4][2];	// L8755
  #pragma HLS array_partition variable=rbuf8 complete dim=1
  #pragma HLS array_partition variable=rbuf8 complete dim=2

  for (int v5591 = 0; v5591 < 4; v5591++) {	// L8756
    for (int v5592 = 0; v5592 < 2; v5592++) {	// L8756
      rbuf8[v5591][v5592] = 0;	// L8756
    }
  }
  int32_t rbcnt8[4];	// L8757
  #pragma HLS array_partition variable=rbcnt8 complete dim=1

  for (int v5594 = 0; v5594 < 4; v5594++) {	// L8758
    rbcnt8[v5594] = 0;	// L8758
  }
  int32_t rcred8[4];	// L8759
  #pragma HLS array_partition variable=rcred8 complete dim=1

  for (int v5596 = 0; v5596 < 4; v5596++) {	// L8760
    rcred8[v5596] = 0;	// L8760
  }
  int32_t cre_r8;	// L8761
  cre_r8 = 2;	// L8762
  int32_t crw_r8;	// L8763
  crw_r8 = 2;	// L8764
  int32_t crs_r8;	// L8765
  crs_r8 = 2;	// L8766
  int32_t crn_r8;	// L8767
  crn_r8 = 2;	// L8768
  int32_t cfg_isz8;	// L8769
  cfg_isz8 = 0;	// L8770
  int32_t cfg_itsz8;	// L8771
  cfg_itsz8 = 0;	// L8772
  int32_t fetch_en8;	// L8773
  fetch_en8 = 0;	// L8774
  int32_t instr_cnt8;	// L8775
  instr_cnt8 = 0;	// L8776
  int32_t iter_cnt8;	// L8777
  iter_cnt8 = 0;	// L8778
  int32_t condition_reg8;	// L8779
  condition_reg8 = 0;	// L8780
  l_S_t_0_t8: for (int t8 = 0; t8 < 8; t8++) {	// L8781
  #pragma HLS pipeline II=1
    ap_int<26> v5608 = oe_r8;	// L8782
    v5536.write(v5608);	// L8783
    ap_int<26> v5609 = ow_r8;	// L8784
    v5537.write(v5609);	// L8785
    ap_int<26> v5610 = os_r8;	// L8786
    v5538.write(v5610);	// L8787
    ap_int<26> v5611 = on_r8;	// L8788
    v5539.write(v5611);	// L8789
    ap_int<17> v5612 = txe_r8;	// L8790
    v5540.write(v5612);	// L8791
    ap_int<17> v5613 = txw_r8;	// L8792
    v5541.write(v5613);	// L8793
    ap_int<17> v5614 = txs_r8;	// L8794
    v5542.write(v5614);	// L8795
    ap_int<17> v5615 = txn_r8;	// L8796
    v5543.write(v5615);	// L8797
    int32_t v5616 = cre_r8;	// L8798
    v5544.write(v5616);	// L8799
    int32_t v5617 = crw_r8;	// L8800
    v5545.write(v5617);	// L8801
    int32_t v5618 = crs_r8;	// L8802
    v5546.write(v5618);	// L8803
    int32_t v5619 = crn_r8;	// L8804
    v5547.write(v5619);	// L8805
    ap_uint<26> v5620 = v5548.read();	// L8806
    ap_uint<26> p_w8;	// L8807
    p_w8 = v5620;	// L8808
    ap_uint<26> v5622 = v5549.read();	// L8809
    ap_uint<26> p_e8;	// L8810
    p_e8 = v5622;	// L8811
    ap_uint<26> v5624 = v5550.read();	// L8812
    ap_uint<26> p_n8;	// L8813
    p_n8 = v5624;	// L8814
    ap_uint<26> v5626 = v5551.read();	// L8815
    ap_uint<26> p_s8;	// L8816
    p_s8 = v5626;	// L8817
    int32_t v5628 = v5552.read();	// L8818
    int32_t v5629 = rcred8[0];	// L8819
    ap_int<33> v5630 = v5629;	// L8820
    ap_int<33> v5631 = v5628;	// L8821
    ap_int<33> v5632 = v5630 + v5631;	// L8822
    int32_t v5633 = v5632;	// L8823
    rcred8[0] = v5633;	// L8824
    int32_t v5634 = v5553.read();	// L8825
    int32_t v5635 = rcred8[1];	// L8826
    ap_int<33> v5636 = v5635;	// L8827
    ap_int<33> v5637 = v5634;	// L8828
    ap_int<33> v5638 = v5636 + v5637;	// L8829
    int32_t v5639 = v5638;	// L8830
    rcred8[1] = v5639;	// L8831
    int32_t v5640 = v5554.read();	// L8832
    int32_t v5641 = rcred8[2];	// L8833
    ap_int<33> v5642 = v5641;	// L8834
    ap_int<33> v5643 = v5640;	// L8835
    ap_int<33> v5644 = v5642 + v5643;	// L8836
    int32_t v5645 = v5644;	// L8837
    rcred8[2] = v5645;	// L8838
    int32_t v5646 = v5555.read();	// L8839
    int32_t v5647 = rcred8[3];	// L8840
    ap_int<33> v5648 = v5647;	// L8841
    ap_int<33> v5649 = v5646;	// L8842
    ap_int<33> v5650 = v5648 + v5649;	// L8843
    int32_t v5651 = v5650;	// L8844
    rcred8[3] = v5651;	// L8845
    ap_uint<26> fin8[4];	// L8846
    for (int v5653 = 0; v5653 < 4; v5653++) {	// L8847
      fin8[v5653] = 0;	// L8847
    }
    ap_int<26> v5654 = p_w8;	// L8848
    fin8[0] = v5654;	// L8849
    ap_int<26> v5655 = p_e8;	// L8850
    fin8[1] = v5655;	// L8851
    ap_int<26> v5656 = p_n8;	// L8852
    fin8[2] = v5656;	// L8853
    ap_int<26> v5657 = p_s8;	// L8854
    fin8[3] = v5657;	// L8855
    l_S_d_0_d32: for (int d32 = 0; d32 < 4; d32++) {	// L8856
      ap_uint<26> v5659 = fin8[d32];	// L8857
      bool v5660;
      ap_int<26> v5660_tmp = v5659;
      v5660 = v5660_tmp[25];	// L8858
      int32_t v5661 = v5660;	// L8859
      bool v5662 = v5661 == 1;	// L8860
      int32_t v5663 = rbcnt8[d32];	// L8861
      bool v5664 = v5663 < 2;	// L8862
      bool v5665 = v5662 & v5664;	// L8863
      if (v5665) {	// L8864
        ap_uint<26> v5666 = fin8[d32];	// L8865
        int32_t v5667 = rbcnt8[d32];	// L8866
        int v5668 = v5667;	// L8867
        rbuf8[d32][v5668] = v5666;	// L8868
        int32_t v5669 = rbcnt8[d32];	// L8869
        ap_int<33> v5670 = v5669;	// L8870
        ap_int<33> v5671 = v5670 + 1;	// L8871
        int32_t v5672 = v5671;	// L8872
        rbcnt8[d32] = v5672;	// L8873
      }
    }
    ap_uint<26> hd8[4];	// L8876
    for (int v5674 = 0; v5674 < 4; v5674++) {	// L8877
      hd8[v5674] = 0;	// L8877
    }
    int32_t hvld8[4];	// L8878
    for (int v5676 = 0; v5676 < 4; v5676++) {	// L8879
      hvld8[v5676] = 0;	// L8879
    }
    int32_t hit8[4];	// L8880
    for (int v5678 = 0; v5678 < 4; v5678++) {	// L8881
      hit8[v5678] = 0;	// L8881
    }
    int32_t axis8[4];	// L8882
    for (int v5680 = 0; v5680 < 4; v5680++) {	// L8883
      axis8[v5680] = 0;	// L8883
    }
    int32_t v5681 = col_id8;	// L8884
    axis8[0] = v5681;	// L8885
    int32_t v5682 = col_id8;	// L8886
    axis8[1] = v5682;	// L8887
    int32_t v5683 = row_id8;	// L8888
    axis8[2] = v5683;	// L8889
    int32_t v5684 = row_id8;	// L8890
    axis8[3] = v5684;	// L8891
    l_S_d_1_d33: for (int d33 = 0; d33 < 4; d33++) {	// L8892
      int32_t v5686 = rbcnt8[d33];	// L8893
      bool v5687 = v5686 > 0;	// L8894
      if (v5687) {	// L8895
        ap_uint<26> v5688 = rbuf8[d33][0];	// L8896
        hd8[d33] = v5688;	// L8897
        hvld8[d33] = 1;	// L8898
        ap_uint<26> v5689 = hd8[d33];	// L8899
        ap_int<4> v5690;
        ap_int<26> v5690_tmp = v5689;
        v5690 = v5690_tmp(24, 21);	// L8900
        int32_t v5691 = axis8[d33];	// L8901
        int32_t v5692 = v5690;	// L8902
        bool v5693 = v5692 == v5691;	// L8903
        if (v5693) {	// L8904
          hit8[d33] = 1;	// L8905
        }
      }
    }
    ap_uint<26> o_crv8;	// L8909
    o_crv8 = 0;	// L8910
    int32_t crv_in8;	// L8911
    crv_in8 = -1;	// L8912
    int32_t v5696 = hit8[3];	// L8913
    bool v5697 = v5696 == 1;	// L8914
    if (v5697) {	// L8915
      ap_uint<26> v5698 = hd8[3];	// L8916
      o_crv8 = v5698;	// L8917
      crv_in8 = 3;	// L8918
    } else {
      int32_t v5699 = hit8[2];	// L8920
      bool v5700 = v5699 == 1;	// L8921
      if (v5700) {	// L8922
        ap_uint<26> v5701 = hd8[2];	// L8923
        o_crv8 = v5701;	// L8924
        crv_in8 = 2;	// L8925
      } else {
        int32_t v5702 = hit8[1];	// L8927
        bool v5703 = v5702 == 1;	// L8928
        if (v5703) {	// L8929
          ap_uint<26> v5704 = hd8[1];	// L8930
          o_crv8 = v5704;	// L8931
          crv_in8 = 1;	// L8932
        } else {
          int32_t v5705 = hit8[0];	// L8934
          bool v5706 = v5705 == 1;	// L8935
          if (v5706) {	// L8936
            ap_uint<26> v5707 = hd8[0];	// L8937
            o_crv8 = v5707;	// L8938
            crv_in8 = 0;	// L8939
          }
        }
      }
    }
    ap_uint<26> o_out8[4];	// L8944
    for (int v5709 = 0; v5709 < 4; v5709++) {	// L8945
      o_out8[v5709] = 0;	// L8945
    }
    int32_t pop8[4];	// L8946
    for (int v5711 = 0; v5711 < 4; v5711++) {	// L8947
      pop8[v5711] = 0;	// L8947
    }
    int32_t inj_done8;	// L8948
    inj_done8 = 0;	// L8949
    int32_t idir8;	// L8950
    idir8 = -1;	// L8951
    ap_int<26> v5714 = csd_pkt8;	// L8952
    bool v5715;
    ap_int<26> v5715_tmp = v5714;
    v5715 = v5715_tmp[25];	// L8953
    int32_t v5716 = v5715;	// L8954
    bool v5717 = v5716 == 1;	// L8955
    if (v5717) {	// L8956
      int32_t v5718 = csd_dir8;	// L8957
      ap_int<33> v5719 = v5718;	// L8958
      ap_int<33> v5720 = 3 - v5719;	// L8959
      int32_t v5721 = v5720;	// L8960
      idir8 = v5721;	// L8961
    }
    l_S_o_2_o8: for (int o8 = 0; o8 < 4; o8++) {	// L8963
      int32_t v5723 = rcred8[o8];	// L8964
      bool v5724 = v5723 > 0;	// L8965
      if (v5724) {	// L8966
        int32_t v5725 = idir8;	// L8967
        ap_int<33> v5726 = v5725;	// L8968
        ap_int<33> v5727 = o8;	// L8969
        bool v5728 = v5726 == v5727;	// L8970
        if (v5728) {	// L8971
          ap_int<26> v5729 = csd_pkt8;	// L8972
          o_out8[o8] = v5729;	// L8973
          int32_t v5730 = rcred8[o8];	// L8974
          ap_int<33> v5731 = v5730;	// L8975
          ap_int<33> v5732 = v5731 - 1;	// L8976
          int32_t v5733 = v5732;	// L8977
          rcred8[o8] = v5733;	// L8978
          inj_done8 = 1;	// L8979
        } else {
          int32_t v5734 = hvld8[o8];	// L8981
          bool v5735 = v5734 == 1;	// L8982
          int32_t v5736 = hit8[o8];	// L8983
          bool v5737 = v5736 == 0;	// L8984
          bool v5738 = v5735 & v5737;	// L8985
          if (v5738) {	// L8986
            ap_uint<26> v5739 = hd8[o8];	// L8987
            o_out8[o8] = v5739;	// L8988
            int32_t v5740 = rcred8[o8];	// L8989
            ap_int<33> v5741 = v5740;	// L8990
            ap_int<33> v5742 = v5741 - 1;	// L8991
            int32_t v5743 = v5742;	// L8992
            rcred8[o8] = v5743;	// L8993
            pop8[o8] = 1;	// L8994
          }
        }
      }
    }
    int32_t v5744 = crv_in8;	// L8999
    bool v5745 = v5744 >= 0;	// L9000
    if (v5745) {	// L9001
      int32_t v5746 = crv_in8;	// L9002
      int v5747 = v5746;	// L9003
      pop8[v5747] = 1;	// L9004
    }
    int32_t ret8[4];	// L9006
    for (int v5749 = 0; v5749 < 4; v5749++) {	// L9007
      ret8[v5749] = 0;	// L9007
    }
    l_S_d_3_d34: for (int d34 = 0; d34 < 4; d34++) {	// L9008
      int32_t v5751 = pop8[d34];	// L9009
      bool v5752 = v5751 == 1;	// L9010
      if (v5752) {	// L9011
        l_S_sft_3_sft8: for (int sft8 = 0; sft8 < 1; sft8++) {	// L9012
          ap_uint<26> v5754 = rbuf8[d34][(sft8 + 1)];	// L9013
          rbuf8[d34][sft8] = v5754;	// L9014
        }
        int32_t v5755 = rbcnt8[d34];	// L9016
        ap_int<33> v5756 = v5755;	// L9017
        ap_int<33> v5757 = v5756 - 1;	// L9018
        int32_t v5758 = v5757;	// L9019
        rbcnt8[d34] = v5758;	// L9020
        ret8[d34] = 1;	// L9021
      }
    }
    int32_t v5759 = ret8[0];	// L9024
    cre_r8 = v5759;	// L9025
    int32_t v5760 = ret8[1];	// L9026
    crw_r8 = v5760;	// L9027
    int32_t v5761 = ret8[2];	// L9028
    crs_r8 = v5761;	// L9029
    int32_t v5762 = ret8[3];	// L9030
    crn_r8 = v5762;	// L9031
    ap_uint<26> v5763 = o_out8[0];	// L9032
    oe_r8 = v5763;	// L9033
    ap_uint<26> v5764 = o_out8[1];	// L9034
    ow_r8 = v5764;	// L9035
    ap_uint<26> v5765 = o_out8[2];	// L9036
    os_r8 = v5765;	// L9037
    ap_uint<26> v5766 = o_out8[3];	// L9038
    on_r8 = v5766;	// L9039
    int32_t v5767 = inj_done8;	// L9040
    bool v5768 = v5767 == 1;	// L9041
    if (v5768) {	// L9042
      csd_pkt8 = 0;	// L9043
    }
    ap_int<26> v5769 = o_crv8;	// L9045
    bool v5770;
    ap_int<26> v5770_tmp = v5769;
    v5770 = v5770_tmp[25];	// L9046
    int32_t v5771 = v5770;	// L9047
    crv_vld8 = v5771;	// L9048
    ap_int<26> v5772 = o_crv8;	// L9049
    int16_t v5773;
    ap_int<26> v5773_tmp = v5772;
    v5773 = v5773_tmp(15, 0);	// L9050
    half v5774;
    union { uint16_t from; half to;} _converter_v5773_to_v5774;
    _converter_v5773_to_v5774.from = v5773;
    v5774 = _converter_v5773_to_v5774.to;	// L9051
    crv_data8 = v5774;	// L9052
    ap_int<26> v5775 = o_crv8;	// L9053
    ap_int<4> v5776;
    ap_int<26> v5776_tmp = v5775;
    v5776 = v5776_tmp(19, 16);	// L9054
    int32_t v5777 = v5776;	// L9055
    crv_addr8 = v5777;	// L9056
    ap_int<26> v5778 = o_crv8;	// L9057
    bool v5779;
    ap_int<26> v5779_tmp = v5778;
    v5779 = v5779_tmp[20];	// L9058
    int32_t v5780 = v5779;	// L9059
    crv_mode8 = v5780;	// L9060
    ap_int<26> v5781 = o_crv8;	// L9061
    int16_t v5782;
    ap_int<26> v5782_tmp = v5781;
    v5782 = v5782_tmp(15, 0);	// L9062
    int32_t v5783 = v5782;	// L9063
    crv_raw8 = v5783;	// L9064
    ap_uint<17> v5784 = v5556.read();	// L9065
    ap_uint<17> rx_w8;	// L9066
    rx_w8 = v5784;	// L9067
    ap_uint<17> v5786 = v5557.read();	// L9068
    ap_uint<17> rx_e8;	// L9069
    rx_e8 = v5786;	// L9070
    ap_uint<17> v5788 = v5558.read();	// L9071
    ap_uint<17> rx_n8;	// L9072
    rx_n8 = v5788;	// L9073
    ap_uint<17> v5790 = v5559.read();	// L9074
    ap_uint<17> rx_s8;	// L9075
    rx_s8 = v5790;	// L9076
    half rxv8[4];	// L9077
    for (int v5793 = 0; v5793 < 4; v5793++) {	// L9078
      rxv8[v5793] = (double)0.000000;	// L9078
    }
    int32_t rxvld8[4];	// L9079
    for (int v5795 = 0; v5795 < 4; v5795++) {	// L9080
      rxvld8[v5795] = 0;	// L9080
    }
    ap_int<17> v5796 = rx_n8;	// L9081
    int16_t v5797;
    ap_int<17> v5797_tmp = v5796;
    v5797 = v5797_tmp(16, 1);	// L9082
    half v5798;
    union { uint16_t from; half to;} _converter_v5797_to_v5798;
    _converter_v5797_to_v5798.from = v5797;
    v5798 = _converter_v5797_to_v5798.to;	// L9083
    rxv8[0] = v5798;	// L9084
    ap_int<17> v5799 = rx_n8;	// L9085
    bool v5800;
    ap_int<17> v5800_tmp = v5799;
    v5800 = v5800_tmp[0];	// L9086
    int32_t v5801 = v5800;	// L9087
    rxvld8[0] = v5801;	// L9088
    ap_int<17> v5802 = rx_s8;	// L9089
    int16_t v5803;
    ap_int<17> v5803_tmp = v5802;
    v5803 = v5803_tmp(16, 1);	// L9090
    half v5804;
    union { uint16_t from; half to;} _converter_v5803_to_v5804;
    _converter_v5803_to_v5804.from = v5803;
    v5804 = _converter_v5803_to_v5804.to;	// L9091
    rxv8[1] = v5804;	// L9092
    ap_int<17> v5805 = rx_s8;	// L9093
    bool v5806;
    ap_int<17> v5806_tmp = v5805;
    v5806 = v5806_tmp[0];	// L9094
    int32_t v5807 = v5806;	// L9095
    rxvld8[1] = v5807;	// L9096
    ap_int<17> v5808 = rx_w8;	// L9097
    int16_t v5809;
    ap_int<17> v5809_tmp = v5808;
    v5809 = v5809_tmp(16, 1);	// L9098
    half v5810;
    union { uint16_t from; half to;} _converter_v5809_to_v5810;
    _converter_v5809_to_v5810.from = v5809;
    v5810 = _converter_v5809_to_v5810.to;	// L9099
    rxv8[2] = v5810;	// L9100
    ap_int<17> v5811 = rx_w8;	// L9101
    bool v5812;
    ap_int<17> v5812_tmp = v5811;
    v5812 = v5812_tmp[0];	// L9102
    int32_t v5813 = v5812;	// L9103
    rxvld8[2] = v5813;	// L9104
    ap_int<17> v5814 = rx_e8;	// L9105
    int16_t v5815;
    ap_int<17> v5815_tmp = v5814;
    v5815 = v5815_tmp(16, 1);	// L9106
    half v5816;
    union { uint16_t from; half to;} _converter_v5815_to_v5816;
    _converter_v5815_to_v5816.from = v5815;
    v5816 = _converter_v5815_to_v5816.to;	// L9107
    rxv8[3] = v5816;	// L9108
    ap_int<17> v5817 = rx_e8;	// L9109
    bool v5818;
    ap_int<17> v5818_tmp = v5817;
    v5818 = v5818_tmp[0];	// L9110
    int32_t v5819 = v5818;	// L9111
    rxvld8[3] = v5819;	// L9112
    l_S_d_5_d35: for (int d35 = 0; d35 < 4; d35++) {	// L9113
      int32_t v5821 = rxvld8[d35];	// L9114
      bool v5822 = v5821 == 1;	// L9115
      int32_t v5823 = hold_cnt8[d35];	// L9116
      bool v5824 = v5823 < 2;	// L9117
      bool v5825 = v5822 & v5824;	// L9118
      if (v5825) {	// L9119
        half v5826 = rxv8[d35];	// L9120
        int32_t v5827 = hold_cnt8[d35];	// L9121
        int v5828 = v5827;	// L9122
        hold_v8[d35][v5828] = v5826;	// L9123
        int32_t v5829 = hold_cnt8[d35];	// L9124
        ap_int<33> v5830 = v5829;	// L9125
        ap_int<33> v5831 = v5830 + 1;	// L9126
        int32_t v5832 = v5831;	// L9127
        hold_cnt8[d35] = v5832;	// L9128
      }
    }
    int32_t pc8;	// L9131
    pc8 = -1;	// L9132
    int32_t v5834 = fetch_en8;	// L9133
    bool v5835 = v5834 == 1;	// L9134
    if (v5835) {	// L9135
      int32_t v5836 = instr_cnt8;	// L9136
      pc8 = v5836;	// L9137
    }
    int32_t instr8;	// L9139
    instr8 = 0;	// L9140
    int32_t v5838 = pc8;	// L9141
    bool v5839 = v5838 >= 0;	// L9142
    if (v5839) {	// L9143
      int32_t v5840 = pc8;	// L9144
      int v5841 = v5840;	// L9145
      int32_t v5842 = irf8[v5841];	// L9146
      instr8 = v5842;	// L9147
    }
    int32_t v5843 = instr8;	// L9149
    int32_t v5844 = v5843 & 15;	// L9150
    int32_t op8;	// L9151
    op8 = v5844;	// L9152
    int32_t v5846 = instr8;	// L9153
    int32_t v5847 = v5846 >> 4;	// L9154
    int32_t v5848 = v5847 & 15;	// L9155
    int32_t dst8;	// L9156
    dst8 = v5848;	// L9157
    int32_t v5850 = instr8;	// L9158
    int32_t v5851 = v5850 >> 8;	// L9159
    int32_t v5852 = v5851 & 15;	// L9160
    int32_t s18;	// L9161
    s18 = v5852;	// L9162
    int32_t v5854 = instr8;	// L9163
    int32_t v5855 = v5854 >> 12;	// L9164
    int32_t v5856 = v5855 & 15;	// L9165
    int32_t s28;	// L9166
    s28 = v5856;	// L9167
    half a8;	// L9168
    a8 = (double)0.000000;	// L9169
    half b8;	// L9170
    b8 = (double)0.000000;	// L9171
    int32_t v5860 = s18;	// L9172
    bool v5861 = v5860 >= 12;	// L9173
    if (v5861) {	// L9174
      int32_t v5862 = s18;	// L9175
      int32_t v5863 = v5862 & 3;	// L9176
      int v5864 = v5863;	// L9177
      half v5865 = hold_v8[v5864][0];	// L9178
      a8 = v5865;	// L9179
    } else {
      int32_t v5866 = s18;	// L9181
      int v5867 = v5866;	// L9182
      half v5868 = drf8[v5867];	// L9183
      a8 = v5868;	// L9184
    }
    int32_t v5869 = s28;	// L9186
    bool v5870 = v5869 >= 12;	// L9187
    if (v5870) {	// L9188
      int32_t v5871 = s28;	// L9189
      int32_t v5872 = v5871 & 3;	// L9190
      int v5873 = v5872;	// L9191
      half v5874 = hold_v8[v5873][0];	// L9192
      b8 = v5874;	// L9193
    } else {
      int32_t v5875 = s28;	// L9195
      int v5876 = v5875;	// L9196
      half v5877 = drf8[v5876];	// L9197
      b8 = v5877;	// L9198
    }
    int32_t a_vld8;	// L9200
    a_vld8 = 1;	// L9201
    int32_t b_vld8;	// L9202
    b_vld8 = 1;	// L9203
    int32_t v5880 = s18;	// L9204
    bool v5881 = v5880 >= 12;	// L9205
    if (v5881) {	// L9206
      a_vld8 = 0;	// L9207
      int32_t v5882 = s18;	// L9208
      int32_t v5883 = v5882 & 3;	// L9209
      int v5884 = v5883;	// L9210
      int32_t v5885 = hold_cnt8[v5884];	// L9211
      bool v5886 = v5885 > 0;	// L9212
      if (v5886) {	// L9213
        a_vld8 = 1;	// L9214
      }
    }
    int32_t v5887 = s28;	// L9217
    bool v5888 = v5887 >= 12;	// L9218
    if (v5888) {	// L9219
      b_vld8 = 0;	// L9220
      int32_t v5889 = s28;	// L9221
      int32_t v5890 = v5889 & 3;	// L9222
      int v5891 = v5890;	// L9223
      int32_t v5892 = hold_cnt8[v5891];	// L9224
      bool v5893 = v5892 > 0;	// L9225
      if (v5893) {	// L9226
        b_vld8 = 1;	// L9227
      }
    }
    int32_t v5894 = s18;	// L9230
    bool v5895 = v5894 < 8;	// L9231
    int32_t v5896 = dsmask8;	// L9232
    int32_t v5897 = v5896 >> v5894;	// L9233
    int32_t v5898 = v5897 & 1;	// L9234
    bool v5899 = v5898 == 1;	// L9235
    bool v5900 = v5895 & v5899;	// L9236
    if (v5900) {	// L9237
      int32_t v5901 = s18;	// L9238
      int v5902 = v5901;	// L9239
      int32_t v5903 = drf_full8[v5902];	// L9240
      bool v5904 = v5903 == 0;	// L9241
      if (v5904) {	// L9242
        a_vld8 = 0;	// L9243
      }
    }
    int32_t v5905 = s28;	// L9246
    bool v5906 = v5905 < 8;	// L9247
    int32_t v5907 = dsmask8;	// L9248
    int32_t v5908 = v5907 >> v5905;	// L9249
    int32_t v5909 = v5908 & 1;	// L9250
    bool v5910 = v5909 == 1;	// L9251
    bool v5911 = v5906 & v5910;	// L9252
    if (v5911) {	// L9253
      int32_t v5912 = s28;	// L9254
      int v5913 = v5912;	// L9255
      int32_t v5914 = drf_full8[v5913];	// L9256
      bool v5915 = v5914 == 0;	// L9257
      if (v5915) {	// L9258
        b_vld8 = 0;	// L9259
      }
    }
    int32_t binop8;	// L9262
    binop8 = 0;	// L9263
    int32_t v5917 = op8;	// L9264
    bool v5918 = v5917 == 0;	// L9265
    bool v5919 = v5917 == 1;	// L9266
    bool v5920 = v5917 == 2;	// L9267
    bool v5921 = v5917 == 8;	// L9268
    bool v5922 = v5917 == 9;	// L9269
    bool v5923 = v5918 | v5919;	// L9270
    bool v5924 = v5923 | v5920;	// L9271
    bool v5925 = v5924 | v5921;	// L9272
    bool v5926 = v5925 | v5922;	// L9273
    if (v5926) {	// L9274
      binop8 = 1;	// L9275
    }
    int32_t grant8;	// L9277
    grant8 = 0;	// L9278
    int32_t v5928 = pc8;	// L9279
    bool v5929 = v5928 >= 0;	// L9280
    if (v5929) {	// L9281
      grant8 = 1;	// L9282
    }
    int32_t v5930 = pc8;	// L9284
    bool v5931 = v5930 >= 0;	// L9285
    int32_t v5932 = a_vld8;	// L9286
    bool v5933 = v5932 == 0;	// L9287
    int32_t v5934 = binop8;	// L9288
    bool v5935 = v5934 == 1;	// L9289
    int32_t v5936 = b_vld8;	// L9290
    bool v5937 = v5936 == 0;	// L9291
    bool v5938 = v5935 & v5937;	// L9292
    bool v5939 = v5933 | v5938;	// L9293
    bool v5940 = v5931 & v5939;	// L9294
    if (v5940) {	// L9295
      grant8 = 0;	// L9296
    }
    int32_t v5941 = grant8;	// L9298
    bool v5942 = v5941 == 1;	// L9299
    if (v5942) {	// L9300
      int32_t v5943 = instr_cnt8;	// L9301
      int32_t v5944 = cfg_isz8;	// L9302
      bool v5945 = v5943 == v5944;	// L9303
      if (v5945) {	// L9304
        instr_cnt8 = 0;	// L9305
        int32_t v5946 = iter_cnt8;	// L9306
        int32_t v5947 = cfg_itsz8;	// L9307
        ap_int<33> v5948 = v5947;	// L9308
        ap_int<33> v5949 = v5948 - 1;	// L9309
        ap_int<33> v5950 = v5946;	// L9310
        bool v5951 = v5950 == v5949;	// L9311
        if (v5951) {	// L9312
          fetch_en8 = 0;	// L9313
        } else {
          int32_t v5952 = iter_cnt8;	// L9315
          ap_int<33> v5953 = v5952;	// L9316
          ap_int<33> v5954 = v5953 + 1;	// L9317
          int32_t v5955 = v5954;	// L9318
          iter_cnt8 = v5955;	// L9319
        }
      } else {
        int32_t v5956 = instr_cnt8;	// L9322
        ap_int<33> v5957 = v5956;	// L9323
        ap_int<33> v5958 = v5957 + 1;	// L9324
        int32_t v5959 = v5958;	// L9325
        instr_cnt8 = v5959;	// L9326
      }
    }
    int32_t c18;	// L9329
    c18 = -1;	// L9330
    int32_t c28;	// L9331
    c28 = -1;	// L9332
    int32_t v5962 = grant8;	// L9333
    bool v5963 = v5962 == 1;	// L9334
    int32_t v5964 = s18;	// L9335
    bool v5965 = v5964 >= 12;	// L9336
    bool v5966 = v5963 & v5965;	// L9337
    if (v5966) {	// L9338
      int32_t v5967 = s18;	// L9339
      int32_t v5968 = v5967 & 3;	// L9340
      c18 = v5968;	// L9341
    }
    int32_t v5969 = grant8;	// L9343
    bool v5970 = v5969 == 1;	// L9344
    int32_t v5971 = s28;	// L9345
    bool v5972 = v5971 >= 12;	// L9346
    bool v5973 = v5970 & v5972;	// L9347
    if (v5973) {	// L9348
      int32_t v5974 = s28;	// L9349
      int32_t v5975 = v5974 & 3;	// L9350
      c28 = v5975;	// L9351
    }
    int32_t v5976 = c18;	// L9353
    bool v5977 = v5976 >= 0;	// L9354
    if (v5977) {	// L9355
      int32_t v5978 = c18;	// L9356
      int v5979 = v5978;	// L9357
      half v5980 = hold_v8[v5979][1];	// L9358
      hold_v8[v5979][0] = v5980;	// L9359
      int32_t v5981 = c18;	// L9360
      int v5982 = v5981;	// L9361
      int32_t v5983 = hold_cnt8[v5982];	// L9362
      ap_int<33> v5984 = v5983;	// L9363
      ap_int<33> v5985 = v5984 - 1;	// L9364
      int32_t v5986 = v5985;	// L9365
      hold_cnt8[v5982] = v5986;	// L9366
    }
    int32_t v5987 = c28;	// L9368
    bool v5988 = v5987 >= 0;	// L9369
    int32_t v5989 = c18;	// L9370
    bool v5990 = v5987 != v5989;	// L9371
    bool v5991 = v5988 & v5990;	// L9372
    if (v5991) {	// L9373
      int32_t v5992 = c28;	// L9374
      int v5993 = v5992;	// L9375
      half v5994 = hold_v8[v5993][1];	// L9376
      hold_v8[v5993][0] = v5994;	// L9377
      int32_t v5995 = c28;	// L9378
      int v5996 = v5995;	// L9379
      int32_t v5997 = hold_cnt8[v5996];	// L9380
      ap_int<33> v5998 = v5997;	// L9381
      ap_int<33> v5999 = v5998 - 1;	// L9382
      int32_t v6000 = v5999;	// L9383
      hold_cnt8[v5996] = v6000;	// L9384
    }
    int32_t v6001 = grant8;	// L9386
    bool v6002 = v6001 == 1;	// L9387
    int32_t v6003 = s18;	// L9388
    bool v6004 = v6003 < 8;	// L9389
    int32_t v6005 = dsmask8;	// L9390
    int32_t v6006 = v6005 >> v6003;	// L9391
    int32_t v6007 = v6006 & 1;	// L9392
    bool v6008 = v6007 == 1;	// L9393
    bool v6009 = v6002 & v6004;	// L9394
    bool v6010 = v6009 & v6008;	// L9395
    if (v6010) {	// L9396
      int32_t v6011 = s18;	// L9397
      int v6012 = v6011;	// L9398
      drf_full8[v6012] = 0;	// L9399
    }
    int32_t v6013 = grant8;	// L9401
    bool v6014 = v6013 == 1;	// L9402
    int32_t v6015 = s28;	// L9403
    bool v6016 = v6015 < 8;	// L9404
    int32_t v6017 = dsmask8;	// L9405
    int32_t v6018 = v6017 >> v6015;	// L9406
    int32_t v6019 = v6018 & 1;	// L9407
    bool v6020 = v6019 == 1;	// L9408
    bool v6021 = v6014 & v6016;	// L9409
    bool v6022 = v6021 & v6020;	// L9410
    if (v6022) {	// L9411
      int32_t v6023 = s28;	// L9412
      int v6024 = v6023;	// L9413
      drf_full8[v6024] = 0;	// L9414
    }
    half res8;	// L9416
    res8 = (double)0.000000;	// L9417
    int32_t v6026 = op8;	// L9418
    bool v6027 = v6026 == 0;	// L9419
    if (v6027) {	// L9420
      half v6028 = a8;	// L9421
      half v6029 = b8;	// L9422
      half v6030 = v6028 + v6029;	// L9423
      res8 = v6030;	// L9424
    } else {
      int32_t v6031 = op8;	// L9426
      bool v6032 = v6031 == 1;	// L9427
      if (v6032) {	// L9428
        half v6033 = a8;	// L9429
        half v6034 = b8;	// L9430
        half v6035 = v6033 - v6034;	// L9431
        res8 = v6035;	// L9432
      } else {
        int32_t v6036 = op8;	// L9434
        bool v6037 = v6036 == 2;	// L9435
        if (v6037) {	// L9436
          half v6038 = a8;	// L9437
          half v6039 = b8;	// L9438
          half v6040 = v6038 * v6039;	// L9439
          res8 = v6040;	// L9440
        } else {
          int32_t v6041 = op8;	// L9442
          bool v6042 = v6041 == 8;	// L9443
          if (v6042) {	// L9444
            half v6043 = a8;	// L9445
            half v6044 = b8;	// L9446
            bool v6045 = v6043 >= v6044;	// L9447
            if (v6045) {	// L9448
              res8 = (double)1.000000;	// L9449
            } else {
              res8 = (double)-1.000000;	// L9451
            }
          } else {
            int32_t v6046 = op8;	// L9454
            bool v6047 = v6046 == 9;	// L9455
            if (v6047) {	// L9456
              half v6048 = a8;	// L9457
              half v6049 = b8;	// L9458
              bool v6050 = v6048 < v6049;	// L9459
              if (v6050) {	// L9460
                res8 = (double)1.000000;	// L9461
              } else {
                res8 = (double)-1.000000;	// L9463
              }
            } else {
              half v6051 = a8;	// L9466
              res8 = v6051;	// L9467
            }
          }
        }
      }
    }
    int32_t v6052 = a_vld8;	// L9473
    int32_t res_vld8;	// L9474
    res_vld8 = v6052;	// L9475
    int32_t v6054 = op8;	// L9476
    bool v6055 = v6054 == 0;	// L9477
    bool v6056 = v6054 == 1;	// L9478
    bool v6057 = v6054 == 2;	// L9479
    bool v6058 = v6054 == 8;	// L9480
    bool v6059 = v6054 == 9;	// L9481
    bool v6060 = v6055 | v6056;	// L9482
    bool v6061 = v6060 | v6057;	// L9483
    bool v6062 = v6061 | v6058;	// L9484
    bool v6063 = v6062 | v6059;	// L9485
    if (v6063) {	// L9486
      int32_t v6064 = a_vld8;	// L9487
      int32_t v6065 = b_vld8;	// L9488
      int64_t v6066 = v6064;	// L9489
      int64_t v6067 = v6065;	// L9490
      int64_t v6068 = v6066 * v6067;	// L9491
      int32_t v6069 = v6068;	// L9492
      res_vld8 = v6069;	// L9493
    }
    int32_t v6070 = grant8;	// L9495
    bool v6071 = v6070 == 0;	// L9496
    if (v6071) {	// L9497
      res_vld8 = 0;	// L9498
    }
    int32_t v6072 = grant8;	// L9500
    bool v6073 = v6072 == 1;	// L9501
    int32_t v6074 = op8;	// L9502
    bool v6075 = v6074 == 8;	// L9503
    bool v6076 = v6073 & v6075;	// L9504
    if (v6076) {	// L9505
      condition_reg8 = 0;	// L9506
      half v6077 = a8;	// L9507
      half v6078 = b8;	// L9508
      bool v6079 = v6077 >= v6078;	// L9509
      if (v6079) {	// L9510
        condition_reg8 = 1;	// L9511
      }
    }
    int32_t v6080 = grant8;	// L9514
    bool v6081 = v6080 == 1;	// L9515
    int32_t v6082 = op8;	// L9516
    bool v6083 = v6082 == 9;	// L9517
    bool v6084 = v6081 & v6083;	// L9518
    if (v6084) {	// L9519
      condition_reg8 = 0;	// L9520
      half v6085 = a8;	// L9521
      half v6086 = b8;	// L9522
      bool v6087 = v6085 < v6086;	// L9523
      if (v6087) {	// L9524
        condition_reg8 = 1;	// L9525
      }
    }
    ap_uint<17> tx_n8;	// L9528
    tx_n8 = 0;	// L9529
    ap_uint<17> tx_s8;	// L9530
    tx_s8 = 0;	// L9531
    ap_uint<17> tx_w8;	// L9532
    tx_w8 = 0;	// L9533
    ap_uint<17> tx_e8;	// L9534
    tx_e8 = 0;	// L9535
    int32_t is_rtr8;	// L9536
    is_rtr8 = 0;	// L9537
    int32_t do_inj8;	// L9538
    do_inj8 = 0;	// L9539
    int32_t v6094 = op8;	// L9540
    bool v6095 = v6094 >= 4;	// L9541
    ap_int<33> v6096 = v6094;	// L9542
    bool v6097 = v6096 <= 7;	// L9543
    bool v6098 = v6095 & v6097;	// L9544
    if (v6098) {	// L9545
      is_rtr8 = 1;	// L9546
      do_inj8 = 1;	// L9547
    }
    int32_t v6099 = op8;	// L9549
    bool v6100 = v6099 >= 12;	// L9550
    ap_int<33> v6101 = v6099;	// L9551
    bool v6102 = v6101 <= 15;	// L9552
    bool v6103 = v6100 & v6102;	// L9553
    if (v6103) {	// L9554
      is_rtr8 = 1;	// L9555
      int32_t v6104 = condition_reg8;	// L9556
      bool v6105 = v6104 == 1;	// L9557
      if (v6105) {	// L9558
        do_inj8 = 1;	// L9559
      }
    }
    int32_t v6106 = is_rtr8;	// L9562
    bool v6107 = v6106 == 1;	// L9563
    if (v6107) {	// L9564
      int32_t v6108 = do_inj8;	// L9565
      bool v6109 = v6108 == 1;	// L9566
      ap_int<26> v6110 = csd_pkt8;	// L9567
      bool v6111;
      ap_int<26> v6111_tmp = v6110;
      v6111 = v6111_tmp[25];	// L9568
      int32_t v6112 = v6111;	// L9569
      bool v6113 = v6112 == 0;	// L9570
      bool v6114 = v6109 & v6113;	// L9571
      if (v6114) {	// L9572
        half v6115 = res8;	// L9573
        uint16_t v6116;
        union { half from; uint16_t to;} _converter_v6115_to_v6116;
        _converter_v6115_to_v6116.from = v6115;
        v6116 = _converter_v6115_to_v6116.to;	// L9574
        ap_int<26> v6117 = csd_pkt8;	// L9575
        ap_int<26> v6118;
        ap_int<26> v6118_tmp = v6117;
        v6118_tmp(15, 0) = v6116;
        v6118 = v6118_tmp;	// L9576
        csd_pkt8 = v6118;	// L9577
        int32_t v6119 = dst8;	// L9578
        ap_uint<4> v6120 = v6119;	// L9579
        ap_int<26> v6121 = csd_pkt8;	// L9580
        ap_int<26> v6122;
        ap_int<26> v6122_tmp = v6121;
        v6122_tmp(19, 16) = v6120;
        v6122 = v6122_tmp;	// L9581
        csd_pkt8 = v6122;	// L9582
        int32_t v6123 = s28;	// L9583
        ap_uint<4> v6124 = v6123;	// L9584
        ap_int<26> v6125 = csd_pkt8;	// L9585
        ap_int<26> v6126;
        ap_int<26> v6126_tmp = v6125;
        v6126_tmp(24, 21) = v6124;
        v6126 = v6126_tmp;	// L9586
        csd_pkt8 = v6126;	// L9587
        int32_t v6127 = res_vld8;	// L9588
        bool v6128 = v6127;	// L9589
        ap_int<26> v6129 = csd_pkt8;	// L9590
        ap_int<26> v6130;
        ap_int<26> v6130_tmp = v6129;
        v6130_tmp[25] = v6128;        v6130 = v6130_tmp;	// L9591
        csd_pkt8 = v6130;	// L9592
        int32_t v6131 = op8;	// L9593
        int32_t v6132 = v6131 & 3;	// L9594
        csd_dir8 = v6132;	// L9595
      }
    } else {
      int32_t v6133 = dst8;	// L9598
      bool v6134 = v6133 >= 12;	// L9599
      if (v6134) {	// L9600
        ap_uint<17> tw8;	// L9601
        tw8 = 0;	// L9602
        int32_t v6136 = res_vld8;	// L9603
        bool v6137 = v6136;	// L9604
        ap_int<17> v6138 = tw8;	// L9605
        ap_int<17> v6139;
        ap_int<17> v6139_tmp = v6138;
        v6139_tmp[0] = v6137;        v6139 = v6139_tmp;	// L9606
        tw8 = v6139;	// L9607
        half v6140 = res8;	// L9608
        uint16_t v6141;
        union { half from; uint16_t to;} _converter_v6140_to_v6141;
        _converter_v6140_to_v6141.from = v6140;
        v6141 = _converter_v6140_to_v6141.to;	// L9609
        ap_int<17> v6142 = tw8;	// L9610
        ap_int<17> v6143;
        ap_int<17> v6143_tmp = v6142;
        v6143_tmp(16, 1) = v6141;
        v6143 = v6143_tmp;	// L9611
        tw8 = v6143;	// L9612
        int32_t v6144 = dst8;	// L9613
        int32_t v6145 = v6144 & 3;	// L9614
        bool v6146 = v6145 == 0;	// L9615
        if (v6146) {	// L9616
          ap_int<17> v6147 = tw8;	// L9617
          tx_n8 = v6147;	// L9618
        } else {
          int32_t v6148 = dst8;	// L9620
          int32_t v6149 = v6148 & 3;	// L9621
          bool v6150 = v6149 == 1;	// L9622
          if (v6150) {	// L9623
            ap_int<17> v6151 = tw8;	// L9624
            tx_s8 = v6151;	// L9625
          } else {
            int32_t v6152 = dst8;	// L9627
            int32_t v6153 = v6152 & 3;	// L9628
            bool v6154 = v6153 == 2;	// L9629
            if (v6154) {	// L9630
              ap_int<17> v6155 = tw8;	// L9631
              tx_w8 = v6155;	// L9632
            } else {
              ap_int<17> v6156 = tw8;	// L9634
              tx_e8 = v6156;	// L9635
            }
          }
        }
      } else {
        int32_t v6157 = res_vld8;	// L9640
        bool v6158 = v6157 == 1;	// L9641
        if (v6158) {	// L9642
          int32_t v6159 = dst8;	// L9643
          bool v6160 = v6159 < 8;	// L9644
          int32_t v6161 = dsmask8;	// L9645
          int32_t v6162 = v6161 >> v6159;	// L9646
          int32_t v6163 = v6162 & 1;	// L9647
          bool v6164 = v6163 == 1;	// L9648
          bool v6165 = v6160 & v6164;	// L9649
          if (v6165) {	// L9650
            int32_t v6166 = dst8;	// L9651
            int v6167 = v6166;	// L9652
            int32_t v6168 = drf_full8[v6167];	// L9653
            bool v6169 = v6168 == 0;	// L9654
            if (v6169) {	// L9655
              half v6170 = res8;	// L9656
              int32_t v6171 = dst8;	// L9657
              int v6172 = v6171;	// L9658
              drf8[v6172] = v6170;	// L9659
              int32_t v6173 = dst8;	// L9660
              int v6174 = v6173;	// L9661
              drf_full8[v6174] = 1;	// L9662
            }
          } else {
            half v6175 = res8;	// L9665
            int32_t v6176 = dst8;	// L9666
            int v6177 = v6176;	// L9667
            drf8[v6177] = v6175;	// L9668
          }
        }
      }
    }
    ap_int<17> v6178 = tx_n8;	// L9673
    txn_r8 = v6178;	// L9674
    ap_int<17> v6179 = tx_s8;	// L9675
    txs_r8 = v6179;	// L9676
    ap_int<17> v6180 = tx_w8;	// L9677
    txw_r8 = v6180;	// L9678
    ap_int<17> v6181 = tx_e8;	// L9679
    txe_r8 = v6181;	// L9680
    int32_t v6182 = crv_vld8;	// L9681
    bool v6183 = v6182 == 1;	// L9682
    if (v6183) {	// L9683
      int32_t v6184 = crv_mode8;	// L9684
      bool v6185 = v6184 == 1;	// L9685
      if (v6185) {	// L9686
        int32_t v6186 = crv_addr8;	// L9687
        int32_t v6187 = v6186 >> 3;	// L9688
        int32_t v6188 = v6187 & 1;	// L9689
        bool v6189 = v6188 == 1;	// L9690
        if (v6189) {	// L9691
          int32_t v6190 = crv_raw8;	// L9692
          int32_t v6191 = crv_addr8;	// L9693
          int32_t v6192 = v6191 & 7;	// L9694
          int v6193 = v6192;	// L9695
          irf8[v6193] = v6190;	// L9696
        } else {
          int32_t v6194 = crv_addr8;	// L9698
          bool v6195 = v6194 == 0;	// L9699
          if (v6195) {	// L9700
            int32_t v6196 = crv_raw8;	// L9701
            int32_t v6197 = v6196 & 255;	// L9702
            dsmask8 = v6197;	// L9703
            int32_t v6198 = crv_raw8;	// L9704
            int32_t v6199 = v6198 >> 8;	// L9705
            int32_t v6200 = v6199 & 7;	// L9706
            cfg_isz8 = v6200;	// L9707
            int32_t v6201 = crv_raw8;	// L9708
            int32_t v6202 = v6201 >> 15;	// L9709
            int32_t v6203 = v6202 & 1;	// L9710
            bool v6204 = v6203 == 1;	// L9711
            if (v6204) {	// L9712
              fetch_en8 = 1;	// L9713
              instr_cnt8 = 0;	// L9714
              iter_cnt8 = 0;	// L9715
            }
          } else {
            int32_t v6205 = crv_addr8;	// L9718
            bool v6206 = v6205 == 1;	// L9719
            if (v6206) {	// L9720
              int32_t v6207 = crv_raw8;	// L9721
              int32_t v6208 = v6207 & 255;	// L9722
              cfg_itsz8 = v6208;	// L9723
            }
          }
        }
      } else {
        int32_t v6209 = crv_addr8;	// L9728
        bool v6210 = v6209 < 8;	// L9729
        int32_t v6211 = dsmask8;	// L9730
        int32_t v6212 = v6211 >> v6209;	// L9731
        int32_t v6213 = v6212 & 1;	// L9732
        bool v6214 = v6213 == 1;	// L9733
        bool v6215 = v6210 & v6214;	// L9734
        if (v6215) {	// L9735
          int32_t v6216 = crv_addr8;	// L9736
          int v6217 = v6216;	// L9737
          int32_t v6218 = drf_full8[v6217];	// L9738
          bool v6219 = v6218 == 0;	// L9739
          if (v6219) {	// L9740
            half v6220 = crv_data8;	// L9741
            int32_t v6221 = crv_addr8;	// L9742
            int v6222 = v6221;	// L9743
            drf8[v6222] = v6220;	// L9744
            int32_t v6223 = crv_addr8;	// L9745
            int v6224 = v6223;	// L9746
            drf_full8[v6224] = 1;	// L9747
          }
        } else {
          half v6225 = crv_data8;	// L9750
          int32_t v6226 = crv_addr8;	// L9751
          int v6227 = v6226;	// L9752
          drf8[v6227] = v6225;	// L9753
        }
      }
    }
  }
}

void node_2_1(
  hls::stream< ap_uint<26> >& v6228,
  hls::stream< ap_uint<26> >& v6229,
  hls::stream< ap_uint<26> >& v6230,
  hls::stream< ap_uint<26> >& v6231,
  hls::stream< ap_uint<17> >& v6232,
  hls::stream< ap_uint<17> >& v6233,
  hls::stream< ap_uint<17> >& v6234,
  hls::stream< ap_uint<17> >& v6235,
  hls::stream< int32_t >& v6236,
  hls::stream< int32_t >& v6237,
  hls::stream< int32_t >& v6238,
  hls::stream< int32_t >& v6239,
  hls::stream< ap_uint<26> >& v6240,
  hls::stream< ap_uint<26> >& v6241,
  hls::stream< ap_uint<26> >& v6242,
  hls::stream< ap_uint<26> >& v6243,
  hls::stream< int32_t >& v6244,
  hls::stream< int32_t >& v6245,
  hls::stream< int32_t >& v6246,
  hls::stream< int32_t >& v6247,
  hls::stream< ap_uint<17> >& v6248,
  hls::stream< ap_uint<17> >& v6249,
  hls::stream< ap_uint<17> >& v6250,
  hls::stream< ap_uint<17> >& v6251
) {	// L9760
  int32_t irf9[8];	// L9791
  for (int v6253 = 0; v6253 < 8; v6253++) {	// L9792
    irf9[v6253] = 0;	// L9792
  }
  half drf9[8];	// L9793
  #pragma HLS array_partition variable=drf9 complete dim=1

  for (int v6255 = 0; v6255 < 8; v6255++) {	// L9794
    drf9[v6255] = (double)0.000000;	// L9794
  }
  int32_t drf_full9[8];	// L9795
  #pragma HLS array_partition variable=drf_full9 complete dim=1

  for (int v6257 = 0; v6257 < 8; v6257++) {	// L9796
    drf_full9[v6257] = 0;	// L9796
  }
  int32_t dsmask9;	// L9797
  dsmask9 = 0;	// L9798
  int32_t crv_vld9;	// L9799
  crv_vld9 = 0;	// L9800
  half crv_data9;	// L9801
  crv_data9 = (double)0.000000;	// L9802
  int32_t crv_addr9;	// L9803
  crv_addr9 = 0;	// L9804
  int32_t crv_mode9;	// L9805
  crv_mode9 = 0;	// L9806
  int32_t crv_raw9;	// L9807
  crv_raw9 = 0;	// L9808
  int32_t csd_vld9;	// L9809
  csd_vld9 = 0;	// L9810
  ap_uint<26> csd_pkt9;	// L9811
  csd_pkt9 = 0;	// L9812
  int32_t csd_dir9;	// L9813
  csd_dir9 = 0;	// L9814
  int32_t row_id9;	// L9815
  row_id9 = 2;	// L9816
  int32_t col_id9;	// L9817
  col_id9 = 1;	// L9818
  ap_uint<26> oe_r9;	// L9819
  oe_r9 = 0;	// L9820
  ap_uint<26> ow_r9;	// L9821
  ow_r9 = 0;	// L9822
  ap_uint<26> on_r9;	// L9823
  on_r9 = 0;	// L9824
  ap_uint<26> os_r9;	// L9825
  os_r9 = 0;	// L9826
  ap_uint<17> txn_r9;	// L9827
  txn_r9 = 0;	// L9828
  ap_uint<17> txs_r9;	// L9829
  txs_r9 = 0;	// L9830
  ap_uint<17> txw_r9;	// L9831
  txw_r9 = 0;	// L9832
  ap_uint<17> txe_r9;	// L9833
  txe_r9 = 0;	// L9834
  half hold_v9[4][2];	// L9835
  #pragma HLS array_partition variable=hold_v9 complete dim=1
  #pragma HLS array_partition variable=hold_v9 complete dim=2

  for (int v6278 = 0; v6278 < 4; v6278++) {	// L9836
    for (int v6279 = 0; v6279 < 2; v6279++) {	// L9836
      hold_v9[v6278][v6279] = (double)0.000000;	// L9836
    }
  }
  int32_t hold_cnt9[4];	// L9837
  #pragma HLS array_partition variable=hold_cnt9 complete dim=1

  for (int v6281 = 0; v6281 < 4; v6281++) {	// L9838
    hold_cnt9[v6281] = 0;	// L9838
  }
  ap_uint<26> rbuf9[4][2];	// L9839
  #pragma HLS array_partition variable=rbuf9 complete dim=1
  #pragma HLS array_partition variable=rbuf9 complete dim=2

  for (int v6283 = 0; v6283 < 4; v6283++) {	// L9840
    for (int v6284 = 0; v6284 < 2; v6284++) {	// L9840
      rbuf9[v6283][v6284] = 0;	// L9840
    }
  }
  int32_t rbcnt9[4];	// L9841
  #pragma HLS array_partition variable=rbcnt9 complete dim=1

  for (int v6286 = 0; v6286 < 4; v6286++) {	// L9842
    rbcnt9[v6286] = 0;	// L9842
  }
  int32_t rcred9[4];	// L9843
  #pragma HLS array_partition variable=rcred9 complete dim=1

  for (int v6288 = 0; v6288 < 4; v6288++) {	// L9844
    rcred9[v6288] = 0;	// L9844
  }
  int32_t cre_r9;	// L9845
  cre_r9 = 2;	// L9846
  int32_t crw_r9;	// L9847
  crw_r9 = 2;	// L9848
  int32_t crs_r9;	// L9849
  crs_r9 = 2;	// L9850
  int32_t crn_r9;	// L9851
  crn_r9 = 2;	// L9852
  int32_t cfg_isz9;	// L9853
  cfg_isz9 = 0;	// L9854
  int32_t cfg_itsz9;	// L9855
  cfg_itsz9 = 0;	// L9856
  int32_t fetch_en9;	// L9857
  fetch_en9 = 0;	// L9858
  int32_t instr_cnt9;	// L9859
  instr_cnt9 = 0;	// L9860
  int32_t iter_cnt9;	// L9861
  iter_cnt9 = 0;	// L9862
  int32_t condition_reg9;	// L9863
  condition_reg9 = 0;	// L9864
  l_S_t_0_t9: for (int t9 = 0; t9 < 8; t9++) {	// L9865
  #pragma HLS pipeline II=1
    ap_int<26> v6300 = oe_r9;	// L9866
    v6228.write(v6300);	// L9867
    ap_int<26> v6301 = ow_r9;	// L9868
    v6229.write(v6301);	// L9869
    ap_int<26> v6302 = os_r9;	// L9870
    v6230.write(v6302);	// L9871
    ap_int<26> v6303 = on_r9;	// L9872
    v6231.write(v6303);	// L9873
    ap_int<17> v6304 = txe_r9;	// L9874
    v6232.write(v6304);	// L9875
    ap_int<17> v6305 = txw_r9;	// L9876
    v6233.write(v6305);	// L9877
    ap_int<17> v6306 = txs_r9;	// L9878
    v6234.write(v6306);	// L9879
    ap_int<17> v6307 = txn_r9;	// L9880
    v6235.write(v6307);	// L9881
    int32_t v6308 = cre_r9;	// L9882
    v6236.write(v6308);	// L9883
    int32_t v6309 = crw_r9;	// L9884
    v6237.write(v6309);	// L9885
    int32_t v6310 = crs_r9;	// L9886
    v6238.write(v6310);	// L9887
    int32_t v6311 = crn_r9;	// L9888
    v6239.write(v6311);	// L9889
    ap_uint<26> v6312 = v6240.read();	// L9890
    ap_uint<26> p_w9;	// L9891
    p_w9 = v6312;	// L9892
    ap_uint<26> v6314 = v6241.read();	// L9893
    ap_uint<26> p_e9;	// L9894
    p_e9 = v6314;	// L9895
    ap_uint<26> v6316 = v6242.read();	// L9896
    ap_uint<26> p_n9;	// L9897
    p_n9 = v6316;	// L9898
    ap_uint<26> v6318 = v6243.read();	// L9899
    ap_uint<26> p_s9;	// L9900
    p_s9 = v6318;	// L9901
    int32_t v6320 = v6244.read();	// L9902
    int32_t v6321 = rcred9[0];	// L9903
    ap_int<33> v6322 = v6321;	// L9904
    ap_int<33> v6323 = v6320;	// L9905
    ap_int<33> v6324 = v6322 + v6323;	// L9906
    int32_t v6325 = v6324;	// L9907
    rcred9[0] = v6325;	// L9908
    int32_t v6326 = v6245.read();	// L9909
    int32_t v6327 = rcred9[1];	// L9910
    ap_int<33> v6328 = v6327;	// L9911
    ap_int<33> v6329 = v6326;	// L9912
    ap_int<33> v6330 = v6328 + v6329;	// L9913
    int32_t v6331 = v6330;	// L9914
    rcred9[1] = v6331;	// L9915
    int32_t v6332 = v6246.read();	// L9916
    int32_t v6333 = rcred9[2];	// L9917
    ap_int<33> v6334 = v6333;	// L9918
    ap_int<33> v6335 = v6332;	// L9919
    ap_int<33> v6336 = v6334 + v6335;	// L9920
    int32_t v6337 = v6336;	// L9921
    rcred9[2] = v6337;	// L9922
    int32_t v6338 = v6247.read();	// L9923
    int32_t v6339 = rcred9[3];	// L9924
    ap_int<33> v6340 = v6339;	// L9925
    ap_int<33> v6341 = v6338;	// L9926
    ap_int<33> v6342 = v6340 + v6341;	// L9927
    int32_t v6343 = v6342;	// L9928
    rcred9[3] = v6343;	// L9929
    ap_uint<26> fin9[4];	// L9930
    for (int v6345 = 0; v6345 < 4; v6345++) {	// L9931
      fin9[v6345] = 0;	// L9931
    }
    ap_int<26> v6346 = p_w9;	// L9932
    fin9[0] = v6346;	// L9933
    ap_int<26> v6347 = p_e9;	// L9934
    fin9[1] = v6347;	// L9935
    ap_int<26> v6348 = p_n9;	// L9936
    fin9[2] = v6348;	// L9937
    ap_int<26> v6349 = p_s9;	// L9938
    fin9[3] = v6349;	// L9939
    l_S_d_0_d36: for (int d36 = 0; d36 < 4; d36++) {	// L9940
      ap_uint<26> v6351 = fin9[d36];	// L9941
      bool v6352;
      ap_int<26> v6352_tmp = v6351;
      v6352 = v6352_tmp[25];	// L9942
      int32_t v6353 = v6352;	// L9943
      bool v6354 = v6353 == 1;	// L9944
      int32_t v6355 = rbcnt9[d36];	// L9945
      bool v6356 = v6355 < 2;	// L9946
      bool v6357 = v6354 & v6356;	// L9947
      if (v6357) {	// L9948
        ap_uint<26> v6358 = fin9[d36];	// L9949
        int32_t v6359 = rbcnt9[d36];	// L9950
        int v6360 = v6359;	// L9951
        rbuf9[d36][v6360] = v6358;	// L9952
        int32_t v6361 = rbcnt9[d36];	// L9953
        ap_int<33> v6362 = v6361;	// L9954
        ap_int<33> v6363 = v6362 + 1;	// L9955
        int32_t v6364 = v6363;	// L9956
        rbcnt9[d36] = v6364;	// L9957
      }
    }
    ap_uint<26> hd9[4];	// L9960
    for (int v6366 = 0; v6366 < 4; v6366++) {	// L9961
      hd9[v6366] = 0;	// L9961
    }
    int32_t hvld9[4];	// L9962
    for (int v6368 = 0; v6368 < 4; v6368++) {	// L9963
      hvld9[v6368] = 0;	// L9963
    }
    int32_t hit9[4];	// L9964
    for (int v6370 = 0; v6370 < 4; v6370++) {	// L9965
      hit9[v6370] = 0;	// L9965
    }
    int32_t axis9[4];	// L9966
    for (int v6372 = 0; v6372 < 4; v6372++) {	// L9967
      axis9[v6372] = 0;	// L9967
    }
    int32_t v6373 = col_id9;	// L9968
    axis9[0] = v6373;	// L9969
    int32_t v6374 = col_id9;	// L9970
    axis9[1] = v6374;	// L9971
    int32_t v6375 = row_id9;	// L9972
    axis9[2] = v6375;	// L9973
    int32_t v6376 = row_id9;	// L9974
    axis9[3] = v6376;	// L9975
    l_S_d_1_d37: for (int d37 = 0; d37 < 4; d37++) {	// L9976
      int32_t v6378 = rbcnt9[d37];	// L9977
      bool v6379 = v6378 > 0;	// L9978
      if (v6379) {	// L9979
        ap_uint<26> v6380 = rbuf9[d37][0];	// L9980
        hd9[d37] = v6380;	// L9981
        hvld9[d37] = 1;	// L9982
        ap_uint<26> v6381 = hd9[d37];	// L9983
        ap_int<4> v6382;
        ap_int<26> v6382_tmp = v6381;
        v6382 = v6382_tmp(24, 21);	// L9984
        int32_t v6383 = axis9[d37];	// L9985
        int32_t v6384 = v6382;	// L9986
        bool v6385 = v6384 == v6383;	// L9987
        if (v6385) {	// L9988
          hit9[d37] = 1;	// L9989
        }
      }
    }
    ap_uint<26> o_crv9;	// L9993
    o_crv9 = 0;	// L9994
    int32_t crv_in9;	// L9995
    crv_in9 = -1;	// L9996
    int32_t v6388 = hit9[3];	// L9997
    bool v6389 = v6388 == 1;	// L9998
    if (v6389) {	// L9999
      ap_uint<26> v6390 = hd9[3];	// L10000
      o_crv9 = v6390;	// L10001
      crv_in9 = 3;	// L10002
    } else {
      int32_t v6391 = hit9[2];	// L10004
      bool v6392 = v6391 == 1;	// L10005
      if (v6392) {	// L10006
        ap_uint<26> v6393 = hd9[2];	// L10007
        o_crv9 = v6393;	// L10008
        crv_in9 = 2;	// L10009
      } else {
        int32_t v6394 = hit9[1];	// L10011
        bool v6395 = v6394 == 1;	// L10012
        if (v6395) {	// L10013
          ap_uint<26> v6396 = hd9[1];	// L10014
          o_crv9 = v6396;	// L10015
          crv_in9 = 1;	// L10016
        } else {
          int32_t v6397 = hit9[0];	// L10018
          bool v6398 = v6397 == 1;	// L10019
          if (v6398) {	// L10020
            ap_uint<26> v6399 = hd9[0];	// L10021
            o_crv9 = v6399;	// L10022
            crv_in9 = 0;	// L10023
          }
        }
      }
    }
    ap_uint<26> o_out9[4];	// L10028
    for (int v6401 = 0; v6401 < 4; v6401++) {	// L10029
      o_out9[v6401] = 0;	// L10029
    }
    int32_t pop9[4];	// L10030
    for (int v6403 = 0; v6403 < 4; v6403++) {	// L10031
      pop9[v6403] = 0;	// L10031
    }
    int32_t inj_done9;	// L10032
    inj_done9 = 0;	// L10033
    int32_t idir9;	// L10034
    idir9 = -1;	// L10035
    ap_int<26> v6406 = csd_pkt9;	// L10036
    bool v6407;
    ap_int<26> v6407_tmp = v6406;
    v6407 = v6407_tmp[25];	// L10037
    int32_t v6408 = v6407;	// L10038
    bool v6409 = v6408 == 1;	// L10039
    if (v6409) {	// L10040
      int32_t v6410 = csd_dir9;	// L10041
      ap_int<33> v6411 = v6410;	// L10042
      ap_int<33> v6412 = 3 - v6411;	// L10043
      int32_t v6413 = v6412;	// L10044
      idir9 = v6413;	// L10045
    }
    l_S_o_2_o9: for (int o9 = 0; o9 < 4; o9++) {	// L10047
      int32_t v6415 = rcred9[o9];	// L10048
      bool v6416 = v6415 > 0;	// L10049
      if (v6416) {	// L10050
        int32_t v6417 = idir9;	// L10051
        ap_int<33> v6418 = v6417;	// L10052
        ap_int<33> v6419 = o9;	// L10053
        bool v6420 = v6418 == v6419;	// L10054
        if (v6420) {	// L10055
          ap_int<26> v6421 = csd_pkt9;	// L10056
          o_out9[o9] = v6421;	// L10057
          int32_t v6422 = rcred9[o9];	// L10058
          ap_int<33> v6423 = v6422;	// L10059
          ap_int<33> v6424 = v6423 - 1;	// L10060
          int32_t v6425 = v6424;	// L10061
          rcred9[o9] = v6425;	// L10062
          inj_done9 = 1;	// L10063
        } else {
          int32_t v6426 = hvld9[o9];	// L10065
          bool v6427 = v6426 == 1;	// L10066
          int32_t v6428 = hit9[o9];	// L10067
          bool v6429 = v6428 == 0;	// L10068
          bool v6430 = v6427 & v6429;	// L10069
          if (v6430) {	// L10070
            ap_uint<26> v6431 = hd9[o9];	// L10071
            o_out9[o9] = v6431;	// L10072
            int32_t v6432 = rcred9[o9];	// L10073
            ap_int<33> v6433 = v6432;	// L10074
            ap_int<33> v6434 = v6433 - 1;	// L10075
            int32_t v6435 = v6434;	// L10076
            rcred9[o9] = v6435;	// L10077
            pop9[o9] = 1;	// L10078
          }
        }
      }
    }
    int32_t v6436 = crv_in9;	// L10083
    bool v6437 = v6436 >= 0;	// L10084
    if (v6437) {	// L10085
      int32_t v6438 = crv_in9;	// L10086
      int v6439 = v6438;	// L10087
      pop9[v6439] = 1;	// L10088
    }
    int32_t ret9[4];	// L10090
    for (int v6441 = 0; v6441 < 4; v6441++) {	// L10091
      ret9[v6441] = 0;	// L10091
    }
    l_S_d_3_d38: for (int d38 = 0; d38 < 4; d38++) {	// L10092
      int32_t v6443 = pop9[d38];	// L10093
      bool v6444 = v6443 == 1;	// L10094
      if (v6444) {	// L10095
        l_S_sft_3_sft9: for (int sft9 = 0; sft9 < 1; sft9++) {	// L10096
          ap_uint<26> v6446 = rbuf9[d38][(sft9 + 1)];	// L10097
          rbuf9[d38][sft9] = v6446;	// L10098
        }
        int32_t v6447 = rbcnt9[d38];	// L10100
        ap_int<33> v6448 = v6447;	// L10101
        ap_int<33> v6449 = v6448 - 1;	// L10102
        int32_t v6450 = v6449;	// L10103
        rbcnt9[d38] = v6450;	// L10104
        ret9[d38] = 1;	// L10105
      }
    }
    int32_t v6451 = ret9[0];	// L10108
    cre_r9 = v6451;	// L10109
    int32_t v6452 = ret9[1];	// L10110
    crw_r9 = v6452;	// L10111
    int32_t v6453 = ret9[2];	// L10112
    crs_r9 = v6453;	// L10113
    int32_t v6454 = ret9[3];	// L10114
    crn_r9 = v6454;	// L10115
    ap_uint<26> v6455 = o_out9[0];	// L10116
    oe_r9 = v6455;	// L10117
    ap_uint<26> v6456 = o_out9[1];	// L10118
    ow_r9 = v6456;	// L10119
    ap_uint<26> v6457 = o_out9[2];	// L10120
    os_r9 = v6457;	// L10121
    ap_uint<26> v6458 = o_out9[3];	// L10122
    on_r9 = v6458;	// L10123
    int32_t v6459 = inj_done9;	// L10124
    bool v6460 = v6459 == 1;	// L10125
    if (v6460) {	// L10126
      csd_pkt9 = 0;	// L10127
    }
    ap_int<26> v6461 = o_crv9;	// L10129
    bool v6462;
    ap_int<26> v6462_tmp = v6461;
    v6462 = v6462_tmp[25];	// L10130
    int32_t v6463 = v6462;	// L10131
    crv_vld9 = v6463;	// L10132
    ap_int<26> v6464 = o_crv9;	// L10133
    int16_t v6465;
    ap_int<26> v6465_tmp = v6464;
    v6465 = v6465_tmp(15, 0);	// L10134
    half v6466;
    union { uint16_t from; half to;} _converter_v6465_to_v6466;
    _converter_v6465_to_v6466.from = v6465;
    v6466 = _converter_v6465_to_v6466.to;	// L10135
    crv_data9 = v6466;	// L10136
    ap_int<26> v6467 = o_crv9;	// L10137
    ap_int<4> v6468;
    ap_int<26> v6468_tmp = v6467;
    v6468 = v6468_tmp(19, 16);	// L10138
    int32_t v6469 = v6468;	// L10139
    crv_addr9 = v6469;	// L10140
    ap_int<26> v6470 = o_crv9;	// L10141
    bool v6471;
    ap_int<26> v6471_tmp = v6470;
    v6471 = v6471_tmp[20];	// L10142
    int32_t v6472 = v6471;	// L10143
    crv_mode9 = v6472;	// L10144
    ap_int<26> v6473 = o_crv9;	// L10145
    int16_t v6474;
    ap_int<26> v6474_tmp = v6473;
    v6474 = v6474_tmp(15, 0);	// L10146
    int32_t v6475 = v6474;	// L10147
    crv_raw9 = v6475;	// L10148
    ap_uint<17> v6476 = v6248.read();	// L10149
    ap_uint<17> rx_w9;	// L10150
    rx_w9 = v6476;	// L10151
    ap_uint<17> v6478 = v6249.read();	// L10152
    ap_uint<17> rx_e9;	// L10153
    rx_e9 = v6478;	// L10154
    ap_uint<17> v6480 = v6250.read();	// L10155
    ap_uint<17> rx_n9;	// L10156
    rx_n9 = v6480;	// L10157
    ap_uint<17> v6482 = v6251.read();	// L10158
    ap_uint<17> rx_s9;	// L10159
    rx_s9 = v6482;	// L10160
    half rxv9[4];	// L10161
    for (int v6485 = 0; v6485 < 4; v6485++) {	// L10162
      rxv9[v6485] = (double)0.000000;	// L10162
    }
    int32_t rxvld9[4];	// L10163
    for (int v6487 = 0; v6487 < 4; v6487++) {	// L10164
      rxvld9[v6487] = 0;	// L10164
    }
    ap_int<17> v6488 = rx_n9;	// L10165
    int16_t v6489;
    ap_int<17> v6489_tmp = v6488;
    v6489 = v6489_tmp(16, 1);	// L10166
    half v6490;
    union { uint16_t from; half to;} _converter_v6489_to_v6490;
    _converter_v6489_to_v6490.from = v6489;
    v6490 = _converter_v6489_to_v6490.to;	// L10167
    rxv9[0] = v6490;	// L10168
    ap_int<17> v6491 = rx_n9;	// L10169
    bool v6492;
    ap_int<17> v6492_tmp = v6491;
    v6492 = v6492_tmp[0];	// L10170
    int32_t v6493 = v6492;	// L10171
    rxvld9[0] = v6493;	// L10172
    ap_int<17> v6494 = rx_s9;	// L10173
    int16_t v6495;
    ap_int<17> v6495_tmp = v6494;
    v6495 = v6495_tmp(16, 1);	// L10174
    half v6496;
    union { uint16_t from; half to;} _converter_v6495_to_v6496;
    _converter_v6495_to_v6496.from = v6495;
    v6496 = _converter_v6495_to_v6496.to;	// L10175
    rxv9[1] = v6496;	// L10176
    ap_int<17> v6497 = rx_s9;	// L10177
    bool v6498;
    ap_int<17> v6498_tmp = v6497;
    v6498 = v6498_tmp[0];	// L10178
    int32_t v6499 = v6498;	// L10179
    rxvld9[1] = v6499;	// L10180
    ap_int<17> v6500 = rx_w9;	// L10181
    int16_t v6501;
    ap_int<17> v6501_tmp = v6500;
    v6501 = v6501_tmp(16, 1);	// L10182
    half v6502;
    union { uint16_t from; half to;} _converter_v6501_to_v6502;
    _converter_v6501_to_v6502.from = v6501;
    v6502 = _converter_v6501_to_v6502.to;	// L10183
    rxv9[2] = v6502;	// L10184
    ap_int<17> v6503 = rx_w9;	// L10185
    bool v6504;
    ap_int<17> v6504_tmp = v6503;
    v6504 = v6504_tmp[0];	// L10186
    int32_t v6505 = v6504;	// L10187
    rxvld9[2] = v6505;	// L10188
    ap_int<17> v6506 = rx_e9;	// L10189
    int16_t v6507;
    ap_int<17> v6507_tmp = v6506;
    v6507 = v6507_tmp(16, 1);	// L10190
    half v6508;
    union { uint16_t from; half to;} _converter_v6507_to_v6508;
    _converter_v6507_to_v6508.from = v6507;
    v6508 = _converter_v6507_to_v6508.to;	// L10191
    rxv9[3] = v6508;	// L10192
    ap_int<17> v6509 = rx_e9;	// L10193
    bool v6510;
    ap_int<17> v6510_tmp = v6509;
    v6510 = v6510_tmp[0];	// L10194
    int32_t v6511 = v6510;	// L10195
    rxvld9[3] = v6511;	// L10196
    l_S_d_5_d39: for (int d39 = 0; d39 < 4; d39++) {	// L10197
      int32_t v6513 = rxvld9[d39];	// L10198
      bool v6514 = v6513 == 1;	// L10199
      int32_t v6515 = hold_cnt9[d39];	// L10200
      bool v6516 = v6515 < 2;	// L10201
      bool v6517 = v6514 & v6516;	// L10202
      if (v6517) {	// L10203
        half v6518 = rxv9[d39];	// L10204
        int32_t v6519 = hold_cnt9[d39];	// L10205
        int v6520 = v6519;	// L10206
        hold_v9[d39][v6520] = v6518;	// L10207
        int32_t v6521 = hold_cnt9[d39];	// L10208
        ap_int<33> v6522 = v6521;	// L10209
        ap_int<33> v6523 = v6522 + 1;	// L10210
        int32_t v6524 = v6523;	// L10211
        hold_cnt9[d39] = v6524;	// L10212
      }
    }
    int32_t pc9;	// L10215
    pc9 = -1;	// L10216
    int32_t v6526 = fetch_en9;	// L10217
    bool v6527 = v6526 == 1;	// L10218
    if (v6527) {	// L10219
      int32_t v6528 = instr_cnt9;	// L10220
      pc9 = v6528;	// L10221
    }
    int32_t instr9;	// L10223
    instr9 = 0;	// L10224
    int32_t v6530 = pc9;	// L10225
    bool v6531 = v6530 >= 0;	// L10226
    if (v6531) {	// L10227
      int32_t v6532 = pc9;	// L10228
      int v6533 = v6532;	// L10229
      int32_t v6534 = irf9[v6533];	// L10230
      instr9 = v6534;	// L10231
    }
    int32_t v6535 = instr9;	// L10233
    int32_t v6536 = v6535 & 15;	// L10234
    int32_t op9;	// L10235
    op9 = v6536;	// L10236
    int32_t v6538 = instr9;	// L10237
    int32_t v6539 = v6538 >> 4;	// L10238
    int32_t v6540 = v6539 & 15;	// L10239
    int32_t dst9;	// L10240
    dst9 = v6540;	// L10241
    int32_t v6542 = instr9;	// L10242
    int32_t v6543 = v6542 >> 8;	// L10243
    int32_t v6544 = v6543 & 15;	// L10244
    int32_t s19;	// L10245
    s19 = v6544;	// L10246
    int32_t v6546 = instr9;	// L10247
    int32_t v6547 = v6546 >> 12;	// L10248
    int32_t v6548 = v6547 & 15;	// L10249
    int32_t s29;	// L10250
    s29 = v6548;	// L10251
    half a9;	// L10252
    a9 = (double)0.000000;	// L10253
    half b9;	// L10254
    b9 = (double)0.000000;	// L10255
    int32_t v6552 = s19;	// L10256
    bool v6553 = v6552 >= 12;	// L10257
    if (v6553) {	// L10258
      int32_t v6554 = s19;	// L10259
      int32_t v6555 = v6554 & 3;	// L10260
      int v6556 = v6555;	// L10261
      half v6557 = hold_v9[v6556][0];	// L10262
      a9 = v6557;	// L10263
    } else {
      int32_t v6558 = s19;	// L10265
      int v6559 = v6558;	// L10266
      half v6560 = drf9[v6559];	// L10267
      a9 = v6560;	// L10268
    }
    int32_t v6561 = s29;	// L10270
    bool v6562 = v6561 >= 12;	// L10271
    if (v6562) {	// L10272
      int32_t v6563 = s29;	// L10273
      int32_t v6564 = v6563 & 3;	// L10274
      int v6565 = v6564;	// L10275
      half v6566 = hold_v9[v6565][0];	// L10276
      b9 = v6566;	// L10277
    } else {
      int32_t v6567 = s29;	// L10279
      int v6568 = v6567;	// L10280
      half v6569 = drf9[v6568];	// L10281
      b9 = v6569;	// L10282
    }
    int32_t a_vld9;	// L10284
    a_vld9 = 1;	// L10285
    int32_t b_vld9;	// L10286
    b_vld9 = 1;	// L10287
    int32_t v6572 = s19;	// L10288
    bool v6573 = v6572 >= 12;	// L10289
    if (v6573) {	// L10290
      a_vld9 = 0;	// L10291
      int32_t v6574 = s19;	// L10292
      int32_t v6575 = v6574 & 3;	// L10293
      int v6576 = v6575;	// L10294
      int32_t v6577 = hold_cnt9[v6576];	// L10295
      bool v6578 = v6577 > 0;	// L10296
      if (v6578) {	// L10297
        a_vld9 = 1;	// L10298
      }
    }
    int32_t v6579 = s29;	// L10301
    bool v6580 = v6579 >= 12;	// L10302
    if (v6580) {	// L10303
      b_vld9 = 0;	// L10304
      int32_t v6581 = s29;	// L10305
      int32_t v6582 = v6581 & 3;	// L10306
      int v6583 = v6582;	// L10307
      int32_t v6584 = hold_cnt9[v6583];	// L10308
      bool v6585 = v6584 > 0;	// L10309
      if (v6585) {	// L10310
        b_vld9 = 1;	// L10311
      }
    }
    int32_t v6586 = s19;	// L10314
    bool v6587 = v6586 < 8;	// L10315
    int32_t v6588 = dsmask9;	// L10316
    int32_t v6589 = v6588 >> v6586;	// L10317
    int32_t v6590 = v6589 & 1;	// L10318
    bool v6591 = v6590 == 1;	// L10319
    bool v6592 = v6587 & v6591;	// L10320
    if (v6592) {	// L10321
      int32_t v6593 = s19;	// L10322
      int v6594 = v6593;	// L10323
      int32_t v6595 = drf_full9[v6594];	// L10324
      bool v6596 = v6595 == 0;	// L10325
      if (v6596) {	// L10326
        a_vld9 = 0;	// L10327
      }
    }
    int32_t v6597 = s29;	// L10330
    bool v6598 = v6597 < 8;	// L10331
    int32_t v6599 = dsmask9;	// L10332
    int32_t v6600 = v6599 >> v6597;	// L10333
    int32_t v6601 = v6600 & 1;	// L10334
    bool v6602 = v6601 == 1;	// L10335
    bool v6603 = v6598 & v6602;	// L10336
    if (v6603) {	// L10337
      int32_t v6604 = s29;	// L10338
      int v6605 = v6604;	// L10339
      int32_t v6606 = drf_full9[v6605];	// L10340
      bool v6607 = v6606 == 0;	// L10341
      if (v6607) {	// L10342
        b_vld9 = 0;	// L10343
      }
    }
    int32_t binop9;	// L10346
    binop9 = 0;	// L10347
    int32_t v6609 = op9;	// L10348
    bool v6610 = v6609 == 0;	// L10349
    bool v6611 = v6609 == 1;	// L10350
    bool v6612 = v6609 == 2;	// L10351
    bool v6613 = v6609 == 8;	// L10352
    bool v6614 = v6609 == 9;	// L10353
    bool v6615 = v6610 | v6611;	// L10354
    bool v6616 = v6615 | v6612;	// L10355
    bool v6617 = v6616 | v6613;	// L10356
    bool v6618 = v6617 | v6614;	// L10357
    if (v6618) {	// L10358
      binop9 = 1;	// L10359
    }
    int32_t grant9;	// L10361
    grant9 = 0;	// L10362
    int32_t v6620 = pc9;	// L10363
    bool v6621 = v6620 >= 0;	// L10364
    if (v6621) {	// L10365
      grant9 = 1;	// L10366
    }
    int32_t v6622 = pc9;	// L10368
    bool v6623 = v6622 >= 0;	// L10369
    int32_t v6624 = a_vld9;	// L10370
    bool v6625 = v6624 == 0;	// L10371
    int32_t v6626 = binop9;	// L10372
    bool v6627 = v6626 == 1;	// L10373
    int32_t v6628 = b_vld9;	// L10374
    bool v6629 = v6628 == 0;	// L10375
    bool v6630 = v6627 & v6629;	// L10376
    bool v6631 = v6625 | v6630;	// L10377
    bool v6632 = v6623 & v6631;	// L10378
    if (v6632) {	// L10379
      grant9 = 0;	// L10380
    }
    int32_t v6633 = grant9;	// L10382
    bool v6634 = v6633 == 1;	// L10383
    if (v6634) {	// L10384
      int32_t v6635 = instr_cnt9;	// L10385
      int32_t v6636 = cfg_isz9;	// L10386
      bool v6637 = v6635 == v6636;	// L10387
      if (v6637) {	// L10388
        instr_cnt9 = 0;	// L10389
        int32_t v6638 = iter_cnt9;	// L10390
        int32_t v6639 = cfg_itsz9;	// L10391
        ap_int<33> v6640 = v6639;	// L10392
        ap_int<33> v6641 = v6640 - 1;	// L10393
        ap_int<33> v6642 = v6638;	// L10394
        bool v6643 = v6642 == v6641;	// L10395
        if (v6643) {	// L10396
          fetch_en9 = 0;	// L10397
        } else {
          int32_t v6644 = iter_cnt9;	// L10399
          ap_int<33> v6645 = v6644;	// L10400
          ap_int<33> v6646 = v6645 + 1;	// L10401
          int32_t v6647 = v6646;	// L10402
          iter_cnt9 = v6647;	// L10403
        }
      } else {
        int32_t v6648 = instr_cnt9;	// L10406
        ap_int<33> v6649 = v6648;	// L10407
        ap_int<33> v6650 = v6649 + 1;	// L10408
        int32_t v6651 = v6650;	// L10409
        instr_cnt9 = v6651;	// L10410
      }
    }
    int32_t c19;	// L10413
    c19 = -1;	// L10414
    int32_t c29;	// L10415
    c29 = -1;	// L10416
    int32_t v6654 = grant9;	// L10417
    bool v6655 = v6654 == 1;	// L10418
    int32_t v6656 = s19;	// L10419
    bool v6657 = v6656 >= 12;	// L10420
    bool v6658 = v6655 & v6657;	// L10421
    if (v6658) {	// L10422
      int32_t v6659 = s19;	// L10423
      int32_t v6660 = v6659 & 3;	// L10424
      c19 = v6660;	// L10425
    }
    int32_t v6661 = grant9;	// L10427
    bool v6662 = v6661 == 1;	// L10428
    int32_t v6663 = s29;	// L10429
    bool v6664 = v6663 >= 12;	// L10430
    bool v6665 = v6662 & v6664;	// L10431
    if (v6665) {	// L10432
      int32_t v6666 = s29;	// L10433
      int32_t v6667 = v6666 & 3;	// L10434
      c29 = v6667;	// L10435
    }
    int32_t v6668 = c19;	// L10437
    bool v6669 = v6668 >= 0;	// L10438
    if (v6669) {	// L10439
      int32_t v6670 = c19;	// L10440
      int v6671 = v6670;	// L10441
      half v6672 = hold_v9[v6671][1];	// L10442
      hold_v9[v6671][0] = v6672;	// L10443
      int32_t v6673 = c19;	// L10444
      int v6674 = v6673;	// L10445
      int32_t v6675 = hold_cnt9[v6674];	// L10446
      ap_int<33> v6676 = v6675;	// L10447
      ap_int<33> v6677 = v6676 - 1;	// L10448
      int32_t v6678 = v6677;	// L10449
      hold_cnt9[v6674] = v6678;	// L10450
    }
    int32_t v6679 = c29;	// L10452
    bool v6680 = v6679 >= 0;	// L10453
    int32_t v6681 = c19;	// L10454
    bool v6682 = v6679 != v6681;	// L10455
    bool v6683 = v6680 & v6682;	// L10456
    if (v6683) {	// L10457
      int32_t v6684 = c29;	// L10458
      int v6685 = v6684;	// L10459
      half v6686 = hold_v9[v6685][1];	// L10460
      hold_v9[v6685][0] = v6686;	// L10461
      int32_t v6687 = c29;	// L10462
      int v6688 = v6687;	// L10463
      int32_t v6689 = hold_cnt9[v6688];	// L10464
      ap_int<33> v6690 = v6689;	// L10465
      ap_int<33> v6691 = v6690 - 1;	// L10466
      int32_t v6692 = v6691;	// L10467
      hold_cnt9[v6688] = v6692;	// L10468
    }
    int32_t v6693 = grant9;	// L10470
    bool v6694 = v6693 == 1;	// L10471
    int32_t v6695 = s19;	// L10472
    bool v6696 = v6695 < 8;	// L10473
    int32_t v6697 = dsmask9;	// L10474
    int32_t v6698 = v6697 >> v6695;	// L10475
    int32_t v6699 = v6698 & 1;	// L10476
    bool v6700 = v6699 == 1;	// L10477
    bool v6701 = v6694 & v6696;	// L10478
    bool v6702 = v6701 & v6700;	// L10479
    if (v6702) {	// L10480
      int32_t v6703 = s19;	// L10481
      int v6704 = v6703;	// L10482
      drf_full9[v6704] = 0;	// L10483
    }
    int32_t v6705 = grant9;	// L10485
    bool v6706 = v6705 == 1;	// L10486
    int32_t v6707 = s29;	// L10487
    bool v6708 = v6707 < 8;	// L10488
    int32_t v6709 = dsmask9;	// L10489
    int32_t v6710 = v6709 >> v6707;	// L10490
    int32_t v6711 = v6710 & 1;	// L10491
    bool v6712 = v6711 == 1;	// L10492
    bool v6713 = v6706 & v6708;	// L10493
    bool v6714 = v6713 & v6712;	// L10494
    if (v6714) {	// L10495
      int32_t v6715 = s29;	// L10496
      int v6716 = v6715;	// L10497
      drf_full9[v6716] = 0;	// L10498
    }
    half res9;	// L10500
    res9 = (double)0.000000;	// L10501
    int32_t v6718 = op9;	// L10502
    bool v6719 = v6718 == 0;	// L10503
    if (v6719) {	// L10504
      half v6720 = a9;	// L10505
      half v6721 = b9;	// L10506
      half v6722 = v6720 + v6721;	// L10507
      res9 = v6722;	// L10508
    } else {
      int32_t v6723 = op9;	// L10510
      bool v6724 = v6723 == 1;	// L10511
      if (v6724) {	// L10512
        half v6725 = a9;	// L10513
        half v6726 = b9;	// L10514
        half v6727 = v6725 - v6726;	// L10515
        res9 = v6727;	// L10516
      } else {
        int32_t v6728 = op9;	// L10518
        bool v6729 = v6728 == 2;	// L10519
        if (v6729) {	// L10520
          half v6730 = a9;	// L10521
          half v6731 = b9;	// L10522
          half v6732 = v6730 * v6731;	// L10523
          res9 = v6732;	// L10524
        } else {
          int32_t v6733 = op9;	// L10526
          bool v6734 = v6733 == 8;	// L10527
          if (v6734) {	// L10528
            half v6735 = a9;	// L10529
            half v6736 = b9;	// L10530
            bool v6737 = v6735 >= v6736;	// L10531
            if (v6737) {	// L10532
              res9 = (double)1.000000;	// L10533
            } else {
              res9 = (double)-1.000000;	// L10535
            }
          } else {
            int32_t v6738 = op9;	// L10538
            bool v6739 = v6738 == 9;	// L10539
            if (v6739) {	// L10540
              half v6740 = a9;	// L10541
              half v6741 = b9;	// L10542
              bool v6742 = v6740 < v6741;	// L10543
              if (v6742) {	// L10544
                res9 = (double)1.000000;	// L10545
              } else {
                res9 = (double)-1.000000;	// L10547
              }
            } else {
              half v6743 = a9;	// L10550
              res9 = v6743;	// L10551
            }
          }
        }
      }
    }
    int32_t v6744 = a_vld9;	// L10557
    int32_t res_vld9;	// L10558
    res_vld9 = v6744;	// L10559
    int32_t v6746 = op9;	// L10560
    bool v6747 = v6746 == 0;	// L10561
    bool v6748 = v6746 == 1;	// L10562
    bool v6749 = v6746 == 2;	// L10563
    bool v6750 = v6746 == 8;	// L10564
    bool v6751 = v6746 == 9;	// L10565
    bool v6752 = v6747 | v6748;	// L10566
    bool v6753 = v6752 | v6749;	// L10567
    bool v6754 = v6753 | v6750;	// L10568
    bool v6755 = v6754 | v6751;	// L10569
    if (v6755) {	// L10570
      int32_t v6756 = a_vld9;	// L10571
      int32_t v6757 = b_vld9;	// L10572
      int64_t v6758 = v6756;	// L10573
      int64_t v6759 = v6757;	// L10574
      int64_t v6760 = v6758 * v6759;	// L10575
      int32_t v6761 = v6760;	// L10576
      res_vld9 = v6761;	// L10577
    }
    int32_t v6762 = grant9;	// L10579
    bool v6763 = v6762 == 0;	// L10580
    if (v6763) {	// L10581
      res_vld9 = 0;	// L10582
    }
    int32_t v6764 = grant9;	// L10584
    bool v6765 = v6764 == 1;	// L10585
    int32_t v6766 = op9;	// L10586
    bool v6767 = v6766 == 8;	// L10587
    bool v6768 = v6765 & v6767;	// L10588
    if (v6768) {	// L10589
      condition_reg9 = 0;	// L10590
      half v6769 = a9;	// L10591
      half v6770 = b9;	// L10592
      bool v6771 = v6769 >= v6770;	// L10593
      if (v6771) {	// L10594
        condition_reg9 = 1;	// L10595
      }
    }
    int32_t v6772 = grant9;	// L10598
    bool v6773 = v6772 == 1;	// L10599
    int32_t v6774 = op9;	// L10600
    bool v6775 = v6774 == 9;	// L10601
    bool v6776 = v6773 & v6775;	// L10602
    if (v6776) {	// L10603
      condition_reg9 = 0;	// L10604
      half v6777 = a9;	// L10605
      half v6778 = b9;	// L10606
      bool v6779 = v6777 < v6778;	// L10607
      if (v6779) {	// L10608
        condition_reg9 = 1;	// L10609
      }
    }
    ap_uint<17> tx_n9;	// L10612
    tx_n9 = 0;	// L10613
    ap_uint<17> tx_s9;	// L10614
    tx_s9 = 0;	// L10615
    ap_uint<17> tx_w9;	// L10616
    tx_w9 = 0;	// L10617
    ap_uint<17> tx_e9;	// L10618
    tx_e9 = 0;	// L10619
    int32_t is_rtr9;	// L10620
    is_rtr9 = 0;	// L10621
    int32_t do_inj9;	// L10622
    do_inj9 = 0;	// L10623
    int32_t v6786 = op9;	// L10624
    bool v6787 = v6786 >= 4;	// L10625
    ap_int<33> v6788 = v6786;	// L10626
    bool v6789 = v6788 <= 7;	// L10627
    bool v6790 = v6787 & v6789;	// L10628
    if (v6790) {	// L10629
      is_rtr9 = 1;	// L10630
      do_inj9 = 1;	// L10631
    }
    int32_t v6791 = op9;	// L10633
    bool v6792 = v6791 >= 12;	// L10634
    ap_int<33> v6793 = v6791;	// L10635
    bool v6794 = v6793 <= 15;	// L10636
    bool v6795 = v6792 & v6794;	// L10637
    if (v6795) {	// L10638
      is_rtr9 = 1;	// L10639
      int32_t v6796 = condition_reg9;	// L10640
      bool v6797 = v6796 == 1;	// L10641
      if (v6797) {	// L10642
        do_inj9 = 1;	// L10643
      }
    }
    int32_t v6798 = is_rtr9;	// L10646
    bool v6799 = v6798 == 1;	// L10647
    if (v6799) {	// L10648
      int32_t v6800 = do_inj9;	// L10649
      bool v6801 = v6800 == 1;	// L10650
      ap_int<26> v6802 = csd_pkt9;	// L10651
      bool v6803;
      ap_int<26> v6803_tmp = v6802;
      v6803 = v6803_tmp[25];	// L10652
      int32_t v6804 = v6803;	// L10653
      bool v6805 = v6804 == 0;	// L10654
      bool v6806 = v6801 & v6805;	// L10655
      if (v6806) {	// L10656
        half v6807 = res9;	// L10657
        uint16_t v6808;
        union { half from; uint16_t to;} _converter_v6807_to_v6808;
        _converter_v6807_to_v6808.from = v6807;
        v6808 = _converter_v6807_to_v6808.to;	// L10658
        ap_int<26> v6809 = csd_pkt9;	// L10659
        ap_int<26> v6810;
        ap_int<26> v6810_tmp = v6809;
        v6810_tmp(15, 0) = v6808;
        v6810 = v6810_tmp;	// L10660
        csd_pkt9 = v6810;	// L10661
        int32_t v6811 = dst9;	// L10662
        ap_uint<4> v6812 = v6811;	// L10663
        ap_int<26> v6813 = csd_pkt9;	// L10664
        ap_int<26> v6814;
        ap_int<26> v6814_tmp = v6813;
        v6814_tmp(19, 16) = v6812;
        v6814 = v6814_tmp;	// L10665
        csd_pkt9 = v6814;	// L10666
        int32_t v6815 = s29;	// L10667
        ap_uint<4> v6816 = v6815;	// L10668
        ap_int<26> v6817 = csd_pkt9;	// L10669
        ap_int<26> v6818;
        ap_int<26> v6818_tmp = v6817;
        v6818_tmp(24, 21) = v6816;
        v6818 = v6818_tmp;	// L10670
        csd_pkt9 = v6818;	// L10671
        int32_t v6819 = res_vld9;	// L10672
        bool v6820 = v6819;	// L10673
        ap_int<26> v6821 = csd_pkt9;	// L10674
        ap_int<26> v6822;
        ap_int<26> v6822_tmp = v6821;
        v6822_tmp[25] = v6820;        v6822 = v6822_tmp;	// L10675
        csd_pkt9 = v6822;	// L10676
        int32_t v6823 = op9;	// L10677
        int32_t v6824 = v6823 & 3;	// L10678
        csd_dir9 = v6824;	// L10679
      }
    } else {
      int32_t v6825 = dst9;	// L10682
      bool v6826 = v6825 >= 12;	// L10683
      if (v6826) {	// L10684
        ap_uint<17> tw9;	// L10685
        tw9 = 0;	// L10686
        int32_t v6828 = res_vld9;	// L10687
        bool v6829 = v6828;	// L10688
        ap_int<17> v6830 = tw9;	// L10689
        ap_int<17> v6831;
        ap_int<17> v6831_tmp = v6830;
        v6831_tmp[0] = v6829;        v6831 = v6831_tmp;	// L10690
        tw9 = v6831;	// L10691
        half v6832 = res9;	// L10692
        uint16_t v6833;
        union { half from; uint16_t to;} _converter_v6832_to_v6833;
        _converter_v6832_to_v6833.from = v6832;
        v6833 = _converter_v6832_to_v6833.to;	// L10693
        ap_int<17> v6834 = tw9;	// L10694
        ap_int<17> v6835;
        ap_int<17> v6835_tmp = v6834;
        v6835_tmp(16, 1) = v6833;
        v6835 = v6835_tmp;	// L10695
        tw9 = v6835;	// L10696
        int32_t v6836 = dst9;	// L10697
        int32_t v6837 = v6836 & 3;	// L10698
        bool v6838 = v6837 == 0;	// L10699
        if (v6838) {	// L10700
          ap_int<17> v6839 = tw9;	// L10701
          tx_n9 = v6839;	// L10702
        } else {
          int32_t v6840 = dst9;	// L10704
          int32_t v6841 = v6840 & 3;	// L10705
          bool v6842 = v6841 == 1;	// L10706
          if (v6842) {	// L10707
            ap_int<17> v6843 = tw9;	// L10708
            tx_s9 = v6843;	// L10709
          } else {
            int32_t v6844 = dst9;	// L10711
            int32_t v6845 = v6844 & 3;	// L10712
            bool v6846 = v6845 == 2;	// L10713
            if (v6846) {	// L10714
              ap_int<17> v6847 = tw9;	// L10715
              tx_w9 = v6847;	// L10716
            } else {
              ap_int<17> v6848 = tw9;	// L10718
              tx_e9 = v6848;	// L10719
            }
          }
        }
      } else {
        int32_t v6849 = res_vld9;	// L10724
        bool v6850 = v6849 == 1;	// L10725
        if (v6850) {	// L10726
          int32_t v6851 = dst9;	// L10727
          bool v6852 = v6851 < 8;	// L10728
          int32_t v6853 = dsmask9;	// L10729
          int32_t v6854 = v6853 >> v6851;	// L10730
          int32_t v6855 = v6854 & 1;	// L10731
          bool v6856 = v6855 == 1;	// L10732
          bool v6857 = v6852 & v6856;	// L10733
          if (v6857) {	// L10734
            int32_t v6858 = dst9;	// L10735
            int v6859 = v6858;	// L10736
            int32_t v6860 = drf_full9[v6859];	// L10737
            bool v6861 = v6860 == 0;	// L10738
            if (v6861) {	// L10739
              half v6862 = res9;	// L10740
              int32_t v6863 = dst9;	// L10741
              int v6864 = v6863;	// L10742
              drf9[v6864] = v6862;	// L10743
              int32_t v6865 = dst9;	// L10744
              int v6866 = v6865;	// L10745
              drf_full9[v6866] = 1;	// L10746
            }
          } else {
            half v6867 = res9;	// L10749
            int32_t v6868 = dst9;	// L10750
            int v6869 = v6868;	// L10751
            drf9[v6869] = v6867;	// L10752
          }
        }
      }
    }
    ap_int<17> v6870 = tx_n9;	// L10757
    txn_r9 = v6870;	// L10758
    ap_int<17> v6871 = tx_s9;	// L10759
    txs_r9 = v6871;	// L10760
    ap_int<17> v6872 = tx_w9;	// L10761
    txw_r9 = v6872;	// L10762
    ap_int<17> v6873 = tx_e9;	// L10763
    txe_r9 = v6873;	// L10764
    int32_t v6874 = crv_vld9;	// L10765
    bool v6875 = v6874 == 1;	// L10766
    if (v6875) {	// L10767
      int32_t v6876 = crv_mode9;	// L10768
      bool v6877 = v6876 == 1;	// L10769
      if (v6877) {	// L10770
        int32_t v6878 = crv_addr9;	// L10771
        int32_t v6879 = v6878 >> 3;	// L10772
        int32_t v6880 = v6879 & 1;	// L10773
        bool v6881 = v6880 == 1;	// L10774
        if (v6881) {	// L10775
          int32_t v6882 = crv_raw9;	// L10776
          int32_t v6883 = crv_addr9;	// L10777
          int32_t v6884 = v6883 & 7;	// L10778
          int v6885 = v6884;	// L10779
          irf9[v6885] = v6882;	// L10780
        } else {
          int32_t v6886 = crv_addr9;	// L10782
          bool v6887 = v6886 == 0;	// L10783
          if (v6887) {	// L10784
            int32_t v6888 = crv_raw9;	// L10785
            int32_t v6889 = v6888 & 255;	// L10786
            dsmask9 = v6889;	// L10787
            int32_t v6890 = crv_raw9;	// L10788
            int32_t v6891 = v6890 >> 8;	// L10789
            int32_t v6892 = v6891 & 7;	// L10790
            cfg_isz9 = v6892;	// L10791
            int32_t v6893 = crv_raw9;	// L10792
            int32_t v6894 = v6893 >> 15;	// L10793
            int32_t v6895 = v6894 & 1;	// L10794
            bool v6896 = v6895 == 1;	// L10795
            if (v6896) {	// L10796
              fetch_en9 = 1;	// L10797
              instr_cnt9 = 0;	// L10798
              iter_cnt9 = 0;	// L10799
            }
          } else {
            int32_t v6897 = crv_addr9;	// L10802
            bool v6898 = v6897 == 1;	// L10803
            if (v6898) {	// L10804
              int32_t v6899 = crv_raw9;	// L10805
              int32_t v6900 = v6899 & 255;	// L10806
              cfg_itsz9 = v6900;	// L10807
            }
          }
        }
      } else {
        int32_t v6901 = crv_addr9;	// L10812
        bool v6902 = v6901 < 8;	// L10813
        int32_t v6903 = dsmask9;	// L10814
        int32_t v6904 = v6903 >> v6901;	// L10815
        int32_t v6905 = v6904 & 1;	// L10816
        bool v6906 = v6905 == 1;	// L10817
        bool v6907 = v6902 & v6906;	// L10818
        if (v6907) {	// L10819
          int32_t v6908 = crv_addr9;	// L10820
          int v6909 = v6908;	// L10821
          int32_t v6910 = drf_full9[v6909];	// L10822
          bool v6911 = v6910 == 0;	// L10823
          if (v6911) {	// L10824
            half v6912 = crv_data9;	// L10825
            int32_t v6913 = crv_addr9;	// L10826
            int v6914 = v6913;	// L10827
            drf9[v6914] = v6912;	// L10828
            int32_t v6915 = crv_addr9;	// L10829
            int v6916 = v6915;	// L10830
            drf_full9[v6916] = 1;	// L10831
          }
        } else {
          half v6917 = crv_data9;	// L10834
          int32_t v6918 = crv_addr9;	// L10835
          int v6919 = v6918;	// L10836
          drf9[v6919] = v6917;	// L10837
        }
      }
    }
  }
}

void node_2_2(
  hls::stream< ap_uint<26> >& v6920,
  hls::stream< ap_uint<26> >& v6921,
  hls::stream< ap_uint<26> >& v6922,
  hls::stream< ap_uint<26> >& v6923,
  hls::stream< ap_uint<17> >& v6924,
  hls::stream< ap_uint<17> >& v6925,
  hls::stream< ap_uint<17> >& v6926,
  hls::stream< ap_uint<17> >& v6927,
  hls::stream< int32_t >& v6928,
  hls::stream< int32_t >& v6929,
  hls::stream< int32_t >& v6930,
  hls::stream< int32_t >& v6931,
  hls::stream< ap_uint<26> >& v6932,
  hls::stream< ap_uint<26> >& v6933,
  hls::stream< ap_uint<26> >& v6934,
  hls::stream< ap_uint<26> >& v6935,
  hls::stream< int32_t >& v6936,
  hls::stream< int32_t >& v6937,
  hls::stream< int32_t >& v6938,
  hls::stream< int32_t >& v6939,
  hls::stream< ap_uint<17> >& v6940,
  hls::stream< ap_uint<17> >& v6941,
  hls::stream< ap_uint<17> >& v6942,
  hls::stream< ap_uint<17> >& v6943
) {	// L10844
  int32_t irf10[8];	// L10875
  for (int v6945 = 0; v6945 < 8; v6945++) {	// L10876
    irf10[v6945] = 0;	// L10876
  }
  half drf10[8];	// L10877
  #pragma HLS array_partition variable=drf10 complete dim=1

  for (int v6947 = 0; v6947 < 8; v6947++) {	// L10878
    drf10[v6947] = (double)0.000000;	// L10878
  }
  int32_t drf_full10[8];	// L10879
  #pragma HLS array_partition variable=drf_full10 complete dim=1

  for (int v6949 = 0; v6949 < 8; v6949++) {	// L10880
    drf_full10[v6949] = 0;	// L10880
  }
  int32_t dsmask10;	// L10881
  dsmask10 = 0;	// L10882
  int32_t crv_vld10;	// L10883
  crv_vld10 = 0;	// L10884
  half crv_data10;	// L10885
  crv_data10 = (double)0.000000;	// L10886
  int32_t crv_addr10;	// L10887
  crv_addr10 = 0;	// L10888
  int32_t crv_mode10;	// L10889
  crv_mode10 = 0;	// L10890
  int32_t crv_raw10;	// L10891
  crv_raw10 = 0;	// L10892
  int32_t csd_vld10;	// L10893
  csd_vld10 = 0;	// L10894
  ap_uint<26> csd_pkt10;	// L10895
  csd_pkt10 = 0;	// L10896
  int32_t csd_dir10;	// L10897
  csd_dir10 = 0;	// L10898
  int32_t row_id10;	// L10899
  row_id10 = 2;	// L10900
  int32_t col_id10;	// L10901
  col_id10 = 2;	// L10902
  ap_uint<26> oe_r10;	// L10903
  oe_r10 = 0;	// L10904
  ap_uint<26> ow_r10;	// L10905
  ow_r10 = 0;	// L10906
  ap_uint<26> on_r10;	// L10907
  on_r10 = 0;	// L10908
  ap_uint<26> os_r10;	// L10909
  os_r10 = 0;	// L10910
  ap_uint<17> txn_r10;	// L10911
  txn_r10 = 0;	// L10912
  ap_uint<17> txs_r10;	// L10913
  txs_r10 = 0;	// L10914
  ap_uint<17> txw_r10;	// L10915
  txw_r10 = 0;	// L10916
  ap_uint<17> txe_r10;	// L10917
  txe_r10 = 0;	// L10918
  half hold_v10[4][2];	// L10919
  #pragma HLS array_partition variable=hold_v10 complete dim=1
  #pragma HLS array_partition variable=hold_v10 complete dim=2

  for (int v6970 = 0; v6970 < 4; v6970++) {	// L10920
    for (int v6971 = 0; v6971 < 2; v6971++) {	// L10920
      hold_v10[v6970][v6971] = (double)0.000000;	// L10920
    }
  }
  int32_t hold_cnt10[4];	// L10921
  #pragma HLS array_partition variable=hold_cnt10 complete dim=1

  for (int v6973 = 0; v6973 < 4; v6973++) {	// L10922
    hold_cnt10[v6973] = 0;	// L10922
  }
  ap_uint<26> rbuf10[4][2];	// L10923
  #pragma HLS array_partition variable=rbuf10 complete dim=1
  #pragma HLS array_partition variable=rbuf10 complete dim=2

  for (int v6975 = 0; v6975 < 4; v6975++) {	// L10924
    for (int v6976 = 0; v6976 < 2; v6976++) {	// L10924
      rbuf10[v6975][v6976] = 0;	// L10924
    }
  }
  int32_t rbcnt10[4];	// L10925
  #pragma HLS array_partition variable=rbcnt10 complete dim=1

  for (int v6978 = 0; v6978 < 4; v6978++) {	// L10926
    rbcnt10[v6978] = 0;	// L10926
  }
  int32_t rcred10[4];	// L10927
  #pragma HLS array_partition variable=rcred10 complete dim=1

  for (int v6980 = 0; v6980 < 4; v6980++) {	// L10928
    rcred10[v6980] = 0;	// L10928
  }
  int32_t cre_r10;	// L10929
  cre_r10 = 2;	// L10930
  int32_t crw_r10;	// L10931
  crw_r10 = 2;	// L10932
  int32_t crs_r10;	// L10933
  crs_r10 = 2;	// L10934
  int32_t crn_r10;	// L10935
  crn_r10 = 2;	// L10936
  int32_t cfg_isz10;	// L10937
  cfg_isz10 = 0;	// L10938
  int32_t cfg_itsz10;	// L10939
  cfg_itsz10 = 0;	// L10940
  int32_t fetch_en10;	// L10941
  fetch_en10 = 0;	// L10942
  int32_t instr_cnt10;	// L10943
  instr_cnt10 = 0;	// L10944
  int32_t iter_cnt10;	// L10945
  iter_cnt10 = 0;	// L10946
  int32_t condition_reg10;	// L10947
  condition_reg10 = 0;	// L10948
  l_S_t_0_t10: for (int t10 = 0; t10 < 8; t10++) {	// L10949
  #pragma HLS pipeline II=1
    ap_int<26> v6992 = oe_r10;	// L10950
    v6920.write(v6992);	// L10951
    ap_int<26> v6993 = ow_r10;	// L10952
    v6921.write(v6993);	// L10953
    ap_int<26> v6994 = os_r10;	// L10954
    v6922.write(v6994);	// L10955
    ap_int<26> v6995 = on_r10;	// L10956
    v6923.write(v6995);	// L10957
    ap_int<17> v6996 = txe_r10;	// L10958
    v6924.write(v6996);	// L10959
    ap_int<17> v6997 = txw_r10;	// L10960
    v6925.write(v6997);	// L10961
    ap_int<17> v6998 = txs_r10;	// L10962
    v6926.write(v6998);	// L10963
    ap_int<17> v6999 = txn_r10;	// L10964
    v6927.write(v6999);	// L10965
    int32_t v7000 = cre_r10;	// L10966
    v6928.write(v7000);	// L10967
    int32_t v7001 = crw_r10;	// L10968
    v6929.write(v7001);	// L10969
    int32_t v7002 = crs_r10;	// L10970
    v6930.write(v7002);	// L10971
    int32_t v7003 = crn_r10;	// L10972
    v6931.write(v7003);	// L10973
    ap_uint<26> v7004 = v6932.read();	// L10974
    ap_uint<26> p_w10;	// L10975
    p_w10 = v7004;	// L10976
    ap_uint<26> v7006 = v6933.read();	// L10977
    ap_uint<26> p_e10;	// L10978
    p_e10 = v7006;	// L10979
    ap_uint<26> v7008 = v6934.read();	// L10980
    ap_uint<26> p_n10;	// L10981
    p_n10 = v7008;	// L10982
    ap_uint<26> v7010 = v6935.read();	// L10983
    ap_uint<26> p_s10;	// L10984
    p_s10 = v7010;	// L10985
    int32_t v7012 = v6936.read();	// L10986
    int32_t v7013 = rcred10[0];	// L10987
    ap_int<33> v7014 = v7013;	// L10988
    ap_int<33> v7015 = v7012;	// L10989
    ap_int<33> v7016 = v7014 + v7015;	// L10990
    int32_t v7017 = v7016;	// L10991
    rcred10[0] = v7017;	// L10992
    int32_t v7018 = v6937.read();	// L10993
    int32_t v7019 = rcred10[1];	// L10994
    ap_int<33> v7020 = v7019;	// L10995
    ap_int<33> v7021 = v7018;	// L10996
    ap_int<33> v7022 = v7020 + v7021;	// L10997
    int32_t v7023 = v7022;	// L10998
    rcred10[1] = v7023;	// L10999
    int32_t v7024 = v6938.read();	// L11000
    int32_t v7025 = rcred10[2];	// L11001
    ap_int<33> v7026 = v7025;	// L11002
    ap_int<33> v7027 = v7024;	// L11003
    ap_int<33> v7028 = v7026 + v7027;	// L11004
    int32_t v7029 = v7028;	// L11005
    rcred10[2] = v7029;	// L11006
    int32_t v7030 = v6939.read();	// L11007
    int32_t v7031 = rcred10[3];	// L11008
    ap_int<33> v7032 = v7031;	// L11009
    ap_int<33> v7033 = v7030;	// L11010
    ap_int<33> v7034 = v7032 + v7033;	// L11011
    int32_t v7035 = v7034;	// L11012
    rcred10[3] = v7035;	// L11013
    ap_uint<26> fin10[4];	// L11014
    for (int v7037 = 0; v7037 < 4; v7037++) {	// L11015
      fin10[v7037] = 0;	// L11015
    }
    ap_int<26> v7038 = p_w10;	// L11016
    fin10[0] = v7038;	// L11017
    ap_int<26> v7039 = p_e10;	// L11018
    fin10[1] = v7039;	// L11019
    ap_int<26> v7040 = p_n10;	// L11020
    fin10[2] = v7040;	// L11021
    ap_int<26> v7041 = p_s10;	// L11022
    fin10[3] = v7041;	// L11023
    l_S_d_0_d40: for (int d40 = 0; d40 < 4; d40++) {	// L11024
      ap_uint<26> v7043 = fin10[d40];	// L11025
      bool v7044;
      ap_int<26> v7044_tmp = v7043;
      v7044 = v7044_tmp[25];	// L11026
      int32_t v7045 = v7044;	// L11027
      bool v7046 = v7045 == 1;	// L11028
      int32_t v7047 = rbcnt10[d40];	// L11029
      bool v7048 = v7047 < 2;	// L11030
      bool v7049 = v7046 & v7048;	// L11031
      if (v7049) {	// L11032
        ap_uint<26> v7050 = fin10[d40];	// L11033
        int32_t v7051 = rbcnt10[d40];	// L11034
        int v7052 = v7051;	// L11035
        rbuf10[d40][v7052] = v7050;	// L11036
        int32_t v7053 = rbcnt10[d40];	// L11037
        ap_int<33> v7054 = v7053;	// L11038
        ap_int<33> v7055 = v7054 + 1;	// L11039
        int32_t v7056 = v7055;	// L11040
        rbcnt10[d40] = v7056;	// L11041
      }
    }
    ap_uint<26> hd10[4];	// L11044
    for (int v7058 = 0; v7058 < 4; v7058++) {	// L11045
      hd10[v7058] = 0;	// L11045
    }
    int32_t hvld10[4];	// L11046
    for (int v7060 = 0; v7060 < 4; v7060++) {	// L11047
      hvld10[v7060] = 0;	// L11047
    }
    int32_t hit10[4];	// L11048
    for (int v7062 = 0; v7062 < 4; v7062++) {	// L11049
      hit10[v7062] = 0;	// L11049
    }
    int32_t axis10[4];	// L11050
    for (int v7064 = 0; v7064 < 4; v7064++) {	// L11051
      axis10[v7064] = 0;	// L11051
    }
    int32_t v7065 = col_id10;	// L11052
    axis10[0] = v7065;	// L11053
    int32_t v7066 = col_id10;	// L11054
    axis10[1] = v7066;	// L11055
    int32_t v7067 = row_id10;	// L11056
    axis10[2] = v7067;	// L11057
    int32_t v7068 = row_id10;	// L11058
    axis10[3] = v7068;	// L11059
    l_S_d_1_d41: for (int d41 = 0; d41 < 4; d41++) {	// L11060
      int32_t v7070 = rbcnt10[d41];	// L11061
      bool v7071 = v7070 > 0;	// L11062
      if (v7071) {	// L11063
        ap_uint<26> v7072 = rbuf10[d41][0];	// L11064
        hd10[d41] = v7072;	// L11065
        hvld10[d41] = 1;	// L11066
        ap_uint<26> v7073 = hd10[d41];	// L11067
        ap_int<4> v7074;
        ap_int<26> v7074_tmp = v7073;
        v7074 = v7074_tmp(24, 21);	// L11068
        int32_t v7075 = axis10[d41];	// L11069
        int32_t v7076 = v7074;	// L11070
        bool v7077 = v7076 == v7075;	// L11071
        if (v7077) {	// L11072
          hit10[d41] = 1;	// L11073
        }
      }
    }
    ap_uint<26> o_crv10;	// L11077
    o_crv10 = 0;	// L11078
    int32_t crv_in10;	// L11079
    crv_in10 = -1;	// L11080
    int32_t v7080 = hit10[3];	// L11081
    bool v7081 = v7080 == 1;	// L11082
    if (v7081) {	// L11083
      ap_uint<26> v7082 = hd10[3];	// L11084
      o_crv10 = v7082;	// L11085
      crv_in10 = 3;	// L11086
    } else {
      int32_t v7083 = hit10[2];	// L11088
      bool v7084 = v7083 == 1;	// L11089
      if (v7084) {	// L11090
        ap_uint<26> v7085 = hd10[2];	// L11091
        o_crv10 = v7085;	// L11092
        crv_in10 = 2;	// L11093
      } else {
        int32_t v7086 = hit10[1];	// L11095
        bool v7087 = v7086 == 1;	// L11096
        if (v7087) {	// L11097
          ap_uint<26> v7088 = hd10[1];	// L11098
          o_crv10 = v7088;	// L11099
          crv_in10 = 1;	// L11100
        } else {
          int32_t v7089 = hit10[0];	// L11102
          bool v7090 = v7089 == 1;	// L11103
          if (v7090) {	// L11104
            ap_uint<26> v7091 = hd10[0];	// L11105
            o_crv10 = v7091;	// L11106
            crv_in10 = 0;	// L11107
          }
        }
      }
    }
    ap_uint<26> o_out10[4];	// L11112
    for (int v7093 = 0; v7093 < 4; v7093++) {	// L11113
      o_out10[v7093] = 0;	// L11113
    }
    int32_t pop10[4];	// L11114
    for (int v7095 = 0; v7095 < 4; v7095++) {	// L11115
      pop10[v7095] = 0;	// L11115
    }
    int32_t inj_done10;	// L11116
    inj_done10 = 0;	// L11117
    int32_t idir10;	// L11118
    idir10 = -1;	// L11119
    ap_int<26> v7098 = csd_pkt10;	// L11120
    bool v7099;
    ap_int<26> v7099_tmp = v7098;
    v7099 = v7099_tmp[25];	// L11121
    int32_t v7100 = v7099;	// L11122
    bool v7101 = v7100 == 1;	// L11123
    if (v7101) {	// L11124
      int32_t v7102 = csd_dir10;	// L11125
      ap_int<33> v7103 = v7102;	// L11126
      ap_int<33> v7104 = 3 - v7103;	// L11127
      int32_t v7105 = v7104;	// L11128
      idir10 = v7105;	// L11129
    }
    l_S_o_2_o10: for (int o10 = 0; o10 < 4; o10++) {	// L11131
      int32_t v7107 = rcred10[o10];	// L11132
      bool v7108 = v7107 > 0;	// L11133
      if (v7108) {	// L11134
        int32_t v7109 = idir10;	// L11135
        ap_int<33> v7110 = v7109;	// L11136
        ap_int<33> v7111 = o10;	// L11137
        bool v7112 = v7110 == v7111;	// L11138
        if (v7112) {	// L11139
          ap_int<26> v7113 = csd_pkt10;	// L11140
          o_out10[o10] = v7113;	// L11141
          int32_t v7114 = rcred10[o10];	// L11142
          ap_int<33> v7115 = v7114;	// L11143
          ap_int<33> v7116 = v7115 - 1;	// L11144
          int32_t v7117 = v7116;	// L11145
          rcred10[o10] = v7117;	// L11146
          inj_done10 = 1;	// L11147
        } else {
          int32_t v7118 = hvld10[o10];	// L11149
          bool v7119 = v7118 == 1;	// L11150
          int32_t v7120 = hit10[o10];	// L11151
          bool v7121 = v7120 == 0;	// L11152
          bool v7122 = v7119 & v7121;	// L11153
          if (v7122) {	// L11154
            ap_uint<26> v7123 = hd10[o10];	// L11155
            o_out10[o10] = v7123;	// L11156
            int32_t v7124 = rcred10[o10];	// L11157
            ap_int<33> v7125 = v7124;	// L11158
            ap_int<33> v7126 = v7125 - 1;	// L11159
            int32_t v7127 = v7126;	// L11160
            rcred10[o10] = v7127;	// L11161
            pop10[o10] = 1;	// L11162
          }
        }
      }
    }
    int32_t v7128 = crv_in10;	// L11167
    bool v7129 = v7128 >= 0;	// L11168
    if (v7129) {	// L11169
      int32_t v7130 = crv_in10;	// L11170
      int v7131 = v7130;	// L11171
      pop10[v7131] = 1;	// L11172
    }
    int32_t ret10[4];	// L11174
    for (int v7133 = 0; v7133 < 4; v7133++) {	// L11175
      ret10[v7133] = 0;	// L11175
    }
    l_S_d_3_d42: for (int d42 = 0; d42 < 4; d42++) {	// L11176
      int32_t v7135 = pop10[d42];	// L11177
      bool v7136 = v7135 == 1;	// L11178
      if (v7136) {	// L11179
        l_S_sft_3_sft10: for (int sft10 = 0; sft10 < 1; sft10++) {	// L11180
          ap_uint<26> v7138 = rbuf10[d42][(sft10 + 1)];	// L11181
          rbuf10[d42][sft10] = v7138;	// L11182
        }
        int32_t v7139 = rbcnt10[d42];	// L11184
        ap_int<33> v7140 = v7139;	// L11185
        ap_int<33> v7141 = v7140 - 1;	// L11186
        int32_t v7142 = v7141;	// L11187
        rbcnt10[d42] = v7142;	// L11188
        ret10[d42] = 1;	// L11189
      }
    }
    int32_t v7143 = ret10[0];	// L11192
    cre_r10 = v7143;	// L11193
    int32_t v7144 = ret10[1];	// L11194
    crw_r10 = v7144;	// L11195
    int32_t v7145 = ret10[2];	// L11196
    crs_r10 = v7145;	// L11197
    int32_t v7146 = ret10[3];	// L11198
    crn_r10 = v7146;	// L11199
    ap_uint<26> v7147 = o_out10[0];	// L11200
    oe_r10 = v7147;	// L11201
    ap_uint<26> v7148 = o_out10[1];	// L11202
    ow_r10 = v7148;	// L11203
    ap_uint<26> v7149 = o_out10[2];	// L11204
    os_r10 = v7149;	// L11205
    ap_uint<26> v7150 = o_out10[3];	// L11206
    on_r10 = v7150;	// L11207
    int32_t v7151 = inj_done10;	// L11208
    bool v7152 = v7151 == 1;	// L11209
    if (v7152) {	// L11210
      csd_pkt10 = 0;	// L11211
    }
    ap_int<26> v7153 = o_crv10;	// L11213
    bool v7154;
    ap_int<26> v7154_tmp = v7153;
    v7154 = v7154_tmp[25];	// L11214
    int32_t v7155 = v7154;	// L11215
    crv_vld10 = v7155;	// L11216
    ap_int<26> v7156 = o_crv10;	// L11217
    int16_t v7157;
    ap_int<26> v7157_tmp = v7156;
    v7157 = v7157_tmp(15, 0);	// L11218
    half v7158;
    union { uint16_t from; half to;} _converter_v7157_to_v7158;
    _converter_v7157_to_v7158.from = v7157;
    v7158 = _converter_v7157_to_v7158.to;	// L11219
    crv_data10 = v7158;	// L11220
    ap_int<26> v7159 = o_crv10;	// L11221
    ap_int<4> v7160;
    ap_int<26> v7160_tmp = v7159;
    v7160 = v7160_tmp(19, 16);	// L11222
    int32_t v7161 = v7160;	// L11223
    crv_addr10 = v7161;	// L11224
    ap_int<26> v7162 = o_crv10;	// L11225
    bool v7163;
    ap_int<26> v7163_tmp = v7162;
    v7163 = v7163_tmp[20];	// L11226
    int32_t v7164 = v7163;	// L11227
    crv_mode10 = v7164;	// L11228
    ap_int<26> v7165 = o_crv10;	// L11229
    int16_t v7166;
    ap_int<26> v7166_tmp = v7165;
    v7166 = v7166_tmp(15, 0);	// L11230
    int32_t v7167 = v7166;	// L11231
    crv_raw10 = v7167;	// L11232
    ap_uint<17> v7168 = v6940.read();	// L11233
    ap_uint<17> rx_w10;	// L11234
    rx_w10 = v7168;	// L11235
    ap_uint<17> v7170 = v6941.read();	// L11236
    ap_uint<17> rx_e10;	// L11237
    rx_e10 = v7170;	// L11238
    ap_uint<17> v7172 = v6942.read();	// L11239
    ap_uint<17> rx_n10;	// L11240
    rx_n10 = v7172;	// L11241
    ap_uint<17> v7174 = v6943.read();	// L11242
    ap_uint<17> rx_s10;	// L11243
    rx_s10 = v7174;	// L11244
    half rxv10[4];	// L11245
    for (int v7177 = 0; v7177 < 4; v7177++) {	// L11246
      rxv10[v7177] = (double)0.000000;	// L11246
    }
    int32_t rxvld10[4];	// L11247
    for (int v7179 = 0; v7179 < 4; v7179++) {	// L11248
      rxvld10[v7179] = 0;	// L11248
    }
    ap_int<17> v7180 = rx_n10;	// L11249
    int16_t v7181;
    ap_int<17> v7181_tmp = v7180;
    v7181 = v7181_tmp(16, 1);	// L11250
    half v7182;
    union { uint16_t from; half to;} _converter_v7181_to_v7182;
    _converter_v7181_to_v7182.from = v7181;
    v7182 = _converter_v7181_to_v7182.to;	// L11251
    rxv10[0] = v7182;	// L11252
    ap_int<17> v7183 = rx_n10;	// L11253
    bool v7184;
    ap_int<17> v7184_tmp = v7183;
    v7184 = v7184_tmp[0];	// L11254
    int32_t v7185 = v7184;	// L11255
    rxvld10[0] = v7185;	// L11256
    ap_int<17> v7186 = rx_s10;	// L11257
    int16_t v7187;
    ap_int<17> v7187_tmp = v7186;
    v7187 = v7187_tmp(16, 1);	// L11258
    half v7188;
    union { uint16_t from; half to;} _converter_v7187_to_v7188;
    _converter_v7187_to_v7188.from = v7187;
    v7188 = _converter_v7187_to_v7188.to;	// L11259
    rxv10[1] = v7188;	// L11260
    ap_int<17> v7189 = rx_s10;	// L11261
    bool v7190;
    ap_int<17> v7190_tmp = v7189;
    v7190 = v7190_tmp[0];	// L11262
    int32_t v7191 = v7190;	// L11263
    rxvld10[1] = v7191;	// L11264
    ap_int<17> v7192 = rx_w10;	// L11265
    int16_t v7193;
    ap_int<17> v7193_tmp = v7192;
    v7193 = v7193_tmp(16, 1);	// L11266
    half v7194;
    union { uint16_t from; half to;} _converter_v7193_to_v7194;
    _converter_v7193_to_v7194.from = v7193;
    v7194 = _converter_v7193_to_v7194.to;	// L11267
    rxv10[2] = v7194;	// L11268
    ap_int<17> v7195 = rx_w10;	// L11269
    bool v7196;
    ap_int<17> v7196_tmp = v7195;
    v7196 = v7196_tmp[0];	// L11270
    int32_t v7197 = v7196;	// L11271
    rxvld10[2] = v7197;	// L11272
    ap_int<17> v7198 = rx_e10;	// L11273
    int16_t v7199;
    ap_int<17> v7199_tmp = v7198;
    v7199 = v7199_tmp(16, 1);	// L11274
    half v7200;
    union { uint16_t from; half to;} _converter_v7199_to_v7200;
    _converter_v7199_to_v7200.from = v7199;
    v7200 = _converter_v7199_to_v7200.to;	// L11275
    rxv10[3] = v7200;	// L11276
    ap_int<17> v7201 = rx_e10;	// L11277
    bool v7202;
    ap_int<17> v7202_tmp = v7201;
    v7202 = v7202_tmp[0];	// L11278
    int32_t v7203 = v7202;	// L11279
    rxvld10[3] = v7203;	// L11280
    l_S_d_5_d43: for (int d43 = 0; d43 < 4; d43++) {	// L11281
      int32_t v7205 = rxvld10[d43];	// L11282
      bool v7206 = v7205 == 1;	// L11283
      int32_t v7207 = hold_cnt10[d43];	// L11284
      bool v7208 = v7207 < 2;	// L11285
      bool v7209 = v7206 & v7208;	// L11286
      if (v7209) {	// L11287
        half v7210 = rxv10[d43];	// L11288
        int32_t v7211 = hold_cnt10[d43];	// L11289
        int v7212 = v7211;	// L11290
        hold_v10[d43][v7212] = v7210;	// L11291
        int32_t v7213 = hold_cnt10[d43];	// L11292
        ap_int<33> v7214 = v7213;	// L11293
        ap_int<33> v7215 = v7214 + 1;	// L11294
        int32_t v7216 = v7215;	// L11295
        hold_cnt10[d43] = v7216;	// L11296
      }
    }
    int32_t pc10;	// L11299
    pc10 = -1;	// L11300
    int32_t v7218 = fetch_en10;	// L11301
    bool v7219 = v7218 == 1;	// L11302
    if (v7219) {	// L11303
      int32_t v7220 = instr_cnt10;	// L11304
      pc10 = v7220;	// L11305
    }
    int32_t instr10;	// L11307
    instr10 = 0;	// L11308
    int32_t v7222 = pc10;	// L11309
    bool v7223 = v7222 >= 0;	// L11310
    if (v7223) {	// L11311
      int32_t v7224 = pc10;	// L11312
      int v7225 = v7224;	// L11313
      int32_t v7226 = irf10[v7225];	// L11314
      instr10 = v7226;	// L11315
    }
    int32_t v7227 = instr10;	// L11317
    int32_t v7228 = v7227 & 15;	// L11318
    int32_t op10;	// L11319
    op10 = v7228;	// L11320
    int32_t v7230 = instr10;	// L11321
    int32_t v7231 = v7230 >> 4;	// L11322
    int32_t v7232 = v7231 & 15;	// L11323
    int32_t dst10;	// L11324
    dst10 = v7232;	// L11325
    int32_t v7234 = instr10;	// L11326
    int32_t v7235 = v7234 >> 8;	// L11327
    int32_t v7236 = v7235 & 15;	// L11328
    int32_t s110;	// L11329
    s110 = v7236;	// L11330
    int32_t v7238 = instr10;	// L11331
    int32_t v7239 = v7238 >> 12;	// L11332
    int32_t v7240 = v7239 & 15;	// L11333
    int32_t s210;	// L11334
    s210 = v7240;	// L11335
    half a10;	// L11336
    a10 = (double)0.000000;	// L11337
    half b10;	// L11338
    b10 = (double)0.000000;	// L11339
    int32_t v7244 = s110;	// L11340
    bool v7245 = v7244 >= 12;	// L11341
    if (v7245) {	// L11342
      int32_t v7246 = s110;	// L11343
      int32_t v7247 = v7246 & 3;	// L11344
      int v7248 = v7247;	// L11345
      half v7249 = hold_v10[v7248][0];	// L11346
      a10 = v7249;	// L11347
    } else {
      int32_t v7250 = s110;	// L11349
      int v7251 = v7250;	// L11350
      half v7252 = drf10[v7251];	// L11351
      a10 = v7252;	// L11352
    }
    int32_t v7253 = s210;	// L11354
    bool v7254 = v7253 >= 12;	// L11355
    if (v7254) {	// L11356
      int32_t v7255 = s210;	// L11357
      int32_t v7256 = v7255 & 3;	// L11358
      int v7257 = v7256;	// L11359
      half v7258 = hold_v10[v7257][0];	// L11360
      b10 = v7258;	// L11361
    } else {
      int32_t v7259 = s210;	// L11363
      int v7260 = v7259;	// L11364
      half v7261 = drf10[v7260];	// L11365
      b10 = v7261;	// L11366
    }
    int32_t a_vld10;	// L11368
    a_vld10 = 1;	// L11369
    int32_t b_vld10;	// L11370
    b_vld10 = 1;	// L11371
    int32_t v7264 = s110;	// L11372
    bool v7265 = v7264 >= 12;	// L11373
    if (v7265) {	// L11374
      a_vld10 = 0;	// L11375
      int32_t v7266 = s110;	// L11376
      int32_t v7267 = v7266 & 3;	// L11377
      int v7268 = v7267;	// L11378
      int32_t v7269 = hold_cnt10[v7268];	// L11379
      bool v7270 = v7269 > 0;	// L11380
      if (v7270) {	// L11381
        a_vld10 = 1;	// L11382
      }
    }
    int32_t v7271 = s210;	// L11385
    bool v7272 = v7271 >= 12;	// L11386
    if (v7272) {	// L11387
      b_vld10 = 0;	// L11388
      int32_t v7273 = s210;	// L11389
      int32_t v7274 = v7273 & 3;	// L11390
      int v7275 = v7274;	// L11391
      int32_t v7276 = hold_cnt10[v7275];	// L11392
      bool v7277 = v7276 > 0;	// L11393
      if (v7277) {	// L11394
        b_vld10 = 1;	// L11395
      }
    }
    int32_t v7278 = s110;	// L11398
    bool v7279 = v7278 < 8;	// L11399
    int32_t v7280 = dsmask10;	// L11400
    int32_t v7281 = v7280 >> v7278;	// L11401
    int32_t v7282 = v7281 & 1;	// L11402
    bool v7283 = v7282 == 1;	// L11403
    bool v7284 = v7279 & v7283;	// L11404
    if (v7284) {	// L11405
      int32_t v7285 = s110;	// L11406
      int v7286 = v7285;	// L11407
      int32_t v7287 = drf_full10[v7286];	// L11408
      bool v7288 = v7287 == 0;	// L11409
      if (v7288) {	// L11410
        a_vld10 = 0;	// L11411
      }
    }
    int32_t v7289 = s210;	// L11414
    bool v7290 = v7289 < 8;	// L11415
    int32_t v7291 = dsmask10;	// L11416
    int32_t v7292 = v7291 >> v7289;	// L11417
    int32_t v7293 = v7292 & 1;	// L11418
    bool v7294 = v7293 == 1;	// L11419
    bool v7295 = v7290 & v7294;	// L11420
    if (v7295) {	// L11421
      int32_t v7296 = s210;	// L11422
      int v7297 = v7296;	// L11423
      int32_t v7298 = drf_full10[v7297];	// L11424
      bool v7299 = v7298 == 0;	// L11425
      if (v7299) {	// L11426
        b_vld10 = 0;	// L11427
      }
    }
    int32_t binop10;	// L11430
    binop10 = 0;	// L11431
    int32_t v7301 = op10;	// L11432
    bool v7302 = v7301 == 0;	// L11433
    bool v7303 = v7301 == 1;	// L11434
    bool v7304 = v7301 == 2;	// L11435
    bool v7305 = v7301 == 8;	// L11436
    bool v7306 = v7301 == 9;	// L11437
    bool v7307 = v7302 | v7303;	// L11438
    bool v7308 = v7307 | v7304;	// L11439
    bool v7309 = v7308 | v7305;	// L11440
    bool v7310 = v7309 | v7306;	// L11441
    if (v7310) {	// L11442
      binop10 = 1;	// L11443
    }
    int32_t grant10;	// L11445
    grant10 = 0;	// L11446
    int32_t v7312 = pc10;	// L11447
    bool v7313 = v7312 >= 0;	// L11448
    if (v7313) {	// L11449
      grant10 = 1;	// L11450
    }
    int32_t v7314 = pc10;	// L11452
    bool v7315 = v7314 >= 0;	// L11453
    int32_t v7316 = a_vld10;	// L11454
    bool v7317 = v7316 == 0;	// L11455
    int32_t v7318 = binop10;	// L11456
    bool v7319 = v7318 == 1;	// L11457
    int32_t v7320 = b_vld10;	// L11458
    bool v7321 = v7320 == 0;	// L11459
    bool v7322 = v7319 & v7321;	// L11460
    bool v7323 = v7317 | v7322;	// L11461
    bool v7324 = v7315 & v7323;	// L11462
    if (v7324) {	// L11463
      grant10 = 0;	// L11464
    }
    int32_t v7325 = grant10;	// L11466
    bool v7326 = v7325 == 1;	// L11467
    if (v7326) {	// L11468
      int32_t v7327 = instr_cnt10;	// L11469
      int32_t v7328 = cfg_isz10;	// L11470
      bool v7329 = v7327 == v7328;	// L11471
      if (v7329) {	// L11472
        instr_cnt10 = 0;	// L11473
        int32_t v7330 = iter_cnt10;	// L11474
        int32_t v7331 = cfg_itsz10;	// L11475
        ap_int<33> v7332 = v7331;	// L11476
        ap_int<33> v7333 = v7332 - 1;	// L11477
        ap_int<33> v7334 = v7330;	// L11478
        bool v7335 = v7334 == v7333;	// L11479
        if (v7335) {	// L11480
          fetch_en10 = 0;	// L11481
        } else {
          int32_t v7336 = iter_cnt10;	// L11483
          ap_int<33> v7337 = v7336;	// L11484
          ap_int<33> v7338 = v7337 + 1;	// L11485
          int32_t v7339 = v7338;	// L11486
          iter_cnt10 = v7339;	// L11487
        }
      } else {
        int32_t v7340 = instr_cnt10;	// L11490
        ap_int<33> v7341 = v7340;	// L11491
        ap_int<33> v7342 = v7341 + 1;	// L11492
        int32_t v7343 = v7342;	// L11493
        instr_cnt10 = v7343;	// L11494
      }
    }
    int32_t c110;	// L11497
    c110 = -1;	// L11498
    int32_t c210;	// L11499
    c210 = -1;	// L11500
    int32_t v7346 = grant10;	// L11501
    bool v7347 = v7346 == 1;	// L11502
    int32_t v7348 = s110;	// L11503
    bool v7349 = v7348 >= 12;	// L11504
    bool v7350 = v7347 & v7349;	// L11505
    if (v7350) {	// L11506
      int32_t v7351 = s110;	// L11507
      int32_t v7352 = v7351 & 3;	// L11508
      c110 = v7352;	// L11509
    }
    int32_t v7353 = grant10;	// L11511
    bool v7354 = v7353 == 1;	// L11512
    int32_t v7355 = s210;	// L11513
    bool v7356 = v7355 >= 12;	// L11514
    bool v7357 = v7354 & v7356;	// L11515
    if (v7357) {	// L11516
      int32_t v7358 = s210;	// L11517
      int32_t v7359 = v7358 & 3;	// L11518
      c210 = v7359;	// L11519
    }
    int32_t v7360 = c110;	// L11521
    bool v7361 = v7360 >= 0;	// L11522
    if (v7361) {	// L11523
      int32_t v7362 = c110;	// L11524
      int v7363 = v7362;	// L11525
      half v7364 = hold_v10[v7363][1];	// L11526
      hold_v10[v7363][0] = v7364;	// L11527
      int32_t v7365 = c110;	// L11528
      int v7366 = v7365;	// L11529
      int32_t v7367 = hold_cnt10[v7366];	// L11530
      ap_int<33> v7368 = v7367;	// L11531
      ap_int<33> v7369 = v7368 - 1;	// L11532
      int32_t v7370 = v7369;	// L11533
      hold_cnt10[v7366] = v7370;	// L11534
    }
    int32_t v7371 = c210;	// L11536
    bool v7372 = v7371 >= 0;	// L11537
    int32_t v7373 = c110;	// L11538
    bool v7374 = v7371 != v7373;	// L11539
    bool v7375 = v7372 & v7374;	// L11540
    if (v7375) {	// L11541
      int32_t v7376 = c210;	// L11542
      int v7377 = v7376;	// L11543
      half v7378 = hold_v10[v7377][1];	// L11544
      hold_v10[v7377][0] = v7378;	// L11545
      int32_t v7379 = c210;	// L11546
      int v7380 = v7379;	// L11547
      int32_t v7381 = hold_cnt10[v7380];	// L11548
      ap_int<33> v7382 = v7381;	// L11549
      ap_int<33> v7383 = v7382 - 1;	// L11550
      int32_t v7384 = v7383;	// L11551
      hold_cnt10[v7380] = v7384;	// L11552
    }
    int32_t v7385 = grant10;	// L11554
    bool v7386 = v7385 == 1;	// L11555
    int32_t v7387 = s110;	// L11556
    bool v7388 = v7387 < 8;	// L11557
    int32_t v7389 = dsmask10;	// L11558
    int32_t v7390 = v7389 >> v7387;	// L11559
    int32_t v7391 = v7390 & 1;	// L11560
    bool v7392 = v7391 == 1;	// L11561
    bool v7393 = v7386 & v7388;	// L11562
    bool v7394 = v7393 & v7392;	// L11563
    if (v7394) {	// L11564
      int32_t v7395 = s110;	// L11565
      int v7396 = v7395;	// L11566
      drf_full10[v7396] = 0;	// L11567
    }
    int32_t v7397 = grant10;	// L11569
    bool v7398 = v7397 == 1;	// L11570
    int32_t v7399 = s210;	// L11571
    bool v7400 = v7399 < 8;	// L11572
    int32_t v7401 = dsmask10;	// L11573
    int32_t v7402 = v7401 >> v7399;	// L11574
    int32_t v7403 = v7402 & 1;	// L11575
    bool v7404 = v7403 == 1;	// L11576
    bool v7405 = v7398 & v7400;	// L11577
    bool v7406 = v7405 & v7404;	// L11578
    if (v7406) {	// L11579
      int32_t v7407 = s210;	// L11580
      int v7408 = v7407;	// L11581
      drf_full10[v7408] = 0;	// L11582
    }
    half res10;	// L11584
    res10 = (double)0.000000;	// L11585
    int32_t v7410 = op10;	// L11586
    bool v7411 = v7410 == 0;	// L11587
    if (v7411) {	// L11588
      half v7412 = a10;	// L11589
      half v7413 = b10;	// L11590
      half v7414 = v7412 + v7413;	// L11591
      res10 = v7414;	// L11592
    } else {
      int32_t v7415 = op10;	// L11594
      bool v7416 = v7415 == 1;	// L11595
      if (v7416) {	// L11596
        half v7417 = a10;	// L11597
        half v7418 = b10;	// L11598
        half v7419 = v7417 - v7418;	// L11599
        res10 = v7419;	// L11600
      } else {
        int32_t v7420 = op10;	// L11602
        bool v7421 = v7420 == 2;	// L11603
        if (v7421) {	// L11604
          half v7422 = a10;	// L11605
          half v7423 = b10;	// L11606
          half v7424 = v7422 * v7423;	// L11607
          res10 = v7424;	// L11608
        } else {
          int32_t v7425 = op10;	// L11610
          bool v7426 = v7425 == 8;	// L11611
          if (v7426) {	// L11612
            half v7427 = a10;	// L11613
            half v7428 = b10;	// L11614
            bool v7429 = v7427 >= v7428;	// L11615
            if (v7429) {	// L11616
              res10 = (double)1.000000;	// L11617
            } else {
              res10 = (double)-1.000000;	// L11619
            }
          } else {
            int32_t v7430 = op10;	// L11622
            bool v7431 = v7430 == 9;	// L11623
            if (v7431) {	// L11624
              half v7432 = a10;	// L11625
              half v7433 = b10;	// L11626
              bool v7434 = v7432 < v7433;	// L11627
              if (v7434) {	// L11628
                res10 = (double)1.000000;	// L11629
              } else {
                res10 = (double)-1.000000;	// L11631
              }
            } else {
              half v7435 = a10;	// L11634
              res10 = v7435;	// L11635
            }
          }
        }
      }
    }
    int32_t v7436 = a_vld10;	// L11641
    int32_t res_vld10;	// L11642
    res_vld10 = v7436;	// L11643
    int32_t v7438 = op10;	// L11644
    bool v7439 = v7438 == 0;	// L11645
    bool v7440 = v7438 == 1;	// L11646
    bool v7441 = v7438 == 2;	// L11647
    bool v7442 = v7438 == 8;	// L11648
    bool v7443 = v7438 == 9;	// L11649
    bool v7444 = v7439 | v7440;	// L11650
    bool v7445 = v7444 | v7441;	// L11651
    bool v7446 = v7445 | v7442;	// L11652
    bool v7447 = v7446 | v7443;	// L11653
    if (v7447) {	// L11654
      int32_t v7448 = a_vld10;	// L11655
      int32_t v7449 = b_vld10;	// L11656
      int64_t v7450 = v7448;	// L11657
      int64_t v7451 = v7449;	// L11658
      int64_t v7452 = v7450 * v7451;	// L11659
      int32_t v7453 = v7452;	// L11660
      res_vld10 = v7453;	// L11661
    }
    int32_t v7454 = grant10;	// L11663
    bool v7455 = v7454 == 0;	// L11664
    if (v7455) {	// L11665
      res_vld10 = 0;	// L11666
    }
    int32_t v7456 = grant10;	// L11668
    bool v7457 = v7456 == 1;	// L11669
    int32_t v7458 = op10;	// L11670
    bool v7459 = v7458 == 8;	// L11671
    bool v7460 = v7457 & v7459;	// L11672
    if (v7460) {	// L11673
      condition_reg10 = 0;	// L11674
      half v7461 = a10;	// L11675
      half v7462 = b10;	// L11676
      bool v7463 = v7461 >= v7462;	// L11677
      if (v7463) {	// L11678
        condition_reg10 = 1;	// L11679
      }
    }
    int32_t v7464 = grant10;	// L11682
    bool v7465 = v7464 == 1;	// L11683
    int32_t v7466 = op10;	// L11684
    bool v7467 = v7466 == 9;	// L11685
    bool v7468 = v7465 & v7467;	// L11686
    if (v7468) {	// L11687
      condition_reg10 = 0;	// L11688
      half v7469 = a10;	// L11689
      half v7470 = b10;	// L11690
      bool v7471 = v7469 < v7470;	// L11691
      if (v7471) {	// L11692
        condition_reg10 = 1;	// L11693
      }
    }
    ap_uint<17> tx_n10;	// L11696
    tx_n10 = 0;	// L11697
    ap_uint<17> tx_s10;	// L11698
    tx_s10 = 0;	// L11699
    ap_uint<17> tx_w10;	// L11700
    tx_w10 = 0;	// L11701
    ap_uint<17> tx_e10;	// L11702
    tx_e10 = 0;	// L11703
    int32_t is_rtr10;	// L11704
    is_rtr10 = 0;	// L11705
    int32_t do_inj10;	// L11706
    do_inj10 = 0;	// L11707
    int32_t v7478 = op10;	// L11708
    bool v7479 = v7478 >= 4;	// L11709
    ap_int<33> v7480 = v7478;	// L11710
    bool v7481 = v7480 <= 7;	// L11711
    bool v7482 = v7479 & v7481;	// L11712
    if (v7482) {	// L11713
      is_rtr10 = 1;	// L11714
      do_inj10 = 1;	// L11715
    }
    int32_t v7483 = op10;	// L11717
    bool v7484 = v7483 >= 12;	// L11718
    ap_int<33> v7485 = v7483;	// L11719
    bool v7486 = v7485 <= 15;	// L11720
    bool v7487 = v7484 & v7486;	// L11721
    if (v7487) {	// L11722
      is_rtr10 = 1;	// L11723
      int32_t v7488 = condition_reg10;	// L11724
      bool v7489 = v7488 == 1;	// L11725
      if (v7489) {	// L11726
        do_inj10 = 1;	// L11727
      }
    }
    int32_t v7490 = is_rtr10;	// L11730
    bool v7491 = v7490 == 1;	// L11731
    if (v7491) {	// L11732
      int32_t v7492 = do_inj10;	// L11733
      bool v7493 = v7492 == 1;	// L11734
      ap_int<26> v7494 = csd_pkt10;	// L11735
      bool v7495;
      ap_int<26> v7495_tmp = v7494;
      v7495 = v7495_tmp[25];	// L11736
      int32_t v7496 = v7495;	// L11737
      bool v7497 = v7496 == 0;	// L11738
      bool v7498 = v7493 & v7497;	// L11739
      if (v7498) {	// L11740
        half v7499 = res10;	// L11741
        uint16_t v7500;
        union { half from; uint16_t to;} _converter_v7499_to_v7500;
        _converter_v7499_to_v7500.from = v7499;
        v7500 = _converter_v7499_to_v7500.to;	// L11742
        ap_int<26> v7501 = csd_pkt10;	// L11743
        ap_int<26> v7502;
        ap_int<26> v7502_tmp = v7501;
        v7502_tmp(15, 0) = v7500;
        v7502 = v7502_tmp;	// L11744
        csd_pkt10 = v7502;	// L11745
        int32_t v7503 = dst10;	// L11746
        ap_uint<4> v7504 = v7503;	// L11747
        ap_int<26> v7505 = csd_pkt10;	// L11748
        ap_int<26> v7506;
        ap_int<26> v7506_tmp = v7505;
        v7506_tmp(19, 16) = v7504;
        v7506 = v7506_tmp;	// L11749
        csd_pkt10 = v7506;	// L11750
        int32_t v7507 = s210;	// L11751
        ap_uint<4> v7508 = v7507;	// L11752
        ap_int<26> v7509 = csd_pkt10;	// L11753
        ap_int<26> v7510;
        ap_int<26> v7510_tmp = v7509;
        v7510_tmp(24, 21) = v7508;
        v7510 = v7510_tmp;	// L11754
        csd_pkt10 = v7510;	// L11755
        int32_t v7511 = res_vld10;	// L11756
        bool v7512 = v7511;	// L11757
        ap_int<26> v7513 = csd_pkt10;	// L11758
        ap_int<26> v7514;
        ap_int<26> v7514_tmp = v7513;
        v7514_tmp[25] = v7512;        v7514 = v7514_tmp;	// L11759
        csd_pkt10 = v7514;	// L11760
        int32_t v7515 = op10;	// L11761
        int32_t v7516 = v7515 & 3;	// L11762
        csd_dir10 = v7516;	// L11763
      }
    } else {
      int32_t v7517 = dst10;	// L11766
      bool v7518 = v7517 >= 12;	// L11767
      if (v7518) {	// L11768
        ap_uint<17> tw10;	// L11769
        tw10 = 0;	// L11770
        int32_t v7520 = res_vld10;	// L11771
        bool v7521 = v7520;	// L11772
        ap_int<17> v7522 = tw10;	// L11773
        ap_int<17> v7523;
        ap_int<17> v7523_tmp = v7522;
        v7523_tmp[0] = v7521;        v7523 = v7523_tmp;	// L11774
        tw10 = v7523;	// L11775
        half v7524 = res10;	// L11776
        uint16_t v7525;
        union { half from; uint16_t to;} _converter_v7524_to_v7525;
        _converter_v7524_to_v7525.from = v7524;
        v7525 = _converter_v7524_to_v7525.to;	// L11777
        ap_int<17> v7526 = tw10;	// L11778
        ap_int<17> v7527;
        ap_int<17> v7527_tmp = v7526;
        v7527_tmp(16, 1) = v7525;
        v7527 = v7527_tmp;	// L11779
        tw10 = v7527;	// L11780
        int32_t v7528 = dst10;	// L11781
        int32_t v7529 = v7528 & 3;	// L11782
        bool v7530 = v7529 == 0;	// L11783
        if (v7530) {	// L11784
          ap_int<17> v7531 = tw10;	// L11785
          tx_n10 = v7531;	// L11786
        } else {
          int32_t v7532 = dst10;	// L11788
          int32_t v7533 = v7532 & 3;	// L11789
          bool v7534 = v7533 == 1;	// L11790
          if (v7534) {	// L11791
            ap_int<17> v7535 = tw10;	// L11792
            tx_s10 = v7535;	// L11793
          } else {
            int32_t v7536 = dst10;	// L11795
            int32_t v7537 = v7536 & 3;	// L11796
            bool v7538 = v7537 == 2;	// L11797
            if (v7538) {	// L11798
              ap_int<17> v7539 = tw10;	// L11799
              tx_w10 = v7539;	// L11800
            } else {
              ap_int<17> v7540 = tw10;	// L11802
              tx_e10 = v7540;	// L11803
            }
          }
        }
      } else {
        int32_t v7541 = res_vld10;	// L11808
        bool v7542 = v7541 == 1;	// L11809
        if (v7542) {	// L11810
          int32_t v7543 = dst10;	// L11811
          bool v7544 = v7543 < 8;	// L11812
          int32_t v7545 = dsmask10;	// L11813
          int32_t v7546 = v7545 >> v7543;	// L11814
          int32_t v7547 = v7546 & 1;	// L11815
          bool v7548 = v7547 == 1;	// L11816
          bool v7549 = v7544 & v7548;	// L11817
          if (v7549) {	// L11818
            int32_t v7550 = dst10;	// L11819
            int v7551 = v7550;	// L11820
            int32_t v7552 = drf_full10[v7551];	// L11821
            bool v7553 = v7552 == 0;	// L11822
            if (v7553) {	// L11823
              half v7554 = res10;	// L11824
              int32_t v7555 = dst10;	// L11825
              int v7556 = v7555;	// L11826
              drf10[v7556] = v7554;	// L11827
              int32_t v7557 = dst10;	// L11828
              int v7558 = v7557;	// L11829
              drf_full10[v7558] = 1;	// L11830
            }
          } else {
            half v7559 = res10;	// L11833
            int32_t v7560 = dst10;	// L11834
            int v7561 = v7560;	// L11835
            drf10[v7561] = v7559;	// L11836
          }
        }
      }
    }
    ap_int<17> v7562 = tx_n10;	// L11841
    txn_r10 = v7562;	// L11842
    ap_int<17> v7563 = tx_s10;	// L11843
    txs_r10 = v7563;	// L11844
    ap_int<17> v7564 = tx_w10;	// L11845
    txw_r10 = v7564;	// L11846
    ap_int<17> v7565 = tx_e10;	// L11847
    txe_r10 = v7565;	// L11848
    int32_t v7566 = crv_vld10;	// L11849
    bool v7567 = v7566 == 1;	// L11850
    if (v7567) {	// L11851
      int32_t v7568 = crv_mode10;	// L11852
      bool v7569 = v7568 == 1;	// L11853
      if (v7569) {	// L11854
        int32_t v7570 = crv_addr10;	// L11855
        int32_t v7571 = v7570 >> 3;	// L11856
        int32_t v7572 = v7571 & 1;	// L11857
        bool v7573 = v7572 == 1;	// L11858
        if (v7573) {	// L11859
          int32_t v7574 = crv_raw10;	// L11860
          int32_t v7575 = crv_addr10;	// L11861
          int32_t v7576 = v7575 & 7;	// L11862
          int v7577 = v7576;	// L11863
          irf10[v7577] = v7574;	// L11864
        } else {
          int32_t v7578 = crv_addr10;	// L11866
          bool v7579 = v7578 == 0;	// L11867
          if (v7579) {	// L11868
            int32_t v7580 = crv_raw10;	// L11869
            int32_t v7581 = v7580 & 255;	// L11870
            dsmask10 = v7581;	// L11871
            int32_t v7582 = crv_raw10;	// L11872
            int32_t v7583 = v7582 >> 8;	// L11873
            int32_t v7584 = v7583 & 7;	// L11874
            cfg_isz10 = v7584;	// L11875
            int32_t v7585 = crv_raw10;	// L11876
            int32_t v7586 = v7585 >> 15;	// L11877
            int32_t v7587 = v7586 & 1;	// L11878
            bool v7588 = v7587 == 1;	// L11879
            if (v7588) {	// L11880
              fetch_en10 = 1;	// L11881
              instr_cnt10 = 0;	// L11882
              iter_cnt10 = 0;	// L11883
            }
          } else {
            int32_t v7589 = crv_addr10;	// L11886
            bool v7590 = v7589 == 1;	// L11887
            if (v7590) {	// L11888
              int32_t v7591 = crv_raw10;	// L11889
              int32_t v7592 = v7591 & 255;	// L11890
              cfg_itsz10 = v7592;	// L11891
            }
          }
        }
      } else {
        int32_t v7593 = crv_addr10;	// L11896
        bool v7594 = v7593 < 8;	// L11897
        int32_t v7595 = dsmask10;	// L11898
        int32_t v7596 = v7595 >> v7593;	// L11899
        int32_t v7597 = v7596 & 1;	// L11900
        bool v7598 = v7597 == 1;	// L11901
        bool v7599 = v7594 & v7598;	// L11902
        if (v7599) {	// L11903
          int32_t v7600 = crv_addr10;	// L11904
          int v7601 = v7600;	// L11905
          int32_t v7602 = drf_full10[v7601];	// L11906
          bool v7603 = v7602 == 0;	// L11907
          if (v7603) {	// L11908
            half v7604 = crv_data10;	// L11909
            int32_t v7605 = crv_addr10;	// L11910
            int v7606 = v7605;	// L11911
            drf10[v7606] = v7604;	// L11912
            int32_t v7607 = crv_addr10;	// L11913
            int v7608 = v7607;	// L11914
            drf_full10[v7608] = 1;	// L11915
          }
        } else {
          half v7609 = crv_data10;	// L11918
          int32_t v7610 = crv_addr10;	// L11919
          int v7611 = v7610;	// L11920
          drf10[v7611] = v7609;	// L11921
        }
      }
    }
  }
}

void node_2_3(
  hls::stream< ap_uint<26> >& v7612,
  hls::stream< ap_uint<26> >& v7613,
  hls::stream< ap_uint<26> >& v7614,
  hls::stream< ap_uint<26> >& v7615,
  hls::stream< ap_uint<17> >& v7616,
  hls::stream< ap_uint<17> >& v7617,
  hls::stream< ap_uint<17> >& v7618,
  hls::stream< ap_uint<17> >& v7619,
  hls::stream< int32_t >& v7620,
  hls::stream< int32_t >& v7621,
  hls::stream< int32_t >& v7622,
  hls::stream< int32_t >& v7623,
  hls::stream< ap_uint<26> >& v7624,
  hls::stream< ap_uint<26> >& v7625,
  hls::stream< ap_uint<26> >& v7626,
  hls::stream< ap_uint<26> >& v7627,
  hls::stream< int32_t >& v7628,
  hls::stream< int32_t >& v7629,
  hls::stream< int32_t >& v7630,
  hls::stream< int32_t >& v7631,
  hls::stream< ap_uint<17> >& v7632,
  hls::stream< ap_uint<17> >& v7633,
  hls::stream< ap_uint<17> >& v7634,
  hls::stream< ap_uint<17> >& v7635
) {	// L11928
  int32_t irf11[8];	// L11959
  for (int v7637 = 0; v7637 < 8; v7637++) {	// L11960
    irf11[v7637] = 0;	// L11960
  }
  half drf11[8];	// L11961
  #pragma HLS array_partition variable=drf11 complete dim=1

  for (int v7639 = 0; v7639 < 8; v7639++) {	// L11962
    drf11[v7639] = (double)0.000000;	// L11962
  }
  int32_t drf_full11[8];	// L11963
  #pragma HLS array_partition variable=drf_full11 complete dim=1

  for (int v7641 = 0; v7641 < 8; v7641++) {	// L11964
    drf_full11[v7641] = 0;	// L11964
  }
  int32_t dsmask11;	// L11965
  dsmask11 = 0;	// L11966
  int32_t crv_vld11;	// L11967
  crv_vld11 = 0;	// L11968
  half crv_data11;	// L11969
  crv_data11 = (double)0.000000;	// L11970
  int32_t crv_addr11;	// L11971
  crv_addr11 = 0;	// L11972
  int32_t crv_mode11;	// L11973
  crv_mode11 = 0;	// L11974
  int32_t crv_raw11;	// L11975
  crv_raw11 = 0;	// L11976
  int32_t csd_vld11;	// L11977
  csd_vld11 = 0;	// L11978
  ap_uint<26> csd_pkt11;	// L11979
  csd_pkt11 = 0;	// L11980
  int32_t csd_dir11;	// L11981
  csd_dir11 = 0;	// L11982
  int32_t row_id11;	// L11983
  row_id11 = 2;	// L11984
  int32_t col_id11;	// L11985
  col_id11 = 3;	// L11986
  ap_uint<26> oe_r11;	// L11987
  oe_r11 = 0;	// L11988
  ap_uint<26> ow_r11;	// L11989
  ow_r11 = 0;	// L11990
  ap_uint<26> on_r11;	// L11991
  on_r11 = 0;	// L11992
  ap_uint<26> os_r11;	// L11993
  os_r11 = 0;	// L11994
  ap_uint<17> txn_r11;	// L11995
  txn_r11 = 0;	// L11996
  ap_uint<17> txs_r11;	// L11997
  txs_r11 = 0;	// L11998
  ap_uint<17> txw_r11;	// L11999
  txw_r11 = 0;	// L12000
  ap_uint<17> txe_r11;	// L12001
  txe_r11 = 0;	// L12002
  half hold_v11[4][2];	// L12003
  #pragma HLS array_partition variable=hold_v11 complete dim=1
  #pragma HLS array_partition variable=hold_v11 complete dim=2

  for (int v7662 = 0; v7662 < 4; v7662++) {	// L12004
    for (int v7663 = 0; v7663 < 2; v7663++) {	// L12004
      hold_v11[v7662][v7663] = (double)0.000000;	// L12004
    }
  }
  int32_t hold_cnt11[4];	// L12005
  #pragma HLS array_partition variable=hold_cnt11 complete dim=1

  for (int v7665 = 0; v7665 < 4; v7665++) {	// L12006
    hold_cnt11[v7665] = 0;	// L12006
  }
  ap_uint<26> rbuf11[4][2];	// L12007
  #pragma HLS array_partition variable=rbuf11 complete dim=1
  #pragma HLS array_partition variable=rbuf11 complete dim=2

  for (int v7667 = 0; v7667 < 4; v7667++) {	// L12008
    for (int v7668 = 0; v7668 < 2; v7668++) {	// L12008
      rbuf11[v7667][v7668] = 0;	// L12008
    }
  }
  int32_t rbcnt11[4];	// L12009
  #pragma HLS array_partition variable=rbcnt11 complete dim=1

  for (int v7670 = 0; v7670 < 4; v7670++) {	// L12010
    rbcnt11[v7670] = 0;	// L12010
  }
  int32_t rcred11[4];	// L12011
  #pragma HLS array_partition variable=rcred11 complete dim=1

  for (int v7672 = 0; v7672 < 4; v7672++) {	// L12012
    rcred11[v7672] = 0;	// L12012
  }
  int32_t cre_r11;	// L12013
  cre_r11 = 2;	// L12014
  int32_t crw_r11;	// L12015
  crw_r11 = 2;	// L12016
  int32_t crs_r11;	// L12017
  crs_r11 = 2;	// L12018
  int32_t crn_r11;	// L12019
  crn_r11 = 2;	// L12020
  int32_t cfg_isz11;	// L12021
  cfg_isz11 = 0;	// L12022
  int32_t cfg_itsz11;	// L12023
  cfg_itsz11 = 0;	// L12024
  int32_t fetch_en11;	// L12025
  fetch_en11 = 0;	// L12026
  int32_t instr_cnt11;	// L12027
  instr_cnt11 = 0;	// L12028
  int32_t iter_cnt11;	// L12029
  iter_cnt11 = 0;	// L12030
  int32_t condition_reg11;	// L12031
  condition_reg11 = 0;	// L12032
  l_S_t_0_t11: for (int t11 = 0; t11 < 8; t11++) {	// L12033
  #pragma HLS pipeline II=1
    ap_int<26> v7684 = oe_r11;	// L12034
    v7612.write(v7684);	// L12035
    ap_int<26> v7685 = ow_r11;	// L12036
    v7613.write(v7685);	// L12037
    ap_int<26> v7686 = os_r11;	// L12038
    v7614.write(v7686);	// L12039
    ap_int<26> v7687 = on_r11;	// L12040
    v7615.write(v7687);	// L12041
    ap_int<17> v7688 = txe_r11;	// L12042
    v7616.write(v7688);	// L12043
    ap_int<17> v7689 = txw_r11;	// L12044
    v7617.write(v7689);	// L12045
    ap_int<17> v7690 = txs_r11;	// L12046
    v7618.write(v7690);	// L12047
    ap_int<17> v7691 = txn_r11;	// L12048
    v7619.write(v7691);	// L12049
    int32_t v7692 = cre_r11;	// L12050
    v7620.write(v7692);	// L12051
    int32_t v7693 = crw_r11;	// L12052
    v7621.write(v7693);	// L12053
    int32_t v7694 = crs_r11;	// L12054
    v7622.write(v7694);	// L12055
    int32_t v7695 = crn_r11;	// L12056
    v7623.write(v7695);	// L12057
    ap_uint<26> v7696 = v7624.read();	// L12058
    ap_uint<26> p_w11;	// L12059
    p_w11 = v7696;	// L12060
    ap_uint<26> v7698 = v7625.read();	// L12061
    ap_uint<26> p_e11;	// L12062
    p_e11 = v7698;	// L12063
    ap_uint<26> v7700 = v7626.read();	// L12064
    ap_uint<26> p_n11;	// L12065
    p_n11 = v7700;	// L12066
    ap_uint<26> v7702 = v7627.read();	// L12067
    ap_uint<26> p_s11;	// L12068
    p_s11 = v7702;	// L12069
    int32_t v7704 = v7628.read();	// L12070
    int32_t v7705 = rcred11[0];	// L12071
    ap_int<33> v7706 = v7705;	// L12072
    ap_int<33> v7707 = v7704;	// L12073
    ap_int<33> v7708 = v7706 + v7707;	// L12074
    int32_t v7709 = v7708;	// L12075
    rcred11[0] = v7709;	// L12076
    int32_t v7710 = v7629.read();	// L12077
    int32_t v7711 = rcred11[1];	// L12078
    ap_int<33> v7712 = v7711;	// L12079
    ap_int<33> v7713 = v7710;	// L12080
    ap_int<33> v7714 = v7712 + v7713;	// L12081
    int32_t v7715 = v7714;	// L12082
    rcred11[1] = v7715;	// L12083
    int32_t v7716 = v7630.read();	// L12084
    int32_t v7717 = rcred11[2];	// L12085
    ap_int<33> v7718 = v7717;	// L12086
    ap_int<33> v7719 = v7716;	// L12087
    ap_int<33> v7720 = v7718 + v7719;	// L12088
    int32_t v7721 = v7720;	// L12089
    rcred11[2] = v7721;	// L12090
    int32_t v7722 = v7631.read();	// L12091
    int32_t v7723 = rcred11[3];	// L12092
    ap_int<33> v7724 = v7723;	// L12093
    ap_int<33> v7725 = v7722;	// L12094
    ap_int<33> v7726 = v7724 + v7725;	// L12095
    int32_t v7727 = v7726;	// L12096
    rcred11[3] = v7727;	// L12097
    ap_uint<26> fin11[4];	// L12098
    for (int v7729 = 0; v7729 < 4; v7729++) {	// L12099
      fin11[v7729] = 0;	// L12099
    }
    ap_int<26> v7730 = p_w11;	// L12100
    fin11[0] = v7730;	// L12101
    ap_int<26> v7731 = p_e11;	// L12102
    fin11[1] = v7731;	// L12103
    ap_int<26> v7732 = p_n11;	// L12104
    fin11[2] = v7732;	// L12105
    ap_int<26> v7733 = p_s11;	// L12106
    fin11[3] = v7733;	// L12107
    l_S_d_0_d44: for (int d44 = 0; d44 < 4; d44++) {	// L12108
      ap_uint<26> v7735 = fin11[d44];	// L12109
      bool v7736;
      ap_int<26> v7736_tmp = v7735;
      v7736 = v7736_tmp[25];	// L12110
      int32_t v7737 = v7736;	// L12111
      bool v7738 = v7737 == 1;	// L12112
      int32_t v7739 = rbcnt11[d44];	// L12113
      bool v7740 = v7739 < 2;	// L12114
      bool v7741 = v7738 & v7740;	// L12115
      if (v7741) {	// L12116
        ap_uint<26> v7742 = fin11[d44];	// L12117
        int32_t v7743 = rbcnt11[d44];	// L12118
        int v7744 = v7743;	// L12119
        rbuf11[d44][v7744] = v7742;	// L12120
        int32_t v7745 = rbcnt11[d44];	// L12121
        ap_int<33> v7746 = v7745;	// L12122
        ap_int<33> v7747 = v7746 + 1;	// L12123
        int32_t v7748 = v7747;	// L12124
        rbcnt11[d44] = v7748;	// L12125
      }
    }
    ap_uint<26> hd11[4];	// L12128
    for (int v7750 = 0; v7750 < 4; v7750++) {	// L12129
      hd11[v7750] = 0;	// L12129
    }
    int32_t hvld11[4];	// L12130
    for (int v7752 = 0; v7752 < 4; v7752++) {	// L12131
      hvld11[v7752] = 0;	// L12131
    }
    int32_t hit11[4];	// L12132
    for (int v7754 = 0; v7754 < 4; v7754++) {	// L12133
      hit11[v7754] = 0;	// L12133
    }
    int32_t axis11[4];	// L12134
    for (int v7756 = 0; v7756 < 4; v7756++) {	// L12135
      axis11[v7756] = 0;	// L12135
    }
    int32_t v7757 = col_id11;	// L12136
    axis11[0] = v7757;	// L12137
    int32_t v7758 = col_id11;	// L12138
    axis11[1] = v7758;	// L12139
    int32_t v7759 = row_id11;	// L12140
    axis11[2] = v7759;	// L12141
    int32_t v7760 = row_id11;	// L12142
    axis11[3] = v7760;	// L12143
    l_S_d_1_d45: for (int d45 = 0; d45 < 4; d45++) {	// L12144
      int32_t v7762 = rbcnt11[d45];	// L12145
      bool v7763 = v7762 > 0;	// L12146
      if (v7763) {	// L12147
        ap_uint<26> v7764 = rbuf11[d45][0];	// L12148
        hd11[d45] = v7764;	// L12149
        hvld11[d45] = 1;	// L12150
        ap_uint<26> v7765 = hd11[d45];	// L12151
        ap_int<4> v7766;
        ap_int<26> v7766_tmp = v7765;
        v7766 = v7766_tmp(24, 21);	// L12152
        int32_t v7767 = axis11[d45];	// L12153
        int32_t v7768 = v7766;	// L12154
        bool v7769 = v7768 == v7767;	// L12155
        if (v7769) {	// L12156
          hit11[d45] = 1;	// L12157
        }
      }
    }
    ap_uint<26> o_crv11;	// L12161
    o_crv11 = 0;	// L12162
    int32_t crv_in11;	// L12163
    crv_in11 = -1;	// L12164
    int32_t v7772 = hit11[3];	// L12165
    bool v7773 = v7772 == 1;	// L12166
    if (v7773) {	// L12167
      ap_uint<26> v7774 = hd11[3];	// L12168
      o_crv11 = v7774;	// L12169
      crv_in11 = 3;	// L12170
    } else {
      int32_t v7775 = hit11[2];	// L12172
      bool v7776 = v7775 == 1;	// L12173
      if (v7776) {	// L12174
        ap_uint<26> v7777 = hd11[2];	// L12175
        o_crv11 = v7777;	// L12176
        crv_in11 = 2;	// L12177
      } else {
        int32_t v7778 = hit11[1];	// L12179
        bool v7779 = v7778 == 1;	// L12180
        if (v7779) {	// L12181
          ap_uint<26> v7780 = hd11[1];	// L12182
          o_crv11 = v7780;	// L12183
          crv_in11 = 1;	// L12184
        } else {
          int32_t v7781 = hit11[0];	// L12186
          bool v7782 = v7781 == 1;	// L12187
          if (v7782) {	// L12188
            ap_uint<26> v7783 = hd11[0];	// L12189
            o_crv11 = v7783;	// L12190
            crv_in11 = 0;	// L12191
          }
        }
      }
    }
    ap_uint<26> o_out11[4];	// L12196
    for (int v7785 = 0; v7785 < 4; v7785++) {	// L12197
      o_out11[v7785] = 0;	// L12197
    }
    int32_t pop11[4];	// L12198
    for (int v7787 = 0; v7787 < 4; v7787++) {	// L12199
      pop11[v7787] = 0;	// L12199
    }
    int32_t inj_done11;	// L12200
    inj_done11 = 0;	// L12201
    int32_t idir11;	// L12202
    idir11 = -1;	// L12203
    ap_int<26> v7790 = csd_pkt11;	// L12204
    bool v7791;
    ap_int<26> v7791_tmp = v7790;
    v7791 = v7791_tmp[25];	// L12205
    int32_t v7792 = v7791;	// L12206
    bool v7793 = v7792 == 1;	// L12207
    if (v7793) {	// L12208
      int32_t v7794 = csd_dir11;	// L12209
      ap_int<33> v7795 = v7794;	// L12210
      ap_int<33> v7796 = 3 - v7795;	// L12211
      int32_t v7797 = v7796;	// L12212
      idir11 = v7797;	// L12213
    }
    l_S_o_2_o11: for (int o11 = 0; o11 < 4; o11++) {	// L12215
      int32_t v7799 = rcred11[o11];	// L12216
      bool v7800 = v7799 > 0;	// L12217
      if (v7800) {	// L12218
        int32_t v7801 = idir11;	// L12219
        ap_int<33> v7802 = v7801;	// L12220
        ap_int<33> v7803 = o11;	// L12221
        bool v7804 = v7802 == v7803;	// L12222
        if (v7804) {	// L12223
          ap_int<26> v7805 = csd_pkt11;	// L12224
          o_out11[o11] = v7805;	// L12225
          int32_t v7806 = rcred11[o11];	// L12226
          ap_int<33> v7807 = v7806;	// L12227
          ap_int<33> v7808 = v7807 - 1;	// L12228
          int32_t v7809 = v7808;	// L12229
          rcred11[o11] = v7809;	// L12230
          inj_done11 = 1;	// L12231
        } else {
          int32_t v7810 = hvld11[o11];	// L12233
          bool v7811 = v7810 == 1;	// L12234
          int32_t v7812 = hit11[o11];	// L12235
          bool v7813 = v7812 == 0;	// L12236
          bool v7814 = v7811 & v7813;	// L12237
          if (v7814) {	// L12238
            ap_uint<26> v7815 = hd11[o11];	// L12239
            o_out11[o11] = v7815;	// L12240
            int32_t v7816 = rcred11[o11];	// L12241
            ap_int<33> v7817 = v7816;	// L12242
            ap_int<33> v7818 = v7817 - 1;	// L12243
            int32_t v7819 = v7818;	// L12244
            rcred11[o11] = v7819;	// L12245
            pop11[o11] = 1;	// L12246
          }
        }
      }
    }
    int32_t v7820 = crv_in11;	// L12251
    bool v7821 = v7820 >= 0;	// L12252
    if (v7821) {	// L12253
      int32_t v7822 = crv_in11;	// L12254
      int v7823 = v7822;	// L12255
      pop11[v7823] = 1;	// L12256
    }
    int32_t ret11[4];	// L12258
    for (int v7825 = 0; v7825 < 4; v7825++) {	// L12259
      ret11[v7825] = 0;	// L12259
    }
    l_S_d_3_d46: for (int d46 = 0; d46 < 4; d46++) {	// L12260
      int32_t v7827 = pop11[d46];	// L12261
      bool v7828 = v7827 == 1;	// L12262
      if (v7828) {	// L12263
        l_S_sft_3_sft11: for (int sft11 = 0; sft11 < 1; sft11++) {	// L12264
          ap_uint<26> v7830 = rbuf11[d46][(sft11 + 1)];	// L12265
          rbuf11[d46][sft11] = v7830;	// L12266
        }
        int32_t v7831 = rbcnt11[d46];	// L12268
        ap_int<33> v7832 = v7831;	// L12269
        ap_int<33> v7833 = v7832 - 1;	// L12270
        int32_t v7834 = v7833;	// L12271
        rbcnt11[d46] = v7834;	// L12272
        ret11[d46] = 1;	// L12273
      }
    }
    int32_t v7835 = ret11[0];	// L12276
    cre_r11 = v7835;	// L12277
    int32_t v7836 = ret11[1];	// L12278
    crw_r11 = v7836;	// L12279
    int32_t v7837 = ret11[2];	// L12280
    crs_r11 = v7837;	// L12281
    int32_t v7838 = ret11[3];	// L12282
    crn_r11 = v7838;	// L12283
    ap_uint<26> v7839 = o_out11[0];	// L12284
    oe_r11 = v7839;	// L12285
    ap_uint<26> v7840 = o_out11[1];	// L12286
    ow_r11 = v7840;	// L12287
    ap_uint<26> v7841 = o_out11[2];	// L12288
    os_r11 = v7841;	// L12289
    ap_uint<26> v7842 = o_out11[3];	// L12290
    on_r11 = v7842;	// L12291
    int32_t v7843 = inj_done11;	// L12292
    bool v7844 = v7843 == 1;	// L12293
    if (v7844) {	// L12294
      csd_pkt11 = 0;	// L12295
    }
    ap_int<26> v7845 = o_crv11;	// L12297
    bool v7846;
    ap_int<26> v7846_tmp = v7845;
    v7846 = v7846_tmp[25];	// L12298
    int32_t v7847 = v7846;	// L12299
    crv_vld11 = v7847;	// L12300
    ap_int<26> v7848 = o_crv11;	// L12301
    int16_t v7849;
    ap_int<26> v7849_tmp = v7848;
    v7849 = v7849_tmp(15, 0);	// L12302
    half v7850;
    union { uint16_t from; half to;} _converter_v7849_to_v7850;
    _converter_v7849_to_v7850.from = v7849;
    v7850 = _converter_v7849_to_v7850.to;	// L12303
    crv_data11 = v7850;	// L12304
    ap_int<26> v7851 = o_crv11;	// L12305
    ap_int<4> v7852;
    ap_int<26> v7852_tmp = v7851;
    v7852 = v7852_tmp(19, 16);	// L12306
    int32_t v7853 = v7852;	// L12307
    crv_addr11 = v7853;	// L12308
    ap_int<26> v7854 = o_crv11;	// L12309
    bool v7855;
    ap_int<26> v7855_tmp = v7854;
    v7855 = v7855_tmp[20];	// L12310
    int32_t v7856 = v7855;	// L12311
    crv_mode11 = v7856;	// L12312
    ap_int<26> v7857 = o_crv11;	// L12313
    int16_t v7858;
    ap_int<26> v7858_tmp = v7857;
    v7858 = v7858_tmp(15, 0);	// L12314
    int32_t v7859 = v7858;	// L12315
    crv_raw11 = v7859;	// L12316
    ap_uint<17> v7860 = v7632.read();	// L12317
    ap_uint<17> rx_w11;	// L12318
    rx_w11 = v7860;	// L12319
    ap_uint<17> v7862 = v7633.read();	// L12320
    ap_uint<17> rx_e11;	// L12321
    rx_e11 = v7862;	// L12322
    ap_uint<17> v7864 = v7634.read();	// L12323
    ap_uint<17> rx_n11;	// L12324
    rx_n11 = v7864;	// L12325
    ap_uint<17> v7866 = v7635.read();	// L12326
    ap_uint<17> rx_s11;	// L12327
    rx_s11 = v7866;	// L12328
    half rxv11[4];	// L12329
    for (int v7869 = 0; v7869 < 4; v7869++) {	// L12330
      rxv11[v7869] = (double)0.000000;	// L12330
    }
    int32_t rxvld11[4];	// L12331
    for (int v7871 = 0; v7871 < 4; v7871++) {	// L12332
      rxvld11[v7871] = 0;	// L12332
    }
    ap_int<17> v7872 = rx_n11;	// L12333
    int16_t v7873;
    ap_int<17> v7873_tmp = v7872;
    v7873 = v7873_tmp(16, 1);	// L12334
    half v7874;
    union { uint16_t from; half to;} _converter_v7873_to_v7874;
    _converter_v7873_to_v7874.from = v7873;
    v7874 = _converter_v7873_to_v7874.to;	// L12335
    rxv11[0] = v7874;	// L12336
    ap_int<17> v7875 = rx_n11;	// L12337
    bool v7876;
    ap_int<17> v7876_tmp = v7875;
    v7876 = v7876_tmp[0];	// L12338
    int32_t v7877 = v7876;	// L12339
    rxvld11[0] = v7877;	// L12340
    ap_int<17> v7878 = rx_s11;	// L12341
    int16_t v7879;
    ap_int<17> v7879_tmp = v7878;
    v7879 = v7879_tmp(16, 1);	// L12342
    half v7880;
    union { uint16_t from; half to;} _converter_v7879_to_v7880;
    _converter_v7879_to_v7880.from = v7879;
    v7880 = _converter_v7879_to_v7880.to;	// L12343
    rxv11[1] = v7880;	// L12344
    ap_int<17> v7881 = rx_s11;	// L12345
    bool v7882;
    ap_int<17> v7882_tmp = v7881;
    v7882 = v7882_tmp[0];	// L12346
    int32_t v7883 = v7882;	// L12347
    rxvld11[1] = v7883;	// L12348
    ap_int<17> v7884 = rx_w11;	// L12349
    int16_t v7885;
    ap_int<17> v7885_tmp = v7884;
    v7885 = v7885_tmp(16, 1);	// L12350
    half v7886;
    union { uint16_t from; half to;} _converter_v7885_to_v7886;
    _converter_v7885_to_v7886.from = v7885;
    v7886 = _converter_v7885_to_v7886.to;	// L12351
    rxv11[2] = v7886;	// L12352
    ap_int<17> v7887 = rx_w11;	// L12353
    bool v7888;
    ap_int<17> v7888_tmp = v7887;
    v7888 = v7888_tmp[0];	// L12354
    int32_t v7889 = v7888;	// L12355
    rxvld11[2] = v7889;	// L12356
    ap_int<17> v7890 = rx_e11;	// L12357
    int16_t v7891;
    ap_int<17> v7891_tmp = v7890;
    v7891 = v7891_tmp(16, 1);	// L12358
    half v7892;
    union { uint16_t from; half to;} _converter_v7891_to_v7892;
    _converter_v7891_to_v7892.from = v7891;
    v7892 = _converter_v7891_to_v7892.to;	// L12359
    rxv11[3] = v7892;	// L12360
    ap_int<17> v7893 = rx_e11;	// L12361
    bool v7894;
    ap_int<17> v7894_tmp = v7893;
    v7894 = v7894_tmp[0];	// L12362
    int32_t v7895 = v7894;	// L12363
    rxvld11[3] = v7895;	// L12364
    l_S_d_5_d47: for (int d47 = 0; d47 < 4; d47++) {	// L12365
      int32_t v7897 = rxvld11[d47];	// L12366
      bool v7898 = v7897 == 1;	// L12367
      int32_t v7899 = hold_cnt11[d47];	// L12368
      bool v7900 = v7899 < 2;	// L12369
      bool v7901 = v7898 & v7900;	// L12370
      if (v7901) {	// L12371
        half v7902 = rxv11[d47];	// L12372
        int32_t v7903 = hold_cnt11[d47];	// L12373
        int v7904 = v7903;	// L12374
        hold_v11[d47][v7904] = v7902;	// L12375
        int32_t v7905 = hold_cnt11[d47];	// L12376
        ap_int<33> v7906 = v7905;	// L12377
        ap_int<33> v7907 = v7906 + 1;	// L12378
        int32_t v7908 = v7907;	// L12379
        hold_cnt11[d47] = v7908;	// L12380
      }
    }
    int32_t pc11;	// L12383
    pc11 = -1;	// L12384
    int32_t v7910 = fetch_en11;	// L12385
    bool v7911 = v7910 == 1;	// L12386
    if (v7911) {	// L12387
      int32_t v7912 = instr_cnt11;	// L12388
      pc11 = v7912;	// L12389
    }
    int32_t instr11;	// L12391
    instr11 = 0;	// L12392
    int32_t v7914 = pc11;	// L12393
    bool v7915 = v7914 >= 0;	// L12394
    if (v7915) {	// L12395
      int32_t v7916 = pc11;	// L12396
      int v7917 = v7916;	// L12397
      int32_t v7918 = irf11[v7917];	// L12398
      instr11 = v7918;	// L12399
    }
    int32_t v7919 = instr11;	// L12401
    int32_t v7920 = v7919 & 15;	// L12402
    int32_t op11;	// L12403
    op11 = v7920;	// L12404
    int32_t v7922 = instr11;	// L12405
    int32_t v7923 = v7922 >> 4;	// L12406
    int32_t v7924 = v7923 & 15;	// L12407
    int32_t dst11;	// L12408
    dst11 = v7924;	// L12409
    int32_t v7926 = instr11;	// L12410
    int32_t v7927 = v7926 >> 8;	// L12411
    int32_t v7928 = v7927 & 15;	// L12412
    int32_t s111;	// L12413
    s111 = v7928;	// L12414
    int32_t v7930 = instr11;	// L12415
    int32_t v7931 = v7930 >> 12;	// L12416
    int32_t v7932 = v7931 & 15;	// L12417
    int32_t s211;	// L12418
    s211 = v7932;	// L12419
    half a11;	// L12420
    a11 = (double)0.000000;	// L12421
    half b11;	// L12422
    b11 = (double)0.000000;	// L12423
    int32_t v7936 = s111;	// L12424
    bool v7937 = v7936 >= 12;	// L12425
    if (v7937) {	// L12426
      int32_t v7938 = s111;	// L12427
      int32_t v7939 = v7938 & 3;	// L12428
      int v7940 = v7939;	// L12429
      half v7941 = hold_v11[v7940][0];	// L12430
      a11 = v7941;	// L12431
    } else {
      int32_t v7942 = s111;	// L12433
      int v7943 = v7942;	// L12434
      half v7944 = drf11[v7943];	// L12435
      a11 = v7944;	// L12436
    }
    int32_t v7945 = s211;	// L12438
    bool v7946 = v7945 >= 12;	// L12439
    if (v7946) {	// L12440
      int32_t v7947 = s211;	// L12441
      int32_t v7948 = v7947 & 3;	// L12442
      int v7949 = v7948;	// L12443
      half v7950 = hold_v11[v7949][0];	// L12444
      b11 = v7950;	// L12445
    } else {
      int32_t v7951 = s211;	// L12447
      int v7952 = v7951;	// L12448
      half v7953 = drf11[v7952];	// L12449
      b11 = v7953;	// L12450
    }
    int32_t a_vld11;	// L12452
    a_vld11 = 1;	// L12453
    int32_t b_vld11;	// L12454
    b_vld11 = 1;	// L12455
    int32_t v7956 = s111;	// L12456
    bool v7957 = v7956 >= 12;	// L12457
    if (v7957) {	// L12458
      a_vld11 = 0;	// L12459
      int32_t v7958 = s111;	// L12460
      int32_t v7959 = v7958 & 3;	// L12461
      int v7960 = v7959;	// L12462
      int32_t v7961 = hold_cnt11[v7960];	// L12463
      bool v7962 = v7961 > 0;	// L12464
      if (v7962) {	// L12465
        a_vld11 = 1;	// L12466
      }
    }
    int32_t v7963 = s211;	// L12469
    bool v7964 = v7963 >= 12;	// L12470
    if (v7964) {	// L12471
      b_vld11 = 0;	// L12472
      int32_t v7965 = s211;	// L12473
      int32_t v7966 = v7965 & 3;	// L12474
      int v7967 = v7966;	// L12475
      int32_t v7968 = hold_cnt11[v7967];	// L12476
      bool v7969 = v7968 > 0;	// L12477
      if (v7969) {	// L12478
        b_vld11 = 1;	// L12479
      }
    }
    int32_t v7970 = s111;	// L12482
    bool v7971 = v7970 < 8;	// L12483
    int32_t v7972 = dsmask11;	// L12484
    int32_t v7973 = v7972 >> v7970;	// L12485
    int32_t v7974 = v7973 & 1;	// L12486
    bool v7975 = v7974 == 1;	// L12487
    bool v7976 = v7971 & v7975;	// L12488
    if (v7976) {	// L12489
      int32_t v7977 = s111;	// L12490
      int v7978 = v7977;	// L12491
      int32_t v7979 = drf_full11[v7978];	// L12492
      bool v7980 = v7979 == 0;	// L12493
      if (v7980) {	// L12494
        a_vld11 = 0;	// L12495
      }
    }
    int32_t v7981 = s211;	// L12498
    bool v7982 = v7981 < 8;	// L12499
    int32_t v7983 = dsmask11;	// L12500
    int32_t v7984 = v7983 >> v7981;	// L12501
    int32_t v7985 = v7984 & 1;	// L12502
    bool v7986 = v7985 == 1;	// L12503
    bool v7987 = v7982 & v7986;	// L12504
    if (v7987) {	// L12505
      int32_t v7988 = s211;	// L12506
      int v7989 = v7988;	// L12507
      int32_t v7990 = drf_full11[v7989];	// L12508
      bool v7991 = v7990 == 0;	// L12509
      if (v7991) {	// L12510
        b_vld11 = 0;	// L12511
      }
    }
    int32_t binop11;	// L12514
    binop11 = 0;	// L12515
    int32_t v7993 = op11;	// L12516
    bool v7994 = v7993 == 0;	// L12517
    bool v7995 = v7993 == 1;	// L12518
    bool v7996 = v7993 == 2;	// L12519
    bool v7997 = v7993 == 8;	// L12520
    bool v7998 = v7993 == 9;	// L12521
    bool v7999 = v7994 | v7995;	// L12522
    bool v8000 = v7999 | v7996;	// L12523
    bool v8001 = v8000 | v7997;	// L12524
    bool v8002 = v8001 | v7998;	// L12525
    if (v8002) {	// L12526
      binop11 = 1;	// L12527
    }
    int32_t grant11;	// L12529
    grant11 = 0;	// L12530
    int32_t v8004 = pc11;	// L12531
    bool v8005 = v8004 >= 0;	// L12532
    if (v8005) {	// L12533
      grant11 = 1;	// L12534
    }
    int32_t v8006 = pc11;	// L12536
    bool v8007 = v8006 >= 0;	// L12537
    int32_t v8008 = a_vld11;	// L12538
    bool v8009 = v8008 == 0;	// L12539
    int32_t v8010 = binop11;	// L12540
    bool v8011 = v8010 == 1;	// L12541
    int32_t v8012 = b_vld11;	// L12542
    bool v8013 = v8012 == 0;	// L12543
    bool v8014 = v8011 & v8013;	// L12544
    bool v8015 = v8009 | v8014;	// L12545
    bool v8016 = v8007 & v8015;	// L12546
    if (v8016) {	// L12547
      grant11 = 0;	// L12548
    }
    int32_t v8017 = grant11;	// L12550
    bool v8018 = v8017 == 1;	// L12551
    if (v8018) {	// L12552
      int32_t v8019 = instr_cnt11;	// L12553
      int32_t v8020 = cfg_isz11;	// L12554
      bool v8021 = v8019 == v8020;	// L12555
      if (v8021) {	// L12556
        instr_cnt11 = 0;	// L12557
        int32_t v8022 = iter_cnt11;	// L12558
        int32_t v8023 = cfg_itsz11;	// L12559
        ap_int<33> v8024 = v8023;	// L12560
        ap_int<33> v8025 = v8024 - 1;	// L12561
        ap_int<33> v8026 = v8022;	// L12562
        bool v8027 = v8026 == v8025;	// L12563
        if (v8027) {	// L12564
          fetch_en11 = 0;	// L12565
        } else {
          int32_t v8028 = iter_cnt11;	// L12567
          ap_int<33> v8029 = v8028;	// L12568
          ap_int<33> v8030 = v8029 + 1;	// L12569
          int32_t v8031 = v8030;	// L12570
          iter_cnt11 = v8031;	// L12571
        }
      } else {
        int32_t v8032 = instr_cnt11;	// L12574
        ap_int<33> v8033 = v8032;	// L12575
        ap_int<33> v8034 = v8033 + 1;	// L12576
        int32_t v8035 = v8034;	// L12577
        instr_cnt11 = v8035;	// L12578
      }
    }
    int32_t c111;	// L12581
    c111 = -1;	// L12582
    int32_t c211;	// L12583
    c211 = -1;	// L12584
    int32_t v8038 = grant11;	// L12585
    bool v8039 = v8038 == 1;	// L12586
    int32_t v8040 = s111;	// L12587
    bool v8041 = v8040 >= 12;	// L12588
    bool v8042 = v8039 & v8041;	// L12589
    if (v8042) {	// L12590
      int32_t v8043 = s111;	// L12591
      int32_t v8044 = v8043 & 3;	// L12592
      c111 = v8044;	// L12593
    }
    int32_t v8045 = grant11;	// L12595
    bool v8046 = v8045 == 1;	// L12596
    int32_t v8047 = s211;	// L12597
    bool v8048 = v8047 >= 12;	// L12598
    bool v8049 = v8046 & v8048;	// L12599
    if (v8049) {	// L12600
      int32_t v8050 = s211;	// L12601
      int32_t v8051 = v8050 & 3;	// L12602
      c211 = v8051;	// L12603
    }
    int32_t v8052 = c111;	// L12605
    bool v8053 = v8052 >= 0;	// L12606
    if (v8053) {	// L12607
      int32_t v8054 = c111;	// L12608
      int v8055 = v8054;	// L12609
      half v8056 = hold_v11[v8055][1];	// L12610
      hold_v11[v8055][0] = v8056;	// L12611
      int32_t v8057 = c111;	// L12612
      int v8058 = v8057;	// L12613
      int32_t v8059 = hold_cnt11[v8058];	// L12614
      ap_int<33> v8060 = v8059;	// L12615
      ap_int<33> v8061 = v8060 - 1;	// L12616
      int32_t v8062 = v8061;	// L12617
      hold_cnt11[v8058] = v8062;	// L12618
    }
    int32_t v8063 = c211;	// L12620
    bool v8064 = v8063 >= 0;	// L12621
    int32_t v8065 = c111;	// L12622
    bool v8066 = v8063 != v8065;	// L12623
    bool v8067 = v8064 & v8066;	// L12624
    if (v8067) {	// L12625
      int32_t v8068 = c211;	// L12626
      int v8069 = v8068;	// L12627
      half v8070 = hold_v11[v8069][1];	// L12628
      hold_v11[v8069][0] = v8070;	// L12629
      int32_t v8071 = c211;	// L12630
      int v8072 = v8071;	// L12631
      int32_t v8073 = hold_cnt11[v8072];	// L12632
      ap_int<33> v8074 = v8073;	// L12633
      ap_int<33> v8075 = v8074 - 1;	// L12634
      int32_t v8076 = v8075;	// L12635
      hold_cnt11[v8072] = v8076;	// L12636
    }
    int32_t v8077 = grant11;	// L12638
    bool v8078 = v8077 == 1;	// L12639
    int32_t v8079 = s111;	// L12640
    bool v8080 = v8079 < 8;	// L12641
    int32_t v8081 = dsmask11;	// L12642
    int32_t v8082 = v8081 >> v8079;	// L12643
    int32_t v8083 = v8082 & 1;	// L12644
    bool v8084 = v8083 == 1;	// L12645
    bool v8085 = v8078 & v8080;	// L12646
    bool v8086 = v8085 & v8084;	// L12647
    if (v8086) {	// L12648
      int32_t v8087 = s111;	// L12649
      int v8088 = v8087;	// L12650
      drf_full11[v8088] = 0;	// L12651
    }
    int32_t v8089 = grant11;	// L12653
    bool v8090 = v8089 == 1;	// L12654
    int32_t v8091 = s211;	// L12655
    bool v8092 = v8091 < 8;	// L12656
    int32_t v8093 = dsmask11;	// L12657
    int32_t v8094 = v8093 >> v8091;	// L12658
    int32_t v8095 = v8094 & 1;	// L12659
    bool v8096 = v8095 == 1;	// L12660
    bool v8097 = v8090 & v8092;	// L12661
    bool v8098 = v8097 & v8096;	// L12662
    if (v8098) {	// L12663
      int32_t v8099 = s211;	// L12664
      int v8100 = v8099;	// L12665
      drf_full11[v8100] = 0;	// L12666
    }
    half res11;	// L12668
    res11 = (double)0.000000;	// L12669
    int32_t v8102 = op11;	// L12670
    bool v8103 = v8102 == 0;	// L12671
    if (v8103) {	// L12672
      half v8104 = a11;	// L12673
      half v8105 = b11;	// L12674
      half v8106 = v8104 + v8105;	// L12675
      res11 = v8106;	// L12676
    } else {
      int32_t v8107 = op11;	// L12678
      bool v8108 = v8107 == 1;	// L12679
      if (v8108) {	// L12680
        half v8109 = a11;	// L12681
        half v8110 = b11;	// L12682
        half v8111 = v8109 - v8110;	// L12683
        res11 = v8111;	// L12684
      } else {
        int32_t v8112 = op11;	// L12686
        bool v8113 = v8112 == 2;	// L12687
        if (v8113) {	// L12688
          half v8114 = a11;	// L12689
          half v8115 = b11;	// L12690
          half v8116 = v8114 * v8115;	// L12691
          res11 = v8116;	// L12692
        } else {
          int32_t v8117 = op11;	// L12694
          bool v8118 = v8117 == 8;	// L12695
          if (v8118) {	// L12696
            half v8119 = a11;	// L12697
            half v8120 = b11;	// L12698
            bool v8121 = v8119 >= v8120;	// L12699
            if (v8121) {	// L12700
              res11 = (double)1.000000;	// L12701
            } else {
              res11 = (double)-1.000000;	// L12703
            }
          } else {
            int32_t v8122 = op11;	// L12706
            bool v8123 = v8122 == 9;	// L12707
            if (v8123) {	// L12708
              half v8124 = a11;	// L12709
              half v8125 = b11;	// L12710
              bool v8126 = v8124 < v8125;	// L12711
              if (v8126) {	// L12712
                res11 = (double)1.000000;	// L12713
              } else {
                res11 = (double)-1.000000;	// L12715
              }
            } else {
              half v8127 = a11;	// L12718
              res11 = v8127;	// L12719
            }
          }
        }
      }
    }
    int32_t v8128 = a_vld11;	// L12725
    int32_t res_vld11;	// L12726
    res_vld11 = v8128;	// L12727
    int32_t v8130 = op11;	// L12728
    bool v8131 = v8130 == 0;	// L12729
    bool v8132 = v8130 == 1;	// L12730
    bool v8133 = v8130 == 2;	// L12731
    bool v8134 = v8130 == 8;	// L12732
    bool v8135 = v8130 == 9;	// L12733
    bool v8136 = v8131 | v8132;	// L12734
    bool v8137 = v8136 | v8133;	// L12735
    bool v8138 = v8137 | v8134;	// L12736
    bool v8139 = v8138 | v8135;	// L12737
    if (v8139) {	// L12738
      int32_t v8140 = a_vld11;	// L12739
      int32_t v8141 = b_vld11;	// L12740
      int64_t v8142 = v8140;	// L12741
      int64_t v8143 = v8141;	// L12742
      int64_t v8144 = v8142 * v8143;	// L12743
      int32_t v8145 = v8144;	// L12744
      res_vld11 = v8145;	// L12745
    }
    int32_t v8146 = grant11;	// L12747
    bool v8147 = v8146 == 0;	// L12748
    if (v8147) {	// L12749
      res_vld11 = 0;	// L12750
    }
    int32_t v8148 = grant11;	// L12752
    bool v8149 = v8148 == 1;	// L12753
    int32_t v8150 = op11;	// L12754
    bool v8151 = v8150 == 8;	// L12755
    bool v8152 = v8149 & v8151;	// L12756
    if (v8152) {	// L12757
      condition_reg11 = 0;	// L12758
      half v8153 = a11;	// L12759
      half v8154 = b11;	// L12760
      bool v8155 = v8153 >= v8154;	// L12761
      if (v8155) {	// L12762
        condition_reg11 = 1;	// L12763
      }
    }
    int32_t v8156 = grant11;	// L12766
    bool v8157 = v8156 == 1;	// L12767
    int32_t v8158 = op11;	// L12768
    bool v8159 = v8158 == 9;	// L12769
    bool v8160 = v8157 & v8159;	// L12770
    if (v8160) {	// L12771
      condition_reg11 = 0;	// L12772
      half v8161 = a11;	// L12773
      half v8162 = b11;	// L12774
      bool v8163 = v8161 < v8162;	// L12775
      if (v8163) {	// L12776
        condition_reg11 = 1;	// L12777
      }
    }
    ap_uint<17> tx_n11;	// L12780
    tx_n11 = 0;	// L12781
    ap_uint<17> tx_s11;	// L12782
    tx_s11 = 0;	// L12783
    ap_uint<17> tx_w11;	// L12784
    tx_w11 = 0;	// L12785
    ap_uint<17> tx_e11;	// L12786
    tx_e11 = 0;	// L12787
    int32_t is_rtr11;	// L12788
    is_rtr11 = 0;	// L12789
    int32_t do_inj11;	// L12790
    do_inj11 = 0;	// L12791
    int32_t v8170 = op11;	// L12792
    bool v8171 = v8170 >= 4;	// L12793
    ap_int<33> v8172 = v8170;	// L12794
    bool v8173 = v8172 <= 7;	// L12795
    bool v8174 = v8171 & v8173;	// L12796
    if (v8174) {	// L12797
      is_rtr11 = 1;	// L12798
      do_inj11 = 1;	// L12799
    }
    int32_t v8175 = op11;	// L12801
    bool v8176 = v8175 >= 12;	// L12802
    ap_int<33> v8177 = v8175;	// L12803
    bool v8178 = v8177 <= 15;	// L12804
    bool v8179 = v8176 & v8178;	// L12805
    if (v8179) {	// L12806
      is_rtr11 = 1;	// L12807
      int32_t v8180 = condition_reg11;	// L12808
      bool v8181 = v8180 == 1;	// L12809
      if (v8181) {	// L12810
        do_inj11 = 1;	// L12811
      }
    }
    int32_t v8182 = is_rtr11;	// L12814
    bool v8183 = v8182 == 1;	// L12815
    if (v8183) {	// L12816
      int32_t v8184 = do_inj11;	// L12817
      bool v8185 = v8184 == 1;	// L12818
      ap_int<26> v8186 = csd_pkt11;	// L12819
      bool v8187;
      ap_int<26> v8187_tmp = v8186;
      v8187 = v8187_tmp[25];	// L12820
      int32_t v8188 = v8187;	// L12821
      bool v8189 = v8188 == 0;	// L12822
      bool v8190 = v8185 & v8189;	// L12823
      if (v8190) {	// L12824
        half v8191 = res11;	// L12825
        uint16_t v8192;
        union { half from; uint16_t to;} _converter_v8191_to_v8192;
        _converter_v8191_to_v8192.from = v8191;
        v8192 = _converter_v8191_to_v8192.to;	// L12826
        ap_int<26> v8193 = csd_pkt11;	// L12827
        ap_int<26> v8194;
        ap_int<26> v8194_tmp = v8193;
        v8194_tmp(15, 0) = v8192;
        v8194 = v8194_tmp;	// L12828
        csd_pkt11 = v8194;	// L12829
        int32_t v8195 = dst11;	// L12830
        ap_uint<4> v8196 = v8195;	// L12831
        ap_int<26> v8197 = csd_pkt11;	// L12832
        ap_int<26> v8198;
        ap_int<26> v8198_tmp = v8197;
        v8198_tmp(19, 16) = v8196;
        v8198 = v8198_tmp;	// L12833
        csd_pkt11 = v8198;	// L12834
        int32_t v8199 = s211;	// L12835
        ap_uint<4> v8200 = v8199;	// L12836
        ap_int<26> v8201 = csd_pkt11;	// L12837
        ap_int<26> v8202;
        ap_int<26> v8202_tmp = v8201;
        v8202_tmp(24, 21) = v8200;
        v8202 = v8202_tmp;	// L12838
        csd_pkt11 = v8202;	// L12839
        int32_t v8203 = res_vld11;	// L12840
        bool v8204 = v8203;	// L12841
        ap_int<26> v8205 = csd_pkt11;	// L12842
        ap_int<26> v8206;
        ap_int<26> v8206_tmp = v8205;
        v8206_tmp[25] = v8204;        v8206 = v8206_tmp;	// L12843
        csd_pkt11 = v8206;	// L12844
        int32_t v8207 = op11;	// L12845
        int32_t v8208 = v8207 & 3;	// L12846
        csd_dir11 = v8208;	// L12847
      }
    } else {
      int32_t v8209 = dst11;	// L12850
      bool v8210 = v8209 >= 12;	// L12851
      if (v8210) {	// L12852
        ap_uint<17> tw11;	// L12853
        tw11 = 0;	// L12854
        int32_t v8212 = res_vld11;	// L12855
        bool v8213 = v8212;	// L12856
        ap_int<17> v8214 = tw11;	// L12857
        ap_int<17> v8215;
        ap_int<17> v8215_tmp = v8214;
        v8215_tmp[0] = v8213;        v8215 = v8215_tmp;	// L12858
        tw11 = v8215;	// L12859
        half v8216 = res11;	// L12860
        uint16_t v8217;
        union { half from; uint16_t to;} _converter_v8216_to_v8217;
        _converter_v8216_to_v8217.from = v8216;
        v8217 = _converter_v8216_to_v8217.to;	// L12861
        ap_int<17> v8218 = tw11;	// L12862
        ap_int<17> v8219;
        ap_int<17> v8219_tmp = v8218;
        v8219_tmp(16, 1) = v8217;
        v8219 = v8219_tmp;	// L12863
        tw11 = v8219;	// L12864
        int32_t v8220 = dst11;	// L12865
        int32_t v8221 = v8220 & 3;	// L12866
        bool v8222 = v8221 == 0;	// L12867
        if (v8222) {	// L12868
          ap_int<17> v8223 = tw11;	// L12869
          tx_n11 = v8223;	// L12870
        } else {
          int32_t v8224 = dst11;	// L12872
          int32_t v8225 = v8224 & 3;	// L12873
          bool v8226 = v8225 == 1;	// L12874
          if (v8226) {	// L12875
            ap_int<17> v8227 = tw11;	// L12876
            tx_s11 = v8227;	// L12877
          } else {
            int32_t v8228 = dst11;	// L12879
            int32_t v8229 = v8228 & 3;	// L12880
            bool v8230 = v8229 == 2;	// L12881
            if (v8230) {	// L12882
              ap_int<17> v8231 = tw11;	// L12883
              tx_w11 = v8231;	// L12884
            } else {
              ap_int<17> v8232 = tw11;	// L12886
              tx_e11 = v8232;	// L12887
            }
          }
        }
      } else {
        int32_t v8233 = res_vld11;	// L12892
        bool v8234 = v8233 == 1;	// L12893
        if (v8234) {	// L12894
          int32_t v8235 = dst11;	// L12895
          bool v8236 = v8235 < 8;	// L12896
          int32_t v8237 = dsmask11;	// L12897
          int32_t v8238 = v8237 >> v8235;	// L12898
          int32_t v8239 = v8238 & 1;	// L12899
          bool v8240 = v8239 == 1;	// L12900
          bool v8241 = v8236 & v8240;	// L12901
          if (v8241) {	// L12902
            int32_t v8242 = dst11;	// L12903
            int v8243 = v8242;	// L12904
            int32_t v8244 = drf_full11[v8243];	// L12905
            bool v8245 = v8244 == 0;	// L12906
            if (v8245) {	// L12907
              half v8246 = res11;	// L12908
              int32_t v8247 = dst11;	// L12909
              int v8248 = v8247;	// L12910
              drf11[v8248] = v8246;	// L12911
              int32_t v8249 = dst11;	// L12912
              int v8250 = v8249;	// L12913
              drf_full11[v8250] = 1;	// L12914
            }
          } else {
            half v8251 = res11;	// L12917
            int32_t v8252 = dst11;	// L12918
            int v8253 = v8252;	// L12919
            drf11[v8253] = v8251;	// L12920
          }
        }
      }
    }
    ap_int<17> v8254 = tx_n11;	// L12925
    txn_r11 = v8254;	// L12926
    ap_int<17> v8255 = tx_s11;	// L12927
    txs_r11 = v8255;	// L12928
    ap_int<17> v8256 = tx_w11;	// L12929
    txw_r11 = v8256;	// L12930
    ap_int<17> v8257 = tx_e11;	// L12931
    txe_r11 = v8257;	// L12932
    int32_t v8258 = crv_vld11;	// L12933
    bool v8259 = v8258 == 1;	// L12934
    if (v8259) {	// L12935
      int32_t v8260 = crv_mode11;	// L12936
      bool v8261 = v8260 == 1;	// L12937
      if (v8261) {	// L12938
        int32_t v8262 = crv_addr11;	// L12939
        int32_t v8263 = v8262 >> 3;	// L12940
        int32_t v8264 = v8263 & 1;	// L12941
        bool v8265 = v8264 == 1;	// L12942
        if (v8265) {	// L12943
          int32_t v8266 = crv_raw11;	// L12944
          int32_t v8267 = crv_addr11;	// L12945
          int32_t v8268 = v8267 & 7;	// L12946
          int v8269 = v8268;	// L12947
          irf11[v8269] = v8266;	// L12948
        } else {
          int32_t v8270 = crv_addr11;	// L12950
          bool v8271 = v8270 == 0;	// L12951
          if (v8271) {	// L12952
            int32_t v8272 = crv_raw11;	// L12953
            int32_t v8273 = v8272 & 255;	// L12954
            dsmask11 = v8273;	// L12955
            int32_t v8274 = crv_raw11;	// L12956
            int32_t v8275 = v8274 >> 8;	// L12957
            int32_t v8276 = v8275 & 7;	// L12958
            cfg_isz11 = v8276;	// L12959
            int32_t v8277 = crv_raw11;	// L12960
            int32_t v8278 = v8277 >> 15;	// L12961
            int32_t v8279 = v8278 & 1;	// L12962
            bool v8280 = v8279 == 1;	// L12963
            if (v8280) {	// L12964
              fetch_en11 = 1;	// L12965
              instr_cnt11 = 0;	// L12966
              iter_cnt11 = 0;	// L12967
            }
          } else {
            int32_t v8281 = crv_addr11;	// L12970
            bool v8282 = v8281 == 1;	// L12971
            if (v8282) {	// L12972
              int32_t v8283 = crv_raw11;	// L12973
              int32_t v8284 = v8283 & 255;	// L12974
              cfg_itsz11 = v8284;	// L12975
            }
          }
        }
      } else {
        int32_t v8285 = crv_addr11;	// L12980
        bool v8286 = v8285 < 8;	// L12981
        int32_t v8287 = dsmask11;	// L12982
        int32_t v8288 = v8287 >> v8285;	// L12983
        int32_t v8289 = v8288 & 1;	// L12984
        bool v8290 = v8289 == 1;	// L12985
        bool v8291 = v8286 & v8290;	// L12986
        if (v8291) {	// L12987
          int32_t v8292 = crv_addr11;	// L12988
          int v8293 = v8292;	// L12989
          int32_t v8294 = drf_full11[v8293];	// L12990
          bool v8295 = v8294 == 0;	// L12991
          if (v8295) {	// L12992
            half v8296 = crv_data11;	// L12993
            int32_t v8297 = crv_addr11;	// L12994
            int v8298 = v8297;	// L12995
            drf11[v8298] = v8296;	// L12996
            int32_t v8299 = crv_addr11;	// L12997
            int v8300 = v8299;	// L12998
            drf_full11[v8300] = 1;	// L12999
          }
        } else {
          half v8301 = crv_data11;	// L13002
          int32_t v8302 = crv_addr11;	// L13003
          int v8303 = v8302;	// L13004
          drf11[v8303] = v8301;	// L13005
        }
      }
    }
  }
}

void node_3_0(
  hls::stream< ap_uint<26> >& v8304,
  hls::stream< ap_uint<26> >& v8305,
  hls::stream< ap_uint<26> >& v8306,
  hls::stream< ap_uint<26> >& v8307,
  hls::stream< ap_uint<17> >& v8308,
  hls::stream< ap_uint<17> >& v8309,
  hls::stream< ap_uint<17> >& v8310,
  hls::stream< ap_uint<17> >& v8311,
  hls::stream< int32_t >& v8312,
  hls::stream< int32_t >& v8313,
  hls::stream< int32_t >& v8314,
  hls::stream< int32_t >& v8315,
  hls::stream< ap_uint<26> >& v8316,
  hls::stream< ap_uint<26> >& v8317,
  hls::stream< ap_uint<26> >& v8318,
  hls::stream< ap_uint<26> >& v8319,
  hls::stream< int32_t >& v8320,
  hls::stream< int32_t >& v8321,
  hls::stream< int32_t >& v8322,
  hls::stream< int32_t >& v8323,
  hls::stream< ap_uint<17> >& v8324,
  hls::stream< ap_uint<17> >& v8325,
  hls::stream< ap_uint<17> >& v8326,
  hls::stream< ap_uint<17> >& v8327
) {	// L13012
  int32_t irf12[8];	// L13043
  for (int v8329 = 0; v8329 < 8; v8329++) {	// L13044
    irf12[v8329] = 0;	// L13044
  }
  half drf12[8];	// L13045
  #pragma HLS array_partition variable=drf12 complete dim=1

  for (int v8331 = 0; v8331 < 8; v8331++) {	// L13046
    drf12[v8331] = (double)0.000000;	// L13046
  }
  int32_t drf_full12[8];	// L13047
  #pragma HLS array_partition variable=drf_full12 complete dim=1

  for (int v8333 = 0; v8333 < 8; v8333++) {	// L13048
    drf_full12[v8333] = 0;	// L13048
  }
  int32_t dsmask12;	// L13049
  dsmask12 = 0;	// L13050
  int32_t crv_vld12;	// L13051
  crv_vld12 = 0;	// L13052
  half crv_data12;	// L13053
  crv_data12 = (double)0.000000;	// L13054
  int32_t crv_addr12;	// L13055
  crv_addr12 = 0;	// L13056
  int32_t crv_mode12;	// L13057
  crv_mode12 = 0;	// L13058
  int32_t crv_raw12;	// L13059
  crv_raw12 = 0;	// L13060
  int32_t csd_vld12;	// L13061
  csd_vld12 = 0;	// L13062
  ap_uint<26> csd_pkt12;	// L13063
  csd_pkt12 = 0;	// L13064
  int32_t csd_dir12;	// L13065
  csd_dir12 = 0;	// L13066
  int32_t row_id12;	// L13067
  row_id12 = 3;	// L13068
  int32_t col_id12;	// L13069
  col_id12 = 0;	// L13070
  ap_uint<26> oe_r12;	// L13071
  oe_r12 = 0;	// L13072
  ap_uint<26> ow_r12;	// L13073
  ow_r12 = 0;	// L13074
  ap_uint<26> on_r12;	// L13075
  on_r12 = 0;	// L13076
  ap_uint<26> os_r12;	// L13077
  os_r12 = 0;	// L13078
  ap_uint<17> txn_r12;	// L13079
  txn_r12 = 0;	// L13080
  ap_uint<17> txs_r12;	// L13081
  txs_r12 = 0;	// L13082
  ap_uint<17> txw_r12;	// L13083
  txw_r12 = 0;	// L13084
  ap_uint<17> txe_r12;	// L13085
  txe_r12 = 0;	// L13086
  half hold_v12[4][2];	// L13087
  #pragma HLS array_partition variable=hold_v12 complete dim=1
  #pragma HLS array_partition variable=hold_v12 complete dim=2

  for (int v8354 = 0; v8354 < 4; v8354++) {	// L13088
    for (int v8355 = 0; v8355 < 2; v8355++) {	// L13088
      hold_v12[v8354][v8355] = (double)0.000000;	// L13088
    }
  }
  int32_t hold_cnt12[4];	// L13089
  #pragma HLS array_partition variable=hold_cnt12 complete dim=1

  for (int v8357 = 0; v8357 < 4; v8357++) {	// L13090
    hold_cnt12[v8357] = 0;	// L13090
  }
  ap_uint<26> rbuf12[4][2];	// L13091
  #pragma HLS array_partition variable=rbuf12 complete dim=1
  #pragma HLS array_partition variable=rbuf12 complete dim=2

  for (int v8359 = 0; v8359 < 4; v8359++) {	// L13092
    for (int v8360 = 0; v8360 < 2; v8360++) {	// L13092
      rbuf12[v8359][v8360] = 0;	// L13092
    }
  }
  int32_t rbcnt12[4];	// L13093
  #pragma HLS array_partition variable=rbcnt12 complete dim=1

  for (int v8362 = 0; v8362 < 4; v8362++) {	// L13094
    rbcnt12[v8362] = 0;	// L13094
  }
  int32_t rcred12[4];	// L13095
  #pragma HLS array_partition variable=rcred12 complete dim=1

  for (int v8364 = 0; v8364 < 4; v8364++) {	// L13096
    rcred12[v8364] = 0;	// L13096
  }
  int32_t cre_r12;	// L13097
  cre_r12 = 2;	// L13098
  int32_t crw_r12;	// L13099
  crw_r12 = 2;	// L13100
  int32_t crs_r12;	// L13101
  crs_r12 = 2;	// L13102
  int32_t crn_r12;	// L13103
  crn_r12 = 2;	// L13104
  int32_t cfg_isz12;	// L13105
  cfg_isz12 = 0;	// L13106
  int32_t cfg_itsz12;	// L13107
  cfg_itsz12 = 0;	// L13108
  int32_t fetch_en12;	// L13109
  fetch_en12 = 0;	// L13110
  int32_t instr_cnt12;	// L13111
  instr_cnt12 = 0;	// L13112
  int32_t iter_cnt12;	// L13113
  iter_cnt12 = 0;	// L13114
  int32_t condition_reg12;	// L13115
  condition_reg12 = 0;	// L13116
  l_S_t_0_t12: for (int t12 = 0; t12 < 8; t12++) {	// L13117
  #pragma HLS pipeline II=1
    ap_int<26> v8376 = oe_r12;	// L13118
    v8304.write(v8376);	// L13119
    ap_int<26> v8377 = ow_r12;	// L13120
    v8305.write(v8377);	// L13121
    ap_int<26> v8378 = os_r12;	// L13122
    v8306.write(v8378);	// L13123
    ap_int<26> v8379 = on_r12;	// L13124
    v8307.write(v8379);	// L13125
    ap_int<17> v8380 = txe_r12;	// L13126
    v8308.write(v8380);	// L13127
    ap_int<17> v8381 = txw_r12;	// L13128
    v8309.write(v8381);	// L13129
    ap_int<17> v8382 = txs_r12;	// L13130
    v8310.write(v8382);	// L13131
    ap_int<17> v8383 = txn_r12;	// L13132
    v8311.write(v8383);	// L13133
    int32_t v8384 = cre_r12;	// L13134
    v8312.write(v8384);	// L13135
    int32_t v8385 = crw_r12;	// L13136
    v8313.write(v8385);	// L13137
    int32_t v8386 = crs_r12;	// L13138
    v8314.write(v8386);	// L13139
    int32_t v8387 = crn_r12;	// L13140
    v8315.write(v8387);	// L13141
    ap_uint<26> v8388 = v8316.read();	// L13142
    ap_uint<26> p_w12;	// L13143
    p_w12 = v8388;	// L13144
    ap_uint<26> v8390 = v8317.read();	// L13145
    ap_uint<26> p_e12;	// L13146
    p_e12 = v8390;	// L13147
    ap_uint<26> v8392 = v8318.read();	// L13148
    ap_uint<26> p_n12;	// L13149
    p_n12 = v8392;	// L13150
    ap_uint<26> v8394 = v8319.read();	// L13151
    ap_uint<26> p_s12;	// L13152
    p_s12 = v8394;	// L13153
    int32_t v8396 = v8320.read();	// L13154
    int32_t v8397 = rcred12[0];	// L13155
    ap_int<33> v8398 = v8397;	// L13156
    ap_int<33> v8399 = v8396;	// L13157
    ap_int<33> v8400 = v8398 + v8399;	// L13158
    int32_t v8401 = v8400;	// L13159
    rcred12[0] = v8401;	// L13160
    int32_t v8402 = v8321.read();	// L13161
    int32_t v8403 = rcred12[1];	// L13162
    ap_int<33> v8404 = v8403;	// L13163
    ap_int<33> v8405 = v8402;	// L13164
    ap_int<33> v8406 = v8404 + v8405;	// L13165
    int32_t v8407 = v8406;	// L13166
    rcred12[1] = v8407;	// L13167
    int32_t v8408 = v8322.read();	// L13168
    int32_t v8409 = rcred12[2];	// L13169
    ap_int<33> v8410 = v8409;	// L13170
    ap_int<33> v8411 = v8408;	// L13171
    ap_int<33> v8412 = v8410 + v8411;	// L13172
    int32_t v8413 = v8412;	// L13173
    rcred12[2] = v8413;	// L13174
    int32_t v8414 = v8323.read();	// L13175
    int32_t v8415 = rcred12[3];	// L13176
    ap_int<33> v8416 = v8415;	// L13177
    ap_int<33> v8417 = v8414;	// L13178
    ap_int<33> v8418 = v8416 + v8417;	// L13179
    int32_t v8419 = v8418;	// L13180
    rcred12[3] = v8419;	// L13181
    ap_uint<26> fin12[4];	// L13182
    for (int v8421 = 0; v8421 < 4; v8421++) {	// L13183
      fin12[v8421] = 0;	// L13183
    }
    ap_int<26> v8422 = p_w12;	// L13184
    fin12[0] = v8422;	// L13185
    ap_int<26> v8423 = p_e12;	// L13186
    fin12[1] = v8423;	// L13187
    ap_int<26> v8424 = p_n12;	// L13188
    fin12[2] = v8424;	// L13189
    ap_int<26> v8425 = p_s12;	// L13190
    fin12[3] = v8425;	// L13191
    l_S_d_0_d48: for (int d48 = 0; d48 < 4; d48++) {	// L13192
      ap_uint<26> v8427 = fin12[d48];	// L13193
      bool v8428;
      ap_int<26> v8428_tmp = v8427;
      v8428 = v8428_tmp[25];	// L13194
      int32_t v8429 = v8428;	// L13195
      bool v8430 = v8429 == 1;	// L13196
      int32_t v8431 = rbcnt12[d48];	// L13197
      bool v8432 = v8431 < 2;	// L13198
      bool v8433 = v8430 & v8432;	// L13199
      if (v8433) {	// L13200
        ap_uint<26> v8434 = fin12[d48];	// L13201
        int32_t v8435 = rbcnt12[d48];	// L13202
        int v8436 = v8435;	// L13203
        rbuf12[d48][v8436] = v8434;	// L13204
        int32_t v8437 = rbcnt12[d48];	// L13205
        ap_int<33> v8438 = v8437;	// L13206
        ap_int<33> v8439 = v8438 + 1;	// L13207
        int32_t v8440 = v8439;	// L13208
        rbcnt12[d48] = v8440;	// L13209
      }
    }
    ap_uint<26> hd12[4];	// L13212
    for (int v8442 = 0; v8442 < 4; v8442++) {	// L13213
      hd12[v8442] = 0;	// L13213
    }
    int32_t hvld12[4];	// L13214
    for (int v8444 = 0; v8444 < 4; v8444++) {	// L13215
      hvld12[v8444] = 0;	// L13215
    }
    int32_t hit12[4];	// L13216
    for (int v8446 = 0; v8446 < 4; v8446++) {	// L13217
      hit12[v8446] = 0;	// L13217
    }
    int32_t axis12[4];	// L13218
    for (int v8448 = 0; v8448 < 4; v8448++) {	// L13219
      axis12[v8448] = 0;	// L13219
    }
    int32_t v8449 = col_id12;	// L13220
    axis12[0] = v8449;	// L13221
    int32_t v8450 = col_id12;	// L13222
    axis12[1] = v8450;	// L13223
    int32_t v8451 = row_id12;	// L13224
    axis12[2] = v8451;	// L13225
    int32_t v8452 = row_id12;	// L13226
    axis12[3] = v8452;	// L13227
    l_S_d_1_d49: for (int d49 = 0; d49 < 4; d49++) {	// L13228
      int32_t v8454 = rbcnt12[d49];	// L13229
      bool v8455 = v8454 > 0;	// L13230
      if (v8455) {	// L13231
        ap_uint<26> v8456 = rbuf12[d49][0];	// L13232
        hd12[d49] = v8456;	// L13233
        hvld12[d49] = 1;	// L13234
        ap_uint<26> v8457 = hd12[d49];	// L13235
        ap_int<4> v8458;
        ap_int<26> v8458_tmp = v8457;
        v8458 = v8458_tmp(24, 21);	// L13236
        int32_t v8459 = axis12[d49];	// L13237
        int32_t v8460 = v8458;	// L13238
        bool v8461 = v8460 == v8459;	// L13239
        if (v8461) {	// L13240
          hit12[d49] = 1;	// L13241
        }
      }
    }
    ap_uint<26> o_crv12;	// L13245
    o_crv12 = 0;	// L13246
    int32_t crv_in12;	// L13247
    crv_in12 = -1;	// L13248
    int32_t v8464 = hit12[3];	// L13249
    bool v8465 = v8464 == 1;	// L13250
    if (v8465) {	// L13251
      ap_uint<26> v8466 = hd12[3];	// L13252
      o_crv12 = v8466;	// L13253
      crv_in12 = 3;	// L13254
    } else {
      int32_t v8467 = hit12[2];	// L13256
      bool v8468 = v8467 == 1;	// L13257
      if (v8468) {	// L13258
        ap_uint<26> v8469 = hd12[2];	// L13259
        o_crv12 = v8469;	// L13260
        crv_in12 = 2;	// L13261
      } else {
        int32_t v8470 = hit12[1];	// L13263
        bool v8471 = v8470 == 1;	// L13264
        if (v8471) {	// L13265
          ap_uint<26> v8472 = hd12[1];	// L13266
          o_crv12 = v8472;	// L13267
          crv_in12 = 1;	// L13268
        } else {
          int32_t v8473 = hit12[0];	// L13270
          bool v8474 = v8473 == 1;	// L13271
          if (v8474) {	// L13272
            ap_uint<26> v8475 = hd12[0];	// L13273
            o_crv12 = v8475;	// L13274
            crv_in12 = 0;	// L13275
          }
        }
      }
    }
    ap_uint<26> o_out12[4];	// L13280
    for (int v8477 = 0; v8477 < 4; v8477++) {	// L13281
      o_out12[v8477] = 0;	// L13281
    }
    int32_t pop12[4];	// L13282
    for (int v8479 = 0; v8479 < 4; v8479++) {	// L13283
      pop12[v8479] = 0;	// L13283
    }
    int32_t inj_done12;	// L13284
    inj_done12 = 0;	// L13285
    int32_t idir12;	// L13286
    idir12 = -1;	// L13287
    ap_int<26> v8482 = csd_pkt12;	// L13288
    bool v8483;
    ap_int<26> v8483_tmp = v8482;
    v8483 = v8483_tmp[25];	// L13289
    int32_t v8484 = v8483;	// L13290
    bool v8485 = v8484 == 1;	// L13291
    if (v8485) {	// L13292
      int32_t v8486 = csd_dir12;	// L13293
      ap_int<33> v8487 = v8486;	// L13294
      ap_int<33> v8488 = 3 - v8487;	// L13295
      int32_t v8489 = v8488;	// L13296
      idir12 = v8489;	// L13297
    }
    l_S_o_2_o12: for (int o12 = 0; o12 < 4; o12++) {	// L13299
      int32_t v8491 = rcred12[o12];	// L13300
      bool v8492 = v8491 > 0;	// L13301
      if (v8492) {	// L13302
        int32_t v8493 = idir12;	// L13303
        ap_int<33> v8494 = v8493;	// L13304
        ap_int<33> v8495 = o12;	// L13305
        bool v8496 = v8494 == v8495;	// L13306
        if (v8496) {	// L13307
          ap_int<26> v8497 = csd_pkt12;	// L13308
          o_out12[o12] = v8497;	// L13309
          int32_t v8498 = rcred12[o12];	// L13310
          ap_int<33> v8499 = v8498;	// L13311
          ap_int<33> v8500 = v8499 - 1;	// L13312
          int32_t v8501 = v8500;	// L13313
          rcred12[o12] = v8501;	// L13314
          inj_done12 = 1;	// L13315
        } else {
          int32_t v8502 = hvld12[o12];	// L13317
          bool v8503 = v8502 == 1;	// L13318
          int32_t v8504 = hit12[o12];	// L13319
          bool v8505 = v8504 == 0;	// L13320
          bool v8506 = v8503 & v8505;	// L13321
          if (v8506) {	// L13322
            ap_uint<26> v8507 = hd12[o12];	// L13323
            o_out12[o12] = v8507;	// L13324
            int32_t v8508 = rcred12[o12];	// L13325
            ap_int<33> v8509 = v8508;	// L13326
            ap_int<33> v8510 = v8509 - 1;	// L13327
            int32_t v8511 = v8510;	// L13328
            rcred12[o12] = v8511;	// L13329
            pop12[o12] = 1;	// L13330
          }
        }
      }
    }
    int32_t v8512 = crv_in12;	// L13335
    bool v8513 = v8512 >= 0;	// L13336
    if (v8513) {	// L13337
      int32_t v8514 = crv_in12;	// L13338
      int v8515 = v8514;	// L13339
      pop12[v8515] = 1;	// L13340
    }
    int32_t ret12[4];	// L13342
    for (int v8517 = 0; v8517 < 4; v8517++) {	// L13343
      ret12[v8517] = 0;	// L13343
    }
    l_S_d_3_d50: for (int d50 = 0; d50 < 4; d50++) {	// L13344
      int32_t v8519 = pop12[d50];	// L13345
      bool v8520 = v8519 == 1;	// L13346
      if (v8520) {	// L13347
        l_S_sft_3_sft12: for (int sft12 = 0; sft12 < 1; sft12++) {	// L13348
          ap_uint<26> v8522 = rbuf12[d50][(sft12 + 1)];	// L13349
          rbuf12[d50][sft12] = v8522;	// L13350
        }
        int32_t v8523 = rbcnt12[d50];	// L13352
        ap_int<33> v8524 = v8523;	// L13353
        ap_int<33> v8525 = v8524 - 1;	// L13354
        int32_t v8526 = v8525;	// L13355
        rbcnt12[d50] = v8526;	// L13356
        ret12[d50] = 1;	// L13357
      }
    }
    int32_t v8527 = ret12[0];	// L13360
    cre_r12 = v8527;	// L13361
    int32_t v8528 = ret12[1];	// L13362
    crw_r12 = v8528;	// L13363
    int32_t v8529 = ret12[2];	// L13364
    crs_r12 = v8529;	// L13365
    int32_t v8530 = ret12[3];	// L13366
    crn_r12 = v8530;	// L13367
    ap_uint<26> v8531 = o_out12[0];	// L13368
    oe_r12 = v8531;	// L13369
    ap_uint<26> v8532 = o_out12[1];	// L13370
    ow_r12 = v8532;	// L13371
    ap_uint<26> v8533 = o_out12[2];	// L13372
    os_r12 = v8533;	// L13373
    ap_uint<26> v8534 = o_out12[3];	// L13374
    on_r12 = v8534;	// L13375
    int32_t v8535 = inj_done12;	// L13376
    bool v8536 = v8535 == 1;	// L13377
    if (v8536) {	// L13378
      csd_pkt12 = 0;	// L13379
    }
    ap_int<26> v8537 = o_crv12;	// L13381
    bool v8538;
    ap_int<26> v8538_tmp = v8537;
    v8538 = v8538_tmp[25];	// L13382
    int32_t v8539 = v8538;	// L13383
    crv_vld12 = v8539;	// L13384
    ap_int<26> v8540 = o_crv12;	// L13385
    int16_t v8541;
    ap_int<26> v8541_tmp = v8540;
    v8541 = v8541_tmp(15, 0);	// L13386
    half v8542;
    union { uint16_t from; half to;} _converter_v8541_to_v8542;
    _converter_v8541_to_v8542.from = v8541;
    v8542 = _converter_v8541_to_v8542.to;	// L13387
    crv_data12 = v8542;	// L13388
    ap_int<26> v8543 = o_crv12;	// L13389
    ap_int<4> v8544;
    ap_int<26> v8544_tmp = v8543;
    v8544 = v8544_tmp(19, 16);	// L13390
    int32_t v8545 = v8544;	// L13391
    crv_addr12 = v8545;	// L13392
    ap_int<26> v8546 = o_crv12;	// L13393
    bool v8547;
    ap_int<26> v8547_tmp = v8546;
    v8547 = v8547_tmp[20];	// L13394
    int32_t v8548 = v8547;	// L13395
    crv_mode12 = v8548;	// L13396
    ap_int<26> v8549 = o_crv12;	// L13397
    int16_t v8550;
    ap_int<26> v8550_tmp = v8549;
    v8550 = v8550_tmp(15, 0);	// L13398
    int32_t v8551 = v8550;	// L13399
    crv_raw12 = v8551;	// L13400
    ap_uint<17> v8552 = v8324.read();	// L13401
    ap_uint<17> rx_w12;	// L13402
    rx_w12 = v8552;	// L13403
    ap_uint<17> v8554 = v8325.read();	// L13404
    ap_uint<17> rx_e12;	// L13405
    rx_e12 = v8554;	// L13406
    ap_uint<17> v8556 = v8326.read();	// L13407
    ap_uint<17> rx_n12;	// L13408
    rx_n12 = v8556;	// L13409
    ap_uint<17> v8558 = v8327.read();	// L13410
    ap_uint<17> rx_s12;	// L13411
    rx_s12 = v8558;	// L13412
    half rxv12[4];	// L13413
    for (int v8561 = 0; v8561 < 4; v8561++) {	// L13414
      rxv12[v8561] = (double)0.000000;	// L13414
    }
    int32_t rxvld12[4];	// L13415
    for (int v8563 = 0; v8563 < 4; v8563++) {	// L13416
      rxvld12[v8563] = 0;	// L13416
    }
    ap_int<17> v8564 = rx_n12;	// L13417
    int16_t v8565;
    ap_int<17> v8565_tmp = v8564;
    v8565 = v8565_tmp(16, 1);	// L13418
    half v8566;
    union { uint16_t from; half to;} _converter_v8565_to_v8566;
    _converter_v8565_to_v8566.from = v8565;
    v8566 = _converter_v8565_to_v8566.to;	// L13419
    rxv12[0] = v8566;	// L13420
    ap_int<17> v8567 = rx_n12;	// L13421
    bool v8568;
    ap_int<17> v8568_tmp = v8567;
    v8568 = v8568_tmp[0];	// L13422
    int32_t v8569 = v8568;	// L13423
    rxvld12[0] = v8569;	// L13424
    ap_int<17> v8570 = rx_s12;	// L13425
    int16_t v8571;
    ap_int<17> v8571_tmp = v8570;
    v8571 = v8571_tmp(16, 1);	// L13426
    half v8572;
    union { uint16_t from; half to;} _converter_v8571_to_v8572;
    _converter_v8571_to_v8572.from = v8571;
    v8572 = _converter_v8571_to_v8572.to;	// L13427
    rxv12[1] = v8572;	// L13428
    ap_int<17> v8573 = rx_s12;	// L13429
    bool v8574;
    ap_int<17> v8574_tmp = v8573;
    v8574 = v8574_tmp[0];	// L13430
    int32_t v8575 = v8574;	// L13431
    rxvld12[1] = v8575;	// L13432
    ap_int<17> v8576 = rx_w12;	// L13433
    int16_t v8577;
    ap_int<17> v8577_tmp = v8576;
    v8577 = v8577_tmp(16, 1);	// L13434
    half v8578;
    union { uint16_t from; half to;} _converter_v8577_to_v8578;
    _converter_v8577_to_v8578.from = v8577;
    v8578 = _converter_v8577_to_v8578.to;	// L13435
    rxv12[2] = v8578;	// L13436
    ap_int<17> v8579 = rx_w12;	// L13437
    bool v8580;
    ap_int<17> v8580_tmp = v8579;
    v8580 = v8580_tmp[0];	// L13438
    int32_t v8581 = v8580;	// L13439
    rxvld12[2] = v8581;	// L13440
    ap_int<17> v8582 = rx_e12;	// L13441
    int16_t v8583;
    ap_int<17> v8583_tmp = v8582;
    v8583 = v8583_tmp(16, 1);	// L13442
    half v8584;
    union { uint16_t from; half to;} _converter_v8583_to_v8584;
    _converter_v8583_to_v8584.from = v8583;
    v8584 = _converter_v8583_to_v8584.to;	// L13443
    rxv12[3] = v8584;	// L13444
    ap_int<17> v8585 = rx_e12;	// L13445
    bool v8586;
    ap_int<17> v8586_tmp = v8585;
    v8586 = v8586_tmp[0];	// L13446
    int32_t v8587 = v8586;	// L13447
    rxvld12[3] = v8587;	// L13448
    l_S_d_5_d51: for (int d51 = 0; d51 < 4; d51++) {	// L13449
      int32_t v8589 = rxvld12[d51];	// L13450
      bool v8590 = v8589 == 1;	// L13451
      int32_t v8591 = hold_cnt12[d51];	// L13452
      bool v8592 = v8591 < 2;	// L13453
      bool v8593 = v8590 & v8592;	// L13454
      if (v8593) {	// L13455
        half v8594 = rxv12[d51];	// L13456
        int32_t v8595 = hold_cnt12[d51];	// L13457
        int v8596 = v8595;	// L13458
        hold_v12[d51][v8596] = v8594;	// L13459
        int32_t v8597 = hold_cnt12[d51];	// L13460
        ap_int<33> v8598 = v8597;	// L13461
        ap_int<33> v8599 = v8598 + 1;	// L13462
        int32_t v8600 = v8599;	// L13463
        hold_cnt12[d51] = v8600;	// L13464
      }
    }
    int32_t pc12;	// L13467
    pc12 = -1;	// L13468
    int32_t v8602 = fetch_en12;	// L13469
    bool v8603 = v8602 == 1;	// L13470
    if (v8603) {	// L13471
      int32_t v8604 = instr_cnt12;	// L13472
      pc12 = v8604;	// L13473
    }
    int32_t instr12;	// L13475
    instr12 = 0;	// L13476
    int32_t v8606 = pc12;	// L13477
    bool v8607 = v8606 >= 0;	// L13478
    if (v8607) {	// L13479
      int32_t v8608 = pc12;	// L13480
      int v8609 = v8608;	// L13481
      int32_t v8610 = irf12[v8609];	// L13482
      instr12 = v8610;	// L13483
    }
    int32_t v8611 = instr12;	// L13485
    int32_t v8612 = v8611 & 15;	// L13486
    int32_t op12;	// L13487
    op12 = v8612;	// L13488
    int32_t v8614 = instr12;	// L13489
    int32_t v8615 = v8614 >> 4;	// L13490
    int32_t v8616 = v8615 & 15;	// L13491
    int32_t dst12;	// L13492
    dst12 = v8616;	// L13493
    int32_t v8618 = instr12;	// L13494
    int32_t v8619 = v8618 >> 8;	// L13495
    int32_t v8620 = v8619 & 15;	// L13496
    int32_t s112;	// L13497
    s112 = v8620;	// L13498
    int32_t v8622 = instr12;	// L13499
    int32_t v8623 = v8622 >> 12;	// L13500
    int32_t v8624 = v8623 & 15;	// L13501
    int32_t s212;	// L13502
    s212 = v8624;	// L13503
    half a12;	// L13504
    a12 = (double)0.000000;	// L13505
    half b12;	// L13506
    b12 = (double)0.000000;	// L13507
    int32_t v8628 = s112;	// L13508
    bool v8629 = v8628 >= 12;	// L13509
    if (v8629) {	// L13510
      int32_t v8630 = s112;	// L13511
      int32_t v8631 = v8630 & 3;	// L13512
      int v8632 = v8631;	// L13513
      half v8633 = hold_v12[v8632][0];	// L13514
      a12 = v8633;	// L13515
    } else {
      int32_t v8634 = s112;	// L13517
      int v8635 = v8634;	// L13518
      half v8636 = drf12[v8635];	// L13519
      a12 = v8636;	// L13520
    }
    int32_t v8637 = s212;	// L13522
    bool v8638 = v8637 >= 12;	// L13523
    if (v8638) {	// L13524
      int32_t v8639 = s212;	// L13525
      int32_t v8640 = v8639 & 3;	// L13526
      int v8641 = v8640;	// L13527
      half v8642 = hold_v12[v8641][0];	// L13528
      b12 = v8642;	// L13529
    } else {
      int32_t v8643 = s212;	// L13531
      int v8644 = v8643;	// L13532
      half v8645 = drf12[v8644];	// L13533
      b12 = v8645;	// L13534
    }
    int32_t a_vld12;	// L13536
    a_vld12 = 1;	// L13537
    int32_t b_vld12;	// L13538
    b_vld12 = 1;	// L13539
    int32_t v8648 = s112;	// L13540
    bool v8649 = v8648 >= 12;	// L13541
    if (v8649) {	// L13542
      a_vld12 = 0;	// L13543
      int32_t v8650 = s112;	// L13544
      int32_t v8651 = v8650 & 3;	// L13545
      int v8652 = v8651;	// L13546
      int32_t v8653 = hold_cnt12[v8652];	// L13547
      bool v8654 = v8653 > 0;	// L13548
      if (v8654) {	// L13549
        a_vld12 = 1;	// L13550
      }
    }
    int32_t v8655 = s212;	// L13553
    bool v8656 = v8655 >= 12;	// L13554
    if (v8656) {	// L13555
      b_vld12 = 0;	// L13556
      int32_t v8657 = s212;	// L13557
      int32_t v8658 = v8657 & 3;	// L13558
      int v8659 = v8658;	// L13559
      int32_t v8660 = hold_cnt12[v8659];	// L13560
      bool v8661 = v8660 > 0;	// L13561
      if (v8661) {	// L13562
        b_vld12 = 1;	// L13563
      }
    }
    int32_t v8662 = s112;	// L13566
    bool v8663 = v8662 < 8;	// L13567
    int32_t v8664 = dsmask12;	// L13568
    int32_t v8665 = v8664 >> v8662;	// L13569
    int32_t v8666 = v8665 & 1;	// L13570
    bool v8667 = v8666 == 1;	// L13571
    bool v8668 = v8663 & v8667;	// L13572
    if (v8668) {	// L13573
      int32_t v8669 = s112;	// L13574
      int v8670 = v8669;	// L13575
      int32_t v8671 = drf_full12[v8670];	// L13576
      bool v8672 = v8671 == 0;	// L13577
      if (v8672) {	// L13578
        a_vld12 = 0;	// L13579
      }
    }
    int32_t v8673 = s212;	// L13582
    bool v8674 = v8673 < 8;	// L13583
    int32_t v8675 = dsmask12;	// L13584
    int32_t v8676 = v8675 >> v8673;	// L13585
    int32_t v8677 = v8676 & 1;	// L13586
    bool v8678 = v8677 == 1;	// L13587
    bool v8679 = v8674 & v8678;	// L13588
    if (v8679) {	// L13589
      int32_t v8680 = s212;	// L13590
      int v8681 = v8680;	// L13591
      int32_t v8682 = drf_full12[v8681];	// L13592
      bool v8683 = v8682 == 0;	// L13593
      if (v8683) {	// L13594
        b_vld12 = 0;	// L13595
      }
    }
    int32_t binop12;	// L13598
    binop12 = 0;	// L13599
    int32_t v8685 = op12;	// L13600
    bool v8686 = v8685 == 0;	// L13601
    bool v8687 = v8685 == 1;	// L13602
    bool v8688 = v8685 == 2;	// L13603
    bool v8689 = v8685 == 8;	// L13604
    bool v8690 = v8685 == 9;	// L13605
    bool v8691 = v8686 | v8687;	// L13606
    bool v8692 = v8691 | v8688;	// L13607
    bool v8693 = v8692 | v8689;	// L13608
    bool v8694 = v8693 | v8690;	// L13609
    if (v8694) {	// L13610
      binop12 = 1;	// L13611
    }
    int32_t grant12;	// L13613
    grant12 = 0;	// L13614
    int32_t v8696 = pc12;	// L13615
    bool v8697 = v8696 >= 0;	// L13616
    if (v8697) {	// L13617
      grant12 = 1;	// L13618
    }
    int32_t v8698 = pc12;	// L13620
    bool v8699 = v8698 >= 0;	// L13621
    int32_t v8700 = a_vld12;	// L13622
    bool v8701 = v8700 == 0;	// L13623
    int32_t v8702 = binop12;	// L13624
    bool v8703 = v8702 == 1;	// L13625
    int32_t v8704 = b_vld12;	// L13626
    bool v8705 = v8704 == 0;	// L13627
    bool v8706 = v8703 & v8705;	// L13628
    bool v8707 = v8701 | v8706;	// L13629
    bool v8708 = v8699 & v8707;	// L13630
    if (v8708) {	// L13631
      grant12 = 0;	// L13632
    }
    int32_t v8709 = grant12;	// L13634
    bool v8710 = v8709 == 1;	// L13635
    if (v8710) {	// L13636
      int32_t v8711 = instr_cnt12;	// L13637
      int32_t v8712 = cfg_isz12;	// L13638
      bool v8713 = v8711 == v8712;	// L13639
      if (v8713) {	// L13640
        instr_cnt12 = 0;	// L13641
        int32_t v8714 = iter_cnt12;	// L13642
        int32_t v8715 = cfg_itsz12;	// L13643
        ap_int<33> v8716 = v8715;	// L13644
        ap_int<33> v8717 = v8716 - 1;	// L13645
        ap_int<33> v8718 = v8714;	// L13646
        bool v8719 = v8718 == v8717;	// L13647
        if (v8719) {	// L13648
          fetch_en12 = 0;	// L13649
        } else {
          int32_t v8720 = iter_cnt12;	// L13651
          ap_int<33> v8721 = v8720;	// L13652
          ap_int<33> v8722 = v8721 + 1;	// L13653
          int32_t v8723 = v8722;	// L13654
          iter_cnt12 = v8723;	// L13655
        }
      } else {
        int32_t v8724 = instr_cnt12;	// L13658
        ap_int<33> v8725 = v8724;	// L13659
        ap_int<33> v8726 = v8725 + 1;	// L13660
        int32_t v8727 = v8726;	// L13661
        instr_cnt12 = v8727;	// L13662
      }
    }
    int32_t c112;	// L13665
    c112 = -1;	// L13666
    int32_t c212;	// L13667
    c212 = -1;	// L13668
    int32_t v8730 = grant12;	// L13669
    bool v8731 = v8730 == 1;	// L13670
    int32_t v8732 = s112;	// L13671
    bool v8733 = v8732 >= 12;	// L13672
    bool v8734 = v8731 & v8733;	// L13673
    if (v8734) {	// L13674
      int32_t v8735 = s112;	// L13675
      int32_t v8736 = v8735 & 3;	// L13676
      c112 = v8736;	// L13677
    }
    int32_t v8737 = grant12;	// L13679
    bool v8738 = v8737 == 1;	// L13680
    int32_t v8739 = s212;	// L13681
    bool v8740 = v8739 >= 12;	// L13682
    bool v8741 = v8738 & v8740;	// L13683
    if (v8741) {	// L13684
      int32_t v8742 = s212;	// L13685
      int32_t v8743 = v8742 & 3;	// L13686
      c212 = v8743;	// L13687
    }
    int32_t v8744 = c112;	// L13689
    bool v8745 = v8744 >= 0;	// L13690
    if (v8745) {	// L13691
      int32_t v8746 = c112;	// L13692
      int v8747 = v8746;	// L13693
      half v8748 = hold_v12[v8747][1];	// L13694
      hold_v12[v8747][0] = v8748;	// L13695
      int32_t v8749 = c112;	// L13696
      int v8750 = v8749;	// L13697
      int32_t v8751 = hold_cnt12[v8750];	// L13698
      ap_int<33> v8752 = v8751;	// L13699
      ap_int<33> v8753 = v8752 - 1;	// L13700
      int32_t v8754 = v8753;	// L13701
      hold_cnt12[v8750] = v8754;	// L13702
    }
    int32_t v8755 = c212;	// L13704
    bool v8756 = v8755 >= 0;	// L13705
    int32_t v8757 = c112;	// L13706
    bool v8758 = v8755 != v8757;	// L13707
    bool v8759 = v8756 & v8758;	// L13708
    if (v8759) {	// L13709
      int32_t v8760 = c212;	// L13710
      int v8761 = v8760;	// L13711
      half v8762 = hold_v12[v8761][1];	// L13712
      hold_v12[v8761][0] = v8762;	// L13713
      int32_t v8763 = c212;	// L13714
      int v8764 = v8763;	// L13715
      int32_t v8765 = hold_cnt12[v8764];	// L13716
      ap_int<33> v8766 = v8765;	// L13717
      ap_int<33> v8767 = v8766 - 1;	// L13718
      int32_t v8768 = v8767;	// L13719
      hold_cnt12[v8764] = v8768;	// L13720
    }
    int32_t v8769 = grant12;	// L13722
    bool v8770 = v8769 == 1;	// L13723
    int32_t v8771 = s112;	// L13724
    bool v8772 = v8771 < 8;	// L13725
    int32_t v8773 = dsmask12;	// L13726
    int32_t v8774 = v8773 >> v8771;	// L13727
    int32_t v8775 = v8774 & 1;	// L13728
    bool v8776 = v8775 == 1;	// L13729
    bool v8777 = v8770 & v8772;	// L13730
    bool v8778 = v8777 & v8776;	// L13731
    if (v8778) {	// L13732
      int32_t v8779 = s112;	// L13733
      int v8780 = v8779;	// L13734
      drf_full12[v8780] = 0;	// L13735
    }
    int32_t v8781 = grant12;	// L13737
    bool v8782 = v8781 == 1;	// L13738
    int32_t v8783 = s212;	// L13739
    bool v8784 = v8783 < 8;	// L13740
    int32_t v8785 = dsmask12;	// L13741
    int32_t v8786 = v8785 >> v8783;	// L13742
    int32_t v8787 = v8786 & 1;	// L13743
    bool v8788 = v8787 == 1;	// L13744
    bool v8789 = v8782 & v8784;	// L13745
    bool v8790 = v8789 & v8788;	// L13746
    if (v8790) {	// L13747
      int32_t v8791 = s212;	// L13748
      int v8792 = v8791;	// L13749
      drf_full12[v8792] = 0;	// L13750
    }
    half res12;	// L13752
    res12 = (double)0.000000;	// L13753
    int32_t v8794 = op12;	// L13754
    bool v8795 = v8794 == 0;	// L13755
    if (v8795) {	// L13756
      half v8796 = a12;	// L13757
      half v8797 = b12;	// L13758
      half v8798 = v8796 + v8797;	// L13759
      res12 = v8798;	// L13760
    } else {
      int32_t v8799 = op12;	// L13762
      bool v8800 = v8799 == 1;	// L13763
      if (v8800) {	// L13764
        half v8801 = a12;	// L13765
        half v8802 = b12;	// L13766
        half v8803 = v8801 - v8802;	// L13767
        res12 = v8803;	// L13768
      } else {
        int32_t v8804 = op12;	// L13770
        bool v8805 = v8804 == 2;	// L13771
        if (v8805) {	// L13772
          half v8806 = a12;	// L13773
          half v8807 = b12;	// L13774
          half v8808 = v8806 * v8807;	// L13775
          res12 = v8808;	// L13776
        } else {
          int32_t v8809 = op12;	// L13778
          bool v8810 = v8809 == 8;	// L13779
          if (v8810) {	// L13780
            half v8811 = a12;	// L13781
            half v8812 = b12;	// L13782
            bool v8813 = v8811 >= v8812;	// L13783
            if (v8813) {	// L13784
              res12 = (double)1.000000;	// L13785
            } else {
              res12 = (double)-1.000000;	// L13787
            }
          } else {
            int32_t v8814 = op12;	// L13790
            bool v8815 = v8814 == 9;	// L13791
            if (v8815) {	// L13792
              half v8816 = a12;	// L13793
              half v8817 = b12;	// L13794
              bool v8818 = v8816 < v8817;	// L13795
              if (v8818) {	// L13796
                res12 = (double)1.000000;	// L13797
              } else {
                res12 = (double)-1.000000;	// L13799
              }
            } else {
              half v8819 = a12;	// L13802
              res12 = v8819;	// L13803
            }
          }
        }
      }
    }
    int32_t v8820 = a_vld12;	// L13809
    int32_t res_vld12;	// L13810
    res_vld12 = v8820;	// L13811
    int32_t v8822 = op12;	// L13812
    bool v8823 = v8822 == 0;	// L13813
    bool v8824 = v8822 == 1;	// L13814
    bool v8825 = v8822 == 2;	// L13815
    bool v8826 = v8822 == 8;	// L13816
    bool v8827 = v8822 == 9;	// L13817
    bool v8828 = v8823 | v8824;	// L13818
    bool v8829 = v8828 | v8825;	// L13819
    bool v8830 = v8829 | v8826;	// L13820
    bool v8831 = v8830 | v8827;	// L13821
    if (v8831) {	// L13822
      int32_t v8832 = a_vld12;	// L13823
      int32_t v8833 = b_vld12;	// L13824
      int64_t v8834 = v8832;	// L13825
      int64_t v8835 = v8833;	// L13826
      int64_t v8836 = v8834 * v8835;	// L13827
      int32_t v8837 = v8836;	// L13828
      res_vld12 = v8837;	// L13829
    }
    int32_t v8838 = grant12;	// L13831
    bool v8839 = v8838 == 0;	// L13832
    if (v8839) {	// L13833
      res_vld12 = 0;	// L13834
    }
    int32_t v8840 = grant12;	// L13836
    bool v8841 = v8840 == 1;	// L13837
    int32_t v8842 = op12;	// L13838
    bool v8843 = v8842 == 8;	// L13839
    bool v8844 = v8841 & v8843;	// L13840
    if (v8844) {	// L13841
      condition_reg12 = 0;	// L13842
      half v8845 = a12;	// L13843
      half v8846 = b12;	// L13844
      bool v8847 = v8845 >= v8846;	// L13845
      if (v8847) {	// L13846
        condition_reg12 = 1;	// L13847
      }
    }
    int32_t v8848 = grant12;	// L13850
    bool v8849 = v8848 == 1;	// L13851
    int32_t v8850 = op12;	// L13852
    bool v8851 = v8850 == 9;	// L13853
    bool v8852 = v8849 & v8851;	// L13854
    if (v8852) {	// L13855
      condition_reg12 = 0;	// L13856
      half v8853 = a12;	// L13857
      half v8854 = b12;	// L13858
      bool v8855 = v8853 < v8854;	// L13859
      if (v8855) {	// L13860
        condition_reg12 = 1;	// L13861
      }
    }
    ap_uint<17> tx_n12;	// L13864
    tx_n12 = 0;	// L13865
    ap_uint<17> tx_s12;	// L13866
    tx_s12 = 0;	// L13867
    ap_uint<17> tx_w12;	// L13868
    tx_w12 = 0;	// L13869
    ap_uint<17> tx_e12;	// L13870
    tx_e12 = 0;	// L13871
    int32_t is_rtr12;	// L13872
    is_rtr12 = 0;	// L13873
    int32_t do_inj12;	// L13874
    do_inj12 = 0;	// L13875
    int32_t v8862 = op12;	// L13876
    bool v8863 = v8862 >= 4;	// L13877
    ap_int<33> v8864 = v8862;	// L13878
    bool v8865 = v8864 <= 7;	// L13879
    bool v8866 = v8863 & v8865;	// L13880
    if (v8866) {	// L13881
      is_rtr12 = 1;	// L13882
      do_inj12 = 1;	// L13883
    }
    int32_t v8867 = op12;	// L13885
    bool v8868 = v8867 >= 12;	// L13886
    ap_int<33> v8869 = v8867;	// L13887
    bool v8870 = v8869 <= 15;	// L13888
    bool v8871 = v8868 & v8870;	// L13889
    if (v8871) {	// L13890
      is_rtr12 = 1;	// L13891
      int32_t v8872 = condition_reg12;	// L13892
      bool v8873 = v8872 == 1;	// L13893
      if (v8873) {	// L13894
        do_inj12 = 1;	// L13895
      }
    }
    int32_t v8874 = is_rtr12;	// L13898
    bool v8875 = v8874 == 1;	// L13899
    if (v8875) {	// L13900
      int32_t v8876 = do_inj12;	// L13901
      bool v8877 = v8876 == 1;	// L13902
      ap_int<26> v8878 = csd_pkt12;	// L13903
      bool v8879;
      ap_int<26> v8879_tmp = v8878;
      v8879 = v8879_tmp[25];	// L13904
      int32_t v8880 = v8879;	// L13905
      bool v8881 = v8880 == 0;	// L13906
      bool v8882 = v8877 & v8881;	// L13907
      if (v8882) {	// L13908
        half v8883 = res12;	// L13909
        uint16_t v8884;
        union { half from; uint16_t to;} _converter_v8883_to_v8884;
        _converter_v8883_to_v8884.from = v8883;
        v8884 = _converter_v8883_to_v8884.to;	// L13910
        ap_int<26> v8885 = csd_pkt12;	// L13911
        ap_int<26> v8886;
        ap_int<26> v8886_tmp = v8885;
        v8886_tmp(15, 0) = v8884;
        v8886 = v8886_tmp;	// L13912
        csd_pkt12 = v8886;	// L13913
        int32_t v8887 = dst12;	// L13914
        ap_uint<4> v8888 = v8887;	// L13915
        ap_int<26> v8889 = csd_pkt12;	// L13916
        ap_int<26> v8890;
        ap_int<26> v8890_tmp = v8889;
        v8890_tmp(19, 16) = v8888;
        v8890 = v8890_tmp;	// L13917
        csd_pkt12 = v8890;	// L13918
        int32_t v8891 = s212;	// L13919
        ap_uint<4> v8892 = v8891;	// L13920
        ap_int<26> v8893 = csd_pkt12;	// L13921
        ap_int<26> v8894;
        ap_int<26> v8894_tmp = v8893;
        v8894_tmp(24, 21) = v8892;
        v8894 = v8894_tmp;	// L13922
        csd_pkt12 = v8894;	// L13923
        int32_t v8895 = res_vld12;	// L13924
        bool v8896 = v8895;	// L13925
        ap_int<26> v8897 = csd_pkt12;	// L13926
        ap_int<26> v8898;
        ap_int<26> v8898_tmp = v8897;
        v8898_tmp[25] = v8896;        v8898 = v8898_tmp;	// L13927
        csd_pkt12 = v8898;	// L13928
        int32_t v8899 = op12;	// L13929
        int32_t v8900 = v8899 & 3;	// L13930
        csd_dir12 = v8900;	// L13931
      }
    } else {
      int32_t v8901 = dst12;	// L13934
      bool v8902 = v8901 >= 12;	// L13935
      if (v8902) {	// L13936
        ap_uint<17> tw12;	// L13937
        tw12 = 0;	// L13938
        int32_t v8904 = res_vld12;	// L13939
        bool v8905 = v8904;	// L13940
        ap_int<17> v8906 = tw12;	// L13941
        ap_int<17> v8907;
        ap_int<17> v8907_tmp = v8906;
        v8907_tmp[0] = v8905;        v8907 = v8907_tmp;	// L13942
        tw12 = v8907;	// L13943
        half v8908 = res12;	// L13944
        uint16_t v8909;
        union { half from; uint16_t to;} _converter_v8908_to_v8909;
        _converter_v8908_to_v8909.from = v8908;
        v8909 = _converter_v8908_to_v8909.to;	// L13945
        ap_int<17> v8910 = tw12;	// L13946
        ap_int<17> v8911;
        ap_int<17> v8911_tmp = v8910;
        v8911_tmp(16, 1) = v8909;
        v8911 = v8911_tmp;	// L13947
        tw12 = v8911;	// L13948
        int32_t v8912 = dst12;	// L13949
        int32_t v8913 = v8912 & 3;	// L13950
        bool v8914 = v8913 == 0;	// L13951
        if (v8914) {	// L13952
          ap_int<17> v8915 = tw12;	// L13953
          tx_n12 = v8915;	// L13954
        } else {
          int32_t v8916 = dst12;	// L13956
          int32_t v8917 = v8916 & 3;	// L13957
          bool v8918 = v8917 == 1;	// L13958
          if (v8918) {	// L13959
            ap_int<17> v8919 = tw12;	// L13960
            tx_s12 = v8919;	// L13961
          } else {
            int32_t v8920 = dst12;	// L13963
            int32_t v8921 = v8920 & 3;	// L13964
            bool v8922 = v8921 == 2;	// L13965
            if (v8922) {	// L13966
              ap_int<17> v8923 = tw12;	// L13967
              tx_w12 = v8923;	// L13968
            } else {
              ap_int<17> v8924 = tw12;	// L13970
              tx_e12 = v8924;	// L13971
            }
          }
        }
      } else {
        int32_t v8925 = res_vld12;	// L13976
        bool v8926 = v8925 == 1;	// L13977
        if (v8926) {	// L13978
          int32_t v8927 = dst12;	// L13979
          bool v8928 = v8927 < 8;	// L13980
          int32_t v8929 = dsmask12;	// L13981
          int32_t v8930 = v8929 >> v8927;	// L13982
          int32_t v8931 = v8930 & 1;	// L13983
          bool v8932 = v8931 == 1;	// L13984
          bool v8933 = v8928 & v8932;	// L13985
          if (v8933) {	// L13986
            int32_t v8934 = dst12;	// L13987
            int v8935 = v8934;	// L13988
            int32_t v8936 = drf_full12[v8935];	// L13989
            bool v8937 = v8936 == 0;	// L13990
            if (v8937) {	// L13991
              half v8938 = res12;	// L13992
              int32_t v8939 = dst12;	// L13993
              int v8940 = v8939;	// L13994
              drf12[v8940] = v8938;	// L13995
              int32_t v8941 = dst12;	// L13996
              int v8942 = v8941;	// L13997
              drf_full12[v8942] = 1;	// L13998
            }
          } else {
            half v8943 = res12;	// L14001
            int32_t v8944 = dst12;	// L14002
            int v8945 = v8944;	// L14003
            drf12[v8945] = v8943;	// L14004
          }
        }
      }
    }
    ap_int<17> v8946 = tx_n12;	// L14009
    txn_r12 = v8946;	// L14010
    ap_int<17> v8947 = tx_s12;	// L14011
    txs_r12 = v8947;	// L14012
    ap_int<17> v8948 = tx_w12;	// L14013
    txw_r12 = v8948;	// L14014
    ap_int<17> v8949 = tx_e12;	// L14015
    txe_r12 = v8949;	// L14016
    int32_t v8950 = crv_vld12;	// L14017
    bool v8951 = v8950 == 1;	// L14018
    if (v8951) {	// L14019
      int32_t v8952 = crv_mode12;	// L14020
      bool v8953 = v8952 == 1;	// L14021
      if (v8953) {	// L14022
        int32_t v8954 = crv_addr12;	// L14023
        int32_t v8955 = v8954 >> 3;	// L14024
        int32_t v8956 = v8955 & 1;	// L14025
        bool v8957 = v8956 == 1;	// L14026
        if (v8957) {	// L14027
          int32_t v8958 = crv_raw12;	// L14028
          int32_t v8959 = crv_addr12;	// L14029
          int32_t v8960 = v8959 & 7;	// L14030
          int v8961 = v8960;	// L14031
          irf12[v8961] = v8958;	// L14032
        } else {
          int32_t v8962 = crv_addr12;	// L14034
          bool v8963 = v8962 == 0;	// L14035
          if (v8963) {	// L14036
            int32_t v8964 = crv_raw12;	// L14037
            int32_t v8965 = v8964 & 255;	// L14038
            dsmask12 = v8965;	// L14039
            int32_t v8966 = crv_raw12;	// L14040
            int32_t v8967 = v8966 >> 8;	// L14041
            int32_t v8968 = v8967 & 7;	// L14042
            cfg_isz12 = v8968;	// L14043
            int32_t v8969 = crv_raw12;	// L14044
            int32_t v8970 = v8969 >> 15;	// L14045
            int32_t v8971 = v8970 & 1;	// L14046
            bool v8972 = v8971 == 1;	// L14047
            if (v8972) {	// L14048
              fetch_en12 = 1;	// L14049
              instr_cnt12 = 0;	// L14050
              iter_cnt12 = 0;	// L14051
            }
          } else {
            int32_t v8973 = crv_addr12;	// L14054
            bool v8974 = v8973 == 1;	// L14055
            if (v8974) {	// L14056
              int32_t v8975 = crv_raw12;	// L14057
              int32_t v8976 = v8975 & 255;	// L14058
              cfg_itsz12 = v8976;	// L14059
            }
          }
        }
      } else {
        int32_t v8977 = crv_addr12;	// L14064
        bool v8978 = v8977 < 8;	// L14065
        int32_t v8979 = dsmask12;	// L14066
        int32_t v8980 = v8979 >> v8977;	// L14067
        int32_t v8981 = v8980 & 1;	// L14068
        bool v8982 = v8981 == 1;	// L14069
        bool v8983 = v8978 & v8982;	// L14070
        if (v8983) {	// L14071
          int32_t v8984 = crv_addr12;	// L14072
          int v8985 = v8984;	// L14073
          int32_t v8986 = drf_full12[v8985];	// L14074
          bool v8987 = v8986 == 0;	// L14075
          if (v8987) {	// L14076
            half v8988 = crv_data12;	// L14077
            int32_t v8989 = crv_addr12;	// L14078
            int v8990 = v8989;	// L14079
            drf12[v8990] = v8988;	// L14080
            int32_t v8991 = crv_addr12;	// L14081
            int v8992 = v8991;	// L14082
            drf_full12[v8992] = 1;	// L14083
          }
        } else {
          half v8993 = crv_data12;	// L14086
          int32_t v8994 = crv_addr12;	// L14087
          int v8995 = v8994;	// L14088
          drf12[v8995] = v8993;	// L14089
        }
      }
    }
  }
}

void node_3_1(
  hls::stream< ap_uint<26> >& v8996,
  hls::stream< ap_uint<26> >& v8997,
  hls::stream< ap_uint<26> >& v8998,
  hls::stream< ap_uint<26> >& v8999,
  hls::stream< ap_uint<17> >& v9000,
  hls::stream< ap_uint<17> >& v9001,
  hls::stream< ap_uint<17> >& v9002,
  hls::stream< ap_uint<17> >& v9003,
  hls::stream< int32_t >& v9004,
  hls::stream< int32_t >& v9005,
  hls::stream< int32_t >& v9006,
  hls::stream< int32_t >& v9007,
  hls::stream< ap_uint<26> >& v9008,
  hls::stream< ap_uint<26> >& v9009,
  hls::stream< ap_uint<26> >& v9010,
  hls::stream< ap_uint<26> >& v9011,
  hls::stream< int32_t >& v9012,
  hls::stream< int32_t >& v9013,
  hls::stream< int32_t >& v9014,
  hls::stream< int32_t >& v9015,
  hls::stream< ap_uint<17> >& v9016,
  hls::stream< ap_uint<17> >& v9017,
  hls::stream< ap_uint<17> >& v9018,
  hls::stream< ap_uint<17> >& v9019
) {	// L14096
  int32_t irf13[8];	// L14127
  for (int v9021 = 0; v9021 < 8; v9021++) {	// L14128
    irf13[v9021] = 0;	// L14128
  }
  half drf13[8];	// L14129
  #pragma HLS array_partition variable=drf13 complete dim=1

  for (int v9023 = 0; v9023 < 8; v9023++) {	// L14130
    drf13[v9023] = (double)0.000000;	// L14130
  }
  int32_t drf_full13[8];	// L14131
  #pragma HLS array_partition variable=drf_full13 complete dim=1

  for (int v9025 = 0; v9025 < 8; v9025++) {	// L14132
    drf_full13[v9025] = 0;	// L14132
  }
  int32_t dsmask13;	// L14133
  dsmask13 = 0;	// L14134
  int32_t crv_vld13;	// L14135
  crv_vld13 = 0;	// L14136
  half crv_data13;	// L14137
  crv_data13 = (double)0.000000;	// L14138
  int32_t crv_addr13;	// L14139
  crv_addr13 = 0;	// L14140
  int32_t crv_mode13;	// L14141
  crv_mode13 = 0;	// L14142
  int32_t crv_raw13;	// L14143
  crv_raw13 = 0;	// L14144
  int32_t csd_vld13;	// L14145
  csd_vld13 = 0;	// L14146
  ap_uint<26> csd_pkt13;	// L14147
  csd_pkt13 = 0;	// L14148
  int32_t csd_dir13;	// L14149
  csd_dir13 = 0;	// L14150
  int32_t row_id13;	// L14151
  row_id13 = 3;	// L14152
  int32_t col_id13;	// L14153
  col_id13 = 1;	// L14154
  ap_uint<26> oe_r13;	// L14155
  oe_r13 = 0;	// L14156
  ap_uint<26> ow_r13;	// L14157
  ow_r13 = 0;	// L14158
  ap_uint<26> on_r13;	// L14159
  on_r13 = 0;	// L14160
  ap_uint<26> os_r13;	// L14161
  os_r13 = 0;	// L14162
  ap_uint<17> txn_r13;	// L14163
  txn_r13 = 0;	// L14164
  ap_uint<17> txs_r13;	// L14165
  txs_r13 = 0;	// L14166
  ap_uint<17> txw_r13;	// L14167
  txw_r13 = 0;	// L14168
  ap_uint<17> txe_r13;	// L14169
  txe_r13 = 0;	// L14170
  half hold_v13[4][2];	// L14171
  #pragma HLS array_partition variable=hold_v13 complete dim=1
  #pragma HLS array_partition variable=hold_v13 complete dim=2

  for (int v9046 = 0; v9046 < 4; v9046++) {	// L14172
    for (int v9047 = 0; v9047 < 2; v9047++) {	// L14172
      hold_v13[v9046][v9047] = (double)0.000000;	// L14172
    }
  }
  int32_t hold_cnt13[4];	// L14173
  #pragma HLS array_partition variable=hold_cnt13 complete dim=1

  for (int v9049 = 0; v9049 < 4; v9049++) {	// L14174
    hold_cnt13[v9049] = 0;	// L14174
  }
  ap_uint<26> rbuf13[4][2];	// L14175
  #pragma HLS array_partition variable=rbuf13 complete dim=1
  #pragma HLS array_partition variable=rbuf13 complete dim=2

  for (int v9051 = 0; v9051 < 4; v9051++) {	// L14176
    for (int v9052 = 0; v9052 < 2; v9052++) {	// L14176
      rbuf13[v9051][v9052] = 0;	// L14176
    }
  }
  int32_t rbcnt13[4];	// L14177
  #pragma HLS array_partition variable=rbcnt13 complete dim=1

  for (int v9054 = 0; v9054 < 4; v9054++) {	// L14178
    rbcnt13[v9054] = 0;	// L14178
  }
  int32_t rcred13[4];	// L14179
  #pragma HLS array_partition variable=rcred13 complete dim=1

  for (int v9056 = 0; v9056 < 4; v9056++) {	// L14180
    rcred13[v9056] = 0;	// L14180
  }
  int32_t cre_r13;	// L14181
  cre_r13 = 2;	// L14182
  int32_t crw_r13;	// L14183
  crw_r13 = 2;	// L14184
  int32_t crs_r13;	// L14185
  crs_r13 = 2;	// L14186
  int32_t crn_r13;	// L14187
  crn_r13 = 2;	// L14188
  int32_t cfg_isz13;	// L14189
  cfg_isz13 = 0;	// L14190
  int32_t cfg_itsz13;	// L14191
  cfg_itsz13 = 0;	// L14192
  int32_t fetch_en13;	// L14193
  fetch_en13 = 0;	// L14194
  int32_t instr_cnt13;	// L14195
  instr_cnt13 = 0;	// L14196
  int32_t iter_cnt13;	// L14197
  iter_cnt13 = 0;	// L14198
  int32_t condition_reg13;	// L14199
  condition_reg13 = 0;	// L14200
  l_S_t_0_t13: for (int t13 = 0; t13 < 8; t13++) {	// L14201
  #pragma HLS pipeline II=1
    ap_int<26> v9068 = oe_r13;	// L14202
    v8996.write(v9068);	// L14203
    ap_int<26> v9069 = ow_r13;	// L14204
    v8997.write(v9069);	// L14205
    ap_int<26> v9070 = os_r13;	// L14206
    v8998.write(v9070);	// L14207
    ap_int<26> v9071 = on_r13;	// L14208
    v8999.write(v9071);	// L14209
    ap_int<17> v9072 = txe_r13;	// L14210
    v9000.write(v9072);	// L14211
    ap_int<17> v9073 = txw_r13;	// L14212
    v9001.write(v9073);	// L14213
    ap_int<17> v9074 = txs_r13;	// L14214
    v9002.write(v9074);	// L14215
    ap_int<17> v9075 = txn_r13;	// L14216
    v9003.write(v9075);	// L14217
    int32_t v9076 = cre_r13;	// L14218
    v9004.write(v9076);	// L14219
    int32_t v9077 = crw_r13;	// L14220
    v9005.write(v9077);	// L14221
    int32_t v9078 = crs_r13;	// L14222
    v9006.write(v9078);	// L14223
    int32_t v9079 = crn_r13;	// L14224
    v9007.write(v9079);	// L14225
    ap_uint<26> v9080 = v9008.read();	// L14226
    ap_uint<26> p_w13;	// L14227
    p_w13 = v9080;	// L14228
    ap_uint<26> v9082 = v9009.read();	// L14229
    ap_uint<26> p_e13;	// L14230
    p_e13 = v9082;	// L14231
    ap_uint<26> v9084 = v9010.read();	// L14232
    ap_uint<26> p_n13;	// L14233
    p_n13 = v9084;	// L14234
    ap_uint<26> v9086 = v9011.read();	// L14235
    ap_uint<26> p_s13;	// L14236
    p_s13 = v9086;	// L14237
    int32_t v9088 = v9012.read();	// L14238
    int32_t v9089 = rcred13[0];	// L14239
    ap_int<33> v9090 = v9089;	// L14240
    ap_int<33> v9091 = v9088;	// L14241
    ap_int<33> v9092 = v9090 + v9091;	// L14242
    int32_t v9093 = v9092;	// L14243
    rcred13[0] = v9093;	// L14244
    int32_t v9094 = v9013.read();	// L14245
    int32_t v9095 = rcred13[1];	// L14246
    ap_int<33> v9096 = v9095;	// L14247
    ap_int<33> v9097 = v9094;	// L14248
    ap_int<33> v9098 = v9096 + v9097;	// L14249
    int32_t v9099 = v9098;	// L14250
    rcred13[1] = v9099;	// L14251
    int32_t v9100 = v9014.read();	// L14252
    int32_t v9101 = rcred13[2];	// L14253
    ap_int<33> v9102 = v9101;	// L14254
    ap_int<33> v9103 = v9100;	// L14255
    ap_int<33> v9104 = v9102 + v9103;	// L14256
    int32_t v9105 = v9104;	// L14257
    rcred13[2] = v9105;	// L14258
    int32_t v9106 = v9015.read();	// L14259
    int32_t v9107 = rcred13[3];	// L14260
    ap_int<33> v9108 = v9107;	// L14261
    ap_int<33> v9109 = v9106;	// L14262
    ap_int<33> v9110 = v9108 + v9109;	// L14263
    int32_t v9111 = v9110;	// L14264
    rcred13[3] = v9111;	// L14265
    ap_uint<26> fin13[4];	// L14266
    for (int v9113 = 0; v9113 < 4; v9113++) {	// L14267
      fin13[v9113] = 0;	// L14267
    }
    ap_int<26> v9114 = p_w13;	// L14268
    fin13[0] = v9114;	// L14269
    ap_int<26> v9115 = p_e13;	// L14270
    fin13[1] = v9115;	// L14271
    ap_int<26> v9116 = p_n13;	// L14272
    fin13[2] = v9116;	// L14273
    ap_int<26> v9117 = p_s13;	// L14274
    fin13[3] = v9117;	// L14275
    l_S_d_0_d52: for (int d52 = 0; d52 < 4; d52++) {	// L14276
      ap_uint<26> v9119 = fin13[d52];	// L14277
      bool v9120;
      ap_int<26> v9120_tmp = v9119;
      v9120 = v9120_tmp[25];	// L14278
      int32_t v9121 = v9120;	// L14279
      bool v9122 = v9121 == 1;	// L14280
      int32_t v9123 = rbcnt13[d52];	// L14281
      bool v9124 = v9123 < 2;	// L14282
      bool v9125 = v9122 & v9124;	// L14283
      if (v9125) {	// L14284
        ap_uint<26> v9126 = fin13[d52];	// L14285
        int32_t v9127 = rbcnt13[d52];	// L14286
        int v9128 = v9127;	// L14287
        rbuf13[d52][v9128] = v9126;	// L14288
        int32_t v9129 = rbcnt13[d52];	// L14289
        ap_int<33> v9130 = v9129;	// L14290
        ap_int<33> v9131 = v9130 + 1;	// L14291
        int32_t v9132 = v9131;	// L14292
        rbcnt13[d52] = v9132;	// L14293
      }
    }
    ap_uint<26> hd13[4];	// L14296
    for (int v9134 = 0; v9134 < 4; v9134++) {	// L14297
      hd13[v9134] = 0;	// L14297
    }
    int32_t hvld13[4];	// L14298
    for (int v9136 = 0; v9136 < 4; v9136++) {	// L14299
      hvld13[v9136] = 0;	// L14299
    }
    int32_t hit13[4];	// L14300
    for (int v9138 = 0; v9138 < 4; v9138++) {	// L14301
      hit13[v9138] = 0;	// L14301
    }
    int32_t axis13[4];	// L14302
    for (int v9140 = 0; v9140 < 4; v9140++) {	// L14303
      axis13[v9140] = 0;	// L14303
    }
    int32_t v9141 = col_id13;	// L14304
    axis13[0] = v9141;	// L14305
    int32_t v9142 = col_id13;	// L14306
    axis13[1] = v9142;	// L14307
    int32_t v9143 = row_id13;	// L14308
    axis13[2] = v9143;	// L14309
    int32_t v9144 = row_id13;	// L14310
    axis13[3] = v9144;	// L14311
    l_S_d_1_d53: for (int d53 = 0; d53 < 4; d53++) {	// L14312
      int32_t v9146 = rbcnt13[d53];	// L14313
      bool v9147 = v9146 > 0;	// L14314
      if (v9147) {	// L14315
        ap_uint<26> v9148 = rbuf13[d53][0];	// L14316
        hd13[d53] = v9148;	// L14317
        hvld13[d53] = 1;	// L14318
        ap_uint<26> v9149 = hd13[d53];	// L14319
        ap_int<4> v9150;
        ap_int<26> v9150_tmp = v9149;
        v9150 = v9150_tmp(24, 21);	// L14320
        int32_t v9151 = axis13[d53];	// L14321
        int32_t v9152 = v9150;	// L14322
        bool v9153 = v9152 == v9151;	// L14323
        if (v9153) {	// L14324
          hit13[d53] = 1;	// L14325
        }
      }
    }
    ap_uint<26> o_crv13;	// L14329
    o_crv13 = 0;	// L14330
    int32_t crv_in13;	// L14331
    crv_in13 = -1;	// L14332
    int32_t v9156 = hit13[3];	// L14333
    bool v9157 = v9156 == 1;	// L14334
    if (v9157) {	// L14335
      ap_uint<26> v9158 = hd13[3];	// L14336
      o_crv13 = v9158;	// L14337
      crv_in13 = 3;	// L14338
    } else {
      int32_t v9159 = hit13[2];	// L14340
      bool v9160 = v9159 == 1;	// L14341
      if (v9160) {	// L14342
        ap_uint<26> v9161 = hd13[2];	// L14343
        o_crv13 = v9161;	// L14344
        crv_in13 = 2;	// L14345
      } else {
        int32_t v9162 = hit13[1];	// L14347
        bool v9163 = v9162 == 1;	// L14348
        if (v9163) {	// L14349
          ap_uint<26> v9164 = hd13[1];	// L14350
          o_crv13 = v9164;	// L14351
          crv_in13 = 1;	// L14352
        } else {
          int32_t v9165 = hit13[0];	// L14354
          bool v9166 = v9165 == 1;	// L14355
          if (v9166) {	// L14356
            ap_uint<26> v9167 = hd13[0];	// L14357
            o_crv13 = v9167;	// L14358
            crv_in13 = 0;	// L14359
          }
        }
      }
    }
    ap_uint<26> o_out13[4];	// L14364
    for (int v9169 = 0; v9169 < 4; v9169++) {	// L14365
      o_out13[v9169] = 0;	// L14365
    }
    int32_t pop13[4];	// L14366
    for (int v9171 = 0; v9171 < 4; v9171++) {	// L14367
      pop13[v9171] = 0;	// L14367
    }
    int32_t inj_done13;	// L14368
    inj_done13 = 0;	// L14369
    int32_t idir13;	// L14370
    idir13 = -1;	// L14371
    ap_int<26> v9174 = csd_pkt13;	// L14372
    bool v9175;
    ap_int<26> v9175_tmp = v9174;
    v9175 = v9175_tmp[25];	// L14373
    int32_t v9176 = v9175;	// L14374
    bool v9177 = v9176 == 1;	// L14375
    if (v9177) {	// L14376
      int32_t v9178 = csd_dir13;	// L14377
      ap_int<33> v9179 = v9178;	// L14378
      ap_int<33> v9180 = 3 - v9179;	// L14379
      int32_t v9181 = v9180;	// L14380
      idir13 = v9181;	// L14381
    }
    l_S_o_2_o13: for (int o13 = 0; o13 < 4; o13++) {	// L14383
      int32_t v9183 = rcred13[o13];	// L14384
      bool v9184 = v9183 > 0;	// L14385
      if (v9184) {	// L14386
        int32_t v9185 = idir13;	// L14387
        ap_int<33> v9186 = v9185;	// L14388
        ap_int<33> v9187 = o13;	// L14389
        bool v9188 = v9186 == v9187;	// L14390
        if (v9188) {	// L14391
          ap_int<26> v9189 = csd_pkt13;	// L14392
          o_out13[o13] = v9189;	// L14393
          int32_t v9190 = rcred13[o13];	// L14394
          ap_int<33> v9191 = v9190;	// L14395
          ap_int<33> v9192 = v9191 - 1;	// L14396
          int32_t v9193 = v9192;	// L14397
          rcred13[o13] = v9193;	// L14398
          inj_done13 = 1;	// L14399
        } else {
          int32_t v9194 = hvld13[o13];	// L14401
          bool v9195 = v9194 == 1;	// L14402
          int32_t v9196 = hit13[o13];	// L14403
          bool v9197 = v9196 == 0;	// L14404
          bool v9198 = v9195 & v9197;	// L14405
          if (v9198) {	// L14406
            ap_uint<26> v9199 = hd13[o13];	// L14407
            o_out13[o13] = v9199;	// L14408
            int32_t v9200 = rcred13[o13];	// L14409
            ap_int<33> v9201 = v9200;	// L14410
            ap_int<33> v9202 = v9201 - 1;	// L14411
            int32_t v9203 = v9202;	// L14412
            rcred13[o13] = v9203;	// L14413
            pop13[o13] = 1;	// L14414
          }
        }
      }
    }
    int32_t v9204 = crv_in13;	// L14419
    bool v9205 = v9204 >= 0;	// L14420
    if (v9205) {	// L14421
      int32_t v9206 = crv_in13;	// L14422
      int v9207 = v9206;	// L14423
      pop13[v9207] = 1;	// L14424
    }
    int32_t ret13[4];	// L14426
    for (int v9209 = 0; v9209 < 4; v9209++) {	// L14427
      ret13[v9209] = 0;	// L14427
    }
    l_S_d_3_d54: for (int d54 = 0; d54 < 4; d54++) {	// L14428
      int32_t v9211 = pop13[d54];	// L14429
      bool v9212 = v9211 == 1;	// L14430
      if (v9212) {	// L14431
        l_S_sft_3_sft13: for (int sft13 = 0; sft13 < 1; sft13++) {	// L14432
          ap_uint<26> v9214 = rbuf13[d54][(sft13 + 1)];	// L14433
          rbuf13[d54][sft13] = v9214;	// L14434
        }
        int32_t v9215 = rbcnt13[d54];	// L14436
        ap_int<33> v9216 = v9215;	// L14437
        ap_int<33> v9217 = v9216 - 1;	// L14438
        int32_t v9218 = v9217;	// L14439
        rbcnt13[d54] = v9218;	// L14440
        ret13[d54] = 1;	// L14441
      }
    }
    int32_t v9219 = ret13[0];	// L14444
    cre_r13 = v9219;	// L14445
    int32_t v9220 = ret13[1];	// L14446
    crw_r13 = v9220;	// L14447
    int32_t v9221 = ret13[2];	// L14448
    crs_r13 = v9221;	// L14449
    int32_t v9222 = ret13[3];	// L14450
    crn_r13 = v9222;	// L14451
    ap_uint<26> v9223 = o_out13[0];	// L14452
    oe_r13 = v9223;	// L14453
    ap_uint<26> v9224 = o_out13[1];	// L14454
    ow_r13 = v9224;	// L14455
    ap_uint<26> v9225 = o_out13[2];	// L14456
    os_r13 = v9225;	// L14457
    ap_uint<26> v9226 = o_out13[3];	// L14458
    on_r13 = v9226;	// L14459
    int32_t v9227 = inj_done13;	// L14460
    bool v9228 = v9227 == 1;	// L14461
    if (v9228) {	// L14462
      csd_pkt13 = 0;	// L14463
    }
    ap_int<26> v9229 = o_crv13;	// L14465
    bool v9230;
    ap_int<26> v9230_tmp = v9229;
    v9230 = v9230_tmp[25];	// L14466
    int32_t v9231 = v9230;	// L14467
    crv_vld13 = v9231;	// L14468
    ap_int<26> v9232 = o_crv13;	// L14469
    int16_t v9233;
    ap_int<26> v9233_tmp = v9232;
    v9233 = v9233_tmp(15, 0);	// L14470
    half v9234;
    union { uint16_t from; half to;} _converter_v9233_to_v9234;
    _converter_v9233_to_v9234.from = v9233;
    v9234 = _converter_v9233_to_v9234.to;	// L14471
    crv_data13 = v9234;	// L14472
    ap_int<26> v9235 = o_crv13;	// L14473
    ap_int<4> v9236;
    ap_int<26> v9236_tmp = v9235;
    v9236 = v9236_tmp(19, 16);	// L14474
    int32_t v9237 = v9236;	// L14475
    crv_addr13 = v9237;	// L14476
    ap_int<26> v9238 = o_crv13;	// L14477
    bool v9239;
    ap_int<26> v9239_tmp = v9238;
    v9239 = v9239_tmp[20];	// L14478
    int32_t v9240 = v9239;	// L14479
    crv_mode13 = v9240;	// L14480
    ap_int<26> v9241 = o_crv13;	// L14481
    int16_t v9242;
    ap_int<26> v9242_tmp = v9241;
    v9242 = v9242_tmp(15, 0);	// L14482
    int32_t v9243 = v9242;	// L14483
    crv_raw13 = v9243;	// L14484
    ap_uint<17> v9244 = v9016.read();	// L14485
    ap_uint<17> rx_w13;	// L14486
    rx_w13 = v9244;	// L14487
    ap_uint<17> v9246 = v9017.read();	// L14488
    ap_uint<17> rx_e13;	// L14489
    rx_e13 = v9246;	// L14490
    ap_uint<17> v9248 = v9018.read();	// L14491
    ap_uint<17> rx_n13;	// L14492
    rx_n13 = v9248;	// L14493
    ap_uint<17> v9250 = v9019.read();	// L14494
    ap_uint<17> rx_s13;	// L14495
    rx_s13 = v9250;	// L14496
    half rxv13[4];	// L14497
    for (int v9253 = 0; v9253 < 4; v9253++) {	// L14498
      rxv13[v9253] = (double)0.000000;	// L14498
    }
    int32_t rxvld13[4];	// L14499
    for (int v9255 = 0; v9255 < 4; v9255++) {	// L14500
      rxvld13[v9255] = 0;	// L14500
    }
    ap_int<17> v9256 = rx_n13;	// L14501
    int16_t v9257;
    ap_int<17> v9257_tmp = v9256;
    v9257 = v9257_tmp(16, 1);	// L14502
    half v9258;
    union { uint16_t from; half to;} _converter_v9257_to_v9258;
    _converter_v9257_to_v9258.from = v9257;
    v9258 = _converter_v9257_to_v9258.to;	// L14503
    rxv13[0] = v9258;	// L14504
    ap_int<17> v9259 = rx_n13;	// L14505
    bool v9260;
    ap_int<17> v9260_tmp = v9259;
    v9260 = v9260_tmp[0];	// L14506
    int32_t v9261 = v9260;	// L14507
    rxvld13[0] = v9261;	// L14508
    ap_int<17> v9262 = rx_s13;	// L14509
    int16_t v9263;
    ap_int<17> v9263_tmp = v9262;
    v9263 = v9263_tmp(16, 1);	// L14510
    half v9264;
    union { uint16_t from; half to;} _converter_v9263_to_v9264;
    _converter_v9263_to_v9264.from = v9263;
    v9264 = _converter_v9263_to_v9264.to;	// L14511
    rxv13[1] = v9264;	// L14512
    ap_int<17> v9265 = rx_s13;	// L14513
    bool v9266;
    ap_int<17> v9266_tmp = v9265;
    v9266 = v9266_tmp[0];	// L14514
    int32_t v9267 = v9266;	// L14515
    rxvld13[1] = v9267;	// L14516
    ap_int<17> v9268 = rx_w13;	// L14517
    int16_t v9269;
    ap_int<17> v9269_tmp = v9268;
    v9269 = v9269_tmp(16, 1);	// L14518
    half v9270;
    union { uint16_t from; half to;} _converter_v9269_to_v9270;
    _converter_v9269_to_v9270.from = v9269;
    v9270 = _converter_v9269_to_v9270.to;	// L14519
    rxv13[2] = v9270;	// L14520
    ap_int<17> v9271 = rx_w13;	// L14521
    bool v9272;
    ap_int<17> v9272_tmp = v9271;
    v9272 = v9272_tmp[0];	// L14522
    int32_t v9273 = v9272;	// L14523
    rxvld13[2] = v9273;	// L14524
    ap_int<17> v9274 = rx_e13;	// L14525
    int16_t v9275;
    ap_int<17> v9275_tmp = v9274;
    v9275 = v9275_tmp(16, 1);	// L14526
    half v9276;
    union { uint16_t from; half to;} _converter_v9275_to_v9276;
    _converter_v9275_to_v9276.from = v9275;
    v9276 = _converter_v9275_to_v9276.to;	// L14527
    rxv13[3] = v9276;	// L14528
    ap_int<17> v9277 = rx_e13;	// L14529
    bool v9278;
    ap_int<17> v9278_tmp = v9277;
    v9278 = v9278_tmp[0];	// L14530
    int32_t v9279 = v9278;	// L14531
    rxvld13[3] = v9279;	// L14532
    l_S_d_5_d55: for (int d55 = 0; d55 < 4; d55++) {	// L14533
      int32_t v9281 = rxvld13[d55];	// L14534
      bool v9282 = v9281 == 1;	// L14535
      int32_t v9283 = hold_cnt13[d55];	// L14536
      bool v9284 = v9283 < 2;	// L14537
      bool v9285 = v9282 & v9284;	// L14538
      if (v9285) {	// L14539
        half v9286 = rxv13[d55];	// L14540
        int32_t v9287 = hold_cnt13[d55];	// L14541
        int v9288 = v9287;	// L14542
        hold_v13[d55][v9288] = v9286;	// L14543
        int32_t v9289 = hold_cnt13[d55];	// L14544
        ap_int<33> v9290 = v9289;	// L14545
        ap_int<33> v9291 = v9290 + 1;	// L14546
        int32_t v9292 = v9291;	// L14547
        hold_cnt13[d55] = v9292;	// L14548
      }
    }
    int32_t pc13;	// L14551
    pc13 = -1;	// L14552
    int32_t v9294 = fetch_en13;	// L14553
    bool v9295 = v9294 == 1;	// L14554
    if (v9295) {	// L14555
      int32_t v9296 = instr_cnt13;	// L14556
      pc13 = v9296;	// L14557
    }
    int32_t instr13;	// L14559
    instr13 = 0;	// L14560
    int32_t v9298 = pc13;	// L14561
    bool v9299 = v9298 >= 0;	// L14562
    if (v9299) {	// L14563
      int32_t v9300 = pc13;	// L14564
      int v9301 = v9300;	// L14565
      int32_t v9302 = irf13[v9301];	// L14566
      instr13 = v9302;	// L14567
    }
    int32_t v9303 = instr13;	// L14569
    int32_t v9304 = v9303 & 15;	// L14570
    int32_t op13;	// L14571
    op13 = v9304;	// L14572
    int32_t v9306 = instr13;	// L14573
    int32_t v9307 = v9306 >> 4;	// L14574
    int32_t v9308 = v9307 & 15;	// L14575
    int32_t dst13;	// L14576
    dst13 = v9308;	// L14577
    int32_t v9310 = instr13;	// L14578
    int32_t v9311 = v9310 >> 8;	// L14579
    int32_t v9312 = v9311 & 15;	// L14580
    int32_t s113;	// L14581
    s113 = v9312;	// L14582
    int32_t v9314 = instr13;	// L14583
    int32_t v9315 = v9314 >> 12;	// L14584
    int32_t v9316 = v9315 & 15;	// L14585
    int32_t s213;	// L14586
    s213 = v9316;	// L14587
    half a13;	// L14588
    a13 = (double)0.000000;	// L14589
    half b13;	// L14590
    b13 = (double)0.000000;	// L14591
    int32_t v9320 = s113;	// L14592
    bool v9321 = v9320 >= 12;	// L14593
    if (v9321) {	// L14594
      int32_t v9322 = s113;	// L14595
      int32_t v9323 = v9322 & 3;	// L14596
      int v9324 = v9323;	// L14597
      half v9325 = hold_v13[v9324][0];	// L14598
      a13 = v9325;	// L14599
    } else {
      int32_t v9326 = s113;	// L14601
      int v9327 = v9326;	// L14602
      half v9328 = drf13[v9327];	// L14603
      a13 = v9328;	// L14604
    }
    int32_t v9329 = s213;	// L14606
    bool v9330 = v9329 >= 12;	// L14607
    if (v9330) {	// L14608
      int32_t v9331 = s213;	// L14609
      int32_t v9332 = v9331 & 3;	// L14610
      int v9333 = v9332;	// L14611
      half v9334 = hold_v13[v9333][0];	// L14612
      b13 = v9334;	// L14613
    } else {
      int32_t v9335 = s213;	// L14615
      int v9336 = v9335;	// L14616
      half v9337 = drf13[v9336];	// L14617
      b13 = v9337;	// L14618
    }
    int32_t a_vld13;	// L14620
    a_vld13 = 1;	// L14621
    int32_t b_vld13;	// L14622
    b_vld13 = 1;	// L14623
    int32_t v9340 = s113;	// L14624
    bool v9341 = v9340 >= 12;	// L14625
    if (v9341) {	// L14626
      a_vld13 = 0;	// L14627
      int32_t v9342 = s113;	// L14628
      int32_t v9343 = v9342 & 3;	// L14629
      int v9344 = v9343;	// L14630
      int32_t v9345 = hold_cnt13[v9344];	// L14631
      bool v9346 = v9345 > 0;	// L14632
      if (v9346) {	// L14633
        a_vld13 = 1;	// L14634
      }
    }
    int32_t v9347 = s213;	// L14637
    bool v9348 = v9347 >= 12;	// L14638
    if (v9348) {	// L14639
      b_vld13 = 0;	// L14640
      int32_t v9349 = s213;	// L14641
      int32_t v9350 = v9349 & 3;	// L14642
      int v9351 = v9350;	// L14643
      int32_t v9352 = hold_cnt13[v9351];	// L14644
      bool v9353 = v9352 > 0;	// L14645
      if (v9353) {	// L14646
        b_vld13 = 1;	// L14647
      }
    }
    int32_t v9354 = s113;	// L14650
    bool v9355 = v9354 < 8;	// L14651
    int32_t v9356 = dsmask13;	// L14652
    int32_t v9357 = v9356 >> v9354;	// L14653
    int32_t v9358 = v9357 & 1;	// L14654
    bool v9359 = v9358 == 1;	// L14655
    bool v9360 = v9355 & v9359;	// L14656
    if (v9360) {	// L14657
      int32_t v9361 = s113;	// L14658
      int v9362 = v9361;	// L14659
      int32_t v9363 = drf_full13[v9362];	// L14660
      bool v9364 = v9363 == 0;	// L14661
      if (v9364) {	// L14662
        a_vld13 = 0;	// L14663
      }
    }
    int32_t v9365 = s213;	// L14666
    bool v9366 = v9365 < 8;	// L14667
    int32_t v9367 = dsmask13;	// L14668
    int32_t v9368 = v9367 >> v9365;	// L14669
    int32_t v9369 = v9368 & 1;	// L14670
    bool v9370 = v9369 == 1;	// L14671
    bool v9371 = v9366 & v9370;	// L14672
    if (v9371) {	// L14673
      int32_t v9372 = s213;	// L14674
      int v9373 = v9372;	// L14675
      int32_t v9374 = drf_full13[v9373];	// L14676
      bool v9375 = v9374 == 0;	// L14677
      if (v9375) {	// L14678
        b_vld13 = 0;	// L14679
      }
    }
    int32_t binop13;	// L14682
    binop13 = 0;	// L14683
    int32_t v9377 = op13;	// L14684
    bool v9378 = v9377 == 0;	// L14685
    bool v9379 = v9377 == 1;	// L14686
    bool v9380 = v9377 == 2;	// L14687
    bool v9381 = v9377 == 8;	// L14688
    bool v9382 = v9377 == 9;	// L14689
    bool v9383 = v9378 | v9379;	// L14690
    bool v9384 = v9383 | v9380;	// L14691
    bool v9385 = v9384 | v9381;	// L14692
    bool v9386 = v9385 | v9382;	// L14693
    if (v9386) {	// L14694
      binop13 = 1;	// L14695
    }
    int32_t grant13;	// L14697
    grant13 = 0;	// L14698
    int32_t v9388 = pc13;	// L14699
    bool v9389 = v9388 >= 0;	// L14700
    if (v9389) {	// L14701
      grant13 = 1;	// L14702
    }
    int32_t v9390 = pc13;	// L14704
    bool v9391 = v9390 >= 0;	// L14705
    int32_t v9392 = a_vld13;	// L14706
    bool v9393 = v9392 == 0;	// L14707
    int32_t v9394 = binop13;	// L14708
    bool v9395 = v9394 == 1;	// L14709
    int32_t v9396 = b_vld13;	// L14710
    bool v9397 = v9396 == 0;	// L14711
    bool v9398 = v9395 & v9397;	// L14712
    bool v9399 = v9393 | v9398;	// L14713
    bool v9400 = v9391 & v9399;	// L14714
    if (v9400) {	// L14715
      grant13 = 0;	// L14716
    }
    int32_t v9401 = grant13;	// L14718
    bool v9402 = v9401 == 1;	// L14719
    if (v9402) {	// L14720
      int32_t v9403 = instr_cnt13;	// L14721
      int32_t v9404 = cfg_isz13;	// L14722
      bool v9405 = v9403 == v9404;	// L14723
      if (v9405) {	// L14724
        instr_cnt13 = 0;	// L14725
        int32_t v9406 = iter_cnt13;	// L14726
        int32_t v9407 = cfg_itsz13;	// L14727
        ap_int<33> v9408 = v9407;	// L14728
        ap_int<33> v9409 = v9408 - 1;	// L14729
        ap_int<33> v9410 = v9406;	// L14730
        bool v9411 = v9410 == v9409;	// L14731
        if (v9411) {	// L14732
          fetch_en13 = 0;	// L14733
        } else {
          int32_t v9412 = iter_cnt13;	// L14735
          ap_int<33> v9413 = v9412;	// L14736
          ap_int<33> v9414 = v9413 + 1;	// L14737
          int32_t v9415 = v9414;	// L14738
          iter_cnt13 = v9415;	// L14739
        }
      } else {
        int32_t v9416 = instr_cnt13;	// L14742
        ap_int<33> v9417 = v9416;	// L14743
        ap_int<33> v9418 = v9417 + 1;	// L14744
        int32_t v9419 = v9418;	// L14745
        instr_cnt13 = v9419;	// L14746
      }
    }
    int32_t c113;	// L14749
    c113 = -1;	// L14750
    int32_t c213;	// L14751
    c213 = -1;	// L14752
    int32_t v9422 = grant13;	// L14753
    bool v9423 = v9422 == 1;	// L14754
    int32_t v9424 = s113;	// L14755
    bool v9425 = v9424 >= 12;	// L14756
    bool v9426 = v9423 & v9425;	// L14757
    if (v9426) {	// L14758
      int32_t v9427 = s113;	// L14759
      int32_t v9428 = v9427 & 3;	// L14760
      c113 = v9428;	// L14761
    }
    int32_t v9429 = grant13;	// L14763
    bool v9430 = v9429 == 1;	// L14764
    int32_t v9431 = s213;	// L14765
    bool v9432 = v9431 >= 12;	// L14766
    bool v9433 = v9430 & v9432;	// L14767
    if (v9433) {	// L14768
      int32_t v9434 = s213;	// L14769
      int32_t v9435 = v9434 & 3;	// L14770
      c213 = v9435;	// L14771
    }
    int32_t v9436 = c113;	// L14773
    bool v9437 = v9436 >= 0;	// L14774
    if (v9437) {	// L14775
      int32_t v9438 = c113;	// L14776
      int v9439 = v9438;	// L14777
      half v9440 = hold_v13[v9439][1];	// L14778
      hold_v13[v9439][0] = v9440;	// L14779
      int32_t v9441 = c113;	// L14780
      int v9442 = v9441;	// L14781
      int32_t v9443 = hold_cnt13[v9442];	// L14782
      ap_int<33> v9444 = v9443;	// L14783
      ap_int<33> v9445 = v9444 - 1;	// L14784
      int32_t v9446 = v9445;	// L14785
      hold_cnt13[v9442] = v9446;	// L14786
    }
    int32_t v9447 = c213;	// L14788
    bool v9448 = v9447 >= 0;	// L14789
    int32_t v9449 = c113;	// L14790
    bool v9450 = v9447 != v9449;	// L14791
    bool v9451 = v9448 & v9450;	// L14792
    if (v9451) {	// L14793
      int32_t v9452 = c213;	// L14794
      int v9453 = v9452;	// L14795
      half v9454 = hold_v13[v9453][1];	// L14796
      hold_v13[v9453][0] = v9454;	// L14797
      int32_t v9455 = c213;	// L14798
      int v9456 = v9455;	// L14799
      int32_t v9457 = hold_cnt13[v9456];	// L14800
      ap_int<33> v9458 = v9457;	// L14801
      ap_int<33> v9459 = v9458 - 1;	// L14802
      int32_t v9460 = v9459;	// L14803
      hold_cnt13[v9456] = v9460;	// L14804
    }
    int32_t v9461 = grant13;	// L14806
    bool v9462 = v9461 == 1;	// L14807
    int32_t v9463 = s113;	// L14808
    bool v9464 = v9463 < 8;	// L14809
    int32_t v9465 = dsmask13;	// L14810
    int32_t v9466 = v9465 >> v9463;	// L14811
    int32_t v9467 = v9466 & 1;	// L14812
    bool v9468 = v9467 == 1;	// L14813
    bool v9469 = v9462 & v9464;	// L14814
    bool v9470 = v9469 & v9468;	// L14815
    if (v9470) {	// L14816
      int32_t v9471 = s113;	// L14817
      int v9472 = v9471;	// L14818
      drf_full13[v9472] = 0;	// L14819
    }
    int32_t v9473 = grant13;	// L14821
    bool v9474 = v9473 == 1;	// L14822
    int32_t v9475 = s213;	// L14823
    bool v9476 = v9475 < 8;	// L14824
    int32_t v9477 = dsmask13;	// L14825
    int32_t v9478 = v9477 >> v9475;	// L14826
    int32_t v9479 = v9478 & 1;	// L14827
    bool v9480 = v9479 == 1;	// L14828
    bool v9481 = v9474 & v9476;	// L14829
    bool v9482 = v9481 & v9480;	// L14830
    if (v9482) {	// L14831
      int32_t v9483 = s213;	// L14832
      int v9484 = v9483;	// L14833
      drf_full13[v9484] = 0;	// L14834
    }
    half res13;	// L14836
    res13 = (double)0.000000;	// L14837
    int32_t v9486 = op13;	// L14838
    bool v9487 = v9486 == 0;	// L14839
    if (v9487) {	// L14840
      half v9488 = a13;	// L14841
      half v9489 = b13;	// L14842
      half v9490 = v9488 + v9489;	// L14843
      res13 = v9490;	// L14844
    } else {
      int32_t v9491 = op13;	// L14846
      bool v9492 = v9491 == 1;	// L14847
      if (v9492) {	// L14848
        half v9493 = a13;	// L14849
        half v9494 = b13;	// L14850
        half v9495 = v9493 - v9494;	// L14851
        res13 = v9495;	// L14852
      } else {
        int32_t v9496 = op13;	// L14854
        bool v9497 = v9496 == 2;	// L14855
        if (v9497) {	// L14856
          half v9498 = a13;	// L14857
          half v9499 = b13;	// L14858
          half v9500 = v9498 * v9499;	// L14859
          res13 = v9500;	// L14860
        } else {
          int32_t v9501 = op13;	// L14862
          bool v9502 = v9501 == 8;	// L14863
          if (v9502) {	// L14864
            half v9503 = a13;	// L14865
            half v9504 = b13;	// L14866
            bool v9505 = v9503 >= v9504;	// L14867
            if (v9505) {	// L14868
              res13 = (double)1.000000;	// L14869
            } else {
              res13 = (double)-1.000000;	// L14871
            }
          } else {
            int32_t v9506 = op13;	// L14874
            bool v9507 = v9506 == 9;	// L14875
            if (v9507) {	// L14876
              half v9508 = a13;	// L14877
              half v9509 = b13;	// L14878
              bool v9510 = v9508 < v9509;	// L14879
              if (v9510) {	// L14880
                res13 = (double)1.000000;	// L14881
              } else {
                res13 = (double)-1.000000;	// L14883
              }
            } else {
              half v9511 = a13;	// L14886
              res13 = v9511;	// L14887
            }
          }
        }
      }
    }
    int32_t v9512 = a_vld13;	// L14893
    int32_t res_vld13;	// L14894
    res_vld13 = v9512;	// L14895
    int32_t v9514 = op13;	// L14896
    bool v9515 = v9514 == 0;	// L14897
    bool v9516 = v9514 == 1;	// L14898
    bool v9517 = v9514 == 2;	// L14899
    bool v9518 = v9514 == 8;	// L14900
    bool v9519 = v9514 == 9;	// L14901
    bool v9520 = v9515 | v9516;	// L14902
    bool v9521 = v9520 | v9517;	// L14903
    bool v9522 = v9521 | v9518;	// L14904
    bool v9523 = v9522 | v9519;	// L14905
    if (v9523) {	// L14906
      int32_t v9524 = a_vld13;	// L14907
      int32_t v9525 = b_vld13;	// L14908
      int64_t v9526 = v9524;	// L14909
      int64_t v9527 = v9525;	// L14910
      int64_t v9528 = v9526 * v9527;	// L14911
      int32_t v9529 = v9528;	// L14912
      res_vld13 = v9529;	// L14913
    }
    int32_t v9530 = grant13;	// L14915
    bool v9531 = v9530 == 0;	// L14916
    if (v9531) {	// L14917
      res_vld13 = 0;	// L14918
    }
    int32_t v9532 = grant13;	// L14920
    bool v9533 = v9532 == 1;	// L14921
    int32_t v9534 = op13;	// L14922
    bool v9535 = v9534 == 8;	// L14923
    bool v9536 = v9533 & v9535;	// L14924
    if (v9536) {	// L14925
      condition_reg13 = 0;	// L14926
      half v9537 = a13;	// L14927
      half v9538 = b13;	// L14928
      bool v9539 = v9537 >= v9538;	// L14929
      if (v9539) {	// L14930
        condition_reg13 = 1;	// L14931
      }
    }
    int32_t v9540 = grant13;	// L14934
    bool v9541 = v9540 == 1;	// L14935
    int32_t v9542 = op13;	// L14936
    bool v9543 = v9542 == 9;	// L14937
    bool v9544 = v9541 & v9543;	// L14938
    if (v9544) {	// L14939
      condition_reg13 = 0;	// L14940
      half v9545 = a13;	// L14941
      half v9546 = b13;	// L14942
      bool v9547 = v9545 < v9546;	// L14943
      if (v9547) {	// L14944
        condition_reg13 = 1;	// L14945
      }
    }
    ap_uint<17> tx_n13;	// L14948
    tx_n13 = 0;	// L14949
    ap_uint<17> tx_s13;	// L14950
    tx_s13 = 0;	// L14951
    ap_uint<17> tx_w13;	// L14952
    tx_w13 = 0;	// L14953
    ap_uint<17> tx_e13;	// L14954
    tx_e13 = 0;	// L14955
    int32_t is_rtr13;	// L14956
    is_rtr13 = 0;	// L14957
    int32_t do_inj13;	// L14958
    do_inj13 = 0;	// L14959
    int32_t v9554 = op13;	// L14960
    bool v9555 = v9554 >= 4;	// L14961
    ap_int<33> v9556 = v9554;	// L14962
    bool v9557 = v9556 <= 7;	// L14963
    bool v9558 = v9555 & v9557;	// L14964
    if (v9558) {	// L14965
      is_rtr13 = 1;	// L14966
      do_inj13 = 1;	// L14967
    }
    int32_t v9559 = op13;	// L14969
    bool v9560 = v9559 >= 12;	// L14970
    ap_int<33> v9561 = v9559;	// L14971
    bool v9562 = v9561 <= 15;	// L14972
    bool v9563 = v9560 & v9562;	// L14973
    if (v9563) {	// L14974
      is_rtr13 = 1;	// L14975
      int32_t v9564 = condition_reg13;	// L14976
      bool v9565 = v9564 == 1;	// L14977
      if (v9565) {	// L14978
        do_inj13 = 1;	// L14979
      }
    }
    int32_t v9566 = is_rtr13;	// L14982
    bool v9567 = v9566 == 1;	// L14983
    if (v9567) {	// L14984
      int32_t v9568 = do_inj13;	// L14985
      bool v9569 = v9568 == 1;	// L14986
      ap_int<26> v9570 = csd_pkt13;	// L14987
      bool v9571;
      ap_int<26> v9571_tmp = v9570;
      v9571 = v9571_tmp[25];	// L14988
      int32_t v9572 = v9571;	// L14989
      bool v9573 = v9572 == 0;	// L14990
      bool v9574 = v9569 & v9573;	// L14991
      if (v9574) {	// L14992
        half v9575 = res13;	// L14993
        uint16_t v9576;
        union { half from; uint16_t to;} _converter_v9575_to_v9576;
        _converter_v9575_to_v9576.from = v9575;
        v9576 = _converter_v9575_to_v9576.to;	// L14994
        ap_int<26> v9577 = csd_pkt13;	// L14995
        ap_int<26> v9578;
        ap_int<26> v9578_tmp = v9577;
        v9578_tmp(15, 0) = v9576;
        v9578 = v9578_tmp;	// L14996
        csd_pkt13 = v9578;	// L14997
        int32_t v9579 = dst13;	// L14998
        ap_uint<4> v9580 = v9579;	// L14999
        ap_int<26> v9581 = csd_pkt13;	// L15000
        ap_int<26> v9582;
        ap_int<26> v9582_tmp = v9581;
        v9582_tmp(19, 16) = v9580;
        v9582 = v9582_tmp;	// L15001
        csd_pkt13 = v9582;	// L15002
        int32_t v9583 = s213;	// L15003
        ap_uint<4> v9584 = v9583;	// L15004
        ap_int<26> v9585 = csd_pkt13;	// L15005
        ap_int<26> v9586;
        ap_int<26> v9586_tmp = v9585;
        v9586_tmp(24, 21) = v9584;
        v9586 = v9586_tmp;	// L15006
        csd_pkt13 = v9586;	// L15007
        int32_t v9587 = res_vld13;	// L15008
        bool v9588 = v9587;	// L15009
        ap_int<26> v9589 = csd_pkt13;	// L15010
        ap_int<26> v9590;
        ap_int<26> v9590_tmp = v9589;
        v9590_tmp[25] = v9588;        v9590 = v9590_tmp;	// L15011
        csd_pkt13 = v9590;	// L15012
        int32_t v9591 = op13;	// L15013
        int32_t v9592 = v9591 & 3;	// L15014
        csd_dir13 = v9592;	// L15015
      }
    } else {
      int32_t v9593 = dst13;	// L15018
      bool v9594 = v9593 >= 12;	// L15019
      if (v9594) {	// L15020
        ap_uint<17> tw13;	// L15021
        tw13 = 0;	// L15022
        int32_t v9596 = res_vld13;	// L15023
        bool v9597 = v9596;	// L15024
        ap_int<17> v9598 = tw13;	// L15025
        ap_int<17> v9599;
        ap_int<17> v9599_tmp = v9598;
        v9599_tmp[0] = v9597;        v9599 = v9599_tmp;	// L15026
        tw13 = v9599;	// L15027
        half v9600 = res13;	// L15028
        uint16_t v9601;
        union { half from; uint16_t to;} _converter_v9600_to_v9601;
        _converter_v9600_to_v9601.from = v9600;
        v9601 = _converter_v9600_to_v9601.to;	// L15029
        ap_int<17> v9602 = tw13;	// L15030
        ap_int<17> v9603;
        ap_int<17> v9603_tmp = v9602;
        v9603_tmp(16, 1) = v9601;
        v9603 = v9603_tmp;	// L15031
        tw13 = v9603;	// L15032
        int32_t v9604 = dst13;	// L15033
        int32_t v9605 = v9604 & 3;	// L15034
        bool v9606 = v9605 == 0;	// L15035
        if (v9606) {	// L15036
          ap_int<17> v9607 = tw13;	// L15037
          tx_n13 = v9607;	// L15038
        } else {
          int32_t v9608 = dst13;	// L15040
          int32_t v9609 = v9608 & 3;	// L15041
          bool v9610 = v9609 == 1;	// L15042
          if (v9610) {	// L15043
            ap_int<17> v9611 = tw13;	// L15044
            tx_s13 = v9611;	// L15045
          } else {
            int32_t v9612 = dst13;	// L15047
            int32_t v9613 = v9612 & 3;	// L15048
            bool v9614 = v9613 == 2;	// L15049
            if (v9614) {	// L15050
              ap_int<17> v9615 = tw13;	// L15051
              tx_w13 = v9615;	// L15052
            } else {
              ap_int<17> v9616 = tw13;	// L15054
              tx_e13 = v9616;	// L15055
            }
          }
        }
      } else {
        int32_t v9617 = res_vld13;	// L15060
        bool v9618 = v9617 == 1;	// L15061
        if (v9618) {	// L15062
          int32_t v9619 = dst13;	// L15063
          bool v9620 = v9619 < 8;	// L15064
          int32_t v9621 = dsmask13;	// L15065
          int32_t v9622 = v9621 >> v9619;	// L15066
          int32_t v9623 = v9622 & 1;	// L15067
          bool v9624 = v9623 == 1;	// L15068
          bool v9625 = v9620 & v9624;	// L15069
          if (v9625) {	// L15070
            int32_t v9626 = dst13;	// L15071
            int v9627 = v9626;	// L15072
            int32_t v9628 = drf_full13[v9627];	// L15073
            bool v9629 = v9628 == 0;	// L15074
            if (v9629) {	// L15075
              half v9630 = res13;	// L15076
              int32_t v9631 = dst13;	// L15077
              int v9632 = v9631;	// L15078
              drf13[v9632] = v9630;	// L15079
              int32_t v9633 = dst13;	// L15080
              int v9634 = v9633;	// L15081
              drf_full13[v9634] = 1;	// L15082
            }
          } else {
            half v9635 = res13;	// L15085
            int32_t v9636 = dst13;	// L15086
            int v9637 = v9636;	// L15087
            drf13[v9637] = v9635;	// L15088
          }
        }
      }
    }
    ap_int<17> v9638 = tx_n13;	// L15093
    txn_r13 = v9638;	// L15094
    ap_int<17> v9639 = tx_s13;	// L15095
    txs_r13 = v9639;	// L15096
    ap_int<17> v9640 = tx_w13;	// L15097
    txw_r13 = v9640;	// L15098
    ap_int<17> v9641 = tx_e13;	// L15099
    txe_r13 = v9641;	// L15100
    int32_t v9642 = crv_vld13;	// L15101
    bool v9643 = v9642 == 1;	// L15102
    if (v9643) {	// L15103
      int32_t v9644 = crv_mode13;	// L15104
      bool v9645 = v9644 == 1;	// L15105
      if (v9645) {	// L15106
        int32_t v9646 = crv_addr13;	// L15107
        int32_t v9647 = v9646 >> 3;	// L15108
        int32_t v9648 = v9647 & 1;	// L15109
        bool v9649 = v9648 == 1;	// L15110
        if (v9649) {	// L15111
          int32_t v9650 = crv_raw13;	// L15112
          int32_t v9651 = crv_addr13;	// L15113
          int32_t v9652 = v9651 & 7;	// L15114
          int v9653 = v9652;	// L15115
          irf13[v9653] = v9650;	// L15116
        } else {
          int32_t v9654 = crv_addr13;	// L15118
          bool v9655 = v9654 == 0;	// L15119
          if (v9655) {	// L15120
            int32_t v9656 = crv_raw13;	// L15121
            int32_t v9657 = v9656 & 255;	// L15122
            dsmask13 = v9657;	// L15123
            int32_t v9658 = crv_raw13;	// L15124
            int32_t v9659 = v9658 >> 8;	// L15125
            int32_t v9660 = v9659 & 7;	// L15126
            cfg_isz13 = v9660;	// L15127
            int32_t v9661 = crv_raw13;	// L15128
            int32_t v9662 = v9661 >> 15;	// L15129
            int32_t v9663 = v9662 & 1;	// L15130
            bool v9664 = v9663 == 1;	// L15131
            if (v9664) {	// L15132
              fetch_en13 = 1;	// L15133
              instr_cnt13 = 0;	// L15134
              iter_cnt13 = 0;	// L15135
            }
          } else {
            int32_t v9665 = crv_addr13;	// L15138
            bool v9666 = v9665 == 1;	// L15139
            if (v9666) {	// L15140
              int32_t v9667 = crv_raw13;	// L15141
              int32_t v9668 = v9667 & 255;	// L15142
              cfg_itsz13 = v9668;	// L15143
            }
          }
        }
      } else {
        int32_t v9669 = crv_addr13;	// L15148
        bool v9670 = v9669 < 8;	// L15149
        int32_t v9671 = dsmask13;	// L15150
        int32_t v9672 = v9671 >> v9669;	// L15151
        int32_t v9673 = v9672 & 1;	// L15152
        bool v9674 = v9673 == 1;	// L15153
        bool v9675 = v9670 & v9674;	// L15154
        if (v9675) {	// L15155
          int32_t v9676 = crv_addr13;	// L15156
          int v9677 = v9676;	// L15157
          int32_t v9678 = drf_full13[v9677];	// L15158
          bool v9679 = v9678 == 0;	// L15159
          if (v9679) {	// L15160
            half v9680 = crv_data13;	// L15161
            int32_t v9681 = crv_addr13;	// L15162
            int v9682 = v9681;	// L15163
            drf13[v9682] = v9680;	// L15164
            int32_t v9683 = crv_addr13;	// L15165
            int v9684 = v9683;	// L15166
            drf_full13[v9684] = 1;	// L15167
          }
        } else {
          half v9685 = crv_data13;	// L15170
          int32_t v9686 = crv_addr13;	// L15171
          int v9687 = v9686;	// L15172
          drf13[v9687] = v9685;	// L15173
        }
      }
    }
  }
}

void node_3_2(
  hls::stream< ap_uint<26> >& v9688,
  hls::stream< ap_uint<26> >& v9689,
  hls::stream< ap_uint<26> >& v9690,
  hls::stream< ap_uint<26> >& v9691,
  hls::stream< ap_uint<17> >& v9692,
  hls::stream< ap_uint<17> >& v9693,
  hls::stream< ap_uint<17> >& v9694,
  hls::stream< ap_uint<17> >& v9695,
  hls::stream< int32_t >& v9696,
  hls::stream< int32_t >& v9697,
  hls::stream< int32_t >& v9698,
  hls::stream< int32_t >& v9699,
  hls::stream< ap_uint<26> >& v9700,
  hls::stream< ap_uint<26> >& v9701,
  hls::stream< ap_uint<26> >& v9702,
  hls::stream< ap_uint<26> >& v9703,
  hls::stream< int32_t >& v9704,
  hls::stream< int32_t >& v9705,
  hls::stream< int32_t >& v9706,
  hls::stream< int32_t >& v9707,
  hls::stream< ap_uint<17> >& v9708,
  hls::stream< ap_uint<17> >& v9709,
  hls::stream< ap_uint<17> >& v9710,
  hls::stream< ap_uint<17> >& v9711
) {	// L15180
  int32_t irf14[8];	// L15211
  for (int v9713 = 0; v9713 < 8; v9713++) {	// L15212
    irf14[v9713] = 0;	// L15212
  }
  half drf14[8];	// L15213
  #pragma HLS array_partition variable=drf14 complete dim=1

  for (int v9715 = 0; v9715 < 8; v9715++) {	// L15214
    drf14[v9715] = (double)0.000000;	// L15214
  }
  int32_t drf_full14[8];	// L15215
  #pragma HLS array_partition variable=drf_full14 complete dim=1

  for (int v9717 = 0; v9717 < 8; v9717++) {	// L15216
    drf_full14[v9717] = 0;	// L15216
  }
  int32_t dsmask14;	// L15217
  dsmask14 = 0;	// L15218
  int32_t crv_vld14;	// L15219
  crv_vld14 = 0;	// L15220
  half crv_data14;	// L15221
  crv_data14 = (double)0.000000;	// L15222
  int32_t crv_addr14;	// L15223
  crv_addr14 = 0;	// L15224
  int32_t crv_mode14;	// L15225
  crv_mode14 = 0;	// L15226
  int32_t crv_raw14;	// L15227
  crv_raw14 = 0;	// L15228
  int32_t csd_vld14;	// L15229
  csd_vld14 = 0;	// L15230
  ap_uint<26> csd_pkt14;	// L15231
  csd_pkt14 = 0;	// L15232
  int32_t csd_dir14;	// L15233
  csd_dir14 = 0;	// L15234
  int32_t row_id14;	// L15235
  row_id14 = 3;	// L15236
  int32_t col_id14;	// L15237
  col_id14 = 2;	// L15238
  ap_uint<26> oe_r14;	// L15239
  oe_r14 = 0;	// L15240
  ap_uint<26> ow_r14;	// L15241
  ow_r14 = 0;	// L15242
  ap_uint<26> on_r14;	// L15243
  on_r14 = 0;	// L15244
  ap_uint<26> os_r14;	// L15245
  os_r14 = 0;	// L15246
  ap_uint<17> txn_r14;	// L15247
  txn_r14 = 0;	// L15248
  ap_uint<17> txs_r14;	// L15249
  txs_r14 = 0;	// L15250
  ap_uint<17> txw_r14;	// L15251
  txw_r14 = 0;	// L15252
  ap_uint<17> txe_r14;	// L15253
  txe_r14 = 0;	// L15254
  half hold_v14[4][2];	// L15255
  #pragma HLS array_partition variable=hold_v14 complete dim=1
  #pragma HLS array_partition variable=hold_v14 complete dim=2

  for (int v9738 = 0; v9738 < 4; v9738++) {	// L15256
    for (int v9739 = 0; v9739 < 2; v9739++) {	// L15256
      hold_v14[v9738][v9739] = (double)0.000000;	// L15256
    }
  }
  int32_t hold_cnt14[4];	// L15257
  #pragma HLS array_partition variable=hold_cnt14 complete dim=1

  for (int v9741 = 0; v9741 < 4; v9741++) {	// L15258
    hold_cnt14[v9741] = 0;	// L15258
  }
  ap_uint<26> rbuf14[4][2];	// L15259
  #pragma HLS array_partition variable=rbuf14 complete dim=1
  #pragma HLS array_partition variable=rbuf14 complete dim=2

  for (int v9743 = 0; v9743 < 4; v9743++) {	// L15260
    for (int v9744 = 0; v9744 < 2; v9744++) {	// L15260
      rbuf14[v9743][v9744] = 0;	// L15260
    }
  }
  int32_t rbcnt14[4];	// L15261
  #pragma HLS array_partition variable=rbcnt14 complete dim=1

  for (int v9746 = 0; v9746 < 4; v9746++) {	// L15262
    rbcnt14[v9746] = 0;	// L15262
  }
  int32_t rcred14[4];	// L15263
  #pragma HLS array_partition variable=rcred14 complete dim=1

  for (int v9748 = 0; v9748 < 4; v9748++) {	// L15264
    rcred14[v9748] = 0;	// L15264
  }
  int32_t cre_r14;	// L15265
  cre_r14 = 2;	// L15266
  int32_t crw_r14;	// L15267
  crw_r14 = 2;	// L15268
  int32_t crs_r14;	// L15269
  crs_r14 = 2;	// L15270
  int32_t crn_r14;	// L15271
  crn_r14 = 2;	// L15272
  int32_t cfg_isz14;	// L15273
  cfg_isz14 = 0;	// L15274
  int32_t cfg_itsz14;	// L15275
  cfg_itsz14 = 0;	// L15276
  int32_t fetch_en14;	// L15277
  fetch_en14 = 0;	// L15278
  int32_t instr_cnt14;	// L15279
  instr_cnt14 = 0;	// L15280
  int32_t iter_cnt14;	// L15281
  iter_cnt14 = 0;	// L15282
  int32_t condition_reg14;	// L15283
  condition_reg14 = 0;	// L15284
  l_S_t_0_t14: for (int t14 = 0; t14 < 8; t14++) {	// L15285
  #pragma HLS pipeline II=1
    ap_int<26> v9760 = oe_r14;	// L15286
    v9688.write(v9760);	// L15287
    ap_int<26> v9761 = ow_r14;	// L15288
    v9689.write(v9761);	// L15289
    ap_int<26> v9762 = os_r14;	// L15290
    v9690.write(v9762);	// L15291
    ap_int<26> v9763 = on_r14;	// L15292
    v9691.write(v9763);	// L15293
    ap_int<17> v9764 = txe_r14;	// L15294
    v9692.write(v9764);	// L15295
    ap_int<17> v9765 = txw_r14;	// L15296
    v9693.write(v9765);	// L15297
    ap_int<17> v9766 = txs_r14;	// L15298
    v9694.write(v9766);	// L15299
    ap_int<17> v9767 = txn_r14;	// L15300
    v9695.write(v9767);	// L15301
    int32_t v9768 = cre_r14;	// L15302
    v9696.write(v9768);	// L15303
    int32_t v9769 = crw_r14;	// L15304
    v9697.write(v9769);	// L15305
    int32_t v9770 = crs_r14;	// L15306
    v9698.write(v9770);	// L15307
    int32_t v9771 = crn_r14;	// L15308
    v9699.write(v9771);	// L15309
    ap_uint<26> v9772 = v9700.read();	// L15310
    ap_uint<26> p_w14;	// L15311
    p_w14 = v9772;	// L15312
    ap_uint<26> v9774 = v9701.read();	// L15313
    ap_uint<26> p_e14;	// L15314
    p_e14 = v9774;	// L15315
    ap_uint<26> v9776 = v9702.read();	// L15316
    ap_uint<26> p_n14;	// L15317
    p_n14 = v9776;	// L15318
    ap_uint<26> v9778 = v9703.read();	// L15319
    ap_uint<26> p_s14;	// L15320
    p_s14 = v9778;	// L15321
    int32_t v9780 = v9704.read();	// L15322
    int32_t v9781 = rcred14[0];	// L15323
    ap_int<33> v9782 = v9781;	// L15324
    ap_int<33> v9783 = v9780;	// L15325
    ap_int<33> v9784 = v9782 + v9783;	// L15326
    int32_t v9785 = v9784;	// L15327
    rcred14[0] = v9785;	// L15328
    int32_t v9786 = v9705.read();	// L15329
    int32_t v9787 = rcred14[1];	// L15330
    ap_int<33> v9788 = v9787;	// L15331
    ap_int<33> v9789 = v9786;	// L15332
    ap_int<33> v9790 = v9788 + v9789;	// L15333
    int32_t v9791 = v9790;	// L15334
    rcred14[1] = v9791;	// L15335
    int32_t v9792 = v9706.read();	// L15336
    int32_t v9793 = rcred14[2];	// L15337
    ap_int<33> v9794 = v9793;	// L15338
    ap_int<33> v9795 = v9792;	// L15339
    ap_int<33> v9796 = v9794 + v9795;	// L15340
    int32_t v9797 = v9796;	// L15341
    rcred14[2] = v9797;	// L15342
    int32_t v9798 = v9707.read();	// L15343
    int32_t v9799 = rcred14[3];	// L15344
    ap_int<33> v9800 = v9799;	// L15345
    ap_int<33> v9801 = v9798;	// L15346
    ap_int<33> v9802 = v9800 + v9801;	// L15347
    int32_t v9803 = v9802;	// L15348
    rcred14[3] = v9803;	// L15349
    ap_uint<26> fin14[4];	// L15350
    for (int v9805 = 0; v9805 < 4; v9805++) {	// L15351
      fin14[v9805] = 0;	// L15351
    }
    ap_int<26> v9806 = p_w14;	// L15352
    fin14[0] = v9806;	// L15353
    ap_int<26> v9807 = p_e14;	// L15354
    fin14[1] = v9807;	// L15355
    ap_int<26> v9808 = p_n14;	// L15356
    fin14[2] = v9808;	// L15357
    ap_int<26> v9809 = p_s14;	// L15358
    fin14[3] = v9809;	// L15359
    l_S_d_0_d56: for (int d56 = 0; d56 < 4; d56++) {	// L15360
      ap_uint<26> v9811 = fin14[d56];	// L15361
      bool v9812;
      ap_int<26> v9812_tmp = v9811;
      v9812 = v9812_tmp[25];	// L15362
      int32_t v9813 = v9812;	// L15363
      bool v9814 = v9813 == 1;	// L15364
      int32_t v9815 = rbcnt14[d56];	// L15365
      bool v9816 = v9815 < 2;	// L15366
      bool v9817 = v9814 & v9816;	// L15367
      if (v9817) {	// L15368
        ap_uint<26> v9818 = fin14[d56];	// L15369
        int32_t v9819 = rbcnt14[d56];	// L15370
        int v9820 = v9819;	// L15371
        rbuf14[d56][v9820] = v9818;	// L15372
        int32_t v9821 = rbcnt14[d56];	// L15373
        ap_int<33> v9822 = v9821;	// L15374
        ap_int<33> v9823 = v9822 + 1;	// L15375
        int32_t v9824 = v9823;	// L15376
        rbcnt14[d56] = v9824;	// L15377
      }
    }
    ap_uint<26> hd14[4];	// L15380
    for (int v9826 = 0; v9826 < 4; v9826++) {	// L15381
      hd14[v9826] = 0;	// L15381
    }
    int32_t hvld14[4];	// L15382
    for (int v9828 = 0; v9828 < 4; v9828++) {	// L15383
      hvld14[v9828] = 0;	// L15383
    }
    int32_t hit14[4];	// L15384
    for (int v9830 = 0; v9830 < 4; v9830++) {	// L15385
      hit14[v9830] = 0;	// L15385
    }
    int32_t axis14[4];	// L15386
    for (int v9832 = 0; v9832 < 4; v9832++) {	// L15387
      axis14[v9832] = 0;	// L15387
    }
    int32_t v9833 = col_id14;	// L15388
    axis14[0] = v9833;	// L15389
    int32_t v9834 = col_id14;	// L15390
    axis14[1] = v9834;	// L15391
    int32_t v9835 = row_id14;	// L15392
    axis14[2] = v9835;	// L15393
    int32_t v9836 = row_id14;	// L15394
    axis14[3] = v9836;	// L15395
    l_S_d_1_d57: for (int d57 = 0; d57 < 4; d57++) {	// L15396
      int32_t v9838 = rbcnt14[d57];	// L15397
      bool v9839 = v9838 > 0;	// L15398
      if (v9839) {	// L15399
        ap_uint<26> v9840 = rbuf14[d57][0];	// L15400
        hd14[d57] = v9840;	// L15401
        hvld14[d57] = 1;	// L15402
        ap_uint<26> v9841 = hd14[d57];	// L15403
        ap_int<4> v9842;
        ap_int<26> v9842_tmp = v9841;
        v9842 = v9842_tmp(24, 21);	// L15404
        int32_t v9843 = axis14[d57];	// L15405
        int32_t v9844 = v9842;	// L15406
        bool v9845 = v9844 == v9843;	// L15407
        if (v9845) {	// L15408
          hit14[d57] = 1;	// L15409
        }
      }
    }
    ap_uint<26> o_crv14;	// L15413
    o_crv14 = 0;	// L15414
    int32_t crv_in14;	// L15415
    crv_in14 = -1;	// L15416
    int32_t v9848 = hit14[3];	// L15417
    bool v9849 = v9848 == 1;	// L15418
    if (v9849) {	// L15419
      ap_uint<26> v9850 = hd14[3];	// L15420
      o_crv14 = v9850;	// L15421
      crv_in14 = 3;	// L15422
    } else {
      int32_t v9851 = hit14[2];	// L15424
      bool v9852 = v9851 == 1;	// L15425
      if (v9852) {	// L15426
        ap_uint<26> v9853 = hd14[2];	// L15427
        o_crv14 = v9853;	// L15428
        crv_in14 = 2;	// L15429
      } else {
        int32_t v9854 = hit14[1];	// L15431
        bool v9855 = v9854 == 1;	// L15432
        if (v9855) {	// L15433
          ap_uint<26> v9856 = hd14[1];	// L15434
          o_crv14 = v9856;	// L15435
          crv_in14 = 1;	// L15436
        } else {
          int32_t v9857 = hit14[0];	// L15438
          bool v9858 = v9857 == 1;	// L15439
          if (v9858) {	// L15440
            ap_uint<26> v9859 = hd14[0];	// L15441
            o_crv14 = v9859;	// L15442
            crv_in14 = 0;	// L15443
          }
        }
      }
    }
    ap_uint<26> o_out14[4];	// L15448
    for (int v9861 = 0; v9861 < 4; v9861++) {	// L15449
      o_out14[v9861] = 0;	// L15449
    }
    int32_t pop14[4];	// L15450
    for (int v9863 = 0; v9863 < 4; v9863++) {	// L15451
      pop14[v9863] = 0;	// L15451
    }
    int32_t inj_done14;	// L15452
    inj_done14 = 0;	// L15453
    int32_t idir14;	// L15454
    idir14 = -1;	// L15455
    ap_int<26> v9866 = csd_pkt14;	// L15456
    bool v9867;
    ap_int<26> v9867_tmp = v9866;
    v9867 = v9867_tmp[25];	// L15457
    int32_t v9868 = v9867;	// L15458
    bool v9869 = v9868 == 1;	// L15459
    if (v9869) {	// L15460
      int32_t v9870 = csd_dir14;	// L15461
      ap_int<33> v9871 = v9870;	// L15462
      ap_int<33> v9872 = 3 - v9871;	// L15463
      int32_t v9873 = v9872;	// L15464
      idir14 = v9873;	// L15465
    }
    l_S_o_2_o14: for (int o14 = 0; o14 < 4; o14++) {	// L15467
      int32_t v9875 = rcred14[o14];	// L15468
      bool v9876 = v9875 > 0;	// L15469
      if (v9876) {	// L15470
        int32_t v9877 = idir14;	// L15471
        ap_int<33> v9878 = v9877;	// L15472
        ap_int<33> v9879 = o14;	// L15473
        bool v9880 = v9878 == v9879;	// L15474
        if (v9880) {	// L15475
          ap_int<26> v9881 = csd_pkt14;	// L15476
          o_out14[o14] = v9881;	// L15477
          int32_t v9882 = rcred14[o14];	// L15478
          ap_int<33> v9883 = v9882;	// L15479
          ap_int<33> v9884 = v9883 - 1;	// L15480
          int32_t v9885 = v9884;	// L15481
          rcred14[o14] = v9885;	// L15482
          inj_done14 = 1;	// L15483
        } else {
          int32_t v9886 = hvld14[o14];	// L15485
          bool v9887 = v9886 == 1;	// L15486
          int32_t v9888 = hit14[o14];	// L15487
          bool v9889 = v9888 == 0;	// L15488
          bool v9890 = v9887 & v9889;	// L15489
          if (v9890) {	// L15490
            ap_uint<26> v9891 = hd14[o14];	// L15491
            o_out14[o14] = v9891;	// L15492
            int32_t v9892 = rcred14[o14];	// L15493
            ap_int<33> v9893 = v9892;	// L15494
            ap_int<33> v9894 = v9893 - 1;	// L15495
            int32_t v9895 = v9894;	// L15496
            rcred14[o14] = v9895;	// L15497
            pop14[o14] = 1;	// L15498
          }
        }
      }
    }
    int32_t v9896 = crv_in14;	// L15503
    bool v9897 = v9896 >= 0;	// L15504
    if (v9897) {	// L15505
      int32_t v9898 = crv_in14;	// L15506
      int v9899 = v9898;	// L15507
      pop14[v9899] = 1;	// L15508
    }
    int32_t ret14[4];	// L15510
    for (int v9901 = 0; v9901 < 4; v9901++) {	// L15511
      ret14[v9901] = 0;	// L15511
    }
    l_S_d_3_d58: for (int d58 = 0; d58 < 4; d58++) {	// L15512
      int32_t v9903 = pop14[d58];	// L15513
      bool v9904 = v9903 == 1;	// L15514
      if (v9904) {	// L15515
        l_S_sft_3_sft14: for (int sft14 = 0; sft14 < 1; sft14++) {	// L15516
          ap_uint<26> v9906 = rbuf14[d58][(sft14 + 1)];	// L15517
          rbuf14[d58][sft14] = v9906;	// L15518
        }
        int32_t v9907 = rbcnt14[d58];	// L15520
        ap_int<33> v9908 = v9907;	// L15521
        ap_int<33> v9909 = v9908 - 1;	// L15522
        int32_t v9910 = v9909;	// L15523
        rbcnt14[d58] = v9910;	// L15524
        ret14[d58] = 1;	// L15525
      }
    }
    int32_t v9911 = ret14[0];	// L15528
    cre_r14 = v9911;	// L15529
    int32_t v9912 = ret14[1];	// L15530
    crw_r14 = v9912;	// L15531
    int32_t v9913 = ret14[2];	// L15532
    crs_r14 = v9913;	// L15533
    int32_t v9914 = ret14[3];	// L15534
    crn_r14 = v9914;	// L15535
    ap_uint<26> v9915 = o_out14[0];	// L15536
    oe_r14 = v9915;	// L15537
    ap_uint<26> v9916 = o_out14[1];	// L15538
    ow_r14 = v9916;	// L15539
    ap_uint<26> v9917 = o_out14[2];	// L15540
    os_r14 = v9917;	// L15541
    ap_uint<26> v9918 = o_out14[3];	// L15542
    on_r14 = v9918;	// L15543
    int32_t v9919 = inj_done14;	// L15544
    bool v9920 = v9919 == 1;	// L15545
    if (v9920) {	// L15546
      csd_pkt14 = 0;	// L15547
    }
    ap_int<26> v9921 = o_crv14;	// L15549
    bool v9922;
    ap_int<26> v9922_tmp = v9921;
    v9922 = v9922_tmp[25];	// L15550
    int32_t v9923 = v9922;	// L15551
    crv_vld14 = v9923;	// L15552
    ap_int<26> v9924 = o_crv14;	// L15553
    int16_t v9925;
    ap_int<26> v9925_tmp = v9924;
    v9925 = v9925_tmp(15, 0);	// L15554
    half v9926;
    union { uint16_t from; half to;} _converter_v9925_to_v9926;
    _converter_v9925_to_v9926.from = v9925;
    v9926 = _converter_v9925_to_v9926.to;	// L15555
    crv_data14 = v9926;	// L15556
    ap_int<26> v9927 = o_crv14;	// L15557
    ap_int<4> v9928;
    ap_int<26> v9928_tmp = v9927;
    v9928 = v9928_tmp(19, 16);	// L15558
    int32_t v9929 = v9928;	// L15559
    crv_addr14 = v9929;	// L15560
    ap_int<26> v9930 = o_crv14;	// L15561
    bool v9931;
    ap_int<26> v9931_tmp = v9930;
    v9931 = v9931_tmp[20];	// L15562
    int32_t v9932 = v9931;	// L15563
    crv_mode14 = v9932;	// L15564
    ap_int<26> v9933 = o_crv14;	// L15565
    int16_t v9934;
    ap_int<26> v9934_tmp = v9933;
    v9934 = v9934_tmp(15, 0);	// L15566
    int32_t v9935 = v9934;	// L15567
    crv_raw14 = v9935;	// L15568
    ap_uint<17> v9936 = v9708.read();	// L15569
    ap_uint<17> rx_w14;	// L15570
    rx_w14 = v9936;	// L15571
    ap_uint<17> v9938 = v9709.read();	// L15572
    ap_uint<17> rx_e14;	// L15573
    rx_e14 = v9938;	// L15574
    ap_uint<17> v9940 = v9710.read();	// L15575
    ap_uint<17> rx_n14;	// L15576
    rx_n14 = v9940;	// L15577
    ap_uint<17> v9942 = v9711.read();	// L15578
    ap_uint<17> rx_s14;	// L15579
    rx_s14 = v9942;	// L15580
    half rxv14[4];	// L15581
    for (int v9945 = 0; v9945 < 4; v9945++) {	// L15582
      rxv14[v9945] = (double)0.000000;	// L15582
    }
    int32_t rxvld14[4];	// L15583
    for (int v9947 = 0; v9947 < 4; v9947++) {	// L15584
      rxvld14[v9947] = 0;	// L15584
    }
    ap_int<17> v9948 = rx_n14;	// L15585
    int16_t v9949;
    ap_int<17> v9949_tmp = v9948;
    v9949 = v9949_tmp(16, 1);	// L15586
    half v9950;
    union { uint16_t from; half to;} _converter_v9949_to_v9950;
    _converter_v9949_to_v9950.from = v9949;
    v9950 = _converter_v9949_to_v9950.to;	// L15587
    rxv14[0] = v9950;	// L15588
    ap_int<17> v9951 = rx_n14;	// L15589
    bool v9952;
    ap_int<17> v9952_tmp = v9951;
    v9952 = v9952_tmp[0];	// L15590
    int32_t v9953 = v9952;	// L15591
    rxvld14[0] = v9953;	// L15592
    ap_int<17> v9954 = rx_s14;	// L15593
    int16_t v9955;
    ap_int<17> v9955_tmp = v9954;
    v9955 = v9955_tmp(16, 1);	// L15594
    half v9956;
    union { uint16_t from; half to;} _converter_v9955_to_v9956;
    _converter_v9955_to_v9956.from = v9955;
    v9956 = _converter_v9955_to_v9956.to;	// L15595
    rxv14[1] = v9956;	// L15596
    ap_int<17> v9957 = rx_s14;	// L15597
    bool v9958;
    ap_int<17> v9958_tmp = v9957;
    v9958 = v9958_tmp[0];	// L15598
    int32_t v9959 = v9958;	// L15599
    rxvld14[1] = v9959;	// L15600
    ap_int<17> v9960 = rx_w14;	// L15601
    int16_t v9961;
    ap_int<17> v9961_tmp = v9960;
    v9961 = v9961_tmp(16, 1);	// L15602
    half v9962;
    union { uint16_t from; half to;} _converter_v9961_to_v9962;
    _converter_v9961_to_v9962.from = v9961;
    v9962 = _converter_v9961_to_v9962.to;	// L15603
    rxv14[2] = v9962;	// L15604
    ap_int<17> v9963 = rx_w14;	// L15605
    bool v9964;
    ap_int<17> v9964_tmp = v9963;
    v9964 = v9964_tmp[0];	// L15606
    int32_t v9965 = v9964;	// L15607
    rxvld14[2] = v9965;	// L15608
    ap_int<17> v9966 = rx_e14;	// L15609
    int16_t v9967;
    ap_int<17> v9967_tmp = v9966;
    v9967 = v9967_tmp(16, 1);	// L15610
    half v9968;
    union { uint16_t from; half to;} _converter_v9967_to_v9968;
    _converter_v9967_to_v9968.from = v9967;
    v9968 = _converter_v9967_to_v9968.to;	// L15611
    rxv14[3] = v9968;	// L15612
    ap_int<17> v9969 = rx_e14;	// L15613
    bool v9970;
    ap_int<17> v9970_tmp = v9969;
    v9970 = v9970_tmp[0];	// L15614
    int32_t v9971 = v9970;	// L15615
    rxvld14[3] = v9971;	// L15616
    l_S_d_5_d59: for (int d59 = 0; d59 < 4; d59++) {	// L15617
      int32_t v9973 = rxvld14[d59];	// L15618
      bool v9974 = v9973 == 1;	// L15619
      int32_t v9975 = hold_cnt14[d59];	// L15620
      bool v9976 = v9975 < 2;	// L15621
      bool v9977 = v9974 & v9976;	// L15622
      if (v9977) {	// L15623
        half v9978 = rxv14[d59];	// L15624
        int32_t v9979 = hold_cnt14[d59];	// L15625
        int v9980 = v9979;	// L15626
        hold_v14[d59][v9980] = v9978;	// L15627
        int32_t v9981 = hold_cnt14[d59];	// L15628
        ap_int<33> v9982 = v9981;	// L15629
        ap_int<33> v9983 = v9982 + 1;	// L15630
        int32_t v9984 = v9983;	// L15631
        hold_cnt14[d59] = v9984;	// L15632
      }
    }
    int32_t pc14;	// L15635
    pc14 = -1;	// L15636
    int32_t v9986 = fetch_en14;	// L15637
    bool v9987 = v9986 == 1;	// L15638
    if (v9987) {	// L15639
      int32_t v9988 = instr_cnt14;	// L15640
      pc14 = v9988;	// L15641
    }
    int32_t instr14;	// L15643
    instr14 = 0;	// L15644
    int32_t v9990 = pc14;	// L15645
    bool v9991 = v9990 >= 0;	// L15646
    if (v9991) {	// L15647
      int32_t v9992 = pc14;	// L15648
      int v9993 = v9992;	// L15649
      int32_t v9994 = irf14[v9993];	// L15650
      instr14 = v9994;	// L15651
    }
    int32_t v9995 = instr14;	// L15653
    int32_t v9996 = v9995 & 15;	// L15654
    int32_t op14;	// L15655
    op14 = v9996;	// L15656
    int32_t v9998 = instr14;	// L15657
    int32_t v9999 = v9998 >> 4;	// L15658
    int32_t v10000 = v9999 & 15;	// L15659
    int32_t dst14;	// L15660
    dst14 = v10000;	// L15661
    int32_t v10002 = instr14;	// L15662
    int32_t v10003 = v10002 >> 8;	// L15663
    int32_t v10004 = v10003 & 15;	// L15664
    int32_t s114;	// L15665
    s114 = v10004;	// L15666
    int32_t v10006 = instr14;	// L15667
    int32_t v10007 = v10006 >> 12;	// L15668
    int32_t v10008 = v10007 & 15;	// L15669
    int32_t s214;	// L15670
    s214 = v10008;	// L15671
    half a14;	// L15672
    a14 = (double)0.000000;	// L15673
    half b14;	// L15674
    b14 = (double)0.000000;	// L15675
    int32_t v10012 = s114;	// L15676
    bool v10013 = v10012 >= 12;	// L15677
    if (v10013) {	// L15678
      int32_t v10014 = s114;	// L15679
      int32_t v10015 = v10014 & 3;	// L15680
      int v10016 = v10015;	// L15681
      half v10017 = hold_v14[v10016][0];	// L15682
      a14 = v10017;	// L15683
    } else {
      int32_t v10018 = s114;	// L15685
      int v10019 = v10018;	// L15686
      half v10020 = drf14[v10019];	// L15687
      a14 = v10020;	// L15688
    }
    int32_t v10021 = s214;	// L15690
    bool v10022 = v10021 >= 12;	// L15691
    if (v10022) {	// L15692
      int32_t v10023 = s214;	// L15693
      int32_t v10024 = v10023 & 3;	// L15694
      int v10025 = v10024;	// L15695
      half v10026 = hold_v14[v10025][0];	// L15696
      b14 = v10026;	// L15697
    } else {
      int32_t v10027 = s214;	// L15699
      int v10028 = v10027;	// L15700
      half v10029 = drf14[v10028];	// L15701
      b14 = v10029;	// L15702
    }
    int32_t a_vld14;	// L15704
    a_vld14 = 1;	// L15705
    int32_t b_vld14;	// L15706
    b_vld14 = 1;	// L15707
    int32_t v10032 = s114;	// L15708
    bool v10033 = v10032 >= 12;	// L15709
    if (v10033) {	// L15710
      a_vld14 = 0;	// L15711
      int32_t v10034 = s114;	// L15712
      int32_t v10035 = v10034 & 3;	// L15713
      int v10036 = v10035;	// L15714
      int32_t v10037 = hold_cnt14[v10036];	// L15715
      bool v10038 = v10037 > 0;	// L15716
      if (v10038) {	// L15717
        a_vld14 = 1;	// L15718
      }
    }
    int32_t v10039 = s214;	// L15721
    bool v10040 = v10039 >= 12;	// L15722
    if (v10040) {	// L15723
      b_vld14 = 0;	// L15724
      int32_t v10041 = s214;	// L15725
      int32_t v10042 = v10041 & 3;	// L15726
      int v10043 = v10042;	// L15727
      int32_t v10044 = hold_cnt14[v10043];	// L15728
      bool v10045 = v10044 > 0;	// L15729
      if (v10045) {	// L15730
        b_vld14 = 1;	// L15731
      }
    }
    int32_t v10046 = s114;	// L15734
    bool v10047 = v10046 < 8;	// L15735
    int32_t v10048 = dsmask14;	// L15736
    int32_t v10049 = v10048 >> v10046;	// L15737
    int32_t v10050 = v10049 & 1;	// L15738
    bool v10051 = v10050 == 1;	// L15739
    bool v10052 = v10047 & v10051;	// L15740
    if (v10052) {	// L15741
      int32_t v10053 = s114;	// L15742
      int v10054 = v10053;	// L15743
      int32_t v10055 = drf_full14[v10054];	// L15744
      bool v10056 = v10055 == 0;	// L15745
      if (v10056) {	// L15746
        a_vld14 = 0;	// L15747
      }
    }
    int32_t v10057 = s214;	// L15750
    bool v10058 = v10057 < 8;	// L15751
    int32_t v10059 = dsmask14;	// L15752
    int32_t v10060 = v10059 >> v10057;	// L15753
    int32_t v10061 = v10060 & 1;	// L15754
    bool v10062 = v10061 == 1;	// L15755
    bool v10063 = v10058 & v10062;	// L15756
    if (v10063) {	// L15757
      int32_t v10064 = s214;	// L15758
      int v10065 = v10064;	// L15759
      int32_t v10066 = drf_full14[v10065];	// L15760
      bool v10067 = v10066 == 0;	// L15761
      if (v10067) {	// L15762
        b_vld14 = 0;	// L15763
      }
    }
    int32_t binop14;	// L15766
    binop14 = 0;	// L15767
    int32_t v10069 = op14;	// L15768
    bool v10070 = v10069 == 0;	// L15769
    bool v10071 = v10069 == 1;	// L15770
    bool v10072 = v10069 == 2;	// L15771
    bool v10073 = v10069 == 8;	// L15772
    bool v10074 = v10069 == 9;	// L15773
    bool v10075 = v10070 | v10071;	// L15774
    bool v10076 = v10075 | v10072;	// L15775
    bool v10077 = v10076 | v10073;	// L15776
    bool v10078 = v10077 | v10074;	// L15777
    if (v10078) {	// L15778
      binop14 = 1;	// L15779
    }
    int32_t grant14;	// L15781
    grant14 = 0;	// L15782
    int32_t v10080 = pc14;	// L15783
    bool v10081 = v10080 >= 0;	// L15784
    if (v10081) {	// L15785
      grant14 = 1;	// L15786
    }
    int32_t v10082 = pc14;	// L15788
    bool v10083 = v10082 >= 0;	// L15789
    int32_t v10084 = a_vld14;	// L15790
    bool v10085 = v10084 == 0;	// L15791
    int32_t v10086 = binop14;	// L15792
    bool v10087 = v10086 == 1;	// L15793
    int32_t v10088 = b_vld14;	// L15794
    bool v10089 = v10088 == 0;	// L15795
    bool v10090 = v10087 & v10089;	// L15796
    bool v10091 = v10085 | v10090;	// L15797
    bool v10092 = v10083 & v10091;	// L15798
    if (v10092) {	// L15799
      grant14 = 0;	// L15800
    }
    int32_t v10093 = grant14;	// L15802
    bool v10094 = v10093 == 1;	// L15803
    if (v10094) {	// L15804
      int32_t v10095 = instr_cnt14;	// L15805
      int32_t v10096 = cfg_isz14;	// L15806
      bool v10097 = v10095 == v10096;	// L15807
      if (v10097) {	// L15808
        instr_cnt14 = 0;	// L15809
        int32_t v10098 = iter_cnt14;	// L15810
        int32_t v10099 = cfg_itsz14;	// L15811
        ap_int<33> v10100 = v10099;	// L15812
        ap_int<33> v10101 = v10100 - 1;	// L15813
        ap_int<33> v10102 = v10098;	// L15814
        bool v10103 = v10102 == v10101;	// L15815
        if (v10103) {	// L15816
          fetch_en14 = 0;	// L15817
        } else {
          int32_t v10104 = iter_cnt14;	// L15819
          ap_int<33> v10105 = v10104;	// L15820
          ap_int<33> v10106 = v10105 + 1;	// L15821
          int32_t v10107 = v10106;	// L15822
          iter_cnt14 = v10107;	// L15823
        }
      } else {
        int32_t v10108 = instr_cnt14;	// L15826
        ap_int<33> v10109 = v10108;	// L15827
        ap_int<33> v10110 = v10109 + 1;	// L15828
        int32_t v10111 = v10110;	// L15829
        instr_cnt14 = v10111;	// L15830
      }
    }
    int32_t c114;	// L15833
    c114 = -1;	// L15834
    int32_t c214;	// L15835
    c214 = -1;	// L15836
    int32_t v10114 = grant14;	// L15837
    bool v10115 = v10114 == 1;	// L15838
    int32_t v10116 = s114;	// L15839
    bool v10117 = v10116 >= 12;	// L15840
    bool v10118 = v10115 & v10117;	// L15841
    if (v10118) {	// L15842
      int32_t v10119 = s114;	// L15843
      int32_t v10120 = v10119 & 3;	// L15844
      c114 = v10120;	// L15845
    }
    int32_t v10121 = grant14;	// L15847
    bool v10122 = v10121 == 1;	// L15848
    int32_t v10123 = s214;	// L15849
    bool v10124 = v10123 >= 12;	// L15850
    bool v10125 = v10122 & v10124;	// L15851
    if (v10125) {	// L15852
      int32_t v10126 = s214;	// L15853
      int32_t v10127 = v10126 & 3;	// L15854
      c214 = v10127;	// L15855
    }
    int32_t v10128 = c114;	// L15857
    bool v10129 = v10128 >= 0;	// L15858
    if (v10129) {	// L15859
      int32_t v10130 = c114;	// L15860
      int v10131 = v10130;	// L15861
      half v10132 = hold_v14[v10131][1];	// L15862
      hold_v14[v10131][0] = v10132;	// L15863
      int32_t v10133 = c114;	// L15864
      int v10134 = v10133;	// L15865
      int32_t v10135 = hold_cnt14[v10134];	// L15866
      ap_int<33> v10136 = v10135;	// L15867
      ap_int<33> v10137 = v10136 - 1;	// L15868
      int32_t v10138 = v10137;	// L15869
      hold_cnt14[v10134] = v10138;	// L15870
    }
    int32_t v10139 = c214;	// L15872
    bool v10140 = v10139 >= 0;	// L15873
    int32_t v10141 = c114;	// L15874
    bool v10142 = v10139 != v10141;	// L15875
    bool v10143 = v10140 & v10142;	// L15876
    if (v10143) {	// L15877
      int32_t v10144 = c214;	// L15878
      int v10145 = v10144;	// L15879
      half v10146 = hold_v14[v10145][1];	// L15880
      hold_v14[v10145][0] = v10146;	// L15881
      int32_t v10147 = c214;	// L15882
      int v10148 = v10147;	// L15883
      int32_t v10149 = hold_cnt14[v10148];	// L15884
      ap_int<33> v10150 = v10149;	// L15885
      ap_int<33> v10151 = v10150 - 1;	// L15886
      int32_t v10152 = v10151;	// L15887
      hold_cnt14[v10148] = v10152;	// L15888
    }
    int32_t v10153 = grant14;	// L15890
    bool v10154 = v10153 == 1;	// L15891
    int32_t v10155 = s114;	// L15892
    bool v10156 = v10155 < 8;	// L15893
    int32_t v10157 = dsmask14;	// L15894
    int32_t v10158 = v10157 >> v10155;	// L15895
    int32_t v10159 = v10158 & 1;	// L15896
    bool v10160 = v10159 == 1;	// L15897
    bool v10161 = v10154 & v10156;	// L15898
    bool v10162 = v10161 & v10160;	// L15899
    if (v10162) {	// L15900
      int32_t v10163 = s114;	// L15901
      int v10164 = v10163;	// L15902
      drf_full14[v10164] = 0;	// L15903
    }
    int32_t v10165 = grant14;	// L15905
    bool v10166 = v10165 == 1;	// L15906
    int32_t v10167 = s214;	// L15907
    bool v10168 = v10167 < 8;	// L15908
    int32_t v10169 = dsmask14;	// L15909
    int32_t v10170 = v10169 >> v10167;	// L15910
    int32_t v10171 = v10170 & 1;	// L15911
    bool v10172 = v10171 == 1;	// L15912
    bool v10173 = v10166 & v10168;	// L15913
    bool v10174 = v10173 & v10172;	// L15914
    if (v10174) {	// L15915
      int32_t v10175 = s214;	// L15916
      int v10176 = v10175;	// L15917
      drf_full14[v10176] = 0;	// L15918
    }
    half res14;	// L15920
    res14 = (double)0.000000;	// L15921
    int32_t v10178 = op14;	// L15922
    bool v10179 = v10178 == 0;	// L15923
    if (v10179) {	// L15924
      half v10180 = a14;	// L15925
      half v10181 = b14;	// L15926
      half v10182 = v10180 + v10181;	// L15927
      res14 = v10182;	// L15928
    } else {
      int32_t v10183 = op14;	// L15930
      bool v10184 = v10183 == 1;	// L15931
      if (v10184) {	// L15932
        half v10185 = a14;	// L15933
        half v10186 = b14;	// L15934
        half v10187 = v10185 - v10186;	// L15935
        res14 = v10187;	// L15936
      } else {
        int32_t v10188 = op14;	// L15938
        bool v10189 = v10188 == 2;	// L15939
        if (v10189) {	// L15940
          half v10190 = a14;	// L15941
          half v10191 = b14;	// L15942
          half v10192 = v10190 * v10191;	// L15943
          res14 = v10192;	// L15944
        } else {
          int32_t v10193 = op14;	// L15946
          bool v10194 = v10193 == 8;	// L15947
          if (v10194) {	// L15948
            half v10195 = a14;	// L15949
            half v10196 = b14;	// L15950
            bool v10197 = v10195 >= v10196;	// L15951
            if (v10197) {	// L15952
              res14 = (double)1.000000;	// L15953
            } else {
              res14 = (double)-1.000000;	// L15955
            }
          } else {
            int32_t v10198 = op14;	// L15958
            bool v10199 = v10198 == 9;	// L15959
            if (v10199) {	// L15960
              half v10200 = a14;	// L15961
              half v10201 = b14;	// L15962
              bool v10202 = v10200 < v10201;	// L15963
              if (v10202) {	// L15964
                res14 = (double)1.000000;	// L15965
              } else {
                res14 = (double)-1.000000;	// L15967
              }
            } else {
              half v10203 = a14;	// L15970
              res14 = v10203;	// L15971
            }
          }
        }
      }
    }
    int32_t v10204 = a_vld14;	// L15977
    int32_t res_vld14;	// L15978
    res_vld14 = v10204;	// L15979
    int32_t v10206 = op14;	// L15980
    bool v10207 = v10206 == 0;	// L15981
    bool v10208 = v10206 == 1;	// L15982
    bool v10209 = v10206 == 2;	// L15983
    bool v10210 = v10206 == 8;	// L15984
    bool v10211 = v10206 == 9;	// L15985
    bool v10212 = v10207 | v10208;	// L15986
    bool v10213 = v10212 | v10209;	// L15987
    bool v10214 = v10213 | v10210;	// L15988
    bool v10215 = v10214 | v10211;	// L15989
    if (v10215) {	// L15990
      int32_t v10216 = a_vld14;	// L15991
      int32_t v10217 = b_vld14;	// L15992
      int64_t v10218 = v10216;	// L15993
      int64_t v10219 = v10217;	// L15994
      int64_t v10220 = v10218 * v10219;	// L15995
      int32_t v10221 = v10220;	// L15996
      res_vld14 = v10221;	// L15997
    }
    int32_t v10222 = grant14;	// L15999
    bool v10223 = v10222 == 0;	// L16000
    if (v10223) {	// L16001
      res_vld14 = 0;	// L16002
    }
    int32_t v10224 = grant14;	// L16004
    bool v10225 = v10224 == 1;	// L16005
    int32_t v10226 = op14;	// L16006
    bool v10227 = v10226 == 8;	// L16007
    bool v10228 = v10225 & v10227;	// L16008
    if (v10228) {	// L16009
      condition_reg14 = 0;	// L16010
      half v10229 = a14;	// L16011
      half v10230 = b14;	// L16012
      bool v10231 = v10229 >= v10230;	// L16013
      if (v10231) {	// L16014
        condition_reg14 = 1;	// L16015
      }
    }
    int32_t v10232 = grant14;	// L16018
    bool v10233 = v10232 == 1;	// L16019
    int32_t v10234 = op14;	// L16020
    bool v10235 = v10234 == 9;	// L16021
    bool v10236 = v10233 & v10235;	// L16022
    if (v10236) {	// L16023
      condition_reg14 = 0;	// L16024
      half v10237 = a14;	// L16025
      half v10238 = b14;	// L16026
      bool v10239 = v10237 < v10238;	// L16027
      if (v10239) {	// L16028
        condition_reg14 = 1;	// L16029
      }
    }
    ap_uint<17> tx_n14;	// L16032
    tx_n14 = 0;	// L16033
    ap_uint<17> tx_s14;	// L16034
    tx_s14 = 0;	// L16035
    ap_uint<17> tx_w14;	// L16036
    tx_w14 = 0;	// L16037
    ap_uint<17> tx_e14;	// L16038
    tx_e14 = 0;	// L16039
    int32_t is_rtr14;	// L16040
    is_rtr14 = 0;	// L16041
    int32_t do_inj14;	// L16042
    do_inj14 = 0;	// L16043
    int32_t v10246 = op14;	// L16044
    bool v10247 = v10246 >= 4;	// L16045
    ap_int<33> v10248 = v10246;	// L16046
    bool v10249 = v10248 <= 7;	// L16047
    bool v10250 = v10247 & v10249;	// L16048
    if (v10250) {	// L16049
      is_rtr14 = 1;	// L16050
      do_inj14 = 1;	// L16051
    }
    int32_t v10251 = op14;	// L16053
    bool v10252 = v10251 >= 12;	// L16054
    ap_int<33> v10253 = v10251;	// L16055
    bool v10254 = v10253 <= 15;	// L16056
    bool v10255 = v10252 & v10254;	// L16057
    if (v10255) {	// L16058
      is_rtr14 = 1;	// L16059
      int32_t v10256 = condition_reg14;	// L16060
      bool v10257 = v10256 == 1;	// L16061
      if (v10257) {	// L16062
        do_inj14 = 1;	// L16063
      }
    }
    int32_t v10258 = is_rtr14;	// L16066
    bool v10259 = v10258 == 1;	// L16067
    if (v10259) {	// L16068
      int32_t v10260 = do_inj14;	// L16069
      bool v10261 = v10260 == 1;	// L16070
      ap_int<26> v10262 = csd_pkt14;	// L16071
      bool v10263;
      ap_int<26> v10263_tmp = v10262;
      v10263 = v10263_tmp[25];	// L16072
      int32_t v10264 = v10263;	// L16073
      bool v10265 = v10264 == 0;	// L16074
      bool v10266 = v10261 & v10265;	// L16075
      if (v10266) {	// L16076
        half v10267 = res14;	// L16077
        uint16_t v10268;
        union { half from; uint16_t to;} _converter_v10267_to_v10268;
        _converter_v10267_to_v10268.from = v10267;
        v10268 = _converter_v10267_to_v10268.to;	// L16078
        ap_int<26> v10269 = csd_pkt14;	// L16079
        ap_int<26> v10270;
        ap_int<26> v10270_tmp = v10269;
        v10270_tmp(15, 0) = v10268;
        v10270 = v10270_tmp;	// L16080
        csd_pkt14 = v10270;	// L16081
        int32_t v10271 = dst14;	// L16082
        ap_uint<4> v10272 = v10271;	// L16083
        ap_int<26> v10273 = csd_pkt14;	// L16084
        ap_int<26> v10274;
        ap_int<26> v10274_tmp = v10273;
        v10274_tmp(19, 16) = v10272;
        v10274 = v10274_tmp;	// L16085
        csd_pkt14 = v10274;	// L16086
        int32_t v10275 = s214;	// L16087
        ap_uint<4> v10276 = v10275;	// L16088
        ap_int<26> v10277 = csd_pkt14;	// L16089
        ap_int<26> v10278;
        ap_int<26> v10278_tmp = v10277;
        v10278_tmp(24, 21) = v10276;
        v10278 = v10278_tmp;	// L16090
        csd_pkt14 = v10278;	// L16091
        int32_t v10279 = res_vld14;	// L16092
        bool v10280 = v10279;	// L16093
        ap_int<26> v10281 = csd_pkt14;	// L16094
        ap_int<26> v10282;
        ap_int<26> v10282_tmp = v10281;
        v10282_tmp[25] = v10280;        v10282 = v10282_tmp;	// L16095
        csd_pkt14 = v10282;	// L16096
        int32_t v10283 = op14;	// L16097
        int32_t v10284 = v10283 & 3;	// L16098
        csd_dir14 = v10284;	// L16099
      }
    } else {
      int32_t v10285 = dst14;	// L16102
      bool v10286 = v10285 >= 12;	// L16103
      if (v10286) {	// L16104
        ap_uint<17> tw14;	// L16105
        tw14 = 0;	// L16106
        int32_t v10288 = res_vld14;	// L16107
        bool v10289 = v10288;	// L16108
        ap_int<17> v10290 = tw14;	// L16109
        ap_int<17> v10291;
        ap_int<17> v10291_tmp = v10290;
        v10291_tmp[0] = v10289;        v10291 = v10291_tmp;	// L16110
        tw14 = v10291;	// L16111
        half v10292 = res14;	// L16112
        uint16_t v10293;
        union { half from; uint16_t to;} _converter_v10292_to_v10293;
        _converter_v10292_to_v10293.from = v10292;
        v10293 = _converter_v10292_to_v10293.to;	// L16113
        ap_int<17> v10294 = tw14;	// L16114
        ap_int<17> v10295;
        ap_int<17> v10295_tmp = v10294;
        v10295_tmp(16, 1) = v10293;
        v10295 = v10295_tmp;	// L16115
        tw14 = v10295;	// L16116
        int32_t v10296 = dst14;	// L16117
        int32_t v10297 = v10296 & 3;	// L16118
        bool v10298 = v10297 == 0;	// L16119
        if (v10298) {	// L16120
          ap_int<17> v10299 = tw14;	// L16121
          tx_n14 = v10299;	// L16122
        } else {
          int32_t v10300 = dst14;	// L16124
          int32_t v10301 = v10300 & 3;	// L16125
          bool v10302 = v10301 == 1;	// L16126
          if (v10302) {	// L16127
            ap_int<17> v10303 = tw14;	// L16128
            tx_s14 = v10303;	// L16129
          } else {
            int32_t v10304 = dst14;	// L16131
            int32_t v10305 = v10304 & 3;	// L16132
            bool v10306 = v10305 == 2;	// L16133
            if (v10306) {	// L16134
              ap_int<17> v10307 = tw14;	// L16135
              tx_w14 = v10307;	// L16136
            } else {
              ap_int<17> v10308 = tw14;	// L16138
              tx_e14 = v10308;	// L16139
            }
          }
        }
      } else {
        int32_t v10309 = res_vld14;	// L16144
        bool v10310 = v10309 == 1;	// L16145
        if (v10310) {	// L16146
          int32_t v10311 = dst14;	// L16147
          bool v10312 = v10311 < 8;	// L16148
          int32_t v10313 = dsmask14;	// L16149
          int32_t v10314 = v10313 >> v10311;	// L16150
          int32_t v10315 = v10314 & 1;	// L16151
          bool v10316 = v10315 == 1;	// L16152
          bool v10317 = v10312 & v10316;	// L16153
          if (v10317) {	// L16154
            int32_t v10318 = dst14;	// L16155
            int v10319 = v10318;	// L16156
            int32_t v10320 = drf_full14[v10319];	// L16157
            bool v10321 = v10320 == 0;	// L16158
            if (v10321) {	// L16159
              half v10322 = res14;	// L16160
              int32_t v10323 = dst14;	// L16161
              int v10324 = v10323;	// L16162
              drf14[v10324] = v10322;	// L16163
              int32_t v10325 = dst14;	// L16164
              int v10326 = v10325;	// L16165
              drf_full14[v10326] = 1;	// L16166
            }
          } else {
            half v10327 = res14;	// L16169
            int32_t v10328 = dst14;	// L16170
            int v10329 = v10328;	// L16171
            drf14[v10329] = v10327;	// L16172
          }
        }
      }
    }
    ap_int<17> v10330 = tx_n14;	// L16177
    txn_r14 = v10330;	// L16178
    ap_int<17> v10331 = tx_s14;	// L16179
    txs_r14 = v10331;	// L16180
    ap_int<17> v10332 = tx_w14;	// L16181
    txw_r14 = v10332;	// L16182
    ap_int<17> v10333 = tx_e14;	// L16183
    txe_r14 = v10333;	// L16184
    int32_t v10334 = crv_vld14;	// L16185
    bool v10335 = v10334 == 1;	// L16186
    if (v10335) {	// L16187
      int32_t v10336 = crv_mode14;	// L16188
      bool v10337 = v10336 == 1;	// L16189
      if (v10337) {	// L16190
        int32_t v10338 = crv_addr14;	// L16191
        int32_t v10339 = v10338 >> 3;	// L16192
        int32_t v10340 = v10339 & 1;	// L16193
        bool v10341 = v10340 == 1;	// L16194
        if (v10341) {	// L16195
          int32_t v10342 = crv_raw14;	// L16196
          int32_t v10343 = crv_addr14;	// L16197
          int32_t v10344 = v10343 & 7;	// L16198
          int v10345 = v10344;	// L16199
          irf14[v10345] = v10342;	// L16200
        } else {
          int32_t v10346 = crv_addr14;	// L16202
          bool v10347 = v10346 == 0;	// L16203
          if (v10347) {	// L16204
            int32_t v10348 = crv_raw14;	// L16205
            int32_t v10349 = v10348 & 255;	// L16206
            dsmask14 = v10349;	// L16207
            int32_t v10350 = crv_raw14;	// L16208
            int32_t v10351 = v10350 >> 8;	// L16209
            int32_t v10352 = v10351 & 7;	// L16210
            cfg_isz14 = v10352;	// L16211
            int32_t v10353 = crv_raw14;	// L16212
            int32_t v10354 = v10353 >> 15;	// L16213
            int32_t v10355 = v10354 & 1;	// L16214
            bool v10356 = v10355 == 1;	// L16215
            if (v10356) {	// L16216
              fetch_en14 = 1;	// L16217
              instr_cnt14 = 0;	// L16218
              iter_cnt14 = 0;	// L16219
            }
          } else {
            int32_t v10357 = crv_addr14;	// L16222
            bool v10358 = v10357 == 1;	// L16223
            if (v10358) {	// L16224
              int32_t v10359 = crv_raw14;	// L16225
              int32_t v10360 = v10359 & 255;	// L16226
              cfg_itsz14 = v10360;	// L16227
            }
          }
        }
      } else {
        int32_t v10361 = crv_addr14;	// L16232
        bool v10362 = v10361 < 8;	// L16233
        int32_t v10363 = dsmask14;	// L16234
        int32_t v10364 = v10363 >> v10361;	// L16235
        int32_t v10365 = v10364 & 1;	// L16236
        bool v10366 = v10365 == 1;	// L16237
        bool v10367 = v10362 & v10366;	// L16238
        if (v10367) {	// L16239
          int32_t v10368 = crv_addr14;	// L16240
          int v10369 = v10368;	// L16241
          int32_t v10370 = drf_full14[v10369];	// L16242
          bool v10371 = v10370 == 0;	// L16243
          if (v10371) {	// L16244
            half v10372 = crv_data14;	// L16245
            int32_t v10373 = crv_addr14;	// L16246
            int v10374 = v10373;	// L16247
            drf14[v10374] = v10372;	// L16248
            int32_t v10375 = crv_addr14;	// L16249
            int v10376 = v10375;	// L16250
            drf_full14[v10376] = 1;	// L16251
          }
        } else {
          half v10377 = crv_data14;	// L16254
          int32_t v10378 = crv_addr14;	// L16255
          int v10379 = v10378;	// L16256
          drf14[v10379] = v10377;	// L16257
        }
      }
    }
  }
}

void node_3_3(
  hls::stream< ap_uint<26> >& v10380,
  hls::stream< ap_uint<26> >& v10381,
  hls::stream< ap_uint<26> >& v10382,
  hls::stream< ap_uint<26> >& v10383,
  hls::stream< ap_uint<17> >& v10384,
  hls::stream< ap_uint<17> >& v10385,
  hls::stream< ap_uint<17> >& v10386,
  hls::stream< ap_uint<17> >& v10387,
  hls::stream< int32_t >& v10388,
  hls::stream< int32_t >& v10389,
  hls::stream< int32_t >& v10390,
  hls::stream< int32_t >& v10391,
  hls::stream< ap_uint<26> >& v10392,
  hls::stream< ap_uint<26> >& v10393,
  hls::stream< ap_uint<26> >& v10394,
  hls::stream< ap_uint<26> >& v10395,
  hls::stream< int32_t >& v10396,
  hls::stream< int32_t >& v10397,
  hls::stream< int32_t >& v10398,
  hls::stream< int32_t >& v10399,
  hls::stream< ap_uint<17> >& v10400,
  hls::stream< ap_uint<17> >& v10401,
  hls::stream< ap_uint<17> >& v10402,
  hls::stream< ap_uint<17> >& v10403
) {	// L16264
  int32_t irf15[8];	// L16295
  for (int v10405 = 0; v10405 < 8; v10405++) {	// L16296
    irf15[v10405] = 0;	// L16296
  }
  half drf15[8];	// L16297
  #pragma HLS array_partition variable=drf15 complete dim=1

  for (int v10407 = 0; v10407 < 8; v10407++) {	// L16298
    drf15[v10407] = (double)0.000000;	// L16298
  }
  int32_t drf_full15[8];	// L16299
  #pragma HLS array_partition variable=drf_full15 complete dim=1

  for (int v10409 = 0; v10409 < 8; v10409++) {	// L16300
    drf_full15[v10409] = 0;	// L16300
  }
  int32_t dsmask15;	// L16301
  dsmask15 = 0;	// L16302
  int32_t crv_vld15;	// L16303
  crv_vld15 = 0;	// L16304
  half crv_data15;	// L16305
  crv_data15 = (double)0.000000;	// L16306
  int32_t crv_addr15;	// L16307
  crv_addr15 = 0;	// L16308
  int32_t crv_mode15;	// L16309
  crv_mode15 = 0;	// L16310
  int32_t crv_raw15;	// L16311
  crv_raw15 = 0;	// L16312
  int32_t csd_vld15;	// L16313
  csd_vld15 = 0;	// L16314
  ap_uint<26> csd_pkt15;	// L16315
  csd_pkt15 = 0;	// L16316
  int32_t csd_dir15;	// L16317
  csd_dir15 = 0;	// L16318
  int32_t row_id15;	// L16319
  row_id15 = 3;	// L16320
  int32_t col_id15;	// L16321
  col_id15 = 3;	// L16322
  ap_uint<26> oe_r15;	// L16323
  oe_r15 = 0;	// L16324
  ap_uint<26> ow_r15;	// L16325
  ow_r15 = 0;	// L16326
  ap_uint<26> on_r15;	// L16327
  on_r15 = 0;	// L16328
  ap_uint<26> os_r15;	// L16329
  os_r15 = 0;	// L16330
  ap_uint<17> txn_r15;	// L16331
  txn_r15 = 0;	// L16332
  ap_uint<17> txs_r15;	// L16333
  txs_r15 = 0;	// L16334
  ap_uint<17> txw_r15;	// L16335
  txw_r15 = 0;	// L16336
  ap_uint<17> txe_r15;	// L16337
  txe_r15 = 0;	// L16338
  half hold_v15[4][2];	// L16339
  #pragma HLS array_partition variable=hold_v15 complete dim=1
  #pragma HLS array_partition variable=hold_v15 complete dim=2

  for (int v10430 = 0; v10430 < 4; v10430++) {	// L16340
    for (int v10431 = 0; v10431 < 2; v10431++) {	// L16340
      hold_v15[v10430][v10431] = (double)0.000000;	// L16340
    }
  }
  int32_t hold_cnt15[4];	// L16341
  #pragma HLS array_partition variable=hold_cnt15 complete dim=1

  for (int v10433 = 0; v10433 < 4; v10433++) {	// L16342
    hold_cnt15[v10433] = 0;	// L16342
  }
  ap_uint<26> rbuf15[4][2];	// L16343
  #pragma HLS array_partition variable=rbuf15 complete dim=1
  #pragma HLS array_partition variable=rbuf15 complete dim=2

  for (int v10435 = 0; v10435 < 4; v10435++) {	// L16344
    for (int v10436 = 0; v10436 < 2; v10436++) {	// L16344
      rbuf15[v10435][v10436] = 0;	// L16344
    }
  }
  int32_t rbcnt15[4];	// L16345
  #pragma HLS array_partition variable=rbcnt15 complete dim=1

  for (int v10438 = 0; v10438 < 4; v10438++) {	// L16346
    rbcnt15[v10438] = 0;	// L16346
  }
  int32_t rcred15[4];	// L16347
  #pragma HLS array_partition variable=rcred15 complete dim=1

  for (int v10440 = 0; v10440 < 4; v10440++) {	// L16348
    rcred15[v10440] = 0;	// L16348
  }
  int32_t cre_r15;	// L16349
  cre_r15 = 2;	// L16350
  int32_t crw_r15;	// L16351
  crw_r15 = 2;	// L16352
  int32_t crs_r15;	// L16353
  crs_r15 = 2;	// L16354
  int32_t crn_r15;	// L16355
  crn_r15 = 2;	// L16356
  int32_t cfg_isz15;	// L16357
  cfg_isz15 = 0;	// L16358
  int32_t cfg_itsz15;	// L16359
  cfg_itsz15 = 0;	// L16360
  int32_t fetch_en15;	// L16361
  fetch_en15 = 0;	// L16362
  int32_t instr_cnt15;	// L16363
  instr_cnt15 = 0;	// L16364
  int32_t iter_cnt15;	// L16365
  iter_cnt15 = 0;	// L16366
  int32_t condition_reg15;	// L16367
  condition_reg15 = 0;	// L16368
  l_S_t_0_t15: for (int t15 = 0; t15 < 8; t15++) {	// L16369
  #pragma HLS pipeline II=1
    ap_int<26> v10452 = oe_r15;	// L16370
    v10380.write(v10452);	// L16371
    ap_int<26> v10453 = ow_r15;	// L16372
    v10381.write(v10453);	// L16373
    ap_int<26> v10454 = os_r15;	// L16374
    v10382.write(v10454);	// L16375
    ap_int<26> v10455 = on_r15;	// L16376
    v10383.write(v10455);	// L16377
    ap_int<17> v10456 = txe_r15;	// L16378
    v10384.write(v10456);	// L16379
    ap_int<17> v10457 = txw_r15;	// L16380
    v10385.write(v10457);	// L16381
    ap_int<17> v10458 = txs_r15;	// L16382
    v10386.write(v10458);	// L16383
    ap_int<17> v10459 = txn_r15;	// L16384
    v10387.write(v10459);	// L16385
    int32_t v10460 = cre_r15;	// L16386
    v10388.write(v10460);	// L16387
    int32_t v10461 = crw_r15;	// L16388
    v10389.write(v10461);	// L16389
    int32_t v10462 = crs_r15;	// L16390
    v10390.write(v10462);	// L16391
    int32_t v10463 = crn_r15;	// L16392
    v10391.write(v10463);	// L16393
    ap_uint<26> v10464 = v10392.read();	// L16394
    ap_uint<26> p_w15;	// L16395
    p_w15 = v10464;	// L16396
    ap_uint<26> v10466 = v10393.read();	// L16397
    ap_uint<26> p_e15;	// L16398
    p_e15 = v10466;	// L16399
    ap_uint<26> v10468 = v10394.read();	// L16400
    ap_uint<26> p_n15;	// L16401
    p_n15 = v10468;	// L16402
    ap_uint<26> v10470 = v10395.read();	// L16403
    ap_uint<26> p_s15;	// L16404
    p_s15 = v10470;	// L16405
    int32_t v10472 = v10396.read();	// L16406
    int32_t v10473 = rcred15[0];	// L16407
    ap_int<33> v10474 = v10473;	// L16408
    ap_int<33> v10475 = v10472;	// L16409
    ap_int<33> v10476 = v10474 + v10475;	// L16410
    int32_t v10477 = v10476;	// L16411
    rcred15[0] = v10477;	// L16412
    int32_t v10478 = v10397.read();	// L16413
    int32_t v10479 = rcred15[1];	// L16414
    ap_int<33> v10480 = v10479;	// L16415
    ap_int<33> v10481 = v10478;	// L16416
    ap_int<33> v10482 = v10480 + v10481;	// L16417
    int32_t v10483 = v10482;	// L16418
    rcred15[1] = v10483;	// L16419
    int32_t v10484 = v10398.read();	// L16420
    int32_t v10485 = rcred15[2];	// L16421
    ap_int<33> v10486 = v10485;	// L16422
    ap_int<33> v10487 = v10484;	// L16423
    ap_int<33> v10488 = v10486 + v10487;	// L16424
    int32_t v10489 = v10488;	// L16425
    rcred15[2] = v10489;	// L16426
    int32_t v10490 = v10399.read();	// L16427
    int32_t v10491 = rcred15[3];	// L16428
    ap_int<33> v10492 = v10491;	// L16429
    ap_int<33> v10493 = v10490;	// L16430
    ap_int<33> v10494 = v10492 + v10493;	// L16431
    int32_t v10495 = v10494;	// L16432
    rcred15[3] = v10495;	// L16433
    ap_uint<26> fin15[4];	// L16434
    for (int v10497 = 0; v10497 < 4; v10497++) {	// L16435
      fin15[v10497] = 0;	// L16435
    }
    ap_int<26> v10498 = p_w15;	// L16436
    fin15[0] = v10498;	// L16437
    ap_int<26> v10499 = p_e15;	// L16438
    fin15[1] = v10499;	// L16439
    ap_int<26> v10500 = p_n15;	// L16440
    fin15[2] = v10500;	// L16441
    ap_int<26> v10501 = p_s15;	// L16442
    fin15[3] = v10501;	// L16443
    l_S_d_0_d60: for (int d60 = 0; d60 < 4; d60++) {	// L16444
      ap_uint<26> v10503 = fin15[d60];	// L16445
      bool v10504;
      ap_int<26> v10504_tmp = v10503;
      v10504 = v10504_tmp[25];	// L16446
      int32_t v10505 = v10504;	// L16447
      bool v10506 = v10505 == 1;	// L16448
      int32_t v10507 = rbcnt15[d60];	// L16449
      bool v10508 = v10507 < 2;	// L16450
      bool v10509 = v10506 & v10508;	// L16451
      if (v10509) {	// L16452
        ap_uint<26> v10510 = fin15[d60];	// L16453
        int32_t v10511 = rbcnt15[d60];	// L16454
        int v10512 = v10511;	// L16455
        rbuf15[d60][v10512] = v10510;	// L16456
        int32_t v10513 = rbcnt15[d60];	// L16457
        ap_int<33> v10514 = v10513;	// L16458
        ap_int<33> v10515 = v10514 + 1;	// L16459
        int32_t v10516 = v10515;	// L16460
        rbcnt15[d60] = v10516;	// L16461
      }
    }
    ap_uint<26> hd15[4];	// L16464
    for (int v10518 = 0; v10518 < 4; v10518++) {	// L16465
      hd15[v10518] = 0;	// L16465
    }
    int32_t hvld15[4];	// L16466
    for (int v10520 = 0; v10520 < 4; v10520++) {	// L16467
      hvld15[v10520] = 0;	// L16467
    }
    int32_t hit15[4];	// L16468
    for (int v10522 = 0; v10522 < 4; v10522++) {	// L16469
      hit15[v10522] = 0;	// L16469
    }
    int32_t axis15[4];	// L16470
    for (int v10524 = 0; v10524 < 4; v10524++) {	// L16471
      axis15[v10524] = 0;	// L16471
    }
    int32_t v10525 = col_id15;	// L16472
    axis15[0] = v10525;	// L16473
    int32_t v10526 = col_id15;	// L16474
    axis15[1] = v10526;	// L16475
    int32_t v10527 = row_id15;	// L16476
    axis15[2] = v10527;	// L16477
    int32_t v10528 = row_id15;	// L16478
    axis15[3] = v10528;	// L16479
    l_S_d_1_d61: for (int d61 = 0; d61 < 4; d61++) {	// L16480
      int32_t v10530 = rbcnt15[d61];	// L16481
      bool v10531 = v10530 > 0;	// L16482
      if (v10531) {	// L16483
        ap_uint<26> v10532 = rbuf15[d61][0];	// L16484
        hd15[d61] = v10532;	// L16485
        hvld15[d61] = 1;	// L16486
        ap_uint<26> v10533 = hd15[d61];	// L16487
        ap_int<4> v10534;
        ap_int<26> v10534_tmp = v10533;
        v10534 = v10534_tmp(24, 21);	// L16488
        int32_t v10535 = axis15[d61];	// L16489
        int32_t v10536 = v10534;	// L16490
        bool v10537 = v10536 == v10535;	// L16491
        if (v10537) {	// L16492
          hit15[d61] = 1;	// L16493
        }
      }
    }
    ap_uint<26> o_crv15;	// L16497
    o_crv15 = 0;	// L16498
    int32_t crv_in15;	// L16499
    crv_in15 = -1;	// L16500
    int32_t v10540 = hit15[3];	// L16501
    bool v10541 = v10540 == 1;	// L16502
    if (v10541) {	// L16503
      ap_uint<26> v10542 = hd15[3];	// L16504
      o_crv15 = v10542;	// L16505
      crv_in15 = 3;	// L16506
    } else {
      int32_t v10543 = hit15[2];	// L16508
      bool v10544 = v10543 == 1;	// L16509
      if (v10544) {	// L16510
        ap_uint<26> v10545 = hd15[2];	// L16511
        o_crv15 = v10545;	// L16512
        crv_in15 = 2;	// L16513
      } else {
        int32_t v10546 = hit15[1];	// L16515
        bool v10547 = v10546 == 1;	// L16516
        if (v10547) {	// L16517
          ap_uint<26> v10548 = hd15[1];	// L16518
          o_crv15 = v10548;	// L16519
          crv_in15 = 1;	// L16520
        } else {
          int32_t v10549 = hit15[0];	// L16522
          bool v10550 = v10549 == 1;	// L16523
          if (v10550) {	// L16524
            ap_uint<26> v10551 = hd15[0];	// L16525
            o_crv15 = v10551;	// L16526
            crv_in15 = 0;	// L16527
          }
        }
      }
    }
    ap_uint<26> o_out15[4];	// L16532
    for (int v10553 = 0; v10553 < 4; v10553++) {	// L16533
      o_out15[v10553] = 0;	// L16533
    }
    int32_t pop15[4];	// L16534
    for (int v10555 = 0; v10555 < 4; v10555++) {	// L16535
      pop15[v10555] = 0;	// L16535
    }
    int32_t inj_done15;	// L16536
    inj_done15 = 0;	// L16537
    int32_t idir15;	// L16538
    idir15 = -1;	// L16539
    ap_int<26> v10558 = csd_pkt15;	// L16540
    bool v10559;
    ap_int<26> v10559_tmp = v10558;
    v10559 = v10559_tmp[25];	// L16541
    int32_t v10560 = v10559;	// L16542
    bool v10561 = v10560 == 1;	// L16543
    if (v10561) {	// L16544
      int32_t v10562 = csd_dir15;	// L16545
      ap_int<33> v10563 = v10562;	// L16546
      ap_int<33> v10564 = 3 - v10563;	// L16547
      int32_t v10565 = v10564;	// L16548
      idir15 = v10565;	// L16549
    }
    l_S_o_2_o15: for (int o15 = 0; o15 < 4; o15++) {	// L16551
      int32_t v10567 = rcred15[o15];	// L16552
      bool v10568 = v10567 > 0;	// L16553
      if (v10568) {	// L16554
        int32_t v10569 = idir15;	// L16555
        ap_int<33> v10570 = v10569;	// L16556
        ap_int<33> v10571 = o15;	// L16557
        bool v10572 = v10570 == v10571;	// L16558
        if (v10572) {	// L16559
          ap_int<26> v10573 = csd_pkt15;	// L16560
          o_out15[o15] = v10573;	// L16561
          int32_t v10574 = rcred15[o15];	// L16562
          ap_int<33> v10575 = v10574;	// L16563
          ap_int<33> v10576 = v10575 - 1;	// L16564
          int32_t v10577 = v10576;	// L16565
          rcred15[o15] = v10577;	// L16566
          inj_done15 = 1;	// L16567
        } else {
          int32_t v10578 = hvld15[o15];	// L16569
          bool v10579 = v10578 == 1;	// L16570
          int32_t v10580 = hit15[o15];	// L16571
          bool v10581 = v10580 == 0;	// L16572
          bool v10582 = v10579 & v10581;	// L16573
          if (v10582) {	// L16574
            ap_uint<26> v10583 = hd15[o15];	// L16575
            o_out15[o15] = v10583;	// L16576
            int32_t v10584 = rcred15[o15];	// L16577
            ap_int<33> v10585 = v10584;	// L16578
            ap_int<33> v10586 = v10585 - 1;	// L16579
            int32_t v10587 = v10586;	// L16580
            rcred15[o15] = v10587;	// L16581
            pop15[o15] = 1;	// L16582
          }
        }
      }
    }
    int32_t v10588 = crv_in15;	// L16587
    bool v10589 = v10588 >= 0;	// L16588
    if (v10589) {	// L16589
      int32_t v10590 = crv_in15;	// L16590
      int v10591 = v10590;	// L16591
      pop15[v10591] = 1;	// L16592
    }
    int32_t ret15[4];	// L16594
    for (int v10593 = 0; v10593 < 4; v10593++) {	// L16595
      ret15[v10593] = 0;	// L16595
    }
    l_S_d_3_d62: for (int d62 = 0; d62 < 4; d62++) {	// L16596
      int32_t v10595 = pop15[d62];	// L16597
      bool v10596 = v10595 == 1;	// L16598
      if (v10596) {	// L16599
        l_S_sft_3_sft15: for (int sft15 = 0; sft15 < 1; sft15++) {	// L16600
          ap_uint<26> v10598 = rbuf15[d62][(sft15 + 1)];	// L16601
          rbuf15[d62][sft15] = v10598;	// L16602
        }
        int32_t v10599 = rbcnt15[d62];	// L16604
        ap_int<33> v10600 = v10599;	// L16605
        ap_int<33> v10601 = v10600 - 1;	// L16606
        int32_t v10602 = v10601;	// L16607
        rbcnt15[d62] = v10602;	// L16608
        ret15[d62] = 1;	// L16609
      }
    }
    int32_t v10603 = ret15[0];	// L16612
    cre_r15 = v10603;	// L16613
    int32_t v10604 = ret15[1];	// L16614
    crw_r15 = v10604;	// L16615
    int32_t v10605 = ret15[2];	// L16616
    crs_r15 = v10605;	// L16617
    int32_t v10606 = ret15[3];	// L16618
    crn_r15 = v10606;	// L16619
    ap_uint<26> v10607 = o_out15[0];	// L16620
    oe_r15 = v10607;	// L16621
    ap_uint<26> v10608 = o_out15[1];	// L16622
    ow_r15 = v10608;	// L16623
    ap_uint<26> v10609 = o_out15[2];	// L16624
    os_r15 = v10609;	// L16625
    ap_uint<26> v10610 = o_out15[3];	// L16626
    on_r15 = v10610;	// L16627
    int32_t v10611 = inj_done15;	// L16628
    bool v10612 = v10611 == 1;	// L16629
    if (v10612) {	// L16630
      csd_pkt15 = 0;	// L16631
    }
    ap_int<26> v10613 = o_crv15;	// L16633
    bool v10614;
    ap_int<26> v10614_tmp = v10613;
    v10614 = v10614_tmp[25];	// L16634
    int32_t v10615 = v10614;	// L16635
    crv_vld15 = v10615;	// L16636
    ap_int<26> v10616 = o_crv15;	// L16637
    int16_t v10617;
    ap_int<26> v10617_tmp = v10616;
    v10617 = v10617_tmp(15, 0);	// L16638
    half v10618;
    union { uint16_t from; half to;} _converter_v10617_to_v10618;
    _converter_v10617_to_v10618.from = v10617;
    v10618 = _converter_v10617_to_v10618.to;	// L16639
    crv_data15 = v10618;	// L16640
    ap_int<26> v10619 = o_crv15;	// L16641
    ap_int<4> v10620;
    ap_int<26> v10620_tmp = v10619;
    v10620 = v10620_tmp(19, 16);	// L16642
    int32_t v10621 = v10620;	// L16643
    crv_addr15 = v10621;	// L16644
    ap_int<26> v10622 = o_crv15;	// L16645
    bool v10623;
    ap_int<26> v10623_tmp = v10622;
    v10623 = v10623_tmp[20];	// L16646
    int32_t v10624 = v10623;	// L16647
    crv_mode15 = v10624;	// L16648
    ap_int<26> v10625 = o_crv15;	// L16649
    int16_t v10626;
    ap_int<26> v10626_tmp = v10625;
    v10626 = v10626_tmp(15, 0);	// L16650
    int32_t v10627 = v10626;	// L16651
    crv_raw15 = v10627;	// L16652
    ap_uint<17> v10628 = v10400.read();	// L16653
    ap_uint<17> rx_w15;	// L16654
    rx_w15 = v10628;	// L16655
    ap_uint<17> v10630 = v10401.read();	// L16656
    ap_uint<17> rx_e15;	// L16657
    rx_e15 = v10630;	// L16658
    ap_uint<17> v10632 = v10402.read();	// L16659
    ap_uint<17> rx_n15;	// L16660
    rx_n15 = v10632;	// L16661
    ap_uint<17> v10634 = v10403.read();	// L16662
    ap_uint<17> rx_s15;	// L16663
    rx_s15 = v10634;	// L16664
    half rxv15[4];	// L16665
    for (int v10637 = 0; v10637 < 4; v10637++) {	// L16666
      rxv15[v10637] = (double)0.000000;	// L16666
    }
    int32_t rxvld15[4];	// L16667
    for (int v10639 = 0; v10639 < 4; v10639++) {	// L16668
      rxvld15[v10639] = 0;	// L16668
    }
    ap_int<17> v10640 = rx_n15;	// L16669
    int16_t v10641;
    ap_int<17> v10641_tmp = v10640;
    v10641 = v10641_tmp(16, 1);	// L16670
    half v10642;
    union { uint16_t from; half to;} _converter_v10641_to_v10642;
    _converter_v10641_to_v10642.from = v10641;
    v10642 = _converter_v10641_to_v10642.to;	// L16671
    rxv15[0] = v10642;	// L16672
    ap_int<17> v10643 = rx_n15;	// L16673
    bool v10644;
    ap_int<17> v10644_tmp = v10643;
    v10644 = v10644_tmp[0];	// L16674
    int32_t v10645 = v10644;	// L16675
    rxvld15[0] = v10645;	// L16676
    ap_int<17> v10646 = rx_s15;	// L16677
    int16_t v10647;
    ap_int<17> v10647_tmp = v10646;
    v10647 = v10647_tmp(16, 1);	// L16678
    half v10648;
    union { uint16_t from; half to;} _converter_v10647_to_v10648;
    _converter_v10647_to_v10648.from = v10647;
    v10648 = _converter_v10647_to_v10648.to;	// L16679
    rxv15[1] = v10648;	// L16680
    ap_int<17> v10649 = rx_s15;	// L16681
    bool v10650;
    ap_int<17> v10650_tmp = v10649;
    v10650 = v10650_tmp[0];	// L16682
    int32_t v10651 = v10650;	// L16683
    rxvld15[1] = v10651;	// L16684
    ap_int<17> v10652 = rx_w15;	// L16685
    int16_t v10653;
    ap_int<17> v10653_tmp = v10652;
    v10653 = v10653_tmp(16, 1);	// L16686
    half v10654;
    union { uint16_t from; half to;} _converter_v10653_to_v10654;
    _converter_v10653_to_v10654.from = v10653;
    v10654 = _converter_v10653_to_v10654.to;	// L16687
    rxv15[2] = v10654;	// L16688
    ap_int<17> v10655 = rx_w15;	// L16689
    bool v10656;
    ap_int<17> v10656_tmp = v10655;
    v10656 = v10656_tmp[0];	// L16690
    int32_t v10657 = v10656;	// L16691
    rxvld15[2] = v10657;	// L16692
    ap_int<17> v10658 = rx_e15;	// L16693
    int16_t v10659;
    ap_int<17> v10659_tmp = v10658;
    v10659 = v10659_tmp(16, 1);	// L16694
    half v10660;
    union { uint16_t from; half to;} _converter_v10659_to_v10660;
    _converter_v10659_to_v10660.from = v10659;
    v10660 = _converter_v10659_to_v10660.to;	// L16695
    rxv15[3] = v10660;	// L16696
    ap_int<17> v10661 = rx_e15;	// L16697
    bool v10662;
    ap_int<17> v10662_tmp = v10661;
    v10662 = v10662_tmp[0];	// L16698
    int32_t v10663 = v10662;	// L16699
    rxvld15[3] = v10663;	// L16700
    l_S_d_5_d63: for (int d63 = 0; d63 < 4; d63++) {	// L16701
      int32_t v10665 = rxvld15[d63];	// L16702
      bool v10666 = v10665 == 1;	// L16703
      int32_t v10667 = hold_cnt15[d63];	// L16704
      bool v10668 = v10667 < 2;	// L16705
      bool v10669 = v10666 & v10668;	// L16706
      if (v10669) {	// L16707
        half v10670 = rxv15[d63];	// L16708
        int32_t v10671 = hold_cnt15[d63];	// L16709
        int v10672 = v10671;	// L16710
        hold_v15[d63][v10672] = v10670;	// L16711
        int32_t v10673 = hold_cnt15[d63];	// L16712
        ap_int<33> v10674 = v10673;	// L16713
        ap_int<33> v10675 = v10674 + 1;	// L16714
        int32_t v10676 = v10675;	// L16715
        hold_cnt15[d63] = v10676;	// L16716
      }
    }
    int32_t pc15;	// L16719
    pc15 = -1;	// L16720
    int32_t v10678 = fetch_en15;	// L16721
    bool v10679 = v10678 == 1;	// L16722
    if (v10679) {	// L16723
      int32_t v10680 = instr_cnt15;	// L16724
      pc15 = v10680;	// L16725
    }
    int32_t instr15;	// L16727
    instr15 = 0;	// L16728
    int32_t v10682 = pc15;	// L16729
    bool v10683 = v10682 >= 0;	// L16730
    if (v10683) {	// L16731
      int32_t v10684 = pc15;	// L16732
      int v10685 = v10684;	// L16733
      int32_t v10686 = irf15[v10685];	// L16734
      instr15 = v10686;	// L16735
    }
    int32_t v10687 = instr15;	// L16737
    int32_t v10688 = v10687 & 15;	// L16738
    int32_t op15;	// L16739
    op15 = v10688;	// L16740
    int32_t v10690 = instr15;	// L16741
    int32_t v10691 = v10690 >> 4;	// L16742
    int32_t v10692 = v10691 & 15;	// L16743
    int32_t dst15;	// L16744
    dst15 = v10692;	// L16745
    int32_t v10694 = instr15;	// L16746
    int32_t v10695 = v10694 >> 8;	// L16747
    int32_t v10696 = v10695 & 15;	// L16748
    int32_t s115;	// L16749
    s115 = v10696;	// L16750
    int32_t v10698 = instr15;	// L16751
    int32_t v10699 = v10698 >> 12;	// L16752
    int32_t v10700 = v10699 & 15;	// L16753
    int32_t s215;	// L16754
    s215 = v10700;	// L16755
    half a15;	// L16756
    a15 = (double)0.000000;	// L16757
    half b15;	// L16758
    b15 = (double)0.000000;	// L16759
    int32_t v10704 = s115;	// L16760
    bool v10705 = v10704 >= 12;	// L16761
    if (v10705) {	// L16762
      int32_t v10706 = s115;	// L16763
      int32_t v10707 = v10706 & 3;	// L16764
      int v10708 = v10707;	// L16765
      half v10709 = hold_v15[v10708][0];	// L16766
      a15 = v10709;	// L16767
    } else {
      int32_t v10710 = s115;	// L16769
      int v10711 = v10710;	// L16770
      half v10712 = drf15[v10711];	// L16771
      a15 = v10712;	// L16772
    }
    int32_t v10713 = s215;	// L16774
    bool v10714 = v10713 >= 12;	// L16775
    if (v10714) {	// L16776
      int32_t v10715 = s215;	// L16777
      int32_t v10716 = v10715 & 3;	// L16778
      int v10717 = v10716;	// L16779
      half v10718 = hold_v15[v10717][0];	// L16780
      b15 = v10718;	// L16781
    } else {
      int32_t v10719 = s215;	// L16783
      int v10720 = v10719;	// L16784
      half v10721 = drf15[v10720];	// L16785
      b15 = v10721;	// L16786
    }
    int32_t a_vld15;	// L16788
    a_vld15 = 1;	// L16789
    int32_t b_vld15;	// L16790
    b_vld15 = 1;	// L16791
    int32_t v10724 = s115;	// L16792
    bool v10725 = v10724 >= 12;	// L16793
    if (v10725) {	// L16794
      a_vld15 = 0;	// L16795
      int32_t v10726 = s115;	// L16796
      int32_t v10727 = v10726 & 3;	// L16797
      int v10728 = v10727;	// L16798
      int32_t v10729 = hold_cnt15[v10728];	// L16799
      bool v10730 = v10729 > 0;	// L16800
      if (v10730) {	// L16801
        a_vld15 = 1;	// L16802
      }
    }
    int32_t v10731 = s215;	// L16805
    bool v10732 = v10731 >= 12;	// L16806
    if (v10732) {	// L16807
      b_vld15 = 0;	// L16808
      int32_t v10733 = s215;	// L16809
      int32_t v10734 = v10733 & 3;	// L16810
      int v10735 = v10734;	// L16811
      int32_t v10736 = hold_cnt15[v10735];	// L16812
      bool v10737 = v10736 > 0;	// L16813
      if (v10737) {	// L16814
        b_vld15 = 1;	// L16815
      }
    }
    int32_t v10738 = s115;	// L16818
    bool v10739 = v10738 < 8;	// L16819
    int32_t v10740 = dsmask15;	// L16820
    int32_t v10741 = v10740 >> v10738;	// L16821
    int32_t v10742 = v10741 & 1;	// L16822
    bool v10743 = v10742 == 1;	// L16823
    bool v10744 = v10739 & v10743;	// L16824
    if (v10744) {	// L16825
      int32_t v10745 = s115;	// L16826
      int v10746 = v10745;	// L16827
      int32_t v10747 = drf_full15[v10746];	// L16828
      bool v10748 = v10747 == 0;	// L16829
      if (v10748) {	// L16830
        a_vld15 = 0;	// L16831
      }
    }
    int32_t v10749 = s215;	// L16834
    bool v10750 = v10749 < 8;	// L16835
    int32_t v10751 = dsmask15;	// L16836
    int32_t v10752 = v10751 >> v10749;	// L16837
    int32_t v10753 = v10752 & 1;	// L16838
    bool v10754 = v10753 == 1;	// L16839
    bool v10755 = v10750 & v10754;	// L16840
    if (v10755) {	// L16841
      int32_t v10756 = s215;	// L16842
      int v10757 = v10756;	// L16843
      int32_t v10758 = drf_full15[v10757];	// L16844
      bool v10759 = v10758 == 0;	// L16845
      if (v10759) {	// L16846
        b_vld15 = 0;	// L16847
      }
    }
    int32_t binop15;	// L16850
    binop15 = 0;	// L16851
    int32_t v10761 = op15;	// L16852
    bool v10762 = v10761 == 0;	// L16853
    bool v10763 = v10761 == 1;	// L16854
    bool v10764 = v10761 == 2;	// L16855
    bool v10765 = v10761 == 8;	// L16856
    bool v10766 = v10761 == 9;	// L16857
    bool v10767 = v10762 | v10763;	// L16858
    bool v10768 = v10767 | v10764;	// L16859
    bool v10769 = v10768 | v10765;	// L16860
    bool v10770 = v10769 | v10766;	// L16861
    if (v10770) {	// L16862
      binop15 = 1;	// L16863
    }
    int32_t grant15;	// L16865
    grant15 = 0;	// L16866
    int32_t v10772 = pc15;	// L16867
    bool v10773 = v10772 >= 0;	// L16868
    if (v10773) {	// L16869
      grant15 = 1;	// L16870
    }
    int32_t v10774 = pc15;	// L16872
    bool v10775 = v10774 >= 0;	// L16873
    int32_t v10776 = a_vld15;	// L16874
    bool v10777 = v10776 == 0;	// L16875
    int32_t v10778 = binop15;	// L16876
    bool v10779 = v10778 == 1;	// L16877
    int32_t v10780 = b_vld15;	// L16878
    bool v10781 = v10780 == 0;	// L16879
    bool v10782 = v10779 & v10781;	// L16880
    bool v10783 = v10777 | v10782;	// L16881
    bool v10784 = v10775 & v10783;	// L16882
    if (v10784) {	// L16883
      grant15 = 0;	// L16884
    }
    int32_t v10785 = grant15;	// L16886
    bool v10786 = v10785 == 1;	// L16887
    if (v10786) {	// L16888
      int32_t v10787 = instr_cnt15;	// L16889
      int32_t v10788 = cfg_isz15;	// L16890
      bool v10789 = v10787 == v10788;	// L16891
      if (v10789) {	// L16892
        instr_cnt15 = 0;	// L16893
        int32_t v10790 = iter_cnt15;	// L16894
        int32_t v10791 = cfg_itsz15;	// L16895
        ap_int<33> v10792 = v10791;	// L16896
        ap_int<33> v10793 = v10792 - 1;	// L16897
        ap_int<33> v10794 = v10790;	// L16898
        bool v10795 = v10794 == v10793;	// L16899
        if (v10795) {	// L16900
          fetch_en15 = 0;	// L16901
        } else {
          int32_t v10796 = iter_cnt15;	// L16903
          ap_int<33> v10797 = v10796;	// L16904
          ap_int<33> v10798 = v10797 + 1;	// L16905
          int32_t v10799 = v10798;	// L16906
          iter_cnt15 = v10799;	// L16907
        }
      } else {
        int32_t v10800 = instr_cnt15;	// L16910
        ap_int<33> v10801 = v10800;	// L16911
        ap_int<33> v10802 = v10801 + 1;	// L16912
        int32_t v10803 = v10802;	// L16913
        instr_cnt15 = v10803;	// L16914
      }
    }
    int32_t c115;	// L16917
    c115 = -1;	// L16918
    int32_t c215;	// L16919
    c215 = -1;	// L16920
    int32_t v10806 = grant15;	// L16921
    bool v10807 = v10806 == 1;	// L16922
    int32_t v10808 = s115;	// L16923
    bool v10809 = v10808 >= 12;	// L16924
    bool v10810 = v10807 & v10809;	// L16925
    if (v10810) {	// L16926
      int32_t v10811 = s115;	// L16927
      int32_t v10812 = v10811 & 3;	// L16928
      c115 = v10812;	// L16929
    }
    int32_t v10813 = grant15;	// L16931
    bool v10814 = v10813 == 1;	// L16932
    int32_t v10815 = s215;	// L16933
    bool v10816 = v10815 >= 12;	// L16934
    bool v10817 = v10814 & v10816;	// L16935
    if (v10817) {	// L16936
      int32_t v10818 = s215;	// L16937
      int32_t v10819 = v10818 & 3;	// L16938
      c215 = v10819;	// L16939
    }
    int32_t v10820 = c115;	// L16941
    bool v10821 = v10820 >= 0;	// L16942
    if (v10821) {	// L16943
      int32_t v10822 = c115;	// L16944
      int v10823 = v10822;	// L16945
      half v10824 = hold_v15[v10823][1];	// L16946
      hold_v15[v10823][0] = v10824;	// L16947
      int32_t v10825 = c115;	// L16948
      int v10826 = v10825;	// L16949
      int32_t v10827 = hold_cnt15[v10826];	// L16950
      ap_int<33> v10828 = v10827;	// L16951
      ap_int<33> v10829 = v10828 - 1;	// L16952
      int32_t v10830 = v10829;	// L16953
      hold_cnt15[v10826] = v10830;	// L16954
    }
    int32_t v10831 = c215;	// L16956
    bool v10832 = v10831 >= 0;	// L16957
    int32_t v10833 = c115;	// L16958
    bool v10834 = v10831 != v10833;	// L16959
    bool v10835 = v10832 & v10834;	// L16960
    if (v10835) {	// L16961
      int32_t v10836 = c215;	// L16962
      int v10837 = v10836;	// L16963
      half v10838 = hold_v15[v10837][1];	// L16964
      hold_v15[v10837][0] = v10838;	// L16965
      int32_t v10839 = c215;	// L16966
      int v10840 = v10839;	// L16967
      int32_t v10841 = hold_cnt15[v10840];	// L16968
      ap_int<33> v10842 = v10841;	// L16969
      ap_int<33> v10843 = v10842 - 1;	// L16970
      int32_t v10844 = v10843;	// L16971
      hold_cnt15[v10840] = v10844;	// L16972
    }
    int32_t v10845 = grant15;	// L16974
    bool v10846 = v10845 == 1;	// L16975
    int32_t v10847 = s115;	// L16976
    bool v10848 = v10847 < 8;	// L16977
    int32_t v10849 = dsmask15;	// L16978
    int32_t v10850 = v10849 >> v10847;	// L16979
    int32_t v10851 = v10850 & 1;	// L16980
    bool v10852 = v10851 == 1;	// L16981
    bool v10853 = v10846 & v10848;	// L16982
    bool v10854 = v10853 & v10852;	// L16983
    if (v10854) {	// L16984
      int32_t v10855 = s115;	// L16985
      int v10856 = v10855;	// L16986
      drf_full15[v10856] = 0;	// L16987
    }
    int32_t v10857 = grant15;	// L16989
    bool v10858 = v10857 == 1;	// L16990
    int32_t v10859 = s215;	// L16991
    bool v10860 = v10859 < 8;	// L16992
    int32_t v10861 = dsmask15;	// L16993
    int32_t v10862 = v10861 >> v10859;	// L16994
    int32_t v10863 = v10862 & 1;	// L16995
    bool v10864 = v10863 == 1;	// L16996
    bool v10865 = v10858 & v10860;	// L16997
    bool v10866 = v10865 & v10864;	// L16998
    if (v10866) {	// L16999
      int32_t v10867 = s215;	// L17000
      int v10868 = v10867;	// L17001
      drf_full15[v10868] = 0;	// L17002
    }
    half res15;	// L17004
    res15 = (double)0.000000;	// L17005
    int32_t v10870 = op15;	// L17006
    bool v10871 = v10870 == 0;	// L17007
    if (v10871) {	// L17008
      half v10872 = a15;	// L17009
      half v10873 = b15;	// L17010
      half v10874 = v10872 + v10873;	// L17011
      res15 = v10874;	// L17012
    } else {
      int32_t v10875 = op15;	// L17014
      bool v10876 = v10875 == 1;	// L17015
      if (v10876) {	// L17016
        half v10877 = a15;	// L17017
        half v10878 = b15;	// L17018
        half v10879 = v10877 - v10878;	// L17019
        res15 = v10879;	// L17020
      } else {
        int32_t v10880 = op15;	// L17022
        bool v10881 = v10880 == 2;	// L17023
        if (v10881) {	// L17024
          half v10882 = a15;	// L17025
          half v10883 = b15;	// L17026
          half v10884 = v10882 * v10883;	// L17027
          res15 = v10884;	// L17028
        } else {
          int32_t v10885 = op15;	// L17030
          bool v10886 = v10885 == 8;	// L17031
          if (v10886) {	// L17032
            half v10887 = a15;	// L17033
            half v10888 = b15;	// L17034
            bool v10889 = v10887 >= v10888;	// L17035
            if (v10889) {	// L17036
              res15 = (double)1.000000;	// L17037
            } else {
              res15 = (double)-1.000000;	// L17039
            }
          } else {
            int32_t v10890 = op15;	// L17042
            bool v10891 = v10890 == 9;	// L17043
            if (v10891) {	// L17044
              half v10892 = a15;	// L17045
              half v10893 = b15;	// L17046
              bool v10894 = v10892 < v10893;	// L17047
              if (v10894) {	// L17048
                res15 = (double)1.000000;	// L17049
              } else {
                res15 = (double)-1.000000;	// L17051
              }
            } else {
              half v10895 = a15;	// L17054
              res15 = v10895;	// L17055
            }
          }
        }
      }
    }
    int32_t v10896 = a_vld15;	// L17061
    int32_t res_vld15;	// L17062
    res_vld15 = v10896;	// L17063
    int32_t v10898 = op15;	// L17064
    bool v10899 = v10898 == 0;	// L17065
    bool v10900 = v10898 == 1;	// L17066
    bool v10901 = v10898 == 2;	// L17067
    bool v10902 = v10898 == 8;	// L17068
    bool v10903 = v10898 == 9;	// L17069
    bool v10904 = v10899 | v10900;	// L17070
    bool v10905 = v10904 | v10901;	// L17071
    bool v10906 = v10905 | v10902;	// L17072
    bool v10907 = v10906 | v10903;	// L17073
    if (v10907) {	// L17074
      int32_t v10908 = a_vld15;	// L17075
      int32_t v10909 = b_vld15;	// L17076
      int64_t v10910 = v10908;	// L17077
      int64_t v10911 = v10909;	// L17078
      int64_t v10912 = v10910 * v10911;	// L17079
      int32_t v10913 = v10912;	// L17080
      res_vld15 = v10913;	// L17081
    }
    int32_t v10914 = grant15;	// L17083
    bool v10915 = v10914 == 0;	// L17084
    if (v10915) {	// L17085
      res_vld15 = 0;	// L17086
    }
    int32_t v10916 = grant15;	// L17088
    bool v10917 = v10916 == 1;	// L17089
    int32_t v10918 = op15;	// L17090
    bool v10919 = v10918 == 8;	// L17091
    bool v10920 = v10917 & v10919;	// L17092
    if (v10920) {	// L17093
      condition_reg15 = 0;	// L17094
      half v10921 = a15;	// L17095
      half v10922 = b15;	// L17096
      bool v10923 = v10921 >= v10922;	// L17097
      if (v10923) {	// L17098
        condition_reg15 = 1;	// L17099
      }
    }
    int32_t v10924 = grant15;	// L17102
    bool v10925 = v10924 == 1;	// L17103
    int32_t v10926 = op15;	// L17104
    bool v10927 = v10926 == 9;	// L17105
    bool v10928 = v10925 & v10927;	// L17106
    if (v10928) {	// L17107
      condition_reg15 = 0;	// L17108
      half v10929 = a15;	// L17109
      half v10930 = b15;	// L17110
      bool v10931 = v10929 < v10930;	// L17111
      if (v10931) {	// L17112
        condition_reg15 = 1;	// L17113
      }
    }
    ap_uint<17> tx_n15;	// L17116
    tx_n15 = 0;	// L17117
    ap_uint<17> tx_s15;	// L17118
    tx_s15 = 0;	// L17119
    ap_uint<17> tx_w15;	// L17120
    tx_w15 = 0;	// L17121
    ap_uint<17> tx_e15;	// L17122
    tx_e15 = 0;	// L17123
    int32_t is_rtr15;	// L17124
    is_rtr15 = 0;	// L17125
    int32_t do_inj15;	// L17126
    do_inj15 = 0;	// L17127
    int32_t v10938 = op15;	// L17128
    bool v10939 = v10938 >= 4;	// L17129
    ap_int<33> v10940 = v10938;	// L17130
    bool v10941 = v10940 <= 7;	// L17131
    bool v10942 = v10939 & v10941;	// L17132
    if (v10942) {	// L17133
      is_rtr15 = 1;	// L17134
      do_inj15 = 1;	// L17135
    }
    int32_t v10943 = op15;	// L17137
    bool v10944 = v10943 >= 12;	// L17138
    ap_int<33> v10945 = v10943;	// L17139
    bool v10946 = v10945 <= 15;	// L17140
    bool v10947 = v10944 & v10946;	// L17141
    if (v10947) {	// L17142
      is_rtr15 = 1;	// L17143
      int32_t v10948 = condition_reg15;	// L17144
      bool v10949 = v10948 == 1;	// L17145
      if (v10949) {	// L17146
        do_inj15 = 1;	// L17147
      }
    }
    int32_t v10950 = is_rtr15;	// L17150
    bool v10951 = v10950 == 1;	// L17151
    if (v10951) {	// L17152
      int32_t v10952 = do_inj15;	// L17153
      bool v10953 = v10952 == 1;	// L17154
      ap_int<26> v10954 = csd_pkt15;	// L17155
      bool v10955;
      ap_int<26> v10955_tmp = v10954;
      v10955 = v10955_tmp[25];	// L17156
      int32_t v10956 = v10955;	// L17157
      bool v10957 = v10956 == 0;	// L17158
      bool v10958 = v10953 & v10957;	// L17159
      if (v10958) {	// L17160
        half v10959 = res15;	// L17161
        uint16_t v10960;
        union { half from; uint16_t to;} _converter_v10959_to_v10960;
        _converter_v10959_to_v10960.from = v10959;
        v10960 = _converter_v10959_to_v10960.to;	// L17162
        ap_int<26> v10961 = csd_pkt15;	// L17163
        ap_int<26> v10962;
        ap_int<26> v10962_tmp = v10961;
        v10962_tmp(15, 0) = v10960;
        v10962 = v10962_tmp;	// L17164
        csd_pkt15 = v10962;	// L17165
        int32_t v10963 = dst15;	// L17166
        ap_uint<4> v10964 = v10963;	// L17167
        ap_int<26> v10965 = csd_pkt15;	// L17168
        ap_int<26> v10966;
        ap_int<26> v10966_tmp = v10965;
        v10966_tmp(19, 16) = v10964;
        v10966 = v10966_tmp;	// L17169
        csd_pkt15 = v10966;	// L17170
        int32_t v10967 = s215;	// L17171
        ap_uint<4> v10968 = v10967;	// L17172
        ap_int<26> v10969 = csd_pkt15;	// L17173
        ap_int<26> v10970;
        ap_int<26> v10970_tmp = v10969;
        v10970_tmp(24, 21) = v10968;
        v10970 = v10970_tmp;	// L17174
        csd_pkt15 = v10970;	// L17175
        int32_t v10971 = res_vld15;	// L17176
        bool v10972 = v10971;	// L17177
        ap_int<26> v10973 = csd_pkt15;	// L17178
        ap_int<26> v10974;
        ap_int<26> v10974_tmp = v10973;
        v10974_tmp[25] = v10972;        v10974 = v10974_tmp;	// L17179
        csd_pkt15 = v10974;	// L17180
        int32_t v10975 = op15;	// L17181
        int32_t v10976 = v10975 & 3;	// L17182
        csd_dir15 = v10976;	// L17183
      }
    } else {
      int32_t v10977 = dst15;	// L17186
      bool v10978 = v10977 >= 12;	// L17187
      if (v10978) {	// L17188
        ap_uint<17> tw15;	// L17189
        tw15 = 0;	// L17190
        int32_t v10980 = res_vld15;	// L17191
        bool v10981 = v10980;	// L17192
        ap_int<17> v10982 = tw15;	// L17193
        ap_int<17> v10983;
        ap_int<17> v10983_tmp = v10982;
        v10983_tmp[0] = v10981;        v10983 = v10983_tmp;	// L17194
        tw15 = v10983;	// L17195
        half v10984 = res15;	// L17196
        uint16_t v10985;
        union { half from; uint16_t to;} _converter_v10984_to_v10985;
        _converter_v10984_to_v10985.from = v10984;
        v10985 = _converter_v10984_to_v10985.to;	// L17197
        ap_int<17> v10986 = tw15;	// L17198
        ap_int<17> v10987;
        ap_int<17> v10987_tmp = v10986;
        v10987_tmp(16, 1) = v10985;
        v10987 = v10987_tmp;	// L17199
        tw15 = v10987;	// L17200
        int32_t v10988 = dst15;	// L17201
        int32_t v10989 = v10988 & 3;	// L17202
        bool v10990 = v10989 == 0;	// L17203
        if (v10990) {	// L17204
          ap_int<17> v10991 = tw15;	// L17205
          tx_n15 = v10991;	// L17206
        } else {
          int32_t v10992 = dst15;	// L17208
          int32_t v10993 = v10992 & 3;	// L17209
          bool v10994 = v10993 == 1;	// L17210
          if (v10994) {	// L17211
            ap_int<17> v10995 = tw15;	// L17212
            tx_s15 = v10995;	// L17213
          } else {
            int32_t v10996 = dst15;	// L17215
            int32_t v10997 = v10996 & 3;	// L17216
            bool v10998 = v10997 == 2;	// L17217
            if (v10998) {	// L17218
              ap_int<17> v10999 = tw15;	// L17219
              tx_w15 = v10999;	// L17220
            } else {
              ap_int<17> v11000 = tw15;	// L17222
              tx_e15 = v11000;	// L17223
            }
          }
        }
      } else {
        int32_t v11001 = res_vld15;	// L17228
        bool v11002 = v11001 == 1;	// L17229
        if (v11002) {	// L17230
          int32_t v11003 = dst15;	// L17231
          bool v11004 = v11003 < 8;	// L17232
          int32_t v11005 = dsmask15;	// L17233
          int32_t v11006 = v11005 >> v11003;	// L17234
          int32_t v11007 = v11006 & 1;	// L17235
          bool v11008 = v11007 == 1;	// L17236
          bool v11009 = v11004 & v11008;	// L17237
          if (v11009) {	// L17238
            int32_t v11010 = dst15;	// L17239
            int v11011 = v11010;	// L17240
            int32_t v11012 = drf_full15[v11011];	// L17241
            bool v11013 = v11012 == 0;	// L17242
            if (v11013) {	// L17243
              half v11014 = res15;	// L17244
              int32_t v11015 = dst15;	// L17245
              int v11016 = v11015;	// L17246
              drf15[v11016] = v11014;	// L17247
              int32_t v11017 = dst15;	// L17248
              int v11018 = v11017;	// L17249
              drf_full15[v11018] = 1;	// L17250
            }
          } else {
            half v11019 = res15;	// L17253
            int32_t v11020 = dst15;	// L17254
            int v11021 = v11020;	// L17255
            drf15[v11021] = v11019;	// L17256
          }
        }
      }
    }
    ap_int<17> v11022 = tx_n15;	// L17261
    txn_r15 = v11022;	// L17262
    ap_int<17> v11023 = tx_s15;	// L17263
    txs_r15 = v11023;	// L17264
    ap_int<17> v11024 = tx_w15;	// L17265
    txw_r15 = v11024;	// L17266
    ap_int<17> v11025 = tx_e15;	// L17267
    txe_r15 = v11025;	// L17268
    int32_t v11026 = crv_vld15;	// L17269
    bool v11027 = v11026 == 1;	// L17270
    if (v11027) {	// L17271
      int32_t v11028 = crv_mode15;	// L17272
      bool v11029 = v11028 == 1;	// L17273
      if (v11029) {	// L17274
        int32_t v11030 = crv_addr15;	// L17275
        int32_t v11031 = v11030 >> 3;	// L17276
        int32_t v11032 = v11031 & 1;	// L17277
        bool v11033 = v11032 == 1;	// L17278
        if (v11033) {	// L17279
          int32_t v11034 = crv_raw15;	// L17280
          int32_t v11035 = crv_addr15;	// L17281
          int32_t v11036 = v11035 & 7;	// L17282
          int v11037 = v11036;	// L17283
          irf15[v11037] = v11034;	// L17284
        } else {
          int32_t v11038 = crv_addr15;	// L17286
          bool v11039 = v11038 == 0;	// L17287
          if (v11039) {	// L17288
            int32_t v11040 = crv_raw15;	// L17289
            int32_t v11041 = v11040 & 255;	// L17290
            dsmask15 = v11041;	// L17291
            int32_t v11042 = crv_raw15;	// L17292
            int32_t v11043 = v11042 >> 8;	// L17293
            int32_t v11044 = v11043 & 7;	// L17294
            cfg_isz15 = v11044;	// L17295
            int32_t v11045 = crv_raw15;	// L17296
            int32_t v11046 = v11045 >> 15;	// L17297
            int32_t v11047 = v11046 & 1;	// L17298
            bool v11048 = v11047 == 1;	// L17299
            if (v11048) {	// L17300
              fetch_en15 = 1;	// L17301
              instr_cnt15 = 0;	// L17302
              iter_cnt15 = 0;	// L17303
            }
          } else {
            int32_t v11049 = crv_addr15;	// L17306
            bool v11050 = v11049 == 1;	// L17307
            if (v11050) {	// L17308
              int32_t v11051 = crv_raw15;	// L17309
              int32_t v11052 = v11051 & 255;	// L17310
              cfg_itsz15 = v11052;	// L17311
            }
          }
        }
      } else {
        int32_t v11053 = crv_addr15;	// L17316
        bool v11054 = v11053 < 8;	// L17317
        int32_t v11055 = dsmask15;	// L17318
        int32_t v11056 = v11055 >> v11053;	// L17319
        int32_t v11057 = v11056 & 1;	// L17320
        bool v11058 = v11057 == 1;	// L17321
        bool v11059 = v11054 & v11058;	// L17322
        if (v11059) {	// L17323
          int32_t v11060 = crv_addr15;	// L17324
          int v11061 = v11060;	// L17325
          int32_t v11062 = drf_full15[v11061];	// L17326
          bool v11063 = v11062 == 0;	// L17327
          if (v11063) {	// L17328
            half v11064 = crv_data15;	// L17329
            int32_t v11065 = crv_addr15;	// L17330
            int v11066 = v11065;	// L17331
            drf15[v11066] = v11064;	// L17332
            int32_t v11067 = crv_addr15;	// L17333
            int v11068 = v11067;	// L17334
            drf_full15[v11068] = 1;	// L17335
          }
        } else {
          half v11069 = crv_data15;	// L17338
          int32_t v11070 = crv_addr15;	// L17339
          int v11071 = v11070;	// L17340
          drf15[v11071] = v11069;	// L17341
        }
      }
    }
  }
}

void drv_w_0(
  half v11072[4][8],
  int32_t v11073[4][8],
  hls::stream< ap_uint<17> >& v11074,
  hls::stream< ap_uint<17> >& v11075,
  hls::stream< ap_uint<17> >& v11076,
  hls::stream< ap_uint<17> >& v11077
) {	// L17348
  l_S_t_0_t16: for (int t16 = 0; t16 < 8; t16++) {	// L17354
    ap_uint<17> w;	// L17355
    w = 0;	// L17356
    ap_int<33> v11080 = t16;	// L17357
    bool v11081 = v11080 < 8;	// L17358
    if (v11081) {	// L17359
      int32_t v11082 = v11073[0][t16];	// L17360
      bool v11083 = v11082;	// L17361
      ap_int<17> v11084 = w;	// L17362
      ap_int<17> v11085;
      ap_int<17> v11085_tmp = v11084;
      v11085_tmp[0] = v11083;      v11085 = v11085_tmp;	// L17363
      w = v11085;	// L17364
      half v11086 = v11072[0][t16];	// L17365
      uint16_t v11087;
      union { half from; uint16_t to;} _converter_v11086_to_v11087;
      _converter_v11086_to_v11087.from = v11086;
      v11087 = _converter_v11086_to_v11087.to;	// L17366
      ap_int<17> v11088 = w;	// L17367
      ap_int<17> v11089;
      ap_int<17> v11089_tmp = v11088;
      v11089_tmp(16, 1) = v11087;
      v11089 = v11089_tmp;	// L17368
      w = v11089;	// L17369
    }
    ap_int<17> v11090 = w;	// L17371
    v11074.write(v11090);	// L17372
    ap_uint<17> w1;	// L17373
    w1 = 0;	// L17374
    if (v11081) {	// L17375
      int32_t v11092 = v11073[1][t16];	// L17376
      bool v11093 = v11092;	// L17377
      ap_int<17> v11094 = w1;	// L17378
      ap_int<17> v11095;
      ap_int<17> v11095_tmp = v11094;
      v11095_tmp[0] = v11093;      v11095 = v11095_tmp;	// L17379
      w1 = v11095;	// L17380
      half v11096 = v11072[1][t16];	// L17381
      uint16_t v11097;
      union { half from; uint16_t to;} _converter_v11096_to_v11097;
      _converter_v11096_to_v11097.from = v11096;
      v11097 = _converter_v11096_to_v11097.to;	// L17382
      ap_int<17> v11098 = w1;	// L17383
      ap_int<17> v11099;
      ap_int<17> v11099_tmp = v11098;
      v11099_tmp(16, 1) = v11097;
      v11099 = v11099_tmp;	// L17384
      w1 = v11099;	// L17385
    }
    ap_int<17> v11100 = w1;	// L17387
    v11075.write(v11100);	// L17388
    ap_uint<17> w2;	// L17389
    w2 = 0;	// L17390
    if (v11081) {	// L17391
      int32_t v11102 = v11073[2][t16];	// L17392
      bool v11103 = v11102;	// L17393
      ap_int<17> v11104 = w2;	// L17394
      ap_int<17> v11105;
      ap_int<17> v11105_tmp = v11104;
      v11105_tmp[0] = v11103;      v11105 = v11105_tmp;	// L17395
      w2 = v11105;	// L17396
      half v11106 = v11072[2][t16];	// L17397
      uint16_t v11107;
      union { half from; uint16_t to;} _converter_v11106_to_v11107;
      _converter_v11106_to_v11107.from = v11106;
      v11107 = _converter_v11106_to_v11107.to;	// L17398
      ap_int<17> v11108 = w2;	// L17399
      ap_int<17> v11109;
      ap_int<17> v11109_tmp = v11108;
      v11109_tmp(16, 1) = v11107;
      v11109 = v11109_tmp;	// L17400
      w2 = v11109;	// L17401
    }
    ap_int<17> v11110 = w2;	// L17403
    v11076.write(v11110);	// L17404
    ap_uint<17> w3;	// L17405
    w3 = 0;	// L17406
    if (v11081) {	// L17407
      int32_t v11112 = v11073[3][t16];	// L17408
      bool v11113 = v11112;	// L17409
      ap_int<17> v11114 = w3;	// L17410
      ap_int<17> v11115;
      ap_int<17> v11115_tmp = v11114;
      v11115_tmp[0] = v11113;      v11115 = v11115_tmp;	// L17411
      w3 = v11115;	// L17412
      half v11116 = v11072[3][t16];	// L17413
      uint16_t v11117;
      union { half from; uint16_t to;} _converter_v11116_to_v11117;
      _converter_v11116_to_v11117.from = v11116;
      v11117 = _converter_v11116_to_v11117.to;	// L17414
      ap_int<17> v11118 = w3;	// L17415
      ap_int<17> v11119;
      ap_int<17> v11119_tmp = v11118;
      v11119_tmp(16, 1) = v11117;
      v11119 = v11119_tmp;	// L17416
      w3 = v11119;	// L17417
    }
    ap_int<17> v11120 = w3;	// L17419
    v11077.write(v11120);	// L17420
  }
}

void drv_e_0(
  half v11121[4][8],
  int32_t v11122[4][8],
  hls::stream< ap_uint<17> >& v11123,
  hls::stream< ap_uint<17> >& v11124,
  hls::stream< ap_uint<17> >& v11125,
  hls::stream< ap_uint<17> >& v11126
) {	// L17424
  l_S_t_0_t17: for (int t17 = 0; t17 < 8; t17++) {	// L17430
    ap_uint<17> w4;	// L17431
    w4 = 0;	// L17432
    ap_int<33> v11129 = t17;	// L17433
    bool v11130 = v11129 < 8;	// L17434
    if (v11130) {	// L17435
      int32_t v11131 = v11122[0][t17];	// L17436
      bool v11132 = v11131;	// L17437
      ap_int<17> v11133 = w4;	// L17438
      ap_int<17> v11134;
      ap_int<17> v11134_tmp = v11133;
      v11134_tmp[0] = v11132;      v11134 = v11134_tmp;	// L17439
      w4 = v11134;	// L17440
      half v11135 = v11121[0][t17];	// L17441
      uint16_t v11136;
      union { half from; uint16_t to;} _converter_v11135_to_v11136;
      _converter_v11135_to_v11136.from = v11135;
      v11136 = _converter_v11135_to_v11136.to;	// L17442
      ap_int<17> v11137 = w4;	// L17443
      ap_int<17> v11138;
      ap_int<17> v11138_tmp = v11137;
      v11138_tmp(16, 1) = v11136;
      v11138 = v11138_tmp;	// L17444
      w4 = v11138;	// L17445
    }
    ap_int<17> v11139 = w4;	// L17447
    v11123.write(v11139);	// L17448
    ap_uint<17> w5;	// L17449
    w5 = 0;	// L17450
    if (v11130) {	// L17451
      int32_t v11141 = v11122[1][t17];	// L17452
      bool v11142 = v11141;	// L17453
      ap_int<17> v11143 = w5;	// L17454
      ap_int<17> v11144;
      ap_int<17> v11144_tmp = v11143;
      v11144_tmp[0] = v11142;      v11144 = v11144_tmp;	// L17455
      w5 = v11144;	// L17456
      half v11145 = v11121[1][t17];	// L17457
      uint16_t v11146;
      union { half from; uint16_t to;} _converter_v11145_to_v11146;
      _converter_v11145_to_v11146.from = v11145;
      v11146 = _converter_v11145_to_v11146.to;	// L17458
      ap_int<17> v11147 = w5;	// L17459
      ap_int<17> v11148;
      ap_int<17> v11148_tmp = v11147;
      v11148_tmp(16, 1) = v11146;
      v11148 = v11148_tmp;	// L17460
      w5 = v11148;	// L17461
    }
    ap_int<17> v11149 = w5;	// L17463
    v11124.write(v11149);	// L17464
    ap_uint<17> w6;	// L17465
    w6 = 0;	// L17466
    if (v11130) {	// L17467
      int32_t v11151 = v11122[2][t17];	// L17468
      bool v11152 = v11151;	// L17469
      ap_int<17> v11153 = w6;	// L17470
      ap_int<17> v11154;
      ap_int<17> v11154_tmp = v11153;
      v11154_tmp[0] = v11152;      v11154 = v11154_tmp;	// L17471
      w6 = v11154;	// L17472
      half v11155 = v11121[2][t17];	// L17473
      uint16_t v11156;
      union { half from; uint16_t to;} _converter_v11155_to_v11156;
      _converter_v11155_to_v11156.from = v11155;
      v11156 = _converter_v11155_to_v11156.to;	// L17474
      ap_int<17> v11157 = w6;	// L17475
      ap_int<17> v11158;
      ap_int<17> v11158_tmp = v11157;
      v11158_tmp(16, 1) = v11156;
      v11158 = v11158_tmp;	// L17476
      w6 = v11158;	// L17477
    }
    ap_int<17> v11159 = w6;	// L17479
    v11125.write(v11159);	// L17480
    ap_uint<17> w7;	// L17481
    w7 = 0;	// L17482
    if (v11130) {	// L17483
      int32_t v11161 = v11122[3][t17];	// L17484
      bool v11162 = v11161;	// L17485
      ap_int<17> v11163 = w7;	// L17486
      ap_int<17> v11164;
      ap_int<17> v11164_tmp = v11163;
      v11164_tmp[0] = v11162;      v11164 = v11164_tmp;	// L17487
      w7 = v11164;	// L17488
      half v11165 = v11121[3][t17];	// L17489
      uint16_t v11166;
      union { half from; uint16_t to;} _converter_v11165_to_v11166;
      _converter_v11165_to_v11166.from = v11165;
      v11166 = _converter_v11165_to_v11166.to;	// L17490
      ap_int<17> v11167 = w7;	// L17491
      ap_int<17> v11168;
      ap_int<17> v11168_tmp = v11167;
      v11168_tmp(16, 1) = v11166;
      v11168 = v11168_tmp;	// L17492
      w7 = v11168;	// L17493
    }
    ap_int<17> v11169 = w7;	// L17495
    v11126.write(v11169);	// L17496
  }
}

void drv_n_0(
  half v11170[4][8],
  int32_t v11171[4][8],
  hls::stream< ap_uint<17> >& v11172,
  hls::stream< ap_uint<17> >& v11173,
  hls::stream< ap_uint<17> >& v11174,
  hls::stream< ap_uint<17> >& v11175
) {	// L17500
  l_S_t_0_t18: for (int t18 = 0; t18 < 8; t18++) {	// L17506
    ap_uint<17> w8;	// L17507
    w8 = 0;	// L17508
    ap_int<33> v11178 = t18;	// L17509
    bool v11179 = v11178 < 8;	// L17510
    if (v11179) {	// L17511
      int32_t v11180 = v11171[0][t18];	// L17512
      bool v11181 = v11180;	// L17513
      ap_int<17> v11182 = w8;	// L17514
      ap_int<17> v11183;
      ap_int<17> v11183_tmp = v11182;
      v11183_tmp[0] = v11181;      v11183 = v11183_tmp;	// L17515
      w8 = v11183;	// L17516
      half v11184 = v11170[0][t18];	// L17517
      uint16_t v11185;
      union { half from; uint16_t to;} _converter_v11184_to_v11185;
      _converter_v11184_to_v11185.from = v11184;
      v11185 = _converter_v11184_to_v11185.to;	// L17518
      ap_int<17> v11186 = w8;	// L17519
      ap_int<17> v11187;
      ap_int<17> v11187_tmp = v11186;
      v11187_tmp(16, 1) = v11185;
      v11187 = v11187_tmp;	// L17520
      w8 = v11187;	// L17521
    }
    ap_int<17> v11188 = w8;	// L17523
    v11172.write(v11188);	// L17524
    ap_uint<17> w9;	// L17525
    w9 = 0;	// L17526
    if (v11179) {	// L17527
      int32_t v11190 = v11171[1][t18];	// L17528
      bool v11191 = v11190;	// L17529
      ap_int<17> v11192 = w9;	// L17530
      ap_int<17> v11193;
      ap_int<17> v11193_tmp = v11192;
      v11193_tmp[0] = v11191;      v11193 = v11193_tmp;	// L17531
      w9 = v11193;	// L17532
      half v11194 = v11170[1][t18];	// L17533
      uint16_t v11195;
      union { half from; uint16_t to;} _converter_v11194_to_v11195;
      _converter_v11194_to_v11195.from = v11194;
      v11195 = _converter_v11194_to_v11195.to;	// L17534
      ap_int<17> v11196 = w9;	// L17535
      ap_int<17> v11197;
      ap_int<17> v11197_tmp = v11196;
      v11197_tmp(16, 1) = v11195;
      v11197 = v11197_tmp;	// L17536
      w9 = v11197;	// L17537
    }
    ap_int<17> v11198 = w9;	// L17539
    v11173.write(v11198);	// L17540
    ap_uint<17> w10;	// L17541
    w10 = 0;	// L17542
    if (v11179) {	// L17543
      int32_t v11200 = v11171[2][t18];	// L17544
      bool v11201 = v11200;	// L17545
      ap_int<17> v11202 = w10;	// L17546
      ap_int<17> v11203;
      ap_int<17> v11203_tmp = v11202;
      v11203_tmp[0] = v11201;      v11203 = v11203_tmp;	// L17547
      w10 = v11203;	// L17548
      half v11204 = v11170[2][t18];	// L17549
      uint16_t v11205;
      union { half from; uint16_t to;} _converter_v11204_to_v11205;
      _converter_v11204_to_v11205.from = v11204;
      v11205 = _converter_v11204_to_v11205.to;	// L17550
      ap_int<17> v11206 = w10;	// L17551
      ap_int<17> v11207;
      ap_int<17> v11207_tmp = v11206;
      v11207_tmp(16, 1) = v11205;
      v11207 = v11207_tmp;	// L17552
      w10 = v11207;	// L17553
    }
    ap_int<17> v11208 = w10;	// L17555
    v11174.write(v11208);	// L17556
    ap_uint<17> w11;	// L17557
    w11 = 0;	// L17558
    if (v11179) {	// L17559
      int32_t v11210 = v11171[3][t18];	// L17560
      bool v11211 = v11210;	// L17561
      ap_int<17> v11212 = w11;	// L17562
      ap_int<17> v11213;
      ap_int<17> v11213_tmp = v11212;
      v11213_tmp[0] = v11211;      v11213 = v11213_tmp;	// L17563
      w11 = v11213;	// L17564
      half v11214 = v11170[3][t18];	// L17565
      uint16_t v11215;
      union { half from; uint16_t to;} _converter_v11214_to_v11215;
      _converter_v11214_to_v11215.from = v11214;
      v11215 = _converter_v11214_to_v11215.to;	// L17566
      ap_int<17> v11216 = w11;	// L17567
      ap_int<17> v11217;
      ap_int<17> v11217_tmp = v11216;
      v11217_tmp(16, 1) = v11215;
      v11217 = v11217_tmp;	// L17568
      w11 = v11217;	// L17569
    }
    ap_int<17> v11218 = w11;	// L17571
    v11175.write(v11218);	// L17572
  }
}

void drv_s_0(
  half v11219[4][8],
  int32_t v11220[4][8],
  hls::stream< ap_uint<17> >& v11221,
  hls::stream< ap_uint<17> >& v11222,
  hls::stream< ap_uint<17> >& v11223,
  hls::stream< ap_uint<17> >& v11224
) {	// L17576
  l_S_t_0_t19: for (int t19 = 0; t19 < 8; t19++) {	// L17582
    ap_uint<17> w12;	// L17583
    w12 = 0;	// L17584
    ap_int<33> v11227 = t19;	// L17585
    bool v11228 = v11227 < 8;	// L17586
    if (v11228) {	// L17587
      int32_t v11229 = v11220[0][t19];	// L17588
      bool v11230 = v11229;	// L17589
      ap_int<17> v11231 = w12;	// L17590
      ap_int<17> v11232;
      ap_int<17> v11232_tmp = v11231;
      v11232_tmp[0] = v11230;      v11232 = v11232_tmp;	// L17591
      w12 = v11232;	// L17592
      half v11233 = v11219[0][t19];	// L17593
      uint16_t v11234;
      union { half from; uint16_t to;} _converter_v11233_to_v11234;
      _converter_v11233_to_v11234.from = v11233;
      v11234 = _converter_v11233_to_v11234.to;	// L17594
      ap_int<17> v11235 = w12;	// L17595
      ap_int<17> v11236;
      ap_int<17> v11236_tmp = v11235;
      v11236_tmp(16, 1) = v11234;
      v11236 = v11236_tmp;	// L17596
      w12 = v11236;	// L17597
    }
    ap_int<17> v11237 = w12;	// L17599
    v11221.write(v11237);	// L17600
    ap_uint<17> w13;	// L17601
    w13 = 0;	// L17602
    if (v11228) {	// L17603
      int32_t v11239 = v11220[1][t19];	// L17604
      bool v11240 = v11239;	// L17605
      ap_int<17> v11241 = w13;	// L17606
      ap_int<17> v11242;
      ap_int<17> v11242_tmp = v11241;
      v11242_tmp[0] = v11240;      v11242 = v11242_tmp;	// L17607
      w13 = v11242;	// L17608
      half v11243 = v11219[1][t19];	// L17609
      uint16_t v11244;
      union { half from; uint16_t to;} _converter_v11243_to_v11244;
      _converter_v11243_to_v11244.from = v11243;
      v11244 = _converter_v11243_to_v11244.to;	// L17610
      ap_int<17> v11245 = w13;	// L17611
      ap_int<17> v11246;
      ap_int<17> v11246_tmp = v11245;
      v11246_tmp(16, 1) = v11244;
      v11246 = v11246_tmp;	// L17612
      w13 = v11246;	// L17613
    }
    ap_int<17> v11247 = w13;	// L17615
    v11222.write(v11247);	// L17616
    ap_uint<17> w14;	// L17617
    w14 = 0;	// L17618
    if (v11228) {	// L17619
      int32_t v11249 = v11220[2][t19];	// L17620
      bool v11250 = v11249;	// L17621
      ap_int<17> v11251 = w14;	// L17622
      ap_int<17> v11252;
      ap_int<17> v11252_tmp = v11251;
      v11252_tmp[0] = v11250;      v11252 = v11252_tmp;	// L17623
      w14 = v11252;	// L17624
      half v11253 = v11219[2][t19];	// L17625
      uint16_t v11254;
      union { half from; uint16_t to;} _converter_v11253_to_v11254;
      _converter_v11253_to_v11254.from = v11253;
      v11254 = _converter_v11253_to_v11254.to;	// L17626
      ap_int<17> v11255 = w14;	// L17627
      ap_int<17> v11256;
      ap_int<17> v11256_tmp = v11255;
      v11256_tmp(16, 1) = v11254;
      v11256 = v11256_tmp;	// L17628
      w14 = v11256;	// L17629
    }
    ap_int<17> v11257 = w14;	// L17631
    v11223.write(v11257);	// L17632
    ap_uint<17> w15;	// L17633
    w15 = 0;	// L17634
    if (v11228) {	// L17635
      int32_t v11259 = v11220[3][t19];	// L17636
      bool v11260 = v11259;	// L17637
      ap_int<17> v11261 = w15;	// L17638
      ap_int<17> v11262;
      ap_int<17> v11262_tmp = v11261;
      v11262_tmp[0] = v11260;      v11262 = v11262_tmp;	// L17639
      w15 = v11262;	// L17640
      half v11263 = v11219[3][t19];	// L17641
      uint16_t v11264;
      union { half from; uint16_t to;} _converter_v11263_to_v11264;
      _converter_v11263_to_v11264.from = v11263;
      v11264 = _converter_v11263_to_v11264.to;	// L17642
      ap_int<17> v11265 = w15;	// L17643
      ap_int<17> v11266;
      ap_int<17> v11266_tmp = v11265;
      v11266_tmp(16, 1) = v11264;
      v11266 = v11266_tmp;	// L17644
      w15 = v11266;	// L17645
    }
    ap_int<17> v11267 = w15;	// L17647
    v11224.write(v11267);	// L17648
  }
}

void col_w_0(
  half v11268[4][8],
  hls::stream< ap_uint<17> >& v11269,
  hls::stream< ap_uint<17> >& v11270,
  hls::stream< ap_uint<17> >& v11271,
  hls::stream< ap_uint<17> >& v11272
) {	// L17652
  int32_t k[4];	// L17662
  for (int v11274 = 0; v11274 < 4; v11274++) {	// L17663
    k[v11274] = 0;	// L17663
  }
  l_S_t_0_t20: for (int t20 = 0; t20 < 8; t20++) {	// L17664
    ap_uint<17> v11276 = v11269.read();	// L17665
    ap_uint<17> w16;	// L17666
    w16 = v11276;	// L17667
    ap_int<17> v11278 = w16;	// L17668
    bool v11279;
    ap_int<17> v11279_tmp = v11278;
    v11279 = v11279_tmp[0];	// L17669
    int32_t v11280 = v11279;	// L17670
    bool v11281 = v11280 == 1;	// L17671
    int32_t v11282 = k[0];	// L17672
    bool v11283 = v11282 < 8;	// L17673
    bool v11284 = v11281 & v11283;	// L17674
    if (v11284) {	// L17675
      ap_int<17> v11285 = w16;	// L17676
      int16_t v11286;
      ap_int<17> v11286_tmp = v11285;
      v11286 = v11286_tmp(16, 1);	// L17677
      half v11287;
      union { uint16_t from; half to;} _converter_v11286_to_v11287;
      _converter_v11286_to_v11287.from = v11286;
      v11287 = _converter_v11286_to_v11287.to;	// L17678
      int32_t v11288 = k[0];	// L17679
      int v11289 = v11288;	// L17680
      v11268[0][v11289] = v11287;	// L17681
      int32_t v11290 = k[0];	// L17682
      ap_int<33> v11291 = v11290;	// L17683
      ap_int<33> v11292 = v11291 + 1;	// L17684
      int32_t v11293 = v11292;	// L17685
      k[0] = v11293;	// L17686
    }
    ap_uint<17> v11294 = v11270.read();	// L17688
    ap_uint<17> w17;	// L17689
    w17 = v11294;	// L17690
    ap_int<17> v11296 = w17;	// L17691
    bool v11297;
    ap_int<17> v11297_tmp = v11296;
    v11297 = v11297_tmp[0];	// L17692
    int32_t v11298 = v11297;	// L17693
    bool v11299 = v11298 == 1;	// L17694
    int32_t v11300 = k[1];	// L17695
    bool v11301 = v11300 < 8;	// L17696
    bool v11302 = v11299 & v11301;	// L17697
    if (v11302) {	// L17698
      ap_int<17> v11303 = w17;	// L17699
      int16_t v11304;
      ap_int<17> v11304_tmp = v11303;
      v11304 = v11304_tmp(16, 1);	// L17700
      half v11305;
      union { uint16_t from; half to;} _converter_v11304_to_v11305;
      _converter_v11304_to_v11305.from = v11304;
      v11305 = _converter_v11304_to_v11305.to;	// L17701
      int32_t v11306 = k[1];	// L17702
      int v11307 = v11306;	// L17703
      v11268[1][v11307] = v11305;	// L17704
      int32_t v11308 = k[1];	// L17705
      ap_int<33> v11309 = v11308;	// L17706
      ap_int<33> v11310 = v11309 + 1;	// L17707
      int32_t v11311 = v11310;	// L17708
      k[1] = v11311;	// L17709
    }
    ap_uint<17> v11312 = v11271.read();	// L17711
    ap_uint<17> w18;	// L17712
    w18 = v11312;	// L17713
    ap_int<17> v11314 = w18;	// L17714
    bool v11315;
    ap_int<17> v11315_tmp = v11314;
    v11315 = v11315_tmp[0];	// L17715
    int32_t v11316 = v11315;	// L17716
    bool v11317 = v11316 == 1;	// L17717
    int32_t v11318 = k[2];	// L17718
    bool v11319 = v11318 < 8;	// L17719
    bool v11320 = v11317 & v11319;	// L17720
    if (v11320) {	// L17721
      ap_int<17> v11321 = w18;	// L17722
      int16_t v11322;
      ap_int<17> v11322_tmp = v11321;
      v11322 = v11322_tmp(16, 1);	// L17723
      half v11323;
      union { uint16_t from; half to;} _converter_v11322_to_v11323;
      _converter_v11322_to_v11323.from = v11322;
      v11323 = _converter_v11322_to_v11323.to;	// L17724
      int32_t v11324 = k[2];	// L17725
      int v11325 = v11324;	// L17726
      v11268[2][v11325] = v11323;	// L17727
      int32_t v11326 = k[2];	// L17728
      ap_int<33> v11327 = v11326;	// L17729
      ap_int<33> v11328 = v11327 + 1;	// L17730
      int32_t v11329 = v11328;	// L17731
      k[2] = v11329;	// L17732
    }
    ap_uint<17> v11330 = v11272.read();	// L17734
    ap_uint<17> w19;	// L17735
    w19 = v11330;	// L17736
    ap_int<17> v11332 = w19;	// L17737
    bool v11333;
    ap_int<17> v11333_tmp = v11332;
    v11333 = v11333_tmp[0];	// L17738
    int32_t v11334 = v11333;	// L17739
    bool v11335 = v11334 == 1;	// L17740
    int32_t v11336 = k[3];	// L17741
    bool v11337 = v11336 < 8;	// L17742
    bool v11338 = v11335 & v11337;	// L17743
    if (v11338) {	// L17744
      ap_int<17> v11339 = w19;	// L17745
      int16_t v11340;
      ap_int<17> v11340_tmp = v11339;
      v11340 = v11340_tmp(16, 1);	// L17746
      half v11341;
      union { uint16_t from; half to;} _converter_v11340_to_v11341;
      _converter_v11340_to_v11341.from = v11340;
      v11341 = _converter_v11340_to_v11341.to;	// L17747
      int32_t v11342 = k[3];	// L17748
      int v11343 = v11342;	// L17749
      v11268[3][v11343] = v11341;	// L17750
      int32_t v11344 = k[3];	// L17751
      ap_int<33> v11345 = v11344;	// L17752
      ap_int<33> v11346 = v11345 + 1;	// L17753
      int32_t v11347 = v11346;	// L17754
      k[3] = v11347;	// L17755
    }
  }
}

void col_e_0(
  half v11348[4][8],
  hls::stream< ap_uint<17> >& v11349,
  hls::stream< ap_uint<17> >& v11350,
  hls::stream< ap_uint<17> >& v11351,
  hls::stream< ap_uint<17> >& v11352
) {	// L17760
  int32_t k1[4];	// L17770
  for (int v11354 = 0; v11354 < 4; v11354++) {	// L17771
    k1[v11354] = 0;	// L17771
  }
  l_S_t_0_t21: for (int t21 = 0; t21 < 8; t21++) {	// L17772
    ap_uint<17> v11356 = v11349.read();	// L17773
    ap_uint<17> w20;	// L17774
    w20 = v11356;	// L17775
    ap_int<17> v11358 = w20;	// L17776
    bool v11359;
    ap_int<17> v11359_tmp = v11358;
    v11359 = v11359_tmp[0];	// L17777
    int32_t v11360 = v11359;	// L17778
    bool v11361 = v11360 == 1;	// L17779
    int32_t v11362 = k1[0];	// L17780
    bool v11363 = v11362 < 8;	// L17781
    bool v11364 = v11361 & v11363;	// L17782
    if (v11364) {	// L17783
      ap_int<17> v11365 = w20;	// L17784
      int16_t v11366;
      ap_int<17> v11366_tmp = v11365;
      v11366 = v11366_tmp(16, 1);	// L17785
      half v11367;
      union { uint16_t from; half to;} _converter_v11366_to_v11367;
      _converter_v11366_to_v11367.from = v11366;
      v11367 = _converter_v11366_to_v11367.to;	// L17786
      int32_t v11368 = k1[0];	// L17787
      int v11369 = v11368;	// L17788
      v11348[0][v11369] = v11367;	// L17789
      int32_t v11370 = k1[0];	// L17790
      ap_int<33> v11371 = v11370;	// L17791
      ap_int<33> v11372 = v11371 + 1;	// L17792
      int32_t v11373 = v11372;	// L17793
      k1[0] = v11373;	// L17794
    }
    ap_uint<17> v11374 = v11350.read();	// L17796
    ap_uint<17> w21;	// L17797
    w21 = v11374;	// L17798
    ap_int<17> v11376 = w21;	// L17799
    bool v11377;
    ap_int<17> v11377_tmp = v11376;
    v11377 = v11377_tmp[0];	// L17800
    int32_t v11378 = v11377;	// L17801
    bool v11379 = v11378 == 1;	// L17802
    int32_t v11380 = k1[1];	// L17803
    bool v11381 = v11380 < 8;	// L17804
    bool v11382 = v11379 & v11381;	// L17805
    if (v11382) {	// L17806
      ap_int<17> v11383 = w21;	// L17807
      int16_t v11384;
      ap_int<17> v11384_tmp = v11383;
      v11384 = v11384_tmp(16, 1);	// L17808
      half v11385;
      union { uint16_t from; half to;} _converter_v11384_to_v11385;
      _converter_v11384_to_v11385.from = v11384;
      v11385 = _converter_v11384_to_v11385.to;	// L17809
      int32_t v11386 = k1[1];	// L17810
      int v11387 = v11386;	// L17811
      v11348[1][v11387] = v11385;	// L17812
      int32_t v11388 = k1[1];	// L17813
      ap_int<33> v11389 = v11388;	// L17814
      ap_int<33> v11390 = v11389 + 1;	// L17815
      int32_t v11391 = v11390;	// L17816
      k1[1] = v11391;	// L17817
    }
    ap_uint<17> v11392 = v11351.read();	// L17819
    ap_uint<17> w22;	// L17820
    w22 = v11392;	// L17821
    ap_int<17> v11394 = w22;	// L17822
    bool v11395;
    ap_int<17> v11395_tmp = v11394;
    v11395 = v11395_tmp[0];	// L17823
    int32_t v11396 = v11395;	// L17824
    bool v11397 = v11396 == 1;	// L17825
    int32_t v11398 = k1[2];	// L17826
    bool v11399 = v11398 < 8;	// L17827
    bool v11400 = v11397 & v11399;	// L17828
    if (v11400) {	// L17829
      ap_int<17> v11401 = w22;	// L17830
      int16_t v11402;
      ap_int<17> v11402_tmp = v11401;
      v11402 = v11402_tmp(16, 1);	// L17831
      half v11403;
      union { uint16_t from; half to;} _converter_v11402_to_v11403;
      _converter_v11402_to_v11403.from = v11402;
      v11403 = _converter_v11402_to_v11403.to;	// L17832
      int32_t v11404 = k1[2];	// L17833
      int v11405 = v11404;	// L17834
      v11348[2][v11405] = v11403;	// L17835
      int32_t v11406 = k1[2];	// L17836
      ap_int<33> v11407 = v11406;	// L17837
      ap_int<33> v11408 = v11407 + 1;	// L17838
      int32_t v11409 = v11408;	// L17839
      k1[2] = v11409;	// L17840
    }
    ap_uint<17> v11410 = v11352.read();	// L17842
    ap_uint<17> w23;	// L17843
    w23 = v11410;	// L17844
    ap_int<17> v11412 = w23;	// L17845
    bool v11413;
    ap_int<17> v11413_tmp = v11412;
    v11413 = v11413_tmp[0];	// L17846
    int32_t v11414 = v11413;	// L17847
    bool v11415 = v11414 == 1;	// L17848
    int32_t v11416 = k1[3];	// L17849
    bool v11417 = v11416 < 8;	// L17850
    bool v11418 = v11415 & v11417;	// L17851
    if (v11418) {	// L17852
      ap_int<17> v11419 = w23;	// L17853
      int16_t v11420;
      ap_int<17> v11420_tmp = v11419;
      v11420 = v11420_tmp(16, 1);	// L17854
      half v11421;
      union { uint16_t from; half to;} _converter_v11420_to_v11421;
      _converter_v11420_to_v11421.from = v11420;
      v11421 = _converter_v11420_to_v11421.to;	// L17855
      int32_t v11422 = k1[3];	// L17856
      int v11423 = v11422;	// L17857
      v11348[3][v11423] = v11421;	// L17858
      int32_t v11424 = k1[3];	// L17859
      ap_int<33> v11425 = v11424;	// L17860
      ap_int<33> v11426 = v11425 + 1;	// L17861
      int32_t v11427 = v11426;	// L17862
      k1[3] = v11427;	// L17863
    }
  }
}

void col_n_0(
  half v11428[4][8],
  hls::stream< ap_uint<17> >& v11429,
  hls::stream< ap_uint<17> >& v11430,
  hls::stream< ap_uint<17> >& v11431,
  hls::stream< ap_uint<17> >& v11432
) {	// L17868
  int32_t k2[4];	// L17878
  for (int v11434 = 0; v11434 < 4; v11434++) {	// L17879
    k2[v11434] = 0;	// L17879
  }
  l_S_t_0_t22: for (int t22 = 0; t22 < 8; t22++) {	// L17880
    ap_uint<17> v11436 = v11429.read();	// L17881
    ap_uint<17> w24;	// L17882
    w24 = v11436;	// L17883
    ap_int<17> v11438 = w24;	// L17884
    bool v11439;
    ap_int<17> v11439_tmp = v11438;
    v11439 = v11439_tmp[0];	// L17885
    int32_t v11440 = v11439;	// L17886
    bool v11441 = v11440 == 1;	// L17887
    int32_t v11442 = k2[0];	// L17888
    bool v11443 = v11442 < 8;	// L17889
    bool v11444 = v11441 & v11443;	// L17890
    if (v11444) {	// L17891
      ap_int<17> v11445 = w24;	// L17892
      int16_t v11446;
      ap_int<17> v11446_tmp = v11445;
      v11446 = v11446_tmp(16, 1);	// L17893
      half v11447;
      union { uint16_t from; half to;} _converter_v11446_to_v11447;
      _converter_v11446_to_v11447.from = v11446;
      v11447 = _converter_v11446_to_v11447.to;	// L17894
      int32_t v11448 = k2[0];	// L17895
      int v11449 = v11448;	// L17896
      v11428[0][v11449] = v11447;	// L17897
      int32_t v11450 = k2[0];	// L17898
      ap_int<33> v11451 = v11450;	// L17899
      ap_int<33> v11452 = v11451 + 1;	// L17900
      int32_t v11453 = v11452;	// L17901
      k2[0] = v11453;	// L17902
    }
    ap_uint<17> v11454 = v11430.read();	// L17904
    ap_uint<17> w25;	// L17905
    w25 = v11454;	// L17906
    ap_int<17> v11456 = w25;	// L17907
    bool v11457;
    ap_int<17> v11457_tmp = v11456;
    v11457 = v11457_tmp[0];	// L17908
    int32_t v11458 = v11457;	// L17909
    bool v11459 = v11458 == 1;	// L17910
    int32_t v11460 = k2[1];	// L17911
    bool v11461 = v11460 < 8;	// L17912
    bool v11462 = v11459 & v11461;	// L17913
    if (v11462) {	// L17914
      ap_int<17> v11463 = w25;	// L17915
      int16_t v11464;
      ap_int<17> v11464_tmp = v11463;
      v11464 = v11464_tmp(16, 1);	// L17916
      half v11465;
      union { uint16_t from; half to;} _converter_v11464_to_v11465;
      _converter_v11464_to_v11465.from = v11464;
      v11465 = _converter_v11464_to_v11465.to;	// L17917
      int32_t v11466 = k2[1];	// L17918
      int v11467 = v11466;	// L17919
      v11428[1][v11467] = v11465;	// L17920
      int32_t v11468 = k2[1];	// L17921
      ap_int<33> v11469 = v11468;	// L17922
      ap_int<33> v11470 = v11469 + 1;	// L17923
      int32_t v11471 = v11470;	// L17924
      k2[1] = v11471;	// L17925
    }
    ap_uint<17> v11472 = v11431.read();	// L17927
    ap_uint<17> w26;	// L17928
    w26 = v11472;	// L17929
    ap_int<17> v11474 = w26;	// L17930
    bool v11475;
    ap_int<17> v11475_tmp = v11474;
    v11475 = v11475_tmp[0];	// L17931
    int32_t v11476 = v11475;	// L17932
    bool v11477 = v11476 == 1;	// L17933
    int32_t v11478 = k2[2];	// L17934
    bool v11479 = v11478 < 8;	// L17935
    bool v11480 = v11477 & v11479;	// L17936
    if (v11480) {	// L17937
      ap_int<17> v11481 = w26;	// L17938
      int16_t v11482;
      ap_int<17> v11482_tmp = v11481;
      v11482 = v11482_tmp(16, 1);	// L17939
      half v11483;
      union { uint16_t from; half to;} _converter_v11482_to_v11483;
      _converter_v11482_to_v11483.from = v11482;
      v11483 = _converter_v11482_to_v11483.to;	// L17940
      int32_t v11484 = k2[2];	// L17941
      int v11485 = v11484;	// L17942
      v11428[2][v11485] = v11483;	// L17943
      int32_t v11486 = k2[2];	// L17944
      ap_int<33> v11487 = v11486;	// L17945
      ap_int<33> v11488 = v11487 + 1;	// L17946
      int32_t v11489 = v11488;	// L17947
      k2[2] = v11489;	// L17948
    }
    ap_uint<17> v11490 = v11432.read();	// L17950
    ap_uint<17> w27;	// L17951
    w27 = v11490;	// L17952
    ap_int<17> v11492 = w27;	// L17953
    bool v11493;
    ap_int<17> v11493_tmp = v11492;
    v11493 = v11493_tmp[0];	// L17954
    int32_t v11494 = v11493;	// L17955
    bool v11495 = v11494 == 1;	// L17956
    int32_t v11496 = k2[3];	// L17957
    bool v11497 = v11496 < 8;	// L17958
    bool v11498 = v11495 & v11497;	// L17959
    if (v11498) {	// L17960
      ap_int<17> v11499 = w27;	// L17961
      int16_t v11500;
      ap_int<17> v11500_tmp = v11499;
      v11500 = v11500_tmp(16, 1);	// L17962
      half v11501;
      union { uint16_t from; half to;} _converter_v11500_to_v11501;
      _converter_v11500_to_v11501.from = v11500;
      v11501 = _converter_v11500_to_v11501.to;	// L17963
      int32_t v11502 = k2[3];	// L17964
      int v11503 = v11502;	// L17965
      v11428[3][v11503] = v11501;	// L17966
      int32_t v11504 = k2[3];	// L17967
      ap_int<33> v11505 = v11504;	// L17968
      ap_int<33> v11506 = v11505 + 1;	// L17969
      int32_t v11507 = v11506;	// L17970
      k2[3] = v11507;	// L17971
    }
  }
}

void col_s_0(
  half v11508[4][8],
  hls::stream< ap_uint<17> >& v11509,
  hls::stream< ap_uint<17> >& v11510,
  hls::stream< ap_uint<17> >& v11511,
  hls::stream< ap_uint<17> >& v11512
) {	// L17976
  int32_t k3[4];	// L17986
  for (int v11514 = 0; v11514 < 4; v11514++) {	// L17987
    k3[v11514] = 0;	// L17987
  }
  l_S_t_0_t23: for (int t23 = 0; t23 < 8; t23++) {	// L17988
    ap_uint<17> v11516 = v11509.read();	// L17989
    ap_uint<17> w28;	// L17990
    w28 = v11516;	// L17991
    ap_int<17> v11518 = w28;	// L17992
    bool v11519;
    ap_int<17> v11519_tmp = v11518;
    v11519 = v11519_tmp[0];	// L17993
    int32_t v11520 = v11519;	// L17994
    bool v11521 = v11520 == 1;	// L17995
    int32_t v11522 = k3[0];	// L17996
    bool v11523 = v11522 < 8;	// L17997
    bool v11524 = v11521 & v11523;	// L17998
    if (v11524) {	// L17999
      ap_int<17> v11525 = w28;	// L18000
      int16_t v11526;
      ap_int<17> v11526_tmp = v11525;
      v11526 = v11526_tmp(16, 1);	// L18001
      half v11527;
      union { uint16_t from; half to;} _converter_v11526_to_v11527;
      _converter_v11526_to_v11527.from = v11526;
      v11527 = _converter_v11526_to_v11527.to;	// L18002
      int32_t v11528 = k3[0];	// L18003
      int v11529 = v11528;	// L18004
      v11508[0][v11529] = v11527;	// L18005
      int32_t v11530 = k3[0];	// L18006
      ap_int<33> v11531 = v11530;	// L18007
      ap_int<33> v11532 = v11531 + 1;	// L18008
      int32_t v11533 = v11532;	// L18009
      k3[0] = v11533;	// L18010
    }
    ap_uint<17> v11534 = v11510.read();	// L18012
    ap_uint<17> w29;	// L18013
    w29 = v11534;	// L18014
    ap_int<17> v11536 = w29;	// L18015
    bool v11537;
    ap_int<17> v11537_tmp = v11536;
    v11537 = v11537_tmp[0];	// L18016
    int32_t v11538 = v11537;	// L18017
    bool v11539 = v11538 == 1;	// L18018
    int32_t v11540 = k3[1];	// L18019
    bool v11541 = v11540 < 8;	// L18020
    bool v11542 = v11539 & v11541;	// L18021
    if (v11542) {	// L18022
      ap_int<17> v11543 = w29;	// L18023
      int16_t v11544;
      ap_int<17> v11544_tmp = v11543;
      v11544 = v11544_tmp(16, 1);	// L18024
      half v11545;
      union { uint16_t from; half to;} _converter_v11544_to_v11545;
      _converter_v11544_to_v11545.from = v11544;
      v11545 = _converter_v11544_to_v11545.to;	// L18025
      int32_t v11546 = k3[1];	// L18026
      int v11547 = v11546;	// L18027
      v11508[1][v11547] = v11545;	// L18028
      int32_t v11548 = k3[1];	// L18029
      ap_int<33> v11549 = v11548;	// L18030
      ap_int<33> v11550 = v11549 + 1;	// L18031
      int32_t v11551 = v11550;	// L18032
      k3[1] = v11551;	// L18033
    }
    ap_uint<17> v11552 = v11511.read();	// L18035
    ap_uint<17> w30;	// L18036
    w30 = v11552;	// L18037
    ap_int<17> v11554 = w30;	// L18038
    bool v11555;
    ap_int<17> v11555_tmp = v11554;
    v11555 = v11555_tmp[0];	// L18039
    int32_t v11556 = v11555;	// L18040
    bool v11557 = v11556 == 1;	// L18041
    int32_t v11558 = k3[2];	// L18042
    bool v11559 = v11558 < 8;	// L18043
    bool v11560 = v11557 & v11559;	// L18044
    if (v11560) {	// L18045
      ap_int<17> v11561 = w30;	// L18046
      int16_t v11562;
      ap_int<17> v11562_tmp = v11561;
      v11562 = v11562_tmp(16, 1);	// L18047
      half v11563;
      union { uint16_t from; half to;} _converter_v11562_to_v11563;
      _converter_v11562_to_v11563.from = v11562;
      v11563 = _converter_v11562_to_v11563.to;	// L18048
      int32_t v11564 = k3[2];	// L18049
      int v11565 = v11564;	// L18050
      v11508[2][v11565] = v11563;	// L18051
      int32_t v11566 = k3[2];	// L18052
      ap_int<33> v11567 = v11566;	// L18053
      ap_int<33> v11568 = v11567 + 1;	// L18054
      int32_t v11569 = v11568;	// L18055
      k3[2] = v11569;	// L18056
    }
    ap_uint<17> v11570 = v11512.read();	// L18058
    ap_uint<17> w31;	// L18059
    w31 = v11570;	// L18060
    ap_int<17> v11572 = w31;	// L18061
    bool v11573;
    ap_int<17> v11573_tmp = v11572;
    v11573 = v11573_tmp[0];	// L18062
    int32_t v11574 = v11573;	// L18063
    bool v11575 = v11574 == 1;	// L18064
    int32_t v11576 = k3[3];	// L18065
    bool v11577 = v11576 < 8;	// L18066
    bool v11578 = v11575 & v11577;	// L18067
    if (v11578) {	// L18068
      ap_int<17> v11579 = w31;	// L18069
      int16_t v11580;
      ap_int<17> v11580_tmp = v11579;
      v11580 = v11580_tmp(16, 1);	// L18070
      half v11581;
      union { uint16_t from; half to;} _converter_v11580_to_v11581;
      _converter_v11580_to_v11581.from = v11580;
      v11581 = _converter_v11580_to_v11581.to;	// L18071
      int32_t v11582 = k3[3];	// L18072
      int v11583 = v11582;	// L18073
      v11508[3][v11583] = v11581;	// L18074
      int32_t v11584 = k3[3];	// L18075
      ap_int<33> v11585 = v11584;	// L18076
      ap_int<33> v11586 = v11585 + 1;	// L18077
      int32_t v11587 = v11586;	// L18078
      k3[3] = v11587;	// L18079
    }
  }
}

void rdrv_w_0(
  int32_t v11588[4][8],
  hls::stream< int32_t >& v11589,
  hls::stream< ap_uint<26> >& v11590,
  hls::stream< int32_t >& v11591,
  hls::stream< ap_uint<26> >& v11592,
  hls::stream< int32_t >& v11593,
  hls::stream< ap_uint<26> >& v11594,
  hls::stream< int32_t >& v11595,
  hls::stream< ap_uint<26> >& v11596
) {	// L18084
  int32_t dcred[4];	// L18094
  for (int v11598 = 0; v11598 < 4; v11598++) {	// L18095
    dcred[v11598] = 0;	// L18095
  }
  int32_t sp[4];	// L18096
  for (int v11600 = 0; v11600 < 4; v11600++) {	// L18097
    sp[v11600] = 0;	// L18097
  }
  l_S_t_0_t24: for (int t24 = 0; t24 < 8; t24++) {	// L18098
    int32_t v11602 = v11589.read();	// L18099
    int32_t v11603 = dcred[0];	// L18100
    ap_int<33> v11604 = v11603;	// L18101
    ap_int<33> v11605 = v11602;	// L18102
    ap_int<33> v11606 = v11604 + v11605;	// L18103
    int32_t v11607 = v11606;	// L18104
    dcred[0] = v11607;	// L18105
    ap_uint<26> pw;	// L18106
    pw = 0;	// L18107
    int32_t v11609 = sp[0];	// L18108
    bool v11610 = v11609 < 8;	// L18109
    if (v11610) {	// L18110
      ap_uint<26> cand;	// L18111
      cand = 0;	// L18112
      int32_t v11612 = sp[0];	// L18113
      int v11613 = v11612;	// L18114
      int32_t v11614 = v11588[0][v11613];	// L18115
      ap_uint<26> v11615 = v11614;	// L18116
      ap_int<26> v11616 = cand;	// L18117
      ap_int<26> v11617;
      ap_int<26> v11617_tmp = v11616;
      v11617_tmp(25, 0) = v11615;
      v11617 = v11617_tmp;	// L18118
      cand = v11617;	// L18119
      ap_int<26> v11618 = cand;	// L18120
      bool v11619;
      ap_int<26> v11619_tmp = v11618;
      v11619 = v11619_tmp[25];	// L18121
      int32_t v11620 = v11619;	// L18122
      bool v11621 = v11620 == 0;	// L18123
      if (v11621) {	// L18124
        int32_t v11622 = sp[0];	// L18125
        ap_int<33> v11623 = v11622;	// L18126
        ap_int<33> v11624 = v11623 + 1;	// L18127
        int32_t v11625 = v11624;	// L18128
        sp[0] = v11625;	// L18129
      } else {
        int32_t v11626 = dcred[0];	// L18131
        bool v11627 = v11626 > 0;	// L18132
        if (v11627) {	// L18133
          ap_int<26> v11628 = cand;	// L18134
          pw = v11628;	// L18135
          int32_t v11629 = dcred[0];	// L18136
          ap_int<33> v11630 = v11629;	// L18137
          ap_int<33> v11631 = v11630 - 1;	// L18138
          int32_t v11632 = v11631;	// L18139
          dcred[0] = v11632;	// L18140
          int32_t v11633 = sp[0];	// L18141
          ap_int<33> v11634 = v11633;	// L18142
          ap_int<33> v11635 = v11634 + 1;	// L18143
          int32_t v11636 = v11635;	// L18144
          sp[0] = v11636;	// L18145
        }
      }
    }
    ap_int<26> v11637 = pw;	// L18149
    v11590.write(v11637);	// L18150
    int32_t v11638 = v11591.read();	// L18151
    int32_t v11639 = dcred[1];	// L18152
    ap_int<33> v11640 = v11639;	// L18153
    ap_int<33> v11641 = v11638;	// L18154
    ap_int<33> v11642 = v11640 + v11641;	// L18155
    int32_t v11643 = v11642;	// L18156
    dcred[1] = v11643;	// L18157
    ap_uint<26> pw1;	// L18158
    pw1 = 0;	// L18159
    int32_t v11645 = sp[1];	// L18160
    bool v11646 = v11645 < 8;	// L18161
    if (v11646) {	// L18162
      ap_uint<26> cand1;	// L18163
      cand1 = 0;	// L18164
      int32_t v11648 = sp[1];	// L18165
      int v11649 = v11648;	// L18166
      int32_t v11650 = v11588[1][v11649];	// L18167
      ap_uint<26> v11651 = v11650;	// L18168
      ap_int<26> v11652 = cand1;	// L18169
      ap_int<26> v11653;
      ap_int<26> v11653_tmp = v11652;
      v11653_tmp(25, 0) = v11651;
      v11653 = v11653_tmp;	// L18170
      cand1 = v11653;	// L18171
      ap_int<26> v11654 = cand1;	// L18172
      bool v11655;
      ap_int<26> v11655_tmp = v11654;
      v11655 = v11655_tmp[25];	// L18173
      int32_t v11656 = v11655;	// L18174
      bool v11657 = v11656 == 0;	// L18175
      if (v11657) {	// L18176
        int32_t v11658 = sp[1];	// L18177
        ap_int<33> v11659 = v11658;	// L18178
        ap_int<33> v11660 = v11659 + 1;	// L18179
        int32_t v11661 = v11660;	// L18180
        sp[1] = v11661;	// L18181
      } else {
        int32_t v11662 = dcred[1];	// L18183
        bool v11663 = v11662 > 0;	// L18184
        if (v11663) {	// L18185
          ap_int<26> v11664 = cand1;	// L18186
          pw1 = v11664;	// L18187
          int32_t v11665 = dcred[1];	// L18188
          ap_int<33> v11666 = v11665;	// L18189
          ap_int<33> v11667 = v11666 - 1;	// L18190
          int32_t v11668 = v11667;	// L18191
          dcred[1] = v11668;	// L18192
          int32_t v11669 = sp[1];	// L18193
          ap_int<33> v11670 = v11669;	// L18194
          ap_int<33> v11671 = v11670 + 1;	// L18195
          int32_t v11672 = v11671;	// L18196
          sp[1] = v11672;	// L18197
        }
      }
    }
    ap_int<26> v11673 = pw1;	// L18201
    v11592.write(v11673);	// L18202
    int32_t v11674 = v11593.read();	// L18203
    int32_t v11675 = dcred[2];	// L18204
    ap_int<33> v11676 = v11675;	// L18205
    ap_int<33> v11677 = v11674;	// L18206
    ap_int<33> v11678 = v11676 + v11677;	// L18207
    int32_t v11679 = v11678;	// L18208
    dcred[2] = v11679;	// L18209
    ap_uint<26> pw2;	// L18210
    pw2 = 0;	// L18211
    int32_t v11681 = sp[2];	// L18212
    bool v11682 = v11681 < 8;	// L18213
    if (v11682) {	// L18214
      ap_uint<26> cand2;	// L18215
      cand2 = 0;	// L18216
      int32_t v11684 = sp[2];	// L18217
      int v11685 = v11684;	// L18218
      int32_t v11686 = v11588[2][v11685];	// L18219
      ap_uint<26> v11687 = v11686;	// L18220
      ap_int<26> v11688 = cand2;	// L18221
      ap_int<26> v11689;
      ap_int<26> v11689_tmp = v11688;
      v11689_tmp(25, 0) = v11687;
      v11689 = v11689_tmp;	// L18222
      cand2 = v11689;	// L18223
      ap_int<26> v11690 = cand2;	// L18224
      bool v11691;
      ap_int<26> v11691_tmp = v11690;
      v11691 = v11691_tmp[25];	// L18225
      int32_t v11692 = v11691;	// L18226
      bool v11693 = v11692 == 0;	// L18227
      if (v11693) {	// L18228
        int32_t v11694 = sp[2];	// L18229
        ap_int<33> v11695 = v11694;	// L18230
        ap_int<33> v11696 = v11695 + 1;	// L18231
        int32_t v11697 = v11696;	// L18232
        sp[2] = v11697;	// L18233
      } else {
        int32_t v11698 = dcred[2];	// L18235
        bool v11699 = v11698 > 0;	// L18236
        if (v11699) {	// L18237
          ap_int<26> v11700 = cand2;	// L18238
          pw2 = v11700;	// L18239
          int32_t v11701 = dcred[2];	// L18240
          ap_int<33> v11702 = v11701;	// L18241
          ap_int<33> v11703 = v11702 - 1;	// L18242
          int32_t v11704 = v11703;	// L18243
          dcred[2] = v11704;	// L18244
          int32_t v11705 = sp[2];	// L18245
          ap_int<33> v11706 = v11705;	// L18246
          ap_int<33> v11707 = v11706 + 1;	// L18247
          int32_t v11708 = v11707;	// L18248
          sp[2] = v11708;	// L18249
        }
      }
    }
    ap_int<26> v11709 = pw2;	// L18253
    v11594.write(v11709);	// L18254
    int32_t v11710 = v11595.read();	// L18255
    int32_t v11711 = dcred[3];	// L18256
    ap_int<33> v11712 = v11711;	// L18257
    ap_int<33> v11713 = v11710;	// L18258
    ap_int<33> v11714 = v11712 + v11713;	// L18259
    int32_t v11715 = v11714;	// L18260
    dcred[3] = v11715;	// L18261
    ap_uint<26> pw3;	// L18262
    pw3 = 0;	// L18263
    int32_t v11717 = sp[3];	// L18264
    bool v11718 = v11717 < 8;	// L18265
    if (v11718) {	// L18266
      ap_uint<26> cand3;	// L18267
      cand3 = 0;	// L18268
      int32_t v11720 = sp[3];	// L18269
      int v11721 = v11720;	// L18270
      int32_t v11722 = v11588[3][v11721];	// L18271
      ap_uint<26> v11723 = v11722;	// L18272
      ap_int<26> v11724 = cand3;	// L18273
      ap_int<26> v11725;
      ap_int<26> v11725_tmp = v11724;
      v11725_tmp(25, 0) = v11723;
      v11725 = v11725_tmp;	// L18274
      cand3 = v11725;	// L18275
      ap_int<26> v11726 = cand3;	// L18276
      bool v11727;
      ap_int<26> v11727_tmp = v11726;
      v11727 = v11727_tmp[25];	// L18277
      int32_t v11728 = v11727;	// L18278
      bool v11729 = v11728 == 0;	// L18279
      if (v11729) {	// L18280
        int32_t v11730 = sp[3];	// L18281
        ap_int<33> v11731 = v11730;	// L18282
        ap_int<33> v11732 = v11731 + 1;	// L18283
        int32_t v11733 = v11732;	// L18284
        sp[3] = v11733;	// L18285
      } else {
        int32_t v11734 = dcred[3];	// L18287
        bool v11735 = v11734 > 0;	// L18288
        if (v11735) {	// L18289
          ap_int<26> v11736 = cand3;	// L18290
          pw3 = v11736;	// L18291
          int32_t v11737 = dcred[3];	// L18292
          ap_int<33> v11738 = v11737;	// L18293
          ap_int<33> v11739 = v11738 - 1;	// L18294
          int32_t v11740 = v11739;	// L18295
          dcred[3] = v11740;	// L18296
          int32_t v11741 = sp[3];	// L18297
          ap_int<33> v11742 = v11741;	// L18298
          ap_int<33> v11743 = v11742 + 1;	// L18299
          int32_t v11744 = v11743;	// L18300
          sp[3] = v11744;	// L18301
        }
      }
    }
    ap_int<26> v11745 = pw3;	// L18305
    v11596.write(v11745);	// L18306
  }
}

void rdrv_e_0(
  int32_t v11746[4][8],
  hls::stream< int32_t >& v11747,
  hls::stream< ap_uint<26> >& v11748,
  hls::stream< int32_t >& v11749,
  hls::stream< ap_uint<26> >& v11750,
  hls::stream< int32_t >& v11751,
  hls::stream< ap_uint<26> >& v11752,
  hls::stream< int32_t >& v11753,
  hls::stream< ap_uint<26> >& v11754
) {	// L18310
  int32_t dcred1[4];	// L18320
  for (int v11756 = 0; v11756 < 4; v11756++) {	// L18321
    dcred1[v11756] = 0;	// L18321
  }
  int32_t sp1[4];	// L18322
  for (int v11758 = 0; v11758 < 4; v11758++) {	// L18323
    sp1[v11758] = 0;	// L18323
  }
  l_S_t_0_t25: for (int t25 = 0; t25 < 8; t25++) {	// L18324
    int32_t v11760 = v11747.read();	// L18325
    int32_t v11761 = dcred1[0];	// L18326
    ap_int<33> v11762 = v11761;	// L18327
    ap_int<33> v11763 = v11760;	// L18328
    ap_int<33> v11764 = v11762 + v11763;	// L18329
    int32_t v11765 = v11764;	// L18330
    dcred1[0] = v11765;	// L18331
    ap_uint<26> pw4;	// L18332
    pw4 = 0;	// L18333
    int32_t v11767 = sp1[0];	// L18334
    bool v11768 = v11767 < 8;	// L18335
    if (v11768) {	// L18336
      ap_uint<26> cand4;	// L18337
      cand4 = 0;	// L18338
      int32_t v11770 = sp1[0];	// L18339
      int v11771 = v11770;	// L18340
      int32_t v11772 = v11746[0][v11771];	// L18341
      ap_uint<26> v11773 = v11772;	// L18342
      ap_int<26> v11774 = cand4;	// L18343
      ap_int<26> v11775;
      ap_int<26> v11775_tmp = v11774;
      v11775_tmp(25, 0) = v11773;
      v11775 = v11775_tmp;	// L18344
      cand4 = v11775;	// L18345
      ap_int<26> v11776 = cand4;	// L18346
      bool v11777;
      ap_int<26> v11777_tmp = v11776;
      v11777 = v11777_tmp[25];	// L18347
      int32_t v11778 = v11777;	// L18348
      bool v11779 = v11778 == 0;	// L18349
      if (v11779) {	// L18350
        int32_t v11780 = sp1[0];	// L18351
        ap_int<33> v11781 = v11780;	// L18352
        ap_int<33> v11782 = v11781 + 1;	// L18353
        int32_t v11783 = v11782;	// L18354
        sp1[0] = v11783;	// L18355
      } else {
        int32_t v11784 = dcred1[0];	// L18357
        bool v11785 = v11784 > 0;	// L18358
        if (v11785) {	// L18359
          ap_int<26> v11786 = cand4;	// L18360
          pw4 = v11786;	// L18361
          int32_t v11787 = dcred1[0];	// L18362
          ap_int<33> v11788 = v11787;	// L18363
          ap_int<33> v11789 = v11788 - 1;	// L18364
          int32_t v11790 = v11789;	// L18365
          dcred1[0] = v11790;	// L18366
          int32_t v11791 = sp1[0];	// L18367
          ap_int<33> v11792 = v11791;	// L18368
          ap_int<33> v11793 = v11792 + 1;	// L18369
          int32_t v11794 = v11793;	// L18370
          sp1[0] = v11794;	// L18371
        }
      }
    }
    ap_int<26> v11795 = pw4;	// L18375
    v11748.write(v11795);	// L18376
    int32_t v11796 = v11749.read();	// L18377
    int32_t v11797 = dcred1[1];	// L18378
    ap_int<33> v11798 = v11797;	// L18379
    ap_int<33> v11799 = v11796;	// L18380
    ap_int<33> v11800 = v11798 + v11799;	// L18381
    int32_t v11801 = v11800;	// L18382
    dcred1[1] = v11801;	// L18383
    ap_uint<26> pw5;	// L18384
    pw5 = 0;	// L18385
    int32_t v11803 = sp1[1];	// L18386
    bool v11804 = v11803 < 8;	// L18387
    if (v11804) {	// L18388
      ap_uint<26> cand5;	// L18389
      cand5 = 0;	// L18390
      int32_t v11806 = sp1[1];	// L18391
      int v11807 = v11806;	// L18392
      int32_t v11808 = v11746[1][v11807];	// L18393
      ap_uint<26> v11809 = v11808;	// L18394
      ap_int<26> v11810 = cand5;	// L18395
      ap_int<26> v11811;
      ap_int<26> v11811_tmp = v11810;
      v11811_tmp(25, 0) = v11809;
      v11811 = v11811_tmp;	// L18396
      cand5 = v11811;	// L18397
      ap_int<26> v11812 = cand5;	// L18398
      bool v11813;
      ap_int<26> v11813_tmp = v11812;
      v11813 = v11813_tmp[25];	// L18399
      int32_t v11814 = v11813;	// L18400
      bool v11815 = v11814 == 0;	// L18401
      if (v11815) {	// L18402
        int32_t v11816 = sp1[1];	// L18403
        ap_int<33> v11817 = v11816;	// L18404
        ap_int<33> v11818 = v11817 + 1;	// L18405
        int32_t v11819 = v11818;	// L18406
        sp1[1] = v11819;	// L18407
      } else {
        int32_t v11820 = dcred1[1];	// L18409
        bool v11821 = v11820 > 0;	// L18410
        if (v11821) {	// L18411
          ap_int<26> v11822 = cand5;	// L18412
          pw5 = v11822;	// L18413
          int32_t v11823 = dcred1[1];	// L18414
          ap_int<33> v11824 = v11823;	// L18415
          ap_int<33> v11825 = v11824 - 1;	// L18416
          int32_t v11826 = v11825;	// L18417
          dcred1[1] = v11826;	// L18418
          int32_t v11827 = sp1[1];	// L18419
          ap_int<33> v11828 = v11827;	// L18420
          ap_int<33> v11829 = v11828 + 1;	// L18421
          int32_t v11830 = v11829;	// L18422
          sp1[1] = v11830;	// L18423
        }
      }
    }
    ap_int<26> v11831 = pw5;	// L18427
    v11750.write(v11831);	// L18428
    int32_t v11832 = v11751.read();	// L18429
    int32_t v11833 = dcred1[2];	// L18430
    ap_int<33> v11834 = v11833;	// L18431
    ap_int<33> v11835 = v11832;	// L18432
    ap_int<33> v11836 = v11834 + v11835;	// L18433
    int32_t v11837 = v11836;	// L18434
    dcred1[2] = v11837;	// L18435
    ap_uint<26> pw6;	// L18436
    pw6 = 0;	// L18437
    int32_t v11839 = sp1[2];	// L18438
    bool v11840 = v11839 < 8;	// L18439
    if (v11840) {	// L18440
      ap_uint<26> cand6;	// L18441
      cand6 = 0;	// L18442
      int32_t v11842 = sp1[2];	// L18443
      int v11843 = v11842;	// L18444
      int32_t v11844 = v11746[2][v11843];	// L18445
      ap_uint<26> v11845 = v11844;	// L18446
      ap_int<26> v11846 = cand6;	// L18447
      ap_int<26> v11847;
      ap_int<26> v11847_tmp = v11846;
      v11847_tmp(25, 0) = v11845;
      v11847 = v11847_tmp;	// L18448
      cand6 = v11847;	// L18449
      ap_int<26> v11848 = cand6;	// L18450
      bool v11849;
      ap_int<26> v11849_tmp = v11848;
      v11849 = v11849_tmp[25];	// L18451
      int32_t v11850 = v11849;	// L18452
      bool v11851 = v11850 == 0;	// L18453
      if (v11851) {	// L18454
        int32_t v11852 = sp1[2];	// L18455
        ap_int<33> v11853 = v11852;	// L18456
        ap_int<33> v11854 = v11853 + 1;	// L18457
        int32_t v11855 = v11854;	// L18458
        sp1[2] = v11855;	// L18459
      } else {
        int32_t v11856 = dcred1[2];	// L18461
        bool v11857 = v11856 > 0;	// L18462
        if (v11857) {	// L18463
          ap_int<26> v11858 = cand6;	// L18464
          pw6 = v11858;	// L18465
          int32_t v11859 = dcred1[2];	// L18466
          ap_int<33> v11860 = v11859;	// L18467
          ap_int<33> v11861 = v11860 - 1;	// L18468
          int32_t v11862 = v11861;	// L18469
          dcred1[2] = v11862;	// L18470
          int32_t v11863 = sp1[2];	// L18471
          ap_int<33> v11864 = v11863;	// L18472
          ap_int<33> v11865 = v11864 + 1;	// L18473
          int32_t v11866 = v11865;	// L18474
          sp1[2] = v11866;	// L18475
        }
      }
    }
    ap_int<26> v11867 = pw6;	// L18479
    v11752.write(v11867);	// L18480
    int32_t v11868 = v11753.read();	// L18481
    int32_t v11869 = dcred1[3];	// L18482
    ap_int<33> v11870 = v11869;	// L18483
    ap_int<33> v11871 = v11868;	// L18484
    ap_int<33> v11872 = v11870 + v11871;	// L18485
    int32_t v11873 = v11872;	// L18486
    dcred1[3] = v11873;	// L18487
    ap_uint<26> pw7;	// L18488
    pw7 = 0;	// L18489
    int32_t v11875 = sp1[3];	// L18490
    bool v11876 = v11875 < 8;	// L18491
    if (v11876) {	// L18492
      ap_uint<26> cand7;	// L18493
      cand7 = 0;	// L18494
      int32_t v11878 = sp1[3];	// L18495
      int v11879 = v11878;	// L18496
      int32_t v11880 = v11746[3][v11879];	// L18497
      ap_uint<26> v11881 = v11880;	// L18498
      ap_int<26> v11882 = cand7;	// L18499
      ap_int<26> v11883;
      ap_int<26> v11883_tmp = v11882;
      v11883_tmp(25, 0) = v11881;
      v11883 = v11883_tmp;	// L18500
      cand7 = v11883;	// L18501
      ap_int<26> v11884 = cand7;	// L18502
      bool v11885;
      ap_int<26> v11885_tmp = v11884;
      v11885 = v11885_tmp[25];	// L18503
      int32_t v11886 = v11885;	// L18504
      bool v11887 = v11886 == 0;	// L18505
      if (v11887) {	// L18506
        int32_t v11888 = sp1[3];	// L18507
        ap_int<33> v11889 = v11888;	// L18508
        ap_int<33> v11890 = v11889 + 1;	// L18509
        int32_t v11891 = v11890;	// L18510
        sp1[3] = v11891;	// L18511
      } else {
        int32_t v11892 = dcred1[3];	// L18513
        bool v11893 = v11892 > 0;	// L18514
        if (v11893) {	// L18515
          ap_int<26> v11894 = cand7;	// L18516
          pw7 = v11894;	// L18517
          int32_t v11895 = dcred1[3];	// L18518
          ap_int<33> v11896 = v11895;	// L18519
          ap_int<33> v11897 = v11896 - 1;	// L18520
          int32_t v11898 = v11897;	// L18521
          dcred1[3] = v11898;	// L18522
          int32_t v11899 = sp1[3];	// L18523
          ap_int<33> v11900 = v11899;	// L18524
          ap_int<33> v11901 = v11900 + 1;	// L18525
          int32_t v11902 = v11901;	// L18526
          sp1[3] = v11902;	// L18527
        }
      }
    }
    ap_int<26> v11903 = pw7;	// L18531
    v11754.write(v11903);	// L18532
  }
}

void rdrv_n_0(
  int32_t v11904[4][8],
  hls::stream< int32_t >& v11905,
  hls::stream< ap_uint<26> >& v11906,
  hls::stream< int32_t >& v11907,
  hls::stream< ap_uint<26> >& v11908,
  hls::stream< int32_t >& v11909,
  hls::stream< ap_uint<26> >& v11910,
  hls::stream< int32_t >& v11911,
  hls::stream< ap_uint<26> >& v11912
) {	// L18536
  int32_t dcred2[4];	// L18546
  for (int v11914 = 0; v11914 < 4; v11914++) {	// L18547
    dcred2[v11914] = 0;	// L18547
  }
  int32_t sp2[4];	// L18548
  for (int v11916 = 0; v11916 < 4; v11916++) {	// L18549
    sp2[v11916] = 0;	// L18549
  }
  l_S_t_0_t26: for (int t26 = 0; t26 < 8; t26++) {	// L18550
    int32_t v11918 = v11905.read();	// L18551
    int32_t v11919 = dcred2[0];	// L18552
    ap_int<33> v11920 = v11919;	// L18553
    ap_int<33> v11921 = v11918;	// L18554
    ap_int<33> v11922 = v11920 + v11921;	// L18555
    int32_t v11923 = v11922;	// L18556
    dcred2[0] = v11923;	// L18557
    ap_uint<26> pw8;	// L18558
    pw8 = 0;	// L18559
    int32_t v11925 = sp2[0];	// L18560
    bool v11926 = v11925 < 8;	// L18561
    if (v11926) {	// L18562
      ap_uint<26> cand8;	// L18563
      cand8 = 0;	// L18564
      int32_t v11928 = sp2[0];	// L18565
      int v11929 = v11928;	// L18566
      int32_t v11930 = v11904[0][v11929];	// L18567
      ap_uint<26> v11931 = v11930;	// L18568
      ap_int<26> v11932 = cand8;	// L18569
      ap_int<26> v11933;
      ap_int<26> v11933_tmp = v11932;
      v11933_tmp(25, 0) = v11931;
      v11933 = v11933_tmp;	// L18570
      cand8 = v11933;	// L18571
      ap_int<26> v11934 = cand8;	// L18572
      bool v11935;
      ap_int<26> v11935_tmp = v11934;
      v11935 = v11935_tmp[25];	// L18573
      int32_t v11936 = v11935;	// L18574
      bool v11937 = v11936 == 0;	// L18575
      if (v11937) {	// L18576
        int32_t v11938 = sp2[0];	// L18577
        ap_int<33> v11939 = v11938;	// L18578
        ap_int<33> v11940 = v11939 + 1;	// L18579
        int32_t v11941 = v11940;	// L18580
        sp2[0] = v11941;	// L18581
      } else {
        int32_t v11942 = dcred2[0];	// L18583
        bool v11943 = v11942 > 0;	// L18584
        if (v11943) {	// L18585
          ap_int<26> v11944 = cand8;	// L18586
          pw8 = v11944;	// L18587
          int32_t v11945 = dcred2[0];	// L18588
          ap_int<33> v11946 = v11945;	// L18589
          ap_int<33> v11947 = v11946 - 1;	// L18590
          int32_t v11948 = v11947;	// L18591
          dcred2[0] = v11948;	// L18592
          int32_t v11949 = sp2[0];	// L18593
          ap_int<33> v11950 = v11949;	// L18594
          ap_int<33> v11951 = v11950 + 1;	// L18595
          int32_t v11952 = v11951;	// L18596
          sp2[0] = v11952;	// L18597
        }
      }
    }
    ap_int<26> v11953 = pw8;	// L18601
    v11906.write(v11953);	// L18602
    int32_t v11954 = v11907.read();	// L18603
    int32_t v11955 = dcred2[1];	// L18604
    ap_int<33> v11956 = v11955;	// L18605
    ap_int<33> v11957 = v11954;	// L18606
    ap_int<33> v11958 = v11956 + v11957;	// L18607
    int32_t v11959 = v11958;	// L18608
    dcred2[1] = v11959;	// L18609
    ap_uint<26> pw9;	// L18610
    pw9 = 0;	// L18611
    int32_t v11961 = sp2[1];	// L18612
    bool v11962 = v11961 < 8;	// L18613
    if (v11962) {	// L18614
      ap_uint<26> cand9;	// L18615
      cand9 = 0;	// L18616
      int32_t v11964 = sp2[1];	// L18617
      int v11965 = v11964;	// L18618
      int32_t v11966 = v11904[1][v11965];	// L18619
      ap_uint<26> v11967 = v11966;	// L18620
      ap_int<26> v11968 = cand9;	// L18621
      ap_int<26> v11969;
      ap_int<26> v11969_tmp = v11968;
      v11969_tmp(25, 0) = v11967;
      v11969 = v11969_tmp;	// L18622
      cand9 = v11969;	// L18623
      ap_int<26> v11970 = cand9;	// L18624
      bool v11971;
      ap_int<26> v11971_tmp = v11970;
      v11971 = v11971_tmp[25];	// L18625
      int32_t v11972 = v11971;	// L18626
      bool v11973 = v11972 == 0;	// L18627
      if (v11973) {	// L18628
        int32_t v11974 = sp2[1];	// L18629
        ap_int<33> v11975 = v11974;	// L18630
        ap_int<33> v11976 = v11975 + 1;	// L18631
        int32_t v11977 = v11976;	// L18632
        sp2[1] = v11977;	// L18633
      } else {
        int32_t v11978 = dcred2[1];	// L18635
        bool v11979 = v11978 > 0;	// L18636
        if (v11979) {	// L18637
          ap_int<26> v11980 = cand9;	// L18638
          pw9 = v11980;	// L18639
          int32_t v11981 = dcred2[1];	// L18640
          ap_int<33> v11982 = v11981;	// L18641
          ap_int<33> v11983 = v11982 - 1;	// L18642
          int32_t v11984 = v11983;	// L18643
          dcred2[1] = v11984;	// L18644
          int32_t v11985 = sp2[1];	// L18645
          ap_int<33> v11986 = v11985;	// L18646
          ap_int<33> v11987 = v11986 + 1;	// L18647
          int32_t v11988 = v11987;	// L18648
          sp2[1] = v11988;	// L18649
        }
      }
    }
    ap_int<26> v11989 = pw9;	// L18653
    v11908.write(v11989);	// L18654
    int32_t v11990 = v11909.read();	// L18655
    int32_t v11991 = dcred2[2];	// L18656
    ap_int<33> v11992 = v11991;	// L18657
    ap_int<33> v11993 = v11990;	// L18658
    ap_int<33> v11994 = v11992 + v11993;	// L18659
    int32_t v11995 = v11994;	// L18660
    dcred2[2] = v11995;	// L18661
    ap_uint<26> pw10;	// L18662
    pw10 = 0;	// L18663
    int32_t v11997 = sp2[2];	// L18664
    bool v11998 = v11997 < 8;	// L18665
    if (v11998) {	// L18666
      ap_uint<26> cand10;	// L18667
      cand10 = 0;	// L18668
      int32_t v12000 = sp2[2];	// L18669
      int v12001 = v12000;	// L18670
      int32_t v12002 = v11904[2][v12001];	// L18671
      ap_uint<26> v12003 = v12002;	// L18672
      ap_int<26> v12004 = cand10;	// L18673
      ap_int<26> v12005;
      ap_int<26> v12005_tmp = v12004;
      v12005_tmp(25, 0) = v12003;
      v12005 = v12005_tmp;	// L18674
      cand10 = v12005;	// L18675
      ap_int<26> v12006 = cand10;	// L18676
      bool v12007;
      ap_int<26> v12007_tmp = v12006;
      v12007 = v12007_tmp[25];	// L18677
      int32_t v12008 = v12007;	// L18678
      bool v12009 = v12008 == 0;	// L18679
      if (v12009) {	// L18680
        int32_t v12010 = sp2[2];	// L18681
        ap_int<33> v12011 = v12010;	// L18682
        ap_int<33> v12012 = v12011 + 1;	// L18683
        int32_t v12013 = v12012;	// L18684
        sp2[2] = v12013;	// L18685
      } else {
        int32_t v12014 = dcred2[2];	// L18687
        bool v12015 = v12014 > 0;	// L18688
        if (v12015) {	// L18689
          ap_int<26> v12016 = cand10;	// L18690
          pw10 = v12016;	// L18691
          int32_t v12017 = dcred2[2];	// L18692
          ap_int<33> v12018 = v12017;	// L18693
          ap_int<33> v12019 = v12018 - 1;	// L18694
          int32_t v12020 = v12019;	// L18695
          dcred2[2] = v12020;	// L18696
          int32_t v12021 = sp2[2];	// L18697
          ap_int<33> v12022 = v12021;	// L18698
          ap_int<33> v12023 = v12022 + 1;	// L18699
          int32_t v12024 = v12023;	// L18700
          sp2[2] = v12024;	// L18701
        }
      }
    }
    ap_int<26> v12025 = pw10;	// L18705
    v11910.write(v12025);	// L18706
    int32_t v12026 = v11911.read();	// L18707
    int32_t v12027 = dcred2[3];	// L18708
    ap_int<33> v12028 = v12027;	// L18709
    ap_int<33> v12029 = v12026;	// L18710
    ap_int<33> v12030 = v12028 + v12029;	// L18711
    int32_t v12031 = v12030;	// L18712
    dcred2[3] = v12031;	// L18713
    ap_uint<26> pw11;	// L18714
    pw11 = 0;	// L18715
    int32_t v12033 = sp2[3];	// L18716
    bool v12034 = v12033 < 8;	// L18717
    if (v12034) {	// L18718
      ap_uint<26> cand11;	// L18719
      cand11 = 0;	// L18720
      int32_t v12036 = sp2[3];	// L18721
      int v12037 = v12036;	// L18722
      int32_t v12038 = v11904[3][v12037];	// L18723
      ap_uint<26> v12039 = v12038;	// L18724
      ap_int<26> v12040 = cand11;	// L18725
      ap_int<26> v12041;
      ap_int<26> v12041_tmp = v12040;
      v12041_tmp(25, 0) = v12039;
      v12041 = v12041_tmp;	// L18726
      cand11 = v12041;	// L18727
      ap_int<26> v12042 = cand11;	// L18728
      bool v12043;
      ap_int<26> v12043_tmp = v12042;
      v12043 = v12043_tmp[25];	// L18729
      int32_t v12044 = v12043;	// L18730
      bool v12045 = v12044 == 0;	// L18731
      if (v12045) {	// L18732
        int32_t v12046 = sp2[3];	// L18733
        ap_int<33> v12047 = v12046;	// L18734
        ap_int<33> v12048 = v12047 + 1;	// L18735
        int32_t v12049 = v12048;	// L18736
        sp2[3] = v12049;	// L18737
      } else {
        int32_t v12050 = dcred2[3];	// L18739
        bool v12051 = v12050 > 0;	// L18740
        if (v12051) {	// L18741
          ap_int<26> v12052 = cand11;	// L18742
          pw11 = v12052;	// L18743
          int32_t v12053 = dcred2[3];	// L18744
          ap_int<33> v12054 = v12053;	// L18745
          ap_int<33> v12055 = v12054 - 1;	// L18746
          int32_t v12056 = v12055;	// L18747
          dcred2[3] = v12056;	// L18748
          int32_t v12057 = sp2[3];	// L18749
          ap_int<33> v12058 = v12057;	// L18750
          ap_int<33> v12059 = v12058 + 1;	// L18751
          int32_t v12060 = v12059;	// L18752
          sp2[3] = v12060;	// L18753
        }
      }
    }
    ap_int<26> v12061 = pw11;	// L18757
    v11912.write(v12061);	// L18758
  }
}

void rdrv_s_0(
  int32_t v12062[4][8],
  hls::stream< int32_t >& v12063,
  hls::stream< ap_uint<26> >& v12064,
  hls::stream< int32_t >& v12065,
  hls::stream< ap_uint<26> >& v12066,
  hls::stream< int32_t >& v12067,
  hls::stream< ap_uint<26> >& v12068,
  hls::stream< int32_t >& v12069,
  hls::stream< ap_uint<26> >& v12070
) {	// L18762
  int32_t dcred3[4];	// L18772
  for (int v12072 = 0; v12072 < 4; v12072++) {	// L18773
    dcred3[v12072] = 0;	// L18773
  }
  int32_t sp3[4];	// L18774
  for (int v12074 = 0; v12074 < 4; v12074++) {	// L18775
    sp3[v12074] = 0;	// L18775
  }
  l_S_t_0_t27: for (int t27 = 0; t27 < 8; t27++) {	// L18776
    int32_t v12076 = v12063.read();	// L18777
    int32_t v12077 = dcred3[0];	// L18778
    ap_int<33> v12078 = v12077;	// L18779
    ap_int<33> v12079 = v12076;	// L18780
    ap_int<33> v12080 = v12078 + v12079;	// L18781
    int32_t v12081 = v12080;	// L18782
    dcred3[0] = v12081;	// L18783
    ap_uint<26> pw12;	// L18784
    pw12 = 0;	// L18785
    int32_t v12083 = sp3[0];	// L18786
    bool v12084 = v12083 < 8;	// L18787
    if (v12084) {	// L18788
      ap_uint<26> cand12;	// L18789
      cand12 = 0;	// L18790
      int32_t v12086 = sp3[0];	// L18791
      int v12087 = v12086;	// L18792
      int32_t v12088 = v12062[0][v12087];	// L18793
      ap_uint<26> v12089 = v12088;	// L18794
      ap_int<26> v12090 = cand12;	// L18795
      ap_int<26> v12091;
      ap_int<26> v12091_tmp = v12090;
      v12091_tmp(25, 0) = v12089;
      v12091 = v12091_tmp;	// L18796
      cand12 = v12091;	// L18797
      ap_int<26> v12092 = cand12;	// L18798
      bool v12093;
      ap_int<26> v12093_tmp = v12092;
      v12093 = v12093_tmp[25];	// L18799
      int32_t v12094 = v12093;	// L18800
      bool v12095 = v12094 == 0;	// L18801
      if (v12095) {	// L18802
        int32_t v12096 = sp3[0];	// L18803
        ap_int<33> v12097 = v12096;	// L18804
        ap_int<33> v12098 = v12097 + 1;	// L18805
        int32_t v12099 = v12098;	// L18806
        sp3[0] = v12099;	// L18807
      } else {
        int32_t v12100 = dcred3[0];	// L18809
        bool v12101 = v12100 > 0;	// L18810
        if (v12101) {	// L18811
          ap_int<26> v12102 = cand12;	// L18812
          pw12 = v12102;	// L18813
          int32_t v12103 = dcred3[0];	// L18814
          ap_int<33> v12104 = v12103;	// L18815
          ap_int<33> v12105 = v12104 - 1;	// L18816
          int32_t v12106 = v12105;	// L18817
          dcred3[0] = v12106;	// L18818
          int32_t v12107 = sp3[0];	// L18819
          ap_int<33> v12108 = v12107;	// L18820
          ap_int<33> v12109 = v12108 + 1;	// L18821
          int32_t v12110 = v12109;	// L18822
          sp3[0] = v12110;	// L18823
        }
      }
    }
    ap_int<26> v12111 = pw12;	// L18827
    v12064.write(v12111);	// L18828
    int32_t v12112 = v12065.read();	// L18829
    int32_t v12113 = dcred3[1];	// L18830
    ap_int<33> v12114 = v12113;	// L18831
    ap_int<33> v12115 = v12112;	// L18832
    ap_int<33> v12116 = v12114 + v12115;	// L18833
    int32_t v12117 = v12116;	// L18834
    dcred3[1] = v12117;	// L18835
    ap_uint<26> pw13;	// L18836
    pw13 = 0;	// L18837
    int32_t v12119 = sp3[1];	// L18838
    bool v12120 = v12119 < 8;	// L18839
    if (v12120) {	// L18840
      ap_uint<26> cand13;	// L18841
      cand13 = 0;	// L18842
      int32_t v12122 = sp3[1];	// L18843
      int v12123 = v12122;	// L18844
      int32_t v12124 = v12062[1][v12123];	// L18845
      ap_uint<26> v12125 = v12124;	// L18846
      ap_int<26> v12126 = cand13;	// L18847
      ap_int<26> v12127;
      ap_int<26> v12127_tmp = v12126;
      v12127_tmp(25, 0) = v12125;
      v12127 = v12127_tmp;	// L18848
      cand13 = v12127;	// L18849
      ap_int<26> v12128 = cand13;	// L18850
      bool v12129;
      ap_int<26> v12129_tmp = v12128;
      v12129 = v12129_tmp[25];	// L18851
      int32_t v12130 = v12129;	// L18852
      bool v12131 = v12130 == 0;	// L18853
      if (v12131) {	// L18854
        int32_t v12132 = sp3[1];	// L18855
        ap_int<33> v12133 = v12132;	// L18856
        ap_int<33> v12134 = v12133 + 1;	// L18857
        int32_t v12135 = v12134;	// L18858
        sp3[1] = v12135;	// L18859
      } else {
        int32_t v12136 = dcred3[1];	// L18861
        bool v12137 = v12136 > 0;	// L18862
        if (v12137) {	// L18863
          ap_int<26> v12138 = cand13;	// L18864
          pw13 = v12138;	// L18865
          int32_t v12139 = dcred3[1];	// L18866
          ap_int<33> v12140 = v12139;	// L18867
          ap_int<33> v12141 = v12140 - 1;	// L18868
          int32_t v12142 = v12141;	// L18869
          dcred3[1] = v12142;	// L18870
          int32_t v12143 = sp3[1];	// L18871
          ap_int<33> v12144 = v12143;	// L18872
          ap_int<33> v12145 = v12144 + 1;	// L18873
          int32_t v12146 = v12145;	// L18874
          sp3[1] = v12146;	// L18875
        }
      }
    }
    ap_int<26> v12147 = pw13;	// L18879
    v12066.write(v12147);	// L18880
    int32_t v12148 = v12067.read();	// L18881
    int32_t v12149 = dcred3[2];	// L18882
    ap_int<33> v12150 = v12149;	// L18883
    ap_int<33> v12151 = v12148;	// L18884
    ap_int<33> v12152 = v12150 + v12151;	// L18885
    int32_t v12153 = v12152;	// L18886
    dcred3[2] = v12153;	// L18887
    ap_uint<26> pw14;	// L18888
    pw14 = 0;	// L18889
    int32_t v12155 = sp3[2];	// L18890
    bool v12156 = v12155 < 8;	// L18891
    if (v12156) {	// L18892
      ap_uint<26> cand14;	// L18893
      cand14 = 0;	// L18894
      int32_t v12158 = sp3[2];	// L18895
      int v12159 = v12158;	// L18896
      int32_t v12160 = v12062[2][v12159];	// L18897
      ap_uint<26> v12161 = v12160;	// L18898
      ap_int<26> v12162 = cand14;	// L18899
      ap_int<26> v12163;
      ap_int<26> v12163_tmp = v12162;
      v12163_tmp(25, 0) = v12161;
      v12163 = v12163_tmp;	// L18900
      cand14 = v12163;	// L18901
      ap_int<26> v12164 = cand14;	// L18902
      bool v12165;
      ap_int<26> v12165_tmp = v12164;
      v12165 = v12165_tmp[25];	// L18903
      int32_t v12166 = v12165;	// L18904
      bool v12167 = v12166 == 0;	// L18905
      if (v12167) {	// L18906
        int32_t v12168 = sp3[2];	// L18907
        ap_int<33> v12169 = v12168;	// L18908
        ap_int<33> v12170 = v12169 + 1;	// L18909
        int32_t v12171 = v12170;	// L18910
        sp3[2] = v12171;	// L18911
      } else {
        int32_t v12172 = dcred3[2];	// L18913
        bool v12173 = v12172 > 0;	// L18914
        if (v12173) {	// L18915
          ap_int<26> v12174 = cand14;	// L18916
          pw14 = v12174;	// L18917
          int32_t v12175 = dcred3[2];	// L18918
          ap_int<33> v12176 = v12175;	// L18919
          ap_int<33> v12177 = v12176 - 1;	// L18920
          int32_t v12178 = v12177;	// L18921
          dcred3[2] = v12178;	// L18922
          int32_t v12179 = sp3[2];	// L18923
          ap_int<33> v12180 = v12179;	// L18924
          ap_int<33> v12181 = v12180 + 1;	// L18925
          int32_t v12182 = v12181;	// L18926
          sp3[2] = v12182;	// L18927
        }
      }
    }
    ap_int<26> v12183 = pw14;	// L18931
    v12068.write(v12183);	// L18932
    int32_t v12184 = v12069.read();	// L18933
    int32_t v12185 = dcred3[3];	// L18934
    ap_int<33> v12186 = v12185;	// L18935
    ap_int<33> v12187 = v12184;	// L18936
    ap_int<33> v12188 = v12186 + v12187;	// L18937
    int32_t v12189 = v12188;	// L18938
    dcred3[3] = v12189;	// L18939
    ap_uint<26> pw15;	// L18940
    pw15 = 0;	// L18941
    int32_t v12191 = sp3[3];	// L18942
    bool v12192 = v12191 < 8;	// L18943
    if (v12192) {	// L18944
      ap_uint<26> cand15;	// L18945
      cand15 = 0;	// L18946
      int32_t v12194 = sp3[3];	// L18947
      int v12195 = v12194;	// L18948
      int32_t v12196 = v12062[3][v12195];	// L18949
      ap_uint<26> v12197 = v12196;	// L18950
      ap_int<26> v12198 = cand15;	// L18951
      ap_int<26> v12199;
      ap_int<26> v12199_tmp = v12198;
      v12199_tmp(25, 0) = v12197;
      v12199 = v12199_tmp;	// L18952
      cand15 = v12199;	// L18953
      ap_int<26> v12200 = cand15;	// L18954
      bool v12201;
      ap_int<26> v12201_tmp = v12200;
      v12201 = v12201_tmp[25];	// L18955
      int32_t v12202 = v12201;	// L18956
      bool v12203 = v12202 == 0;	// L18957
      if (v12203) {	// L18958
        int32_t v12204 = sp3[3];	// L18959
        ap_int<33> v12205 = v12204;	// L18960
        ap_int<33> v12206 = v12205 + 1;	// L18961
        int32_t v12207 = v12206;	// L18962
        sp3[3] = v12207;	// L18963
      } else {
        int32_t v12208 = dcred3[3];	// L18965
        bool v12209 = v12208 > 0;	// L18966
        if (v12209) {	// L18967
          ap_int<26> v12210 = cand15;	// L18968
          pw15 = v12210;	// L18969
          int32_t v12211 = dcred3[3];	// L18970
          ap_int<33> v12212 = v12211;	// L18971
          ap_int<33> v12213 = v12212 - 1;	// L18972
          int32_t v12214 = v12213;	// L18973
          dcred3[3] = v12214;	// L18974
          int32_t v12215 = sp3[3];	// L18975
          ap_int<33> v12216 = v12215;	// L18976
          ap_int<33> v12217 = v12216 + 1;	// L18977
          int32_t v12218 = v12217;	// L18978
          sp3[3] = v12218;	// L18979
        }
      }
    }
    ap_int<26> v12219 = pw15;	// L18983
    v12070.write(v12219);	// L18984
  }
}

void rclc_w_0(
  int32_t v12220[4][8],
  hls::stream< int32_t >& v12221,
  hls::stream< ap_uint<26> >& v12222,
  hls::stream< int32_t >& v12223,
  hls::stream< ap_uint<26> >& v12224,
  hls::stream< int32_t >& v12225,
  hls::stream< ap_uint<26> >& v12226,
  hls::stream< int32_t >& v12227,
  hls::stream< ap_uint<26> >& v12228
) {	// L18988
  int32_t k4[4];	// L18999
  for (int v12230 = 0; v12230 < 4; v12230++) {	// L19000
    k4[v12230] = 0;	// L19000
  }
  int32_t cret[4];	// L19001
  for (int v12232 = 0; v12232 < 4; v12232++) {	// L19002
    cret[v12232] = 0;	// L19002
  }
  cret[0] = 2;	// L19003
  cret[1] = 2;	// L19004
  cret[2] = 2;	// L19005
  cret[3] = 2;	// L19006
  l_S_t_0_t28: for (int t28 = 0; t28 < 8; t28++) {	// L19007
    int32_t v12234 = cret[0];	// L19008
    v12221.write(v12234);	// L19009
    ap_uint<26> v12235 = v12222.read();	// L19010
    ap_uint<26> pw16;	// L19011
    pw16 = v12235;	// L19012
    cret[0] = 0;	// L19013
    ap_int<26> v12237 = pw16;	// L19014
    bool v12238;
    ap_int<26> v12238_tmp = v12237;
    v12238 = v12238_tmp[25];	// L19015
    int32_t v12239 = v12238;	// L19016
    bool v12240 = v12239 == 1;	// L19017
    if (v12240) {	// L19018
      cret[0] = 1;	// L19019
      int32_t v12241 = k4[0];	// L19020
      bool v12242 = v12241 < 8;	// L19021
      if (v12242) {	// L19022
        ap_int<26> v12243 = pw16;	// L19023
        int32_t v12244 = v12243;	// L19024
        int32_t v12245 = k4[0];	// L19025
        int v12246 = v12245;	// L19026
        v12220[0][v12246] = v12244;	// L19027
        int32_t v12247 = k4[0];	// L19028
        ap_int<33> v12248 = v12247;	// L19029
        ap_int<33> v12249 = v12248 + 1;	// L19030
        int32_t v12250 = v12249;	// L19031
        k4[0] = v12250;	// L19032
      }
    }
    int32_t v12251 = cret[1];	// L19035
    v12223.write(v12251);	// L19036
    ap_uint<26> v12252 = v12224.read();	// L19037
    ap_uint<26> pw17;	// L19038
    pw17 = v12252;	// L19039
    cret[1] = 0;	// L19040
    ap_int<26> v12254 = pw17;	// L19041
    bool v12255;
    ap_int<26> v12255_tmp = v12254;
    v12255 = v12255_tmp[25];	// L19042
    int32_t v12256 = v12255;	// L19043
    bool v12257 = v12256 == 1;	// L19044
    if (v12257) {	// L19045
      cret[1] = 1;	// L19046
      int32_t v12258 = k4[1];	// L19047
      bool v12259 = v12258 < 8;	// L19048
      if (v12259) {	// L19049
        ap_int<26> v12260 = pw17;	// L19050
        int32_t v12261 = v12260;	// L19051
        int32_t v12262 = k4[1];	// L19052
        int v12263 = v12262;	// L19053
        v12220[1][v12263] = v12261;	// L19054
        int32_t v12264 = k4[1];	// L19055
        ap_int<33> v12265 = v12264;	// L19056
        ap_int<33> v12266 = v12265 + 1;	// L19057
        int32_t v12267 = v12266;	// L19058
        k4[1] = v12267;	// L19059
      }
    }
    int32_t v12268 = cret[2];	// L19062
    v12225.write(v12268);	// L19063
    ap_uint<26> v12269 = v12226.read();	// L19064
    ap_uint<26> pw18;	// L19065
    pw18 = v12269;	// L19066
    cret[2] = 0;	// L19067
    ap_int<26> v12271 = pw18;	// L19068
    bool v12272;
    ap_int<26> v12272_tmp = v12271;
    v12272 = v12272_tmp[25];	// L19069
    int32_t v12273 = v12272;	// L19070
    bool v12274 = v12273 == 1;	// L19071
    if (v12274) {	// L19072
      cret[2] = 1;	// L19073
      int32_t v12275 = k4[2];	// L19074
      bool v12276 = v12275 < 8;	// L19075
      if (v12276) {	// L19076
        ap_int<26> v12277 = pw18;	// L19077
        int32_t v12278 = v12277;	// L19078
        int32_t v12279 = k4[2];	// L19079
        int v12280 = v12279;	// L19080
        v12220[2][v12280] = v12278;	// L19081
        int32_t v12281 = k4[2];	// L19082
        ap_int<33> v12282 = v12281;	// L19083
        ap_int<33> v12283 = v12282 + 1;	// L19084
        int32_t v12284 = v12283;	// L19085
        k4[2] = v12284;	// L19086
      }
    }
    int32_t v12285 = cret[3];	// L19089
    v12227.write(v12285);	// L19090
    ap_uint<26> v12286 = v12228.read();	// L19091
    ap_uint<26> pw19;	// L19092
    pw19 = v12286;	// L19093
    cret[3] = 0;	// L19094
    ap_int<26> v12288 = pw19;	// L19095
    bool v12289;
    ap_int<26> v12289_tmp = v12288;
    v12289 = v12289_tmp[25];	// L19096
    int32_t v12290 = v12289;	// L19097
    bool v12291 = v12290 == 1;	// L19098
    if (v12291) {	// L19099
      cret[3] = 1;	// L19100
      int32_t v12292 = k4[3];	// L19101
      bool v12293 = v12292 < 8;	// L19102
      if (v12293) {	// L19103
        ap_int<26> v12294 = pw19;	// L19104
        int32_t v12295 = v12294;	// L19105
        int32_t v12296 = k4[3];	// L19106
        int v12297 = v12296;	// L19107
        v12220[3][v12297] = v12295;	// L19108
        int32_t v12298 = k4[3];	// L19109
        ap_int<33> v12299 = v12298;	// L19110
        ap_int<33> v12300 = v12299 + 1;	// L19111
        int32_t v12301 = v12300;	// L19112
        k4[3] = v12301;	// L19113
      }
    }
  }
}

void rclc_e_0(
  int32_t v12302[4][8],
  hls::stream< int32_t >& v12303,
  hls::stream< ap_uint<26> >& v12304,
  hls::stream< int32_t >& v12305,
  hls::stream< ap_uint<26> >& v12306,
  hls::stream< int32_t >& v12307,
  hls::stream< ap_uint<26> >& v12308,
  hls::stream< int32_t >& v12309,
  hls::stream< ap_uint<26> >& v12310
) {	// L19119
  int32_t k5[4];	// L19130
  for (int v12312 = 0; v12312 < 4; v12312++) {	// L19131
    k5[v12312] = 0;	// L19131
  }
  int32_t cret1[4];	// L19132
  for (int v12314 = 0; v12314 < 4; v12314++) {	// L19133
    cret1[v12314] = 0;	// L19133
  }
  cret1[0] = 2;	// L19134
  cret1[1] = 2;	// L19135
  cret1[2] = 2;	// L19136
  cret1[3] = 2;	// L19137
  l_S_t_0_t29: for (int t29 = 0; t29 < 8; t29++) {	// L19138
    int32_t v12316 = cret1[0];	// L19139
    v12303.write(v12316);	// L19140
    ap_uint<26> v12317 = v12304.read();	// L19141
    ap_uint<26> pw20;	// L19142
    pw20 = v12317;	// L19143
    cret1[0] = 0;	// L19144
    ap_int<26> v12319 = pw20;	// L19145
    bool v12320;
    ap_int<26> v12320_tmp = v12319;
    v12320 = v12320_tmp[25];	// L19146
    int32_t v12321 = v12320;	// L19147
    bool v12322 = v12321 == 1;	// L19148
    if (v12322) {	// L19149
      cret1[0] = 1;	// L19150
      int32_t v12323 = k5[0];	// L19151
      bool v12324 = v12323 < 8;	// L19152
      if (v12324) {	// L19153
        ap_int<26> v12325 = pw20;	// L19154
        int32_t v12326 = v12325;	// L19155
        int32_t v12327 = k5[0];	// L19156
        int v12328 = v12327;	// L19157
        v12302[0][v12328] = v12326;	// L19158
        int32_t v12329 = k5[0];	// L19159
        ap_int<33> v12330 = v12329;	// L19160
        ap_int<33> v12331 = v12330 + 1;	// L19161
        int32_t v12332 = v12331;	// L19162
        k5[0] = v12332;	// L19163
      }
    }
    int32_t v12333 = cret1[1];	// L19166
    v12305.write(v12333);	// L19167
    ap_uint<26> v12334 = v12306.read();	// L19168
    ap_uint<26> pw21;	// L19169
    pw21 = v12334;	// L19170
    cret1[1] = 0;	// L19171
    ap_int<26> v12336 = pw21;	// L19172
    bool v12337;
    ap_int<26> v12337_tmp = v12336;
    v12337 = v12337_tmp[25];	// L19173
    int32_t v12338 = v12337;	// L19174
    bool v12339 = v12338 == 1;	// L19175
    if (v12339) {	// L19176
      cret1[1] = 1;	// L19177
      int32_t v12340 = k5[1];	// L19178
      bool v12341 = v12340 < 8;	// L19179
      if (v12341) {	// L19180
        ap_int<26> v12342 = pw21;	// L19181
        int32_t v12343 = v12342;	// L19182
        int32_t v12344 = k5[1];	// L19183
        int v12345 = v12344;	// L19184
        v12302[1][v12345] = v12343;	// L19185
        int32_t v12346 = k5[1];	// L19186
        ap_int<33> v12347 = v12346;	// L19187
        ap_int<33> v12348 = v12347 + 1;	// L19188
        int32_t v12349 = v12348;	// L19189
        k5[1] = v12349;	// L19190
      }
    }
    int32_t v12350 = cret1[2];	// L19193
    v12307.write(v12350);	// L19194
    ap_uint<26> v12351 = v12308.read();	// L19195
    ap_uint<26> pw22;	// L19196
    pw22 = v12351;	// L19197
    cret1[2] = 0;	// L19198
    ap_int<26> v12353 = pw22;	// L19199
    bool v12354;
    ap_int<26> v12354_tmp = v12353;
    v12354 = v12354_tmp[25];	// L19200
    int32_t v12355 = v12354;	// L19201
    bool v12356 = v12355 == 1;	// L19202
    if (v12356) {	// L19203
      cret1[2] = 1;	// L19204
      int32_t v12357 = k5[2];	// L19205
      bool v12358 = v12357 < 8;	// L19206
      if (v12358) {	// L19207
        ap_int<26> v12359 = pw22;	// L19208
        int32_t v12360 = v12359;	// L19209
        int32_t v12361 = k5[2];	// L19210
        int v12362 = v12361;	// L19211
        v12302[2][v12362] = v12360;	// L19212
        int32_t v12363 = k5[2];	// L19213
        ap_int<33> v12364 = v12363;	// L19214
        ap_int<33> v12365 = v12364 + 1;	// L19215
        int32_t v12366 = v12365;	// L19216
        k5[2] = v12366;	// L19217
      }
    }
    int32_t v12367 = cret1[3];	// L19220
    v12309.write(v12367);	// L19221
    ap_uint<26> v12368 = v12310.read();	// L19222
    ap_uint<26> pw23;	// L19223
    pw23 = v12368;	// L19224
    cret1[3] = 0;	// L19225
    ap_int<26> v12370 = pw23;	// L19226
    bool v12371;
    ap_int<26> v12371_tmp = v12370;
    v12371 = v12371_tmp[25];	// L19227
    int32_t v12372 = v12371;	// L19228
    bool v12373 = v12372 == 1;	// L19229
    if (v12373) {	// L19230
      cret1[3] = 1;	// L19231
      int32_t v12374 = k5[3];	// L19232
      bool v12375 = v12374 < 8;	// L19233
      if (v12375) {	// L19234
        ap_int<26> v12376 = pw23;	// L19235
        int32_t v12377 = v12376;	// L19236
        int32_t v12378 = k5[3];	// L19237
        int v12379 = v12378;	// L19238
        v12302[3][v12379] = v12377;	// L19239
        int32_t v12380 = k5[3];	// L19240
        ap_int<33> v12381 = v12380;	// L19241
        ap_int<33> v12382 = v12381 + 1;	// L19242
        int32_t v12383 = v12382;	// L19243
        k5[3] = v12383;	// L19244
      }
    }
  }
}

void rclc_n_0(
  int32_t v12384[4][8],
  hls::stream< int32_t >& v12385,
  hls::stream< ap_uint<26> >& v12386,
  hls::stream< int32_t >& v12387,
  hls::stream< ap_uint<26> >& v12388,
  hls::stream< int32_t >& v12389,
  hls::stream< ap_uint<26> >& v12390,
  hls::stream< int32_t >& v12391,
  hls::stream< ap_uint<26> >& v12392
) {	// L19250
  int32_t k6[4];	// L19261
  for (int v12394 = 0; v12394 < 4; v12394++) {	// L19262
    k6[v12394] = 0;	// L19262
  }
  int32_t cret2[4];	// L19263
  for (int v12396 = 0; v12396 < 4; v12396++) {	// L19264
    cret2[v12396] = 0;	// L19264
  }
  cret2[0] = 2;	// L19265
  cret2[1] = 2;	// L19266
  cret2[2] = 2;	// L19267
  cret2[3] = 2;	// L19268
  l_S_t_0_t30: for (int t30 = 0; t30 < 8; t30++) {	// L19269
    int32_t v12398 = cret2[0];	// L19270
    v12385.write(v12398);	// L19271
    ap_uint<26> v12399 = v12386.read();	// L19272
    ap_uint<26> pw24;	// L19273
    pw24 = v12399;	// L19274
    cret2[0] = 0;	// L19275
    ap_int<26> v12401 = pw24;	// L19276
    bool v12402;
    ap_int<26> v12402_tmp = v12401;
    v12402 = v12402_tmp[25];	// L19277
    int32_t v12403 = v12402;	// L19278
    bool v12404 = v12403 == 1;	// L19279
    if (v12404) {	// L19280
      cret2[0] = 1;	// L19281
      int32_t v12405 = k6[0];	// L19282
      bool v12406 = v12405 < 8;	// L19283
      if (v12406) {	// L19284
        ap_int<26> v12407 = pw24;	// L19285
        int32_t v12408 = v12407;	// L19286
        int32_t v12409 = k6[0];	// L19287
        int v12410 = v12409;	// L19288
        v12384[0][v12410] = v12408;	// L19289
        int32_t v12411 = k6[0];	// L19290
        ap_int<33> v12412 = v12411;	// L19291
        ap_int<33> v12413 = v12412 + 1;	// L19292
        int32_t v12414 = v12413;	// L19293
        k6[0] = v12414;	// L19294
      }
    }
    int32_t v12415 = cret2[1];	// L19297
    v12387.write(v12415);	// L19298
    ap_uint<26> v12416 = v12388.read();	// L19299
    ap_uint<26> pw25;	// L19300
    pw25 = v12416;	// L19301
    cret2[1] = 0;	// L19302
    ap_int<26> v12418 = pw25;	// L19303
    bool v12419;
    ap_int<26> v12419_tmp = v12418;
    v12419 = v12419_tmp[25];	// L19304
    int32_t v12420 = v12419;	// L19305
    bool v12421 = v12420 == 1;	// L19306
    if (v12421) {	// L19307
      cret2[1] = 1;	// L19308
      int32_t v12422 = k6[1];	// L19309
      bool v12423 = v12422 < 8;	// L19310
      if (v12423) {	// L19311
        ap_int<26> v12424 = pw25;	// L19312
        int32_t v12425 = v12424;	// L19313
        int32_t v12426 = k6[1];	// L19314
        int v12427 = v12426;	// L19315
        v12384[1][v12427] = v12425;	// L19316
        int32_t v12428 = k6[1];	// L19317
        ap_int<33> v12429 = v12428;	// L19318
        ap_int<33> v12430 = v12429 + 1;	// L19319
        int32_t v12431 = v12430;	// L19320
        k6[1] = v12431;	// L19321
      }
    }
    int32_t v12432 = cret2[2];	// L19324
    v12389.write(v12432);	// L19325
    ap_uint<26> v12433 = v12390.read();	// L19326
    ap_uint<26> pw26;	// L19327
    pw26 = v12433;	// L19328
    cret2[2] = 0;	// L19329
    ap_int<26> v12435 = pw26;	// L19330
    bool v12436;
    ap_int<26> v12436_tmp = v12435;
    v12436 = v12436_tmp[25];	// L19331
    int32_t v12437 = v12436;	// L19332
    bool v12438 = v12437 == 1;	// L19333
    if (v12438) {	// L19334
      cret2[2] = 1;	// L19335
      int32_t v12439 = k6[2];	// L19336
      bool v12440 = v12439 < 8;	// L19337
      if (v12440) {	// L19338
        ap_int<26> v12441 = pw26;	// L19339
        int32_t v12442 = v12441;	// L19340
        int32_t v12443 = k6[2];	// L19341
        int v12444 = v12443;	// L19342
        v12384[2][v12444] = v12442;	// L19343
        int32_t v12445 = k6[2];	// L19344
        ap_int<33> v12446 = v12445;	// L19345
        ap_int<33> v12447 = v12446 + 1;	// L19346
        int32_t v12448 = v12447;	// L19347
        k6[2] = v12448;	// L19348
      }
    }
    int32_t v12449 = cret2[3];	// L19351
    v12391.write(v12449);	// L19352
    ap_uint<26> v12450 = v12392.read();	// L19353
    ap_uint<26> pw27;	// L19354
    pw27 = v12450;	// L19355
    cret2[3] = 0;	// L19356
    ap_int<26> v12452 = pw27;	// L19357
    bool v12453;
    ap_int<26> v12453_tmp = v12452;
    v12453 = v12453_tmp[25];	// L19358
    int32_t v12454 = v12453;	// L19359
    bool v12455 = v12454 == 1;	// L19360
    if (v12455) {	// L19361
      cret2[3] = 1;	// L19362
      int32_t v12456 = k6[3];	// L19363
      bool v12457 = v12456 < 8;	// L19364
      if (v12457) {	// L19365
        ap_int<26> v12458 = pw27;	// L19366
        int32_t v12459 = v12458;	// L19367
        int32_t v12460 = k6[3];	// L19368
        int v12461 = v12460;	// L19369
        v12384[3][v12461] = v12459;	// L19370
        int32_t v12462 = k6[3];	// L19371
        ap_int<33> v12463 = v12462;	// L19372
        ap_int<33> v12464 = v12463 + 1;	// L19373
        int32_t v12465 = v12464;	// L19374
        k6[3] = v12465;	// L19375
      }
    }
  }
}

void rclc_s_0(
  int32_t v12466[4][8],
  hls::stream< int32_t >& v12467,
  hls::stream< ap_uint<26> >& v12468,
  hls::stream< int32_t >& v12469,
  hls::stream< ap_uint<26> >& v12470,
  hls::stream< int32_t >& v12471,
  hls::stream< ap_uint<26> >& v12472,
  hls::stream< int32_t >& v12473,
  hls::stream< ap_uint<26> >& v12474
) {	// L19381
  int32_t k7[4];	// L19392
  for (int v12476 = 0; v12476 < 4; v12476++) {	// L19393
    k7[v12476] = 0;	// L19393
  }
  int32_t cret3[4];	// L19394
  for (int v12478 = 0; v12478 < 4; v12478++) {	// L19395
    cret3[v12478] = 0;	// L19395
  }
  cret3[0] = 2;	// L19396
  cret3[1] = 2;	// L19397
  cret3[2] = 2;	// L19398
  cret3[3] = 2;	// L19399
  l_S_t_0_t31: for (int t31 = 0; t31 < 8; t31++) {	// L19400
    int32_t v12480 = cret3[0];	// L19401
    v12467.write(v12480);	// L19402
    ap_uint<26> v12481 = v12468.read();	// L19403
    ap_uint<26> pw28;	// L19404
    pw28 = v12481;	// L19405
    cret3[0] = 0;	// L19406
    ap_int<26> v12483 = pw28;	// L19407
    bool v12484;
    ap_int<26> v12484_tmp = v12483;
    v12484 = v12484_tmp[25];	// L19408
    int32_t v12485 = v12484;	// L19409
    bool v12486 = v12485 == 1;	// L19410
    if (v12486) {	// L19411
      cret3[0] = 1;	// L19412
      int32_t v12487 = k7[0];	// L19413
      bool v12488 = v12487 < 8;	// L19414
      if (v12488) {	// L19415
        ap_int<26> v12489 = pw28;	// L19416
        int32_t v12490 = v12489;	// L19417
        int32_t v12491 = k7[0];	// L19418
        int v12492 = v12491;	// L19419
        v12466[0][v12492] = v12490;	// L19420
        int32_t v12493 = k7[0];	// L19421
        ap_int<33> v12494 = v12493;	// L19422
        ap_int<33> v12495 = v12494 + 1;	// L19423
        int32_t v12496 = v12495;	// L19424
        k7[0] = v12496;	// L19425
      }
    }
    int32_t v12497 = cret3[1];	// L19428
    v12469.write(v12497);	// L19429
    ap_uint<26> v12498 = v12470.read();	// L19430
    ap_uint<26> pw29;	// L19431
    pw29 = v12498;	// L19432
    cret3[1] = 0;	// L19433
    ap_int<26> v12500 = pw29;	// L19434
    bool v12501;
    ap_int<26> v12501_tmp = v12500;
    v12501 = v12501_tmp[25];	// L19435
    int32_t v12502 = v12501;	// L19436
    bool v12503 = v12502 == 1;	// L19437
    if (v12503) {	// L19438
      cret3[1] = 1;	// L19439
      int32_t v12504 = k7[1];	// L19440
      bool v12505 = v12504 < 8;	// L19441
      if (v12505) {	// L19442
        ap_int<26> v12506 = pw29;	// L19443
        int32_t v12507 = v12506;	// L19444
        int32_t v12508 = k7[1];	// L19445
        int v12509 = v12508;	// L19446
        v12466[1][v12509] = v12507;	// L19447
        int32_t v12510 = k7[1];	// L19448
        ap_int<33> v12511 = v12510;	// L19449
        ap_int<33> v12512 = v12511 + 1;	// L19450
        int32_t v12513 = v12512;	// L19451
        k7[1] = v12513;	// L19452
      }
    }
    int32_t v12514 = cret3[2];	// L19455
    v12471.write(v12514);	// L19456
    ap_uint<26> v12515 = v12472.read();	// L19457
    ap_uint<26> pw30;	// L19458
    pw30 = v12515;	// L19459
    cret3[2] = 0;	// L19460
    ap_int<26> v12517 = pw30;	// L19461
    bool v12518;
    ap_int<26> v12518_tmp = v12517;
    v12518 = v12518_tmp[25];	// L19462
    int32_t v12519 = v12518;	// L19463
    bool v12520 = v12519 == 1;	// L19464
    if (v12520) {	// L19465
      cret3[2] = 1;	// L19466
      int32_t v12521 = k7[2];	// L19467
      bool v12522 = v12521 < 8;	// L19468
      if (v12522) {	// L19469
        ap_int<26> v12523 = pw30;	// L19470
        int32_t v12524 = v12523;	// L19471
        int32_t v12525 = k7[2];	// L19472
        int v12526 = v12525;	// L19473
        v12466[2][v12526] = v12524;	// L19474
        int32_t v12527 = k7[2];	// L19475
        ap_int<33> v12528 = v12527;	// L19476
        ap_int<33> v12529 = v12528 + 1;	// L19477
        int32_t v12530 = v12529;	// L19478
        k7[2] = v12530;	// L19479
      }
    }
    int32_t v12531 = cret3[3];	// L19482
    v12473.write(v12531);	// L19483
    ap_uint<26> v12532 = v12474.read();	// L19484
    ap_uint<26> pw31;	// L19485
    pw31 = v12532;	// L19486
    cret3[3] = 0;	// L19487
    ap_int<26> v12534 = pw31;	// L19488
    bool v12535;
    ap_int<26> v12535_tmp = v12534;
    v12535 = v12535_tmp[25];	// L19489
    int32_t v12536 = v12535;	// L19490
    bool v12537 = v12536 == 1;	// L19491
    if (v12537) {	// L19492
      cret3[3] = 1;	// L19493
      int32_t v12538 = k7[3];	// L19494
      bool v12539 = v12538 < 8;	// L19495
      if (v12539) {	// L19496
        ap_int<26> v12540 = pw31;	// L19497
        int32_t v12541 = v12540;	// L19498
        int32_t v12542 = k7[3];	// L19499
        int v12543 = v12542;	// L19500
        v12466[3][v12543] = v12541;	// L19501
        int32_t v12544 = k7[3];	// L19502
        ap_int<33> v12545 = v12544;	// L19503
        ap_int<33> v12546 = v12545 + 1;	// L19504
        int32_t v12547 = v12546;	// L19505
        k7[3] = v12547;	// L19506
      }
    }
  }
}

/// This is top function.
void top(
  half v12548[4][8],
  int32_t v12549[4][8],
  half v12550[4][8],
  int32_t v12551[4][8],
  half v12552[4][8],
  int32_t v12553[4][8],
  half v12554[4][8],
  int32_t v12555[4][8],
  half v12556[4][8],
  half v12557[4][8],
  half v12558[4][8],
  half v12559[4][8],
  int32_t v12560[4][8],
  int32_t v12561[4][8],
  int32_t v12562[4][8],
  int32_t v12563[4][8],
  int32_t v12564[4][8],
  int32_t v12565[4][8],
  int32_t v12566[4][8],
  int32_t v12567[4][8]
) {	// L19512
  #pragma HLS dataflow
  hls::stream< ap_uint<17> > v12568;
  #pragma HLS stream variable=v12568 depth=2	// L19513
  hls::stream< ap_uint<17> > v12569;
  #pragma HLS stream variable=v12569 depth=2	// L19514
  hls::stream< ap_uint<17> > v12570;
  #pragma HLS stream variable=v12570 depth=2	// L19515
  hls::stream< ap_uint<17> > v12571;
  #pragma HLS stream variable=v12571 depth=2	// L19516
  hls::stream< ap_uint<17> > v12572;
  #pragma HLS stream variable=v12572 depth=2	// L19517
  hls::stream< ap_uint<17> > v12573;
  #pragma HLS stream variable=v12573 depth=2	// L19518
  hls::stream< ap_uint<17> > v12574;
  #pragma HLS stream variable=v12574 depth=2	// L19519
  hls::stream< ap_uint<17> > v12575;
  #pragma HLS stream variable=v12575 depth=2	// L19520
  hls::stream< ap_uint<17> > v12576;
  #pragma HLS stream variable=v12576 depth=2	// L19521
  hls::stream< ap_uint<17> > v12577;
  #pragma HLS stream variable=v12577 depth=2	// L19522
  hls::stream< ap_uint<17> > v12578;
  #pragma HLS stream variable=v12578 depth=2	// L19523
  hls::stream< ap_uint<17> > v12579;
  #pragma HLS stream variable=v12579 depth=2	// L19524
  hls::stream< ap_uint<17> > v12580;
  #pragma HLS stream variable=v12580 depth=2	// L19525
  hls::stream< ap_uint<17> > v12581;
  #pragma HLS stream variable=v12581 depth=2	// L19526
  hls::stream< ap_uint<17> > v12582;
  #pragma HLS stream variable=v12582 depth=2	// L19527
  hls::stream< ap_uint<17> > v12583;
  #pragma HLS stream variable=v12583 depth=2	// L19528
  hls::stream< ap_uint<17> > v12584;
  #pragma HLS stream variable=v12584 depth=2	// L19529
  hls::stream< ap_uint<17> > v12585;
  #pragma HLS stream variable=v12585 depth=2	// L19530
  hls::stream< ap_uint<17> > v12586;
  #pragma HLS stream variable=v12586 depth=2	// L19531
  hls::stream< ap_uint<17> > v12587;
  #pragma HLS stream variable=v12587 depth=2	// L19532
  hls::stream< ap_uint<17> > v12588;
  #pragma HLS stream variable=v12588 depth=2	// L19533
  hls::stream< ap_uint<17> > v12589;
  #pragma HLS stream variable=v12589 depth=2	// L19534
  hls::stream< ap_uint<17> > v12590;
  #pragma HLS stream variable=v12590 depth=2	// L19535
  hls::stream< ap_uint<17> > v12591;
  #pragma HLS stream variable=v12591 depth=2	// L19536
  hls::stream< ap_uint<17> > v12592;
  #pragma HLS stream variable=v12592 depth=2	// L19537
  hls::stream< ap_uint<17> > v12593;
  #pragma HLS stream variable=v12593 depth=2	// L19538
  hls::stream< ap_uint<17> > v12594;
  #pragma HLS stream variable=v12594 depth=2	// L19539
  hls::stream< ap_uint<17> > v12595;
  #pragma HLS stream variable=v12595 depth=2	// L19540
  hls::stream< ap_uint<17> > v12596;
  #pragma HLS stream variable=v12596 depth=2	// L19541
  hls::stream< ap_uint<17> > v12597;
  #pragma HLS stream variable=v12597 depth=2	// L19542
  hls::stream< ap_uint<17> > v12598;
  #pragma HLS stream variable=v12598 depth=2	// L19543
  hls::stream< ap_uint<17> > v12599;
  #pragma HLS stream variable=v12599 depth=2	// L19544
  hls::stream< ap_uint<17> > v12600;
  #pragma HLS stream variable=v12600 depth=2	// L19545
  hls::stream< ap_uint<17> > v12601;
  #pragma HLS stream variable=v12601 depth=2	// L19546
  hls::stream< ap_uint<17> > v12602;
  #pragma HLS stream variable=v12602 depth=2	// L19547
  hls::stream< ap_uint<17> > v12603;
  #pragma HLS stream variable=v12603 depth=2	// L19548
  hls::stream< ap_uint<17> > v12604;
  #pragma HLS stream variable=v12604 depth=2	// L19549
  hls::stream< ap_uint<17> > v12605;
  #pragma HLS stream variable=v12605 depth=2	// L19550
  hls::stream< ap_uint<17> > v12606;
  #pragma HLS stream variable=v12606 depth=2	// L19551
  hls::stream< ap_uint<17> > v12607;
  #pragma HLS stream variable=v12607 depth=2	// L19552
  hls::stream< ap_uint<17> > v12608;
  #pragma HLS stream variable=v12608 depth=2	// L19553
  hls::stream< ap_uint<17> > v12609;
  #pragma HLS stream variable=v12609 depth=2	// L19554
  hls::stream< ap_uint<17> > v12610;
  #pragma HLS stream variable=v12610 depth=2	// L19555
  hls::stream< ap_uint<17> > v12611;
  #pragma HLS stream variable=v12611 depth=2	// L19556
  hls::stream< ap_uint<17> > v12612;
  #pragma HLS stream variable=v12612 depth=2	// L19557
  hls::stream< ap_uint<17> > v12613;
  #pragma HLS stream variable=v12613 depth=2	// L19558
  hls::stream< ap_uint<17> > v12614;
  #pragma HLS stream variable=v12614 depth=2	// L19559
  hls::stream< ap_uint<17> > v12615;
  #pragma HLS stream variable=v12615 depth=2	// L19560
  hls::stream< ap_uint<17> > v12616;
  #pragma HLS stream variable=v12616 depth=2	// L19561
  hls::stream< ap_uint<17> > v12617;
  #pragma HLS stream variable=v12617 depth=2	// L19562
  hls::stream< ap_uint<17> > v12618;
  #pragma HLS stream variable=v12618 depth=2	// L19563
  hls::stream< ap_uint<17> > v12619;
  #pragma HLS stream variable=v12619 depth=2	// L19564
  hls::stream< ap_uint<17> > v12620;
  #pragma HLS stream variable=v12620 depth=2	// L19565
  hls::stream< ap_uint<17> > v12621;
  #pragma HLS stream variable=v12621 depth=2	// L19566
  hls::stream< ap_uint<17> > v12622;
  #pragma HLS stream variable=v12622 depth=2	// L19567
  hls::stream< ap_uint<17> > v12623;
  #pragma HLS stream variable=v12623 depth=2	// L19568
  hls::stream< ap_uint<17> > v12624;
  #pragma HLS stream variable=v12624 depth=2	// L19569
  hls::stream< ap_uint<17> > v12625;
  #pragma HLS stream variable=v12625 depth=2	// L19570
  hls::stream< ap_uint<17> > v12626;
  #pragma HLS stream variable=v12626 depth=2	// L19571
  hls::stream< ap_uint<17> > v12627;
  #pragma HLS stream variable=v12627 depth=2	// L19572
  hls::stream< ap_uint<17> > v12628;
  #pragma HLS stream variable=v12628 depth=2	// L19573
  hls::stream< ap_uint<17> > v12629;
  #pragma HLS stream variable=v12629 depth=2	// L19574
  hls::stream< ap_uint<17> > v12630;
  #pragma HLS stream variable=v12630 depth=2	// L19575
  hls::stream< ap_uint<17> > v12631;
  #pragma HLS stream variable=v12631 depth=2	// L19576
  hls::stream< ap_uint<17> > v12632;
  #pragma HLS stream variable=v12632 depth=2	// L19577
  hls::stream< ap_uint<17> > v12633;
  #pragma HLS stream variable=v12633 depth=2	// L19578
  hls::stream< ap_uint<17> > v12634;
  #pragma HLS stream variable=v12634 depth=2	// L19579
  hls::stream< ap_uint<17> > v12635;
  #pragma HLS stream variable=v12635 depth=2	// L19580
  hls::stream< ap_uint<17> > v12636;
  #pragma HLS stream variable=v12636 depth=2	// L19581
  hls::stream< ap_uint<17> > v12637;
  #pragma HLS stream variable=v12637 depth=2	// L19582
  hls::stream< ap_uint<17> > v12638;
  #pragma HLS stream variable=v12638 depth=2	// L19583
  hls::stream< ap_uint<17> > v12639;
  #pragma HLS stream variable=v12639 depth=2	// L19584
  hls::stream< ap_uint<17> > v12640;
  #pragma HLS stream variable=v12640 depth=2	// L19585
  hls::stream< ap_uint<17> > v12641;
  #pragma HLS stream variable=v12641 depth=2	// L19586
  hls::stream< ap_uint<17> > v12642;
  #pragma HLS stream variable=v12642 depth=2	// L19587
  hls::stream< ap_uint<17> > v12643;
  #pragma HLS stream variable=v12643 depth=2	// L19588
  hls::stream< ap_uint<17> > v12644;
  #pragma HLS stream variable=v12644 depth=2	// L19589
  hls::stream< ap_uint<17> > v12645;
  #pragma HLS stream variable=v12645 depth=2	// L19590
  hls::stream< ap_uint<17> > v12646;
  #pragma HLS stream variable=v12646 depth=2	// L19591
  hls::stream< ap_uint<17> > v12647;
  #pragma HLS stream variable=v12647 depth=2	// L19592
  hls::stream< ap_uint<26> > v12648;
  #pragma HLS stream variable=v12648 depth=2	// L19593
  hls::stream< ap_uint<26> > v12649;
  #pragma HLS stream variable=v12649 depth=2	// L19594
  hls::stream< ap_uint<26> > v12650;
  #pragma HLS stream variable=v12650 depth=2	// L19595
  hls::stream< ap_uint<26> > v12651;
  #pragma HLS stream variable=v12651 depth=2	// L19596
  hls::stream< ap_uint<26> > v12652;
  #pragma HLS stream variable=v12652 depth=2	// L19597
  hls::stream< ap_uint<26> > v12653;
  #pragma HLS stream variable=v12653 depth=2	// L19598
  hls::stream< ap_uint<26> > v12654;
  #pragma HLS stream variable=v12654 depth=2	// L19599
  hls::stream< ap_uint<26> > v12655;
  #pragma HLS stream variable=v12655 depth=2	// L19600
  hls::stream< ap_uint<26> > v12656;
  #pragma HLS stream variable=v12656 depth=2	// L19601
  hls::stream< ap_uint<26> > v12657;
  #pragma HLS stream variable=v12657 depth=2	// L19602
  hls::stream< ap_uint<26> > v12658;
  #pragma HLS stream variable=v12658 depth=2	// L19603
  hls::stream< ap_uint<26> > v12659;
  #pragma HLS stream variable=v12659 depth=2	// L19604
  hls::stream< ap_uint<26> > v12660;
  #pragma HLS stream variable=v12660 depth=2	// L19605
  hls::stream< ap_uint<26> > v12661;
  #pragma HLS stream variable=v12661 depth=2	// L19606
  hls::stream< ap_uint<26> > v12662;
  #pragma HLS stream variable=v12662 depth=2	// L19607
  hls::stream< ap_uint<26> > v12663;
  #pragma HLS stream variable=v12663 depth=2	// L19608
  hls::stream< ap_uint<26> > v12664;
  #pragma HLS stream variable=v12664 depth=2	// L19609
  hls::stream< ap_uint<26> > v12665;
  #pragma HLS stream variable=v12665 depth=2	// L19610
  hls::stream< ap_uint<26> > v12666;
  #pragma HLS stream variable=v12666 depth=2	// L19611
  hls::stream< ap_uint<26> > v12667;
  #pragma HLS stream variable=v12667 depth=2	// L19612
  hls::stream< ap_uint<26> > v12668;
  #pragma HLS stream variable=v12668 depth=2	// L19613
  hls::stream< ap_uint<26> > v12669;
  #pragma HLS stream variable=v12669 depth=2	// L19614
  hls::stream< ap_uint<26> > v12670;
  #pragma HLS stream variable=v12670 depth=2	// L19615
  hls::stream< ap_uint<26> > v12671;
  #pragma HLS stream variable=v12671 depth=2	// L19616
  hls::stream< ap_uint<26> > v12672;
  #pragma HLS stream variable=v12672 depth=2	// L19617
  hls::stream< ap_uint<26> > v12673;
  #pragma HLS stream variable=v12673 depth=2	// L19618
  hls::stream< ap_uint<26> > v12674;
  #pragma HLS stream variable=v12674 depth=2	// L19619
  hls::stream< ap_uint<26> > v12675;
  #pragma HLS stream variable=v12675 depth=2	// L19620
  hls::stream< ap_uint<26> > v12676;
  #pragma HLS stream variable=v12676 depth=2	// L19621
  hls::stream< ap_uint<26> > v12677;
  #pragma HLS stream variable=v12677 depth=2	// L19622
  hls::stream< ap_uint<26> > v12678;
  #pragma HLS stream variable=v12678 depth=2	// L19623
  hls::stream< ap_uint<26> > v12679;
  #pragma HLS stream variable=v12679 depth=2	// L19624
  hls::stream< ap_uint<26> > v12680;
  #pragma HLS stream variable=v12680 depth=2	// L19625
  hls::stream< ap_uint<26> > v12681;
  #pragma HLS stream variable=v12681 depth=2	// L19626
  hls::stream< ap_uint<26> > v12682;
  #pragma HLS stream variable=v12682 depth=2	// L19627
  hls::stream< ap_uint<26> > v12683;
  #pragma HLS stream variable=v12683 depth=2	// L19628
  hls::stream< ap_uint<26> > v12684;
  #pragma HLS stream variable=v12684 depth=2	// L19629
  hls::stream< ap_uint<26> > v12685;
  #pragma HLS stream variable=v12685 depth=2	// L19630
  hls::stream< ap_uint<26> > v12686;
  #pragma HLS stream variable=v12686 depth=2	// L19631
  hls::stream< ap_uint<26> > v12687;
  #pragma HLS stream variable=v12687 depth=2	// L19632
  hls::stream< ap_uint<26> > v12688;
  #pragma HLS stream variable=v12688 depth=2	// L19633
  hls::stream< ap_uint<26> > v12689;
  #pragma HLS stream variable=v12689 depth=2	// L19634
  hls::stream< ap_uint<26> > v12690;
  #pragma HLS stream variable=v12690 depth=2	// L19635
  hls::stream< ap_uint<26> > v12691;
  #pragma HLS stream variable=v12691 depth=2	// L19636
  hls::stream< ap_uint<26> > v12692;
  #pragma HLS stream variable=v12692 depth=2	// L19637
  hls::stream< ap_uint<26> > v12693;
  #pragma HLS stream variable=v12693 depth=2	// L19638
  hls::stream< ap_uint<26> > v12694;
  #pragma HLS stream variable=v12694 depth=2	// L19639
  hls::stream< ap_uint<26> > v12695;
  #pragma HLS stream variable=v12695 depth=2	// L19640
  hls::stream< ap_uint<26> > v12696;
  #pragma HLS stream variable=v12696 depth=2	// L19641
  hls::stream< ap_uint<26> > v12697;
  #pragma HLS stream variable=v12697 depth=2	// L19642
  hls::stream< ap_uint<26> > v12698;
  #pragma HLS stream variable=v12698 depth=2	// L19643
  hls::stream< ap_uint<26> > v12699;
  #pragma HLS stream variable=v12699 depth=2	// L19644
  hls::stream< ap_uint<26> > v12700;
  #pragma HLS stream variable=v12700 depth=2	// L19645
  hls::stream< ap_uint<26> > v12701;
  #pragma HLS stream variable=v12701 depth=2	// L19646
  hls::stream< ap_uint<26> > v12702;
  #pragma HLS stream variable=v12702 depth=2	// L19647
  hls::stream< ap_uint<26> > v12703;
  #pragma HLS stream variable=v12703 depth=2	// L19648
  hls::stream< ap_uint<26> > v12704;
  #pragma HLS stream variable=v12704 depth=2	// L19649
  hls::stream< ap_uint<26> > v12705;
  #pragma HLS stream variable=v12705 depth=2	// L19650
  hls::stream< ap_uint<26> > v12706;
  #pragma HLS stream variable=v12706 depth=2	// L19651
  hls::stream< ap_uint<26> > v12707;
  #pragma HLS stream variable=v12707 depth=2	// L19652
  hls::stream< ap_uint<26> > v12708;
  #pragma HLS stream variable=v12708 depth=2	// L19653
  hls::stream< ap_uint<26> > v12709;
  #pragma HLS stream variable=v12709 depth=2	// L19654
  hls::stream< ap_uint<26> > v12710;
  #pragma HLS stream variable=v12710 depth=2	// L19655
  hls::stream< ap_uint<26> > v12711;
  #pragma HLS stream variable=v12711 depth=2	// L19656
  hls::stream< ap_uint<26> > v12712;
  #pragma HLS stream variable=v12712 depth=2	// L19657
  hls::stream< ap_uint<26> > v12713;
  #pragma HLS stream variable=v12713 depth=2	// L19658
  hls::stream< ap_uint<26> > v12714;
  #pragma HLS stream variable=v12714 depth=2	// L19659
  hls::stream< ap_uint<26> > v12715;
  #pragma HLS stream variable=v12715 depth=2	// L19660
  hls::stream< ap_uint<26> > v12716;
  #pragma HLS stream variable=v12716 depth=2	// L19661
  hls::stream< ap_uint<26> > v12717;
  #pragma HLS stream variable=v12717 depth=2	// L19662
  hls::stream< ap_uint<26> > v12718;
  #pragma HLS stream variable=v12718 depth=2	// L19663
  hls::stream< ap_uint<26> > v12719;
  #pragma HLS stream variable=v12719 depth=2	// L19664
  hls::stream< ap_uint<26> > v12720;
  #pragma HLS stream variable=v12720 depth=2	// L19665
  hls::stream< ap_uint<26> > v12721;
  #pragma HLS stream variable=v12721 depth=2	// L19666
  hls::stream< ap_uint<26> > v12722;
  #pragma HLS stream variable=v12722 depth=2	// L19667
  hls::stream< ap_uint<26> > v12723;
  #pragma HLS stream variable=v12723 depth=2	// L19668
  hls::stream< ap_uint<26> > v12724;
  #pragma HLS stream variable=v12724 depth=2	// L19669
  hls::stream< ap_uint<26> > v12725;
  #pragma HLS stream variable=v12725 depth=2	// L19670
  hls::stream< ap_uint<26> > v12726;
  #pragma HLS stream variable=v12726 depth=2	// L19671
  hls::stream< ap_uint<26> > v12727;
  #pragma HLS stream variable=v12727 depth=2	// L19672
  hls::stream< int32_t > v12728;
  #pragma HLS stream variable=v12728 depth=2	// L19673
  hls::stream< int32_t > v12729;
  #pragma HLS stream variable=v12729 depth=2	// L19674
  hls::stream< int32_t > v12730;
  #pragma HLS stream variable=v12730 depth=2	// L19675
  hls::stream< int32_t > v12731;
  #pragma HLS stream variable=v12731 depth=2	// L19676
  hls::stream< int32_t > v12732;
  #pragma HLS stream variable=v12732 depth=2	// L19677
  hls::stream< int32_t > v12733;
  #pragma HLS stream variable=v12733 depth=2	// L19678
  hls::stream< int32_t > v12734;
  #pragma HLS stream variable=v12734 depth=2	// L19679
  hls::stream< int32_t > v12735;
  #pragma HLS stream variable=v12735 depth=2	// L19680
  hls::stream< int32_t > v12736;
  #pragma HLS stream variable=v12736 depth=2	// L19681
  hls::stream< int32_t > v12737;
  #pragma HLS stream variable=v12737 depth=2	// L19682
  hls::stream< int32_t > v12738;
  #pragma HLS stream variable=v12738 depth=2	// L19683
  hls::stream< int32_t > v12739;
  #pragma HLS stream variable=v12739 depth=2	// L19684
  hls::stream< int32_t > v12740;
  #pragma HLS stream variable=v12740 depth=2	// L19685
  hls::stream< int32_t > v12741;
  #pragma HLS stream variable=v12741 depth=2	// L19686
  hls::stream< int32_t > v12742;
  #pragma HLS stream variable=v12742 depth=2	// L19687
  hls::stream< int32_t > v12743;
  #pragma HLS stream variable=v12743 depth=2	// L19688
  hls::stream< int32_t > v12744;
  #pragma HLS stream variable=v12744 depth=2	// L19689
  hls::stream< int32_t > v12745;
  #pragma HLS stream variable=v12745 depth=2	// L19690
  hls::stream< int32_t > v12746;
  #pragma HLS stream variable=v12746 depth=2	// L19691
  hls::stream< int32_t > v12747;
  #pragma HLS stream variable=v12747 depth=2	// L19692
  hls::stream< int32_t > v12748;
  #pragma HLS stream variable=v12748 depth=2	// L19693
  hls::stream< int32_t > v12749;
  #pragma HLS stream variable=v12749 depth=2	// L19694
  hls::stream< int32_t > v12750;
  #pragma HLS stream variable=v12750 depth=2	// L19695
  hls::stream< int32_t > v12751;
  #pragma HLS stream variable=v12751 depth=2	// L19696
  hls::stream< int32_t > v12752;
  #pragma HLS stream variable=v12752 depth=2	// L19697
  hls::stream< int32_t > v12753;
  #pragma HLS stream variable=v12753 depth=2	// L19698
  hls::stream< int32_t > v12754;
  #pragma HLS stream variable=v12754 depth=2	// L19699
  hls::stream< int32_t > v12755;
  #pragma HLS stream variable=v12755 depth=2	// L19700
  hls::stream< int32_t > v12756;
  #pragma HLS stream variable=v12756 depth=2	// L19701
  hls::stream< int32_t > v12757;
  #pragma HLS stream variable=v12757 depth=2	// L19702
  hls::stream< int32_t > v12758;
  #pragma HLS stream variable=v12758 depth=2	// L19703
  hls::stream< int32_t > v12759;
  #pragma HLS stream variable=v12759 depth=2	// L19704
  hls::stream< int32_t > v12760;
  #pragma HLS stream variable=v12760 depth=2	// L19705
  hls::stream< int32_t > v12761;
  #pragma HLS stream variable=v12761 depth=2	// L19706
  hls::stream< int32_t > v12762;
  #pragma HLS stream variable=v12762 depth=2	// L19707
  hls::stream< int32_t > v12763;
  #pragma HLS stream variable=v12763 depth=2	// L19708
  hls::stream< int32_t > v12764;
  #pragma HLS stream variable=v12764 depth=2	// L19709
  hls::stream< int32_t > v12765;
  #pragma HLS stream variable=v12765 depth=2	// L19710
  hls::stream< int32_t > v12766;
  #pragma HLS stream variable=v12766 depth=2	// L19711
  hls::stream< int32_t > v12767;
  #pragma HLS stream variable=v12767 depth=2	// L19712
  hls::stream< int32_t > v12768;
  #pragma HLS stream variable=v12768 depth=2	// L19713
  hls::stream< int32_t > v12769;
  #pragma HLS stream variable=v12769 depth=2	// L19714
  hls::stream< int32_t > v12770;
  #pragma HLS stream variable=v12770 depth=2	// L19715
  hls::stream< int32_t > v12771;
  #pragma HLS stream variable=v12771 depth=2	// L19716
  hls::stream< int32_t > v12772;
  #pragma HLS stream variable=v12772 depth=2	// L19717
  hls::stream< int32_t > v12773;
  #pragma HLS stream variable=v12773 depth=2	// L19718
  hls::stream< int32_t > v12774;
  #pragma HLS stream variable=v12774 depth=2	// L19719
  hls::stream< int32_t > v12775;
  #pragma HLS stream variable=v12775 depth=2	// L19720
  hls::stream< int32_t > v12776;
  #pragma HLS stream variable=v12776 depth=2	// L19721
  hls::stream< int32_t > v12777;
  #pragma HLS stream variable=v12777 depth=2	// L19722
  hls::stream< int32_t > v12778;
  #pragma HLS stream variable=v12778 depth=2	// L19723
  hls::stream< int32_t > v12779;
  #pragma HLS stream variable=v12779 depth=2	// L19724
  hls::stream< int32_t > v12780;
  #pragma HLS stream variable=v12780 depth=2	// L19725
  hls::stream< int32_t > v12781;
  #pragma HLS stream variable=v12781 depth=2	// L19726
  hls::stream< int32_t > v12782;
  #pragma HLS stream variable=v12782 depth=2	// L19727
  hls::stream< int32_t > v12783;
  #pragma HLS stream variable=v12783 depth=2	// L19728
  hls::stream< int32_t > v12784;
  #pragma HLS stream variable=v12784 depth=2	// L19729
  hls::stream< int32_t > v12785;
  #pragma HLS stream variable=v12785 depth=2	// L19730
  hls::stream< int32_t > v12786;
  #pragma HLS stream variable=v12786 depth=2	// L19731
  hls::stream< int32_t > v12787;
  #pragma HLS stream variable=v12787 depth=2	// L19732
  hls::stream< int32_t > v12788;
  #pragma HLS stream variable=v12788 depth=2	// L19733
  hls::stream< int32_t > v12789;
  #pragma HLS stream variable=v12789 depth=2	// L19734
  hls::stream< int32_t > v12790;
  #pragma HLS stream variable=v12790 depth=2	// L19735
  hls::stream< int32_t > v12791;
  #pragma HLS stream variable=v12791 depth=2	// L19736
  hls::stream< int32_t > v12792;
  #pragma HLS stream variable=v12792 depth=2	// L19737
  hls::stream< int32_t > v12793;
  #pragma HLS stream variable=v12793 depth=2	// L19738
  hls::stream< int32_t > v12794;
  #pragma HLS stream variable=v12794 depth=2	// L19739
  hls::stream< int32_t > v12795;
  #pragma HLS stream variable=v12795 depth=2	// L19740
  hls::stream< int32_t > v12796;
  #pragma HLS stream variable=v12796 depth=2	// L19741
  hls::stream< int32_t > v12797;
  #pragma HLS stream variable=v12797 depth=2	// L19742
  hls::stream< int32_t > v12798;
  #pragma HLS stream variable=v12798 depth=2	// L19743
  hls::stream< int32_t > v12799;
  #pragma HLS stream variable=v12799 depth=2	// L19744
  hls::stream< int32_t > v12800;
  #pragma HLS stream variable=v12800 depth=2	// L19745
  hls::stream< int32_t > v12801;
  #pragma HLS stream variable=v12801 depth=2	// L19746
  hls::stream< int32_t > v12802;
  #pragma HLS stream variable=v12802 depth=2	// L19747
  hls::stream< int32_t > v12803;
  #pragma HLS stream variable=v12803 depth=2	// L19748
  hls::stream< int32_t > v12804;
  #pragma HLS stream variable=v12804 depth=2	// L19749
  hls::stream< int32_t > v12805;
  #pragma HLS stream variable=v12805 depth=2	// L19750
  hls::stream< int32_t > v12806;
  #pragma HLS stream variable=v12806 depth=2	// L19751
  hls::stream< int32_t > v12807;
  #pragma HLS stream variable=v12807 depth=2	// L19752
  node_0_0(v12649, v12668, v12692, v12708, v12569, v12588, v12612, v12628, v12728, v12749, v12768, v12792, v12648, v12669, v12688, v12712, v12729, v12748, v12772, v12788, v12568, v12589, v12608, v12632);	// L19753
  node_0_1(v12650, v12669, v12693, v12709, v12570, v12589, v12613, v12629, v12729, v12750, v12769, v12793, v12649, v12670, v12689, v12713, v12730, v12749, v12773, v12789, v12569, v12590, v12609, v12633);	// L19754
  node_0_2(v12651, v12670, v12694, v12710, v12571, v12590, v12614, v12630, v12730, v12751, v12770, v12794, v12650, v12671, v12690, v12714, v12731, v12750, v12774, v12790, v12570, v12591, v12610, v12634);	// L19755
  node_0_3(v12652, v12671, v12695, v12711, v12572, v12591, v12615, v12631, v12731, v12752, v12771, v12795, v12651, v12672, v12691, v12715, v12732, v12751, v12775, v12791, v12571, v12592, v12611, v12635);	// L19756
  node_1_0(v12654, v12673, v12696, v12712, v12574, v12593, v12616, v12632, v12733, v12754, v12772, v12796, v12653, v12674, v12692, v12716, v12734, v12753, v12776, v12792, v12573, v12594, v12612, v12636);	// L19757
  node_1_1(v12655, v12674, v12697, v12713, v12575, v12594, v12617, v12633, v12734, v12755, v12773, v12797, v12654, v12675, v12693, v12717, v12735, v12754, v12777, v12793, v12574, v12595, v12613, v12637);	// L19758
  node_1_2(v12656, v12675, v12698, v12714, v12576, v12595, v12618, v12634, v12735, v12756, v12774, v12798, v12655, v12676, v12694, v12718, v12736, v12755, v12778, v12794, v12575, v12596, v12614, v12638);	// L19759
  node_1_3(v12657, v12676, v12699, v12715, v12577, v12596, v12619, v12635, v12736, v12757, v12775, v12799, v12656, v12677, v12695, v12719, v12737, v12756, v12779, v12795, v12576, v12597, v12615, v12639);	// L19760
  node_2_0(v12659, v12678, v12700, v12716, v12579, v12598, v12620, v12636, v12738, v12759, v12776, v12800, v12658, v12679, v12696, v12720, v12739, v12758, v12780, v12796, v12578, v12599, v12616, v12640);	// L19761
  node_2_1(v12660, v12679, v12701, v12717, v12580, v12599, v12621, v12637, v12739, v12760, v12777, v12801, v12659, v12680, v12697, v12721, v12740, v12759, v12781, v12797, v12579, v12600, v12617, v12641);	// L19762
  node_2_2(v12661, v12680, v12702, v12718, v12581, v12600, v12622, v12638, v12740, v12761, v12778, v12802, v12660, v12681, v12698, v12722, v12741, v12760, v12782, v12798, v12580, v12601, v12618, v12642);	// L19763
  node_2_3(v12662, v12681, v12703, v12719, v12582, v12601, v12623, v12639, v12741, v12762, v12779, v12803, v12661, v12682, v12699, v12723, v12742, v12761, v12783, v12799, v12581, v12602, v12619, v12643);	// L19764
  node_3_0(v12664, v12683, v12704, v12720, v12584, v12603, v12624, v12640, v12743, v12764, v12780, v12804, v12663, v12684, v12700, v12724, v12744, v12763, v12784, v12800, v12583, v12604, v12620, v12644);	// L19765
  node_3_1(v12665, v12684, v12705, v12721, v12585, v12604, v12625, v12641, v12744, v12765, v12781, v12805, v12664, v12685, v12701, v12725, v12745, v12764, v12785, v12801, v12584, v12605, v12621, v12645);	// L19766
  node_3_2(v12666, v12685, v12706, v12722, v12586, v12605, v12626, v12642, v12745, v12766, v12782, v12806, v12665, v12686, v12702, v12726, v12746, v12765, v12786, v12802, v12585, v12606, v12622, v12646);	// L19767
  node_3_3(v12667, v12686, v12707, v12723, v12587, v12606, v12627, v12643, v12746, v12767, v12783, v12807, v12666, v12687, v12703, v12727, v12747, v12766, v12787, v12803, v12586, v12607, v12623, v12647);	// L19768
  drv_w_0(v12548, v12549, v12568, v12573, v12578, v12583);	// L19769
  drv_e_0(v12550, v12551, v12592, v12597, v12602, v12607);	// L19770
  drv_n_0(v12552, v12553, v12608, v12609, v12610, v12611);	// L19771
  drv_s_0(v12554, v12555, v12644, v12645, v12646, v12647);	// L19772
  col_w_0(v12556, v12588, v12593, v12598, v12603);	// L19773
  col_e_0(v12557, v12572, v12577, v12582, v12587);	// L19774
  col_n_0(v12558, v12628, v12629, v12630, v12631);	// L19775
  col_s_0(v12559, v12624, v12625, v12626, v12627);	// L19776
  rdrv_w_0(v12560, v12728, v12648, v12733, v12653, v12738, v12658, v12743, v12663);	// L19777
  rdrv_e_0(v12561, v12752, v12672, v12757, v12677, v12762, v12682, v12767, v12687);	// L19778
  rdrv_n_0(v12562, v12768, v12688, v12769, v12689, v12770, v12690, v12771, v12691);	// L19779
  rdrv_s_0(v12563, v12804, v12724, v12805, v12725, v12806, v12726, v12807, v12727);	// L19780
  rclc_w_0(v12564, v12748, v12668, v12753, v12673, v12758, v12678, v12763, v12683);	// L19781
  rclc_e_0(v12565, v12732, v12652, v12737, v12657, v12742, v12662, v12747, v12667);	// L19782
  rclc_n_0(v12566, v12788, v12708, v12789, v12709, v12790, v12710, v12791, v12711);	// L19783
  rclc_s_0(v12567, v12784, v12704, v12785, v12705, v12786, v12706, v12787, v12707);	// L19784
}

